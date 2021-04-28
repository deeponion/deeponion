{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/rpcs/getlastanontxinfo.md" %}

##### GetLastanonTxInfo
{% include helpers/subhead-links.md %}

{% assign summary_getLastanonTxInfo="returns the last/current anonymous transaction info and log." %}

{% autocrossref %}

The `getlastanontxinfo` RPC {{summary_getLastanonTxInfo}}

*Parameters: none*

*Result*

{% itemplate ntpd1 %}
- n: "`result`"
  t: "string (hex)"
  p: "Required<br>(exactly 1)"
  d: "The transaction info"

{% enditemplate %}

*Example*

{% highlight bash %}
DeepOnion-cli getlastanontxinfo
{% endhighlight %}

{% endautocrossref %}
