// Copyright (c) 2020 The PIVX developers
// Copyright (c) 2019-2021 The KTV developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTV_CONSENSUS_ZEROCOIN_VERIFY_H
#define KTV_CONSENSUS_ZEROCOIN_VERIFY_H

#include "consensus/consensus.h"
#include "script/interpreter.h"
#include "zktvchain.h"

// Fake Serial attack Range
bool isBlockBetweenFakeSerialAttackRange(int nHeight);
// Public coin spend
bool CheckPublicCoinSpendEnforced(int blockHeight, bool isPublicSpend);
bool ContextualCheckZerocoinTx(const CTransactionRef& tx, CValidationState& state, const Consensus::Params& consensus, int nHeight, bool isMined);
bool ContextualCheckZerocoinSpend(const CTransaction& tx, const libzerocoin::CoinSpend* spend, int nHeight);
bool ContextualCheckZerocoinSpendNoSerialCheck(const CTransaction& tx, const libzerocoin::CoinSpend* spend, int nHeight);

// Returns false if coin spend is invalid. Invalidity/DoS causes are treated inside the function.
bool ParseAndValidateZerocoinSpends(const Consensus::Params& consensus,
                                    const CTransaction& tx, int chainHeight,
                                    CValidationState& state,
                                    std::vector<std::pair<CBigNum, uint256>>& vSpendsRet);

#endif //KTV_CONSENSUS_ZEROCOIN_VERIFY_H
