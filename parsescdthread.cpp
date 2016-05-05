#include "parsescdthread.h"

ParseSCDThread::ParseSCDThread(QObject *parent) :
    QThread(parent)
{
    fileName = "";
}

ParseSCDThread::~ParseSCDThread()
{
}

void ParseSCDThread::run()
{
    explorerSCDFile(fileName);
}

void ParseSCDThread::explorerSCDFile(const QString fileName)
{
    if(fileName.isEmpty())
        return;

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
        return;


    QXmlStreamReader xml(&file);
    xml.setNamespaceProcessing(false);

    xml.readNextStartElement();
    if(xml.name() != "SCL")
        return;
    while(xml.readNextStartElement()) {
        if(xml.name() == "Communication")
            parseCommunication(xml);
        else if(xml.name() == "IED")
            parseIED(xml);
        else if(xml.name() == "DataTypeTemplates")
            break;
        else
            xml.skipCurrentElement();

    }

    xml.clear();
    emit parseOvered();

}

void ParseSCDThread::parseCommunication(QXmlStreamReader &xml)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "Communication");

    while(xml.readNextStartElement()) {
        if(xml.name() == "SubNetwork")
            parseSubNetwork(xml);
        else
            xml.skipCurrentElement();
    }

}

void ParseSCDThread::parseSubNetwork(QXmlStreamReader &xml)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "SubNetwork");

    while(xml.readNextStartElement()) {
        if(xml.name() == "ConnectedAP")
            parseConnectedAP(xml);
        else
            xml.skipCurrentElement();
    }
}

void ParseSCDThread::parseConnectedAP(QXmlStreamReader& xml)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "ConnectedAP");

    QString iedName = xml.attributes().value("iedName").toString();
    while(xml.readNextStartElement()) {//!xml.atEnd()) {

        QString gseSmv = xml.name().toString();
        if(gseSmv == "GSE" || gseSmv == "SMV")
            parseGseSmv(xml, iedName, gseSmv);
        else
            xml.skipCurrentElement();
    }

}

void ParseSCDThread::parseGseSmv(QXmlStreamReader &xml, const QString iedName, const QString gseSmv)
{
    Q_ASSERT(xml.isStartElement() && (xml.name()=="GSE" || (xml.name()=="SMV")));

    QString cbName = iedName + "/" + xml.attributes().value("cbName").toString();
    QString ldInst = xml.attributes().value("ldInst").toString();

    while(xml.readNextStartElement()) {
        if(xml.name() == "Address")
            parseAddress(xml, cbName, gseSmv);
        else
            xml.skipCurrentElement();
    }
}

void ParseSCDThread::parseAddress(QXmlStreamReader &xml, const QString cbName, const QString gseSmv)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "Address");

    QString macAddress = "", appID = "";
    while(xml.readNextStartElement()) {
        if(xml.attributes().value("type").toString() == "MAC-Address")
            macAddress = xml.readElementText();
        else if(xml.attributes().value("type").toString() == "APPID")
            appID = xml.readElementText();
        else
            xml.skipCurrentElement();
    }

    controlBlock *newCB = new controlBlock;
    newCB->iedName = cbName.split("/").at(0);
    newCB->cbName = cbName.split("/").at(1);
    newCB->APPID = appID;
    newCB->MAC = macAddress;
    if(gseSmv == "GSE")
        gseItemList.append(newCB);
    else if(gseSmv == "SMV")
        svItemList.append(newCB);

//    QTreeWidgetItem *newItem = new QTreeWidgetItem(QStringList()<<cbName<<macAddress<<appID);
//    if(gseSmv == "GSE")
//        gseItemList->append(newItem);
//    else if(gseSmv == "SMV")
//        svItemList->append(newItem);

}

void ParseSCDThread::parseIED(QXmlStreamReader &xml)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "IED");

    QString iedName = xml.attributes().value("name").toString();
    QString iedDesc = xml.attributes().value("desc").toString();

    while(xml.readNextStartElement())
        xml.skipCurrentElement();

    QListIterator<controlBlock*> gseItem(gseItemList);
    while(gseItem.hasNext()) {
        controlBlock *item = gseItem.next();
        if(item->iedName == iedName){
            item->iedDesc = iedDesc;
        }
    }
    QListIterator<controlBlock*> svItem(svItemList);
    while(svItem.hasNext()) {
        controlBlock *item = svItem.next();
        if(item->iedName == iedName){
            item->iedDesc = iedDesc;
        }
    }

}

void ParseSCDThread::setFileName(const QString newFileName)
{
    fileName = newFileName;
}

