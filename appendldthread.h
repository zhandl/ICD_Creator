#ifndef APPENDLDTHREAD_H
#define APPENDLDTHREAD_H

#include <QThread>
#include <QDomDocument>
#include <QDomElement>
#include <QList>

#include "controlBlock.h"


class AppendLDThread : public QThread
{
    Q_OBJECT
public:
    explicit AppendLDThread(QObject *parent = 0);

    void setParentElement(const QDomElement &parentElement) { this->parentElement = parentElement; }
    void setAuNo(const int &auNo) { _auNo = auNo; }
    void setGseItemList(const QList<controlBlock*> itemList) { gseItemList = itemList; }
    void setSvItemList(const QList<controlBlock*> itemList) { svItemList = itemList; }
    void setMmsItemList(const QList<controlBlock*> itemList) { mmsItemList = itemList; }
    void setIec104ItemList(const QList<controlBlock*> itemList) { iec104ItemList = itemList; }
    void setDocument(const QDomDocument &doc) { *document = doc; }
protected:
    virtual void run();

private:
    QDomElement parentElement;
    QDomDocument *document;
    int _auNo;
    QList<controlBlock*> gseItemList;
    QList<controlBlock*> svItemList;
    QList<controlBlock*> mmsItemList;
    QList<controlBlock*> iec104ItemList;

    void appendLD(QDomElement &parentElement);

    void appendLD0(QDomElement &parentElement, int dauNo);
    void appendPLD(QDomElement &parentElement);
    void appendANGO(QDomElement &parentElement, int gocbNum);
    void appendANSV(QDomElement &parentElement, int svcbNum);
    void appendANMMS(QDomElement &parentElement, int mmsNum);
    void appendAN104(QDomElement &parentElement, int iec104Num);

    void append_LD0_LLN0(QDomElement &parentElement, const int auNo);
    void append_PLD_LLN0(QDomElement &parentElement);
    void append_ANGO_LLN0(QDomElement &parentElement, const int gcbNum);
    void append_ANSV_LLN0(QDomElement &parentElement, const int svcbNum);
    void append_ANMMS_LLN0(QDomElement &parentElement, const int mmsNum);
    void append_AN104_LLN0(QDomElement &parentElement, const int iec104Num);
    void appendLPHD(QDomElement &parentElement);
    void appendLTSM(QDomElement &parentElement);

    void append_LD0_GGIO(QDomElement &parentElement, int lnInst);
    void append_PLD_GGIO(QDomElement &parentElement, int lnInst);
    void append_ANGO_GGIO(QDomElement &parentElement, int lnInst);
    void append_ANSV_GGIO(QDomElement &parentElement, int lnInst);
    void append_ANMMS_GGIO(QDomElement &parentElement, int lnInst);
    void append_AN104_GGIO(QDomElement &parentElement, int lnInst);


    void append_LD0_DataSet(QDomElement &parentElement, const QString name, const int dataSetIndex, int auNo);
    void append_PLD_DataSet(QDomElement &parentElement, const QString name);
    void append_ANGO_DataSet(QDomElement &parentElement, const QString name, const int dataSetIndex, int itemNum);
    void append_ANSV_DataSet(QDomElement &parentElement, const QString name, const int dataSetIndex, int itemNum);
    void append_ANMMS_DataSet(QDomElement &parentElement, const QString name, const int dataSetIndex, int itemNum);
    void append_AN104_DataSet(QDomElement &parentElement, const QString name, const int dataSetIndex, int itemNum);

    void appendReportControl(QDomElement &parentElement, const QString name, const QString id, const QString datSet);
    void appendFcdNode(QDomElement &parentElment, const QString ldInst, const QString lnClass, const QString lnInst, const QString doName, const QString fc);
    void appendFcdaNode(QDomElement &parentElment, const QString ldInst, const QString lnClass, const QString lnInst, const QString doName, const QString daName, const QString fc);
    void appendDOI(QDomElement &parentElement, const QString DOIname, const QString DOIdesc,
                   const QString DAIname, const QString DAIVal
                   );
    void appendDOI(QDomElement &parentElement, const QString DOIname, const QString DOIdesc,
                   const QString DAIname1, const QString DAIVal1,
                   const QString DAname2, const QString DAIVal2
                   );
    void appendDOI(QDomElement &parentElement, const QString DOIname, const QString DOIdesc,
                   const QString DAIname1, const QString DAIVal1,
                   const QString DAIname2, const QString DAIVal2,
                   const QString DAIname3, const QString DAIVal3,
                   const QString DAIname4, const QString DAIVal4
                   );


signals:
    void appendLDOvered();
public slots:

};

#endif // APPENDLDTHREAD_H
