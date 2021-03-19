// Copyright (c) 2019 The DeepOnion developers
// Distributed under the MIT/X11 software license

#include <base58.h>
#include <net.h>
#include <rpc/safemode.h>
#include <rpc/server.h>
#include <validation.h>
#include <wallet/coincontrol.h>
#include <wallet/wallet.h>

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

UniValue getdeepsendinfo(const JSONRPCRequest& request)
{
	CWallet * const pwallet = GetWalletForJSONRPCRequest(request);
    if (!EnsureWalletIsAvailable(pwallet, request.fHelp)) {
        return NullUniValue;
    }

    if (request.fHelp || request.params.size() != 0)
	        throw std::runtime_error(
            "getdeepsendinfo\n"
            "Returns an object containing deepsend-related information."
			"\nResult:\n"
			"{\n"
			"  \"enabled\": true,             (boolean) If deepsend is enabled\n"
	        "  \"servicenodes\": 2,           (int) Currently connected service nodes\n"
            "  \"anontxinprogress\": true,    (boolean) If deepsend tx is in progress\n"
			"}\n"
			"\nExamples:\n"
			+ HelpExampleCli("getdeepsendinfo", "")
			+ HelpExampleRpc("getdeepsendinfo", "")
        );

    LOCK(cs_main);

    UniValue obj(UniValue::VOBJ);

    obj.push_back(Pair("enabled", CheckAnonymousServiceConditions() ));
    obj.push_back(Pair("servicenodes", g_connman->GetUpdatedServiceListCount() ));
    obj.push_back(Pair("anontxinprogress", IsCurrentAnonymousTxInProcess() ));

    return obj;
}

UniValue sendwithdeepsend(const JSONRPCRequest& request)
{
    CWallet * const pwallet = GetWalletForJSONRPCRequest(request);
    if (!EnsureWalletIsAvailable(pwallet, request.fHelp)) {
        return NullUniValue;
    }

    if (request.fHelp || request.params.size() < 2 || request.params.size() > 5)
        throw std::runtime_error(
            "sendwithdeepsend \"address\" amount \n"
            "\nSend an amount to a given address unisng deepsend service.\n"
            + HelpRequiringPassphrase(pwallet) +
            "\nArguments:\n"
            "1. \"address\"            (string, required) The DeepOnion address to send to.\n"
            "2. \"amount\"             (numeric or string, required) The amount in " + CURRENCY_UNIT + " to send. eg 0.1\n"
            "\nResult:\n"
            "\"txid\"                  (string) Info related with deepsend service.\n"
            "\nExamples:\n"
            + HelpExampleCli("sendwithdeepsend", "\"Dc7BLTLqSyWSp6uEpQPbbcb7figA7xHjKQ\" 0.123")
        );

    ObserveSafeMode();

    // Make sure the results are valid at least up to the most recent block
    // the user could have gotten from another RPC command prior to now
    pwallet->BlockUntilSyncedToCurrentChain();

    LOCK2(cs_main, pwallet->cs_wallet);

    // Destination address
    std::string sAddr = request.params[0].get_str();
    if (!IsValidDestination(DecodeDestination(sAddr))) {
        throw JSONRPCError(RPC_INVALID_ADDRESS_OR_KEY, "Invalid address");
    }

    // Amount
    CAmount nAmount = AmountFromValue(request.params[1]);
    if (nAmount <= 0)
        throw JSONRPCError(RPC_TYPE_ERROR, "Invalid amount for send");

    // check on deepsend
    CAmount mixerFee = 0;
    // also we allow max MAX_ALLOWED_DEEP_SEND ONION at a time using deepsend
	/*if(nAmount > MAX_ALLOWED_DEEP_SEND)
        return "DeepSend only allows maximum of %1 now. Please reduce send amount or use regular send.";*/

    // check if the wallet is synced
    if(IsInitialBlockDownload2())
        return "DeepSend requires the wallet to be synced.";

    // check if there are mixer/garantor available
    if(!(g_connman->GetUpdatedServiceListCount() > 1))
        return "DeepSend requires at least 2 anonymous service nodes available. You don't have enough service nodes connected. Please use regular-send or try later.";

    // check if another DeepSend still waiting
    if(IsCurrentAnonymousTxInProcess())
        return "Another DeepSend transaction still in progress. Please wait it finishes before starting a new DeepSend.";

    // need to make sure will have enough money to cover the 1% fee (minimum 0.01 ONION)
    mixerFee = DEEPSEND_FEE_RATE * nAmount;
    if(mixerFee < DEEPSEND_MIN_FEE)
        mixerFee = DEEPSEND_MIN_FEE;

    //need 2X amount for the transaction
    CAmount curBalance = pwallet->GetBalance();
    if((mixerFee + nAmount + nAmount) > curBalance)
        return "Not enough reserve for DeepSend. You must maintain at least 2X send amount + fee. Please use regular send.";

    CCoinControl coinControl;
    coinControl.SetDeepSend(true);

    std::vector< std::pair<std::string, CAmount> > vecSend;
    vecSend.push_back(std::make_pair(sAddr, nAmount));

    //Make sure wallet is either unflagged unlocked or unlocked and flagged for deepsend only
    if((pwallet->IsLocked() || (!pwallet->IsLocked() && !fWalletUnlockDeepSendOnly && fWalletUnlockStakingOnly)))
        return "Unlock wallet for DeepSend";
    
    std::string selfaddress = pwallet->GetRandomSelfAddress();
    if(selfaddress.length() == 0) {
        return "StartP2pMixerSendProcess failed - Create legacy addresses for and send ONION to them for DeepSend to work.";
    }


    bool b = StartP2pMixerSendProcess(vecSend, &coinControl);

    return b ? "StartP2pMixerSendProcess successfully started.": "StartP2pMixerSendProcess failed.";
}

static const CRPCCommand commands[] =
{ //  category              name                      actor (function)         argNames
  //  --------------------- ------------------------  -----------------------  ----------
    { "deepsend",           "getlastanontxinfo",      &getlastanontxinfo,      {} },
    { "deepsend",           "getdeepsendinfo",        &getdeepsendinfo,        {} },
    { "deepsend",           "listservicenodes",       &listservicenodes,       {} },
    { "deepsend",           "sendwithdeepsend",       &sendwithdeepsend,       {} },
};

void RegisterDeepSendRPCCommands(CRPCTable &t)
{
    for (unsigned int vcidx = 0; vcidx < ARRAYLEN(commands); vcidx++)
        t.appendCommand(commands[vcidx].name, &commands[vcidx]);
}
