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

#define PIXMAP_XSD_INFO ":/xsdimages/documentinfo"
#define PIXMAP_XSD_LINK ":/xsdimages/link2"
#define PIXMAP_XSD_ATTRIBUTE ":/xsdimages/attrIcon"
#define PIXMAP_XSD_ELEMENT ":/xsdimages/attrElement"
#define PIXMAP_XSD_TYPE ":/xsdimages/attrType"
#define PIXMAP_XSD_EXTRA_ATTRS ":/xsdimages/extra-attributes"
//--------------------------------------------------------------------------------------
// TODO: remember to inject images in html with src: resources like that:<img src=':/xsdimages/link2'/>

//--------------------------------------------------------------------------------------

XItemMenuBuilder::XItemMenuBuilder(XSDItem * newItem)
{
    _item = newItem ;
    _rootMenuBuilder = NULL ;
}

XItemMenuBuilder::~XItemMenuBuilder()
{
}

void XItemMenuBuilder::setRootMenuBuilder(XMainMenuBuilder *rootMenuBuilder)
{
    _rootMenuBuilder = rootMenuBuilder ;
}

XMainMenuBuilder *XItemMenuBuilder::rootMenuBuilder()
{
    return _rootMenuBuilder ;
}


QMenu *XItemMenuBuilder::buildMenu()
{
    if(NULL != _rootMenuBuilder) {
        return _rootMenuBuilder->buildMenu(_item->item());
    }
    return NULL ;
}

//--------------------------------------------------------------------------------------

XSDItem::XSDItem(XsdGraphicContext *newContext) : _menuBuilder(this)
{
    _iconExtraAttrs = NULL ;
    _context = newContext;
    _chain = NULL ;
}

XSDItem::~XSDItem()
{
    //TODO removeObject( _item );
}

RChild *XSDItem::chain()
{
    return _chain ;
}

void XSDItem::setChain(RChild* newChain)
{
    _chain = newChain;
}

void XSDItem::setRootContext(XsdGraphicContext *value)
{
    _context = value ;
    if(NULL != _context) {
        _menuBuilder.setRootMenuBuilder(value->menuBuilder());
    }
}

void XSDItem::afterPositionChange()
{
    RChild *theChain = chain();
    if(NULL != theChain) {
        chain()->updatePosition();
    }
    foreach(RChild * child, _children.children()) {
        child->item()->afterPositionChange();
    }
}

void XSDItem::setObject(XSchemaObject *newObject, XSchemaObject *oldObject)
{
    Q_ASSERT(_context != NULL);
    _context->removeObject(oldObject);
    _context->addObject(newObject, this);
}

void XSDItem::removeObject(XSchemaObject *object)
{
    Q_ASSERT(_context != NULL);
    _context->removeObject(object);
}

void XSDItem::createExtraAttrsIcon(QGraphicsItem *parent, const int xPos)
{
    _iconExtraAttrs = new QGraphicsPixmapItem(parent);
    _iconExtraAttrs->hide();
    _iconExtraAttrs->setPos(xPos, 4);
    QPixmap pixmap ;
    pixmap.load(PIXMAP_XSD_EXTRA_ATTRS);
    _iconExtraAttrs->setPixmap(pixmap);
}

/**
  WARNING: this routine calls an asynchronous dispatch handler at the end of which
  the original item can even be destroyed, so after the exec() don't do anything that
  depends from this object or the caller
  */
void XSDItem::execMenuEvent(QGraphicsSceneContextMenuEvent *event, QGraphicsItem *item)
{
    if(NULL != item) {
        item->scene()->clearSelection();
        item->setSelected(true);
    }
    QMenu *menu = _menuBuilder.buildMenu();
    if(NULL != menu) {
        menu->exec(event->screenPos());
        delete menu;
    } else {
        Utils::error(tr("Cannot open menu"));
    }
    /** WARNING: DO NOT DO ANYTHING OTHER HERE
      */
}

//--------------------------------------------------------------------------------------


/** to judge what item has to be created is not the duty of the graphic item.
  Any type created in the original structure is legal.
  */
XSDItem *XSDItem::factoryCreateItem(XSchemaObject *newChild, QGraphicsItem *parent)
{
    if(NULL == newChild) {
        return NULL ;
    }
    ESchemaType type = newChild->getType()  ;
    XSDItem* newItem ;
    if(SchemaTypeAttribute == type) {
        newItem = new AttributeItem(_context, (XSchemaAttribute *)newChild, parent);
    } else if(SchemaTypeChoice  == type) {
        newItem = new ChoiceItem(_context, (XSchemaChoice *)newChild, parent);
    } else if(SchemaTypeSequence  == type) {
        newItem = new SequenceItem(_context, (XSchemaSequence *)newChild, parent);   //TODO
    } else if(SchemaTypeElement  == type) {
        newItem = new ElementItem(_context, (XSchemaElement *)newChild, parent);
    } else if(SchemaTypeSimpleTypeRestriction == type) {
        newItem = new RestrictionItem(_context, newChild, parent);
    } else if(SchemaTypeSimpleTypeList == type) {
        newItem = new ListItem(_context, (XSchemaSimpleTypeList*)newChild, parent);
    } else if(SchemaTypeSimpleTypeUnion == type) {
        newItem = new UnionItem(_context, (XSchemaSimpleTypeUnion*)newChild, parent);
    } else if(SchemaTypeInclude == type) {
        newItem = new GenericItem(_context, newChild, parent);
    } else if(SchemaTypeImport == type) {
        newItem = new GenericItem(_context, newChild, parent);
    } else if(SchemaTypeNotation == type) {
        newItem = new GenericItem(_context, newChild, parent);
    } else if(SchemaTypeAnnotation == type) {
        newItem = new GenericItem(_context, newChild, parent);
    } else if(SchemaTypeGroup == type) {
        newItem = new GenericItem(_context, newChild, parent);
    } else {
        newItem = new GenericItem(_context, newChild, parent);
    }

    return newItem ;
}

QRectF XSDItem::measureOptimumDimensions(const int nItems, QGraphicsItem ** items)
{
    QRectF childrenBoundsRect(0, 0, 0, 0); // = graphicItem()->boundingRect();
    // the children list must be tailored on the particular item.
    int nIterations = nItems ;
    while(nIterations --) {
        if((NULL != *items) && ((*items)->isVisible())) {
            QRectF childRect = (*items)->boundingRect();
            QPointF origin = (*items)->pos();
            childRect.translate(origin);
            QRectF chTemp = childrenBoundsRect.united(childRect);
            childrenBoundsRect = chTemp ;
        }
        items++;
    }
    //QRectF childrenBounds = graphicItem()->childrenBoundingRect() ;
    if(childrenBoundsRect.isEmpty()) {
        childrenBoundsRect = graphicItem()->boundingRect();
    }
    return childrenBoundsRect ;
}

QRectF XSDItem::measureOptimumDimensions(QList<QGraphicsItem*> &items)
{
    QRectF childrenBoundsRect(0, 0, 0, 0); // = graphicItem()->boundingRect();
    // the children list must be tailored on the particular item.
    foreach(QGraphicsItem * item, items) {
        if((NULL != item) && item->isVisible()) {
            QRectF childRect = item->boundingRect();
            QPointF origin = item->pos();
            childRect.translate(origin);
            QRectF chTemp = childrenBoundsRect.united(childRect);
            childrenBoundsRect = chTemp ;
        }
    }
    if(childrenBoundsRect.isEmpty()) {
        childrenBoundsRect = graphicItem()->boundingRect();
    }
    return childrenBoundsRect ;
}

XSDItem *XSDItem::addChild(XSchemaObject *child)
{
    XSDItem *xsdItem = factoryCreateItem(child, graphicItem());
    if(NULL != xsdItem) {
        xsdItem->setRootContext(_context);
        _children.init(this);
        // set the position of the new item
        newChildPosition(xsdItem->graphicItem());

        if(!_children.createChild(this, xsdItem)) {
            delete xsdItem ;
            xsdItem = NULL ;
        }

    }
    return xsdItem ;
}

qreal XSDItem::recalcChildrenPos()
{
    QGraphicsItem *parentItem = graphicItem() ;
    QPointF posParent = parentItem->scenePos();
    QPointF offset = posParent;
    QRectF bounds = parentItem->boundingRect();
    offset.setX(offset.x() + bounds .width());
    offset.setY(offset.y() + bounds .height());
    // finds the total height
    qreal totalHeight = 0;
    qreal startY = offset.y();
    qreal lastHeight = 0 ;
    qreal lastChildBounds = 0 ;
    foreach(RChild * rchild, _children.children()) {
        XSDItem *xsdItem = rchild->item();

        QGraphicsItem *child = xsdItem->graphicItem();
        offset.setY(startY + totalHeight);
        QPointF newPosGlobal(offset.x(), offset.y());
        //QPointF newPos = child->mapToScene(newPosGlobal);
        child->setPos(newPosGlobal);
        lastHeight = xsdItem->recalcChildrenPos();
        totalHeight += lastHeight + 10 ;
        lastChildBounds = child->boundingRect().height() ;
    }
    startY = offset.y() - (totalHeight / 2);
    if(startY < 0) {
        startY = 0 ;
    }

    if(NULL != _children._line) {
        qreal posX = bounds.width() / 2 ;
        _children._line->setLine(posX, bounds.height(),
                                 posX, bounds.height() + totalHeight - lastHeight - 10 + (lastChildBounds / 2));
    }
    return totalHeight + bounds.height();
}

void XSDItem::totalSize(QRectF &totalSize)
{
    QGraphicsItem *parentItem = graphicItem() ;
    QRectF boundsInParentCoordinated = parentItem->mapToParent(parentItem->boundingRect()).boundingRect();
    totalSize = totalSize.united(boundsInParentCoordinated);
    foreach(RChild * child, _children.children()) {
        QRectF childTotalSize(0, 0, 0, 0);
        child->item()->totalSize(childTotalSize);
        // converti il pos in top
        QRectF inThisCoords = parentItem->mapToParent(childTotalSize).boundingRect();
        totalSize = inThisCoords.united(totalSize);
    }
}

void XSDItem::newChildPosition(QGraphicsItem *newChild)
{
    QGraphicsItem *parentItem = graphicItem() ;
    QPointF posParent = parentItem->scenePos();
    QPointF offset = posParent;
    QRectF bounds = parentItem->boundingRect();
    offset.setX(offset.x() + bounds .width());
    offset.setY(offset.y() + bounds .height());
    // finds the total height
    qreal totalHeight = 0 ;
    foreach(RChild * rchild, _children.children()) {
        QGraphicsItem *child = rchild->item()->graphicItem();
        if(newChild != child)  {
            totalHeight += child->boundingRect().height();
        }
        totalHeight += 10 ;
    }
    qreal startY = offset.y() - (totalHeight / 2);
    if(startY < 0) {
        startY = 0 ;
    }
    foreach(RChild * rchild, _children.children()) {
        QGraphicsItem *child = rchild->item()->graphicItem();
        if(newChild != child)  {
            qreal height = child->boundingRect().height();
            offset.setY(startY + height);
            QPointF newPosGlobal(offset.x(), startY);
            QPointF newPos = child->mapToScene(newPosGlobal);
            child->setPos(newPos);
            startY += height ;
            startY += 10 ;
        }
    }

    QPointF newPosGlobal(offset.x(), startY);
    QPointF newPos = newChild->mapToScene(newPosGlobal);
    newChild->setPos(newPos);

    if(NULL != _children._line) {
        qreal posX = posParent.x() + bounds.width() / 2 ;
        _children._line->setLine(posX, posParent.y() + bounds.height(),
                                 posX, startY + newChild->boundingRect().height() / 2);

    }
}

void XSDItem::remove(XSchemaObject *child)
{
    int indexOfChild = _children.findObject(child);
    if(indexOfChild >= 0) {
        _children.deleteAt(indexOfChild);
    }
}

//--------------------------------------------------------------------------------------


RChild::RChild(XSDItem *newParent, XSDItem *newItem, LineItem *newLine)
{
    _item = newItem ;
    _line = newLine ;
    _parent = newParent ;
}

RChild::~RChild()
{
    if(NULL != _line) {
        //_line->scene()->removeItem(_line);
        delete _line ;
        _line = NULL ;
    }
    if(NULL != _item) {
        delete _item ;
        _item = NULL ;
    }
    _parent = NULL ;
}

void RChild::updatePosition()
{
    if(NULL != _line) {
        _line->updatePosition();
    }
}


int RChildren::findObject(XSchemaObject *object)
{
    foreach(RChild * child, _children) {
        if(child->item()->item() == object) {
            return _children.indexOf(child);
        }
    }
    return -1 ;
}

void RChildren::deleteAt(const int &position)
{
    RChild *child = _children.at(position);
    _children.removeAt(position);
    if(NULL != child) {
        delete child ;
    }
}

/*
RChild *RChild::parent()
{
    return _parent ;
}

void RChild::setParent( RChild* newParent )
{
    _parent = newParent ;
}
****/


//--------------------------------------------------------------------------------------


RootItem::RootItem(XsdGraphicContext *newContext) : XSDItem(newContext), _graphicsItem(this, NULL), _item(NULL)
{
    _graphicsItem.setData(XSD_ITEM_DATA, qVariantFromValue((void*)this));
    init();
}

RootItem::~RootItem()
{
}

void RootItem::init()
{
    QPainterPath path;
    /*path.moveTo(150, 50);
    path.arcTo(100, 0, 50, 50, 0, 90);
    path.arcTo(0, 0, 50, 50, 90, 90);
    path.arcTo(0, 50, 50, 50, 180, 90);
    path.arcTo(100, 50, 50, 50, 270, 90);
    path.lineTo(150, 25);*/
    path.addRoundedRect(0, 0, 100, 100, 16, 16);
    _contour = path.toFillPolygon();
    _graphicsItem.setPolygon(_contour);
    _graphicsItem.setFlag(QGraphicsItem::ItemIsMovable, false);
    _graphicsItem.setFlag(QGraphicsItem::ItemIsSelectable, true);
    _graphicsItem.setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    _graphicsItem.setFlag(QGraphicsItem::ItemIsSelectable, true);
    _graphicsItem.setPos(0, 0);
    QGraphicsTextItem *textItem = new QGraphicsTextItem(&_graphicsItem);
    if(NULL != textItem) {
        textItem->setPlainText(tr("Root"));
        textItem->setPos(30, 50);
        _graphicsItem.childItems().append(textItem);
        textItem->setDefaultTextColor(QColor::fromRgb(0, 0, 0));
    }
};


XSDSchema *RootItem::schema() const
{
    return _item ;
}

void RootItem::setItem(XSDSchema *newItem)
{
    if(_item != newItem) {
        if(NULL != _item) {
            disconnect(_item, SIGNAL(childAdded(XSchemaObject*)), this, SLOT(childAdded(XSchemaObject*)));
            disconnect(_item, SIGNAL(deleted(XSchemaObject*)), this, SLOT(deleted(XSchemaObject*)));
        }
        _item = newItem ;
        if(NULL != newItem) {
            connect(_item, SIGNAL(childAdded(XSchemaObject*)), this, SLOT(childAdded(XSchemaObject*)));
            connect(_item, SIGNAL(childRemoved(XSchemaObject*)), this, SLOT(childRemoved(XSchemaObject*)));
            connect(_item, SIGNAL(deleted(XSchemaObject*)), this, SLOT(objectDeleted(XSchemaObject*)));
            // follow the elements childrens
            foreach(XSchemaObject * child, _item->getChildren()) {
                childAdded(child);
            }
        }
    }
}

void RootItem::childAdded(XSchemaObject* newChild)
{
    if(NULL == newChild) {
        return ;
    }
    XSDItem *child = addChild(newChild);
    if(NULL == child) {
        Utils::error(tr("An error occurred inserting the graphic item corresponding to the object."));
    }
}

void RootItem::objectDeleted(XSchemaObject* /*self*/)
{
    //TODO _graphicsItem.childItems().clear(); // NO, DEVO FARE UN REMOVE!
    _graphicsItem.scene()->removeItem(&_graphicsItem);
    delete this;
}

void RootItem::childRemoved(XSchemaObject* child)
{
    remove(child);
}

//--------------------------------------------------------------------------------------

RChildren::RChildren()
{
    _line = NULL ;
}

RChildren::~RChildren()
{
    /*if( NULL != _line ) {
        QGraphicsScene *scene = _line->scene() ;
        if( NULL != scene ) {
            scene->removeItem(_line);
        }
        delete _line ; line is deleted by the parent item
        _line = NULL ;
    }*/
    reset();
}

void RChildren::reset()
{
    foreach(RChild * child, _children) {
        delete child;
    }
    _children.clear();
}

bool RChildren::init(XSDItem *parent)
{
    if(NULL == _line) {
        QGraphicsItem *parentItem = parent->graphicItem();
        _line = new QGraphicsLineItem(parentItem);
        if(NULL == _line) {
            return false;
        }
        return true;
        /* the item is already added to the scene.
        QGraphicsScene *scene = parentItem->scene() ;
        if(NULL != scene) {
            scene->addItem(_line);
            return true ;
        }*/
    }
    return false ;
}

bool RChildren::createChild(XSDItem *parent, XSDItem *item)
{
    QGraphicsItem *childItem = item->graphicItem();
    QGraphicsItem *parentItem = parent->graphicItem();

    init(parent);

    LineItem *line = new LineItem(parentItem, childItem/*, parent->graphicItem()*/);
    if(NULL != line) {
        RChild *child = new RChild(parent, item, line);
        if(NULL != child) {
            QGraphicsScene *scene = parentItem->scene() ;
            if(NULL != scene) {
                // item should be already added scene->addItem(childItem);
                scene->addItem(line);
            }
            _children.append(child);
            line->setZValue(std::min(parentItem->zValue() - 1, childItem->zValue()) - 1);
            item->setChain(child);
        } else {
            delete line ;
            line  = NULL ;
        }
    }
    return (NULL != line) ;
}


//--------------------------------------------------------------------------------


ElementItem::ElementItem(XsdGraphicContext *newContext, XSchemaElement *newItem, QGraphicsItem * parent)
    : XSDItem(newContext), _item(NULL),
      _graphicsItem(this, true),  //_textItem(&_graphicsItem), _labelItem(&_graphicsItem)
      _textItem(NULL), _propertiesItem(NULL), _iconInfo(NULL), _iconLink(NULL), _separator(NULL)
{
    parent->scene()->addItem(&_graphicsItem);
    _graphicsItem.setData(XSD_ITEM_DATA, qVariantFromValue((void*)this));
    init();
    setItem(newItem);
}

ElementItem::~ElementItem()
{
    /* if( NULL != _textItem ) {
         //TODO disconnect(_textItem, SIGNAL(itemChange(GraphicsItemChange,QVariant&)), this, SLOT(textChanged()) );
     }*/
    reset();
}

void ElementItem::reset()
{
    /*foreach( AttributeItem* attribute, _attributes){
        delete attribute ;
    }
    _attributes.clear();*/
    //_graphicsItem.childItems().clear();
    //_graphicsItem.scene()->removeItem(&_graphicsItem);
    //_graphicsItem.childItems().clear();
}

void ElementItem::init()
{
    //_contour = QRectF( 0, 0, 200, 80 );
    //_graphicsItem.setRect(_contour);
    _graphicsItem.setFlag(QGraphicsItem::ItemIsMovable, false);
    _graphicsItem.setFlag(QGraphicsItem::ItemIsSelectable, true);
    _graphicsItem.setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    _graphicsItem.setPos(0, 0);

    QLinearGradient gradient(0, 0, 0, 100);
    gradient.setColorAt(0, QColor::fromRgbF(0, 1, 0, 1));
    gradient.setColorAt(1, QColor::fromRgbF(1, 1, 1, 1));

    _graphicsItem.setBrush(QBrush(gradient));


    QPainterPath path;
    path.moveTo(0, 60);
    path.lineTo(0, 20);
    path.lineTo(30, 0);
    path.lineTo(200, 0);
    path.lineTo(200, 60);
    path.lineTo(0, 60);

    _contour = path.toFillPolygon();
    _graphicsItem.setPolygon(_contour);
    //QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(&_graphicsItem);
    //_graphicsItem.setGraphicsEffect(effect);

    _propertiesItem = new QGraphicsTextItem(&_graphicsItem);
    _propertiesItem->setPlainText(tr("Element"));
    _propertiesItem->setPos(25, 30);
    _propertiesItem->setDefaultTextColor(QColor::fromRgb(0, 0, 0));
    _graphicsItem.childItems().append(_propertiesItem);

    //TODO _textItem->setTextInteractionFlags(Qt::TextEditable);
    _textItem = new QGraphicsTextItem(&_graphicsItem);
    _textItem->setPos(45, 10);
    _textItem->setDefaultTextColor(QColor::fromRgb(0, 0, 0));

    _graphicsItem.setPen(QPen(Qt::NoPen));
    _graphicsItem.childItems().append(_textItem);

    _iconInfo = new QGraphicsPixmapItem(&_graphicsItem);
    _iconInfo->hide();
    _iconInfo->setPos(24, 4);
    QPixmap pixmap ;
    pixmap.load(PIXMAP_XSD_INFO);
    _iconInfo->setPixmap(pixmap);

    createExtraAttrsIcon((&_graphicsItem), 24);

    _iconType = new QGraphicsPixmapItem(&_graphicsItem);
    _iconType->setPos(4, 14);

    _separator = new QGraphicsLineItem(&_graphicsItem);
    _separator->setLine(0, 0, 20, 25);

    //_graphicsItem.scene()->addItem(&_textItem);
    //TODO connect(_textItem, SIGNAL(itemChanged(GraphicsItemChange, QVariant&)), this, SLOT(textChanged()));
    connect(&_graphicsItem, SIGNAL(itemChanged(QGraphicsItem::GraphicsItemChange, const QVariant&)), this, SLOT(itemChanged(QGraphicsItem::GraphicsItemChange, const QVariant&)));
}

XSchemaElement *ElementItem::element() const
{
    return _item ;
}

void ElementItem::setItem(XSchemaElement *newItem)
{
    QString annotationInfo;
    bool showInfo = false;
    if(_item != newItem) {
        removeObject(_item);
        QString newName = "";
        QString newDescription = "";
        if(NULL != _item) {
            disconnect(_item, SIGNAL(nameChanged(QString)), this, SLOT(elmNameChanged(QString)));
            disconnect(_item, SIGNAL(childAdded(XSchemaObject*)), this, SLOT(childAdded(XSchemaObject*)));
            //TODO disconnect(_item, SIGNAL(childRemoved(XSchemaObject*)), this, SLOT(childRemoved(XSchemaObject*)));
            //disconnect( _item, SIGNAL(itemChanged(QGraphicsItem::GraphicsItemChange,QVariant&)), this, SLOT(itemChanged(QGraphicsItem::GraphicsItemChange,QVariant&)));
        }
        _item = newItem ;
        if(NULL != newItem) {
            setObject(newItem, NULL);
            connect(_item, SIGNAL(nameChanged(QString)), this, SLOT(elmNameChanged(QString)));
            connect(_item, SIGNAL(childAdded(XSchemaObject*)), this, SLOT(childAdded(XSchemaObject*)));
            // TODO connect(_item, SIGNAL(childRemoved(XSchemaObject*)), this, SLOT(childRemoved(XSchemaObject*)));
            //connect( _item, SIGNAL(itemChanged(QGraphicsItem::GraphicsItemChange,QVariant&)), this, SLOT(itemChanged(QGraphicsItem::GraphicsItemChange,QVariant&)));
            foreach(XSchemaObject * child, _item->getChildren()) {
                childAdded(child);
            }
            foreach(XSchemaAttribute * attr, _item->attributes()) {
                childAdded(attr);
            }
            newName = _item->name();
            newDescription = _item->description();
            if(NULL != _item->annotation()) {
                showInfo = true ;
                annotationInfo = _item->annotation()->text();
            }
        }
        //_labelItem->setPlainText(newDescription);
    }
    // TODO: refactor
    if(showInfo) {
        _iconInfo->show();
        _iconInfo->setToolTip(annotationInfo);
    } else {
        _iconInfo->hide();
    }
    setIconType();
    if(NULL != newItem) {

        // TODO: move the icons as appropriated
        _textItem->setPlainText(_item->nameDescr());
        QString occurences = _item->occurrencesDescr();
        QString type = _item->xsdType();
        QString simpleComplex = _item->simpleComplexDescr();
        QString typeHTML ;
        if(!type.isEmpty()) {
            typeHTML += tr("<span style='background-color:#ECC;'><span style='font-weight:bold;font-size:9pt'>type:</span>");
            typeHTML += QString("&nbsp;<span style='font-size:8pt' >%1</span></span> ").arg(type);
        }
        if(!occurences.isEmpty()) {
            typeHTML += QString(" &nbsp;&nbsp;<span style='color:#048; background-color:#FFF;padding-top:4px;padding-bottom:4px;font-size:10pt'>&nbsp;&nbsp;%1&nbsp;&nbsp;</span> ").arg(occurences);
        }
        if(!simpleComplex.isEmpty()) {
            typeHTML += QString(" &nbsp;&nbsp;<span style='font-style:italic'>&nbsp;&nbsp;%1</span>").arg(simpleComplex);
        }

        _propertiesItem->setHtml(typeHTML);

        // simple type?
        bool isSimpleTypeInElements = (newItem-> isTypeOrElement()
                                       && (newItem->category() == XSchemaElement::EES_SIMPLETYPE_ONLY)
                                       && (newItem->xsdParent()->getType() != SchemaTypeSchema));
        QRectF size ;
        QList<QGraphicsItem*> items;
        items.append(_iconType);
        if(isSimpleTypeInElements) {
            items.append(_propertiesItem);
            items.append(_iconInfo);
            items.append(_iconLink) ;
        } else {
            items.append(_textItem);
            items.append(_propertiesItem);
            items.append(_iconInfo);
            items.append(_iconLink);
        }
        if(_item->hasOtherAttributes()) {
            _iconExtraAttrs->setVisible(true);
            items.append(_iconExtraAttrs);
            _iconExtraAttrs->setToolTip(_item->getOhterAttrsAsTextList());
        }
        size = measureOptimumDimensions(items);
        qreal width = size.x() + size.width() + 10;
        qreal height = size.y() + size.height() ;//+ 10;

        _separator->setLine(20, 28, width - 10, 28);

        if(isSimpleTypeInElements) {
            QPainterPath path;
            path.moveTo(0, height);
            path.lineTo(0, 20);
            path.lineTo(30, 0);
            path.lineTo(width, 0);
            path.lineTo(width, height);
            path.lineTo(0, height);
            _graphicsItem.setColor(QColor::fromRgb(.2, .6, .1));

            _contour = path.toFillPolygon();
            _graphicsItem.setPolygon(_contour);

        } else {
            QPainterPath path;
            path.moveTo(0, height);
            path.lineTo(0, 0);
            path.lineTo(width, 0);
            path.lineTo(width, height);
            path.lineTo(0, height);
            _graphicsItem.setColor(QColor::fromRgb(.8, .4, .1));

            _contour = path.toFillPolygon();
            _graphicsItem.setPolygon(_contour);
        }
    } else {
        _textItem->setPlainText("");
        _propertiesItem->setPlainText("");
    }
    changeGraphics();
}

void ElementItem::setIconType()
{
    QPixmap pixmap ;
    if(NULL == _item) {
        _iconType->hide();
    }
    if(_item->isTypeOrElement()) {
        pixmap.load(PIXMAP_XSD_TYPE);
    } else {
        pixmap.load(PIXMAP_XSD_ELEMENT);
    }
    _iconType->setPixmap(pixmap);
}

void ElementItem::elmNameChanged(const QString &newName)
{
    _textItem->setPlainText(newName);
}

void ElementItem::textChanged()
{
    if(NULL != _item) {
        _item->setName(_textItem->toPlainText());
    }
}

void ElementItem::changeGraphics()
{
    if(NULL == _item) {
        return ;
    }
    if(_item->isTypeOrElement()) {
        QLinearGradient gradient(0, 0, 0, 100);
        gradient.setColorAt(0, QColor::fromRgb(192, 255, 102, 234));
        gradient.setColorAt(1, QColor::fromRgb(220, 255, 220, 255));
        QRectF bounds = _graphicsItem.boundingRect();
        gradient.setStart(QPointF(0, bounds.height() / 2));
        gradient.setFinalStop(QPointF(bounds.width(), bounds.height() / 2));

        _graphicsItem.setBrush(QBrush(gradient));
    } else {
        QLinearGradient gradient(0, 0, 0, 100);
        gradient.setColorAt(0, QColor::fromRgb(192, 240, 255, 234));
        gradient.setColorAt(1, QColor::fromRgb(220, 240, 255, 255));
        QRectF bounds = _graphicsItem.boundingRect();
        gradient.setStart(QPointF(0, bounds.height() / 2));
        gradient.setFinalStop(QPointF(bounds.width(), bounds.height() / 2));

        _graphicsItem.setBrush(QBrush(gradient));
    }
    if(! _item->ref().isEmpty()) {
        if(NULL == _iconLink) {
            _iconLink = new QGraphicsPixmapItem(&_graphicsItem);
            QPixmap pixmap ;
            pixmap.load(PIXMAP_XSD_LINK);
            _iconLink->setPixmap(pixmap);
        }
        if(_iconInfo->isVisible()) {
            _iconLink ->setPos(65, 6);
            _textItem->setPos(45, 10);
        } else {
            _iconLink->setPos(24, 6);
            _textItem->setPos(45, 10);
        }
    } else {
        if(NULL != _iconLink) {
            _iconLink->hide();
            _textItem->setPos(25, 10);
        }
    }
}


void ElementItem::itemChanged(QGraphicsItem::GraphicsItemChange change, const QVariant & /*value*/)
{
    if(change == QGraphicsItem::ItemPositionChange) {
        RChild *theChain = chain();
        if(NULL != theChain) {
            chain()->updatePosition();
            updateScenePosition(&_graphicsItem);
        }
        foreach(RChild * child, _children.children()) {
            child->updatePosition();
        }
    }
}

void ElementItem::childAdded(XSchemaObject *newChild)
{
    if(NULL == newChild) {
        return ;
    }
    XSDItem *child = NULL ;
    /*ESchemaType type = newChild->getType()  ;
    if( SchemaTypeAttribute == type ) { TODO
        child = addAttribute( (XSchemaAttribute *)newChild, QPointF(0,0) );
    } else  {*/
    child = addChild(newChild);
    /*}*/
    if(NULL == child) {
        Utils::error(tr("An error occurred inserting the graphic item corresponding to the object."));
    }
}

AttributeItem *ElementItem::addAttribute(XSchemaAttribute *attribute, QPointF /*pos*/)
{
    AttributeItem *attributeItem = new AttributeItem(_context, attribute, graphicItem());
    if(NULL != attributeItem) {
        _attributes.append(attributeItem);

        //graphicItem()->scene()->addItem(attributeItem->graphicItem());
        attributeItem->graphicItem()->setPos(10, 22 * _attributes.size());
        //TODO _contour.setHeight(_contour.height()+22);
        //TODO _graphicsItem.setRect(_contour);
    }
    return attributeItem ;
}


//--------------------------------------------------------------------------

AttributeItem::AttributeItem(XsdGraphicContext *newContext, XSchemaAttribute *newItem, QGraphicsItem * parent)
    : XSDItem(newContext),
      _item(NULL), _graphics(this), _textItem(NULL), _iconInfo(NULL)
{
    parent->scene()->addItem(&_graphics);
    _graphics.setData(XSD_ITEM_DATA, qVariantFromValue((void*)this));
    init();
    setItem(newItem);
}

AttributeItem::~AttributeItem()
{
    //if( NULL != _textItem ) {
    //TODO disconnect(_textItem, SIGNAL(itemChange(GraphicsItemChange,QVariant&)), this, SLOT(textChanged()) );
    //}
}

void AttributeItem::init()
{
    _contour = QRectF(0, 0, 80, 20);
    _graphics.setRect(_contour);
    _graphics.setFlag(QGraphicsItem::ItemIsMovable, false);
    _graphics.setFlag(QGraphicsItem::ItemIsSelectable, true);
    _graphics.setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    _graphics.setPos(0, 0);

    QLinearGradient gradient(0, 0, 0, 100);
    gradient.setColorAt(0, QColor::fromRgbF(1, 1, .5, 1));
    gradient.setColorAt(1, QColor::fromRgbF(1, 1, .7, 0.9));

    _graphics.setBrush(QBrush(gradient));
    _textItem = new TextItem(&_graphics);
    _textItem->setPos(24, 0);
    _textItem->setDefaultTextColor(QColor::fromRgb(0, 0, 0));

    _iconType = new QGraphicsPixmapItem(&_graphics);
    _iconType ->setPos(4, 4);
    QPixmap pixmap ;
    pixmap.load(PIXMAP_XSD_ATTRIBUTE);
    _iconType->setPixmap(pixmap);

    _iconInfo = new QGraphicsPixmapItem(&_graphics);
    _iconInfo->hide();
    _iconInfo->setPos(24, 4);
    QPixmap pixmapInfo ;
    pixmapInfo.load(PIXMAP_XSD_INFO);
    _iconInfo->setPixmap(pixmapInfo);

    createExtraAttrsIcon(&_graphics, 24);

    //_textItem->setTextInteractionFlags(Qt::TextEditable);
    _graphics.childItems().append(_textItem);
    //TODO connect(_textItem, SIGNAL(itemChange(GraphicsItemChange, QVariant&)), this, SLOT(textChanged()));
}

XSchemaAttribute *AttributeItem::item() const
{
    return _item ;
}

void AttributeItem::setItem(XSchemaAttribute *newItem)
{
    QString annotationInfo ;
    if(_item != newItem) {
        QString newName = "";
        if(NULL != _item) {
            removeObject(_item);
            disconnect(_item, SIGNAL(nameChanged(QString)), this, SLOT(nameChanged(QString)));
            //TODO
        }
        _item = newItem ;
        if(NULL != newItem) {
            setObject(newItem, NULL);
            connect(_item, SIGNAL(nameChanged(QString)), this, SLOT(nameChanged(QString)));
            foreach(XSchemaObject * child, _item->getChildren()) {
                childAdded(child);
            }
            newName = _item->description();
            if(NULL != _item->annotation()) {
                annotationInfo = _item->annotation()->text();
            }
        }
        _textItem->setPlainText(tr("%1").arg(newName));
    }

    if(!annotationInfo.isEmpty()) {
        _textItem->setPos(48, 0);
        _iconInfo->setToolTip(annotationInfo);
        _iconInfo->show();
    } else {
        _textItem->setPos(24, 0);
        _iconInfo->hide();
    }
    QList<QGraphicsItem*> items;
    items.append(_textItem);
    if(_item->hasOtherAttributes()) {
        _iconExtraAttrs->setVisible(true);
        items.append(_iconExtraAttrs);
        _iconExtraAttrs->setToolTip(_item->getOhterAttrsAsTextList());
    }
    QRectF size = measureOptimumDimensions(items);
    qreal width = size.x() + size.width() + 10;
    qreal height = size.y() + size.height() + 10;
    _contour = QRectF(0, 0, width, height);
    _graphics.setRect(_contour);
}

void AttributeItem::childAdded(XSchemaObject *newChild)
{
    XSDItem *child = NULL ;
    if(NULL == newChild) {
        return ;
    }
    if(newChild->getType() == SchemaTypeElement) {
        // look for childrens (this is a simple type with restrictions and so on )
        QList<XSchemaObject*> elementChildren = newChild->getChildren();
        if(!elementChildren.isEmpty()) {
            // att: non deve essere una annotation, ma un simple type
            XSchemaObject* st = elementChildren.at(0);
            child = addChild(st);
        }
    } else {
        child = addChild(newChild);
    }
    if(NULL == child) {
        Utils::error(tr("An error occurred inserting the graphic item corresponding to the object."));
    }
}


void AttributeItem::nameChanged(const QString &newName)
{
    //if( NULL != _textItem ) {
    _textItem->setPlainText(newName);
    //}
}

void AttributeItem::textChanged()
{
    if(/*( NULL != _textItem ) &&*/ (NULL != _item)) {
        _item->setName(_textItem->toPlainText());
    }
}


//--------------------------------------------------------------------------------------

GenericItem::GenericItem(XsdGraphicContext *newContext, XSchemaObject *newItem, QGraphicsItem * parent)
    : XSDItem(newContext), _item(NULL), _graphicsItem(this),
      _icon(NULL), _textItem(NULL), _iconInfo(NULL)
{
    parent->scene()->addItem(&_graphicsItem);
    _graphicsItem.setData(XSD_ITEM_DATA, qVariantFromValue((void*)this));
    init();
    setItem(newItem);
}

GenericItem::~GenericItem()
{
    /* if( NULL != _textItem ) {
         //TODO disconnect(_textItem, SIGNAL(itemChange(GraphicsItemChange,QVariant&)), this, SLOT(textChanged()) );
     }*/
    reset();
}

void GenericItem::reset()
{
    /*foreach( AttributeItem* attribute, _attributes){
        delete attribute ;
    }
    _attributes.clear();*/
}


void GenericItem::init()
{
    //_contour = QRectF( 0, 0, 100, 100 );
    QPainterPath path;
    path.moveTo(150, 50);
    path.arcTo(100, 0, 50, 50, 0, 90);
    path.arcTo(0, 0, 50, 50, 90, 90);
    path.arcTo(0, 50, 50, 50, 180, 90);
    path.arcTo(100, 50, 50, 50, 270, 90);
    path.lineTo(150, 25);
    _contour = path.toFillPolygon();
    _graphicsItem.setPolygon(_contour);

    _graphicsItem.setFlag(QGraphicsItem::ItemIsMovable, false);
    _graphicsItem.setFlag(QGraphicsItem::ItemIsSelectable, true);
    _graphicsItem.setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    _graphicsItem.setPos(0, 0);

    /*_icon = new QGraphicsPixmapItem(&_graphicsItem);
    _icon->setPos(10, 10 );*/
    setGraphics(QColor::fromRgbF(1, 1, 1, 1));

    _textItem = new QGraphicsTextItem(&_graphicsItem);
    _textItem->setPos(30, 10);
    _textItem->setDefaultTextColor(QColor::fromRgb(0, 0, 0));

    _iconInfo = new QGraphicsPixmapItem(&_graphicsItem);
    _iconInfo->hide();
    _iconInfo ->setPos(10, 10);
    QPixmap pixmap ;
    pixmap.load(PIXMAP_XSD_INFO);
    _iconInfo->setPixmap(pixmap);
    createExtraAttrsIcon((&_graphicsItem), 24);

    //_graphicsItem.childItems().append(&_textItem);
    //_graphicsItem.scene()->addItem(&_textItem);
    //TODO connect( &_textItem, SIGNAL(itemChanged(GraphicsItemChange,QVariant&)), this, SLOT(textChanged()) );
    connect(&_graphicsItem, SIGNAL(itemChanged(QGraphicsItem::GraphicsItemChange, const QVariant&)), this, SLOT(itemChanged(QGraphicsItem::GraphicsItemChange, const QVariant&)));
}

/* TODO
XSchemaObject *GenericItem::item() const
{
    return _item ;
}
*/

void GenericItem::setGraphics(/*const QPixmap & pixmap,*/ QColor bkColor)
{
    QLinearGradient gradient(0, 0, 0, 100);
    QColor clr2(bkColor);
    clr2 = clr2.lighter();
    clr2.setAlpha(100);
    gradient.setColorAt(0, bkColor);
    gradient.setColorAt(1, clr2);
    _graphicsItem.setBrush(QBrush(gradient));
    //_icon->setPixmap(pixmap);
}

void GenericItem::setItem(XSchemaObject *newItem)
{
    QString annotationInfo;
    bool showInfo = false;
    if(_item != newItem) {
        if(NULL != _item) {
            removeObject(_item);
            //TODO disconnect( _item, SIGNAL(nameChanged(QString)), this, SLOT(elmNameChanged(QString)) );
            disconnect(_item, SIGNAL(childAdded(XSchemaObject*)), this, SLOT(childAdded(XSchemaObject*)));
            //TODO disconnect(_item, SIGNAL(childRemoved(XSchemaObject*)), this, SLOT(childRemoved(XSchemaObject*)));
            //disconnect( _item, SIGNAL(itemChanged(QGraphicsItem::GraphicsItemChange,QVariant&)), this, SLOT(itemChanged(QGraphicsItem::GraphicsItemChange,QVariant&)));
        }
        _item = newItem ;
        if(NULL != newItem) {
            setObject(_item, NULL);
            //TODO connect( _item, SIGNAL(nameChanged(QString)), this, SLOT(elmNameChanged(QString)) );
            connect(_item, SIGNAL(childAdded(XSchemaObject*)), this, SLOT(childAdded(XSchemaObject*)));
            //TODO connect(_item, SIGNAL(childRemoved(XSchemaObject*)), this, SLOT(childRemoved(XSchemaObject*)));
            //connect( _item, SIGNAL(itemChanged(QGraphicsItem::GraphicsItemChange,QVariant&)), this, SLOT(itemChanged(QGraphicsItem::GraphicsItemChange,QVariant&)));
            _textItem->setPlainText(newItem->description());
            setGraphics(/*newItem->icon(),*/ newItem->color());
            foreach(XSchemaObject * child, _item->getChildren()) {
                childAdded(child);
            }
            if(NULL != _item->annotation()) {
                showInfo = true ;
                annotationInfo = _item->annotation()->text();
            }
        } else {
            setGraphics(QColor(0, 0, 0, 0));
            _textItem->setPlainText("");
        }
    }
    // TODO: refactor
    if(showInfo) {
        _iconInfo->show();
        _iconInfo->setToolTip(annotationInfo);
    } else {
        _iconInfo->hide();
    }
    QList<QGraphicsItem*> items;
    items.append(_icon);
    items.append(_textItem);
    items.append(_iconInfo);
    if(_item->hasOtherAttributes()) {
        _iconExtraAttrs->setVisible(true);
        items.append(_iconExtraAttrs);
        _iconExtraAttrs->setToolTip(_item->getOhterAttrsAsTextList());
    }
    QRectF size = measureOptimumDimensions(items) ;
    QPainterPath path;
    qreal width = size.x() + size.width() + 10;
    qreal height = size.y() + size.height() + 20;
    /*path.moveTo( width, height/4);
    path.arcMoveTo((qreal)width-50, (qreal)0, (qreal)50, (qreal)height/4, (qreal)90);
    path.lineTo(50, 0);
    path.arcMoveTo( (qreal)0, (qreal)0, (qreal)50, (qreal)height/4, (qreal)90);
    path.lineTo(0, height - height/4);
    path.arcMoveTo((qreal)0, (qreal)height - height/4, (qreal)50, (qreal)height, (qreal)90);
    //path.arcTo(width-50, height-50, 50, 50, 270, 90);
    //path.lineTo(width+20, height);*/

    path.moveTo(0, 0);
    path.lineTo(width, 0);
    path.lineTo(width, height);
    path.lineTo(0, height);
    _contour = path.toFillPolygon();
    _graphicsItem.setPolygon(_contour);

}

/*TODO
void GenericItem::textChanged()
{
    if( NULL != _item ){
        _item->setName(_textItem.toPlainText());
    }
}*/

void GenericItem::itemChanged(QGraphicsItem::GraphicsItemChange change, const QVariant & /*value*/)
{
    if(change == QGraphicsItem::ItemPositionChange) {
        RChild *theChain = chain();
        if(NULL != theChain) {
            chain()->updatePosition();
            updateScenePosition(&_graphicsItem);
        }
        foreach(RChild * child, _children.children()) {
            child->updatePosition();
        }
    }
}

void GenericItem::childAdded(XSchemaObject *newChild)
{
    if(NULL == newChild) {
        return ;
    }
    XSDItem *child = NULL ;
    child = addChild(newChild);
    if(NULL == child) {
        Utils::error(tr("An error occurred inserting the graphic item corresponding to the object."));
    }
}


void updateScenePosition(QGraphicsItem * /*item*/)
{
    /* TODO QGraphicsScene *scene = item->scene();
    if( NULL != scene ) {
        QRectF rectItem = item->boundingRect () ;
        QRectF rectItemToScene = item->mapRectToScene(rectItem);
        QRectF sceneRect = scene->sceneRect();
        bool isChanged = false ;
        int itemX = rectItemToScene.left()+rectItemToScene.width() ;
        if( itemX > scene->width() ) {
            sceneRect.setWidth(itemX);
            isChanged = true ;
        }
        int itemY = rectItemToScene.top()+ rectItemToScene.height();
        if( itemY > scene->height() ) {
           sceneRect.setHeight(itemY);
           isChanged = true ;
        }
        if( isChanged ) {
            scene->setSceneRect(sceneRect);
        }
    }*/
}
