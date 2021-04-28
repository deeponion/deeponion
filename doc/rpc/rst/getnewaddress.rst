.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

getnewaddress
=============

``getnewaddress ( "account" "address_type" )``

Returns a new DeepOnion address for receiving payments.

If 'account' is specified (DEPRECATED), it is added to the address book
so payments received with the address will be credited to 'account'.

Argument #1 - account
~~~~~~~~~~~~~~~~~~~~~

**Type:** string, optional

DEPRECATED. The account name for the address to be linked to. If not provided, the default account "" is used. It can also be set to the empty string "" to represent the default account. The account does not need to exist, it will be created if there is no account by the given name.

Argument #2 - address_type
~~~~~~~~~~~~~~~~~~~~~~~~~~

**Type:** string, optional

The address type to use. Options are "legacy", "p2sh-segwit", and "bech32". Default is set by -addresstype.

Result
~~~~~~

.. list-table::
   :header-rows: 1

   * - Name
     - Type
     - Description
   * - address
     - string
     - The new DeepOnion address

Examples
~~~~~~~~


.. highlight:: shell

::

  DeepOnion-cli getnewaddress

::

  curl --user myusername --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "getnewaddress", "params": [] }' -H 'content-type: text/plain;' http://127.0.0.1:9332/

