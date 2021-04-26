// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2017 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <pow.h>

#include <arith_uint256.h>
#include <chain.h>
#include <primitives/block.h>
#include <uint256.h>
#include <util.h>

// DeepOnion: find last block index up to pindex
const CBlockIndex* GetLastBlockIndex(const CBlockIndex* pindex, bool fProofOfStake)
{
    while (pindex && pindex->pprev && (pindex->IsProofOfStake() != fProofOfStake))
        pindex = pindex->pprev;
    return pindex;
}


unsigned int GetNextWorkRequired(const CBlockIndex* pindexLast, const CBlockHeader *pblock, const Consensus::Params& params, bool fProofOfStake)
{
    if (params.fPowNoRetargeting)
        return pindexLast->nBits;
        
	unsigned int nTargetLimit = UintToArith256(params.powLimit).GetCompact();

	if (fProofOfStake)
	{
		nTargetLimit = UintToArith256(params.posLimit).GetCompact();
	}
	
    // genesis block
    if (pindexLast == NULL)
        return nTargetLimit;

    const CBlockIndex* pindexPrev = GetLastBlockIndex(pindexLast, fProofOfStake);   
    if (pindexPrev->pprev == NULL)
        return nTargetLimit;	// first block

    const CBlockIndex* pindexPrevPrev = GetLastBlockIndex(pindexPrev->pprev, fProofOfStake);
    if (pindexPrevPrev->pprev == NULL)
        return nTargetLimit;	// second block
    
    // min difficulty
    if (params.fPowAllowMinDifficultyBlocks)
    {
    	LogPrintf(">> Allow minimum diff\n");
    	
        // Special difficulty rule for testnet:
        // If the new block's timestamp is more than 2 * 4 minutes
        // then allow mining of a min-difficulty block.
        if (pblock->GetBlockTime() > pindexLast->GetBlockTime() + params.nPowTargetSpacing * 2)
            return nTargetLimit;
        else
        {
            // Return the last non-special-min-difficulty-rules-block
            const CBlockIndex* pindex = pindexLast;
            while (pindex->pprev && pindex->nBits == nTargetLimit)
                pindex = pindex->pprev;
            return pindex->nBits;
        }
    }    
    
    /*
    unsigned int nProofOfWorkLimit = UintToArith256(params.powLimit).GetCompact();

    // Only change once per difficulty adjustment interval
    if ((pindexLast->nHeight+1) % params.DifficultyAdjustmentInterval() != 0)
    {
    	LogPrintf(">> Diff no need to be adjusted\n");
        if (params.fPowAllowMinDifficultyBlocks)
        {
            // Special difficulty rule for testnet:
            // If the new block's timestamp is more than 2 * 4 minutes
            // then allow mining of a min-difficulty block.
            if (pblock->GetBlockTime() > pindexLast->GetBlockTime() + params.nPowTargetSpacing*2)
                return nProofOfWorkLimit;
            else
            {
                // Return the last non-special-min-difficulty-rules-block
                const CBlockIndex* pindex = pindexLast;
                while (pindex->pprev && pindex->nHeight % params.DifficultyAdjustmentInterval() != 0 && pindex->nBits == nProofOfWorkLimit)
                    pindex = pindex->pprev;
                return pindex->nBits;
            }
        }
        return pindexLast->nBits;
    }
	*/
    
    return CalculateNextWorkRequired(pindexPrev, pindexPrevPrev->GetBlockTime(), params, fProofOfStake);
}


unsigned int CalculateNextWorkRequired(const CBlockIndex* pindexLast, int64_t nFirstBlockTime, const Consensus::Params& params, bool fProofOfStake)
{
	const int64_t nInterval = 60;
	arith_uint256 bnTargetLimit = UintToArith256(params.powLimit);

	if (fProofOfStake)
	{
		bnTargetLimit = UintToArith256(params.posLimit);
	}

	// Limit adjustment step
	int64_t nTargetSpacing = params.nPowTargetSpacing;
	if(fProofOfStake)
		nTargetSpacing = params.nPosTargetSpacing;

    int64_t nActualSpacing = pindexLast->GetBlockTime() - nFirstBlockTime;
	if (nActualSpacing < nTargetSpacing / 4)
		nActualSpacing = nTargetSpacing / 4;
	if (nActualSpacing > nTargetSpacing * 4)
		nActualSpacing = nTargetSpacing * 4;

	arith_uint256 bnNew;
	bnNew.SetCompact(pindexLast->nBits);

	bnNew *= ((nInterval - 1) * nTargetSpacing + nActualSpacing + nActualSpacing);
	bnNew /= ((nInterval + 1) * nTargetSpacing);

	/*
	printf(">> Height = %d, fProofOfStake = %d, nInterval = %"PRI64d", nTargetSpacing = %"PRI64d", nActualSpacing = %"PRI64d"\n",
	pindexPrev->nHeight, fProofOfStake, nInterval, nTargetSpacing, nActualSpacing);
	printf(">> pindexPrev->GetBlockTime() = %"PRI64d", pindexPrev->nHeight = %d, pindexPrevPrev->GetBlockTime() = %"PRI64d", pindexPrevPrev->nHeight = %d\n",
	pindexPrev->GetBlockTime(), pindexPrev->nHeight, pindexPrevPrev->GetBlockTime(), pindexPrevPrev->nHeight);
	*/

	if (bnNew <= 0 || bnNew > bnTargetLimit)
		bnNew = bnTargetLimit;

	return bnNew.GetCompact();
}

bool CheckProofOfWork(uint256 hash, unsigned int nBits, const Consensus::Params& params, bool fProofOfStake)
{
	// this function check only pow
	if(fProofOfStake)
		return true;
	
    bool fNegative;
    bool fOverflow;
    arith_uint256 bnTarget;
    arith_uint256 bnTargetLimit = UintToArith256(params.powLimit);

    bnTarget.SetCompact(nBits, &fNegative, &fOverflow);

    if(fNegative)
    	LogPrintf(">> fNegative\n");
    if(fOverflow)
    	LogPrintf(">> fOverflow\n");
    if(bnTarget == 0)
    	LogPrintf(">> bnTarget == 0\n");
    if(bnTarget > bnTargetLimit)
    	LogPrintf(">> bnTarget > bnTargetLimit\n");
    
    // Check range
    if (fNegative || bnTarget == 0 || fOverflow || bnTarget > bnTargetLimit)
        return false;

    // Check proof of work matches claimed amount
    if (UintToArith256(hash) > bnTarget) {
    	LogPrintf(">> UintToArith256(hash) > bnTarget\n");
    	LogPrintf(">> hash = %s, bnTarget256 = %s\n", hash.ToString().c_str(), ArithToUint256(bnTarget).ToString().c_str());
        return false;
    }

    return true;
}
