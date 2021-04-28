{% comment %}
This file is licensed under the MIT License (MIT) available on
http://opensource.org/licenses/MIT.
{% endcomment %}
{% assign filename="_data/devdocs/en/bitcoin-core/rpcs/rpcs/listtransactions.md" %}

##### ListTransactions
{% include helpers/subhead-links.md %}

{% assign summary_listTransactions="returns up to 'count' most recent transactions skipping the first 'from' transactions for account 'account'." %}

{% autocrossref %}

The `listtransactions` RPC {{summary_listTransactions}}

*Parameter #1---account*

{% itemplate ntpd1 %}
- n: "account"
  t: "string"
  p: "Optional"
  d: "DEPRECATED. The account name. Should be \"*\"."

{% enditemplate %}

*Parameter #2---count*

{% itemplate ntpd1 %}
- n: "count"
  t: "number (int)"
  p: "Optional<br>Default=10"
  d: "The number of transactions to return"

{% enditemplate %}

*Parameter #3---skip*

{% itemplate ntpd1 %}
- n: "skip"
  t: "number (int)"
  p: "Optional<br>Default=0"
  d: "The number of transactions to skip"

{% enditemplate %}

*Parameter #4---include_watchonly*

{% itemplate ntpd1 %}
- n: "include_watchonly"
  t: "bool"
  p: "Optional<br>Default=false"
  d: "Include transactions to watch-only addresses (see 'importaddress')"

{% enditemplate %}

*Result*

{% endautocrossref %}

    [
      {
        "account":"accountname",       (string) DEPRECATED. The account name associated with the transaction.
                                                    It will be "" for the default account.
        "address":"address",    (string) The DeepOnion address of the transaction. Not present for
                                                    move transactions (category = move).
        "category":"send|receive|move", (string) The transaction category. 'move' is a local (off blockchain)
                                                    transaction between accounts, and not associated with an address,
                                                    transaction id or block. 'send' and 'receive' transactions are
                                                    associated with an address, transaction id and block details
        "amount": x.xxx,          (numeric) The amount in ONION. This is negative for the 'send' category, and for the
                                             'move' category for moves outbound. It is positive for the 'receive' category,
                                             and for the 'move' category for inbound funds.
        "label": "label",       (string) A comment for the address/transaction, if any
        "vout": n,                (numeric) the vout value
        "fee": x.xxx,             (numeric) The amount of the fee in ONION. This is negative and only available for the
                                             'send' category of transactions.
        "confirmations": n,       (numeric) The number of confirmations for the transaction. Available for 'send' and
                                             'receive' category of transactions. Negative confirmations indicate the
                                             transaction conflicts with the block chain
        "trusted": xxx,           (bool) Whether we consider the outputs of this unconfirmed transaction safe to spend.
        "blockhash": "hashvalue", (string) The block hash containing the transaction. Available for 'send' and 'receive'
                                              category of transactions.
        "blockindex": n,          (numeric) The index of the transaction in the block that includes it. Available for 'send' and 'receive'
                                              category of transactions.
        "blocktime": xxx,         (numeric) The block time in seconds since epoch (1 Jan 1970 GMT).
        "txid": "transactionid", (string) The transaction id. Available for 'send' and 'receive' category of transactions.
        "time": xxx,              (numeric) The transaction time in seconds since epoch (midnight Jan 1 1970 GMT).
        "timereceived": xxx,      (numeric) The time received in seconds since epoch (midnight Jan 1 1970 GMT). Available
                                              for 'send' and 'receive' category of transactions.
        "comment": "...",       (string) If a comment is associated with the transaction.
        "otheraccount": "accountname",  (string) DEPRECATED. For the 'move' category of transactions, the account the funds came
                                              from (for receiving funds, positive amounts), or went to (for sending funds,
                                              negative amounts).
        "bip125-replaceable": "yes|no|unknown",  (string) Whether this transaction could be replaced due to BIP125 (replace-by-fee);
                                                         may be unknown for unconfirmed transactions not in the mempool
        "abandoned": xxx          (bool) 'true' if the transaction has been abandoned (inputs are respendable). Only available for the
                                             'send' category of transactions.
      }
    ]

{% autocrossref %}

*Example*

List the most recent 10 transactions in the systems

{% highlight bash %}
DeepOnion-cli listtransactions
{% endhighlight %}
List transactions 100 to 120

{% highlight bash %}
DeepOnion-cli listtransactions "*" 20 100
{% endhighlight %}

*See also*

* [GetTransaction][rpc gettransaction]: {{summary_getTransaction}}
* [ListSinceBlock][rpc listsinceblock]: {{summary_listSinceBlock}}

{% endautocrossref %}
