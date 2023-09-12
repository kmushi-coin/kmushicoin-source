// Copyright (c) 2020 The PIVX developers
// Copyright (c) 2019-2021 The KTV developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://www.opensource.org/licenses/mit-license.php.

#include "wallet/test/pos_test_fixture.h"

#include "blockassembler.h"
#include "util/blockstatecatcher.h"
#include "blocksignature.h"
#include "consensus/merkle.h"
#include "primitives/block.h"
#include "script/sign.h"
#include "test/util/blocksutil.h"
#include "wallet/wallet.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(pos_validations_tests)

void reSignTx(CMutableTransaction& mtx,
              const std::vector<CTxOut>& txPrevOutputs,
              CWallet* wallet)
{
    CTransaction txNewConst(mtx);
    for (int index=0; index < (int) txPrevOutputs.size(); index++) {
        const CTxOut& prevOut = txPrevOutputs.at(index);
        SignatureData sigdata;
        BOOST_ASSERT(ProduceSignature(
                TransactionSignatureCreator(wallet, &txNewConst, index, prevOut.nValue, SIGHASH_ALL),
                prevOut.scriptPubKey,
                sigdata,
                txNewConst.GetRequiredSigVersion(),
                true));
        UpdateTransaction(mtx, index, sigdata);
    }
}

BOOST_FIXTURE_TEST_CASE(coinstake_tests, TestPoSChainSetup)
{
    // Verify that we are at block 251
    BOOST_CHECK_EQUAL(WITH_LOCK(cs_main, return chainActive.Tip()->nHeight), 250);
    SyncWithValidationInterfaceQueue();

    // Let's create the block
    std::vector<CStakeableOutput> availableCoins;
    BOOST_CHECK(pwalletMain->StakeableCoins(&availableCoins));
    std::unique_ptr<CBlockTemplate> pblocktemplate = BlockAssembler(
            Params(), false).CreateNewBlock(CScript(),
                                            pwalletMain.get(),
                                            true,
                                            &availableCoins,
                                            true);
    std::shared_ptr<CBlock> pblock = std::make_shared<CBlock>(pblocktemplate->block);
    BOOST_CHECK(pblock->IsProofOfStake());

    // Add a second input to a coinstake
    CMutableTransaction mtx(*pblock->vtx[1]);
    const CStakeableOutput& in2 = availableCoins.back();
    availableCoins.pop_back();
    CTxIn vin2(in2.tx->GetHash(), in2.i);
    mtx.vin.emplace_back(vin2);

    CTxOut prevOutput1 = pwalletMain->GetWalletTx(mtx.vin[0].prevout.hash)->tx->vout[mtx.vin[0].prevout.n];
    std::vector<CTxOut> txPrevOutputs{prevOutput1, in2.tx->tx->vout[in2.i]};

    reSignTx(mtx, txPrevOutputs, pwalletMain.get());
    pblock->vtx[1] = MakeTransactionRef(mtx);
    pblock->hashMerkleRoot = BlockMerkleRoot(*pblock);
    BOOST_CHECK(SignBlock(*pblock, *pwalletMain));
    ProcessBlockAndCheckRejectionReason(pblock, "bad-cs-multi-inputs", 250);

    // Check multi-empty-outputs now
    pblock = std::make_shared<CBlock>(pblocktemplate->block);
    mtx = CMutableTransaction(*pblock->vtx[1]);
    for (int i = 0; i < 999; ++i) {
        mtx.vout.emplace_back();
        mtx.vout.back().SetEmpty();
    }
    reSignTx(mtx, {prevOutput1}, pwalletMain.get());
    pblock->vtx[1] = MakeTransactionRef(mtx);
    pblock->hashMerkleRoot = BlockMerkleRoot(*pblock);
    BOOST_CHECK(SignBlock(*pblock, *pwalletMain));
    ProcessBlockAndCheckRejectionReason(pblock, "bad-txns-vout-empty", 250);

    // Now connect the proper block
    pblock = std::make_shared<CBlock>(pblocktemplate->block);
    ProcessNewBlock(pblock, nullptr);
    BOOST_CHECK_EQUAL(WITH_LOCK(cs_main, return chainActive.Tip()->GetBlockHash()), pblock->GetHash());
}

BOOST_AUTO_TEST_SUITE_END()
