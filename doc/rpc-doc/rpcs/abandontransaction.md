{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/rpcs/abandontransaction.md" %}

##### AbandonTransaction
{% include helpers/subhead-links.md %}

{% assign summary_abandonTransaction="marks an in-wallet transaction and all its in-wallet descendants as abandoned. This allows their inputs to be respent." %}

{% autocrossref %}

*Added in Bitcoin Core 0.12.0*

The `abandontransaction` RPC {{summary_abandonTransaction}}

Mark in-wallet transaction <txid> as abandoned
This will mark this transaction and all its in-wallet descendants as abandoned which will allow
for their inputs to be respent.  It can be used to replace "stuck" or evicted transactions.

It only works on transactions which are not included in a block and are not currently in the mempool.

It has no effect on transactions which are already conflicted or abandoned.

*Parameter #1---txid*

{% itemplate ntpd1 %}
- n: "txid"
  t: "string (hex)"
  p: "Required<br>(exactly 1)"
  d: "The transaction id"

{% enditemplate %}

*Result---`null` on success*

{% itemplate ntpd1 %}
- n: "`result`"
  t: "null"
  p: "Required<br>(exactly 1)"
  d: "JSON `null` when the command was successfull or a JSON with an error field on error."

{% enditemplate %}

*Example*

{% highlight bash %}
DeepOnion-cli abandontransaction "c1700d6dd3e690866de56686e893cbe4e637eb5d84e3591cdfbbdbb0fcee49f8"
{% endhighlight %}

*See also*

* [SendRawTransaction][rpc sendrawtransaction]: {{summary_sendRawTransaction}}

{% endautocrossref %}
