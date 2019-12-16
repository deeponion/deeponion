#!/usr/bin/env bash
#
# Copyright (c) 2019 The Bitcoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

export LC_ALL=C.UTF-8

export PACKAGES="python3-zmq qtbase5-dev qttools5-dev-tools libdbus-1-dev libharfbuzz-dev build-essential libtool autotools-dev automake pkg-config libssl-dev libevent-dev bsdmainutils python3 libboost-system-dev libboost-filesystem-dev libboost-chrono-dev libboost-program-options-dev libboost-test-dev libboost-thread-dev libminiupnpc-dev libqt5gui5 libqt5core5a libqt5dbus5 qttools5-dev qttools5-dev-tools libprotobuf-dev protobuf-compiler libzmq3-dev libseccomp-dev libcap-dev"
export DEP_OPTS="NO_QT=1 NO_UPNP=1 DEBUG=1 ALLOW_HOST_PACKAGES=1"
#export TEST_RUNNER_EXTRA="--coverage --extended --exclude feature_dbcrash"  # Run extended tests so that coverage does not fail, but exclude the very slow dbcrash
export RUN_UNIT_TESTS=false
export RUN_FUNCTIONAL_TESTS=false
#export NO_DEPENDS=1
export GOAL="install"
export BITCOIN_CONFIG="--enable-zmq --with-gui=qt5 --enable-glibc-back-compat --enable-reduce-exports --enable-debug CFLAGS=\"-g0 -O2 -funsigned-char\" CXXFLAGS=\"-g0 -O2 -funsigned-char\""
