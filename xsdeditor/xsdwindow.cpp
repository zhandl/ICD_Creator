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
#include "xsdwindow.h"
#include "utils.h"
#include "ui_xsdwindow.h"
#include "config.h"
#include "xsdeditor/widgets/xsdgenericeditor.h"
#include <QSvgGenerator>

#ifdef  QML
#include <QDeclarativeView>
#include <QDeclarativeContext>
#endif


#define RES_IMAGE_LINK ":/xsdimages/link2"

//#define SCHEMA_FILE_READ    ":/data/test.xsd"
//TODO: test
#define SCHEMA_FILE_READ    Config::getString(Config::KEY_TEST_SAMPLE_FILE_XSD, "" )

void xsdTest()
{
#ifdef  QML
    QDeclarativeView view;
    QDeclarativeContext *context = view.rootContext();
    context->setContextProperty("backgroundColor", QColor(Qt::yellow));
    view.setSource(QUrl::fromLocalFile(QDir::homePath() + QString("/devel/qxmledit/xsd/src/resources/test.qml"));
                   //view.setSource(QUrl("qrc:/data/test.qml"));
                   view.show();
#endif

                   XSDWindow xsdEditor ;
                   //xsdEditor.setWindowModality(Qt::ApplicationModal);

                   QEventLoop eventLoop;
                   xsdEditor.EVENTLOOP = &eventLoop ;
                   //xsdEditor.setEventLoop(&eventLoop);
                   xsdEditor.show();
                   // occorre gestire event loop inside the window.
    if(eventLoop.exec() > 0) {
    return ;
}
return ;
}


//----------------------------------------------------------------------------------------------

MainItemMenuBuilder::MainItemMenuBuilder(XSDWindow *newParent)
{
    _parent = newParent;
}

MainItemMenuBuilder::~MainItemMenuBuilder()
{
}

QMenu *MainItemMenuBuilder::buildMenu(XSchemaObject *target)
{
    if(NULL == target) {
        return NULL ;
    }
    QMenu *contextMenu = new QMenu(NULL);
    if(NULL == contextMenu) {
        return false;
    }
    foreach(ESchemaType type, _actionsOrdered) {
        if(target->canAddChild(type)) {
            QAction *action  = _actions.value(type);
            if(NULL != action) {
                contextMenu->addAction(action);
            }
        }
    }
    if(target->hasAReference()) {
        contextMenu ->addAction(_parent->getGotoAction());
    }
    contextMenu ->addSeparator();
    //contextMenu ->addAction(_parent->getDeleteAction()); IN THE EDITOR ONLY
    return contextMenu;
}

void MainItemMenuBuilder::addAction(const ESchemaType type, QAction* action)
{
    _actions.insert(type, action);
    _actionsOrdered.append(type);
}

//----------------------------------------------------------------------------------------------

XSDWindow::XSDWindow(QWidget *parent) :
    QMainWindow(parent),
    _menuBuilder(this),
    ui(new Ui::XSDWindow),
    _scene(NULL),
    currentHistoryPosition(-1)
{
    oldSizeFirstWidget = -1 ;
    _context.setMenuBuilder(&_menuBuilder);
    ui->setupUi(this);
    if(!completeUi()) {
        Utils::error(tr("Error opening XSD viewer."));
        this->close();
        return ;
    }
    enableHistory();
    this->showMaximized();
}

XSDWindow::~XSDWindow()
{
    _context.clear();
    delete ui;
}

void XSDWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch(e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

QAction *XSDWindow::getDeleteAction()
{
    return deleteAction ;
}

QAction *XSDWindow::getGotoAction()
{
    return _gotoAction ;
}

void XSDWindow::loadString(const QString &inputData)
{
    _stringToLoad = inputData ;
    QTimer::singleShot(1, this, SLOT(on_loadFromString_triggered()));
}

void XSDWindow::setTitle(const QString &newTitle)
{
    _title = newTitle;
    setWindowTitle(_title);
}

void XSDWindow::setFileName(const QString &newFileName)
{
    fileName = newFileName;
}

void XSDWindow::addEditors()
{
    QStackedWidget *parentWidget = ui->properties;

    QWidget *genericEditor = new XSDGenericEditor(parentWidget);
    parentWidget->addWidget(genericEditor);
    /* TODO: test for declarative view
    QDeclarativeView *xxx=NULL;
    QDeclarativeView *qmlEditorInclude = new QDeclarativeView();
    //TODO
    xxx=qmlEditorInclude;
    qmlEditorInclude->setSource(QUrl(PATH_EDITOR_INCLUDE) );
    QStackedWidget *parentWidget = ui->properties;
    parentWidget->addWidget(qmlEditorInclude);
    */
}


void XSDWindow::setElementsPanel()
{
    ui->splitter->setStretchFactor(0, 1);
    ui->splitter->setStretchFactor(1, 4);
    int width = ui->splitter->width();
    int width0 = width / 4 ;
    if(width0 < 50) {
        width0 = 50 ;
    }
    int width1 = width - width0 ;
    setNavSplitterWidgetSizes(width0 , width1);
}

bool XSDWindow::completeUi()
{
    ui->properties->setCurrentIndex(EDITOR_NONE);
    _view = ui->view ;
    ui->view->setDragMode(QGraphicsView::RubberBandDrag) ;
    _scene = new XSDScene();

    setElementsPanel();

#ifdef  XSD_READONLY
    ui->properties->setEnabled(false);
    ui->newCmd->setVisible(false);
    ui->cmdC->setVisible(false);
    ui->cmdE->setVisible(false);
    ui->cmdA->setVisible(false);
    ui->cmdS->setVisible(false);
    ui->newR->setVisible(false);
    ui->newExt->setVisible(false);
    ui->load->setVisible(false);
    ui->fromClipb->setVisible(false);
    ui->saveToClipbopard->setVisible(false);
#endif

    ui->properties->setVisible(false);

    if(NULL == _scene) {
        return false ;
    }
    connect(_scene, SIGNAL(selectionChanged()), this, SLOT(selectionChanged()));

    ui->view->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->view->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    //TODO _scene->setSceneRect(QRectF(0, 0, InitialWidth, InitialHeight));
    ui->view->setScene(_scene);
    ui->view->centerOn(0, 0);

    _gotoAction = new QAction(QIcon(RES_IMAGE_LINK), tr("Go To Reference"), this);
    addSequenceAction = createMenuAction(tr("Add Sequence"), SchemaTypeSequence);
    addChoiceAction = createMenuAction(tr("Add Choice"), SchemaTypeChoice);
    addRestrictionAction = new QAction(tr("Add Restriction"), this);//TODO
    addExtensionAction = new QAction(tr("Add Extension"), this);//TODO
    addUnionAction = new QAction(tr("Add Union"), this);//TODO
    addListAction = new QAction(tr("Add List"), this);//TODO
    deleteAction = new QAction(QIcon(":/images/edit-delete"), tr("Delete"), this);

    if(
        /*||  ( NULL == addAttributeAction )
        ||  ( NULL == addSequenceAction ) TODO
        ||  ( NULL == addChoiceAction )
        ||  ( NULL == addUnionAction )
        ||  ( NULL == addExtensionAction )
        ||  ( NULL == addListAction )
        ||  ( NULL == addRestrictionAction )
        ||  ( NULL == deleteAction )
        ||*/ (NULL == _gotoAction)
        /*|| (NULL == createMenuAction(tr("Add Include"), SchemaTypeInclude))
        || (NULL == createMenuAction(tr("Add Import"), SchemaTypeImport))
        || (NULL == createMenuAction(tr("Add Redefine"), SchemaTypeRedefine))
        || (NULL == createMenuAction(tr("Add Annotation"), SchemaTypeAnnotation))
        || (NULL == createMenuAction(tr("Add Element"), SchemaTypeElement))*/
    ) {
        return false ;
    }

    itemContextMenu = new QMenu(this);
    if(NULL == itemContextMenu) {
        return false;
    }

    itemContextMenu->addAction(_gotoAction);
    itemContextMenu->addSeparator();
#ifndef  XSD_READONLY
    //itemContextMenu->addAction(addAttributeAction );
    //itemContextMenu->addAction(addSequenceAction);
    //itemContextMenu->addAction(addChoiceAction);
    itemContextMenu->addSeparator();
    //itemContextMenu->addAction(addRestrictionAction);
    //itemContextMenu->addAction(addExtensionAction);
    //itemContextMenu->addAction(addUnionAction);
    itemContextMenu->addAction(addListAction);
    itemContextMenu->addSeparator();
    itemContextMenu->addAction(deleteAction);


    /*connect(addAttributeAction, SIGNAL(triggered()), this, SLOT(on_addAttributeAction_triggered()));
    connect(addSequenceAction, SIGNAL(triggered()), this, SLOT(on_addSequenceAction_triggered()));
    connect(addChoiceAction, SIGNAL(triggered()), this, SLOT(on_addChoiceAction_triggered()));
    connect(addRestrictionAction, SIGNAL(triggered()), this, SLOT(on_addRestrictionAction_triggered()));
    connect(addExtensionAction, SIGNAL(triggered()), this, SLOT(on_addExtensionAction_triggered()));
    connect(addUnionAction, SIGNAL(triggered()), this, SLOT(on_addUnionAction_triggered()));
    connect(addListAction, SIGNAL(triggered()), this, SLOT(on_addListAction_triggered())); TODO
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(on_deleteAction_triggered()));*/

#endif
    connect(_gotoAction, SIGNAL(triggered()), this, SLOT(on_gotoAction_triggered()));
    //-------- editors ----
    addEditors();

    return true ;
}

QAction *XSDWindow::createMenuAction(const QString &label, const ESchemaType type)
{
    QAction *action = new QAction(label, this);
    action->setData((int)type);
    _menuBuilder.addAction(type, action);
    //TODO connect(action, SIGNAL(triggered()), this, SLOT(onAddChildAction()));
    return action;
}

XSDItem *XSDWindow::itemData(QGraphicsItem *item)
{
    if(NULL == item) {
        return NULL ;
    }
    QVariant data = item->data(XSD_ITEM_DATA);
    XSDItem *object = (XSDItem *)data.value<void*>();
    return object ;
}


void XSDWindow::clear()
{
    if(NULL != _scene) {
        _scene->clear();
    }
    _context.clear();
}

bool XSDWindow::newSchema()
{
    _context.setSchema(new XSDSchema());
    if(NULL == _context.schema()) {
        return false;
    }
    return true ;

}

bool XSDWindow::showRoot()
{
    _context.setRootItem(new RootItem(&_context));
    _scene->addItem(_context.rootItem()->graphicItem());
    _context.rootItem()->setItem(_context.schema());
    if(NULL == _context.rootItem()) {
        return false ;
    }
    _context.rootItem()->recalcChildrenPos();
    _context.rootItem()->afterPositionChange();
    _scene->updateBounds();
    ui->navigation->emptyNavigationBox();
    ui->navigation->loadNavigationBox(_context.schema());
    //TODO connect(_rootItem, SIGNAL(deleted(XSchemaObject*)), this, SLOT(rootDeleted(XSchemaObject*)));
    // set boundaries TODO
    /*QRectF totalSizeRect(0,0,0,0);
    _rootItem->totalSize( totalSizeRect );
    _scene->setSceneRect(QRectF(0, 0, totalSizeRect.width(), totalSizeRect.height() ) );*/

    return true ;
}


void XSDWindow::on_navigationCmd_clicked()
{
    bool isShow = ui->navigationCmd->isChecked();
    ui->navigation->setShown(isShow);
    ui->searchBox->setShown(isShow);
    ui->clearSearch->setShown(isShow);
    if(!isShow) {
        oldSizeFirstWidget = ui->navigation->width();
        int width = ui->splitter->width();
        int width0 = 0 ;
        int width1 = width ;
        setNavSplitterWidgetSizes(width0 , width1);
    } else {
        if(oldSizeFirstWidget != -1) {
            int width = ui->splitter->width();
            int width0 = oldSizeFirstWidget ;
            if(width0 < 50) {
                width0 = 50 ;
            }
            int width1 = width - width0 ;
            if(width1 < 0) {
                width1 = 0 ;
            }
            setNavSplitterWidgetSizes(width0 , width1);
        }
    }
}

void XSDWindow::setNavSplitterWidgetSizes(const int width0 , const int width1)
{
    QList<int> sizes;
    sizes.append(width0);
    sizes.append(width1);
    ui->splitter->setSizes(sizes);
    ui->splitter->update();
}

void XSDWindow::setNavigationTargetSelection(XSchemaObject *newSelection)
{
    ui->navigation->setNavigationTargetSelection(newSelection);
}

XSchemaObject *XSDWindow::fromItemData(QTreeWidgetItem *item)
{
    if(NULL == item) {
        return NULL ;
    }
    QVariant data = item->data(0, Qt::UserRole);
    XSchemaObject *object = (XSchemaObject *)data.value<void*>();
    return object ;
}

bool XSDWindow::newRoot()
{
    clear();
    if(newSchema()) {
        return showRoot();
    }
    return false ;
}

XSDItem *XSDWindow::getSelectedItem()
{
    if(NULL == _scene) {
        Utils::error(this, tr("Selection is not valid"));
        return NULL;
    }
    QList<QGraphicsItem*> selection = _scene->selectedItems();
    if(selection.count() != 1) {
        Utils::error(this, tr("Selected item not valid"));
        return NULL;
    }
    QGraphicsItem *item = selection.first();
    XSDItem *xitem = itemData(item);
    return xitem;
}

XSchemaObject *XSDWindow::getSelectedSchemaObject()
{
    XSDItem *xitem = getSelectedItem();
    if(NULL == xitem) {
        Utils::error(this, tr("The selected item is not valid"));
        return NULL ;
    }
    XSchemaObject *object = xitem->item();
    return object ;
}

#ifdef  XSD_EVENTS_HANDLED
void XSDWindow::on_newCmd_clicked()
{
    if(!newRoot()) {
        Utils::error(tr("Error"));
    }
}


void XSDWindow::on_cmdA_clicked()
{
    XSchemaObject *object = getSelectedSchemaObject();
    if(NULL == object) {
        Utils::error(this, tr("Unkown object type."));
        return ;
    }
    if(!object->canAddAttribute()) {
        Utils::error(this, tr("Cannot add an element here."));
        return ;
    }
    XSchemaAttribute *attribute = object->addAttribute() ;
    if(NULL == attribute) {
        Utils::error(this, tr("Error creating item."));
        return ;
    }
    attribute->setName("newAttribute1");
}

void XSDWindow::on_cmdE_clicked()
{
    XSchemaObject *object = getSelectedSchemaObject();
    if(NULL == object) {
        Utils::error(this, tr("Unkown object type."));
        return ;
    }
    if(!object->canAddElement()) {
        Utils::error(this, tr("Cannot add an element here."));
        return ;
    }
    XSchemaElement *element = object->addElement() ;
    if(NULL == element) {
        Utils::error(this, tr("Error creating item."));
        return ;
    }
    element->setName("newElement");
}

void XSDWindow::on_cmdC_clicked()
{
    XSchemaObject *object = getSelectedSchemaObject();
    if(NULL == object) {
        Utils::error(this, tr("Unkown object type."));
        return ;
    }
    if(!object->canAddChoice()) {
        Utils::error(this, tr("Cannot add a choice here."));
        return ;
    }
    XSchemaChoice *choice = object->addChoice() ;
    if(NULL == choice) {
        Utils::error(this, tr("Error creating item."));
        return ;
    }
}

void XSDWindow::on_cmdS_clicked()
{
    XSchemaObject *object = getSelectedSchemaObject();
    if(NULL == object) {
        Utils::error(this, tr("Unkown object type."));
        return ;
    }
    if(!object->canAddSequence()) {
        Utils::error(this, tr("Cannot add a sequence here."));
        return ;
    }
    XSchemaSequence *sequence = object->addSequence() ;
    if(NULL == sequence) {
        Utils::error(this, tr("Error creating item."));
        return ;
    }
}

void XSDWindow::on_newR_clicked()
{
    XSchemaObject *object = getSelectedSchemaObject();
    if(NULL == object) {
        Utils::error(this, tr("Unkown object type."));
        return ;
    }
    if(!object->canAddRestriction()) {
        Utils::error(this, tr("Cannot add a restriction here."));
        return ;
    }
    XSchemaObject *restriction = object->addRestriction() ;
    if(NULL == restriction) {
        Utils::error(this, tr("Error creating item."));
        return ;
    }
}

void XSDWindow::on_addExtensionAction_triggered()
{
    XSchemaObject *object = getSelectedSchemaObject();
    if(NULL == object) {
        Utils::error(this, tr("Unkown object type."));
        return ;
    }
    if(!object->canAddExtension()) {
        Utils::error(this, tr("Cannot add an extension here."));
        return ;
    }
    XSchemaObject *extension = object->addExtension() ;
    if(NULL == extension) {
        Utils::error(this, tr("Error creating item."));
        return ;
    }
}

void XSDWindow::on_addUnionAction_triggered()
{
    XSchemaObject *object = getSelectedSchemaObject();
    if(NULL == object) {
        Utils::error(this, tr("Unkown object type."));
        return ;
    }
    if(!object->canAddUnion()) {
        Utils::error(this, tr("Cannot add an union here."));
        return ;
    }
    XSchemaSimpleTypeUnion *xunion = object->addUnion() ;
    if(NULL == xunion) {
        Utils::error(this, tr("Error creating item."));
        return ;
    }
}

void XSDWindow::on_addListAction_triggered()
{
    XSchemaObject *object = getSelectedSchemaObject();
    if(NULL == object) {
        Utils::error(this, tr("Unkown object type."));
        return ;
    }
    if(!object->canAddList()) {
        Utils::error(this, tr("Cannot add a list here."));
        return ;
    }
    XSchemaSimpleTypeList *list = object->addList() ;
    if(NULL == list) {
        Utils::error(this, tr("Error creating item."));
        return ;
    }
}

void XSDWindow::on_addRestrictionAction_triggered()
{
    on_newR_clicked();
}

void XSDWindow::on_addElementAction_triggered()
{
    on_cmdE_clicked();
}

void XSDWindow::on_addAttributeAction_triggered()
{
    on_cmdA_clicked();
}

void XSDWindow::on_addSequenceAction_triggered()
{
    on_cmdS_clicked();
}

void XSDWindow::on_addChoiceAction_triggered()
{
    on_cmdC_clicked();
}

void XSDWindow::on_saveToClipbopard_clicked()
{
    if(NULL != _schema) {
        _schema->saveToClipboard();
    } else {
        Utils::error(tr("No root item"));
    }
}

//TODO: use try catch for IO
void XSDWindow::on_load_clicked()
{
    if(newSchema()) {
        try {
            _schema->read(SCHEMA_FILE_READ);
            showRoot();
        } catch(XsdException *ex) {
            Utils::error(tr("Error loading schema.\n%1").arg(ex->cause()));
        } catch(...) {
            Utils::error(tr("Unknown exception."));
        }
    } else {
        Utils::error(tr("No root item"));
    }
}

void XSDWindow::on_fromClipb_clicked()
{
    if(newSchema()) {
        _schema->readFromClipboard();
        showRoot();
    } else {
        Utils::error(tr("No root item"));
    }
}

void XSDWindow::on_deleteAction_triggered()
{
    XSchemaObject *object = getSelectedSchemaObject();
    if(NULL == object) {
        Utils::error(this, tr("Unkown object type."));
        return ;
    }
    if(Utils::askYN(tr("Do you really want to delete this item?"))) {
        object->deleteObject();
        if(object == _schema) {
            _rootItem = NULL ;
            _schema = NULL ;
        }
    }
}

void XSDWindow::onAddChildAction()
{
    //get the type
    QAction *action = qobject_cast<QAction*>(sender());
    if(NULL == action) {
        return ;
    }
    ESchemaType type = (ESchemaType)(action->data().toInt());
    XSchemaObject *object = getSelectedSchemaObject();
    if(NULL == object) {
        Utils::error(this, tr("Unkown object type."));
        return ;
    }
    if(!object->canAddChild(type)) {
        Utils::error(this, tr("Cannot add a child here."));
        return ;
    }
    XSchemaObject *newChild = object->addNewChild(type) ;
    if(NULL == newChild) {
        Utils::error(this, tr("Error creating item."));
        return ;
    }
}
#endif

void XSDWindow::on_gotoAction_triggered()
{
    XSchemaObject *object = getSelectedSchemaObject();
    if(NULL == object) {
        Utils::error(this, tr("Unkown object type."));
        return ;
    }
    QString referenceName = object->referencedObjectName();
    XReferenceType referenceType = object->referencedObjectType();
    XSchemaObject *target = NULL;
    switch(referenceType) {
    default:
        // do nothing here
        break;
    case XRT_ELEMENT:
        target = _context.rootItem()->schema()->rootElement(referenceName);
        break;
    case XRT_TYPE:
        target = _context.rootItem()->schema()->rootType(referenceName);
        break;
    case XRT_ATTRIBUTE:
        target = _context.rootItem()->schema()->rootAttribute(referenceName);
        break;
    }
    if(NULL == target) {
        Utils::error(this, tr("Error finding the referenced element."));
        return ;
    }
    jumpToObject(target);
}

void XSDWindow::closeEvent(QCloseEvent *event)
{
    EVENTLOOP->quit();
    QMainWindow::closeEvent(event);
}


void XSDWindow::on_loadFromString_triggered()
{
    try {
        if(newSchema()) {
            _context.schema()->readFromString(_stringToLoad);
            showRoot();
        } else {
            Utils::error(tr("No root item"));
        }
    } catch(XsdException *ex) {
        Utils::error(tr("Error loading schema.\n%1").arg(ex->cause()));
    } catch(...) {
        Utils::error(tr("Unknown exception."));
    }
}


// activates the right editor
//TODO: investigare se l'editor non attivo viene disabilitato o meno.
// IMPORTANTE
// uso Q_INTERFACE
void XSDWindow::setPropertyTarget(XSchemaObject *target)
{
    EEditor currentIndex = EDITOR_NONE ;
    if(NULL == target) {
        currentIndex = EDITOR_NONE ;
    } else {
        ESchemaType type = target->getType()  ;
        if(SchemaTypeSchema == type) {
            currentIndex = EDITOR_SCHEMA ;
        } else if(SchemaTypeChoice  == type) {
            currentIndex = EDITOR_CHOICE ;
        } else if(SchemaTypeSequence  == type) {
            currentIndex = EDITOR_SEQUENCE ;
        } else if(SchemaTypeElement  == type) {
            currentIndex = EDITOR_ELEMENT ;
        } else if(SchemaTypeAttribute  == type) {
            currentIndex = EDITOR_ATTRIBUTE ;
        } else if(SchemaTypeInclude  == type) {
            currentIndex = EDITOR_INCLUDE ;
        } else {
            currentIndex = EDITOR_GENERIC ;
        }
        /* TODO qml experimental code
        currentIndex = EDITOR_INCLUDE ;
        if( NULL != xxx ) {
            QDeclarativeContext *context = xxx->rootContext();
            context->setContextProperty("item", target);
        }
        */
    }
    //TODO QWidget *actualWidget = ui->properties->currentWidget();
    /*TODO if( NULL != actualWidget ) {
        actualWidget->setEnabled(false);
    }*/
    ui->properties->setCurrentIndex((int)currentIndex);
    QWidget *actualWidget = ui->properties->currentWidget();
    if(NULL != actualWidget) {
        if(actualWidget->children().size() > 0) {
            QWidget *firstChild = qobject_cast<QWidget *>(actualWidget->children().at(0));
            if(NULL != firstChild) {
                XEditorInterface *iEditor  = qobject_cast<XEditorInterface *>(firstChild);
                if(NULL != iEditor) {
                    iEditor->setTarget(target);
                }
            }
        }
    }
}

void XSDWindow::selectionChanged()
{
    XSchemaObject *newSelection = NULL ;
    if(NULL != _scene) {
        QList<QGraphicsItem*> selection = _scene->selectedItems();
        if(selection.count() == 1) {
            QGraphicsItem *item = selection.first();
            XSDItem *xitem = itemData(item);
            if(NULL != xitem) {
                newSelection = xitem->item();
            }
        }
    }
    setPropertyTarget(newSelection);
    setNavigationTargetSelection(newSelection);
}


void XSDWindow::on_cmdZoomIn_clicked()
{
    if(NULL != _view) {
        _view->scale(1.1, 1.1);
    }
}

void XSDWindow::on_cmdZoomOut_clicked()
{
    if(NULL != _view) {
        _view->scale(0.9, 0.9);
    }
}

void XSDWindow::on_cmdZoom1_clicked()
{
    if(NULL != _view) {
        _view->resetTransform();
    }
}

void XSDWindow::on_closeButton_clicked()
{
    QMainWindow::close();
}

void XSDWindow::on_clearSearch_clicked()
{
    ui->searchBox->setText("");
}

void XSDWindow::on_searchBox_textChanged(const QString &newText)
{
    ui->navigation->newSearchText(newText);
}

void XSDWindow::truncateHistory()
{
    if((currentHistoryPosition >= 0)  && (currentHistoryPosition < history.count())) {
        history.resize(currentHistoryPosition + 1);
    }
}

void XSDWindow::enableHistory()
{
    ui->backButton->setEnabled(currentHistoryPosition > 0);
    ui->forwardButton->setEnabled(currentHistoryPosition <= (history.count() - 2));
}

void XSDWindow::on_backButton_clicked()
{
    if((currentHistoryPosition > 0) && (history.count() > currentHistoryPosition)) {
        XSDItem *item = _context.getItemOfObject(history.at(currentHistoryPosition - 1));
        if(NULL != item) {
            currentHistoryPosition -- ;
            enableHistory();
            _scene->gotoItem(item->graphicItem());
        }
    }
}

void XSDWindow::on_forwardButton_clicked()
{
    if((currentHistoryPosition >= 0) && ((history.count() - 2) >= currentHistoryPosition)) {
        XSDItem *item = _context.getItemOfObject(history.at(currentHistoryPosition + 1));
        if(NULL != item) {
            currentHistoryPosition ++ ;
            enableHistory();
            _scene->gotoItem(item->graphicItem());
        }
    }
}

void XSDWindow::on_navigation_itemDoubleClicked(QTreeWidgetItem *item, int /*column*/)
{
    XSchemaObject *target = fromItemData(item);
    if(NULL == target) {
        return ;
    }
    // jump to the object
    jumpToObject(target);
}

void XSDWindow::historyNewTarget(XSchemaObject *target)
{
    history.append(target);
    currentHistoryPosition = history.count() - 1;
}

void XSDWindow::jumpToObject(XSchemaObject *target)
{
    XSDItem *item = _context.getItemOfObject(target);
    if(NULL != item) {
        truncateHistory();
        historyNewTarget(target);
        enableHistory();
        _scene->gotoItem(item->graphicItem());
    }
}

//TODO: error checking
void XSDWindow::on_printCmd_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Export as PDF"),
                       Utils::changeFileType(fileName, ".pdf"),
                       tr("PDF documents (*.pdf);;All files (*);;"));
    if(filePath.isEmpty()) {
        return ;
    }
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFileName(filePath);
    printer.setOutputFormat(QPrinter::PdfFormat);

    /**
      what I impose is: 100 points on video (since 100pts is a width of a badge) are 2cm on paper
      */
    QPainter painter(&printer);
    QRectF pageNumberArea;
    calculatePageRect(&painter, pageNumberArea);
    // width of a printer page in mm
    QRectF pageRect = printer.pageRect(QPrinter::Inch);
    QRectF pageRectInDevicePoints = printer.pageRect();

    // take out page position
    pageRectInDevicePoints.setHeight(pageRectInDevicePoints.height() - pageNumberArea.height());
    double resYPrinter = printer.logicalDpiY();
    if(0 == resYPrinter) {
        Utils::error(tr("Error in calculating printer resolution."));
        return ;
    }
    double pageHeightPrinter = pageNumberArea.height() / resYPrinter ;
    pageRect.setHeight(pageRect.height() - pageHeightPrinter);

    // scene resolution
    double resXVideo = logicalDpiX();
    double resYVideo = logicalDpiY();
    // find the dimensions of a printer page on scene
    // abs width value * device resolution -> device points
    double pageWidthScene = pageRect.width() * resXVideo ;
    double pageHeightScene = pageRect.height() * resYVideo ;

    // maps
    if((0 == pageWidthScene) || (0 == pageHeightScene)) {
        Utils::error(tr("Error in calculating scene dimensions."));
        return ;
    }

    // calculate the number of pages: how many times the scene can be divided by the page dimensions
    // find the number of pages
    double dnumberOfPagesInARow = _scene->sceneRect().width() / pageWidthScene  ;
    double dnumberOfPagesInAColumn = _scene->sceneRect().height() / pageHeightScene  ;

    // round fractional values to integer
    int numberOfPagesInARow = int(dnumberOfPagesInARow);
    int numberOfPagesInAColumn = int(dnumberOfPagesInAColumn);

    // check for factional pages
    if((dnumberOfPagesInARow - numberOfPagesInARow) > 0) {
        numberOfPagesInARow++;
    }
    if(dnumberOfPagesInAColumn - dnumberOfPagesInAColumn > 0) {
        numberOfPagesInAColumn++;
    }
    // last check
    if(numberOfPagesInAColumn == 0) {
        numberOfPagesInAColumn = 1;
    }
    if(numberOfPagesInARow == 0) {
        numberOfPagesInARow = 1;
    }

    // for all the pages
    int numPages = numberOfPagesInARow * numberOfPagesInAColumn ;
    int currentPage = 0;
    QRectF sourceArea;
    for(int pageRow = 0 ; pageRow < numberOfPagesInARow ; pageRow ++) {
        for(int pageColumn = 0 ; pageColumn < numberOfPagesInAColumn ; pageColumn ++) {
            currentPage++;
            sourceArea.setRect(pageRow * pageWidthScene, pageColumn * pageHeightScene, pageWidthScene, pageHeightScene);
            //printf("x %g y %g w %g h %g\n", pageRow * pageWidthScene, pageColumn * pageHeightScene, pageWidthScene, pageHeightScene);
            // is next instruction useful?
            painter.fillRect(painter.window(), QColor(255, 255, 255, 0));
            paintScene(&painter, sourceArea, pageRectInDevicePoints, currentPage, numPages);

            if(currentPage < numPages) {
                printer.newPage();
            }
        }
    }
    painter.end();

    // end print
    setWindowTitle(_title);
    Utils::message(tr("Diagram exported in PDF format."));
}

//TODO: error checking
void XSDWindow::on_svgCmd_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Export as SVG"),
                       Utils::changeFileType(fileName, ".svg"),
                       tr("SVG images (*.svg);;All files (*);;"));

    if(filePath.isEmpty()) {
        return ;
    }

    QSvgGenerator svg;
    svg.setFileName(filePath);
    svg.setTitle(_title);
    svg.setDescription(tr("View"));
    //svg.setSize(_scene. printer->paperSize(QPrinter::Point).toSize());
    QRectF sceneRect = _scene->sceneRect();
    svg.setSize(QSize(sceneRect.width(), sceneRect.height()));
    {
        QPainter painter(&svg);
        paintScene(&painter, QRectF(), QRectF(), 0, 0);
    }
    setWindowTitle(_title);
    Utils::message(tr("Diagram exported in SVG format."));
}

//TODO: error checking
void XSDWindow::paintScene(QPainter *painter, const QRectF &sourceArea, const QRectF &destArea, const int pageNumber, const int totalPages)
{
    QList<QGraphicsItem*> items = _scene->selectedItems();
    _scene->clearSelection();

    _scene->render(painter, destArea, sourceArea);
    if(totalPages != 0) {
        QFontMetrics fm = painter->fontMetrics();
        QString text = QString(tr("Page %1/%2")).arg(pageNumber).arg(totalPages);
        QRectF measRect = fm.boundingRect(text);
        float intervalx = (destArea.width() - measRect.width()) / 2;
        float x = destArea.left() + intervalx;
        float y = destArea.bottom() ;
        QRectF drawRect(x, y, measRect.width() + intervalx, measRect.height());
        painter->drawLine(QPointF(destArea.left() + 10., y), QPointF(destArea.right() - 10., y));
        painter->drawText(drawRect, text);
        //printf("page number: x %g y %g w %g h %g\n", drawRect.left(), drawRect.top(), drawRect.width(), drawRect.height());
        //printf("  dest area : x %g y %g w %g h %g\n", destArea.left(), destArea.top(), destArea.width(), destArea.height());
    }
    restoreSelection(items);
}

void XSDWindow::restoreSelection(QList<QGraphicsItem*> &itemsToSelect)
{
    foreach(QGraphicsItem * item, itemsToSelect) {
        item->setSelected(true);
    }
}

void XSDWindow::calculatePageRect(QPainter *painter, QRectF &destArea)
{
    QFontMetrics fm = painter->fontMetrics();
    QString text = QString(tr("Page %1/%1")).arg(999).arg(999);
    QRectF measRect = fm.boundingRect(text);
    int x = destArea.left() + (destArea.width() - measRect.width()) / 2;
    int y = destArea.bottom() - measRect.height();
    destArea.setRect(x, y, measRect.width() + measRect.width() / 10, measRect.height());
}


