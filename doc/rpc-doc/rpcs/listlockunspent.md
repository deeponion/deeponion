{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/rpcs/listlockunspent.md" %}

##### ListLockUnspent
{% include helpers/subhead-links.md %}

{% assign summary_listLockUnspent="returns list of temporarily unspendable outputs." %}

{% autocrossref %}

The `listlockunspent` RPC {{summary_listLockUnspent}}

See the lockunspent call to lock and unlock transactions for spending.

*Parameters: none*

*Result*

{% endautocrossref %}

    [
      {
        "txid" : "transactionid",     (string) The transaction id locked
        "vout" : n                      (numeric) The vout value
      }
      ,...
    ]

{% autocrossref %}

*Example*

List the unspent transactions

{% highlight bash %}
DeepOnion-cli listunspent
{% endhighlight %}
Lock an unspent transaction

{% highlight bash %}
DeepOnion-cli lockunspent false "[{\"txid\":\"daaf44ec1e64e66ffda4a7e195ea60d5c8c8b602fc6bf22928582d3ff2530462\",\"vout\":1}]"
{% endhighlight %}
List the locked transactions

{% highlight bash %}
DeepOnion-cli listlockunspent
{% endhighlight %}
Unlock the transaction again

{% highlight bash %}
DeepOnion-cli lockunspent true "[{\"txid\":\"daaf44ec1e64e66ffda4a7e195ea60d5c8c8b602fc6bf22928582d3ff2530462\",\"vout\":1}]"
{% endhighlight %}

*See also*

* [LockUnspent][rpc lockunspent]: {{summary_lockUnspent}}

{% endautocrossref %}
