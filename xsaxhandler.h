#ifndef XSAXHANDLER_H
#define XSAXHANDLER_H

#include <QXmlDefaultHandler>
#include "dommodel.h"

class XSaxHandler : public QXmlDefaultHandler
{
    DomModel *xmlTree;
    DomItem *currentElement;
public:
    XSaxHandler(DomModel *regola);
    ~XSaxHandler();

    bool startElement(const QString &namespaceURI, const QString &localName,
                      const QString &qName, const QXmlAttributes &attributes);
    bool endElement(const QString &namespaceURI, const QString &localName,
                    const QString &qName);
    bool characters(const QString &str);
    bool fatalError(const QXmlParseException &exception);
    bool error(const QXmlParseException &exception);
    QString errorString() const;
};

#endif // XSAXHANDLER_H
