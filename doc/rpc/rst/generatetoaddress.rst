.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

generatetoaddress
=================

``generatetoaddress nblocks address (maxtries)``

Mine blocks immediately to a specified address (before the RPC call returns)

Argument #1 - nblocks
~~~~~~~~~~~~~~~~~~~~~

**Type:** numeric, required

How many blocks are generated immediately.

Argument #2 - address
~~~~~~~~~~~~~~~~~~~~~

**Type:** string, required

The address to send the newly generated DeepOnion to.

Argument #3 - maxtries
~~~~~~~~~~~~~~~~~~~~~~

**Type:** numeric, optional

How many iterations to try (default = 1000000).

Result
~~~~~~

::

  [ blockhashes ]     (array) hashes of blocks generated

Examples
~~~~~~~~


.. highlight:: shell

Generate 11 blocks to myaddress::

  DeepOnion-cli generatetoaddress 11 "myaddress"

