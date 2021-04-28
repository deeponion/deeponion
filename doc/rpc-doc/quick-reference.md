{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/quick-reference.md" %}

#### Quick Reference {#rpc-quick-reference}
{% include helpers/subhead-links.md %}

<!-- the summaries used below are defined in the files for the
     particular RPC and aggregated into this helper file by the makefile
     function manual-update-summaries-file. For example, to edit the
     summary for GetBestBlockHash, edit
     _includes/rpc/getbestblockhash.md and run `make manual-update-summaries`. -->
{% include helpers/summaries.md %}

#### Blockchain RPCs
{:.no_toc}
<!-- no subhead-links here -->

{% autocrossref %}

* [GetBestBlockHash][rpc getbestblockhash]: {{summary_getBestBlockHash}}
* [GetBlock][rpc getblock]: {{summary_getBlock}}
* [GetBlockChainInfo][rpc getblockchaininfo]: {{summary_getBlockChainInfo}}
* [GetBlockCount][rpc getblockcount]: {{summary_getBlockCount}}
* [GetBlockHash][rpc getblockhash]: {{summary_getBlockHash}}
* [GetBlockHeader][rpc getblockheader]: {{summary_getBlockHeader}}
* [GetChainTips][rpc getchaintips]: {{summary_getChainTips}}
* [GetChainTxStats][rpc getchaintxstats]: {{summary_getChainTxStats}}
* [GetDifficulty][rpc getdifficulty]: {{summary_getDifficulty}}
* [GetMemPoolAncestors][rpc getmempoolancestors]: {{summary_getMemPoolAncestors}}
* [GetMemPoolDescendants][rpc getmempooldescendants]: {{summary_getMemPoolDescendants}}
* [GetMemPoolEntry][rpc getmempoolentry]: {{summary_getMemPoolEntry}}
* [GetMemPoolInfo][rpc getmempoolinfo]: {{summary_getMemPoolInfo}}
* [GetRawMemPool][rpc getrawmempool]: {{summary_getRawMemPool}}
* [GetTxOut][rpc gettxout]: {{summary_getTxOut}}
* [GetTxOutProof][rpc gettxoutproof]: {{summary_getTxOutProof}}
* [GetTxOutSetInfo][rpc gettxoutsetinfo]: {{summary_getTxOutSetInfo}}
* [PreciousBlock][rpc preciousblock]: {{summary_preciousBlock}}
* [PruneBlockChain][rpc pruneblockchain]: {{summary_pruneBlockChain}}
* [SaveMemPool][rpc savemempool]: {{summary_saveMemPool}}
* [VerifyBlockChain][rpc verifyblockchain]: {{summary_verifyBlockChain}}
* [VerifyChain][rpc verifychain]: {{summary_verifyChain}}
* [VerifyTxOutProof][rpc verifytxoutproof]: {{summary_verifyTxOutProof}}

{% endautocrossref %}

#### Control RPCs
{:.no_toc}
<!-- no subhead-links here -->

{% autocrossref %}

* [GetMemoryInfo][rpc getmemoryinfo]: {{summary_getMemoryInfo}}
* [Help][rpc help]: {{summary_help}}
* [Logging][rpc logging]: {{summary_logging}}
* [Stop][rpc stop]: {{summary_stop}}
* [Uptime][rpc uptime]: {{summary_uptime}}

{% endautocrossref %}

#### Deepsend RPCs
{:.no_toc}
<!-- no subhead-links here -->

{% autocrossref %}

* [GetDeepSendInfo][rpc getdeepsendinfo]: {{summary_getDeepSendInfo}}
* [GetLastanonTxInfo][rpc getlastanontxinfo]: {{summary_getLastanonTxInfo}}
* [ListServiceNodeS][rpc listservicenodes]: {{summary_listServiceNodeS}}
* [SendWithdeepSend][rpc sendwithdeepsend]: {{summary_sendWithdeepSend}}

{% endautocrossref %}

#### Deepvault RPCs
{:.no_toc}
<!-- no subhead-links here -->

{% autocrossref %}

* [Dvregisterfile][rpc dvregisterfile]: {{summary_dvregisterfile}}
* [DvregisterfileHash][rpc dvregisterfilehash]: {{summary_dvregisterfileHash}}
* [Dvverifyfile][rpc dvverifyfile]: {{summary_dvverifyfile}}
* [DvverifyfileHash][rpc dvverifyfilehash]: {{summary_dvverifyfileHash}}

{% endautocrossref %}

#### Generating RPCs
{:.no_toc}
<!-- no subhead-links here -->

{% autocrossref %}

* [Generate][rpc generate]: {{summary_generate}}
* [GenerateToAddress][rpc generatetoaddress]: {{summary_generateToAddress}}

{% endautocrossref %}

#### Mining RPCs
{:.no_toc}
<!-- no subhead-links here -->

{% autocrossref %}

* [GetBlockTemplate][rpc getblocktemplate]: {{summary_getBlockTemplate}}
* [GetMiningInfo][rpc getmininginfo]: {{summary_getMiningInfo}}
* [GetNetworkHashPs][rpc getnetworkhashps]: {{summary_getNetworkHashPs}}
* [GetStakingInfo][rpc getstakinginfo]: {{summary_getStakingInfo}}
* [GetWork][rpc getwork]: {{summary_getWork}}
* [PrioritiseTransaction][rpc prioritisetransaction]: {{summary_prioritiseTransaction}}
* [SubmitBlock][rpc submitblock]: {{summary_submitBlock}}

{% endautocrossref %}

#### Network RPCs
{:.no_toc}
<!-- no subhead-links here -->

{% autocrossref %}

* [AddNode][rpc addnode]: {{summary_addNode}}
* [ClearBanned][rpc clearbanned]: {{summary_clearBanned}}
* [DisconnectNode][rpc disconnectnode]: {{summary_disconnectNode}}
* [GetAddedNodeInfo][rpc getaddednodeinfo]: {{summary_getAddedNodeInfo}}
* [GetConnectionCount][rpc getconnectioncount]: {{summary_getConnectionCount}}
* [GetNetTotals][rpc getnettotals]: {{summary_getNetTotals}}
* [GetNetworkInfo][rpc getnetworkinfo]: {{summary_getNetworkInfo}}
* [GetPeerInfo][rpc getpeerinfo]: {{summary_getPeerInfo}}
* [ListBanned][rpc listbanned]: {{summary_listBanned}}
* [Ping][rpc ping]: {{summary_ping-rpc}}
* [SetBan][rpc setban]: {{summary_setBan}}
* [SetNetworkActive][rpc setnetworkactive]: {{summary_setNetworkActive}}

{% endautocrossref %}

#### Rawtransactions RPCs
{:.no_toc}
<!-- no subhead-links here -->

{% autocrossref %}

* [CombineRawTransaction][rpc combinerawtransaction]: {{summary_combineRawTransaction}}
* [CreateRawTransaction][rpc createrawtransaction]: {{summary_createRawTransaction}}
* [DecodeRawTransaction][rpc decoderawtransaction]: {{summary_decodeRawTransaction}}
* [DecodeScript][rpc decodescript]: {{summary_decodeScript}}
* [FundRawTransaction][rpc fundrawtransaction]: {{summary_fundRawTransaction}}
* [GetRawTransaction][rpc getrawtransaction]: {{summary_getRawTransaction}}
* [SendRawTransaction][rpc sendrawtransaction]: {{summary_sendRawTransaction}}
* [SignRawTransaction][rpc signrawtransaction]: {{summary_signRawTransaction}}

{% endautocrossref %}

#### Stealth RPCs
{:.no_toc}
<!-- no subhead-links here -->

{% autocrossref %}

* [ExportstealthAddress][rpc exportstealthaddress]: {{summary_exportstealthAddress}}
* [GetNewstealthAddress][rpc getnewstealthaddress]: {{summary_getNewstealthAddress}}
* [ImportStealthAddress][rpc importstealthaddress]: {{summary_importStealthAddress}}
* [ListStealthAddressEs][rpc liststealthaddresses]: {{summary_listStealthAddressEs}}
* [SendTostealthAddress][rpc sendtostealthaddress]: {{summary_sendTostealthAddress}}

{% endautocrossref %}

#### Util RPCs
{:.no_toc}
<!-- no subhead-links here -->

{% autocrossref %}

* [CreateMultiSig][rpc createmultisig]: {{summary_createMultiSig}}
* [EstimateFee][rpc estimatefee]: {{summary_estimateFee}}
* [EstimateSmartFee][rpc estimatesmartfee]: {{summary_estimateSmartFee}}
* [SignMessageWithPrivKey][rpc signmessagewithprivkey]: {{summary_signMessageWithPrivKey}}
* [ValidateAddress][rpc validateaddress]: {{summary_validateAddress}}
* [VerifyMessage][rpc verifymessage]: {{summary_verifyMessage}}

{% endautocrossref %}

#### Wallet RPCs
{:.no_toc}
<!-- no subhead-links here -->

{% autocrossref %}

**Note:** the wallet RPCs are only available if Bitcoin Core was built
with [wallet support][]{:#term-wallet-support}{:.term}, which is the
default.

* [AbandonTransaction][rpc abandontransaction]: {{summary_abandonTransaction}}
* [AbortRescan][rpc abortrescan]: {{summary_abortRescan}}
* [AddMultiSigAddress][rpc addmultisigaddress]: {{summary_addMultiSigAddress}}
* [BackupWallet][rpc backupwallet]: {{summary_backupWallet}}
* [BumpFee][rpc bumpfee]: {{summary_bumpFee}}
* [DumpPrivKey][rpc dumpprivkey]: {{summary_dumpPrivKey}}
* [DumpWallet][rpc dumpwallet]: {{summary_dumpWallet}}
* [EncryptWallet][rpc encryptwallet]: {{summary_encryptWallet}}
* [GetAccount][rpc getaccount]: {{summary_getAccount}}
* [GetAccountAddress][rpc getaccountaddress]: {{summary_getAccountAddress}}
* [GetAddressesByAccount][rpc getaddressesbyaccount]: {{summary_getAddressesByAccount}}
* [GetBalance][rpc getbalance]: {{summary_getBalance}}
* [GetNewAddress][rpc getnewaddress]: {{summary_getNewAddress}}
* [GetRawChangeAddress][rpc getrawchangeaddress]: {{summary_getRawChangeAddress}}
* [GetReceivedByAccount][rpc getreceivedbyaccount]: {{summary_getReceivedByAccount}}
* [GetReceivedByAddress][rpc getreceivedbyaddress]: {{summary_getReceivedByAddress}}
* [GetTransaction][rpc gettransaction]: {{summary_getTransaction}}
* [GetUnconfirmedBalance][rpc getunconfirmedbalance]: {{summary_getUnconfirmedBalance}}
* [GetWalletInfo][rpc getwalletinfo]: {{summary_getWalletInfo}}
* [ImportAddress][rpc importaddress]: {{summary_importAddress}}
* [ImportMulti][rpc importmulti]: {{summary_importMulti}}
* [ImportPrivKey][rpc importprivkey]: {{summary_importPrivKey}}
* [ImportPrunedFunds][rpc importprunedfunds]: {{summary_importPrunedFunds}}
* [ImportPubKey][rpc importpubkey]: {{summary_importPubKey}}
* [ImportWallet][rpc importwallet]: {{summary_importWallet}}
* [KeyPoolRefill][rpc keypoolrefill]: {{summary_keyPoolRefill}}
* [ListAccounts][rpc listaccounts]: {{summary_listAccounts}}
* [ListAddressGroupings][rpc listaddressgroupings]: {{summary_listAddressGroupings}}
* [ListLockUnspent][rpc listlockunspent]: {{summary_listLockUnspent}}
* [ListReceivedByAccount][rpc listreceivedbyaccount]: {{summary_listReceivedByAccount}}
* [ListReceivedByAddress][rpc listreceivedbyaddress]: {{summary_listReceivedByAddress}}
* [ListSinceBlock][rpc listsinceblock]: {{summary_listSinceBlock}}
* [ListTransactions][rpc listtransactions]: {{summary_listTransactions}}
* [ListUnspent][rpc listunspent]: {{summary_listUnspent}}
* [ListWallets][rpc listwallets]: {{summary_listWallets}}
* [LockUnspent][rpc lockunspent]: {{summary_lockUnspent}}
* [MakeKeyPair][rpc makekeypair]: {{summary_makeKeyPair}}
* [Move][rpc move]: {{summary_move}}
* [RemovePrunedFunds][rpc removeprunedfunds]: {{summary_removePrunedFunds}}
* [RescanBlockChain][rpc rescanblockchain]: {{summary_rescanBlockChain}}
* [ReserveBalance][rpc reservebalance]: {{summary_reserveBalance}}
* [SendFrom][rpc sendfrom]: {{summary_sendFrom}}
* [SendMany][rpc sendmany]: {{summary_sendMany}}
* [SendToAddress][rpc sendtoaddress]: {{summary_sendToAddress}}
* [SetAccount][rpc setaccount]: {{summary_setAccount}}
* [SetTxFee][rpc settxfee]: {{summary_setTxFee}}
* [SignMessage][rpc signmessage]: {{summary_signMessage}}
* [WalletLock][rpc walletlock]: {{summary_walletLock}}
* [WalletPassphraseChange][rpc walletpassphrasechange]: {{summary_walletPassphraseChange}}

{% endautocrossref %}

