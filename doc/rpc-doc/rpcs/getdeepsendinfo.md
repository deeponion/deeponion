{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/rpcs/getdeepsendinfo.md" %}

##### GetDeepSendInfo
{% include helpers/subhead-links.md %}

{% assign summary_getDeepSendInfo="returns an object containing deepsend-related information." %}

{% autocrossref %}

The `getdeepsendinfo` RPC {{summary_getDeepSendInfo}}

*Parameters: none*

*Result*

{% endautocrossref %}

    {
      "enabled": true,             (boolean) If deepsend is enabled
      "servicenodes": 2,           (int) Currently connected service nodes
      "anontxinprogress": true,    (boolean) If deepsend tx is in progress
    }

{% autocrossref %}

*Example*

{% highlight bash %}
DeepOnion-cli getdeepsendinfo
{% endhighlight %}

{% endautocrossref %}
