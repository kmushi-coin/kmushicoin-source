// Copyright (c) 2019-2020 The PIVX developers
// Copyright (c) 2019-2021 The KTV developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SENDCUSTOMFEEDIALOG_H
#define SENDCUSTOMFEEDIALOG_H

#include "policy/feerate.h"
#include "qt/ktv/focuseddialog.h"
#include "qt/ktv/snackbar.h"

class KTVGUI;
class WalletModel;

namespace Ui {
class SendCustomFeeDialog;
}

class SendCustomFeeDialog : public FocusedDialog
{
    Q_OBJECT

public:
    explicit SendCustomFeeDialog(KTVGUI* parent, WalletModel* model);
    ~SendCustomFeeDialog();

    void showEvent(QShowEvent* event) override;
    CFeeRate getFeeRate();
    bool isCustomFeeChecked();
    void clear();

public Q_SLOTS:
    void onRecommendedChecked();
    void onCustomChecked();
    void updateFee();
    void onChangeTheme(bool isLightTheme, QString& theme);

protected Q_SLOTS:
    void accept() override;

private:
    Ui::SendCustomFeeDialog* ui;
    WalletModel* walletModel = nullptr;
    CFeeRate feeRate;
    SnackBar* snackBar = nullptr;
    void inform(const QString& text);
};

#endif // SENDCUSTOMFEEDIALOG_H
