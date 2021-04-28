.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

makekeypair
===========

``makekeypair``

Make a public/private key pair.

Result
~~~~~~

::

  {
    "PrivateKey": "value", (string)  The resulting Private Key (hex-encoded string)
    "PublicKey": "value", (string)  The resulting Public Key (hex-encoded string)
  }

Examples
~~~~~~~~


.. highlight:: shell

::

  DeepOnion-cli makekeypair

::

  curl --user myusername --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "makekeypair", "params": [] }' -H 'content-type: text/plain;' http://127.0.0.1:9332/

