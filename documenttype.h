#ifndef DOCUMENTTYPE_H
#define DOCUMENTTYPE_H

#include <QDomDocument>

/**
  \brief XML document type
  */
class DocumentType
{
    QString _docType;
    QString _systemId;
    QString _publicId;

public:
    DocumentType();
    ~DocumentType();

    QString docType();
    void setDocType(const QString& value);
    QString systemId();
    void setSystemId(const QString& value);
    QString publicId();
    void setPublicId(const QString& value);


    bool hasDocType();

    QDomDocument createDocument();

};

#endif // DOCUMENTTYPE_H
