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

#ifndef XSDCONTENT_H
#define XSDCONTENT_H

#include "xsdeditor/xsdtypes.h"
#include "xsdeditor/xproperties.h"
#include "xsdeditor/xschema.h"

// simple and complex content definition

class XSchemaSimpleContent : public XSchemaObject
{
    Q_OBJECT

    QString _idContainer;
    XSchemaAnnotation *_mainAnnotation;
    QMap<QString, QString> _otherTypeAttributes;

protected:
    virtual void reset();
    virtual bool generateDom(QDomDocument &document, QDomNode &parent) ;
    bool readOtherAttributes(QDomAttr & attribute);
    QDomElement writeBaseProperties(QDomElement &element);

public:
    XSchemaSimpleContent(XSchemaObject *newParent, XSchemaRoot *newRoot);
    ~XSchemaSimpleContent();
    bool readBaseProperties(QDomElement &element);

    virtual ESchemaType getType() {
        return SchemaTypeSimpleContent;
    }

    static XSchemaSimpleContent *readChild(XSchemaObject *parent, QDomElement &element);
};


class XSchemaSimpleContentRestriction : public XSchemaSimpleContent
{
    Q_OBJECT

    bool    anyAttribute;
    QString _base;
    RestrictionFacets _facets;

protected:
    virtual void reset();
    virtual bool generateDom(QDomDocument &document, QDomNode &parent) ;
    void loadFromDom(QDomElement &elementToExamine);

    virtual void scanForAttributes(QDomAttr &attribute, void * context);
    virtual void scanForElements(QDomElement &element, void * context);

public:
    XSchemaSimpleContentRestriction(XSchemaObject *newParent, XSchemaRoot *newRoot);
    ~XSchemaSimpleContentRestriction();

    virtual ESchemaType getType() {
        return SchemaTypeSimpleContentRestriction ;
    }

};


class XSchemaSimpleContentExtension : public XSchemaSimpleContent
{
    Q_OBJECT

    bool    anyAttribute;
    QString _base;

protected:
    virtual void reset();
    virtual bool generateDom(QDomDocument &document, QDomNode &parent) ;
    void loadFromDom(QDomElement &elementToExamine);

    virtual void scanForAttributes(QDomAttr &attribute, void * context);
    virtual void scanForElements(QDomElement &element, void * context);

public:
    XSchemaSimpleContentExtension(XSchemaObject *newParent, XSchemaRoot *newRoot);
    ~XSchemaSimpleContentExtension();

    virtual ESchemaType getType() {
        return SchemaTypeContentExtension ;
    }

signals:

};


class XSchemaComplexContent : public XSchemaObject
{
    Q_OBJECT
protected:
    bool    anyAttribute;
    QString _base;
    XEnums::XBool _mixed;
    XSchemaAnnotation *_mainAnnotation;
    QString _idContainer;
    QMap<QString, QString> _otherTypeAttributes;

protected:
    virtual void reset();
    virtual bool generateDom(QDomDocument &document, QDomNode &parent) ;

    void scanForAttributes(QDomAttr &attribute, void * context);
    void scanForElements(QDomElement &element, void * context);
    void loadFromDom(QDomElement &elementToExamine);

public:
    XSchemaComplexContent(XSchemaObject *newParent, XSchemaRoot *newRoot);
    ~XSchemaComplexContent();

    bool readBaseProperties(QDomElement &element);
    bool readOtherAttributes(QDomAttr & attribute);
    QDomElement writeBaseProperties(QDomElement &element);

    virtual ESchemaType getType() {
        return SchemaTypeComplexContent ;
    }
    virtual bool examineType(XValidationContext *context, XSingleElementContent *parent);

signals:

};


class XSchemaComplexContentRestriction : public XSchemaComplexContent
{
    Q_OBJECT

protected:
    virtual void reset();
    virtual bool generateDom(QDomDocument &document, QDomNode &parent) ;

public:
    XSchemaComplexContentRestriction(XSchemaObject *newParent, XSchemaRoot *newRoot);
    ~XSchemaComplexContentRestriction();

    virtual ESchemaType getType() {
        return SchemaTypeComplexContentRestriction ;
    }

    virtual QString description();
signals:

};


class XSchemaComplexContentExtension : public XSchemaComplexContent
{
    Q_OBJECT;


protected:
    virtual void reset();
    virtual bool generateDom(QDomDocument &document, QDomNode &parent) ;

public:
    XSchemaComplexContentExtension(XSchemaObject *newParent, XSchemaRoot *newRoot);
    ~XSchemaComplexContentExtension();

    virtual ESchemaType getType() {
        return SchemaTypeComplexContentExtension ;
    }

    virtual QString description();

signals:

};

#endif // XSDCONTENT_H
