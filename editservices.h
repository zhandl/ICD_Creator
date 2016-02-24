#ifndef EDITSERVICES_H
#define EDITSERVICES_H

#include <QDialog>

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QDialogButtonBox>

class DomItem;

class EditServices : public QDialog
{
    Q_OBJECT
public:
    explicit EditServices(QWidget *parent = 0);

    DomItem *target;

    QGridLayout *iedServiceGridLayout;

    QGroupBox *servicesGroupBox;
    QGridLayout *servicesGridLayout;


    QLabel *iedModeSelLabel;
    QComboBox *iedModeSelComboBox;

    QGroupBox *servicesWOAttrGroupBox;
    QGridLayout *servicesWOAttrGridLayout;

    QCheckBox *dynAssociationCheckBox;
    QLabel *dynAssociationLabel;
    QCheckBox *getDirectoryCheckBox;
    QLabel *getDirectoryLabel;
    QCheckBox *getDataObjectDefinitionCheckBox;
    QLabel *getDataObjectDefinitionLabel;
    QCheckBox *dataObjectDirectoryCheckBox;
    QLabel *dataObjectDirectoryLabel;
    QCheckBox *getDataSetValueCheckBox;
    QLabel *getDataSetValueLabel;
    QCheckBox *setDataSetValueCheckBox;
    QLabel *setDataSetValueLabel;
    QCheckBox *dataSetDirectoryCheckBox;
    QLabel *dataSetDirectoryLabel;
    QCheckBox *readWriteCheckBox;
    QLabel *readWriteLabel;
    QCheckBox *timerActivatedControlCheckBox;
    QLabel *timerActivatedControlLabel;
    QCheckBox *getCBValuesCheckBox;
    QLabel *getCBValuesLabel;
    QCheckBox *gseDirCheckBox;
    QLabel *gseDirLabel;
    QCheckBox *fileHandlingCheckBox;
    QLabel *fileHandlingLabel;


    QGroupBox *gooseGroupBox;
    QHBoxLayout *gooseHLayout;
    QLabel *gooseMaxLabel;
    QLineEdit *gooseMaxText;

    QGroupBox *gsseGroupBox;
    QHBoxLayout *gsseHLayout;
    QLabel *gsseMaxLabel;
    QLineEdit *gsseMaxText;

    QGroupBox *confDataSetGroupBox;
    QGridLayout *confDataSetGridLayout;
    QLabel *confDataSetMaxLabel;
    QLineEdit *confDataSetMaxText;
    QLabel *confDataSetMaxAttrLabel;
    QLineEdit *confDataSetMaxAttrText;

    QGroupBox *confReportControlGroupBox;
    QHBoxLayout *confReportControlHLayout;
    QLabel *confReportControlMaxLabel;
    QLineEdit *confReportControlMaxText;

    QGroupBox *confLogControlGroupBox;
    QHBoxLayout *confLogControlHLayout;
    QLabel *conLogControlMaxLabel;
    QLineEdit *confLogControlMaxText;

    QGroupBox *dynDataSetGroupBox;
    QGridLayout *dynDataSetGridLayout;
    QLabel *dynDataSetMaxLabel;
    QLineEdit *dynDataSetMaxText;
    QLabel *dynDataSetMaxAttrLabel;
    QLineEdit *dynDataSetMaxAttrText;


    QGroupBox *reportSettingsGroupBox;
    QGridLayout *reportSettingsGridLayout;
    QCheckBox *reportSettingsCbNameCheckBox;
    QLabel *reportSettingsCbNameLabel;
    QComboBox *reportSettingsCbNameComboBox;
    QCheckBox *reportSettingsDatSetCheckBox;
    QLabel *reportSettingsDatSetLabel;
    QComboBox *reportSettingsDatSetComboBox;
    QCheckBox *reportSettingsRptIdCheckBox;
    QLabel *reportSettingsRptIdLabel;
    QComboBox *reportSettingsRptIdComboBox;
    QCheckBox *reportSettingsOptFieldsCheckBox;
    QLabel *reportSettingsOptFieldsLabel;
    QComboBox *reportSettingsOptFieldsComboBox;
    QCheckBox *reportSettingsBufTimeCheckBox;
    QLabel *reportSettingsBufTimeLabel;
    QComboBox *reportSettingsBufTimeComboBox;
    QCheckBox *reportSettingsTrgOpsCheckBox;
    QLabel *reportSettingsTrgOpsLabel;
    QComboBox *reportSettingsTrgOpsComboBox;
    QCheckBox *reportSettingsIntgPdCheckBox;
    QLabel *reportSettingsIntgPdLabel;
    QComboBox *reportSettingsIntgPdComboBox;

    QGroupBox *logSettingsGroupBox;
    QGridLayout *logSettingsGridLayout;
    QCheckBox *logSettingsCbNameCheckBox;
    QLabel *logSettingsCbNameLabel;
    QComboBox *logSettingsCbNameComboBox;
    QCheckBox *logSettingsDatSetCheckBox;
    QLabel *logSettingsDatSetLabel;
    QComboBox *logSettingsDatSetComboBox;
    QCheckBox *logSettingsLogEnaCheckBox;
    QLabel *logSettingsLogEnaLabel;
    QComboBox *logSettingsLogEnaComboBox;
    QCheckBox *logSettingsTrgOpsCheckBox;
    QLabel *logSettingsTrgOpsLabel;
    QComboBox *logSettingsTrgOpsComboBox;
    QCheckBox *logSettingsIntgPdCheckBox;
    QLabel *logSettingsIntgPdLabel;
    QComboBox *logSettingsIntgPdComboBox;

    QGroupBox *settingGroupsGroupBox;
    QGridLayout *settingGroupsGridLayout;
    QCheckBox *settingGroupsSGEditCheckBox;
    QLabel *settingGroupsSGEditLabel;
    QCheckBox *settingGroupsConfSGCheckBox;
    QLabel *settingGroupsConfSGLabel;

    QGroupBox *gseSettingsGroupBox;
    QGridLayout *gseSettingsGridLayout;
    QCheckBox *gseSettingsCbNameCheckBox;
    QLabel *gseSettingsCbNameLabel;
    QComboBox *gseSettingsCbNameComboBox;
    QCheckBox *gseSettingsDatSetCheckBox;
    QLabel *gseSettingsDatSetLabel;
    QComboBox *gseSettingsDatSetComboBox;
    QCheckBox *gseSettingsAppIDCheckBox;
    QLabel *gseSettingsAppIDLabel;
    QComboBox *gseSettingsAppIDComboBox;
    QCheckBox *gseSettingsDataLabelCheckBox;
    QLabel *gseSettingsDataLabelLabel;
    QComboBox *gseSettingsDataLabelComboBox;

    QGroupBox *smvSettingsGroupBox;
    QGridLayout *smvSettingsGridLayout;
    QCheckBox *smvSettingsCbNameCheckBox;
    QLabel *smvSettingsCbNameLabel;
    QComboBox *smvSettingsCbNameComboBox;
    QCheckBox *smvSettingsDatSetCheckBox;
    QLabel *smvSettingsDatSetLabel;
    QComboBox *smvSettingsDatSetComboBox;
    QCheckBox *smvSettingsSvIDCheckBox;
    QLabel *smvSettingsSvIDLabel;
    QComboBox *smvSettingsSvIDComboBox;
    QCheckBox *smvSettingsOptFieldsCheckBox;
    QLabel *smvSettingsOptFieldsLabel;
    QComboBox *smvSettingsOptFieldsComboBox;
    QCheckBox *smvSettingsSmpRateCheckBox;
    QLabel *smvSettingsSmpRateLabel;
    QComboBox *smvSettingsSmpRateComboBox;

    QGroupBox *confLNsGroupBox;
    QGridLayout *confLNsGridLayout;
    QCheckBox *confLNsFixPrefixCheckBox;
    QLabel *confLNsFixPrefixLabel;
    QComboBox *confLNsFixPrefixComboBox;
    QCheckBox *confLNsFixLnInstCheckBox;
    QLabel *confLNsFixLnInstLabel;
    QComboBox *confLNsFixLnInstComboBox;

    QDialogButtonBox *buttonBox;

    void setTarget(DomItem *pTarget);
private:

    void init();
    void retranslateUi();
    void finishInit();

    void error(const QString& message);


    void setModeDefault();
    void setModeAllClear();
    void setModeAllSel();

signals:

public slots:
    void selMode(int);
    void accept();



};

#endif // EDITSERVICES_H
