{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/rpcs/getaccountaddress.md" %}

##### GetAccountAddress
{% include helpers/subhead-links.md %}

{% assign summary_getAccountAddress="dEPRECATED." %}

{% autocrossref %}

The `getaccountaddress` RPC {{summary_getAccountAddress}}

Returns the current DeepOnion address for receiving payments to this account.

*Parameter #1---account*

{% itemplate ntpd1 %}
- n: "account"
  t: "string"
  p: "Required<br>(exactly 1)"
  d: "The account name for the address. It can also be set to the empty string \"\" to represent the default account. The account does not need to exist, it will be created and a new address created  if there is no account by the given name."

{% enditemplate %}

*Result*

{% itemplate ntpd1 %}
- n: "`result`"
  t: "string (hex)"
  p: "Required<br>(exactly 1)"
  d: "The account DeepOnion address"

{% enditemplate %}

*Example*

{% highlight bash %}
DeepOnion-cli getaccountaddress
{% endhighlight %}
{% highlight bash %}
DeepOnion-cli getaccountaddress ""
{% endhighlight %}
{% highlight bash %}
DeepOnion-cli getaccountaddress "myaccount"
{% endhighlight %}

{% endautocrossref %}
