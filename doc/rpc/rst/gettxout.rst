.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

gettxout
========

``gettxout "txid" n ( include_mempool )``

Returns details about an unspent transaction output.

Argument #1 - txid
~~~~~~~~~~~~~~~~~~

**Type:** string, required

The transaction id

Argument #2 - n
~~~~~~~~~~~~~~~

**Type:** numeric, required

vout number

Argument #3 - include_mempool
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Type:** boolean, optional

Whether to include the mempool. Default: true.     Note that an unspent output that is spent in the mempool won't appear.

Result
~~~~~~

::

  {
    "bestblock" : "hash",    (string) the block hash
    "confirmations" : n,       (numeric) The number of confirmations
    "value" : x.xxx,           (numeric) The transaction value in ONION
    "scriptPubKey" : {         (json object)
       "asm" : "code",       (string)
       "hex" : "hex",        (string)
       "reqSigs" : n,          (numeric) Number of required signatures
       "type" : "pubkeyhash", (string) The type, eg pubkeyhash
       "addresses" : [          (array of string) array of DeepOnion addresses
          "address"     (string) DeepOnion address
          ,...
       ]
    },
    "coinbase" : true|false   (boolean) Coinbase or not
  }

Examples
~~~~~~~~


.. highlight:: shell

Get unspent transactions::

  DeepOnion-cli listunspent

View the details::

  DeepOnion-cli gettxout "txid" 1

As a json rpc call::

  curl --user myusername --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "gettxout", "params": ["txid", 1] }' -H 'content-type: text/plain;' http://127.0.0.1:9332/

