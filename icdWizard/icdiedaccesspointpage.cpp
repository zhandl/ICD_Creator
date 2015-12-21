#include "icdiedaccesspointpage.h"

icdIedAccessPointPage::icdIedAccessPointPage(QWidget *parent) :
    QWizardPage(parent)
{
    setTitle(tr("IED AccessPoint Setting"));
    setSubTitle(tr("This page can set the AccessPoint of ied segment."));

    init();

    connect(apDescCheckBox, SIGNAL(toggled(bool)), apDescLabel, SLOT(setEnabled(bool)));
    connect(apDescCheckBox, SIGNAL(toggled(bool)), apDescText, SLOT(setEnabled(bool)));
    connect(apServerDescCheckBox, SIGNAL(toggled(bool)), apServerDescLabel, SLOT(setEnabled(bool)));
    connect(apServerDescCheckBox, SIGNAL(toggled(bool)), apServerDescText, SLOT(setEnabled(bool)));
    connect(apServerTimeoutCheckBox, SIGNAL(toggled(bool)), apServerTimeoutLabel, SLOT(setEnabled(bool)));
    connect(apServerTimeoutCheckBox, SIGNAL(toggled(bool)), apServerTimeoutText, SLOT(setEnabled(bool)));
    connect(apServerAuthenticationNoneCheckBox, SIGNAL(toggled(bool)), apServerAuthenticationNoneLabel, SLOT(setEnabled(bool)));
    connect(apServerAuthenticationNoneCheckBox, SIGNAL(toggled(bool)), apServerAuthenticationNoneComboBox, SLOT(setEnabled(bool)));
    connect(apServerAuthenticationPasswordCheckBox, SIGNAL(toggled(bool)), apServerAuthenticationPasswordLabel, SLOT(setEnabled(bool)));
    connect(apServerAuthenticationPasswordCheckBox, SIGNAL(toggled(bool)), apServerAuthenticationPasswordComboBox, SLOT(setEnabled(bool)));
    connect(apServerAuthenticationWeakCheckBox, SIGNAL(toggled(bool)), apServerAuthenticationWeakLabel, SLOT(setEnabled(bool)));
    connect(apServerAuthenticationWeakCheckBox, SIGNAL(toggled(bool)), apServerAuthenticationWeakComboBox, SLOT(setEnabled(bool)));
    connect(apServerAuthenticationStrongCheckBox, SIGNAL(toggled(bool)), apServerAuthenticationStrongLabel, SLOT(setEnabled(bool)));
    connect(apServerAuthenticationStrongCheckBox, SIGNAL(toggled(bool)), apServerAuthenticationStrongComboBox, SLOT(setEnabled(bool)));
    connect(apServerAuthenticationCertificateCheckBox, SIGNAL(toggled(bool)), apServerAuthenticationCertificateLabel, SLOT(setEnabled(bool)));
    connect(apServerAuthenticationCertificateCheckBox, SIGNAL(toggled(bool)), apServerAuthenticationCertificateComboBox, SLOT(setEnabled(bool)));
    connect(apIed0DescCheckBox, SIGNAL(toggled(bool)), apIed0DescLabel, SLOT(setEnabled(bool)));
    connect(apIed0DescCheckBox, SIGNAL(toggled(bool)), apIed0DescText, SLOT(setEnabled(bool)));
    connect(apIed1DescCheckBox, SIGNAL(toggled(bool)), apIed1DescLabel, SLOT(setEnabled(bool)));
    connect(apIed1DescCheckBox, SIGNAL(toggled(bool)), apIed1DescText, SLOT(setEnabled(bool)));

    bool apDescIsChecked = apDescCheckBox->isChecked();
    apDescLabel->setEnabled(apDescIsChecked);
    apDescText->setEnabled(apDescIsChecked);
    bool apServerDescIsChecked = apServerDescCheckBox->isChecked();
    apServerDescLabel->setEnabled(apServerDescIsChecked);
    apServerDescText->setEnabled(apServerDescIsChecked);
    bool apServerTimeoutIsChecked = apServerTimeoutCheckBox->isChecked();
    apServerTimeoutLabel->setEnabled(apServerTimeoutIsChecked);
    apServerTimeoutText->setEnabled(apServerTimeoutIsChecked);
    bool apServerAuthenticationNoneIsChecked = apServerAuthenticationNoneCheckBox->isChecked();
    apServerAuthenticationNoneLabel->setEnabled(apServerAuthenticationNoneIsChecked);
    apServerAuthenticationNoneComboBox->setEnabled(apServerAuthenticationNoneIsChecked);
    bool apServerAuthenticationPasswordIsChecked = apServerAuthenticationPasswordCheckBox->isChecked();
    apServerAuthenticationPasswordLabel->setEnabled(apServerAuthenticationPasswordIsChecked);
    apServerAuthenticationPasswordComboBox->setEnabled(apServerAuthenticationPasswordIsChecked);
    bool apServerAuthenticationWeakIsChecked = apServerAuthenticationWeakCheckBox->isChecked();
    apServerAuthenticationWeakLabel->setEnabled(apServerAuthenticationWeakIsChecked);
    apServerAuthenticationWeakComboBox->setEnabled(apServerAuthenticationWeakIsChecked);
    bool apServerAuthenticationStrongIsChecked = apServerAuthenticationStrongCheckBox->isChecked();
    apServerAuthenticationStrongLabel->setEnabled(apServerAuthenticationStrongIsChecked);
    apServerAuthenticationStrongComboBox->setEnabled(apServerAuthenticationStrongIsChecked);
    bool apServerAuthenticationCertificateIsChecked = apServerAuthenticationCertificateCheckBox->isChecked();
    apServerAuthenticationCertificateLabel->setEnabled(apServerAuthenticationCertificateIsChecked);
    apServerAuthenticationCertificateComboBox->setEnabled(apServerAuthenticationCertificateIsChecked);
    bool apIed0DescIsChecked = apIed0DescCheckBox->isChecked();
    apIed0DescLabel->setEnabled(apIed0DescIsChecked);
    apIed0DescText->setEnabled(apIed0DescIsChecked);
    bool apIed1DescIsChecked = apIed1DescCheckBox->isChecked();
    apIed1DescLabel->setEnabled(apIed1DescIsChecked);
    apIed1DescText->setEnabled(apIed1DescIsChecked);

    apIed0InstComboBox->setCurrentIndex(0);
    apIed1InstComboBox->setCurrentIndex(1);

    apNameText->setText(tr("S1"));
    apServerAuthenticationNoneCheckBox->setChecked(true);
    apServerAuthenticationNoneComboBox->setCurrentIndex(1);

    apIed0DescCheckBox->setChecked(true);
    apIed0DescText->setText(tr("公共逻辑设备"));
    apIed1DescCheckBox->setChecked(true);
    apIed1DescText->setText(tr("录波控制单元"));

}


void icdIedAccessPointPage::init()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QString::fromUtf8("icdIedAccessPoingPage"));
    this->resize(800, 600);
    QFont font;
    font.setFamily(QString::fromUtf8("Calibri"));
    font.setPointSize(12);
    setFont(font);

    apVLayout = new QVBoxLayout(this);
    apVLayout->setObjectName(QString::fromUtf8("apVLayout"));

    apAttributeGroupBox = new QGroupBox(this);
    apAttributeGroupBox->setObjectName(QString::fromUtf8("apAttributeGroupBox"));
    apAttributeGridLayout = new QGridLayout(apAttributeGroupBox);
    apAttributeGridLayout->setObjectName(QString::fromUtf8("apAttributeGridLayout"));
    apNameLabel = new QLabel(apAttributeGroupBox);
    apNameLabel->setObjectName(QString::fromUtf8("apNameLabel"));
    apNameLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    apNameText = new QLineEdit(apAttributeGroupBox);
    apNameText->setObjectName(QString::fromUtf8("apNameText"));
    apDescCheckBox = new QCheckBox(apAttributeGroupBox);
    apDescCheckBox->setObjectName(QString::fromUtf8("apDescCheckBox"));
    apDescCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    apDescLabel = new QLabel(apAttributeGroupBox);
    apDescLabel->setObjectName(QString::fromUtf8("apDescLabel"));
    apDescLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    apDescText = new QLineEdit(apAttributeGroupBox);
    apDescText->setObjectName(QString::fromUtf8("apDescText"));

    apAttributeGridLayout->addWidget(apNameLabel, 0, 0, 1, 1);
    apAttributeGridLayout->addWidget(apNameText, 0, 1, 1, 1);
    apAttributeGridLayout->addWidget(apDescCheckBox, 0, 2, 1, 1);
    apAttributeGridLayout->addWidget(apDescLabel, 0, 3, 1, 1);
    apAttributeGridLayout->addWidget(apDescText, 0, 4, 1, 1);

    apServerGroupBox = new QGroupBox(this);
    apServerGroupBox->setObjectName(QString::fromUtf8("apServerGroupBox"));
    apServerVLayout = new QVBoxLayout(apServerGroupBox);
    apServerVLayout->setObjectName(QString::fromUtf8("apServerVLayout"));

    apServerAttributeGroupBox = new QGroupBox(apServerGroupBox);
    apServerAttributeGroupBox->setObjectName(QString::fromUtf8("apServerAttributeGroupBox"));
    apServerAttributeGridLayout = new QGridLayout(apServerAttributeGroupBox);
    apServerAttributeGridLayout->setObjectName(QString::fromUtf8("apServerAttributeGridLayout"));

    apServerDescCheckBox = new QCheckBox(apServerGroupBox);
    apServerDescCheckBox->setObjectName(QString::fromUtf8("apServerDescCheckBox"));
    apServerDescCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    apServerDescLabel = new QLabel(apServerGroupBox);
    apServerDescLabel->setObjectName(QString::fromUtf8("apServerDescLabel"));
    apServerDescLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    apServerDescText = new QLineEdit(apServerGroupBox);
    apServerDescText->setObjectName(QString::fromUtf8("apServerDescText"));
    apServerTimeoutCheckBox = new QCheckBox(apServerGroupBox);
    apServerTimeoutCheckBox->setObjectName(QString::fromUtf8("apServerTimeoutCheckBox"));
    apServerTimeoutCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    apServerTimeoutLabel = new QLabel(apServerGroupBox);
    apServerTimeoutLabel->setObjectName(QString::fromUtf8("apServerTimeoutLabel"));
    apServerTimeoutLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    apServerTimeoutText = new QLineEdit(apServerGroupBox);
    apServerTimeoutText->setObjectName(QString::fromUtf8("apServerTimeoutText"));

    apServerAttributeGridLayout->addWidget(apServerDescCheckBox, 0, 0, 1, 1);
    apServerAttributeGridLayout->addWidget(apServerDescLabel, 0, 1, 1, 1);
    apServerAttributeGridLayout->addWidget(apServerDescText, 0, 2, 1, 1);
    apServerAttributeGridLayout->addWidget(apServerTimeoutCheckBox, 0, 3, 1, 1);
    apServerAttributeGridLayout->addWidget(apServerTimeoutLabel, 0, 4, 1, 1);
    apServerAttributeGridLayout->addWidget(apServerTimeoutText, 0, 5, 1, 1);

    apServerAuthenticationGroupBox = new QGroupBox(apServerGroupBox);
    apServerAuthenticationGroupBox->setObjectName(QString::fromUtf8("apServerAuthenticationGroupBox"));
    apServerAuthenticationGridLayout = new QGridLayout(apServerAuthenticationGroupBox);
    apServerAuthenticationGridLayout->setObjectName(QString::fromUtf8("apServerAuthenticationGridLayout"));

    apServerAuthenticationNoneCheckBox = new QCheckBox(apServerAuthenticationGroupBox);
    apServerAuthenticationNoneCheckBox->setObjectName(QString::fromUtf8("apServerAuthenticationNoneCheckBox"));
    apServerAuthenticationNoneCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    apServerAuthenticationNoneLabel = new QLabel(apServerAuthenticationGroupBox);
    apServerAuthenticationNoneLabel->setObjectName(QString::fromUtf8("apServerAuthenticationNoneLabel"));
    apServerAuthenticationNoneLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    apServerAuthenticationNoneComboBox = new QComboBox(apServerAuthenticationGroupBox);
    apServerAuthenticationNoneComboBox->setObjectName(QString::fromUtf8("apServerAuthenticationNoneComboBox"));
    apServerAuthenticationPasswordCheckBox = new QCheckBox(apServerAuthenticationGroupBox);
    apServerAuthenticationPasswordCheckBox->setObjectName(QString::fromUtf8("apServerAuthenticationPasswordCheckBox"));
    apServerAuthenticationPasswordCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    apServerAuthenticationPasswordLabel = new QLabel(apServerAuthenticationGroupBox);
    apServerAuthenticationPasswordLabel->setObjectName(QString::fromUtf8("apServerAuthenticationPasswordLabel"));
    apServerAuthenticationPasswordLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    apServerAuthenticationPasswordComboBox = new QComboBox(apServerAuthenticationGroupBox);
    apServerAuthenticationPasswordComboBox->setObjectName(QString::fromUtf8("apServerAuthenticationPasswordComboBox"));
    apServerAuthenticationWeakCheckBox = new QCheckBox(apServerAuthenticationGroupBox);
    apServerAuthenticationWeakCheckBox->setObjectName(QString::fromUtf8("apServerAuthenticationWeakCheckBox"));
    apServerAuthenticationWeakCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    apServerAuthenticationWeakLabel = new QLabel(apServerAuthenticationGroupBox);
    apServerAuthenticationWeakLabel->setObjectName(QString::fromUtf8("apServerAuthenticationWeakLabel"));
    apServerAuthenticationWeakLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    apServerAuthenticationWeakComboBox = new QComboBox(apServerAuthenticationGroupBox);
    apServerAuthenticationWeakComboBox->setObjectName(QString::fromUtf8("apServerAuthenticationWeakComboBox"));
    apServerAuthenticationStrongCheckBox = new QCheckBox(apServerAuthenticationGroupBox);
    apServerAuthenticationStrongCheckBox->setObjectName(QString::fromUtf8("apServerAuthenticationStrongCheckBox"));
    apServerAuthenticationStrongCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    apServerAuthenticationStrongLabel = new QLabel(apServerAuthenticationGroupBox);
    apServerAuthenticationStrongLabel->setObjectName(QString::fromUtf8("apServerAuthenticationStrongLabel"));
    apServerAuthenticationStrongLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    apServerAuthenticationStrongComboBox = new QComboBox(apServerAuthenticationGroupBox);
    apServerAuthenticationStrongComboBox->setObjectName(QString::fromUtf8("apServerAuthenticationStrongComboBox"));
    apServerAuthenticationCertificateCheckBox = new QCheckBox(apServerAuthenticationGroupBox);
    apServerAuthenticationCertificateCheckBox->setObjectName(QString::fromUtf8("apServerAuthenticationCertificateCheckBox"));
    apServerAuthenticationCertificateCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    apServerAuthenticationCertificateLabel = new QLabel(apServerAuthenticationGroupBox);
    apServerAuthenticationCertificateLabel->setObjectName(QString::fromUtf8("apServerAuthenticationCertificateLabel"));
    apServerAuthenticationCertificateLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    apServerAuthenticationCertificateComboBox = new QComboBox(apServerAuthenticationGroupBox);
    apServerAuthenticationCertificateComboBox->setObjectName(QString::fromUtf8("apServerAuthenticationCertificateComboBox"));

    apServerAuthenticationGridLayout->addWidget(apServerAuthenticationNoneCheckBox, 0, 0, 1, 1);
    apServerAuthenticationGridLayout->addWidget(apServerAuthenticationNoneLabel, 0, 1, 1, 1);
    apServerAuthenticationGridLayout->addWidget(apServerAuthenticationNoneComboBox, 0, 2, 1, 1);
    apServerAuthenticationGridLayout->addWidget(apServerAuthenticationPasswordCheckBox, 0, 3, 1, 1);
    apServerAuthenticationGridLayout->addWidget(apServerAuthenticationPasswordLabel, 0, 4, 1, 1);
    apServerAuthenticationGridLayout->addWidget(apServerAuthenticationPasswordComboBox, 0, 5, 1, 1);
    apServerAuthenticationGridLayout->addWidget(apServerAuthenticationWeakCheckBox, 0, 6, 1, 1);
    apServerAuthenticationGridLayout->addWidget(apServerAuthenticationWeakLabel, 0, 7, 1, 1);
    apServerAuthenticationGridLayout->addWidget(apServerAuthenticationWeakComboBox, 0, 8, 1, 1);
    apServerAuthenticationGridLayout->addWidget(apServerAuthenticationStrongCheckBox, 1, 0, 1, 1);
    apServerAuthenticationGridLayout->addWidget(apServerAuthenticationStrongLabel, 1, 1, 1, 1);
    apServerAuthenticationGridLayout->addWidget(apServerAuthenticationStrongComboBox, 1, 2, 1, 1);
    apServerAuthenticationGridLayout->addWidget(apServerAuthenticationCertificateCheckBox, 1, 3, 1, 1);
    apServerAuthenticationGridLayout->addWidget(apServerAuthenticationCertificateLabel, 1, 4, 1, 1);
    apServerAuthenticationGridLayout->addWidget(apServerAuthenticationCertificateComboBox, 1, 5, 1, 1);

    apLDeviceGroupBox = new QGroupBox(apServerGroupBox);
    apLDeviceGroupBox->setObjectName(QString::fromUtf8("apLDeviceGroupBox"));
    apLDeviceGridLayout = new QGridLayout(apLDeviceGroupBox);
    apLDeviceGridLayout->setObjectName(QString::fromUtf8("apLDeviceGridLayout"));

    apIed0InstLabel = new QLabel(apLDeviceGroupBox);
    apIed0InstLabel->setObjectName(QString::fromUtf8("apIed0InstLabel"));
    apIed0InstLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    apIed0InstComboBox = new QComboBox(apLDeviceGroupBox);
    apIed0InstComboBox->setObjectName(QString::fromUtf8("apIed0InstComboBox"));
    apIed0DescCheckBox = new QCheckBox(apLDeviceGroupBox);
    apIed0DescCheckBox->setObjectName(QString::fromUtf8("apIed0DescCheckBox"));
    apIed0DescCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    apIed0DescLabel = new QLabel(apLDeviceGroupBox);
    apIed0DescLabel->setObjectName(QString::fromUtf8("apIed0DescLabel"));
    apIed0DescLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    apIed0DescText = new QLineEdit(apLDeviceGroupBox);
    apIed0DescText->setObjectName(QString::fromUtf8("apIed0DescText"));
    apIed1InstLabel = new QLabel(apLDeviceGroupBox);
    apIed1InstLabel->setObjectName(QString::fromUtf8("apIed1InstLabel"));
    apIed1InstLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    apIed1InstComboBox = new QComboBox(apLDeviceGroupBox);
    apIed1InstComboBox->setObjectName(QString::fromUtf8("apIed1InstComboBox"));
    apIed1DescCheckBox = new QCheckBox(apLDeviceGroupBox);
    apIed1DescCheckBox->setObjectName(QString::fromUtf8("apIed1DescCheckBox"));
    apIed1DescCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    apIed1DescLabel = new QLabel(apLDeviceGroupBox);
    apIed1DescLabel->setObjectName(QString::fromUtf8("apIed1DescLabel"));
    apIed1DescLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    apIed1DescText = new QLineEdit(apLDeviceGroupBox);
    apIed1DescText->setObjectName(QString::fromUtf8("apIed1DescText"));

    apLDeviceGridLayout->addWidget(apIed0InstLabel, 0, 0, 1, 1);
    apLDeviceGridLayout->addWidget(apIed0InstComboBox, 0, 1, 1, 1);
    apLDeviceGridLayout->addWidget(apIed0DescCheckBox, 0, 2, 1, 1);
    apLDeviceGridLayout->addWidget(apIed0DescLabel, 0, 3, 1, 1);
    apLDeviceGridLayout->addWidget(apIed0DescText, 0, 4, 1, 1);
    apLDeviceGridLayout->addWidget(apIed1InstLabel, 1, 0, 1, 1);
    apLDeviceGridLayout->addWidget(apIed1InstComboBox, 1, 1, 1, 1);
    apLDeviceGridLayout->addWidget(apIed1DescCheckBox, 1, 2, 1, 1);
    apLDeviceGridLayout->addWidget(apIed1DescLabel, 1, 3, 1, 1);
    apLDeviceGridLayout->addWidget(apIed1DescText, 1, 4, 1, 1);

    apServerVLayout->addWidget(apServerAttributeGroupBox);
    apServerVLayout->addWidget(apServerAuthenticationGroupBox);
    apServerVLayout->addWidget(apLDeviceGroupBox);

    apVLayout->addWidget(apAttributeGroupBox);
    apVLayout->addWidget(apServerGroupBox);

    QStringList booleanEnum = QStringList()<<tr("false")<<tr("true");
    QStringList LDeviceNameEnum = QStringList()<<tr("LD0")<<tr("RCD");
    setWindowTitle(tr("icdIedAccessPointPage"));

    apAttributeGroupBox->setTitle(tr("AccessPoint Attributes"));
    apNameLabel->setText(tr("name: "));
    apDescCheckBox->setText(QString());
    apDescLabel->setText(tr("desc: "));

    apServerGroupBox->setTitle(tr("Server"));
    apServerAttributeGroupBox->setTitle(tr("Server Attributes"));
    apServerDescCheckBox->setText(QString());
    apServerDescLabel->setText(tr("desc"));
    apServerTimeoutCheckBox->setText(QString());
    apServerTimeoutLabel->setText(tr("timeout"));

    apServerAuthenticationGroupBox->setTitle(tr("Authentication"));
    apServerAuthenticationNoneCheckBox->setText(QString());
    apServerAuthenticationNoneLabel->setText(tr("none: "));
    apServerAuthenticationNoneComboBox->addItems(booleanEnum);
    apServerAuthenticationPasswordCheckBox->setText(QString());
    apServerAuthenticationPasswordLabel->setText(tr("password: "));
    apServerAuthenticationPasswordComboBox->addItems(booleanEnum);
    apServerAuthenticationWeakCheckBox->setText(QString());
    apServerAuthenticationWeakLabel->setText(tr("weak: "));
    apServerAuthenticationWeakComboBox->addItems(booleanEnum);
    apServerAuthenticationStrongCheckBox->setText(QString());
    apServerAuthenticationStrongLabel->setText(tr("strong: "));
    apServerAuthenticationStrongComboBox->addItems(booleanEnum);
    apServerAuthenticationNoneCheckBox->setText(QString());
    apServerAuthenticationCertificateLabel->setText(tr("certificate: "));
    apServerAuthenticationCertificateComboBox->addItems(booleanEnum);

    apLDeviceGroupBox->setTitle(tr("LDevice"));
    apIed0InstLabel->setText(tr("inst: "));
    apIed0InstComboBox->addItems(LDeviceNameEnum);
    apIed0DescCheckBox->setText(QString());
    apIed0DescLabel->setText(tr("desc: "));
    apIed1InstLabel->setText(tr("inst: "));
    apIed1InstComboBox->addItems(LDeviceNameEnum);
    apIed1DescCheckBox->setText(QString());
    apIed1DescLabel->setText(tr("desc: "));
}
