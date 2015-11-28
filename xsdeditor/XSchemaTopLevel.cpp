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
#include <limits>

// Top level objects

void XSchemaInclude::reset()
{
    XSchemaObject::reset();
}

XSchemaInclude::XSchemaInclude(XSchemaObject *newParent, XSchemaRoot *newRoot): XSchemaObject(newParent, newRoot)
{
}

XSchemaInclude::~XSchemaInclude()
{
    reset();
}

bool XSchemaInclude::generateDom(QDomDocument &document, QDomNode &parent)
{
    QDomElement node = createElement(document, IO_XSD_TAGINCLUDE);
    addAttrNotEmpty(node, IO_GENERIC_ID, _id);
    addAttrNotEmpty(node, IO_INCLUDE_ATTR_SCHEMALOCATION, _schemaLocation);
    addOtherAttributesToDom(node);
    if(NULL != _annotation) {
        _annotation->generateDom(document, node);
    }
    parent.appendChild(node);
    return true;
}

// ---------- load -----------------------------

void XSchemaInclude::loadFromDom(QDomElement &elementToExamine)
{
    XScanContext context ;
    scanDom(elementToExamine, &context);
}

void XSchemaInclude::scanForAttributes(QDomAttr &attribute, void * /*context*/)
{
    QString name = attribute.nodeName();

    if(name == IO_GENERIC_ID) {
        _id = attribute.value() ;
    } else if(name == IO_INCLUDE_ATTR_SCHEMALOCATION) {
        _schemaLocation = attribute.value() ;
    } else {
        if(!readOtherAttributes(attribute)) {
            raiseError(this, attribute, false);
        }
    }
}

void XSchemaInclude::scanForElements(QDomElement &element, void * context)
{
    scanForContentAnnotation(element, context);
}

QString XSchemaInclude::description()
{
    return QString("include %1").arg(_schemaLocation);
}

// ---------- notation -----------------------------


void XSchemaNotation::reset()
{
    XSchemaObject::reset();
}

XSchemaNotation::XSchemaNotation(XSchemaObject *newParent, XSchemaRoot *newRoot): XSchemaObject(newParent, newRoot)
{
}

XSchemaNotation::~XSchemaNotation()
{
    reset();
}

bool XSchemaNotation::generateDom(QDomDocument &document, QDomNode &parent)
{
    QDomElement node = createElement(document, IO_XSD_TAGNOTATION);
    addAttrNotEmpty(node, IO_GENERIC_ID, _id);
    addAttrNotEmpty(node, IO_GENERIC_NAME, _name);
    addAttrNotEmpty(node, IO_NOTATION_ATTR_PUBLIC, _publicIdentifier);
    addAttrNotEmpty(node, IO_NOTATION_ATTR_SYSTEM, _system);

    addOtherAttributesToDom(node);
    if(NULL != _annotation) {
        _annotation->generateDom(document, node);
    }
    parent.appendChild(node);
    return true;
}

// ---------- load -----------------------------

void XSchemaNotation::loadFromDom(QDomElement &elementToExamine)
{
    XScanContext context ;
    scanDom(elementToExamine, &context);
}

void XSchemaNotation::scanForAttributes(QDomAttr &attribute, void * /*context*/)
{
    QString name = attribute.nodeName();

    if(name == IO_GENERIC_ID) {
        _id = attribute.value() ;
    } else if(name == IO_GENERIC_NAME) {
        _name = attribute.value() ;
    } else if(name == IO_NOTATION_ATTR_PUBLIC) {
        _publicIdentifier = attribute.value() ;
    } else if(name == IO_NOTATION_ATTR_SYSTEM) {
        _system = attribute.value() ;
    } else {
        if(!readOtherAttributes(attribute)) {
            raiseError(this, attribute, false);
        }
    }
}

void XSchemaNotation::scanForElements(QDomElement &element, void *context)
{
    scanForContentAnnotation(element, context);
}

void XSchemaNotation::validateAfterRead(QDomElement &node, void * /*context*/)
{
    if(_name.isEmpty()) {
        invalidObjectState(this, node, IO_GENERIC_NAME);
    }
    if(_publicIdentifier.isEmpty()) {
        invalidObjectState(this, node, IO_NOTATION_ATTR_SYSTEM);
    }
}

QString XSchemaNotation::description()
{
    return QString("notation %1:%2").arg(_name).arg(_publicIdentifier);
}

//---------------- import -------------------------------------------

void XSchemaImport::reset()
{
    XSchemaObject::reset();
}

XSchemaImport::XSchemaImport(XSchemaObject *newParent, XSchemaRoot *newRoot): XSchemaObject(newParent, newRoot)
{
}

XSchemaImport::~XSchemaImport()
{
    reset();
}

bool XSchemaImport::generateDom(QDomDocument &document, QDomNode &parent)
{
    QDomElement node = createElement(document, IO_XSD_TAGIMPORT);
    addAttrNotEmpty(node, IO_GENERIC_ID, _id);
    addAttrNotEmpty(node, IO_GENERIC_ATTR_SCHEMALOCATION , _schemaLocation);
    addAttrNotEmpty(node, IO_GENERIC_NAMESPACE, _namespace);
    addOtherAttributesToDom(node);
    if(NULL != _annotation) {
        _annotation->generateDom(document, node);
    }
    parent.appendChild(node);
    return true;
}

// ---------- load -----------------------------

void XSchemaImport::loadFromDom(QDomElement &elementToExamine)
{
    XScanContext context ;
    scanDom(elementToExamine, &context);
}

void XSchemaImport::scanForAttributes(QDomAttr &attribute, void * /*context*/)
{
    QString name = attribute.nodeName();

    if(name == IO_GENERIC_ID) {
        _id = attribute.value() ;
    } else if(name == IO_GENERIC_ATTR_SCHEMALOCATION) {
        _schemaLocation = attribute.value() ;
    } else if(name == IO_GENERIC_NAMESPACE) {
        _namespace = attribute.value() ;
    } else {
        if(!readOtherAttributes(attribute)) {
            raiseError(this, attribute, false);
        }
    }
}

void XSchemaImport::scanForElements(QDomElement &element, void * context)
{
    scanForContentAnnotation(element, context);
}

QString XSchemaImport::description()
{
    return QString("import %1 (%2)").arg(_namespace).arg(_schemaLocation);
}


//---------------- key -------------------------------------------

void XSchemaKey::reset()
{
    XSchemaObject::reset();
}

XSchemaKey::XSchemaKey(XSchemaObject *newParent, XSchemaRoot *newRoot): XSchemaObject(newParent, newRoot)
{
}

XSchemaKey::~XSchemaKey()
{
    reset();
}

bool XSchemaKey::generateDom(QDomDocument &document, QDomNode &parent)
{
    QDomElement node = createElement(document, IO_XSD_KEY);
    addAttrNotEmpty(node, IO_GENERIC_ID, _id);
    addAttrNotEmpty(node, IO_GENERIC_NAME, _name);
    addOtherAttributesToDom(node);
    if(NULL != _annotation) {
        _annotation->generateDom(document, node);
    }
    generateInnerDom(document, node);
    parent.appendChild(node);
    return true;
}

// ---------- load

void XSchemaKey::loadFromDom(QDomElement &elementToExamine)
{
    XScanContext context ;
    scanDom(elementToExamine, &context);
}

void XSchemaKey::scanForAttributes(QDomAttr &attribute, void * /*context*/)
{
    QString name = attribute.nodeName();

    if(name == IO_GENERIC_ID) {
        _id = attribute.value() ;
    } else if(name == IO_GENERIC_NAME) {
        _name = attribute.value() ;
    } else {
        if(!readOtherAttributes(attribute)) {
            raiseError(this, attribute, false);
        }
    }
}

void XSchemaKey::scanForElements(QDomElement &element, void * context)
{
    XScanContext *theContext = (XScanContext*) context;
    QString name = element.localName();
    if(element.prefix() == _root->namespacePrefix()) {
        if(name == IO_XSD_ANNOTATION) {
            readHandleAnnotation(element);
            return;
        } else if(name == IO_XSD_SELECTOR) {
            if(theContext->selectorFound) {
                raiseError(this, element, true);
            }
            readHandleObject(element, new XSchemaSelector(this, _root));
            theContext->selectorFound = true ;
            return ;
        } else if(name == IO_XSD_FIELD) {
            readHandleObject(element, new XSchemaField(this, _root));
            theContext->fieldFound = true ;
            return ;
        }
    }
    raiseError(this, element, true);
}


void XSchemaKey::validateAfterRead(QDomElement &node, void * context)
{
    XScanContext *theContext = (XScanContext*) context;
    if(!theContext->selectorFound) {
        invalidObjectState(this, node, IO_XSD_SELECTOR);
    }
    if(_name.isEmpty()) {
        invalidObjectState(this, node, IO_GENERIC_NAME);
    }
    if(!theContext->fieldFound) {
        invalidObjectState(this, node, IO_XSD_FIELD);
    }
}

//---------------- selector -------------------------------------------

void XSchemaSelector::reset()
{
    XSchemaObject::reset();
}

XSchemaSelector::XSchemaSelector(XSchemaObject *newParent, XSchemaRoot *newRoot): XSchemaObject(newParent, newRoot)
{
}

XSchemaSelector::~XSchemaSelector()
{
    reset();
}

bool XSchemaSelector::generateDom(QDomDocument &document, QDomNode &parent)
{
    QDomElement node = createElement(document, IO_XSD_SELECTOR);
    addAttrNotEmpty(node, IO_GENERIC_ID, _id);
    addAttrNotEmpty(node, IO_GENERIC_ATTR_XPATH, _xpath);
    addOtherAttributesToDom(node);
    if(NULL != _annotation) {
        _annotation->generateDom(document, node);
    }
    parent.appendChild(node);
    return true;
}

// ---------- load

void XSchemaSelector::loadFromDom(QDomElement &elementToExamine)
{
    XScanContext context ;
    scanDom(elementToExamine, &context);
}

void XSchemaSelector::scanForAttributes(QDomAttr &attribute, void * /*context*/)
{
    QString name = attribute.nodeName();

    if(name == IO_GENERIC_ID) {
        _id = attribute.value() ;
    } else if(name == IO_GENERIC_ATTR_XPATH) {
        _xpath = attribute.value() ;
    } else {
        if(!readOtherAttributes(attribute)) {
            raiseError(this, attribute, false);
        }
    }
}

void XSchemaSelector::scanForElements(QDomElement &element, void * context)
{
    scanForContentAnnotation(element, context);
}


void XSchemaSelector::validateAfterRead(QDomElement &node, void * /*context*/)
{
    if(_xpath.isEmpty()) {
        invalidObjectState(this, node, IO_GENERIC_ATTR_XPATH);
    }
}

//---------------- field -------------------------------------------

void XSchemaField::reset()
{
    XSchemaObject::reset();
}

XSchemaField::XSchemaField(XSchemaObject *newParent, XSchemaRoot *newRoot): XSchemaObject(newParent, newRoot)
{
}

XSchemaField::~XSchemaField()
{
    reset();
}

bool XSchemaField::generateDom(QDomDocument &document, QDomNode &parent)
{
    QDomElement node = createElement(document, IO_XSD_FIELD);
    addAttrNotEmpty(node, IO_GENERIC_ID, _id);
    addAttrNotEmpty(node, IO_GENERIC_ATTR_XPATH, _xpath);
    addOtherAttributesToDom(node);
    if(NULL != _annotation) {
        _annotation->generateDom(document, node);
    }
    parent.appendChild(node);
    return true;
}

// ---------- load

void XSchemaField::loadFromDom(QDomElement &elementToExamine)
{
    XScanContext context ;
    scanDom(elementToExamine, &context);
}

void XSchemaField::scanForAttributes(QDomAttr &attribute, void * /*context*/)
{
    QString name = attribute.nodeName();

    if(name == IO_GENERIC_ID) {
        _id = attribute.value() ;
    } else if(name == IO_GENERIC_ATTR_XPATH) {
        _xpath = attribute.value() ;
    } else {
        if(!readOtherAttributes(attribute)) {
            raiseError(this, attribute, false);
        }
    }
}

void XSchemaField::scanForElements(QDomElement &element, void * context)
{
    scanForContentAnnotation(element, context);
}


void XSchemaField::validateAfterRead(QDomElement &node, void * /*context*/)
{
    if(_xpath.isEmpty()) {
        invalidObjectState(this, node, IO_GENERIC_ATTR_XPATH);
    }
}

//---------------- keyref -------------------------------------------

void XSchemaKeyRef::reset()
{
    XSchemaObject::reset();
}

XSchemaKeyRef::XSchemaKeyRef(XSchemaObject *newParent, XSchemaRoot *newRoot): XSchemaObject(newParent, newRoot)
{
}

XSchemaKeyRef::~XSchemaKeyRef()
{
    reset();
}

bool XSchemaKeyRef::generateDom(QDomDocument &document, QDomNode &parent)
{
    QDomElement node = createElement(document, IO_XSD_KEYREF);
    addAttrNotEmpty(node, IO_GENERIC_ID, _id);
    addAttrNotEmpty(node, IO_GENERIC_NAME, _name);
    addAttrNotEmpty(node, IO_GENERIC_REFER, _refer);
    addOtherAttributesToDom(node);
    if(NULL != _annotation) {
        _annotation->generateDom(document, node);
    }
    generateInnerDom(document, node);
    parent.appendChild(node);
    return true;
}

// ---------- load

void XSchemaKeyRef::loadFromDom(QDomElement &elementToExamine)
{
    XScanContext context ;
    scanDom(elementToExamine, &context);
}

void XSchemaKeyRef::scanForAttributes(QDomAttr &attribute, void * /*context*/)
{
    QString name = attribute.nodeName();

    if(name == IO_GENERIC_ID) {
        _id = attribute.value() ;
    } else if(name == IO_GENERIC_NAME) {
        _name = attribute.value() ;
    } else if(name == IO_GENERIC_REFER) {
        _refer = attribute.value() ;
    } else {
        if(!readOtherAttributes(attribute)) {
            raiseError(this, attribute, false);
        }
    }
}

void XSchemaKeyRef::scanForElements(QDomElement &element, void * context)
{
    XScanContext *theContext = (XScanContext*) context;
    QString name = element.localName();
    if(element.prefix() == _root->namespacePrefix()) {
        if(name == IO_XSD_ANNOTATION) {
            readHandleAnnotation(element);
            return;
        } else if(name == IO_XSD_SELECTOR) {
            if(theContext->selectorFound) {
                raiseError(this, element, true);
            }
            readHandleObject(element, new XSchemaSelector(this, _root));
            theContext->selectorFound = true ;
            return ;
        } else if(name == IO_XSD_FIELD) {
            readHandleObject(element, new XSchemaField(this, _root));
            theContext->fieldFound = true ;
            return ;
        }
    }
    raiseError(this, element, true);
}


void XSchemaKeyRef::validateAfterRead(QDomElement &node, void * context)
{
    XScanContext *theContext = (XScanContext*) context;
    if(!theContext->selectorFound) {
        invalidObjectState(this, node, IO_XSD_SELECTOR);
    }
    if(_name.isEmpty()) {
        invalidObjectState(this, node, IO_GENERIC_NAME);
    }
    if(_refer.isEmpty()) {
        invalidObjectState(this, node, IO_GENERIC_REFER);
    }
    if(!theContext->fieldFound) {
        invalidObjectState(this, node, IO_XSD_FIELD);
    }
}

//---------------- unique -------------------------------------------

void XSchemaUnique::reset()
{
    XSchemaObject::reset();
}

XSchemaUnique::XSchemaUnique(XSchemaObject *newParent, XSchemaRoot *newRoot): XSchemaObject(newParent, newRoot)
{
}

XSchemaUnique::~XSchemaUnique()
{
    reset();
}

bool XSchemaUnique::generateDom(QDomDocument &document, QDomNode &parent)
{
    QDomElement node = createElement(document, IO_XSD_UNIQUE);
    addAttrNotEmpty(node, IO_GENERIC_ID, _id);
    addAttrNotEmpty(node, IO_GENERIC_NAME, _name);
    addOtherAttributesToDom(node);
    if(NULL != _annotation) {
        _annotation->generateDom(document, node);
    }
    generateInnerDom(document, node);
    parent.appendChild(node);
    return true;
}

// ---------- load

void XSchemaUnique::loadFromDom(QDomElement &elementToExamine)
{
    XScanContext context ;
    scanDom(elementToExamine, &context);
}

void XSchemaUnique::scanForAttributes(QDomAttr &attribute, void * /*context*/)
{
    QString name = attribute.nodeName();

    if(name == IO_GENERIC_ID) {
        _id = attribute.value() ;
    } else if(name == IO_GENERIC_NAME) {
        _name = attribute.value() ;
    } else {
        if(!readOtherAttributes(attribute)) {
            raiseError(this, attribute, false);
        }
    }
}

void XSchemaUnique::scanForElements(QDomElement &element, void * context)
{
    XScanContext *theContext = (XScanContext*) context;
    QString name = element.localName();
    if(element.prefix() == _root->namespacePrefix()) {
        if(name == IO_XSD_ANNOTATION) {
            readHandleAnnotation(element);
            return;
        } else if(name == IO_XSD_SELECTOR) {
            if(theContext->selectorFound) {
                raiseError(this, element, true);
            }
            readHandleObject(element, new XSchemaSelector(this, _root));
            theContext->selectorFound = true ;
            return ;
        } else if(name == IO_XSD_FIELD) {
            readHandleObject(element, new XSchemaField(this, _root));
            theContext->fieldFound = true ;
            return ;
        }
    }
    raiseError(this, element, true);
}


void XSchemaUnique::validateAfterRead(QDomElement &node, void * context)
{
    XScanContext *theContext = (XScanContext*) context;
    if(!theContext->selectorFound) {
        invalidObjectState(this, node, IO_XSD_SELECTOR);
    }
    if(_name.isEmpty()) {
        invalidObjectState(this, node, IO_GENERIC_NAME);
    }
    if(!theContext->fieldFound) {
        invalidObjectState(this, node, IO_XSD_FIELD);
    }
}

//---------------- group -------------------------------------------

void XSchemaGroup::reset()
{
    XSchemaObject::reset();
}

XSchemaGroup::XSchemaGroup(XSchemaObject *newParent, XSchemaRoot *newRoot): XSchemaObject(newParent, newRoot)
{
    _maxOccurs.isUnbounded = true ;
}

XSchemaGroup::~XSchemaGroup()
{
    reset();
}

bool XSchemaGroup::generateDom(QDomDocument &document, QDomNode &parentNode)
{
    bool isTopLevelNode ;
    switch(this->_parent->getType()) {
    case SchemaTypeSchema:
    case SchemaTypeRedefine:
        isTopLevelNode = true;
    default:
        isTopLevelNode = false;
    }

    QDomElement element = createElement(document, IO_XSD_GROUP);
    addAttrNotEmpty(element, IO_GENERIC_ID, _id);
    if(isTopLevelNode) {
        addAttrNotEmpty(element, IO_GENERIC_NAME, _name);
    } else {
        addAttrNotEmpty(element, IO_GENERIC_REF, _ref);
        _minOccurs.addAttrToNode(element, IO_GENERIC_MINOCCURS);
        _maxOccurs.addAttrToNode(element, IO_GENERIC_MAXOCCURS);
    }
    addOtherAttributesToDom(element);
    if(isTopLevelNode) {
        if(NULL != _annotation) {
            _annotation->generateDom(document, element);
        }
        generateInnerDom(document, element);
    }
    parentNode.appendChild(element);
    return true;
}

QString XSchemaGroup::description()
{
    return QString("group %1").arg(_name);
}

// ---------- load

void XSchemaGroup::loadFromDom(QDomElement &elementToExamine)
{
    XScanContext context ;
    scanDom(elementToExamine, &context);
}

void XSchemaGroup::scanForAttributes(QDomAttr &attribute, void * /*context*/)
{
    QString name = attribute.nodeName();

    if(name == IO_GENERIC_ID) {
        _id = attribute.value() ;
    } else if(name == IO_GENERIC_NAME) {
        _name = attribute.value() ;
    } else if(name == IO_GENERIC_REF) {
        _ref = attribute.value() ;
    } else if(name == IO_GENERIC_MINOCCURS) {
        if(!_minOccurs.setValueFromAttribute(attribute.value())) {
            raiseError(this, attribute, false);
        }
    } else if(name == IO_GENERIC_MAXOCCURS) {
        if(!_maxOccurs.setValueFromAttribute(attribute.value())) {
            raiseError(this, attribute, false);
        }
    } else {
        if(!readOtherAttributes(attribute)) {
            raiseError(this, attribute, false);
        }
    }
}

void XSchemaGroup::scanForElements(QDomElement &element, void * context)
{
    XScanContext *theContext = (XScanContext*) context;
    QString name = element.localName();
    if(element.prefix() == _root->namespacePrefix()) {
        if(name == IO_XSD_ANNOTATION) {
            readHandleAnnotation(element);
            return;
        } else if(name == IO_XSD_ALL) {
            if(theContext->childFound) {
                raiseError(this, element, true);
            }
            readHandleObject(element, new XSchemaAll(this, _root));
            theContext->childFound = true ;
            return;
        } else if(name == IO_XSD_CHOICE) {
            if(theContext->childFound) {
                raiseError(this, element, true);
            }
            readHandleObject(element, new XSchemaChoice(this, _root));
            theContext->childFound = true ;
            return;
        } else if(name == IO_XSD_SEQUENCE) {
            if(theContext->childFound) {
                raiseError(this, element, true);
            }
            readHandleObject(element, new XSchemaSequence(this, _root));
            theContext->childFound = true ;
            return;
        }
    }
    raiseError(this, element, true);
}


void XSchemaGroup::validateAfterRead(QDomElement & /*node*/, void * /*context*/)
{
    /* TODO
    }*/
}

//------------ Redefine ----------------------------------------------------------------------------

void XSchemaRedefine::reset()
{
    XSchemaObject::reset();
}

XSchemaRedefine::XSchemaRedefine(XSchemaObject *newParent, XSchemaRoot *newRoot): XSchemaObject(newParent, newRoot)
{
}

XSchemaRedefine::~XSchemaRedefine()
{
    reset();
}

bool XSchemaRedefine::generateDom(QDomDocument &document, QDomNode &parentNode)
{
    QDomElement element = createElement(document, IO_XSD_REDEFINE);
    addAttrNotEmpty(element, IO_GENERIC_ID, _id);
    element.setAttribute(IO_REDEFINE_ATTR_SCHEMALOCATION_REF, _schemaLocation);
    addOtherAttributesToDom(element);
    if(NULL != _annotation) {
        _annotation->generateDom(document, element);
    }
    generateInnerDom(document, element);
    parentNode.appendChild(element);
    return true;
}

// ---------- load

void XSchemaRedefine::loadFromDom(QDomElement &elementToExamine)
{
    XScanContext context ;
    scanDom(elementToExamine, &context);
}

void XSchemaRedefine::scanForAttributes(QDomAttr &attribute, void * /*context*/)
{
    QString name = attribute.nodeName();

    if(name == IO_GENERIC_ID) {
        _id = attribute.value() ;
    } else if(name == IO_REDEFINE_ATTR_SCHEMALOCATION_REF) {
        _schemaLocation = attribute.value() ;
    } else {
        if(!readOtherAttributes(attribute)) {
            raiseError(this, attribute, false);
        }
    }
}

void XSchemaRedefine::scanForElements(QDomElement &element, void * /*context*/)
{
    //XScanContext *theContext = (XScanContext*) context;
    QString name = element.localName();
    if(element.prefix() == _root->namespacePrefix()) {
        if(name == IO_XSD_ANNOTATION) {
            readHandleObject(element, new XSchemaAnnotation(this, _root));
            return;
        } else if((name == IO_XSD_SIMPLETYPE) || (name == IO_XSD_COMPLEXTYPE)) {
            readHandleObject(element, new XSchemaElement(this, _root));
            return;
        } else if(name == IO_XSD_GROUP) {
            readHandleObject(element, new XSchemaGroup(this, _root));
        } else if(name == IO_XSD_ATTRIBUTEGROUP) {
            readHandleObject(element, new XSchemaAttributeGroup(this, _root));
            return;
        }
    }
    raiseError(this, element, true);
}


void XSchemaRedefine::validateAfterRead(QDomElement & node, void * /*context*/)
{
    if(_schemaLocation.isEmpty()) {
        invalidObjectState(this, node, IO_REDEFINE_ATTR_SCHEMALOCATION_REF);
    }
}

void XSchemaAny::reset()
{
    XSchemaObject::reset();
}

XSchemaAny::XSchemaAny(XSchemaObject *newParent, XSchemaRoot *newRoot): XSchemaObject(newParent, newRoot)
{
    _maxOccurs.isUnbounded = true ;
}

XSchemaAny::~XSchemaAny()
{
    reset();
}

bool XSchemaAny::generateDom(QDomDocument &document, QDomNode &parentNode)
{
    QDomElement element = createElement(document, IO_XSD_ANY);
    addAttrNotEmpty(element, IO_GENERIC_ID, _id);
    addAttrNotEmpty(element, IO_GENERIC_NAMESPACE, _namespaces);
    _minOccurs.addAttrToNode(element, IO_GENERIC_MINOCCURS);
    _maxOccurs.addAttrToNode(element, IO_GENERIC_MAXOCCURS);
    addAttrNotEmpty(element, IO_GENERIC_ATTR_PROCESSCONTENTS, processContentstoString(_processContent));
    addOtherAttributesToDom(element);
    if(NULL != _annotation) {
        _annotation->generateDom(document, element);
    }
    parentNode.appendChild(element);
    return true;
}

// ---------- load

void XSchemaAny::loadFromDom(QDomElement &elementToExamine)
{
    XScanContext context ;
    scanDom(elementToExamine, &context);
}

void XSchemaAny::scanForAttributes(QDomAttr &attribute, void * /*context*/)
{
    QString name = attribute.nodeName();

    if(name == IO_GENERIC_ID) {
        _id = attribute.value() ;
    } else if(name == IO_GENERIC_NAMESPACE) {
        _namespaces  = attribute.value() ; //(##any,##local,##other,...)
    } else if(name == IO_GENERIC_ATTR_PROCESSCONTENTS) {
        _processContent = decodeProcessContents(attribute.value());
    } else if(name == IO_GENERIC_MINOCCURS) {
        if(!_minOccurs.setValueFromAttribute(attribute.value())) {
            raiseError(this, attribute, false);
        }
    } else if(name == IO_GENERIC_MAXOCCURS) {
        if(!_maxOccurs.setValueFromAttribute(attribute.value())) {
            raiseError(this, attribute, false);
        }
    } else {
        if(!readOtherAttributes(attribute)) {
            raiseError(this, attribute, false);
        }
    }
}

void XSchemaAny::scanForElements(QDomElement &element, void * context)
{
    scanForContentAnnotation(element, context);
}


void XSchemaAny::validateAfterRead(QDomElement & /*node*/, void * /*context*/)
{
    /* TODO
    }*/
}


// parking zone -------------------------------------------------------------



XSchemaAll::XSchemaAll(XSchemaObject *newParent, XSchemaRoot *newRoot) : XSchemaObject(newParent, newRoot)
{
    //TODO: check
    _maxOccursOne.defaultValue = 0 ;
    // max:1
    _minOccurs .defaultValue = 1 ;
}

XSchemaAll::~XSchemaAll()
{
    reset();
}

void XSchemaAll::reset()
{
}

bool XSchemaAll::generateDom(QDomDocument &/*document*/, QDomNode &/*parent*/)
{
    XsdError("TODO");
    return false;
}

void XSchemaAll::loadFromDom(QDomElement &element)
{
    XScanContext context ;
    scanDom(element, &context);
}

void XSchemaAll::scanForAttributes(QDomAttr &attribute, void * /*context*/)
{
    QString name = attribute.nodeName();

    if(name == IO_GENERIC_ID) {
        _id = attribute.value() ;
    } else if(name == IO_GENERIC_MINOCCURS) {
        if(!_minOccurs.setValueFromAttribute(attribute.value())) {
            raiseError(this, attribute, false);
        }
    } else if(name == IO_GENERIC_MAXOCCURS) {
        if(!_maxOccursOne.setValueFromAttribute(attribute.value())) {
            raiseError(this, attribute, false);
        }
    } else {
        if(!readOtherAttributes(attribute)) {
            raiseError(this, attribute, false);
        }
    }
}

void XSchemaAll::scanForElements(QDomElement &element, void * /*context*/)
{
    //XScanContext *theContext = (XScanContext*) context;
    QString name = element.localName();
    if(element.prefix() == _root->namespacePrefix()) {
        if(name == IO_XSD_ANNOTATION) {
            readHandleObject(element, new XSchemaAnnotation(this, _root));
            return;
        } else if((name == IO_XSD_TAGELEMENT)) {
            readHandleObject(element, new XSchemaElement(this, _root));
            return;
        }
    }
    raiseError(this, element, true);
}


//--------------------- class XSchemaAnyAttribute -------------------------------

XSchemaAnyAttribute::XSchemaAnyAttribute(XSchemaObject *newParent, XSchemaRoot *newRoot): XSchemaObject(newParent, newRoot)
{

}

XSchemaAnyAttribute::~XSchemaAnyAttribute()
{
    reset();
}

void XSchemaAnyAttribute::reset()
{
    XSchemaObject::reset();
}

// ---------- load

void XSchemaAnyAttribute::loadFromDom(QDomElement &elementToExamine)
{
    XScanContext context ;
    scanDom(elementToExamine, &context);
}

void XSchemaAnyAttribute::scanForAttributes(QDomAttr &attribute, void * /*context*/)
{
    QString name = attribute.nodeName();

    if(name == IO_GENERIC_ID) {
        _id = attribute.value() ;
    } else if(name == IO_GENERIC_NAMESPACE) {
        _namespaces  = attribute.value().split(" ") ; //(##any,##local,##other,...)
    } else if(name == IO_GENERIC_ATTR_PROCESSCONTENTS) {
        _processContent = decodeProcessContents(attribute.value());
    } else {
        if(!readOtherAttributes(attribute)) {
            raiseError(this, attribute, false);
        }
    }
}

void XSchemaAnyAttribute::scanForElements(QDomElement &element, void * context)
{
    scanForContentAnnotation(element, context);
}


bool XSchemaAnyAttribute::generateDom(QDomDocument &document, QDomNode &parentNode)
{
    QDomElement element = createElement(document, IO_XSD_ANYATTRIBUTE);
    addAttrNotEmpty(element, IO_GENERIC_ID, _id);
    addAttrNotEmpty(element, IO_GENERIC_NAMESPACE, _namespaces.join(" ").trimmed());
    addAttrNotEmpty(element, IO_GENERIC_ATTR_PROCESSCONTENTS, processContentstoString(_processContent));
    addOtherAttributesToDom(element);
    if(NULL != _annotation) {
        _annotation->generateDom(document, element);
    }
    parentNode.appendChild(element);
    return true;
}

//-------------------- class XSchemaAttributeGroup ----------------------

XSchemaAttributeGroup::XSchemaAttributeGroup(XSchemaObject *newParent, XSchemaRoot *newRoot): XSchemaObject(newParent, newRoot)
{

}

XSchemaAttributeGroup::~XSchemaAttributeGroup()
{
    reset();
}

void XSchemaAttributeGroup::reset()
{
    XSchemaObject::reset();
}


// ---------- load

void XSchemaAttributeGroup::loadFromDom(QDomElement &elementToExamine)
{
    XScanContext context ;
    scanDom(elementToExamine, &context);
}

void XSchemaAttributeGroup::scanForAttributes(QDomAttr &attribute, void * /*context*/)
{
    QString name = attribute.nodeName();

    if(name == IO_GENERIC_ID) {
        _id = attribute.value() ;
    } else if(name == IO_GENERIC_REF) {
        _ref  = attribute.value() ;
    } else if(name == IO_GENERIC_NAME) {
        _name  = attribute.value() ;
    } else {
        if(!readOtherAttributes(attribute)) {
            raiseError(this, attribute, false);
        }
    }
}

void XSchemaAttributeGroup::scanForElements(QDomElement &element, void * context)
{
    XScanContext *theContext = (XScanContext*) context;
    QString name = element.localName();
    if(element.prefix() == _root->namespacePrefix()) {
        if(name == IO_XSD_ANNOTATION) {
            readHandleAnnotation(element);
            return;
        } else if((name == IO_XSD_ATTRIBUTE)) {
            readHandleObject(element, new XSchemaAttribute(this, _root));
            return;
        } else if(name == IO_XSD_ATTRIBUTEGROUP) {
            readHandleObject(element, new XSchemaAttributeGroup(this, _root));
        } else if(name == IO_XSD_ANYATTRIBUTE) {
            if(theContext->childFound) {
                raiseError(this, element, true);
            }
            readHandleObject(element, new XSchemaAnyAttribute(this, _root));
            theContext->childFound = true ;
            return;
        }
    }
    raiseError(this, element, true);
}


bool XSchemaAttributeGroup::generateDom(QDomDocument &document, QDomNode &parentNode)
{
    QDomElement element = createElement(document, IO_XSD_ATTRIBUTEGROUP);
    addAttrNotEmpty(element, IO_GENERIC_ID, _id);
    addAttrNotEmpty(element, IO_GENERIC_REF, _ref);
    addAttrNotEmpty(element, IO_GENERIC_NAME, _name);
    addOtherAttributesToDom(element);
    if(NULL != _annotation) {
        _annotation->generateDom(document, element);
    }
    if(!generateInnerDom(document, parentNode)) {
        return false;
    }
    parentNode.appendChild(element);
    return true;
}

//---------- utlities -------------------

XOccurrence::XOccurrence()
{
    isSet = false ;
    occurrences = 1 ;
    isUnbounded = false ;
    defaultValue = 1 ;
}

XOccurrence::XOccurrence(const XOccurrence &ref)
{
    isSet = ref.isSet ;
    occurrences = ref.occurrences;
    isUnbounded = ref.isUnbounded;
    defaultValue = ref.defaultValue ;
}


XOccurrence::~XOccurrence()
{

}

void XOccurrence::addAttrToNode(QDomElement &element, const QString &attributeName)
{
    if(isSet) {
        if(isUnbounded) {
            element.setAttribute(attributeName, IO_GENERIC_UNBOUNDED);
            return ;
        }
        element.setAttribute(attributeName, QString().setNum(occurrences));
    }
}

QString XOccurrence::toString()
{
    if(isSet) {
        if(isUnbounded) {
            return IO_GENERIC_UNBOUNDED ;
        }
        return QString().setNum(occurrences) ;
    }
    return QString("");
}

bool XOccurrence::setValueFromAttribute(const QString &attributeValue)
{
    isSet = true ;
    if(IO_GENERIC_UNBOUNDED == attributeValue) {
        isUnbounded = true ;
        occurrences = std::numeric_limits<int>::max() ;
        return true;
    } else {
        bool isOk = false ;
        occurrences = attributeValue.toUInt(&isOk);
        //TODO: check for minimum value if a limit is set (e.g.: minOccurs in <all
        if(isOk) {
            return true;
        }
    }
    return false;
}
