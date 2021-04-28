.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

gettransaction
==============

``gettransaction "txid" ( include_watchonly )``

Get detailed information about in-wallet transaction <txid>

Argument #1 - txid
~~~~~~~~~~~~~~~~~~

**Type:** string, required

The transaction id

Argument #2 - include_watchonly
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Type:** bool, optional, default=false

Whether to include watch-only addresses in balance calculation and details[]

Result
~~~~~~

::

  {
    "amount" : x.xxx,        (numeric) The transaction amount in ONION
    "fee": x.xxx,            (numeric) The amount of the fee in ONION. This is negative and only available for the
                                'send' category of transactions.
    "confirmations" : n,     (numeric) The number of confirmations
    "blockhash" : "hash",  (string) The block hash
    "blockindex" : xx,       (numeric) The index of the transaction in the block that includes it
    "blocktime" : ttt,       (numeric) The time in seconds since epoch (1 Jan 1970 GMT)
    "txid" : "transactionid",   (string) The transaction id.
    "time" : ttt,            (numeric) The transaction time in seconds since epoch (1 Jan 1970 GMT)
    "timereceived" : ttt,    (numeric) The time received in seconds since epoch (1 Jan 1970 GMT)
    "bip125-replaceable": "yes|no|unknown",  (string) Whether this transaction could be replaced due to BIP125 (replace-by-fee);
                                                     may be unknown for unconfirmed transactions not in the mempool
    "details" : [
      {
        "account" : "accountname",      (string) DEPRECATED. The account name involved in the transaction, can be "" for the default account.
        "address" : "address",          (string) The DeepOnion address involved in the transaction
        "category" : "send|receive",    (string) The category, either 'send' or 'receive'
        "amount" : x.xxx,                 (numeric) The amount in ONION
        "label" : "label",              (string) A comment for the address/transaction, if any
        "vout" : n,                       (numeric) the vout value
        "fee": x.xxx,                     (numeric) The amount of the fee in ONION. This is negative and only available for the
                                             'send' category of transactions.
        "abandoned": xxx                  (bool) 'true' if the transaction has been abandoned (inputs are respendable). Only available for the
                                             'send' category of transactions.
      }
      ,...
    ],
    "hex" : "data"         (string) Raw data for transaction
  }

Examples
~~~~~~~~


.. highlight:: shell

::

  DeepOnion-cli gettransaction "c1700d6dd3e690866de56686e893cbe4e637eb5d84e3591cdfbbdbb0fcee49f8"

::

  DeepOnion-cli gettransaction "c1700d6dd3e690866de56686e893cbe4e637eb5d84e3591cdfbbdbb0fcee49f8" true

::

  curl --user myusername --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "gettransaction", "params": ["c1700d6dd3e690866de56686e893cbe4e637eb5d84e3591cdfbbdbb0fcee49f8"] }' -H 'content-type: text/plain;' http://127.0.0.1:9332/

