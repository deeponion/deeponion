.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

signmessagewithprivkey
======================

``signmessagewithprivkey "privkey" "message"``

Sign a message with the private key of an address

Argument #1 - privkey
~~~~~~~~~~~~~~~~~~~~~

**Type:** string, required

The private key to sign the message with.

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

Create the signature::

  DeepOnion-cli signmessagewithprivkey "privkey" "my message"

Verify the signature::

  DeepOnion-cli verifymessage "LEr4hNAefWYhBMgxCFP2Po1NPrUeiK8kM2" "signature" "my message"

As json rpc::

  curl --user myusername --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "signmessagewithprivkey", "params": ["privkey", "my message"] }' -H 'content-type: text/plain;' http://127.0.0.1:9332/

