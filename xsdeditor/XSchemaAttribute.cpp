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

XSchemaAttribute::XSchemaAttribute(XSchemaObject *newParent, XSchemaRoot *newRoot)
    : XSchemaObject(newParent, newRoot),
      _use(Missing)
{
}

XSchemaAttribute::~XSchemaAttribute()
{
    reset();
}


void XSchemaAttribute::reset()
{
    XSchemaObject::reset();
}

XReferenceType XSchemaAttribute::referencedObjectType()
{
    if(_ref.isEmpty()) {
        return XRT_NONE;
    } else {
        return XRT_ATTRIBUTE;
    }
}

QString XSchemaAttribute::referencedObjectName()
{
    return _ref ;
}


QString XSchemaAttribute::description()
{
    QString description ;
    if(!_name.isEmpty()) {
        description.append(_name);
    } else if(! _ref.isEmpty()) {
        description.append(tr("ref to "));
        description.append(_ref);
    }
    if(!_xsdType.isEmpty()) {
        description.append("\n");
        description.append(_xsdType);
    }
    if(!_fixed.isEmpty()) {
        description.append("\n");
        description.append(tr("fixed:"));
        description.append(_fixed);
    }
    if(!_defaultValue.isEmpty()) {
        description.append("\n");
        description.append(tr("default:"));
        description.append(_defaultValue);
    }
    if(_use != Missing) {
        description.append(" (");
        description.append(toStringUse(_use));
        description.append(")");
    }
    return description;
}

QString XSchemaAttribute::toStringUse(const EUse theUse)
{
    switch(theUse) {
    default:
        return "" ;
    case Optional:
        return "optional";
    case Prohibited:
        return "prohibited";
    case Required:
        return "required";
    }
}

QString XSchemaAttribute::toStringForSave(const EUse theUse)
{
    switch(theUse) {
    default:
        // note the empty tag: it is essential
        return IO_ATTRIBUTE_USE_MISSING ;
    case Optional:
        return IO_ATTRIBUTE_USE_OPTIONAL;
    case Prohibited:
        return IO_ATTRIBUTE_USE_PROHIBITED;
    case Required:
        return IO_ATTRIBUTE_USE_REQUIRED;
    }
}

bool XSchemaAttribute::hasAReference()
{
    return !_ref.isEmpty();
}

// ---------- save -----------------------------

bool XSchemaAttribute::generateDom(QDomDocument &document, QDomNode &parent)
{
    QDomElement node = createElement(document, IO_XSD_ATTRIBUTE);

    //TODO node.setAttribute( IO_ATTRIBUTE_ATTR_FORM, (EQ_UNQUALIFIED==_attributeFormDefault)? IO_SCHEMA_UNQUALIFIED:IO_SCHEMA_QUALIFIED);
    addAttrNotEmpty(node, IO_GENERIC_NAME, _name);
    addAttrNotEmpty(node, IO_GENERIC_ID, _id);
    addAttrNotEmpty(node, IO_ATTRIBUTE_ATTR_FIXED, _fixed);
    addAttrNotEmpty(node, IO_ATTRIBUTE_ATTR_DEFAULT, _defaultValue);
    addAttrNotEmpty(node, IO_ATTRIBUTE_ATTR_REF, _ref);
    addAttrNotEmpty(node, IO_ATTRIBUTE_ATTR_TYPE, _xsdType);
    addAttrNotEmpty(node, IO_ATTRIBUTE_ATTR_USE, toStringForSave(_use));
    addOtherAttributesToDom(node);
    if(NULL != _annotation) {
        _annotation->generateDom(document, node);
    }

    if(!generateInnerDom(document, node)) {
        return false;
    }
    parent.appendChild(node);
    return true;
}

// ---------- load -----------------------------

void XSchemaAttribute::loadFromDom(QDomElement &elementToExamine)
{
    XScanContext context ;
    scanDom(elementToExamine, &context);
}

void XSchemaAttribute::scanForAttributes(QDomAttr &attribute, void * /*context*/)
{
    QString name = attribute.nodeName();

    if(name == IO_GENERIC_ID) {
        _id = attribute.value() ;
    } else if(name == IO_GENERIC_NAME) {
        _name = attribute.value() ;
    } else if(name == IO_ATTRIBUTE_ATTR_DEFAULT) {
        _defaultValue = attribute.value() ;
    } else if(name == IO_ATTRIBUTE_ATTR_FIXED) {
        _fixed = attribute.value() ;
    } else if(name == IO_ATTRIBUTE_ATTR_FORM) {
        //TODO form
    } else if(name == IO_ATTRIBUTE_ATTR_REF) {
        _ref = attribute.value() ;
    } else if(name == IO_ATTRIBUTE_ATTR_TYPE) {
        _xsdType =  attribute.value() ;
    } else if(name == IO_ATTRIBUTE_ATTR_USE) {
        if(IO_ATTRIBUTE_USE_OPTIONAL == attribute.value()) {
            _use = Optional ;
        } else if(IO_ATTRIBUTE_USE_PROHIBITED == attribute.value()) {
            _use = Prohibited ;
        } else if(IO_ATTRIBUTE_USE_REQUIRED == attribute.value()) {
            _use = Required ;
        } else {
            raiseError(this, attribute, false);
        }
    } else {
        if(!readOtherAttributes(attribute)) {
            raiseError(this, attribute, false);
        }
    }
}

void XSchemaAttribute::scanForElements(QDomElement &element, void *context)
{
    XScanContext *theContext = (XScanContext*) context;
    QString name = element.localName();
    if(element.prefix() == _root->namespacePrefix()) {
        if(name == IO_XSD_ANNOTATION) {
            readHandleAnnotation(element);
        } else if(name == IO_XSD_SIMPLETYPE) {
            if(theContext->childFound) {
                raiseError(this, element, true);
            }
            theContext->childFound = true;
            //readHandleSimpleType(element);
            readHandleObject(element, new XSchemaElement(this, _root));
        } else {
            raiseError(this, element, true);
        }
    } else {
        raiseError(this, element, true);
    }
}


bool XSchemaAttribute::readHandleSimpleType(QDomElement &element)
{
    bool isOk = true ;
    QString namespacePrefix = _root->namespacePrefix();
    int nodi = element.childNodes().count();
    for(int i = 0 ; i < nodi ; i ++) {
        QDomNode childNode = element.childNodes().item(i) ;

        bool childFound = false;
        if(childNode.isElement()) {
            QDomElement element = childNode.toElement();
            QString localName = element.localName();
            if(element.prefix() == namespacePrefix) {
                if(localName == IO_XSD_ANNOTATION) {
                } else if(localName == IO_XSD_RESTRICTION) {
                    if(childFound) {
                        raiseError(this, childNode, true);
                    }
                    childFound = true;
                    readHandleObject(element, new XSchemaSimpleTypeRestriction(this, _root));
                } else if(localName == IO_XSD_LIST) {
                    if(childFound) {
                        raiseError(this, childNode, true);
                    }
                    childFound = true;
                    readHandleObject(element, new XSchemaSimpleTypeList(this, _root));
                } else if(localName == IO_XSD_UNION) {
                    if(childFound) {
                        raiseError(this, childNode, true);
                    }
                    childFound = true;
                    readHandleObject(element, new XSchemaSimpleTypeUnion(this, _root));
                } else {
                    raiseError(this, childNode, true);
                }
            }
        }
    }
    return isOk;
}
