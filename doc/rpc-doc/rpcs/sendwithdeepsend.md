{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/rpcs/sendwithdeepsend.md" %}

##### SendWithdeepSend
{% include helpers/subhead-links.md %}

{% assign summary_sendWithdeepSend="send an amount to a given address unisng deepsend service." %}

{% autocrossref %}

The `sendwithdeepsend` RPC {{summary_sendWithdeepSend}}

*Parameter #1---address*

{% itemplate ntpd1 %}
- n: "address"
  t: "string"
  p: "Required<br>(exactly 1)"
  d: "The DeepOnion address to send to."

{% enditemplate %}

*Parameter #2---amount*

{% itemplate ntpd1 %}
- n: "amount"
  t: "numeric or string"
  p: "Required<br>(exactly 1)"
  d: "The amount in ONION to send. eg 0.1"

{% enditemplate %}

*Result*

{% itemplate ntpd1 %}
- n: "`result`"
  t: "string (hex)"
  p: "Required<br>(exactly 1)"
  d: "Info related with deepsend service."

{% enditemplate %}

*Example*

{% highlight bash %}
DeepOnion-cli sendwithdeepsend "Dc7BLTLqSyWSp6uEpQPbbcb7figA7xHjKQ" 0.123
{% endhighlight %}

{% endautocrossref %}
