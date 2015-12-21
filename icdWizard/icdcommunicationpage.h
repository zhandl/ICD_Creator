#ifndef ICDCOMMUNICATIONPAGE_H
#define ICDCOMMUNICATIONPAGE_H

#include <QWizardPage>

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

#include "ipaddredit.h"

class icdCommunicationPage : public QWizardPage
{
    Q_OBJECT
public:
    explicit icdCommunicationPage(QWidget *parent = 0);
    ~icdCommunicationPage();

    QVBoxLayout *communicationVLayout;
    QGroupBox *communicationGroupBox;
    QGridLayout *communicationGridLayout;
    QGroupBox *subNetworkGroupBox;
    QGridLayout *subNetworkGridLayout;
    QLabel *subNetworkTypeLabel;
    QCheckBox *subNetworkDescCheckBox;
    QLineEdit *subNetworkDescText;
    QCheckBox *subNetworkTypeCheckBox;
    QLabel *subNetworkDescLabel;
    QGroupBox *bitRateGroupBox;
    QGridLayout *bitRateGridLayout;
    QComboBox *bitRateComboBox;
    QLabel *bitRateLabel;
    QLabel *bitRateUnitLabel;
    QGroupBox *connectedAPGroupBox;
    QGridLayout *connectAPGridLayout;
    QLineEdit *connectedApNameText;
    QLabel *connectedIedNameLabel;
    QLabel *connectedApNameLabel;
    QLineEdit *connectedIedNameText;
    QGroupBox *addressGroupBox;
    QGridLayout *addressGridLayout;
//    QPushButton *addressAddPButton;
//    QPushButton *addressDelPButton;
//    QTableWidget *addressPTableWidget;
    QLineEdit *subNetworkTypeText;
    QLabel *subNetworkNamelabel;
    QLineEdit *subNetworkNameText;
    QCheckBox *ipAddressCheckBox;
    QLabel *ipAddressLabel;
    CIpAddrEdit *ipAddressText;
    QCheckBox *ipSubMaskCheckBox;
    QLabel *ipSubMaskLabel;
    CIpAddrEdit *ipSubMaskText;
    QCheckBox *ipGateCheckBox;
    QLabel *ipGateLabel;
    CIpAddrEdit *ipGateText;


private:
    void init();
    void retranslateUi();

signals:

public slots:
    void setIedName(QString iedName);
    void setApName(QString apName);
};

#endif // ICDCOMMUNICATIONPAGE_H
