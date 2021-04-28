.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

importstealthaddress
====================

``importstealthaddress "scan_secret" "spend_secret" ("label")``

Imports owned stealth address.

Argument #1 - scan_secret
~~~~~~~~~~~~~~~~~~~~~~~~~

**Type:** string, required

Scan secret.

Argument #2 - spend_secret
~~~~~~~~~~~~~~~~~~~~~~~~~~

**Type:** string, required

Spend secret.

Argument #3 - label
~~~~~~~~~~~~~~~~~~~

**Type:** string, optional, default=""

Stealth address label to import

Result
~~~~~~

::

  {
    "result": "str",     (string) Import status: success or failed.
    "address": "str",    (string) Imported stealth address.
  }

Examples
~~~~~~~~


.. highlight:: shell

::

  DeepOnion-cli importstealthaddress my_scan_secret my_spend_secret

::

  curl --user myusername --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "importstealthaddress", "params": [my_scan_secret , my_spend_secret] }' -H 'content-type: text/plain;' http://127.0.0.1:9332/

