.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

signmessage
===========

``signmessage "address" "message"``

Sign a message with the private key of an address

Argument #1 - address
~~~~~~~~~~~~~~~~~~~~~

**Type:** string, required

The DeepOnion address to use for the private key.

Argument #2 - message
~~~~~~~~~~~~~~~~~~~~~

**Type:** string, required

The message to create a signature of.

Result
~~~~~~

.. list-table::
   :header-rows: 1

   * - Name
     - Type
     - Description
   * - signature
     - string
     - The signature of the message encoded in base 64

Examples
~~~~~~~~


.. highlight:: shell

Unlock the wallet for 30 seconds::

  DeepOnion-cli walletpassphrase "mypassphrase" 30

Create the signature::

  DeepOnion-cli signmessage "Dc7BLTLqSyWSp6uEpQPbbcb7figA7xHjKQ" "my message"

Verify the signature::

  DeepOnion-cli verifymessage "Dc7BLTLqSyWSp6uEpQPbbcb7figA7xHjKQ" "signature" "my message"

As json rpc::

  curl --user myusername --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "signmessage", "params": ["Dc7BLTLqSyWSp6uEpQPbbcb7figA7xHjKQ", "my message"] }' -H 'content-type: text/plain;' http://127.0.0.1:9332/

