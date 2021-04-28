.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

getreceivedbyaddress
====================

``getreceivedbyaddress "address" ( minconf )``

Returns the total amount received by the given address in transactions with at least minconf confirmations.

Argument #1 - address
~~~~~~~~~~~~~~~~~~~~~

**Type:** string, required

The DeepOnion address for transactions.

Argument #2 - minconf
~~~~~~~~~~~~~~~~~~~~~

**Type:** numeric, optional, default=1

Only include transactions confirmed at least this many times.

Result
~~~~~~

.. list-table::
   :header-rows: 1

   * - Name
     - Type
     - Description
   * - amount
     - numeric
     - The total amount in ONION received at this address.

Examples
~~~~~~~~


.. highlight:: shell

The amount from transactions with at least 1 confirmation::

  DeepOnion-cli getreceivedbyaddress "Dc7BLTLqSyWSp6uEpQPbbcb7figA7xHjKQ"

The amount including unconfirmed transactions, zero confirmations::

  DeepOnion-cli getreceivedbyaddress "Dc7BLTLqSyWSp6uEpQPbbcb7figA7xHjKQ" 0

The amount with at least 6 confirmations::

  DeepOnion-cli getreceivedbyaddress "Dc7BLTLqSyWSp6uEpQPbbcb7figA7xHjKQ" 6

As a json rpc call::

  curl --user myusername --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "getreceivedbyaddress", "params": ["Dc7BLTLqSyWSp6uEpQPbbcb7figA7xHjKQ", 6] }' -H 'content-type: text/plain;' http://127.0.0.1:9332/

