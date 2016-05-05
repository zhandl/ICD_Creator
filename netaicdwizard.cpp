#include "netaicdwizard.h"
#include <QRegExp>

NetaIcdWizard::NetaIcdWizard(QWidget *parent) :
    QWizard(parent)
{
    QString text(tr("This wizard will generate a ICD file"));
    setWizardStyle(QWizard::ModernStyle);

    resize(800, 600);

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

    icdNETIedLDevice_page = new icdNETIedLDevicePage(this);
    addPage(icdNETIedLDevice_page);

    icdCommunication_page = new icdCommunicationPage(this);
    addPage(icdCommunication_page);

    connect(icdIedServices_page->iedNameText, SIGNAL(textChanged(QString)), icdCommunication_page, SLOT(setIedName(QString)));
    connect(icdIedAccessPoint_page->apNameText, SIGNAL(textChanged(QString)), icdCommunication_page, SLOT(setApName(QString)));

}

void NetaIcdWizard::accept()
{
    setDocument();
//    document = new QDomDocument();
//    createDoc(document);

//    appendHeader(root);

//    if(icdSubstation_page->substationGroupBox->isChecked()) {
//        appendSubstation(root);
//    }

//    QDomElement dataTypeTemplates = document->createElement("DataTypeTemplates");

//    DataTypeModel *dataTypeModel = icdDataTypeTemplateNew_page->selectedModel;
//    foreach (DataTypeItem* item, dataTypeModel->root()->getItems()) {
//        item->generateDom(*document, dataTypeTemplates);
//    }

//    if(icdCommunication_page->communicationGroupBox->isChecked()) {
//        appendCommunication(root);
//    }

//    appendIED(root);


//    root.appendChild(dataTypeTemplates);



//    QFile   file("test111.icd");
//    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
////        Utils::error(tr("Error writing data: %1").arg(file.error()));
//        return ;
//    }
//    QTextStream streamOut(&file);
//    streamOut.setCodec("UTF-8");
//    //streamOut << "<?xml version=\"1.0\" encoding=\"utf-8\" ?>\n";
//    streamOut << document->toString(4);
//    streamOut.flush();
//    file.close();



    QDialog::accept();

}

void NetaIcdWizard::setDocument()
{
    document = new QDomDocument();
    createDoc(document);

    appendHeader(root);

    if(icdSubstation_page->substationGroupBox->isChecked()) {
        appendSubstation(root);
    }

    QDomElement dataTypeTemplates = document->createElement("DataTypeTemplates");

    DataTypeModel *dataTypeModel = icdDataTypeTemplateNew_page->selectedModel;
    foreach (DataTypeItem* item, dataTypeModel->root()->getItems()) {
        item->generateDom(*document, dataTypeTemplates);
    }

    if(icdCommunication_page->communicationGroupBox->isChecked()) {
        appendCommunication(root);
    }

    appendIED(root);


    root.appendChild(dataTypeTemplates);
}

void NetaIcdWizard::createDoc(QDomDocument *doc)
{
    QDomProcessingInstruction instruction;
    instruction = doc->createProcessingInstruction("xml", "version=\"1.0\" encoding = \"UTF-8\"");
    doc->appendChild(instruction);

    root = doc->createElement(tr("SCL"));

    root.setAttribute("xmlns", "http://www.iec.ch/61850/2003/SCL");
    root.setAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
    root.setAttribute("xsi:schemaLocation", "http://www.iec.ch/61850/2003/SCL\\ SCL.xsd");

    doc->appendChild(root);

}

void NetaIcdWizard::appendHeader(QDomElement &parentElement)
{
    QDomElement header = document->createElement("Header");
    parentElement.appendChild(header);

    header.setAttribute("id", icdHeader_page->headerIdText->text());
    header.setAttribute("nameStructure", icdHeader_page->headerNameStructureCombo->currentText());

    if(icdHeader_page->headerVersionCheckBox->isChecked()) {
        header.setAttribute("version", icdHeader_page->headerVersionText->text());
    }
    if(icdHeader_page->headerRevisionCheckBox->isChecked()) {
        header.setAttribute("revision", icdHeader_page->headerRevisionText->text());
    }
    if(icdHeader_page->headerToolIdCheckBox->isChecked()) {
        header.setAttribute("toolID", icdHeader_page->headerToolIdText->text());
    }
    if(icdHeader_page->headerRefCheckBox->isChecked()) {
        header.setAttribute("Ref", icdHeader_page->headerRefText->text());
    }
    if(icdHeader_page->hitemTableWidget->rowCount() > 0) {
        QDomElement headerHistroy = document->createElement("History");
        header.appendChild(headerHistroy);

        for(int i = 0; i < icdHeader_page->hitemTableWidget->rowCount(); i++) {
            QDomElement hitem = document->createElement("Hitem");

            hitem.setAttribute("version",((QLineEdit*)(icdHeader_page->hitemTableWidget->cellWidget(i,0)))->text());
            hitem.setAttribute("revision",((QLineEdit*)(icdHeader_page->hitemTableWidget->cellWidget(i,1)))->text());
            hitem.setAttribute("when",((QDateTimeEdit*)(icdHeader_page->hitemTableWidget->cellWidget(i,2)))->text());
            hitem.setAttribute("what",((QLineEdit*)(icdHeader_page->hitemTableWidget->cellWidget(i,3)))->text());
            hitem.setAttribute("why",((QLineEdit*)(icdHeader_page->hitemTableWidget->cellWidget(i,4)))->text());
            hitem.setAttribute("who",((QLineEdit*)(icdHeader_page->hitemTableWidget->cellWidget(i,0)))->text());

            headerHistroy.appendChild(hitem);
        }
    }
}

void NetaIcdWizard::appendSubstation(QDomElement &parentElement)
{
    QDomElement substation = document->createElement("Substation");
    parentElement.appendChild(substation);

    substation.setAttribute("name", icdSubstation_page->subStationNameText->text());
    if(icdSubstation_page->substationDescCheckBox->isChecked())
        substation.setAttribute("desc", icdSubstation_page->substationDescText->text());

    QDomElement voltageLevel = document->createElement("VoltageLevel");
    substation.appendChild(voltageLevel);

    voltageLevel.setAttribute("name", icdSubstation_page->voltageLevelNameText->text());

    if(icdSubstation_page->voltageGroupBox->isChecked()) {
        QDomElement voltage = document->createElement("Voltage");
        voltageLevel.appendChild(voltage);
        voltage.setAttribute("unit", icdSubstation_page->voltageUnitComboBox->currentText());
        if(icdSubstation_page->voltageMultiplierCheckBox->isChecked())
            voltage.setAttribute("multiplier", icdSubstation_page->voltageMultiplierComboBox->currentText());
    }

    QDomElement bay = document->createElement("Bay");
    voltageLevel.appendChild(bay);
    bay.setAttribute("name", icdSubstation_page->bayNameText->text());
    if(icdSubstation_page->bayDescCheckBox->isChecked())
        bay.setAttribute("desc", icdSubstation_page->bayDescText->text());
}

void NetaIcdWizard::appendCommunication(QDomElement &parentElement)
{
    QDomElement communication = document->createElement("Communication");
    parentElement.appendChild(communication);

    QDomElement subNetwork = document->createElement("SubNetwork");
    subNetwork.setAttribute("name", icdCommunication_page->subNetworkNameText->text());

    if(icdCommunication_page->subNetworkTypeCheckBox->isChecked()) {
        subNetwork.setAttribute("type", icdCommunication_page->subNetworkTypeText->text());
    }
    if(icdCommunication_page->subNetworkDescCheckBox->isChecked()) {
        subNetwork.setAttribute("desc", icdCommunication_page->subNetworkDescText->text());
    }

    if(icdCommunication_page->bitRateGroupBox->isChecked()) {
        QDomElement bitRate = document->createElement("BitRate");
        bitRate.setAttribute("unit", "b/s");
        bitRate.setAttribute("multiplier", "M");

        QDomText bitRateValue = document->createTextNode(icdCommunication_page->bitRateComboBox->currentText());
        bitRate.appendChild(bitRateValue);

        subNetwork.appendChild(bitRate);
    }

    QDomElement connectedAP = document->createElement("ConnectedAP");
    connectedAP.setAttribute("iedName", icdCommunication_page->connectedIedNameText->text());
    connectedAP.setAttribute("apName", icdCommunication_page->connectedApNameText->text());

    if(icdCommunication_page->addressGroupBox->isChecked()) {
        QDomElement address = document->createElement("Address");

        QDomElement osi_ap_title = document->createElement("P");
        osi_ap_title.setAttribute("type", "OSI-AP-Title");
        QDomText osi_ap_title_value = document->createTextNode("1 3 9999 33");
        osi_ap_title.appendChild(osi_ap_title_value);

        QDomElement osi_ae_qualifier = document->createElement("P");
        osi_ae_qualifier.setAttribute("type", "OSI-AE-Qualifier");
        QDomText osi_ae_qualifier_value = document->createTextNode("33");
        osi_ae_qualifier.appendChild(osi_ae_qualifier_value);

        QDomElement osi_psel = document->createElement("P");
        osi_psel.setAttribute("type", "OSI-PSEL");
        QDomText osi_psel_value = document->createTextNode("00 00 00 01");
        osi_psel.appendChild(osi_psel_value);

        QDomElement osi_ssel = document->createElement("P");
        osi_ssel.setAttribute("type", "OSI-SSEL");
        QDomText osi_ssel_value = document->createTextNode("00 01");
        osi_ssel.appendChild(osi_ssel_value);

        QDomElement osi_tsel = document->createElement("P");
        osi_tsel.setAttribute("type", "OSI-TSEL");
        QDomText osi_tsel_value = document->createTextNode("00 01");
        osi_tsel.appendChild(osi_tsel_value);

        address.appendChild(osi_ap_title);
        address.appendChild(osi_ae_qualifier);
        address.appendChild(osi_psel);
        address.appendChild(osi_ssel);
        address.appendChild(osi_tsel);

        if(icdCommunication_page->ipAddressCheckBox->isChecked()) {
            QDomElement ipAddress = document->createElement("P");
            ipAddress.setAttribute("type", "IP");
            QDomText ipAddress_value = document->createTextNode(icdCommunication_page->ipAddressText->m_strGetText());
            ipAddress.appendChild(ipAddress_value);

            address.appendChild(ipAddress);
        }
        if(icdCommunication_page->ipSubMaskCheckBox->isChecked()) {
            QDomElement ipSubMask = document->createElement("P");
            ipSubMask.setAttribute("type", "IP-SUBNET");
            QDomText ipSubMask_value = document->createTextNode(icdCommunication_page->ipSubMaskText->m_strGetText());
            ipSubMask.appendChild(ipSubMask_value);

            address.appendChild(ipSubMask);
        }
        if(icdCommunication_page->ipGateCheckBox->isChecked()) {
            QDomElement ipGate = document->createElement("P");
            ipGate.setAttribute("type", "IP-GATEWAY");
            QDomText ipGate_value = document->createTextNode(icdCommunication_page->ipGateText->m_strGetText());
            ipGate.appendChild(ipGate_value);

            address.appendChild(ipGate);
        }
        connectedAP.appendChild(address);
    }
    subNetwork.appendChild(connectedAP);
    communication.appendChild(subNetwork);

}

void NetaIcdWizard::appendIED(QDomElement &parentElement)
{
    QDomElement ied = document->createElement("IED");
    parentElement.appendChild(ied);

    ied.setAttribute("name", icdIedServices_page->iedNameText->text());

    if(icdIedServices_page->iedConfigVersionCheckBox->isChecked()) {
        ied.setAttribute("configVersion", icdIedServices_page->iedConfigVersionText->text());
    }
    if(icdIedServices_page->iedTypeCheckBox->isChecked()) {
        ied.setAttribute("type", icdIedServices_page->iedTypeText->text());
    }
    if(icdIedServices_page->iedManuCheckBox->isChecked()) {
        ied.setAttribute("manufacturer", icdIedServices_page->iedManuText->text());
    }
    if(icdIedServices_page->iedDescCheckBox->isChecked()) {
        ied.setAttribute("desc", icdIedServices_page->iedDescText->text());
    }

    appendIEDServices(ied);
    appendAccessPoint(ied);
}

void NetaIcdWizard::appendIEDServices(QDomElement &parentElement)
{
    QDomElement services = document->createElement("Services");
    parentElement.appendChild(services);

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
        goose.setAttribute("max", icdIedServices_page->gooseMaxText->text());
        services.appendChild(goose);
    }
    if(icdIedServices_page->gsseGroupBox->isChecked()) {
        QDomElement gsse = document->createElement("GSSE");
        gsse.setAttribute("max", icdIedServices_page->gsseMaxText->text());
        services.appendChild(gsse);
    }
    if(icdIedServices_page->confReportControlGroupBox->isChecked()) {
        QDomElement confReportControl = document->createElement("ConfReportControl");
        confReportControl.setAttribute("max", icdIedServices_page->confReportControlMaxText->text());
        services.appendChild(confReportControl);
    }
    if(icdIedServices_page->confLogControlGroupBox->isChecked()) {
        QDomElement confLogControl = document->createElement("ConfLogControl");
        confLogControl.setAttribute("max", icdIedServices_page->confLogControlMaxText->text());
        services.appendChild(confLogControl);
    }
    if(icdIedServices_page->confDataSetGroupBox->isChecked()) {
        QDomElement confDataSet = document->createElement("ConfDataSet");
        confDataSet.setAttribute("max", icdIedServices_page->confDataSetMaxText->text());
        confDataSet.setAttribute("maxAttributes", icdIedServices_page->confDataSetMaxAttrText->text());

        services.appendChild(confDataSet);
    }
    if(icdIedServices_page->dynDataSetGroupBox->isChecked()) {
        QDomElement dynDataSet = document->createElement("DynDataSet");
        dynDataSet.setAttribute("max", icdIedServices_page->dynDataSetMaxText->text());
        dynDataSet.setAttribute("maxAttributes", icdIedServices_page->dynDataSetMaxAttrText->text());

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
            reportSettings.setAttribute("cbName", icdIedServices_page->reportSettingsCbNameComboBox->currentText());
        }
        if(icdIedServices_page->reportSettingsDatSetCheckBox->isChecked()) {
            reportSettings.setAttribute("datSet", icdIedServices_page->reportSettingsDatSetComboBox->currentText());
        }
        if(icdIedServices_page->reportSettingsRptIdCheckBox->isChecked()) {
            reportSettings.setAttribute("rptId", icdIedServices_page->reportSettingsRptIdComboBox->currentText());
        }
        if(icdIedServices_page->reportSettingsOptFieldsCheckBox->isChecked()) {
            reportSettings.setAttribute("optFields", icdIedServices_page->reportSettingsOptFieldsComboBox->currentText());
        }
        if(icdIedServices_page->reportSettingsBufTimeCheckBox->isChecked()) {
            reportSettings.setAttribute("bufTime", icdIedServices_page->reportSettingsBufTimeComboBox->currentText());
        }
        if(icdIedServices_page->reportSettingsTrgOpsCheckBox->isChecked()) {
            reportSettings.setAttribute("trgOps", icdIedServices_page->reportSettingsTrgOpsComboBox->currentText());
        }
        if(icdIedServices_page->reportSettingsIntgPdCheckBox->isChecked()) {
            reportSettings.setAttribute("intgPd", icdIedServices_page->reportSettingsIntgPdComboBox->currentText());
        }

        services.appendChild(reportSettings);
    }
    if(icdIedServices_page->logSettingsGroupBox->isChecked()) {
        QDomElement logSettings = document->createElement("LogSettings");
        if(icdIedServices_page->logSettingsCbNameCheckBox->isChecked()) {
            logSettings.setAttribute("cbName", icdIedServices_page->logSettingsCbNameComboBox->currentText());
        }
        if(icdIedServices_page->logSettingsDatSetCheckBox->isChecked()) {
            logSettings.setAttribute("datSet", icdIedServices_page->logSettingsDatSetComboBox->currentText());
        }
        if(icdIedServices_page->logSettingsLogEnaCheckBox->isChecked()) {
            logSettings.setAttribute("logEna", icdIedServices_page->logSettingsLogEnaComboBox->currentText());
        }
        if(icdIedServices_page->logSettingsTrgOpsCheckBox->isChecked()) {
            logSettings.setAttribute("trgOps", icdIedServices_page->logSettingsTrgOpsComboBox->currentText());
        }
        if(icdIedServices_page->logSettingsIntgPdCheckBox->isChecked()) {
            logSettings.setAttribute("intgPd", icdIedServices_page->logSettingsIntgPdComboBox->currentText());
        }

        services.appendChild(logSettings);
    }
    if(icdIedServices_page->smvSettingsGroupBox->isChecked()) {
        QDomElement smvSettings = document->createElement("SMVSettings");
        if(icdIedServices_page->smvSettingsCbNameCheckBox->isChecked()) {
            smvSettings.setAttribute("cbName", icdIedServices_page->smvSettingsCbNameComboBox->currentText());
        }
        if(icdIedServices_page->smvSettingsDatSetCheckBox->isChecked()) {
            smvSettings.setAttribute("datSet", icdIedServices_page->smvSettingsDatSetComboBox->currentText());
        }
        if(icdIedServices_page->smvSettingsSvIDCheckBox->isChecked()) {
            smvSettings.setAttribute("svId", icdIedServices_page->smvSettingsSvIDComboBox->currentText());
        }
        if(icdIedServices_page->smvSettingsOptFieldsCheckBox->isChecked()) {
            smvSettings.setAttribute("optFields", icdIedServices_page->smvSettingsOptFieldsComboBox->currentText());
        }
        if(icdIedServices_page->smvSettingsSmpRateCheckBox->isChecked()) {
            smvSettings.setAttribute("smpRate", icdIedServices_page->smvSettingsSmpRateComboBox->currentText());
        }

        services.appendChild(smvSettings);
    }
    if(icdIedServices_page->gseSettingsGroupBox->isChecked()) {
        QDomElement gseSettings = document->createElement("GSESettings");
        if(icdIedServices_page->gseSettingsCbNameCheckBox->isChecked()) {
            gseSettings.setAttribute("cbName", icdIedServices_page->gseSettingsCbNameComboBox->currentText());
        }
        if(icdIedServices_page->gseSettingsDatSetCheckBox->isChecked()) {
            gseSettings.setAttribute("datSet", icdIedServices_page->gseSettingsDatSetComboBox->currentText());
        }
        if(icdIedServices_page->gseSettingsAppIDCheckBox->isChecked()) {
            gseSettings.setAttribute("appID", icdIedServices_page->gseSettingsAppIDComboBox->currentText());
        }
        if(icdIedServices_page->gseSettingsDataLabelCheckBox->isChecked()) {
            gseSettings.setAttribute("dataLabel", icdIedServices_page->gseSettingsDataLabelComboBox->currentText());
        }

        services.appendChild(gseSettings);
    }
    if(icdIedServices_page->confLNsGroupBox->isChecked()) {
        QDomElement confLNs = document->createElement("ConfLNs");
        if(icdIedServices_page->confLNsFixPrefixCheckBox->isChecked()) {
            confLNs.setAttribute("fixPrefix", icdIedServices_page->confLNsFixPrefixComboBox->currentText());
        }
        if(icdIedServices_page->confLNsFixLnInstCheckBox->isChecked()) {
            confLNs.setAttribute("fixLnInst", icdIedServices_page->confLNsFixLnInstComboBox->currentText());
        }
        services.appendChild(confLNs);
    }
}

void NetaIcdWizard::appendAccessPoint(QDomElement &parentElement)
{
    QDomElement accessPoint = document->createElement("AccessPoint");
    parentElement.appendChild(accessPoint);

    accessPoint.setAttribute("name", icdIedAccessPoint_page->apNameText->text());
    if(icdIedAccessPoint_page->apDescCheckBox->isChecked()) {
        accessPoint.setAttribute("desc", icdIedAccessPoint_page->apDescText->text());
    }

    appendServer(accessPoint);
}

void NetaIcdWizard::appendServer(QDomElement &parentElement)
{
    QDomElement server = document->createElement("Server");
    parentElement.appendChild(server);

    if(icdIedAccessPoint_page->apServerDescCheckBox->isChecked()) {
        server.setAttribute("desc", icdIedAccessPoint_page->apServerDescText->text());
    }
    if(icdIedAccessPoint_page->apServerTimeoutCheckBox->isChecked()) {
        server.setAttribute("timeout", icdIedAccessPoint_page->apServerTimeoutText->text());
    }

    appendAuthentication(server);
    appendLD0(server, icdNETIedLDevice_page->auNoComboBox->currentIndex()+1);
    appendPLD(server);

    if(icdNETIedLDevice_page->getGocbNum() > 0)
        appendANGO(server, icdNETIedLDevice_page->getGocbNum());
    if(icdNETIedLDevice_page->getSvcbNum() > 0)
        appendANSV(server, icdNETIedLDevice_page->getSvcbNum());
    if(icdNETIedLDevice_page->getMMSNum() > 0)
        appendANMMS(server, icdNETIedLDevice_page->getMMSNum());
    if(icdNETIedLDevice_page->getIec104Num() > 0)
        appendAN104(server, icdNETIedLDevice_page->getIec104Num());

//    appendLD_thread = new AppendLDThread();
//    appendLD_thread->setParentElement(server);
//    appendLD_thread->setAuNo(icdNETIedLDevice_page->auNoComboBox->currentIndex()+1);
//    appendLD_thread->setGseItemList(icdNETIedLDevice_page->getGseItemList());
//    appendLD_thread->setSvItemList(icdNETIedLDevice_page->getSvItemList());
//    appendLD_thread->setMmsItemList(icdNETIedLDevice_page->getMmsItemList());
//    appendLD_thread->setIec104ItemList(icdNETIedLDevice_page->getIec104ItemList());

//    connect(appendLD_thread, SIGNAL(appendLDOvered()), appendLD_thread, SLOT(deleteLater()));
//    appendLD_thread->start();


}

void NetaIcdWizard::appendAuthentication(QDomElement &parentElement)
{
    QDomElement authentication = document->createElement("Authentication");
    parentElement.appendChild(authentication);

    if(icdIedAccessPoint_page->apServerAuthenticationNoneCheckBox->isChecked()) {
        authentication.setAttribute("none", icdIedAccessPoint_page->apServerAuthenticationNoneComboBox->currentText());
    }
    if(icdIedAccessPoint_page->apServerAuthenticationPasswordCheckBox->isChecked()) {
        authentication.setAttribute("password", icdIedAccessPoint_page->apServerAuthenticationPasswordComboBox->currentText());
    }
    if(icdIedAccessPoint_page->apServerAuthenticationWeakCheckBox->isChecked()) {
        authentication.setAttribute("weak", icdIedAccessPoint_page->apServerAuthenticationWeakComboBox->currentText());
    }
    if(icdIedAccessPoint_page->apServerAuthenticationStrongCheckBox->isChecked()) {
        authentication.setAttribute("strong", icdIedAccessPoint_page->apServerAuthenticationStrongComboBox->currentText());
    }
    if(icdIedAccessPoint_page->apServerAuthenticationCertificateCheckBox->isChecked()) {
        authentication.setAttribute("certificate", icdIedAccessPoint_page->apServerAuthenticationCertificateComboBox->currentText());
    }
}

void NetaIcdWizard::appendLD0(QDomElement &parentElement, int dauNo)
{
    QDomElement LD0 = document->createElement("LDevice");
    parentElement.appendChild(LD0);

    LD0.setAttribute("inst", "LD0");
    LD0.setAttribute("desc", tr("公用LD"));

    appendLLN0(LD0, dauNo);
    appendLPHD(LD0);
    appendLTSM(LD0);
    for(int i = 1; i < dauNo; i++)
        appendGGIO(LD0, i);
}

void NetaIcdWizard::appendPLD(QDomElement &parentElement)
{
    QDomElement PLD = document->createElement("LDevice");
    parentElement.appendChild(PLD);

    PLD.setAttribute("inst", "PLD");
    PLD.setAttribute("desc", tr("预警LD"));

    appendLLN0(PLD, 1);
    appendLPHD(PLD);
    appendGGIO(PLD, 1);
}

void NetaIcdWizard::appendANGO(QDomElement &parentElement, int gocbNum)
{
    QDomElement ANGO = document->createElement("LDevice");
    parentElement.appendChild(ANGO);

    ANGO.setAttribute("inst", "ANGO");
    ANGO.setAttribute("desc", tr("GOOSE控制块链路LD"));

    appendLLN0(ANGO, gocbNum);
    appendLPHD(ANGO);

    for(int i = 1; i <= gocbNum; i++){
        appendGGIO(ANGO, i);
    }
}

void NetaIcdWizard::appendANSV(QDomElement &parentElement, int svcbNum)
{
    QDomElement ANSV = document->createElement("LDevice");
    parentElement.appendChild(ANSV);

    ANSV.setAttribute("inst", "ANSV");
    ANSV.setAttribute("desc", tr("SV控制块链路LD"));

    appendLLN0(ANSV, svcbNum);
    appendLPHD(ANSV);

    for(int i = 1; i <= svcbNum; i++)
        appendGGIO(ANSV, i);
}

void NetaIcdWizard::appendANMMS(QDomElement &parentElement, int mmsNum)
{
    QDomElement ANMMS = document->createElement("LDevice");
    parentElement.appendChild(ANMMS);

    ANMMS.setAttribute("inst", "ANMMS");
    ANMMS.setAttribute("desc", tr("MMS链路LD"));

    appendLLN0(ANMMS, mmsNum);
    appendLPHD(ANMMS);

    for(int i = 1; i <= mmsNum; i++)
        appendGGIO(ANMMS, i);
}

void NetaIcdWizard::appendAN104(QDomElement &parentElement, int iec104Num)
{
    QDomElement AN104 = document->createElement("LDevice");
    parentElement.appendChild(AN104);

    AN104.setAttribute("inst", "AN104");
    AN104.setAttribute("desc", tr("IEC104链路LD"));

    appendLLN0(AN104, iec104Num);
    appendLPHD(AN104);

    for(int i = 1; i <= iec104Num; i++)
        appendGGIO(AN104, i);
}


void NetaIcdWizard::appendLLN0(QDomElement &parentElement, int auNo)
{
    QDomElement LN0 = document->createElement("LN0");
    parentElement.appendChild(LN0);

    LN0.setAttribute("desc", tr("General"));
    LN0.setAttribute("inst", "");
    LN0.setAttribute("lnClass", tr("LLN0"));

    QString ldInst = parentElement.attribute("inst");

    if(ldInst == "LD0") {
        LN0.setAttribute("lnType", tr("LD0/LLN0"));

        int tmpAuNo = auNo;
        int dataSetIndex = 1;

        if(auNo > 25) { //Numbers of FCDA is auNo*10+3 > 256
            while(tmpAuNo > 25) {
                QString dataSetName = "dsWarning" + QString::number(dataSetIndex, 10);
                appendDataSet(LN0, dataSetName, dataSetIndex, 25);
                dataSetIndex++;
                tmpAuNo -= 25;
            }
            QString dataSetName = "dsWarning" + QString::number(dataSetIndex, 10);
            appendDataSet(LN0, dataSetName, dataSetIndex, tmpAuNo);
        } else {
            appendDataSet(LN0, "dsWarning", 1, auNo);
        }

        if(auNo > 25) {  //Numbers of FCDA is auNo*10+3 > 256
            for(int i = 1; i <= dataSetIndex; i++) {
                QByteArray a;
                a.resize(1);
                a[0] = i + 0x40;
                QString reportControlName = "brcbdsWarning" + QString(a.data());
                QString reportControlId = "LD0/LLN0$BR$brcbWarning" + QString(a.data());
                QString reportControlDataSet = "dsWarning" + QString::number(i, 10);
                appendReportControl(LN0, reportControlName, reportControlId, reportControlDataSet);
            }
        } else {
            appendReportControl(LN0, "brcbWarning", "LD0/LLN0$BR$brcbWarning", "dsWarning");
        }

//        appendDataSet(LN0, "dsWarning", auNo);
//        appendReportControl(LN0, "brcbWarning", "LD0/LLN0$BR$brcbWarning", "dsWarning");

        appendDOI(LN0, "Mod", "Mode", "stVal", "on", "ctlModel", "status-only");
        appendDOI(LN0, "Beh", "Behaviour", "stVal", "on");
        appendDOI(LN0, "Health", "Health", "stVal", "Ok");
        appendDOI(LN0, "LEDRs", "SignalReset", "ctlModel", "direct-with-normal-security", "dU", "SignalReset");

    } else if(ldInst == "PLD") {
        LN0.setAttribute("lnType", tr("AN/LLN0"));

        appendDataSet(LN0, "dsWarning", 1, 1);
        appendReportControl(LN0, "brcbWarning", "PLD/LLN0$BR$brcbWarning", "dsWarning");

    } else if(ldInst == "ANGO") {
        LN0.setAttribute("lnType", tr("AN/LLN0"));

        int tmpAuNo = auNo;
        int dataSetIndex = 1;

        if(auNo > 64) { //Numbers of FCDA is gcbNum*4 > 256
            while(tmpAuNo > 64) {
                QString dataSetName = "dsDin" + QString::number(dataSetIndex, 10);
                appendDataSet(LN0, dataSetName, dataSetIndex, 64);
                dataSetIndex++;
                tmpAuNo -= 64;
            }
            QString dataSetName = "dsDin" + QString::number(dataSetIndex, 10);
            appendDataSet(LN0, dataSetName, dataSetIndex, tmpAuNo);
        } else {
            appendDataSet(LN0, "dsDin", 1, auNo);
        }

        tmpAuNo = auNo;
        dataSetIndex = 1;
        if(auNo > 64) { //Numbers of FCDA is gcbNum*4 > 256
            while(tmpAuNo > 64) {
                QString dataSetName = "dsEvent" + QString::number(dataSetIndex, 10);
                appendDataSet(LN0, dataSetName, dataSetIndex, 64);
                dataSetIndex++;
                tmpAuNo -= 64;
            }
            QString dataSetName = "dsEvent" + QString::number(dataSetIndex, 10);
            appendDataSet(LN0, dataSetName, dataSetIndex, tmpAuNo);
        } else {
            appendDataSet(LN0, "dsEvent", 1, auNo);
        }

        tmpAuNo = auNo;
        dataSetIndex = 1;
        if(auNo > 51) { //Numbers of FCDA is gcbNum*5 > 256
            while(tmpAuNo > 51) {
                QString dataSetName = "dsStatistic" + QString::number(dataSetIndex, 10);
                appendDataSet(LN0, dataSetName, dataSetIndex, 51);
                dataSetIndex++;
                tmpAuNo -= 51;
            }
            QString dataSetName = "dsStatistic" + QString::number(dataSetIndex, 10);
            appendDataSet(LN0, dataSetName, dataSetIndex, tmpAuNo);
        } else {
            appendDataSet(LN0, "dsStatistic", 1, auNo);
        }

        if(auNo > 64) {  //Numbers of FCDA is gcbNum*4 > 256
            for(int i = 1; i <= (auNo/64+1); i++) {
                QByteArray a;
                a.resize(1);
                a[0] = i + 0x40;
                QString reportControlName = "brcbGOOSEDin" + QString(a.data());
                QString reportControlId = "ANGO/LLN0$BR$brcbGOOSEDin" + QString(a.data());
                QString reportControlDataSet = "dsDin" + QString::number(i, 10);
                appendReportControl(LN0, reportControlName, reportControlId, reportControlDataSet);
            }
        } else {
            appendReportControl(LN0, "brcbGOOSEDin", "ANGO/LLN0$BR$brcbGOOSEDin", "dsDin");
        }

        if(auNo > 64) {  //Numbers of FCDA is gcbNum*4 > 256
            for(int i = 1; i <= (auNo/64+1); i++) {
                QByteArray a;
                a.resize(1);
                a[0] = i + 0x40;
                QString reportControlName = "brcbGOOSEEvent" + QString(a.data());
                QString reportControlId = "ANGO/LLN0$BR$brcbGOOSEEvent" + QString(a.data());
                QString reportControlDataSet = "dsEvent" + QString::number(i, 10);
                appendReportControl(LN0, reportControlName, reportControlId, reportControlDataSet);
            }
        } else {
            appendReportControl(LN0, "brcbGOOSEEvent", "ANGO/LLN0$BR$brcbGOOSEEvent", "dsEvent");
        }

        if(auNo > 51) {  //Numbers of FCDA is gcbNum*5 > 256
            for(int i = 1; i <= (auNo/51+1); i++) {
                QByteArray a;
                a.resize(1);
                a[0] = i + 0x40;
                QString reportControlName = "urcbGOOSEStatistic" + QString(a.data());
                QString reportControlId = "ANGO/LLN0$RP$urcbGOOSEStatistic" + QString(a.data());
                QString reportControlDataSet = "dsStatistic" + QString::number(i, 10);
                appendReportControl(LN0, reportControlName, reportControlId, reportControlDataSet);
            }
        } else {
            appendReportControl(LN0, "urcbGOOSEStatistic", "ANGO/LLN0$RP$urcbGOOSEStatistic", "dsStatistic");
        }

//        appendDataSet(LN0, "dsDin", auNo);
//        appendDataSet(LN0, "dsEvent", auNo);
//        appendDataSet(LN0, "dsStatistic", auNo);

//        appendReportControl(LN0, "brcbGOOSEDin", "ANGO/LLN0$BR$brcbGOOSEDin", "dsDin");
//        appendReportControl(LN0, "brcbGOOSEEvnet", "ANGO/LLN0$BR$brcbGOOSEEvent", "dsEvent");
//        appendReportControl(LN0, "urcbGOOSEStatistic", "ANGO/LLN0$RP$urcbGOOSEStatistic", "dsStatistic");

        appendDOI(LN0, "Mod", "Mode", "stVal", "on");
        appendDOI(LN0, "Beh", "Behaviour", "stVal", "on");
        appendDOI(LN0, "Health", "Health", "stVal", "Ok");

    } else if(ldInst == "ANSV") {
        LN0.setAttribute("lnType", tr("AN/LLN0"));

        int tmpAuNo = auNo;
        int dataSetIndex = 1;

        if(auNo > 51) { //Numbers of FCDA is svcbNum*5 > 256
            while(tmpAuNo > 51) {
                QString dataSetName = "dsDin" + QString::number(dataSetIndex, 10);
                appendDataSet(LN0, dataSetName, dataSetIndex, 51);
                dataSetIndex++;
                tmpAuNo -= 51;
            }
            QString dataSetName = "dsDin" + QString::number(dataSetIndex, 10);
            appendDataSet(LN0, dataSetName, dataSetIndex, tmpAuNo);
        } else {
            appendDataSet(LN0, "dsDin", 1, auNo);
        }

        tmpAuNo = auNo;
        dataSetIndex = 1;
        if(auNo > 256) { //Numbers of FCDA is gcbNum*1 > 256
            while(tmpAuNo > 256) {
                QString dataSetName = "dsEvent" + QString::number(dataSetIndex, 10);
                appendDataSet(LN0, dataSetName, dataSetIndex, 256);
                dataSetIndex++;
                tmpAuNo -= 256;
            }
            QString dataSetName = "dsEvent" + QString::number(dataSetIndex, 10);
            appendDataSet(LN0, dataSetName, dataSetIndex, tmpAuNo);
        } else {
            appendDataSet(LN0, "dsEvent", 1, auNo);
        }

        tmpAuNo = auNo;
        dataSetIndex = 1;
        if(auNo > 51) { //Numbers of FCDA is svcbNum*5 > 256
            while(tmpAuNo > 51) {
                QString dataSetName = "dsStatistic" + QString::number(dataSetIndex, 10);
                appendDataSet(LN0, dataSetName, dataSetIndex, 51);
                dataSetIndex++;
                tmpAuNo -= 51;
            }
            QString dataSetName = "dsStatistic" + QString::number(dataSetIndex, 10);
            appendDataSet(LN0, dataSetName, dataSetIndex, tmpAuNo);
        } else {
            appendDataSet(LN0, "dsStatistic", 1, auNo);
        }

        if(auNo > 51) {  //Numbers of FCDA is gcbNum*4 > 256
            for(int i = 1; i <= (auNo/64+1); i++) {
                QByteArray a;
                a.resize(1);
                a[0] = i + 0x40;
                QString reportControlName = "brcbSVDin" + QString(a.data());
                QString reportControlId = "ANSV/LLN0$BR$brcbSVDin" + QString(a.data());
                QString reportControlDataSet = "dsDin" + QString::number(i, 10);
                appendReportControl(LN0, reportControlName, reportControlId, reportControlDataSet);
            }
        } else {
            appendReportControl(LN0, "brcbSVDin", "ANSV/LLN0$BR$brcbSVDin", "dsDin");
        }

        if(auNo > 256) {  //Numbers of FCDA is gcbNum*4 > 256
            for(int i = 1; i <= (auNo/256+1); i++) {
                QByteArray a;
                a.resize(1);
                a[0] = i + 0x40;
                QString reportControlName = "brcbSVEvent" + QString(a.data());
                QString reportControlId = "ANSV/LLN0$BR$brcbSVEvent" + QString(a.data());
                QString reportControlDataSet = "dsEvent" + QString::number(i, 10);
                appendReportControl(LN0, reportControlName, reportControlId, reportControlDataSet);
            }
        } else {
            appendReportControl(LN0, "brcbSVEvent", "ANSV/LLN0$BR$brcbSVEvent", "dsEvent");
        }

        if(auNo > 51) {  //Numbers of FCDA is gcbNum*5 > 256
            for(int i = 1; i <= (auNo/51+1); i++) {
                QByteArray a;
                a.resize(1);
                a[0] = i + 0x40;
                QString reportControlName = "urcbSVStatistic" + QString(a.data());
                QString reportControlId = "ANSV/LLN0$RP$urcbSVStatistic" + QString(a.data());
                QString reportControlDataSet = "dsStatistic" + QString::number(i, 10);
                appendReportControl(LN0, reportControlName, reportControlId, reportControlDataSet);
            }
        } else {
            appendReportControl(LN0, "urcbSVStatistic", "ANSV/LLN0$RP$urcbSVStatistic", "dsStatistic");
        }
//        LN0.setAttribute("lnType", tr("AN/LLN0"));

//        appendDataSet(LN0, "dsDin", 1, auNo);
//        appendDataSet(LN0, "dsEvent", 1, auNo);
//        appendDataSet(LN0, "dsStatistic", 1, auNo);

//        appendReportControl(LN0, "brcbSVDin", "ANSV/LLN0$BR$brcbSVDin", "dsDin");
//        appendReportControl(LN0, "brcbSVEvnet", "ANSV/LLN0$BR$brcbSVEvent", "dsEvent");
//        appendReportControl(LN0, "urcbSVStatistic", "ANSV/LLN0$RP$urcbSVStatistic", "dsStatistic");

        appendDOI(LN0, "Mod", "Mode", "stVal", "on", "ctModel", "status-only");
        appendDOI(LN0, "Beh", "Behaviour", "stVal", "on");
        appendDOI(LN0, "Health", "Health", "stVal", "Ok");
    }

    else if(ldInst == "ANMMS") {
        LN0.setAttribute("lnType", tr("AN/LLN0"));

        int tmpAuNo = auNo;
        int dataSetIndex = 1;

        if(auNo > 51) { //Numbers of FCDA is mmsNum*5 > 256
            while(tmpAuNo > 51) {
                QString dataSetName = "dsDin" + QString::number(dataSetIndex, 10);
                appendDataSet(LN0, dataSetName, dataSetIndex, 51);
                dataSetIndex++;
                tmpAuNo -= 51;
            }
            QString dataSetName = "dsDin" + QString::number(dataSetIndex, 10);
            appendDataSet(LN0, dataSetName, dataSetIndex, tmpAuNo);
        } else {
            appendDataSet(LN0, "dsDin", 1, auNo);
        }

        tmpAuNo = auNo;
        dataSetIndex = 1;
        if(auNo > 42) { //Numbers of FCDA is mmsNum*6 > 256
            while(tmpAuNo > 42) {
                QString dataSetName = "dsEvent" + QString::number(dataSetIndex, 10);
                appendDataSet(LN0, dataSetName, dataSetIndex, 42);
                dataSetIndex++;
                tmpAuNo -= 42;
            }
            QString dataSetName = "dsEvent" + QString::number(dataSetIndex, 10);
            appendDataSet(LN0, dataSetName, dataSetIndex, tmpAuNo);
        } else {
            appendDataSet(LN0, "dsEvent", 1, auNo);
        }

        tmpAuNo = auNo;
        dataSetIndex = 1;
        if(auNo > 25) { //Numbers of FCDA is mmsNum*10 > 256
            while(tmpAuNo > 25) {
                QString dataSetName = "dsStatistic" + QString::number(dataSetIndex, 10);
                appendDataSet(LN0, dataSetName, dataSetIndex, 25);
                dataSetIndex++;
                tmpAuNo -= 25;
            }
            QString dataSetName = "dsStatistic" + QString::number(dataSetIndex, 10);
            appendDataSet(LN0, dataSetName, dataSetIndex, tmpAuNo);
        } else {
            appendDataSet(LN0, "dsStatistic", 1, auNo);
        }

        if(auNo > 51) {  //Numbers of FCDA is mmsNum*5 > 256
            for(int i = 1; i <= (auNo/51+1); i++) {
                QByteArray a;
                a.resize(1);
                a[0] = i + 0x40;
                QString reportControlName = "brcbMMSDin" + QString(a.data());
                QString reportControlId = "ANMMS/LLN0$BR$brcbMMSDin" + QString(a.data());
                QString reportControlDataSet = "dsDin" + QString::number(i, 10);
                appendReportControl(LN0, reportControlName, reportControlId, reportControlDataSet);
            }
        } else {
            appendReportControl(LN0, "brcbMMSDin", "ANMMS/LLN0$BR$brcbMMSDin", "dsDin");
        }

        if(auNo > 42) {  //Numbers of FCDA is mmsNum*4 > 256
            for(int i = 1; i <= (auNo/42+1); i++) {
                QByteArray a;
                a.resize(1);
                a[0] = i + 0x40;
                QString reportControlName = "brcbMMSEvent" + QString(a.data());
                QString reportControlId = "ANMMS/LLN0$BR$brcbMMSEvent" + QString(a.data());
                QString reportControlDataSet = "dsEvent" + QString::number(i, 10);
                appendReportControl(LN0, reportControlName, reportControlId, reportControlDataSet);
            }
        } else {
            appendReportControl(LN0, "brcbMMSEvent", "ANMMS/LLN0$BR$brcbMMSEvent", "dsEvent");
        }

        if(auNo > 25) {  //Numbers of FCDA is mmsNum*10 > 256
            for(int i = 1; i <= (auNo/25+1); i++) {
                QByteArray a;
                a.resize(1);
                a[0] = i + 0x40;
                QString reportControlName = "urcbMMSStatistic" + QString(a.data());
                QString reportControlId = "ANMMS/LLN0$RP$urcbMMSStatistic" + QString(a.data());
                QString reportControlDataSet = "dsStatistic" + QString::number(i, 10);
                appendReportControl(LN0, reportControlName, reportControlId, reportControlDataSet);
            }
        } else {
            appendReportControl(LN0, "urcbMMSStatistic", "ANMMS/LLN0$RP$urcbMMSStatistic", "dsStatistic");
        }
//        LN0.setAttribute("lnType", tr("AN/LLN0"));

//        appendDataSet(LN0, "dsDin", 1, auNo);
//        appendDataSet(LN0, "dsEvent", 1, auNo);
//        appendDataSet(LN0, "dsStatistic", 1, auNo);

//        appendReportControl(LN0, "brcbSVDin", "ANSV/LLN0$BR$brcbSVDin", "dsDin");
//        appendReportControl(LN0, "brcbSVEvnet", "ANSV/LLN0$BR$brcbSVEvent", "dsEvent");
//        appendReportControl(LN0, "urcbSVStatistic", "ANSV/LLN0$RP$urcbSVStatistic", "dsStatistic");

        appendDOI(LN0, "Mod", "Mode", "stVal", "on", "ctModel", "status-only");
        appendDOI(LN0, "Beh", "Behaviour", "stVal", "on");
        appendDOI(LN0, "Health", "Health", "stVal", "Ok");
    }

    else if(ldInst == "AN104") {
        LN0.setAttribute("lnType", tr("AN/LLN0"));

        int tmpAuNo = auNo;
        int dataSetIndex = 1;

        if(auNo > 256) { //Numbers of FCDA is iec104Num*1 > 256
            while(tmpAuNo > 256) {
                QString dataSetName = "dsDin" + QString::number(dataSetIndex, 10);
                appendDataSet(LN0, dataSetName, dataSetIndex, 256);
                dataSetIndex++;
                tmpAuNo -= 256;
            }
            QString dataSetName = "dsDin" + QString::number(dataSetIndex, 10);
            appendDataSet(LN0, dataSetName, dataSetIndex, tmpAuNo);
        } else {
            appendDataSet(LN0, "dsDin", 1, auNo);
        }

        tmpAuNo = auNo;
        dataSetIndex = 1;
        if(auNo > 85) { //Numbers of FCDA is iec104Num*3 > 256
            while(tmpAuNo > 85) {
                QString dataSetName = "dsEvent" + QString::number(dataSetIndex, 10);
                appendDataSet(LN0, dataSetName, dataSetIndex, 85);
                dataSetIndex++;
                tmpAuNo -= 85;
            }
            QString dataSetName = "dsEvent" + QString::number(dataSetIndex, 10);
            appendDataSet(LN0, dataSetName, dataSetIndex, tmpAuNo);
        } else {
            appendDataSet(LN0, "dsEvent", 1, auNo);
        }

        tmpAuNo = auNo;
        dataSetIndex = 1;
        if(auNo > 23) { //Numbers of FCDA is iec104Num*11 > 256
            while(tmpAuNo > 23) {
                QString dataSetName = "dsStatistic" + QString::number(dataSetIndex, 10);
                appendDataSet(LN0, dataSetName, dataSetIndex, 23);
                dataSetIndex++;
                tmpAuNo -= 23;
            }
            QString dataSetName = "dsStatistic" + QString::number(dataSetIndex, 10);
            appendDataSet(LN0, dataSetName, dataSetIndex, tmpAuNo);
        } else {
            appendDataSet(LN0, "dsStatistic", 1, auNo);
        }

        if(auNo > 256) {  //Numbers of FCDA is mmsNum*5 > 256
            for(int i = 1; i <= (auNo/256+1); i++) {
                QByteArray a;
                a.resize(1);
                a[0] = i + 0x40;
                QString reportControlName = "brcb104Din" + QString(a.data());
                QString reportControlId = "AN104/LLN0$BR$brcb104Din" + QString(a.data());
                QString reportControlDataSet = "dsDin" + QString::number(i, 10);
                appendReportControl(LN0, reportControlName, reportControlId, reportControlDataSet);
            }
        } else {
            appendReportControl(LN0, "brcb104Din", "AN104/LLN0$BR$brcb104Din", "dsDin");
        }

        if(auNo > 85) {  //Numbers of FCDA is iec104Num*3 > 256
            for(int i = 1; i <= (auNo/85+1); i++) {
                QByteArray a;
                a.resize(1);
                a[0] = i + 0x40;
                QString reportControlName = "brcb104Event" + QString(a.data());
                QString reportControlId = "AN104/LLN0$BR$brcb104Event" + QString(a.data());
                QString reportControlDataSet = "dsEvent" + QString::number(i, 10);
                appendReportControl(LN0, reportControlName, reportControlId, reportControlDataSet);
            }
        } else {
            appendReportControl(LN0, "brcb104Event", "AN104/LLN0$BR$brcb104Event", "dsEvent");
        }

        if(auNo > 23) {  //Numbers of FCDA is mmsNum*10 > 256
            for(int i = 1; i <= (auNo/23+1); i++) {
                QByteArray a;
                a.resize(1);
                a[0] = i + 0x40;
                QString reportControlName = "urcb104Statistic" + QString(a.data());
                QString reportControlId = "AN104/LLN0$RP$urcb104Statistic" + QString(a.data());
                QString reportControlDataSet = "dsStatistic" + QString::number(i, 10);
                appendReportControl(LN0, reportControlName, reportControlId, reportControlDataSet);
            }
        } else {
            appendReportControl(LN0, "urcb104Statistic", "AN104/LLN0$RP$urcb104Statistic", "dsStatistic");
        }
//        LN0.setAttribute("lnType", tr("AN/LLN0"));

//        appendDataSet(LN0, "dsDin", 1, auNo);
//        appendDataSet(LN0, "dsEvent", 1, auNo);
//        appendDataSet(LN0, "dsStatistic", 1, auNo);

//        appendReportControl(LN0, "brcbSVDin", "ANSV/LLN0$BR$brcbSVDin", "dsDin");
//        appendReportControl(LN0, "brcbSVEvnet", "ANSV/LLN0$BR$brcbSVEvent", "dsEvent");
//        appendReportControl(LN0, "urcbSVStatistic", "ANSV/LLN0$RP$urcbSVStatistic", "dsStatistic");

        appendDOI(LN0, "Mod", "Mode", "stVal", "on", "ctModel", "status-only");
        appendDOI(LN0, "Beh", "Behaviour", "stVal", "on");
        appendDOI(LN0, "Health", "Health", "stVal", "Ok");
    }

}

void NetaIcdWizard::appendLPHD(QDomElement &parentElement)
{
    QDomElement LPHD = document->createElement("LN");
    parentElement.appendChild(LPHD);

    LPHD.setAttribute("desc", "device");
    LPHD.setAttribute("inst", "1");
    LPHD.setAttribute("lnClass", "LPHD");
    LPHD.setAttribute("lnType", "LPHD");

    QString ldInst = parentElement.attribute("inst");

    if(ldInst == "LD0"){
        appendDOI(LPHD, "PhyNam", "PhyName", "hwRev", "1.00", "swRev", "1.00", "vendor", "GDWY", "model", "ZJ");
    } else {//if(ldInst == "ANGO"){
        appendDOI(LPHD, "PhyHealth", "PhyHealth", "stVal", "Ok");
    }
}

void NetaIcdWizard::appendLTSM(QDomElement &parentElement)
{
    QDomElement LTSM = document->createElement("LN");
    parentElement.appendChild(LTSM);

    LTSM.setAttribute("desc", tr("对时自检信息"));
    LTSM.setAttribute("inst", "1");
    LTSM.setAttribute("lnClass", "LTSM");

    if(parentElement.attribute("inst") == "LD0"){
        LTSM.setAttribute("lnType", "LD0/LTSM");
        appendDOI(LTSM, "Mod", "Mode", "stVal", "on", "ctlModel", "status-only");
        appendDOI(LTSM, "Beh", "Behaviour", "stVal", "on");
        appendDOI(LTSM, "Health", "Health", "stVal", "Ok");
        appendDOI(LTSM, "NamPlt", "NamPlt", "lnNs", "SGCC MODEL:2012");
        appendDOI(LTSM, "HostTPortAlarm", tr("对时信号状态"), "dU", tr("对时信号状态"));
        appendDOI(LTSM, "HostTSrvAlarm", tr("对时服务状态"), "dU", tr("对时服务状态"));
        appendDOI(LTSM, "HostContAlarm", tr("时间跳变侦测状态"), "dU", tr("时间跳变侦测状态"));
    }
}

void NetaIcdWizard::appendGGIO(QDomElement &parentElement, int lnInst)
{
    QDomElement GGIO = document->createElement("LN");
    parentElement.appendChild(GGIO);

    GGIO.setAttribute("inst", QString::number(lnInst, 10));
    GGIO.setAttribute("lnClass", "GGIO");

    QString ldInst = parentElement.attribute("inst");

    if(ldInst == "LD0"){
        GGIO.setAttribute("desc", "device");
        GGIO.setAttribute("lnType", "LD0/GGIO");
        appendDOI(GGIO, "Mod", "Mode", "stVal", "on", "ctlModel", "status-only");
        appendDOI(GGIO, "Beh", "Behaviour", "stVal", "on");
        appendDOI(GGIO, "Health", "Health", "stVal", "Ok");
        appendDOI(GGIO, "ConSt", tr("联通状态"), "dU", tr("联通状态"));
        appendDOI(GGIO, "DSAlm", tr("单元故障告警"), "dU", tr("单元故障告警"));
        appendDOI(GGIO, "CI1St", tr("采集接口1中断"), "dU", tr("采集接口1中断"));
        appendDOI(GGIO, "CI2St", tr("采集接口2中断"), "dU", tr("采集接口2中断"));
        appendDOI(GGIO, "CI3St", tr("采集接口3中断"), "dU", tr("采集接口3中断"));
        appendDOI(GGIO, "CI4St", tr("采集接口4中断"), "dU", tr("采集接口4中断"));
        appendDOI(GGIO, "CI5St", tr("采集接口5中断"), "dU", tr("采集接口5中断"));
        appendDOI(GGIO, "CI6St", tr("采集接口6中断"), "dU", tr("采集接口6中断"));
        appendDOI(GGIO, "CI7St", tr("采集接口7中断"), "dU", tr("采集接口7中断"));
        appendDOI(GGIO, "CI8St", tr("采集接口8中断"), "dU", tr("采集接口8中断"));

    } else if(ldInst == "PLD") {
        GGIO.setAttribute("desc", tr("公共告警信息"));
        GGIO.setAttribute("lnType", "AlmLD/GGIO");
        appendDOI(GGIO, "TrafficChgAlm", tr("流量突变"), "dU", tr("流量突变"));
        appendDOI(GGIO, "TcpConAlm", tr("TCP会话异常"), "dU", tr("TCP会话异常"));
        appendDOI(GGIO, "ModelInconAlm", tr("SCD模型不一致"), "dU", tr("SCD模型不一致"));
        appendDOI(GGIO, "YCNoUdpAlm", tr("遥测不刷新"), "dU", tr("遥测不刷新"));
        appendDOI(GGIO, "YXFrqChgAlm", tr("遥信频繁变位"), "dU", tr("遥信频繁变位"));

    } else if(ldInst == "ANGO") {
        int childIndex = lnInst - 1;
        QString gcbDesc = icdNETIedLDevice_page->_gcbItem->child(childIndex)->text(4);
        QString gcbAppID = icdNETIedLDevice_page->_gcbItem->child(childIndex)->text(3);
        QString gcbMac = icdNETIedLDevice_page->_gcbItem->child(childIndex)->text(2);
        QString NamPlt = gcbMac+"@"+gcbAppID;
        GGIO.setAttribute("desc", "@"+gcbDesc+"@"+tr("GOOSE发送")+"@"+gcbAppID);
        GGIO.setAttribute("lnType", "GOOSE/GGIO");

        appendDOI(GGIO, "NamPlt", NamPlt, "dU", NamPlt);

        appendDOI(GGIO, "ConSt", tr("通信状态"), "dU", tr("通信状态"));
        appendDOI(GGIO, "EtyTmSt", tr("条目时间状态"), "dU", tr("条目时间状态"));
        appendDOI(GGIO, "TestSt", tr("测试状态"), "dU", tr("测试状态"));
        appendDOI(GGIO, "CfgSt", tr("配置状态"), "dU", tr("配置状态"));
        appendDOI(GGIO, "Reset", tr("GOOSE控制块重启"), "dU", tr("GOOSE控制块重启"));
        appendDOI(GGIO, "StFakeChg", tr("GOOSE状态虚变"), "dU", tr("GOOSE状态虚变"));
        appendDOI(GGIO, "StAbnChg", tr("GOOSE状态异常变化"), "dU", tr("GOOSE状态异常变化"));
        appendDOI(GGIO, "Tmout", tr("GOOSE发送超时"), "dU", tr("GOOSE发送超时"));
        appendDOI(GGIO, "FrmErrCnt", tr("报文结构错误次数"), "dU", tr("报文结构错误次数"));
        appendDOI(GGIO, "ChkErrCnt", tr("规约符合性错误次数"), "dU", tr("规约符合性错误次数"));
        appendDOI(GGIO, "FrmSeqAbnCnt", tr("GOOSE帧序号异常次数"), "dU", tr("GOOSE帧序号异常次数"));
        appendDOI(GGIO, "FramesQty", tr("GOOSE报文帧数"), "dU", tr("GOOSE报文帧数"));
        appendDOI(GGIO, "BytesQty", tr("GOOSE报文字节数"), "dU", tr("GOOSE报文字节数"));

    } else if(ldInst == "ANSV") {
        int childIndex = lnInst - 1;
        QString svcbDesc = icdNETIedLDevice_page->_svcbItem->child(childIndex)->text(4);
        QString svcbAppID = icdNETIedLDevice_page->_svcbItem->child(childIndex)->text(3);
        QString svcbMac = icdNETIedLDevice_page->_svcbItem->child(childIndex)->text(2);
        QString NamPlt = svcbMac+"@"+svcbAppID;
        GGIO.setAttribute("desc", "@"+svcbDesc+"@"+svcbAppID);
        GGIO.setAttribute("lnType", "SV/GGIO");

        appendDOI(GGIO, "NamPlt", NamPlt, "dU", NamPlt);

        appendDOI(GGIO, "ConSt", tr("通信状态"), "dU", tr("通信状态"));
        appendDOI(GGIO, "SynSt", tr("同步状态"), "dU", tr("同步状态"));
        appendDOI(GGIO, "TestSt", tr("测试状态"), "dU", tr("测试状态"));
        appendDOI(GGIO, "VlvInvSt", tr("数据无效状态"), "dU", tr("数据无效状态"));
        appendDOI(GGIO, "CfgSt", tr("配置状态"), "dU", tr("配置状态"));
        appendDOI(GGIO, "LimLosOv", tr("采样严重丢帧"), "dU", tr("采样严重丢帧"));
        appendDOI(GGIO, "FrmErrCnt", tr("报文结构错误次数"), "dU", tr("报文结构错误次数"));
        appendDOI(GGIO, "ChkErrCnt", tr("规约符合性错误次数"), "dU", tr("规约符合性错误次数"));
        appendDOI(GGIO, "LosCnt", tr("采样丢帧发生次数"), "dU", tr("采样丢帧发生次数"));
        appendDOI(GGIO, "FramesQty", tr("SV报文帧数"), "dU", tr("SV报文帧数"));
        appendDOI(GGIO, "BytesQty", tr("SV报文字节数"), "dU", tr("SV报文字节数"));
    }
}

void NetaIcdWizard::appendDataSet(QDomElement &parentElement, const QString name, const int dataSetIndex, int auNo)
{
    QDomElement LN0DataSet  = document->createElement("DataSet");
    parentElement.appendChild(LN0DataSet);

    QString desc = "";

    LN0DataSet.setAttribute("name", name);
    if(name.contains("dsWarning"))
        desc = tr("告警信号");
    else if(name.contains("dsDin"))
        desc = tr("状态数据集");
    else if(name.contains("dsEvent"))
        desc = tr("事件数据集");
    else if(name.contains("dsStatistic"))
        desc = tr("统计数据集");

    LN0DataSet.setAttribute("desc", desc);

    QString ldInst = parentElement.parentNode().toElement().attribute("inst");
//    QString lnType = parentElement.attribute("lnType");

    if(ldInst == "LD0" && name.contains("dsWarning")) {
        if(dataSetIndex == 1) {
            appendFcdNode(LN0DataSet, "LD0", "LTSM", "1", "HostTPortAlarm", "ST");
            appendFcdNode(LN0DataSet, "LD0", "LTSM", "1", "HostTSrvAlarm", "ST");
            appendFcdNode(LN0DataSet, "LD0", "LTSM", "1", "HostContAlarm", "ST");
        }
        for(int i = 1; i <= auNo; i++) {
            QString lnInst = QString::number(25 * (dataSetIndex - 1) + i, 10);
            appendFcdNode(LN0DataSet, "LD0", "GGIO", lnInst, "ConSt", "ST");
            appendFcdNode(LN0DataSet, "LD0", "GGIO", lnInst, "DSAlm", "ST");
            appendFcdNode(LN0DataSet, "LD0", "GGIO", lnInst, "CI1St", "ST");
            appendFcdNode(LN0DataSet, "LD0", "GGIO", lnInst, "CI2St", "ST");
            appendFcdNode(LN0DataSet, "LD0", "GGIO", lnInst, "CI3St", "ST");
            appendFcdNode(LN0DataSet, "LD0", "GGIO", lnInst, "CI4St", "ST");
            appendFcdNode(LN0DataSet, "LD0", "GGIO", lnInst, "CI5St", "ST");
            appendFcdNode(LN0DataSet, "LD0", "GGIO", lnInst, "CI6St", "ST");
            appendFcdNode(LN0DataSet, "LD0", "GGIO", lnInst, "CI7St", "ST");
            appendFcdNode(LN0DataSet, "LD0", "GGIO", lnInst, "CI8St", "ST");
        }

    } else if(ldInst == "PLD" && name.contains("dsWarning")) {
        LN0DataSet.setAttribute("desc", tr("告警信号"));
        LN0DataSet.setAttribute("name", "dsWarning");

        appendFcdNode(LN0DataSet, "PLD", "GGIO", "1", "TrafficChgAlm", "ST");
        appendFcdNode(LN0DataSet, "PLD", "GGIO", "1", "TcpConAlm", "ST");
        appendFcdNode(LN0DataSet, "PLD", "GGIO", "1", "ModelInconAlm", "ST");
        appendFcdNode(LN0DataSet, "PLD", "GGIO", "1", "YCNoUdpAlm", "ST");
        appendFcdNode(LN0DataSet, "PLD", "GGIO", "1", "YXFrqChgAlm", "ST");

    } else if(ldInst == "ANGO" && name.contains("dsDin")) {
        for(int i = 1; i <= auNo; i++) {
            QString lnInst = QString::number(64 * (dataSetIndex - 1) + i, 10);
            appendFcdNode(LN0DataSet, "ANGO", "GGIO", lnInst, "ConSt", "ST");
            appendFcdNode(LN0DataSet, "ANGO", "GGIO", lnInst, "EtyTmSt", "ST");
            appendFcdNode(LN0DataSet, "ANGO", "GGIO", lnInst, "TestSt", "ST");
            appendFcdNode(LN0DataSet, "ANGO", "GGIO", lnInst, "CfgSt", "ST");
        }
    } else if(ldInst == "ANGO" && name.contains("dsEvent")) {
        for(int i = 1; i <= auNo; i++) {
            QString lnInst = QString::number(64 * (dataSetIndex - 1) + i, 10);
            appendFcdNode(LN0DataSet, "ANGO", "GGIO", lnInst, "Reset", "ST");
            appendFcdNode(LN0DataSet, "ANGO", "GGIO", lnInst, "StFakeChg", "ST");
            appendFcdNode(LN0DataSet, "ANGO", "GGIO", lnInst, "StAbnChg", "ST");
            appendFcdNode(LN0DataSet, "ANGO", "GGIO", lnInst, "Tmout", "ST");
        }
    } else if(ldInst == "ANGO" && name.contains("dsStatistic")) {
        for(int i = 1; i <= auNo; i++) {
            QString lnInst = QString::number(51 * (dataSetIndex - 1) + i, 10);
            appendFcdaNode(LN0DataSet, "ANGO", "GGIO", lnInst, "FrmErrCnt", "stVal", "ST");
            appendFcdaNode(LN0DataSet, "ANGO", "GGIO", lnInst, "ChkErrCnt", "stVal", "ST");
            appendFcdaNode(LN0DataSet, "ANGO", "GGIO", lnInst, "FrmSeqAbnCnt", "stVal", "ST");
            appendFcdaNode(LN0DataSet, "ANGO", "GGIO", lnInst, "FramesQty", "stVal", "ST");
            appendFcdaNode(LN0DataSet, "ANGO", "GGIO", lnInst, "BytesQty", "stVal", "ST");
        }

    } else if(ldInst == "ANSV" && name.contains("dsDin")) {
        for(int i = 1; i <= auNo; i++) {
            QString lnInst = QString::number(51 * (dataSetIndex - 1) + i, 10);
            appendFcdNode(LN0DataSet, "ANSV", "GGIO", lnInst, "ConSt", "ST");
            appendFcdNode(LN0DataSet, "ANSV", "GGIO", lnInst, "SynSt", "ST");
            appendFcdNode(LN0DataSet, "ANSV", "GGIO", lnInst, "TestSt", "ST");
            appendFcdNode(LN0DataSet, "ANSV", "GGIO", lnInst, "VlvInvSt", "ST");
            appendFcdNode(LN0DataSet, "ANSV", "GGIO", lnInst, "CfgSt", "ST");
        }
    } else if(ldInst == "ANSV" && name.contains("dsEvent")) {
        for(int i = 1; i <= auNo; i++) {
            QString lnInst = QString::number(256 * (dataSetIndex - 1) + i, 10);
            appendFcdNode(LN0DataSet, "ANSV", "GGIO", lnInst, "LimLosOv", "ST");
        }
    } else if(ldInst == "ANSV" && name.contains("dsStatistic")) {
        for(int i = 1; i <= auNo; i++) {
            QString lnInst = QString::number(51 * (dataSetIndex - 1) + i, 10);
            appendFcdaNode(LN0DataSet, "ANSV", "GGIO", lnInst, "FrmErrCnt", "stVal", "ST");
            appendFcdaNode(LN0DataSet, "ANSV", "GGIO", lnInst, "ChkErrCnt", "stVal", "ST");
            appendFcdaNode(LN0DataSet, "ANSV", "GGIO", lnInst, "LosCnt", "stVal", "ST");
            appendFcdaNode(LN0DataSet, "ANSV", "GGIO", lnInst, "FramesQty", "stVal", "ST");
            appendFcdaNode(LN0DataSet, "ANSV", "GGIO", lnInst, "BytesQty", "stVal", "ST");
        }
    }

    else if(ldInst == "ANMMS" && name.contains("dsDin")) {
        for(int i = 1; i <= auNo; i++) {
            QString lnInst = QString::number(51 * (dataSetIndex - 1) + i, 10);
            appendFcdNode(LN0DataSet, "ANMMS", "GGIO", lnInst, "ConSt", "ST");
            appendFcdNode(LN0DataSet, "ANMMS", "GGIO", lnInst, "BRCBInitSt", "ST");
            appendFcdNode(LN0DataSet, "ANMMS", "GGIO", lnInst, "EtyTmSt", "ST");
            appendFcdNode(LN0DataSet, "ANMMS", "GGIO", lnInst, "EtyTstSt", "ST");
            appendFcdNode(LN0DataSet, "ANMMS", "GGIO", lnInst, "CfgSt", "ST");
        }
    } else if(ldInst == "ANMMS" && name.contains("dsEvent")) {
        for(int i = 1; i <= auNo; i++) {
            QString lnInst = QString::number(42 * (dataSetIndex - 1) + i, 10);
            appendFcdNode(LN0DataSet, "ANMMS", "GGIO", lnInst, "SbowOp", "ST");
            appendFcdNode(LN0DataSet, "ANMMS", "GGIO", lnInst, "DirectOp", "ST");
            appendFcdNode(LN0DataSet, "ANMMS", "GGIO", lnInst, "SetSGValOp", "ST");
            appendFcdNode(LN0DataSet, "ANMMS", "GGIO", lnInst, "SetSGOp", "ST");
            appendFcdNode(LN0DataSet, "ANMMS", "GGIO", lnInst, "BRCBOvfl", "ST");
            appendFcdNode(LN0DataSet, "ANMMS", "GGIO", lnInst, "BRCBPurge", "ST");
        }
    } else if(ldInst == "ANMMS" && name.contains("dsStatistic")) {
        for(int i = 1; i <= auNo; i++) {
            QString lnInst = QString::number(25 * (dataSetIndex - 1) + i, 10);
            appendFcdaNode(LN0DataSet, "ANMMS", "GGIO", lnInst, "FrmErrCnt", "stVal", "ST");
            appendFcdaNode(LN0DataSet, "ANMMS", "GGIO", lnInst, "ChkErrCnt", "stVal", "ST");
            appendFcdaNode(LN0DataSet, "ANMMS", "GGIO", lnInst, "TcpConCnt", "stVal", "ST");
            appendFcdaNode(LN0DataSet, "ANMMS", "GGIO", lnInst, "LocTcpBrkCnt", "stVal", "ST");
            appendFcdaNode(LN0DataSet, "ANMMS", "GGIO", lnInst, "RmtTcpBrkCnt", "stVal", "ST");
            appendFcdaNode(LN0DataSet, "ANMMS", "GGIO", lnInst, "OthOpFailCnt", "stVal", "ST");
            appendFcdaNode(LN0DataSet, "ANMMS", "GGIO", lnInst, "TmoutCnt", "stVal", "ST");
            appendFcdaNode(LN0DataSet, "ANMMS", "GGIO", lnInst, "BRCBInitCnt", "stVal", "ST");
            appendFcdaNode(LN0DataSet, "ANMMS", "GGIO", lnInst, "FramesQty", "stVal", "ST");
            appendFcdaNode(LN0DataSet, "ANMMS", "GGIO", lnInst, "BytesQty", "stVal", "ST");
        }
    }

    else if(ldInst == "AN104" && name.contains("dsDin")) {
        for(int i = 1; i <= auNo; i++) {
            QString lnInst = QString::number(256 * (dataSetIndex - 1) + i, 10);
            appendFcdNode(LN0DataSet, "AN104", "GGIO", lnInst, "ConSt", "ST");
        }
    } else if(ldInst == "AN104" && name.contains("dsEvent")) {
        for(int i = 1; i <= auNo; i++) {
            QString lnInst = QString::number(85 * (dataSetIndex - 1) + i, 10);
            appendFcdNode(LN0DataSet, "AN104", "GGIO", lnInst, "SbowOp", "ST");
            appendFcdNode(LN0DataSet, "AN104", "GGIO", lnInst, "DirectOp", "ST");
            appendFcdNode(LN0DataSet, "AN104", "GGIO", lnInst, "YTOp", "ST");
        }
    } else if(ldInst == "AN104" && name.contains("dsStatistic")) {
        for(int i = 1; i <= auNo; i++) {
            QString lnInst = QString::number(25 * (dataSetIndex - 1) + i, 10);
            appendFcdaNode(LN0DataSet, "AN104", "GGIO", lnInst, "FrmErrCnt", "stVal", "ST");
            appendFcdaNode(LN0DataSet, "AN104", "GGIO", lnInst, "ChkErrCnt", "stVal", "ST");
            appendFcdaNode(LN0DataSet, "AN104", "GGIO", lnInst, "TcpConCnt", "stVal", "ST");
            appendFcdaNode(LN0DataSet, "AN104", "GGIO", lnInst, "LocTcpBrkCnt", "stVal", "ST");
            appendFcdaNode(LN0DataSet, "AN104", "GGIO", lnInst, "RmtTcpBrkCnt", "stVal", "ST");
            appendFcdaNode(LN0DataSet, "AN104", "GGIO", lnInst, "YXInvCnt", "stVal", "ST");
            appendFcdaNode(LN0DataSet, "AN104", "GGIO", lnInst, "YCInvCnt", "stVal", "ST");
            appendFcdaNode(LN0DataSet, "AN104", "GGIO", lnInst, "YCOvflCnt", "stVal", "ST");
            appendFcdaNode(LN0DataSet, "AN104", "GGIO", lnInst, "TmoutCnt", "stVal", "ST");
            appendFcdaNode(LN0DataSet, "AN104", "GGIO", lnInst, "FramesQty", "stVal", "ST");
            appendFcdaNode(LN0DataSet, "AN104", "GGIO", lnInst, "BytesQty", "stVal", "ST");
        }
    }
}

void NetaIcdWizard::appendReportControl(QDomElement &parentElement, const QString name, const QString id, const QString datSet)
{
    QDomElement Ld0LN0ReportControl = document->createElement("ReportControl");
    parentElement.appendChild(Ld0LN0ReportControl);

    QString desc = "";

    QRegExp prefix("(brcb|urcb)([\\w]*)(Din|Event|Statistic)([0-9]*)");

    if(name.contains("Warning"))
        desc = tr("告警信号");
    else if(name.contains("Din")) {
        prefix.indexIn(name);
        desc = prefix.cap(2) + tr("状态");
    }
    else if(name.contains("Event")) {
        prefix.indexIn(name);
        desc = prefix.cap(2) +  tr("事件");
    }
    else if(name.contains("Statistic")) {
        prefix.indexIn(name);
        desc = prefix.cap(2) +  tr("统计");
    }

    Ld0LN0ReportControl.setAttribute("name", name);
    Ld0LN0ReportControl.setAttribute("desc", desc);
    Ld0LN0ReportControl.setAttribute("rptID", id);
    Ld0LN0ReportControl.setAttribute("datSet", datSet);
    Ld0LN0ReportControl.setAttribute("confRev", "1");

    if(name.contains("Statistic"))
        Ld0LN0ReportControl.setAttribute("buffered", "false");
    else
        Ld0LN0ReportControl.setAttribute("buffered", "true");

    QDomElement trgOps = document->createElement("TrgOps");
    if(id.contains("ANGO") && name.contains("Statistic"))
        trgOps.setAttribute("dchg", "false");
    else
        trgOps.setAttribute("dchg", "true");

    if(name.contains("Statistic") || name.contains("Event"))
        trgOps.setAttribute("dupd", "true");

    if(id.contains("ANGO") && name.contains("Statistic"))
        trgOps.setAttribute("qchg", "false");
    else
        trgOps.setAttribute("qchg", "true");

    if(id.contains("ANGO") && name.contains("Statistic"))
        trgOps.setAttribute("period", "true");
    else
        trgOps.setAttribute("period", "false");

    QDomElement optFields = document->createElement("OptFields");
    optFields.setAttribute("seqNum", "true");
    optFields.setAttribute("timeStamp", "true");
    optFields.setAttribute("dataSet", "true");
    optFields.setAttribute("reasonCode", "true");
    QDomElement rptEnabled = document->createElement("RptEnabled");
    rptEnabled.setAttribute("max", "16");

    Ld0LN0ReportControl.appendChild(trgOps);
    Ld0LN0ReportControl.appendChild(optFields);
    Ld0LN0ReportControl.appendChild(rptEnabled);

}

void NetaIcdWizard::appendFcdNode(QDomElement &parentElement, const QString ldInst, const QString lnClass, const QString lnInst, const QString doName, const QString fc)
{
    QDomElement FCDA = document->createElement("FCDA");
    parentElement.appendChild(FCDA);

    FCDA.setAttribute("ldInst", ldInst);
    FCDA.setAttribute("prefix", "");
    FCDA.setAttribute("lnClass", lnClass);
    FCDA.setAttribute("lnInst", lnInst);
    FCDA.setAttribute("doName", doName);
    FCDA.setAttribute("fc", fc);

}

void NetaIcdWizard::appendFcdaNode(QDomElement &parentElement, const QString ldInst, const QString lnClass, const QString lnInst, const QString doName, const QString daName, const QString fc)
{
    QDomElement FCDA = document->createElement("FCDA");
    parentElement.appendChild(FCDA);

    FCDA.setAttribute("ldInst", ldInst);
    FCDA.setAttribute("prefix", "");
    FCDA.setAttribute("lnClass", lnClass);
    FCDA.setAttribute("lnInst", lnInst);
    FCDA.setAttribute("doName", doName);
    FCDA.setAttribute("daName", daName);
    FCDA.setAttribute("fc", fc);

}

void NetaIcdWizard::appendDOI(QDomElement &parentElement, const QString DOIname, const QString DOIdesc, const QString DAIname, const QString DAIVal)
{
    QDomElement doi = document->createElement("DOI");
    parentElement.appendChild(doi);

    doi.setAttribute("name", DOIname);
    doi.setAttribute("desc", DOIdesc);

    QDomElement dai = document->createElement("DAI");
    dai.setAttribute("name", DAIname);
    QDomElement val = document->createElement("Val");
    QDomText value = document->createTextNode(DAIVal);

    val.appendChild(value);
    dai.appendChild(val);
    doi.appendChild(dai);

}

void NetaIcdWizard::appendDOI(QDomElement &parentElement, const QString DOIname, const QString DOIdesc,
                              const QString DAIname1, const QString DAIVal1,
                              const QString DAIname2, const QString DAIVal2)
{
    QDomElement doi = document->createElement("DOI");
    parentElement.appendChild(doi);

    doi.setAttribute("name", DOIname);
    doi.setAttribute("desc", DOIdesc);

    QDomElement dai1 = document->createElement("DAI");
    dai1.setAttribute("name", DAIname1);
    QDomElement val1 = document->createElement("Val");
    QDomText value1 = document->createTextNode(DAIVal1);
    QDomElement dai2 = document->createElement("DAI");
    dai2.setAttribute("name", DAIname2);
    QDomElement val2 = document->createElement("Val");
    QDomText value2 = document->createTextNode(DAIVal2);

    val1.appendChild(value1);
    dai1.appendChild(val1);
    val2.appendChild(value2);
    dai2.appendChild(val2);

    doi.appendChild(dai1);
    doi.appendChild(dai2);

}

void NetaIcdWizard::appendDOI(QDomElement &parentElement, const QString DOIname, const QString DOIdesc,
                              const QString DAIname1, const QString DAIVal1,
                              const QString DAIname2, const QString DAIVal2,
                              const QString DAIname3, const QString DAIVal3,
                              const QString DAIname4, const QString DAIVal4)
{
    QDomElement doi = document->createElement("DOI");
    parentElement.appendChild(doi);

    doi.setAttribute("name", DOIname);
    doi.setAttribute("desc", DOIdesc);

    QDomElement dai1 = document->createElement("DAI");
    dai1.setAttribute("name", DAIname1);
    QDomElement val1 = document->createElement("Val");
    QDomText value1 = document->createTextNode(DAIVal1);
    QDomElement dai2 = document->createElement("DAI");
    dai2.setAttribute("name", DAIname2);
    QDomElement val2 = document->createElement("Val");
    QDomText value2 = document->createTextNode(DAIVal2);
    QDomElement dai3 = document->createElement("DAI");
    dai3.setAttribute("name", DAIname3);
    QDomElement val3 = document->createElement("Val");
    QDomText value3 = document->createTextNode(DAIVal3);
    QDomElement dai4 = document->createElement("DAI");
    dai4.setAttribute("name", DAIname4);
    QDomElement val4 = document->createElement("Val");
    QDomText value4 = document->createTextNode(DAIVal4);

    val1.appendChild(value1);
    dai1.appendChild(val1);
    val2.appendChild(value2);
    dai2.appendChild(val2);
    val3.appendChild(value3);
    dai3.appendChild(val3);
    val4.appendChild(value4);
    dai4.appendChild(val4);

    doi.appendChild(dai1);
    doi.appendChild(dai2);
    doi.appendChild(dai3);
    doi.appendChild(dai4);

}
