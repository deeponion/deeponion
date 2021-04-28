.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

RPC API Reference
=================

Blockchain RPCs
---------------

.. toctree::
  :maxdepth: 1

  getbestblockhash
  getblock
  getblockchaininfo
  getblockcount
  getblockhash
  getblockheader
  getchaintips
  getchaintxstats
  getdifficulty
  getmempoolancestors
  getmempooldescendants
  getmempoolentry
  getmempoolinfo
  getrawmempool
  gettxout
  gettxoutproof
  gettxoutsetinfo
  preciousblock
  pruneblockchain
  savemempool
  verifyblockchain
  verifychain
  verifytxoutproof

Control RPCs
------------

.. toctree::
  :maxdepth: 1

  getmemoryinfo
  help
  logging
  stop
  uptime

Deepsend RPCs
-------------

.. toctree::
  :maxdepth: 1

  getdeepsendinfo
  getlastanontxinfo
  listservicenodes
  sendwithdeepsend

Deepvault RPCs
--------------

.. toctree::
  :maxdepth: 1

  dvregisterfile
  dvregisterfilehash
  dvverifyfile
  dvverifyfilehash

Generating RPCs
---------------

.. toctree::
  :maxdepth: 1

  generate
  generatetoaddress

Mining RPCs
-----------

.. toctree::
  :maxdepth: 1

  getblocktemplate
  getmininginfo
  getnetworkhashps
  getstakinginfo
  getwork
  prioritisetransaction
  submitblock

Network RPCs
------------

.. toctree::
  :maxdepth: 1

  addnode
  clearbanned
  disconnectnode
  getaddednodeinfo
  getconnectioncount
  getnettotals
  getnetworkinfo
  getpeerinfo
  listbanned
  ping
  setban
  setnetworkactive

Rawtransactions RPCs
--------------------

.. toctree::
  :maxdepth: 1

  combinerawtransaction
  createrawtransaction
  decoderawtransaction
  decodescript
  fundrawtransaction
  getrawtransaction
  sendrawtransaction
  signrawtransaction

Stealth RPCs
------------

.. toctree::
  :maxdepth: 1

  exportstealthaddress
  getnewstealthaddress
  importstealthaddress
  liststealthaddresses
  sendtostealthaddress

Util RPCs
---------

.. toctree::
  :maxdepth: 1

  createmultisig
  estimatefee
  estimatesmartfee
  signmessagewithprivkey
  validateaddress
  verifymessage

Wallet RPCs
-----------

**Note:** the wallet RPCs are only available if Bitcoin Core was built
with wallet support, which is the default.

.. toctree::
  :maxdepth: 1

  abandontransaction
  abortrescan
  addmultisigaddress
  backupwallet
  bumpfee
  dumpprivkey
  dumpwallet
  encryptwallet
  getaccount
  getaccountaddress
  getaddressesbyaccount
  getbalance
  getnewaddress
  getrawchangeaddress
  getreceivedbyaccount
  getreceivedbyaddress
  gettransaction
  getunconfirmedbalance
  getwalletinfo
  importaddress
  importmulti
  importprivkey
  importprunedfunds
  importpubkey
  importwallet
  keypoolrefill
  listaccounts
  listaddressgroupings
  listlockunspent
  listreceivedbyaccount
  listreceivedbyaddress
  listsinceblock
  listtransactions
  listunspent
  listwallets
  lockunspent
  makekeypair
  move
  removeprunedfunds
  rescanblockchain
  reservebalance
  sendfrom
  sendmany
  sendtoaddress
  setaccount
  settxfee
  signmessage
  walletlock
  walletpassphrasechange

