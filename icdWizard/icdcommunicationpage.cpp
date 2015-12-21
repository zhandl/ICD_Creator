#include "icdcommunicationpage.h"
#include "ui_icdCommunicationPage.h"
#include <QStringList>
#include "icdiedservicespage.h"

QStringList PType = QStringList()<<QString::fromUtf8("IP")<<QString::fromUtf8("IP-SUBNET")<<QString::fromUtf8("IP-GATEWAY")<< \
                                   QString::fromUtf8("OSI-NSAP")<<QString::fromUtf8("OSI-TSEL")<<QString::fromUtf8("OSI-SSEL")<<QString::fromUtf8("OSI-PSEL")<< \
                                   QString::fromUtf8("OSI-AP-Title")<<QString::fromUtf8("OSI-AP-Invoke")<<QString::fromUtf8("OSI-AE-Qualifier")<<QString::fromUtf8("OSI-AE-Invoke")<< \
                                   QString::fromUtf8("MAC-Address")<<QString::fromUtf8("APPID")<<QString::fromUtf8("VLAN-PRIORITY")<<QString::fromUtf8("VLAN-ID");

icdCommunicationPage::icdCommunicationPage(QWidget *parent) :
    QWizardPage(parent)
{
    init();

    connect(subNetworkTypeCheckBox, SIGNAL(toggled(bool)), subNetworkTypeLabel, SLOT(setEnabled(bool)));
    connect(subNetworkTypeCheckBox, SIGNAL(toggled(bool)), subNetworkTypeText, SLOT(setEnabled(bool)));
    connect(subNetworkDescCheckBox, SIGNAL(toggled(bool)), subNetworkDescLabel, SLOT(setEnabled(bool)));
    connect(subNetworkDescCheckBox, SIGNAL(toggled(bool)), subNetworkDescText, SLOT(setEnabled(bool)));
    connect(ipAddressCheckBox, SIGNAL(toggled(bool)), ipAddressLabel, SLOT(setEnabled(bool)));
    connect(ipAddressCheckBox, SIGNAL(toggled(bool)), ipAddressText, SLOT(setEnabled(bool)));
    connect(ipSubMaskCheckBox, SIGNAL(toggled(bool)), ipSubMaskLabel, SLOT(setEnabled(bool)));
    connect(ipSubMaskCheckBox, SIGNAL(toggled(bool)), ipSubMaskText, SLOT(setEnabled(bool)));
    connect(ipGateCheckBox, SIGNAL(toggled(bool)), ipGateLabel, SLOT(setEnabled(bool)));
    connect(ipGateCheckBox, SIGNAL(toggled(bool)), ipGateText, SLOT(setEnabled(bool)));

    bool subNetworkTypeIsChecked = subNetworkTypeCheckBox->isChecked();
    bool subNetworkDescIsChecked = subNetworkDescCheckBox->isChecked();
    bool ipAddressIsChecked = ipAddressCheckBox->isChecked();
    bool ipSubMaskIsChecked = ipSubMaskCheckBox->isChecked();
    bool ipGateIsChecked = ipGateCheckBox->isChecked();
    subNetworkTypeLabel->setEnabled(subNetworkTypeIsChecked);
    subNetworkTypeText->setEnabled(subNetworkTypeIsChecked);
    subNetworkDescLabel->setEnabled(subNetworkDescIsChecked);
    subNetworkDescText->setEnabled(subNetworkDescIsChecked);
    ipAddressLabel->setEnabled(ipAddressIsChecked);
    ipAddressText->setEnabled(ipAddressIsChecked);
    ipSubMaskLabel->setEnabled(ipSubMaskIsChecked);
    ipSubMaskText->setEnabled(ipSubMaskIsChecked);
    ipGateLabel->setEnabled(ipGateIsChecked);
    ipGateText->setEnabled(ipGateIsChecked);

    subNetworkTypeCheckBox->setChecked(true);
    subNetworkTypeText->setText(tr("8-MMS"));

    ipAddressCheckBox->setChecked(true);
    ipAddressText->m_vSetText(tr("127.0.0.1"));
}

icdCommunicationPage::~icdCommunicationPage()
{

}

void icdCommunicationPage::init()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QString::fromUtf8("icdCommunicationPage"));
    this->resize(800, 600);
    communicationVLayout = new QVBoxLayout(this);
    communicationVLayout->setObjectName(QString::fromUtf8("communicationVLayout"));
    communicationVLayout->setContentsMargins(11, 11,11, 11);

    QFont font;
    font.setFamily(QString::fromUtf8("Calibri"));
    font.setPointSize(11);

    communicationGroupBox = new QGroupBox(this);
    communicationGroupBox->setObjectName(QString::fromUtf8("communicationGroupBox"));
    communicationGroupBox->setCheckable(true);
    communicationGroupBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    communicationGroupBox->setFont(font);

    communicationGridLayout = new QGridLayout(communicationGroupBox);
    communicationGridLayout->setObjectName(QString::fromUtf8("communicationGridLayout"));
    communicationGridLayout->setContentsMargins(11, 11, 11, 11);

    subNetworkGroupBox = new QGroupBox(communicationGroupBox);
    subNetworkGroupBox->setObjectName(QString::fromUtf8("subNetworkGroupBox"));

    subNetworkGridLayout = new QGridLayout(subNetworkGroupBox);
    subNetworkGridLayout->setObjectName(QString::fromUtf8("subNetworkGridLayout"));
    subNetworkGridLayout->setContentsMargins(11, 11, 11, 11);

    subNetworkNamelabel = new QLabel(subNetworkGroupBox);
    subNetworkNamelabel->setObjectName(QString::fromUtf8("subNetworkNamelabel"));
    subNetworkNamelabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);

    subNetworkNameText = new QLineEdit(subNetworkGroupBox);
    subNetworkNameText->setObjectName(QString::fromUtf8("subNetworkNameText"));
    subNetworkNameText->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 200);"));
    subNetworkNameText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);

    subNetworkTypeCheckBox = new QCheckBox(subNetworkGroupBox);
    subNetworkTypeCheckBox->setObjectName(QString::fromUtf8("subNetworkTypeCheckBox"));
    subNetworkTypeCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);

    subNetworkTypeLabel = new QLabel(subNetworkGroupBox);
    subNetworkTypeLabel->setObjectName(QString::fromUtf8("subNetworkTypeLabel"));
    subNetworkTypeLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);

    subNetworkTypeText = new QLineEdit(subNetworkGroupBox);
    subNetworkTypeText->setObjectName(QString::fromUtf8("subNetworkTypeText"));
    subNetworkTypeText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);

    subNetworkDescCheckBox = new QCheckBox(subNetworkGroupBox);
    subNetworkDescCheckBox->setObjectName(QString::fromUtf8("subNetworkDescCheckBox"));
    subNetworkDescCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);

    subNetworkDescLabel = new QLabel(subNetworkGroupBox);
    subNetworkDescLabel->setObjectName(QString::fromUtf8("subNetworkDescLabel"));
    subNetworkDescLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);

    subNetworkDescText = new QLineEdit(subNetworkGroupBox);
    subNetworkDescText->setObjectName(QString::fromUtf8("subNetworkDescText"));
    subNetworkDescText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);

    bitRateGroupBox = new QGroupBox(subNetworkGroupBox);
    bitRateGroupBox->setObjectName(QString::fromUtf8("bitRateGroupBox"));
    bitRateGroupBox->setCheckable(true);

    bitRateGridLayout = new QGridLayout(bitRateGroupBox);
    bitRateGridLayout->setObjectName(QString::fromUtf8("bitRateGridLayout"));
    bitRateGridLayout->setContentsMargins(11, 11, 11, 11);

    bitRateLabel = new QLabel(bitRateGroupBox);
    bitRateLabel->setObjectName(QString::fromUtf8("bitRateLabel"));
    bitRateLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);

    bitRateComboBox = new QComboBox(bitRateGroupBox);
    bitRateComboBox->setObjectName(QString::fromUtf8("bitRateComboBox"));
    bitRateComboBox->setEditable(true);
    bitRateComboBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);

    bitRateUnitLabel = new QLabel(bitRateGroupBox);
    bitRateUnitLabel->setObjectName(QString::fromUtf8("bitRateUnitLabel"));
    bitRateUnitLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);

    bitRateGridLayout->addWidget(bitRateLabel, 0, 0, 1, 1);
    bitRateGridLayout->addWidget(bitRateComboBox, 0, 1, 1, 1);
    bitRateGridLayout->addWidget(bitRateUnitLabel, 0, 2, 1, 1);
    bitRateGridLayout->setColumnStretch(3,4);

    connectedAPGroupBox = new QGroupBox(bitRateGroupBox);
    connectedAPGroupBox->setObjectName(QString::fromUtf8("connectedAPGroupBox"));
//    connectedAPGroupBox->setGeometry(QRect(0, 130, 659, 221));

    connectAPGridLayout = new QGridLayout(connectedAPGroupBox);
    connectAPGridLayout->setObjectName(QString::fromUtf8("connectAPGridLayout"));
    connectAPGridLayout->setContentsMargins(11, 11, 11, 11);

    connectedApNameLabel = new QLabel(connectedAPGroupBox);
    connectedApNameLabel->setObjectName(QString::fromUtf8("connectedApNameLabel"));
    connectedApNameLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);

    connectedApNameText = new QLineEdit(connectedAPGroupBox);
    connectedApNameText->setObjectName(QString::fromUtf8("connectedApNameText"));
    connectedApNameText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    connectedApNameText->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 200);"));
    connectedApNameText->setText("S1");

    connectedIedNameLabel = new QLabel(connectedAPGroupBox);
    connectedIedNameLabel->setObjectName(QString::fromUtf8("connectedIedNameLabel"));
    connectedIedNameLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);

    connectedIedNameText = new QLineEdit(connectedAPGroupBox);
    connectedIedNameText->setObjectName(QString::fromUtf8("connectedIedNameText"));
    connectedIedNameText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    connectedIedNameText->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 200);"));

    addressGroupBox = new QGroupBox(connectedAPGroupBox);
    addressGroupBox->setObjectName(QString::fromUtf8("addressGroupBox"));
    addressGroupBox->setCheckable(true);

    addressGridLayout = new QGridLayout(addressGroupBox);
    addressGridLayout->setObjectName(QString::fromUtf8("addressGridLayout"));
    addressGridLayout->setContentsMargins(11, 11, 11, 11);

//    addressPTableWidget = new QTableWidget(addressGroupBox);
//    addressPTableWidget->setObjectName(QString::fromUtf8("addressPTableWidget"));
//    addressPTableWidget->setRowCount(6);
//    addressPTableWidget->setColumnCount(2);
//    addressPTableWidget->verticalHeader()->setVisible(false);
//    addressPTableWidget->setHorizontalHeaderLabels(QStringList()<<tr("Type")<<tr("Value"));

//    QComboBox *newPTypeItem = new QComboBox(this);
//    newPTypeItem->setEditable(true);
//    newPTypeItem->addItems(PType);
//    newPTypeItem->setCurrentIndex(5);
//    addressPTableWidget->setCellWidget(0, 0, newPTypeItem);
//    QTableWidgetItem *newPTypeValueItem = new QTableWidgetItem(tr("1,3,9999,33"));
//    addressPTableWidget->setItem(0, 1, newPTypeValueItem);

//    QComboBox *newPTypeItem1 = new QComboBox(this);
//    newPTypeItem1->setEditable(true);
//    newPTypeItem1->addItems(PType);
//    newPTypeItem1->setCurrentIndex(8);
//    addressPTableWidget->setCellWidget(1, 0, newPTypeItem1);
//    QTableWidgetItem *newPTypeValueItem1 = new QTableWidgetItem(tr("33"));
//    addressPTableWidget->setItem(1, 1, newPTypeValueItem1);

//    QComboBox *newPTypeItem2 = new QComboBox(this);
//    newPTypeItem2->setEditable(true);
//    newPTypeItem2->addItems(PType);
//    newPTypeItem2->setCurrentIndex(6);
//    addressPTableWidget->setCellWidget(2, 0, newPTypeItem2);
//    QTableWidgetItem *newPTypeValueItem2 = new QTableWidgetItem(tr("00000001"));
//    addressPTableWidget->setItem(2, 1, newPTypeValueItem2);

//    QComboBox *newPTypeItem3 = new QComboBox(this);
//    newPTypeItem3->setEditable(true);
//    newPTypeItem3->addItems(PType);
//    newPTypeItem3->setCurrentIndex(5);
//    addressPTableWidget->setCellWidget(3, 0, newPTypeItem3);
//    QTableWidgetItem *newPTypeValueItem3 = new QTableWidgetItem(tr("0001"));
//    addressPTableWidget->setItem(3, 1, newPTypeValueItem3);

//    QComboBox *newPTypeItem4 = new QComboBox(this);
//    newPTypeItem4->setEditable(true);
//    newPTypeItem4->addItems(PType);
//    newPTypeItem4->setCurrentIndex(4);
//    addressPTableWidget->setCellWidget(4, 0, newPTypeItem4);
//    QTableWidgetItem *newPTypeValueItem4 = new QTableWidgetItem(tr("0001"));
//    addressPTableWidget->setItem(4, 1, newPTypeValueItem4);

//    QComboBox *newPTypeItem5 = new QComboBox(this);
//    newPTypeItem5->setEditable(true);
//    newPTypeItem5->addItems(PType);
//    newPTypeItem5->setCurrentIndex(0);
//    addressPTableWidget->setCellWidget(5, 0, newPTypeItem5);
//    QTableWidgetItem *newPTypeValueItem5 = new QTableWidgetItem(tr("127.0.0.1"));
//    addressPTableWidget->setItem(5, 1, newPTypeValueItem5);

//    addressPTableWidget->setColumnWidth(0, 130);

//    addressAddPButton = new QPushButton(addressGroupBox);
//    addressAddPButton->setObjectName(QString::fromUtf8("addressAddPButton"));

//    addressDelPButton = new QPushButton(addressGroupBox);
//    addressDelPButton->setObjectName(QString::fromUtf8("addressDelPButton"));

    ipAddressCheckBox = new QCheckBox(addressGroupBox);
    ipAddressCheckBox->setObjectName("ipAddressCheckBox");
    ipAddressCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    ipAddressLabel = new QLabel(addressGroupBox);
    ipAddressLabel->setObjectName("ipAddressLabel");
    ipAddressLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    ipAddressText = new CIpAddrEdit(addressGroupBox);
    ipAddressText->setObjectName("ipAddressText");

    ipSubMaskCheckBox = new QCheckBox(addressGroupBox);
    ipSubMaskCheckBox->setObjectName("ipSubMaskCheckBox");
    ipSubMaskCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    ipSubMaskLabel = new QLabel(addressGroupBox);
    ipSubMaskLabel->setObjectName("ipSubMaskLabel");
    ipSubMaskLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    ipSubMaskText = new CIpAddrEdit(addressGroupBox);
    ipSubMaskText->setObjectName("ipSubMaskText");

    ipGateCheckBox = new QCheckBox(addressGroupBox);
    ipGateCheckBox->setObjectName("ipGateCheckBox");
    ipGateCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    ipGateLabel = new QLabel(addressGroupBox);
    ipGateLabel->setObjectName("ipGateLabel");
    ipGateLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    ipGateText = new CIpAddrEdit(addressGroupBox);
    ipGateText->setObjectName("ipGateText");

    addressGridLayout->addWidget(ipAddressCheckBox, 0, 0, 1, 1);
    addressGridLayout->addWidget(ipAddressLabel, 0, 1, 1, 1);
    addressGridLayout->addWidget(ipAddressText, 0, 2, 1, 4);
    addressGridLayout->addWidget(ipSubMaskCheckBox, 1, 0, 1, 1);
    addressGridLayout->addWidget(ipSubMaskLabel, 1, 1, 1, 1);
    addressGridLayout->addWidget(ipSubMaskText, 1, 2, 1, 4);
    addressGridLayout->addWidget(ipGateCheckBox, 2, 0, 1, 1);
    addressGridLayout->addWidget(ipGateLabel, 2, 1, 1, 1);
    addressGridLayout->addWidget(ipGateText, 2, 2, 1, 4);


//    addressGridLayout->addWidget(addressPTableWidget, 0, 0, 6, 1);
//    addressGridLayout->addWidget(addressAddPButton, 0, 4, 1, 1);
//    addressGridLayout->addWidget(addressDelPButton, 1, 4, 1, 1);
//    addressGridLayout->setColumnStretch(1,3);

    connectAPGridLayout->addWidget(connectedIedNameLabel, 0, 0, 1, 1);
    connectAPGridLayout->addWidget(connectedIedNameText, 0, 1, 1, 1);
    connectAPGridLayout->addWidget(connectedApNameLabel, 0, 2, 1, 1);
    connectAPGridLayout->addWidget(connectedApNameText, 0, 3, 1, 1);
    connectAPGridLayout->addWidget(addressGroupBox, 1, 0, 1, 5);
    connectAPGridLayout->setColumnStretch(4,1);

    subNetworkGridLayout->addWidget(subNetworkNamelabel, 0, 0, 1, 1);
    subNetworkGridLayout->addWidget(subNetworkNameText, 0, 1, 1, 1);
    subNetworkGridLayout->addWidget(subNetworkTypeCheckBox, 0, 2, 1, 1);
    subNetworkGridLayout->addWidget(subNetworkTypeLabel, 0, 3, 1, 1);
    subNetworkGridLayout->addWidget(subNetworkTypeText, 0, 4, 1, 1);
    subNetworkGridLayout->addWidget(subNetworkDescCheckBox, 0, 5, 1, 1);
    subNetworkGridLayout->addWidget(subNetworkDescLabel, 0, 6, 1, 1);
    subNetworkGridLayout->addWidget(subNetworkDescText, 0, 7, 1, 1);
    subNetworkGridLayout->addWidget(bitRateGroupBox, 1, 0, 1, 9);
    subNetworkGridLayout->addWidget(connectedAPGroupBox, 2, 0, 1, 9);
    subNetworkGridLayout->setColumnStretch(8, 1);
    subNetworkGridLayout->setRowStretch(3,1);

    communicationGridLayout->addWidget(subNetworkGroupBox, 0, 0, 1, 1);

    communicationVLayout->addWidget(communicationGroupBox);

    subNetworkNamelabel->setBuddy(subNetworkNameText);
    subNetworkTypeLabel->setBuddy(subNetworkTypeText);
    subNetworkDescLabel->setBuddy(subNetworkDescText);
    connectedApNameLabel->setBuddy(connectedApNameText);
    connectedIedNameLabel->setBuddy(connectedIedNameText);

    retranslateUi();
    QMetaObject::connectSlotsByName(this);

    bitRateComboBox->setCurrentIndex(1);
}

void icdCommunicationPage::retranslateUi()
{
    setWindowTitle(QApplication::translate("icdCommunicationPage", "WizardPage", 0, QApplication::UnicodeUTF8));
    setTitle(QApplication::translate("icdCommunicationPage", "ICD Communication Setting", 0, QApplication::UnicodeUTF8));
    setSubTitle(QApplication::translate("icdCommunicationPage", "This page can set the attributes of communication segment, if needed.", 0, QApplication::UnicodeUTF8));
    communicationGroupBox->setTitle(QApplication::translate("icdCommunicationPage", "Communication", 0, QApplication::UnicodeUTF8));
    subNetworkGroupBox->setTitle(QApplication::translate("icdCommunicationPage", "SubNetwork", 0, QApplication::UnicodeUTF8));
    subNetworkTypeLabel->setText(QApplication::translate("icdCommunicationPage", "type", 0, QApplication::UnicodeUTF8));
    subNetworkDescCheckBox->setText(QString());
    subNetworkTypeCheckBox->setText(QString());
    subNetworkDescLabel->setText(QApplication::translate("icdCommunicationPage", "desc", 0, QApplication::UnicodeUTF8));
    bitRateGroupBox->setTitle(QApplication::translate("icdCommunicationPage", "BitRate", 0, QApplication::UnicodeUTF8));
    bitRateComboBox->clear();
    bitRateComboBox->insertItems(0, QStringList()
     << QApplication::translate("icdCommunicationPage", "10", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("icdCommunicationPage", "100", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("icdCommunicationPage", "1000", 0, QApplication::UnicodeUTF8)
    );
    bitRateLabel->setText(QApplication::translate("icdCommunicationPage", "Setting BitRate of this subNetwork:", 0, QApplication::UnicodeUTF8));
    bitRateUnitLabel->setText(QApplication::translate("icdCommunicationPage", "(unit : Mb/s)", 0, QApplication::UnicodeUTF8));
    connectedAPGroupBox->setTitle(QApplication::translate("icdCommunicationPage", "ConnectedAP", 0, QApplication::UnicodeUTF8));
    connectedIedNameLabel->setText(QApplication::translate("icdCommunicationPage", "iedName", 0, QApplication::UnicodeUTF8));
    connectedApNameLabel->setText(QApplication::translate("icdCommunicationPage", "apName", 0, QApplication::UnicodeUTF8));
    addressGroupBox->setTitle(QApplication::translate("icdCommunicationPage", "Address", 0, QApplication::UnicodeUTF8));
    ipAddressLabel->setText(tr("IP"));
    ipSubMaskLabel->setText(tr("Mask"));
    ipGateLabel->setText(tr("Gate"));
    subNetworkNamelabel->setText(QApplication::translate("icdCommunicationPage", "name", 0, QApplication::UnicodeUTF8));
    subNetworkNameText->setText(tr("LAN1"));

}


void icdCommunicationPage::setIedName(QString iedName)
{
    connectedIedNameText->setText(iedName);
}

void icdCommunicationPage::setApName(QString apName)
{
    connectedApNameText->setText(apName);
}
