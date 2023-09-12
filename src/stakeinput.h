// Copyright (c) 2017-2020 The PIVX developers
// Copyright (c) 2019-2021 The KTV developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTV_STAKEINPUT_H
#define KTV_STAKEINPUT_H

#include "chain.h"
#include "streams.h"
#include "uint256.h"

class CKeyStore;
class CWallet;
class CWalletTx;

class CStakeInput
{
protected:
    const CBlockIndex* pindexFrom = nullptr;

public:
    CStakeInput(const CBlockIndex* _pindexFrom) : pindexFrom(_pindexFrom) {}
    virtual ~CStakeInput(){};
    virtual const CBlockIndex* GetIndexFrom() const = 0;
    virtual bool GetTxOutFrom(CTxOut& out) const = 0;
    virtual CAmount GetValue() const = 0;
    virtual bool IsZPIV() const = 0;
    virtual CDataStream GetUniqueness() const = 0;
};


class CKtvStake : public CStakeInput
{
private:
    const CTxOut outputFrom;
    const COutPoint outpointFrom;

public:
    CKtvStake(const CTxOut& _from, const COutPoint& _outPointFrom, const CBlockIndex* _pindexFrom) :
            CStakeInput(_pindexFrom), outputFrom(_from), outpointFrom(_outPointFrom) {}

    static CKtvStake* NewPivStake(const CTxIn& txin, int nHeight, uint32_t nTime);

    const CBlockIndex* GetIndexFrom() const override;
    bool GetTxOutFrom(CTxOut& out) const override;
    CAmount GetValue() const override;
    CDataStream GetUniqueness() const override;
    CTxIn GetTxIn() const;
    bool CreateTxOuts(const CWallet* pwallet, std::vector<CTxOut>& vout, CAmount nTotal) const;
    bool IsZPIV() const override { return false; }
};


#endif //KTV_STAKEINPUT_H
