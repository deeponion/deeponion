// Copyright (c) 2018 DeepOnion
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

/**
 * Functionality for starting Tor.
 */
#ifndef BITCOIN_TORSERVICE_H
#define BITCOIN_TORSERVICE_H

#include <scheduler.h>

void StartTor(boost::thread_group& threadGroup, CScheduler& scheduler);
void InterruptTor();
void StopTor();

#endif /* BITCOIN_TORSERVICE_H */
