.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

listservicenodes
================

``listservicenodes``

Lists the currently connected service nodes.

Result
~~~~~~

::

  [                         (json array of strings)
    "nodeaddress"         (string) The node tor address
     ...
  ]

Examples
~~~~~~~~


.. highlight:: shell

::

  DeepOnion-cli listservicenodes

::

  curl --user myusername --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "listservicenodes", "params": [] }' -H 'content-type: text/plain;' http://127.0.0.1:9332/

