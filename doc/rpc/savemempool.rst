.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

savemempool
===========

``savemempool``

Dumps the mempool to disk.

Examples
~~~~~~~~


.. highlight:: shell

::

  DeepOnion-cli savemempool

::

  curl --user myusername --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "savemempool", "params": [] }' -H 'content-type: text/plain;' http://127.0.0.1:9332/

