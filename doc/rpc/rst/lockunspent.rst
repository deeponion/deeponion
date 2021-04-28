.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

lockunspent
===========

``lockunspent unlock ([{"txid":"txid","vout":n},...])``

Updates list of temporarily unspendable outputs.

Temporarily lock (unlock=false) or unlock (unlock=true) specified transaction outputs.

If no transaction outputs are specified when unlocking then all current locked transaction outputs are unlocked.

A locked transaction output will not be chosen by automatic coin selection, when spending DeepOnion.

Locks are stored in memory only. Nodes start with zero locked outputs, and the locked output list
is always cleared (by virtue of process exit) when a node stops or fails.

Also see the listunspent call

Argument #1 - unlock
~~~~~~~~~~~~~~~~~~~~

**Type:** boolean, required

Whether to unlock (true) or lock (false) the specified transactions

Argument #2 - transactions
~~~~~~~~~~~~~~~~~~~~~~~~~~

**Type:** string, optional

A json array of objects. Each object the txid (string) vout (numeric)

::

     [           (json array of json objects)
       {
         "txid":"id",    (string) The transaction id
         "vout": n         (numeric) The output number
       }
       ,...
     ]

Result
~~~~~~

.. list-table::
   :header-rows: 1

   * - Name
     - Type
     - Description
   * - true|false
     - boolean
     - Whether the command was successful or not

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

  curl --user myusername --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "lockunspent", "params": [false, "[{\"txid\":\"daaf44ec1e64e66ffda4a7e195ea60d5c8c8b602fc6bf22928582d3ff2530462\",\"vout\":1}]"] }' -H 'content-type: text/plain;' http://127.0.0.1:9332/

