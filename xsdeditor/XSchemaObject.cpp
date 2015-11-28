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

#define PIXMAP_DEFAULT_XSD_OBJECT   ":/xsdimages/base"

const QString XSchemaObject::_xsdXML("http://www.w3.org/XML/1998/namespace");

//--------------------------

XEnums::XEnums()
{
}

XEnums::~XEnums()
{
}

XEnums::XBool XEnums::parseBool(const QString input)
{
    // cfr: 3.2.2.1 Lexical representation
    if(input.isEmpty()) {
        return XBOOL_UNSET;
    }
    if(input == "true") {
        return XBOOL_TRUE ;
    }
    if(input == "1") {
        return XBOOL_TRUE ;
    }
    if(input == "false") {
        return XBOOL_FALSE ;
    }
    if(input == "0") {
        return XBOOL_FALSE ;
    }
    XsdError(QString(tr("Invalid boolean value:%1").arg(input)));
    return XBOOL_UNSET;
}

QString XEnums::boolToString(const XBool value)
{
    // cfr: 3.2.2.2 Canonical representation
    switch(value) {
    case XBOOL_UNSET:
        return "";
    case XBOOL_TRUE:
        return "true";
    case XBOOL_FALSE:
        return "false";
    }
    XsdError(QString(tr("Invalid boolean value:%1").arg(value)));
    return "";
}

/* TODO: delete?
XBool::XBool(const bool newValue)
{
    setValue(newValue);
}

XBool::~XBool()
{
}

bool XBool::value()
{
    return _value ;
}

void XBool::setValue(const bool newValue)
{
    _value = newValue ;
}

*/

//-----------------------------------------------------
QString RestrictionFacets::getFacet(const QString &name, const QString &value)
{
    if(!value.isEmpty()) {
        return QString("\n%1 = %2").arg(name).arg(value);
    } else {
        return "";
    }
}

QString RestrictionFacets::toString()
{
    QString res ;

    res += getFacet(IO_XSD_MINEXCLUSIVE, _minExclusive);
    res += getFacet(IO_XSD_MININCLUSIVE, _minInclusive);
    res += getFacet(IO_XSD_MAXEXCLUSIVE, _maxExclusive);
    res += getFacet(IO_XSD_MAXINCLUSIVE, _maxInclusive);
    res += getFacet(IO_XSD_TOTALDIGITS, _totalDigits);
    res += getFacet(IO_XSD_FRACTIONDIGITS, _fractionDigits);
    res += getFacet(IO_XSD_LENGTH, _length);
    res += getFacet(IO_XSD_MINLENGTH, _minLength);
    res += getFacet(IO_XSD_MAXLENGTH, _maxLength);
    if(!_enumeration.isEmpty()) {
        res += "\nEnumeration:";
        foreach(QString restrictionValue, _enumeration) {
            res += QString("\n  %1").arg(restrictionValue);
        }
    }
    // TODO: WRONG!!!!
    res += getFacet(IO_XSD_WHITESPACE, _whiteSpace);
    res += getFacet(IO_XSD_PATTERN, _pattern);
    return res;
};
/*
void RestrictionFacets::generateFacets(QDomElement &node)
{
    // TODO: factor this (complex type, etc.)
    addFacetIfNotEmpty( node, IO_XSD_MINEXCLUSIVE, _minExclusive );
    addFacetIfNotEmpty( node, IO_XSD_MININCLUSIVE, _minInclusive );
    addFacetIfNotEmpty( node, IO_XSD_MAXEXCLUSIVE, _maxExclusive );
    addFacetIfNotEmpty( node, IO_XSD_MAXINCLUSIVE, _maxInclusive );
    addFacetIfNotEmpty( node, IO_XSD_TOTALDIGITS, _totalDigits );
    addFacetIfNotEmpty( node, IO_XSD_FRACTIONDIGITS, _fractionDigits );
    addFacetIfNotEmpty( node, IO_XSD_LENGTH, _length );
    addFacetIfNotEmpty( node, IO_XSD_MINLENGTH, _minLength );
    addFacetIfNotEmpty( node, IO_XSD_MAXLENGTH, _maxLength );
    foreach( QString restrictionValue, _enumeration ) {
        addFacetIfNotEmpty( node, IO_XSD_ENUMERATION, restrictionValue ); // TODO: WRONG!!!!
    }
    // TODO: WRONG!!!!
    addFacetIfNotEmpty( node, IO_XSD_WHITESPACE, _whiteSpace );
    addFacetIfNotEmpty( node, IO_XSD_PATTERN, _pattern );
}

void RestrictionFacets::addFacetIfNotEmpty(QDomElement &element, const QString &elementTag, const QString &value )
{
    if( !value.isEmpty() ) {
        QDomDocument document = element.ownerDocument();
        QDomElement innerElement = createElement( document, elementTag );
        innerElement.setAttribute( IO_FACET_ATTR_VALUE, value );
        element.appendChild(innerElement);
    }
}
*/
// TODO: sostituire
bool RestrictionFacets::scanForFacets(const QString &name, const QString &value)
{
    if(name == IO_XSD_MINEXCLUSIVE) {
        _minExclusive = value;
        return true;
    } else if(name == IO_XSD_MININCLUSIVE) {
        _minInclusive = value;
        return true;
    } else if(name == IO_XSD_MAXEXCLUSIVE) {
        _maxExclusive = value;
        return true;
    } else if(name == IO_XSD_MAXINCLUSIVE) {
        _maxInclusive = value;
        return true;
    } else if(name == IO_XSD_TOTALDIGITS) {
        _totalDigits = value;
        return true;
    } else if(name == IO_XSD_FRACTIONDIGITS) {
        _fractionDigits = value;
        return true;
    } else if(name == IO_XSD_LENGTH) {
        _length = value;
        return true;
    } else if(name == IO_XSD_MINLENGTH) {
        _minLength = value;
        return true;
    } else if(name == IO_XSD_MAXLENGTH) {
        _maxLength = value;
        return true;
    } else if(name == IO_XSD_ENUMERATION) {   // TODO: WRONG!!!!
        _enumeration.append(value);
        return true;
    } else if(name == IO_XSD_WHITESPACE) {  // TODO: WRONG!!!!
        _whiteSpace = value;
        return true;
    } else if(name == IO_XSD_PATTERN) {
        _pattern = value;
        return true;
    }
    return false;
}

//-----------------------------------------------------

XSchemaObject::XSchemaObject(XSchemaObject *newParent, XSchemaRoot *newRoot)
{
    _parent = newParent;
    _root = newRoot;
    _annotation = NULL;
}

XSchemaObject::~XSchemaObject()
{
    reset();
    _parent = NULL ;
    _root = NULL ;
}

QString XSchemaObject::name()
{
    return _name;
}

QString XSchemaObject::id()
{
    return _id;
}

XSchemaAnnotation *XSchemaObject::annotation()
{
    return _annotation ;
}


void XSchemaObject::deleteObject()
{
    if(NULL != _parent) {
        _parent->deleteChild(this);
    } else {
        reset();
        emit deleted(this);
        delete this;
    }
}

void XSchemaObject::deleteChild(XSchemaObject *theChild)
{
    // theChild must be valid
    int indexOfChild = _children.indexOf(theChild);
    if(indexOfChild >= 0) {
        _children.removeAt(indexOfChild);
        emit childRemoved(theChild);
        delete theChild;
    }
}


void XSchemaObject::setName(const QString &newName)
{
    if(_name != newName) {
        _name = newName ;
        emit nameChanged(_name);
    }
}

void XSchemaObject::setId(const QString &newId)
{
    if(_id != newId) {
        _id = newId ;
        emit idChanged(_id);
    }
}

/* why?
bool XSchemaObject::operator< ( const XSchemaObject & other ) const
{
    QString thisName = _name;
    QString otherName = other._name;
    if( thisName < otherName ) {
        return true ;
    }
    return false;
}
*/

QList<XSchemaObject*> &XSchemaObject::getChildren()
{
    return _children ;
}

void XSchemaObject::reset()
{
    foreach(XSchemaObject * schema, _children) {
        emit childRemoved(schema);
        delete schema;
    }
    _children.clear();
    _otherAttributes.clear();
    if(_annotation) {
        delete _annotation ;
        _annotation = NULL ;
    }
}

bool XSchemaObject::isSimpleType()
{
    return false ;
}

XSchemaObject* XSchemaObject::addChild(XSchemaObject *child)
{
    if(NULL != child) {
        _children.append(child);
    }
    return child ;
}


bool XSchemaObject::canAddElement()
{
    return false ;
}

bool XSchemaObject::canAddAttribute()
{
    return false ;
}

bool XSchemaObject::canAddSequence()
{
    return false ;
}

bool XSchemaObject::canAddChoice()
{
    return false ;
}

bool XSchemaObject::canAddRestriction()
{
    return false ;
}

bool XSchemaObject::canAddExtension()
{
    return false;
}

bool XSchemaObject::canAddUnion()
{
    return false;
}

bool XSchemaObject::canAddList()
{
    return false;
}

bool XSchemaObject::canAddChild(const ESchemaType /*newType*/)
{
    return false;
}

XSchemaElement *XSchemaObject::addElement()
{
    return NULL ;
}

XSchemaAttribute *XSchemaObject::addAttribute()
{
    return NULL ;
}

XSchemaChoice* XSchemaObject::addChoice()
{
    return NULL ;
}

XSchemaSequence* XSchemaObject::addSequence()
{
    return NULL ;
}

XSchemaObject* XSchemaObject::addRestriction()
{
    return NULL ;
}

XSchemaObject* XSchemaObject::addExtension()
{
    return NULL ;
}

XSchemaSimpleTypeUnion* XSchemaObject::addUnion()
{
    return realAddUnion();
}

XSchemaSimpleTypeList* XSchemaObject::addList()
{
    return realAddList() ;
}

XSchemaElement* XSchemaObject::realAddElement()
{
    XSchemaElement* element = new XSchemaElement(this, _root);
    XSchemaObject::addChild(element);
    emit childAdded(element);
    return element ;
}


XSchemaChoice* XSchemaObject::realAddChoice()
{
    XSchemaChoice* choice = new XSchemaChoice(this, _root);
    XSchemaObject::addChild(choice);
    emit childAdded(choice);
    return choice;
}

XSchemaSequence* XSchemaObject::realAddSequence()
{
    XSchemaSequence* sequence = new XSchemaSequence(this, _root);
    XSchemaObject::addChild(sequence);
    emit childAdded(sequence);
    return sequence;
}

XSchemaAttribute* XSchemaObject::realAddAttribute()
{
    XSchemaAttribute* attribute = new XSchemaAttribute(this, _root);
    XSchemaObject::addChild(attribute);
    emit childAdded(attribute);
    return attribute;
}

XSchemaSimpleTypeUnion* XSchemaObject::realAddUnion()
{
    XSchemaSimpleTypeUnion* xunion = new XSchemaSimpleTypeUnion(this, _root);
    XSchemaObject::addChild(xunion);
    emit childAdded(xunion);
    return xunion;
}

XSchemaSimpleTypeList* XSchemaObject::realAddList()
{
    XSchemaSimpleTypeList* list = new XSchemaSimpleTypeList(this, _root);
    XSchemaObject::addChild(list);
    emit childAdded(list);
    return list;
}

XSchemaSimpleTypeRestriction* XSchemaObject::realAddSimpleTypeRestriction()
{
    XSchemaSimpleTypeRestriction* child = new XSchemaSimpleTypeRestriction(this, _root);
    XSchemaObject::addChild(child);
    emit childAdded(child);
    return child ;
}

XReferenceType XSchemaObject::referencedObjectType()
{
    return XRT_NONE;
}

QString XSchemaObject::referencedObjectName()
{
    return "";
}

XSchemaObject *XSchemaObject::xsdParent()
{
    return _parent ;
}

bool XSchemaObject::generateInnerDom(QDomDocument &document, QDomNode &parent)
{
    foreach(XSchemaObject * child, _children) {
        if(!child->generateDom(document, parent)) {
            return false;
        }
    }
    return true ;
}

QString XSchemaObject::description()
{
    return _name + metaObject()->className();
}

QPixmap XSchemaObject::icon()
{
    // TODO: use cache
    QPixmap pixmap ;
    pixmap.load(PIXMAP_DEFAULT_XSD_OBJECT);
    return pixmap ;
}

QColor XSchemaObject::color()
{
    return QColor::fromRgbF(.9, .9, .8, 1) ;
}

bool XSchemaObject::containsSimpleType()
{
    foreach(XSchemaObject * child, _children) {
        switch(child->getType()) {
        case SchemaTypeSimpleTypeRestriction:
        case SchemaTypeSimpleTypeUnion:
        case SchemaTypeSimpleTypeList:
            return true;
        default:
            break;
        }
    }
    return false;
}

QString XSchemaObject::fromFinalTypeToString(const EFinalType fType)
{
    switch(fType) {
    default:
        return "?";
    case FINALTYPE_NONE: return "" ;
    case FINALTYPE_ALL: return FINALTYPE_ALL_STRING;
    case FINALTYPE_RESTRICTION: return FINALTYPE_RESTRICTION_STRING;
    case FINALTYPE_EXTENSION: return FINALTYPE_EXTENSION_STRING;
    case FINALTYPE_LIST: return FINALTYPE_LIST_STRING;
    case FINALTYPE_UNION: return FINALTYPE_UNION_STRING;
    case FINALTYPE_SUBSTITUTION: return FINALTYPE_SUBSTITUTION_STRING;

    }
}

QString XSchemaObject::finalListToString(QList<EFinalType> &types)
{
    QString result ;
    bool isFirst = true;
    if(!types.isEmpty()) {
        foreach(EFinalType type, types) {
            if(type == FINALTYPE_ALL) {
                return FINALTYPE_ALL_STRING;
            } else {
                if(!isFirst) {
                    result += " ";
                }
                result += fromFinalTypeToString(type);
            }
            isFirst = false;
        }
    }
    return result;
}

QList<XSchemaObject::EFinalType> XSchemaObject::decodeFinalListToString(const QString &encodedData)
{
    QList<EFinalType> result ;
    if(! encodedData.isEmpty()) {
        QStringList options = encodedData.split(" ");
        foreach(QString value, options) {
            if(value == FINALTYPE_ALL_STRING) {
                result.append(FINALTYPE_ALL);
            } else if(value == FINALTYPE_RESTRICTION_STRING) {
                result.append(FINALTYPE_RESTRICTION);
            } else if(value == FINALTYPE_EXTENSION_STRING) {
                result.append(FINALTYPE_EXTENSION);
            } else if(value == FINALTYPE_LIST_STRING) {
                result.append(FINALTYPE_LIST);
            } else if(value == FINALTYPE_UNION_STRING) {
                result.append(FINALTYPE_UNION);
            } else if(value == FINALTYPE_SUBSTITUTION_STRING) {
                result.append(FINALTYPE_SUBSTITUTION);
            } else {
                XsdError(tr("Invalid final/block value: %1").arg(encodedData));
            }
        }
    }
    return result ;
}

void XSchemaObject::addAttrNotEmpty(QDomElement element, const QString &attributeName, const QString &value)
{
    if(!value.isEmpty()) {
        element.setAttribute(attributeName, value);
    }
}

void XSchemaObject::addElementIfNotEmpty(QDomElement &element, const QString &elementTag, const QString &value)
{
    if(!value.isEmpty()) {
        QDomDocument document = element.ownerDocument();
        QDomElement innerElement = createElement(document, elementTag);
        QDomText textNode = document.createTextNode(value);
        innerElement.appendChild(textNode);
        element.appendChild(innerElement);
    }
}

void XSchemaObject::addFacetIfNotEmpty(QDomElement &element, const QString &elementTag, const QString &value)
{
    if(!value.isEmpty()) {
        QDomDocument document = element.ownerDocument();
        QDomElement innerElement = createElement(document, elementTag);
        innerElement.setAttribute(IO_FACET_ATTR_VALUE, value);
        element.appendChild(innerElement);
    }
}

QDomElement XSchemaObject::createElement(QDomDocument &document, const QString &tagName)
{
    return _root->createElementWithNamespace(document, tagName);
}

void XSchemaObject::addOtherAttributesToDom(QDomElement & element)
{
    foreach(QString otherKey, _otherAttributes.keys()) {
        element.setAttribute(otherKey, _otherAttributes.value(otherKey));
    }
}

bool XSchemaObject::readOtherAttributes(QDomAttr & attribute)
{
    if(_root->existsNamespace(attribute.prefix())) {
        _otherAttributes.insert(attribute.name(), attribute.value());   //TODO check namespace
        return true;
    }
    return false;
}

void XSchemaObject::readHandleObject(QDomElement &element, XSchemaObject *newObject)
{
    if(NULL == newObject) {
        raiseErrorForObject(element);
    }
    addChild(newObject);
    newObject->loadFromDom(element);
}

void XSchemaObject::readHandleObject(QDomElement &element, XSchemaObject *parent, XSchemaObject *newObject)
{
    parent->readHandleObject(element, newObject);
}

void XSchemaObject::loadFromDom(QDomElement &/*element*/)
{
    XsdError("TODO vf called");
}

bool XSchemaObject::scanDom(QDomElement &elementToExamine, void *context)
{
    QDomNamedNodeMap attributes = elementToExamine.attributes();
    int numAttrs = attributes.length();
    for(int i = 0 ; i < numAttrs ; i++) {
        QDomNode node = attributes.item(i);
        QDomAttr attr = node.toAttr();
        scanForAttributes(attr, context);
    } // for

    int nodi = elementToExamine.childNodes().count();
    for(int i = 0 ; i < nodi ; i ++) {
        QDomNode childNode = elementToExamine.childNodes().item(i) ;

        if(childNode.isElement()) {
            QDomElement element = childNode.toElement();
            scanForElements(element, context);
        }
    }
    validateAfterRead(elementToExamine, context);
    return true;
}

void XSchemaObject::scanForAttributes(QDomAttr & /*attribute*/, void * /*context*/)
{
}

void XSchemaObject::scanForElements(QDomElement & /*element*/, void * /*context*/)
{
}

void XSchemaObject::validateAfterRead(QDomElement & /*node*/, void * /*context*/)
{
}

void XSchemaObject::readHandleAnnotation(/*TODO XSchemaObject *origin,*/ QDomElement &element)
{
    if(NULL != _annotation) {
        raiseError(this, element, true);
    }
    _annotation = new XSchemaAnnotation(this, _root) ;
    if(NULL == _annotation) {
        raiseErrorForObject(element);
    }
    _annotation->loadFromDom(element);
}

void XSchemaObject::invalidObjectState(XSchemaObject *origin, QDomNode &node, const QString &fieldName)
{
    QString parentName ;
    QString className ;
    const QMetaObject *mo = origin->metaObject();
    if(NULL != mo)     {
        className = mo->className();
    }
    QDomNode parent = node.parentNode();
    if(!parent.isNull()) {
        parentName = parent.nodeName();
    }
    throw new XsdException(tr("[%1] Element '%2' (contained in '%4' at line %5, position %6) with invalid field '%3'.")
                           .arg(className)
                           .arg(node.nodeName())
                           .arg(fieldName)
                           .arg(parentName)
                           .arg(node.lineNumber())
                           .arg(node.columnNumber()));
}

void XSchemaObject::raiseError(XSchemaObject *origin, QDomNode &node, const bool isElement)
{
    QString parentName ;
    QString className ;
    const QMetaObject *mo = origin->metaObject();
    if(NULL != mo)     {
        className = mo->className();
    }
    QDomNode parent = node.parentNode();
    if(!parent.isNull()) {
        parentName = parent.nodeName();
    }
    if(isElement) {
        throw new XsdException(tr("[%5] Unexpected element '%1' contained in '%2' at line %3, position %4.")
                               .arg(node.nodeName())
                               .arg(parentName)
                               .arg(node.lineNumber())
                               .arg(node.columnNumber())
                               .arg(className));
    } else {
        throw new XsdException(tr("[%5] Unexpected attribute '%1' contained in '%2' at line %3, position %4.")
                               .arg(node.nodeName())
                               .arg(parentName)
                               .arg(node.lineNumber())
                               .arg(node.columnNumber())
                               .arg(className));
    }
}

void XSchemaObject::raiseErrorForObject(QDomNode &node)
{
    throw new XsdException(tr("Unable to get new object of type: %1")
                           .arg(node.nodeName()));
}

QStringList XSchemaObject::readFinalAttribute(const QString &value)
{
    QStringList result = value.split(" ");
    return result ;
}

XSchemaObject::EProcessContent XSchemaObject::decodeProcessContents(const QString &value)
{
    if(value == IO_ANY_ATTR_PROCESSCONTENTS_LAX) {
        return lax;
    }
    if(value == IO_ANY_ATTR_PROCESSCONTENTS_SKIP) {
        return skip;
    }
    if(value == IO_ANY_ATTR_PROCESSCONTENTS_STRICT) {
        return strict;
    }
    return none ;
}

QString XSchemaObject::processContentstoString(const EProcessContent pc)
{
    switch(pc) {
    case lax:
        return IO_ANY_ATTR_PROCESSCONTENTS_LAX;
    case skip:
        return IO_ANY_ATTR_PROCESSCONTENTS_SKIP ;
    case strict:
        return IO_ANY_ATTR_PROCESSCONTENTS_STRICT;
    default:
        return "" ;
    }
}

void XSchemaObject::scanForContentAnnotation(QDomElement &element, void * context)
{
    XScanContext *theContext = (XScanContext*) context;
    QString name = element.localName();
    if(element.prefix() == _root->namespacePrefix()) {
        if(name == IO_XSD_ANNOTATION) {
            if(theContext ->childFound) {
                raiseError(this, element, true);
            }
            readHandleAnnotation(element);
            theContext ->childFound = true ;
            return;
        }
    }
    raiseError(this, element, true);
}

void XSchemaObject::generateFacets(QDomElement &node, RestrictionFacets &facets)
{
    // TODO: factor this (complex type, etc.)
    addFacetIfNotEmpty(node, IO_XSD_MINEXCLUSIVE, facets._minExclusive);
    addFacetIfNotEmpty(node, IO_XSD_MININCLUSIVE, facets._minInclusive);
    addFacetIfNotEmpty(node, IO_XSD_MAXEXCLUSIVE, facets._maxExclusive);
    addFacetIfNotEmpty(node, IO_XSD_MAXINCLUSIVE, facets._maxInclusive);
    addFacetIfNotEmpty(node, IO_XSD_TOTALDIGITS, facets._totalDigits);
    addFacetIfNotEmpty(node, IO_XSD_FRACTIONDIGITS, facets._fractionDigits);
    addFacetIfNotEmpty(node, IO_XSD_LENGTH, facets._length);
    addFacetIfNotEmpty(node, IO_XSD_MINLENGTH, facets._minLength);
    addFacetIfNotEmpty(node, IO_XSD_MAXLENGTH, facets._maxLength);
    foreach(QString restrictionValue, facets._enumeration) {
        addFacetIfNotEmpty(node, IO_XSD_ENUMERATION, restrictionValue);   // TODO: WRONG!!!!
    }
    // TODO: WRONG!!!!
    addFacetIfNotEmpty(node, IO_XSD_WHITESPACE, facets._whiteSpace);
    addFacetIfNotEmpty(node, IO_XSD_PATTERN, facets._pattern);
}

bool XSchemaObject::hasAReference()
{
    return false;
}


QString XSchemaObject::descriptionForProposal()
{
    return name();
}

QString XSchemaObject::getOhterAttrsAsTextList()
{
    QString result ;
    foreach(QString key, _otherAttributes.keys()) {
        result.append(key);
        result.append("=\"");
        result.append(_otherAttributes[key]);
        result.append("\"\n");
    }
    return result;
}

bool XSchemaObject::hasOtherAttributes()
{
    return !_otherAttributes.isEmpty();
}
