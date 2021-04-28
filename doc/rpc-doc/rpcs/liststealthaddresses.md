{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/rpcs/liststealthaddresses.md" %}

##### ListStealthAddressEs
{% include helpers/subhead-links.md %}

{% assign summary_listStealthAddressEs="list owned stealth addresses." %}

{% autocrossref %}

The `liststealthaddresses` RPC {{summary_listStealthAddressEs}}

*Parameter #1---show_secrets*

{% itemplate ntpd1 %}
- n: "show_secrets"
  t: "bool"
  p: "Optional"
  d: "Display secret keys to stealth addresses.
       If [show_secrets] is true secret keys to stealth addresses will be shown 
       The wallet must be unlocked if true."

{% enditemplate %}

*Result*

{% endautocrossref %}

    {
      "Stealth Address": {
        "Label": "str",          (string) Stealth address label.
        "Address": "str",        (string) Stealth address.
        "Scan Secret": "str",    (string) Scan secret, if show_secrets=1.
        "Spend Secret": "str",   (string) Spend secret, if show_secrets=1.
      }
    }

{% autocrossref %}

*Example*

{% highlight bash %}
DeepOnion-cli liststealthaddresses
{% endhighlight %}

{% endautocrossref %}
