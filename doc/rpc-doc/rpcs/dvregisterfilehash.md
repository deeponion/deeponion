{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/rpcs/dvregisterfilehash.md" %}

##### DvregisterfileHash
{% include helpers/subhead-links.md %}

{% assign summary_dvregisterfileHash="register a file (hash) in DeepOnion blockchain." %}

{% autocrossref %}

The `dvregisterfilehash` RPC {{summary_dvregisterfileHash}}

*Parameters: none*

*Result---`null` on success*

{% itemplate ntpd1 %}
- n: "`result`"
  t: "null"
  p: "Required<br>(exactly 1)"
  d: "JSON `null` when the command was successfull or a JSON with an error field on error."

{% enditemplate %}

{% endautocrossref %}
