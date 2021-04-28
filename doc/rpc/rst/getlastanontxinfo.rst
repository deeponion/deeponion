.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

getlastanontxinfo
=================

``getlastanontxinfo``

Returns the last/current anonymous transaction info and log.

Result
~~~~~~

.. list-table::
   :header-rows: 1

   * - Name
     - Type
     - Description
   * - info
     - string
     - The transaction info

Examples
~~~~~~~~


.. highlight:: shell

::

  DeepOnion-cli getlastanontxinfo

::

  curl --user myusername --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "getlastanontxinfo", "params": [] }' -H 'content-type: text/plain;' http://127.0.0.1:9332/

