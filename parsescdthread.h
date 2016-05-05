#ifndef PARSESCDTHREAD_H
#define PARSESCDTHREAD_H

#include <QThread>

#include <QTreeWidgetItem>
#include <QList>
#include <QFile>
#include <QXmlStreamReader>

#include "controlBlock.h"

class ParseSCDThread : public QThread
{
    Q_OBJECT
public:
    explicit ParseSCDThread(QObject *parent = 0);
    ~ParseSCDThread();

    void setFileName(const QString newFileName);

    void explorerSCDFile(const QString fileName);

    QList<controlBlock*> getGSEItemList() {
        return gseItemList;
    }
    QList<controlBlock*> getSMVItemList() {
        return svItemList;
    }
    QList<controlBlock*> getMMSItemList() {
        return mmsItemList;
    }
    QList<controlBlock*> get104ItemList() {
        return iec104ItemList;
    }

signals:

    void parseOvered();

protected:
    virtual void run();

private:
    QString fileName;

//    QList<QTreeWidgetItem*> *gseItemList;
//    QList<QTreeWidgetItem*> *svItemList;
//    QList<QTreeWidgetItem*> *mmsItemList;
//    QList<QTreeWidgetItem*> *an104ItemList;

    QList<controlBlock*> gseItemList;
    QList<controlBlock*> svItemList;
    QList<controlBlock*> mmsItemList;
    QList<controlBlock*> iec104ItemList;

    void parseCommunication(QXmlStreamReader &xml);
    void parseSubNetwork(QXmlStreamReader &xml);
    void parseConnectedAP(QXmlStreamReader& xml);
    void parseGseSmv(QXmlStreamReader &xml, const QString iedName, const QString gseSmv);
    void parseAddress(QXmlStreamReader &xml, const QString cbName, const QString gseSmv);

    void parseIED(QXmlStreamReader &xml);

public slots:

};

#endif // PARSESCDTHREAD_H
