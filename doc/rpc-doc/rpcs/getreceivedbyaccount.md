{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/rpcs/getreceivedbyaccount.md" %}

##### GetReceivedByAccount
{% include helpers/subhead-links.md %}

{% assign summary_getReceivedByAccount="dEPRECATED." %}

{% autocrossref %}

The `getreceivedbyaccount` RPC {{summary_getReceivedByAccount}}

Returns the total amount received by addresses with <account> in transactions with at least [minconf] confirmations.

*Parameter #1---account*

{% itemplate ntpd1 %}
- n: "account"
  t: "string"
  p: "Required<br>(exactly 1)"
  d: "The selected account, may be the default account using \"\"."

{% enditemplate %}

*Parameter #2---minconf*

{% itemplate ntpd1 %}
- n: "minconf"
  t: "number (int)"
  p: "Optional<br>Default=1"
  d: "Only include transactions confirmed at least this many times."

{% enditemplate %}

*Result*

{% itemplate ntpd1 %}
- n: "`result`"
  t: "number (int)"
  p: "Required<br>(exactly 1)"
  d: "The total amount in ONION received for this account."

{% enditemplate %}

*Example*

Amount received by the default account with at least 1 confirmation

{% highlight bash %}
DeepOnion-cli getreceivedbyaccount ""
{% endhighlight %}
Amount received at the tabby account including unconfirmed amounts with zero confirmations

{% highlight bash %}
DeepOnion-cli getreceivedbyaccount "tabby" 0
{% endhighlight %}
The amount with at least 6 confirmations

{% highlight bash %}
DeepOnion-cli getreceivedbyaccount "tabby" 6
{% endhighlight %}

{% endautocrossref %}
