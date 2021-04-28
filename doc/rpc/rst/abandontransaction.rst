.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

abandontransaction
==================

``abandontransaction "txid"``

Mark in-wallet transaction <txid> as abandoned
This will mark this transaction and all its in-wallet descendants as abandoned which will allow
for their inputs to be respent.  It can be used to replace "stuck" or evicted transactions.

It only works on transactions which are not included in a block and are not currently in the mempool.

It has no effect on transactions which are already conflicted or abandoned.

Argument #1 - txid
~~~~~~~~~~~~~~~~~~

**Type:** string, required

The transaction id

Examples
~~~~~~~~


.. highlight:: shell

::

  DeepOnion-cli abandontransaction "c1700d6dd3e690866de56686e893cbe4e637eb5d84e3591cdfbbdbb0fcee49f8"

::

  curl --user myusername --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "abandontransaction", "params": ["c1700d6dd3e690866de56686e893cbe4e637eb5d84e3591cdfbbdbb0fcee49f8"] }' -H 'content-type: text/plain;' http://127.0.0.1:9332/

