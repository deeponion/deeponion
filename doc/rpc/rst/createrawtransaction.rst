.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

createrawtransaction
====================

``createrawtransaction [{"txid":"id","vout":n},...] {"address":amount,"data":"hex",...} ( locktime ) ( replaceable )``

Create a transaction spending the given inputs and creating new outputs.

Outputs can be addresses or data.

Returns hex-encoded raw transaction.

Note that the transaction's inputs are not signed, and
it is not stored in the wallet or transmitted to the network.

Argument #1 - inputs
~~~~~~~~~~~~~~~~~~~~

**Type:** array, required

A json array of json objects

::

     [
       {
         "txid":"id",    (string, required) The transaction id
         "vout":n,         (numeric, required) The output number
         "sequence":n      (numeric, optional) The sequence number
       } 
       ,...
     ]

Argument #2 - outputs
~~~~~~~~~~~~~~~~~~~~~

**Type:** object, required

a json object with outputs

::

    {
      "address": x.xxx,    (numeric or string, required) The key is the DeepOnion address, the numeric value (can be string) is the ONION amount
      "data": "hex"      (string, required) The key is "data", the value is hex encoded data
      ,...
    }

Argument #3 - locktime
~~~~~~~~~~~~~~~~~~~~~~

**Type:** numeric, optional, default=0

Raw locktime. Non-0 value also locktime-activates inputs

Argument #4 - replaceable
~~~~~~~~~~~~~~~~~~~~~~~~~

**Type:** boolean, optional, default=false

Marks this transaction as BIP125 replaceable.
       Allows this transaction to be replaced by a transaction with higher fees. If provided, it is an error if explicit sequence numbers are incompatible.

Result
~~~~~~

.. list-table::
   :header-rows: 1

   * - Name
     - Type
     - Description
   * - transaction
     - string
     - hex string of the transaction

Examples
~~~~~~~~


.. highlight:: shell

::

  DeepOnion-cli createrawtransaction "[{\"txid\":\"myid\",\"vout\":0}]" "{\"address\":0.01}"

::

  DeepOnion-cli createrawtransaction "[{\"txid\":\"myid\",\"vout\":0}]" "{\"data\":\"00010203\"}"

::

  curl --user myusername --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "createrawtransaction", "params": ["[{\"txid\":\"myid\",\"vout\":0}]", "{\"address\":0.01}"] }' -H 'content-type: text/plain;' http://127.0.0.1:9332/

::

  curl --user myusername --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "createrawtransaction", "params": ["[{\"txid\":\"myid\",\"vout\":0}]", "{\"data\":\"00010203\"}"] }' -H 'content-type: text/plain;' http://127.0.0.1:9332/

