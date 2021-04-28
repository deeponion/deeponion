{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/rpcs/importstealthaddress.md" %}

##### ImportStealthAddress
{% include helpers/subhead-links.md %}

{% assign summary_importStealthAddress="imports owned stealth address." %}

{% autocrossref %}

The `importstealthaddress` RPC {{summary_importStealthAddress}}

*Parameter #1---scan_secret*

{% itemplate ntpd1 %}
- n: "scan_secret"
  t: "string"
  p: "Required<br>(exactly 1)"
  d: "Scan secret."

{% enditemplate %}

*Parameter #2---spend_secret*

{% itemplate ntpd1 %}
- n: "spend_secret"
  t: "string"
  p: "Required<br>(exactly 1)"
  d: "Spend secret."

{% enditemplate %}

*Parameter #3---label*

{% itemplate ntpd1 %}
- n: "label"
  t: "string"
  p: "Optional<br>Default=\"\""
  d: "Stealth address label to import"

{% enditemplate %}

*Result*

{% endautocrossref %}

    {
      "result": "str",     (string) Import status: success or failed.
      "address": "str",    (string) Imported stealth address.
    }

{% autocrossref %}

*Example*

{% highlight bash %}
DeepOnion-cli importstealthaddress my_scan_secret my_spend_secret
{% endhighlight %}

{% endautocrossref %}
