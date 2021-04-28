{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/rpcs/setaccount.md" %}

##### SetAccount
{% include helpers/subhead-links.md %}

{% assign summary_setAccount="dEPRECATED." %}

{% autocrossref %}

The `setaccount` RPC {{summary_setAccount}}

Sets the account associated with the given address.

*Parameter #1---address*

{% itemplate ntpd1 %}
- n: "address"
  t: "string"
  p: "Required<br>(exactly 1)"
  d: "The DeepOnion address to be associated with an account."

{% enditemplate %}

*Parameter #2---account*

{% itemplate ntpd1 %}
- n: "account"
  t: "string"
  p: "Required<br>(exactly 1)"
  d: "The account to assign the address to."

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
DeepOnion-cli setaccount "Dc7BLTLqSyWSp6uEpQPbbcb7figA7xHjKQ" "tabby"
{% endhighlight %}

{% endautocrossref %}
