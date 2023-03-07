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
        consensus.SegwitHeight = 2335200; //f597f75df4f8582aca13bcd5c07a769410c5f828edcbfdedc4eefb1d9050abd0
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
        consensus.fPowNoRetargeting = false;
        // consensus.fPosNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 180; // 75% of 240
        consensus.nMinerConfirmationWindow = 240; // nPowTargetTimespan / nPowTargetSpacing * 4
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1499817600; // July 12, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1514764799; // December 31, 2017

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1625140800; // Jul 01 2021 12:00:00 GMT+0000
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1627819200; // Aug 01 2021 12:00:00 GMT+0000
            
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

        vFixedSeeds = std::vector<uint8_t>(chainparams_seed_main, chainparams_seed_main + ARRAYLEN(chainparams_seed_main));

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
                {1650039, uint256S("0x000000000000d29ac370d3931acae97e5f60faf20156d37393571194f7c41fe2")},
                {1700011, uint256S("0x0000000000013db11c2b26ca4d40546964bcab1ecfba4d56d9c8706043ce3b8b")},
                {1750036, uint256S("0x000000000001e342e9a2101180fec4939341974003a1fe94ea554af417a21097")},
                {1800046, uint256S("0x0000000000008ae28b23d32eb3cd781d203a37f175ab38316f581346c1c9c0b8")},
                {1850000, uint256S("0x000000000002067bcba645f4145cf46060b80228612cfe825fc55c6d86619912")},
                {1900004, uint256S("0x000000000000366221aa2cfe55f4abb47eee64a7a46d321cc1923b9bb3ad590a")},
                {1950010, uint256S("0x00000000000551ae872500d4884a765d4bc49a9e3cc3efb7101e25ab3a673b84")},
                {2000006, uint256S("0x0000000000007f882184c11a88a58e31b690e6fd2e7bdcec13c07ace7e4133ea")},
                {2050031, uint256S("0x000000000002df6471ae9596fe92fc43c740a48a0d01bdbab367116292fa27cb")},
                {2100009, uint256S("0x00000000000838a5a76350649b5d9771421f1655bf1a962a1a54e5ecbc505938")},
                {2150009, uint256S("0x00000000000524c49549430e00e510fdf4f1eced35ffa1409f35a749ee531702")},
                {2200004, uint256S("0x0000000000011fe6a986ccf4026660a713653b22a7b799ce7715b8449ba0f6e4")},
                {2250000, uint256S("0x00000000000273bdd091deb0a0ff5f4f926fe5acd36559de49fe7283a7c27f93")},
                {2300002, uint256S("0x0000000000000809e9d7ed187d5f2353ebf62a3cb2817fdf1c8e323fa76457f4")},
                {2350008, uint256S("0x0000000000010b873cc2149322a74c456d510c6604ef8a92d030f011daa95077")},
                {2400007, uint256S("0x0000000000013bb1b034d635aee4cedee9f38a8ca4297986297f5829358e1d15")},
                {2450000, uint256S("0x0000000000070a31b2a38588cc60234c2b82d3aa3c58dc3f4ab8d2c5499ad4eb")},
                {2500000, uint256S("0x00000000001b80efcc3de42dae6e5961ded3f9df19254171d56f7b388989d6dc")},
                {2550032, uint256S("0x0000000000044768f678440ef4b8f3bcb140864a8c787f74e6463c1b557009dd")},
                {2600007, uint256S("0x000000000001426b974cbc3f139174f23bd607707d1f2cb75cdc4c5ffb72f93c")},
                {2650008, uint256S("0x0000000000007d74f9d3f30bd86ff0f9ff7bae323a988e363f338f224bc55d16")},
                {2700002, uint256S("0x0000000000006759c7cf878f4cf14dd9cc4da46a74b3f33356052150b3726d22")},
                {2751510, uint256S("0x00000000000059385fd3d81b193f905630014b413f3acd4ec91f6975374a815e")},
                {2800014, uint256S("0x00000000000028d14a60be1849b9f9278b7f293d9c2634e492cdd6bcd247ae8a")},
                {2850003, uint256S("0x0000000000014ec4dd1ba53c63905548c2647aff7e00135ccf3e498aa8ac3c7a")},
                {2900002, uint256S("0x0000000000015f98c4067d9913ea35f40ecec38f92e36b89d4fc12308f37fb28")},
                {2950002, uint256S("0x0000000000040e741e85d20272afd22ecc008720b38992ef189578fcedf5f735")},
                {3000001, uint256S("0x000000000002326723312c5e190253d91f6fb7592a3d9a2204aa8e1cd1aece6d")},
                {3050025, uint256S("0x0000000000011e33d680f3d67688894a3b28e0671d84fc42121d948f37d80e23")},
                {3100000, uint256S("0x00000000000aa8515c338c3f10f1ad93b7b8b9409b53f2db23a53fe39218176d")},
                {3150002, uint256S("0x0000000000046e868a927a631fe24b04bace8713ecf25c9a533c3d1683adab3f")},
                {3200001, uint256S("0x000000000005a83b549df4fcc01fb9560274b6e4c5c7a2ed01b1db5f11a7083c")},
                {3250010, uint256S("0x000000000013d11815f18bb0c56fb2d8720281ad5653ebc89c78f778c83c9fe6")},
                {3300000, uint256S("0x0000000000007e97778c85dad93d20c4641299938ac53454a39376d1d87b7f02")},
                {3350008, uint256S("0x00000000000072f397b8e190c6bebe4baf9e0539e35f8172ec99da9ca3665dec")},
                {3400004, uint256S("0x000000000004f86383f9d8ed84f0f68b76885e810ad47459179cb158b0b4c9cf")},
                {3450003, uint256S("0x00000000000a8bfc292090665e9ced8823470545b5bac51ac1c86acd9071a4d5")},
                {3500008, uint256S("0x0000000000082cf0cdeaebbac169ff06cde8541179718f1ea010ae95bc6c41da")},
                {3550003, uint256S("0x0000000000132aa450ea8046359508288078cea3453e4dc682935794d80aa0fa")},
                {3600008, uint256S("0x000000000009e64632de6a1397ba1c449bf838edc4c205f1f622989fe8a09af3")},
                {3650001, uint256S("0x00000000000906d0cab27bebffcbff228675957babe99b452a1d88bad25a0426")},
                {3700009, uint256S("0x0000000000119011f724999e9522c8a80dce498585bcc6463f75cf9401fa2d5a")},
                {3750035, uint256S("0x00000000000379f9a9dd218a211cad55bae9409ad2a9e4473c212bf332b29822")},
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
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(1650039, 0xe0efbf2du));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(1700011, 0xfce6d343u));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(1750036, 0x71887c28u));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(1800046, 0x7a7c9398u));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(1850000, 0x76bb3f14u));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(1900004, 0xfb8cdf25u));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(1950010, 0xae0986fbu));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(2000006, 0x65dba23du));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(2050031, 0xcb53d1c8u));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(2100009, 0xd1d27ec1u));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(2150009, 0xc45c83bau));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(2200004, 0x5912da6du));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(2250000, 0x971ca6fcu));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(2300002, 0x0d9fdca6u));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(2350008, 0xf797c2cau));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(2400007, 0x4abe44f4u));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(2450000, 0x2341d7eau));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(2500000, 0x406a8f88u));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(2550032, 0xd091ebecu));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(2600007, 0x13ed88cau));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(2650008, 0x5f9ced4du));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(2700002, 0xb07600aeu));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(2751510, 0xa5a4f150u));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(2800014, 0xc627143fu));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(2850003, 0xb3bcb649u));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(2900002, 0x853ae272u));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(2950002, 0x0979a088u));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(3000001, 0xe296623cu));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(3050025, 0x466577dbu));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(3100000, 0xd756791bu));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(3150002, 0xffc8e9efu));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(3200001, 0x65b725b5));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(3250010, 0x7480808e));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(3300000, 0x2a7e0eb1));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(3350008, 0xe6ab3665));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(3400004, 0x7f366077));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(3450003, 0x436a84c9));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(3500008, 0x76c6a21c));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(3550003, 0xec707162));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(3600008, 0xcf97b299));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(3650001, 0x5d145732));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(3700009, 0x167576fb));
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(3750035, 0xa7eb1849));
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
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        // consensus.fPosNoRetargeting = false;
        consensus.nStakeMinAge = 60;					    // minimum age for coin age: 20 Minutes
        consensus.nStakeMaxAge = 60 * 60 * 24 * 30;	        // stake age of full weight: 30d
        consensus.nModifierInterval = 60;					// time to elapse before new modifier is computed
        consensus.nCoinbaseMaturity = 10;					// Blocks maturity
        consensus.nRuleChangeActivationThreshold = 45; 		// 75% for testchains
        consensus.nMinerConfirmationWindow = 60; 			// nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1625140800; // Jul 01 2021 12:00:00 GMT+0000
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1627819200; // Aug 01 2021 12:00:00 GMT+0000

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1618052400; // Sat Apr 10 2021 11:00:00 GMT+0000
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1649588400; // Sun Apr 10 2022 11:00:00 GMT+0000

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0xa0afbded94d4be233e191525dc2d467af5c7eab3143c852c3cd549831022aad6"); //343833

		pchMessageStart[0] = 0xa3;
		pchMessageStart[1] = 0xa1;
		pchMessageStart[2] = 0xa0;
		pchMessageStart[3] = 0xf1;
        nDefaultPort = 26550;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1617977000, 461649, 0x1e0fffff, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        // printf(">> block = %s\n", genesis.ToString().c_str()); 
        // printf(">> block.GetHash() == %s\n", genesis.GetHash().ToString().c_str());
        // printf(">> block.hashMerkleRoot == %s\n", genesis.hashMerkleRoot.ToString().c_str());
        // printf(">> block.nTime = %u \n", genesis.nTime);
        // printf(">> block.nNonce = %u \n", genesis.nNonce);

        assert(consensus.hashGenesisBlock == uint256S("0xdde47d50dd650a434fa299a98a09e5f5a16dde43ddb8d34b95be38c576a740c3"));
        assert(genesis.hashMerkleRoot == uint256S("0xdbc1d6a49eddf0c5fed1b6832696d598945fd8841286bb9bffc66e863c424746"));

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
        vFixedSeeds = std::vector<uint8_t>(chainparams_seed_test, chainparams_seed_test + ARRAYLEN(chainparams_seed_test));

        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;

        checkpointData = (CCheckpointData) {
            {
            	// {  1000000, uint256S("d6ee31197c5d271cf4cd16f15c6ae35ed2e6e545ba78407c559f6c746143eb9c")}
            }
        };

        chainTxData = ChainTxData{
            // Data as of block a0afbded94d4be233e191525dc2d467af5c7eab3143c852c3cd549831022aad6 (height 343833)
        	1597854998,
            794057,
            0.01
        };
        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(0, 0xabad6120u));
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
        consensus.fPowNoRetargeting = true;
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

        mapStakeModifierCheckpoints.insert(std::pair<int, unsigned int>(0, 0x000000000e00670b));

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
