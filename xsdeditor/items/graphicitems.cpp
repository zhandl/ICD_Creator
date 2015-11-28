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

GraphicsRectItem::GraphicsRectItem(ItemServiceExecutor *service, QGraphicsItem * parent) : QGraphicsRectItem(parent)
{
    setService(service);
}

GraphicsRectItem::~GraphicsRectItem()
{
}

void GraphicsRectItem::setService(ItemServiceExecutor *newService)
{
    _service = newService;
}

void GraphicsRectItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    if(NULL != _service) {
        _service->execMenuEvent(event, this);
    }
}

QVariant GraphicsRectItem::itemChange(GraphicsItemChange change,
                                      const QVariant &value)
{
    emit itemChanged(change, value);
    return QGraphicsItem::itemChange(change, value);
}

//-------------------------------------------------------------------------------

LineItem::LineItem(QGraphicsItem *newOne, QGraphicsItem *newOther, QGraphicsItem * parent, QGraphicsScene *scene)
    : QGraphicsLineItem(parent, scene)
{
    _one = newOne ;
    _other = newOther ;
}

LineItem::~LineItem()
{
}

void LineItem::updatePosition()
{
    if((NULL != _one) && (NULL != _other)) {
        QRectF r1 = _one->boundingRect();
        QRectF r2 = _other->boundingRect();
        //QLineF line( mapFromItem(_one, r1.left()+(r1.width()/2), r1.top()+(r1.height()/2)), mapFromItem(_other, r2.left()+(r2.width()/2), r2.top()+(r2.height()/2)) );
        QPointF pos1 = mapFromItem(_one, r1.left() + (r1.width() / 2), r1.top() + (r1.height() / 2)) ;
        QPointF pos2 = mapFromItem(_other, r2.left() + (r2.width() / 2), r2.top() + (r2.height() / 2)) ;
        QLineF line(pos1.x(), pos2.y(), pos2.x(), pos2.y());
        setLine(line);
    }
}

//--------------------------------------------------------------------------------
TextItem::TextItem(QGraphicsItem * parent) : QGraphicsTextItem(parent)
{
}

TextItem::~TextItem()
{
}

QVariant TextItem::itemChange(QGraphicsItem::GraphicsItemChange change,
                              const QVariant &value)
{
    emit itemChanged(change, value);
    return QGraphicsTextItem::itemChange(change, value);
}

//--------------------------------------------------------------------------------

PolygonItem::PolygonItem(ItemServiceExecutor *service, const bool doubleBorder, QGraphicsItem * parent) : QGraphicsPolygonItem(parent)
{
    setService(service);
    _isDoubleBorder = doubleBorder ;
    _color = QColor::fromRgb(0, 0, 0);
    _pen.setColor(_color);
}

PolygonItem::~PolygonItem()
{
}

void PolygonItem::setService(ItemServiceExecutor *newService)
{
    _service = newService;
}

void PolygonItem::setColor(const QColor newColor)
{
    _color = newColor ;
    _pen.setColor(_color);
}

void PolygonItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsPolygonItem::paint(painter, option, widget);
    if(_isDoubleBorder) {
        QRectF bounds = boundingRect();
        QPen oldPen = painter->pen();
        painter->setPen(_pen);
        painter->drawRoundedRect(bounds, 8, 8);
        bounds.adjust(4, 4, -4, -4);
        painter->drawRoundedRect(bounds, 8, 8);
        painter->setPen(oldPen);
    }
}


void PolygonItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    if(NULL != _service) {
        _service->execMenuEvent(event, this);
    }
}


QVariant PolygonItem::itemChange(GraphicsItemChange change,
                                 const QVariant &value)
{
    emit itemChanged(change, value);
    return QGraphicsItem::itemChange(change, value);
}

//--------------------------------------------------------------------------------

CircleItem::CircleItem(ItemServiceExecutor *service, QGraphicsItem * parent) : QGraphicsEllipseItem(parent)
{
    setService(service);
}

CircleItem::~CircleItem()
{
}

void CircleItem::setService(ItemServiceExecutor *newService)
{
    _service = newService;
}

void CircleItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    if(NULL != _service) {
        _service->execMenuEvent(event, this);
    }
}

QVariant CircleItem::itemChange(GraphicsItemChange change,
                                const QVariant &value)
{
    emit itemChanged(change, value);
    return QGraphicsItem::itemChange(change, value);
}

//--------------------------------------------------------------------------------
