#include "appendldthread.h"
#include <QRegExp>
#include <QMutex>

#define MAX_FCDA_NUM 256

#define LD0_DSWARNING_FCDA_NUM 10

#define ANGO_DSDIN_FCDA_NUM 4
#define ANGO_DSEVENT_FCDA_NUM 4
#define ANGO_DSSTATISTIC_FCDA_NUM 5

#define ANSV_DSDIN_FCDA_NUM 5
#define ANSV_DSEVENT_FCDA_NUM 1
#define ANSV_DSSTATISTIC_FCDA_NUM 5

#define ANMMS_DSDIN_FCDA_NUM 5
#define ANMMS_DSEVENT_FCDA_NUM 6
#define ANMMS_DSSTATISTIC_FCDA_NUM 10

#define AN104_DSDIN_FCDA_NUM 1
#define AN104_DSEVENT_FCDA_NUM 3
#define AN104_DSSTATISTIC_FCDA_NUM 11

AppendLDThread::AppendLDThread(QObject *parent) :
    QThread(parent)
{
    document = new QDomDocument();
}

void AppendLDThread::run()
{
    QMutex mutex;
    mutex.lock();
    appendLD(parentElement);

    mutex.unlock();
    emit appendLDOvered();
}

void AppendLDThread::appendLD(QDomElement &parentElement)
{
    appendLD0(parentElement, _auNo);
    appendPLD(parentElement);

    if(gseItemList.count() > 0) {
        appendANGO(parentElement, gseItemList.count());
    }

    if(svItemList.count() > 0) {
        appendANSV(parentElement, svItemList.count());
    }

    if(mmsItemList.count() > 0) {
        appendANMMS(parentElement, mmsItemList.count());
    }

    if(iec104ItemList.count() > 0) {
        appendAN104(parentElement, iec104ItemList.count());
    }
}

void AppendLDThread::appendLD0(QDomElement &parentElement, int dauNo)
{
    QDomElement LD0 = document->createElement("LDevice");
    parentElement.appendChild(LD0);

    LD0.setAttribute("inst", "LD0");
    LD0.setAttribute("desc", tr("公用LD"));

    append_LD0_LLN0(LD0, dauNo);
    appendLPHD(LD0);
    appendLTSM(LD0);
    for(int i = 1; i < dauNo; i++)
        append_LD0_GGIO(LD0, i);
}

void AppendLDThread::appendPLD(QDomElement &parentElement)
{
    QDomElement PLD = document->createElement("LDevice");
    parentElement.appendChild(PLD);

    PLD.setAttribute("inst", "PLD");
    PLD.setAttribute("desc", tr("预警LD"));

    append_PLD_LLN0(PLD);
    appendLPHD(PLD);
    append_PLD_GGIO(PLD, 1);
}

void AppendLDThread::appendANGO(QDomElement &parentElement, int gocbNum)
{
    QDomElement ANGO = document->createElement("LDevice");
    parentElement.appendChild(ANGO);

    ANGO.setAttribute("inst", "ANGO");
    ANGO.setAttribute("desc", tr("GOOSE控制块链路LD"));

    append_ANGO_LLN0(ANGO, gocbNum);
    appendLPHD(ANGO);

    for(int i = 1; i <= gocbNum; i++){
        append_ANGO_GGIO(ANGO, i);
    }
}

void AppendLDThread::appendANSV(QDomElement &parentElement, int svcbNum)
{
    QDomElement ANSV = document->createElement("LDevice");
    parentElement.appendChild(ANSV);

    ANSV.setAttribute("inst", "ANSV");
    ANSV.setAttribute("desc", tr("SV控制块链路LD"));

    append_ANSV_LLN0(ANSV, svcbNum);
    appendLPHD(ANSV);

    for(int i = 1; i <= svcbNum; i++)
        append_ANSV_GGIO(ANSV, i);
}

void AppendLDThread::appendANMMS(QDomElement &parentElement, int mmsNum)
{
    QDomElement ANMMS = document->createElement("LDevice");
    parentElement.appendChild(ANMMS);

    ANMMS.setAttribute("inst", "ANMMS");
    ANMMS.setAttribute("desc", tr("MMS链路LD"));

    append_ANMMS_LLN0(ANMMS, mmsNum);
    appendLPHD(ANMMS);

    for(int i = 1; i <= mmsNum; i++)
        append_ANMMS_GGIO(ANMMS, i);
}

void AppendLDThread::appendAN104(QDomElement &parentElement, int iec104Num)
{
    QDomElement AN104 = document->createElement("LDevice");
    parentElement.appendChild(AN104);

    AN104.setAttribute("inst", "AN104");
    AN104.setAttribute("desc", tr("IEC104链路LD"));

    append_AN104_LLN0(AN104, iec104Num);
    appendLPHD(AN104);

    for(int i = 1; i <= iec104Num; i++)
        append_AN104_GGIO(AN104, i);
}

void AppendLDThread::append_LD0_LLN0(QDomElement &parentElement, const int auNo)
{
    int dauNoPerGroup = (MAX_FCDA_NUM - 3)/LD0_DSWARNING_FCDA_NUM;

    QDomElement LN0 = document->createElement("LN0");
    parentElement.appendChild(LN0);

    LN0.setAttribute("desc", tr("General"));
    LN0.setAttribute("inst", "");
    LN0.setAttribute("lnClass", tr("LLN0"));
    LN0.setAttribute("lnType", tr("LD0/LLN0"));

    int tmpAuNo = auNo;
    int dataSetIndex = 1;

    if(auNo > dauNoPerGroup) { //Total Numbers of FCDA is auNoPerGroup*10 + 3 < 256
        while(tmpAuNo > dauNoPerGroup) {
            QString dataSetName = "dsWarning" + QString::number(dataSetIndex, 10);
            append_LD0_DataSet(LN0, dataSetName, dataSetIndex, dauNoPerGroup);
            dataSetIndex++;
            tmpAuNo -= dauNoPerGroup;
        }
        QString dataSetName = "dsWarning" + QString::number(dataSetIndex, 10);
        append_LD0_DataSet(LN0, dataSetName, dataSetIndex, tmpAuNo);
    } else {
        append_LD0_DataSet(LN0, "dsWarning", 1, auNo);
    }

    if(auNo > dauNoPerGroup) {  //Numbers of FCDA is auNo*10+3 > 256
        for(int i = 1; i <= dataSetIndex; i++) {
            QString reportControlName = "brcbdsWarning" + QString::number(i, 10);
            QString reportControlId = "LD0/LLN0$BR$brcbWarning" + QString::number(i, 10);
            QString reportControlDataSet = "dsWarning" + QString::number(i, 10);
            appendReportControl(LN0, reportControlName, reportControlId, reportControlDataSet);
        }
    } else {
        appendReportControl(LN0, "brcbWarning", "LD0/LLN0$BR$brcbWarning", "dsWarning");
    }

    appendDOI(LN0, "Mod", "Mode", "stVal", "on", "ctlModel", "status-only");
    appendDOI(LN0, "Beh", "Behaviour", "stVal", "on");
    appendDOI(LN0, "Health", "Health", "stVal", "Ok");
    appendDOI(LN0, "LEDRs", "SignalReset", "ctModel", "direct-with-normal-security", "dU", "SignalReset");

}

void AppendLDThread::append_PLD_LLN0(QDomElement &parentElement)
{
    QDomElement LN0 = document->createElement("LN0");
    parentElement.appendChild(LN0);

    LN0.setAttribute("desc", tr("General"));
    LN0.setAttribute("inst", "");
    LN0.setAttribute("lnClass", tr("LLN0"));
    LN0.setAttribute("lnType", tr("AN/LLN0"));

    append_PLD_DataSet(LN0, "dsWarning");
    appendReportControl(LN0, "brcbWarning", "PLD/LLN0$BR$brcbWarning", "dsWarning");
}

void AppendLDThread::append_ANGO_LLN0(QDomElement &parentElement, const int itemNum)
{
    int cbNoPerDsDin = MAX_FCDA_NUM/ANGO_DSDIN_FCDA_NUM;
    int cbNoPerDsEvent = MAX_FCDA_NUM/ANGO_DSEVENT_FCDA_NUM;
    int cbNoPerDsStatistic = MAX_FCDA_NUM/ANGO_DSSTATISTIC_FCDA_NUM;

    QDomElement LN0 = document->createElement("LN0");
    parentElement.appendChild(LN0);

    LN0.setAttribute("desc", tr("General"));
    LN0.setAttribute("inst", "");
    LN0.setAttribute("lnClass", tr("LLN0"));
    LN0.setAttribute("lnType", tr("AN/LLN0"));

    int tmpCbNo = itemNum;
    int dataSetIndex = 1;

    if(itemNum > cbNoPerDsDin) { //Total Numbers of FCDA is cbNoPerDsDin * 4  < 256
        while(tmpCbNo > cbNoPerDsDin) {
            QString dataSetName = "dsDin" + QString::number(dataSetIndex, 10);
            append_ANGO_DataSet(LN0, dataSetName, dataSetIndex, cbNoPerDsDin);
            dataSetIndex++;
            tmpCbNo -= cbNoPerDsDin;
        }
        QString dataSetName = "dsDin" + QString::number(dataSetIndex, 10);
        append_ANGO_DataSet(LN0, dataSetName, dataSetIndex, tmpCbNo);
    } else {
        append_ANGO_DataSet(LN0, "dsDin", 1, itemNum);
    }

    tmpCbNo = itemNum;
    dataSetIndex = 1;

    if(itemNum > cbNoPerDsEvent) { //Total Numbers of FCDA is cbNoPerDsDin * 4  < 256
        while(tmpCbNo > cbNoPerDsEvent) {
            QString dataSetName = "dsEvnet" + QString::number(dataSetIndex, 10);
            append_ANGO_DataSet(LN0, dataSetName, dataSetIndex, cbNoPerDsEvent);
            dataSetIndex++;
            tmpCbNo -= cbNoPerDsEvent;
        }
        QString dataSetName = "dsEvnet" + QString::number(dataSetIndex, 10);
        append_ANGO_DataSet(LN0, dataSetName, dataSetIndex, tmpCbNo);
    } else {
        append_ANGO_DataSet(LN0, "dsEvnet", 1, itemNum);
    }

    tmpCbNo = itemNum;
    dataSetIndex = 1;

    if(itemNum > cbNoPerDsStatistic) { //Total Numbers of FCDA is cbNoPerDsDin * 4  < 256
        while(tmpCbNo > cbNoPerDsStatistic) {
            QString dataSetName = "dsStatistic" + QString::number(dataSetIndex, 10);
            append_ANGO_DataSet(LN0, dataSetName, dataSetIndex, cbNoPerDsStatistic);
            dataSetIndex++;
            tmpCbNo -= cbNoPerDsStatistic;
        }
        QString dataSetName = "dsStatistic" + QString::number(dataSetIndex, 10);
        append_ANGO_DataSet(LN0, dataSetName, dataSetIndex, tmpCbNo);
    } else {
        append_ANGO_DataSet(LN0, "dsStatistic", 1, itemNum);
    }

    if(itemNum > cbNoPerDsDin) {
        for(int i = 1; i <= (itemNum/cbNoPerDsDin + 1); i++) {
            QString reportControlName = "brcbGOOSEDin" + QString::number(i, 10);
            QString reportControlId = "ANGO/LLN0$BR$brcbGOOSEDin" + QString::number(i, 10);
            QString reportControlDataSet = "dsDin" + QString::number(i, 10);
            appendReportControl(LN0, reportControlName, reportControlId, reportControlDataSet);
        }
    } else {
        appendReportControl(LN0, "brcbGOOSEDin", "ANGO/LLN0$BR$brcbGOOSEDin", "dsDin");
    }
    if(itemNum > cbNoPerDsEvent) {  //Numbers of FCDA is gcbNum*4 > 256
        for(int i = 1; i <= (itemNum/cbNoPerDsEvent+1); i++) {
            QString reportControlName = "brcbGOOSEEvent" + QString::number(i, 10);
            QString reportControlId = "ANGO/LLN0$BR$brcbGOOSEEvent" + QString::number(i, 10);
            QString reportControlDataSet = "dsEvent" + QString::number(i, 10);
            appendReportControl(LN0, reportControlName, reportControlId, reportControlDataSet);
        }
    } else {
        appendReportControl(LN0, "brcbGOOSEEvent", "ANGO/LLN0$BR$brcbGOOSEEvent", "dsEvent");
    }

    if(itemNum > cbNoPerDsStatistic) {  //Numbers of FCDA is gcbNum*5 > 256
        for(int i = 1; i <= (itemNum/cbNoPerDsStatistic+1); i++) {
            QString reportControlName = "urcbGOOSEStatistic" + QString::number(i, 10);
            QString reportControlId = "ANGO/LLN0$RP$urcbGOOSEStatistic" + QString::number(i, 10);
            QString reportControlDataSet = "dsStatistic" + QString::number(i, 10);
            appendReportControl(LN0, reportControlName, reportControlId, reportControlDataSet);
        }
    } else {
        appendReportControl(LN0, "urcbGOOSEStatistic", "ANGO/LLN0$RP$urcbGOOSEStatistic", "dsStatistic");
    }
    appendDOI(LN0, "Mod", "Mode", "stVal", "on", "ctModel", "status-only");
    appendDOI(LN0, "Beh", "Behaviour", "stVal", "on");
    appendDOI(LN0, "Health", "Health", "stVal", "Ok");
}

void AppendLDThread::append_ANSV_LLN0(QDomElement &parentElement, const int itemNum)
{
    int cbNoPerDsDin = MAX_FCDA_NUM/ANSV_DSDIN_FCDA_NUM;
    int cbNoPerDsEvent = MAX_FCDA_NUM/ANSV_DSEVENT_FCDA_NUM;
    int cbNoPerDsStatistic = MAX_FCDA_NUM/ANSV_DSSTATISTIC_FCDA_NUM;

    QDomElement LN0 = document->createElement("LN0");
    parentElement.appendChild(LN0);

    LN0.setAttribute("desc", tr("General"));
    LN0.setAttribute("inst", "");
    LN0.setAttribute("lnClass", tr("LLN0"));
    LN0.setAttribute("lnType", tr("AN/LLN0"));

    int tmpCbNo = itemNum;
    int dataSetIndex = 1;

    if(itemNum > cbNoPerDsDin) { //Total Numbers of FCDA is cbNoPerDsDin * 4  < 256
        while(tmpCbNo > cbNoPerDsDin) {
            QString dataSetName = "dsDin" + QString::number(dataSetIndex, 10);
            append_ANSV_DataSet(LN0, dataSetName, dataSetIndex, cbNoPerDsDin);
            dataSetIndex++;
            tmpCbNo -= cbNoPerDsDin;
        }
        QString dataSetName = "dsDin" + QString::number(dataSetIndex, 10);
        append_ANSV_DataSet(LN0, dataSetName, dataSetIndex, tmpCbNo);
    } else {
        append_ANSV_DataSet(LN0, "dsDin", 1, itemNum);
    }

    tmpCbNo = itemNum;
    dataSetIndex = 1;

    if(itemNum > cbNoPerDsEvent) { //Total Numbers of FCDA is cbNoPerDsDin * 4  < 256
        while(tmpCbNo > cbNoPerDsEvent) {
            QString dataSetName = "dsEvnet" + QString::number(dataSetIndex, 10);
            append_ANSV_DataSet(LN0, dataSetName, dataSetIndex, cbNoPerDsEvent);
            dataSetIndex++;
            tmpCbNo -= cbNoPerDsEvent;
        }
        QString dataSetName = "dsEvnet" + QString::number(dataSetIndex, 10);
        append_ANSV_DataSet(LN0, dataSetName, dataSetIndex, tmpCbNo);
    } else {
        append_ANSV_DataSet(LN0, "dsEvnet", 1, itemNum);
    }

    tmpCbNo = itemNum;
    dataSetIndex = 1;

    if(itemNum > cbNoPerDsStatistic) { //Total Numbers of FCDA is cbNoPerDsDin * 4  < 256
        while(tmpCbNo > cbNoPerDsStatistic) {
            QString dataSetName = "dsStatistic" + QString::number(dataSetIndex, 10);
            append_ANSV_DataSet(LN0, dataSetName, dataSetIndex, cbNoPerDsStatistic);
            dataSetIndex++;
            tmpCbNo -= cbNoPerDsStatistic;
        }
        QString dataSetName = "dsStatistic" + QString::number(dataSetIndex, 10);
        append_ANSV_DataSet(LN0, dataSetName, dataSetIndex, tmpCbNo);
    } else {
        append_ANSV_DataSet(LN0, "dsStatistic", 1, itemNum);
    }

    if(itemNum > cbNoPerDsDin) {
        for(int i = 1; i <= (itemNum/cbNoPerDsDin + 1); i++) {
            QString reportControlName = "brcbSVDin" + QString::number(i, 10);
            QString reportControlId = "ANSV/LLN0$BR$brcbSVDin" + QString::number(i, 10);
            QString reportControlDataSet = "dsDin" + QString::number(i, 10);
            appendReportControl(LN0, reportControlName, reportControlId, reportControlDataSet);
        }
    } else {
        appendReportControl(LN0, "brcbSVDin", "ANSV/LLN0$BR$brcbSVDin", "dsDin");
    }
    if(itemNum > cbNoPerDsEvent) {  //Numbers of FCDA is gcbNum*4 > 256
        for(int i = 1; i <= (itemNum/cbNoPerDsEvent+1); i++) {
            QString reportControlName = "brcbSVEvent" + QString::number(i, 10);
            QString reportControlId = "ANSV/LLN0$BR$brcbSVEvent" + QString::number(i, 10);
            QString reportControlDataSet = "dsEvent" + QString::number(i, 10);
            appendReportControl(LN0, reportControlName, reportControlId, reportControlDataSet);
        }
    } else {
        appendReportControl(LN0, "brcbSVEvent", "ANSV/LLN0$BR$brcbSVEvent", "dsEvent");
    }

    if(itemNum > cbNoPerDsStatistic) {  //Numbers of FCDA is gcbNum*5 > 256
        for(int i = 1; i <= (itemNum/cbNoPerDsStatistic+1); i++) {
            QString reportControlName = "urcbSVStatistic" + QString::number(i, 10);
            QString reportControlId = "ANSV/LLN0$RP$urcbSVStatistic" + QString::number(i, 10);
            QString reportControlDataSet = "dsStatistic" + QString::number(i, 10);
            appendReportControl(LN0, reportControlName, reportControlId, reportControlDataSet);
        }
    } else {
        appendReportControl(LN0, "urcbSVStatistic", "ANSV/LLN0$RP$urcbSVStatistic", "dsStatistic");
    }
    appendDOI(LN0, "Mod", "Mode", "stVal", "on", "ctModel", "status-only");
    appendDOI(LN0, "Beh", "Behaviour", "stVal", "on");
    appendDOI(LN0, "Health", "Health", "stVal", "Ok");
}

void AppendLDThread::append_ANMMS_LLN0(QDomElement &parentElement, const int itemNum)
{
    int cbNoPerDsDin = MAX_FCDA_NUM/ANMMS_DSDIN_FCDA_NUM;
    int cbNoPerDsEvent = MAX_FCDA_NUM/ANMMS_DSEVENT_FCDA_NUM;
    int cbNoPerDsStatistic = MAX_FCDA_NUM/ANMMS_DSSTATISTIC_FCDA_NUM;

    QDomElement LN0 = document->createElement("LN0");
    parentElement.appendChild(LN0);

    LN0.setAttribute("desc", tr("General"));
    LN0.setAttribute("inst", "");
    LN0.setAttribute("lnClass", tr("LLN0"));
    LN0.setAttribute("lnType", tr("AN/LLN0"));

    int tmpCbNo = itemNum;
    int dataSetIndex = 1;

    if(itemNum > cbNoPerDsDin) { //Total Numbers of FCDA is cbNoPerDsDin * 4  < 256
        while(tmpCbNo > cbNoPerDsDin) {
            QString dataSetName = "dsDin" + QString::number(dataSetIndex, 10);
            append_ANMMS_DataSet(LN0, dataSetName, dataSetIndex, cbNoPerDsDin);
            dataSetIndex++;
            tmpCbNo -= cbNoPerDsDin;
        }
        QString dataSetName = "dsDin" + QString::number(dataSetIndex, 10);
        append_ANMMS_DataSet(LN0, dataSetName, dataSetIndex, tmpCbNo);
    } else {
        append_ANMMS_DataSet(LN0, "dsDin", 1, itemNum);
    }

    tmpCbNo = itemNum;
    dataSetIndex = 1;

    if(itemNum > cbNoPerDsEvent) { //Total Numbers of FCDA is cbNoPerDsDin * 4  < 256
        while(tmpCbNo > cbNoPerDsEvent) {
            QString dataSetName = "dsEvnet" + QString::number(dataSetIndex, 10);
            append_ANMMS_DataSet(LN0, dataSetName, dataSetIndex, cbNoPerDsEvent);
            dataSetIndex++;
            tmpCbNo -= cbNoPerDsEvent;
        }
        QString dataSetName = "dsEvnet" + QString::number(dataSetIndex, 10);
        append_ANMMS_DataSet(LN0, dataSetName, dataSetIndex, tmpCbNo);
    } else {
        append_ANMMS_DataSet(LN0, "dsEvnet", 1, itemNum);
    }

    tmpCbNo = itemNum;
    dataSetIndex = 1;

    if(itemNum > cbNoPerDsStatistic) { //Total Numbers of FCDA is cbNoPerDsDin * 4  < 256
        while(tmpCbNo > cbNoPerDsStatistic) {
            QString dataSetName = "dsStatistic" + QString::number(dataSetIndex, 10);
            append_ANMMS_DataSet(LN0, dataSetName, dataSetIndex, cbNoPerDsStatistic);
            dataSetIndex++;
            tmpCbNo -= cbNoPerDsStatistic;
        }
        QString dataSetName = "dsStatistic" + QString::number(dataSetIndex, 10);
        append_ANMMS_DataSet(LN0, dataSetName, dataSetIndex, tmpCbNo);
    } else {
        append_ANMMS_DataSet(LN0, "dsStatistic", 1, itemNum);
    }

    if(itemNum > cbNoPerDsDin) {
        for(int i = 1; i <= (itemNum/cbNoPerDsDin + 1); i++) {
            QString reportControlName = "brcbMMSDin" + QString::number(i, 10);
            QString reportControlId = "ANMMS/LLN0$BR$brcbMMSDin" + QString::number(i, 10);
            QString reportControlDataSet = "dsDin" + QString::number(i, 10);
            appendReportControl(LN0, reportControlName, reportControlId, reportControlDataSet);
        }
    } else {
        appendReportControl(LN0, "brcbMMSDin", "ANMMS/LLN0$BR$brcbMMSDin", "dsDin");
    }
    if(itemNum > cbNoPerDsEvent) {  //Numbers of FCDA is gcbNum*4 > 256
        for(int i = 1; i <= (itemNum/cbNoPerDsEvent+1); i++) {
            QString reportControlName = "brcbMMSEvent" + QString::number(i, 10);
            QString reportControlId = "ANMMS/LLN0$BR$brcbMMSEvent" + QString::number(i, 10);
            QString reportControlDataSet = "dsEvent" + QString::number(i, 10);
            appendReportControl(LN0, reportControlName, reportControlId, reportControlDataSet);
        }
    } else {
        appendReportControl(LN0, "brcbMMSEvent", "ANMMS/LLN0$BR$brcbMMSEvent", "dsEvent");
    }

    if(itemNum > cbNoPerDsStatistic) {  //Numbers of FCDA is gcbNum*5 > 256
        for(int i = 1; i <= (itemNum/cbNoPerDsStatistic+1); i++) {
            QString reportControlName = "urcbMMSStatistic" + QString::number(i, 10);
            QString reportControlId = "ANMMS/LLN0$RP$urcbMMSStatistic" + QString::number(i, 10);
            QString reportControlDataSet = "dsStatistic" + QString::number(i, 10);
            appendReportControl(LN0, reportControlName, reportControlId, reportControlDataSet);
        }
    } else {
        appendReportControl(LN0, "urcbMMSStatistic", "ANMMS/LLN0$RP$urcbMMSStatistic", "dsStatistic");
    }
    appendDOI(LN0, "Mod", "Mode", "stVal", "on", "ctModel", "status-only");
    appendDOI(LN0, "Beh", "Behaviour", "stVal", "on");
    appendDOI(LN0, "Health", "Health", "stVal", "Ok");
}

void AppendLDThread::append_AN104_LLN0(QDomElement &parentElement, const int itemNum)
{
    int cbNoPerDsDin = MAX_FCDA_NUM/AN104_DSDIN_FCDA_NUM;
    int cbNoPerDsEvent = MAX_FCDA_NUM/AN104_DSEVENT_FCDA_NUM;
    int cbNoPerDsStatistic = MAX_FCDA_NUM/AN104_DSSTATISTIC_FCDA_NUM;

    QDomElement LN0 = document->createElement("LN0");
    parentElement.appendChild(LN0);

    LN0.setAttribute("desc", tr("General"));
    LN0.setAttribute("inst", "");
    LN0.setAttribute("lnClass", tr("LLN0"));
    LN0.setAttribute("lnType", tr("AN/LLN0"));

    int tmpCbNo = itemNum;
    int dataSetIndex = 1;

    if(itemNum > cbNoPerDsDin) { //Total Numbers of FCDA is cbNoPerDsDin * 4  < 256
        while(tmpCbNo > cbNoPerDsDin) {
            QString dataSetName = "dsDin" + QString::number(dataSetIndex, 10);
            append_AN104_DataSet(LN0, dataSetName, dataSetIndex, cbNoPerDsDin);
            dataSetIndex++;
            tmpCbNo -= cbNoPerDsDin;
        }
        QString dataSetName = "dsDin" + QString::number(dataSetIndex, 10);
        append_AN104_DataSet(LN0, dataSetName, dataSetIndex, tmpCbNo);
    } else {
        append_AN104_DataSet(LN0, "dsDin", 1, itemNum);
    }

    tmpCbNo = itemNum;
    dataSetIndex = 1;

    if(itemNum > cbNoPerDsEvent) { //Total Numbers of FCDA is cbNoPerDsDin * 4  < 256
        while(tmpCbNo > cbNoPerDsEvent) {
            QString dataSetName = "dsEvnet" + QString::number(dataSetIndex, 10);
            append_AN104_DataSet(LN0, dataSetName, dataSetIndex, cbNoPerDsEvent);
            dataSetIndex++;
            tmpCbNo -= cbNoPerDsEvent;
        }
        QString dataSetName = "dsEvnet" + QString::number(dataSetIndex, 10);
        append_AN104_DataSet(LN0, dataSetName, dataSetIndex, tmpCbNo);
    } else {
        append_AN104_DataSet(LN0, "dsEvnet", 1, itemNum);
    }

    tmpCbNo = itemNum;
    dataSetIndex = 1;

    if(itemNum > cbNoPerDsStatistic) { //Total Numbers of FCDA is cbNoPerDsDin * 4  < 256
        while(tmpCbNo > cbNoPerDsStatistic) {
            QString dataSetName = "dsStatistic" + QString::number(dataSetIndex, 10);
            append_AN104_DataSet(LN0, dataSetName, dataSetIndex, cbNoPerDsStatistic);
            dataSetIndex++;
            tmpCbNo -= cbNoPerDsStatistic;
        }
        QString dataSetName = "dsStatistic" + QString::number(dataSetIndex, 10);
        append_AN104_DataSet(LN0, dataSetName, dataSetIndex, tmpCbNo);
    } else {
        append_AN104_DataSet(LN0, "dsStatistic", 1, itemNum);
    }

    if(itemNum > cbNoPerDsDin) {
        for(int i = 1; i <= (itemNum/cbNoPerDsDin + 1); i++) {
            QString reportControlName = "brcb104Din" + QString::number(i, 10);
            QString reportControlId = "AN104/LLN0$BR$brcb104Din" + QString::number(i, 10);
            QString reportControlDataSet = "dsDin" + QString::number(i, 10);
            appendReportControl(LN0, reportControlName, reportControlId, reportControlDataSet);
        }
    } else {
        appendReportControl(LN0, "brcb104Din", "AN104/LLN0$BR$brcb104Din", "dsDin");
    }
    if(itemNum > cbNoPerDsEvent) {  //Numbers of FCDA is gcbNum*4 > 256
        for(int i = 1; i <= (itemNum/cbNoPerDsEvent+1); i++) {
            QString reportControlName = "brcb104Event" + QString::number(i, 10);
            QString reportControlId = "AN104/LLN0$BR$brcb104Event" + QString::number(i, 10);
            QString reportControlDataSet = "dsEvent" + QString::number(i, 10);
            appendReportControl(LN0, reportControlName, reportControlId, reportControlDataSet);
        }
    } else {
        appendReportControl(LN0, "brcb104Event", "AN104/LLN0$BR$brcb104Event", "dsEvent");
    }

    if(itemNum > cbNoPerDsStatistic) {  //Numbers of FCDA is gcbNum*5 > 256
        for(int i = 1; i <= (itemNum/cbNoPerDsStatistic+1); i++) {
            QString reportControlName = "urcb104Statistic" + QString::number(i, 10);
            QString reportControlId = "AN104/LLN0$RP$urcb104Statistic" + QString::number(i, 10);
            QString reportControlDataSet = "dsStatistic" + QString::number(i, 10);
            appendReportControl(LN0, reportControlName, reportControlId, reportControlDataSet);
        }
    } else {
        appendReportControl(LN0, "urcb104Statistic", "AN104/LLN0$RP$urcb104Statistic", "dsStatistic");
    }
    appendDOI(LN0, "Mod", "Mode", "stVal", "on", "ctModel", "status-only");
    appendDOI(LN0, "Beh", "Behaviour", "stVal", "on");
    appendDOI(LN0, "Health", "Health", "stVal", "Ok");
}

void AppendLDThread::appendLPHD(QDomElement &parentElement)
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
    } else {
        appendDOI(LPHD, "PhyHealth", "PhyHealth", "stVal", "Ok");
    }
}

void AppendLDThread::appendLTSM(QDomElement &parentElement)
{
    QDomElement LTSM = document->createElement("LN");
    parentElement.appendChild(LTSM);

    LTSM.setAttribute("desc", tr("对时自检信息"));
    LTSM.setAttribute("inst", "1");
    LTSM.setAttribute("lnClass", "LTSM");
    LTSM.setAttribute("lnType", "LD0/LTSM");

    appendDOI(LTSM, "Mod", "Mode", "stVal", "on", "ctlModel", "status-only");
    appendDOI(LTSM, "Beh", "Behaviour", "stVal", "on");
    appendDOI(LTSM, "Health", "Health", "stVal", "Ok");
    appendDOI(LTSM, "NamPlt", "NamPlt", "lnNs", "SGCC MODEL:2012");
    appendDOI(LTSM, "HostTPortAlarm", tr("对时信号状态"), "dU", tr("对时信号状态"));
    appendDOI(LTSM, "HostTSrvAlarm", tr("对时服务状态"), "dU", tr("对时服务状态"));
    appendDOI(LTSM, "HostContAlarm", tr("时间跳变侦测状态"), "dU", tr("时间跳变侦测状态"));

}

void AppendLDThread::append_LD0_GGIO(QDomElement &parentElement, const int lnInst)
{
    QDomElement GGIO = document->createElement("LN");
    parentElement.appendChild(GGIO);

    GGIO.setAttribute("inst", QString::number(lnInst, 10));
    GGIO.setAttribute("lnClass", "GGIO");
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
}

void AppendLDThread::append_PLD_GGIO(QDomElement &parentElement, const int lnInst)
{
    QDomElement GGIO = document->createElement("LN");
    parentElement.appendChild(GGIO);

    GGIO.setAttribute("inst", QString::number(lnInst, 10));
    GGIO.setAttribute("lnClass", "GGIO");

    GGIO.setAttribute("desc", tr("公共告警信息"));
    GGIO.setAttribute("lnType", "AlmLD/GGIO");
    appendDOI(GGIO, "TrafficChgAlm", tr("流量突变"), "dU", tr("流量突变"));
    appendDOI(GGIO, "TcpConAlm", tr("TCP会话异常"), "dU", tr("TCP会话异常"));
    appendDOI(GGIO, "ModelInconAlm", tr("SCD模型不一致"), "dU", tr("SCD模型不一致"));
    appendDOI(GGIO, "YCNoUdpAlm", tr("遥测不刷新"), "dU", tr("遥测不刷新"));
    appendDOI(GGIO, "YXFrqChgAlm", tr("遥信频繁变位"), "dU", tr("遥信频繁变位"));
}

void AppendLDThread::append_ANGO_GGIO(QDomElement &parentElement, const int lnInst)
{
    QDomElement GGIO = document->createElement("LN");
    parentElement.appendChild(GGIO);

    GGIO.setAttribute("inst", QString::number(lnInst, 10));
    GGIO.setAttribute("lnClass", "GGIO");

    int childIndex = lnInst - 1;
    QString gcbDesc = gseItemList.at(childIndex)->iedDesc;
    QString gcbAppID = gseItemList.at(childIndex)->APPID;
    QString gcbMac = gseItemList.at(childIndex)->MAC;
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
}

void AppendLDThread::append_ANSV_GGIO(QDomElement &parentElement, const int lnInst)
{
    QDomElement GGIO = document->createElement("LN");
    parentElement.appendChild(GGIO);

    GGIO.setAttribute("inst", QString::number(lnInst, 10));
    GGIO.setAttribute("lnClass", "GGIO");


    int childIndex = lnInst - 1;
    QString svcbDesc = svItemList.at(childIndex)->iedDesc;
    QString svcbAppID = svItemList.at(childIndex)->APPID;
    QString svcbMac = svItemList.at(childIndex)->MAC;
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

void AppendLDThread::append_ANMMS_GGIO(QDomElement &parentElement, const int lnInst)
{
    QDomElement GGIO = document->createElement("LN");
    parentElement.appendChild(GGIO);

    GGIO.setAttribute("inst", QString::number(lnInst, 10));
    GGIO.setAttribute("lnClass", "GGIO");


    int childIndex = lnInst - 1;
    QString mmsDesc = mmsItemList.at(childIndex)->iedDesc;
    QString mmsIPS = mmsItemList.at(childIndex)->APPID;
    QString mmsIPC = mmsItemList.at(childIndex)->MAC;
    QString NamPlt = mmsIPC+"@"+mmsIPS;
    GGIO.setAttribute("desc", "@"+mmsDesc+"@"+mmsIPS);
    GGIO.setAttribute("lnType", "MMS/GGIO");

    appendDOI(GGIO, "NamPlt", NamPlt, "dU", NamPlt);
    appendDOI(GGIO, "ConSt", tr("通信状态"), "dU", tr("通信状态"));
    appendDOI(GGIO, "BRCBInitSt", tr("报告控制块初始化状态"), "dU", tr("报告控制块初始化状态"));
    appendDOI(GGIO, "EtyTmSt", tr("条目时间状态"), "dU", tr("条目时间状态"));
    appendDOI(GGIO, "EtyTstSt", tr("条目测试状态"), "dU", tr("条目测试状态"));
    appendDOI(GGIO, "CfgSt", tr("配置状态"), "dU", tr("配置状态"));
    appendDOI(GGIO, "SbowOp", tr("带选择遥控操作"), "dU", tr("带选择遥控操作"));
    appendDOI(GGIO, "DirectOp", tr("直接遥控操作"), "dU", tr("直接遥控操作"));
    appendDOI(GGIO, "SetSGValOp", tr("修改定值操作"), "dU", tr("修改定值操作"));
    appendDOI(GGIO, "SetSGOp", tr("切换定值区"), "dU", tr("切换定值区"));
    appendDOI(GGIO, "BRCBOvfl", tr("缓存报告溢出"), "dU", tr("缓存报告溢出"));
    appendDOI(GGIO, "BRCBPurge", tr("缓存报告清除操作"), "dU", tr("缓存报告清除操作"));
    appendDOI(GGIO, "FrmErrCnt", tr("报文结构错误次数"), "dU", tr("报文结构错误次数"));
    appendDOI(GGIO, "ChkErrCnt", tr("规约符合性错误次数"), "dU", tr("规约符合性错误次数"));
    appendDOI(GGIO, "TcpConCnt", tr("所关联的TCP连接数"), "dU", tr("所关联的TCP连接数"));
    appendDOI(GGIO, "LocTcpBrkCnt", tr("本端TCP连接中断次数"), "dU", tr("本端TCP连接中断次数"));
    appendDOI(GGIO, "RmtTcpBrkCnt", tr("对端TCP连接中断次数"), "dU", tr("对端TCP连接中断次数"));
    appendDOI(GGIO, "OthOpFailCnt", tr("其它写操作失败次数"), "dU", tr("其它写操作失败次数"));
    appendDOI(GGIO, "TmoutCnt", tr("通信响应超时次数"), "dU", tr("通信响应超时次数"));
    appendDOI(GGIO, "BRCBInitCnt", tr("报告控制块初始化次数"), "dU", tr("报告控制块初始化次数"));
    appendDOI(GGIO, "FramesQty", tr("MMS报文帧数"), "dU", tr("MMS报文帧数"));
    appendDOI(GGIO, "BytesQty", tr("MMS报文字节数"), "dU", tr("MMS报文字节数"));
}

void AppendLDThread::append_AN104_GGIO(QDomElement &parentElement, const int lnInst)
{
    QDomElement GGIO = document->createElement("LN");
    parentElement.appendChild(GGIO);

    GGIO.setAttribute("inst", QString::number(lnInst, 10));
    GGIO.setAttribute("lnClass", "GGIO");


    int childIndex = lnInst - 1;
    QString iec104Desc = svItemList.at(childIndex)->iedDesc;
    QString iec104IPS = svItemList.at(childIndex)->APPID;
    QString iec104IPC = svItemList.at(childIndex)->MAC;
    QString NamPlt = iec104IPC+"@"+iec104IPS;
    GGIO.setAttribute("desc", "@"+iec104Desc+"@"+iec104IPS);
    GGIO.setAttribute("lnType", "AN104/GGIO");

    appendDOI(GGIO, "NamPlt", NamPlt, "dU", NamPlt);
    appendDOI(GGIO, "ConSt", tr("通信状态"), "dU", tr("通信状态"));
    appendDOI(GGIO, "SbowOp", tr("带选择遥控操作"), "dU", tr("带选择遥控操作"));
    appendDOI(GGIO, "DirectOp", tr("直接遥控操作"), "dU", tr("直接遥控操作"));
    appendDOI(GGIO, "YTOp", tr("遥调操作"), "dU", tr("遥调操作"));
    appendDOI(GGIO, "FrmErrCnt", tr("报文结构错误次数"), "dU", tr("报文结构错误次数"));
    appendDOI(GGIO, "ChkErrCnt", tr("规约符合性错误次数"), "dU", tr("规约符合性错误次数"));
    appendDOI(GGIO, "TcpConCnt", tr("所关联的TCP连接数"), "dU", tr("所关联的TCP连接数"));
    appendDOI(GGIO, "LocTcpBrkCnt", tr("本端TCP连接中断次数"), "dU", tr("本端TCP连接中断次数"));
    appendDOI(GGIO, "RmtTcpBrkCnt", tr("对端TCP连接中断次数"), "dU", tr("对端TCP连接中断次数"));
    appendDOI(GGIO, "YXInvCnt", tr("遥信数据无效次数"), "dU", tr("遥信数据无效次数"));
    appendDOI(GGIO, "YCInvCnt", tr("遥测数据无效次数"), "dU", tr("遥测数据无效次数"));
    appendDOI(GGIO, "YCOvflCnt", tr("遥测数据溢出次数"), "dU", tr("遥测数据溢出次数"));
    appendDOI(GGIO, "TmoutCnt", tr("通信响应超时次数"), "dU", tr("通信响应超时次数"));
    appendDOI(GGIO, "FramesQty", tr("MMS报文帧数"), "dU", tr("MMS报文帧数"));
    appendDOI(GGIO, "BytesQty", tr("MMS报文字节数"), "dU", tr("MMS报文字节数"));
}

void AppendLDThread::append_LD0_DataSet(QDomElement &parentElement, const QString name, const int dataSetIndex, int auNo)
{
    int dauNoPerGroup = (MAX_FCDA_NUM - 3)/LD0_DSWARNING_FCDA_NUM;

    QDomElement LN0DataSet  = document->createElement("DataSet");
    parentElement.appendChild(LN0DataSet);

    QString desc = "";

    LN0DataSet.setAttribute("name", name);
    if(name.contains("dsWarning"))
        desc = tr("告警信号");

    LN0DataSet.setAttribute("desc", desc);

    if(name.contains("dsWarning")) {
        if(dataSetIndex == 1) {
            appendFcdNode(LN0DataSet, "LD0", "LTSM", "1", "HostTPortAlarm", "ST");
            appendFcdNode(LN0DataSet, "LD0", "LTSM", "1", "HostTSrvAlarm", "ST");
            appendFcdNode(LN0DataSet, "LD0", "LTSM", "1", "HostContAlarm", "ST");
        }
        for(int i = 1; i <= auNo; i++) {
            QString lnInst = QString::number(dauNoPerGroup * (dataSetIndex - 1) + i, 10);
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
    }
}

void AppendLDThread::append_PLD_DataSet(QDomElement &parentElement, const QString name)
{
    QDomElement LN0DataSet  = document->createElement("DataSet");
    parentElement.appendChild(LN0DataSet);

    QString desc = "";
    LN0DataSet.setAttribute("name", name);
    if(name.contains("dsWarning"))
        desc = tr("告警信号");

    LN0DataSet.setAttribute("desc", desc);

    if(name.contains("dsWarning")) {
        appendFcdNode(LN0DataSet, "PLD", "GGIO", "1", "TrafficChgAlm", "ST");
        appendFcdNode(LN0DataSet, "PLD", "GGIO", "1", "TcpConAlm", "ST");
        appendFcdNode(LN0DataSet, "PLD", "GGIO", "1", "ModelInconAlm", "ST");
        appendFcdNode(LN0DataSet, "PLD", "GGIO", "1", "YCNoUdpAlm", "ST");
        appendFcdNode(LN0DataSet, "PLD", "GGIO", "1", "YXFrqChgAlm", "ST");
    }
}

void AppendLDThread::append_ANGO_DataSet(QDomElement &parentElement, const QString name, const int dataSetIndex, int itemNum)
{
    int cbNoPerDinGroup = MAX_FCDA_NUM / ANGO_DSDIN_FCDA_NUM;
    int cbNoPerEventGroup = MAX_FCDA_NUM / ANGO_DSEVENT_FCDA_NUM;
    int cbNoPerStatisticGroup = MAX_FCDA_NUM / ANGO_DSSTATISTIC_FCDA_NUM;

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

    if(name.contains("dsDin")) {
        for(int i = 1; i <= itemNum; i++) {
            QString lnInst = QString::number(cbNoPerDinGroup * (dataSetIndex - 1) + i, 10);
            appendFcdNode(LN0DataSet, "ANGO", "GGIO", lnInst, "ConSt", "ST");
            appendFcdNode(LN0DataSet, "ANGO", "GGIO", lnInst, "EtyTmSt", "ST");
            appendFcdNode(LN0DataSet, "ANGO", "GGIO", lnInst, "TestSt", "ST");
            appendFcdNode(LN0DataSet, "ANGO", "GGIO", lnInst, "CfgSt", "ST");
        }
    } else if(name.contains("dsEvent")) {
        for(int i = 1; i <= itemNum; i++) {
            QString lnInst = QString::number(cbNoPerEventGroup * (dataSetIndex - 1) + i, 10);
            appendFcdNode(LN0DataSet, "ANGO", "GGIO", lnInst, "Reset", "ST");
            appendFcdNode(LN0DataSet, "ANGO", "GGIO", lnInst, "StFakeChg", "ST");
            appendFcdNode(LN0DataSet, "ANGO", "GGIO", lnInst, "StAbnChg", "ST");
            appendFcdNode(LN0DataSet, "ANGO", "GGIO", lnInst, "Tmout", "ST");
        }
    } else if(name.contains("dsStatistic")) {
        for(int i = 1; i <= itemNum; i++) {
            QString lnInst = QString::number(cbNoPerStatisticGroup * (dataSetIndex - 1) + i, 10);
            appendFcdaNode(LN0DataSet, "ANGO", "GGIO", lnInst, "FrmErrCnt", "stVal", "ST");
            appendFcdaNode(LN0DataSet, "ANGO", "GGIO", lnInst, "ChkErrCnt", "stVal", "ST");
            appendFcdaNode(LN0DataSet, "ANGO", "GGIO", lnInst, "FrmSeqAbnCnt", "stVal", "ST");
            appendFcdaNode(LN0DataSet, "ANGO", "GGIO", lnInst, "FramesQty", "stVal", "ST");
            appendFcdaNode(LN0DataSet, "ANGO", "GGIO", lnInst, "BytesQty", "stVal", "ST");
        }
    }
}

void AppendLDThread::append_ANSV_DataSet(QDomElement &parentElement, const QString name, const int dataSetIndex, int itemNum)
{
    int cbNoPerDinGroup = MAX_FCDA_NUM / ANSV_DSDIN_FCDA_NUM;
    int cbNoPerEventGroup = MAX_FCDA_NUM / ANSV_DSEVENT_FCDA_NUM;
    int cbNoPerStatisticGroup = MAX_FCDA_NUM / ANSV_DSSTATISTIC_FCDA_NUM;

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

    if(name.contains("dsDin")) {
        for(int i = 1; i <= itemNum; i++) {
            QString lnInst = QString::number(cbNoPerDinGroup * (dataSetIndex - 1) + i, 10);
            appendFcdNode(LN0DataSet, "ANSV", "GGIO", lnInst, "ConSt", "ST");
            appendFcdNode(LN0DataSet, "ANSV", "GGIO", lnInst, "SynSt", "ST");
            appendFcdNode(LN0DataSet, "ANSV", "GGIO", lnInst, "TestSt", "ST");
            appendFcdNode(LN0DataSet, "ANSV", "GGIO", lnInst, "VlvInvSt", "ST");
            appendFcdNode(LN0DataSet, "ANSV", "GGIO", lnInst, "CfgSt", "ST");
        }
    } else if(name.contains("dsEvent")) {
        for(int i = 1; i <= itemNum; i++) {
            QString lnInst = QString::number(cbNoPerEventGroup * (dataSetIndex - 1) + i, 10);
            appendFcdNode(LN0DataSet, "ANSV", "GGIO", lnInst, "LimLosOv", "ST");
        }
    } else if(name.contains("dsStatistic")) {
        for(int i = 1; i <= itemNum; i++) {
            QString lnInst = QString::number(cbNoPerStatisticGroup * (dataSetIndex - 1) + i, 10);
            appendFcdaNode(LN0DataSet, "ANSV", "GGIO", lnInst, "FrmErrCnt", "stVal", "ST");
            appendFcdaNode(LN0DataSet, "ANSV", "GGIO", lnInst, "ChkErrCnt", "stVal", "ST");
            appendFcdaNode(LN0DataSet, "ANSV", "GGIO", lnInst, "LosCnt", "stVal", "ST");
            appendFcdaNode(LN0DataSet, "ANSV", "GGIO", lnInst, "FramesQty", "stVal", "ST");
            appendFcdaNode(LN0DataSet, "ANSV", "GGIO", lnInst, "BytesQty", "stVal", "ST");
        }
    }
}

void AppendLDThread::append_ANMMS_DataSet(QDomElement &parentElement, const QString name, const int dataSetIndex, int itemNum)
{
    int cbNoPerDinGroup = MAX_FCDA_NUM / ANMMS_DSDIN_FCDA_NUM;
    int cbNoPerEventGroup = MAX_FCDA_NUM / ANMMS_DSEVENT_FCDA_NUM;
    int cbNoPerStatisticGroup = MAX_FCDA_NUM / ANMMS_DSSTATISTIC_FCDA_NUM;

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

    if(name.contains("dsDin")) {
        for(int i = 1; i <= itemNum; i++) {
            QString lnInst = QString::number(cbNoPerDinGroup * (dataSetIndex - 1) + i, 10);
            appendFcdNode(LN0DataSet, "ANMMS", "GGIO", lnInst, "ConSt", "ST");
            appendFcdNode(LN0DataSet, "ANMMS", "GGIO", lnInst, "BRCBInitSt", "ST");
            appendFcdNode(LN0DataSet, "ANMMS", "GGIO", lnInst, "EtyTmSt", "ST");
            appendFcdNode(LN0DataSet, "ANMMS", "GGIO", lnInst, "EtyTstSt", "ST");
            appendFcdNode(LN0DataSet, "ANMMS", "GGIO", lnInst, "CfgSt", "ST");
        }
    } else if(name.contains("dsEvent")) {
        for(int i = 1; i <= itemNum; i++) {
            QString lnInst = QString::number(cbNoPerEventGroup * (dataSetIndex - 1) + i, 10);
            appendFcdNode(LN0DataSet, "ANMMS", "GGIO", lnInst, "SbowOp", "ST");
            appendFcdNode(LN0DataSet, "ANMMS", "GGIO", lnInst, "DirectOp", "ST");
            appendFcdNode(LN0DataSet, "ANMMS", "GGIO", lnInst, "SetSGValOp", "ST");
            appendFcdNode(LN0DataSet, "ANMMS", "GGIO", lnInst, "SetSGOp", "ST");
            appendFcdNode(LN0DataSet, "ANMMS", "GGIO", lnInst, "BRCBOvfl", "ST");
            appendFcdNode(LN0DataSet, "ANMMS", "GGIO", lnInst, "BRCBPurge", "ST");
        }
    } else if(name.contains("dsStatistic")) {
        for(int i = 1; i <= itemNum; i++) {
            QString lnInst = QString::number(cbNoPerStatisticGroup * (dataSetIndex - 1) + i, 10);
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
}

void AppendLDThread::append_AN104_DataSet(QDomElement &parentElement, const QString name, const int dataSetIndex, int itemNum)
{
    int cbNoPerDinGroup = MAX_FCDA_NUM / AN104_DSDIN_FCDA_NUM;
    int cbNoPerEventGroup = MAX_FCDA_NUM / AN104_DSEVENT_FCDA_NUM;
    int cbNoPerStatisticGroup = MAX_FCDA_NUM / AN104_DSSTATISTIC_FCDA_NUM;

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

    if(name.contains("dsDin")) {
        for(int i = 1; i <= itemNum; i++) {
            QString lnInst = QString::number(cbNoPerDinGroup * (dataSetIndex - 1) + i, 10);
            appendFcdNode(LN0DataSet, "AN104", "GGIO", lnInst, "ConSt", "ST");
        }
    } else if(name.contains("dsEvent")) {
        for(int i = 1; i <= itemNum; i++) {
            QString lnInst = QString::number(cbNoPerEventGroup * (dataSetIndex - 1) + i, 10);
            appendFcdNode(LN0DataSet, "AN104", "GGIO", lnInst, "SbowOp", "ST");
            appendFcdNode(LN0DataSet, "AN104", "GGIO", lnInst, "DirectOp", "ST");
            appendFcdNode(LN0DataSet, "AN104", "GGIO", lnInst, "YTOp", "ST");
        }
    } else if(name.contains("dsStatistic")) {
        for(int i = 1; i <= itemNum; i++) {
            QString lnInst = QString::number(cbNoPerStatisticGroup * (dataSetIndex - 1) + i, 10);
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

void AppendLDThread::appendReportControl(QDomElement &parentElement, const QString name, const QString id, const QString datSet)
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

void AppendLDThread::appendFcdNode(QDomElement &parentElement, const QString ldInst, const QString lnClass, const QString lnInst, const QString doName, const QString fc)
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

void AppendLDThread::appendFcdaNode(QDomElement &parentElement, const QString ldInst, const QString lnClass, const QString lnInst, const QString doName, const QString daName, const QString fc)
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

void AppendLDThread::appendDOI(QDomElement &parentElement, const QString DOIname, const QString DOIdesc, const QString DAIname, const QString DAIVal)
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

void AppendLDThread::appendDOI(QDomElement &parentElement, const QString DOIname, const QString DOIdesc,
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

void AppendLDThread::appendDOI(QDomElement &parentElement, const QString DOIname, const QString DOIdesc,
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
