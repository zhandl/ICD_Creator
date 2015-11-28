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

#ifndef XSDGRAPHICCONTEXT_H
#define XSDGRAPHICCONTEXT_H

#include <QObject>
#include <QHash>

class XSDItem ;
class XSchemaObject;
class XMainMenuBuilder;
class RootItem;
class XSDSchema;

class XsdGraphicContext : public QObject
{
    Q_OBJECT
    QHash<XSchemaObject*, XSDItem*> _mapObjectsToItems;
    XMainMenuBuilder *_menuBuilder;
    RootItem *_rootItem;
    XSDSchema *_schema;

    // TODO QStack<XSDItem*> _navigation;

public:
    explicit XsdGraphicContext(QObject *parent = 0);
    ~XsdGraphicContext();

    void addObject(XSchemaObject* object, XSDItem* item);
    void removeObject(XSchemaObject* object);
    XSDItem *getItemOfObject(XSchemaObject* object);
    XMainMenuBuilder *menuBuilder();
    void setMenuBuilder(XMainMenuBuilder *newBuilder);

    RootItem *rootItem();
    XSDSchema *schema();

    void setRootItem(RootItem *rootItem);
    void setSchema(XSDSchema *schema);

    void clear();


signals:

public slots:

};

#endif // XSDGRAPHICCONTEXT_H
