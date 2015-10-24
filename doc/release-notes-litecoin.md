Litecoin Core version 0.10.3.0 is now available from:

  <https://download.litecoin.org/litecoin-0.10.3.0/>

This is a new minor version release, bringing security fixes and translation 
updates. It is recommended to upgrade to this version as soon as possible.

Please report bugs using the issue tracker at github:

  <https://github.com/litecoin-project/litecoin/issues>

Upgrading and downgrading
=========================

How to Upgrade
--------------

If you are running an older version, shut it down. Wait until it has completely
shut down (which might take a few minutes for older versions), then run the
installer (on Windows) or just copy over /Applications/Litecoin-Qt (on Mac) or
litecoind/litecoin-qt (on Linux).

Downgrade warning
------------------

Because release 0.10+ and later makes use of headers-first synchronization and
parallel block download (see further), the block files and databases are not
backwards-compatible with pre-0.10 versions of Litecoin Core or other software:

* Blocks will be stored on disk out of order (in the order they are
received, really), which makes it incompatible with some tools or
other programs. Reindexing using earlier versions will also not work
anymore as a result of this.

* The block index database will now hold headers for which no block is
stored on disk, which earlier versions won't support.

If you want to be able to downgrade smoothly, make a backup of your entire data
directory. Without this your node will need start syncing (or importing from
bootstrap.dat) anew afterwards. It is possible that the data from a completely
synchronised 0.10 node may be usable in older versions as-is, but this is not
supported and may break as soon as the older version attempts to reindex.

This does not affect wallet forward or backward compatibility.

Notable changes
===============

Fix buffer overflow in bundled upnp
------------------------------------

Bundled miniupnpc was updated to 1.9.20151008. This fixes a buffer overflow in
the XML parser during initial network discovery.

Details can be found here: http://talosintel.com/reports/TALOS-2015-0035/

This applies to the distributed executables only, not when building from source or
using distribution provided packages.

Additionally, upnp has been disabled by default. This may result in a lower
number of reachable nodes on IPv4, however this prevents future libupnpc
vulnerabilities from being a structural risk to the network
(see https://github.com/bitcoin/bitcoin/pull/6795).

Test for LowS signatures before relaying
-----------------------------------------

Make the node require the canonical 'low-s' encoding for ECDSA signatures when
relaying or mining.  This removes a nuisance malleability vector.

Consensus behavior is unchanged.

If widely deployed this change would eliminate the last remaining known vector
for nuisance malleability on SIGHASH_ALL P2PKH transactions. On the down-side
it will block most transactions made by sufficiently out of date software.

Unlike the other avenues to change txids on transactions this
one was randomly violated by all deployed litecoin software prior to
its discovery. So, while other malleability vectors where made
non-standard as soon as they were discovered, this one has remained
permitted. Even BIP62 did not propose applying this rule to
old version transactions, but conforming implementations have become
much more common since BIP62 was initially written.

Litecoin Core has produced compatible signatures since the 0.9 development
branch, but this didn't make it into a release until 0.10. Both litecoinj
and Electrum have been more recently updated.

This does not replace the need for BIP62 or similar, as miners can
still cooperate to break transactions.  Nor does it replace the
need for wallet software to handle malleability sanely[1]. This
only eliminates the cheap and irritating DOS attack.

[1] On the Malleability of Bitcoin Transactions
Marcin Andrychowicz, Stefan Dziembowski, Daniel Malinowski, Łukasz Mazurek
http://fc15.ifca.ai/preproceedings/bitcoin/paper_9.pdf

0.10.3 Change log
=================

This release is based upon Bitcoin Core v0.10.3.  Their upstream changelog applies to us and
is included in as separate release-notes.  This section describes the Litecoin-specific differences.

- Adjusted default confirmation target value (nTxConfirmTarget) which is used for transaction fee 
	calculation, resulting in lower and more accurate fees. This mainly impacts users who use
	litecoind via litecoin-cli or the RPC service to send transactions as GUI (Qt) users
	already have the option to change their fee preferences. 
- Fixed OSX notification bug displaying incorrect icon.
- Fixed OSX Chinese language Unicode character display bug.
- Fixed make check testing suite.
- Updated Qt translations.
- Updated build instructions for OSX and Unix.

Credits
=======

Thanks to everyone who directly contributed to this release:

- Charles Lee
- pooler
- CohibAA
- kaykurokawa
- Adrian Gallagher
- Anton Yemelyanov
- Warren Togami

