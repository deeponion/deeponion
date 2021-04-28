.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

listlockunspent
===============

``listlockunspent``

Returns list of temporarily unspendable outputs.

See the lockunspent call to lock and unlock transactions for spending.

Result
~~~~~~

::

  [
    {
      "txid" : "transactionid",     (string) The transaction id locked
      "vout" : n                      (numeric) The vout value
    }
    ,...
  ]

Examples
~~~~~~~~


.. highlight:: shell

List the unspent transactions::

  DeepOnion-cli listunspent

Lock an unspent transaction::

  DeepOnion-cli lockunspent false "[{\"txid\":\"daaf44ec1e64e66ffda4a7e195ea60d5c8c8b602fc6bf22928582d3ff2530462\",\"vout\":1}]"

List the locked transactions::

  DeepOnion-cli listlockunspent

Unlock the transaction again::

  DeepOnion-cli lockunspent true "[{\"txid\":\"daaf44ec1e64e66ffda4a7e195ea60d5c8c8b602fc6bf22928582d3ff2530462\",\"vout\":1}]"

As a json rpc call::

  curl --user myusername --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "listlockunspent", "params": [] }' -H 'content-type: text/plain;' http://127.0.0.1:9332/

