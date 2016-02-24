#include "editservices.h"
#include "domitem.h"
#include "dommodel.h"
#include "utils.h"

EditServices::EditServices(QWidget *parent) :
    QDialog(parent)
{
    init();
    finishInit();
}

void EditServices::init()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QString::fromUtf8("EditServices"));
    this->resize(800, 600);
    QFont font;
    font.setFamily(QString::fromUtf8("Calibri"));
    font.setPointSize(9);
    setFont(font);

    iedServiceGridLayout = new QGridLayout(this);
    iedServiceGridLayout->setObjectName(QString::fromUtf8("iedServiceGridLayout"));


    iedModeSelLabel = new QLabel(this);
    iedModeSelLabel->setObjectName(QString::fromUtf8("iedModeSelLabel"));
    iedModeSelComboBox = new QComboBox(this);
    iedModeSelComboBox->setObjectName(QString::fromUtf8("iedModeSelComboBox"));

    servicesGroupBox = new QGroupBox(this);
    servicesGroupBox->setObjectName(QString::fromUtf8("servicesGroupBox"));

    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy5.setHorizontalStretch(0);
    sizePolicy5.setVerticalStretch(0);
    sizePolicy5.setHeightForWidth(buttonBox->sizePolicy().hasHeightForWidth());
    buttonBox->setSizePolicy(sizePolicy5);
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    buttonBox->setCenterButtons(false);

    iedServiceGridLayout->addWidget(iedModeSelLabel, 0, 9, 1, 1);
    iedServiceGridLayout->addWidget(iedModeSelComboBox, 0, 10, 1, 1);
    iedServiceGridLayout->addWidget(servicesGroupBox, 1, 0, 1, 12);
    iedServiceGridLayout->addWidget(buttonBox, 2, 10, 1, 1);

    servicesGridLayout = new QGridLayout(servicesGroupBox);
    servicesGridLayout->setObjectName(QString::fromUtf8("servicesGridLayout"));

    servicesWOAttrGroupBox = new QGroupBox(servicesGroupBox);
    servicesWOAttrGroupBox->setObjectName(QString::fromUtf8("servicesWOAttrGroupBox"));
    servicesWOAttrGridLayout = new QGridLayout(servicesWOAttrGroupBox);
    servicesWOAttrGridLayout->setObjectName(QString::fromUtf8("servicesWOAttrGridLayout"));

    dynAssociationCheckBox = new QCheckBox(servicesWOAttrGroupBox);
    dynAssociationCheckBox->setObjectName(QString::fromUtf8("dynAssociationCheckBox"));
    dynAssociationCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    dynAssociationLabel = new QLabel(servicesWOAttrGroupBox);
    dynAssociationLabel->setObjectName(QString::fromUtf8("dynAssociationLabel"));

    getDirectoryCheckBox = new QCheckBox(servicesWOAttrGroupBox);
    getDirectoryCheckBox->setObjectName(QString::fromUtf8("getDirectoryCheckBox"));
    getDirectoryCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    getDirectoryLabel = new QLabel(servicesWOAttrGroupBox);
    getDirectoryLabel->setObjectName(QString::fromUtf8("getDirectoryLabel"));

    getDataObjectDefinitionCheckBox = new QCheckBox(servicesWOAttrGroupBox);
    getDataObjectDefinitionCheckBox->setObjectName(QString::fromUtf8("getDataObjectDefinitionCheckBox"));
    getDataObjectDefinitionCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    getDataObjectDefinitionLabel = new QLabel(servicesWOAttrGroupBox);
    getDataObjectDefinitionLabel->setObjectName(QString::fromUtf8("getDataObjectDefinitionLabel"));

    dataObjectDirectoryCheckBox = new QCheckBox(servicesWOAttrGroupBox);
    dataObjectDirectoryCheckBox->setObjectName(QString::fromUtf8("dataObjectDirectoryCheckBox"));
    dataObjectDirectoryCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    dataObjectDirectoryLabel = new QLabel(servicesWOAttrGroupBox);
    dataObjectDirectoryLabel->setObjectName(QString::fromUtf8("dataObjectDirectoryLabel"));

    getDataSetValueCheckBox = new QCheckBox(servicesWOAttrGroupBox);
    getDataSetValueCheckBox->setObjectName(QString::fromUtf8("getDataValueCheckBox"));
    getDataSetValueCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    getDataSetValueLabel = new QLabel(servicesWOAttrGroupBox);
    getDataSetValueLabel->setObjectName(QString::fromUtf8("getDataValueLabel"));

    setDataSetValueCheckBox = new QCheckBox(servicesWOAttrGroupBox);
    setDataSetValueCheckBox->setObjectName(QString::fromUtf8("setDataSetValueCheckBox"));
    setDataSetValueCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    setDataSetValueLabel = new QLabel(servicesWOAttrGroupBox);
    setDataSetValueLabel->setObjectName(QString::fromUtf8("setDataSetValueLabel"));

    dataSetDirectoryCheckBox = new QCheckBox(servicesWOAttrGroupBox);
    dataSetDirectoryCheckBox->setObjectName(QString::fromUtf8("dataSetDirectoryCheckBox"));
    dataSetDirectoryCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    dataSetDirectoryLabel = new QLabel(servicesWOAttrGroupBox);
    dataSetDirectoryLabel->setObjectName(QString::fromUtf8("dataSetDirectoryLabel"));

    readWriteCheckBox = new QCheckBox(servicesWOAttrGroupBox);
    readWriteCheckBox->setObjectName(QString::fromUtf8("readWriteCheckBox"));
    readWriteCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    readWriteLabel = new QLabel(servicesWOAttrGroupBox);
    readWriteLabel->setObjectName(QString::fromUtf8("readWriteLabel"));

    timerActivatedControlCheckBox = new QCheckBox(servicesWOAttrGroupBox);
    timerActivatedControlCheckBox->setObjectName(QString::fromUtf8("timerActivatedContorlCheckBox"));
    timerActivatedControlCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    timerActivatedControlLabel = new QLabel(servicesWOAttrGroupBox);
    timerActivatedControlLabel->setObjectName(QString::fromUtf8("timerActivatedControlLabel"));

    getCBValuesCheckBox = new QCheckBox(servicesWOAttrGroupBox);
    getCBValuesCheckBox->setObjectName(QString::fromUtf8("getCBValuesCheckBox"));
    getCBValuesCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    getCBValuesLabel = new QLabel(servicesWOAttrGroupBox);
    getCBValuesLabel->setObjectName(QString::fromUtf8("getCBValuesLabel"));

    gseDirCheckBox = new QCheckBox(servicesWOAttrGroupBox);
    gseDirCheckBox->setObjectName(QString::fromUtf8("gseDirCheckBox"));
    gseDirCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    gseDirLabel = new QLabel(servicesWOAttrGroupBox);
    gseDirLabel->setObjectName(QString::fromUtf8("gseDirLabel"));

    fileHandlingCheckBox = new QCheckBox(servicesWOAttrGroupBox);
    fileHandlingCheckBox->setObjectName(QString::fromUtf8("fileHandlingCheckBox"));
    fileHandlingCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    fileHandlingLabel = new QLabel(servicesWOAttrGroupBox);
    fileHandlingLabel->setObjectName(QString::fromUtf8("fileHandlingLabel"));

    servicesWOAttrGridLayout->addWidget(dynAssociationCheckBox, 0, 0, 1, 1);
    servicesWOAttrGridLayout->addWidget(dynAssociationLabel, 0, 1, 1, 1);
    servicesWOAttrGridLayout->addWidget(getDirectoryCheckBox, 0, 2, 1, 1);
    servicesWOAttrGridLayout->addWidget(getDirectoryLabel, 0, 3, 1, 1);
    servicesWOAttrGridLayout->addWidget(getDataObjectDefinitionCheckBox, 0, 4, 1, 1);
    servicesWOAttrGridLayout->addWidget(getDataObjectDefinitionLabel, 0, 5, 1, 1);
    servicesWOAttrGridLayout->addWidget(dataObjectDirectoryCheckBox, 0, 6, 1, 1);
    servicesWOAttrGridLayout->addWidget(dataObjectDirectoryLabel, 0, 7, 1, 1);
    servicesWOAttrGridLayout->addWidget(getDataSetValueCheckBox, 1, 0, 1, 1);
    servicesWOAttrGridLayout->addWidget(getDataSetValueLabel, 1, 1, 1, 1);
    servicesWOAttrGridLayout->addWidget(setDataSetValueCheckBox, 1, 2, 1, 1);
    servicesWOAttrGridLayout->addWidget(setDataSetValueLabel, 1, 3, 1, 1);
    servicesWOAttrGridLayout->addWidget(dataSetDirectoryCheckBox, 1, 4, 1, 1);
    servicesWOAttrGridLayout->addWidget(dataSetDirectoryLabel, 1, 5, 1, 1);
    servicesWOAttrGridLayout->addWidget(readWriteCheckBox, 1, 6, 1, 1);
    servicesWOAttrGridLayout->addWidget(readWriteLabel, 1, 7, 1, 1);
    servicesWOAttrGridLayout->addWidget(timerActivatedControlCheckBox, 2, 0, 1, 1);
    servicesWOAttrGridLayout->addWidget(timerActivatedControlLabel, 2, 1, 1, 1);
    servicesWOAttrGridLayout->addWidget(getCBValuesCheckBox, 2, 2, 1, 1);
    servicesWOAttrGridLayout->addWidget(getCBValuesLabel, 2, 3, 1, 1);
    servicesWOAttrGridLayout->addWidget(gseDirCheckBox, 2, 4, 1, 1);
    servicesWOAttrGridLayout->addWidget(gseDirLabel, 2, 5, 1, 1);
    servicesWOAttrGridLayout->addWidget(fileHandlingCheckBox, 2, 6, 1, 1);
    servicesWOAttrGridLayout->addWidget(fileHandlingLabel, 2, 7, 1, 1);

    gooseGroupBox = new QGroupBox(servicesGroupBox);
    gooseGroupBox->setObjectName(QString::fromUtf8("gooseGroupBox"));
    gooseGroupBox->setCheckable(true);
    gooseHLayout = new QHBoxLayout(gooseGroupBox);
    gooseHLayout->setObjectName(QString::fromUtf8("gooseHLayout"));

    gooseMaxLabel = new QLabel(gooseGroupBox);
    gooseMaxLabel->setObjectName(QString::fromUtf8("gooseMaxLabel"));
    gooseMaxText = new QLineEdit(gooseGroupBox);
    gooseMaxText->setObjectName(QString::fromUtf8("gooseMaxText"));

    gooseHLayout->addWidget(gooseMaxLabel);
    gooseHLayout->addWidget(gooseMaxText);

    gsseGroupBox = new QGroupBox(servicesGroupBox);
    gsseGroupBox->setObjectName(QString::fromUtf8("gsseGroupBox"));
    gsseGroupBox->setCheckable(true);
    gsseHLayout = new QHBoxLayout(gsseGroupBox);
    gsseHLayout->setObjectName(QString::fromUtf8("gsseHLayout"));

    gsseMaxLabel = new QLabel(gsseGroupBox);
    gsseMaxLabel->setObjectName(QString::fromUtf8("gsseMaxLabel"));
    gsseMaxText = new QLineEdit(gsseGroupBox);
    gsseMaxText->setObjectName(QString::fromUtf8("gsseMaxText"));

    gsseHLayout->addWidget(gsseMaxLabel);
    gsseHLayout->addWidget(gsseMaxText);

    confDataSetGroupBox = new QGroupBox(servicesGroupBox);
    confDataSetGroupBox->setObjectName(QString::fromUtf8("confDataSetGroupBox"));
    confDataSetGroupBox->setCheckable(true);
    confDataSetGridLayout = new QGridLayout(confDataSetGroupBox);
    confDataSetGridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    confDataSetMaxLabel = new QLabel(confDataSetGroupBox);
    confDataSetMaxLabel->setObjectName(QString::fromUtf8("confDataSetMaxLabel"));
    confDataSetMaxText = new QLineEdit(confDataSetGroupBox);
    confDataSetMaxText->setObjectName(QString::fromUtf8("confDataSetMaxText"));

    confDataSetMaxAttrLabel = new QLabel(confDataSetGroupBox);
    confDataSetMaxAttrLabel->setObjectName(QString::fromUtf8("confDataSetMaxAttrLabel"));
    confDataSetMaxAttrText = new QLineEdit(confDataSetGroupBox);
    confDataSetMaxAttrText->setObjectName(QString::fromUtf8("confDataSetMaxAttrText"));

    confDataSetGridLayout->addWidget(confDataSetMaxLabel, 0, 0, 1, 1);
    confDataSetGridLayout->addWidget(confDataSetMaxText, 0, 2, 1, 1);
    confDataSetGridLayout->addWidget(confDataSetMaxAttrLabel, 1, 0, 1, 2);
    confDataSetGridLayout->addWidget(confDataSetMaxAttrText, 1, 2, 1, 1);


    confReportControlGroupBox = new QGroupBox(servicesGroupBox);
    confReportControlGroupBox->setObjectName(QString::fromUtf8("confReportControlGroupBox"));
    confReportControlGroupBox->setCheckable(true);
    confReportControlHLayout = new QHBoxLayout(confReportControlGroupBox);
    confReportControlHLayout->setObjectName(QString::fromUtf8("confReportControlHLayout"));

    confReportControlMaxLabel = new QLabel(confReportControlGroupBox);
    confReportControlMaxLabel->setObjectName(QString::fromUtf8("confReportControlMaxLabel"));
    confReportControlMaxText = new QLineEdit(confReportControlGroupBox);
    confReportControlMaxText->setObjectName(QString::fromUtf8("confReportControlMaxText"));

    confReportControlHLayout->addWidget(confReportControlMaxLabel);
    confReportControlHLayout->addWidget(confReportControlMaxText);

    confLogControlGroupBox = new QGroupBox(servicesGroupBox);
    confLogControlGroupBox->setObjectName(QString::fromUtf8("confLogControlGroupBox"));
    confLogControlGroupBox->setCheckable(true);
    confLogControlHLayout = new QHBoxLayout(confLogControlGroupBox);
    confLogControlHLayout->setObjectName(QString::fromUtf8("confLogControlHLayout"));

    conLogControlMaxLabel = new QLabel(confLogControlGroupBox);
    conLogControlMaxLabel->setObjectName(QString::fromUtf8("conLogControlMaxLabel"));
    confLogControlMaxText = new QLineEdit(confLogControlGroupBox);
    confLogControlMaxText->setObjectName(QString::fromUtf8("confLogControlMaxText"));

    confLogControlHLayout->addWidget(conLogControlMaxLabel);
    confLogControlHLayout->addWidget(confLogControlMaxText);

    dynDataSetGroupBox = new QGroupBox(servicesGroupBox);
    dynDataSetGroupBox->setObjectName(QString::fromUtf8("dynDataSetGroupBox"));
    dynDataSetGroupBox->setCheckable(true);
    dynDataSetGridLayout = new QGridLayout(dynDataSetGroupBox);
    dynDataSetGridLayout->setObjectName(QString::fromUtf8("dynDataSetGridLayout"));

    dynDataSetMaxLabel = new QLabel(dynDataSetGroupBox);
    dynDataSetMaxLabel->setObjectName(QString::fromUtf8("dynDataSetMaxLabel"));
    dynDataSetMaxText = new QLineEdit(dynDataSetGroupBox);
    dynDataSetMaxText->setObjectName(QString::fromUtf8("dynDataSetMaxText"));

    dynDataSetMaxAttrLabel = new QLabel(dynDataSetGroupBox);
    dynDataSetMaxAttrLabel->setObjectName(QString::fromUtf8("dynDataSetMaxAttrLabel"));
    dynDataSetMaxAttrText = new QLineEdit(dynDataSetGroupBox);
    dynDataSetMaxAttrText->setObjectName(QString::fromUtf8("dynDataSetMaxAttrText"));

    dynDataSetGridLayout->addWidget(dynDataSetMaxLabel, 0, 0, 1, 1);
    dynDataSetGridLayout->addWidget(dynDataSetMaxText, 0, 1, 1, 1);
    dynDataSetGridLayout->addWidget(dynDataSetMaxAttrLabel, 1, 0, 1, 1);
    dynDataSetGridLayout->addWidget(dynDataSetMaxAttrText, 1, 1, 1, 1);


    reportSettingsGroupBox = new QGroupBox(servicesGroupBox);
    reportSettingsGroupBox->setObjectName(QString::fromUtf8("reportSettingsGroupBox"));
    reportSettingsGroupBox->setCheckable(true);
    reportSettingsGridLayout = new QGridLayout(reportSettingsGroupBox);
    reportSettingsGridLayout->setObjectName(QString::fromUtf8("reportSettingsGridLayout"));

    reportSettingsCbNameCheckBox = new QCheckBox(reportSettingsGroupBox);
    reportSettingsCbNameCheckBox->setObjectName(QString::fromUtf8("reportSettingsCbNameCheckBox"));
    reportSettingsCbNameCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    reportSettingsCbNameLabel = new QLabel(reportSettingsGroupBox);
    reportSettingsCbNameLabel->setObjectName(QString::fromUtf8("reportSettingsCbNameLabel"));
    reportSettingsCbNameComboBox = new QComboBox(reportSettingsGroupBox);
    reportSettingsCbNameComboBox->setObjectName(QString::fromUtf8("reportSettingsCbNameComboBox"));

    reportSettingsDatSetCheckBox = new QCheckBox(reportSettingsGroupBox);
    reportSettingsDatSetCheckBox->setObjectName(QString::fromUtf8("reportSettingsDatSetCheckBox"));
    reportSettingsDatSetCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    reportSettingsDatSetLabel = new QLabel(reportSettingsGroupBox);
    reportSettingsDatSetLabel->setObjectName(QString::fromUtf8("reportSettingsDatSetLabel"));
    reportSettingsDatSetComboBox = new QComboBox(reportSettingsGroupBox);
    reportSettingsDatSetComboBox->setObjectName(QString::fromUtf8("reportSettingsDatSetComboBox"));

    reportSettingsRptIdCheckBox = new QCheckBox(reportSettingsGroupBox);
    reportSettingsRptIdCheckBox->setObjectName(QString::fromUtf8("reportSettingsRptIdCheckBox"));
    reportSettingsRptIdCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    reportSettingsRptIdLabel = new QLabel(reportSettingsGroupBox);
    reportSettingsRptIdLabel->setObjectName(QString::fromUtf8("reportSettingsRptIdLabel"));
    reportSettingsRptIdComboBox = new QComboBox(reportSettingsGroupBox);
    reportSettingsRptIdComboBox->setObjectName(QString::fromUtf8("reportSettingsRptIdComboBox"));

    reportSettingsOptFieldsCheckBox = new QCheckBox(reportSettingsGroupBox);
    reportSettingsOptFieldsCheckBox->setObjectName(QString::fromUtf8("reportSettingsOptFieldsCheckBox"));
    reportSettingsOptFieldsCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    reportSettingsOptFieldsLabel = new QLabel(reportSettingsGroupBox);
    reportSettingsOptFieldsLabel->setObjectName(QString::fromUtf8("reportSettingsOptFieldsLabel"));
    reportSettingsOptFieldsComboBox = new QComboBox(reportSettingsGroupBox);
    reportSettingsOptFieldsComboBox->setObjectName(QString::fromUtf8("reportSettingsOptFieldsComboBox"));

    reportSettingsBufTimeCheckBox = new QCheckBox(reportSettingsGroupBox);
    reportSettingsBufTimeCheckBox->setObjectName(QString::fromUtf8("reportSettingsBufTimeCheckBox"));
    reportSettingsBufTimeCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    reportSettingsBufTimeLabel = new QLabel(reportSettingsGroupBox);
    reportSettingsBufTimeLabel->setObjectName(QString::fromUtf8("reportSettingsBufTimeLabel"));
    reportSettingsBufTimeComboBox = new QComboBox(reportSettingsGroupBox);
    reportSettingsBufTimeComboBox->setObjectName(QString::fromUtf8("reportSettingsBufTimeComboBox"));

    reportSettingsTrgOpsCheckBox = new QCheckBox(reportSettingsGroupBox);
    reportSettingsTrgOpsCheckBox->setObjectName(QString::fromUtf8("reportSettingsTrgOpsCheckBox"));
    reportSettingsTrgOpsCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    reportSettingsTrgOpsLabel = new QLabel(reportSettingsGroupBox);
    reportSettingsTrgOpsLabel->setObjectName(QString::fromUtf8("reportSettingsTrgOpsLabel"));
    reportSettingsTrgOpsComboBox = new QComboBox(reportSettingsGroupBox);
    reportSettingsTrgOpsComboBox->setObjectName(QString::fromUtf8("reportSettingsTrgOpsComboBox"));

    reportSettingsIntgPdCheckBox = new QCheckBox(reportSettingsGroupBox);
    reportSettingsIntgPdCheckBox->setObjectName(QString::fromUtf8("reportSettingsIntgPdCheckBox"));
    reportSettingsIntgPdCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    reportSettingsIntgPdLabel = new QLabel(reportSettingsGroupBox);
    reportSettingsIntgPdLabel->setObjectName(QString::fromUtf8("reportSettingsIntgPdLabel"));
    reportSettingsIntgPdComboBox = new QComboBox(reportSettingsGroupBox);
    reportSettingsIntgPdComboBox->setObjectName(QString::fromUtf8("reportSettingsIntgPdComboBox"));

    reportSettingsGridLayout->addWidget(reportSettingsCbNameCheckBox, 0, 0, 1, 1);
    reportSettingsGridLayout->addWidget(reportSettingsCbNameLabel, 0, 1, 1, 1);
    reportSettingsGridLayout->addWidget(reportSettingsCbNameComboBox, 0, 2, 1, 1);
    reportSettingsGridLayout->addWidget(reportSettingsDatSetCheckBox, 0, 3, 1, 1);
    reportSettingsGridLayout->addWidget(reportSettingsDatSetLabel, 0, 4, 1, 1);
    reportSettingsGridLayout->addWidget(reportSettingsDatSetComboBox, 0, 5, 1, 1);
    reportSettingsGridLayout->addWidget(reportSettingsRptIdCheckBox, 1, 0, 1, 1);
    reportSettingsGridLayout->addWidget(reportSettingsRptIdLabel, 1, 1, 1, 1);
    reportSettingsGridLayout->addWidget(reportSettingsRptIdComboBox, 1, 2, 1, 1);
    reportSettingsGridLayout->addWidget(reportSettingsOptFieldsCheckBox, 1, 3, 1, 1);
    reportSettingsGridLayout->addWidget(reportSettingsOptFieldsLabel, 1, 4, 1, 1);
    reportSettingsGridLayout->addWidget(reportSettingsOptFieldsComboBox, 1, 5, 1, 1);
    reportSettingsGridLayout->addWidget(reportSettingsBufTimeCheckBox, 2, 0, 1, 1);
    reportSettingsGridLayout->addWidget(reportSettingsBufTimeLabel, 2, 1, 1, 1);
    reportSettingsGridLayout->addWidget(reportSettingsBufTimeComboBox, 2, 2, 1, 1);
    reportSettingsGridLayout->addWidget(reportSettingsTrgOpsCheckBox, 2, 3, 1, 1);
    reportSettingsGridLayout->addWidget(reportSettingsTrgOpsLabel, 2, 4, 1, 1);
    reportSettingsGridLayout->addWidget(reportSettingsTrgOpsComboBox, 2, 5, 1, 1);
    reportSettingsGridLayout->addWidget(reportSettingsIntgPdCheckBox, 3, 0, 1, 1);
    reportSettingsGridLayout->addWidget(reportSettingsIntgPdLabel, 3, 1, 1, 1);
    reportSettingsGridLayout->addWidget(reportSettingsIntgPdComboBox, 3, 2, 1, 1);


    logSettingsGroupBox = new QGroupBox(servicesGroupBox);
    logSettingsGroupBox->setObjectName(QString::fromUtf8("logSettingsGroupBox"));
    logSettingsGroupBox->setCheckable(true);

    logSettingsGridLayout = new QGridLayout(logSettingsGroupBox);
    logSettingsGridLayout->setObjectName(QString::fromUtf8("logSettingsGridLayout"));

    logSettingsCbNameCheckBox = new QCheckBox(logSettingsGroupBox);
    logSettingsCbNameCheckBox->setObjectName(QString::fromUtf8("logSettingsCbNameCheckBox"));
    logSettingsCbNameCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    logSettingsCbNameLabel = new QLabel(logSettingsGroupBox);
    logSettingsCbNameLabel->setObjectName(QString::fromUtf8("logSettingsCbNameLabel"));
    logSettingsCbNameComboBox = new QComboBox(logSettingsGroupBox);
    logSettingsCbNameComboBox->setObjectName(QString::fromUtf8("logSettingsCbNameComboBox"));

    logSettingsDatSetCheckBox = new QCheckBox(logSettingsGroupBox);
    logSettingsDatSetCheckBox->setObjectName(QString::fromUtf8("logSettingsDatSetCheckBox"));
    logSettingsDatSetCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    logSettingsDatSetLabel = new QLabel(logSettingsGroupBox);
    logSettingsDatSetLabel->setObjectName(QString::fromUtf8("logSettingsDatSetLabel"));
    logSettingsDatSetComboBox = new QComboBox(logSettingsGroupBox);
    logSettingsDatSetComboBox->setObjectName(QString::fromUtf8("logSettingsDatSetComboBox"));

    logSettingsLogEnaCheckBox = new QCheckBox(logSettingsGroupBox);
    logSettingsLogEnaCheckBox->setObjectName(QString::fromUtf8("logSettingsLogEnaCheckBox"));
    logSettingsLogEnaCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    logSettingsLogEnaLabel = new QLabel(logSettingsGroupBox);
    logSettingsLogEnaLabel->setObjectName(QString::fromUtf8("logSettingsLogEnaLabel"));
    logSettingsLogEnaComboBox = new QComboBox(logSettingsGroupBox);
    logSettingsLogEnaComboBox->setObjectName(QString::fromUtf8("logSettingsLogEnaComboBox"));

    logSettingsTrgOpsCheckBox = new QCheckBox(logSettingsGroupBox);
    logSettingsTrgOpsCheckBox->setObjectName(QString::fromUtf8("logSettingsTrgOpsCheckBox"));
    logSettingsTrgOpsCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    logSettingsTrgOpsLabel = new QLabel(logSettingsGroupBox);
    logSettingsTrgOpsLabel->setObjectName(QString::fromUtf8("logSettingsTrgOpsLabel"));
    logSettingsTrgOpsComboBox = new QComboBox(logSettingsGroupBox);
    logSettingsTrgOpsComboBox->setObjectName(QString::fromUtf8("logSettingsTrgOpsComboBox"));

    logSettingsIntgPdCheckBox = new QCheckBox(logSettingsGroupBox);
    logSettingsIntgPdCheckBox->setObjectName(QString::fromUtf8("logSettingsIntgPdCheckBox"));
    logSettingsIntgPdCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    logSettingsIntgPdLabel = new QLabel(logSettingsGroupBox);
    logSettingsIntgPdLabel->setObjectName(QString::fromUtf8("logSettingsIntgPdLabel"));
    logSettingsIntgPdComboBox = new QComboBox(logSettingsGroupBox);
    logSettingsIntgPdComboBox->setObjectName(QString::fromUtf8("logSettingsIntgPdComboBox"));

    logSettingsGridLayout->addWidget(logSettingsCbNameCheckBox, 0, 0, 1, 1);
    logSettingsGridLayout->addWidget(logSettingsCbNameLabel, 0, 1, 1, 1);
    logSettingsGridLayout->addWidget(logSettingsCbNameComboBox, 0, 2, 1, 1);
    logSettingsGridLayout->addWidget(logSettingsDatSetCheckBox, 0, 3, 1, 1);
    logSettingsGridLayout->addWidget(logSettingsDatSetLabel, 0, 4, 1, 1);
    logSettingsGridLayout->addWidget(logSettingsDatSetComboBox, 0, 5, 1, 1);
    logSettingsGridLayout->addWidget(logSettingsLogEnaCheckBox, 1, 0, 1, 1);
    logSettingsGridLayout->addWidget(logSettingsLogEnaLabel, 1, 1, 1, 1);
    logSettingsGridLayout->addWidget(logSettingsLogEnaComboBox, 1, 2, 1, 1);
    logSettingsGridLayout->addWidget(logSettingsTrgOpsCheckBox, 1, 3, 1, 1);
    logSettingsGridLayout->addWidget(logSettingsTrgOpsLabel, 1, 4, 1, 1);
    logSettingsGridLayout->addWidget(logSettingsTrgOpsComboBox, 1, 5, 1, 1);
    logSettingsGridLayout->addWidget(logSettingsIntgPdCheckBox, 2, 0, 1, 1);
    logSettingsGridLayout->addWidget(logSettingsIntgPdLabel, 2, 1, 1, 1);
    logSettingsGridLayout->addWidget(logSettingsIntgPdComboBox, 2, 2, 1, 1);

    settingGroupsGroupBox = new QGroupBox(servicesGroupBox);
    settingGroupsGroupBox->setObjectName(QString::fromUtf8("settingGroupsGroupBox"));
    settingGroupsGroupBox->setCheckable(true);

    settingGroupsGridLayout = new QGridLayout(settingGroupsGroupBox);
    settingGroupsGridLayout->setObjectName(QString::fromUtf8("settingGroupsGridLayout"));

    settingGroupsSGEditCheckBox = new QCheckBox(settingGroupsGroupBox);
    settingGroupsSGEditCheckBox->setObjectName(QString::fromUtf8("settingGroupsSGEditCheckBox"));
    settingGroupsSGEditCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    settingGroupsSGEditLabel = new QLabel(settingGroupsGroupBox);
    settingGroupsSGEditLabel->setObjectName(QString::fromUtf8("settingGroupsSGEditLabel"));

    settingGroupsConfSGCheckBox = new QCheckBox(settingGroupsGroupBox);
    settingGroupsConfSGCheckBox->setObjectName(QString::fromUtf8("settingGroupsConfSGCheckBox"));
    settingGroupsConfSGCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    settingGroupsConfSGLabel = new QLabel(settingGroupsGroupBox);
    settingGroupsConfSGLabel->setObjectName(QString::fromUtf8("settingGroupsConfSGLabel"));

    settingGroupsGridLayout->addWidget(settingGroupsSGEditCheckBox, 0, 0, 1, 1);
    settingGroupsGridLayout->addWidget(settingGroupsSGEditLabel, 0, 1, 1, 1);
    settingGroupsGridLayout->addWidget(settingGroupsConfSGCheckBox, 0, 2, 1, 1);
    settingGroupsGridLayout->addWidget(settingGroupsConfSGLabel, 0, 3, 1, 1);

    gseSettingsGroupBox = new QGroupBox(servicesGroupBox);
    gseSettingsGroupBox->setObjectName(QString::fromUtf8("gseSettingsGroupBox"));
    gseSettingsGroupBox->setCheckable(true);

    gseSettingsGridLayout = new QGridLayout(gseSettingsGroupBox);
    gseSettingsGridLayout->setObjectName(QString::fromUtf8("gseSettingsGridLayout"));

    gseSettingsCbNameCheckBox = new QCheckBox(gseSettingsGroupBox);
    gseSettingsCbNameCheckBox->setObjectName(QString::fromUtf8("gseSettingsCbNameCheckBox"));
    gseSettingsCbNameCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    gseSettingsCbNameLabel = new QLabel(gseSettingsGroupBox);
    gseSettingsCbNameLabel->setObjectName(QString::fromUtf8("gseSettingsCbNameLabel"));
    gseSettingsCbNameComboBox = new QComboBox(gseSettingsGroupBox);
    gseSettingsCbNameComboBox->setObjectName(QString::fromUtf8("gseSettingsCbNameComboBox"));

    gseSettingsDatSetCheckBox = new QCheckBox(gseSettingsGroupBox);
    gseSettingsDatSetCheckBox->setObjectName(QString::fromUtf8("gseSettingsDatSetCheckBox"));
    gseSettingsDatSetCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    gseSettingsDatSetLabel = new QLabel(gseSettingsGroupBox);
    gseSettingsDatSetLabel->setObjectName(QString::fromUtf8("gseSettingsDatSetLabel"));
    gseSettingsDatSetComboBox = new QComboBox(gseSettingsGroupBox);
    gseSettingsDatSetComboBox->setObjectName(QString::fromUtf8("gseSettingsDatSetComboBox"));

    gseSettingsAppIDCheckBox = new QCheckBox(gseSettingsGroupBox);
    gseSettingsAppIDCheckBox->setObjectName(QString::fromUtf8("gseSettingsAppIDCheckBox"));
    gseSettingsAppIDCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    gseSettingsAppIDLabel = new QLabel(gseSettingsGroupBox);
    gseSettingsAppIDLabel->setObjectName(QString::fromUtf8("gseSettingsAppIDLabel"));
    gseSettingsAppIDComboBox = new QComboBox(gseSettingsGroupBox);
    gseSettingsAppIDComboBox->setObjectName(QString::fromUtf8("gseSettingsAppIDComboBox"));

    gseSettingsDataLabelCheckBox = new QCheckBox(gseSettingsGroupBox);
    gseSettingsDataLabelCheckBox->setObjectName(QString::fromUtf8("gseSettingsDataLabelCheckBox"));
    gseSettingsDataLabelCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    gseSettingsDataLabelLabel = new QLabel(gseSettingsGroupBox);
    gseSettingsDataLabelLabel->setObjectName(QString::fromUtf8("gseSettingsDataLabelLabel"));
    gseSettingsDataLabelComboBox = new QComboBox(gseSettingsGroupBox);
    gseSettingsDataLabelComboBox->setObjectName(QString::fromUtf8("gseSettingsDataLabelComboBox"));

    gseSettingsGridLayout->addWidget(gseSettingsCbNameCheckBox, 0, 0, 1, 1);
    gseSettingsGridLayout->addWidget(gseSettingsCbNameLabel, 0, 1, 1, 1);
    gseSettingsGridLayout->addWidget(gseSettingsCbNameComboBox, 0, 2, 1, 1);
    gseSettingsGridLayout->addWidget(gseSettingsDatSetCheckBox, 0, 3, 1, 1);
    gseSettingsGridLayout->addWidget(gseSettingsDatSetLabel, 0, 4, 1, 1);
    gseSettingsGridLayout->addWidget(gseSettingsDatSetComboBox, 0, 5, 1, 1);
    gseSettingsGridLayout->addWidget(gseSettingsAppIDCheckBox, 1, 0, 1, 1);
    gseSettingsGridLayout->addWidget(gseSettingsAppIDLabel, 1, 1, 1, 1);
    gseSettingsGridLayout->addWidget(gseSettingsAppIDComboBox, 1, 2, 1, 1);
    gseSettingsGridLayout->addWidget(gseSettingsDataLabelCheckBox, 1, 3, 1, 1);
    gseSettingsGridLayout->addWidget(gseSettingsDataLabelLabel, 1, 4, 1, 1);
    gseSettingsGridLayout->addWidget(gseSettingsDataLabelComboBox, 1, 5, 1, 1);

    smvSettingsGroupBox = new QGroupBox(servicesGroupBox);
    smvSettingsGroupBox->setObjectName(QString::fromUtf8("smvSettingsGroupBox"));
    smvSettingsGroupBox->setCheckable(true);

    smvSettingsGridLayout = new QGridLayout(smvSettingsGroupBox);
    smvSettingsGridLayout->setObjectName(QString::fromUtf8("smvSettingsGridLayout"));

    smvSettingsCbNameCheckBox = new QCheckBox(smvSettingsGroupBox);
    smvSettingsCbNameCheckBox->setObjectName(QString::fromUtf8("smvSettingsCbNameCheckBox"));
    smvSettingsCbNameCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    smvSettingsCbNameLabel = new QLabel(smvSettingsGroupBox);
    smvSettingsCbNameLabel->setObjectName(QString::fromUtf8("smvSettingsCbNameLabel"));
    smvSettingsCbNameComboBox = new QComboBox(smvSettingsGroupBox);
    smvSettingsCbNameComboBox->setObjectName(QString::fromUtf8("smvSettingsCbNameComboBox"));

    smvSettingsDatSetCheckBox = new QCheckBox(smvSettingsGroupBox);
    smvSettingsDatSetCheckBox->setObjectName(QString::fromUtf8("smvSettingsDatSetCheckBox"));
    smvSettingsDatSetCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    smvSettingsDatSetLabel = new QLabel(smvSettingsGroupBox);
    smvSettingsDatSetLabel->setObjectName(QString::fromUtf8("smvSettingsDatSetLabel"));
    smvSettingsDatSetComboBox = new QComboBox(smvSettingsGroupBox);
    smvSettingsDatSetComboBox->setObjectName(QString::fromUtf8("smvSettingsDatSetComboBox"));

    smvSettingsSvIDCheckBox = new QCheckBox(smvSettingsGroupBox);
    smvSettingsSvIDCheckBox->setObjectName(QString::fromUtf8("smvSettingsSvIDCheckBox"));
    smvSettingsSvIDCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    smvSettingsSvIDLabel = new QLabel(smvSettingsGroupBox);
    smvSettingsSvIDLabel->setObjectName(QString::fromUtf8("smvSettingsSvIDLabel"));
    smvSettingsSvIDComboBox = new QComboBox(smvSettingsGroupBox);
    smvSettingsSvIDComboBox->setObjectName(QString::fromUtf8("smvSettingsSvIDComboBox"));

    smvSettingsOptFieldsCheckBox = new QCheckBox(smvSettingsGroupBox);
    smvSettingsOptFieldsCheckBox->setObjectName(QString::fromUtf8("smvSettingsOptFieldsCheckBox"));
    smvSettingsOptFieldsCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    smvSettingsOptFieldsLabel = new QLabel(smvSettingsGroupBox);
    smvSettingsOptFieldsLabel->setObjectName(QString::fromUtf8("smvSettingsOptFieldsLabel"));
    smvSettingsOptFieldsComboBox = new QComboBox(smvSettingsGroupBox);
    smvSettingsOptFieldsComboBox->setObjectName(QString::fromUtf8("smvSettingsOptFieldsComboBox"));

    smvSettingsSmpRateCheckBox = new QCheckBox(smvSettingsGroupBox);
    smvSettingsSmpRateCheckBox->setObjectName(QString::fromUtf8("smvSettingsSmpRateCheckBox"));
    smvSettingsSmpRateCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    smvSettingsSmpRateLabel = new QLabel(smvSettingsGroupBox);
    smvSettingsSmpRateLabel->setObjectName(QString::fromUtf8("smvSettingsSmpRateLabel"));
    smvSettingsSmpRateComboBox = new QComboBox(smvSettingsGroupBox);
    smvSettingsSmpRateComboBox->setObjectName(QString::fromUtf8("smvSettingsSmpRateComboBox"));

    smvSettingsGridLayout->addWidget(smvSettingsCbNameCheckBox, 0, 0, 1, 1);
    smvSettingsGridLayout->addWidget(smvSettingsCbNameLabel, 0, 1, 1, 1);
    smvSettingsGridLayout->addWidget(smvSettingsCbNameComboBox, 0, 2, 1, 1);
    smvSettingsGridLayout->addWidget(smvSettingsDatSetCheckBox, 0, 3, 1, 1);
    smvSettingsGridLayout->addWidget(smvSettingsDatSetLabel, 0, 4, 1, 1);
    smvSettingsGridLayout->addWidget(smvSettingsDatSetComboBox, 0, 5, 1, 1);
    smvSettingsGridLayout->addWidget(smvSettingsSvIDCheckBox, 1, 0, 1, 1);
    smvSettingsGridLayout->addWidget(smvSettingsSvIDLabel, 1, 1, 1, 1);
    smvSettingsGridLayout->addWidget(smvSettingsSvIDComboBox, 1, 2, 1, 1);
    smvSettingsGridLayout->addWidget(smvSettingsOptFieldsCheckBox, 1, 3, 1, 1);
    smvSettingsGridLayout->addWidget(smvSettingsOptFieldsLabel, 1, 4, 1, 1);
    smvSettingsGridLayout->addWidget(smvSettingsOptFieldsComboBox, 1, 5, 1, 1);
    smvSettingsGridLayout->addWidget(smvSettingsSmpRateCheckBox, 2, 0, 1, 1);
    smvSettingsGridLayout->addWidget(smvSettingsSmpRateLabel, 2, 1, 1, 1);
    smvSettingsGridLayout->addWidget(smvSettingsSmpRateComboBox, 2, 2, 1, 1);

    confLNsGroupBox = new QGroupBox(servicesGroupBox);
    confLNsGroupBox->setObjectName(QString::fromUtf8("confLNsGroupBox"));
    confLNsGroupBox->setCheckable(true);

    confLNsGridLayout = new QGridLayout(confLNsGroupBox);
    confLNsGridLayout->setObjectName(QString::fromUtf8("confLNsGridLayout"));

    confLNsFixPrefixCheckBox = new QCheckBox(confLNsGroupBox);
    confLNsFixPrefixCheckBox->setObjectName(QString::fromUtf8("confLNsFixPrefixCheckBox"));
    confLNsFixPrefixCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    confLNsFixPrefixLabel = new QLabel(confLNsGroupBox);
    confLNsFixPrefixLabel->setObjectName(QString::fromUtf8("confLNsFixPrefixLabel"));
    confLNsFixPrefixComboBox = new QComboBox(confLNsGroupBox);
    confLNsFixPrefixComboBox->setObjectName(QString::fromUtf8("confLNsFixPrefixComboBox"));

    confLNsFixLnInstCheckBox = new QCheckBox(confLNsGroupBox);
    confLNsFixLnInstCheckBox->setObjectName(QString::fromUtf8("confLNsFixLnInstCheckBox"));
    confLNsFixLnInstCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    confLNsFixLnInstLabel = new QLabel(confLNsGroupBox);
    confLNsFixLnInstLabel->setObjectName(QString::fromUtf8("confLNsFixLnInstLabel"));
    confLNsFixLnInstComboBox = new QComboBox(confLNsGroupBox);
    confLNsFixLnInstComboBox->setObjectName(QString::fromUtf8("confLNsFixLnInstComboBox"));



    confLNsGridLayout->addWidget(confLNsFixPrefixCheckBox, 0, 0, 1, 1);
    confLNsGridLayout->addWidget(confLNsFixPrefixLabel, 0, 1, 1, 1);
    confLNsGridLayout->addWidget(confLNsFixPrefixComboBox, 0, 2, 1, 1);
    confLNsGridLayout->addWidget(confLNsFixLnInstCheckBox, 1, 0, 1, 1);
    confLNsGridLayout->addWidget(confLNsFixLnInstLabel, 1, 1, 1, 1);
    confLNsGridLayout->addWidget(confLNsFixLnInstComboBox, 1, 2, 1, 1);

    servicesGridLayout->addWidget(servicesWOAttrGroupBox, 0, 0, 1, 4);

//    servicesGridLayout->addWidget(gooseGroupBox, 1, 0, 1, 1);
//    servicesGridLayout->addWidget(gsseGroupBox, 1, 1, 1, 1);
//    servicesGridLayout->addWidget(confDataSetGroupBox, 2, 0, 1, 1);
//    servicesGridLayout->addWidget(confReportControlGroupBox, 1, 2, 1, 1);
//    servicesGridLayout->addWidget(confLogControlGroupBox, 1, 3, 1, 1);
//    servicesGridLayout->addWidget(dynDataSetGroupBox, 2, 1, 1, 1);
//    servicesGridLayout->addWidget(reportSettingsGroupBox, 3, 0, 1, 1);
//    servicesGridLayout->addWidget(smvSettingsGroupBox, 3, 1, 1, 1);
//    servicesGridLayout->addWidget(settingGroupsGroupBox, 2, 2, 1, 1);
//    servicesGridLayout->addWidget(logSettingsGroupBox, 3, 2, 1, 1);
//    servicesGridLayout->addWidget(gseSettingsGroupBox, 3, 3, 1, 1);
//    servicesGridLayout->addWidget(confLNsGroupBox, 2, 3, 1, 1);
    servicesGridLayout->addWidget(gooseGroupBox, 1, 0, 1, 1);
    servicesGridLayout->addWidget(gsseGroupBox, 1, 1, 1, 1);
    servicesGridLayout->addWidget(confDataSetGroupBox, 1, 2, 1, 1);
    servicesGridLayout->addWidget(confReportControlGroupBox, 2, 0, 1, 1);
    servicesGridLayout->addWidget(confLogControlGroupBox, 2, 1, 1, 1);
    servicesGridLayout->addWidget(dynDataSetGroupBox, 2, 2, 1, 1);
    servicesGridLayout->addWidget(reportSettingsGroupBox, 3, 0, 1, 1);
    servicesGridLayout->addWidget(smvSettingsGroupBox, 3, 1, 1, 1);
    servicesGridLayout->addWidget(settingGroupsGroupBox, 3, 2, 1, 1);
    servicesGridLayout->addWidget(logSettingsGroupBox, 4, 0, 1, 1);
    servicesGridLayout->addWidget(gseSettingsGroupBox, 4, 1, 1, 1);
    servicesGridLayout->addWidget(confLNsGroupBox, 4, 2, 1, 1);


    retranslateUi();

    QMetaObject::connectSlotsByName(this);

}

void EditServices::retranslateUi()
{
    QStringList serviceSettingEnum = QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix");
    QStringList confLnsEnum = QStringList()<<tr("false")<<tr("true");
    setWindowTitle(tr("EditServices"));

    iedModeSelLabel->setText(tr("Setting Mode:"));
    iedModeSelComboBox->addItems(QStringList()<<tr("自定义")<<tr("默认")<<tr("全清")<<tr("全选"));

    servicesGroupBox->setTitle(tr("Services"));

    servicesWOAttrGroupBox->setTitle(tr("Services without attributes"));

    dynAssociationCheckBox->setText(QString());
    dynAssociationLabel->setText(tr("DynAssociation"));
    getDirectoryCheckBox->setText(QString());
    getDirectoryLabel->setText(tr("GetDirectory"));
    getDataObjectDefinitionCheckBox->setText(QString());
    getDataObjectDefinitionLabel->setText(tr("GetDataObjectDefinition"));
    dataObjectDirectoryCheckBox->setText(QString());;
    dataObjectDirectoryLabel->setText(tr("DataObjectDirectory"));
    getDataSetValueCheckBox->setText(QString());;
    getDataSetValueLabel->setText(tr("GetDataSetValue"));
    setDataSetValueCheckBox->setText(QString());;
    setDataSetValueLabel->setText(tr("SetDataSetValue"));
    dataSetDirectoryCheckBox->setText(QString());;
    dataSetDirectoryLabel->setText(tr("DataSetDirectory"));
    readWriteCheckBox->setText(QString());;
    readWriteLabel->setText(tr("ReadWrite"));
    timerActivatedControlCheckBox->setText(QString());;
    timerActivatedControlLabel->setText(tr("TimerActivatedControl"));
    getCBValuesCheckBox->setText(QString());;
    getCBValuesLabel->setText(tr("GetCBValues"));
    gseDirCheckBox->setText(QString());;
    gseDirLabel->setText(tr("GSEDir"));
    fileHandlingCheckBox->setText(QString());;
    fileHandlingLabel->setText(tr("FileHandling"));

    gooseGroupBox->setTitle("GOOSE");
    gooseMaxLabel->setText("max: ");

    gsseGroupBox->setTitle("GSSE");
    gsseMaxLabel->setText("max: ");

    confDataSetGroupBox->setTitle("ConfDataSet");
    confDataSetMaxLabel->setText("max: ");
    confDataSetMaxAttrLabel->setText("maxAttributes: ");

    confReportControlGroupBox->setTitle("ConfReportControl");
    confReportControlMaxLabel->setText("max: ");

    confLogControlGroupBox->setTitle("ConfLogControl");
    conLogControlMaxLabel->setText("max: ");

    dynDataSetGroupBox->setTitle("DynDataSet");
    dynDataSetMaxLabel->setText("max: ");
    dynDataSetMaxAttrLabel->setText("maxAttributes: ");

    reportSettingsGroupBox->setTitle("ReportSettings");
    reportSettingsCbNameCheckBox->setText(QString());
    reportSettingsCbNameLabel->setText("cbName");
    reportSettingsCbNameComboBox->addItems(serviceSettingEnum);
    reportSettingsDatSetCheckBox->setText(QString());
    reportSettingsDatSetLabel->setText("datSet");
    reportSettingsDatSetComboBox->addItems(serviceSettingEnum);
    reportSettingsRptIdCheckBox->setText(QString());
    reportSettingsRptIdLabel->setText("rptID");
    reportSettingsRptIdComboBox->addItems(serviceSettingEnum);
    reportSettingsOptFieldsCheckBox->setText(QString());
    reportSettingsOptFieldsLabel->setText("optFields");
    reportSettingsOptFieldsComboBox->addItems(serviceSettingEnum);
    reportSettingsBufTimeCheckBox->setText(QString());
    reportSettingsBufTimeLabel->setText("bufTime");
    reportSettingsBufTimeComboBox->addItems(serviceSettingEnum);
    reportSettingsTrgOpsCheckBox->setText(QString());
    reportSettingsTrgOpsLabel->setText("trgOps");
    reportSettingsTrgOpsComboBox->addItems(serviceSettingEnum);
    reportSettingsIntgPdCheckBox->setText(QString());
    reportSettingsIntgPdLabel->setText("intgPd");
    reportSettingsIntgPdComboBox->addItems(serviceSettingEnum);

    logSettingsGroupBox->setTitle("LogSettings");
    logSettingsCbNameCheckBox->setText(QString());
    logSettingsCbNameLabel->setText("cbName");;
    logSettingsCbNameComboBox->addItems(serviceSettingEnum);
    logSettingsDatSetCheckBox->setText(QString());
    logSettingsDatSetLabel->setText("datSet");;
    logSettingsDatSetComboBox->addItems(serviceSettingEnum);
    logSettingsLogEnaCheckBox->setText(QString());
    logSettingsLogEnaLabel->setText("logEna");;
    logSettingsLogEnaComboBox->addItems(serviceSettingEnum);
    logSettingsTrgOpsCheckBox->setText(QString());
    logSettingsTrgOpsLabel->setText("trgOps");;
    logSettingsTrgOpsComboBox->addItems(serviceSettingEnum);
    logSettingsIntgPdCheckBox->setText(QString());
    logSettingsIntgPdLabel->setText("intgPd");
    logSettingsIntgPdComboBox->addItems(serviceSettingEnum);

    settingGroupsGroupBox->setTitle("SettingGroups");
    settingGroupsSGEditCheckBox->setText(QString());
    settingGroupsSGEditLabel->setText("SGEdit");
    settingGroupsConfSGCheckBox->setText(QString());
    settingGroupsConfSGLabel->setText("ConfSG");

    gseSettingsGroupBox->setTitle("GSESettings");
    gseSettingsCbNameCheckBox->setText(QString());
    gseSettingsCbNameLabel->setText("cbName");
    gseSettingsCbNameComboBox->addItems(serviceSettingEnum);
    gseSettingsDatSetCheckBox->setText(QString());
    gseSettingsDatSetLabel->setText("datSet");
    gseSettingsDatSetComboBox->addItems(serviceSettingEnum);
    gseSettingsAppIDCheckBox->setText(QString());
    gseSettingsAppIDLabel->setText("appID");
    gseSettingsAppIDComboBox->addItems(serviceSettingEnum);
    gseSettingsDataLabelCheckBox->setText(QString());
    gseSettingsDataLabelLabel->setText("dataLabel");
    gseSettingsDataLabelComboBox->addItems(serviceSettingEnum);

    smvSettingsGroupBox->setTitle("SMVSettings");
    smvSettingsCbNameCheckBox->setText(QString());
    smvSettingsCbNameLabel->setText("cbName");
    smvSettingsCbNameComboBox->addItems(serviceSettingEnum);
    smvSettingsDatSetCheckBox->setText(QString());
    smvSettingsDatSetLabel->setText("datSet");
    smvSettingsDatSetComboBox->addItems(serviceSettingEnum);
    smvSettingsSvIDCheckBox->setText(QString());
    smvSettingsSvIDLabel->setText("svID");
    smvSettingsSvIDComboBox->addItems(serviceSettingEnum);
    smvSettingsOptFieldsCheckBox->setText(QString());
    smvSettingsOptFieldsLabel->setText("optFields");
    smvSettingsOptFieldsComboBox->addItems(serviceSettingEnum);
    smvSettingsSmpRateCheckBox->setText(QString());
    smvSettingsSmpRateLabel->setText("smpRate");
    smvSettingsSmpRateComboBox->addItems(serviceSettingEnum);

    confLNsGroupBox->setTitle("ConfLNs");
    confLNsFixPrefixCheckBox->setText(QString());
    confLNsFixPrefixLabel->setText("fixPrefix");
    confLNsFixPrefixComboBox->addItems(confLnsEnum);
    confLNsFixLnInstCheckBox->setText(QString());
    confLNsFixLnInstLabel->setText("fixLnInst");
    confLNsFixLnInstComboBox->addItems(confLnsEnum);

}

void EditServices::finishInit()
{
    connect(iedModeSelComboBox, SIGNAL(activated(int)), this, SLOT(selMode(int)));
    iedModeSelComboBox->setCurrentIndex(0);

    reportSettingsCbNameComboBox->setCurrentIndex(2);
    reportSettingsDatSetComboBox->setCurrentIndex(2);
    reportSettingsRptIdComboBox->setCurrentIndex(2);
    reportSettingsOptFieldsComboBox->setCurrentIndex(2);
    reportSettingsBufTimeComboBox->setCurrentIndex(2);
    reportSettingsTrgOpsComboBox->setCurrentIndex(2);
    reportSettingsIntgPdComboBox->setCurrentIndex(2);

    logSettingsCbNameComboBox->setCurrentIndex(2);
    logSettingsDatSetComboBox->setCurrentIndex(2);
    logSettingsLogEnaComboBox->setCurrentIndex(2);
    logSettingsTrgOpsComboBox->setCurrentIndex(2);
    logSettingsIntgPdComboBox->setCurrentIndex(2);

    gseSettingsCbNameComboBox->setCurrentIndex(2);
    gseSettingsDatSetComboBox->setCurrentIndex(2);
    gseSettingsAppIDComboBox->setCurrentIndex(2);
    gseSettingsDataLabelComboBox->setCurrentIndex(2);

    smvSettingsCbNameComboBox->setCurrentIndex(2);
    smvSettingsDatSetComboBox->setCurrentIndex(2);
    smvSettingsSvIDComboBox->setCurrentIndex(2);
    smvSettingsOptFieldsComboBox->setCurrentIndex(2);
    smvSettingsSmpRateComboBox->setCurrentIndex(2);

    confLNsFixPrefixComboBox->setCurrentIndex(0);
    confLNsFixLnInstComboBox->setCurrentIndex(0);

    connect(dynAssociationCheckBox, SIGNAL(toggled(bool)), dynAssociationLabel, SLOT(setEnabled(bool)));
    connect(getDirectoryCheckBox, SIGNAL(toggled(bool)), getDirectoryLabel, SLOT(setEnabled(bool)));
    connect(getDataObjectDefinitionCheckBox, SIGNAL(toggled(bool)), getDataObjectDefinitionLabel, SLOT(setEnabled(bool)));
    connect(dataObjectDirectoryCheckBox, SIGNAL(toggled(bool)), dataObjectDirectoryLabel, SLOT(setEnabled(bool)));
    connect(getDataSetValueCheckBox, SIGNAL(toggled(bool)), getDataSetValueLabel, SLOT(setEnabled(bool)));
    connect(setDataSetValueCheckBox, SIGNAL(toggled(bool)), setDataSetValueLabel, SLOT(setEnabled(bool)));
    connect(dataSetDirectoryCheckBox, SIGNAL(toggled(bool)), dataSetDirectoryLabel, SLOT(setEnabled(bool)));
    connect(readWriteCheckBox, SIGNAL(toggled(bool)), readWriteLabel, SLOT(setEnabled(bool)));
    connect(timerActivatedControlCheckBox, SIGNAL(toggled(bool)), timerActivatedControlLabel, SLOT(setEnabled(bool)));
    connect(getCBValuesCheckBox, SIGNAL(toggled(bool)), getCBValuesLabel, SLOT(setEnabled(bool)));
    connect(gseDirCheckBox, SIGNAL(toggled(bool)), gseDirLabel, SLOT(setEnabled(bool)));
    connect(fileHandlingCheckBox, SIGNAL(toggled(bool)), fileHandlingLabel, SLOT(setEnabled(bool)));
    bool dynAssociationIsChecked = dynAssociationCheckBox->checkState();
    bool getDirectoryIsChecked = getDirectoryCheckBox->checkState();
    bool getDataObjectDefinitionIsChecked = getDataObjectDefinitionCheckBox->checkState();
    bool dataObjectDirectoryIsChecked = dataObjectDirectoryCheckBox->checkState();
    bool getDataSetValueIsChecked = getDataSetValueCheckBox->checkState();
    bool setDataSetValueIsChecked = setDataSetValueCheckBox->checkState();
    bool dataSetDirectoryIsChecked = dataSetDirectoryCheckBox->checkState();
    bool readWriteIsChecked = readWriteCheckBox->checkState();
    bool timerActivatedControlIsChecked = timerActivatedControlCheckBox->checkState();
    bool getCBValuesIsChecked = getCBValuesCheckBox->checkState();
    bool gseDirIsChecked = gseDirCheckBox->checkState();
    bool fileHandlingIsChecked = fileHandlingCheckBox->checkState();
    dynAssociationLabel->setEnabled(dynAssociationIsChecked);
    getDirectoryLabel->setEnabled(getDirectoryIsChecked);
    getDataObjectDefinitionLabel->setEnabled(getDataObjectDefinitionIsChecked);
    dataObjectDirectoryLabel->setEnabled(dataObjectDirectoryIsChecked);
    getDataSetValueLabel->setEnabled(getDataSetValueIsChecked);
    setDataSetValueLabel->setEnabled(setDataSetValueIsChecked);
    dataSetDirectoryLabel->setEnabled(dataSetDirectoryIsChecked);
    readWriteLabel->setEnabled(readWriteIsChecked);
    timerActivatedControlLabel->setEnabled(timerActivatedControlIsChecked);
    getCBValuesLabel->setEnabled(getCBValuesIsChecked);
    gseDirLabel->setEnabled(gseDirIsChecked);
    fileHandlingLabel->setEnabled(fileHandlingIsChecked);

    connect(reportSettingsCbNameCheckBox, SIGNAL(toggled(bool)), reportSettingsCbNameLabel, SLOT(setEnabled(bool)));
    connect(reportSettingsCbNameCheckBox, SIGNAL(toggled(bool)), reportSettingsCbNameComboBox, SLOT(setEnabled(bool)));
    connect(reportSettingsDatSetCheckBox, SIGNAL(toggled(bool)), reportSettingsDatSetLabel, SLOT(setEnabled(bool)));
    connect(reportSettingsDatSetCheckBox, SIGNAL(toggled(bool)), reportSettingsDatSetComboBox, SLOT(setEnabled(bool)));
    connect(reportSettingsRptIdCheckBox, SIGNAL(toggled(bool)), reportSettingsRptIdLabel, SLOT(setEnabled(bool)));
    connect(reportSettingsRptIdCheckBox, SIGNAL(toggled(bool)), reportSettingsRptIdComboBox, SLOT(setEnabled(bool)));
    connect(reportSettingsOptFieldsCheckBox, SIGNAL(toggled(bool)), reportSettingsOptFieldsLabel, SLOT(setEnabled(bool)));
    connect(reportSettingsOptFieldsCheckBox, SIGNAL(toggled(bool)), reportSettingsOptFieldsComboBox, SLOT(setEnabled(bool)));
    connect(reportSettingsBufTimeCheckBox, SIGNAL(toggled(bool)), reportSettingsBufTimeLabel, SLOT(setEnabled(bool)));
    connect(reportSettingsBufTimeCheckBox, SIGNAL(toggled(bool)), reportSettingsBufTimeComboBox, SLOT(setEnabled(bool)));
    connect(reportSettingsTrgOpsCheckBox, SIGNAL(toggled(bool)), reportSettingsTrgOpsLabel, SLOT(setEnabled(bool)));
    connect(reportSettingsTrgOpsCheckBox, SIGNAL(toggled(bool)), reportSettingsTrgOpsComboBox, SLOT(setEnabled(bool)));
    connect(reportSettingsIntgPdCheckBox, SIGNAL(toggled(bool)), reportSettingsIntgPdLabel, SLOT(setEnabled(bool)));
    connect(reportSettingsIntgPdCheckBox, SIGNAL(toggled(bool)), reportSettingsIntgPdComboBox, SLOT(setEnabled(bool)));
    bool reportSettingsCbNameIsChecked = reportSettingsCbNameCheckBox->checkState();
    bool reportSettingsDatSetIsChecked = reportSettingsDatSetCheckBox->checkState();
    bool reportSettingsRptIdIsChecked = reportSettingsRptIdCheckBox->checkState();
    bool reportSettingsOptFieldsIsChecked = reportSettingsOptFieldsCheckBox->checkState();
    bool reportSettingsBufTimeIsChecked = reportSettingsBufTimeCheckBox->checkState();
    bool reportSettingsTrgOpsIsChecked = reportSettingsTrgOpsCheckBox->checkState();
    bool reportSettingsIntgPdIsChecked = reportSettingsIntgPdCheckBox->checkState();
    reportSettingsCbNameLabel->setEnabled(reportSettingsCbNameIsChecked);
    reportSettingsCbNameComboBox->setEnabled(reportSettingsCbNameIsChecked);
    reportSettingsDatSetLabel->setEnabled(reportSettingsDatSetIsChecked);
    reportSettingsDatSetComboBox->setEnabled(reportSettingsDatSetIsChecked);
    reportSettingsRptIdLabel->setEnabled(reportSettingsRptIdIsChecked);
    reportSettingsRptIdComboBox->setEnabled(reportSettingsRptIdIsChecked);
    reportSettingsOptFieldsLabel->setEnabled(reportSettingsOptFieldsIsChecked);
    reportSettingsOptFieldsComboBox->setEnabled(reportSettingsOptFieldsIsChecked);
    reportSettingsBufTimeLabel->setEnabled(reportSettingsBufTimeIsChecked);
    reportSettingsBufTimeComboBox->setEnabled(reportSettingsBufTimeIsChecked);
    reportSettingsTrgOpsLabel->setEnabled(reportSettingsTrgOpsIsChecked);
    reportSettingsTrgOpsComboBox->setEnabled(reportSettingsTrgOpsIsChecked);
    reportSettingsIntgPdLabel->setEnabled(reportSettingsIntgPdIsChecked);
    reportSettingsIntgPdComboBox->setEnabled(reportSettingsIntgPdIsChecked);

    connect(logSettingsCbNameCheckBox, SIGNAL(toggled(bool)), logSettingsCbNameLabel, SLOT(setEnabled(bool)));
    connect(logSettingsCbNameCheckBox, SIGNAL(toggled(bool)), logSettingsCbNameComboBox, SLOT(setEnabled(bool)));
    connect(logSettingsDatSetCheckBox, SIGNAL(toggled(bool)), logSettingsDatSetLabel, SLOT(setEnabled(bool)));
    connect(logSettingsDatSetCheckBox, SIGNAL(toggled(bool)), logSettingsDatSetComboBox, SLOT(setEnabled(bool)));
    connect(logSettingsLogEnaCheckBox, SIGNAL(toggled(bool)), logSettingsLogEnaLabel, SLOT(setEnabled(bool)));
    connect(logSettingsLogEnaCheckBox, SIGNAL(toggled(bool)), logSettingsLogEnaComboBox, SLOT(setEnabled(bool)));
    connect(logSettingsTrgOpsCheckBox, SIGNAL(toggled(bool)), logSettingsTrgOpsLabel, SLOT(setEnabled(bool)));
    connect(logSettingsTrgOpsCheckBox, SIGNAL(toggled(bool)), logSettingsTrgOpsComboBox, SLOT(setEnabled(bool)));
    connect(logSettingsIntgPdCheckBox, SIGNAL(toggled(bool)), logSettingsIntgPdLabel, SLOT(setEnabled(bool)));
    connect(logSettingsIntgPdCheckBox, SIGNAL(toggled(bool)), logSettingsIntgPdComboBox, SLOT(setEnabled(bool)));
    bool logSettingsCbNameIsChecked = logSettingsCbNameCheckBox->checkState();
    bool logSettingsDatSetIsChecked = logSettingsDatSetCheckBox->checkState();
    bool logSettingsLogEnaIsChecked = logSettingsLogEnaCheckBox->checkState();
    bool logSettingsTrgOpsIsChecked = logSettingsTrgOpsCheckBox->checkState();
    bool logSettingsIntgPdIsChecked = logSettingsIntgPdCheckBox->checkState();
    logSettingsCbNameLabel->setEnabled(logSettingsCbNameIsChecked);
    logSettingsCbNameComboBox->setEnabled(logSettingsCbNameIsChecked);
    logSettingsDatSetLabel->setEnabled(logSettingsDatSetIsChecked);
    logSettingsDatSetComboBox->setEnabled(logSettingsDatSetIsChecked);
    logSettingsLogEnaLabel->setEnabled(logSettingsLogEnaIsChecked);
    logSettingsLogEnaComboBox->setEnabled(logSettingsLogEnaIsChecked);
    logSettingsTrgOpsLabel->setEnabled(logSettingsTrgOpsIsChecked);
    logSettingsTrgOpsComboBox->setEnabled(logSettingsTrgOpsIsChecked);
    logSettingsIntgPdLabel->setEnabled(logSettingsIntgPdIsChecked);
    logSettingsIntgPdComboBox->setEnabled(logSettingsIntgPdIsChecked);

    connect(settingGroupsSGEditCheckBox, SIGNAL(toggled(bool)), settingGroupsSGEditLabel, SLOT(setEnabled(bool)));
    connect(settingGroupsConfSGCheckBox, SIGNAL(toggled(bool)), settingGroupsConfSGLabel, SLOT(setEnabled(bool)));
    bool settingGroupsSGEditIsChecked = settingGroupsSGEditCheckBox->checkState();
    bool settingGroupsConfSGIsChecked = settingGroupsConfSGCheckBox->checkState();
    settingGroupsSGEditLabel->setEnabled(settingGroupsSGEditIsChecked);
    settingGroupsConfSGLabel->setEnabled(settingGroupsConfSGIsChecked);

    connect(gseSettingsCbNameCheckBox, SIGNAL(toggled(bool)), gseSettingsCbNameLabel, SLOT(setEnabled(bool)));
    connect(gseSettingsCbNameCheckBox, SIGNAL(toggled(bool)), gseSettingsCbNameComboBox, SLOT(setEnabled(bool)));
    connect(gseSettingsDatSetCheckBox, SIGNAL(toggled(bool)), gseSettingsDatSetLabel, SLOT(setEnabled(bool)));
    connect(gseSettingsDatSetCheckBox, SIGNAL(toggled(bool)), gseSettingsDatSetComboBox, SLOT(setEnabled(bool)));
    connect(gseSettingsAppIDCheckBox, SIGNAL(toggled(bool)), gseSettingsAppIDLabel, SLOT(setEnabled(bool)));
    connect(gseSettingsAppIDCheckBox, SIGNAL(toggled(bool)), gseSettingsAppIDComboBox, SLOT(setEnabled(bool)));
    connect(gseSettingsDataLabelCheckBox, SIGNAL(toggled(bool)), gseSettingsDataLabelLabel, SLOT(setEnabled(bool)));
    connect(gseSettingsDataLabelCheckBox, SIGNAL(toggled(bool)), gseSettingsDataLabelComboBox, SLOT(setEnabled(bool)));
    bool gseSettingsCbNameIsChecked = gseSettingsCbNameCheckBox->checkState();
    bool gseSettingsDatSetIsChecked = gseSettingsDatSetCheckBox->checkState();
    bool gseSettingsAppIDIsChecked = gseSettingsAppIDCheckBox->checkState();
    bool gseSettingsDataLabelIsChecked = gseSettingsDataLabelCheckBox->checkState();
    gseSettingsCbNameLabel->setEnabled(gseSettingsCbNameIsChecked);
    gseSettingsCbNameComboBox->setEnabled(gseSettingsCbNameIsChecked);
    gseSettingsDatSetLabel->setEnabled(gseSettingsDatSetIsChecked);
    gseSettingsDatSetComboBox->setEnabled(gseSettingsDatSetIsChecked);
    gseSettingsAppIDLabel->setEnabled(gseSettingsAppIDIsChecked);
    gseSettingsAppIDComboBox->setEnabled(gseSettingsAppIDIsChecked);
    gseSettingsDataLabelLabel->setEnabled(gseSettingsDataLabelIsChecked);
    gseSettingsDataLabelComboBox->setEnabled(gseSettingsDataLabelIsChecked);


    connect(smvSettingsCbNameCheckBox, SIGNAL(toggled(bool)), smvSettingsCbNameLabel, SLOT(setEnabled(bool)));
    connect(smvSettingsCbNameCheckBox, SIGNAL(toggled(bool)), smvSettingsCbNameComboBox, SLOT(setEnabled(bool)));
    connect(smvSettingsDatSetCheckBox, SIGNAL(toggled(bool)), smvSettingsDatSetLabel, SLOT(setEnabled(bool)));
    connect(smvSettingsDatSetCheckBox, SIGNAL(toggled(bool)), smvSettingsDatSetComboBox, SLOT(setEnabled(bool)));
    connect(smvSettingsSvIDCheckBox, SIGNAL(toggled(bool)), smvSettingsSvIDLabel, SLOT(setEnabled(bool)));
    connect(smvSettingsSvIDCheckBox, SIGNAL(toggled(bool)), smvSettingsSvIDComboBox, SLOT(setEnabled(bool)));
    connect(smvSettingsOptFieldsCheckBox, SIGNAL(toggled(bool)), smvSettingsOptFieldsLabel, SLOT(setEnabled(bool)));
    connect(smvSettingsOptFieldsCheckBox, SIGNAL(toggled(bool)), smvSettingsOptFieldsComboBox, SLOT(setEnabled(bool)));
    connect(smvSettingsSmpRateCheckBox, SIGNAL(toggled(bool)), smvSettingsSmpRateLabel, SLOT(setEnabled(bool)));
    connect(smvSettingsSmpRateCheckBox, SIGNAL(toggled(bool)), smvSettingsSmpRateComboBox, SLOT(setEnabled(bool)));
    bool smvSettingsCbNameIsChecked = smvSettingsCbNameCheckBox->checkState();
    bool smvSettingsDatSetIsChecked = smvSettingsDatSetCheckBox->checkState();
    bool smvSettingsSvIDIsChecked = smvSettingsSvIDCheckBox->checkState();
    bool smvSettingsOptFieldsIsChecked = smvSettingsOptFieldsCheckBox->checkState();
    bool smvSettingsSmpRateIsChecked = smvSettingsSmpRateCheckBox->checkState();
    smvSettingsCbNameLabel->setEnabled(smvSettingsCbNameIsChecked);
    smvSettingsCbNameComboBox->setEnabled(smvSettingsCbNameIsChecked);
    smvSettingsDatSetLabel->setEnabled(smvSettingsDatSetIsChecked);
    smvSettingsDatSetComboBox->setEnabled(smvSettingsDatSetIsChecked);
    smvSettingsSvIDLabel->setEnabled(smvSettingsSvIDIsChecked);
    smvSettingsSvIDComboBox->setEnabled(smvSettingsSvIDIsChecked);
    smvSettingsOptFieldsLabel->setEnabled(smvSettingsOptFieldsIsChecked);
    smvSettingsOptFieldsComboBox->setEnabled(smvSettingsOptFieldsIsChecked);
    smvSettingsSmpRateLabel->setEnabled(smvSettingsSmpRateIsChecked);
    smvSettingsSmpRateComboBox->setEnabled(smvSettingsSmpRateIsChecked);

    connect(confLNsFixPrefixCheckBox, SIGNAL(toggled(bool)), confLNsFixPrefixLabel, SLOT(setEnabled(bool)));
    connect(confLNsFixPrefixCheckBox, SIGNAL(toggled(bool)), confLNsFixPrefixComboBox, SLOT(setEnabled(bool)));
    connect(confLNsFixLnInstCheckBox, SIGNAL(toggled(bool)), confLNsFixLnInstLabel, SLOT(setEnabled(bool)));
    connect(confLNsFixLnInstCheckBox, SIGNAL(toggled(bool)), confLNsFixLnInstComboBox, SLOT(setEnabled(bool)));
    bool confLNsFixPrefixIsChecked = confLNsFixPrefixCheckBox->checkState();
    bool confLNsFixLnInstIsChecked = confLNsFixLnInstCheckBox->checkState();
    confLNsFixPrefixLabel->setEnabled(confLNsFixPrefixIsChecked);
    confLNsFixPrefixComboBox->setEnabled(confLNsFixPrefixIsChecked);
    confLNsFixLnInstLabel->setEnabled(confLNsFixLnInstIsChecked);
    confLNsFixLnInstComboBox->setEnabled(confLNsFixLnInstIsChecked);

    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QMetaObject::connectSlotsByName(this);

}

void EditServices::selMode(int index)
{
    switch(index) {
    default:
    case 0:
        return;
    case 1:
        setModeDefault();
        return;
    case 2:
        setModeAllClear();
        return;
    case 3:
        setModeAllSel();
        return;
    }
}

void EditServices::setModeDefault()
{
    servicesGroupBox->setChecked(true);
    dynAssociationCheckBox->setChecked(1);
    getDirectoryCheckBox->setChecked(1);
    getDataObjectDefinitionCheckBox->setChecked(1);
    dataObjectDirectoryCheckBox->setChecked(1);
    getDataSetValueCheckBox->setChecked(1);
    setDataSetValueCheckBox->setChecked(0);
    dataSetDirectoryCheckBox->setChecked(1);
    readWriteCheckBox->setChecked(1);
    timerActivatedControlCheckBox->setChecked(0);
    getCBValuesCheckBox->setChecked(1);
    gseDirCheckBox->setChecked(0);
    fileHandlingCheckBox->setChecked(1);

    gooseGroupBox->setChecked(0);
    gooseMaxText->clear();

    gsseGroupBox->setChecked(0);
    gsseMaxText->clear();

    settingGroupsGroupBox->setChecked(1);
    settingGroupsSGEditCheckBox->setChecked(1);
    settingGroupsConfSGCheckBox->setChecked(1);

    confDataSetGroupBox->setChecked(1);
    confDataSetMaxText->setText(tr("100"));
    confDataSetMaxAttrText->setText(tr("255"));

    dynDataSetGroupBox->setChecked(1);
    dynDataSetMaxText->setText(tr("100"));
    dynDataSetMaxAttrText->setText(tr("255"));

    confReportControlGroupBox->setChecked(1);
    confReportControlMaxText->setText(tr("32"));

    confLogControlGroupBox->setChecked(1);
    confLogControlMaxText->setText(tr("1"));

    reportSettingsGroupBox->setChecked(1);
    reportSettingsCbNameCheckBox->setChecked(1);
    reportSettingsCbNameComboBox->setCurrentIndex(0);
    reportSettingsDatSetCheckBox->setChecked(1);
    reportSettingsDatSetComboBox->setCurrentIndex(0);
    reportSettingsRptIdCheckBox->setChecked(1);
    reportSettingsRptIdComboBox->setCurrentIndex(0);
    reportSettingsOptFieldsCheckBox->setChecked(1);
    reportSettingsOptFieldsComboBox->setCurrentIndex(2);
    reportSettingsBufTimeCheckBox->setChecked(1);
    reportSettingsBufTimeComboBox->setCurrentIndex(2);
    reportSettingsTrgOpsCheckBox->setChecked(1);
    reportSettingsTrgOpsComboBox->setCurrentIndex(2);
    reportSettingsIntgPdCheckBox->setChecked(1);
    reportSettingsIntgPdComboBox->setCurrentIndex(2);

    logSettingsGroupBox->setChecked(1);
    logSettingsCbNameCheckBox->setChecked(1);
    logSettingsCbNameComboBox->setCurrentIndex(0);
    logSettingsDatSetCheckBox->setChecked(1);
    logSettingsDatSetComboBox->setCurrentIndex(0);
    logSettingsLogEnaCheckBox->setChecked(1);
    logSettingsLogEnaComboBox->setCurrentIndex(2);
    logSettingsTrgOpsCheckBox->setChecked(1);
    logSettingsTrgOpsComboBox->setCurrentIndex(2);
    logSettingsIntgPdCheckBox->setChecked(1);
    logSettingsIntgPdComboBox->setCurrentIndex(2);

    gseSettingsGroupBox->setChecked(0);
    gseSettingsCbNameCheckBox->setChecked(0);
    gseSettingsDatSetCheckBox->setChecked(0);
    gseSettingsAppIDCheckBox->setChecked(0);
    gseSettingsDataLabelCheckBox->setChecked(0);

    smvSettingsGroupBox->setChecked(0);
    smvSettingsCbNameCheckBox->setChecked(0);
    smvSettingsDatSetCheckBox->setChecked(0);
    smvSettingsSvIDCheckBox->setChecked(0);
    smvSettingsOptFieldsCheckBox->setChecked(0);
    smvSettingsSmpRateCheckBox->setChecked(0);

    confLNsGroupBox->setChecked(1);
    confLNsFixPrefixCheckBox->setChecked(1);
    confLNsFixPrefixComboBox->setCurrentIndex(1);
    confLNsFixLnInstCheckBox->setChecked(1);
    confLNsFixLnInstComboBox->setCurrentIndex(1);
}

void EditServices::setModeAllClear()
{
    servicesWOAttrGroupBox->setChecked(0);
    dynAssociationCheckBox->setChecked(0);
    getDirectoryCheckBox->setChecked(0);
    getDataObjectDefinitionCheckBox->setChecked(0);
    dataObjectDirectoryCheckBox->setChecked(0);
    getDataSetValueCheckBox->setChecked(0);
    setDataSetValueCheckBox->setChecked(0);
    dataSetDirectoryCheckBox->setChecked(0);
    readWriteCheckBox->setChecked(0);
    timerActivatedControlCheckBox->setChecked(0);
    getCBValuesCheckBox->setChecked(0);
    gseDirCheckBox->setChecked(0);
    fileHandlingCheckBox->setChecked(0);

    settingGroupsGroupBox->setChecked(0);
    settingGroupsSGEditCheckBox->setChecked(0);
    settingGroupsConfSGCheckBox->setChecked(0);

    confDataSetGroupBox->setChecked(0);
    confDataSetMaxText->clear();
    confDataSetMaxAttrText->clear();

    dynDataSetGroupBox->setChecked(0);
    dynDataSetMaxText->clear();
    dynDataSetMaxAttrText->clear();

    confReportControlGroupBox->setChecked(0);
    confReportControlMaxText->clear();

    confLogControlGroupBox->setChecked(0);
    confLogControlMaxText->clear();

    reportSettingsGroupBox->setChecked(0);
    reportSettingsCbNameCheckBox->setChecked(0);
    reportSettingsDatSetCheckBox->setChecked(0);
    reportSettingsRptIdCheckBox->setChecked(0);
    reportSettingsOptFieldsCheckBox->setChecked(0);
    reportSettingsBufTimeCheckBox->setChecked(0);
    reportSettingsTrgOpsCheckBox->setChecked(0);
    reportSettingsIntgPdCheckBox->setChecked(0);

    logSettingsGroupBox->setChecked(0);
    logSettingsCbNameCheckBox->setChecked(0);
    logSettingsDatSetCheckBox->setChecked(0);
    logSettingsLogEnaCheckBox->setChecked(0);
    logSettingsTrgOpsCheckBox->setChecked(0);
    logSettingsIntgPdCheckBox->setChecked(0);

    gseSettingsGroupBox->setChecked(0);
    gseSettingsCbNameCheckBox->setChecked(0);
    gseSettingsDatSetCheckBox->setChecked(0);
    gseSettingsAppIDCheckBox->setChecked(0);
    gseSettingsDataLabelCheckBox->setChecked(0);

    smvSettingsGroupBox->setChecked(0);
    smvSettingsCbNameCheckBox->setChecked(0);
    smvSettingsDatSetCheckBox->setChecked(0);
    smvSettingsSvIDCheckBox->setChecked(0);
    smvSettingsOptFieldsCheckBox->setChecked(0);
    smvSettingsSmpRateCheckBox->setChecked(0);

    gooseGroupBox->setChecked(0);
    gooseMaxText->clear();

    gsseGroupBox->setChecked(0);
    gsseMaxText->clear();

    confLNsGroupBox->setChecked(0);
    confLNsFixPrefixCheckBox->setChecked(0);
    confLNsFixLnInstCheckBox->setChecked(0);
}

void EditServices::setModeAllSel()
{

    servicesWOAttrGroupBox->setChecked(1);
    dynAssociationCheckBox->setChecked(1);
    getDirectoryCheckBox->setChecked(1);
    getDataObjectDefinitionCheckBox->setChecked(1);
    dataObjectDirectoryCheckBox->setChecked(1);
    getDataSetValueCheckBox->setChecked(1);
    setDataSetValueCheckBox->setChecked(1);
    dataSetDirectoryCheckBox->setChecked(1);
    readWriteCheckBox->setChecked(1);
    timerActivatedControlCheckBox->setChecked(1);
    getCBValuesCheckBox->setChecked(1);
    gseDirCheckBox->setChecked(1);
    fileHandlingCheckBox->setChecked(1);

    settingGroupsGroupBox->setChecked(1);
    settingGroupsSGEditCheckBox->setChecked(1);
    settingGroupsConfSGCheckBox->setChecked(1);

    confDataSetGroupBox->setChecked(1);

    dynDataSetGroupBox->setChecked(1);

    confReportControlGroupBox->setChecked(1);

    confLogControlGroupBox->setChecked(1);

    reportSettingsGroupBox->setChecked(1);
    reportSettingsCbNameCheckBox->setChecked(1);
    reportSettingsDatSetCheckBox->setChecked(1);
    reportSettingsRptIdCheckBox->setChecked(1);
    reportSettingsOptFieldsCheckBox->setChecked(1);
    reportSettingsBufTimeCheckBox->setChecked(1);
    reportSettingsTrgOpsCheckBox->setChecked(1);
    reportSettingsIntgPdCheckBox->setChecked(1);

    logSettingsGroupBox->setChecked(1);
    logSettingsCbNameCheckBox->setChecked(1);
    logSettingsDatSetCheckBox->setChecked(1);
    logSettingsLogEnaCheckBox->setChecked(1);
    logSettingsTrgOpsCheckBox->setChecked(1);
    logSettingsIntgPdCheckBox->setChecked(1);

    gseSettingsGroupBox->setChecked(1);
    gseSettingsCbNameCheckBox->setChecked(1);
    gseSettingsDatSetCheckBox->setChecked(1);
    gseSettingsAppIDCheckBox->setChecked(1);
    gseSettingsDataLabelCheckBox->setChecked(1);

    smvSettingsGroupBox->setChecked(1);
    smvSettingsCbNameCheckBox->setChecked(1);
    smvSettingsDatSetCheckBox->setChecked(1);
    smvSettingsSvIDCheckBox->setChecked(1);
    smvSettingsOptFieldsCheckBox->setChecked(1);
    smvSettingsSmpRateCheckBox->setChecked(1);

    gooseGroupBox->setChecked(1);

    gsseGroupBox->setChecked(1);

    confLNsGroupBox->setChecked(1);
    confLNsFixPrefixCheckBox->setChecked(1);
    confLNsFixLnInstCheckBox->setChecked(1);
}

void EditServices::setTarget(DomItem *pTarget)
{
    target = pTarget ;
    setModeAllClear();
    if(target->hasChildOfName(tr("DynAssociation")))
        dynAssociationCheckBox->setChecked(true);
    if(target->hasChildOfName(tr("GetDataSetValue")))
        getDataSetValueCheckBox->setChecked(true);
    if(target->hasChildOfName(tr("TimerActivatedControl")))
        timerActivatedControlCheckBox->setChecked(true);
    if(target->hasChildOfName(tr("GetDirectory")))
        getDirectoryCheckBox->setChecked(true);
    if(target->hasChildOfName(tr("SetDataSetValue")))
        setDataSetValueCheckBox->setChecked(true);
    if(target->hasChildOfName(tr("GetCBValues")))
        getCBValuesCheckBox->setChecked(true);
    if(target->hasChildOfName(tr("GetDataObjectDefinition")))
        getDataObjectDefinitionCheckBox->setChecked(true);
    if(target->hasChildOfName(tr("DataSetDirectory")))
        dataSetDirectoryCheckBox->setChecked(true);
    if(target->hasChildOfName(tr("GSEDir")))
        gseDirCheckBox->setChecked(true);
    if(target->hasChildOfName(tr("DataObjectDirectory")))
        dataObjectDirectoryCheckBox->setChecked(true);
    if(target->hasChildOfName(tr("ReadWrite")))
        readWriteCheckBox->setChecked(true);
    if(target->hasChildOfName(tr("FileHandling")))
        fileHandlingCheckBox->setChecked(true);

    QVectorIterator<DomItem*> it(target->getItems());
    while(it.hasNext()) {
        DomItem *item = it.next();
        if(item->tag() == tr("DynAssociation")) {
            dynAssociationCheckBox->setChecked(true);
            continue;
        }
        if(item->tag() == tr("GetDataSetValue")) {
            getDataSetValueCheckBox->setChecked(true);
            continue;
        }
        if(item->tag() == tr("TimerActivatedControl")) {
            timerActivatedControlCheckBox->setChecked(true);
            continue;
        }
        if(item->tag() == tr("GetDirectory")) {
            getDirectoryCheckBox->setChecked(true);
            continue;
        }
        if(item->tag() == tr("SetDataSetValue")) {
            setDataSetValueCheckBox->setChecked(true);
            continue;
        }
        if(item->tag() == tr("GetCBValues")) {
            getCBValuesCheckBox->setChecked(true);
            continue;
        }
        if(item->tag() == tr("GetDataObjectDefinition")) {
            getDataObjectDefinitionCheckBox->setChecked(true);
            continue;
        }
        if(item->tag() == tr("DataSetDirectory")) {
            dataSetDirectoryCheckBox->setChecked(true);
            continue;
        }
        if(item->tag() == tr("GSEDir")) {
            gseDirCheckBox->setChecked(true);
            continue;
        }
        if(item->tag() == tr("DataObjectDirectory")) {
            dataObjectDirectoryCheckBox->setChecked(true);
            continue;
        }
        if(item->tag() == tr("ReadWrite")) {
            readWriteCheckBox->setChecked(true);
            continue;
        }
        if(item->tag() == tr("FileHandling")) {
            fileHandlingCheckBox->setChecked(true);
            continue;
        }
        if(item->tag() == tr("GOOSE")) {
            gooseGroupBox->setChecked(true);
            gooseMaxText->setText(item->getAttribute(tr("max"))->value);
            continue;
        }
        if(item->tag() == tr("ConfReportControl")) {
            confReportControlGroupBox->setChecked(true);
            confReportControlMaxText->setText(item->getAttribute(tr("max"))->value);
            continue;
        }
        if(item->tag() == tr("GSSE")) {
            gsseGroupBox->setChecked(true);
            gsseMaxText->setText(item->getAttribute(tr("max"))->value);
            continue;
        }
        if(item->tag() == tr("ConfLogControl")) {
            confLogControlGroupBox->setChecked(true);
            confLogControlMaxText->setText(item->getAttribute(tr("max"))->value);
            continue;
        }
        if(item->tag() == tr("ConfDataSet")) {
            confDataSetGroupBox->setChecked(true);
            confDataSetMaxText->setText(item->getAttribute(tr("max"))->value);
            confDataSetMaxAttrText->setText(item->getAttribute(tr("maxAttributes"))->value);
            continue;
        }
        if(item->tag() == tr("DynDataSet")) {
            dynDataSetGroupBox->setChecked(true);
            dynDataSetMaxText->setText(item->getAttribute(tr("max"))->value);
            dynDataSetMaxAttrText->setText(item->getAttribute(tr("maxAttributes"))->value);
            continue;
        }
        if(item->tag() == tr("ReportSettings")) {
            reportSettingsGroupBox->setChecked(true);
            if(item->hasAttrOfName(tr("cbName"))) {
                reportSettingsCbNameCheckBox->setChecked(true);
                int index = 0;
                QString attrValue = item->getAttribute(tr("cbName"))->value;
                if(attrValue == tr("Dyn"))
                    index = 0;
                else if(attrValue == tr("Conf"))
                    index = 1;
                else if(attrValue == tr("Fix"))
                    index = 2;
                reportSettingsCbNameComboBox->setCurrentIndex(index);
            }
            if(item->hasAttrOfName(tr("datSet"))) {
                reportSettingsDatSetCheckBox->setChecked(true);
                int index = 0;
                QString attrValue = item->getAttribute(tr("datSet"))->value;
                if(attrValue == tr("Dyn"))
                    index = 0;
                else if(attrValue == tr("Conf"))
                    index = 1;
                else if(attrValue == tr("Fix"))
                    index = 2;
                reportSettingsDatSetComboBox->setCurrentIndex(index);
            }
            if(item->hasAttrOfName(tr("rptID"))) {
                reportSettingsRptIdCheckBox->setChecked(true);
                int index = 0;
                QString attrValue = item->getAttribute(tr("rptID"))->value;
                if(attrValue == tr("Dyn"))
                    index = 0;
                else if(attrValue == tr("Conf"))
                    index = 1;
                else if(attrValue == tr("Fix"))
                    index = 2;
                reportSettingsRptIdComboBox->setCurrentIndex(index);
            }
            if(item->hasAttrOfName(tr("optFields"))) {
                reportSettingsOptFieldsCheckBox->setChecked(true);
                int index = 0;
                QString attrValue = item->getAttribute(tr("optFields"))->value;
                if(attrValue == tr("Dyn"))
                    index = 0;
                else if(attrValue == tr("Conf"))
                    index = 1;
                else if(attrValue == tr("Fix"))
                    index = 2;
                reportSettingsOptFieldsComboBox->setCurrentIndex(index);
            }
            if(item->hasAttrOfName(tr("bufTime"))) {
                reportSettingsBufTimeCheckBox->setChecked(true);
                int index = 0;
                QString attrValue = item->getAttribute(tr("bufTime"))->value;
                if(attrValue == tr("Dyn"))
                    index = 0;
                else if(attrValue == tr("Conf"))
                    index = 1;
                else if(attrValue == tr("Fix"))
                    index = 2;
                reportSettingsBufTimeComboBox->setCurrentIndex(index);
            }
            if(item->hasAttrOfName(tr("trgOps"))) {
                reportSettingsTrgOpsCheckBox->setChecked(true);
                int index = 0;
                QString attrValue = item->getAttribute(tr("trgOps"))->value;
                if(attrValue == tr("Dyn"))
                    index = 0;
                else if(attrValue == tr("Conf"))
                    index = 1;
                else if(attrValue == tr("Fix"))
                    index = 2;
                reportSettingsTrgOpsComboBox->setCurrentIndex(index);
            }
            if(item->hasAttrOfName(tr("intgPd"))) {
                reportSettingsIntgPdCheckBox->setChecked(true);
                int index = 0;
                QString attrValue = item->getAttribute(tr("intgPd"))->value;
                if(attrValue == tr("Dyn"))
                    index = 0;
                else if(attrValue == tr("Conf"))
                    index = 1;
                else if(attrValue == tr("Fix"))
                    index = 2;
                reportSettingsIntgPdComboBox->setCurrentIndex(index);
            }
            continue;
        }
        if(item->tag() == tr("LogSettings")) {
            logSettingsGroupBox->setChecked(true);
            if(item->hasAttrOfName(tr("cbName"))) {
                logSettingsCbNameCheckBox->setChecked(true);
                int index = 0;
                QString attrValue = item->getAttribute(tr("cbName"))->value;
                if(attrValue == tr("Dyn"))
                    index = 0;
                else if(attrValue == tr("Conf"))
                    index = 1;
                else if(attrValue == tr("Fix"))
                    index = 2;
                logSettingsCbNameComboBox->setCurrentIndex(index);
            }
            if(item->hasAttrOfName(tr("datSet"))) {
                logSettingsDatSetCheckBox->setChecked(true);
                int index = 0;
                QString attrValue = item->getAttribute(tr("datSet"))->value;
                if(attrValue == tr("Dyn"))
                    index = 0;
                else if(attrValue == tr("Conf"))
                    index = 1;
                else if(attrValue == tr("Fix"))
                    index = 2;
                logSettingsDatSetComboBox->setCurrentIndex(index);
            }
            if(item->hasAttrOfName(tr("logEna"))) {
                logSettingsLogEnaCheckBox->setChecked(true);
                int index = 0;
                QString attrValue = item->getAttribute(tr("logEna"))->value;
                if(attrValue == tr("Dyn"))
                    index = 0;
                else if(attrValue == tr("Conf"))
                    index = 1;
                else if(attrValue == tr("Fix"))
                    index = 2;
                logSettingsLogEnaComboBox->setCurrentIndex(index);
            }
            if(item->hasAttrOfName(tr("trgOps"))) {
                logSettingsTrgOpsCheckBox->setChecked(true);
                int index = 0;
                QString attrValue = item->getAttribute(tr("trgOps"))->value;
                if(attrValue == tr("Dyn"))
                    index = 0;
                else if(attrValue == tr("Conf"))
                    index = 1;
                else if(attrValue == tr("Fix"))
                    index = 2;
                logSettingsTrgOpsComboBox->setCurrentIndex(index);
            }
            if(item->hasAttrOfName(tr("intgPd"))) {
                logSettingsIntgPdCheckBox->setChecked(true);
                int index = 0;
                QString attrValue = item->getAttribute(tr("intgPd"))->value;
                if(attrValue == tr("Dyn"))
                    index = 0;
                else if(attrValue == tr("Conf"))
                    index = 1;
                else if(attrValue == tr("Fix"))
                    index = 2;
                logSettingsIntgPdComboBox->setCurrentIndex(index);
            }
            continue;
        }
        if(item->tag() == tr("SMVSettings")) {
            smvSettingsGroupBox->setChecked(true);
            if(item->hasAttrOfName(tr("cbName"))) {
                smvSettingsCbNameCheckBox->setChecked(true);
                int index = 0;
                QString attrValue = item->getAttribute(tr("cbName"))->value;
                if(attrValue == tr("Dyn"))
                    index = 0;
                else if(attrValue == tr("Conf"))
                    index = 1;
                else if(attrValue == tr("Fix"))
                    index = 2;
                smvSettingsCbNameComboBox->setCurrentIndex(index);
            }
            if(item->hasAttrOfName(tr("datSet"))) {
                smvSettingsDatSetCheckBox->setChecked(true);
                int index = 0;
                QString attrValue = item->getAttribute(tr("datSet"))->value;
                if(attrValue == tr("Dyn"))
                    index = 0;
                else if(attrValue == tr("Conf"))
                    index = 1;
                else if(attrValue == tr("Fix"))
                    index = 2;
                smvSettingsDatSetComboBox->setCurrentIndex(index);
            }
            if(item->hasAttrOfName(tr("svID"))) {
                smvSettingsSvIDCheckBox->setChecked(true);
                int index = 0;
                QString attrValue = item->getAttribute(tr("svID"))->value;
                if(attrValue == tr("Dyn"))
                    index = 0;
                else if(attrValue == tr("Conf"))
                    index = 1;
                else if(attrValue == tr("Fix"))
                    index = 2;
                smvSettingsSvIDComboBox->setCurrentIndex(index);
            }
            if(item->hasAttrOfName(tr("optFields"))) {
                smvSettingsOptFieldsCheckBox->setChecked(true);
                int index = 0;
                QString attrValue = item->getAttribute(tr("optFields"))->value;
                if(attrValue == tr("Dyn"))
                    index = 0;
                else if(attrValue == tr("Conf"))
                    index = 1;
                else if(attrValue == tr("Fix"))
                    index = 2;
                smvSettingsOptFieldsComboBox->setCurrentIndex(index);
            }
            if(item->hasAttrOfName(tr("smpRate"))) {
                smvSettingsSmpRateCheckBox->setChecked(true);
                int index = 0;
                QString attrValue = item->getAttribute(tr("smpRate"))->value;
                if(attrValue == tr("Dyn"))
                    index = 0;
                else if(attrValue == tr("Conf"))
                    index = 1;
                else if(attrValue == tr("Fix"))
                    index = 2;
                smvSettingsSmpRateComboBox->setCurrentIndex(index);
            }
            continue;
        }
        if(item->tag() == tr("GSESettings")) {
            gseSettingsGroupBox->setChecked(true);
            if(item->hasAttrOfName(tr("cbName"))) {
                gseSettingsCbNameCheckBox->setChecked(true);
                int index = 0;
                QString attrValue = item->getAttribute(tr("cbName"))->value;
                if(attrValue == tr("Dyn"))
                    index = 0;
                else if(attrValue == tr("Conf"))
                    index = 1;
                else if(attrValue == tr("Fix"))
                    index = 2;
                gseSettingsCbNameComboBox->setCurrentIndex(index);
            }
            if(item->hasAttrOfName(tr("datSet"))) {
                gseSettingsDatSetCheckBox->setChecked(true);
                int index = 0;
                QString attrValue = item->getAttribute(tr("datSet"))->value;
                if(attrValue == tr("Dyn"))
                    index = 0;
                else if(attrValue == tr("Conf"))
                    index = 1;
                else if(attrValue == tr("Fix"))
                    index = 2;
                gseSettingsDatSetComboBox->setCurrentIndex(index);
            }
            if(item->hasAttrOfName(tr("appID"))) {
                gseSettingsAppIDCheckBox->setChecked(true);
                int index = 0;
                QString attrValue = item->getAttribute(tr("appID"))->value;
                if(attrValue == tr("Dyn"))
                    index = 0;
                else if(attrValue == tr("Conf"))
                    index = 1;
                else if(attrValue == tr("Fix"))
                    index = 2;
                gseSettingsAppIDComboBox->setCurrentIndex(index);
            }
            if(item->hasAttrOfName(tr("dataLabel"))) {
                gseSettingsDataLabelCheckBox->setChecked(true);
                int index = 0;
                QString attrValue = item->getAttribute(tr("dataLabel"))->value;
                if(attrValue == tr("Dyn"))
                    index = 0;
                else if(attrValue == tr("Conf"))
                    index = 1;
                else if(attrValue == tr("Fix"))
                    index = 2;
                gseSettingsDataLabelComboBox->setCurrentIndex(index);
            }
            continue;
        }
        if(item->tag() == tr("SettingGroups")) {
            settingGroupsGroupBox->setChecked(true);
            if(item->hasChildOfName(tr("SGEdit")))
                settingGroupsSGEditCheckBox->setChecked(true);
            if(item->hasChildOfName(tr("ConfSG")))
                settingGroupsConfSGCheckBox->setChecked(true);
            continue;
        }
        if(item->tag() == tr("ConfLNs")) {
            confLNsGroupBox->setChecked(true);
            if(item->hasAttrOfName(tr("fixPrefix"))) {
                confLNsFixPrefixCheckBox->setChecked(true);
                int index = 0;
                QString attrValue = item->getAttribute(tr("fixPrefix"))->value;
                if(attrValue == tr("false"))
                    index = 0;
                else if(attrValue == tr("true"))
                    index = 1;
                confLNsFixPrefixComboBox->setCurrentIndex(index);
            }
            if(item->hasAttrOfName(tr("fixLnInst"))) {
                confLNsFixLnInstCheckBox->setChecked(true);
                int index = 0;
                QString attrValue = item->getAttribute(tr("fixLnInst"))->value;
                if(attrValue == tr("false"))
                    index = 0;
                else if(attrValue == tr("true"))
                    index = 1;
                confLNsFixLnInstComboBox->setCurrentIndex(index);
            }
            continue;

        }

    }

}

void EditServices::error(const QString &message)
{
    Utils::error(this, message);
}

void EditServices::accept()
{
    if(NULL == target) {
        error(tr("No target"));
        return;
    }

//    foreach (DomItem *child , target->getItems()) {
//        target->getParentRule()->deleteItem(child, true);
//    }
    target->getItems().clear();

    if(dynAssociationCheckBox->isChecked()) {
        DomItem *newService = new DomItem("DynAssociation", "", target->getParentRule(), target);
        target->addChild(newService);
    }

    if(getDirectoryCheckBox->isChecked()) {
        DomItem *newService = new DomItem("GetDirectory", "", target->getParentRule(), target);
        target->addChild(newService);
    }

    if(getDataObjectDefinitionCheckBox->isChecked()) {
        DomItem *newService = new DomItem("GetDataObjectDefinition", "", target->getParentRule(), target);
        target->addChild(newService);
    }

    if(dataObjectDirectoryCheckBox->isChecked()) {
        DomItem *newService = new DomItem("DataObjectDirectory", "", target->getParentRule(), target);
        target->addChild(newService);
    }

    if(getDataSetValueCheckBox->isChecked()) {
        DomItem *newService = new DomItem("GetDataSetValue", "", target->getParentRule(), target);
        target->addChild(newService);
    }

    if(setDataSetValueCheckBox->isChecked()) {
        DomItem *newService = new DomItem("SetDataSetValue", "", target->getParentRule(), target);
        target->addChild(newService);
    }

    if(dataSetDirectoryCheckBox->isChecked()) {
        DomItem *newService = new DomItem("DataSetDirectory", "", target->getParentRule(), target);
        target->addChild(newService);
    }

    if(readWriteCheckBox->isChecked()) {
        DomItem *newService = new DomItem("ReadWrite", "", target->getParentRule(), target);
        target->addChild(newService);
    }

    if(timerActivatedControlCheckBox->isChecked()) {
        DomItem *newService = new DomItem("TimerActivatedControl", "", target->getParentRule(), target);
        target->addChild(newService);
    }

    if(getCBValuesCheckBox->isChecked()) {
        DomItem *newService = new DomItem("GetCBValues", "", target->getParentRule(), target);
        target->addChild(newService);
    }

    if(gseDirCheckBox->isChecked()) {
        DomItem *newService = new DomItem("GSEDir", "", target->getParentRule(), target);
        target->addChild(newService);
    }

    if(fileHandlingCheckBox->isChecked()) {
        DomItem *newService = new DomItem("FileHandling", "", target->getParentRule(), target);
        target->addChild(newService);
    }

    if(gooseGroupBox->isChecked()) {
        DomItem *newService = new DomItem("GOOSE", "", target->getParentRule(), target);
        newService->addAttribute("max", gooseMaxText->text());
        target->addChild(newService);
    }

    if(gsseGroupBox->isChecked()) {
        DomItem *newService = new DomItem("GSSE", "", target->getParentRule(), target);
        newService->addAttribute("max", gsseMaxText->text());
        target->addChild(newService);
    }

    if(confDataSetGroupBox->isChecked()) {
        DomItem *newService = new DomItem("ConfDataSet", "", target->getParentRule(), target);
        newService->addAttribute("max", confDataSetMaxText->text());
        newService->addAttribute("maxAttributes", confDataSetMaxAttrText->text());
        target->addChild(newService);
    }

    if(confReportControlGroupBox->isChecked()) {
        DomItem *newService = new DomItem("ConfReportControl", "", target->getParentRule(), target);
        newService->addAttribute("max", confReportControlMaxText->text());
        target->addChild(newService);
    }

    if(confLogControlGroupBox->isChecked()) {
        DomItem *newService = new DomItem("ConfLogControl", "", target->getParentRule(), target);
        newService->addAttribute("max", confLogControlMaxText->text());
        target->addChild(newService);
    }

    if(dynDataSetGroupBox->isChecked()) {
        DomItem *newService = new DomItem("DynDataSet", "", target->getParentRule(), target);
        newService->addAttribute("max", dynDataSetMaxText->text());
        newService->addAttribute("maxAttributes", dynDataSetMaxAttrText->text());
        target->addChild(newService);
    }

    if(reportSettingsGroupBox->isChecked()) {
        DomItem *newService = new DomItem("ReportSettings", "", target->getParentRule(), target);

        if(reportSettingsCbNameCheckBox->isChecked())
            newService->addAttribute("cbName", reportSettingsCbNameComboBox->currentText());
        if(reportSettingsDatSetCheckBox->isChecked())
            newService->addAttribute("datSet", reportSettingsDatSetComboBox->currentText());
        if(reportSettingsRptIdCheckBox->isChecked())
            newService->addAttribute("rptID", reportSettingsRptIdComboBox->currentText());
        if(reportSettingsOptFieldsCheckBox->isChecked())
            newService->addAttribute("optFields", reportSettingsOptFieldsComboBox->currentText());
        if(reportSettingsBufTimeCheckBox->isChecked())
            newService->addAttribute("bufTime", reportSettingsBufTimeComboBox->currentText());
        if(reportSettingsTrgOpsCheckBox->isChecked())
            newService->addAttribute("trgOps", reportSettingsTrgOpsComboBox->currentText());
        if(reportSettingsIntgPdCheckBox->isChecked())
            newService->addAttribute("intgPd", reportSettingsIntgPdComboBox->currentText());

        target->addChild(newService);
    }

    if(logSettingsGroupBox->isChecked()) {
        DomItem *newService = new DomItem("LogSettings", "", target->getParentRule(), target);

        if(logSettingsCbNameCheckBox->isChecked())
            newService->addAttribute("cbName", logSettingsCbNameComboBox->currentText());
        if(logSettingsDatSetCheckBox->isChecked())
            newService->addAttribute("datSet", logSettingsDatSetComboBox->currentText());
        if(logSettingsLogEnaCheckBox->isChecked())
            newService->addAttribute("logEna", logSettingsLogEnaComboBox->currentText());
        if(logSettingsTrgOpsCheckBox->isChecked())
            newService->addAttribute("trgOps", logSettingsTrgOpsComboBox->currentText());
        if(logSettingsIntgPdCheckBox->isChecked())
            newService->addAttribute("intgPd", logSettingsIntgPdComboBox->currentText());

        target->addChild(newService);
    }

    if(settingGroupsGroupBox->isChecked()) {
        DomItem *newService = new DomItem("SettingGroups", "", target->getParentRule(), target);

        if(settingGroupsSGEditCheckBox->isChecked()) {
            DomItem *newServiceItem = new DomItem("SGEdit", "", target->getParentRule(), newService);
            newService->addChild(newServiceItem);
        }
        if(settingGroupsConfSGCheckBox->isChecked()) {
            DomItem *newServiceItem = new DomItem("ConfSG", "", target->getParentRule(), newService);
            newService->addChild(newServiceItem);
        }

        target->addChild(newService);
    }

    if(gseSettingsGroupBox->isChecked()) {
        DomItem *newService = new DomItem("GSESettings", "", target->getParentRule(), target);

        if(gseSettingsCbNameCheckBox->isChecked())
            newService->addAttribute("cbName", gseSettingsCbNameComboBox->currentText());
        if(gseSettingsDatSetCheckBox->isChecked())
            newService->addAttribute("datSet", gseSettingsDatSetComboBox->currentText());
        if(gseSettingsAppIDCheckBox->isChecked())
            newService->addAttribute("appID", gseSettingsAppIDComboBox->currentText());
        if(gseSettingsDataLabelCheckBox->isChecked())
            newService->addAttribute("dataLabel", gseSettingsDataLabelComboBox->currentText());

        target->addChild(newService);
    }

    if(smvSettingsGroupBox->isChecked()) {
        DomItem *newService = new DomItem("SMVSettings", "", target->getParentRule(), target);

        if(smvSettingsCbNameCheckBox->isChecked())
            newService->addAttribute("cbName", smvSettingsCbNameComboBox->currentText());
        if(smvSettingsDatSetCheckBox->isChecked())
            newService->addAttribute("datSet", smvSettingsDatSetComboBox->currentText());
        if(smvSettingsSvIDCheckBox->isChecked())
            newService->addAttribute("svID", smvSettingsSvIDComboBox->currentText());
        if(smvSettingsOptFieldsCheckBox->isChecked())
            newService->addAttribute("optFields", smvSettingsOptFieldsComboBox->currentText());
        if(smvSettingsSmpRateCheckBox->isChecked())
            newService->addAttribute("smpRate", smvSettingsSmpRateComboBox->currentText());

        target->addChild(newService);
    }


    if(confLNsGroupBox->isChecked()) {
        DomItem *newService = new DomItem("ConfLNs", "", target->getParentRule(), target);

        if(confLNsFixPrefixCheckBox->isChecked())
            newService->addAttribute("fixPrefix", confLNsFixPrefixComboBox->currentText());
        if(confLNsFixLnInstCheckBox->isChecked())
            newService->addAttribute("fixLnInst", confLNsFixLnInstComboBox->currentText());

        target->addChild(newService);
    }


    QDialog::accept();

}


