// Copyright (c) 2012-2013 The DeepOnion developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef DeepOnion_POS_H
#define DeepOnion_POS_H

#include "chain.h"
#include "primitives/transaction.h"
#include "consensus/validation.h"
#include "txdb.h"
#include "validation.h"
#include "arith_uint256.h"
#include "hash.h"
#include "timedata.h"
#include "chainparams.h"
#include "script/sign.h"
#include "consensus/consensus.h"


// MODIFIER_INTERVAL_RATIO:
// ratio of group interval length between the last group and the first group
static const int MODIFIER_INTERVAL_RATIO = 3;

// Compute the hash modifier for proof-of-stake
bool ComputeNextStakeModifier(const CBlockIndex* pindexPrev, uint64_t& nStakeModifier, bool& fGeneratedStakeModifier, const Consensus::Params& consensusParams);

// Check whether stake kernel meets hash target
// Sets hashProofOfStake on success return
bool CheckStakeKernelHash(unsigned int nBits, CBlockIndex* pBlockFrom, CValidationState& state, CTransactionRef txPrevRef, unsigned int nTxPrevOffset,  
		const COutPoint& prevout, unsigned int nTimeTx, uint256& hashProofOfStake, uint256& targetProofOfStake, bool fDebugLog);

// Check kernel hash target and coinstake signature
// Sets hashProofOfStake on success return
bool CheckProofOfStake(CBlockTreeDB& blockTreeDB, CBlockIndex* pindexPrev, CValidationState& state, const CBlock& block, uint256& hashProofOfStake, 
		uint256& targetProofOfStake, BlockMap& mapBlockIndex, CCoinsViewCache& view);

// Check whether the coinstake timestamp meets protocol
bool CheckCoinStakeTimestamp(int64_t nTimeBlock, int64_t nTimeTx);

// Get stake modifier checksum
unsigned int GetStakeModifierChecksum(const CBlockIndex* pindex);

// Check stake modifier hard checkpoints
bool CheckStakeModifierCheckpoints(int nHeight, unsigned int nStakeModifierChecksum);

// Get time weight using supplied timestamps
int64_t GetWeight(int64_t nIntervalBeginning, int64_t nIntervalEnd);

#endif // DeepOnion_POS_H
