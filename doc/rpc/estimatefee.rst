.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

estimatefee
===========

``estimatefee nblocks``

DEPRECATED. Please use estimatesmartfee for more intelligent estimates.

Estimates the approximate fee per kilobyte needed for a transaction to begin
confirmation within nblocks blocks. Uses virtual transaction size of transaction
as defined in BIP 141 (witness data is discounted).

Argument #1 - nblocks
~~~~~~~~~~~~~~~~~~~~~

**Type:** numeric, required

Result
~~~~~~

.. list-table::
   :header-rows: 1

   * - Name
     - Type
     - Description
   * - n
     - numeric
     - estimated fee-per-kilobyte

Examples
~~~~~~~~


.. highlight:: shell

::

  DeepOnion-cli estimatefee 6

