{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/rpcs/getaddressesbyaccount.md" %}

##### GetAddressesByAccount
{% include helpers/subhead-links.md %}

{% assign summary_getAddressesByAccount="dEPRECATED." %}

{% autocrossref %}

The `getaddressesbyaccount` RPC {{summary_getAddressesByAccount}}

Returns the list of addresses for the given account.

*Parameter #1---account*

{% itemplate ntpd1 %}
- n: "account"
  t: "string"
  p: "Required<br>(exactly 1)"
  d: "The account name."

{% enditemplate %}

*Result*

{% endautocrossref %}

    [                     (json array of string)
      "address"         (string) a DeepOnion address associated with the given account
      ,...
    ]

{% autocrossref %}

*Example*

{% highlight bash %}
DeepOnion-cli getaddressesbyaccount "tabby"
{% endhighlight %}

*See also*

* [GetBalance][rpc getbalance]: {{summary_getBalance}}

{% endautocrossref %}
