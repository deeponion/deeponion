{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/rpcs/getnewaddress.md" %}

##### GetNewAddress
{% include helpers/subhead-links.md %}

{% assign summary_getNewAddress="returns a new DeepOnion address for receiving payments." %}

{% autocrossref %}

The `getnewaddress` RPC {{summary_getNewAddress}}

If 'account' is specified (DEPRECATED), it is added to the address book
so payments received with the address will be credited to 'account'.

*Parameter #1---account*

{% itemplate ntpd1 %}
- n: "account"
  t: "string"
  p: "Optional"
  d: "DEPRECATED. The account name for the address to be linked to. If not provided, the default account \"\" is used. It can also be set to the empty string \"\" to represent the default account. The account does not need to exist, it will be created if there is no account by the given name."

{% enditemplate %}

*Parameter #2---address_type*

{% itemplate ntpd1 %}
- n: "address_type"
  t: "string"
  p: "Optional"
  d: "The address type to use. Options are \"legacy\", \"p2sh-segwit\", and \"bech32\". Default is set by -addresstype."

{% enditemplate %}

*Result*

{% itemplate ntpd1 %}
- n: "`result`"
  t: "string (hex)"
  p: "Required<br>(exactly 1)"
  d: "The new DeepOnion address"

{% enditemplate %}

*Example*

{% highlight bash %}
DeepOnion-cli getnewaddress
{% endhighlight %}

*See also*

* [GetRawChangeAddress][rpc getrawchangeaddress]: {{summary_getRawChangeAddress}}
* [GetBalance][rpc getbalance]: {{summary_getBalance}}

{% endautocrossref %}
