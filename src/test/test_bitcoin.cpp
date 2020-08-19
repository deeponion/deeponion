// Copyright (c) 2011-2017 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <test/test_bitcoin.h>

#include <chainparams.h>
#include <consensus/consensus.h>
#include <consensus/validation.h>
#include <crypto/sha256.h>
#include <validation.h>
#include <miner.h>
#include <net_processing.h>
#include <ui_interface.h>
#include <streams.h>
#include <rpc/server.h>
#include <rpc/register.h>
#include <script/sigcache.h>

#include <memory>

void CConnmanTest::AddNode(CNode& node)
{
    LOCK(g_connman->cs_vNodes);
    g_connman->vNodes.push_back(&node);
}

void CConnmanTest::ClearNodes()
{
    LOCK(g_connman->cs_vNodes);
    g_connman->vNodes.clear();
}

uint256 insecure_rand_seed = GetRandHash();
FastRandomContext insecure_rand_ctx(insecure_rand_seed);

extern bool fPrintToConsole;
extern void noui_connect();

BasicTestingSetup::BasicTestingSetup(const std::string& chainName)
{
        SHA256AutoDetect();
        RandomInit();
        ECC_Start();
        SetupEnvironment();
        SetupNetworking();
        InitSignatureCache();
        InitScriptExecutionCache();
        fPrintToDebugLog = false; // don't want to write to debug.log file
        fCheckBlockIndex = true;
        SelectParams(chainName);
        noui_connect();
}

BasicTestingSetup::~BasicTestingSetup()
{
        ECC_Stop();
}

TestingSetup::TestingSetup(const std::string& chainName) : BasicTestingSetup(chainName)
{
    const CChainParams& chainparams = Params();
        // Ideally we'd move all the RPC tests to the functional testing framework
        // instead of unit tests, but for now we need these here.

        RegisterAllCoreRPCCommands(tableRPC);
        ClearDatadirCache();
        pathTemp = fs::temp_directory_path() / strprintf("test_DeepOnion_%lu_%i", (unsigned long)GetTime(), (int)(InsecureRandRange(100000)));
        fs::create_directories(pathTemp);
        gArgs.ForceSetArg("-datadir", pathTemp.string());

        // We have to run a scheduler thread to prevent ActivateBestChain
        // from blocking due to queue overrun.
        threadGroup.create_thread(boost::bind(&CScheduler::serviceQueue, &scheduler));
        GetMainSignals().RegisterBackgroundSignalScheduler(scheduler);

        mempool.setSanityCheck(1.0);
        pblocktree.reset(new CBlockTreeDB(1 << 20, true));
        pcoinsdbview.reset(new CCoinsViewDB(1 << 23, true));
        pcoinsTip.reset(new CCoinsViewCache(pcoinsdbview.get()));
        if (!LoadGenesisBlock(chainparams)) {
            throw std::runtime_error("LoadGenesisBlock failed.");
        }
        {
            CValidationState state;
            if (!ActivateBestChain(state, chainparams)) {
                throw std::runtime_error("ActivateBestChain failed.");
            }
        }
        nScriptCheckThreads = 3;
        for (int i=0; i < nScriptCheckThreads-1; i++)
            threadGroup.create_thread(&ThreadScriptCheck);
        g_connman = std::unique_ptr<CConnman>(new CConnman(0x1337, 0x1337)); // Deterministic randomness for tests.
        connman = g_connman.get();
        peerLogic.reset(new PeerLogicValidation(connman, scheduler));
}

TestingSetup::~TestingSetup()
{
        threadGroup.interrupt_all();
        threadGroup.join_all();
        GetMainSignals().FlushBackgroundCallbacks();
        GetMainSignals().UnregisterBackgroundSignalScheduler();
        g_connman.reset();
        peerLogic.reset();
        UnloadBlockIndex();
        pcoinsTip.reset();
        pcoinsdbview.reset();
        pblocktree.reset();
        fs::remove_all(pathTemp);
}

TestChain100Setup::TestChain100Setup() : TestingSetup(CBaseChainParams::REGTEST)
{
    // CreateAndProcessBlock() does not support building SegWit blocks, so don't activate in these tests.
    // TODO: fix the code to support SegWit blocks.
    UpdateVersionBitsParameters(Consensus::DEPLOYMENT_SEGWIT, 0, Consensus::BIP9Deployment::NO_TIMEOUT);
    // Generate a 100-block chain:
    coinbaseKey.MakeNewKey(true);
    CScript scriptPubKey = CScript() <<  ToByteVector(coinbaseKey.GetPubKey()) << OP_CHECKSIG;
// FIXME
//    for (int i = 0; i < COINBASE_MATURITY; i++)
//    {
//        std::vector<CMutableTransaction> noTxns;
//        CBlock b = CreateAndProcessBlock(noTxns, scriptPubKey);
//        coinbaseTxns.push_back(*b.vtx[0]);
//    }
}

//
// Create a new block with just given transactions, coinbase paying to
// scriptPubKey, and try to add it to the current chain.
//
CBlock
TestChain100Setup::CreateAndProcessBlock(const std::vector<CMutableTransaction>& txns, const CScript& scriptPubKey)
{
    const CChainParams& chainparams = Params();
    std::unique_ptr<CBlockTemplate> pblocktemplate = BlockAssembler(chainparams).CreateNewBlock(scriptPubKey);
    CBlock& block = pblocktemplate->block;

    // Replace mempool-selected txns with just coinbase plus passed-in txns:
    block.vtx.resize(1);
    for (const CMutableTransaction& tx : txns)
        block.vtx.push_back(MakeTransactionRef(tx));
    // IncrementExtraNonce creates a valid coinbase and merkleRoot
    unsigned int extraNonce = 0;
    {
        LOCK(cs_main);
        IncrementExtraNonce(&block, chainActive.Tip(), extraNonce);
    }

    while (!CheckProofOfWork(block.GetPoWHash(), block.nBits, chainparams.GetConsensus())) ++block.nNonce;

    std::shared_ptr<const CBlock> shared_pblock = std::make_shared<const CBlock>(block);
    ProcessNewBlock(chainparams, shared_pblock, true, nullptr);

    CBlock result = block;
    return result;
}

TestChain100Setup::~TestChain100Setup()
{
}


CTxMemPoolEntry TestMemPoolEntryHelper::FromTx(const CMutableTransaction &tx) {
    CTransaction txn(tx);
    return FromTx(txn);
}

CTxMemPoolEntry TestMemPoolEntryHelper::FromTx(const CTransaction &txn) {
    return CTxMemPoolEntry(MakeTransactionRef(txn), nFee, nTime, nHeight,
                           spendsCoinbase, sigOpCost, lp);
}

/**
 * @returns a real block (0ac3fababb398124e86b4fa1d6f6ea6f7acf8b36234c94507c43f38770df0e04) #height: #2000017
 *      with 5 txs.
 */
CBlock getBlockac3fa()
{
    CBlock block;
    CDataStream stream(ParseHex("0600000083dac1f45cd11465483316f6bf2a90377ac139973dfac1ddaf6dd49efc56cf52d3e7a9d15864960ef2902104dc02e04883290467b69780df20301d7c2f0fcc11c15c095f39bd011d000000000501000000c15c095f010000000000000000000000000000000000000000000000000000000000000000ffffffff040391841effffffff010000000000000000000000000001000000c15c095f013047a109c7818820f6cc16453e24d1e721597182cf49b57a1c0bce92e346b7af010000004847304402203baf5b0db398a5b7062c5cc63008eec6cae478d59fc42e1119c2a2ed8337540f02200194f3405a64cafc5a4851dfc77aa1298e5363b796c8194c298bd83ae92126b901ffffffff03000000000000000000c009bccb0300000023210383ef167e305d13fcb43ea661f97af4de271ddc021db9721a0f4426034348042facdf8bbecb0300000023210383ef167e305d13fcb43ea661f97af4de271ddc021db9721a0f4426034348042fac0000000001000000a65c095f01306ef59062438f67e81493736df655608470e3b7d3d5ba7b061e5bf2ab27f6f1000000006a47304402205ab5c40afe9a78f05fd650b03a97f50c4f9fff593636cee55c028d9509b40f5702201c7c4f761ef26bcc192d433b06d02bd05ec3e8dbe8988badebedfcdfbcbc3035012103826180c82800e0024df05128eb8e2713d221533a203040f6f8977763879d49fefeffffff028af6c8010400000017a914da69e89a663abf1df486b9e112e9048ec88480eb87840aaaf4010000001976a914e9bc8b09a2db6233beca813a6a870493d356eb1d88ac90841e0001000000b65c095f010eced2342c019995f1b44a31d8f08229c24afa4c799692a92fddfcc5cc1b86a3010000006b483045022100961a0303f24ce798a6acd5014610d016cba7d259be0e0ac3cc65100652ca1d1802205dcfa941d5a867173e895d4b6c305ccad1afaaa8752ad53109cf01f6a4b0f8dc01210304307974f2ae1fb00aad06e21de22f013c991a9ed0ccac277fbbcddfd3876ba0feffffff025a401a11020000001976a9147cd519f5ba82d6d97b7815b8f10fc92146cd28b488accc3e57fe0100000017a914da69e89a663abf1df486b9e112e9048ec88480eb8790841e0001000000b75c095f022f7e32c19d5b6fa4a80e0c2bee6bf43124d9cbdd092ffc9bc408e53b3d9aaac4020000006b483045022100f068887ea2f15c52d10f770b205a9e71ca83b7b71e9d362903075c8235a1746d02205c514bd7bc69562090ad3ad03411ef9aa17006d80605764c851733a69d4e0844012103a3eb5ed64e3df30abb47684650f8eb536678349e264f56908f20330256ff2170feffffff65e09da1f86c3d73e10d2bd3f405176a9f4f8d2853fec43be8c6cd6d02877c4b000000006b483045022100d178b1d41243bda6a84ddc28c4fbde7e78f09795a7dea788f9509daee5182e450220442d21d3ed386294d23ac32e23ae4efcd7de2aaaaba836a56de7fb4178612e2c01210207ded14957e185ace2070e96eb4a79fbf1c659a9d2746488b1a531c349511db3feffffff02cc3e57fe0100000017a914da69e89a663abf1df486b9e112e9048ec88480eb873060a30c000000001976a914fdc5b5ce6c4c465e0d4fc47a7a9c4ae3e761292088ac90841e004730450221009573534921a34c5ec750bee8b9b4d11cb94f231639cf2f3c1b2accd18a3a2de40220486617193f7a1e0fa90ed9a7a442f25d8fa71759b21a441b7fe9e1270e9dd57a"), SER_NETWORK, PROTOCOL_VERSION);
    stream >> block;
    return block;
}
