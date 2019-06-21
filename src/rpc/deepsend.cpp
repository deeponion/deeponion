// Copyright (c) 2019 The DeepOnion developers
// Distributed under the MIT/X11 software license

#include <rpc/server.h>
#include <validation.h>

#include <univalue.h>

UniValue getlastanontxinfo(const JSONRPCRequest& request)
{
    if (request.fHelp || request.params.size() != 0) {
        throw std::runtime_error(
            "getlastanontxinfo\n"
            "\nReturns the last/current anonymous transaction info and log.\n"
            "\nResult:\n"
            "\"info\"                (string) The transaction info\n"
            "\nExamples:\n"
            + HelpExampleCli("getlastanontxinfo", "")
            + HelpExampleRpc("getlastanontxinfo", "")
        );
    }

    return pCurrentAnonymousTxInfo->GetLastAnonymousTxLog();
}

UniValue listservicenodes(const JSONRPCRequest& request)
{
    if (request.fHelp || request.params.size() != 0) {
        throw std::runtime_error(
            "listservicenodes\n"
            "\nLists the currently connected service nodes.\n"
            "\nResult:\n"
            "[                         (json array of strings)\n"
            "  \"nodeaddress\"         (string) The node tor address\n"
            "   ...\n"
            "]\n"
            "\nExamples:\n"
            + HelpExampleCli("listservicenodes", "")
            + HelpExampleRpc("listservicenodes", "")
        );
    }

    UniValue obj(UniValue::VARR);

    int sz = mapAnonymousServices.size();

    if(sz == 0)	{
        obj.push_back("No connected service nodes.\n");
    } else {
       for(std::map<std::string, std::string>::iterator it = mapAnonymousServices.begin(); it != mapAnonymousServices.end(); it++) {
           obj.push_back(it->second);
	   } 
    }

    return obj;   
}

static const CRPCCommand commands[] =
{ //  category              name                      actor (function)         argNames
  //  --------------------- ------------------------  -----------------------  ----------
    { "deepsend",           "getlastanontxinfo",      &getlastanontxinfo,      {} },
    { "deepsend",           "listservicenodes",       &listservicenodes,       {} },
};

void RegisterDeepSendRPCCommands(CRPCTable &t)
{
    for (unsigned int vcidx = 0; vcidx < ARRAYLEN(commands); vcidx++)
        t.appendCommand(commands[vcidx].name, &commands[vcidx]);
}
