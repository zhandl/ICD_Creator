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

#include "xsdeditor/xsdgraphiccontext.h"
#include "xsdeditor/xsdwindow.h"

XsdGraphicContext::XsdGraphicContext(QObject *parent) :
    QObject(parent)
{
    _rootItem = NULL ;
    _schema = NULL ;
}

XsdGraphicContext::~XsdGraphicContext()
{
    clear();
}

void XsdGraphicContext::clear()
{
    if(NULL != _rootItem) {
        delete _rootItem;
        _rootItem = NULL ;
    }

    if(_schema != NULL) {
        delete _schema ;
        _schema = NULL;
    }
}

void XsdGraphicContext::addObject(XSchemaObject* object, XSDItem* item)
{
    if(NULL != object) {
        _mapObjectsToItems[object] = item;
    }
}

void XsdGraphicContext::removeObject(XSchemaObject* object)
{
    if(NULL != object) {
        _mapObjectsToItems.remove(object);
    }
}

XSDItem *XsdGraphicContext::getItemOfObject(XSchemaObject* object)
{
    if(_mapObjectsToItems.contains(object)) {
        return _mapObjectsToItems[object];
    }
    return NULL ;
}

XMainMenuBuilder *XsdGraphicContext::menuBuilder()
{
    return _menuBuilder ;
}

void XsdGraphicContext::setMenuBuilder(XMainMenuBuilder *newBuilder)
{
    _menuBuilder = newBuilder ;
}

RootItem *XsdGraphicContext::rootItem()
{
    return _rootItem;
}

XSDSchema *XsdGraphicContext::schema()
{
    return _schema;
}

void XsdGraphicContext::setRootItem(RootItem *newRootItem)
{
    _rootItem = newRootItem ;
}

void XsdGraphicContext::setSchema(XSDSchema *newSchema)
{
    _schema = newSchema ;
}
