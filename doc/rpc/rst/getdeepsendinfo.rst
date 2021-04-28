.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

getdeepsendinfo
===============

``getdeepsendinfo``

Returns an object containing deepsend-related information.

Result
~~~~~~

::

  {
    "enabled": true,             (boolean) If deepsend is enabled
    "servicenodes": 2,           (int) Currently connected service nodes
    "anontxinprogress": true,    (boolean) If deepsend tx is in progress
  }

Examples
~~~~~~~~


.. highlight:: shell

::

  DeepOnion-cli getdeepsendinfo

::

  curl --user myusername --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "getdeepsendinfo", "params": [] }' -H 'content-type: text/plain;' http://127.0.0.1:9332/

