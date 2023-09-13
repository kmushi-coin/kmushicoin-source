// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2020 The PIVX developers
// Copyright (c) 2019-2021 The KTV developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "chainparamsseeds.h"
#include "consensus/merkle.h"
#include "tinyformat.h"
#include "utilstrencodings.h"

#include <assert.h>

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.vtx.push_back(std::make_shared<const CTransaction>(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.nVersion = nVersion;
    genesis.nTime = nTime;
    genesis.nBits = nBits;
    genesis.nNonce = nNonce;
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

void CChainParams::UpdateNetworkUpgradeParameters(Consensus::UpgradeIndex idx, int nActivationHeight)
{
    assert(IsRegTestNet()); // only available for regtest
    assert(idx > Consensus::BASE_NETWORK && idx < Consensus::MAX_NETWORK_UPGRADES);
    consensus.vUpgrades[idx].nActivationHeight = nActivationHeight;
}

/**
 * Build the genesis block. Note that the output of the genesis coinbase cannot
 * be spent as it did not originally exist in the database.
 *
 * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
 *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
 *   vMerkleTree: e0028e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "Kmushicoin Evoluciona";
    const CScript genesisOutputScript = CScript() << ParseHex("04c10e83b2703ccf322f7dbd62dd5855ac7c10bd055814ce121ba32607d573b8810c02c0582aed05b4deb9c4b77b26d92428c61256cd42774babea0a073b2ed0c9") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
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
static Checkpoints::MapCheckpoints mapCheckpoints = {
    {0, uint256S("0000096fb6742a7e770f5866fd761a71a97f0aeadcaf13a28bdb98717b6b01e0")},
    {209, uint256S("0000002381714b9d8f0db9f114b175da7222741205b5cdb1d0c9ea70c226822d")},
    {305, uint256S("c41cdc7cd9d8fb798b6f90952bbbf73a317b7959b485ad7723b77388f56c58fd")},
};

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1694386304, // * UNIX timestamp of last checkpoint block
    0,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    200        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet = {
    {0, uint256S("0x001")},
    //{    201, uint256S("6ae7d52092fd918c8ac8d9b1334400387d3057997e6e927a88e57186dc395231")},     // v5 activation (PoS/Sapling)
};

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1454124731,
    0,
    3000};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest = {{0, uint256S("0x001")}};
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1454124731,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        strNetworkID = "main";

        genesis = CreateGenesisBlock(1694219027, 374234, 0x1e0ffff0, 1, 250 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x0000096fb6742a7e770f5866fd761a71a97f0aeadcaf13a28bdb98717b6b01e0"));
        assert(genesis.hashMerkleRoot == uint256S("0xa4c33a1805b1c77faedbf902169d72dfcab38d5debff3379d62ed2dfd208ee41"));

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.powLimit = uint256S("0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.posLimitV1 = uint256S("0x000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.posLimitV2 = uint256S("0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nBudgetCycleBlocks = 43200;  // approx. 1 every 30 days
        consensus.nBudgetFeeConfirmations = 6; // Number of confirmations for the finalization fee
        consensus.nCoinbaseMaturity = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 21000000 * COIN;
        consensus.nMNCollateralAmt = 500 * COIN;
        consensus.nPoolMaxTransactions = 3;
        consensus.nProposalEstablishmentTime = 60 * 60 * 24; // must be at least a day old to make it into a budget
        consensus.nStakeMinAge = 60 * 60;
        consensus.nStakeMinDepth = 100;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;
        consensus.nMaxProposalPayments = 6;

        // spork keys
        consensus.strSporkPubKey = "04eb4a35342135eabf6e5974ac98ca2f9746957a24972e5b667ea8c883e2ff674956d6f044c852a7646ce55a8d037592d2fd89cb79213b4e428bd3f1ee6ccc6909";
        consensus.strSporkPubKeyOld = "04031614d3640b94844ad3139ee8cd62e6c7937ce10e7fc3e56bac50f039d5c3143d4aff458879357312845f78fbd19600f8c55ffe6c1a5c01b16ebd6c72455c41";
        consensus.nTime_EnforceNewSporkKey = 1639699200; //!> Friday, December 17, 2021 12:00:00 AM
        consensus.nTime_RejectOldSporkKey = 1641254400;  //!> Tuesday, January 4, 2022 12:00:00 AM

        // height-based activations
        consensus.height_last_invalid_UTXO = 99999999;
        consensus.height_last_ZC_AccumCheckpoint = 99999999;
        consensus.height_last_ZC_WrappedSerials = 99999999;
        consensus.height_ZC_RecalcAccumulators = 99999999;

        // validation by-pass
        consensus.nKtvBadBlockTime = 1471401614; // Skip nBit validation of Block 259201 per PR #915
        consensus.nKtvBadBlockBits = 0x1c056dac; // Skip nBit validation of Block 259201 per PR #915

        // Zerocoin-related params
        consensus.ZC_Modulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
                               "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
                               "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
                               "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
                               "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
                               "31438167899885040445364023527381951378636564391212010397122822120720357";
        consensus.ZC_MaxPublicSpendsPerTx = 637; // Assume about 220 bytes each input
        consensus.ZC_MaxSpendsPerTx = 7;         // Assume about 20kb each input
        consensus.ZC_MinMintConfirmations = 20;
        consensus.ZC_MinMintFee = 1 * CENT;
        consensus.ZC_MinStakeDepth = 200;
        consensus.ZC_TimeStart = 1508214600; // October 17, 2017 4:30:00 AM
        consensus.ZC_HeightStart = 99999999;

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight =
            Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
            Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight = 210;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight = 99999999;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight = 99999999;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight = 99999999;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight = 1;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight = 99999999;
        consensus.vUpgrades[Consensus::UPGRADE_V3_4].nActivationHeight = 210;
        consensus.vUpgrades[Consensus::UPGRADE_V4_0].nActivationHeight = 210;
        consensus.vUpgrades[Consensus::UPGRADE_V5_0].nActivationHeight = 630000;
        consensus.vUpgrades[Consensus::UPGRADE_V5_2].nActivationHeight = 99999999;
        consensus.vUpgrades[Consensus::UPGRADE_V5_3].nActivationHeight = 99999999;
        consensus.vUpgrades[Consensus::UPGRADE_V6_0].nActivationHeight =
            Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;

        /*consensus.vUpgrades[Consensus::UPGRADE_ZC].hashActivationBlock =
                uint256S("0x5b2482eca24caf2a46bb22e0545db7b7037282733faa3a42ec20542509999a64");
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].hashActivationBlock =
                uint256S("0x37ea75fe1c9314171cff429a91b25b9f11331076d1c9de50ee4054d61877f8af");*/
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock =
            uint256S("000001cedeedf270ca8568a3902903b0813aa1c4e49edfc61031e2cd9a899854");
        //consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].hashActivationBlock =
        //        uint256S("0xe2448b76d88d37aba4194ffed1041b680d779919157ddf5cbf423373d7f8078e");
        consensus.vUpgrades[Consensus::UPGRADE_V3_4].hashActivationBlock =
            uint256S("261b6d1ff5900d87517dc5341dd037975e20fabd57f0dcd9d46b7c6da224cd4e");
        consensus.vUpgrades[Consensus::UPGRADE_V4_0].hashActivationBlock =
            uint256S("261b6d1ff5900d87517dc5341dd037975e20fabd57f0dcd9d46b7c6da224cd4e");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x37;
        pchMessageStart[1] = 0xad;
        pchMessageStart[2] = 0x98;
        pchMessageStart[3] = 0x7f;
        nDefaultPort = 36599;

        vSeeds.emplace_back("dnsseed.kmushicoin.co", true);
        vSeeds.emplace_back("dnsseed.kmushicoin.co", "ghos6.kmushicoin.co", true);
        vSeeds.push_back(CDNSSeedData("node1.kmushicoin.co", "node1.kmushicoin.co"));
        vSeeds.push_back(CDNSSeedData("ghos2.kmushicoin.co", "ghos2.kmushicoin.co"));
        vSeeds.push_back(CDNSSeedData("ghos3.kmushicoin.co", "ghos3.kmushicoin.co"));
        vSeeds.push_back(CDNSSeedData("ghos4.kmushicoin.co", "ghos4.kmushicoin.co"));
        vSeeds.push_back(CDNSSeedData("ghos5.kmushicoin.co", "ghos5.kmushicoin.co"));
        vSeeds.push_back(CDNSSeedData("ghos6.kmushicoin.co", "ghos6.kmushicoin.co"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 46);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 85);
        base58Prefixes[STAKING_ADDRESS] = std::vector<unsigned char>(1, 63); // starting with 'S'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 174);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x88, 0xB2, 0x1E};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x88, 0xB2, 0x1E};
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = {0x80, 0x00, 0x01, 0xab};

        //vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));
        vFixedSeeds.clear();

        // Reject non-standard transactions by default
        fRequireStandard = true;

        // Sapling
        bech32HRPs[SAPLING_PAYMENT_ADDRESS] = "ps";
        bech32HRPs[SAPLING_FULL_VIEWING_KEY] = "pviews";
        bech32HRPs[SAPLING_INCOMING_VIEWING_KEY] = "pivks";
        bech32HRPs[SAPLING_EXTENDED_SPEND_KEY] = "p-secret-spending-key-main";
        bech32HRPs[SAPLING_EXTENDED_FVK] = "pxviews";
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};

/**
 * Testnet (v5)
 */
class CTestNetParams : public CChainParams
{
public:
    CTestNetParams()
    {
        strNetworkID = "test";

        genesis = CreateGenesisBlock(1694220380, 2623164, 0x1e0ffff0, 1, 250 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000d3ca2e77d97f4803dc2503440a445e6d9d4540291a6257ee34fa774ce09"));
        assert(genesis.hashMerkleRoot == uint256S("0xa4c33a1805b1c77faedbf902169d72dfcab38d5debff3379d62ed2dfd208ee41"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.powLimit = uint256S("0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.posLimitV1 = uint256S("0x000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.posLimitV2 = uint256S("0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nBudgetCycleBlocks = 144;    // approx 10 cycles per day
        consensus.nBudgetFeeConfirmations = 3; // (only 8-blocks window for finalization on testnet)
        consensus.nCoinbaseMaturity = 15;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 21000000 * COIN;
        consensus.nMNCollateralAmt = 10000 * COIN;
        consensus.nPoolMaxTransactions = 3;
        consensus.nProposalEstablishmentTime = 60 * 5; // at least 5 min old to make it into a budget
        consensus.nStakeMinAge = 60 * 60;
        consensus.nStakeMinDepth = 100;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;
        consensus.nMaxProposalPayments = 20;

        // spork keys
        consensus.strSporkPubKey = "04677c34726c491117265f4b1c83cef085684f36c8df5a97a3a42fc499316d0c4e63959c9eca0dba239d9aaaf72011afffeb3ef9f51b9017811dec686e412eb504";
        consensus.strSporkPubKeyOld = "04E88BB455E2A04E65FCC41D88CD367E9CCE1F5A409BE94D8C2B4B35D223DED9C8E2F4E061349BA3A38839282508066B6DC4DB72DD432AC4067991E6BF20176127";
        consensus.nTime_EnforceNewSporkKey = 1608512400; //!> December 21, 2020 01:00:00 AM GMT
        consensus.nTime_RejectOldSporkKey = 1614560400;  //!> March 1, 2021 01:00:00 AM GMT

        // height based activations
        consensus.height_last_invalid_UTXO = -1;
        consensus.height_last_ZC_AccumCheckpoint = -1;
        consensus.height_last_ZC_WrappedSerials = -1;
        consensus.height_ZC_RecalcAccumulators = 999999999;
        consensus.ZC_HeightStart = 0;

        // Zerocoin-related params
        consensus.ZC_Modulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
                               "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
                               "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
                               "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
                               "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
                               "31438167899885040445364023527381951378636564391212010397122822120720357";
        consensus.ZC_MaxPublicSpendsPerTx = 637; // Assume about 220 bytes each input
        consensus.ZC_MaxSpendsPerTx = 7;         // Assume about 20kb each input
        consensus.ZC_MinMintConfirmations = 20;
        consensus.ZC_MinMintFee = 1 * CENT;
        consensus.ZC_MinStakeDepth = 200;
        consensus.ZC_TimeStart = 1508214600; // October 17, 2017 4:30:00 AM

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight =
            Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
            Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight = 201;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight = 201;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight = 201;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight = 201;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight = 201;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight = 201;
        consensus.vUpgrades[Consensus::UPGRADE_V3_4].nActivationHeight = 201;
        consensus.vUpgrades[Consensus::UPGRADE_V4_0].nActivationHeight = 201;
        consensus.vUpgrades[Consensus::UPGRADE_V5_0].nActivationHeight = 201;
        consensus.vUpgrades[Consensus::UPGRADE_V5_2].nActivationHeight = 262525;
        consensus.vUpgrades[Consensus::UPGRADE_V5_3].nActivationHeight = 332300;
        consensus.vUpgrades[Consensus::UPGRADE_V6_0].nActivationHeight =
            Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x22;
        pchMessageStart[1] = 0xd0;
        pchMessageStart[2] = 0x6e;
        pchMessageStart[3] = 0x13;
        nDefaultPort = 51474;

        // nodes with support for servicebits filtering should be at the top

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet ktv addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet ktv script addresses start with '8' or '9'
        base58Prefixes[STAKING_ADDRESS] = std::vector<unsigned char>(1, 73); // starting with 'W'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet ktv BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = {0x3a, 0x80, 0x61, 0xa0};
        // Testnet ktv BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = {0x3a, 0x80, 0x58, 0x37};
        // Testnet ktv BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = {0x80, 0x00, 0x00, 0x01};

        vFixedSeeds = std::vector<uint8_t>(std::begin(chainparams_seed_test), std::end(chainparams_seed_test));

        fRequireStandard = false;

        // Sapling
        bech32HRPs[SAPLING_PAYMENT_ADDRESS] = "ptestsapling";
        bech32HRPs[SAPLING_FULL_VIEWING_KEY] = "pviewtestsapling";
        bech32HRPs[SAPLING_INCOMING_VIEWING_KEY] = "pivktestsapling";
        bech32HRPs[SAPLING_EXTENDED_SPEND_KEY] = "p-secret-spending-key-test";
        bech32HRPs[SAPLING_EXTENDED_FVK] = "pxviewtestsapling";
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};

/**
 * Regression test
 */
class CRegTestParams : public CChainParams
{
public:
    CRegTestParams()
    {
        strNetworkID = "regtest";

        genesis = CreateGenesisBlock(1694220512, 12345, 0x207fffff, 1, 250 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x0ac13933e387aa36bef63fda6328c99a4be362178d603a79d8b6e6a6eb75c234"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.powLimit = uint256S("0x7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.posLimitV1 = uint256S("0x000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.posLimitV2 = uint256S("0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nBudgetCycleBlocks = 144;    // approx 10 cycles per day
        consensus.nBudgetFeeConfirmations = 3; // (only 8-blocks window for finalization on regtest)
        consensus.nCoinbaseMaturity = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 43199500 * COIN;
        consensus.nMNCollateralAmt = 100 * COIN;
        consensus.nPoolMaxTransactions = 2;
        consensus.nProposalEstablishmentTime = 60 * 5; // at least 5 min old to make it into a budget
        consensus.nStakeMinAge = 0;
        consensus.nStakeMinDepth = 2;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;
        consensus.nMaxProposalPayments = 20;

        /* Spork Key for RegTest:
        WIF private key: 932HEevBSujW2ud7RfB1YF91AFygbBRQj3de3LyaCRqNzKKgWXi
        private key hex: bd4960dcbd9e7f2223f24e7164ecb6f1fe96fc3a416f5d3a830ba5720c84b8ca
        Address: yCvUVd72w7xpimf981m114FSFbmAmne7j9
        */
        consensus.strSporkPubKey = "043969b1b0e6f327de37f297a015d37e2235eaaeeb3933deecd8162c075cee0207b13537618bde640879606001a8136091c62ec272dd0133424a178704e6e75bb7";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // height based activations
        consensus.height_last_invalid_UTXO = -1;
        consensus.height_last_ZC_AccumCheckpoint = 310; // no checkpoints on regtest
        consensus.height_last_ZC_WrappedSerials = -1;
        consensus.height_ZC_RecalcAccumulators = 999999999;

        // Zerocoin-related params
        consensus.ZC_Modulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
                               "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
                               "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
                               "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
                               "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
                               "31438167899885040445364023527381951378636564391212010397122822120720357";
        consensus.ZC_MaxPublicSpendsPerTx = 637; // Assume about 220 bytes each input
        consensus.ZC_MaxSpendsPerTx = 7;         // Assume about 20kb each input
        consensus.ZC_MinMintConfirmations = 10;
        consensus.ZC_MinMintFee = 1 * CENT;
        consensus.ZC_MinStakeDepth = 10;
        consensus.ZC_TimeStart = 0; // not implemented on regtest
        consensus.ZC_HeightStart = 0;

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight =
            Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
            Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight = 251;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight = 251;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight = 300;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight = 300;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight =
            Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight = 400;
        consensus.vUpgrades[Consensus::UPGRADE_V3_4].nActivationHeight = 251;
        consensus.vUpgrades[Consensus::UPGRADE_V4_0].nActivationHeight =
            Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_V5_0].nActivationHeight = 300;
        consensus.vUpgrades[Consensus::UPGRADE_V5_2].nActivationHeight = 300;
        consensus.vUpgrades[Consensus::UPGRADE_V5_3].nActivationHeight = 251;
        consensus.vUpgrades[Consensus::UPGRADE_V6_0].nActivationHeight =
            Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        nDefaultPort = 51476;

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet ktv addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet ktv script addresses start with '8' or '9'
        base58Prefixes[STAKING_ADDRESS] = std::vector<unsigned char>(1, 73); // starting with 'W'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet ktv BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = {0x3a, 0x80, 0x61, 0xa0};
        // Testnet ktv BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = {0x3a, 0x80, 0x58, 0x37};
        // Testnet ktv BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = {0x80, 0x00, 0x00, 0x01};

        // Reject non-standard transactions by default
        fRequireStandard = true;

        // Sapling
        bech32HRPs[SAPLING_PAYMENT_ADDRESS] = "ptestsapling";
        bech32HRPs[SAPLING_FULL_VIEWING_KEY] = "pviewtestsapling";
        bech32HRPs[SAPLING_INCOMING_VIEWING_KEY] = "pivktestsapling";
        bech32HRPs[SAPLING_EXTENDED_SPEND_KEY] = "p-secret-spending-key-test";
        bech32HRPs[SAPLING_EXTENDED_FVK] = "pxviewtestsapling";
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};

static std::unique_ptr<CChainParams> globalChainParams;

const CChainParams& Params()
{
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

void UpdateNetworkUpgradeParameters(Consensus::UpgradeIndex idx, int nActivationHeight)
{
    globalChainParams->UpdateNetworkUpgradeParameters(idx, nActivationHeight);
}
