.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

liststealthaddresses
====================

``liststealthaddresses [show_secrets]``

List owned stealth addresses.

Argument #1 - show_secrets
~~~~~~~~~~~~~~~~~~~~~~~~~~

**Type:** bool, optional

Display secret keys to stealth addresses.
       If [show_secrets] is true secret keys to stealth addresses will be shown 
       The wallet must be unlocked if true.

Result
~~~~~~

::

  {
    "Stealth Address": {
      "Label": "str",          (string) Stealth address label.
      "Address": "str",        (string) Stealth address.
      "Scan Secret": "str",    (string) Scan secret, if show_secrets=1.
      "Spend Secret": "str",   (string) Spend secret, if show_secrets=1.
    }
  }

Examples
~~~~~~~~


.. highlight:: shell

::

  DeepOnion-cli liststealthaddresses

::

  curl --user myusername --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "liststealthaddresses", "params": [] }' -H 'content-type: text/plain;' http://127.0.0.1:9332/

