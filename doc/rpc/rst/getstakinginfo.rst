.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

getstakinginfo
==============

``getstakinginfo``

Returns an object containing staking-related information.

Result
~~~~~~

::

  {
    "enabled": true,             (boolean) If staking is enabled
    "staking": true, 	          (boolean) If currently staking
    "errors": "...",           (string)  any network and blockchain warnings
    "currentblocksize": nnn      (numeric) The current block size
    "currentblocktx": nnn,       (numeric) The last block transaction
    "difficulty": xxx.xxxxx      (numeric) Staking difficulty
    "search-interval": nnn,      (numeric) Last interval between stake searches
    "weight": nnn                (numeric) Current wallet staking weight
    "netstakeweight": nnn        (numeric) Total network staking wieght
    "expectedtime": nnn          (numeric) Expected time until next wallet stake
  }

Examples
~~~~~~~~


.. highlight:: shell

::

  DeepOnion-cli getstakinginfo

::

  curl --user myusername --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "getstakinginfo", "params": [] }' -H 'content-type: text/plain;' http://127.0.0.1:9332/

