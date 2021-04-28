{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/rpcs/getstakinginfo.md" %}

##### GetStakingInfo
{% include helpers/subhead-links.md %}

{% assign summary_getStakingInfo="returns an object containing staking-related information." %}

{% autocrossref %}

The `getstakinginfo` RPC {{summary_getStakingInfo}}

*Parameters: none*

*Result*

{% endautocrossref %}

    {
      "enabled": true,             (boolean) If staking is enabled
      "staking": true, 	          (boolean) If currently staking
      "errors": "...",           (string)  any network and blockchain warnings
      "currentblocksize": nnn      (numeric) The current block size
      "currentblocktx": nnn,       (numeric) The last block transaction
      "difficulty": xxx.xxxxx      (numeric) Staking difficulty
      "search-interval": nnn,      (numeric) Last interval between stake searches
      "weight": nnn                (numeric) Current wallet staking weight
      "netstakeweight": nnn        (numeric) Total network staking wieght
      "expectedtime": nnn          (numeric) Expected time until next wallet stake
    }

{% autocrossref %}

*Example*

{% highlight bash %}
DeepOnion-cli getstakinginfo
{% endhighlight %}

{% endautocrossref %}
