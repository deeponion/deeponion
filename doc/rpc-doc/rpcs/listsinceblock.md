{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/rpcs/listsinceblock.md" %}

##### ListSinceBlock
{% include helpers/subhead-links.md %}

{% assign summary_listSinceBlock="get all transactions in blocks since block [blockhash], or all transactions if omitted." %}

{% autocrossref %}

The `listsinceblock` RPC {{summary_listSinceBlock}}

If "blockhash" is no longer a part of the main chain, transactions from the fork point onward are included.

Additionally, if include_removed is set, transactions affecting the wallet which were removed are returned in the "removed" array.

*Parameter #1---blockhash*

{% itemplate ntpd1 %}
- n: "blockhash"
  t: "string"
  p: "Optional"
  d: "The block hash to list transactions since"

{% enditemplate %}

*Parameter #2---target_confirmations:*

{% itemplate ntpd1 %}
- n: "target_confirmations:"
  t: "number (int)"
  p: "Optional<br>Default=1"
  d: "Return the nth block hash from the main chain. e.g. 1 would mean the best block hash. Note: this is not used as a filter, but only affects [lastblock] in the return value"

{% enditemplate %}

*Parameter #3---include_watchonly:*

{% itemplate ntpd1 %}
- n: "include_watchonly:"
  t: "bool"
  p: "Optional<br>Default=false"
  d: "Include transactions to watch-only addresses (see 'importaddress')"

{% enditemplate %}

*Parameter #4---include_removed:*

{% itemplate ntpd1 %}
- n: "include_removed:"
  t: "bool"
  p: "Optional<br>Default=true"
  d: "Show transactions that were removed due to a reorg in the \"removed\" array
       (not guaranteed to work on pruned nodes)"

{% enditemplate %}

*Result*

{% endautocrossref %}

    {
      "transactions": [
        "account":"accountname",       (string) DEPRECATED. The account name associated with the transaction. Will be "" for the default account.
        "address":"address",    (string) The DeepOnion address of the transaction. Not present for move transactions (category = move).
        "category":"send|receive",     (string) The transaction category. 'send' has negative amounts, 'receive' has positive amounts.
        "amount": x.xxx,          (numeric) The amount in ONION. This is negative for the 'send' category, and for the 'move' category for moves
                                              outbound. It is positive for the 'receive' category, and for the 'move' category for inbound funds.
        "vout" : n,               (numeric) the vout value
        "fee": x.xxx,             (numeric) The amount of the fee in ONION. This is negative and only available for the 'send' category of transactions.
        "confirmations": n,       (numeric) The number of confirmations for the transaction. Available for 'send' and 'receive' category of transactions.
                                              When it's < 0, it means the transaction conflicted that many blocks ago.
        "blockhash": "hashvalue",     (string) The block hash containing the transaction. Available for 'send' and 'receive' category of transactions.
        "blockindex": n,          (numeric) The index of the transaction in the block that includes it. Available for 'send' and 'receive' category of transactions.
        "blocktime": xxx,         (numeric) The block time in seconds since epoch (1 Jan 1970 GMT).
        "txid": "transactionid",  (string) The transaction id. Available for 'send' and 'receive' category of transactions.
        "time": xxx,              (numeric) The transaction time in seconds since epoch (Jan 1 1970 GMT).
        "timereceived": xxx,      (numeric) The time received in seconds since epoch (Jan 1 1970 GMT). Available for 'send' and 'receive' category of transactions.
        "bip125-replaceable": "yes|no|unknown",  (string) Whether this transaction could be replaced due to BIP125 (replace-by-fee);
                                                       may be unknown for unconfirmed transactions not in the mempool
        "abandoned": xxx,         (bool) 'true' if the transaction has been abandoned (inputs are respendable). Only available for the 'send' category of transactions.
        "comment": "...",       (string) If a comment is associated with the transaction.
        "label" : "label"       (string) A comment for the address/transaction, if any
        "to": "...",            (string) If a comment to is associated with the transaction.
      ],
      "removed": [
        <structure is the same as "transactions" above, only present if include_removed=true>
        Note: transactions that were readded in the active chain will appear as-is in this array, and may thus have a positive confirmation count.
      ],
      "lastblock": "lastblockhash"     (string) The hash of the block (target_confirmations-1) from the best block on the main chain. This is typically used to feed back into listsinceblock the next time you call it. So you would generally use a target_confirmations of say 6, so you will be continually re-notified of transactions until they've reached 6 confirmations plus any new ones
    }

{% autocrossref %}

*Example*

{% highlight bash %}
DeepOnion-cli listsinceblock
{% endhighlight %}
{% highlight bash %}
DeepOnion-cli listsinceblock "2c5a0ff9e4d8a7cdece6cc0f11d8f949a0c58b2028fab79b90485a811253e217" 6
{% endhighlight %}

*See also*

* [ListReceivedByAddress][rpc listreceivedbyaddress]: {{summary_listReceivedByAddress}}

{% endautocrossref %}
