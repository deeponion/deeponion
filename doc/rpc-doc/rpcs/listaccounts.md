{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/rpcs/listaccounts.md" %}

##### ListAccounts
{% include helpers/subhead-links.md %}

{% assign summary_listAccounts="dEPRECATED." %}

{% autocrossref %}

The `listaccounts` RPC {{summary_listAccounts}}

Returns Object that has account names as keys, account balances as values.

*Parameter #1---minconf*

{% itemplate ntpd1 %}
- n: "minconf"
  t: "number (int)"
  p: "Optional<br>Default=1"
  d: "Only include transactions with at least this many confirmations"

{% enditemplate %}

*Parameter #2---include_watchonly*

{% itemplate ntpd1 %}
- n: "include_watchonly"
  t: "bool"
  p: "Optional<br>Default=false"
  d: "Include balances in watch-only addresses (see 'importaddress')"

{% enditemplate %}

*Result*

{% endautocrossref %}

    {                      (json object where keys are account names, and values are numeric balances
      "account": x.xxx,  (numeric) The property name is the account name, and the value is the total balance for the account.
      ...
    }

{% autocrossref %}

*Example*

List account balances where there at least 1 confirmation

{% highlight bash %}
DeepOnion-cli listaccounts
{% endhighlight %}
List account balances including zero confirmation transactions

{% highlight bash %}
DeepOnion-cli listaccounts 0
{% endhighlight %}
List account balances for 6 or more confirmations

{% highlight bash %}
DeepOnion-cli listaccounts 6
{% endhighlight %}

{% endautocrossref %}
