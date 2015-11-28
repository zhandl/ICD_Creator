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

/**
  Condizioni:
  Figli  Attributi
  ---------------
   No  | No    : SimpleType
   No  | si    : ComplexType SimpleContent
   Si  | No    : Complex Type Complex Content
   Si  | Si    : Complex Type Complex Content


  */
#include "xsdeditor/xschema.h"
#include "xsdeditor/xsddefinitions.h"
#include "xsdeditor/XSchemaIOContants.h"
#include "utils.h"

XSchemaElement::XSchemaElement(XSchemaObject *newParent, XSchemaRoot *newRoot, const ElementCategory category) : XSchemaObject(newParent, newRoot)
{
    _elementCategory = category ;
    _maxOccurs.defaultValue = 1 ;
    _minOccurs.defaultValue = 1 ;
    _abstract = XEnums::XBOOL_FALSE ;
    _nillable = XEnums::XBOOL_TRUE ;
    _mixed = XEnums::XBOOL_FALSE;
    _isTypeOrElement = false ;
    _annotation = NULL ;
    _innerAnnotation = NULL ;
}

XSchemaElement::~XSchemaElement()
{
    if(_innerAnnotation) {
        delete _innerAnnotation ;
        _innerAnnotation = NULL ;
    }
    reset();
}


bool XSchemaElement::isTypeOrElement()
{
    return _isTypeOrElement ;
}

bool XSchemaElement::canAddAttribute()
{
    switch(category()) {
    case EES_SIMPLETYPE_WITHATTRIBUTES:
    case EES_COMPLEX_DERIVED:
    case EES_COMPLEX_DEFINITION:
        return true ;
    default:
        return false ;
    }
}

bool XSchemaElement::canAddSequence()
{
    if(category() == EES_COMPLEX_DEFINITION) {
        return true ;
    }
    return false ;
}

bool XSchemaElement::canAddChoice()
{
    if(category() == EES_COMPLEX_DEFINITION) {
        return true ;
    }
    return false ;
}

bool XSchemaElement::canAddRestriction()
{
    switch(_elementCategory) {
    default:
        return false;

    case EES_SIMPLETYPE_ONLY:
    case EES_SIMPLETYPE_WITHATTRIBUTES:
    case EES_COMPLEX_DERIVED:
        return true ; //TODO !hasChild();
    }
}


XSchemaElement::ElementCategory XSchemaElement::category()
{
    return _elementCategory ;
}

/**
  does a content transformation to set it cohererent with desired setting
  */
void XSchemaElement::setCategory(const XSchemaElement::ElementCategory newCategory)
{
    if(newCategory == _elementCategory) {
        return ;
    }
    _elementCategory = newCategory ;
    switch(_elementCategory) {
    default:
        XsdError("TODO bad type (3)");
    case EES_REFERENCE:
        reset();
        break;
    case EES_SIMPLETYPE_ONLY:
        reset();
        break;
    case EES_SIMPLETYPE_WITHATTRIBUTES:
        XSchemaObject::reset();
        break;
    case EES_COMPLEX_DERIVED:
        //TODO: elimina i figli non coerenti
        XSchemaObject::reset();
        break;
    case EES_COMPLEX_DEFINITION:
        //TODO: elimina i figli non coerenti
        break;
    }
    emit propertyChanged(PROPERTY_ELEMENT_CATEGORY);
}

XReferenceType XSchemaElement::referencedObjectType()
{
    if(EES_REFERENCE == _elementCategory) {
        if(isTypeOrElement()) {
            return XRT_TYPE;
        } else {
            return XRT_ELEMENT;
        }
    }
    return XRT_NONE ;
}

QString XSchemaElement::referencedObjectName()
{
    return _ref ;
}

QString XSchemaElement::occurrencesDescr()
{
    QString occurrences ;
    if((_minOccurs.isSet) && (_maxOccurs.isSet)) {
        occurrences = QString("%1 .. %2").arg(_minOccurs.toString()).arg(_maxOccurs.toString());
    } else if(_minOccurs.isSet) {
        occurrences = QString("%1 .. ").arg(_minOccurs.toString());
    } else if(_maxOccurs.isSet) {
        occurrences = QString(" .. %1").arg(_maxOccurs.toString());
    }
    return occurrences;
}

QString XSchemaElement::nameDescr()
{
    QString ownName ;
    if(_parent->getType() == SchemaTypeSchema) {
        ownName = name();
    }

    QString result ;
    switch(_elementCategory) {
    default:
        XsdError("TODO bad type (3)");
    case EES_EMPTY:
        result = name();
        break;
    case EES_REFERENCE:
        if(!ownName.isEmpty()) {
            result = QString(tr("%1 Reference to %1")).arg(name()).arg(_ref);
        } else {
            result = QString(tr("Reference to %1")).arg(_ref);
        }
        break;
    case EES_SIMPLETYPE_ONLY:
    case EES_SIMPLETYPE_WITHATTRIBUTES: {
        result = name();
        break;
        case EES_COMPLEX_DERIVED:
            result = name();
            break;
        case EES_COMPLEX_DEFINITION:
            result = name();
            break;
        }
    }
    return result;
}

QString XSchemaElement::simpleComplexDescr()
{
    QString result ;
    switch(_elementCategory) {
    default:
        XsdError("TODO bad type (3)");

    case EES_EMPTY:
    case EES_REFERENCE:
        break;
    case EES_SIMPLETYPE_ONLY:
    case EES_SIMPLETYPE_WITHATTRIBUTES:
        result = QString(tr("simple"));
        break;
    case EES_COMPLEX_DERIVED:
        result = QString(tr("complex"));
        break;
    case EES_COMPLEX_DEFINITION:
        result = QString(tr("complex"));
        break;
    }
    return result;
}

QString XSchemaElement::description()
{
    QString occurrences ;
    if((_minOccurs.isSet) && (_maxOccurs.isSet)) {
        occurrences = QString("%1 .. %2").arg(_minOccurs.toString()).arg(_maxOccurs.toString());
    } else if(_minOccurs.isSet) {
        occurrences = QString("%1 .. ").arg(_minOccurs.toString());
    } else if(_maxOccurs.isSet) {
        occurrences = QString(" .. %1").arg(_maxOccurs.toString());
    }

    QString ownName ;
    if(_parent->getType() == SchemaTypeSchema) {
        ownName = name();
    }
    QString result ;
    switch(_elementCategory) {
    default:
        XsdError("TODO bad type (3)");
    case EES_EMPTY :
        if(!ownName.isEmpty()) {
            result = QString(tr("'%1' simple")).arg(name());
        } else {
            result = QString(tr("simple"));
        }
        break;

    case EES_REFERENCE:
        if(_isTypeOrElement) {
            result = QString(tr("Reference to %1")).arg(_ref);
        } else {
            result = QString(tr("Reference to %1")).arg(_ref);
        }
        break;
    case EES_SIMPLETYPE_ONLY:
    case EES_SIMPLETYPE_WITHATTRIBUTES:
        if(!ownName.isEmpty()) {
            result = QString(tr("'%1' simple")).arg(name());
        } else {
            result = QString(tr("simple"));
        }
        break;
    case EES_COMPLEX_DERIVED:
        if(!ownName.isEmpty()) {
            result = QString(tr("'%1' complex")).arg(name());
        } else {
            result = QString(tr("complex"));
        }
        break;
    case EES_COMPLEX_DEFINITION:
        if(!ownName.isEmpty()) {
            result = QString(tr("'%1' complex")).arg(name());
        } else {
            result = QString(tr("complex"));
        }
        break;
    }
    if(!xsdType().isEmpty()) {
        result.append(" (");
        result.append(_xsdType);
        result.append(")");
    }
    if(!occurrences.isEmpty()) {
        result.append("\n");
        result += occurrences ;
    }
    return result ;
}


void XSchemaElement::reset()
{
    XSchemaObject::reset();
    resetAttributes();
}

void XSchemaElement::resetAttributes()
{
    foreach(XSchemaAttribute * attribute, _attributes) {
        delete attribute;
    }
    _attributes.clear();
}

XSchemaAttribute* XSchemaElement::addAttribute()
{
    XSchemaAttribute* attribute = new XSchemaAttribute(this, _root);
    if(NULL != attribute) {
        _attributes.append(attribute);
        emit childAdded(attribute);
    }
    return attribute ;
}

XSchemaElement* XSchemaElement::addElement()
{
    return realAddElement();
}


XSchemaChoice* XSchemaElement::addChoice()
{
    return realAddChoice();
}

XSchemaSequence* XSchemaElement::addSequence()
{
    return realAddSequence();
}

XSchemaObject* XSchemaElement::addRestriction()
{
    switch(_elementCategory) {
    default:
        return NULL;

    case EES_SIMPLETYPE_ONLY:
    case EES_SIMPLETYPE_WITHATTRIBUTES:
        return realAddSimpleTypeRestriction();
    case EES_COMPLEX_DERIVED:
        XsdError("TODO");
        //return realAddComplexTypeRestriction();
        return NULL;
    }
}

bool XSchemaElement::generateDom(QDomDocument &document, QDomNode &parent)
{
    QDomElement node ;
    if(!_isTypeOrElement) {
        node = createElement(document, IO_XSD_TAGELEMENT);
        // attribute evaluation
    }
    QDomElement typeSpecifier ;
    switch(category()) {
    default:
        XsdError("TODO bad type (2)");

    case EES_EMPTY:
        break;
    case EES_REFERENCE:
        if(!ref().isEmpty()) {
            if(_isTypeOrElement) {
                XsdError("type with reference set "); //TODO
            }
            node.setAttribute(IO_ELEMENT_ATTR_REF, ref());
        }
        break;
    case EES_SIMPLETYPE_ONLY:
        typeSpecifier = createElement(document, IO_XSD_SIMPLETYPE);
        writeHandleSimpleType(document, typeSpecifier);
        break;
    case EES_SIMPLETYPE_WITHATTRIBUTES:
        typeSpecifier = createElement(document, IO_XSD_SIMPLETYPE);
        writeHandleComplexType(document, typeSpecifier);
        break;
    case EES_COMPLEX_DERIVED:
        typeSpecifier = createElement(document, IO_XSD_COMPLEXTYPE);
        writeHandleComplexType(document, typeSpecifier);
        break;
    case EES_COMPLEX_DEFINITION:
        typeSpecifier = createElement(document, IO_XSD_COMPLEXTYPE);
        writeHandleComplexType(document, typeSpecifier);
        break;
    }
    if(_isTypeOrElement) {
        parent.appendChild(typeSpecifier);
    } else {
        if(NULL != _annotation) {
            _annotation->generateDom(document, node);
        }
        if(!typeSpecifier.isNull()) {
            node.appendChild(typeSpecifier);
        }
        writeAppendElementAttributes(document, node);
        parent.appendChild(node);
    }
    return true ;
}

void XSchemaElement::writeHandleSimpleType(QDomDocument &document, QDomElement &typeSpecifier)
{
    // handles type attributes
    //TODO
    if(!_isTypeOrElement) {
        addAttrNotEmpty(typeSpecifier, IO_SIMPLETYPE_ATTR_ID, _containedId);
    } else {
        addAttrNotEmpty(typeSpecifier, IO_SIMPLETYPE_ATTR_ID, id());
        addAttrNotEmpty(typeSpecifier, IO_SIMPLETYPE_ATTR_NAME, name());
        //TODOaddAttrNotEmpty( typeSpecifier, IO_SIMPLETYPE_ATTR_FINAL, final() );
    }
    //TODO: any other attrs _innerTypeAttributes
    if(_isTypeOrElement) {
        if(NULL != _annotation) {
            _annotation->generateDom(document, typeSpecifier);
        }
    } else {
        if(NULL != _innerAnnotation) {
            _innerAnnotation->generateDom(document, typeSpecifier);
        }
    }
    foreach(XSchemaObject * child, _children) {
        child->generateDom(document, typeSpecifier);
    }
}

void XSchemaElement::writeHandleComplexType(QDomDocument &document, QDomElement &typeSpecifier)
{
    // handles type attributes
    //TODO LOOK FOR PROPERTIES PARENT DEPENDENT
    addAttrNotEmpty(typeSpecifier, IO_COMPLEXTYPE_ATTR_ABSTRACT, XEnums::boolToString(abstract()));
    //TODO addAttrNotEmpty(typeSpecifier, IO_COMPLEXTYPE_ATTR_BLOCK, block() );
    //TODO addAttrNotEmpty(typeSpecifier, IO_COMPLEXTYPE_ATTR_FINAL, final() );
    addAttrNotEmpty(typeSpecifier, IO_COMPLEXTYPE_ATTR_ID, id());  // TODO: innerid?
    addAttrNotEmpty(typeSpecifier, IO_GENERIC_MIXED, XEnums::boolToString(mixed()));
    if(_isTypeOrElement) {
        addAttrNotEmpty(typeSpecifier, IO_GENERIC_NAME, name());
    }
    addOtherAttributesToDom(typeSpecifier);

    writeAppendNotAttributes(document, typeSpecifier);

    writeAppendAttributes(document, typeSpecifier);
}

void XSchemaElement::writeAppendElementAttributes(QDomDocument &/*document*/, QDomElement &node)
{
    //TODO
    //addAttributeIfNotEmpty();
    /*TODO
    if( !id().isEmpty() ) {
        node.setAttribute( "id", id() );
    }*//*
TODO: apply specific rules
*/
    addAttrNotEmpty(node, IO_ELEMENT_ATTR_NAME, name());
    addAttrNotEmpty(node, IO_ELEMENT_ATTR_ID, id());
    addAttrNotEmpty(node, IO_ELEMENT_ATTR_TYPE, xsdType());
    addAttrNotEmpty(node, IO_ELEMENT_ATTR_REF, ref());

    addAttrNotEmpty(node, IO_ELEMENT_ATTR_ABSTRACT, XEnums::boolToString(abstract()));
    //TODO block = (#all | List of (extension | restriction | substitution))
    addAttrNotEmpty(node, IO_ELEMENT_ATTR_DEFAULT, defaultValue());
    //TODO final = (#all | List of (extension | restriction))
    addAttrNotEmpty(node, IO_ELEMENT_ATTR_FIXED, fixed());
    //TODO form = (qualified | unqualified)
    _minOccurs.addAttrToNode(node, IO_GENERIC_MINOCCURS);
    _maxOccurs.addAttrToNode(node, IO_GENERIC_MAXOCCURS);
    addAttrNotEmpty(node, IO_ELEMENT_ATTR_NILLABLE, XEnums::boolToString(nillable()));
    //  substitutionGroup = QName
    addOtherAttributesToDom(node);
}

void XSchemaElement::writeAppendAttributes(QDomDocument &document, QDomElement &node)
{
    // attributes (attribute|attributeGroup)*,anyAttribute?
    foreach(XSchemaObject * child, _children) {
        if(child->getType() == SchemaTypeAttribute) {
            QDomElement elmentAttr = createElement(document, IO_XSD_ATTRIBUTE);
            //TODO: fill attributes in their own class
            node.appendChild(elmentAttr);

        }
    }
}

void XSchemaElement::writeAppendNotAttributes(QDomDocument &document, QDomElement &node)
{
    foreach(XSchemaObject * child, _children) {
        if(child->getType() != SchemaTypeAttribute) {
            child->generateDom(document, node);
        }
    }
}

//----------------------- accessors -----------------
/*
bool XSchemaElement::abstract()
{
    return _abstract ;
}

void XSchemaElement::setAbstract(bool newAbstract)
{
    if( _abstract != newAbstract ) {
        _abstract = newAbstract ;
        emit abstractChanged(_abstract);
    }
}
*/

IMPL_QPROP(XEnums::XBool, XSchemaElement, abstract, setAbstract, PROPERTY_ELEMENT_ABSTRACT);
IMPL_QPROP(XEnums::XBool, XSchemaElement, nillable, setNillable, PROPERTY_ELEMENT_NILLABLE);
IMPL_QPROP(XEnums::XBool, XSchemaElement, mixed, setMixed, PROPERTY_ELEMENT_MIXED);
IMPL_QPROPS(XSchemaElement, fixed, setFixed, PROPERTY_ELEMENT_FIXED);
IMPL_QPROPS(XSchemaElement, defaultValue, setDefaultValue, PROPERTY_ELEMENT_DEFAULTVALUE);
// TODO IMPL_QPROP(XOccurrence,XSchemaElement,maxOccurs,setMaxOccurs,PROPERTY_ELEMENT_MAXOCCURS);
// TODO IMPL_QPROP(XOccurrence,XSchemaElement,minOccurs,setMinOccurs,PROPERTY_ELEMENT_MINOCCURS);
//TODO IMPL_QPROP(XSchemaElement::EFinalType, XSchemaElement, final, setFinal, PROPERTY_ELEMENT_FINAL);
//TODO IMPL_QPROP(XSchemaElement::EFinalType, XSchemaElement, block, setBlock, PROPERTY_ELEMENT_BLOCK);
IMPL_QPROPS(XSchemaElement, xsdType, setXsdType, PROPERTY_ELEMENT_TYPE);
IMPL_QPROPS(XSchemaElement, ref, setRef, PROPERTY_ELEMENT_REF);
#if 0

IMPL_QPROPS(XSchemaElement, substitutionGroup, setSubstitutionGroup, PROPERTY_ELEMENT_SUBSTITUTIONGROUP);

#endif


bool XSchemaElement::isSimpleType()
{
    return (_elementCategory == EES_SIMPLETYPE_ONLY);
}

void XSchemaElement::loadFromDom(QDomElement &element)
{
    reset();
    bool isComplexType = false;
    bool isSimpleType = false;
    //TODO: manca il set del tipo interno
    if(element.localName() == IO_XSD_COMPLEXTYPE) {
        _isTypeOrElement = true ;
        isComplexType = true ;
        readHandleComplexType(element);
        // TODO: chiarire attributi
        return ;
    } else if(element.localName() == IO_XSD_SIMPLETYPE) {
        _isTypeOrElement = true ;
        isSimpleType = true ;
        readHandleSimpleType(element);
        // TODO: chiarire attributi
        return ;
    } else {
        _isTypeOrElement = false ;
    }
// TODO : category
    QDomNamedNodeMap attributes = element.attributes();
    int numAttrs = attributes.length();
    for(int i = 0 ; i < numAttrs ; i++) {
        QDomNode node = attributes.item(i);
        QDomAttr attr = node.toAttr();
        QString name = node.nodeName();

        /*if( isComplexType ) { TODO: check if fully handled separately
            if( name == IO_COMPLEXTYPE_ATTR_ABSTRACT ) {
                //TODO abstract = "false"
            } else if( name == IO_COMPLEXTYPE_ATTR_BLOCK ) {
              //TODO block = "#all"
            } else if( name == IO_COMPLEXTYPE_ATTR_FINAL ) {
              //TODO final = "#all"
            } else if( name == IO_COMPLEXTYPE_ATTR_ID ) {
              _id = attr.value();
            } else if( name == IO_COMPLEXTYPE_ATTR_MIXED ) {
              //TODO mixed = "false"
            } else if( name == IO_GENERIC_NAME ) {
              _name = attr.value();
             } else {
                 if( !readOtherAttributes(attr) ) {
                     raiseError( this, attr, false );
                 }
             }*/
        /*} TODO: DELETE else if( isSimpleType ) { TODO: check if fully handled separately
             if( name == IO_SIMPLETYPE_ATTR_FINAL ) {
               //TODO final = "#all"
             } else if( name == IO_SIMPLETYPE_ATTR_ID ) {
               _id = attr.value();
             } else if( name == IO_SIMPLETYPE_ATTR_NAME ) {
               _name = attr.value();
              } else {
                  if( !readOtherAttributes(attr) ) {
                      raiseError( this, attr, false );
                  }
              }*/
        /*if(!_isTypeOrElement) {*/
        if(name == IO_ELEMENT_ATTR_ID) {
            _id = attr.value() ;
        } else if(name == IO_ELEMENT_ATTR_NAME) {
            _name = attr.value() ;
        } else if(name == IO_ELEMENT_ATTR_REF) {
            _ref = attr.value();
        } else if(name == IO_ELEMENT_ATTR_TYPE) {
            _xsdType = attr.value();
        } else if(name == IO_ELEMENT_ATTR_SUBSTGROUP) {
            //TODO
        } else if(name == IO_ELEMENT_ATTR_DEFAULT) {
            _defaultValue = attr.value();
        } else if(name == IO_ELEMENT_ATTR_FIXED) {
            _fixed = attr.value();
        } else if(name == IO_ELEMENT_ATTR_FORM) {
            //TODO
        } else if(name == IO_ELEMENT_ATTR_MAXOCCURS) {
            if(!_maxOccurs.setValueFromAttribute(attr.value())) {
                raiseError(this, attr, false);
            }
        } else if(name == IO_ELEMENT_ATTR_MINOCCURS) {
            if(!_minOccurs.setValueFromAttribute(attr.value())) {
                raiseError(this, attr, false);
            }
        } else if(name == IO_ELEMENT_ATTR_NILLABLE) {
            _nillable = XEnums::parseBool(attr.value());
        } else if(name == IO_ELEMENT_ATTR_ABSTRACT) {
            _abstract = XEnums::parseBool(attr.value());
        } else if(name == IO_ELEMENT_ATTR_BLOCK) {
            _block = decodeFinalListToString(attr.value());
        } else if(name == IO_ELEMENT_ATTR_FINAL) {
            _final = decodeFinalListToString(attr.value());
        } else {
            if(!readOtherAttributes(attr)) {
                raiseError(this, attr, false);
            }
        }
        /*} // element*/
    }
    if(!_isTypeOrElement && ! _ref.isEmpty()) {
        _elementCategory = EES_REFERENCE ;
    }

    QString namespacePrefix = _root->namespacePrefix();
    int nodi = element.childNodes().count();
    for(int i = 0 ; i < nodi ; i ++) {
        QDomNode childNode = element.childNodes().item(i) ;

        if(childNode.isElement()) {
            QDomElement element = childNode.toElement();
            QString name = element.localName();
            if(element.prefix() == namespacePrefix) {
                if(name == IO_XSD_ANNOTATION) {
                    readHandleAnnotation(element, false);
                } else if(name == IO_XSD_SIMPLETYPE) {
                    readHandleSimpleType(element);
                } else if(name == IO_XSD_COMPLEXTYPE) {
                    readHandleComplexType(element);
                } else if(name == IO_XSD_UNIQUE) {
                    readHandleObject(element, new XSchemaUnique(this, _root));
                } else if(name == IO_XSD_KEY) {
                    readHandleObject(element, new XSchemaKey(this, _root));
                } else if(name == IO_XSD_KEYREF) {
                    readHandleObject(element, new XSchemaKeyRef(this, _root));
                } else {
                    raiseError(this, element, true);
                }
            }
        }
    }
}

//TODO la cosa si complica, il validatore w3c permette un id nel simpletype contenuto in un elemento
// la specifica dice altro.

bool XSchemaElement::readHandleSimpleType(QDomElement &element)
{
    bool isOk = true ;
    _elementCategory = EES_SIMPLETYPE_ONLY ;
    QDomNamedNodeMap attributes = element.attributes();
    int numAttrs = attributes.length();
    for(int i = 0 ; i < numAttrs ; i++) {
        QDomNode node = attributes.item(i);
        QDomAttr attr = node.toAttr();
        QString name = node.nodeName();

        if(name == IO_SIMPLETYPE_ATTR_ID) {
            if(_isTypeOrElement) {
                _id = attr.value() ;
            } else {
                _containedId = attr.value() ;
            }
        } else if(name == IO_SIMPLETYPE_ATTR_NAME) {
            if(_isTypeOrElement) {
                _name = attr.value() ;
            }
        } else if(name == IO_SIMPLETYPE_ATTR_FINAL) {
            Utils::error("_final = readFinalAttribute(attr.value());");
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

        bool childFound = false;
        if(childNode.isElement()) {
            QDomElement element = childNode.toElement();
            QString localName = element.localName();
            if(element.prefix() == namespacePrefix) {
                if(localName == IO_XSD_ANNOTATION) {
                    readHandleAnnotation(element, !_isTypeOrElement);
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

bool XSchemaElement::readHandleComplexType(QDomElement &element1)
{
    bool isOk = true ;
    _elementCategory = EES_COMPLEX_DEFINITION ;
    QDomNamedNodeMap attributes = element1.attributes();
    int numAttrs = attributes.length();
    for(int i = 0 ; i < numAttrs ; i++) {
        QDomNode node = attributes.item(i);
        QDomAttr attr = node.toAttr();
        QString name = node.nodeName();

        if((name == IO_GENERIC_ID)) {
            if(_isTypeOrElement) {
                _id = attr.value() ;
            } else {
                _containedId = attr.value() ;
            }
        } else if((name == IO_GENERIC_NAME) && _isTypeOrElement) {
            _name = attr.value() ;
        } else if(name == IO_COMPLEXTYPE_ATTR_ABSTRACT) {
            _abstract = XEnums::parseBool(attr.value());
        } else if(name == IO_COMPLEXTYPE_ATTR_BLOCK) {
            Utils::error("_block = readFinalAttribute(attr.value());");
        } else if(name == IO_COMPLEXTYPE_ATTR_FINAL) {
            Utils::error("_final = readFinalAttribute(attr.value());");
        } else if(name == IO_COMPLEXTYPE_ATTR_ID) {
            _id = attr.value();
        } else if(name == IO_GENERIC_MIXED) {
            _mixed = XEnums::parseBool(attr.value());
        } else {
            if(!readOtherAttributes(attr)) {
                raiseError(this, attr, false);
            }
        }
    }

    QString namespacePrefix = _root->namespacePrefix();
    int nodi = element1.childNodes().count();
    for(int i = 0 ; i < nodi ; i ++) {
        QDomNode childNode = element1.childNodes().item(i) ;

        bool childFound = false;
        if(childNode.isElement()) {
            QDomElement childElement = childNode.toElement();
            QString localName = childElement.localName();
            if(childElement.prefix() == namespacePrefix) {
                if(localName == IO_XSD_ANNOTATION) {
                    readHandleAnnotation(childElement, !_isTypeOrElement);
                } else if(localName == IO_XSD_SIMPLECONTENT) {
                    if(childFound) {
                        raiseError(this, childNode, true);
                    }
                    XSchemaSimpleContent *newObject = readSimpleContentChild(childElement);
                    if(NULL == newObject) {
                        raiseErrorForObject(childElement);
                    }
                    addChild(newObject);
                    childFound = true ;
                } else if(localName == IO_XSD_COMPLEXCONTENT) {
                    //TODO
                    if(childFound) {
                        raiseError(this, childNode, true);
                    }
                    XSchemaComplexContent *newObject = readComplexContentChild(childElement);
                    if(NULL == newObject) {
                        raiseErrorForObject(childElement);
                    }
                    addChild(newObject);
                    childFound = true ;
//---------------------- one at max ---------------------
                } else if(localName == IO_XSD_GROUP) {
                    if(childFound) {
                        raiseError(this, childNode, true);
                    }
                    readHandleObject(childElement, new XSchemaGroup(this, _root));
                    childFound = true ;
                } else if(localName == IO_XSD_ALL) {
                    if(childFound) {
                        raiseError(this, childNode, true);
                    }
                    readHandleObject(childElement, new XSchemaAll(this, _root));
                    childFound = true ;
                } else if(localName == IO_XSD_CHOICE) {
                    if(childFound) {
                        raiseError(this, childNode, true);
                    }
                    readHandleObject(childElement, new XSchemaChoice(this, _root));
                    childFound = true ;
                } else if(localName == IO_XSD_SEQUENCE) {
                    //TODO
                    if(childFound) {
                        raiseError(this, childNode, true);
                    }
                    // TODO: look ahead to find the type of
                    readHandleObject(childElement, new XSchemaSequence(this, _root));
                    childFound = true ;
//---------------------- any number ---------------------
                } else if(localName == IO_XSD_ATTRIBUTE) {
                    // TODO: attributes!
                    XSchemaAttribute* attribute = new XSchemaAttribute(this, _root);
                    if(NULL == attribute) {
                        raiseErrorForObject(childElement);
                    }
                    _attributes.append(attribute);
                    attribute->loadFromDom(childElement);
                } else if(localName == IO_XSD_ATTRIBUTEGROUP) {
                    //TODO
                    readHandleObject(childElement, new XSchemaAttributeGroup(this, _root));
                } else if(localName == IO_XSD_ANYATTRIBUTE) {
                    if(childFound) {
                        raiseError(this, childNode, true);
                    }
                    // TODO: look ahead to foind the type of
                    readHandleObject(childElement, new XSchemaAnyAttribute(this, _root));
                    childFound = true ;
                }
            } else {
                raiseError(this, childNode, true);
            }
        }
    }
    validateComplexType(element1, !_isTypeOrElement);
    return isOk;
}

bool XSchemaElement::isExtension()
{
    if(_elementCategory == EES_COMPLEX_DERIVED) {
        if(_children.size() > 0) {
            XSchemaObject *child = _children.at(0);
            if(child->getType() == SchemaTypeComplexContentExtension) {
                return true;
            }
        }
    }
    return false;
}

void XSchemaElement::validateComplexType(QDomElement &/*element*/, const bool /*isInner*/)
{
    //TODO
}

void XSchemaElement::readHandleAnnotation(QDomElement &element, const bool isInner)
{
    if(!isInner) {
        XSchemaObject::readHandleAnnotation(element);
    } else {
        if(NULL != _innerAnnotation) {
            raiseError(this, element, true);
        }
        _innerAnnotation = new XSchemaAnnotation(this, _root) ;
        if(NULL == _innerAnnotation) {
            raiseError(this, element, true);
        }
        _innerAnnotation->loadFromDom(element);
    }
}

XSchemaSimpleContent *XSchemaElement::readSimpleContentChild(QDomElement &element)
{
    XSchemaSimpleContent *newObject = NULL ;
    QString namespacePrefix = _root->namespacePrefix();
    int nodi = element.childNodes().count();
    for(int i = 0 ; i < nodi ; i ++) {
        QDomNode childNode = element.childNodes().item(i) ;
        if(childNode.isElement()) {
            QDomElement childElement = childNode.toElement();
            QString localName = childElement.localName();
            if(childElement.prefix() == namespacePrefix) {
                if(localName == IO_XSD_SIMPLECONTENT_RESTRICTION) {
                    newObject = new XSchemaSimpleContentRestriction(this, _root);
                    newObject->readBaseProperties(element);
                    _elementCategory = EES_SIMPLETYPE_WITHATTRIBUTES ;
                    return newObject ;
                }
                if(localName == IO_XSD_SIMPLECONTENT_EXTENSION) {
                    newObject = new XSchemaSimpleContentExtension(this, _root);
                    newObject->readBaseProperties(element);
                    _elementCategory = EES_SIMPLETYPE_WITHATTRIBUTES ;
                    return newObject ;
                }
            }
        }
    }
    raiseError(this, element, true);
    return NULL;
}


XSchemaComplexContent *XSchemaElement::readComplexContentChild(QDomElement &element)
{
    XSchemaComplexContent *newObject = NULL ;
    QString namespacePrefix = _root->namespacePrefix();
    int nodi = element.childNodes().count();
    for(int i = 0 ; i < nodi ; i ++) {
        QDomNode childNode = element.childNodes().item(i) ;
        if(childNode.isElement()) {
            QDomElement childElement = childNode.toElement();
            QString localName = childElement.localName();
            if(childElement.prefix() == namespacePrefix) {
                if(localName == IO_XSD_COMPLEXCONTENT_RESTRICTION) {
                    newObject = new XSchemaComplexContentRestriction(this, _root);
                    newObject->readBaseProperties(element);
                    _elementCategory = EES_COMPLEX_DERIVED ;
                    return newObject ;
                }
                if(localName == IO_XSD_COMPLEXCONTENT_EXTENSION) {
                    newObject = new XSchemaComplexContentExtension(this, _root);
                    newObject->readBaseProperties(element);
                    _elementCategory = EES_COMPLEX_DERIVED ;
                    return newObject ;
                }
            }
        }
    }
    raiseError(this, element, true);
    return NULL ;
}
//usare unbounded per il display

bool XSchemaElement::hasAReference()
{
    return !_ref.isEmpty();
}

int XSchemaElement::minOccurrences()
{
    return _minOccurs.occurrences;
}

int XSchemaElement::maxOccurrences()
{
    return _maxOccurs.occurrences;
}
