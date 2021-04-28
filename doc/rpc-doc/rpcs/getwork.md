{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/rpcs/getwork.md" %}

##### GetWork
{% include helpers/subhead-links.md %}

{% assign summary_getWork="if [data] is not specified, returns formatted hash data to work on:    "midstate" : precomputed hash state after hashing the first half of the data (DEPRECATED)   "data" : block data   "hash1" : formatted hash buffer for second hash (DEPRECATED)   "target" : little endian hash target  If [data] is specified, tries to solve the block and returns true if it was successful." %}

{% autocrossref %}

The `getwork` RPC {{summary_getWork}}

*Parameters: none*

*Result---`null` on success*

{% itemplate ntpd1 %}
- n: "`result`"
  t: "null"
  p: "Required<br>(exactly 1)"
  d: "JSON `null` when the command was successfull or a JSON with an error field on error."

{% enditemplate %}

*See also*

* [GetBlockTemplate][rpc getblocktemplate]: {{summary_getBlockTemplate}}
* [SubmitBlock][rpc submitblock]: {{summary_submitBlock}}

{% endautocrossref %}
