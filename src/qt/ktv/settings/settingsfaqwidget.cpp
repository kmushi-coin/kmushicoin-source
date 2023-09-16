// Copyright (c) 2019 The PIVX developers
// Copyright (c) 2019-2021 The KTV developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#if defined(HAVE_CONFIG_H)
#include "config/ktv-config.h"
#endif

#include "qt/ktv/settings/settingsfaqwidget.h"
#include "qt/ktv/settings/forms/ui_settingsfaqwidget.h"
#include "clientmodel.h"
#include "qt/ktv/qtutils.h"

#include <QScrollBar>
#include <QMetaObject>
#include <QDesktopServices>

SettingsFaqWidget::SettingsFaqWidget(KTVGUI* parent, ClientModel* _model) :
    QDialog(parent),
    ui(new Ui::SettingsFaqWidget),
    clientModel(_model)
{
    ui->setupUi(this);
    this->setStyleSheet(parent->styleSheet());

#ifdef Q_OS_MAC
    ui->container->load("://bg-welcome");
    setCssProperty(ui->container, "container-welcome-no-image");
#else
    setCssProperty(ui->container, "container-welcome");
#endif
    setCssProperty(ui->labelTitle, "text-title-faq");
    setCssProperty(ui->labelWebLink, "text-content-white");

    // Content
    setCssProperty({
           ui->labelNumber_Intro,
           ui->labelNumber_UnspendableKTV,
           ui->labelNumber_Stake,
           ui->labelNumber_Support,
           ui->labelNumber_Masternode,
           ui->labelNumber_MNController
        }, "container-number-faq");

    setCssProperty({
              ui->labelSubtitle_Intro,
              ui->labelSubtitle_UnspendableKTV,
              ui->labelSubtitle_Stake,
              ui->labelSubtitle_Support,
              ui->labelSubtitle_Masternode,
              ui->labelSubtitle_MNController
            }, "text-subtitle-faq");


    setCssProperty({
              ui->labelContent_Intro,
              ui->labelContent_UnspendableKTV,
              ui->labelContent_Stake,
              ui->labelContent_Support,
              ui->labelContent_Masternode,
              ui->labelContent_MNController
            }, "text-content-faq");


    setCssProperty({
              ui->pushButton_Intro,
              ui->pushButton_UnspendableKTV,
              ui->pushButton_Stake,
              ui->pushButton_Support,
              ui->pushButton_Masternode,
              ui->pushButton_MNController
            }, "btn-faq-options");

    ui->labelContent_Support->setOpenExternalLinks(true);
    ui->labelContent_Intro->setOpenExternalLinks(true);

    // Set FAQ content strings
    QString introContent = formatFAQContent(
        formatFAQParagraph(
            tr("Kmushicoin is a hybrid POS/MN coin that exists with the sole aim of becoming "
               "one the most widely utilized privacy-based coins in the market. The stated "
               "mission of Kmushicoin is to be an open source, scalable, cryptocurrency "
               "that places user privacy of transaction data above all else. ")) +
        formatFAQParagraph(
            tr("We endeavor to make it impossible for a third party to figure out through chain analysis "
               "who the sender and receiver are and the amount of coins that are transferred on the "
               "blockchain when shields are used.  We accomplish this task utilizing masternodes, "
               "coin mixing, shielded addresses, zk-Snarks and The Onion Router (TOR).  "
               "For more information read the Kmushicoin Whitepaper located here %1 ")
                .arg("<a style='color: #ffcc08' href='https://cdn.tierravivaescarabajos.com/WHITE%20PAPER.pdf'>" + tr("https://cdn.tierravivaescarabajos.com/WHITE%20PAPER.pdf") + "</a>.")));
    ui->labelContent_Intro->setText(introContent);

    QString unspendableKTVContent = formatFAQContent(
        formatFAQParagraph(
            tr("Newly received KTV requires 6 confirmations on the network "
               "to become eligible for spending which can take ~6 minutes.")) +
        formatFAQParagraph(
            tr("Your KTV wallet also needs to be completely synchronized "
               "to see and spend balances on the network.")));
    ui->labelContent_UnspendableKTV->setText(unspendableKTVContent);

    QString stakeContent = formatFAQContent(
        formatFAQOrderedList(
            formatFAQListItem(tr("Make sure your wallet is completely synchronized and you are using the latest release.")) +
            formatFAQListItem(tr("You must have a balance of KTV with a minimum of 100 confirmations.")) +
            formatFAQListItem(tr("Your wallet must stay online and be unlocked for staking purposes.")) +
            formatFAQListItem(tr("Once all those steps are followed staking should be enabled."))) +
        formatFAQParagraph(
            tr("You can see the status of staking in the wallet by mousing over the "
               "package icon in the row on the top left of the wallet interface. The "
               "package will be lit up and will state \"Staking Enabled\" to indicate "
               "it is staking. Using the command line interface (%1); the command %2 "
               "will confirm that staking is active.")
                .arg("ktv-cli", "<span style=\"font-style:italic\">getstakingstatus</span>")));
    ui->labelContent_Stake->setText(stakeContent);

    QString supportContent = formatFAQContent(
        formatFAQParagraph(
            tr("We have support channels in most of our official chat groups, for example %1  if you prefer to submit a ticket, you can do so at soporte@kmushicoin.co")
                .arg("<a style='color: #ffcc08' href='https://t.me/Kmushicoin_es'>" + tr("#support in our Telegram") + "</a>.")));
    ui->labelContent_Support->setText(supportContent);

    QString masternodeContent = formatFAQContent(
        formatFAQParagraph(
            tr("A masternode is a computer running a full node %1 wallet with a "
               "requirement of %2 secured collateral to provide extra services "
               "to the network and in return, receive a portion of the block reward "
               "regularly. These services include:")
                .arg(PACKAGE_NAME)
                .arg(GUIUtil::formatBalance(clientModel->getMNCollateralRequiredAmount(), BitcoinUnits::KTV)) +
            formatFAQUnorderedList(
                formatFAQListItem(tr("A decentralized governance (Proposal Voting)")) +
                formatFAQListItem(tr("A decentralized budgeting system (Treasury)")) +
                formatFAQListItem(tr("Validation of transactions within each block")) +
                formatFAQListItem(tr("Act as an additional full node in the network")))) +
        formatFAQParagraph(
            tr("For providing such services, masternodes are also paid a certain portion "
               "of reward for each block. This can serve as a passive income to the "
               "masternode owners minus their running cost.")) +
        formatFAQParagraph(
            tr("Masternode Perks:") +
            formatFAQUnorderedList(
                formatFAQListItem(tr("Participate in KTV Governance")) +
                formatFAQListItem(tr("Earn Masternode Rewards")) +
                formatFAQListItem(tr("Commodity option for future sale")) +
                formatFAQListItem(tr("Help secure the KTV network")))) +
        formatFAQParagraph(
            tr("Requirements:") +
            formatFAQUnorderedList(
                formatFAQListItem(tr("%1 per single Masternode instance")
                        .arg(GUIUtil::formatBalance(clientModel->getMNCollateralRequiredAmount(), BitcoinUnits::KTV))) +
                formatFAQListItem(tr("Must be stored in a core wallet")) +
                formatFAQListItem(tr("Need dedicated IP address")) +
                formatFAQListItem(tr("Masternode wallet to remain online")))));
    ui->labelContent_Masternode->setText(masternodeContent);

    QString mNControllerContent = formatFAQContent(
        formatFAQParagraph(
            tr("A Masternode Controller wallet is where the %1 collateral "
               "can reside during a Controller-Remote masternode setup. It is a wallet "
               "that can activate the remote masternode wallet(s) and allows you to keep "
               "your collateral coins offline while the remote masternode remains online.")
                    .arg(GUIUtil::formatBalance(clientModel->getMNCollateralRequiredAmount(), BitcoinUnits::KTV))));
    ui->labelContent_MNController->setText(mNControllerContent);


    // Exit button
    setCssProperty(ui->pushButtonExit, "btn-faq-exit");

    // Web Link
    setCssProperty(ui->pushButtonWebLink, "btn-faq-web");
    setCssProperty(ui->containerButtons, "container-faq-buttons");

    // Buttons
    connect(ui->pushButtonExit, &QPushButton::clicked, this, &SettingsFaqWidget::close);
    connect(ui->pushButton_Intro, &QPushButton::clicked, [this](){onFaqClicked(ui->widget_Intro);});
    connect(ui->pushButton_UnspendableKTV, &QPushButton::clicked, [this](){onFaqClicked(ui->widget_UnspendableKTV);});
    connect(ui->pushButton_Stake, &QPushButton::clicked, [this](){onFaqClicked(ui->widget_Stake);});
    connect(ui->pushButton_Support, &QPushButton::clicked, [this](){onFaqClicked(ui->widget_Support);});
    connect(ui->pushButton_Masternode, &QPushButton::clicked, [this](){onFaqClicked(ui->widget_Masternode);});
    connect(ui->pushButton_MNController, &QPushButton::clicked, [this](){onFaqClicked(ui->widget_MNController);});
    connect(ui->pushButtonWebLink, &QPushButton::clicked, this, &SettingsFaqWidget::openLink);
    ui->pushButtonWebLink->setCursor(QCursor(Qt::PointingHandCursor));

    if (parent)
        connect(parent, &KTVGUI::windowResizeEvent, this, &SettingsFaqWidget::windowResizeEvent);
}

void SettingsFaqWidget::openLink()
{
    QDesktopServices::openUrl(QUrl(ui->pushButtonWebLink->text()));
}

void SettingsFaqWidget::showEvent(QShowEvent *event)
{
    QPushButton* btn = getButtons()[section];
    QMetaObject::invokeMethod(btn, "setChecked", Qt::QueuedConnection, Q_ARG(bool, true));
    QMetaObject::invokeMethod(btn, "clicked", Qt::QueuedConnection);
}

void SettingsFaqWidget::setSection(Section _section)
{
    section = _section;
}

void SettingsFaqWidget::onFaqClicked(const QWidget* const widget)
{
    ui->scrollAreaFaq->verticalScrollBar()->setValue(widget->y());
}

void SettingsFaqWidget::windowResizeEvent(QResizeEvent* event)
{
    QWidget* w = qobject_cast<QWidget*>(parent());
    this->resize(w->width(), w->height());
    this->move(QPoint(0, 0));
}

std::vector<QPushButton*> SettingsFaqWidget::getButtons()
{
    return {
            ui->pushButton_Intro,
            ui->pushButton_UnspendableKTV,
            ui->pushButton_Stake,
            ui->pushButton_Support,
            ui->pushButton_Masternode,
            ui->pushButton_MNController
    };
}

SettingsFaqWidget::~SettingsFaqWidget()
{
    delete ui;
}


