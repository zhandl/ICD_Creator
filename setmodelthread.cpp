#include "setmodelthread.h"

#include "dommodel.h"

SetModelThread::SetModelThread(QObject *parent) :
    QThread(parent)
{
    document = new QDomDocument();
    filePath = "";
}

SetModelThread::~SetModelThread()
{
    if(document != NULL)
        delete document;
}


void SetModelThread::run()
{
    model = new DomModel(*document, filePath);
    emit setModelOvered();
}

void SetModelThread::setTarget(QDomDocument &newDoc, const QString &newFileName)
{
    *document = newDoc;
    filePath = newFileName;
}
