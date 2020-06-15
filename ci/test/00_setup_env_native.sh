#!/usr/bin/env bash
# This just tests the native build with the current libdb for ease of use.
#
# Copyright (c) 2020 The DeepOnion developers
# Copyright (c) 2019 The Bitcoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

export LC_ALL=C.UTF-8

export PACKAGES="python3-zmq qtbase5-dev qttools5-dev-tools libdbus-1-dev libharfbuzz-dev build-essential libtool autotools-dev automake pkg-config libssl-dev libevent-dev bsdmainutils python3 libboost-all-dev libminiupnpc-dev libqt5gui5 libqt5core5a libqt5dbus5 qttools5-dev qttools5-dev-tools libprotobuf-dev protobuf-compiler libzmq3-dev libseccomp-dev libcap-dev libattr1-dev libdb5.3++-dev gettext"
export RUN_UNIT_TESTS=false
export NO_DEPENDS=1
export RUN_FUNCTIONAL_TESTS=false
export GOAL="install"
export BITCOIN_CONFIG="--enable-zmq --with-gui=qt5 --with-incompatible-bdb --enable-glibc-back-compat --enable-reduce-exports --enable-debug"
