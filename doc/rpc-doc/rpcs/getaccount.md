{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/rpcs/getaccount.md" %}

##### GetAccount
{% include helpers/subhead-links.md %}

{% assign summary_getAccount="dEPRECATED." %}

{% autocrossref %}

The `getaccount` RPC {{summary_getAccount}}

Returns the account associated with the given address.

*Parameter #1---address*

{% itemplate ntpd1 %}
- n: "address"
  t: "string"
  p: "Required<br>(exactly 1)"
  d: "The DeepOnion address for account lookup."

{% enditemplate %}

*Result*

{% itemplate ntpd1 %}
- n: "`result`"
  t: "string (hex)"
  p: "Required<br>(exactly 1)"
  d: "the account address"

{% enditemplate %}

*Example*

{% highlight bash %}
DeepOnion-cli getaccount "Dc7BLTLqSyWSp6uEpQPbbcb7figA7xHjKQ"
{% endhighlight %}

{% endautocrossref %}
