// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2017 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <primitives/block.h>

#include <chainparams.h>
#include <hash.h>
#include <tinyformat.h>
#include <utilstrencodings.h>
#include <crypto/common.h>

uint256 CBlockHeader::GetHash() const
{
    return HashX13(BEGIN(nVersion), END(nNonce));
}

uint256 CBlockHeader::GetPoWHash() const
{
    return HashX13(BEGIN(nVersion), END(nNonce));
}

bool CBlockHeader::IsProofOfStake() const
{
	// unfortunately with blockheader only it is difficult to determine if a block is pow or pos
	// to determine if a block is pos we need to check its vin/vout
	// thus the formal method will be in the block class
	// here we just temporarily use a hack:
	// pow blocks always has its hash starting with at least 5 "0"s.
	// this is temporary, we should not check the headers, but should move all check functions
	// to checkblock, like the old deeponion code does
	std::string hashStr = GetHash().ToString();
	if(hashStr.find("00000") == 0 || Params().NetworkIDString() == "regtest") {
		return false;
	}
	
	return true;
}

std::string CBlock::ToString() const
{
    std::stringstream s;
    s << strprintf("CBlock(hash=%s, ver=%d, hashPrevBlock=%s, hashMerkleRoot=%s, nTime=%u, nBits=%08x, nNonce=%u, vtx=%u, vchBlockSig=%s)\n",
        GetHash().ToString(),
        nVersion,
        hashPrevBlock.ToString(),
        hashMerkleRoot.ToString(),
        nTime, nBits, nNonce,
        vtx.size(),
		HexStr(vchBlockSig.begin(), vchBlockSig.end()).c_str());
    for (const auto& tx : vtx) {
        s << "  " << tx->ToString() << "\n";
    }
    return s.str();
}
