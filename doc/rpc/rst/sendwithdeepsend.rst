.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

sendwithdeepsend
================

``sendwithdeepsend "address" amount``

Send an amount to a given address unisng deepsend service.

Argument #1 - address
~~~~~~~~~~~~~~~~~~~~~

**Type:** string, required

The DeepOnion address to send to.

Argument #2 - amount
~~~~~~~~~~~~~~~~~~~~

**Type:** numeric or string, required

The amount in ONION to send. eg 0.1

Result
~~~~~~

.. list-table::
   :header-rows: 1

   * - Name
     - Type
     - Description
   * - txid
     - string
     - Info related with deepsend service.

Examples
~~~~~~~~


.. highlight:: shell

::

  DeepOnion-cli sendwithdeepsend "Dc7BLTLqSyWSp6uEpQPbbcb7figA7xHjKQ" 0.123

