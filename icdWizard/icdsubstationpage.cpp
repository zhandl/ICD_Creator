#include "icdsubstationpage.h"
#include "ui_icdSubstationPage.h"

icdSubstationPage::icdSubstationPage(QWidget *parent) :
    QWizardPage(parent)
{
    setTitle(tr("ICD Substation Setting"));
    setSubTitle(tr("This page can set the attributes of substation segment, if needed."));


    init();

    connect(substationDescCheckBox, SIGNAL(toggled(bool)), substationDescText, SLOT(setEnabled(bool)));
    connect(substationDescCheckBox, SIGNAL(toggled(bool)), substationDescLabel, SLOT(setEnabled(bool)));
    connect(voltageMultiplierCheckBox, SIGNAL(toggled(bool)), voltageMultiplierLabel, SLOT(setEnabled(bool)));
    connect(voltageMultiplierCheckBox, SIGNAL(toggled(bool)), voltageMultiplierComboBox, SLOT(setEnabled(bool)));
    connect(bayDescCheckBox, SIGNAL(toggled(bool)), bayDescLabel, SLOT(setEnabled(bool)));
    connect(bayDescCheckBox, SIGNAL(toggled(bool)), bayDescText, SLOT(setEnabled(bool)));

    bool substationDescIsChecked = substationDescCheckBox->isChecked();
    bool voltageMultiplierIsChecked = voltageMultiplierCheckBox->isChecked();
    bool bayDescIsChecked = bayDescCheckBox->isChecked();
    substationDescText->setEnabled(substationDescIsChecked);
    substationDescLabel->setEnabled(substationDescIsChecked);
    voltageMultiplierLabel->setEnabled(voltageMultiplierIsChecked);
    voltageMultiplierComboBox->setEnabled(voltageMultiplierIsChecked);
    bayDescLabel->setEnabled(bayDescIsChecked);
    bayDescText->setEnabled(bayDescIsChecked);


}

icdSubstationPage::~icdSubstationPage()
{

}

void icdSubstationPage::init()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QString::fromUtf8("icdSubstationPage"));
    this->resize(800, 600);
    verticalLayout = new QVBoxLayout(this);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    substationGroupBox = new QGroupBox(this);
    substationGroupBox->setObjectName(QString::fromUtf8("substationGroupBox"));
    QFont font;
    font.setFamily(QString::fromUtf8("Calibri"));
    font.setPointSize(11);
    substationGroupBox->setFont(font);
    substationGroupBox->setCheckable(true);
    substationGridLayout = new QGridLayout(substationGroupBox);
    substationGridLayout->setObjectName(QString::fromUtf8("substationGridLayout"));
    substationNameLabel = new QLabel(substationGroupBox);
    substationNameLabel->setObjectName(QString::fromUtf8("substationNameLabel"));
    substationNameLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);

    subStationNameText = new QLineEdit(substationGroupBox);
    subStationNameText->setObjectName(QString::fromUtf8("subStationNameText"));
    subStationNameText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    subStationNameText->setStyleSheet(tr("background-color:rgba(255, 255, 200, 255)"));

    substationDescCheckBox = new QCheckBox(substationGroupBox);
    substationDescCheckBox->setObjectName(QString::fromUtf8("substationDescCheckBox"));
    substationDescCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);

    substationDescLabel = new QLabel(substationGroupBox);
    substationDescLabel->setObjectName(QString::fromUtf8("substationDescLabel"));
    substationDescLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);

    substationDescText = new QLineEdit(substationGroupBox);
    substationDescText->setObjectName(QString::fromUtf8("substationDescText"));
    substationDescText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);

    voltageLevelGroupBox = new QGroupBox(substationGroupBox);
    voltageLevelGroupBox->setObjectName(QString::fromUtf8("voltageLevelGroupBox"));

    voltageLevelGridLayout = new QGridLayout(voltageLevelGroupBox);
    voltageLevelGridLayout->setObjectName(QString::fromUtf8("gridLayout_2"));

    voltageLevelNameLabel = new QLabel(voltageLevelGroupBox);
    voltageLevelNameLabel->setObjectName(QString::fromUtf8("votageLevelNameLabel"));
    voltageLevelNameLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);

    voltageLevelNameText = new QLineEdit(voltageLevelGroupBox);
    voltageLevelNameText->setObjectName(QString::fromUtf8("voltageLevelNameText"));
    voltageLevelNameText->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    voltageLevelNameText->setStyleSheet(tr("background-color:rgba(255, 255, 200, 255)"));

    voltageGroupBox = new QGroupBox(voltageLevelGroupBox);
    voltageGroupBox->setObjectName(QString::fromUtf8("voltageGroupBox"));
    voltageGroupBox->setCheckable(true);
    voltageGroupBox->setChecked(false);

    voltageGridLayout = new QGridLayout(voltageGroupBox);
    voltageGridLayout->setObjectName(QString::fromUtf8("voltageGridLayout"));

    voltageUnitLabel = new QLabel(voltageGroupBox);
    voltageUnitLabel->setObjectName(QString::fromUtf8("voltageUnitLabel"));
    voltageUnitLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);

    voltageUnitComboBox = new QComboBox(voltageGroupBox);
    voltageUnitComboBox->setObjectName(QString::fromUtf8("voltageUnitComboBox"));
    voltageUnitComboBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    voltageUnitComboBox->setEnabled(false);

    voltageMultiplierCheckBox = new QCheckBox(voltageGroupBox);
    voltageMultiplierCheckBox->setObjectName(QString::fromUtf8("voltageMultiplierCheckBox"));
    voltageMultiplierCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);

    voltageMultiplierLabel = new QLabel(voltageGroupBox);
    voltageMultiplierLabel->setObjectName(QString::fromUtf8("voltageMultiplierLabel"));
    voltageMultiplierLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);

    voltageMultiplierComboBox = new QComboBox(voltageGroupBox);
    voltageMultiplierComboBox->setObjectName(QString::fromUtf8("voltageMultiplierComboBox"));
    voltageMultiplierComboBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);

    voltageGridLayout->addWidget(voltageUnitLabel, 0, 1, 1, 1);
    voltageGridLayout->addWidget(voltageUnitComboBox, 0, 2, 1, 1);
    voltageGridLayout->addWidget(voltageMultiplierCheckBox, 0, 4, 1, 1);
    voltageGridLayout->addWidget(voltageMultiplierLabel, 0, 5, 1, 1);
    voltageGridLayout->addWidget(voltageMultiplierComboBox, 0, 6, 1, 1);
    voltageGridLayout->setColumnStretch(3,1);
    voltageGridLayout->setColumnStretch(7,2);

    bayGroupBox = new QGroupBox(voltageLevelGroupBox);
    bayGroupBox->setObjectName(QString::fromUtf8("bayGroupBox"));

    bayGridLayout = new QGridLayout(bayGroupBox);
    bayGridLayout->setObjectName(QString::fromUtf8("bayGridLayout"));

    bayNameLabel = new QLabel(bayGroupBox);
    bayNameLabel->setObjectName(QString::fromUtf8("bayNameLabel"));
    bayNameLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);

    bayNameText = new QLineEdit(bayGroupBox);
    bayNameText->setObjectName(QString::fromUtf8("bayNameText"));
    bayNameText->setStyleSheet(tr("background-color:rgba(255, 255, 200, 255)"));

    bayDescCheckBox = new QCheckBox(bayGroupBox);
    bayDescCheckBox->setObjectName(QString::fromUtf8("bayDescCheckBox"));
    bayDescCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);

    bayDescLabel = new QLabel(bayGroupBox);
    bayDescLabel->setObjectName(QString::fromUtf8("bayDescLabel"));
    bayDescLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);

    bayDescText = new QLineEdit(bayGroupBox);
    bayDescText->setObjectName(QString::fromUtf8("bayDescText"));

    bayGridLayout->addWidget(bayNameLabel, 0, 0, 1, 1);
    bayGridLayout->addWidget(bayNameText, 0, 1, 1, 1);
    bayGridLayout->addWidget(bayDescCheckBox, 0, 3, 1, 1);
    bayGridLayout->addWidget(bayDescLabel, 0, 4, 1, 1);
    bayGridLayout->addWidget(bayDescText, 0, 5, 1, 1);
    bayGridLayout->setColumnStretch(2,1);
    bayGridLayout->setColumnStretch(6,2);

    voltageLevelGridLayout->addWidget(voltageLevelNameLabel, 0, 0, 1, 1);
    voltageLevelGridLayout->addWidget(voltageLevelNameText, 0, 1, 1, 1);
    voltageLevelGridLayout->addWidget(voltageGroupBox, 1, 0, 1, 8);
    voltageLevelGridLayout->addWidget(bayGroupBox, 2, 0, 1, 8);

    substationGridLayout->addWidget(substationNameLabel, 0, 1, 1, 1);
    substationGridLayout->addWidget(subStationNameText, 0, 2, 1, 1);
    substationGridLayout->addWidget(substationDescCheckBox, 0, 4, 1, 1);
    substationGridLayout->addWidget(substationDescLabel, 0, 5, 1, 1);
    substationGridLayout->addWidget(substationDescText, 0, 6, 1, 1);
    substationGridLayout->addWidget(voltageLevelGroupBox, 1, 0, 1, 8);
    substationGridLayout->setColumnStretch(3,1);
    substationGridLayout->setColumnStretch(7,1);

    verticalLayout->addWidget(substationGroupBox);

#ifndef QT_NO_SHORTCUT
    substationNameLabel->setBuddy(subStationNameText);
    substationDescLabel->setBuddy(substationDescText);
    voltageLevelNameLabel->setBuddy(voltageLevelNameText);
    voltageUnitLabel->setBuddy(voltageUnitComboBox);
    voltageMultiplierLabel->setBuddy(voltageMultiplierComboBox);
    bayNameLabel->setBuddy(bayNameText);
    bayDescLabel->setBuddy(bayDescText);
#endif // QT_NO_SHORTCUT

    retranslateUi();

    QMetaObject::connectSlotsByName(this);
}

void icdSubstationPage::retranslateUi()
{
    substationGroupBox->setTitle(QApplication::translate("icdSubstationPage", "Substation", 0, QApplication::UnicodeUTF8));
    substationDescCheckBox->setText(QString());
    substationDescLabel->setText(QApplication::translate("icdSubstationPage", "desc", 0, QApplication::UnicodeUTF8));
    substationNameLabel->setText(QApplication::translate("icdSubstationPage", "name", 0, QApplication::UnicodeUTF8));
    subStationNameText->setText(tr("TEMPLATE"));
    voltageLevelGroupBox->setTitle(QApplication::translate("icdSubstationPage", "VoltageLevel", 0, QApplication::UnicodeUTF8));
    voltageLevelNameLabel->setText(QApplication::translate("icdSubstationPage", "name", 0, QApplication::UnicodeUTF8));
    voltageLevelNameText->setText(tr("500kV"));
    bayGroupBox->setTitle(QApplication::translate("icdSubstationPage", "Bay", 0, QApplication::UnicodeUTF8));
    bayNameLabel->setText(QApplication::translate("icdSubstationPage", "name", 0, QApplication::UnicodeUTF8));
    bayNameText->setText(tr("Fields1"));
    bayDescCheckBox->setText(QString());
    bayDescLabel->setText(QApplication::translate("icdSubstationPage", "desc", 0, QApplication::UnicodeUTF8));
    voltageGroupBox->setTitle(QApplication::translate("icdSubstationPage", "Voltage", 0, QApplication::UnicodeUTF8));
    voltageUnitLabel->setText(QApplication::translate("icdSubstationPage", "unit", 0, QApplication::UnicodeUTF8));
    voltageUnitComboBox->clear();
    voltageUnitComboBox->insertItems(0, QStringList()
     << QApplication::translate("icdSubstationPage", "V", 0, QApplication::UnicodeUTF8)
    );
    voltageMultiplierCheckBox->setText(QString());
    voltageMultiplierLabel->setText(QApplication::translate("icdSubstationPage", "multiplier", 0, QApplication::UnicodeUTF8));
    voltageMultiplierComboBox->clear();
    voltageMultiplierComboBox->insertItems(0, QStringList()
     << QApplication::translate("icdSubstationPage", "m", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("icdSubstationPage", "k", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("icdSubstationPage", "M", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("icdSubstationPage", "mu", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("icdSubstationPage", "y", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("icdSubstationPage", "z", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("icdSubstationPage", "a", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("icdSubstationPage", "f", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("icdSubstationPage", "p", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("icdSubstationPage", "n", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("icdSubstationPage", "c", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("icdSubstationPage", "d", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("icdSubstationPage", "da", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("icdSubstationPage", "h", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("icdSubstationPage", "G", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("icdSubstationPage", "T", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("icdSubstationPage", "P", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("icdSubstationPage", "E", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("icdSubstationPage", "Z", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("icdSubstationPage", "Y", 0, QApplication::UnicodeUTF8)
    );
}

void icdSubstationPage::registerData()
{
    if(substationGroupBox->isChecked()) {
        registerField("substationName*", subStationNameText);
        if(substationDescCheckBox->isChecked()) {
            registerField("substationDesc", substationDescText);
        }
        registerField("voltageLeveName*", voltageLevelNameText);
        if(voltageGroupBox->isChecked()) {
            registerField("voltageUnit", voltageUnitComboBox);
            if(voltageMultiplierCheckBox->isChecked())
                registerField("voltageMultiple", voltageMultiplierComboBox);
            registerField("bayName*", bayNameText);
            if(bayDescCheckBox->isChecked())
                registerField("bayDesc", bayDescText);
        }
    }
}
