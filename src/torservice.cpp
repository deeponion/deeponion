// Copyright (c) 2018 DeepOnion developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <torservice.h>
#include <chainparamsbase.h>
#include <utilstrencodings.h>
#include <netbase.h>
#include <net.h>
#include <util.h>
#include <crypto/hmac_sha256.h>

#include <vector>
#include <deque>
#include <set>
#include <stdlib.h>
#include <sys/stat.h>

#include <boost/bind.hpp>
#include <boost/signals2/signal.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/replace.hpp>

#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/util.h>
#include <event2/event.h>
#include <event2/thread.h>

extern "C" {
int tor_main(int argc, char *argv[]);
}


void SetupPluggableTransport(boost::optional<std::string> &plugin, struct stat *sb)
{
    std::string torPlugin = gArgs.GetArg("-torplugin", "");
    std::string torPluginPath = gArgs.GetArg("-torpluginpath", "");
    if (torPlugin == "meek")
    {
        LogPrintf("Using Tor with Pluggable Transport => MEEK\n");
#ifdef WIN32
        if (stat("meek-client.exe", sb) == 0 && (*sb).st_mode & S_IXUSR)
        {
            plugin = std::string("meek exec ") + std::string(torPluginPath);
        }
#else
        if ((stat("meek-client", sb) == 0 && (*sb).st_mode & S_IXUSR) || !std::system("which meek-client"))
        {
            plugin = std::string("meek exec ") + std::string(torPluginPath);
        }
#endif
    }
    else if (torPlugin == "obfs4")
    {
    	LogPrintf("Using Tor with Pluggable Transport => OBFS4\n");
#ifdef WIN32
        if (stat("obfs4proxy.exe", sb) == 0 && (*sb).st_mode & S_IXUSR)
        {
            plugin = std::string("obfs4 exec ") + std::string(torPluginPath);
        }
#else
        if ((stat("obfs4proxy", sb) == 0 && (*sb).st_mode & S_IXUSR) || !std::system("which obfs4proxy"))
        {
            plugin = std::string("obfs4 exec ") + std::string(torPluginPath);
        }
#endif
    }
}

static char *convert_str(const std::string &s)
{
    char *pc = new char[s.size() + 1];
    std::strcpy(pc, s.c_str());
    return pc;
}

/****** DeepOnion specific TorService implementation ********/

/**
 * Starts the Tor service.
 */
class TorService
{
public:
	TorService(struct event_base* base);
    ~TorService();
private:
    struct event_base* base;
};

TorService::TorService(struct event_base* _base):
    base(_base)
{
    LogPrintf("torservice: TorService in\n");
	bool fTestNet = gArgs.GetBoolArg("-testnet", false);
    boost::optional<std::string> clientTransportPlugin;
    struct stat sb;
    SetupPluggableTransport(clientTransportPlugin, &sb);

    fs::path tor_dir = GetDataDir() / "tor";
    fs::create_directory(tor_dir);
    fs::path log_file = tor_dir / "tor.log";

    std::vector<std::string> argv;
    argv.push_back("tor");
    argv.push_back("--Log");
    argv.push_back("notice file " + log_file.string());
    argv.push_back("--SocksPort");
    int torport = gArgs.GetArg("-torport", 9081);
    argv.push_back(std::to_string(torport));
    argv.push_back("--ignore-missing-torrc");
    argv.push_back("-f");
    std::string torrc = (tor_dir / "torrc").string();
    argv.push_back(torrc);
    argv.push_back("--DataDirectory");
    argv.push_back(tor_dir.string());
    argv.push_back("--GeoIPFile");
    argv.push_back((tor_dir / "geoip").string());
    argv.push_back("--GeoIPv6File");
    argv.push_back((tor_dir / "geoipv6").string());
    argv.push_back("--HiddenServiceDir");
    argv.push_back((tor_dir / "onion").string());
    argv.push_back("--HiddenServicePort");

    // If the port has changed then create the hidden service on a different port.
    int port = gArgs.GetArg("-port", -1);
    std::string sport = port != -1 ? std::to_string(port) : (fTestNet ? "26550"  : "17570");
    LogPrintf("torservice: Creating hidden service on port %s\n", sport);
    argv.push_back(sport);
    argv.push_back("--HiddenServiceVersion");
    argv.push_back("3");
    if (clientTransportPlugin)
    {
        argv.push_back("--ClientTransportPlugin");
        argv.push_back(*clientTransportPlugin);
        argv.push_back("--UseBridges");
        argv.push_back("1");
    }

    std::vector<char *> argv_c;
    std::transform(argv.begin(), argv.end(), std::back_inserter(argv_c), convert_str);

    tor_main(argv_c.size(), &argv_c[0]);
    LogPrintf("torservice: TorService out\n");

}

TorService::~TorService()
{

}

/****** Thread ********/
static struct event_base *gBase;
static boost::thread torServiceThread;

static void TorServiceThread()
{
	TorService ctrl(gBase);

    event_base_dispatch(gBase);
}

void StartTor(boost::thread_group& threadGroup, CScheduler& scheduler)
{
    LogPrintf("torservice: StartTor\n");
    assert(!gBase);
#ifdef WIN32
    evthread_use_windows_threads();
#else
    evthread_use_pthreads();
#endif
    gBase = event_base_new();
    if (!gBase) {
        LogPrintf("torservice: Unable to create event_base\n");
        return;
    }

    torServiceThread = boost::thread(boost::bind(&TraceThread<void (*)()>, "torservice", &TorServiceThread));
}

void InterruptTor()
{
    LogPrintf("torservice: InterruptTor\n");
    if (gBase) {
        LogPrintf("torservice: Thread interrupt\n");
        event_base_loopbreak(gBase);
    }
}

void StopTor()
{
    LogPrintf("torservice: StopTor\n");
    if (gBase) {
// Tests on OSX don't appear to have an issue with this, however other
// systems appear to not have their Tor thread exit so the join never returns.
// As we don't use the event base in it's intended way, we can probably remove it TODO:
// for now lets just test that the application exits cleanly without waiting for the thread to finish.
//    		torServiceThread.join();
        event_base_free(gBase);
        gBase = nullptr;
    }
}

