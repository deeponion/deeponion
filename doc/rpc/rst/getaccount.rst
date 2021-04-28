.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

getaccount
==========

``getaccount "address"``

DEPRECATED. Returns the account associated with the given address.

Argument #1 - address
~~~~~~~~~~~~~~~~~~~~~

**Type:** string, required

The DeepOnion address for account lookup.

Result
~~~~~~

.. list-table::
   :header-rows: 1

   * - Name
     - Type
     - Description
   * - accountname
     - string
     - the account address

Examples
~~~~~~~~


.. highlight:: shell

::

  DeepOnion-cli getaccount "Dc7BLTLqSyWSp6uEpQPbbcb7figA7xHjKQ"

::

  curl --user myusername --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "getaccount", "params": ["Dc7BLTLqSyWSp6uEpQPbbcb7figA7xHjKQ"] }' -H 'content-type: text/plain;' http://127.0.0.1:9332/

