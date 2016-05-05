#ifndef ICDIEDACCESSPOINTPAGE_H
#define ICDIEDACCESSPOINTPAGE_H

#include <QWizardPage>

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>

class icdIedAccessPointPage : public QWizardPage
{
    Q_OBJECT
public:
    explicit icdIedAccessPointPage(QWidget *parent = 0);

    QVBoxLayout *apVLayout;

    QGroupBox *apAttributeGroupBox;
    QGridLayout *apAttributeGridLayout;

    QLabel *apNameLabel;
    QLineEdit *apNameText;
    QCheckBox *apDescCheckBox;
    QLabel *apDescLabel;
    QLineEdit *apDescText;

    QGroupBox *apServerGroupBox;
    QVBoxLayout *apServerVLayout;

    QGroupBox *apServerAttributeGroupBox;
    QGridLayout *apServerAttributeGridLayout;

    QCheckBox *apServerDescCheckBox;
    QLabel *apServerDescLabel;
    QLineEdit *apServerDescText;
    QCheckBox *apServerTimeoutCheckBox;
    QLabel *apServerTimeoutLabel;
    QLineEdit *apServerTimeoutText;

    QGroupBox *apServerAuthenticationGroupBox;
    QGridLayout *apServerAuthenticationGridLayout;

    QCheckBox *apServerAuthenticationNoneCheckBox;
    QLabel *apServerAuthenticationNoneLabel;
    QComboBox *apServerAuthenticationNoneComboBox;
    QCheckBox *apServerAuthenticationPasswordCheckBox;
    QLabel *apServerAuthenticationPasswordLabel;
    QComboBox *apServerAuthenticationPasswordComboBox;
    QCheckBox *apServerAuthenticationWeakCheckBox;
    QLabel *apServerAuthenticationWeakLabel;
    QComboBox *apServerAuthenticationWeakComboBox;
    QCheckBox *apServerAuthenticationStrongCheckBox;
    QLabel *apServerAuthenticationStrongLabel;
    QComboBox *apServerAuthenticationStrongComboBox;
    QCheckBox *apServerAuthenticationCertificateCheckBox;
    QLabel *apServerAuthenticationCertificateLabel;
    QComboBox *apServerAuthenticationCertificateComboBox;

    QGroupBox *apLDeviceGroupBox;
//    QGridLayout *apLDeviceGridLayout;

//    QLabel *apIed0InstLabel;
//    QComboBox *apIed0InstComboBox;
//    QCheckBox *apIed0DescCheckBox;
//    QLabel *apIed0DescLabel;
//    QLineEdit *apIed0DescText;
//    QLabel *apIed1InstLabel;
//    QComboBox *apIed1InstComboBox;
//    QCheckBox *apIed1DescCheckBox;
//    QLabel *apIed1DescLabel;
//    QLineEdit *apIed1DescText;

private:
    void init();

signals:

public slots:

};

#endif // ICDIEDACCESSPOINTPAGE_H
