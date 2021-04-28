{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/rpcs/listservicenodes.md" %}

##### ListServiceNodeS
{% include helpers/subhead-links.md %}

{% assign summary_listServiceNodeS="lists the currently connected service nodes." %}

{% autocrossref %}

The `listservicenodes` RPC {{summary_listServiceNodeS}}

*Parameters: none*

*Result*

{% endautocrossref %}

    [                         (json array of strings)
      "nodeaddress"         (string) The node tor address
       ...
    ]

{% autocrossref %}

*Example*

{% highlight bash %}
DeepOnion-cli listservicenodes
{% endhighlight %}

{% endautocrossref %}
