// Copyright (c) 2018-2020 The PIVX developers
// Copyright (c) 2019-2021 The KTV developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTV_ZKTVCHAIN_H
#define KTV_ZKTVCHAIN_H

#include "chain.h"
#include "libzerocoin/Coin.h"
#include "libzerocoin/Denominations.h"
#include "libzerocoin/CoinSpend.h"
#include <list>
#include <string>

class CBlock;
class CBlockIndex;
class CBigNum;
class CTransaction;
class CTxIn;
class CTxOut;
class CValidationState;
class uint256;

bool IsSerialInBlockchain(const CBigNum& bnSerial, int& nHeightTx);
libzerocoin::CoinSpend TxInToZerocoinSpend(const CTxIn& txin);
bool TxOutToPublicCoin(const CTxOut& txout, libzerocoin::PublicCoin& pubCoin, CValidationState& state);

#endif //KTV_ZKTVCHAIN_H
