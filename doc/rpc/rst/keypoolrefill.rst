.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

keypoolrefill
=============

``keypoolrefill ( newsize )``

Fills the keypool.

Arguments
1. newsize     (numeric, optional, default=100) The new keypool size

Examples
~~~~~~~~


.. highlight:: shell

::

  DeepOnion-cli keypoolrefill

::

  curl --user myusername --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "keypoolrefill", "params": [] }' -H 'content-type: text/plain;' http://127.0.0.1:9332/

