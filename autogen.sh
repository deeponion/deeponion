#!/bin/bash
# Copyright (c) 2013 - 2016 The Bitcoin Core developers
# Copyright (c) 2017 - 2023 The DeepOnion developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

export LC_ALL=C

srcdir=`pwd`

set -e
git submodule update --init --recursive

if [ -z ${LIBTOOLIZE} ] && GLIBTOOLIZE="`command -v glibtoolize 2>/dev/null`"; then
  LIBTOOLIZE="${GLIBTOOLIZE}"
  export LIBTOOLIZE
fi
command -v autoreconf >/dev/null || \
  (echo "configuration failed, please install autoconf first" && exit 1)
autoreconf --install --force --warnings=all

echo "Configure subtrees (secp256k1 and tor)"
cd "${srcdir}/src/secp256k1"
./autogen.sh
cd "${srcdir}/tor"
./autogen.sh
cd "${srcdir}"

