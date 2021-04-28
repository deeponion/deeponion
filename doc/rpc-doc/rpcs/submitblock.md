{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/rpcs/submitblock.md" %}

##### SubmitBlock
{% include helpers/subhead-links.md %}

{% assign summary_submitBlock="attempts to submit new block to network." %}

{% autocrossref %}

The `submitblock` RPC {{summary_submitBlock}}

See https://en.bitcoin.it/wiki/BIP_0022 for full specification.

Arguments
1. "hexdata"        (string, required) the hex-encoded block data to submit
2. "dummy"          (optional) dummy value, for compatibility with BIP22. This value is ignored.

*Parameters: none*

*Result---`null` on success*

{% itemplate ntpd1 %}
- n: "`result`"
  t: "null"
  p: "Required<br>(exactly 1)"
  d: "JSON `null` when the command was successfull or a JSON with an error field on error."

{% enditemplate %}

*Example*

{% highlight bash %}
DeepOnion-cli submitblock "mydata"
{% endhighlight %}

*See also*

* [GetBlockTemplate][rpc getblocktemplate]: {{summary_getBlockTemplate}}

{% endautocrossref %}
