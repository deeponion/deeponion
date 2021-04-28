.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

getaddressesbyaccount
=====================

``getaddressesbyaccount "account"``

DEPRECATED. Returns the list of addresses for the given account.

Argument #1 - account
~~~~~~~~~~~~~~~~~~~~~

**Type:** string, required

The account name.

Result
~~~~~~

::

  [                     (json array of string)
    "address"         (string) a DeepOnion address associated with the given account
    ,...
  ]

Examples
~~~~~~~~


.. highlight:: shell

::

  DeepOnion-cli getaddressesbyaccount "tabby"

::

  curl --user myusername --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "getaddressesbyaccount", "params": ["tabby"] }' -H 'content-type: text/plain;' http://127.0.0.1:9332/

