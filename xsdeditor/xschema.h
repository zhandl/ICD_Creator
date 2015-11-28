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
#ifndef XSCHEMA_H
#define XSCHEMA_H

#define XSD_READONLY

#include "xsdeditor/xsdtypes.h"
#include "xsdeditor/xproperties.h"
#include <QMap>
#include <QStringList>
#include <QPixmap>

#include "xsdeditor/validator/xvalidationcontext.h"

#define DECLARE_PROP_S_ALL(getter, setter)  private:\
    QString _##getter;\
    public:\
    QString getter(); void setter( const QString &newValue );

#define DECLARE_PROP_S(getter, setter)  QString getter(); void setter( const QString &newValue );


#define DECLARE_PROP(className, prop, type)  type prop(); void set##prop( const type &prop );
#define IMPL_PROP(className, prop, type) type className::prop(){ return m_##prop;} void className::set##prop( const type &new#prop ) { m_##prop = new#prop ; }
#define IMPL_PROPS(className, getter, setter) QString className::getter(){ return _##getter;} void className::setter( const QString &newValue ) { _##getter = newValue ; }
//#define IS_TYPE(xtype)  int type() const { return xtype; }

#define ADD_E(x)   virtual bool canAddElement() { return x ;}
#define ADD_A(x)   virtual bool canAddAttribute() { return x ;}
#define ADD_S(x)   virtual bool canAddSequence()  { return x ;}
#define ADD_C(x)   virtual bool canAddChoice()  { return x ;}

#define D_ADD_E()   virtual bool canAddElement() ;
#define D_ADD_A()   virtual bool canAddAttribute() ;
#define D_ADD_S()   virtual bool canAddSequence() ;
#define D_ADD_C()   virtual bool canAddChoice() ;

class XEnums : public QObject
{
    Q_OBJECT
private:
    XEnums();
    ~XEnums();
public:
    enum XBool { XBOOL_UNSET, XBOOL_TRUE, XBOOL_FALSE} ;
    static XBool parseBool(const QString input);
    static QString boolToString(const XBool value);

    // other general purpose enums

};

#include <QObject>
#include <QDomDocument>
#include <exception>

class XsdException : public std::exception
{
public:
    QString _cause;
    XsdException(const QString &theCause);
    XsdException();
    virtual const char* what() const throw() ;
    virtual QString cause() const throw() ;
    virtual ~XsdException() throw() ;
};

void XsdError(const QString &message);

class RestrictionFacets
{
public:
    // TODO: WRONG!!!! THESE ARE ELEMENTS WITH INNER ANNOTATIONS
    QString _minExclusive, _minInclusive ;
    QString _maxExclusive, _maxInclusive ;
    QString _totalDigits, _fractionDigits, _length;
    QString _minLength, _maxLength ;
    QStringList _enumeration ;
    QString _whiteSpace; // TODO: WRONG!!!!
    QString _pattern;

    QString toString();
    //void generateFacets( QDomElement &node );
    bool scanForFacets(const QString &name, const QString &value);
    QString getFacet(const QString &name, const QString &value);
    void addFacetIfNotEmpty(QDomElement &element, const QString &elementTag, const QString &value);
};


class XOccurrence
{
public:
    bool isSet;
    unsigned int occurrences;
    bool isUnbounded ;
    int defaultValue ; // -1 : unbounded
    XOccurrence();
    ~XOccurrence();
    XOccurrence(const XOccurrence &ref);
    void addAttrToNode(QDomElement &element, const QString &attributeName);
    bool setValueFromAttribute(const QString &attributeValue);
    QString toString();
    QString getFacet(const QString &name, const QString &value);
};

class XSDSchema ;

class XSchemaRoot
{

public:
    //TODO put here root methods
    virtual QString xsdNS() = 0 ;
    virtual QDomElement createElementWithNamespace(QDomDocument &document, const QString &tagName) = 0 ;
    virtual QString namespacePrefix() = 0 ;
    virtual bool existsNamespace(const QString &namespaceToSearch) = 0;
    virtual XSDSchema* schema() = 0;
};

enum XReferenceType {
    XRT_NONE,
    XRT_ELEMENT,
    XRT_TYPE,
    XRT_ATTRIBUTE
};


enum ESchemaType {
    SchemaTypeSchema,
    SchemaTypeElement,
    SchemaTypeAttribute,
    SchemaTypeChoice,
    SchemaTypeSequence,
    SchemaTypeSimpleContent,
    SchemaTypeSimpleContentRestriction,
    SchemaTypeContentExtension,
    SchemaTypeComplexContent,
    SchemaTypeComplexContentRestriction,
    SchemaTypeComplexContentExtension,
    SchemaTypeSimpleType,
    SchemaTypeSimpleTypeRestriction,
    SchemaTypeSimpleTypeUnion,
    SchemaTypeSimpleTypeList,

    SchemaTypeAnnotation,
    SchemaTypeBaseDocumentation,
    SchemaTypeDocumentation,
    SchemaTypeAppInfo,
    SchemaTypeAll,
    SchemaTypeAny,
    SchemaTypeAnyAttribute,
    SchemaTypeAttributeGroup,
    SchemaTypeField,
    SchemaTypeGroup,
    SchemaTypeImport,
    SchemaTypeInclude,
    SchemaTypeKey,
    SchemaTypeKeyRef,
    SchemaTypeNotation,
    SchemaTypeRedefine,
    SchemaTypeSelector,
    SchemaTypeUnique

};


class XSchemaChoice ;
class XSchemaSequence ;
class XSchemaElement ;
class XSchemaAttribute ;
class XSchemaSimpleTypeRestriction;
class XSchemaSimpleTypeList;
class XSchemaSimpleTypeUnion;
class XSchemaAnnotation ;
class XInfoBase;
class XSchemaSimpleContent;
class XSchemaComplexContent;

class XAttribute
{
    QString key;
    QString value;
};

class SchemaSearchContext;

class XSchemaObject : public QObject
{
    Q_OBJECT
    Q_ENUMS(EFinalType)

public:
    enum EFinalType {
        FINALTYPE_NONE = 0,
        FINALTYPE_ALL = 1,
        FINALTYPE_RESTRICTION = 2,
        FINALTYPE_EXTENSION = 3,
        FINALTYPE_LIST = 4,
        FINALTYPE_UNION = 5,
        FINALTYPE_SUBSTITUTION = 6
    };

    enum EProcessContent { none, lax, skip, strict };

    enum EQualified {
        EQ_MISSING,
        EQ_UNQUALIFIED,
        EQ_QUALIFIED
    };


protected:
    QString _id;
    QString _name;
    QList<XSchemaObject*> _children;
    QMap<QString, QString> _otherAttributes;
    XSchemaObject *_parent;
    XSchemaRoot *_root;
    XSchemaAnnotation *_annotation;

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

    virtual void reset();
    XSchemaObject* addChild(XSchemaObject *child);

public:
    QString name();
    void setName(const QString &name);
    QString id();
    void setId(const QString &id_);

    //virtual bool operator< ( const XSchemaObject & other ) const ;


    XSchemaObject(XSchemaObject *newParent, XSchemaRoot *newRoot);
    ~XSchemaObject();

    QList<XSchemaObject*> &getChildren();

    XSchemaAnnotation *annotation();

    static QString fromFinalTypeToString(const EFinalType fType);
    static QString finalListToString(QList<EFinalType> &types);
    QList<EFinalType> decodeFinalListToString(const QString &encodedData);

    virtual ESchemaType getType() = 0;

    virtual bool canAddElement() ;
    virtual bool canAddAttribute() ;
    virtual bool canAddSequence() ;
    virtual bool canAddChoice() ;
    virtual bool canAddRestriction() ;
    virtual bool canAddExtension() ;
    virtual bool canAddUnion() ;
    virtual bool canAddList() ;

    virtual bool isSimpleType() ;

    virtual bool canAddChild(const ESchemaType newType);
    virtual XSchemaObject* addNewChild(const ESchemaType newType);

    virtual XSchemaElement *addElement() ;
    virtual XSchemaAttribute *addAttribute();
    virtual XSchemaChoice* addChoice();
    virtual XSchemaSequence* addSequence();
    virtual XSchemaObject* addRestriction();
    virtual XSchemaObject* addExtension();
    virtual XSchemaSimpleTypeUnion* addUnion();
    virtual XSchemaSimpleTypeList* addList();

    virtual void deleteObject();
    virtual void deleteChild(XSchemaObject *theChild);

    virtual XReferenceType referencedObjectType();
    virtual QString referencedObjectName();
    virtual XSchemaObject *findComponentInValidationPath(SchemaSearchContext *context);
    virtual bool findSchemaChildComponents(XValidationContext *context, XElementContent *content);
    virtual QString descriptionForProposal();

    QString getOhterAttrsAsTextList();
    bool hasOtherAttributes();

protected:
    virtual XSchemaElement *realAddElement() ;
    virtual XSchemaAttribute *realAddAttribute();
    virtual XSchemaChoice* realAddChoice();
    virtual XSchemaSequence* realAddSequence();
    virtual XSchemaSimpleTypeRestriction* realAddSimpleTypeRestriction();
    virtual XSchemaSimpleTypeUnion* realAddUnion();
    virtual XSchemaSimpleTypeList* realAddList();

public: //TODO: protected?
    virtual bool generateDom(QDomDocument &document, QDomNode &parent) = 0 ;
    virtual bool generateInnerDom(QDomDocument &document, QDomNode &parent);
    virtual bool containsSimpleType();
    virtual QString description();
    virtual QColor color();
    virtual QPixmap icon();
    XSchemaObject *xsdParent();
    virtual bool hasAReference();
    virtual bool collect(XValidationContext *context, XSingleElementContent *content);
    virtual int minOccurrences() ;
    virtual int maxOccurrences() ;

protected:
    static void addAttrNotEmpty(QDomElement element, const QString &attributeName, const QString &value);
    QDomElement createElement(QDomDocument &document, const QString &tagName) ;
    void addOtherAttributesToDom(QDomElement & node);
    bool readOtherAttributes(QDomAttr & attribute);
    void addElementIfNotEmpty(QDomElement &element, const QString &elementTag, const QString &value);
    void addFacetIfNotEmpty(QDomElement &element, const QString &elementTag, const QString &value);

    void readHandleObject(QDomElement &element, XSchemaObject *newObject);
    void readHandleObject(QDomElement &element, XSchemaObject *parent, XSchemaObject *newObject);
    virtual void loadFromDom(QDomElement &element);
    bool scanDom(QDomElement &elementToExamine, void *context);
    virtual void scanForAttributes(QDomAttr &attribute, void *context);
    virtual void scanForElements(QDomElement &element, void *context);
    virtual void validateAfterRead(QDomElement &node, void * context);

    void readHandleAnnotation(QDomElement &element);
    void raiseError(XSchemaObject *origin, QDomNode &node, const bool isElement);
    void raiseErrorForObject(QDomNode &node);
    void invalidObjectState(XSchemaObject *origin, QDomNode &node, const QString &fieldName);
    QStringList readFinalAttribute(const QString &value);
    EProcessContent decodeProcessContents(const QString &value);
    QString processContentstoString(const EProcessContent pc);
    void scanForContentAnnotation(QDomElement &element, void * context);
    void generateFacets(QDomElement &node, RestrictionFacets &facets);

    static const QString _xsdXML;

signals:
    void childAdded(XSchemaObject *newChild);
    void childRemoved(XSchemaObject *theChild);
    void deleted(XSchemaObject *theObject);
    void nameChanged(const QString &newName);
    void idChanged(const QString &newId);
    void changed();
    void propertyChanged(const QString &propertyName);

};


class XSchemaAttribute : public XSchemaObject
{
    Q_OBJECT

public:
    enum EUse { Missing, Optional, Prohibited, Required };
private:
    QString _defaultValue;
    QString _fixed;
    EQualified _form ;
    QString _ref;
    QString _xsdType;
    EUse _use;


protected:
    virtual void reset();
    virtual bool generateDom(QDomDocument &document, QDomNode &parent) ;
    virtual void scanForAttributes(QDomAttr &attribute, void *context);
    virtual void scanForElements(QDomElement &element, void *context);

    bool readHandleSimpleType(QDomElement &element);

public:
    XSchemaAttribute(XSchemaObject *newParent, XSchemaRoot *newRoot);
    ~XSchemaAttribute();

    void loadFromDom(QDomElement &elementToExamine);
    virtual QString description();

    virtual ESchemaType getType() {
        return SchemaTypeAttribute ;
    }
    static QString toStringUse(const EUse theUse);
    static QString toStringForSave(const EUse theUse);

    virtual bool hasAReference();

    virtual XReferenceType referencedObjectType();
    virtual QString referencedObjectName();


    //TODO Q_PROPERTY(QString fixed READ fixed WRITE setFixed NOTIFY fixedChanged )
    //TODO Q_PROPERTY(QString defaultValue READ defaultValue WRITE setDefaultValue NOTIFY defaultValueChanged )

};

//ricordarsi, per una gestione corretta: simpleContent gestisce solo contenuto a caratteri, complexContext ammette figli
// Limitations:
// annotations are handled only for main type
class XSchemaElement : public XSchemaObject
{
    Q_OBJECT
    Q_ENUMS(ElementCategory)
    Q_PROPERTY(XEnums::XBool abstract READ abstract WRITE setAbstract NOTIFY abstractChanged)
    Q_PROPERTY(XEnums::XBool nillable READ nillable WRITE setNillable NOTIFY nillableChanged)
    Q_PROPERTY(XEnums::XBool mixed READ mixed WRITE setMixed NOTIFY mixedChanged)
    Q_PROPERTY(QString fixed READ fixed WRITE setFixed NOTIFY fixedChanged)
    Q_PROPERTY(QString defaultValue READ defaultValue WRITE setDefaultValue NOTIFY defaultValueChanged)
    //TODO Q_PROPERTY(XOccurrence maxOccurs READ maxOccurs WRITE setMaxOccurs NOTIFY maxOccursChanged )
    //TODO Q_PROPERTY(XOccurrence minOccurs READ minOccurs WRITE setMinOccurs NOTIFY minOccursChanged )
    //TODO Q_PROPERTY(XSchemaObject::EFinalType final READ final WRITE setFinal NOTIFY finalChanged)
    //TODO Q_PROPERTY(XSchemaObject::EFinalType block READ block WRITE setBlock NOTIFY blockChanged)
    Q_PROPERTY(QString xsdType READ xsdType WRITE setXsdType NOTIFY xsdTypeChanged)
    Q_PROPERTY(XSchemaElement::ElementCategory category READ category WRITE setCategory NOTIFY categoryChanged)
    Q_PROPERTY(QString ref READ ref WRITE setRef NOTIFY refChanged)

public:

    enum ElementCategory {
        EES_EMPTY = 1,      // tag only
        EES_REFERENCE = 2,      // true elements only can be references
        EES_SIMPLETYPE_ONLY = 3, //child text simpletype
        EES_SIMPLETYPE_WITHATTRIBUTES = 4, // child text complexType simpleContent
        EES_COMPLEX_DERIVED = 5, // complexType -  complexContent
        EES_COMPLEX_DEFINITION = 6 // Complex Type sequence/choice/group/all
    };

private:

    // working mode
    bool _isTypeOrElement;
    ElementCategory _elementCategory;

    XEnums::XBool   _abstract;
    QList<EFinalType> _block;
    QString _defaultValue;
    QList<EFinalType> _final;
    QString _fixed;
    //TODO FormType    _form; TODO
    XOccurrence _maxOccurs;
    XOccurrence _minOccurs;
    XEnums::XBool  _nillable;
    QString _ref;
    ///QString _substitutionGroup;TODO
    QString _xsdType;
    //EXType _type; TODO: fare funzione calcolata
    XSchemaAnnotation *_innerAnnotation;

    //----- types specific
    XEnums::XBool   _mixed;
    QString _containedId;
    QMap<QString, QString> _innerTypeAttributes;

    QList<XSchemaAttribute*> _attributes;
protected:
    virtual void reset();
    virtual void resetAttributes();
    virtual bool generateDom(QDomDocument &document, QDomNode &parent) ;
    virtual bool findSchemaChildComponents(XValidationContext *context, XElementContent *content);
    bool elabTypeForCollect(XValidationContext * context, XElementContent * content);
public:

    XSchemaElement(XSchemaObject *newParent, XSchemaRoot *newRoot, const ElementCategory category = EES_EMPTY);
    ~XSchemaElement();

    //TODO: a seconda della categoria?
    virtual ESchemaType getType() {
        return SchemaTypeElement ;
    }

    virtual void loadFromDom(QDomElement &element);
    virtual QString description();
    bool isTypeOrElement();

    virtual XReferenceType referencedObjectType();
    virtual QString referencedObjectName();
    virtual bool isSimpleType() ;

    QList<XSchemaAttribute*> &attributes() {
        return _attributes;
    }

    virtual int minOccurrences() ;
    virtual int maxOccurrences() ;

    bool isExtension();

    /*

    Alla fine

            l'utente sceglie se semplice o complesso simpletype o complextype
            si abilita un altro checkbox che dice se
            contiene figli o no
    il complexcontent lo si fa con una estensione o restrizione.
    */

    //--------------------------------------
    DECL_QPROP(XEnums::XBool, abstract, setAbstract)
    DECL_QPROPS(fixed, setFixed)
    DECL_QPROP(XEnums::XBool, nillable, setNillable)
    DECL_QPROP(XEnums::XBool, mixed, setMixed)
    DECL_QPROPS(defaultValue, setDefaultValue)
    DECL_QPROPS(ref, setRef)
    /*DECL_QPROPS(substitutionGroup,setSubstitutionGroup);*/
    // TODO DECL_QPROP(XOccurrence,maxOccurs,setMaxOccurs);
    // TODO DECL_QPROP(XOccurrence,minOccurs,setMinOccurs);
    //TODO DECL_QPROP(XSchemaElement::EFinalType, final, setFinal);
    //TODO DECL_QPROP(XSchemaElement::EFinalType, block, setBlock);
    DECL_QPROPS(xsdType, setXsdType)
    DECL_QPROP(XSchemaElement::ElementCategory, category, setCategory)
    //---------------------------------------

    virtual XSchemaAttribute* addAttribute();
    virtual XSchemaChoice* addChoice();
    virtual XSchemaElement* addElement();
    virtual XSchemaSequence* addSequence();
    virtual XSchemaObject* addRestriction();

    D_ADD_A()
    D_ADD_S()
    D_ADD_C()
    bool canAddRestriction();

    QString simpleComplexDescr();
    QString nameDescr();
    QString occurrencesDescr();

    virtual bool hasAReference();
    virtual bool examineType(XValidationContext *context, XSingleElementContent *parent);
    virtual bool collect(XValidationContext *context, XSingleElementContent *content);

    /*
    TODO
    serve un qualcosa che mi validi in modo semplice
    voglio un set simple type che elimini i figli non coerenti ecc

    XSchemaSimpleType *getSimpleType();
    */
signals:
    //void childAdded(XSchemaObject *newChild);
    void abstractChanged(const XEnums::XBool newValue);
    void nillableChanged(const XEnums::XBool newValue);
    void fixedChanged(const XEnums::XBool newValue);
    void mixedChanged(const XEnums::XBool newValue);
    void defaultValueChanged(const XEnums::XBool newValue);

    void maxOccursChanged(const int);
    void minOccursChanged(const int);
    //TODO void finalChanged(const XSchemaElement::EFinalType);
    //TODO void blockChanged(const XSchemaElement::EFinalType);
    void xsdTypeChanged(const QString & xsd);
    void refChanged(const QString & xsd);
    void categoryChanged(const XSchemaElement::ElementCategory);



protected:
    // IO handling
    void writeAppendElementAttributes(QDomDocument &document, QDomElement &node);
    void writeHandleSimpleType(QDomDocument &document, QDomElement &typeSpecifier);
    void writeHandleComplexType(QDomDocument &document, QDomElement &typeSpecifier);
    void writeAppendAttributes(QDomDocument &document, QDomElement &node);
    void writeAppendNotAttributes(QDomDocument &document, QDomElement &node);

    bool readHandleSimpleType(QDomElement &element);
    bool readHandleComplexType(QDomElement &element);
    void readHandleAnnotation(QDomElement &element, const bool isInner);
    XSchemaSimpleContent *readSimpleContentChild(QDomElement &element);
    XSchemaComplexContent *readComplexContentChild(QDomElement &element);

    void validateComplexType(QDomElement &element, const bool isInner);
};


class XSchemaChoice : public XSchemaObject
{
    Q_OBJECT

    XOccurrence _maxOccurs;
    XOccurrence _minOccurs;

protected:
    virtual void reset();
    virtual bool generateDom(QDomDocument &document, QDomNode &parent) ;

public:
    XSchemaChoice(XSchemaObject *newParent, XSchemaRoot *newRoot);
    ~XSchemaChoice();

    virtual void loadFromDom(QDomElement &elementToExamine);
    virtual void scanForAttributes(QDomAttr &attribute, void * context);
    virtual void scanForElements(QDomElement &element, void *context);

    virtual ESchemaType getType() {
        return SchemaTypeChoice ;
    }

    virtual XSchemaElement* addElement();
    virtual XSchemaChoice* addChoice();
    virtual XSchemaSequence* addSequence();
    virtual XSchemaAttribute* addAttribute();

    ADD_E(true)
    ADD_S(true)
    ADD_C(true)

    virtual XSchemaObject *findComponentInValidationPath(const QString &component);
    virtual bool findSchemaChildComponents(XValidationContext *context, XElementContent *content);
    virtual bool collect(XValidationContext *context, XSingleElementContent *content);

signals:
    //void childAdded(XSchemaObject *newChild);

};

class XSchemaSequence : public XSchemaObject
{
    Q_OBJECT

    XOccurrence _maxOccurs;
    XOccurrence _minOccurs;

protected:
    virtual void reset();
    virtual bool generateDom(QDomDocument &document, QDomNode &parent) ;

    virtual void loadFromDom(QDomElement &elementToExamine);
    virtual void scanForAttributes(QDomAttr &attribute, void * context);
    virtual void scanForElements(QDomElement &element, void * context);

public:
    XSchemaSequence(XSchemaObject *newParent, XSchemaRoot *newRoot);
    ~XSchemaSequence();

    virtual ESchemaType getType() {
        return SchemaTypeSequence ;
    }

    virtual XSchemaElement* addElement();
    virtual XSchemaChoice* addChoice();
    virtual XSchemaSequence* addSequence();
    virtual XSchemaAttribute* addAttribute();

    virtual QString description();
    virtual QString descriptionForProposal();

    ADD_E(true)
    ADD_A(true)
    ADD_S(true)
    ADD_C(true)

    virtual bool collect(XValidationContext *context, XSingleElementContent *parent);

signals:
    //void childAdded(XSchemaObject *newChild);

};

class XSchemaAnnotation : public XSchemaObject
{
    Q_OBJECT
protected:

    QList<XInfoBase*> _infos;

    virtual void reset();

public:
    XSchemaAnnotation(XSchemaObject *newParent, XSchemaRoot *newRoot);
    ~XSchemaAnnotation();

    virtual void loadFromDom(QDomElement &annotation);
    bool generateDom(QDomDocument &document, QDomNode & parent);
    virtual QString description();
    QString text();

    virtual ESchemaType getType() {
        return SchemaTypeAnnotation ;
    }

signals:
};


class XSchemaAll : public XSchemaObject
{
    Q_OBJECT

    XOccurrence _maxOccursOne;
    XOccurrence _minOccurs;
protected:
    virtual void reset();
    virtual bool generateDom(QDomDocument &document, QDomNode &parent) ;
    virtual void scanForAttributes(QDomAttr &attribute, void * context);
    virtual void scanForElements(QDomElement &element, void * context);

public:
    XSchemaAll(XSchemaObject *newParent, XSchemaRoot *newRoot);
    ~XSchemaAll();

    virtual void loadFromDom(QDomElement &element);

    virtual ESchemaType getType() {
        return SchemaTypeAll ;
    }

    virtual bool collect(XValidationContext * context, XSingleElementContent *parent);
    ADD_E(true)

signals:

};

class XSchemaAny : public XSchemaObject
{
    Q_OBJECT
public:

private:
    XOccurrence _maxOccurs;
    XOccurrence _minOccurs;
    QString _namespaces; //(##any,##local,##other,...)
    EProcessContent _processContent; // default: strict
protected:
    virtual void reset();
    virtual bool generateDom(QDomDocument &document, QDomNode &parent) ;

public:
    XSchemaAny(XSchemaObject *newParent, XSchemaRoot *newRoot);
    ~XSchemaAny();

    virtual ESchemaType getType() {
        return SchemaTypeAny ;
    }

    virtual void loadFromDom(QDomElement &elementToExamine);
    virtual void scanForAttributes(QDomAttr &attribute, void * context);
    virtual void scanForElements(QDomElement &element, void *context);
    virtual void validateAfterRead(QDomElement &node, void * context);
};


class XSchemaAnyAttribute : public XSchemaObject
{
    Q_OBJECT
private:
    QStringList _namespaces; //(##any,##local,##other,...)
    EProcessContent _processContent;
protected:
    virtual void reset();
    virtual bool generateDom(QDomDocument &document, QDomNode &parent) ;
    virtual void loadFromDom(QDomElement &elementToExamine);
    virtual void scanForAttributes(QDomAttr &attribute, void * context);
    virtual void scanForElements(QDomElement &element, void *context);

public:
    XSchemaAnyAttribute(XSchemaObject *newParent, XSchemaRoot *newRoot);
    ~XSchemaAnyAttribute();

    virtual ESchemaType getType() {
        return SchemaTypeAnyAttribute ;
    }

    ADD_E(true)

signals:

};

class XSchemaAttributeGroup : public XSchemaObject
{
    Q_OBJECT;

    QString _ref;

protected:
    virtual void reset();
    virtual bool generateDom(QDomDocument &document, QDomNode &parent) ;
    virtual void loadFromDom(QDomElement &elementToExamine);
    virtual void scanForAttributes(QDomAttr &attribute, void * context);
    virtual void scanForElements(QDomElement &element, void *context);

public:
    XSchemaAttributeGroup(XSchemaObject *newParent, XSchemaRoot *newRoot);
    ~XSchemaAttributeGroup();

    virtual ESchemaType getType() {
        return SchemaTypeAttributeGroup ;
    }

signals:

};


class XSchemaField : public XSchemaObject
{
    Q_OBJECT;

    QString _xpath;

protected:
    virtual void reset();
    virtual bool generateDom(QDomDocument &document, QDomNode &parent) ;

public:
    XSchemaField(XSchemaObject *newParent, XSchemaRoot *newRoot);
    ~XSchemaField();

    virtual ESchemaType getType() {
        return SchemaTypeField ;
    }

    virtual void loadFromDom(QDomElement &elementToExamine);
    virtual void scanForAttributes(QDomAttr &attribute, void * context);
    virtual void scanForElements(QDomElement &element, void *context);
    virtual void validateAfterRead(QDomElement &node, void * context);

};

class XSchemaGroup : public XSchemaObject
{
    Q_OBJECT

    // if the parent is schema or redefine
    XOccurrence _maxOccurs;
    XOccurrence _minOccurs;
    QString _ref;

protected:
    virtual void reset();
    virtual bool generateDom(QDomDocument &document, QDomNode &parent) ;

public:
    XSchemaGroup(XSchemaObject *newParent, XSchemaRoot *newRoot);
    ~XSchemaGroup();
    virtual QString description();

    virtual ESchemaType getType() {
        return SchemaTypeGroup ;
    }

    virtual void loadFromDom(QDomElement &elementToExamine);
    virtual void scanForAttributes(QDomAttr &attribute, void * context);
    virtual void scanForElements(QDomElement &element, void *context);
    virtual void validateAfterRead(QDomElement &node, void * context);

    virtual bool collect(XValidationContext * context, XSingleElementContent *parent);

};

class XSchemaImport : public XSchemaObject
{
    Q_OBJECT

    QString _namespace;
    QString _schemaLocation;

protected:
    virtual void reset();
    virtual bool generateDom(QDomDocument &document, QDomNode &parent) ;

public:
    XSchemaImport(XSchemaObject *newParent, XSchemaRoot *newRoot);
    ~XSchemaImport();

    virtual ESchemaType getType() {
        return SchemaTypeImport ;
    }

    virtual void loadFromDom(QDomElement &elementToExamine);
    virtual void scanForAttributes(QDomAttr &attribute, void * context);
    virtual void scanForElements(QDomElement &element, void *context);
    virtual QString description();
};

class XSchemaInclude : public XSchemaObject
{
    Q_OBJECT

    QString _schemaLocation;

protected:
    virtual void reset();
    virtual bool generateDom(QDomDocument &document, QDomNode &parent) ;

public:
    XSchemaInclude(XSchemaObject *newParent, XSchemaRoot *newRoot);
    ~XSchemaInclude();

    virtual ESchemaType getType() {
        return SchemaTypeInclude ;
    }

    virtual void loadFromDom(QDomElement &elementToExamine);
    virtual void scanForAttributes(QDomAttr &attribute, void * context);
    virtual void scanForElements(QDomElement &element, void *context);
    virtual QString description();

signals:

};

class XSchemaKey : public XSchemaObject
{
    Q_OBJECT

protected:
    virtual void reset();
    virtual bool generateDom(QDomDocument &document, QDomNode &parent) ;

public:
    XSchemaKey(XSchemaObject *newParent, XSchemaRoot *newRoot);
    ~XSchemaKey();

    virtual ESchemaType getType() {
        return SchemaTypeKey ;
    }

    virtual void loadFromDom(QDomElement &elementToExamine);
    virtual void scanForAttributes(QDomAttr &attribute, void * context);
    virtual void scanForElements(QDomElement &element, void *context);
    virtual void validateAfterRead(QDomElement &node, void * context);

};

class XSchemaKeyRef : public XSchemaObject
{
    Q_OBJECT

    QString _refer;

protected:
    virtual void reset();
    virtual bool generateDom(QDomDocument &document, QDomNode &parent) ;

public:
    XSchemaKeyRef(XSchemaObject *newParent, XSchemaRoot *newRoot);
    ~XSchemaKeyRef();

    virtual ESchemaType getType() {
        return SchemaTypeKeyRef ;
    }

    virtual void loadFromDom(QDomElement &elementToExamine);
    virtual void scanForAttributes(QDomAttr &attribute, void * context);
    virtual void scanForElements(QDomElement &element, void *context);
    virtual void validateAfterRead(QDomElement &node, void * context);

};

class XSchemaUnique : public XSchemaObject
{
    Q_OBJECT;

protected:
    virtual void reset();
    virtual bool generateDom(QDomDocument &document, QDomNode &parent) ;

public:
    XSchemaUnique(XSchemaObject *newParent, XSchemaRoot *newRoot);
    ~XSchemaUnique();

    virtual ESchemaType getType() {
        return SchemaTypeUnique ;
    }

    virtual void loadFromDom(QDomElement &elementToExamine);
    virtual void scanForAttributes(QDomAttr &attribute, void * context);
    virtual void scanForElements(QDomElement &element, void *context);
    virtual void validateAfterRead(QDomElement &node, void * context);

};

class XSchemaNotation : public XSchemaObject
{
    Q_OBJECT;

    QString _publicIdentifier;
    QString _system;

protected:
    virtual void reset();
    virtual bool generateDom(QDomDocument &document, QDomNode &parent) ;

public:
    XSchemaNotation(XSchemaObject *newParent, XSchemaRoot *newRoot);
    ~XSchemaNotation();

    virtual ESchemaType getType() {
        return SchemaTypeNotation ;
    }

    virtual void loadFromDom(QDomElement &elementToExamine);
    virtual void scanForAttributes(QDomAttr &attribute, void * context);
    virtual void scanForElements(QDomElement &element, void *context);
    virtual void validateAfterRead(QDomElement &node, void * context);
    virtual QString description();

};


class XSchemaRedefine : public XSchemaObject
{
    Q_OBJECT

    QString _schemaLocation;

protected:
    virtual void reset();
    virtual bool generateDom(QDomDocument &document, QDomNode &parent) ;

public:
    XSchemaRedefine(XSchemaObject *newParent, XSchemaRoot *newRoot);
    ~XSchemaRedefine();

    virtual ESchemaType getType() {
        return SchemaTypeRedefine ;
    }

    virtual void loadFromDom(QDomElement &elementToExamine);
    virtual void scanForAttributes(QDomAttr &attribute, void * context);
    virtual void scanForElements(QDomElement &element, void *context);
    virtual void validateAfterRead(QDomElement &node, void * context);

};

class XSchemaSelector : public XSchemaObject
{
    Q_OBJECT

    QString _xpath;

protected:
    virtual void reset();
    virtual bool generateDom(QDomDocument &document, QDomNode &parent) ;

public:
    XSchemaSelector(XSchemaObject *newParent, XSchemaRoot *newRoot);
    ~XSchemaSelector();

    virtual ESchemaType getType() {
        return SchemaTypeSelector ;
    }

    virtual void loadFromDom(QDomElement &elementToExamine);
    virtual void scanForAttributes(QDomAttr &attribute, void * context);
    virtual void scanForElements(QDomElement &element, void *context);
    virtual void validateAfterRead(QDomElement &node, void * context);

};

#include "xsdeditor/xsdcontent.h"
#include "xsdeditor/xsdsctypes.h"

class XInfoBase : public XSchemaObject
{
    QString _source;
    QDomNode _content;

public:
    XInfoBase(XSchemaObject *newParent, XSchemaRoot *newRoot);
    ~XInfoBase();
    virtual bool generateDom(QDomDocument &document, QDomNode &parent) = 0 ;
    virtual ESchemaType getType() {
        return SchemaTypeBaseDocumentation ;
    }
    void generateInnerNodes(QDomNode &parent);

    void setContent(QDomNode node) {
        _content = node ;
    }
    QDomNode &content() {
        return _content ;
    }
    void setSource(const QString newSource) {
        _source = newSource;
    }
    QString source() {
        return _source ;
    }

};


class XDocumentation : public XInfoBase
{
    QString _language;
public:
    virtual ESchemaType getType() {
        return SchemaTypeDocumentation ;
    }
    XDocumentation(XSchemaObject *newParent, XSchemaRoot *newRoot);
    ~XDocumentation();
    virtual bool generateDom(QDomDocument &document, QDomNode &parent) ;
    void setLanguage(const QString newLanguage) {
        _language = newLanguage;
    }
    QString language() {
        return _language ;
    }
};

class XAppInfo : public XInfoBase
{
public:
    XAppInfo(XSchemaObject *newParent, XSchemaRoot *newRoot);
    ~XAppInfo();
    virtual ESchemaType getType() {
        return SchemaTypeAppInfo ;
    }
    virtual bool generateDom(QDomDocument &document, QDomNode &parent) ;
};


class XSDSchema : public XSchemaObject, public XSchemaRoot
{
    Q_OBJECT

    friend class XSchemaLoader;
private:
    static QString _xsdURI;

    EQualified _attributeFormDefault ;
    EQualified _elementFormDefault ;

    QString _targetNamespace ;
    QString _version;
    QString _language ;

    QList <EFinalType> _blockDefault;
    QList <EFinalType> _finalDefault;

    // this is my own namespace;
    QString _namespacePrefix;
    QMap<QString, QString> _namespaces;

    QMap<QString, XSDSchema*>_includedSchemas;
    QList<XSDSchema*>_importedSchemas;
public:

    bool scanSchema(const QDomElement &schema);
    bool scanSchemaNS(const QDomElement &schema);

protected:

    class SchemaChildOutput
    {
    public:
        QList<XSchemaObject*> includesList;
        QList<XSchemaObject*> importsList;
        QList<XSchemaObject*> redefinesList;
        QList<XSchemaObject*> annotationsList;
        QList<XSchemaObject*> othersChildrenList; //(((simpleType | complexType | group | attributeGroup) | element | attribute | notation)*
        QList<XSchemaObject*> typesList;
        QList<XSchemaObject*> elementsList;
        QList<XSchemaObject*> attributesList;
    };
    SchemaChildOutput indexes;


    void reset();
    virtual bool generateDom(QDomDocument &document) ;
    virtual bool generateDom(QDomDocument &document, QDomNode &parent) ;
    QString getAsString();
    void getChildrenByType(SchemaChildOutput &outVect);
    void addNamespace(QDomAttr &attr);
    bool getNSFromFile(const QString &filePath);

    // RootItem() interface implementation -----------------------------
    QDomElement createElementWithNamespace(QDomDocument &document, const QString &tagName);
    QString xsdNS();
    QString namespacePrefix();
    bool existsNamespace(const QString &namespaceToSearch);
    XSDSchema* schema();
    // -----------------------------------------------------------
    bool readFromInputString(const QString &inputText);
    bool readFromIoDevice(QIODevice *file);
    XSchemaObject *topLevelObject(const QString &name, const ESchemaType type);
    XSchemaObject* topLevelObject(const QString &name, QList<XSchemaObject*> &objects);
    void regenerateInternalLists();

public:
    XSDSchema();
    ~XSDSchema();

    virtual ESchemaType getType() {
        return SchemaTypeSchema ;
    }
    virtual XSchemaElement* addElement();
    virtual XSchemaAttribute *addAttribute();
    bool isAttributeFormQualified();
    bool isElementFormQualified();

    ADD_E(true)
    ADD_A(true)

    bool read(const QString &filePath);
    bool saveToClipboard() ;
    bool readFromClipboard();
    bool readFromString(const QString &inputText);

    virtual bool canAddChild(const ESchemaType newType);

    bool isValidSchema(const QDomElement &schema);
    static bool IsXsdValid(const QString &nsUri, const QString &localName);

    // general utility functions
    static const QString xsdURI() {
        return _xsdURI ;
    }
    QString qName(const QString &name);

    XSchemaElement *rootElement(const QString &referenceName);
    XSchemaAttribute *rootAttribute(const QString &referenceName);
    XSchemaElement *rootType(const QString &referenceName);

    QList<XSchemaObject*> topLevelObjects(const ESchemaType type);
    QList<XSchemaObject*> topLevelElements();
    QList<XSchemaObject*> topLevelTypes();
    QList<XSchemaObject*> topLevelAttributes();
    QList<XSchemaObject*> topLevelReferences();

    virtual XSchemaObject *findComponentInValidationPath(const QString &component);
    virtual XSchemaObject *findComponentInValidationPath(SchemaSearchContext *context);
    virtual bool findSchemaChildComponents(XValidationContext *context, XElementContent *content);

    XSchemaGroup* topLevelGroup(const QString &name);

    void setIncludedSchema(XSDSchema *child);
    void setImportedSchema(XSDSchema *child);
    void setRedefinedSchema(XSDSchema *child);

signals:
    //void loadComplete(XSDSchema *schema, const bool isError);
    //void elementAdded(XSchemaElement* element);
};

#include "xsdeditor/xsdparseutils.h"

#endif // XSCHEMA_H
