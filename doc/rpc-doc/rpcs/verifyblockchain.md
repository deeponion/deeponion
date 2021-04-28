{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/rpcs/verifyblockchain.md" %}

##### VerifyBlockChain
{% include helpers/subhead-links.md %}

{% assign summary_verifyBlockChain="verifies the authenticity of the DeepOnion blockchain." %}

{% autocrossref %}

The `verifyblockchain` RPC {{summary_verifyBlockChain}}

This action can take some time (minutes)

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
DeepOnion-cli verifyblockchain
{% endhighlight %}

{% endautocrossref %}
