{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/rpcs/decoderawtransaction.md" %}

##### DecodeRawTransaction
{% include helpers/subhead-links.md %}

{% assign summary_decodeRawTransaction="return a JSON object representing the serialized, hex-encoded transaction." %}

{% autocrossref %}

The `decoderawtransaction` RPC {{summary_decodeRawTransaction}}

*Parameter #1---hexstring*

{% itemplate ntpd1 %}
- n: "hexstring"
  t: "string"
  p: "Required<br>(exactly 1)"
  d: "The transaction hex string"

{% enditemplate %}

*Parameter #2---iswitness*

{% itemplate ntpd1 %}
- n: "iswitness"
  t: "boolean"
  p: "Optional"
  d: "Whether the transaction hex is a serialized witness transaction
       If iswitness is not present, heuristic tests will be used in decoding"

{% enditemplate %}

*Result*

{% endautocrossref %}

    {
      "txid" : "id",        (string) The transaction id
      "hash" : "id",        (string) The transaction hash (differs from txid for witness transactions)
      "version" : n,          (numeric) The version
      "size" : n,             (numeric) The transaction size
      "vsize" : n,            (numeric) The virtual transaction size (differs from size for witness transactions)
      "time" : ttt,           (numeric) The transaction creation time
      "locktime" : ttt,       (numeric) The lock time
      "vin" : [               (array of json objects)
         {
           "txid": "id",    (string) The transaction id
           "vout": n,         (numeric) The output number
           "scriptSig": {     (json object) The script
             "asm": "asm",  (string) asm
             "hex": "hex"   (string) hex
           },
           "txinwitness": ["hex", ...] (array of string) hex-encoded witness data (if any)
           "sequence": n     (numeric) The script sequence number
         }
         ,...
      ],
      "vout" : [             (array of json objects)
         {
           "value" : x.xxx,            (numeric) The value in ONION
           "n" : n,                    (numeric) index
           "scriptPubKey" : {          (json object)
             "asm" : "asm",          (string) the asm
             "hex" : "hex",          (string) the hex
             "reqSigs" : n,            (numeric) The required sigs
             "type" : "pubkeyhash",  (string) The type, eg 'pubkeyhash'
             "addresses" : [           (json array of string)
               "Dc7BLTLqSyWSp6uEpQPbbcb7figA7xHjKQ"   (string) DeepOnion address
               ,...
             ]
           }
         }
         ,...
      ],
    }

{% autocrossref %}

*Example*

{% highlight bash %}
DeepOnion-cli decoderawtransaction "hexstring"
{% endhighlight %}

*See also*

* [CreateRawTransaction][rpc createrawtransaction]: {{summary_createRawTransaction}}
* [SendRawTransaction][rpc sendrawtransaction]: {{summary_sendRawTransaction}}

{% endautocrossref %}
