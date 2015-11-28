
#include "xsaxhandler.h"
#include "utils.h"

XSaxHandler::XSaxHandler(DomModel *regola)
{
    xmlTree = regola ;
    currentElement = NULL ;
}

XSaxHandler::~XSaxHandler()
{
}

bool XSaxHandler::startElement(const QString &/*namespaceURI*/, const QString &/*localName*/,
                               const QString &qName, const QXmlAttributes &/*attributes*/)
{
    //TODO Element *elem = new Element( xmlTree->getTag(qName), QString(""), xmlTree, currentElement ) ;
    DomItem *elem = new DomItem(xmlTree->addNameToPool(qName), QString(""), xmlTree, currentElement) ;
    if(NULL == currentElement) {
        xmlTree->setRootItem(elem);
    } else {
        currentElement->addChild(elem) ;
    }
    currentElement = elem ;
    return true ;
}

bool XSaxHandler::endElement(const QString &/*namespaceURI*/, const QString &/*localName*/,
                             const QString &/*qName*/)
{
    if(NULL != currentElement) {
        currentElement = currentElement->parent();
    }
    return true;
}

bool XSaxHandler::characters(const QString &str)
{
    if(NULL != currentElement) {
        currentElement->incrementSizeInfo(str.length());
    }
    return true ;
}

bool XSaxHandler::fatalError(const QXmlParseException &exception)
{
    Utils::error(QObject::tr("Parse error (2) at line %1, column %2:\n%3")
                 .arg(exception.lineNumber())
                 .arg(exception.columnNumber())
                 .arg(exception.message()));
    return false;
}

bool XSaxHandler::error(const QXmlParseException &exception)
{
    Utils::error(QObject::tr("Parse error (1) at line %1, column %2:\n%3")
                 .arg(exception.lineNumber())
                 .arg(exception.columnNumber())
                 .arg(exception.message()));
    return false;
}
QString XSaxHandler::errorString() const
{
    return QObject::tr("Generic error.");
}
