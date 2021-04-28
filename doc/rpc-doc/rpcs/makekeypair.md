{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/rpcs/makekeypair.md" %}

##### MakeKeyPair
{% include helpers/subhead-links.md %}

{% assign summary_makeKeyPair="make a public/private key pair." %}

{% autocrossref %}

The `makekeypair` RPC {{summary_makeKeyPair}}

*Parameters: none*

*Result*

{% endautocrossref %}

    {
      "PrivateKey": "value", (string)  The resulting Private Key (hex-encoded string)
      "PublicKey": "value", (string)  The resulting Public Key (hex-encoded string)
    }

{% autocrossref %}

*Example*

{% highlight bash %}
DeepOnion-cli makekeypair
{% endhighlight %}

{% endautocrossref %}
