{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/rpcs/getrawtransaction.md" %}

##### GetRawTransaction
{% include helpers/subhead-links.md %}

{% assign summary_getRawTransaction="nOTE: By default this function only works for mempool transactions." %}

{% autocrossref %}

The `getrawtransaction` RPC {{summary_getRawTransaction}}

If the -txindex option is
enabled, it also works for blockchain transactions. If the block which contains the transaction
is known, its hash can be provided even for nodes without -txindex. Note that if a blockhash is
provided, only that block will be searched and if the transaction is in the mempool or other
blocks, or if this node does not have the given block available, the transaction will not be found.

DEPRECATED: for now, it also works for transactions with unspent outputs.

Return the raw transaction data.

If verbose is 'true', returns an Object with information about 'txid'.

If verbose is 'false' or omitted, returns a string that is serialized, hex-encoded data for 'txid'.

*Parameter #1---txid*

{% itemplate ntpd1 %}
- n: "txid"
  t: "string"
  p: "Required<br>(exactly 1)"
  d: "The transaction id"

{% enditemplate %}

*Parameter #2---verbose*

{% itemplate ntpd1 %}
- n: "verbose"
  t: "bool"
  p: "Optional<br>Default=false"
  d: "If false, return a string, otherwise return a json object"

{% enditemplate %}

*Parameter #3---blockhash*

{% itemplate ntpd1 %}
- n: "blockhash"
  t: "string"
  p: "Optional"
  d: "The block in which to look for the transaction"

{% enditemplate %}

*Result---(if verbose is not set or set to false)*

{% itemplate ntpd1 %}
- n: "`result`"
  t: "string (hex)"
  p: "Required<br>(exactly 1)"
  d: "The serialized, hex-encoded data for 'txid'"

{% enditemplate %}

*Result---(if verbose is set to true)*

{% endautocrossref %}

    {
      "in_active_chain": b, (bool) Whether specified block is in the active chain or not (only present with explicit "blockhash" argument)
      "hex" : "data",       (string) The serialized, hex-encoded data for 'txid'
      "txid" : "id",        (string) The transaction id (same as provided)
      "hash" : "id",        (string) The transaction hash (differs from txid for witness transactions)
      "size" : n,             (numeric) The serialized transaction size
      "vsize" : n,            (numeric) The virtual transaction size (differs from size for witness transactions)
      "version" : n,          (numeric) The version
      "locktime" : ttt,       (numeric) The lock time
      "vin" : [               (array of json objects)
         {
           "txid": "id",    (string) The transaction id
           "vout": n,         (numeric)
           "scriptSig": {     (json object) The script
             "asm": "asm",  (string) asm
             "hex": "hex"   (string) hex
           },
           "sequence": n      (numeric) The script sequence number
           "txinwitness": ["hex", ...] (array of string) hex-encoded witness data (if any)
         }
         ,...
      ],
      "vout" : [              (array of json objects)
         {
           "value" : x.xxx,            (numeric) The value in ONION
           "n" : n,                    (numeric) index
           "scriptPubKey" : {          (json object)
             "asm" : "asm",          (string) the asm
             "hex" : "hex",          (string) the hex
             "reqSigs" : n,            (numeric) The required sigs
             "type" : "pubkeyhash",  (string) The type, eg 'pubkeyhash'
             "addresses" : [           (json array of string)
               "address"        (string) DeepOnion address
               ,...
             ]
           }
         }
         ,...
      ],
      "blockhash" : "hash",   (string) the block hash
      "confirmations" : n,      (numeric) The confirmations
      "time" : ttt,             (numeric) The transaction time in seconds since epoch (Jan 1 1970 GMT)
      "blocktime" : ttt         (numeric) The block time in seconds since epoch (Jan 1 1970 GMT)
    }

{% autocrossref %}

*Example*

{% highlight bash %}
DeepOnion-cli getrawtransaction "mytxid"
{% endhighlight %}
{% highlight bash %}
DeepOnion-cli getrawtransaction "mytxid" true
{% endhighlight %}
{% highlight bash %}
DeepOnion-cli getrawtransaction "mytxid" false "myblockhash"
{% endhighlight %}
{% highlight bash %}
DeepOnion-cli getrawtransaction "mytxid" true "myblockhash"
{% endhighlight %}

*See also*

* [GetTransaction][rpc gettransaction]: {{summary_getTransaction}}

{% endautocrossref %}
