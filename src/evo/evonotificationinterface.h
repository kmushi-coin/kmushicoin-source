// Copyright (c) 2021 The PIVX developers
// Copyright (c) 2019-2021 The KTV developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef EVONOTIFICATIONINTERFACE_H
#define EVONOTIFICATIONINTERFACE_H

#include "validationinterface.h"

class EvoNotificationInterface : public CValidationInterface
{
public:
    explicit EvoNotificationInterface(CConnman& connmanIn): connman(connmanIn) {}
    virtual ~EvoNotificationInterface() = default;

    // a small helper to initialize current block height in sub-modules on startup
    void InitializeCurrentBlockTip();

protected:
    // CValidationInterface
    void UpdatedBlockTip(const CBlockIndex *pindexNew, const CBlockIndex *pindexFork, bool fInitialDownload) override;
    void NotifyMasternodeListChanged(bool undo, const CDeterministicMNList& oldMNList, const CDeterministicMNListDiff& diff) override;

private:
    CConnman& connman;
};

#endif // EVONOTIFICATIONINTERFACE_H
