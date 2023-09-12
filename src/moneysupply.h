// Copyright (c) 2020 The PIVX developers
// Copyright (c) 2019-2021 The KTV developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or https://www.opensource.org/licenses/mit-license.php.

#ifndef KTV_MONEYSUPPLY_H
#define KTV_MONEYSUPPLY_H

#include "amount.h"
#include "sync.h"

/*
 * Class used to cache the sum of utxo's values
 */
class CMoneySupply {
private:
    mutable RecursiveMutex cs;
    CAmount nSupply;
    // height of the chain when the supply was last updated
    int64_t nHeight;

public:
    CMoneySupply(): nSupply(0), nHeight(0) {}

    void Update(const CAmount& _nSupply, int _nHeight)
    {
        LOCK(cs);
        nSupply = _nSupply;
        nHeight = _nHeight;
    }

    CAmount Get() const { LOCK(cs); return nSupply; }
    int64_t GetCacheHeight() const { LOCK(cs); return nHeight; }
};

#endif // KTV_MONEYSUPPLY_H
