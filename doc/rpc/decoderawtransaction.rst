.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

decoderawtransaction
====================

``decoderawtransaction "hexstring" ( iswitness )``

Return a JSON object representing the serialized, hex-encoded transaction.

Argument #1 - hexstring
~~~~~~~~~~~~~~~~~~~~~~~

**Type:** string, required

The transaction hex string

Argument #2 - iswitness
~~~~~~~~~~~~~~~~~~~~~~~

**Type:** boolean, optional

Whether the transaction hex is a serialized witness transaction
       If iswitness is not present, heuristic tests will be used in decoding

Result
~~~~~~

::

  {
    "txid" : "id",        (string) The transaction id
    "hash" : "id",        (string) The transaction hash (differs from txid for witness transactions)
    "version" : n,          (numeric) The version
    "size" : n,             (numeric) The transaction size
    "vsize" : n,            (numeric) The virtual transaction size (differs from size for witness transactions)
    "time" : ttt,           (numeric) The transaction creation time
    "locktime" : ttt,       (numeric) The lock time
    "vin" : [               (array of json objects)
       {
         "txid": "id",    (string) The transaction id
         "vout": n,         (numeric) The output number
         "scriptSig": {     (json object) The script
           "asm": "asm",  (string) asm
           "hex": "hex"   (string) hex
         },
         "txinwitness": ["hex", ...] (array of string) hex-encoded witness data (if any)
         "sequence": n     (numeric) The script sequence number
       }
       ,...
    ],
    "vout" : [             (array of json objects)
       {
         "value" : x.xxx,            (numeric) The value in ONION
         "n" : n,                    (numeric) index
         "scriptPubKey" : {          (json object)
           "asm" : "asm",          (string) the asm
           "hex" : "hex",          (string) the hex
           "reqSigs" : n,            (numeric) The required sigs
           "type" : "pubkeyhash",  (string) The type, eg 'pubkeyhash'
           "addresses" : [           (json array of string)
             "Dc7BLTLqSyWSp6uEpQPbbcb7figA7xHjKQ"   (string) DeepOnion address
             ,...
           ]
         }
       }
       ,...
    ],
  }

Examples
~~~~~~~~


.. highlight:: shell

::

  DeepOnion-cli decoderawtransaction "hexstring"

::

  curl --user myusername --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "decoderawtransaction", "params": ["hexstring"] }' -H 'content-type: text/plain;' http://127.0.0.1:9332/

