#ifndef RECODERICDWIZARD_H
#define RECODERICDWIZARD_H

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

class RecoderIcdWizard : public QWizard
{
    Q_OBJECT
public:
    RecoderIcdWizard(QWidget *parent = 0);
    void accept();

    QDomDocument *document;
    DomModel *model;

    QDomElement root;


private:
    icdHeaderPage *icdHeader_page;
    icdSubstationPage *icdSubstation_page;
    icdDataTypeTemplateNew *icdDataTypeTemplateNew_page;
    icdCommunicationPage *icdCommunication_page;
    icdIedServicesPage *icdIedServices_page;
    icdIedAccessPointPage *icdIedAccessPoint_page;


    void createDoc(QDomDocument *doc);

signals:

public slots:


};

#endif // RECODERICDWIZARD_H
