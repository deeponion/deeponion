.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

sendtostealthaddress
====================

``sendtostealthaddress "stealthaddress" amount  ( "narration" "comment" "comment_to" subtractfeefromamount replaceable conf_target "estimate_mode")``

Send an amount to a given address.

Argument #1 - address
~~~~~~~~~~~~~~~~~~~~~

**Type:** string, required

The DeepOnion stealth address to send to.

Argument #2 - amount
~~~~~~~~~~~~~~~~~~~~

**Type:** numeric or string, required

The amount in ONION to send. eg 0.1

Argument #3 - narration
~~~~~~~~~~~~~~~~~~~~~~~

**Type:** string, optional

A comment sent to the receiver of the transaction. 

Argument #4 - comment
~~~~~~~~~~~~~~~~~~~~~

**Type:** string, optional

A comment used to store what the transaction is for. 
       This is not part of the transaction, just kept in your wallet.

Argument #5 - comment_to
~~~~~~~~~~~~~~~~~~~~~~~~

**Type:** string, optional

A comment to store the name of the person or organization 
       to which you're sending the transaction. This is not part of the 
       transaction, just kept in your wallet.

Argument #6 - subtractfeefromamount
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Type:** boolean, optional, default=false

The fee will be deducted from the amount being sent.
       The recipient will receive less DeepOnion than you enter in the amount field.

Argument #7 - replaceable
~~~~~~~~~~~~~~~~~~~~~~~~~

**Type:** boolean, optional

Allow this transaction to be replaced by a transaction with higher fees via BIP 125

Argument #8 - conf_target
~~~~~~~~~~~~~~~~~~~~~~~~~

**Type:** numeric, optional

Confirmation target (in blocks)

Argument #9 - estimate_mode
~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Type:** string, optional, default=UNSET

The fee estimate mode, must be one of:
       "UNSET"
       "ECONOMICAL"
       "CONSERVATIVE"

Result
~~~~~~

.. list-table::
   :header-rows: 1

   * - Name
     - Type
     - Description
   * - txid
     - string
     - The transaction id.

Examples
~~~~~~~~


.. highlight:: shell

::

  DeepOnion-cli sendtostealthaddress "smYkiNESACbF79HHm3Er6U6h2x7Ty6HG1A2QSTqEqBm9xb1QbFtkp6wPVGLzAgWg1pXHLQzrU6FgYPkq7PLY9fwmpPYdC9cGydo36h" 0.123

::

  DeepOnion-cli sendtostealthaddress "smYkiNESACbF79HHm3Er6U6h2x7Ty6HG1A2QSTqEqBm9xb1QbFtkp6wPVGLzAgWg1pXHLQzrU6FgYPkq7PLY9fwmpPYdC9cGydo36h" 0.123 "narration"

