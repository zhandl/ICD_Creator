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
#ifndef XSDWINDOW_H
#define XSDWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>

#include "xsdeditor/xschema.h"
#include "xsdeditor/items/xgraphicsitems.h"
#include "xsdeditor/xsdgraphiccontext.h"


namespace Ui
{
class XSDWindow;
}

#define XSD_ITEM_DATA   0

class XSDScene : public QGraphicsScene
{
    Q_OBJECT

public:
    XSDScene();
    ~XSDScene();

    void updateBounds();
    void gotoItem(QGraphicsItem *item);
};

#include <QtGui>



class ElementItem ;
class ChoiceItem ;
/**
  questa classe serve a tenere i collegamenti tra la finestra dell'editor
  e l'elemento generico. Da fuori accedo all'item e all'oggetto contenuto
  TODO: decidere se va derivata o posseduta. Se derivo, posso implmentare
      i metodi.
  **/


class RChild;
class XSDItem ;

class XMainMenuBuilder
{
public:
    virtual QMenu *buildMenu(XSchemaObject *item) = 0;
};

class ItemMenuBuilder
{
public:
    virtual QMenu *buildMenu() = 0;
};

class XItemMenuBuilder : public ItemMenuBuilder
{
    XSDItem * _item ;
    XMainMenuBuilder *_rootMenuBuilder;

public:
    virtual QMenu *buildMenu();
    explicit XItemMenuBuilder(XSDItem * newItem) ;
    ~XItemMenuBuilder();

    void setRootMenuBuilder(XMainMenuBuilder *rootMenuBuilder);
    XMainMenuBuilder *rootMenuBuilder();
};


/**
  questa classe gestisce i figli a livello grafico
  */


class RChild
{
    XSDItem *_item;
    XSDItem *_parent;
    LineItem *_line;
public:
    RChild(XSDItem *newParent, XSDItem *newItem, LineItem *newLine);
    ~RChild();
    XSDItem *item() const {
        return _item ;
    }
    void updatePosition() ;
};

class RChildren
{
    QList<RChild*> _children;

public:
    QGraphicsLineItem* _line;
    RChildren();
    ~RChildren();

    //bool addChild( XSDItem *item );
    void reset();
    bool createChild(XSDItem *parent, XSDItem *item);
    QList<RChild*> &children() {
        return _children;
    }
    int findObject(XSchemaObject *object);
    void deleteAt(const int &position);
    bool init(XSDItem *parent);
};

class XSDItem : public QObject, protected ItemServiceExecutor
{
    Q_OBJECT
protected:
    RChildren _children ;
    XsdGraphicContext * _context;
    XItemMenuBuilder _menuBuilder;
    RChild  *_chain;
    QGraphicsPixmapItem *_iconExtraAttrs;

    void setObject(XSchemaObject *newObject, XSchemaObject *oldObject);
    void removeObject(XSchemaObject *object);
    void createExtraAttrsIcon(QGraphicsItem *parent, const int xPos);

public:
    XSDItem(XsdGraphicContext *newContext);
    virtual ~XSDItem();

    XSDItem *addChild(XSchemaObject *child);
    XSDItem *factoryCreateItem(XSchemaObject *newChild, QGraphicsItem *parent);
    void remove(XSchemaObject *child);
    void newChildPosition(QGraphicsItem *newChild);
    virtual QGraphicsItem *graphicItem() = 0;
    virtual XSchemaObject *item() = 0;
    RChild *chain();
    void setChain(RChild* newChain);
    void setRootContext(XsdGraphicContext *value) ;
    void totalSize(QRectF &totalSize);
    qreal recalcChildrenPos();
    void afterPositionChange();
    QRectF measureOptimumDimensions(const int nItems, QGraphicsItem ** items);
    QRectF measureOptimumDimensions(QList<QGraphicsItem*> &items);
    void execMenuEvent(QGraphicsSceneContextMenuEvent *event, QGraphicsItem *item) ;
};


class RootItem : public XSDItem
{
    Q_OBJECT

    PolygonItem _graphicsItem;
    QPolygonF _contour;
    XSDSchema *_item;
    RChildren _children;

    void init();

public:
    //IS_TYPE(TypeSchema)

    RootItem(XsdGraphicContext *newContext);
    ~RootItem();

    XSDSchema *schema() const;
    void setItem(XSDSchema *newItem)  ;
    virtual QGraphicsItem *graphicItem() {
        return &_graphicsItem ;
    }
    virtual XSchemaObject *item() {
        return _item ;
    }

private slots:
    void childAdded(XSchemaObject* newChild);
    void objectDeleted(XSchemaObject* child);
    void childRemoved(XSchemaObject* child);

};


class AttributeItem : public XSDItem
{
    Q_OBJECT
    QRectF _contour;
    XSchemaAttribute *_item;
    GraphicsRectItem _graphics;
    TextItem *_textItem ;
    RChildren _children ;
    QGraphicsPixmapItem *_iconLink;
    QGraphicsPixmapItem *_iconType;
    QGraphicsPixmapItem *_iconInfo;

    void init();

private slots:

    void textChanged();
    void nameChanged(const QString &newName);
    void childAdded(XSchemaObject *newChild);

public:

    AttributeItem(XsdGraphicContext *newContext, XSchemaAttribute *newItem, QGraphicsItem * parent = 0);
    ~AttributeItem();

    XSchemaAttribute *item() const ;
    void setItem(XSchemaAttribute *newItem)  ;

    virtual QGraphicsItem *graphicItem() {
        return &_graphics ;
    }
    virtual XSchemaObject *item() {
        return _item ;
    }

};


class ElementItem : public XSDItem
{
    Q_OBJECT

    QPolygonF _contour;
    XSchemaElement *_item;
    PolygonItem _graphicsItem;
    QGraphicsTextItem *_textItem ;
    QGraphicsTextItem *_propertiesItem ;
    QList<AttributeItem*> _attributes;
    RChildren _children ;
    QGraphicsPixmapItem *_iconInfo;
    QGraphicsPixmapItem *_iconLink;
    QGraphicsPixmapItem *_iconType;
    QGraphicsLineItem *_separator;

    void init();
    void reset();

private slots:
    void textChanged();
    void elmNameChanged(const QString &newName);
    void itemChanged(QGraphicsItem::GraphicsItemChange change, const QVariant &value);
    void childAdded(XSchemaObject *newChild);

protected:
    void setIconType();

public:

    //IS_TYPE(TypeElement)

    ElementItem(XsdGraphicContext *newContext, XSchemaElement *newItem, QGraphicsItem * parent = 0);
    virtual ~ElementItem();

    XSchemaElement *element() const ;
    void setItem(XSchemaElement *newItem)  ;

    virtual QGraphicsItem *graphicItem() {
        return &_graphicsItem ;
    }
    virtual XSchemaObject *item() {
        return _item ;
    }

    virtual AttributeItem *addAttribute(XSchemaAttribute *attribute, QPointF pos);

    void changeGraphics();
};

class ChoiceItem : public XSDItem
{
    Q_OBJECT

    QRectF _contour;
    XSchemaChoice *_item;
    CircleItem _graphicsItem;
    QGraphicsTextItem *_labelItem;
    RChildren _children ;

    void init();
    void reset();

private slots:
    void itemChanged(QGraphicsItem::GraphicsItemChange change, const QVariant &value);
    void childAdded(XSchemaObject *newChild);

public:

    ChoiceItem(XsdGraphicContext *newContext, XSchemaChoice *newItem, QGraphicsItem * parent = 0);
    ~ChoiceItem();

    XSchemaChoice *choice() const ;
    void setItem(XSchemaChoice *newItem)  ;

    virtual QGraphicsItem *graphicItem() {
        return &_graphicsItem ;
    }
    virtual XSchemaObject *item() {
        return _item ;
    }

};

class SequenceItem : public XSDItem
{
    Q_OBJECT

    QRectF _contour;
    XSchemaSequence *_item;
    GraphicsRectItem _graphicsItem;
    QGraphicsTextItem *_labelItem;
    QGraphicsPixmapItem *_icon;
    RChildren _children ;

    void init();
    void reset();

private slots:
    void itemChanged(QGraphicsItem::GraphicsItemChange change, const QVariant &value);
    void childAdded(XSchemaObject *newChild);


public:

    SequenceItem(XsdGraphicContext *newContext, XSchemaSequence *newItem, QGraphicsItem * parent = 0);
    ~SequenceItem();

    XSchemaSequence *sequence() const ;
    void setItem(XSchemaSequence *newItem)  ;

    virtual QGraphicsItem *graphicItem() {
        return &_graphicsItem ;
    }
    virtual XSchemaObject *item() {
        return _item ;
    }

};


class RestrictionItem : public XSDItem
{
    Q_OBJECT

    QPolygonF _contour ;
    //TODO: a generic restriction?
    XSchemaObject *_item;
    PolygonItem _graphicsItem;
    QGraphicsTextItem *_facets;
    QGraphicsTextItem *_name;
    RChildren _children ;

    void init();
    void reset();

private slots:
    void itemChanged(QGraphicsItem::GraphicsItemChange change, const QVariant &value);
    void childAdded(XSchemaObject *newChild);

public:

    RestrictionItem(XsdGraphicContext *newContext, XSchemaObject *newItem, QGraphicsItem * parent = 0);
    ~RestrictionItem();

    XSchemaObject *restriction() const ;
    void setItem(XSchemaObject *newItem) ;

    virtual QGraphicsItem *graphicItem() {
        return &_graphicsItem ;
    }
    virtual XSchemaObject *item() {
        return _item ;
    }

};

class UnionItem : public XSDItem
{
    Q_OBJECT

    QPolygonF _contour ;
    XSchemaSimpleTypeUnion *_item;
    PolygonItem _graphicsItem;
    RChildren _children ;

    void init();
    void reset();

private slots:
    void itemChanged(QGraphicsItem::GraphicsItemChange change, const QVariant &value);
    void childAdded(XSchemaObject *newChild);

public:

    UnionItem(XsdGraphicContext *newContext, XSchemaSimpleTypeUnion *newItem, QGraphicsItem * parent = 0);
    ~UnionItem();

    XSchemaSimpleTypeUnion *xunion() const ;
    void setItem(XSchemaObject *newItem) ;

    virtual QGraphicsItem *graphicItem() {
        return &_graphicsItem ;
    }
    virtual XSchemaObject *item() {
        return _item ;
    }

};

class ListItem : public XSDItem
{
    Q_OBJECT

    QPolygonF _contour ;
    XSchemaSimpleTypeList *_item;
    PolygonItem _graphicsItem;
    RChildren _children ;
    QGraphicsSimpleTextItem *_nameWidget ;

    void init();
    void reset();

private slots:
    void itemChanged(QGraphicsItem::GraphicsItemChange change, const QVariant &value);
    void childAdded(XSchemaObject *newChild);

public:

    ListItem(XsdGraphicContext *newContext, XSchemaSimpleTypeList *newItem, QGraphicsItem * parent = 0);
    ~ListItem();

    XSchemaSimpleTypeList *list() const ;
    void setItem(XSchemaObject *newItem) ;

    virtual QGraphicsItem *graphicItem() {
        return &_graphicsItem ;
    }
    virtual XSchemaObject *item() {
        return _item ;
    }
};

class GenericItem : public XSDItem
{
    Q_OBJECT

    QPolygonF _contour ;
    XSchemaObject *_item;
    PolygonItem _graphicsItem;
    QGraphicsPixmapItem *_icon;
    RChildren _children ;
    QGraphicsTextItem *_textItem ;
    QGraphicsPixmapItem* _iconInfo ;

    void init();
    void reset();

private slots:
    void itemChanged(QGraphicsItem::GraphicsItemChange change, const QVariant &value);
    void childAdded(XSchemaObject *newChild);

protected:
    void setGraphics(/*const QPixmap & pixmap,*/ QColor bkColor);

public:

    GenericItem(XsdGraphicContext *newContext, XSchemaObject *newItem, QGraphicsItem * parent = 0);
    ~GenericItem();

    //XSchemaObject *all() const ;
    void setItem(XSchemaObject *newItem) ;

    virtual QGraphicsItem *graphicItem() {
        return &_graphicsItem ;
    }
    virtual XSchemaObject *item() {
        return _item ;
    }

};

/*
class IncludeItem : public GenericItem
{
    Q_OBJECT

public:

    IncludeItem( XSchemaObject *newItem, QGraphicsItem * parent = 0 );
    ~IncludeItem();

};
*/

class XSDWindow;


class MainItemMenuBuilder : public XMainMenuBuilder
{
    QMap<ESchemaType, QAction*> _actions;
    QList<ESchemaType> _actionsOrdered;
    XSDWindow *_parent;
public:
    virtual QMenu *buildMenu(XSchemaObject *target);
    explicit MainItemMenuBuilder(XSDWindow *newParent) ;
    ~MainItemMenuBuilder();

    void addAction(const ESchemaType type, QAction* action);
};

#include "xsdeditor/xsdcontroller.h"

class XSDWindow : public QMainWindow
{
    Q_OBJECT

    enum EEditor {
        EDITOR_NONE = 0,
        EDITOR_SEQUENCE = 1,
        EDITOR_ELEMENT = 2,
        EDITOR_SCHEMA = 3,
        EDITOR_CHOICE = 4,
        EDITOR_ATTRIBUTE = 5,
        EDITOR_INCLUDE = 6,
        EDITOR_GENERIC = 7
    };

    static const int InitialWidth = 100;
    static const int InitialHeight = 100;

    QAction *addAttributeAction;
    QAction *addSequenceAction;
    QAction *addChoiceAction;
    QAction *addRestrictionAction;
    QAction *addExtensionAction;
    QAction *addUnionAction;
    QAction *addListAction;
    QAction *deleteAction;
    QAction *_gotoAction;

    QMenu *itemContextMenu;
    MainItemMenuBuilder _menuBuilder;
    int     oldSizeFirstWidget ;
    QString _title;

public:
    explicit XSDWindow(QWidget *parent = 0);
    ~XSDWindow();

    QMenu *buildMenu(XSchemaObject *target);
    QAction *getDeleteAction();
    QAction *getGotoAction();
    void loadString(const QString &inputData);
    void setTitle(const QString &newTitle);
    void setFileName(const QString &newFileName);

protected:
    void changeEvent(QEvent *e);
    void addEditors();
    void setElementsPanel();
    QAction *createMenuAction(const QString &label, const ESchemaType type);
    XSchemaObject *fromItemData(QTreeWidgetItem *item);
    void setupNavigationBaseItems();
    void setNavigationTargetSelection(XSchemaObject *newSelection);
    void setNavSplitterWidgetSizes(const int width0 , const int width1);
    void paintScene(QPainter *painter, const QRectF &sourceArea, const QRectF &destArea, const int pageNumber, const int totalPages);
    void calculatePageRect(QPainter *painter, QRectF &destArea);
    void restoreSelection(QList<QGraphicsItem*> &itemsToSelect);

private:
    Ui::XSDWindow *ui;
    QGraphicsView *_view;
    XSDScene *_scene;
    QString _stringToLoad;
    XsdGraphicContext _context;
    XsdController _controller;
    QString fileName;

    bool completeUi();
    bool newRoot();
    void clear();
    bool newSchema();
    bool showRoot();
    QStack<XSchemaObject*> history;
    int currentHistoryPosition;

    XSDItem *itemData(QGraphicsItem *item);
    XSDItem *getSelectedItem();
    XSchemaObject *getSelectedSchemaObject();
    void setPropertyTarget(XSchemaObject *target);

    void emptyNavigationBox();
    void loadNavigationBox(XSDSchema *schema);
    void enableHistory();
    void truncateHistory();
    void historyNewTarget(XSchemaObject *target);
    void jumpToObject(XSchemaObject *target);

private slots:
#ifdef  XSD_EVENTS_HANDLED
    void on_cmdA_clicked();
    void on_cmdE_clicked();
    void on_newCmd_clicked();
    void on_cmdC_clicked();
    void on_cmdS_clicked();
    void on_newR_clicked();
    void on_saveToClipbopard_clicked();
    void on_load_clicked();
    void on_fromClipb_clicked();

    void on_addElementAction_triggered();
    void on_addAttributeAction_triggered();
    void on_addSequenceAction_triggered();
    void on_addChoiceAction_triggered();
    void on_addRestrictionAction_triggered();
    void on_addExtensionAction_triggered();
    void on_addUnionAction_triggered();
    void on_addListAction_triggered();
    void on_deleteAction_triggered();

    void onAddChildAction();
#endif
    void on_gotoAction_triggered();

    void selectionChanged();
    void on_loadFromString_triggered();

    void on_cmdZoomIn_clicked();
    void on_cmdZoomOut_clicked();
    void on_cmdZoom1_clicked();
    void on_closeButton_clicked();
    void on_clearSearch_clicked();
    void on_searchBox_textChanged(const QString &newText);
    void on_forwardButton_clicked();
    void on_backButton_clicked();

    void on_navigation_itemDoubleClicked(QTreeWidgetItem *item, int column);
    void on_navigationCmd_clicked();
    void on_printCmd_clicked();
    void on_svgCmd_clicked();

public:
    QEventLoop *EVENTLOOP;
    void closeEvent(QCloseEvent *event);

    XsdGraphicContext * context() {
        return &_context;
    }

};

void updateScenePosition(QGraphicsItem *item);

#endif // XSDWINDOW_H
