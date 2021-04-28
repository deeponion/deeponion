.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

getwalletinfo
=============

``getwalletinfo``

Returns an object containing various wallet state info.

Result
~~~~~~

::

  {
    "walletname": xxxxx,             (string) the wallet name
    "walletversion": xxxxx,          (numeric) the wallet version
    "balance": xxxxxxx,              (numeric) the total confirmed balance of the wallet in ONION
    "stake": xxxxxxx,                (numeric) the total stake balance of the wallet in ONION
    "unconfirmed_balance": xxx,      (numeric) the total unconfirmed balance of the wallet in ONION
    "immature_balance": xxxxxx,      (numeric) the total immature balance of the wallet in ONION
    "txcount": xxxxxxx,              (numeric) the total number of transactions in the wallet
    "keypoololdest": xxxxxx,         (numeric) the timestamp (seconds since Unix epoch) of the oldest pre-generated key in the key pool
    "keypoolsize": xxxx,             (numeric) how many new keys are pre-generated (only counts external keys)
    "keypoolsize_hd_internal": xxxx, (numeric) how many new keys are pre-generated for internal use (used for change outputs, only appears if the wallet is using this feature, otherwise external keys are used)
    "unlocked_until": ttt,           (numeric) the timestamp in seconds since epoch (midnight Jan 1 1970 GMT) that the wallet is unlocked for transfers, or 0 if the wallet is locked
    "paytxfee": x.xxxx,              (numeric) the transaction fee configuration, set in ONION/kB
    "hdmasterkeyid": "<hash160>"     (string, optional) the Hash160 of the HD master pubkey (only present when HD is enabled)
  }

Examples
~~~~~~~~


.. highlight:: shell

::

  DeepOnion-cli getwalletinfo

::

  curl --user myusername --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "getwalletinfo", "params": [] }' -H 'content-type: text/plain;' http://127.0.0.1:9332/

