.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

getaccountaddress
=================

``getaccountaddress "account"``

DEPRECATED. Returns the current DeepOnion address for receiving payments to this account.

Argument #1 - account
~~~~~~~~~~~~~~~~~~~~~

**Type:** string, required

The account name for the address. It can also be set to the empty string "" to represent the default account. The account does not need to exist, it will be created and a new address created  if there is no account by the given name.

Result
~~~~~~

.. list-table::
   :header-rows: 1

   * - Name
     - Type
     - Description
   * - address
     - string
     - The account DeepOnion address

Examples
~~~~~~~~


.. highlight:: shell

::

  DeepOnion-cli getaccountaddress

::

  DeepOnion-cli getaccountaddress ""

::

  DeepOnion-cli getaccountaddress "myaccount"

::

  curl --user myusername --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "getaccountaddress", "params": ["myaccount"] }' -H 'content-type: text/plain;' http://127.0.0.1:9332/

