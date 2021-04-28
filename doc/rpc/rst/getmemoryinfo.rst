.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

getmemoryinfo
=============

``getmemoryinfo ("mode")``

Returns an object containing information about memory usage.

Result (mode "stats")
~~~~~~~~~~~~~~~~~~~~~

::

  {
    "locked": {               (json object) Information about locked memory manager
      "used": xxxxx,          (numeric) Number of bytes used
      "free": xxxxx,          (numeric) Number of bytes available in current arenas
      "total": xxxxxxx,       (numeric) Total number of bytes managed
      "locked": xxxxxx,       (numeric) Amount of bytes that succeeded locking. If this number is smaller than total, locking pages failed at some point and key data could be swapped to disk.
      "chunks_used": xxxxx,   (numeric) Number allocated chunks
      "chunks_free": xxxxx,   (numeric) Number unused chunks
    }
  }

Result (mode "mallocinfo")
~~~~~~~~~~~~~~~~~~~~~~~~~~

::

  "<malloc version="1">..."

Examples
~~~~~~~~


.. highlight:: shell

::

  DeepOnion-cli getmemoryinfo

::

  curl --user myusername --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "getmemoryinfo", "params": [] }' -H 'content-type: text/plain;' http://127.0.0.1:9332/

