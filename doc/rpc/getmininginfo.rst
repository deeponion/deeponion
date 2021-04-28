.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

getmininginfo
=============

``getmininginfo``

Returns a json object containing mining-related information.

Result
~~~~~~

::

  {
    "blocks": nnn,             (numeric) The current block
    "currentblockweight": nnn, (numeric) The last block weight
    "currentblocktx": nnn,     (numeric) The last block transaction
    "difficulty": xxx.xxxxx    (numeric) The current difficulty
    "networkhashps": nnn,      (numeric) The network hashes per second
    "pooledtx": n              (numeric) The size of the mempool
    "chain": "xxxx",           (string) current network name as defined in BIP70 (main, test, regtest)
    "warnings": "..."          (string) any network and blockchain warnings
    "errors": "..."            (string) DEPRECATED. Same as warnings. Only shown when DeepOniond is started with -deprecatedrpc=getmininginfo
  }

Examples
~~~~~~~~


.. highlight:: shell

::

  DeepOnion-cli getmininginfo

::

  curl --user myusername --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "getmininginfo", "params": [] }' -H 'content-type: text/plain;' http://127.0.0.1:9332/

