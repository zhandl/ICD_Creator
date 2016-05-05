#ifndef NETAICDWIZARD_H
#define NETAICDWIZARD_H

#include <QWizard>
#include <QDomDocument>

#include "domitem.h"
#include "dommodel.h"

#include "icdWizard/welcomepage.h"
#include "icdWizard/icdheaderpage.h"
#include "icdWizard/icdsubstationpage.h"
#include "icdWizard/icdcommunicationpage.h"
#include "icdWizard/icdiedservicespage.h"
#include "icdWizard/icdiedaccesspointpage.h"
#include "icdWizard/icddatatypetemplatenew.h"
#include "icdWizard/icdnetiedldevicepage.h"

#include <QXmlStreamWriter>

#include "appendldthread.h"

class NetaIcdWizard : public QWizard
{
    Q_OBJECT
public:
    explicit NetaIcdWizard(QWidget *parent = 0);

    QDomDocument *document;
    DomModel *model;

    QDomElement root;

    QXmlStreamWriter xml;

    void setDocument();
    void accept();

    AppendLDThread *appendLD_thread;

private:
    icdHeaderPage *icdHeader_page;
    icdSubstationPage *icdSubstation_page;
    icdDataTypeTemplateNew *icdDataTypeTemplateNew_page;
    icdCommunicationPage *icdCommunication_page;
    icdIedServicesPage *icdIedServices_page;
    icdIedAccessPointPage *icdIedAccessPoint_page;
    icdNETIedLDevicePage *icdNETIedLDevice_page;

    void createDoc(QDomDocument *doc);

    void appendHeader(QDomElement &parentElement);
    void appendSubstation(QDomElement &parentElement);
    void appendCommunication(QDomElement &parentElement);
    void appendIED(QDomElement &parentElement);

    void appendIEDServices(QDomElement &parentElement);
    void appendAccessPoint(QDomElement &parentElement);
    void appendServer(QDomElement &parentElement);
    void appendAuthentication(QDomElement &parentElement);

    void appendLD0(QDomElement &parentElement, int dauNo);
    void appendPLD(QDomElement &parentElement);
    void appendANGO(QDomElement &parentElement, int gocbNum);
    void appendANSV(QDomElement &parentElement, int svcbNum);
    void appendANMMS(QDomElement &parentElement, int mmsNum);
    void appendAN104(QDomElement &parentElement, int iec104Num);

    void appendLLN0(QDomElement &parentElement, int auNo);
    void appendLPHD(QDomElement &parentElement);
    void appendLTSM(QDomElement &parentElement);
    void appendGGIO(QDomElement &parentElement, int lnInst);


    void appendDataSet(QDomElement &parentElement, const QString name, const int dataSetIndex, int auNo);
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

public slots:

};

#endif // NETAICDWIZARD_H
