// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2017 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_VALIDATION_H
#define BITCOIN_VALIDATION_H

#if defined(HAVE_CONFIG_H)
#include <config/bitcoin-config.h>
#endif

#include <amount.h>
#include <coins.h>
#include <fs.h>
#include <protocol.h> // For CMessageHeader::MessageStartChars
#include <policy/feerate.h>
#include <script/script_error.h>
#include <sync.h>
#include <versionbits.h>

#include <algorithm>
#include <exception>
#include <map>
#include <set>
#include <stdint.h>
#include <string>
#include <utility>
#include <vector>

#include <atomic>

class CBasicKeyStore;
class CBlockIndex;
class CBlockPolicyEstimator;
class CBlockTreeDB;
class CChainParams;
class CCoinControl;
class CCoinsViewDB;
class CConnman;
class CInv;
class CNode;
class CScriptCheck;
class CTxMemPool;
class CValidationState;
class CWallet;

struct ChainTxData;

struct PrecomputedTransactionData;
struct LockPoints;

/** Default for -whitelistrelay. */
static const bool DEFAULT_WHITELISTRELAY = true;
/** Default for -whitelistforcerelay. */
static const bool DEFAULT_WHITELISTFORCERELAY = true;
/** Default for -minrelaytxfee, minimum relay fee for transactions */
static const unsigned int DEFAULT_MIN_RELAY_TX_FEE = 10000;
//! -maxtxfee default
static const CAmount DEFAULT_TRANSACTION_MAXFEE = 0.1 * COIN;
//! Discourage users to set fees higher than this amount (in satoshis) per kB
static const CAmount HIGH_TX_FEE_PER_KB = 0.01 * COIN;
//! -maxtxfee will warn if called with a higher fee than this amount (in satoshis)
static const CAmount HIGH_MAX_TX_FEE = 100 * HIGH_TX_FEE_PER_KB;
/** Default for -limitancestorcount, max number of in-mempool ancestors */
static const unsigned int DEFAULT_ANCESTOR_LIMIT = 25;
/** Default for -limitancestorsize, maximum kilobytes of tx + all in-mempool ancestors */
static const unsigned int DEFAULT_ANCESTOR_SIZE_LIMIT = 101;
/** Default for -limitdescendantcount, max number of in-mempool descendants */
static const unsigned int DEFAULT_DESCENDANT_LIMIT = 25;
/** Default for -limitdescendantsize, maximum kilobytes of in-mempool descendants */
static const unsigned int DEFAULT_DESCENDANT_SIZE_LIMIT = 101;
/** Default for -mempoolexpiry, expiration time for mempool transactions in hours */
static const unsigned int DEFAULT_MEMPOOL_EXPIRY = 336;
/** Maximum kilobytes for transactions to store for processing during reorg */
static const unsigned int MAX_DISCONNECTED_TX_POOL_SIZE = 20000;
/** The maximum size of a blk?????.dat file (since 0.8) */
static const unsigned int MAX_BLOCKFILE_SIZE = 0x8000000; // 128 MiB
/** The pre-allocation chunk size for blk?????.dat files (since 0.8) */
static const unsigned int BLOCKFILE_CHUNK_SIZE = 0x1000000; // 16 MiB
/** The pre-allocation chunk size for rev?????.dat files (since 0.8) */
static const unsigned int UNDOFILE_CHUNK_SIZE = 0x100000; // 1 MiB

/** Maximum number of script-checking threads allowed */
static const int MAX_SCRIPTCHECK_THREADS = 16;
/** -par default (number of script-checking threads, 0 = auto) */
static const int DEFAULT_SCRIPTCHECK_THREADS = 0;
/** Number of blocks that can be requested at any given time from a single peer. */
static const int MAX_BLOCKS_IN_TRANSIT_PER_PEER = 16;
/** Timeout in seconds during which a peer must stall block download progress before being disconnected. */
static const unsigned int BLOCK_STALLING_TIMEOUT = 2;
/** Number of headers sent in one getheaders result. We rely on the assumption that if a peer sends
 *  less than this number, we reached its tip. Changing this value is a protocol upgrade. */
static const unsigned int MAX_HEADERS_RESULTS = 2000;
/** Maximum depth of blocks we're willing to serve as compact blocks to peers
 *  when requested. For older blocks, a regular BLOCK response will be sent. */
static const int MAX_CMPCTBLOCK_DEPTH = 5;
/** Maximum depth of blocks we're willing to respond to GETBLOCKTXN requests for. */
static const int MAX_BLOCKTXN_DEPTH = 10;
/** Size of the "block download window": how far ahead of our current height do we fetch?
 *  Larger windows tolerate larger download speed differences between peer, but increase the potential
 *  degree of disordering of blocks on disk (which make reindexing and pruning harder). We'll probably
 *  want to make this a per-peer adaptive value at some point. */
static const unsigned int BLOCK_DOWNLOAD_WINDOW = 1024;
/** Time to wait (in seconds) between writing blocks/block index to disk. */
static const unsigned int DATABASE_WRITE_INTERVAL = 60 * 60;
/** Time to wait (in seconds) between flushing chainstate to disk. */
static const unsigned int DATABASE_FLUSH_INTERVAL = 24 * 60 * 60;
/** Maximum length of reject messages. */
static const unsigned int MAX_REJECT_MESSAGE_LENGTH = 111;
/** Average delay between local address broadcasts in seconds. */
static const unsigned int AVG_LOCAL_ADDRESS_BROADCAST_INTERVAL = 24 * 60 * 60;
/** Average delay between peer address broadcasts in seconds. */
static const unsigned int AVG_ADDRESS_BROADCAST_INTERVAL = 30;
/** Average delay between trickled inventory transmissions in seconds.
 *  Blocks and whitelisted receivers bypass this, outbound peers get half this delay. */
static const unsigned int INVENTORY_BROADCAST_INTERVAL = 5;
/** Maximum number of inventory items to send per transmission.
 *  Limits the impact of low-fee transaction floods. */
static const unsigned int INVENTORY_BROADCAST_MAX = 7 * INVENTORY_BROADCAST_INTERVAL;
/** Average delay between feefilter broadcasts in seconds. */
static const unsigned int AVG_FEEFILTER_BROADCAST_INTERVAL = 10 * 60;
/** Maximum feefilter broadcast delay after significant change. */
static const unsigned int MAX_FEEFILTER_CHANGE_DELAY = 5 * 60;
/** Block download timeout base, expressed in millionths of the block interval (i.e. 10 min) */
static const int64_t BLOCK_DOWNLOAD_TIMEOUT_BASE = 1000000;
/** Additional block download timeout per parallel downloading peer (i.e. 5 min) */
static const int64_t BLOCK_DOWNLOAD_TIMEOUT_PER_PEER = 500000;

static const int64_t DEFAULT_MAX_TIP_AGE = 24 * 60 * 60;
/** Maximum age of our tip in seconds for us to be considered current for fee estimation */
static const int64_t MAX_FEE_ESTIMATION_TIP_AGE = 3 * 60 * 60;

/** Default for -permitbaremultisig */
static const bool DEFAULT_PERMIT_BAREMULTISIG = true;
static const bool DEFAULT_CHECKPOINTS_ENABLED = true;
static const bool DEFAULT_TXINDEX = true;
static const unsigned int DEFAULT_BANSCORE_THRESHOLD = 100;
/** Default for -persistmempool */
static const bool DEFAULT_PERSIST_MEMPOOL = true;
/** Default for -mempoolreplacement */
static const bool DEFAULT_ENABLE_REPLACEMENT = false;
/** Default for using fee filter */
static const bool DEFAULT_FEEFILTER = true;

/** Default for checkblockchain */
static const bool DEFAULT_VERIFYBLOCKCHAINHASH = false;

/** Maximum number of headers to announce when relaying blocks with headers message.*/
static const unsigned int MAX_BLOCKS_TO_ANNOUNCE = 8;

/** Maximum number of unconnecting headers announcements before DoS score */
static const int MAX_UNCONNECTING_HEADERS = 10;

static const bool DEFAULT_PEERBLOOMFILTERS = true;

/** DeepSend service default, currently its an opt in service. */
static const bool DEFAULT_DEEPSENDNODE = false;

/** Default for -stopatheight */
static const int DEFAULT_STOPATHEIGHT = 0;

/** Reject headers if someone attempts to start a chain this far back */
static const int ATTACK_DETECTION_HEIGHT = 500;

struct BlockHasher
{
    size_t operator()(const uint256& hash) const { return hash.GetCheapHash(); }
};

extern CScript COINBASE_FLAGS;
extern CCriticalSection cs_main;
extern CCriticalSection cs_deepsend;
extern CCriticalSection cs_servicelist;
extern CBlockPolicyEstimator feeEstimator;
extern CTxMemPool mempool;
typedef std::unordered_map<uint256, CBlockIndex*, BlockHasher> BlockMap;
extern BlockMap& mapBlockIndex;
extern uint64_t nLastBlockTx;
extern uint64_t nLastBlockWeight;
extern int64_t nLastCoinStakeSearchInterval;
extern const std::string strMessageMagic;
extern CWaitableCriticalSection csBestBlock;
extern CConditionVariable cvBlockChange;
extern std::atomic_bool fImporting;
extern std::atomic_bool fReindex;
extern int nScriptCheckThreads;
extern bool fTxIndex;
extern bool fIsBareMultisigStd;
extern bool fRequireStandard;
extern bool fCheckBlockIndex;
extern bool fCheckpointsEnabled;
extern size_t nCoinCacheUsage;
/** A fee rate smaller than this is considered zero fee (for relaying, mining and transaction creation) */
extern CFeeRate minRelayTxFee;
/** Absolute maximum transaction fee (in satoshis) used by wallet and mempool (rejects high fee in sendrawtransaction) */
extern CAmount maxTxFee;
/** If the tip is older than this (in seconds), the node is considered to be in initial block download. */
extern int64_t nMaxTipAge;
extern bool fEnableReplacement;

/** Block hash whose ancestors we will assume to have valid scripts without checking them. */
extern uint256 hashAssumeValid;

/** Minimum work we will assume exists on some valid chain. */
extern arith_uint256 nMinimumChainWork;

/** Best header we've seen so far (used for getheaders queries' starting points). */
extern CBlockIndex *pindexBestHeader;

/** Minimum disk space required - used in CheckDiskSpace() */
static const uint64_t nMinDiskSpace = 52428800;

/** Pruning-related variables and constants */
/** True if any block files have ever been pruned. */
extern bool fHavePruned;
/** True if we're running in -prune mode. */
extern bool fPruneMode;
/** Number of MiB of block files that we're trying to stay below. */
extern uint64_t nPruneTarget;
/** Block files containing a block-height within MIN_BLOCKS_TO_KEEP of chainActive.Tip() will not be pruned. */
static const unsigned int MIN_BLOCKS_TO_KEEP = 288;
/** Minimum blocks required to signal NODE_NETWORK_LIMITED */
static const unsigned int NODE_NETWORK_LIMITED_MIN_BLOCKS = 288;

static const signed int DEFAULT_CHECKBLOCKS = 6 * 4;
static const unsigned int DEFAULT_CHECKLEVEL = 3;

// Require that user allocate at least 550MB for block & undo files (blk???.dat and rev???.dat)
// At 1MB per block, 288 blocks = 288MB.
// Add 15% for Undo data = 331MB
// Add 20% for Orphan block rate = 397MB
// We want the low water mark after pruning to be at least 397 MB and since we prune in
// full block file chunks, we need the high water mark which triggers the prune to be
// one 128MB block file + added 15% undo data = 147MB greater for a total of 545MB
// Setting the target to > than 550MB will make it likely we can respect the target.
static const uint64_t MIN_DISK_SPACE_FOR_BLOCK_FILES = 550 * 1024 * 1024;

extern int LAST_REGISTERED_BLOCK_HEIGHT;
extern int LAST_REGISTERED_BTC_BLOCK_HEIGHT;
extern std::string LAST_REGISTERED_BLOCKCHAIN_HASH;
extern std::string LAST_REGISTERED_BTC_TX;

/** Deepsend related */
static const CAmount MIN_ANON_SERVICE_COIN = 2500 * COIN;
static const double DEEPSEND_FEE_RATE = 0.01;
static const CAmount DEEPSEND_MIN_FEE = 0.01 * COIN;
static const CAmount MAX_ALLOWED_DEEP_SEND = 1000 * COIN;
static const CAmount MIN_ALLOWED_DEEP_SEND = 0.1 * COIN;


enum AnonymousTxRole
{
	ROLE_UNKNOWN	= 0,
	ROLE_SENDER		= 1,
	ROLE_MIXER		= 2,
	ROLE_GUARANTOR	= 3
};

enum AnonymousTxStatus
{
	ATX_STATUS_NONE		= 0,
	ATX_STATUS_RESERVE	= 1,
	ATX_STATUS_INITDATA	= 2,
	ATX_STATUS_PUBKEY	= 3,
	ATX_STATUS_MSADDR	= 4,
	ATX_STATUS_MSDEPO	= 5,
	ATX_STATUS_MSDEPV	= 6,
	ATX_STATUS_MSTXR0	= 7,
	ATX_STATUS_MSTXR1	= 8,
	ATX_STATUS_MSTXRC	= 9,
	ATX_STATUS_COMPLETE = 10
};

/** 
 * Process an incoming block. This only returns after the best known valid
 * block is made active. Note that it does not, however, guarantee that the
 * specific block passed to it has been checked for validity!
 *
 * If you want to *possibly* get feedback on whether pblock is valid, you must
 * install a CValidationInterface (see validationinterface.h) - this will have
 * its BlockChecked method called whenever *any* block completes validation.
 *
 * Note that we guarantee that either the proof-of-work is valid on pblock, or
 * (and possibly also) BlockChecked will have been called.
 * 
 * Call without cs_main held.
 *
 * @param[in]   pblock  The block we want to process.
 * @param[in]   fForceProcessing Process this block even if unrequested; used for non-network block sources and whitelisted peers.
 * @param[out]  fNewBlock A boolean which is set to indicate if the block was first received via this call
 * @return True if state.IsValid()
 */
bool ProcessNewBlock(const CChainParams& chainparams, const std::shared_ptr<const CBlock> pblock, bool fForceProcessing, bool* fNewBlock);

/**
 * Process incoming block headers.
 *
 * Call without cs_main held.
 *
 * @param[in]  block The block headers themselves
 * @param[out] state This may be set to an Error state if any error occurred processing them
 * @param[in]  chainparams The params for the chain we want to connect to
 * @param[out] ppindex If set, the pointer will be set to point to the last new block index object for the given headers
 * @param[out] first_invalid First header that fails validation, if one exists
 */
bool ProcessNewBlockHeaders(const std::vector<CBlockHeader>& block, CValidationState& state, const CChainParams& chainparams, const CBlockIndex** ppindex=nullptr, CBlockHeader *first_invalid=nullptr);

/** Check whether enough disk space is available for an incoming block */
bool CheckDiskSpace(uint64_t nAdditionalBytes = 0);
/** Open a block file (blk?????.dat) */
FILE* OpenBlockFile(const CDiskBlockPos &pos, bool fReadOnly = false);
/** Translation to a filesystem path */
fs::path GetBlockPosFilename(const CDiskBlockPos &pos, const char *prefix);
/** Import blocks from an external file */
bool LoadExternalBlockFile(const CChainParams& chainparams, FILE* fileIn, CDiskBlockPos *dbp = nullptr);
/** Ensures we have a genesis block in the block tree, possibly writing one to disk. */
bool LoadGenesisBlock(const CChainParams& chainparams);
/** Load the block tree and coins database from disk,
 * initializing state if we're running with -reindex. */
bool LoadBlockIndex(const CChainParams& chainparams);
/** Update the chain tip based on database information. */
bool LoadChainTip(const CChainParams& chainparams);
/** Unload database information */
void UnloadBlockIndex();
/** Run an instance of the script checking thread */
void ThreadScriptCheck();
/** Check whether we are doing an initial block download (synchronizing from disk or network) */
bool IsInitialBlockDownload();
bool IsInitialBlockDownload2();
/** Retrieve a transaction (from memory pool, or from disk, if possible) */
bool GetTransaction(const uint256& hash, CTransactionRef& tx, const Consensus::Params& params, uint256& hashBlock, bool fAllowSlow = false, CBlockIndex* blockIndex = nullptr);
/** Find the best known block, and make it the tip of the block chain */
bool ActivateBestChain(CValidationState& state, const CChainParams& chainparams, std::shared_ptr<const CBlock> pblock = std::shared_ptr<const CBlock>());

/** Guess verification progress (as a fraction between 0.0=genesis and 1.0=current tip). */
double GuessVerificationProgress(const ChainTxData& data, const CBlockIndex* pindex);

/** Calculate the amount of disk space the block & undo files currently use */
uint64_t CalculateCurrentUsage();

/**
 *  Mark one block file as pruned.
 */
void PruneOneBlockFile(const int fileNumber);

/**
 *  Actually unlink the specified files
 */
void UnlinkPrunedFiles(const std::set<int>& setFilesToPrune);

/** Flush all state, indexes and buffers to disk. */
void FlushStateToDisk();
/** Prune block files and flush state to disk. */
void PruneAndFlush();
/** Prune block files up to a given height */
void PruneBlockFilesManual(int nManualPruneHeight);

/** (try to) add transaction to memory pool
 * plTxnReplaced will be appended to with all transactions replaced from mempool **/
bool AcceptToMemoryPool(CTxMemPool& pool, CValidationState &state, const CTransactionRef &tx,
                        bool* pfMissingInputs, std::list<CTransactionRef>* plTxnReplaced,
                        bool bypass_limits, const CAmount nAbsurdFee);

/** Convert CValidationState to a human-readable message for logging */
std::string FormatStateMessage(const CValidationState &state);

/** Get the BIP9 state for a given deployment at the current tip. */
ThresholdState VersionBitsTipState(const Consensus::Params& params, Consensus::DeploymentPos pos);

/** Get the numerical statistics for the BIP9 state for a given deployment at the current tip. */
BIP9Stats VersionBitsTipStatistics(const Consensus::Params& params, Consensus::DeploymentPos pos);

/** Get the block height at which the BIP9 deployment switched into the state for the block building on the current tip. */
int VersionBitsTipStateSinceHeight(const Consensus::Params& params, Consensus::DeploymentPos pos);


/** Apply the effects of this transaction on the UTXO set represented by view */
void UpdateCoins(const CTransaction& tx, CCoinsViewCache& inputs, int nHeight);

/** Transaction validation functions */

/**
 * Check if transaction will be final in the next block to be created.
 *
 * Calls IsFinalTx() with current block height and appropriate block time.
 *
 * See consensus/consensus.h for flag definitions.
 */
bool CheckFinalTx(const CTransaction &tx, int flags = -1);

/**
 * Test whether the LockPoints height and time are still valid on the current chain
 */
bool TestLockPointValidity(const LockPoints* lp);

/**
 * Check if transaction will be BIP 68 final in the next block to be created.
 *
 * Simulates calling SequenceLocks() with data from the tip of the current active chain.
 * Optionally stores in LockPoints the resulting height and time calculated and the hash
 * of the block needed for calculation or skips the calculation and uses the LockPoints
 * passed in for evaluation.
 * The LockPoints should not be considered valid if CheckSequenceLocks returns false.
 *
 * See consensus/consensus.h for flag definitions.
 */
bool CheckSequenceLocks(const CTransaction &tx, int flags, LockPoints* lp = nullptr, bool useExistingLockPoints = false);

/**
 * Closure representing one script verification
 * Note that this stores references to the spending transaction 
 */
class CScriptCheck
{
private:
    CTxOut m_tx_out;
    const CTransaction *ptxTo;
    unsigned int nIn;
    unsigned int nFlags;
    bool cacheStore;
    ScriptError error;
    PrecomputedTransactionData *txdata;

public:
    CScriptCheck(): ptxTo(nullptr), nIn(0), nFlags(0), cacheStore(false), error(SCRIPT_ERR_UNKNOWN_ERROR) {}
    CScriptCheck(const CTxOut& outIn, const CTransaction& txToIn, unsigned int nInIn, unsigned int nFlagsIn, bool cacheIn, PrecomputedTransactionData* txdataIn) :
        m_tx_out(outIn), ptxTo(&txToIn), nIn(nInIn), nFlags(nFlagsIn), cacheStore(cacheIn), error(SCRIPT_ERR_UNKNOWN_ERROR), txdata(txdataIn) { }

    bool operator()();

    void swap(CScriptCheck &check) {
        std::swap(ptxTo, check.ptxTo);
        std::swap(m_tx_out, check.m_tx_out);
        std::swap(nIn, check.nIn);
        std::swap(nFlags, check.nFlags);
        std::swap(cacheStore, check.cacheStore);
        std::swap(error, check.error);
        std::swap(txdata, check.txdata);
    }

    ScriptError GetScriptError() const { return error; }
};

/** Initializes the script-execution cache */
void InitScriptExecutionCache();


/** Functions for disk access for blocks */
bool ReadBlockFromDisk(CBlock& block, const CDiskBlockPos& pos, const Consensus::Params& consensusParams, bool isProofOfStake);
bool ReadBlockFromDisk(CBlock& block, const CBlockIndex* pindex, const Consensus::Params& consensusParams);

/** Functions for validating blocks and updating the block tree */

/** Context-independent validity checks */
bool CheckBlock(const CBlock& block, CValidationState& state, const Consensus::Params& consensusParams, bool fCheckPOW = true, bool fCheckMerkleRoot = true);

/** Check a block is completely valid from start to finish (only works on top of our current best block, with cs_main held) */
bool TestBlockValidity(CValidationState& state, const CChainParams& chainparams, const CBlock& block, CBlockIndex* pindexPrev, bool fCheckPOW = true, bool fCheckMerkleRoot = true, bool fProofOfStake = false);

/** Check whether witness commitments are required for block. */
bool IsWitnessEnabled(const CBlockIndex* pindexPrev, const Consensus::Params& params);

/** When there are blocks in the active chain with missing data, rewind the chainstate and remove them from the block index */
bool RewindBlockIndex(const CChainParams& params);

/** Update uncommitted block structures (currently: only the witness nonce). This is safe for submitted blocks. */
void UpdateUncommittedBlockStructures(CBlock& block, const CBlockIndex* pindexPrev, const Consensus::Params& consensusParams);

/** Produce the necessary coinbase commitment for a block (modifies the hash, don't call for mined blocks). */
std::vector<unsigned char> GenerateCoinbaseCommitment(CBlock& block, const CBlockIndex* pindexPrev, const Consensus::Params& consensusParams);

/** Check PoS block signature. */
bool CheckBlockSignature(const CBlock& block);

/** RAII wrapper for VerifyDB: Verify consistency of the block and coin databases */
class CVerifyDB {
public:
    CVerifyDB();
    ~CVerifyDB();
    bool VerifyDB(const CChainParams& chainparams, CCoinsView *coinsview, int nCheckLevel, int nCheckDepth);
};

/** Replay blocks that aren't fully applied to the database. */
bool ReplayBlocks(const CChainParams& params, CCoinsView* view);

/** Find the last common block between the parameter chain and a locator. */
CBlockIndex* FindForkInGlobalIndex(const CChain& chain, const CBlockLocator& locator);

/** Mark a block as precious and reorganize. */
bool PreciousBlock(CValidationState& state, const CChainParams& params, CBlockIndex *pindex);

/** Mark a block as invalid. */
bool InvalidateBlock(CValidationState& state, const CChainParams& chainparams, CBlockIndex *pindex);

/** Remove invalidity status from a block and its descendants. */
bool ResetBlockFailureFlags(CBlockIndex *pindex);

/** The currently-connected chain of blocks (protected by cs_main). */
extern CChain& chainActive;

/** Global variable that points to the coins database (protected by cs_main) */
extern std::unique_ptr<CCoinsViewDB> pcoinsdbview;

/** Global variable that points to the active CCoinsView (protected by cs_main) */
extern std::unique_ptr<CCoinsViewCache> pcoinsTip;

/** Global variable that points to the active block tree (protected by cs_main) */
extern std::unique_ptr<CBlockTreeDB> pblocktree;

/** Get the PoW height of a block */ 
int GetPowHeight(const CBlockIndex* pindex);

/**
 * Return the spend height, which is one more than the inputs.GetBestBlock().
 * While checking, GetBestBlock() refers to the parent block. (protected by cs_main)
 * This is also true for mempool checks.
 */
int GetSpendHeight(const CCoinsViewCache& inputs);

extern VersionBitsCache versionbitscache;

/**
 * Determine what nVersion a new block should use.
 */
int32_t ComputeBlockVersion(const CBlockIndex* pindexPrev, const Consensus::Params& params);

/** Reject codes greater or equal to this can be returned by AcceptToMemPool
 * for transactions, to signal internal conditions. They cannot and should not
 * be sent over the P2P network.
 */
static const unsigned int REJECT_INTERNAL = 0x100;
/** Too high fee. Can not be triggered by P2P transactions */
static const unsigned int REJECT_HIGHFEE = 0x100;

/** Get block file info entry for one block file */
CBlockFileInfo* GetBlockFileInfo(size_t n);

/** Dump the mempool to disk. */
bool DumpMempool();

/** Load the mempool from disk. */
bool LoadMempool();

bool GetCoinAge(uint64_t& nCoinAge, const CTransaction *tx);

CAmount GetProofOfStakeReward(int64_t nCoinAge, const CBlockIndex* pindex);
CAmount GetProofOfWorkReward(int nHeight, const CBlockIndex* pindex);

/** Scan blockchain and get its hash */
extern int blockchainStatus;
//extern int blockchainStatusLast;
extern bool fAbortScanForHash;
void ScanBlockchainForHash(bool bSplashDisplay = false);

class MultisigTxInfo
{
private:
	std::string		tx;
	int				signedCount;
	std::string		txidSender;
	std::string		txidMixer;	
	std::string		txidGuarantor;
	int				voutNSender;
	int				voutNMixer;
	int				voutNGuarantor;
	std::string		sPubKeySender;
	std::string		sPubKeyMixer;	
	std::string		sPubKeyGuarantor;
	CAmount			amountSender;
	CAmount			amountMixer;
	CAmount			amountGuarantor;
	
public:
	MultisigTxInfo()
	{
		tx = "";
		signedCount = 0;
		txidSender = "";
		txidMixer = "";
		txidGuarantor = "";
		voutNSender = 0;
		voutNMixer = 0;
		voutNGuarantor = 0;
		sPubKeySender = "";
		sPubKeyMixer = "";
		sPubKeyGuarantor = "";
		amountSender = 0;
		amountMixer = 0;
		amountGuarantor = 0;
	}

	void clean()
	{
		tx = "";
		signedCount = 0;
		txidSender = "";
		txidMixer = "";
		txidGuarantor = "";
		voutNSender = 0;
		voutNMixer = 0;
		voutNGuarantor = 0;
		sPubKeySender = "";
		sPubKeyMixer = "";
		sPubKeyGuarantor = "";
		amountSender = 0;
		amountMixer = 0;
		amountGuarantor = 0;
	}

	std::string GetTx() const
	{
		return tx;
	}

	int GetSignedCount() const
	{
		return signedCount;
	}

	std::string GetTxid(AnonymousTxRole role) const
	{
		std::string txid = "";

		switch (role)
		{
			case ROLE_SENDER:
				txid = txidSender;
				break;

			case ROLE_MIXER:
				txid = txidMixer;
				break;

			case ROLE_GUARANTOR:
				txid = txidGuarantor;
				break;
				
			case ROLE_UNKNOWN:
				break;
		}

		return txid;
	}

	void GetTxOutInfo(AnonymousTxRole role, std::string& txid, int& voutn, std::string& pubkey, CAmount& amount) const
	{
		txid = "";
		voutn = 0;
		pubkey = "";

		switch (role)
		{
			case ROLE_SENDER:
				txid = txidSender;
				voutn = voutNSender;
				pubkey = sPubKeySender;
				amount = amountSender;
				break;

			case ROLE_MIXER:
				txid = txidMixer;
				voutn = voutNMixer;
				pubkey = sPubKeyMixer;
				amount = amountMixer;
				break;

			case ROLE_GUARANTOR:
				txid = txidGuarantor;
				voutn = voutNGuarantor;
				pubkey = sPubKeyGuarantor;
				amount = amountGuarantor;
				break;
				
			case ROLE_UNKNOWN:
				break;
		}
	}

	void SetTxid(AnonymousTxRole role, std::string txid)
	{
		switch (role)
		{
			case ROLE_SENDER:
				txidSender = txid;
				break;

			case ROLE_MIXER:
				txidMixer = txid;
				break;

			case ROLE_GUARANTOR:
				txidGuarantor = txid;
				break;
				
			case ROLE_UNKNOWN:
				break;
		}
	}

	void SetVoutAndScriptPubKey(AnonymousTxRole role, int voutn, std::string scriptPubKey, CAmount amount)
	{
		switch (role)
		{
			case ROLE_SENDER:
				voutNSender = voutn;
				sPubKeySender = scriptPubKey;
				amountSender = amount;
				break;

			case ROLE_MIXER:
				voutNMixer = voutn;
				sPubKeyMixer = scriptPubKey;
				amountMixer = amount;
				break;

			case ROLE_GUARANTOR:
				voutNGuarantor = voutn;
				sPubKeyGuarantor = scriptPubKey;
				amountGuarantor = amount;
				break;
				
			case ROLE_UNKNOWN:
				break;
		}
	}

	void SetTx(std::string tx0, int scount)
	{
		tx = tx0;
		signedCount = scount;
	}

	bool IsTxidComplete() const
	{
		bool b = (txidSender != "") && (txidMixer != "") && (txidGuarantor != "");
		return b;
	}
};

class AnonymousTxParties
{
private:
	AnonymousTxRole	role;
	CNode*	pSender;
	CNode*	pMixer;
	CNode*	pGuarantor;
	std::string	addressSender;
	std::string	addressMixer;
	std::string	addressGuarantor;
	std::string	pubKeySender;
	std::string	pubKeyMixer;
	std::string	pubKeyGuarantor;

public:
	AnonymousTxParties()
	{
		pSender = NULL;
		pMixer = NULL;
		pGuarantor = NULL;
		role = ROLE_UNKNOWN;
		addressSender = "";
		addressMixer = "";
		addressGuarantor = "";
		pubKeySender = "";
		pubKeyMixer = "";
		pubKeyGuarantor = "";
	}

	AnonymousTxRole GetRole() const
	{
		return role;
	}

	std::string GetSelfAddress() const
	{
		return GetAddress(role);
	}

	std::string GetAddress(AnonymousTxRole role0) const
	{
		std::string address = "";

		switch (role0)
		{
			case ROLE_SENDER:
				address = addressSender;
				break;

			case ROLE_MIXER:
				address = addressMixer;
				break;

			case ROLE_GUARANTOR:
				address = addressGuarantor;
				break;
				
			case ROLE_UNKNOWN:
				break;
		}

		return address;
	}

	std::string GetSelfPubKey() const
	{
		std::string pubKey = "";

		switch (role)
		{
			case ROLE_SENDER:
				pubKey = pubKeySender;
				break;

			case ROLE_MIXER:
				pubKey = pubKeyMixer;
				break;

			case ROLE_GUARANTOR:
				pubKey = pubKeyGuarantor;
				break;
				
			case ROLE_UNKNOWN:
				break;
		}

		return pubKey;
	}

	CNode* GetNode(AnonymousTxRole role0) const
	{
		CNode* pN = NULL;
		switch (role0)
		{
			case ROLE_SENDER:
				pN = pSender;
				break;

			case ROLE_MIXER:
				pN = pMixer;
				break;

			case ROLE_GUARANTOR:
				pN = pGuarantor;
				break;
				
			case ROLE_UNKNOWN:
				break;
		}

		return pN;
	}

	std::vector<std::string> GetAllPubKeys() const
	{
		std::vector<std::string> vec;
		vec.push_back(pubKeySender);
		vec.push_back(pubKeyMixer);
		vec.push_back(pubKeyGuarantor);
		return vec;
	}

	void SetRole(AnonymousTxRole r)
	{
		role = r;
	}

	void SetNode(AnonymousTxRole role0, CNode* pN)
	{
		switch (role0)
		{
			case ROLE_SENDER:
				pSender = pN;
				break;

			case ROLE_MIXER:
				pMixer = pN;
				break;

			case ROLE_GUARANTOR:
				pGuarantor = pN;
				break;
				
			case ROLE_UNKNOWN:
				break;
		}
	}

	void SetAddressAndPubKey(AnonymousTxRole role0, std::string addr, std::string key)
	{
		switch (role0)
		{
			case ROLE_SENDER:
				addressSender = addr;
				pubKeySender = key;
				break;

			case ROLE_MIXER:
				addressMixer = addr;
				pubKeyMixer = key;
				break;

			case ROLE_GUARANTOR:
				addressGuarantor = addr;
				pubKeyGuarantor = key;
				break;
				
			case ROLE_UNKNOWN:
				break;
		}
	}

	bool IsPubKeyComplete() const
	{
		bool b = (pubKeySender != "") && (pubKeyMixer != "") && (pubKeyGuarantor != "");
		return b;
	}

	void clean()
	{
		pSender = NULL;
		pMixer = NULL;
		pGuarantor = NULL;
		role = ROLE_UNKNOWN;
		addressSender = "";
		addressMixer = "";
		addressGuarantor = "";
		pubKeySender = "";
		pubKeyMixer = "";
		pubKeyGuarantor = "";
	}
};


class CAnonymousTxInfo
{
public:
	CAnonymousTxInfo();
	virtual void clean(bool clearLog);

	bool IsNull() const
	{
		return (status == ATX_STATUS_NONE);
	}

	std::pair<std::string, int64_t> GetValue(int i)
	{
		return vecSendInfo.at(i);
	}

	int64_t GetLastActivityTime() const
	{
		return lastActivityTime;
	}

	const CCoinControl*	GetCoinControl() const
	{
		return pCoinControl;
	}

	AnonymousTxRole GetRole() const
	{
		return pParties->GetRole();
	}

	std::string GetSelfAddress() const
	{
		return pParties->GetSelfAddress();
	}

	int GetSize() const
	{
		return size;
	}

	std::string GetTx() const
	{
		return pMultiSigDistributionTx->GetTx();
	}

	std::vector< std::pair<std::string, int64_t> > GetSendInfo() const
	{
		return vecSendInfo;
	}

	std::string GetAddress(AnonymousTxRole role) const
	{
		return pParties->GetAddress(role);
	}

	std::string GetSelfPubKey() const
	{
		return pParties->GetSelfPubKey();
	}

	std::string GetAnonymousId() const
	{
		return anonymousId;
	}

	AnonymousTxStatus GetAtxStatus() const
	{
		return status;
	}

	CNode* GetNode(AnonymousTxRole role) const
	{
		return pParties->GetNode(role);
	}

	std::string GetNodeIpAddress(AnonymousTxRole role) const;

	std::vector<std::string> GetAllPubKeys() const
	{
		return pParties->GetAllPubKeys();
	}

	std::string GetMultiSigAddress() const
	{
		return multiSigAddress;
	}

	std::string GetRedeemScript() const
	{
		return redeemScript;
	}

	std::string GetTxid(AnonymousTxRole role) const
	{
		return pMultiSigDistributionTx->GetTxid(role);
	}

	int GetSignedCount() const
	{
		return pMultiSigDistributionTx->GetSignedCount();
	}

	void GetMultisigTxOutInfo(AnonymousTxRole role, std::string& txid, int& voutn, std::string& pubkey, CAmount& amount) const
	{
		pMultiSigDistributionTx->GetTxOutInfo(role, txid, voutn, pubkey, amount);
	}

	std::string GetCommittedMsTx() const
	{
		return committedMsTx;
	}
	
	void SetSendTx(std::string tx)
	{
		sendTx = tx;
	}

	std::string GetSendTx()
    {
        return sendTx;
    }

	void SetNode(AnonymousTxRole role, CNode* pN)
	{
		pParties->SetNode(role, pN);
	}

	void SetVoutAndScriptPubKey(AnonymousTxRole role, int vout, std::string pubkey, CAmount amount)
	{
		pMultiSigDistributionTx->SetVoutAndScriptPubKey(role, vout, pubkey, amount);
	}

    void SetCancelled(bool c) {
	    cancelled = c;
	}

	void SetLastActivityTime();
	void SetAnonymousId(std::string aId);
	void SetCommittedMsTx(std::string tx);
	void SetAddressAndPubKey(AnonymousTxRole role, std::string address, std::string key);
	void SetTxid(AnonymousTxRole role, std::string txid);
	void SetMultiSigAddress(std::string multiSigAddress0, std::string redeemScript0);
	void SetTx(std::string tx, int sc);
	void SetNewData(std::string anonymousId0, CNode* pMixerNode, CNode* pGuarantorNode);
	bool SetInitialData(AnonymousTxRole role, std::vector< std::pair<std::string, int64_t> > vecSendInfo, const CCoinControl* pCoinControl,
		CNode* pSendNode, CNode* pMixerNode, CNode* pGuarantorNode);
	bool CanReset() const;
	bool ShouldCancelRunawayProcess() const;
	CAmount GetTotalRequiredCoinsToSend(AnonymousTxRole role = ROLE_UNKNOWN);
	
	bool CheckSenderDepositTx();
	bool CheckDepositTxes();
	bool CheckSendTx();
	bool IsCurrentTxInProcess() const;
	void AddToLog(std::string text);
	std::string GetLastAnonymousTxLog();

private:
	bool CheckDeposit(AnonymousTxRole role, CWallet* pWallet);
	CAmount GetDepositedAmount(CTransaction tx);

	AnonymousTxStatus			status;		
	std::string					anonymousId;
	AnonymousTxParties*			pParties;
	int64_t						lastActivityTime;
	int							size;
	const CCoinControl*			pCoinControl;
	std::string					multiSigAddress;
	std::string					redeemScript;
	std::string					sendTx;
	MultisigTxInfo*				pMultiSigDistributionTx;
	std::string					committedMsTx;

	std::vector< std::pair<std::string, int64_t> > vecSendInfo;
	std::vector<std::string>	logs;
	bool                        cancelled;
};


static const int MAX_ALLOWED_ASLIST_SIZE = 32;
extern CAnonymousTxInfo* pCurrentAnonymousTxInfo;
extern std::map<std::string, std::string> mapAnonymousServices;

/** DeepSend related function */
bool AddPrevTxOut(AnonymousTxRole role, CBasicKeyStore& tempKeystore, CCoinsViewCache& view);
bool CheckAnonymousServiceConditions();
bool CreateMultiSigAddress();
std::string CreateMultiSigDistributionTx();
std::string CreateCancelDistributionTx(bool);
bool DepositToMultisig(std::string& txid, CConnman *connman);
bool ExtractVoutAndScriptPubKey(AnonymousTxRole role, std::string txid, int& voutn, std::string& hexScriptPubKey);
bool FindGuarantorKey(std::map<std::string, std::string> mapSnList, std::string& guarantorKey);
CAmount GetAvailableBalance();
std::string GetConnectedIP(std::string key);
bool IsCurrentAnonymousTxInProcess();
bool SelectAnonymousServiceMixNode(CNode*& pMixerNode, std::string& keyMixer, int cnt, CConnman *connman);
bool SendCoinsToDestination(std::string& txid, CConnman *connman);
bool SendMultiSigDistributionTx(CConnman *connman);
bool SignMessageUsingAddress(std::string message, std::string address, std::vector<unsigned char>& vchSig);
bool SignMultiSigDistributionTx();
bool StartP2pMixerSendProcess(std::vector< std::pair<std::string, CAmount> > vecSendInfo, const CCoinControl *coinControl);
void UpdateAnonymousServiceList(CNode* pNode, std::string keyAddress, std::string status, CConnman *connman);
bool VerifyMessageSignature(std::string message, std::string address, std::vector<unsigned char> vchSig);

#endif // BITCOIN_VALIDATION_H
