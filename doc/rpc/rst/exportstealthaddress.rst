.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

exportstealthaddress
====================

``exportstealthaddress <label/address>``

Exports the given stealth address.

Argument #1 - label
~~~~~~~~~~~~~~~~~~~

**Type:** string, optional, default=""

Stealth address label to export

Result
~~~~~~

::

  {
    "label": "str",          (string) Stealth address label.
    "Scan Secret": "str",    (string) Scan secret.
    "Spend Secret": "str",   (string) Spend secret.
  }

Examples
~~~~~~~~


.. highlight:: shell

::

  DeepOnion-cli exportstealthaddress mystealthaddress

::

  curl --user myusername --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "exportstealthaddress", "params": [mystealthaddress] }' -H 'content-type: text/plain;' http://127.0.0.1:9332/

