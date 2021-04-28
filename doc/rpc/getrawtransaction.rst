.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

getrawtransaction
=================

``getrawtransaction "txid" ( verbose "blockhash" )``

NOTE: By default this function only works for mempool transactions. If the -txindex option is
enabled, it also works for blockchain transactions. If the block which contains the transaction
is known, its hash can be provided even for nodes without -txindex. Note that if a blockhash is
provided, only that block will be searched and if the transaction is in the mempool or other
blocks, or if this node does not have the given block available, the transaction will not be found.

DEPRECATED: for now, it also works for transactions with unspent outputs.

Return the raw transaction data.

If verbose is 'true', returns an Object with information about 'txid'.

If verbose is 'false' or omitted, returns a string that is serialized, hex-encoded data for 'txid'.

Argument #1 - txid
~~~~~~~~~~~~~~~~~~

**Type:** string, required

The transaction id

Argument #2 - verbose
~~~~~~~~~~~~~~~~~~~~~

**Type:** bool, optional, default=false

If false, return a string, otherwise return a json object

Argument #3 - blockhash
~~~~~~~~~~~~~~~~~~~~~~~

**Type:** string, optional

The block in which to look for the transaction

Result (if verbose is not set or set to false)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. list-table::
   :header-rows: 1

   * - Name
     - Type
     - Description
   * - data
     - string
     - The serialized, hex-encoded data for 'txid'

Result (if verbose is set to true)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

  {
    "in_active_chain": b, (bool) Whether specified block is in the active chain or not (only present with explicit "blockhash" argument)
    "hex" : "data",       (string) The serialized, hex-encoded data for 'txid'
    "txid" : "id",        (string) The transaction id (same as provided)
    "hash" : "id",        (string) The transaction hash (differs from txid for witness transactions)
    "size" : n,             (numeric) The serialized transaction size
    "vsize" : n,            (numeric) The virtual transaction size (differs from size for witness transactions)
    "version" : n,          (numeric) The version
    "locktime" : ttt,       (numeric) The lock time
    "vin" : [               (array of json objects)
       {
         "txid": "id",    (string) The transaction id
         "vout": n,         (numeric)
         "scriptSig": {     (json object) The script
           "asm": "asm",  (string) asm
           "hex": "hex"   (string) hex
         },
         "sequence": n      (numeric) The script sequence number
         "txinwitness": ["hex", ...] (array of string) hex-encoded witness data (if any)
       }
       ,...
    ],
    "vout" : [              (array of json objects)
       {
         "value" : x.xxx,            (numeric) The value in ONION
         "n" : n,                    (numeric) index
         "scriptPubKey" : {          (json object)
           "asm" : "asm",          (string) the asm
           "hex" : "hex",          (string) the hex
           "reqSigs" : n,            (numeric) The required sigs
           "type" : "pubkeyhash",  (string) The type, eg 'pubkeyhash'
           "addresses" : [           (json array of string)
             "address"        (string) DeepOnion address
             ,...
           ]
         }
       }
       ,...
    ],
    "blockhash" : "hash",   (string) the block hash
    "confirmations" : n,      (numeric) The confirmations
    "time" : ttt,             (numeric) The transaction time in seconds since epoch (Jan 1 1970 GMT)
    "blocktime" : ttt         (numeric) The block time in seconds since epoch (Jan 1 1970 GMT)
  }

Examples
~~~~~~~~


.. highlight:: shell

::

  DeepOnion-cli getrawtransaction "mytxid"

::

  DeepOnion-cli getrawtransaction "mytxid" true

::

  curl --user myusername --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "getrawtransaction", "params": ["mytxid", true] }' -H 'content-type: text/plain;' http://127.0.0.1:9332/

::

  DeepOnion-cli getrawtransaction "mytxid" false "myblockhash"

::

  DeepOnion-cli getrawtransaction "mytxid" true "myblockhash"

