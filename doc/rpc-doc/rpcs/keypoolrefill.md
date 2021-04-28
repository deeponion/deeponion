{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/rpcs/keypoolrefill.md" %}

##### KeyPoolRefill
{% include helpers/subhead-links.md %}

{% assign summary_keyPoolRefill="fills the keypool." %}

{% autocrossref %}

The `keypoolrefill` RPC {{summary_keyPoolRefill}}

Arguments
1. newsize     (numeric, optional, default=100) The new keypool size

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
DeepOnion-cli keypoolrefill
{% endhighlight %}

*See also*

* [GetNewAddress][rpc getnewaddress]: {{summary_getNewAddress}}
* [GetWalletInfo][rpc getwalletinfo]: {{summary_getWalletInfo}}

{% endautocrossref %}
