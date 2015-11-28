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
#include "xsdeditor/XSchemaIOContants.h"

//class XSchemaSimpleContent -----------------------------------------------------------------------------------------


XSchemaSimpleContent::XSchemaSimpleContent(XSchemaObject *newParent, XSchemaRoot *newRoot) :  XSchemaObject(newParent, newRoot), _mainAnnotation(NULL)
{
}

XSchemaSimpleContent::~XSchemaSimpleContent()
{
}

void XSchemaSimpleContent::reset()
{
    _otherTypeAttributes.clear();
    if(_mainAnnotation) {
        delete _mainAnnotation ;
        _mainAnnotation = NULL ;
    }
    XSchemaObject::reset();
}

bool XSchemaSimpleContent::generateDom(QDomDocument & /*document*/, QDomNode & /*parent*/)
{
    XsdError("TODO") ;
    return false;
}
/*****************************************************
XSchemaSimpleContent *XSchemaSimpleContent::readChild(XSchemaObject *parent, QDomElement &element)
{
    XSchemaSimpleContent *newObject = NULL ;
    int nodi = element.childNodes().count();
    for (int i = 0 ; i < nodi ; i ++) {
        QDomNode childNode = element.childNodes().item(i) ;
        if (childNode.isElement()) {
            QDomElement childElement = childNode.toElement();
            QString localName = childElement.localName();
            if( childElement.prefix() == parent->namespacePrefix ) {
                if( localName == IO_XSD_SIMPLECONTENT_RESTRICTION ) {
                    newObject = new XSchemaSimpleContentRestriction( parent, parent->_root );
                    newObject->readBaseProperties( element );
                    return newObject ;
                }
                if( localName == IO_XSD_SIMPLECONTENT_EXTENSION ) {
                    newObject = new XSchemaSimpleContentExtension( parent, parent->_root );
                    newObject->readBaseProperties( element );
                    return newObject ;
                }
            }
        }
    }
    raiseError( parent, childNode, true );
}
************************************/
bool XSchemaSimpleContent::readOtherAttributes(QDomAttr & attribute)
{
    if(_root->existsNamespace(attribute.prefix())) {
        _otherTypeAttributes.insert(attribute.name(), attribute.value());   //TODO check namespace
        return true;
    }
    return false;
}

// Reads base properties
bool XSchemaSimpleContent::readBaseProperties(QDomElement &element)
{
    bool isOk = true ;
    QDomNamedNodeMap attributes = element.attributes();
    int numAttrs = attributes.length();
    for(int i = 0 ; i < numAttrs ; i++) {
        QDomNode node = attributes.item(i);
        QDomAttr attr = node.toAttr();
        QString name = node.nodeName();

        if((name == IO_GENERIC_ID)) {
            _idContainer = attr.value() ;
        } else {
            if(!readOtherAttributes(attr)) {
                raiseError(this, attr, false);
            }
        }
    }

    QString namespacePrefix = _root->namespacePrefix();
    int nodi = element.childNodes().count();
    for(int i = 0 ; i < nodi ; i ++) {
        QDomNode childNode = element.childNodes().item(i) ;

        if(childNode.isElement()) {
            QDomElement childElement = childNode.toElement();
            QString localName = childElement.localName();
            if(childElement.prefix() == namespacePrefix) {
                if(localName == IO_XSD_ANNOTATION) {
                    if(NULL != _mainAnnotation) {
                        raiseError(this, childNode, true);
                    }
                    _mainAnnotation = new XSchemaAnnotation(this, _root) ;
                    if(NULL == _mainAnnotation) {
                        raiseErrorForObject(element);
                    }
                    _mainAnnotation->loadFromDom(childElement);
                } else if(localName == IO_XSD_SIMPLECONTENT_RESTRICTION) {
                    loadFromDom(childElement);
                } else if(localName == IO_XSD_SIMPLECONTENT_EXTENSION) {
                    loadFromDom(childElement);
                } else {
                    raiseError(this, childNode, true);
                }
            } else {
                raiseError(this, childNode, true);
            }
        }
    }
    return isOk;
}

QDomElement XSchemaSimpleContent::writeBaseProperties(QDomElement &element)
{
    QDomDocument document = element.ownerDocument();
    QDomElement node = createElement(document, QString(IO_XSD_SIMPLECONTENT));
    addAttrNotEmpty(node, IO_GENERIC_ID, _idContainer);
    foreach(QString otherKey, _otherTypeAttributes.keys()) {
        element.setAttribute(otherKey, _otherTypeAttributes.value(otherKey));
    }
    if(NULL != _mainAnnotation) {
        _mainAnnotation->generateDom(document, node);
    }
    element.appendChild(node);
    return node;
}

//class XSchemaSimpleContentRestriction -----------------------------------------------------------------------------------------

XSchemaSimpleContentRestriction::XSchemaSimpleContentRestriction(XSchemaObject *newParent, XSchemaRoot *newRoot) : XSchemaSimpleContent(newParent, newRoot)
{
    anyAttribute = false;
}

XSchemaSimpleContentRestriction::~XSchemaSimpleContentRestriction()
{
    reset();
}

void XSchemaSimpleContentRestriction::reset()
{
    XSchemaSimpleContent::reset();
}

bool XSchemaSimpleContentRestriction::generateDom(QDomDocument &document, QDomNode &parent)
{
    QDomElement element = parent.toElement();
    QDomElement parentElement = writeBaseProperties(element);
    QDomElement restriction = createElement(document, IO_XSD_SIMPLECONTENT_RESTRICTION);
    addAttrNotEmpty(restriction, IO_GENERIC_ID, _id);
    addAttrNotEmpty(restriction, IO_GENERIC_BASE, _base);

    addOtherAttributesToDom(restriction);
    if(NULL != _annotation) {
        _annotation->generateDom(document, restriction);
    }
    // if there is a simple type.. TODO
    generateFacets(restriction, _facets);
    //attributes or attributegroup TODO
    //any attribute TODO
    parentElement.appendChild(restriction);
    return true;
}

void XSchemaSimpleContentRestriction::loadFromDom(QDomElement &elementToExamine)
{
    XScanContext context ;
    scanDom(elementToExamine, &context);
}

void XSchemaSimpleContentRestriction::scanForAttributes(QDomAttr &attribute, void * /*context*/)
{
    QString name = attribute.nodeName();

    if(name == IO_GENERIC_ID) {
        _id = attribute.value() ;
    } else if(name == IO_GENERIC_BASE) {
        _base = attribute.value() ;
    } else {
        if(!readOtherAttributes(attribute)) {
            raiseError(this, attribute, false);
        }
    }
}

void XSchemaSimpleContentRestriction::scanForElements(QDomElement &element, void * context)
{
    XScanContext* theContext = (XScanContext*) context ;
    bool isRaiseError = false;
    QString name = element.localName();
    QString value = element.attribute(IO_FACET_ATTR_VALUE, "");
    if(element.prefix() == _root->namespacePrefix()) {
        if(name == IO_XSD_ANNOTATION) {
            readHandleAnnotation(element);
            return;
        } else if(name == IO_XSD_SIMPLETYPE) {
            if(theContext->childFound) {
                raiseError(this, element, true);
            }
            theContext->childFound = true;
            readHandleObject(element, new XSchemaElement(this, _root));
            // } else if( scanForFacets( name, value, _facets ) ) { TODO
        } else if(name == IO_XSD_MINEXCLUSIVE) {
            _facets._minExclusive = value;
        } else if(name == IO_XSD_MININCLUSIVE) {
            _facets._minInclusive = value;
        } else if(name == IO_XSD_MAXEXCLUSIVE) {
            _facets._maxExclusive = value;
        } else if(name == IO_XSD_MAXINCLUSIVE) {
            _facets._maxInclusive = value;
        } else if(name == IO_XSD_TOTALDIGITS) {
            _facets._totalDigits = value;
        } else if(name == IO_XSD_FRACTIONDIGITS) {
            _facets._fractionDigits = value;
        } else if(name == IO_XSD_LENGTH) {
            _facets._length = value;
        } else if(name == IO_XSD_MINLENGTH) {
            _facets._minLength = value;
        } else if(name == IO_XSD_MAXLENGTH) {
            _facets._maxLength = value;
        } else if(name == IO_XSD_ENUMERATION) {   // TODO: WRONG!!!!
            _facets._enumeration.append(value);
        } else if(name == IO_XSD_WHITESPACE) {  // TODO: WRONG!!!!
            _facets._whiteSpace = value;
        } else if(name == IO_XSD_PATTERN) {
            _facets._pattern = value;
        } else if(name == IO_XSD_ATTRIBUTE) {
            readHandleObject(element, new XSchemaAttribute(this, _root));
        } else if(name == IO_XSD_ATTRIBUTEGROUP) {
            readHandleObject(element, new XSchemaAttributeGroup(this, _root));
        } else if(name == IO_XSD_ANYATTRIBUTE) {
            if(anyAttribute) {
                raiseError(this, element, true);
            }
            readHandleObject(element, new XSchemaAnyAttribute(this, _root));
            anyAttribute = true ;
        } else {
            isRaiseError = true;
        }
    } else {
        isRaiseError = true;
    }
    if(isRaiseError) {
        raiseError(this, element, true);
    }
}

// TODO: validate structure

//class XSchemaSimpleContentExtension -----------------------------------------------------------------------------------------

XSchemaSimpleContentExtension::XSchemaSimpleContentExtension(XSchemaObject *newParent, XSchemaRoot *newRoot): XSchemaSimpleContent(newParent, newRoot)
{
    anyAttribute = false;
}

XSchemaSimpleContentExtension::~XSchemaSimpleContentExtension()
{
    reset();
}

void XSchemaSimpleContentExtension::reset()
{
    XSchemaSimpleContent::reset();
}

bool XSchemaSimpleContentExtension::generateDom(QDomDocument &document, QDomNode &parent)
{
    QDomElement element = parent.toElement();
    QDomElement parentElement = writeBaseProperties(element);
    QDomElement restriction = createElement(document, IO_XSD_SIMPLECONTENT_EXTENSION);
    addAttrNotEmpty(restriction, IO_GENERIC_ID, _id);
    addAttrNotEmpty(restriction, IO_GENERIC_BASE, _base);

    addOtherAttributesToDom(restriction);
    if(NULL != _annotation) {
        _annotation->generateDom(document, restriction);
    }
    //attributes or attributegroup TODO
    //any attribute TODO
    parentElement.appendChild(restriction);
    return true;

}

void XSchemaSimpleContentExtension::loadFromDom(QDomElement &elementToExamine)
{
    XScanContext context ;
    scanDom(elementToExamine, &context);
}

void XSchemaSimpleContentExtension::scanForAttributes(QDomAttr &attribute, void * /*context*/)
{
    QString name = attribute.nodeName();

    if(name == IO_GENERIC_ID) {
        _id = attribute.value() ;
    } else if(name == IO_GENERIC_BASE) {
        _base = attribute.value() ;
    } else {
        if(!readOtherAttributes(attribute)) {
            raiseError(this, attribute, false);
        }
    }
}

void XSchemaSimpleContentExtension::scanForElements(QDomElement &element, void * /*context*/)
{
    bool isRaiseError = true;
    QString name = element.localName();
    if(element.prefix() == _root->namespacePrefix()) {
        if(name == IO_XSD_ANNOTATION) {
            readHandleAnnotation(element);
            return;
        } else if(name == IO_XSD_ATTRIBUTE) {
            readHandleObject(element, new XSchemaAttribute(this, _root));
            isRaiseError = false ;
        } else if(name == IO_XSD_ATTRIBUTEGROUP) {
            readHandleObject(element, new XSchemaAttributeGroup(this, _root));
            isRaiseError = false ;
        } else if(name == IO_XSD_ANYATTRIBUTE) {
            if(anyAttribute) {
                raiseError(this, element, true);
            }
            readHandleObject(element, new XSchemaAnyAttribute(this, _root));
            anyAttribute = true ;
            isRaiseError = false ;
        }
    }
    if(isRaiseError) {
        raiseError(this, element, true);
    }
}


//class XSchemaComplexContent -----------------------------------------------------------------------------------------

XSchemaComplexContent::XSchemaComplexContent(XSchemaObject *newParent, XSchemaRoot *newRoot) : XSchemaObject(newParent, newRoot)
{
    _mixed = XEnums::XBOOL_UNSET ;
    anyAttribute = false;
}

XSchemaComplexContent::~XSchemaComplexContent()
{
    reset();
}

void XSchemaComplexContent::reset()
{
    XSchemaObject::reset();
}

bool XSchemaComplexContent::generateDom(QDomDocument &/*document*/, QDomNode &/*parent*/)
{
    XsdError("TODO");
    return false;
}

void XSchemaComplexContent::loadFromDom(QDomElement &elementToExamine)
{
    XScanContext context ;
    scanDom(elementToExamine, &context);
}

// Reads base properties
bool XSchemaComplexContent::readBaseProperties(QDomElement &element)
{
    bool isOk = true ;
    QDomNamedNodeMap attributes = element.attributes();
    int numAttrs = attributes.length();
    for(int i = 0 ; i < numAttrs ; i++) {
        QDomNode node = attributes.item(i);
        QDomAttr attr = node.toAttr();
        QString name = node.nodeName();

        if((name == IO_GENERIC_ID)) {
            _idContainer = attr.value() ;
        } else if((name == IO_GENERIC_MIXED)) {
            _mixed = XEnums::parseBool(attr.value());
        } else {
            if(!readOtherAttributes(attr)) {
                raiseError(this, attr, false);
            }
        }
    }

    QString namespacePrefix = _root->namespacePrefix();
    int nodi = element.childNodes().count();
    for(int i = 0 ; i < nodi ; i ++) {
        QDomNode childNode = element.childNodes().item(i) ;

        if(childNode.isElement()) {
            QDomElement childElement = childNode.toElement();
            QString localName = childElement.localName();
            if(childElement.prefix() == namespacePrefix) {
                if(localName == IO_XSD_ANNOTATION) {
                    if(NULL != _mainAnnotation) {
                        raiseError(this, childNode, true);
                    }
                    _mainAnnotation = new XSchemaAnnotation(this, _root) ;
                    if(NULL == _mainAnnotation) {
                        raiseErrorForObject(element);
                    }
                    _mainAnnotation->loadFromDom(childElement);
                } else if(localName == IO_XSD_COMPLEXCONTENT_RESTRICTION) {
                    loadFromDom(childElement);
                } else if(localName == IO_XSD_COMPLEXCONTENT_EXTENSION) {
                    loadFromDom(childElement);
                } else {
                    raiseError(this, childNode, true);
                }
            } else {
                raiseError(this, childNode, true);
            }
        }
    }
    return isOk;
}

QDomElement XSchemaComplexContent::writeBaseProperties(QDomElement &element)
{
    QDomDocument document = element.ownerDocument();
    QDomElement node = createElement(document, QString(IO_XSD_COMPLEXCONTENT));
    addAttrNotEmpty(node, IO_GENERIC_ID, _idContainer);
    // TODO addAttrNotEmpty( node, IO_GENERIC_MIXED, _mixed );
    foreach(QString otherKey, _otherTypeAttributes.keys()) {
        element.setAttribute(otherKey, _otherTypeAttributes.value(otherKey));
    }
    if(NULL != _mainAnnotation) {
        _mainAnnotation->generateDom(document, node);
    }
    element.appendChild(node);
    return node;
}

void XSchemaComplexContent::scanForAttributes(QDomAttr &attribute, void * /*context*/)
{
    QString name = attribute.nodeName();

    if(name == IO_GENERIC_ID) {
        _id = attribute.value() ;
    } else if(name == IO_GENERIC_BASE) {
        _base = attribute.value() ;
    } else {
        if(!readOtherAttributes(attribute)) {
            raiseError(this, attribute, false);
        }
    }
}

void XSchemaComplexContent::scanForElements(QDomElement &element, void * context)
{
    XScanContext *theContext = (XScanContext*) context;
    bool isRaiseError = false ;
    QString name = element.localName();
    if(element.prefix() == _root->namespacePrefix()) {
        if(name == IO_XSD_ANNOTATION) {
            readHandleAnnotation(element);
        } else if(name == IO_XSD_ATTRIBUTE) {
            readHandleObject(element, new XSchemaAttribute(this, _root));
        } else if(name == IO_XSD_ATTRIBUTEGROUP) {
            readHandleObject(element, new XSchemaAttributeGroup(this, _root));
        } else if(name == IO_XSD_ANYATTRIBUTE) {
            if(anyAttribute) {
                raiseError(this, element, true);
            }
            readHandleObject(element, new XSchemaAnyAttribute(this, _root));
            anyAttribute = true ;
        } else if(name == IO_XSD_GROUP) {
            if(theContext->childFound) {
                raiseError(this, element, true);
            }
            readHandleObject(element, new XSchemaGroup(this, _root));
            theContext->childFound = true ;
        } else if(name == IO_XSD_ALL) {
            if(theContext->childFound) {
                raiseError(this, element, true);
            }
            readHandleObject(element, new XSchemaAll(this, _root));
            theContext->childFound = true ;
        } else if(name == IO_XSD_CHOICE) {
            if(theContext->childFound) {
                raiseError(this, element, true);
            }
            readHandleObject(element, new XSchemaChoice(this, _root));
            theContext->childFound = true ;
        } else if(name == IO_XSD_SEQUENCE) {
            if(theContext->childFound) {
                raiseError(this, element, true);
            }
            readHandleObject(element, new XSchemaSequence(this, _root));
            theContext->childFound = true ;
        } else {
            isRaiseError = true ;
        }
    } else {
        isRaiseError = true ;
    }
    if(isRaiseError) {
        raiseError(this, element, true);
    }
}

bool XSchemaComplexContent::readOtherAttributes(QDomAttr & attribute)
{
    if(_root->existsNamespace(attribute.prefix())) {
        _otherTypeAttributes.insert(attribute.name(), attribute.value());   //TODO check namespace
        return true;
    }
    return false;
}

//class XSchemaComplexContentRestriction -----------------------------------------------------------------------------------------

XSchemaComplexContentRestriction::XSchemaComplexContentRestriction(XSchemaObject *newParent, XSchemaRoot *newRoot) : XSchemaComplexContent(newParent, newRoot)
{
}

XSchemaComplexContentRestriction::~XSchemaComplexContentRestriction()
{
    reset();
}

void XSchemaComplexContentRestriction::reset()
{
    XSchemaComplexContent::reset();
}

bool XSchemaComplexContentRestriction::generateDom(QDomDocument &/*document*/, QDomNode &/*parent*/)
{
    XsdError("TODO");
    return false ;
}

QString XSchemaComplexContentRestriction::description()
{
    QString description = QString("Extension of '%1'").arg(_base) ;
    return description ;
}

//class XSchemaComplexContentRestriction -----------------------------------------------------------------------------------------


XSchemaComplexContentExtension::XSchemaComplexContentExtension(XSchemaObject *newParent, XSchemaRoot *newRoot)  : XSchemaComplexContent(newParent, newRoot)
{
}

XSchemaComplexContentExtension::~XSchemaComplexContentExtension()
{
    reset();
}

void XSchemaComplexContentExtension::reset()
{
    XSchemaComplexContent::reset();
}

bool XSchemaComplexContentExtension::generateDom(QDomDocument & /*document*/, QDomNode & /*parent*/)
{
    XsdError("TODO");
    return false;
}


QString XSchemaComplexContentExtension::description()
{
    QString description = QString("Extension of '%1'").arg(_base) ;
    return description ;
}
