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

#ifndef XGRAPHICSITEMS_H
#define XGRAPHICSITEMS_H

#include <QGraphicsItem>
#include <QPen>


enum {
    TypeBase = QGraphicsItem::UserType + 128,
    //TypeElement = QGraphicsItem::UserType + 129,
    //TypeAttribute = QGraphicsItem::UserType + 130,
    //TypeSchema = QGraphicsItem::UserType + 131,
    TypeText = QGraphicsItem::UserType + 132,
    TypeLine = QGraphicsItem::UserType + 133,
    //TypeChoice = QGraphicsItem::UserType + 134,
    TypeRectItem = QGraphicsItem::UserType + 135,
    TypePolygonItem = QGraphicsItem::UserType + 136,
    TypeCircleItem = QGraphicsItem::UserType + 137
};

#define IS_TYPE(xtype)  enum { Type = xtype }; virtual int type() const { return Type; }


class ItemServiceExecutor
{
public:
    virtual void execMenuEvent(QGraphicsSceneContextMenuEvent *event, QGraphicsItem *item) = 0 ;
};



class GraphicsRectItem : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    ItemServiceExecutor *_service ;

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

public:

    IS_TYPE(TypeRectItem)

    GraphicsRectItem(ItemServiceExecutor *service, QGraphicsItem * parent = 0);
    ~GraphicsRectItem();

    void setService(ItemServiceExecutor *newService);
signals:
    void itemChanged(QGraphicsItem::GraphicsItemChange change, const QVariant &value);
};


class PolygonItem : public QObject, public QGraphicsPolygonItem
{
    Q_OBJECT
    ItemServiceExecutor *_service ;
    bool _isDoubleBorder;
    QColor _color;
    QPen _pen;

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public:

    IS_TYPE(TypePolygonItem)

    PolygonItem(ItemServiceExecutor *service, const bool doubleBorder = false, QGraphicsItem * parent = 0);
    ~PolygonItem();

    void setService(ItemServiceExecutor *newService);
    void setColor(const QColor newColor);

signals:
    void itemChanged(QGraphicsItem::GraphicsItemChange change, const QVariant &value);
};

//------------------------

class CircleItem : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
    ItemServiceExecutor *_service ;

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

public:

    IS_TYPE(TypeCircleItem)

    CircleItem(ItemServiceExecutor *menuBuilder, QGraphicsItem * parent = 0);
    ~CircleItem();

    void setService(ItemServiceExecutor *newService);
signals:
    void itemChanged(QGraphicsItem::GraphicsItemChange change, const QVariant &value);
};

//------------------------

class TextItem : public QGraphicsTextItem
{
    Q_OBJECT

protected:
    QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value);

public:

    IS_TYPE(TypeText)

    TextItem(QGraphicsItem * parent = 0);
    ~TextItem();

signals:
    void itemChanged(QGraphicsItem::GraphicsItemChange change, const QVariant &value);
};

class LineItem : public QGraphicsLineItem
{
    QGraphicsItem *_one;
    QGraphicsItem *_other;

public:

    IS_TYPE(TypeLine)

    LineItem(QGraphicsItem *newOne, QGraphicsItem *newOther, QGraphicsItem * parent = 0, QGraphicsScene *scene = 0);
    ~LineItem();

    void updatePosition();
};


#endif // XGRAPHICSITEMS_H
