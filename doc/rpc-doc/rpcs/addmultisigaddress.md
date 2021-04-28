{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/rpcs/addmultisigaddress.md" %}

##### AddMultiSigAddress
{% include helpers/subhead-links.md %}

{% assign summary_addMultiSigAddress="adds a P2SH multisig address to the wallet." %}

{% autocrossref %}

*Requires wallet support.*

The `addmultisigaddress` RPC {{summary_addMultiSigAddress}}

Add a nrequired-to-sign multisignature address to the wallet. Requires a new wallet backup.

Each key is a DeepOnion address or hex-encoded public key.

This functionality is only intended for use with non-watchonly addresses.

See `importaddress` for watchonly p2sh address support.

If 'account' is specified (DEPRECATED), assign address to that account.

*Parameter #1---nrequired*

{% itemplate ntpd1 %}
- n: "nrequired"
  t: "number (int)"
  p: "Required<br>(exactly 1)"
  d: "The number of required signatures out of the n keys or addresses."

{% enditemplate %}

*Parameter #2---keys*

{% itemplate ntpd1 %}
- n: "keys"
  t: "string"
  p: "Required<br>(exactly 1)"
  d: "A json array of DeepOnion addresses or hex-encoded public keys"

{% enditemplate %}

{% endautocrossref %}

    [
      "address"                  (string) DeepOnion address or hex-encoded public key
      ...,
    ]

{% autocrossref %}

*Parameter #3---account*

{% itemplate ntpd1 %}
- n: "account"
  t: "string"
  p: "Optional"
  d: "DEPRECATED. An account to assign the addresses to."

{% enditemplate %}

*Parameter #4---address_type*

{% itemplate ntpd1 %}
- n: "address_type"
  t: "string"
  p: "Optional"
  d: "The address type to use. Options are \"legacy\", \"p2sh-segwit\", and \"bech32\". Default is set by -addresstype."

{% enditemplate %}

*Result*

{% endautocrossref %}

    {
      "address":"multisigaddress",    (string) The value of the new multisig address.
      "redeemScript":"script"         (string) The string value of the hex-encoded redemption script.
    }

{% autocrossref %}

*Result---(DEPRECATED. To see this result in v0.16 instead, please start DeepOniond with -deprecatedrpc=addmultisigaddress).*

{% itemplate ntpd1 %}
- n: "`result`"
  t: "string (hex)"
  p: "Required<br>(exactly 1)"
  d: "A DeepOnion address associated with the keys."

{% enditemplate %}

*Example*

Add a multisig address from 2 addresses

{% highlight bash %}
DeepOnion-cli addmultisigaddress 2 "[\"LEr4hnAefwYhBmGxcFP2Po1NPrUEIk8KM2\",\"Dc7BLTLqSyWSp6uEpQPbbcb7figA7xHjKQ\"]"
{% endhighlight %}

*See also*

* [CreateMultiSig][rpc createmultisig]: {{summary_createMultiSig}}
* [DecodeScript][rpc decodescript]: {{summary_decodeScript}}
* [Pay-To-Script-Hash (P2SH)][/en/glossary/p2sh-address]

{% endautocrossref %}
