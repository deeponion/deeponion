Repository Tools
---------------------

### [Developer tools](/contrib/devtools) ###
Specific tools for developers working on this repository.
Contains the script `github-merge.py` for merging GitHub pull requests securely and signing them using GPG.

### [Verify-Commits](/contrib/verify-commits) ###
Tool to verify that every merge commit was signed by a developer using the above `github-merge.py` script.

### [Linearize](/contrib/linearize) ###
Construct a linear, no-fork, best version of the blockchain.

### [Qos](/contrib/qos) ###

A Linux bash script that will set up traffic control (tc) to limit the outgoing bandwidth for connections to the Litecoin network. This means one can have an always-on litecoind instance running, and another local litecoind/litecoin-qt instance which connects to this node and receives blocks from it.

### [Seeds](/contrib/seeds) ###
Utility to generate the pnSeed[] array that is compiled into the client.

Build Tools and Keys
---------------------

### [Debian](/contrib/debian) ###
Contains files used to package litecoind/litecoin-qt
for Debian-based Linux systems. If you compile litecoind/litecoin-qt yourself, there are some useful files here.

### [Gitian-descriptors](/contrib/gitian-descriptors) ###
Files used during the gitian build process. For more information about gitian, see the [the Bitcoin Core documentation repository](https://github.com/bitcoin-core/docs).

### [Gitian-keys](/contrib/gitian-keys)
PGP keys used for signing Litecoin Core [Gitian release](/doc/release-process.md) results.

### [MacDeploy](/contrib/macdeploy) ###
Scripts and notes for Mac builds. 

### [RPM](/contrib/rpm) ###
RPM spec file for building blitecoin-core on RPM based distributions.

### [Gitian-build](/contrib/gitian-build.sh) ###
Script for running full Gitian builds.

Test and Verify Tools 
---------------------

### [TestGen](/contrib/testgen) ###
Utilities to generate test vectors for the data-driven Litecoin tests.

### [Verify Binaries](/contrib/verifybinaries) ###
This script attempts to download and verify the signature file SHA256SUMS.asc from litecoin.org.

Node Update Scripts
---------------------

*Work in progress...*

### [README](/contrib/scripts/README.txt)
These scripts will download and/or create DeepOnion.conf for DeepOnion Wallet. 

### [Linux](/contrib/scripts/)

#### [Update Nodes](/contrib/scripts/linux.sh)
Update official DeepOnion nodes
#### [China Nodes](/contrib/scripts/linuxc.sh)
Update for China users or other Tor blocked countries
#### [Nova Nodes](/contrib/scripts/linuxn.sh)
Update to NovaExchange node list

### [Windows](/contrib/scripts/)
*Coming soon...*
### [Mac](/contrib/scripts/)
*Coming soon...*
