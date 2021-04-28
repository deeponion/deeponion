{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/rpcs/move.md" %}

##### Move
{% include helpers/subhead-links.md %}

{% assign summary_move="dEPRECATED." %}

{% autocrossref %}

The `move` RPC {{summary_move}}

Move a specified amount from one account in your wallet to another.

*Parameter #1---fromaccount*

{% itemplate ntpd1 %}
- n: "fromaccount"
  t: "string"
  p: "Required<br>(exactly 1)"
  d: "The name of the account to move funds from. May be the default account using \"\"."

{% enditemplate %}

*Parameter #2---toaccount*

{% itemplate ntpd1 %}
- n: "toaccount"
  t: "string"
  p: "Required<br>(exactly 1)"
  d: "The name of the account to move funds to. May be the default account using \"\"."

{% enditemplate %}

*Parameter #3---amount*

{% itemplate ntpd1 %}
- n: "amount"
  t: "number (int)"
  p: "Required"
  d: "Quantity of ONION to move between accounts."

{% enditemplate %}

*Parameter #4---(dummy)*

{% itemplate ntpd1 %}
- n: "(dummy)"
  t: "number (int)"
  p: "Optional"
  d: "Ignored. Remains for backward compatibility."

{% enditemplate %}

*Parameter #5---comment*

{% itemplate ntpd1 %}
- n: "comment"
  t: "string"
  p: "Optional"
  d: "An optional comment, stored in the wallet only."

{% enditemplate %}

*Result*

{% itemplate ntpd1 %}
- n: "`result`"
  t: "boolean"
  p: "Required<br>(exactly 1)"
  d: "true if successful."

{% enditemplate %}

*Example*

Move 0.01 ONION from the default account to the account named tabby

{% highlight bash %}
DeepOnion-cli move "" "tabby" 0.01
{% endhighlight %}
Move 0.01 ONION timotei to akiko with a comment and funds have 6 confirmations

{% highlight bash %}
DeepOnion-cli move "timotei" "akiko" 0.01 6 "happy birthday!"
{% endhighlight %}

{% endautocrossref %}
