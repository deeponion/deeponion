// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2017 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainparams.h>
#include <consensus/merkle.h>

#include <tinyformat.h>
#include <util.h>
#include <utilstrencodings.h>

#include <assert.h>

#include <chainparamsseeds.h>

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.nTime = nTime;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 0 << CScriptNum(42) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    // txNew.vout[0].scriptPubKey = genesisOutputScript;
    txNew.vout[0].scriptPubKey.clear();

    LogPrintf(">> txNew = %s\n", txNew.GetHash().ToString().substr(0, 10)); 

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=000004e29458ef4f2e0abab544737b07344e6ff13718f7c2d12926166db07b5e, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, 
 *  hashMerkleRoot=48a457c277b124a06b568c0036d2c834e918d952c5b2dbf4035d173f50c8d14c, nTime=1499843027, nBits=1e0fffff, nNonce=3832541, vtx=1, vchBlockSig=)
 *  Coinbase(hash=48a457c277, nTime=1499843027, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *  CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a32446565704f6e696f6e3a20746865206d6f73742073656375726520636f696e20696e20746865206379626572737061636521)
 *  CTxOut(empty)
 * vMerkleTree: 48a457c277 
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "DeepOnion: the most secure coin in the cyberspace!";
    const CScript genesisOutputScript = CScript() << ParseHex("040ca85222159767e5ef1e9640418ddaf37990c3c62e13f5d52cc9620ef1597d7571cf35f670c176f1f28fabcf371d0eadfee616c0ee5385600eaeba3482f3bac2") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

void CChainParams::UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    consensus.vDeployments[d].nStartTime = nStartTime;
    consensus.vDeployments[d].nTimeout = nTimeout;
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 131400;
        consensus.BIP16Height = 0; 
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256S("000004e29458ef4f2e0abab544737b07344e6ff13718f7c2d12926166db07b5e");
        consensus.BIP65Height = 1000000; 
        consensus.BIP66Height = 1000000; 
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); 
        consensus.posLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); 
        consensus.nPowTargetTimespan = 14400; 
        consensus.nPowTargetSpacing = 240;
        consensus.nPosTargetSpacing = 60;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.nStakeMinAge = 60 * 60 * 24 * 1;			// minimum age for coin age: 1d
        consensus.nStakeMaxAge = 60 * 60 * 24 * 30;	        // stake age of full weight: 30d
        consensus.nModifierInterval = 8 * 60;				// time to elapse before new modifier is computed
        consensus.nCoinbaseMaturity = 40;					// 40 Blocks maturity
        // disable NoRetargeting. NoRetargeting is always false
        // consensus.fPowNoRetargeting = false;
        // consensus.fPosNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 180; // 75% of 240
        consensus.nMinerConfirmationWindow = 240; // nPowTargetTimespan / nPowTargetSpacing * 4
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1499817600; // July 12, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1514764799; // December 31, 2017

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1548633600; // January 28, 2019
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1548979199; // January 31st, 2019

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1609462800; // January 1, 2021
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1612054800; // January 31st, 2021

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x000000000000000000000000000000000000000000000000000a3935d31876de"); // Checkpoint 750001

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x0000000000000f9dd816f0b37d5b4bf68da7b3308e4f4feb0890b957bcb807a5"); // 621306

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xd1;
        pchMessageStart[1] = 0xf1;
        pchMessageStart[2] = 0xdb;
        pchMessageStart[3] = 0xf2;
        nDefaultPort = 17570;
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(1499843027, 3832541, 0x1e0fffff, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();

        LogPrintf(">> block = %s\n", genesis.ToString()); 
        LogPrintf(">> block.GetHash() == %s\n", genesis.GetHash().ToString().c_str());
        LogPrintf(">> block.hashMerkleRoot == %s\n", genesis.hashMerkleRoot.ToString().c_str());
        LogPrintf(">> block.nTime = %u \n", genesis.nTime);
        LogPrintf(">> block.nNonce = %u \n", genesis.nNonce);

        assert(consensus.hashGenesisBlock == uint256S("0x000004e29458ef4f2e0abab544737b07344e6ff13718f7c2d12926166db07b5e"));
        assert(genesis.hashMerkleRoot == uint256S("0x48a457c277b124a06b568c0036d2c834e918d952c5b2dbf4035d173f50c8d14c"));

        // Note that of those with the service bits flag, most only support a subset of possible options
//        vSeeds.emplace_back("seed-a.DeepOnion.loshan.co.uk");
//        vSeeds.emplace_back("dnsseed.thrasher.io");
//        vSeeds.emplace_back("dnsseed.DeepOniontools.com");
//        vSeeds.emplace_back("dnsseed.DeepOnionpool.org");
//        vSeeds.emplace_back("dnsseed.koin-project.com");

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,31);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,78);
        base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1,78);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,159);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x88, 0xB2, 0x1E};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x88, 0xAD, 0xE4};

        bech32_hrp = "dpn";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;

        checkpointData = {
            {
			    {   1000, uint256S("0x0000000000850dc77a9601bc78cc6404bf24923475194c392accdb176c8e74da")},
				{  10000, uint256S("0xc304f427bac3bef29e3faf8fe17d483a1e61d3a1749f9a0ac7ece4c1e544bbaa")},
			    {  50008, uint256S("0x00000000000a70b080e12cab200125ecffeebfae7c7fe7c914311a2b1056cf5b")},
			    { 100000, uint256S("0x00000000000338c044ce7a397242372cbc5d71ad7bad08c88089d0011de30f83")},
			    { 150006, uint256S("0x000000000000b5655b0eb5215167d4e18df3c5a43f67494f0385f87be6956114")},
			    { 200830, uint256S("0x000000000000dc867b2fad981c9e4ead671ebe1e0069ba7c9f43ba5a8ef67a07")},
			    { 250008, uint256S("0x00000000000069afef0ee5775301da6815092c4bd1a45928e33da5a894e55e00")},
			    { 300836, uint256S("0x00000000000047d897f3eac5fcacc831f0f77dfbf70222467ee2360dcbc4b266")},
			    { 350003, uint256S("0x0000000000001e6123edc0c5c8ca04ccee16aeb23455d02f12ba8d636516ee52")},
			    { 400002, uint256S("0x0000000000002945e035c7fabd433932269af99f5c033a6c9cea229b67751ba1")},
			    { 450000, uint256S("0x0000000000009bee8de0c52e5f4ea17a69e044b39718b62824eb67768ad18f4e")},
			    { 500001, uint256S("0x00000000000021a4ea50e863c7f9c3ab7a9ef1b452e498a0c5369a03fe224aec")},
			    { 550004, uint256S("0x0000000000008784d0e68a519407498b08d0b56b23726e4bfcc0843017d7d011")},
			    { 600014, uint256S("0x000000000000150feaa5a9669a7b58589333c8195770b675f873fc236cb9f6ce")},
			    { 650002, uint256S("0x000000000000007bc8502ddd5a6f0ce8fbf499a9c189ba4f6a42c6e3a7698b0f")},
			    { 700006, uint256S("0x00000000000052dd063e278fc0d3c95ebcfaa646215c350b7b8f505d6dc7e331")},
			    { 750001, uint256S("0x000000000000792fb98a1a8461e50a910543d90b712b2303e49779ee94238b27")},
			    { 800002, uint256S("0x000000000000b799930f12a319238e283590d7480ac5ca711679548c33e8ebf1")},
			    { 850000, uint256S("0x0000000000019d6b3b3a832567200db8b548f445ba78da7cc6c2fbe8e305c693")},
			    { 900012, uint256S("0x00000000000027b3afa207c5cb8c3e4232129273fa020b9a463d567a01f726cd")},
			    { 950005, uint256S("0x00000000000514c239cbb998a2d7b2a503b57d86b4739f8285fa05ef13fcabf2")},
			    {1000006, uint256S("0x000000000005283dc62422cca1f4d09eaf220e41d9812ac7f659f4b7cb2c65c2")},
			    {1050000, uint256S("0x000000000001ccf45545c4d685142d4ac5ca2f485b2f8d8c5e023de1d2f13228")},
			    {1100013, uint256S("0x0000000000008d7041a212b8ca38e71732b3dcbed3075ed01959a82886a89d02")},
			    {1150015, uint256S("0x00000000000179d7851ad529e89ac18bfd1d241a57c9e3dbc15263ee9058253c")},
			    {1200000, uint256S("0x0000000000044a81ecdf2d5d7b6a314ddc23d6aade3e3c91724c5b16ae70a081")},
			    {1250000, uint256S("0x000000000001ef93e11ef086b7df375f8312c2b504d63655f96c9240b142d43c")},
			    {1300021, uint256S("0x000000000000e4f01a75810a68958b831435d8d8778badda7cc108b0f1837180")},
                {1350006, uint256S("0x00000000000283363cc3b6932640850e39c09b5e8989a1bc55cc5e074d737a61")},
                {1390072, uint256S("0x000000000004cd4562361ac51ccd1887cf615ec4f142be6a551b92e2bd9c16ea")},
                {1400000, uint256S("0x00000000000aa03f5bff2cc0dd3cdc7e7260d5b42eff14acc4cc2f3e4a7392ec")},
                {1450003, uint256S("0x0000000000084abd24b4d1d6cd34d6ff2c49c272c66308b6d050c647179ae2ef")},
                {1500002, uint256S("0x000000000000bdc6e678231b0da05220e03e27e516a87aa0a5709ff6549337c6")},
                {1550011, uint256S("0x0000000000077e24a498bb73b1330c18ce055de8cd50dd6682ce5eb9d4256075")},
                {1600014, uint256S("0x000000000003bb02b4e7d9be35a9901aadd2bd77f1b0ea3000d7cf449089229c")},
            }
        };

        chainTxData = ChainTxData{
            // Data as of block 7faaa11ff882f21d79fb2de39c6847a9c4abbff8c5d0d2bbec17012f3b35c05a (height 624700).
        	1530513460, // * UNIX timestamp of last known number of transactions
			1401767,  // * total number of transactions between genesis and that timestamp
                    //   (the tx=... number in the SetBestChain debug.log lines)
            0.046    // * estimated number of transactions per second after that timestamp
        };

        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(      0, 0xfd11f4e7u));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(   1000, 0x353653feu));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(  10000, 0x8c341084u));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(  50008, 0x9f0053f2u));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>( 100000, 0xaf212909u));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>( 150006, 0x3883af95u));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>( 200830, 0xf2daec0au));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>( 250008, 0x76bd1777u));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>( 300836, 0x18dbac5eu));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>( 350003, 0x17223fa8u));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>( 400002, 0xd1662b8fu));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>( 450000, 0x0fc0c8d3u));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>( 500001, 0x17ac1811u));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>( 550004, 0xcfb3340fu));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>( 600014, 0x74d7cf8cu));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>( 650002, 0xda8bce79u));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>( 700006, 0x42463050u));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>( 750001, 0x4d3e1fe6u));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>( 800002, 0x0c90205du));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>( 850000, 0x40f52778u));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>( 900012, 0xa3e7b278u));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>( 950005, 0xf364b26cu));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(1000006, 0x75801cf9u));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(1050000, 0x2f3cfae9u));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(1100013, 0xb92618a7u));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(1150015, 0x546f1436u));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(1200000, 0x4328bd8fu));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(1250000, 0xa3689d70u));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(1300021, 0x6fa62d97u));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(1350006, 0x469c6019u));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(1400000, 0xc9bbc27eu));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(1450003, 0x5481cba5u));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(1500002, 0xaa17ea68u));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(1550011, 0x42dc3688u));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(1600014, 0x7721a327u));
    }
};



/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 131400;
        consensus.BIP16Height = 0; // always enforce P2SH BIP16 on regtest
        consensus.BIP34Height = 100;
        consensus.BIP34Hash = uint256S("8075c771ed8b495ffd943980a95f702ab34fce3c8c54e379548bda33cc8c0573");
        consensus.BIP65Height = 100; // 8075c771ed8b495ffd943980a95f702ab34fce3c8c54e379548bda33cc8c0573
        consensus.BIP66Height = 100; // 8075c771ed8b495ffd943980a95f702ab34fce3c8c54e379548bda33cc8c0573
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.posLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 14400; 
        consensus.nPowTargetSpacing = 240;
        consensus.nPosTargetSpacing = 60;
        consensus.fPowAllowMinDifficultyBlocks = false;
        // consensus.fPowNoRetargeting = false;
        // consensus.fPosNoRetargeting = false;
        consensus.nStakeMinAge = 20 * 60;					// minimum age for coin age: 20 Minutes
        consensus.nStakeMaxAge = 60 * 60 * 24 * 30;	        // stake age of full weight: 30d
        consensus.nModifierInterval = 60;					// time to elapse before new modifier is computed
        consensus.nCoinbaseMaturity = 10;					// Blocks maturity
        consensus.nRuleChangeActivationThreshold = 45; // 75% for testchains
        consensus.nMinerConfirmationWindow = 60; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1483228800; // January 1, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1517356801; // January 31st, 2018

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1577836800; // January 1, 2020
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 0; //1580428800; // January 31st, 2020

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0xa0afbded94d4be233e191525dc2d467af5c7eab3143c852c3cd549831022aad6"); //343833

		pchMessageStart[0] = 0xa2;
		pchMessageStart[1] = 0xa1;
		pchMessageStart[2] = 0xa0;
		pchMessageStart[3] = 0xf2;
        nDefaultPort = 26550;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1546281565, 1249377, 0x1e0fffff, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x0000045eea7d9a4337a90e48d6269cc97b01874deac2aaf5a3e89c543329ab03"));
        assert(genesis.hashMerkleRoot == uint256S("0xcc3337810d74da69570c3f2778cb2bc7ad78d51d8791b13a6f8d9ee9e8457727"));

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
//        vSeeds.emplace_back("testnet-seed.DeepOniontools.com");
//        vSeeds.emplace_back("seed-b.DeepOnion.loshan.co.uk");
//        vSeeds.emplace_back("dnsseed-testnet.thrasher.io");

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "tdpn";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;

        checkpointData = (CCheckpointData) {
            {
            	{  1000000, uint256S("d6ee31197c5d271cf4cd16f15c6ae35ed2e6e545ba78407c559f6c746143eb9c")}
            }
        };

        chainTxData = ChainTxData{
            // Data as of block a0afbded94d4be233e191525dc2d467af5c7eab3143c852c3cd549831022aad6 (height 343833)
            1516406749,
            794057,
            0.01
        };

        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(0, 0xe00670bu));
    }
};

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
        consensus.BIP16Height = 0; // always enforce P2SH BIP16 on regtest
        consensus.BIP34Height = 100000000; // BIP34 has not activated on regtest (far in the future so block v1 are not rejected in tests)
        consensus.BIP34Hash = uint256();
        consensus.BIP65Height = 1351; // BIP65 activated on regtest (Used in rpc activation tests)
        consensus.BIP66Height = 1251; // BIP66 activated on regtest (Used in rpc activation tests)
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.posLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 14400; // two weeks
        consensus.nPowTargetSpacing = 240;
        consensus.nPosTargetSpacing = 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        // consensus.fPowNoRetargeting = true;
        // consensus.fPosNoRetargeting = true;
        consensus.nStakeMinAge = 60 * 60 * 24 * 1;			// minimum age for coin age: 1d
        consensus.nStakeMaxAge = 60 * 60 * 24 * 30;	        // stake age of full weight: 30d
        consensus.nModifierInterval = 8 * 60;				// time to elapse before new modifier is computed
        consensus.nCoinbaseMaturity = 40;					// 40 Blocks maturity
        consensus.nRuleChangeActivationThreshold = 45; // 75% for testchains
        consensus.nMinerConfirmationWindow = 60; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xbf;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0xda;
        nDefaultPort = 19444;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1546281565, 1249377, 0x1e0fffff, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x0000045eea7d9a4337a90e48d6269cc97b01874deac2aaf5a3e89c543329ab03"));
        assert(genesis.hashMerkleRoot == uint256S("0xcc3337810d74da69570c3f2778cb2bc7ad78d51d8791b13a6f8d9ee9e8457727"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true; 

        checkpointData = {
            {
                {0, uint256S("530827f38f93b43ed12af0b3ad25a288dc02ed74d6d7857862df51fc56c416f9")},
            }
        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1,58);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "rdpn";

        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(0, 0xfd11f4e7u));

    }
};

static std::unique_ptr<CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams());
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}

void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    globalChainParams->UpdateVersionBitsParameters(d, nStartTime, nTimeout);
}
