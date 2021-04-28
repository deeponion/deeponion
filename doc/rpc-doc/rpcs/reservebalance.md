{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/rpcs/reservebalance.md" %}

##### ReserveBalance
{% include helpers/subhead-links.md %}

{% assign summary_reserveBalance="show or set reserve amount not participating in network protection." %}

{% autocrossref %}

The `reservebalance` RPC {{summary_reserveBalance}}

If no parameters provided current setting is printed.

*Parameter #1---reserve*

{% itemplate ntpd1 %}
- n: "reserve"
  t: "boolean"
  p: "Optional"
  d: "is true or false to turn balance reserve on or off."

{% enditemplate %}

*Parameter #2---amount*

{% itemplate ntpd1 %}
- n: "amount"
  t: "number (int)"
  p: "Optional"
  d: "is a real and rounded to cent."

{% enditemplate %}

*Result*

{% endautocrossref %}

    {
      "reserve": true|false   (boolean) Status of the reserve balance
      "amount": x.xxxx        (numeric) Amount reserved
    }

{% autocrossref %}

*Example*

{% highlight bash %}
DeepOnion-cli reservebalance true 120000
{% endhighlight %}

{% endautocrossref %}
