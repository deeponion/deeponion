{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/rpcs/fundrawtransaction.md" %}

##### FundRawTransaction
{% include helpers/subhead-links.md %}

{% assign summary_fundRawTransaction="add inputs to a transaction until it has enough in value to meet its out value." %}

{% autocrossref %}

*Added in Bitcoin Core 0.12.0*

The `fundrawtransaction` RPC {{summary_fundRawTransaction}}

This will not modify existing inputs, and will add at most one change output to the outputs.

No existing outputs will be modified unless "subtractFeeFromOutputs" is specified.

Note that inputs which were signed may need to be resigned after completion since in/outputs have been added.

The inputs added will not be signed, use signrawtransaction for that.

Note that all existing inputs must have their previous output transaction be in the wallet.

Note that all inputs selected must be of standard form and P2SH scripts must be
in the wallet using importaddress or addmultisigaddress (to calculate fees).

You can see whether this is the case by checking the "solvable" field in the listunspent output.

Only pay-to-pubkey, multisig, and P2SH versions thereof are currently supported for watch-only

*Parameter #1---hexstring*

{% itemplate ntpd1 %}
- n: "hexstring"
  t: "string"
  p: "Required<br>(exactly 1)"
  d: "The hex string of the raw transaction"

{% enditemplate %}

*Parameter #2---options*

{% itemplate ntpd1 %}
- n: "options"
  t: "object"
  p: "Optional"
  d: "for backward compatibility: passing in a true instead of an object will result in {\"includeWatching\":true}"

{% enditemplate %}

{% endautocrossref %}

    {
      "changeAddress"          (string, optional, default pool address) The DeepOnion address to receive the change
      "changePosition"         (numeric, optional, default random) The index of the change output
      "change_type"            (string, optional) The output type to use. Only valid if changeAddress is not specified. Options are "legacy", "p2sh-segwit", and "bech32". Default is set by -changetype.
      "includeWatching"        (boolean, optional, default false) Also select inputs which are watch only
      "lockUnspents"           (boolean, optional, default false) Lock selected unspent outputs
      "feeRate"                (numeric, optional, default not set: makes wallet determine the fee) Set a specific fee rate in ONION/kB
      "subtractFeeFromOutputs" (array, optional) A json array of integers.
                               The fee will be equally deducted from the amount of each specified output.
                               The outputs are specified by their zero-based index, before any change output is added.
                               Those recipients will receive less DeepOnion than you enter in their corresponding amount field.
                               If no outputs are specified here, the sender pays the fee.
                                   [vout_index,...]
      "replaceable"            (boolean, optional) Marks this transaction as BIP125 replaceable.
                               Allows this transaction to be replaced by a transaction with higher fees
      "conf_target"            (numeric, optional) Confirmation target (in blocks)
      "estimate_mode"          (string, optional, default=UNSET) The fee estimate mode, must be one of:
          "UNSET"
          "ECONOMICAL"
          "CONSERVATIVE"
    }

{% autocrossref %}

*Parameter #3---iswitness*

{% itemplate ntpd1 %}
- n: "iswitness"
  t: "boolean"
  p: "Optional"
  d: "Whether the transaction hex is a serialized witness transaction 
       If iswitness is not present, heuristic tests will be used in decoding"

{% enditemplate %}

*Result*

{% endautocrossref %}

    {
      "hex":       "value", (string)  The resulting raw transaction (hex-encoded string)
      "fee":       n,         (numeric) Fee in ONION the resulting transaction pays
      "changepos": n          (numeric) The position of the added change output, or -1
    }

{% autocrossref %}

*Example*

Create a transaction with no inputs

{% highlight bash %}
DeepOnion-cli createrawtransaction "[]" "{\"myaddress\":0.01}"
{% endhighlight %}
Add sufficient unsigned inputs to meet the output value

{% highlight bash %}
DeepOnion-cli fundrawtransaction "rawtransactionhex"
{% endhighlight %}
Sign the transaction

{% highlight bash %}
DeepOnion-cli signrawtransaction "fundedtransactionhex"
{% endhighlight %}
Send the transaction

{% highlight bash %}
DeepOnion-cli sendrawtransaction "signedtransactionhex"
{% endhighlight %}

*See also*

* [CreateRawTransaction][rpc createrawtransaction]: {{summary_createRawTransaction}}
* [DecodeRawTransaction][rpc decoderawtransaction]: {{summary_decodeRawTransaction}}
* [SendRawTransaction][rpc sendrawtransaction]: {{summary_sendRawTransaction}}

{% endautocrossref %}
