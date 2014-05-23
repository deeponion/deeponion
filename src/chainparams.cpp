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
    0x6ab5368e, 0x63109859, 0x6c47bb25, 0x87d888c1, 0x1d9b2e48, 0x63a6c545, 0xf3ca1a48, 0x23b6b242,
    0x8a67c7c6, 0x70a6f1c0, 0xc585c96d, 0x5cc4fd36, 0x239be836, 0x6660dc36, 0x2664cb36, 0xa602cd36,
    0xb83dfc36, 0x70a2fe18, 0x2c589d55, 0xf969ec2e, 0x702ab643, 0x6a97e655, 0xad9751ce, 0x57e5025a,
    0x9d065643, 0xe7b5ff60, 0x959d0d5a, 0x9667a318, 0xeba0c118, 0xb380d418, 0x170ccdde, 0x3548d9a2,
    0x3261ff53, 0x42df0676, 0x9d7445ae, 0x1db3e953, 0xafc0b1b7, 0x1648934b, 0x535ee644, 0x4b89b64f,
    0x56ed3060, 0x0810a15f, 0x03590ccf, 0x80752452, 0x0cc87162, 0xfec159d5, 0xcf0df618, 0x48865456,
    0xdec8e55a, 0x91e6ee5b, 0xc4739518, 0x24d45453, 0xd5e5be44, 0xdafcff57, 0x0e73ca18, 0x83c4d148,
    0x5a51ee53, 0x367e1c56, 0x2d651f54, 0x5eb4be43, 0x621589b2, 0x81dddedd, 0xd7499f56, 0xa48a694c,
    0xd408c762, 0x88d36144, 0x6891772e, 0x38e89c73, 0x8ce3a856, 0x52fa1fb0, 0xd9d5796d, 0x27318945,
    0x2e680452, 0x619bc445, 0xd0dc092e, 0x7192c962, 0xc2c9e405, 0xb9e3e747, 0xe459c9c1, 0x9d043b25,
    0xe2b235c6, 0xed2dcf18, 0xb3d03cae, 0x3d2dafb8, 0xd46a0e45, 0x4a32f1d8, 0x350be560, 0xab0a648a,
    0x87b6bc43, 0x6745629b, 0x72b9c362, 0x03a91c05, 0x7320bd3b, 0x32920b18, 0xbc2ca162, 0x216c4f7d,
    0x64151a4e, 0x4b63e20c, 0xe703c3be, 0xc2d5fab2, 0x2b28b762, 0xde47b0ba, 0xf2e19dd9, 0x99044fad,
    0x8252a5c0, 0x6e8be597, 0x4f0bb56c, 0xfaa52252, 0x8f764b52, 0xe5b21cad, 0x020cab4d, 0xc8e8f763,
    0x2eaacc6d, 0x2ce4dd4e, 0xfe27345c, 0xb21f09b0, 0x8b4199d9, 0x6b53c248, 0x42a8966d, 0xd5387145,
    0xc091c257, 0x2fe06751, 0xecf66552, 0x37dd0418, 0x8073c57c, 0x5471d54e, 0x56953360, 0x0d1ffcdf,
    0xb4554318, 0x16cb54c6, 0xa064d05e, 0x2b0fa93a, 0xec26d162, 0x9ca91b42, 0xdcfa4457, 0x1b5c0a7a,
    0x4561a17c, 0xcc52a662, 0xf9d47ad9, 0xfa418cb2, 0x88085618, 0x007aa55f, 0xfa2e4d4d, 0x8516a843,
    0x634ac658, 0x2c36f62e, 0x3f0cbe5e, 0xd0e87257, 0x37d5e6bc, 0x5941c1c7, 0x5ee001ae, 0xc2791e6c,
    0x0c6220b2, 0xab1ba258, 0x4719c076, 0xabb6a942, 0x6e588b52, 0x101a4352, 0x9604b362, 0x16607fc7,
    0x4a687d45, 0xc217feb2, 0xaebb6b18, 0x4439412e, 0x41330360, 0xca23946d, 0x1c699d76, 0xcd302344,
    0x4683afad, 0xad3c644f, 0x95ab4f05, 0xb34ec562, 0x57e3ff50, 0xcb950847, 0x743ced60, 0xb6734347,
    0x6237a2b2, 0x1517e244, 0xfd0b128b, 0xb7eb605f, 0x6a9717ad, 0x7e8d65ae, 0xdddc4cad, 0xc63530a6,
    0xfcd78559, 0xc779e25e, 0xf683de58, 0x7cd1ff50, 0x6e0931ad, 0x7c1b46ad, 0x9f4b4252, 0xf421482e,
    0xeca7e697, 0xfe466544, 0x46fa2240, 0xd33328bc, 0x7be6d7bd, 0xc205c27b, 0xa04c07d8, 0x5bcdb350,
    0x847bc74a, 0x14967f45, 0x59b341ad, 0x9ce4d783, 0xc38300c0, 0x4f1b4aad, 0x018daa32, 0x95d7f854,
    0x4bd58543, 0xfe8446ad, 0xc3288f18, 0xcda2e253, 0x662e4852, 0x9338e24e, 0xc2fd1218, 0xa7198252,
    0x481858b8, 0x55b74374, 0xbd458d5e, 0xb2cc6d54, 0x2ca11b4e, 0x62d1be58, 0xf0637fbc, 0xd9943950,
    0x0f6f4a47, 0x188a6144, 0x768ea0d8, 0xd2c31c54, 0x29462ed5, 0x2b546ad5, 0x8ba12d6c, 0x1a3f7255,
    0xa836e23c, 0xdcde0552, 0xda5b3945, 0x7e3720b2, 0x8c098018, 0x42cddd50, 0x0c52a65f, 0x8cce175e,
    0x96554242, 0x7309c779, 0xcb2537ca, 0xecfb70d9, 0x19c0b259, 0x7b559ed8, 0x2f03ae44, 0x1b2b0f05,
    0x9e72165e, 0x4ac7413e, 0xa22cbb6a, 0x9fc7624d, 0xbb101a54, 0xfdb0c23e, 0x84a65a47, 0x1efded62,
    0x1f47f554, 0xe5c16ad2, 0x76b62332, 0xe4613d46, 0xd74f6ec1, 0x3d0e2b32, 0x6725fe5e, 0xb62a8729,
    0x922e9925, 0x7efc2544, 0x12af60d4, 0x5e042f44, 0x5fcaff54, 0x144a3493, 0x5788ec47, 0x729175b2,
    0x493b316c, 0x949d4542, 0x4ffc8856, 0x18a95b61, 0xdaabc547, 0xc879d855, 0x7d8488c1, 0x3cb7b052,
    0xbe8ade6f, 0x6ef6a555, 0x737e5247, 0x7368e252, 0x5fbe1056, 0xb848e217, 0x44a44105, 0xb7610150,
    0x3c2eed62, 0x2b0c9e6d, 0x2a1698b4, 0x4e6fa443, 0xb6c3fe4d, 0xd86c8a43, 0x48b27125, 0x9d9c60cb,
    0x349a6d4c, 0xae336259, 0x81d7976d, 0x8e9fe2c0, 0x5f20c2dd, 0x6f289e52, 0xe954cf51, 0xc96eb248,
    0x1c29f562, 0xb01e3842, 0x119511b9, 0x4811856d, 0x172ff854, 0x7dab5451, 0x52520752, 0xc414ed52,
    0x368f4105, 0x7767b047, 0x1c459f32, 0x05b5e697, 0xb5273160, 0x99eaec69, 0x0cd7a951, 0x36e1f13e,
    0xee815148, 0x5773e8bc, 0xf61f35ad, 0xa0b903ae, 0x2d811660, 0x98aec3be, 0x851afa59, 0xce25a518,
    0xfcaaf2a2, 0x90bde760, 0x04cb16ad, 0x70a30432, 0xa6cd3e47, 0x0ccac672, 0xb238a018, 0xf7db8156,
    0xed1e0331, 0xe2590ccf, 0x0cde9e56, 0x5cc39744, 0x4e3c957c, 0xc57e67d3, 0x6b547662, 0x073cd243,
    0x670d9a18, 0x4666ae58, 0x661abd59, 0x64c94732, 0x8371cc82, 0x2f460843, 0x03bcfa45, 0xa23cac70,
    0x1fa47b46, 0xec86b4ad, 0x183e3105, 0x6dea2446, 0x0331bcd1, 0x2673cf18, 0x5ccbdaac, 0xa0483850,
    0x9b28c34a, 0xc69b9b62, 0xac944946, 0x3723b456, 0x4a53485d, 0x365fa8bc, 0x3adfbd5e, 0xdefbb143,
    0x6ca64746, 0xadea802e, 0x89c0bbad, 0xefcc854f, 0x38cca5bc, 0xacc61e5e, 0x5bc43ab8, 0x3003795b,
    0x391c2352, 0xe410f6ad, 0x3fa6f957, 0xd6b095d4, 0xeb00ba43, 0xf92f174c, 0xb45c0644, 0x6b299c53,
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

        vSeeds.push_back(CDNSSeedData("bitcoin.sipa.be", "seed.bitcoin.sipa.be"));
        vSeeds.push_back(CDNSSeedData("bluematt.me", "dnsseed.bluematt.me"));
        vSeeds.push_back(CDNSSeedData("dashjr.org", "dnsseed.bitcoin.dashjr.org"));
        vSeeds.push_back(CDNSSeedData("bitcoinstats.com", "seed.bitcoinstats.com"));
        vSeeds.push_back(CDNSSeedData("bitnodes.io", "seed.bitnodes.io"));
        vSeeds.push_back(CDNSSeedData("xf2.org", "bitseed.xf2.org"));

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
        vSeeds.push_back(CDNSSeedData("bitcoin.petertodd.org", "testnet-seed.bitcoin.petertodd.org"));
        vSeeds.push_back(CDNSSeedData("bluematt.me", "testnet-seed.bluematt.me"));

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
