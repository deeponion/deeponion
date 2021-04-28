.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

removeprunedfunds
=================

``removeprunedfunds "txid"``

Deletes the specified transaction from the wallet. Meant for use with pruned wallets and as a companion to importprunedfunds. This will affect wallet balances.

Argument #1 - txid
~~~~~~~~~~~~~~~~~~

**Type:** string, required

The hex-encoded id of the transaction you are deleting

Examples
~~~~~~~~


.. highlight:: shell

::

  DeepOnion-cli removeprunedfunds "c54357a1ff9f4e792198e75c01fc633acc6d093abd67ec1849596637c3457bf2"

As a JSON-RPC call::

  curl --user myusername --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "removeprunedfunds", "params": ["c54357a1ff9f4e792198e75c01fc633acc6d093abd67ec1849596637c3457bf2"] }' -H 'content-type: text/plain;' http://127.0.0.1:9332/

