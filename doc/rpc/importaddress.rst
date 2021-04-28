.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

importaddress
=============

``importaddress "address" ( "label" rescan p2sh )``

Adds a script (in hex) or address that can be watched as if it were in your wallet but cannot be used to spend. Requires a new wallet backup.

Argument #1 - script
~~~~~~~~~~~~~~~~~~~~

**Type:** string, required

The hex-encoded script (or address)

Argument #2 - label
~~~~~~~~~~~~~~~~~~~

**Type:** string, optional, default=""

An optional label

Argument #3 - rescan
~~~~~~~~~~~~~~~~~~~~

**Type:** boolean, optional, default=true

Rescan the wallet for transactions

Argument #4 - p2sh
~~~~~~~~~~~~~~~~~~

**Type:** boolean, optional, default=false

Add the P2SH version of the script as well

Examples
~~~~~~~~


.. highlight:: shell

Import a script with rescan::

  DeepOnion-cli importaddress "myscript"

Import using a label without rescan::

  DeepOnion-cli importaddress "myscript" "testing" false

As a JSON-RPC call::

  curl --user myusername --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "importaddress", "params": ["myscript", "testing", false] }' -H 'content-type: text/plain;' http://127.0.0.1:9332/

