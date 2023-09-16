// Copyright (c) 2019 The PIVX developers
// Copyright (c) 2019-2021 The KTV developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SETTINGSINFORMATIONWIDGET_H
#define SETTINGSINFORMATIONWIDGET_H

#include <QWidget>
#include "qt/ktv/pwidget.h"
#include "rpcconsole.h"

namespace Ui {
class SettingsInformationWidget;
}

class SettingsInformationWidget : public PWidget
{
    Q_OBJECT

public:
    explicit SettingsInformationWidget(KTVGUI* _window, QWidget *parent = nullptr);
    ~SettingsInformationWidget() override;

    void loadClientModel() override;

    void run(int type) override;
    void onError(QString error, int type) override;

private Q_SLOTS:
    void setNumConnections(int count);
    void setNumBlocks(int count);
    void showEvent(QShowEvent* event) override;
    void hideEvent(QHideEvent* event) override;

public Q_SLOTS:
    void openNetworkMonitor();
    void setMasternodeCount(const QString& strMasternodes);

private:
    Ui::SettingsInformationWidget *ui;
    RPCConsole *rpcConsole = nullptr;
};

#endif // SETTINGSINFORMATIONWIDGET_H
