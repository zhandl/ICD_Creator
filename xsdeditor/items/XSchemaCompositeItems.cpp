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


#include "xsdeditor/xsdwindow.h"
#include "utils.h"
#include <QGraphicsTextItem>

#define PIXMAP_SEQUENCE_INFO    ":/xsdimages/sequence"

//--------------------------------------------------------------------------------------


ChoiceItem::ChoiceItem(XsdGraphicContext *newContext, XSchemaChoice *newItem, QGraphicsItem * parent)
    : XSDItem(newContext), _item(NULL),
      _graphicsItem(this), _labelItem(NULL)
{
    parent->scene()->addItem(&_graphicsItem);
    _graphicsItem.setData(XSD_ITEM_DATA, qVariantFromValue((void*)this));
    init();
    setItem(newItem);
}

ChoiceItem::~ChoiceItem()
{
    reset();
}

void ChoiceItem::reset()
{
}

void ChoiceItem::init()
{
    _contour = QRectF(0, 0, 30, 30);
    _graphicsItem.setRect(_contour);
    _graphicsItem.setFlag(QGraphicsItem::ItemIsMovable, false);
    _graphicsItem.setFlag(QGraphicsItem::ItemIsSelectable, true);
    _graphicsItem.setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    _graphicsItem.setPos(0, 0);

    _labelItem = new QGraphicsTextItem(&_graphicsItem);
    _labelItem->setPlainText(tr("Choice"));
    _labelItem->setPos(50, 50);
    _graphicsItem.childItems().append(_labelItem);

    QLinearGradient gradient(0, 0, 0, 100);
    gradient.setColorAt(0, QColor::fromRgbF(0, 0, 1, 1));
    gradient.setColorAt(1, QColor::fromRgbF(0, 1, 1, .9));

    _graphicsItem.setBrush(QBrush(gradient));
    connect(&_graphicsItem, SIGNAL(itemChanged(QGraphicsItem::GraphicsItemChange, const QVariant&)), this, SLOT(itemChanged(QGraphicsItem::GraphicsItemChange, const QVariant&)));
}

XSchemaChoice *ChoiceItem::choice() const
{
    return _item ;
}

void ChoiceItem::setItem(XSchemaChoice *newItem)
{
    if(_item != newItem) {
        if(NULL != _item) {
            disconnect(_item, SIGNAL(childAdded(XSchemaObject*)), this, SLOT(childAdded(XSchemaObject*)));
            //TODO disconnect(_item, SIGNAL(childRemoved(XSchemaObject*)), this, SLOT(childRemoved(XSchemaObject*)));
        }
        _item = newItem ;
        if(NULL != newItem) {
            connect(_item, SIGNAL(childAdded(XSchemaObject*)), this, SLOT(childAdded(XSchemaObject*)));
            //TODO connect(_item, SIGNAL(childRemoved(XSchemaObject*)), this, SLOT(childRemoved(XSchemaObject*)));
            foreach(XSchemaObject * child, _item->getChildren()) {
                childAdded(child);
            }
        }
    }
}

void ChoiceItem::itemChanged(QGraphicsItem::GraphicsItemChange change, const QVariant & /*value*/)
{
    if(change == QGraphicsItem::ItemPositionChange) {
        RChild *theChain = chain();
        if(NULL != theChain) {
            chain()->updatePosition();
            updateScenePosition(&_graphicsItem);
            foreach(RChild * child, _children.children()) {
                child->updatePosition();
            }
        }
    }
}

void ChoiceItem::childAdded(XSchemaObject *newChild)
{
    if(NULL == newChild) {
        return ;
    }
    XSDItem *child = addChild(newChild);
    if(NULL == child) {
        Utils::error(tr("An error occurred inserting the graphic item corresponding to the object."));
    }
}

//--------------------------------------------------------------------------------------


SequenceItem::SequenceItem(XsdGraphicContext *newContext, XSchemaSequence *newItem, QGraphicsItem * parent)
    : XSDItem(newContext), _item(NULL),
      _graphicsItem(this), _labelItem(NULL)
{
    parent->scene()->addItem(&_graphicsItem);
    _graphicsItem.setData(XSD_ITEM_DATA, qVariantFromValue((void*)this));
    init();
    setItem(newItem);
}

SequenceItem::~SequenceItem()
{
    reset();
}

void SequenceItem::reset()
{
}

void SequenceItem::init()
{
    _contour = QRectF(0, 0, 30, 50);
    _graphicsItem.setRect(_contour);
    _graphicsItem.setFlag(QGraphicsItem::ItemIsMovable, false);
    _graphicsItem.setFlag(QGraphicsItem::ItemIsSelectable, true);
    _graphicsItem.setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    _graphicsItem.setPos(11, 0);

    _labelItem = new QGraphicsTextItem(&_graphicsItem);
    _labelItem->setPlainText(tr("Sequence"));
    _labelItem->setPos(60, 10);
    _graphicsItem.childItems().append(_labelItem);

    _icon = new QGraphicsPixmapItem(&_graphicsItem);
    _icon ->setPos(5, 5);
    QPixmap pixmap ;
    pixmap.load(PIXMAP_SEQUENCE_INFO);
    _icon->setPixmap(pixmap);

    QLinearGradient gradient(0, 0, 0, 100);
    gradient.setColorAt(0, QColor::fromRgbF(0, 1, .8, .2));
    gradient.setColorAt(1, QColor::fromRgbF(0, 1, 1, 0));

    _graphicsItem.setBrush(QBrush(gradient));
    connect(&_graphicsItem, SIGNAL(itemChanged(QGraphicsItem::GraphicsItemChange, const QVariant&)), this, SLOT(itemChanged(QGraphicsItem::GraphicsItemChange, const QVariant&)));
}

XSchemaSequence *SequenceItem::sequence() const
{
    return _item ;
}

void SequenceItem::setItem(XSchemaSequence *newItem)
{
    QString descr = "" ;
    if(_item != newItem) {
        if(NULL != _item) {
            disconnect(_item, SIGNAL(childAdded(XSchemaObject*)), this, SLOT(childAdded(XSchemaObject*)));
            //TODO disconnect(_item, SIGNAL(childRemoved(XSchemaObject*)), this, SLOT(childRemoved(XSchemaObject*)));
        }
        _item = newItem ;
        if(NULL != newItem) {
            connect(_item, SIGNAL(childAdded(XSchemaObject*)), this, SLOT(childAdded(XSchemaObject*)));
            //TODO connect(_item, SIGNAL(childRemoved(XSchemaObject*)), this, SLOT(childRemoved(XSchemaObject*)));
            foreach(XSchemaObject * child, _item->getChildren()) {
                childAdded(child);
            }
            descr = _item->description();
        }
    }
    _labelItem->setPlainText(descr);
}

void SequenceItem::itemChanged(QGraphicsItem::GraphicsItemChange change, const QVariant & /*value*/)
{
    if(change == QGraphicsItem::ItemPositionChange) {
        RChild *theChain = chain();
        if(NULL != theChain) {
            chain()->updatePosition();
            updateScenePosition(&_graphicsItem);
            foreach(RChild * child, _children.children()) {
                child->updatePosition();
            }
        }
    }
}

void SequenceItem::childAdded(XSchemaObject *newChild)
{
    if(NULL == newChild) {
        return ;
    }
    XSDItem *child = addChild(newChild);
    if(NULL == child) {
        Utils::error(tr("An error occurred inserting the graphic item corresponding to the object."));
    }
}


//-------------------------------------------------------------------------------
