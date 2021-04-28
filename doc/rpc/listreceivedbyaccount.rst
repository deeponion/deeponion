.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

listreceivedbyaccount
=====================

``listreceivedbyaccount ( minconf include_empty include_watchonly)``

DEPRECATED. List balances by account.

Argument #1 - minconf
~~~~~~~~~~~~~~~~~~~~~

**Type:** numeric, optional, default=1

The minimum number of confirmations before payments are included.

Argument #2 - include_empty
~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Type:** bool, optional, default=false

Whether to include accounts that haven't received any payments.

Argument #3 - include_watchonly
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Type:** bool, optional, default=false

Whether to include watch-only addresses (see 'importaddress').

Result
~~~~~~

::

  [
    {
      "involvesWatchonly" : true,   (bool) Only returned if imported addresses were involved in transaction
      "account" : "accountname",  (string) The account name of the receiving account
      "amount" : x.xxx,             (numeric) The total amount received by addresses with this account
      "confirmations" : n,          (numeric) The number of confirmations of the most recent transaction included
      "label" : "label"           (string) A comment for the address/transaction, if any
    }
    ,...
  ]

Examples
~~~~~~~~


.. highlight:: shell

::

  DeepOnion-cli listreceivedbyaccount

::

  DeepOnion-cli listreceivedbyaccount 6 true

::

  curl --user myusername --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "listreceivedbyaccount", "params": [6, true, true] }' -H 'content-type: text/plain;' http://127.0.0.1:9332/

