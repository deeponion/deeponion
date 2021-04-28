{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/rpcs/createmultisig.md" %}

##### CreateMultiSig
{% include helpers/subhead-links.md %}

{% assign summary_createMultiSig="creates a multi-signature address with n signature of m keys required." %}

{% autocrossref %}

The `createmultisig` RPC {{summary_createMultiSig}}

It returns a json object with the address and redeemScript.

DEPRECATION WARNING: Using addresses with createmultisig is deprecated. Clients must
transition to using addmultisigaddress to create multisig addresses with addresses known
to the wallet before upgrading to v0.17. To use the deprecated functionality, start DeepOniond with -deprecatedrpc=createmultisig

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
  d: "A json array of hex-encoded public keys"

{% enditemplate %}

{% endautocrossref %}

    [
      "key"                    (string) The hex-encoded public key
      ,...
    ]

{% autocrossref %}

*Result*

{% endautocrossref %}

    {
      "address":"multisigaddress",  (string) The value of the new multisig address.
      "redeemScript":"script"       (string) The string value of the hex-encoded redemption script.
    }

{% autocrossref %}

*Example*

Create a multisig address from 2 public keys

{% highlight bash %}
DeepOnion-cli createmultisig 2 "[\"03789ed0bb717d88f7d321a368d905e7430207ebbd82bd342cf11ae157a7ace5fd\",\"03dbc6764b8884a92e871274b87583e6d5c2a58819473e17e107ef3f6aa5a61626\"]"
{% endhighlight %}

*See also*

* [AddMultiSigAddress][rpc addmultisigaddress]: {{summary_addMultiSigAddress}}
* [DecodeScript][rpc decodescript]: {{summary_decodeScript}}

{% endautocrossref %}
