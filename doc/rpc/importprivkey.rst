.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

importprivkey
=============

``importprivkey "privkey" ( "label" ) ( rescan )``

Adds a private key (as returned by dumpprivkey) to your wallet. Requires a new wallet backup.

Argument #1 - privkey
~~~~~~~~~~~~~~~~~~~~~

**Type:** string, required

The private key (see dumpprivkey)

Argument #2 - label
~~~~~~~~~~~~~~~~~~~

**Type:** string, optional, default=""

An optional label

Argument #3 - rescan
~~~~~~~~~~~~~~~~~~~~

**Type:** boolean, optional, default=true

Rescan the wallet for transactions

Examples
~~~~~~~~


.. highlight:: shell

Dump a private key::

  DeepOnion-cli dumpprivkey "myaddress"

Import the private key with rescan::

  DeepOnion-cli importprivkey "mykey"

Import using a label and without rescan::

  DeepOnion-cli importprivkey "mykey" "testing" false

Import using default blank label and without rescan::

  DeepOnion-cli importprivkey "mykey" "" false

As a JSON-RPC call::

  curl --user myusername --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "importprivkey", "params": ["mykey", "testing", false] }' -H 'content-type: text/plain;' http://127.0.0.1:9332/

