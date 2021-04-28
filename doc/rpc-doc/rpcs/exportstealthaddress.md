{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/rpcs/exportstealthaddress.md" %}

##### ExportstealthAddress
{% include helpers/subhead-links.md %}

{% assign summary_exportstealthAddress="exports the given stealth address." %}

{% autocrossref %}

The `exportstealthaddress` RPC {{summary_exportstealthAddress}}

*Parameter #1---label*

{% itemplate ntpd1 %}
- n: "label"
  t: "string"
  p: "Optional<br>Default=\"\""
  d: "Stealth address label to export"

{% enditemplate %}

*Result*

{% endautocrossref %}

    {
      "label": "str",          (string) Stealth address label.
      "Scan Secret": "str",    (string) Scan secret.
      "Spend Secret": "str",   (string) Spend secret.
    }

{% autocrossref %}

*Example*

{% highlight bash %}
DeepOnion-cli exportstealthaddress mystealthaddress
{% endhighlight %}

{% endautocrossref %}
