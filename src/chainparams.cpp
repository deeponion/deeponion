// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "assert.h"
#include "core.h"
#include "protocol.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

//
// Main network
//

unsigned int pnSeed[] =
{
    0x38a9b992, 0x73d4f3a2, 0x43eda52e, 0xa1c4a2b2, 0x73c41955, 0x6992f3a2, 0x729cb992, 0x8b53b205,
    0xb651ec36, 0x8b422e4e, 0x0fe421b2, 0x83c1a2b2, 0xbd432705, 0x2e11b018, 0x281544c1, 0x8b72f3a2,
    0xb934555f, 0x2ba02e4e, 0x6ab7c936, 0x8728555f, 0x03bfd143, 0x0a73df5b, 0xcd2b5a50, 0x746df3a2,
    0x7481bb25, 0x6f4d4550, 0x78582f4e, 0xa03a0f46, 0xe8b0e2bc, 0xa2d17042, 0x718a09b0, 0xdaffd4a2,
    0xbb1a175e, 0xb21f09b0, 0xb5549bc0, 0xe404c755, 0x95d882c3, 0xfff3692e, 0x3777d9c7, 0x425b2746,
    0x497990c6, 0xb2782dcc, 0xf9352225, 0xa75cd443, 0x4c05fb94, 0x44c91c2e, 0x47c6a5bc, 0xd606fb94,
    0xc1b9e2bc, 0x32acd23e, 0x89560da2, 0x5bebdad8, 0x3a210e08, 0xbdc5795b, 0xcc86bb25, 0xbe9f28bc,
    0xef3ff3a2, 0xca29df59, 0xe4fd175e, 0x1f3eaa6b, 0xacdbaa6b, 0xb05f042e, 0x81ed6cd8, 0x9a3c0cc3,
    0x4200175e, 0x5a017ebc, 0x42ef4c90, 0x8abfd143, 0x24fbf3a2, 0x140846a6, 0x4f7d9553, 0xeea5d151,
    0xe67c0905, 0x52d8048e, 0xcabd2e4e, 0xe276692e, 0x07dea445, 0xdde3f3a2, 0x6c47bb25, 0xae0efb94,
    0xf5e15a51, 0xaebdd25b, 0xf341175e, 0x46532705, 0xc47728bc, 0xe4e14c90, 0x9dc8f752, 0x050c042e,
    0x1c84bb25, 0x4f163b25, 0x1a017ebc, 0xa5282e4e, 0x8c667e60, 0xc7113b25, 0xf0b44832, 0xf1a134d0,
    0x973212d4, 0xd35cbb25, 0xd5123b25, 0x68220254, 0x7ad43e32, 0x9268e32e, 0xdf143b25, 0xaf04c436,
    0xaded0051, 0xfa86d454, 0x09db048e, 0x26003b25, 0x58764c90, 0x9a2f555f, 0x0c24ec97, 0x92123b25,
    0x0526d35f, 0x17db048e, 0xd2e42f4e, 0x38cca5bc, 0xc6320ab9, 0xe28ac836, 0xc560aa6b, 0xa5c16041,
    0x70a6f1c0, 0x011ec8c1, 0xd6e9c332, 0x131263c0, 0xa15a4450, 0xef218abc, 0x2729f948, 0x02835443,
    0x5614336c, 0xb12aacb2, 0xe368aa6b, 0x3cc6ffad, 0x36206494, 0x2c90e9c1, 0x32bb53d4, 0xca03de5c,
    0x775c1955, 0x19ef1ba3, 0x0b00dc1f, 0x244d0f40, 0x54d9e2bc, 0x25ced152, 0x967b03ad, 0x951c555f,
    0x4c3f3b25, 0x13f6f3a2, 0x17fca5bc, 0x0e2d306c, 0xacd8764b, 0xca230bcc, 0x8569d3c6, 0x3264d8a2,
    0xe8630905, 0x25e02a64, 0x3aba1fb0, 0x6bbdd25b, 0xee9a4c90, 0xcda25982, 0x8b3e804e, 0xf043fb94,
    0x4b05fb94, 0x0c44c052, 0xf403f45c, 0x4333aa6b, 0xc193484d, 0x3fbf5d4c, 0x0bd7f74d, 0x150e3fb2,
    0x8e2eddb0, 0x09daf150, 0x8a67c7c6, 0x22a9e52e, 0x05cff476, 0xc99b2f4e, 0x0f183b25, 0xd0358953,
    0x20f232c6, 0x0ce9e217, 0x09f55d18, 0x0555795b, 0x5ed2fa59, 0x2ec85917, 0x2bf61fb0, 0x024ef54d,
    0x3c53b859, 0x441cbb25, 0x50c8aa6b, 0x1b79175e, 0x3125795b, 0x27fc1fb0, 0xbcd53e32, 0xfc781718,
    0x7a8ec345, 0x1da6985d, 0x34bd1f32, 0xcb00edcf, 0xf9a5fdce, 0x21ccdbac, 0xb7730118, 0x6a43f6cc,
    0x6e65e262, 0x21ca1f3d, 0x10143b25, 0xc8dea132, 0xaf076693, 0x7e431bc6, 0xaa3df5c6, 0x44f0c536,
    0xeea80925, 0x262371d4, 0xc85c895b, 0xa6611bc6, 0x1844e47a, 0x49084c90, 0xf3d95157, 0x63a4a844,
    0x00477c70, 0x2934d35f, 0xe8d24465, 0x13df88b7, 0x8fcb7557, 0xa591bd5d, 0xc39453d4, 0xd5c49452,
    0xc8de1a56, 0x3cdd0608, 0x3c147a55, 0x49e6cf4a, 0xb38c8705, 0x0bef3479, 0x01540f48, 0xd9c3ec57,
    0xed6d4c90, 0xa529fb94, 0xe1c81955, 0xfde617c6, 0x72d18932, 0x9d61bb6a, 0x6d5cb258, 0x27c7d655,
    0xc5644c90, 0x31fae3bc, 0x3afaf25e, 0x98efe2bc, 0x91020905, 0xb566795b, 0xaf91bd5d, 0xb164d655,
    0x72eb47d4, 0xae62f3a2, 0xb4193b25, 0x0613fb94, 0xa6db048e, 0xf002464b, 0xc15ebb6a, 0x8a51f3a2,
    0x485e2ed5, 0x119675a3, 0x1f3f555f, 0x39dbc082, 0x09dea445, 0x74382446, 0x3e836c4e, 0x6e43f6cc,
    0x134dd9a2, 0x5876f945, 0x3516f725, 0x670c81d4, 0xaf7f170c, 0xb0e31155, 0xe271894e, 0x615e175e,
    0xb3446fd0, 0x13d58ac1, 0x07cff476, 0xe601e405, 0x8321277d, 0x0997548d, 0xdb55336c, 0xa1271d73,
    0x582463c0, 0xc2543025, 0xf6851c73, 0xe75d32ae, 0xf916b4dd, 0xf558fb94, 0x52111d73, 0x2bc8615d,
    0xd4dcaf42, 0x65e30979, 0x2e1b2360, 0x0da01d73, 0x3f1263c0, 0xd15c735d, 0x9cf2134c, 0x20d0048e,
    0x48cf0125, 0xf585bf5d, 0x12d7645e, 0xd5ace2bc, 0x0c6220b2, 0xbe13bb25, 0x88d0a52e, 0x559425b0,
    0x24079e3d, 0xfaa37557, 0xf219b96a, 0x07e61e4c, 0x3ea1d295, 0x24e0d852, 0xdde212df, 0x44c37758,
    0x55c243a4, 0xe77dd35f, 0x10c19a5f, 0x14d1048e, 0x1d50fbc6, 0x1570456c, 0x567c692e, 0x641d6d5b,
    0xab0c0cc6, 0xab6803c0, 0x136f21b2, 0x6a72545d, 0x21d031b2, 0xff8b5fad, 0xfd0096b2, 0x5f469ac3,
    0x3f6ffa62, 0x7501f863, 0x48471f60, 0xcccff3a2, 0x7f772e44, 0xc1de7757, 0x0c94c3cb, 0x620ac658,
    0x520f1d25, 0x37366c5f, 0x7594b159, 0x3804f23c, 0xb81ff054, 0x96dd32c6, 0x928228bc, 0xf4006e41,
    0x0241c244, 0x8dbdf243, 0x26d1b247, 0xd5381c73, 0xf3136e41, 0x4afa9bc0, 0xa3abf8ce, 0x464ce718,
    0xbd9d017b, 0xf4f26132, 0x141b32d4, 0x2ec50c18, 0x4df119d9, 0x93f81772, 0xd9607c70, 0x3522b648,
    0xf2006e41, 0x761fe550, 0x40104836, 0x55dffe96, 0xc45db158, 0xe75e4836, 0x8dfab7ad, 0xe3eff3a2,
    0x6a6eaa6b, 0x2177d9c7, 0x724ce953, 0xafe918b9, 0xf9368a55, 0xdc0a555f, 0xa4b2d35f, 0x4d87b0b8,
    0x93496a54, 0x5a5c967b, 0xd47028bc, 0x3c44e47a, 0x11c363c0, 0x28107c70, 0xb756a558, 0xb82bbb6a,
    0x285d49ad, 0x3b0ce85c, 0xe53eb45f, 0xa836e23c, 0x409f63c0, 0xc80fbd44, 0x3447f677, 0xe4ca983b,
    0x20673774, 0x96471ed9, 0x4c1d09b0, 0x91d5685d, 0x55beec4d, 0x1008be48, 0x660455d0, 0xf8170fda,
    0x3c21dd3a, 0x8239bb36, 0x9fe7e2bc, 0x900c47ae, 0x6a355643, 0x03dcb318, 0xefca123d, 0x6af8c4d9,
    0x5195e1a5, 0x32e89925, 0x0adc51c0, 0x45d7164c, 0x02495177, 0x8131175e, 0x681b5177, 0x41b6aa6b,
    0x55a9603a, 0x1a0c1c1f, 0xdb4da043, 0x3b9b1632, 0x37e08368, 0x8b54e260, 0xcd14d459, 0x82a663c0,
    0x05adc7dd, 0xe683f3a2, 0x4cddb150, 0x67a1a62e, 0x8c0acd25, 0x07f01f3e, 0x3111296c, 0x2d0fda2e,
    0xa4f163c0, 0xca6db982, 0x78ed2359, 0x7eaa21c1, 0x62e4f3a2, 0x50b81d73, 0xcd074a3a, 0xcb2d904b,
    0x9b3735ce, 0xab67f25c, 0xa0eb5036, 0x62ae5344, 0xe2569bb2, 0xc4422e4e, 0xab5ec8d5, 0xaa81e8dd,
    0xa39264c6, 0xf391563d, 0xb79bbb25, 0x174a7857, 0x0fd4aa43, 0x3e158c32, 0x3ae8b982, 0xea342225,
    0x48d1a842, 0xa52bf0da, 0x4bcb4a4c, 0xa6d3c15b, 0x49a0d35f, 0x97131b4c, 0xf197e252, 0xfe3ebd18,
    0x156dacb8, 0xf63328bc, 0x8e95b84c, 0x560455d0, 0xee918c4e, 0x1d3e435f, 0xe1292f50, 0x0f1ec018,
    0x7d70c60e, 0x6a29d5be, 0xf5fecb18, 0xd6da1f63, 0xccce1c2e, 0x7a289f5e, 0x2775ae47, 0x696df560,
    0x4dbe00ae, 0x474e6c5c, 0x604141d5, 0xaed0c718, 0x8acfd23e, 0x7ff4b84c, 0x4b44fc60, 0xdf58aa4f,
    0x9b7440c0, 0xb811c854, 0xd90ec24e, 0xcff75c46, 0xa5a9cc57, 0xb3d21e4c, 0x794779d9, 0xe5613d46,
    0x9478be43, 0xc5d11152, 0xe85fbb6a, 0x3e1ed052, 0xf747e418, 0x3b9c61c2, 0xb2532949, 0x43077432,
    0xa3db0b68, 0xb3b6e35a, 0x70361b6c, 0x3a8bad3e, 0x23079e3d, 0x09314c32, 0x92f90053, 0x4fc31955,
    0xa59b0905, 0x924128bc, 0x4e63c444, 0x344dc236, 0x43055fcb, 0xdc1a1c73, 0x38aaaa6b, 0xa61cf554,
    0x6d8f63c0, 0x24800a4c, 0x2406f953, 0x9558bb6a, 0x1d281660, 0x054c4954, 0x2de4d418, 0x5fdaf043,
    0xb681356c, 0xf8c3febc, 0x8854f950, 0x55b45d32, 0xde07bcd1, 0x156e4bda, 0x924cf718, 0xc34a0d47,
    0xdd5e1c45, 0x4a0d63c0, 0xaf4b88d5, 0x7852b958, 0x6f205fc0, 0x838af043, 0x45ac795b, 0x43bbaa6b,
    0x998d1c73, 0x11c1d558, 0x749ec444, 0x9a38c232, 0xad2f8c32, 0x3446c658, 0x8fe7a52e, 0x4e846b61,
    0x064b2d05, 0x0fd09740, 0x7a81a743, 0xf1f08e3f, 0x35ca1967, 0x24bdb17d, 0x144c2d05, 0x5505bb46,
    0x13fd1bb9, 0x25de2618, 0xc80a8b4b, 0xcec0fd6c, 0xdc30ad4c, 0x4009f3a2, 0x472f3fb2, 0x5e69c936,
    0x0380796d, 0xa463f8a2, 0xa46fbdc7, 0x3b0cc547, 0xb6644f46, 0x4b90fc47, 0x39e3f563, 0x72d81e56,
    0xe177d9c7, 0x95bff743, 0xea985542, 0xc210ec55, 0xeef70b67, 0xc9eb175e, 0x844d38ad, 0x65afa247,
    0x72da6d26, 0xed165dbc, 0xe8c83ad0, 0x9a8f37d8, 0x925adf50, 0x6b6ac162, 0x4b969e32, 0x735e1c45,
    0x4423ff60, 0xfa57ec6d, 0xcde2fb65, 0x11093257, 0x4748cd5b, 0x720c03dd, 0x8c7b0905, 0xba8b2e48
};

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xfb;
        pchMessageStart[1] = 0xc0;
        pchMessageStart[2] = 0xb6;
        pchMessageStart[3] = 0xdb;
        vAlertPubKey = ParseHex("040184710fa689ad5023690c80f3a49c8f13f8d45b8c857fbcbc8bc4a8e4d3eb4b10f4d4604fa08dce601aaf0f470216fe1b51850b4acf21b179c45070ac7b03a9");
        nDefaultPort = 9333;
        nRPCPort = 9332;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20); // Litecoin: starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 840000;

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //
        // CBlock(hash=12a765e31ffd4059bada, PoW=0000050c34a64b415b6b, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=97ddfbbae6, nTime=1317972665, nBits=1e0ffff0, nNonce=2084524493, vtx=1)
        //   CTransaction(hash=97ddfbbae6, ver=1, vin.size=1, vout.size=1, nLockTime=0)
        //     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104404e592054696d65732030352f4f63742f32303131205374657665204a6f62732c204170706c65e280997320566973696f6e6172792c2044696573206174203536)
        //     CTxOut(nValue=50.00000000, scriptPubKey=0x040184710fa689ad5023690c80f3a4)
        //   vMerkleTree: 97ddfbbae6
        const char* pszTimestamp = "NY Times 05/Oct/2011 Steve Jobs, Apple’s Visionary, Dies at 56";
        CTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 50 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("040184710fa689ad5023690c80f3a49c8f13f8d45b8c857fbcbc8bc4a8e4d3eb4b10f4d4604fa08dce601aaf0f470216fe1b51850b4acf21b179c45070ac7b03a9") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1317972665;
        genesis.nBits    = 0x1e0ffff0;
        genesis.nNonce   = 2084524493;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x12a765e31ffd4059bada1e25190f6e98c99d9714d334efa41a195a7e7e04bfe2"));
        assert(genesis.hashMerkleRoot == uint256("0x97ddfbbae6be97fd6cdf3e7ca13232a3afff2353e29badfab7f73011edd4ced9"));

        vSeeds.push_back(CDNSSeedData("litecointools.com", "dnsseed.litecointools.com"));
        vSeeds.push_back(CDNSSeedData("litecoinpool.org", "dnsseed.litecoinpool.org"));
        vSeeds.push_back(CDNSSeedData("xurious.com", "dnsseed.ltc.xurious.com"));
        vSeeds.push_back(CDNSSeedData("koin-project.com", "dnsseed.koin-project.com"));
        vSeeds.push_back(CDNSSeedData("weminemnc.com", "dnsseed.weminemnc.com"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(48);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(5);
        base58Prefixes[SECRET_KEY] =     list_of(176);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4);

        // Convert the pnSeeds array into usable address objects.
        for (unsigned int i = 0; i < ARRAYLEN(pnSeed); i++)
        {
            // It'll only connect to one or two seed nodes because once it connects,
            // it'll get a pile of addresses with newer timestamps.
            // Seed nodes are given a random 'last seen time' of between one and two
            // weeks ago.
            const int64_t nOneWeek = 7*24*60*60;
            struct in_addr ip;
            memcpy(&ip, &pnSeed[i], sizeof(ip));
            CAddress addr(CService(ip, GetDefaultPort()));
            addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
            vFixedSeeds.push_back(addr);
        }
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet (v3)
//
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xfc;
        pchMessageStart[1] = 0xc1;
        pchMessageStart[2] = 0xb7;
        pchMessageStart[3] = 0xdc;
        vAlertPubKey = ParseHex("04302390343f91cc401d56d68b123028bf52e5fca1939df127f63c6467cdf9c8e2c14b61104cf817d0b780da337893ecc4aaff1309e536162dabbdb45200ca2b0a");
        nDefaultPort = 19333;
        nRPCPort = 19332;
        strDataDir = "testnet3";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1317798646;
        genesis.nNonce = 385270584;
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0xf5ae71e26c74beacc88382716aced69cddf3dffff24f384e1808905e0188f68f"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("litecointools.com", "testnet-seed.litecointools.com"));
        vSeeds.push_back(CDNSSeedData("xurious.com", "testnet-seed.ltc.xurious.com"));
        vSeeds.push_back(CDNSSeedData("wemine-testnet.com", "dnsseed.wemine-testnet.com"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(111);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(196);
        base58Prefixes[SECRET_KEY]     = list_of(239);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94);
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xbf;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0xda;
        nSubsidyHalvingInterval = 150;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1296688602;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 2;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 19444;
        nRPCPort = 19443;
        strDataDir = "regtest";
        assert(hashGenesisBlock == uint256("0x9372df8b4c0144d2238b73d65ce81b5eb37ec416c23fc29307b89de4b0493cf8"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
