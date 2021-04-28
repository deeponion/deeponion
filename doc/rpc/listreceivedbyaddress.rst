.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

listreceivedbyaddress
=====================

``listreceivedbyaddress ( minconf include_empty include_watchonly)``

List balances by receiving address.

Argument #1 - minconf
~~~~~~~~~~~~~~~~~~~~~

**Type:** numeric, optional, default=1

The minimum number of confirmations before payments are included.

Argument #2 - include_empty
~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Type:** bool, optional, default=false

Whether to include addresses that haven't received any payments.

Argument #3 - include_watchonly
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Type:** bool, optional, default=false

Whether to include watch-only addresses (see 'importaddress').

Result
~~~~~~

::

  [
    {
      "involvesWatchonly" : true,        (bool) Only returned if imported addresses were involved in transaction
      "address" : "receivingaddress",  (string) The receiving address
      "account" : "accountname",       (string) DEPRECATED. The account of the receiving address. The default account is "".
      "amount" : x.xxx,                  (numeric) The total amount in ONION received by the address
      "confirmations" : n,               (numeric) The number of confirmations of the most recent transaction included
      "label" : "label",               (string) A comment for the address/transaction, if any
      "txids": [
         n,                                (numeric) The ids of transactions received with the address
         ...
      ]
    }
    ,...
  ]

Examples
~~~~~~~~


.. highlight:: shell

::

  DeepOnion-cli listreceivedbyaddress

::

  DeepOnion-cli listreceivedbyaddress 6 true

::

  curl --user myusername --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "listreceivedbyaddress", "params": [6, true, true] }' -H 'content-type: text/plain;' http://127.0.0.1:9332/

