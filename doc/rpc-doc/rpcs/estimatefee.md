{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/rpcs/estimatefee.md" %}

##### EstimateFee
{% include helpers/subhead-links.md %}

{% assign summary_estimateFee="dEPRECATED." %}

{% autocrossref %}

The `estimatefee` RPC {{summary_estimateFee}}

Please use estimatesmartfee for more intelligent estimates.

Estimates the approximate fee per kilobyte needed for a transaction to begin
confirmation within nblocks blocks. Uses virtual transaction size of transaction
as defined in BIP 141 (witness data is discounted).

*Parameter #1---nblocks*

{% itemplate ntpd1 %}
- n: "nblocks"
  t: "number (int)"
  p: "Required<br>(exactly 1)"
  d: ""

{% enditemplate %}

*Result*

{% itemplate ntpd1 %}
- n: "`result`"
  t: "number (int)"
  p: "Required<br>(exactly 1)"
  d: "estimated fee-per-kilobyte"

{% enditemplate %}

*Example*

{% highlight bash %}
DeepOnion-cli estimatefee 6
{% endhighlight %}

*See also*

* [SetTxFee][rpc settxfee]: {{summary_setTxFee}}

{% endautocrossref %}
