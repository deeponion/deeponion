.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

listunspent
===========

``listunspent ( minconf maxconf  ["addresses",...] [include_unsafe] [query_options])``

Returns array of unspent transaction outputs
with between minconf and maxconf (inclusive) confirmations.

Optionally filter to only include txouts paid to specified addresses.

Argument #1 - minconf
~~~~~~~~~~~~~~~~~~~~~

**Type:** numeric, optional, default=1

The minimum confirmations to filter

Argument #2 - maxconf
~~~~~~~~~~~~~~~~~~~~~

**Type:** numeric, optional, default=9999999

The maximum confirmations to filter

Argument #3 - addresses
~~~~~~~~~~~~~~~~~~~~~~~

**Type:** string

A json array of DeepOnion addresses to filter

::

    [
      "address"     (string) DeepOnion address
      ,...
    ]

Argument #4 - include_unsafe
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Type:** bool, optional, default=true

Include outputs that are not safe to spend
       See description of "safe" attribute below.

Argument #5 - query_options
~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Type:** json, optional

JSON with query options

::

    {
      "minimumAmount"    (numeric or string, default=0) Minimum value of each UTXO in ONION
      "maximumAmount"    (numeric or string, default=unlimited) Maximum value of each UTXO in ONION
      "maximumCount"     (numeric or string, default=unlimited) Maximum number of UTXOs
      "minimumSumAmount" (numeric or string, default=unlimited) Minimum sum value of all UTXOs in ONION
    }

Result
~~~~~~

::

  [                   (array of json object)
    {
      "txid" : "txid",          (string) the transaction id
      "vout" : n,               (numeric) the vout value
      "address" : "address",    (string) the DeepOnion address
      "account" : "account",    (string) DEPRECATED. The associated account, or "" for the default account
      "scriptPubKey" : "key",   (string) the script key
      "amount" : x.xxx,         (numeric) the transaction output amount in ONION
      "confirmations" : n,      (numeric) The number of confirmations
      "redeemScript" : n        (string) The redeemScript if scriptPubKey is P2SH
      "spendable" : xxx,        (bool) Whether we have the private keys to spend this output
      "solvable" : xxx,         (bool) Whether we know how to spend this output, ignoring the lack of keys
      "safe" : xxx              (bool) Whether this output is considered safe to spend. Unconfirmed transactions
                                from outside keys and unconfirmed replacement transactions are considered unsafe
                                and are not eligible for spending by fundrawtransaction and sendtoaddress.
    }
    ,...
  ]

