.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

setaccount
==========

``setaccount "address" "account"``

DEPRECATED. Sets the account associated with the given address.

Argument #1 - address
~~~~~~~~~~~~~~~~~~~~~

**Type:** string, required

The DeepOnion address to be associated with an account.

Argument #2 - account
~~~~~~~~~~~~~~~~~~~~~

**Type:** string, required

The account to assign the address to.

Examples
~~~~~~~~


.. highlight:: shell

::

  DeepOnion-cli setaccount "Dc7BLTLqSyWSp6uEpQPbbcb7figA7xHjKQ" "tabby"

::

  curl --user myusername --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "setaccount", "params": ["Dc7BLTLqSyWSp6uEpQPbbcb7figA7xHjKQ", "tabby"] }' -H 'content-type: text/plain;' http://127.0.0.1:9332/

