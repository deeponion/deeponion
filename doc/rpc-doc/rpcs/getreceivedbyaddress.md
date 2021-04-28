{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/rpcs/getreceivedbyaddress.md" %}

##### GetReceivedByAddress
{% include helpers/subhead-links.md %}

{% assign summary_getReceivedByAddress="returns the total amount received by the given address in transactions with at least minconf confirmations." %}

{% autocrossref %}

The `getreceivedbyaddress` RPC {{summary_getReceivedByAddress}}

*Parameter #1---address*

{% itemplate ntpd1 %}
- n: "address"
  t: "string"
  p: "Required<br>(exactly 1)"
  d: "The DeepOnion address for transactions."

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
  d: "The total amount in ONION received at this address."

{% enditemplate %}

*Example*

The amount from transactions with at least 1 confirmation

{% highlight bash %}
DeepOnion-cli getreceivedbyaddress "Dc7BLTLqSyWSp6uEpQPbbcb7figA7xHjKQ"
{% endhighlight %}
The amount including unconfirmed transactions, zero confirmations

{% highlight bash %}
DeepOnion-cli getreceivedbyaddress "Dc7BLTLqSyWSp6uEpQPbbcb7figA7xHjKQ" 0
{% endhighlight %}
The amount with at least 6 confirmations

{% highlight bash %}
DeepOnion-cli getreceivedbyaddress "Dc7BLTLqSyWSp6uEpQPbbcb7figA7xHjKQ" 6
{% endhighlight %}

{% endautocrossref %}
