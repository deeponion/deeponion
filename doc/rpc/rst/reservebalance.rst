.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

reservebalance
==============

``reservebalance ( reserve amount )``

Show or set reserve amount not participating in network protection.

If no parameters provided current setting is printed.

Argument #1 - reserve
~~~~~~~~~~~~~~~~~~~~~

**Type:** boolean, optional

is true or false to turn balance reserve on or off.

Argument #2 - amount
~~~~~~~~~~~~~~~~~~~~

**Type:** numeric, optional

is a real and rounded to cent.

Result
~~~~~~

::

  {
    "reserve": true|false   (boolean) Status of the reserve balance
    "amount": x.xxxx        (numeric) Amount reserved
  }

Examples
~~~~~~~~


.. highlight:: shell

::

  DeepOnion-cli reservebalance true 120000

::

  curl --user myusername --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "reservebalance", "params": [true, 120000] }' -H 'content-type: text/plain;' http://127.0.0.1:9332/

