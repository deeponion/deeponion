{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/rpcs/listunspent.md" %}

##### ListUnspent
{% include helpers/subhead-links.md %}

{% assign summary_listUnspent="returns array of unspent transaction outputs with between minconf and maxconf (inclusive) confirmations." %}

{% autocrossref %}

The `listunspent` RPC {{summary_listUnspent}}

Optionally filter to only include txouts paid to specified addresses.

*Parameter #1---minconf*

{% itemplate ntpd1 %}
- n: "minconf"
  t: "number (int)"
  p: "Optional<br>Default=1"
  d: "The minimum confirmations to filter"

{% enditemplate %}

*Parameter #2---maxconf*

{% itemplate ntpd1 %}
- n: "maxconf"
  t: "number (int)"
  p: "Optional<br>Default=9999999"
  d: "The maximum confirmations to filter"

{% enditemplate %}

*Parameter #3---addresses*

{% itemplate ntpd1 %}
- n: "addresses"
  t: "string"
  p: "Required"
  d: "A json array of DeepOnion addresses to filter"

{% enditemplate %}

{% endautocrossref %}

    [
      "address"     (string) DeepOnion address
      ,...
    ]

{% autocrossref %}

*Parameter #4---include_unsafe*

{% itemplate ntpd1 %}
- n: "include_unsafe"
  t: "bool"
  p: "Optional<br>Default=true"
  d: "Include outputs that are not safe to spend
       See description of \"safe\" attribute below."

{% enditemplate %}

*Parameter #5---query_options*

{% itemplate ntpd1 %}
- n: "query_options"
  t: "json"
  p: "Optional"
  d: "JSON with query options"

{% enditemplate %}

{% endautocrossref %}

    {
      "minimumAmount"    (numeric or string, default=0) Minimum value of each UTXO in ONION
      "maximumAmount"    (numeric or string, default=unlimited) Maximum value of each UTXO in ONION
      "maximumCount"     (numeric or string, default=unlimited) Maximum number of UTXOs
      "minimumSumAmount" (numeric or string, default=unlimited) Minimum sum value of all UTXOs in ONION
    }

{% autocrossref %}

*Result*

{% endautocrossref %}

    [                   (array of json object)
      {
        "txid" : "txid",          (string) the transaction id
        "vout" : n,               (numeric) the vout value
        "address" : "address",    (string) the DeepOnion address
        "account" : "account",    (string) DEPRECATED. The associated account, or "" for the default account
        "scriptPubKey" : "key",   (string) the script key
        "amount" : x.xxx,         (numeric) the transaction output amount in ONION
        "confirmations" : n,      (numeric) The number of confirmations
        "redeemScript" : n        (string) The redeemScript if scriptPubKey is P2SH
        "spendable" : xxx,        (bool) Whether we have the private keys to spend this output
        "solvable" : xxx,         (bool) Whether we know how to spend this output, ignoring the lack of keys
        "safe" : xxx              (bool) Whether this output is considered safe to spend. Unconfirmed transactions
                                  from outside keys and unconfirmed replacement transactions are considered unsafe
                                  and are not eligible for spending by fundrawtransaction and sendtoaddress.
      }
      ,...
    ]

{% autocrossref %}

*See also*

* [ListTransactions][rpc listtransactions]: {{summary_listTransactions}}
* [LockUnspent][rpc lockunspent]: {{summary_lockUnspent}}

{% endautocrossref %}
