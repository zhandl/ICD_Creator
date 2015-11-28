/**************************************************************************
 *  This file is part of QXmlEdit                                         *
 *  Copyright (C) 2011 by Luca Bellonda and individual contributors       *
 *    as indicated in the AUTHORS file                                    *
 *  lbellonda _at_ gmail.com                                              *
 *                                                                        *
 * This library is free software; you can redistribute it and/or          *
 * modify it under the terms of the GNU Library General Public            *
 * License as published by the Free Software Foundation; either           *
 * version 2 of the License, or (at your option) any later version.       *
 *                                                                        *
 * This library is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU      *
 * Library General Public License for more details.                       *
 *                                                                        *
 * You should have received a copy of the GNU Library General Public      *
 * License along with this library; if not, write to the                  *
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,       *
 * Boston, MA  02110-1301  USA                                            *
 **************************************************************************/

#include "xsdeditor/xschema.h"
#include <QClipboard>
#include <QApplication>
#include <QFile>
#include "utils.h"
#include "xsdeditor/XSchemaIOContants.h"

QString XSDSchema::_xsdURI("http://www.w3.org/2001/XMLSchema") ;

XSDSchema::XSDSchema() : XSchemaObject(NULL, this)
{
    _attributeFormDefault = EQ_MISSING ;
    _elementFormDefault = EQ_MISSING ;
}

XSDSchema::~XSDSchema()
{
    reset();
}

void XSDSchema::reset()
{
    XSchemaObject::reset();
    foreach(XSDSchema * schema, _includedSchemas.values()) {
        delete schema ;
    }
    _includedSchemas.clear();

    foreach(XSDSchema * schema, _importedSchemas) {
        delete schema ;
    }
    _importedSchemas.clear();

    //emit resetAction(); TODO
}

XSchemaElement* XSDSchema::addElement()
{
    return realAddElement();
}

XSchemaAttribute *XSDSchema::addAttribute()
{
    return realAddAttribute();
}

bool XSDSchema::saveToClipboard()
{
    QClipboard *clipboard = QApplication::clipboard();
    QString stringText = getAsString();
    clipboard->setText(stringText);
    return true;
}

QString XSDSchema::getAsString()
{
    QDomDocument    document;
    if(!generateDom(document)) {
        XsdError(tr("Unable to convert schema document to string"));
        return "";
    }
    return document.toString(4);
}

QString XSDSchema::qName(const QString &name)
{
    return _namespacePrefix + ":" + name ;
}

void XSDSchema::getChildrenByType(SchemaChildOutput &/*outVect*/)
{
    /*TODO
       foreach( XSchemaObject* child, _children ) {
           switch( child->getType() ) {
           case SchemaInclude: outVect.includes.append(child); break;
           case SchemaImport: outVect.imports.append(child); break;
           case SchemaRedefine: outVect.redefines.append(child); break;
           case SchemaAnnotation: outVect.annotations.append(child); break;
           default:outVect.realChildren.append(child); break;

           }
       }*/
}

QDomElement XSDSchema::createElementWithNamespace(QDomDocument &document, const QString &tagName)
{
    //TODO: broken namespace support????
    if(!xsdURI().isEmpty()) {
        return document.createElement(qName(tagName));
        //return document.createElementNS( xsdURI(), tagName );
    } else {
        return document.createElement(tagName);
    }
}

QString XSDSchema::xsdNS()
{
    return xsdURI() ;
}

bool XSDSchema::existsNamespace(const QString &namespaceToSearch)
{
    if(namespaceToSearch.isEmpty()) {
        return false;
    }
    if(_namespacePrefix == namespaceToSearch) {
        return false;
    }
    return _namespaces.contains(namespaceToSearch);
}

bool XSDSchema::generateDom(QDomDocument &document, QDomNode & /*parent*/)
{
    return generateDom(document);
}

bool XSDSchema::isElementFormQualified()
{
    if((EQ_UNQUALIFIED == _elementFormDefault) || (EQ_MISSING == _elementFormDefault)) {
        return false ;
    }
    return true ;
}

bool XSDSchema::isAttributeFormQualified()
{
    if((EQ_UNQUALIFIED == _attributeFormDefault) || (EQ_MISSING == _attributeFormDefault)) {
        return false ;
    }
    return true ;
}

bool XSDSchema::generateDom(QDomDocument &document)
{
    QDomElement node = createElementWithNamespace(document, IO_XSD_SCHEMA);
    if(_attributeFormDefault != EQ_MISSING) {
        node.setAttribute(IO_SCHEMA_ATTR_AFORMDEFAULT, (EQ_UNQUALIFIED == _attributeFormDefault) ? IO_SCHEMA_UNQUALIFIED : IO_SCHEMA_QUALIFIED);
    }
    if(_elementFormDefault != EQ_MISSING) {
        node.setAttribute(IO_SCHEMA_ATTR_EFORMDEFAULT, (EQ_UNQUALIFIED == _elementFormDefault) ? IO_SCHEMA_UNQUALIFIED : IO_SCHEMA_QUALIFIED);
    }
    addAttrNotEmpty(node, IO_SCHEMA_ATTR_TARGETNAMESPACE, _targetNamespace);
    addAttrNotEmpty(node, IO_SCHEMA_ATTR_ID, _id);
    addAttrNotEmpty(node, IO_SCHEMA_ATTR_VERSION, _version);
    /*if( !_targetNamespace.isEmpty() ) {
        node.setAttribute( IO_SCHEMA_ATTR_TARGETNAMESPACE, _targetNamespace);
    }*/
    if(!generateInnerDom(document, node)) {
        return false;
    }
    QString blockDefaultVal = finalListToString(_blockDefault);
    addAttrNotEmpty(node, IO_SCHEMA_ATTR_BLOCKDEFAULT, blockDefaultVal);
    QString finalDefaultVal = finalListToString(_finalDefault);
    addAttrNotEmpty(node, IO_SCHEMA_ATTR_FINALDEFAULT, finalDefaultVal);
    addAttrNotEmpty(node, XML_LANGUAGE, _language);
    //TODO xmlns

    addOtherAttributesToDom(node);

    const QString nsPrefix(XML_NS_PREFIX ":");
    foreach(QString aNameSpace, _namespaces.keys()) {
        addAttrNotEmpty(node, nsPrefix + aNameSpace, _namespaces[aNameSpace]);
    }

    SchemaChildOutput categories;
    getChildrenByType(categories);
    // include
    /*
    for( XSchemaObject *includeChild, categories.includes ) {
        includeChild->generateInnerDom( document, node );
    }
    for( XSchemaObject *importChild, categories.includes ){
        importChild->generateInnerDom( document, node );
    }
    generateIncludes(QList<XSchemaObject*> includes;
        QList<XSchemaObject*> imports;
        QList<XSchemaObject*> redefines;
        QList<XSchemaObject*> annotations;*/
    document.appendChild(node);
    return true ;
}

void XSDSchema::addNamespace(QDomAttr &attr)
{
    //TODO: check if same namespace.
    //TODO: not my namespace, pls
    QString name = attr.name();
    int index = name.indexOf(':');
    if(index <= 0) {
        XsdError("TODO");
    }
    QString nsPrefix = name.mid(index + 1);
    _namespaces.insert(nsPrefix, attr.value());
}

QString XSDSchema::namespacePrefix()
{
    return _namespacePrefix ;
}

XSDSchema* XSDSchema::schema()
{
    return this ;
}

//------------------------ I/O handling ------------------------------------------------------------------------------


bool XSDSchema::scanSchema(const QDomElement &schema)
{
    if(!isValidSchema(schema)) {
        return false ;
    }
    _namespacePrefix = schema.prefix() ;

    _attributeFormDefault = EQ_MISSING ;
    _elementFormDefault = EQ_MISSING ;

    QDomNamedNodeMap attributes = schema.attributes();
    int numAttrs = attributes.length();
    for(int i = 0 ; i < numAttrs ; i++) {
        QDomNode node = attributes.item(i);
        QDomAttr attr = node.toAttr();
        QString name = node.nodeName();
        QString attrName = attr.name();
        if(name == IO_SCHEMA_ATTR_AFORMDEFAULT) {
            if(attr.nodeValue() == IO_SCHEMA_QUALIFIED) {
                _attributeFormDefault = EQ_QUALIFIED ;
            }
        } else if(name == IO_SCHEMA_ATTR_EFORMDEFAULT) {
            if(attr.nodeValue() == IO_SCHEMA_QUALIFIED) {
                _elementFormDefault = EQ_QUALIFIED ;
            }
        } else if(name == IO_SCHEMA_ATTR_TARGETNAMESPACE) {
            _targetNamespace = attr.nodeValue() ;
        } else if(name == IO_SCHEMA_ATTR_ID) {
            _id = attr.value();
        } else if(name == IO_SCHEMA_ATTR_VERSION) {
            _version = attr.value();
        } else if(attr.prefix() == XML_NS_PREFIX) {
            addNamespace(attr);
        } else if(attrName == IO_SCHEMA_ATTR_BLOCKDEFAULT) {
            _blockDefault = decodeFinalListToString(attr.value());
        } else if(attrName == IO_SCHEMA_ATTR_FINALDEFAULT) {
            _finalDefault = decodeFinalListToString(attr.value());
        } else if((attr.localName() == IO_XML_LANGUAGE) && (attr.prefix() == XML_PREFIX)) {
            _language = attr.value();
        } else {
            if(!readOtherAttributes(attr)) {
                raiseError(this, attr, false);
            }
        }
    } // for

    //TODO QList <EFinalType> _blockDefault;
    //TODO QList <EFinalType> _finalDefault;
    //TODO xmlns
    //TODO others attributes
    //TODO: comments
    int nodi = schema.childNodes().count();
    for(int i = 0 ; i < nodi ; i ++) {
        QDomNode childNode = schema.childNodes().item(i) ;
        if(childNode.isElement()) {
            QDomElement element = childNode.toElement();
            QString name = element.localName();

            if(element.prefix() == _namespacePrefix) {
                if(name == IO_XSD_TAGINCLUDE) {
                    readHandleObject(element, new XSchemaInclude(this, this));
                } else if(name == IO_XSD_TAGIMPORT) {
                    readHandleObject(element, new XSchemaImport(this, this));
                } else if(name == IO_XSD_TAGREDEFINE) {
                    readHandleObject(element, new XSchemaRedefine(this, this));
                } else if(name == IO_XSD_TAGGROUP) {
                    readHandleObject(element, new XSchemaGroup(this, this));
                } else if(name == IO_XSD_TAGATTRIBUTEGROUP) {
                    readHandleObject(element, new XSchemaAttributeGroup(this, this));
                } else if((name == IO_XSD_TAGELEMENT)
                          || (name == IO_XSD_COMPLEXTYPE)
                          || (name == IO_XSD_SIMPLETYPE)) {
                    readHandleObject(element, new XSchemaElement(this, this));
                } else if(name == IO_XSD_TAGATTRIBUTE) {
                    readHandleObject(element, new XSchemaAttribute(this, this));
                } else if(name == IO_XSD_TAGNOTATION) {
                    readHandleObject(element, new XSchemaNotation(this, this));
                } else if(name == IO_XSD_ANNOTATION) {
                    readHandleObject(element, new XSchemaAnnotation(this, this));
                } else {
                    raiseError(this, element, true);
                }
            } else {
                raiseError(this, element, true);
            }
        }
    }
    regenerateInternalLists();
    return true;
}

bool XSDSchema::scanSchemaNS(const QDomElement &schema)
{
    // TODO questo supporto e molto deficitario, cambiare, al limite leggere DOPO aver individuato il proprio namespace.
    if(! schema.nodeName().endsWith(IO_XSD_SCHEMA)) {
        return false ;
    }
    const QString nsAttrPrefix = QString(XML_NS_PREFIX ":");
    QDomNamedNodeMap attributes = schema.attributes();
    int numAttrs = attributes.length();
    for(int i = 0 ; i < numAttrs ; i++) {
        QDomNode node = attributes.item(i);
        QDomAttr attr = node.toAttr();
        QString attrName = attr.name();
        if(attrName.startsWith(nsAttrPrefix)) {
            addNamespace(attr);
        }
    } // for

    return true;
}

bool XSDSchema::getNSFromFile(const QString &filePath)
{
    bool isOk = false;
    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly)) {
        // Kludge to get namespaces
        QDomDocument documentNS;
        if(documentNS.setContent(&file, false)) {
            int nodes = documentNS.childNodes().count();
            for(int i = 0 ; i < nodes ; i ++) {
                isOk = true ;
                QDomNode childNode = documentNS.childNodes().item(i) ;
                if(childNode.isElement()) {
                    if(!scanSchemaNS(childNode.toElement())) {
                        isOk = false;
                    }
                }
            }
        }

        if(!isOk) {
            Utils::error(tr("Unable to parse XML"));
        }
        file.close();
    } else {
        Utils::error(QString(tr("Unable to load schema file.\n Error code is '%1'")).arg(file.error()));
    }
    return isOk ;
}

bool XSDSchema::read(const QString &filePath)
{
    bool isOk = false;
    reset(); // start from a known base
    // Kludge to get namespaces
    if(!getNSFromFile(filePath)) {
        Utils::error(QString(tr("Unable to examine schema file.")));
        return false;
    }
    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly)) {

        isOk = readFromIoDevice(&file);
        /***************************************************************************
                QDomDocument document;
                if(document.setContent(&file, true)) {
                    ///QDomNodeList schemas = document.elementsByTagNameNS ( xsdURI, IO_SCHEMA_NAME );
                    int nodes = document.childNodes().count();
                    for(int i = 0 ; i < nodes ; i ++) {
                        isOk = true ;
                        QDomNode childNode = document.childNodes().item(i) ;
                        if(childNode.isElement()) {
                            if(!scanSchema(childNode.toElement())) {
                                isOk = false;
                            }
                        }
                    }
                }
                if(!isOk) {
                    Utils::error(tr("Unable to parse XML"));
                }
        ***************************************************************************/
        file.close();

    } else {
        Utils::error(QString(tr("Unable to load schema file.\n Error code is '%1'")).arg(file.error()));
    }
    return isOk ;
}

bool XSDSchema::readFromIoDevice(QIODevice *file)
{
    bool isOk = false;
    QDomDocument document;
    if(document.setContent(file, true)) {
        int nodes = document.childNodes().count();
        for(int i = 0 ; i < nodes ; i ++) {
            isOk = true ;
            QDomNode childNode = document.childNodes().item(i) ;
            if(childNode.isElement()) {
                if(!scanSchema(childNode.toElement())) {
                    isOk = false;
                }
            }
        }
    }
    if(!isOk) {
        Utils::error(tr("Unable to parse XML"));
    }
    return isOk ;
}
/* TODO: delete
bool XSDSchema::readFromURL(const QString &inputUrl, QNetworkAccessManager *networkAccessManager)
{
    connect(networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onNetworkAccessFinished(QNetworkReply*)));
    QUrl url = QUrl::fromUserInput(inputUrl);
    // trace( QString("schema loading url: %1" ).arg(url.toString()) );
    networkAccessManager->get(QNetworkRequest(url));
    return true ;
}

void XSDSchema::onNetworkAccessFinished(QNetworkReply* reply)
{
    bool isError = true ;
    if(NULL != _networkAccessManager) {
        disconnect(_networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onNetworkAccessFinished(QNetworkReply*)));
        _networkAccessManager = NULL ;
    }
    // trace( QString("schema loading error: %1" ).arg(reply->error() );
    if(reply->error() == QNetworkReply::NoError) {
        if(readFromIoDevice(reply)) {
            isError = false ;
        }
        reply->close();
    }
    if(isError) {
        Utils::error(tr("Failed to load XML Schema, error is:'%1'").arg(reply->errorString()));
    }
    reply->deleteLater();
    emit loadComplete(this, isError);
}
*/
bool XSDSchema::readFromString(const QString &inputText)
{
    return readFromInputString(inputText);
}

bool XSDSchema::readFromClipboard()
{
    QClipboard *clipboard = QApplication::clipboard();
    if(NULL == clipboard) {
        Utils::error(tr("No clipboard available."));
        return false;
    }
    QString inputText = clipboard->text();
    return readFromInputString(inputText);
}


bool XSDSchema::readFromInputString(const QString &inputText)
{
    bool isOk = false;
    reset(); // start from a known base
    QDomDocument documentNS;
    // Kludge to get namespaces
    if(documentNS.setContent(inputText, false)) {
        int nodes = documentNS.childNodes().count();
        for(int i = 0 ; i < nodes ; i ++) {
            isOk = true ;
            QDomNode childNode = documentNS.childNodes().item(i) ;
            if(childNode.isElement()) {
                if(!scanSchemaNS(childNode.toElement())) {
                    isOk = false;
                }
            }
        }
    }
    QDomDocument document;
    if(document.setContent(inputText, true)) {
        int nodes = document.childNodes().count();
        for(int i = 0 ; i < nodes ; i ++) {
            isOk = true ;
            QDomNode childNode = document.childNodes().item(i) ;
            if(childNode.isElement()) {
                if(!isValidSchema(childNode.toElement())) {
                    Utils::error(tr("The document does not appear to be a XML Schema document."));
                    return false;
                }
                if(!scanSchema(childNode.toElement())) {
                    isOk = false;
                }
            }
        }
        if(!isOk) {
            Utils::error(tr("Unable to parse XML"));
        }
    } else {
        Utils::error(tr("Unable to load schema."));
    }
    return isOk ;
}



bool XSDSchema::canAddChild(const ESchemaType newType)
{
    switch(newType) {
    case SchemaTypeElement:
    case SchemaTypeAttribute:
    case SchemaTypeInclude:
    case SchemaTypeImport:
    case SchemaTypeRedefine:
        //TODO case SchemaTypeSimpleType????
        //TODO   complexType
    case SchemaTypeGroup:
    case SchemaTypeAttributeGroup:
    case SchemaTypeNotation:
    case SchemaTypeAnnotation:
        return true;
        break;
    default:
        return false;
    }
}

bool XSDSchema::isValidSchema(const QDomElement &schema)
{
    return IsXsdValid(schema.namespaceURI(), schema.localName());
}

bool XSDSchema::IsXsdValid(const QString &nsUri, const QString &localName)
{
    if(!((localName == IO_XSD_SCHEMA) && (nsUri == xsdURI()))) {
        return false ;
    }
    return true;

}

XSchemaElement *XSDSchema::rootElement(const QString &referenceName)
{
    return (XSchemaElement*) topLevelObject(referenceName, indexes.elementsList);
}

XSchemaAttribute *XSDSchema::rootAttribute(const QString &referenceName)
{
    return (XSchemaAttribute*) topLevelObject(referenceName, indexes.attributesList);
}

XSchemaElement *XSDSchema::rootType(const QString &referenceName)
{
    return (XSchemaElement*) topLevelObject(referenceName, indexes.typesList);
}

XSchemaObject* XSDSchema::topLevelObject(const QString &name, const ESchemaType type)
{
    QString localName = name;
    int colonIndex = name.indexOf(":");
    if(colonIndex >= 0) {
        localName = name.mid(colonIndex + 1);
    }
    foreach(XSchemaObject * child, _children) {

        if((child->getType() == type) && (localName == child->name())) {
            return child;
        }
    }
    return NULL ;
}

XSchemaObject* XSDSchema::topLevelObject(const QString &name, QList<XSchemaObject*> &objects)
{
    QString localName = name;
    int colonIndex = name.indexOf(":");
    if(colonIndex >= 0) {
        localName = name.mid(colonIndex + 1);
    }
    foreach(XSchemaObject * child, objects) {

        if(localName == child->name()) {
            return child;
        }

    }
    return NULL ;
}

QList<XSchemaObject*> XSDSchema::topLevelObjects(const ESchemaType type)
{
    QList<XSchemaObject*> result ;
    foreach(XSchemaObject * child, _children) {
        if((child->getType() == type)) {
            result.append(child);
        }
    }
    return result ;
}

QList<XSchemaObject*> XSDSchema::topLevelElements()
{
    return indexes.elementsList;
}

QList<XSchemaObject*> XSDSchema::topLevelTypes()
{
    return indexes.typesList;
}


QList<XSchemaObject*> XSDSchema::topLevelAttributes()
{
    return indexes.attributesList;
}

QList<XSchemaObject*> XSDSchema::topLevelReferences()
{
    QList<XSchemaObject*> result;
    result.append(indexes.importsList);
    result.append(indexes.includesList);
    return result ;
}

XSchemaGroup* XSDSchema::topLevelGroup(const QString &name)
{
    foreach(XSchemaObject * child, _children) {
        if((child->getType() == SchemaTypeGroup)) {
            if(child->name() == name) {
                return (XSchemaGroup*)child;
            }
        }
    }
    return NULL ;
}

/*** TODO
vettore?
QList<XSchemaObject*> XSDSchema::topLevelObjects( const ESchemaType type1, const ESchemaType type2)
{
    QList<XSchemaObject*> result ;
    foreach(XSchemaObject *child, _children) {
        if( (child->getType() == type)  ) {
            result.add(child);
        }
    }
    return result ;
}
***********/

void XSDSchema::regenerateInternalLists()
{
    //---
    indexes.includesList.clear();
    indexes.importsList.clear();
    indexes.redefinesList.clear();
    indexes.annotationsList.clear();
    indexes.othersChildrenList.clear();
    indexes.typesList.clear();
    indexes.elementsList.clear();
    indexes.attributesList.clear();
    //---
    foreach(XSchemaObject * child, _children) {
        switch(child->getType()) {
        default:
            indexes.othersChildrenList.append(child);
            break;
        case SchemaTypeAnnotation:
            indexes.annotationsList.append(child);
            break;
        case SchemaTypeImport:
            indexes.importsList.append(child);
            break;
        case SchemaTypeInclude:
            indexes.includesList.append(child);
            break;
        case SchemaTypeAttribute:
            indexes.attributesList.append(child);
            break;
        case SchemaTypeElement: {
            XSchemaElement *element = (XSchemaElement *)child ;
            if(element->isTypeOrElement()) {
                indexes.typesList.append(child);
            } else {
                indexes.elementsList.append(child);
            }
        }
        break;
        }
    }
}


void XSDSchema::setIncludedSchema(XSDSchema *child)
{
    //TODO
}

void XSDSchema::setImportedSchema(XSDSchema *child)
{
    //TODO
}

void XSDSchema::setRedefinedSchema(XSDSchema *child)
{
    //TODO
}
