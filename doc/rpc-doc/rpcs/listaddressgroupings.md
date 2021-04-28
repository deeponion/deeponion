{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/rpcs/listaddressgroupings.md" %}

##### ListAddressGroupings
{% include helpers/subhead-links.md %}

{% assign summary_listAddressGroupings="lists groups of addresses which have had their common ownership made public by common use as inputs or as the resulting change in past transactions." %}

{% autocrossref %}

The `listaddressgroupings` RPC {{summary_listAddressGroupings}}

*Parameters: none*

*Result*

{% endautocrossref %}

    [
      [
        [
          "address",            (string) The DeepOnion address
          amount,                 (numeric) The amount in ONION
          "account"             (string, optional) DEPRECATED. The account
        ]
        ,...
      ]
      ,...
    ]

{% autocrossref %}

*Example*

{% highlight bash %}
DeepOnion-cli listaddressgroupings
{% endhighlight %}

*See also*

* [GetTransaction][rpc gettransaction]: {{summary_getTransaction}}

{% endautocrossref %}
