// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2017 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <protocol.h>

#include <util.h>
#include <utilstrencodings.h>

#ifndef WIN32
# include <arpa/inet.h>
#endif

namespace NetMsgType {
const char *VERSION="version";
const char *VERACK="verack";
const char *ADDR="addr";
const char *INV="inv";
const char *GETDATA="getdata";
const char *MERKLEBLOCK="merkleblock";
const char *GETBLOCKS="getblocks";
const char *GETHEADERS="getheaders";
const char *TX="tx";
const char *HEADERS="headers";
const char *BLOCK="block";
const char *GETADDR="getaddr";
const char *MEMPOOL="mempool";
const char *PING="ping";
const char *PONG="pong";
const char *NOTFOUND="notfound";
const char *FILTERLOAD="filterload";
const char *FILTERADD="filteradd";
const char *FILTERCLEAR="filterclear";
const char *REJECT="reject";
const char *SENDHEADERS="sendheaders";
const char *FEEFILTER="feefilter";
const char *SENDCMPCT="sendcmpct";
const char *CMPCTBLOCK="cmpctblock";
const char *GETBLOCKTXN="getblocktxn";
const char *BLOCKTXN="blocktxn";
// deepsend message types
const char *DS_SVCAVAIL="asvcavail";
const char *DS_SVCREPLY="asvcreply";
const char *DS_MIXREQ="mixrequest";
const char *DS_MIXREPLY="mixreply";
const char *DS_GRNTREQ="guarantreq";
const char *DS_GRNTREPLY="grntreply";
const char *DS_CHKGRNT="checkguarant";
const char *DS_CHKGRNTRPLY="chkgrtreply";
const char *DS_MSIGADDR="msigaddr";
const char *DS_MSIGADDRRPLY="msigreply";
const char *DS_CHKMSTX="checkmstx";
const char *DS_MSDISTTX="msdisttx";
const char *DS_MSTXRELAY="mstxrelay";
const char *DS_MSDISTRELAY="msdistrelay";
const char *DS_DSTTXCMPLT="dsttxcmplt";
const char *DS_CHKDTXRLAY="chkdtxrlay";
const char *DS_CHKDSTTXREQ="chkdsttxreq";
const char *DS_SENDCMPLT="sendcmplt";
const char *DS_SERVICEANN="dsserviceann";
const char *DS_CANCEL="canceldstx";
const char *DS_CANCELCMPLT="cancelcmplt";
const char *DS_MSIGMIXSENT="msigmixsent";
const char *DS_MSIGGRTSENT="msiggrtsent";
const char *DS_CHKSDRELAY="chksdrelay";
const char *DS_CHKSENDERTX="chksendertx";

} // namespace NetMsgType

/** All known message types. Keep this in the same order as the list of
 * messages above and in protocol.h.
 */
const static std::string allNetMessageTypes[] = {
    NetMsgType::VERSION,
    NetMsgType::VERACK,
    NetMsgType::ADDR,
    NetMsgType::INV,
    NetMsgType::GETDATA,
    NetMsgType::MERKLEBLOCK,
    NetMsgType::GETBLOCKS,
    NetMsgType::GETHEADERS,
    NetMsgType::TX,
    NetMsgType::HEADERS,
    NetMsgType::BLOCK,
    NetMsgType::GETADDR,
    NetMsgType::MEMPOOL,
    NetMsgType::PING,
    NetMsgType::PONG,
    NetMsgType::NOTFOUND,
    NetMsgType::FILTERLOAD,
    NetMsgType::FILTERADD,
    NetMsgType::FILTERCLEAR,
    NetMsgType::REJECT,
    NetMsgType::SENDHEADERS,
    NetMsgType::FEEFILTER,
    NetMsgType::SENDCMPCT,
    NetMsgType::CMPCTBLOCK,
    NetMsgType::GETBLOCKTXN,
    NetMsgType::BLOCKTXN,
    NetMsgType::DS_SVCAVAIL,
    NetMsgType::DS_SVCREPLY,
    NetMsgType::DS_MIXREQ,
    NetMsgType::DS_MIXREPLY,
    NetMsgType::DS_GRNTREQ,
    NetMsgType::DS_GRNTREPLY,
    NetMsgType::DS_CHKGRNT,
    NetMsgType::DS_CHKGRNTRPLY,
    NetMsgType::DS_MSIGADDR,
    NetMsgType::DS_MSIGADDRRPLY,
    NetMsgType::DS_CHKMSTX,
    NetMsgType::DS_MSDISTTX,
    NetMsgType::DS_MSTXRELAY,
    NetMsgType::DS_DSTTXCMPLT,
    NetMsgType::DS_CHKDTXRLAY,
    NetMsgType::DS_CHKDSTTXREQ,
    NetMsgType::DS_SENDCMPLT,
    NetMsgType::DS_SERVICEANN,
    NetMsgType::DS_CANCEL,
    NetMsgType::DS_CANCELCMPLT,
    NetMsgType::DS_MSIGMIXSENT,
    NetMsgType::DS_MSIGGRTSENT,
    NetMsgType::DS_CHKSDRELAY,
    NetMsgType::DS_CHKSENDERTX,	
};

const static std::vector<std::string> allNetMessageTypesVec(allNetMessageTypes, allNetMessageTypes+ARRAYLEN(allNetMessageTypes));

CMessageHeader::CMessageHeader(const MessageStartChars& pchMessageStartIn)
{
    memcpy(pchMessageStart, pchMessageStartIn, MESSAGE_START_SIZE);
    memset(pchCommand, 0, sizeof(pchCommand));
    nMessageSize = -1;
    memset(pchChecksum, 0, CHECKSUM_SIZE);
}

CMessageHeader::CMessageHeader(const MessageStartChars& pchMessageStartIn, const char* pszCommand, unsigned int nMessageSizeIn)
{
    memcpy(pchMessageStart, pchMessageStartIn, MESSAGE_START_SIZE);
    memset(pchCommand, 0, sizeof(pchCommand));
    strncpy(pchCommand, pszCommand, COMMAND_SIZE);
    nMessageSize = nMessageSizeIn;
    memset(pchChecksum, 0, CHECKSUM_SIZE);
}

std::string CMessageHeader::GetCommand() const
{
    return std::string(pchCommand, pchCommand + strnlen(pchCommand, COMMAND_SIZE));
}

bool CMessageHeader::IsValid(const MessageStartChars& pchMessageStartIn) const
{
    // Check start string
    if (memcmp(pchMessageStart, pchMessageStartIn, MESSAGE_START_SIZE) != 0)
        return false;

    // Check the command string for errors
    for (const char* p1 = pchCommand; p1 < pchCommand + COMMAND_SIZE; p1++)
    {
        if (*p1 == 0)
        {
            // Must be all zeros after the first zero
            for (; p1 < pchCommand + COMMAND_SIZE; p1++)
                if (*p1 != 0)
                    return false;
        }
        else if (*p1 < ' ' || *p1 > 0x7E)
            return false;
    }

    // Message size
    if (nMessageSize > MAX_SIZE)
    {
        LogPrintf("CMessageHeader::IsValid(): (%s, %u bytes) nMessageSize > MAX_SIZE\n", GetCommand(), nMessageSize);
        return false;
    }

    return true;
}



CAddress::CAddress() : CService()
{
    Init();
}

CAddress::CAddress(CService ipIn, ServiceFlags nServicesIn) : CService(ipIn)
{
    Init();
    nServices = nServicesIn;
}

void CAddress::Init()
{
    nServices = NODE_NONE;
    nTime = 100000000;
}

CInv::CInv()
{
    type = 0;
    hash.SetNull();
}

CInv::CInv(int typeIn, const uint256& hashIn) : type(typeIn), hash(hashIn) {}

bool operator<(const CInv& a, const CInv& b)
{
    return (a.type < b.type || (a.type == b.type && a.hash < b.hash));
}

std::string CInv::GetCommand() const
{
    std::string cmd;
    if (type & MSG_WITNESS_FLAG)
        cmd.append("witness-");
    int masked = type & MSG_TYPE_MASK;
    switch (masked)
    {
    case MSG_TX:             return cmd.append(NetMsgType::TX);
    case MSG_BLOCK:          return cmd.append(NetMsgType::BLOCK);
    case MSG_FILTERED_BLOCK: return cmd.append(NetMsgType::MERKLEBLOCK);
    case MSG_CMPCT_BLOCK:    return cmd.append(NetMsgType::CMPCTBLOCK);
    default:
        throw std::out_of_range(strprintf("CInv::GetCommand(): type=%d unknown type", type));
    }
}

std::string CInv::ToString() const
{
    try {
        return strprintf("%s %s", GetCommand(), hash.ToString());
    } catch(const std::out_of_range &) {
        return strprintf("0x%08x %s", type, hash.ToString());
    }
}

const std::vector<std::string> &getAllNetMessageTypes()
{
    return allNetMessageTypesVec;
}
