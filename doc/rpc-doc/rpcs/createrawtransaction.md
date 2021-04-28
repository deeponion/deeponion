{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/rpcs/createrawtransaction.md" %}

##### CreateRawTransaction
{% include helpers/subhead-links.md %}

{% assign summary_createRawTransaction="create a transaction spending the given inputs and creating new outputs." %}

{% autocrossref %}

The `createrawtransaction` RPC {{summary_createRawTransaction}}

Outputs can be addresses or data.

Returns hex-encoded raw transaction.

Note that the transaction's inputs are not signed, and
it is not stored in the wallet or transmitted to the network.

*Parameter #1---inputs*

{% itemplate ntpd1 %}
- n: "inputs"
  t: "array"
  p: "Required<br>(exactly 1)"
  d: "A json array of json objects"

{% enditemplate %}

{% endautocrossref %}

    [
      {
        "txid":"id",    (string, required) The transaction id
        "vout":n,         (numeric, required) The output number
        "sequence":n      (numeric, optional) The sequence number
      } 
      ,...
    ]

{% autocrossref %}

*Parameter #2---outputs*

{% itemplate ntpd1 %}
- n: "outputs"
  t: "object"
  p: "Required<br>(exactly 1)"
  d: "a json object with outputs"

{% enditemplate %}

{% endautocrossref %}

    {
      "address": x.xxx,    (numeric or string, required) The key is the DeepOnion address, the numeric value (can be string) is the ONION amount
      "data": "hex"      (string, required) The key is "data", the value is hex encoded data
      ,...
    }

{% autocrossref %}

*Parameter #3---locktime*

{% itemplate ntpd1 %}
- n: "locktime"
  t: "number (int)"
  p: "Optional<br>Default=0"
  d: "Raw locktime. Non-0 value also locktime-activates inputs"

{% enditemplate %}

*Parameter #4---replaceable*

{% itemplate ntpd1 %}
- n: "replaceable"
  t: "boolean"
  p: "Optional<br>Default=false"
  d: "Marks this transaction as BIP125 replaceable.
       Allows this transaction to be replaced by a transaction with higher fees. If provided, it is an error if explicit sequence numbers are incompatible."

{% enditemplate %}

*Result*

{% itemplate ntpd1 %}
- n: "`result`"
  t: "string (hex)"
  p: "Required<br>(exactly 1)"
  d: "hex string of the transaction"

{% enditemplate %}

*Example*

{% highlight bash %}
DeepOnion-cli createrawtransaction "[{\"txid\":\"myid\",\"vout\":0}]" "{\"address\":0.01}"
{% endhighlight %}
{% highlight bash %}
DeepOnion-cli createrawtransaction "[{\"txid\":\"myid\",\"vout\":0}]" "{\"data\":\"00010203\"}"
{% endhighlight %}

*See also*

* [DecodeRawTransaction][rpc decoderawtransaction]: {{summary_decodeRawTransaction}}
* [SendRawTransaction][rpc sendrawtransaction]: {{summary_sendRawTransaction}}

{% endautocrossref %}
