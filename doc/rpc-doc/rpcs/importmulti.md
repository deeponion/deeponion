{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/rpcs/importmulti.md" %}

##### ImportMulti
{% include helpers/subhead-links.md %}

{% assign summary_importMulti="import addresses/scripts (with private or public keys, redeem script (P2SH)), rescanning all addresses in one-shot-only (rescan can be disabled via options)." %}

{% autocrossref %}

*Added in Bitcoin Core 0.14.0*

The `importmulti` RPC {{summary_importMulti}}

Requires a new wallet backup.

*Parameter #1---requests*

{% itemplate ntpd1 %}
- n: "requests"
  t: "array"
  p: "Required<br>(exactly 1)"
  d: "Data to be imported"

{% enditemplate %}

{% endautocrossref %}

    [     (array of json objects)
      {
        "scriptPubKey": "<script>" | { "address":"<address>" }, (string / json, required) Type of scriptPubKey (string for script, json for address)
        "timestamp": timestamp | "now"                        , (integer / string, required) Creation time of the key in seconds since epoch (Jan 1 1970 GMT),
                                                                or the string "now" to substitute the current synced blockchain time. The timestamp of the oldest
                                                                key will determine how far back blockchain rescans need to begin for missing wallet transactions.
                                                                "now" can be specified to bypass scanning, for keys which are known to never have been used, and
                                                                0 can be specified to scan the entire blockchain. Blocks up to 2 hours before the earliest key
                                                                creation time of all keys being imported by the importmulti call will be scanned.
        "redeemscript": "<script>"                            , (string, optional) Allowed only if the scriptPubKey is a P2SH address or a P2SH scriptPubKey
        "pubkeys": ["<pubKey>", ... ]                         , (array, optional) Array of strings giving pubkeys that must occur in the output or redeemscript
        "keys": ["<key>", ... ]                               , (array, optional) Array of strings giving private keys whose corresponding public keys must occur in the output or redeemscript
        "internal": <true>                                    , (boolean, optional, default: false) Stating whether matching outputs should be treated as not incoming payments
        "watchonly": <true>                                   , (boolean, optional, default: false) Stating whether matching outputs should be considered watched even when they're not spendable, only allowed if keys are empty
        "label": <label>                                      , (string, optional, default: '') Label to assign to the address (aka account name, for now), only allowed with internal=false
      }
    ,...
    ]

{% autocrossref %}

*Parameter #2---options*

{% itemplate ntpd1 %}
- n: "options"
  t: "json"
  p: "Optional"
  d: ""

{% enditemplate %}

{% endautocrossref %}

    {
       "rescan": <false>,         (boolean, optional, default: true) Stating if should rescan the blockchain after all imports
    }

{% autocrossref %}

*Result---`null` on success*

{% itemplate ntpd1 %}
- n: "`result`"
  t: "null"
  p: "Required<br>(exactly 1)"
  d: "JSON `null` when the command was successfull or a JSON with an error field on error."

{% enditemplate %}

*Example*

{% highlight bash %}
DeepOnion-cli importmulti '[{ "scriptPubKey": { "address": "<my address>" }, "timestamp":1455191478 }, { "scriptPubKey": { "address": "<my 2nd address>" }, "label": "example 2", "timestamp": 1455191480 }]'
{% endhighlight %}
{% highlight bash %}
DeepOnion-cli importmulti '[{ "scriptPubKey": { "address": "<my address>" }, "timestamp":1455191478 }]' '{ "rescan": false}'
{% endhighlight %}
Response is an array with the same size as the input that has the execution result :

  [{ "success": true } , { "success": false, "error": { "code": -1, "message": "Internal Server Error"} }, ... ]


*See also*

* [ImportPrivKey][rpc importprivkey]: {{summary_importPrivKey}}
* [ImportAddress][rpc importaddress]: {{summary_importAddress}}
* [ImportWallet][rpc importwallet]: {{summary_importWallet}}

{% endautocrossref %}
