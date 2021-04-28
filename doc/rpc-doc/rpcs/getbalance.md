{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/rpcs/getbalance.md" %}

##### GetBalance
{% include helpers/subhead-links.md %}

{% assign summary_getBalance="if account is not specified, returns the server's total available balance." %}

{% autocrossref %}

The `getbalance` RPC {{summary_getBalance}}

The available balance is what the wallet considers currently spendable, and is
thus affected by options which limit spendability such as -spendzeroconfchange.

If account is specified (DEPRECATED), returns the balance in the account.

Note that the account "" is not the same as leaving the parameter out.

The server total may be different to the balance in the default "" account.

*Parameter #1---account*

{% itemplate ntpd1 %}
- n: "account"
  t: "string"
  p: "Optional"
  d: "DEPRECATED. The account string may be given as a
       specific account name to find the balance associated with wallet keys in
       a named account, or as the empty string (\"\") to find the balance
       associated with wallet keys not in any named account, or as \"*\" to find
       the balance associated with all wallet keys regardless of account.
       When this option is specified, it calculates the balance in a different
       way than when it is not specified, and which can count spends twice when
       there are conflicting pending transactions (such as those created by
       the bumpfee command), temporarily resulting in low or even negative
       balances. In general, account balance calculation is not considered
       reliable and has resulted in confusing outcomes, so it is recommended to
       avoid passing this argument."

{% enditemplate %}

*Parameter #2---minconf*

{% itemplate ntpd1 %}
- n: "minconf"
  t: "number (int)"
  p: "Optional<br>Default=1"
  d: "Only include transactions confirmed at least this many times."

{% enditemplate %}

*Parameter #3---include_watchonly*

{% itemplate ntpd1 %}
- n: "include_watchonly"
  t: "bool"
  p: "Optional<br>Default=false"
  d: "Also include balance in watch-only addresses (see 'importaddress')"

{% enditemplate %}

*Result*

{% itemplate ntpd1 %}
- n: "`result`"
  t: "number (int)"
  p: "Required<br>(exactly 1)"
  d: "The total amount in ONION received for this account."

{% enditemplate %}

*Example*

The total amount in the wallet with 1 or more confirmations

{% highlight bash %}
DeepOnion-cli getbalance
{% endhighlight %}
The total amount in the wallet at least 6 blocks confirmed

{% highlight bash %}
DeepOnion-cli getbalance "*" 6
{% endhighlight %}

*See also*

* [GetReceivedByAddress][rpc getreceivedbyaddress]: {{summary_getReceivedByAddress}}

{% endautocrossref %}
