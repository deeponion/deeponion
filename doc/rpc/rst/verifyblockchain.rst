.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

verifyblockchain
================

``verifyblockchain``

Verifies the authenticity of the DeepOnion blockchain.

This action can take some time (minutes)

Examples
~~~~~~~~


.. highlight:: shell

::

  DeepOnion-cli verifyblockchain

::

  curl --user myusername --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "verifyblockchain", "params": [] }' -H 'content-type: text/plain;' http://127.0.0.1:9332/

