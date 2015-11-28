#include "documenttype.h"

#include "documenttype.h"

DocumentType::DocumentType()
{
}

DocumentType::~DocumentType()
{
}


QString DocumentType::docType()
{
    return _docType ;
}


void DocumentType::setDocType(const QString& value)
{
    _docType = value ;
}


QString DocumentType::systemId()
{
    return _systemId ;
}


void DocumentType::setSystemId(const QString& value)
{
    _systemId = value ;
}


QString DocumentType::publicId()
{
    return _publicId ;
}


void DocumentType::setPublicId(const QString& value)
{
    _publicId = value ;
}

bool DocumentType::hasDocType()
{
    if(_docType.isEmpty()) {
        return false;
    }
    return true ;
}

QDomDocument DocumentType::createDocument()
{
    if(hasDocType()) {
        QDomImplementation implementation;
        QDomDocumentType documentType = implementation.createDocumentType(docType(), publicId(), systemId());
        QDomDocument  document(documentType);
        return document;
    } else {
        QDomDocument    document;
        return document;
    }
}
