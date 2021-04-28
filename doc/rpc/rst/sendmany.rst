.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

sendmany
========

``sendmany "fromaccount" {"address":amount,...} ( minconf "comment" ["address",...] replaceable conf_target "estimate_mode")``

Send multiple times. Amounts are double-precision floating point numbers.

Argument #1 - fromaccount
~~~~~~~~~~~~~~~~~~~~~~~~~

**Type:** string, required

DEPRECATED. The account to send the funds from. Should be "" for the default account

Argument #2 - amounts
~~~~~~~~~~~~~~~~~~~~~

**Type:** string, required

A json object with addresses and amounts

::

    {
      "address":amount   (numeric or string) The DeepOnion address is the key, the numeric amount (can be string) in ONION is the value
      ,...
    }

Argument #3 - minconf
~~~~~~~~~~~~~~~~~~~~~

**Type:** numeric, optional, default=1

Only use the balance confirmed at least this many times.

Argument #4 - comment
~~~~~~~~~~~~~~~~~~~~~

**Type:** string, optional

A comment

Argument #5 - subtractfeefrom
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Type:** array, optional

A json array with addresses.
       The fee will be equally deducted from the amount of each selected address.
       Those recipients will receive less DeepOnion than you enter in their corresponding amount field.
       If no addresses are specified here, the sender pays the fee.

::

    [
      "address"          (string) Subtract fee from this address
      ,...
    ]

Argument #6 - replaceable
~~~~~~~~~~~~~~~~~~~~~~~~~

**Type:** boolean, optional

Allow this transaction to be replaced by a transaction with higher fees via BIP 125

Argument #7 - conf_target
~~~~~~~~~~~~~~~~~~~~~~~~~

**Type:** numeric, optional

Confirmation target (in blocks)

Argument #8 - estimate_mode
~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Type:** string, optional, default=UNSET

The fee estimate mode, must be one of:
       "UNSET"
       "ECONOMICAL"
       "CONSERVATIVE"

Result
~~~~~~

.. list-table::
   :header-rows: 1

   * - Name
     - Type
     - Description
   * - txid
     - string
     - The transaction id for the send. Only 1 transaction is created regardless of 

Examples
~~~~~~~~


.. highlight:: shell

Send two amounts to two different addresses:::

  DeepOnion-cli sendmany "" "{\"LEr4hNAefWYhBMgxCFP2Po1NPrUeiK8kM2\":0.01,\"Dc7BLTLqSyWSp6uEpQPbbcb7figA7xHjKQ\":0.02}"

Send two amounts to two different addresses setting the confirmation and comment:::

  DeepOnion-cli sendmany "" "{\"LEr4hNAefWYhBMgxCFP2Po1NPrUeiK8kM2\":0.01,\"Dc7BLTLqSyWSp6uEpQPbbcb7figA7xHjKQ\":0.02}" 6 "testing"

Send two amounts to two different addresses, subtract fee from amount:::

  DeepOnion-cli sendmany "" "{\"LEr4hNAefWYhBMgxCFP2Po1NPrUeiK8kM2\":0.01,\"Dc7BLTLqSyWSp6uEpQPbbcb7figA7xHjKQ\":0.02}" 1 "" "[\"LEr4hNAefWYhBMgxCFP2Po1NPrUeiK8kM2\",\"Dc7BLTLqSyWSp6uEpQPbbcb7figA7xHjKQ\"]"

As a json rpc call::

  curl --user myusername --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "sendmany", "params": ["", {"LEr4hNAefWYhBMgxCFP2Po1NPrUeiK8kM2":0.01,"Dc7BLTLqSyWSp6uEpQPbbcb7figA7xHjKQ":0.02}, 6, "testing"] }' -H 'content-type: text/plain;' http://127.0.0.1:9332/

