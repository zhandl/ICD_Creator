#include "recodericdwizard.h"
#include <QString>
#include <QDateTimeEdit>
#include "datatypeitem.h"
#include "datatypemodel.h"

RecoderIcdWizard::RecoderIcdWizard(QWidget *parent) :
    QWizard(parent)
{
    QString text(tr("This wizard will generate a ICD file"));
    setWizardStyle(QWizard::ModernStyle);

    resize(800, 600);
//    setTitleFormat(Qt::RichText);
//    setSubTitleFormat(Qt::RichText);

    addPage(new WelcomePage(text, this));
    icdHeader_page = new icdHeaderPage(this);
    addPage(icdHeader_page);
    icdSubstation_page = new icdSubstationPage(this);
    addPage(icdSubstation_page);
//    addPage(new icdDataTypeTemplatePage(this));
    icdDataTypeTemplateNew_page = new icdDataTypeTemplateNew(this);
    addPage(icdDataTypeTemplateNew_page);

    icdIedServices_page = new icdIedServicesPage(this);
    addPage(icdIedServices_page);

    icdIedAccessPoint_page = new icdIedAccessPointPage(this);
    addPage(icdIedAccessPoint_page);

    icdCommunication_page = new icdCommunicationPage(this);
    addPage(icdCommunication_page);

    connect(icdIedServices_page->iedNameText, SIGNAL(textChanged(QString)), icdCommunication_page, SLOT(setIedName(QString)));
    connect(icdIedAccessPoint_page->apNameText, SIGNAL(textChanged(QString)), icdCommunication_page, SLOT(setApName(QString)));
}

void RecoderIcdWizard::createDoc(QDomDocument *doc)
{
    QDomProcessingInstruction instruction;
    instruction = doc->createProcessingInstruction("xml", "version=\"1.0\" encoding = \"UTF_8\"");
    doc->appendChild(instruction);

    root = doc->createElement(tr("SCL"));
    QDomAttr xmlns = doc->createAttribute(tr("xmlns"));
    xmlns.setValue(tr("http://www.iec.ch/61850/2003/SCL"));
    QDomAttr xsi = doc->createAttribute(tr("xmlns:xsi"));
    xsi.setValue(tr("http://www.w3.org/2001/XMLSchema-instance"));
    QDomAttr schemaLocation = doc->createAttribute(tr("xsi:schemaLocation"));
    schemaLocation.setValue(tr("http://www.iec.ch/61850/2003/SCL\\ SCL.xsd"));

    root.setAttributeNode(xmlns);
    root.setAttributeNode(xsi);
    root.setAttributeNode(schemaLocation);
    doc->appendChild(root);


}

void RecoderIcdWizard::accept()
{
    document = new QDomDocument();
    createDoc(document);

    QDomElement header;
    header = document->createElement("Header");
    QDomAttr headerId = document->createAttribute("id");
    headerId.setValue(icdHeader_page->headerIdText->text());
    header.setAttributeNode(headerId);
    QDomAttr headerNameStruct = document->createAttribute("nameStructure");
    headerNameStruct.setValue(icdHeader_page->headerNameStructureCombo->currentText());
    header.setAttributeNode(headerNameStruct);
    if(icdHeader_page->headerVersionCheckBox->isChecked()) {
        QDomAttr headerVersion = document->createAttribute("version");
        headerVersion.setValue(icdHeader_page->headerVersionText->text());
        header.setAttributeNode(headerVersion);
    }
    if(icdHeader_page->headerRevisionCheckBox->isChecked()) {
        QDomAttr headerRevision = document->createAttribute("revision");
        headerRevision.setValue(icdHeader_page->headerRevisionText->text());
        header.setAttributeNode(headerRevision);
    }
    if(icdHeader_page->headerToolIdCheckBox->isChecked()) {
        QDomAttr headerToolId = document->createAttribute("toolID");
        headerToolId.setValue(icdHeader_page->headerToolIdText->text());
        header.setAttributeNode(headerToolId);
    }
    if(icdHeader_page->headerRefCheckBox->isChecked()) {
        QDomAttr headerRef = document->createAttribute("Ref");
        headerRef.setValue(icdHeader_page->headerRefText->text());
        header.setAttributeNode(headerRef);
    }
    if(icdHeader_page->hitemTableWidget->rowCount() > 0) {
        QDomElement headerHistroy = document->createElement("History");
        header.appendChild(headerHistroy);

        for(int i = 0; i < icdHeader_page->hitemTableWidget->rowCount(); i++) {
            QDomAttr hitemVersion = document->createAttribute("version");
            hitemVersion.setValue(((QLineEdit*)(icdHeader_page->hitemTableWidget->cellWidget(i,0)))->text());
            QDomAttr hitemRevision = document->createAttribute("revision");
            hitemRevision.setValue(((QLineEdit*)(icdHeader_page->hitemTableWidget->cellWidget(i,1)))->text());
            QDomAttr hitemWhen = document->createAttribute("when");
            hitemWhen.setValue(((QDateTimeEdit*)(icdHeader_page->hitemTableWidget->cellWidget(i,2)))->text());
            QDomAttr hitemWhat = document->createAttribute("what");
            hitemWhat.setValue(((QLineEdit*)(icdHeader_page->hitemTableWidget->cellWidget(i,3)))->text());
            QDomAttr hitemWhy = document->createAttribute("why");
            hitemWhy.setValue(((QLineEdit*)(icdHeader_page->hitemTableWidget->cellWidget(i,4)))->text());
            QDomAttr hitemWho = document->createAttribute("who");
            hitemWho.setValue(((QLineEdit*)(icdHeader_page->hitemTableWidget->cellWidget(i,0)))->text());

            QDomElement hitem = document->createElement("hitem");
            hitem.setAttributeNode(hitemVersion);
            hitem.setAttributeNode(hitemRevision);
            hitem.setAttributeNode(hitemWhen);
            hitem.setAttributeNode(hitemWhat);
            hitem.setAttributeNode(hitemWhy);
            hitem.setAttributeNode(hitemWho);

            headerHistroy.appendChild(hitem);
        }
    }
    root.appendChild(header);


    if(icdSubstation_page->substationGroupBox->isChecked()) {
        QDomElement substation = document->createElement("Substation");
        root.appendChild(substation);
    }

    QDomElement dataTypeTemplates = document->createElement("DataTypeTemplates");

    DataTypeModel *dataTypeModel = icdDataTypeTemplateNew_page->selectedModel;
    foreach (DataTypeItem* item, dataTypeModel->root()->getItems()) {
        item->generateDom(*document, dataTypeTemplates);
    }

    QDomElement ied = document->createElement("IED");
    QDomAttr iedName = document->createAttribute("name");
    iedName.setValue(icdIedServices_page->iedNameText->text());
    ied.setAttributeNode(iedName);
    if(icdIedServices_page->iedConfigVersionCheckBox->isChecked()) {
        QDomAttr iedConfigVersion = document->createAttribute("configVersion");
        iedConfigVersion.setValue(icdIedServices_page->iedConfigVersionText->text());
        ied.setAttributeNode(iedConfigVersion);
    }
    if(icdIedServices_page->iedTypeCheckBox->isChecked()) {
        QDomAttr iedType = document->createAttribute("type");
        iedType.setValue(icdIedServices_page->iedTypeText->text());
        ied.setAttributeNode(iedType);
    }
    if(icdIedServices_page->iedManuCheckBox->isChecked()) {
        QDomAttr iedManu = document->createAttribute("manufacturer");
        iedManu.setValue(icdIedServices_page->iedManuText->text());
        ied.setAttributeNode(iedManu);
    }
    if(icdIedServices_page->iedDescCheckBox->isChecked()) {
        QDomAttr iedDesc = document->createAttribute("desc");
        iedDesc.setValue(icdIedServices_page->iedDescText->text());
        ied.setAttributeNode(iedDesc);
    }

    QDomElement services = document->createElement("Services");
    ied.appendChild(services);

    if(icdIedServices_page->dynAssociationCheckBox->isChecked()) {
        QDomElement dynAssociation = document->createElement("DynAssociation");
        services.appendChild(dynAssociation);
    }
    if(icdIedServices_page->getDirectoryCheckBox->isChecked()) {
        QDomElement getDirectory = document->createElement("GetDirectory");
        services.appendChild(getDirectory);
    }
    if(icdIedServices_page->getDataObjectDefinitionCheckBox->isChecked()) {
        QDomElement getDataObjectDefinition = document->createElement("GetDataObjectDefinition");
        services.appendChild(getDataObjectDefinition);
    }
    if(icdIedServices_page->dataObjectDirectoryCheckBox->isChecked()) {
        QDomElement dataObjectDirectory = document->createElement("DataObjectDirectory");
        services.appendChild(dataObjectDirectory);
    }
    if(icdIedServices_page->getDataSetValueCheckBox->isChecked()) {
        QDomElement getDataSetValue = document->createElement("GetDataSetValue");
        services.appendChild(getDataSetValue);
    }
    if(icdIedServices_page->setDataSetValueCheckBox->isChecked()) {
        QDomElement setDataSetValue = document->createElement("SetDataSetValue");
        services.appendChild(setDataSetValue);
    }
    if(icdIedServices_page->dataSetDirectoryCheckBox->isChecked()) {
        QDomElement dataSetDirectory = document->createElement("DataSetDirectory");
        services.appendChild(dataSetDirectory);
    }
    if(icdIedServices_page->readWriteCheckBox->isChecked()) {
        QDomElement readWrite = document->createElement("ReadWrite");
        services.appendChild(readWrite);
    }
    if(icdIedServices_page->timerActivatedControlCheckBox->isChecked()) {
        QDomElement timerActivatedControl = document->createElement("TimerActivatedControl");
        services.appendChild(timerActivatedControl);
    }
    if(icdIedServices_page->getCBValuesCheckBox->isChecked()) {
        QDomElement getCBValues = document->createElement("GetCBValues");
        services.appendChild(getCBValues);
    }
    if(icdIedServices_page->gseDirCheckBox->isChecked()) {
        QDomElement gseDir = document->createElement("GSEDir");
        services.appendChild(gseDir);
    }
    if(icdIedServices_page->fileHandlingCheckBox->isChecked()) {
        QDomElement fileHandling = document->createElement("FileHandling");
        services.appendChild(fileHandling);
    }

    if(icdIedServices_page->gooseGroupBox->isChecked()) {
        QDomElement goose = document->createElement("GOOSE");
        QDomAttr gooseMax = document->createAttribute("max");
        gooseMax.setValue(icdIedServices_page->gooseMaxText->text());
        goose.setAttributeNode(gooseMax);
        services.appendChild(goose);
    }
    if(icdIedServices_page->gsseGroupBox->isChecked()) {
        QDomElement gsse = document->createElement("GSSE");
        QDomAttr gsseMax = document->createAttribute("max");
        gsseMax.setValue(icdIedServices_page->gsseMaxText->text());
        gsse.setAttributeNode(gsseMax);
        services.appendChild(gsse);
    }
    if(icdIedServices_page->confReportControlGroupBox->isChecked()) {
        QDomElement confReportControl = document->createElement("ConfReportControl");
        QDomAttr confReportControlMax = document->createAttribute("max");
        confReportControlMax.setValue(icdIedServices_page->confReportControlMaxText->text());
        confReportControl.setAttributeNode(confReportControlMax);
        services.appendChild(confReportControl);
    }
    if(icdIedServices_page->confLogControlGroupBox->isChecked()) {
        QDomElement confLogControl = document->createElement("ConfLogControl");
        QDomAttr confLogControlMax = document->createAttribute("max");
        confLogControlMax.setValue(icdIedServices_page->confLogControlMaxText->text());
        confLogControl.setAttributeNode(confLogControlMax);
        services.appendChild(confLogControl);
    }
    if(icdIedServices_page->confDataSetGroupBox->isChecked()) {
        QDomElement confDataSet = document->createElement("ConfDataSet");
        QDomAttr confDataSetMax = document->createAttribute("max");
        confDataSetMax.setValue(icdIedServices_page->confDataSetMaxText->text());
        QDomAttr confDataSetMaxAttr = document->createAttribute("maxAttributes");
        confDataSetMaxAttr.setValue(icdIedServices_page->confDataSetMaxAttrText->text());
        confDataSet.setAttributeNode(confDataSetMax);
        confDataSet.setAttributeNode(confDataSetMaxAttr);

        services.appendChild(confDataSet);
    }
    if(icdIedServices_page->dynDataSetGroupBox->isChecked()) {
        QDomElement dynDataSet = document->createElement("DynDataSet");
        QDomAttr dynDataSetMax = document->createAttribute("max");
        dynDataSetMax.setValue(icdIedServices_page->dynDataSetMaxText->text());
        QDomAttr dynDataSetMaxAttr = document->createAttribute("maxAttributes");
        dynDataSetMaxAttr.setValue(icdIedServices_page->dynDataSetMaxAttrText->text());
        dynDataSet.setAttributeNode(dynDataSetMax);
        dynDataSet.setAttributeNode(dynDataSetMaxAttr);

        services.appendChild(dynDataSet);
    }
    if(icdIedServices_page->settingGroupsGroupBox->isChecked()) {
        QDomElement settingGroups = document->createElement("SettingGroups");

        if(icdIedServices_page->settingGroupsSGEditCheckBox->isChecked()) {
            QDomElement settingGroupsSGEdit = document->createElement("SGEdit");
            settingGroups.appendChild(settingGroupsSGEdit);
        }
        if(icdIedServices_page->settingGroupsConfSGCheckBox->isChecked()) {
            QDomElement settingGroupsConfSG = document->createElement("ConfSG");
            settingGroups.appendChild(settingGroupsConfSG);
        }

        services.appendChild(settingGroups);
    }
    if(icdIedServices_page->reportSettingsGroupBox->isChecked()) {
        QDomElement reportSettings = document->createElement("ReportSettings");
        if(icdIedServices_page->reportSettingsCbNameCheckBox->isChecked()) {
            QDomAttr cbName = document->createAttribute("cbName");
            cbName.setValue(icdIedServices_page->reportSettingsCbNameComboBox->currentText());
            reportSettings.setAttributeNode(cbName);
        }
        if(icdIedServices_page->reportSettingsDatSetCheckBox->isChecked()) {
            QDomAttr datSet = document->createAttribute("datSet");
            datSet.setValue(icdIedServices_page->reportSettingsDatSetComboBox->currentText());
            reportSettings.setAttributeNode(datSet);
        }
        if(icdIedServices_page->reportSettingsRptIdCheckBox->isChecked()) {
            QDomAttr rptId = document->createAttribute("rptID");
            rptId.setValue(icdIedServices_page->reportSettingsRptIdComboBox->currentText());
            reportSettings.setAttributeNode(rptId);
        }
        if(icdIedServices_page->reportSettingsOptFieldsCheckBox->isChecked()) {
            QDomAttr optFields = document->createAttribute("optFields");
            optFields.setValue(icdIedServices_page->reportSettingsOptFieldsComboBox->currentText());
            reportSettings.setAttributeNode(optFields);
        }
        if(icdIedServices_page->reportSettingsBufTimeCheckBox->isChecked()) {
            QDomAttr bufTime = document->createAttribute("bufTime");
            bufTime.setValue(icdIedServices_page->reportSettingsBufTimeComboBox->currentText());
            reportSettings.setAttributeNode(bufTime);
        }
        if(icdIedServices_page->reportSettingsTrgOpsCheckBox->isChecked()) {
            QDomAttr trgOps = document->createAttribute("trgOps");
            trgOps.setValue(icdIedServices_page->reportSettingsTrgOpsComboBox->currentText());
            reportSettings.setAttributeNode(trgOps);
        }
        if(icdIedServices_page->reportSettingsIntgPdCheckBox->isChecked()) {
            QDomAttr intgPd = document->createAttribute("intgPd");
            intgPd.setValue(icdIedServices_page->reportSettingsIntgPdComboBox->currentText());
            reportSettings.setAttributeNode(intgPd);
        }

        services.appendChild(reportSettings);
    }
    if(icdIedServices_page->logSettingsGroupBox->isChecked()) {
        QDomElement logSettings = document->createElement("LogSettings");
        if(icdIedServices_page->logSettingsCbNameCheckBox->isChecked()) {
            QDomAttr cbName = document->createAttribute("cbName");
            cbName.setValue(icdIedServices_page->logSettingsCbNameComboBox->currentText());
            logSettings.setAttributeNode(cbName);
        }
        if(icdIedServices_page->logSettingsDatSetCheckBox->isChecked()) {
            QDomAttr datSet = document->createAttribute("datSet");
            datSet.setValue(icdIedServices_page->logSettingsDatSetComboBox->currentText());
            logSettings.setAttributeNode(datSet);
        }
        if(icdIedServices_page->logSettingsLogEnaCheckBox->isChecked()) {
            QDomAttr logEna = document->createAttribute("logEna");
            logEna.setValue(icdIedServices_page->logSettingsLogEnaComboBox->currentText());
            logSettings.setAttributeNode(logEna);
        }
        if(icdIedServices_page->logSettingsTrgOpsCheckBox->isChecked()) {
            QDomAttr trgOps = document->createAttribute("trgOps");
            trgOps.setValue(icdIedServices_page->logSettingsTrgOpsComboBox->currentText());
            logSettings.setAttributeNode(trgOps);
        }
        if(icdIedServices_page->logSettingsIntgPdCheckBox->isChecked()) {
            QDomAttr intgPd = document->createAttribute("intgPd");
            intgPd.setValue(icdIedServices_page->logSettingsIntgPdComboBox->currentText());
            logSettings.setAttributeNode(intgPd);
        }

        services.appendChild(logSettings);
    }
    if(icdIedServices_page->smvSettingsGroupBox->isChecked()) {
        QDomElement smvSettings = document->createElement("SMVSettings");
        if(icdIedServices_page->smvSettingsCbNameCheckBox->isChecked()) {
            QDomAttr cbName = document->createAttribute("cbName");
            cbName.setValue(icdIedServices_page->smvSettingsCbNameComboBox->currentText());
            smvSettings.setAttributeNode(cbName);
        }
        if(icdIedServices_page->smvSettingsDatSetCheckBox->isChecked()) {
            QDomAttr datSet = document->createAttribute("datSet");
            datSet.setValue(icdIedServices_page->smvSettingsDatSetComboBox->currentText());
            smvSettings.setAttributeNode(datSet);
        }
        if(icdIedServices_page->smvSettingsSvIDCheckBox->isChecked()) {
            QDomAttr svId = document->createAttribute("svID");
            svId.setValue(icdIedServices_page->smvSettingsSvIDComboBox->currentText());
            smvSettings.setAttributeNode(svId);
        }
        if(icdIedServices_page->smvSettingsOptFieldsCheckBox->isChecked()) {
            QDomAttr optFields = document->createAttribute("optFields");
            optFields.setValue(icdIedServices_page->smvSettingsOptFieldsComboBox->currentText());
            smvSettings.setAttributeNode(optFields);
        }
        if(icdIedServices_page->smvSettingsSmpRateCheckBox->isChecked()) {
            QDomAttr smpRate = document->createAttribute("smpRate");
            smpRate.setValue(icdIedServices_page->smvSettingsSmpRateComboBox->currentText());
            smvSettings.setAttributeNode(smpRate);
        }

        services.appendChild(smvSettings);
    }
    if(icdIedServices_page->gseSettingsGroupBox->isChecked()) {
        QDomElement gseSettings = document->createElement("GSESettings");
        if(icdIedServices_page->gseSettingsCbNameCheckBox->isChecked()) {
            QDomAttr cbName = document->createAttribute("cbName");
            cbName.setValue(icdIedServices_page->gseSettingsCbNameComboBox->currentText());
            gseSettings.setAttributeNode(cbName);
        }
        if(icdIedServices_page->gseSettingsDatSetCheckBox->isChecked()) {
            QDomAttr datSet = document->createAttribute("datSet");
            datSet.setValue(icdIedServices_page->gseSettingsDatSetComboBox->currentText());
            gseSettings.setAttributeNode(datSet);
        }
        if(icdIedServices_page->gseSettingsAppIDCheckBox->isChecked()) {
            QDomAttr appID = document->createAttribute("appID");
            appID.setValue(icdIedServices_page->gseSettingsAppIDComboBox->currentText());
            gseSettings.setAttributeNode(appID);
        }
        if(icdIedServices_page->gseSettingsDataLabelCheckBox->isChecked()) {
            QDomAttr dataLabel = document->createAttribute("dataLabel");
            dataLabel.setValue(icdIedServices_page->gseSettingsDataLabelComboBox->currentText());
            gseSettings.setAttributeNode(dataLabel);
        }

        services.appendChild(gseSettings);
    }
    if(icdIedServices_page->confLNsGroupBox->isChecked()) {
        QDomElement confLNs = document->createElement("ConfLNs");
        if(icdIedServices_page->confLNsFixPrefixCheckBox->isChecked()) {
            QDomAttr fixPrefix = document->createAttribute("fixPrefix");
            fixPrefix.setValue(icdIedServices_page->confLNsFixPrefixComboBox->currentText());
            confLNs.setAttributeNode(fixPrefix);
        }
        if(icdIedServices_page->confLNsFixLnInstCheckBox->isChecked()) {
            QDomAttr fixLnInst = document->createAttribute("fixLnInst");
            fixLnInst.setValue(icdIedServices_page->confLNsFixLnInstComboBox->currentText());
            confLNs.setAttributeNode(fixLnInst);
        }
        services.appendChild(confLNs);
    }

    QDomElement accessPoint = document->createElement("AccessPoint");
    QDomAttr accessPointName = document->createAttribute("name");
    accessPointName.setValue(icdIedAccessPoint_page->apNameText->text());
    accessPoint.setAttributeNode(accessPointName);
    if(icdIedAccessPoint_page->apDescCheckBox->isChecked()) {
        QDomAttr accessPointDesc = document->createAttribute("desc");
        accessPointDesc.setValue(icdIedAccessPoint_page->apDescText->text());
        accessPoint.setAttributeNode(accessPointDesc);
    }
    ied.appendChild(accessPoint);

    QDomElement server = document->createElement("Server");
    if(icdIedAccessPoint_page->apServerDescCheckBox->isChecked()) {
        QDomAttr accessPointServerDesc = document->createAttribute("desc");
        accessPointServerDesc.setValue(icdIedAccessPoint_page->apServerDescText->text());
        server.setAttributeNode(accessPointServerDesc);
    }
    if(icdIedAccessPoint_page->apServerTimeoutCheckBox->isChecked()) {
        QDomAttr accessPointServerTimeout = document->createAttribute("timeout");
        accessPointServerTimeout.setValue(icdIedAccessPoint_page->apServerTimeoutText->text());
        server.setAttributeNode(accessPointServerTimeout);
    }
    accessPoint.appendChild(server);

    QDomElement authentication = document->createElement("Authentication");
    if(icdIedAccessPoint_page->apServerAuthenticationNoneCheckBox->isChecked()) {
        QDomAttr none = document->createAttribute("none");
        none.setValue(icdIedAccessPoint_page->apServerAuthenticationNoneComboBox->currentText());
        authentication.setAttributeNode(none);
    }
    if(icdIedAccessPoint_page->apServerAuthenticationPasswordCheckBox->isChecked()) {
        QDomAttr password = document->createAttribute("password");
        password.setValue(icdIedAccessPoint_page->apServerAuthenticationPasswordComboBox->currentText());
        authentication.setAttributeNode(password);
    }
    if(icdIedAccessPoint_page->apServerAuthenticationWeakCheckBox->isChecked()) {
        QDomAttr weak = document->createAttribute("weak");
        weak.setValue(icdIedAccessPoint_page->apServerAuthenticationWeakComboBox->currentText());
        authentication.setAttributeNode(weak);
    }
    if(icdIedAccessPoint_page->apServerAuthenticationStrongCheckBox->isChecked()) {
        QDomAttr strong = document->createAttribute("strong");
        strong.setValue(icdIedAccessPoint_page->apServerAuthenticationStrongComboBox->currentText());
        authentication.setAttributeNode(strong);
    }
    if(icdIedAccessPoint_page->apServerAuthenticationCertificateCheckBox->isChecked()) {
        QDomAttr certificate = document->createAttribute("certificate");
        certificate.setValue(icdIedAccessPoint_page->apServerAuthenticationCertificateComboBox->currentText());
        authentication.setAttributeNode(certificate);
    }

    QDomElement LdLd0 = document->createElement("LDevice");
    QDomAttr Ld0Inst = document->createAttribute("inst");
    Ld0Inst.setValue(icdIedAccessPoint_page->apIed0InstComboBox->currentText());
    LdLd0.setAttributeNode(Ld0Inst);
    if(icdIedAccessPoint_page->apIed0DescCheckBox->isChecked()) {
        QDomAttr Ld0Desc = document->createAttribute("desc");
        Ld0Desc.setValue(icdIedAccessPoint_page->apIed0DescText->text());
        LdLd0.setAttributeNode(Ld0Desc);
    }


    QDomElement LdRcd = document->createElement("LDevice");
    QDomAttr LdRcdInst = document->createAttribute("inst");
    LdRcdInst.setValue(icdIedAccessPoint_page->apIed1InstComboBox->currentText());
    LdRcd.setAttributeNode(LdRcdInst);
    if(icdIedAccessPoint_page->apIed0DescCheckBox->isChecked()) {
        QDomAttr LdRcdDesc = document->createAttribute("desc");
        LdRcdDesc.setValue(icdIedAccessPoint_page->apIed1DescText->text());
        LdRcd.setAttributeNode(LdRcdDesc);
    }

    server.appendChild(authentication);
    server.appendChild(LdLd0);
    server.appendChild(LdRcd);

    root.appendChild(ied);

    if(icdCommunication_page->communicationGroupBox->isChecked()) {
        QDomElement communication = document->createElement("Communication");

        QDomElement subNetwork = document->createElement("SubNetwork");
        QDomAttr subNetworkName = document->createAttribute("name");
        subNetworkName.setValue(icdCommunication_page->subNetworkNameText->text());
        subNetwork.setAttributeNode(subNetworkName);
        if(icdCommunication_page->subNetworkTypeCheckBox->isChecked()) {
            QDomAttr subNetworkType = document->createAttribute("type");
            subNetworkType.setValue(icdCommunication_page->subNetworkTypeText->text());
            subNetwork.setAttributeNode(subNetworkType);
        }
        if(icdCommunication_page->subNetworkDescCheckBox->isChecked()) {
            QDomAttr subNetworkDesc = document->createAttribute("desc");
            subNetworkDesc.setValue(icdCommunication_page->subNetworkDescText->text());
            subNetwork.setAttributeNode(subNetworkDesc);
        }

        if(icdCommunication_page->bitRateGroupBox->isChecked()) {
            QDomElement bitRate = document->createElement("BitRate");
            QDomAttr bitRateUnit = document->createAttribute("unit");
            bitRateUnit.setValue("b/s");
            QDomAttr bitRateMulti = document->createAttribute("multiplier");
            bitRateMulti.setValue("M");
            bitRate.setAttributeNode(bitRateUnit);
            bitRate.setAttributeNode(bitRateMulti);

            QDomText bitRateValue = document->createTextNode(icdCommunication_page->bitRateComboBox->currentText());
            bitRate.appendChild(bitRateValue);

            subNetwork.appendChild(bitRate);
        }

        QDomElement connectedAP = document->createElement("ConnectedAP");
        QDomAttr connectedIedName = document->createAttribute("iedName");
        connectedIedName.setValue(icdCommunication_page->connectedIedNameText->text());
        QDomAttr connectedApName = document->createAttribute("apName");
        connectedApName.setValue(icdCommunication_page->connectedApNameText->text());
        connectedAP.setAttributeNode(connectedIedName);
        connectedAP.setAttributeNode(connectedApName);
        if(icdCommunication_page->addressGroupBox->isChecked()) {
            QDomElement address = document->createElement("Address");

            QDomElement osi_ap_title = document->createElement("P");
            QDomAttr osi_ap_title_type = document->createAttribute("type");
            osi_ap_title_type.setValue("OSI-AP-Title");
            osi_ap_title.setAttributeNode(osi_ap_title_type);
            QDomText osi_ap_title_value = document->createTextNode("1 3 9999 33");
            osi_ap_title.appendChild(osi_ap_title_value);

            QDomElement osi_ae_qualifier = document->createElement("P");
            QDomAttr osi_ae_qualifier_type = document->createAttribute("type");
            osi_ae_qualifier_type.setValue("OSI-AE-Qualifier");
            osi_ae_qualifier.setAttributeNode(osi_ae_qualifier_type);
            QDomText osi_ae_qualifier_value = document->createTextNode("33");
            osi_ae_qualifier.appendChild(osi_ae_qualifier_value);

            QDomElement osi_psel = document->createElement("P");
            QDomAttr osi_psel_type = document->createAttribute("type");
            osi_psel_type.setValue("OSI-PSEL");
            osi_psel.setAttributeNode(osi_psel_type);
            QDomText osi_psel_value = document->createTextNode("00 00 00 01");
            osi_psel.appendChild(osi_psel_value);

            QDomElement osi_ssel = document->createElement("P");
            QDomAttr osi_ssel_type = document->createAttribute("type");
            osi_ssel_type.setValue("OSI-SSEL");
            osi_ssel.setAttributeNode(osi_ssel_type);
            QDomText osi_ssel_value = document->createTextNode("00 01");
            osi_ssel.appendChild(osi_ssel_value);

            QDomElement osi_tsel = document->createElement("P");
            QDomAttr osi_tsel_type = document->createAttribute("type");
            osi_tsel_type.setValue("OSI-TSEL");
            osi_tsel.setAttributeNode(osi_tsel_type);
            QDomText osi_tsel_value = document->createTextNode("00 01");
            osi_tsel.appendChild(osi_tsel_value);

            address.appendChild(osi_ap_title);
            address.appendChild(osi_ae_qualifier);
            address.appendChild(osi_psel);
            address.appendChild(osi_ssel);
            address.appendChild(osi_tsel);

            if(icdCommunication_page->ipAddressCheckBox->isChecked()) {
                QDomElement ipAddress = document->createElement("P");
                QDomAttr ipAddress_type = document->createAttribute("type");
                ipAddress_type.setValue("IP");
                ipAddress.setAttributeNode(ipAddress_type);
                QDomText ipAddress_value = document->createTextNode(icdCommunication_page->ipAddressText->m_strGetText());
                ipAddress.appendChild(ipAddress_value);

                address.appendChild(ipAddress);
            }
            if(icdCommunication_page->ipSubMaskCheckBox->isChecked()) {
                QDomElement ipSubMask = document->createElement("P");
                QDomAttr ipSubMask_type = document->createAttribute("type");
                ipSubMask_type.setValue("IP-SUBNET");
                ipSubMask.setAttributeNode(ipSubMask_type);
                QDomText ipSubMask_value = document->createTextNode(icdCommunication_page->ipSubMaskText->m_strGetText());
                ipSubMask.appendChild(ipSubMask_value);

                address.appendChild(ipSubMask);
            }
            if(icdCommunication_page->ipGateCheckBox->isChecked()) {
                QDomElement ipGate = document->createElement("P");
                QDomAttr ipGate_type = document->createAttribute("type");
                ipGate_type.setValue("IP-GATEWAY");
                ipGate.setAttributeNode(ipGate_type);
                QDomText ipGate_value = document->createTextNode(icdCommunication_page->ipGateText->m_strGetText());
                ipGate.appendChild(ipGate_value);

                address.appendChild(ipGate);
            }
            connectedAP.appendChild(address);
        }
        subNetwork.appendChild(connectedAP);
        communication.appendChild(subNetwork);
        root.appendChild(communication);
    }

    root.appendChild(ied);

    root.appendChild(dataTypeTemplates);



    QFile   file("test111.icd");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
//        Utils::error(tr("Error writing data: %1").arg(file.error()));
        return ;
    }
    QTextStream streamOut(&file);
    streamOut.setCodec("UTF-8");
    //streamOut << "<?xml version=\"1.0\" encoding=\"utf-8\" ?>\n";
    streamOut << document->toString(4);
    streamOut.flush();
    file.close();



    QDialog::accept();

}

