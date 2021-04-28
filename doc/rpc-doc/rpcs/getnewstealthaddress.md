{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/rpcs/getnewstealthaddress.md" %}

##### GetNewstealthAddress
{% include helpers/subhead-links.md %}

{% assign summary_getNewstealthAddress="returns a new DeepOnion stealth address for receiving payments anonymously." %}

{% autocrossref %}

The `getnewstealthaddress` RPC {{summary_getNewstealthAddress}}

*Parameter #1---label*

{% itemplate ntpd1 %}
- n: "label"
  t: "string"
  p: "Optional<br>Default=\"\""
  d: "An optional label"

{% enditemplate %}

*Result*

{% endautocrossref %}

    {
      "Label": "str",          (string) Stealth address label.
      "Address": "str",        (string) New DeepOnion Stealth address.
    }

{% autocrossref %}

*Example*

{% highlight bash %}
DeepOnion-cli getnewstealthaddress mystealthaddress
{% endhighlight %}

{% endautocrossref %}
