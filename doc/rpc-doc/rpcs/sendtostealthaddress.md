{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/rpcs/sendtostealthaddress.md" %}

##### SendTostealthAddress
{% include helpers/subhead-links.md %}

{% assign summary_sendTostealthAddress="send an amount to a given address." %}

{% autocrossref %}

The `sendtostealthaddress` RPC {{summary_sendTostealthAddress}}

*Parameter #1---address*

{% itemplate ntpd1 %}
- n: "address"
  t: "string"
  p: "Required<br>(exactly 1)"
  d: "The DeepOnion stealth address to send to."

{% enditemplate %}

*Parameter #2---amount*

{% itemplate ntpd1 %}
- n: "amount"
  t: "numeric or string"
  p: "Required<br>(exactly 1)"
  d: "The amount in ONION to send. eg 0.1"

{% enditemplate %}

*Parameter #3---narration*

{% itemplate ntpd1 %}
- n: "narration"
  t: "string"
  p: "Optional"
  d: "A comment sent to the receiver of the transaction. "

{% enditemplate %}

*Parameter #4---comment*

{% itemplate ntpd1 %}
- n: "comment"
  t: "string"
  p: "Optional"
  d: "A comment used to store what the transaction is for. 
       This is not part of the transaction, just kept in your wallet."

{% enditemplate %}

*Parameter #5---comment_to*

{% itemplate ntpd1 %}
- n: "comment_to"
  t: "string"
  p: "Optional"
  d: "A comment to store the name of the person or organization 
       to which you're sending the transaction. This is not part of the 
       transaction, just kept in your wallet."

{% enditemplate %}

*Parameter #6---subtractfeefromamount*

{% itemplate ntpd1 %}
- n: "subtractfeefromamount"
  t: "boolean"
  p: "Optional<br>Default=false"
  d: "The fee will be deducted from the amount being sent.
       The recipient will receive less DeepOnion than you enter in the amount field."

{% enditemplate %}

*Parameter #7---replaceable*

{% itemplate ntpd1 %}
- n: "replaceable"
  t: "boolean"
  p: "Optional"
  d: "Allow this transaction to be replaced by a transaction with higher fees via BIP 125"

{% enditemplate %}

*Parameter #8---conf_target*

{% itemplate ntpd1 %}
- n: "conf_target"
  t: "number (int)"
  p: "Optional"
  d: "Confirmation target (in blocks)"

{% enditemplate %}

*Parameter #9---estimate_mode*

{% itemplate ntpd1 %}
- n: "estimate_mode"
  t: "string"
  p: "Optional<br>Default=UNSET"
  d: "The fee estimate mode, must be one of:
       \"UNSET\"
       \"ECONOMICAL\"
       \"CONSERVATIVE\""

{% enditemplate %}

*Result*

{% itemplate ntpd1 %}
- n: "`result`"
  t: "string (hex)"
  p: "Required<br>(exactly 1)"
  d: "The transaction id."

{% enditemplate %}

*Example*

{% highlight bash %}
DeepOnion-cli sendtostealthaddress "smYkiNESACbF79HHm3Er6U6h2x7Ty6HG1A2QSTqEqBm9xb1QbFtkp6wPVGLzAgWg1pXHLQzrU6FgYPkq7PLY9fwmpPYdC9cGydo36h" 0.123
{% endhighlight %}
{% highlight bash %}
DeepOnion-cli sendtostealthaddress "smYkiNESACbF79HHm3Er6U6h2x7Ty6HG1A2QSTqEqBm9xb1QbFtkp6wPVGLzAgWg1pXHLQzrU6FgYPkq7PLY9fwmpPYdC9cGydo36h" 0.123 "narration"
{% endhighlight %}

{% endautocrossref %}
