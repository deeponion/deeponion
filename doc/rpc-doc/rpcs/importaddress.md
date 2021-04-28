{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/rpcs/importaddress.md" %}

##### ImportAddress
{% include helpers/subhead-links.md %}

{% assign summary_importAddress="adds a script (in hex) or address that can be watched as if it were in your wallet but cannot be used to spend." %}

{% autocrossref %}

The `importaddress` RPC {{summary_importAddress}}

Requires a new wallet backup.

*Parameter #1---script*

{% itemplate ntpd1 %}
- n: "script"
  t: "string"
  p: "Required<br>(exactly 1)"
  d: "The hex-encoded script (or address)"

{% enditemplate %}

*Parameter #2---label*

{% itemplate ntpd1 %}
- n: "label"
  t: "string"
  p: "Optional<br>Default=\"\""
  d: "An optional label"

{% enditemplate %}

*Parameter #3---rescan*

{% itemplate ntpd1 %}
- n: "rescan"
  t: "boolean"
  p: "Optional<br>Default=true"
  d: "Rescan the wallet for transactions"

{% enditemplate %}

*Parameter #4---p2sh*

{% itemplate ntpd1 %}
- n: "p2sh"
  t: "boolean"
  p: "Optional<br>Default=false"
  d: "Add the P2SH version of the script as well"

{% enditemplate %}

*Result---`null` on success*

{% itemplate ntpd1 %}
- n: "`result`"
  t: "null"
  p: "Required<br>(exactly 1)"
  d: "JSON `null` when the command was successfull or a JSON with an error field on error."

{% enditemplate %}

*Example*

Import a script with rescan

{% highlight bash %}
DeepOnion-cli importaddress "myscript"
{% endhighlight %}
Import using a label without rescan

{% highlight bash %}
DeepOnion-cli importaddress "myscript" "testing" false
{% endhighlight %}

*See also*

* [ImportPrivKey][rpc importprivkey]: {{summary_importPrivKey}}
* [ListReceivedByAddress][rpc listreceivedbyaddress]: {{summary_listReceivedByAddress}}

{% endautocrossref %}
