#include "xmleditwidgetprivate.h"

#include <QXmlSchema>
#include <QXmlSchemaValidator>
#include "xmleditwidget.h"
#include "xsdeditor/xschemaloader.h"
#include "validatormessagehandler.h"
#include "validationresults.h"
#include "schemavalidator.h"
//#include "elementitemdelegate.h"
#include "alloweditemsinsert.h"
//#include "qattributedelegate.h"
#include "config.h"
#include "findtextparams.h"
#include "dommodel.h"
#include "utils.h"
#include "xsdeditor/xsdplugin.h"
//#include "extraction/extractresults.h"
#include "xmleditwidgetprivate.h"

void ShowTextInDialog(QWidget *parent, const QString &text);

#define CS_ELEMENT_TEXT "E"
#define CS_ELEMENT_TAG "T"
#define CS_ATTRIBUTE_NAME "N"
#define CS_ATTRIBUTE_VALUE "V"


XmlEditWidgetPrivate::XmlEditWidgetPrivate(XmlEditWidget *theOwner) :
    styleActionGroup(this)
{
    p = theOwner;
    _appData = &_defaultData;
    started = false;
    internalStateOk = false;

    _schemaRoot = NULL;

    _displayMode = qxmledit::NORMAL;
    paintInfo.setExploreMode(false);
    isSlave = false;

    styleMenu = NULL;
    copyMenu = NULL;

    application = NULL;
    paintInfo.loadState();
    model = newModel();
    model->assignCollectSizeDataFlag(paintInfo.showItemSize());
    clipBoardItem = NULL;
}

XmlEditWidgetPrivate::XmlEditWidgetPrivate() :
    styleActionGroup(this)
{
    p = NULL;
    _appData = &_defaultData;
    started = false;
    internalStateOk = false;

    _schemaRoot = NULL;

    _displayMode = qxmledit::NORMAL;
    paintInfo.setExploreMode(false);
    isSlave = false;

    styleMenu = NULL;
    copyMenu = NULL;

    application = NULL;
    paintInfo.loadState();
    model = newModel();
    model->assignCollectSizeDataFlag(paintInfo.showItemSize());
    clipBoardItem = NULL;
}

DomModel *XmlEditWidgetPrivate::newModel()
{
    DomModel *newRule = new DomModel();
    newRule->setPaintInfo(&paintInfo);
    connect(newRule, SIGNAL(wasModified()), this, SLOT(modelIsModified()));
    connect(newRule, SIGNAL(undoStateChanged()), this, SLOT(modelUndoChanged()));
    connect(newRule, SIGNAL(docTypeChanged(QString)), this, SLOT(docTypeChanged(QString)));
    return newRule;
}

void XmlEditWidgetPrivate::secondStepConstructor()
{
    internalStateOk = finishSetUpUi();
    if(!internalStateOk) {
        Utils::error(tr("Error preparing user interface."));
    }
    init();
    loadSearchSettings();
    p->setAcceptDrops(true);

    connect(p->treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(elementDoubleClicked(QTreeWidgetItem*,int)));

    started = true;
    internalStateOk = true;
}

XmlEditWidgetPrivate::~XmlEditWidgetPrivate()
{
    resetStyleMenu();
    deleteModel();
    cleanClipBoard();
    deleteSchema();
}

bool XmlEditWidgetPrivate::isReady()
{
    return started && internalStateOk;
}

void XmlEditWidgetPrivate::deleteSchema()
{
    if(NULL != _schemaRoot) {
        delete _schemaRoot;
        _schemaRoot = NULL;
    }
}

void XmlEditWidgetPrivate::setData(QApplication *newApplication, QXmlEditData *newData, const bool newIsSlave)
{
    application = newApplication;
    if(NULL != newData) {
        _appData = newData;
    }
    isSlave = newIsSlave;
    init();
}

bool XmlEditWidgetPrivate::init()
{
    p->ok->setEnabled(isSlave);
    p->ok->setVisible(isSlave);

    p->cdataElement->setEnabled(isSlave);
    p->cdataElement->setVisible(isSlave);

    p->cancel->setEnabled(isSlave);
    p->cancel->setVisible(isSlave);

    return internalStateOk;
}

void XmlEditWidgetPrivate::deleteModel()
{
    if(NULL != model) {
        disconnect(model, SIGNAL(wasModified()), this, SLOT(modelIsModified()));
        disconnect(model, SIGNAL(undoStateChanged()), this, SLOT(modelUndoChanged()));
        disconnect(model, SIGNAL(docTypeChanged(QString)), this, SLOT(docTypeChanged(QString)));
        delete model;
        model = NULL;
    }
}

void XmlEditWidgetPrivate::startUIState()
{
    computeSelectionState();
}

qxmledit::EDisplayMode XmlEditWidgetPrivate::displayMode()
{
    return _displayMode;
}

bool XmlEditWidgetPrivate::finishSetUpUi()
{
    connect(p->ok, SIGNAL(clicked()), this, SLOT(on_ok_clicked()));
    connect(p->cancel, SIGNAL(clicked()), this, SLOT(on_cancel_clicked()));
    connect(p->moveUpButton, SIGNAL(clicked()), this, SLOT(on_moveUp_clicked()));
    connect(p->moveDownButton, SIGNAL(clicked()), this, SLOT(on_moveDown_clicked()));
    connect(p->addChildButton, SIGNAL(clicked()), this, SLOT(on_addChild_clicked()));
    connect(p->addBrotherButton, SIGNAL(clicked()), this, SLOT(on_addBrother_clicked()));
    connect(p->editItemButton, SIGNAL(clicked()), this, SLOT(on_editItem_clicked()));
    connect(p->deleteItem, SIGNAL(clicked()), this, SLOT(on_deleteItem_clicked()));
    connect(p->closeSearchPanel, SIGNAL(clicked()), this, SLOT(on_closeSearchPanel_clicked()));
    connect(p->viewAsXsdCmd, SIGNAL(clicked()), this, SLOT(on_viewAsXsdCmd_clicked()));
    connect(p->treeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(on_treeWidget_itemSelectionChanged()));

    // connect to search widget. In the original code these actions were inseted into the UI
    connect(p->findButton, SIGNAL(clicked()), this, SLOT(findText()));
    connect(p->clearText, SIGNAL(clicked()), this, SLOT(clearSearchText()));
    connect(p->counting, SIGNAL(clicked()), this, SLOT(countTextOccurrences()));

    // turn off autoscroll
    p->treeWidget->setAutoScroll(_appData->isAutoScroll());

    p->searchEditBox->installEventFilter(p);

    mainFontSize = p->treeWidget->font().pointSize();
    p->horizontalLowLayout->setAlignment(Qt::AlignLeft);

    p->testNext->setVisible(false);
    p->testPrev->setVisible(false);

    resetTree();
    startUIState();
    p->treeWidget->setAlternatingRowColors(true);

    p->treeWidget->setUniformRowHeights(paintInfo.compactView());

    p->searchGroup->setVisible(false);
    p->searchLocation->insertItem(0, tr("All"), (int)FindTextParams::FIND_ALL);
    p->searchLocation->insertItem(1, tr("Element Tag"), (int)FindTextParams::FIND_TAG);
    p->searchLocation->insertItem(2, tr("Attribute names"), (int)FindTextParams::FIND_ATTRIBUTE_NAME);
    p->searchLocation->insertItem(3, tr("Attribute values"), (int)FindTextParams::FIND_ATTRIBUTE_VALUE);
    p->searchLocation->insertItem(4, tr("Text"), (int)FindTextParams::FIND_TEXT);
    p->searchLocation->setCurrentIndex(0);

    p->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(p->treeWidget, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(treeContextMenu(const QPoint &)));
    //TODO connect( p->searchLocation, SIGNAL(currentIndexChanged(int)), this, SLOT(searchTypeChanged(int)) );
    connect(p->searchEditBox, SIGNAL(textChanged(const QString &)), this, SLOT(searchTextChanged(const QString &)));
    p->clearText->setEnabled(false);

    /********************************************   *******************
    p->ok->setEnabled(isSlave);
    p->ok->setVisible(isSlave);
    */
    p->cdataElement->setEnabled(isSlave);
    p->cdataElement->setVisible(isSlave);
    /*
    p->cancel->setEnabled(isSlave);
    p->cancel->setVisible(isSlave);
    ***************************************************************/

    p->docTypeLabel->setVisible(false);

    VStyle *style = loadStyleMenu();
    setNewStyle(style);

    bool isOk = true;

//    if(!setUpDelegates()) {
//        isOk = false ;
//    }
    return isOk;
}

void XmlEditWidgetPrivate::onCopySpecial()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if(NULL == action) {
        return ;
    }
    DomItem *item = getSelectedItem();
    if(NULL == item) {
        return ;
    }
    QClipboard *clipboard = QApplication::clipboard();
    QString tag = action->data().toString();
    if(tag == CS_ELEMENT_TEXT) {
        clipboard->setText(item->getAsText());
    } else if(tag == CS_ELEMENT_TAG) {
        clipboard->setText(item->tag());
    } else if(tag.startsWith(CS_ATTRIBUTE_NAME)) {
        clipboard->setText(tag.right(tag.length() - 1));
    } else if(tag.startsWith(CS_ATTRIBUTE_VALUE)) {
        Attribute *attribute = item->getAttribute(tag.right(tag.length() - 1));
        if(NULL != attribute) {
            clipboard->setText(attribute->value);
        }
    }
}

void XmlEditWidgetPrivate::buildCopyMenu()
{
    DomItem *item = getSelectedItem();
    resetCopyMenu();
    if(NULL == item) {
        return ;
    }
    copyMenu = new QMenu();

    QAction *itemTextAction = createAnAction(copyMenu, QString(tr("Copy Element Text '%1'")).arg(item->tag()), CS_ELEMENT_TEXT, tr("Copy Element Text"));
    connect(itemTextAction, SIGNAL(triggered()), this, SLOT(onCopySpecial()));
    copyMenu->addAction(itemTextAction);
    QAction *itemTagAction = createAnAction(copyMenu, QString(tr("Copy Element Tag <%1>")).arg(item->tag()), CS_ELEMENT_TAG, tr("Copy Element Tag"));
    connect(itemTagAction, SIGNAL(triggered()), this, SLOT(onCopySpecial()));
    copyMenu->addAction(itemTagAction);

    QList<Attribute*>attributes = item->getAttributesList();
    foreach (Attribute* attribute, attributes) {
        QAction *attributeNameAction = createAnAction(copyMenu, QString(tr("copy Attribute Name '%1'")).arg(attribute->name), CS_ATTRIBUTE_NAME + attribute->name, tr("Copy Attribute Name"));
        connect(attributeNameAction, SIGNAL(triggered()), this, SLOT(onCopySpecial()));
        copyMenu->addAction(attributeNameAction);
        QAction *attributeValueAction = createAnAction(copyMenu, QString(tr("copy Attribute Value ='%1'")).arg(attribute->name), CS_ATTRIBUTE_VALUE + attribute->value, tr("Copy Attribute Value"));
        connect(attributeValueAction, SIGNAL(triggered()), this, SLOT(onCopySpecial()));
        copyMenu->addAction(attributeValueAction);
    }
    p->copySpecial->setMenu(copyMenu);
    p->copySpecial->setPopupMode(QToolButton::InstantPopup);
}

VStyle* XmlEditWidgetPrivate::loadStyleMenu()
{
    VStyle* selectedStyle = NULL;
    QString selected = Config::getString(Config::KEY_VIEW_STYLE, "");
    resetStyleMenu();
    styleMenu = new QMenu();
    QAction *defaultAction = createStyleAction(styleMenu, tr("== No style =="), "", tr("don't use a style"));
    connect(defaultAction, SIGNAL(triggered()), this, SLOT(onStyleChanged()));
    if(selected == "") {
        defaultAction->setChecked(true);
        selectedStyle = NULL;
    }
    styleMenu->addAction(defaultAction);
    styleActionGroup.addAction(defaultAction);
    foreach (VStyle *style, _appData->getStyles()) {
        QString name = style->name();
        QAction *action = createStyleAction(styleMenu, name, name, "");
        connect(action, SIGNAL(triggered()), this, SLOT(onStyleChanged()));
        styleMenu->addAction(action);
        styleActionGroup.addAction(action);
        if(selected == name) {
            action->setChecked(true);
            selectedStyle = style;
        }
    }
    p->styleButton->setMenu(styleMenu);
    p->styleButton->setPopupMode(QToolButton::InstantPopup);

    return selectedStyle;
}

void XmlEditWidgetPrivate::resetStyleMenu()
{
    p->styleButton->setMenu(NULL);
    if(styleMenu != NULL) {
        foreach (QAction *action, styleMenu->actions()) {
            styleActionGroup.removeAction(action);
        }
        styleMenu->deleteLater();
    }
    styleMenu = NULL;
}

void XmlEditWidgetPrivate::resetCopyMenu()
{
    p->copySpecial->setMenu(NULL);
    if(copyMenu != NULL) {
        copyMenu->deleteLater();
    }
    copyMenu = NULL;
}

QAction *XmlEditWidgetPrivate::createStyleAction(QMenu *menu, const QString &label, const QString &tag, const QString &tooltip)
{
    QAction *action = new QAction(menu);
    action->setText(label);
    action->setData(tag);
    action->setToolTip(tooltip);
    action->setCheckable(true);
    return action;
}

QAction *XmlEditWidgetPrivate::createAnAction(QMenu *menu, const QString &label, const QString &tag, const QString &tooltip)
{
    QAction *action = new QAction(menu);
    action->setText(label);
    action->setData(tag);
    action->setToolTip(tooltip);
    return action;
}

void XmlEditWidgetPrivate::onStyleChanged()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if(NULL == action) {
        return ;
    }
    QString tag = action->data().toString();
    VStyle *newStyle = _appData->getStyle(tag);
    setNewStyle(newStyle);
}

void XmlEditWidgetPrivate::setNewStyle(VStyle *newStyle)
{
    if(NULL == newStyle) {
        Config::saveString(Config::KEY_VIEW_STYLE, "");
        VStyle *style = paintInfo.currentStyle();
        if(NULL != style) {
            style->deactivate();
        }
        paintInfo.setCurrentStyle(NULL);
        repaint();
        return ;
    }
    if(newStyle != paintInfo.currentStyle()) {
        Config::saveString(Config::KEY_VIEW_STYLE, newStyle->name());
        if(!newStyle->activate(p->treeWidget->font(), paintInfo.zoom())) {
            Utils::error(tr("Error activating style"));
        }
        paintInfo.setCurrentStyle(newStyle);
        repaint();
    }
}

void XmlEditWidgetPrivate::repaint()
{
    if(NULL != model) {
        p->treeWidget->setUpdatesEnabled(false);
        model->redisplay();
        p->treeWidget->setUpdatesEnabled(true);
    }
}

PaintInfo* XmlEditWidgetPrivate::getPaintInfo()
{
    return &paintInfo;
}

void XmlEditWidgetPrivate::display()
{
    if(NULL != model) {
        p->treeWidget->setUpdatesEnabled(false);
        model->setTreeValue(p->treeWidget);
        p->treeWidget->setUpdatesEnabled(true);
    }
}

void XmlEditWidgetPrivate::treeContextMenu(const QPoint &position)
{
    p->emitTreeContextMenuRequested(position);
}

void XmlEditWidgetPrivate::modelIsModified()
{
    p->emitDocumentIsModified(model->isModified());
}

void XmlEditWidgetPrivate::setClipBoardActoinsState()
{
    bool isAction = false;
    if(NULL != clipBoardItem) {
        isAction = true;
    }
    p->emitSignalSetClipBoardActionsState(isAction && isActionMode());
}

void XmlEditWidgetPrivate::on_treeWidget_itemSelectionChanged()
{
    computeSelectionState();
//    getModel()->unseletedAll();
//    DomItem *item = DomItem::fromItemData(p->treeWidget->currentItem());
//    item->selected();
//    p->treeWidget->currentItem()->setBackground(0, QBrush(QColor(0xFF, 0xC0, 0xFF)));
}

void XmlEditWidgetPrivate::computeSelectionState()
{
    bool isSomItemSeletced = false;
    bool selectSpecials = false;
    bool selectSpecialsUp = false;
    bool selectSpecialsDown = false;
    bool canAddChild = false;
    bool isExplore = (_displayMode != qxmledit::NORMAL) && (_displayMode != qxmledit::SCAN);
    int numberSelected = p->treeWidget->selectedItems().size();
    if(numberSelected > 0) {
        selectSpecials = true;
        selectSpecialsUp = true;
        DomItem *item = DomItem::fromItemData(p->treeWidget->selectedItems().at(0));
        selectSpecialsUp = !item->isFirstChild();
        selectSpecialsDown = !item->isLastChild();
        if(item->getType() == DomItem::ET_ELEMENT)
            canAddChild = true;
        isSomItemSeletced = true;
    } else {
        if(model->isEmpty(true))
            canAddChild = true;
    }
    p->addChildButton->setEnabled(canAddChild && !isExplore);
    p->addBrotherButton->setEnabled(selectSpecials && !isExplore);
    p->deleteItem->setEnabled(isSomItemSeletced && !isExplore);
    p->editItemButton->setEnabled(isSomItemSeletced && !isExplore);
    p->moveUpButton->setEnabled(selectSpecialsUp && !isExplore);
    p->moveDownButton->setEnabled(selectSpecialsDown && !isExplore);
    p->copySpecial->setEnabled(isSomItemSeletced);
    if(isSomItemSeletced) {
        buildCopyMenu();
    }

    p->viewAsXsdCmd->setEnabled(isValidXsd() && !isExplore);
    p->emitReevalueSelectionState();
}

DomItem *XmlEditWidgetPrivate::getSelectedItem()
{
    if((NULL != p->treeWidget) && (p->treeWidget->selectedItems().size() > 0)) {
        DomItem *item = DomItem::fromItemData(p->treeWidget->selectedItems().at(0));
        return item;
    }
    return NULL;
}

void XmlEditWidgetPrivate::resetTree()
{
    p->treeWidget->setColumnCount(6);
    p->treeWidget->clear();
    QStringList headers;
    headers << tr("Elements");
    headers << tr("#Ch.");
    headers << tr("Size");
    headers << tr("Attributes");
    headers << tr("Text");
    headers << tr("Decoded text");
    p->treeWidget->setHeaderLabels(headers);
    setDataColumnTitle(paintInfo.compactView());
    calcColumnState();
}

void XmlEditWidgetPrivate::calcColumnState()
{
    bool isShowSize = paintInfo.showItemSize();
    if(isShowSize) {
        p->treeWidget->showColumn(paintInfo.columnForChildren);
        p->treeWidget->showColumn(paintInfo.columnForSize);
    } else {
        p->treeWidget->hideColumn(paintInfo.columnForChildren);
        p->treeWidget->hideColumn(paintInfo.columnForSize);
    }
}

void XmlEditWidgetPrivate::onActionNewFromClipboard()
{
    const QClipboard *clipBoard = QApplication::clipboard();
    const QMimeData *mimeData = clipBoard->mimeData();
    if(mimeData->hasText()) {
        loadText(mimeData->text());
    }
}

void XmlEditWidgetPrivate::onActionResizeToContents()
{
    resizeTreeColumns();
}

void XmlEditWidgetPrivate::setEncodingLabelVisible(bool isShow)
{
    p->encoding->setVisible(isShow);
}

bool XmlEditWidgetPrivate::isEncodingLabelVisible()
{
    return p->encoding->isVisible();
}

void XmlEditWidgetPrivate::setDocTypeVisible(bool isShow)
{
    p->docTypeLabel->setVisible(isShow);
}

bool XmlEditWidgetPrivate::isDocTypeVisible()
{
    return p->docTypeLabel->isVisible();
}

void XmlEditWidgetPrivate::setViewAsXSDButtonVisible(bool isShow)
{
    if(p->viewAsXsdCmd) {
        p->viewAsXsdCmd->setVisible(isShow);
    }
}

bool XmlEditWidgetPrivate::isViewAsXSDButtonVisible()
{
    return p->viewAsXsdCmd->isVisible();
}

void XmlEditWidgetPrivate::setMoveButtonsVisible(bool isShow)
{
    p->moveDownButton->setVisible(isShow);
    p->moveUpButton->setVisible(isShow);
}

bool XmlEditWidgetPrivate::areMoveButtonsVisible()
{
    return p->moveDownButton->isVisible();
}

ulong XmlEditWidgetPrivate::versionNumber()
{
    return VERSION_NUMBER;
}

void XmlEditWidgetPrivate::resizeTreeColumns()
{
    p->treeWidget->setUpdatesEnabled(false);
    int columns = p->treeWidget->columnCount();
    for(int i = 0; i < columns; i++) {
        p->treeWidget->resizeColumnToContents(i);
    }
    p->treeWidget->setUpdatesEnabled(true);
}

void XmlEditWidgetPrivate::editAttribute()
{
    if(!isActionMode()) {
        return ;
    }
    QTreeWidgetItem *itemSel = getSelItem();
    if(NULL == itemSel) {
        Utils::errorNoSel(p);
        return;
    }
    if(itemSel->text(0) == tr("Services"))
        model->editServices(p, itemSel);
    else
        model->editAttribute(p, itemSel);
    computeSelectionState();

}

bool XmlEditWidgetPrivate::editItem(QTreeWidgetItem *item)
{
    if(NULL == model) {
        errorNoRule();
        return false;
    }
    model->editItem(p, item);
    bool result = false;
    computeSelectionState();
    return result;
}

void XmlEditWidgetPrivate::elementDoubleClicked(QTreeWidgetItem *item, int /*column*/)
{
    if(isActionMode()) {
        editItem(item);
    }
}

QTreeWidgetItem *XmlEditWidgetPrivate::getSelItem()
{
    QList<QTreeWidgetItem *>selItems = p->treeWidget->selectedItems();
    if(selItems.count() < 1)
        return NULL;
    return selItems.at(0);
}

void XmlEditWidgetPrivate::on_editItem_clicked()
{
    editItem();
}

void XmlEditWidgetPrivate::editItem()
{
    if(!isActionMode()) {
        return ;
    }
    QTreeWidgetItem *itemSel = getSelItem();
    if(NULL == itemSel) {
        Utils::errorNoSel(p);
        return;
    }
    editItem(itemSel);
}

void XmlEditWidgetPrivate::on_addChild_clicked()
{
    addChild();
}

void XmlEditWidgetPrivate::addChild()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addChild(p, p->treeWidget);
}

void XmlEditWidgetPrivate::addChild(QString newTag)
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }

    DomItem *parentItem = DomItem::fromItemData(p->treeWidget->currentItem());
    DomItem *newItem = new DomItem(newTag, "", model, parentItem);

    model->addChild(p, p->treeWidget, newItem);
}

void XmlEditWidgetPrivate::addBrother()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addBrother(p, p->treeWidget);
}

void XmlEditWidgetPrivate::addVal()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addVal(p, p->treeWidget);
}

void XmlEditWidgetPrivate::addText()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addText(p, p->treeWidget);
}

void XmlEditWidgetPrivate::addPrivate()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addPrivate(p, p->treeWidget);
}

void XmlEditWidgetPrivate::addSubstation()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addSubstation(p, p->treeWidget);
}

void XmlEditWidgetPrivate::addCommunication()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addCommunication(p, p->treeWidget);
}

void XmlEditWidgetPrivate::addIED()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addIED(p, p->treeWidget);
}

void XmlEditWidgetPrivate::addDataTypeTemplates()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addDataTypeTemplates(p, p->treeWidget);
}

void XmlEditWidgetPrivate::addHistory()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addHistory(p, p->treeWidget);
}

void XmlEditWidgetPrivate::addHitem()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addHitem(p, p->treeWidget);
}

void XmlEditWidgetPrivate::addSubNetwork()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addSubNetwork(p, p->treeWidget);
}

void XmlEditWidgetPrivate::addBitRate()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addBitRate(p, p->treeWidget);
}

void XmlEditWidgetPrivate::addConnectedAP()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addConnectedAP(p, p->treeWidget);
}

void XmlEditWidgetPrivate::addAddress()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addAddress(p, p->treeWidget);
}

void XmlEditWidgetPrivate::addGSE()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addGSE(p, p->treeWidget);
}

void XmlEditWidgetPrivate::addSMV()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addSMV(p, p->treeWidget);
}

void XmlEditWidgetPrivate::addPhysconn()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addPhysconn(p, p->treeWidget);
}

void XmlEditWidgetPrivate::addP()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addP(p, p->treeWidget);
}

void XmlEditWidgetPrivate::addMinTime()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addMinTime(p, p->treeWidget);
}

void XmlEditWidgetPrivate::addMaxTime()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addMaxTime(p, p->treeWidget);
}

void XmlEditWidgetPrivate::addServices()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addServices(p, p->treeWidget);
}

void XmlEditWidgetPrivate::addAccessPoint()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addAccessPoint(p, p->treeWidget);
}

void XmlEditWidgetPrivate::addServer()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addServer(p, p->treeWidget);
}

void XmlEditWidgetPrivate::addServerAt()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addServerAt(p, p->treeWidget);
}

void XmlEditWidgetPrivate::addGOOSESecurity()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addGOOSESecurity(p, p->treeWidget);
}

void XmlEditWidgetPrivate::addSMVSecurity()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addSMVSecurity(p, p->treeWidget);
}

void XmlEditWidgetPrivate::addSubject()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addSubject(p, p->treeWidget);
}

void XmlEditWidgetPrivate::addIssuerName()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addIssuerName(p, p->treeWidget);
}

void XmlEditWidgetPrivate::addAuthentication()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addAuthentication(p, p->treeWidget);
}

void XmlEditWidgetPrivate::addLDevice()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addLDevice(p, p->treeWidget);
}

void XmlEditWidgetPrivate::addAssociation()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addAssociation(p, p->treeWidget);
}

void XmlEditWidgetPrivate::addLN0()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addLN0(p, p->treeWidget);
}

void XmlEditWidgetPrivate::addLN()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addLN(p, p->treeWidget);
}

void XmlEditWidgetPrivate::addAccessControl()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addAccessControl(p, p->treeWidget);
}

void XmlEditWidgetPrivate::addDataSet()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addDataSet(p, p->treeWidget);
}

void XmlEditWidgetPrivate::addReportControl()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addReportControl(p, p->treeWidget);
}

void XmlEditWidgetPrivate::addLogControl()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addLogControl(p, p->treeWidget);
}

void XmlEditWidgetPrivate::addInputs()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addInputs(p, p->treeWidget);
}

void XmlEditWidgetPrivate::addLog()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addLog(p, p->treeWidget);
}

void XmlEditWidgetPrivate::addGSEControl()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addGSEControl(p, p->treeWidget);
}

void XmlEditWidgetPrivate::addSMVControl()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addSMVControl(p, p->treeWidget);
}

void XmlEditWidgetPrivate::addSettingControl()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addSettingControl(p, p->treeWidget);
}



void XmlEditWidgetPrivate::on_addBrother_clicked()
{
    addBrother();
}

void XmlEditWidgetPrivate::errorNoRule()
{
    error(tr("No main structrue"));
}

void XmlEditWidgetPrivate::onActionAddChildElement()
{
    addChild();
}

void XmlEditWidgetPrivate::onActionAppendChildElement()
{
    addBrother();
}

void XmlEditWidgetPrivate::onActionEdit()
{
    editItem();
}

void XmlEditWidgetPrivate::onActionDelete()
{
    deleteItem();
}

void XmlEditWidgetPrivate::onActionMoveUp()
{
    moveUp();
}

void XmlEditWidgetPrivate::onActionMoveDown()
{
    moveDown();
}

void XmlEditWidgetPrivate::deleteItem()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }

    QTreeWidgetItem *currItem = getSelItem();
    if(NULL == currItem) {
        Utils::errorNoSel(p);
        return ;
    }
    if(!Utils::askYN(p,
                     tr("This operation will destroy the element and all his chidren. Do you really want to continue?"))) {
        return ;
    }
    model->deleteItem(DomItem::fromItemData(currItem));
}

void XmlEditWidgetPrivate::on_deleteItem_clicked()
{
    deleteItem();
}

void XmlEditWidgetPrivate::on_moveUp_clicked()
{
    moveUp();
}

void XmlEditWidgetPrivate::moveUp()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }

    QTreeWidgetItem *currItem = getSelItem();
    if(NULL == currItem) {
        Utils::errorNoSel(p);
        return ;
    }
    DomItem *item = DomItem::fromItemData(currItem);
    if(NULL == item) {
        return ;
    }
    model->moveUp(item);
}

void XmlEditWidgetPrivate::moveDown()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }

    QTreeWidgetItem *currItem = getSelItem();
    if(NULL == currItem) {
        Utils::errorNoSel(p);
        return ;
    }
    DomItem *item = DomItem::fromItemData(currItem);
    if(NULL == item) {
        return ;
    }
    model->moveDown(item);
}

void XmlEditWidgetPrivate::on_moveDown_clicked()
{
    moveDown();
}

void XmlEditWidgetPrivate::cleanClipBoard()
{
    if(clipBoardItem != NULL) {
        delete clipBoardItem;
    }
    clipBoardItem = NULL;
}

void XmlEditWidgetPrivate::setClipBoardItem(DomItem *pItem)
{
    clipBoardItem = pItem;
}

void XmlEditWidgetPrivate::onActionCut()
{
    if(!isActionMode()) {
        return ;
    }

    if(NULL == model) {
        errorNoRule();
        return ;
    }

    QTreeWidgetItem *currItem = getSelItem();
    if(NULL == currItem) {
        Utils::errorNoSel(p);
        return ;
    }
    setClipBoardItem(DomItem::fromItemData(currItem)->cutTOClipboard());
    model->setModified(true);
    setClipBoardActoinsState();
}

void XmlEditWidgetPrivate::onActionCopy()
{
    if(NULL == model) {
        errorNoRule();
        return ;
    }

    QTreeWidgetItem *currItem = getSelItem();
    if(NULL == currItem) {
        Utils::errorNoSel(p);
        return ;
    }
    DomItem *item = DomItem::fromItemData(currItem);
    setClipBoardItem(item->copyToClipboard());

    QDomDocument document;
    if(item->generateDom(document, document)) {
        QString clipBoardText = document.toString(4);
        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setText(clipBoardText);
    }
    setClipBoardActoinsState();
}

void XmlEditWidgetPrivate::onActionPaste()
{
    if(isActionMode()) {
        model->paste(p, p->treeWidget, getClipBoardItem());
    }
}

DomItem *XmlEditWidgetPrivate::getClipBoardItem() const
{
    return clipBoardItem;
}

void XmlEditWidgetPrivate::onActionExpandAll()
{
    if(NULL != model)
        model->expand(p->treeWidget);
}

void XmlEditWidgetPrivate::onActionShowAttrLine(const bool state)
{
    paintInfo.setOneAttrPerLine(state);
    repaint();
}

void XmlEditWidgetPrivate::onActionAddComment()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addComment(p, p->treeWidget);
}

void XmlEditWidgetPrivate::onActionAppendComment()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->appendComment(p, p->treeWidget);
}


void XmlEditWidgetPrivate::onActionAppendProcessingInstruction()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->appendProcessingInstruction(p, p->treeWidget);
}

void XmlEditWidgetPrivate::onActionAddProcessingInstruction()
{
    if(!isActionMode()) {
        return ;
    }

    if(NULL == model) {
        errorNoRule();
        return ;
    }
    model->addProcessingInstruction(p, p->treeWidget);
}


void XmlEditWidgetPrivate::onActionFind()
{
    p->searchGroup->setVisible(true);
    p->searchEditBox->setFocus(Qt::OtherFocusReason);
}

void XmlEditWidgetPrivate::on_closeSearchPanel_clicked()
{
    if(NULL != model) {
        model->unseletedAll();
    }

    p->searchGroup->setVisible(false);
    p->setFocus(Qt::OtherFocusReason);
}

void XmlEditWidgetPrivate::findText()
{
    findTextOperation(true);
}

void XmlEditWidgetPrivate::countTextOccurrences()
{
    findTextOperation(false);
}

void XmlEditWidgetPrivate::findTextOperation(const bool isFindOrCount)
{
    if(NULL != model) {
        p->setEnabled(false);
        p->treeWidget->setUpdatesEnabled(false);
        Utils::showWaitCursor();
        FindTextParams::EFindTarget target = FindTextParams::FIND_ALL;
        int itemIndex = p->searchLocation->currentIndex();
        if(itemIndex >= 0) {
            int trg = p->searchLocation->itemData(itemIndex).toInt();
            target = (FindTextParams::EFindTarget) trg;
        }
        FindTextParams findArgs(p->searchEditBox->text(), !isFindOrCount, p->isHiglightAll->isChecked(), p->isMatchExactValue->isChecked(),
                                p->isCaseSensitive->isChecked(), p->isOnlyChildren->isChecked(), target,
                                (isFindOrCount ? p->closeUnrelated->isChecked() : false),
                                p->showSize->isChecked(), p->searchScope->text());
        bool isErrorShown = false;
        bool isError = false;
        if(!findArgs.checkParams(isErrorShown)) {
            isError = true;
            if(!isErrorShown) {
                Utils::error(tr("Impossible start a search; please check parameters."));
            }
        }
        if(!isError) {
            saveSearchSettings(findArgs);
            model->unseletedAll();
            findArgs.start();
            model->findText(findArgs, getSelectedItem());
            int occurrences = findArgs.getOccurrences();
            QString message;
            if(occurrences > 0) {
                if(occurrences > 1) {
                    message = QString(tr("Found %1 occurrences.")).arg(occurrences);
                } else {
                    message = tr("Found 1 occurrence.");
                }
            } else {
                message = tr("No occurrences found.");
            }
            p->emitShowStatusMessage(message, true);
            p->occNumber->setText(message);
            if(findArgs.isShowSize()) {
                p->sizeOfSearch->setText(QString(tr("%1")).arg(findArgs.size()));
            }
            p->lblSize->setVisible(findArgs.isShowSize());
            p->sizeOfSearch->setVisible(findArgs.isShowSize());
        }
    }
    p->treeWidget->setUpdatesEnabled(true);
    p->setEnabled(true);
    Utils::restoreCursor();
}

void XmlEditWidgetPrivate::clearSearchText()
{
    p->searchEditBox->setText("");
    model->unseletedAll();
}

void XmlEditWidgetPrivate::onActionGoToParent()
{
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    QTreeWidgetItem *currItem = getSelItem();
    QTreeWidgetItem *parentItem = NULL;
    if(NULL == currItem) {
        Utils::errorNoSel(p);
        return ;
    }
    if((parentItem = currItem->parent()) != NULL) {
        p->treeWidget->setCurrentItem(parentItem);
    }
}

void XmlEditWidgetPrivate::onActionGoToPreviousBrother()
{
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    QTreeWidgetItem *currItem = getSelItem();
    if(NULL != currItem) {
        DomItem *item = DomItem::fromItemData(currItem);
        if(NULL != item) {
            QTreeWidgetItem *itemToSelect = item->goToPreviousBrother();
            if(NULL != itemToSelect) {
                p->treeWidget->setCurrentItem(itemToSelect);
            }
        }
    }
}

void XmlEditWidgetPrivate::onActionGoToNextBrother()
{
    if(NULL == model) {
        errorNoRule();
        return ;
    }

    QTreeWidgetItem *currItem = getSelItem();
    if(NULL != currItem) {
        DomItem *item = DomItem::fromItemData(currItem);
        if(NULL != item) {
            QTreeWidgetItem *itemToSelect = item->goToNextBrother();
            if(NULL != itemToSelect) {
                p->treeWidget->setCurrentItem(itemToSelect);
            }
        }
    }
}

void XmlEditWidgetPrivate::onActionClearBookmarks()
{
    if(NULL == model) {
        errorNoRule();
        return ;
    }
}

void XmlEditWidgetPrivate::onActionToggleBookmark()
{
    if(NULL == model) {
        errorNoRule();
        return ;
    }
}

void XmlEditWidgetPrivate::onActionGotoNextBookmark()
{
    if(NULL == model) {
        errorNoRule();
        return ;
    }
}

void XmlEditWidgetPrivate::onActionGotoPreviousBookmark()
{
    if(NULL == model) {
        errorNoRule();
        return ;
    }
}

void XmlEditWidgetPrivate::onActionShowChildIndex(const bool isChecked)
{
    paintInfo.setIndexPerChild(isChecked);
    repaint();
}

void XmlEditWidgetPrivate::onActionCompactView(const bool isChecked)
{
    paintInfo.setCompactView(isChecked);
    setDataColumnTitle(paintInfo.compactView());
    p->treeWidget->setUniformRowHeights(paintInfo.compactView());
    repaint();
}

void XmlEditWidgetPrivate::onActionFixedSizeAttributes(const bool isChecked)
{
    paintInfo.setUserFixedLengthFont(isChecked);
    repaint();
}

void XmlEditWidgetPrivate::onActionShowAttributesLength(const bool isChecked)
{
    paintInfo.setShowAttributesLength(isChecked);
    repaint();
}

void XmlEditWidgetPrivate::onActionShowElementTextLength(const bool isChecked)
{
    paintInfo.setShowItemTextLength(isChecked);
    repaint();
}

void XmlEditWidgetPrivate::onActionCloseThisAllBrothers()
{
    QTreeWidgetItem *current = getSelItem();
    if(NULL != current) {
        QTreeWidgetItem *parent = current->parent();
        if(NULL != parent) {
            int numChildren = parent->childCount();
            for(int i = 0; i < numChildren; i++) {
                QTreeWidgetItem *child = parent->child(i);
                child->setExpanded(false);
            }
        }
    }
}

void XmlEditWidgetPrivate::searchTextChanged(const QString &text)
{
    p->clearText->setEnabled(text.length() > 0);
    p->occNumber->setText("");
}

void XmlEditWidgetPrivate::onActionHideBrothers()
{
    QTreeWidgetItem *current = getSelItem();
    if(NULL != current) {
        DomItem *item = DomItem::fromItemData(current);
        if(NULL != item) {
            if(item->isNormalViewState()) {
                item->hideBrothers();
            } else {
                item->showBrothers();
            }
        }
    }
}

void XmlEditWidgetPrivate::loadSearchSettings()
{
    FindTextParams lastSearch;
    lastSearch.loadState();
    updateSearchUI(lastSearch);
    setDataColumnTitle(paintInfo.compactView());
}

void XmlEditWidgetPrivate::setDataColumnTitle(const bool isCompactView)
{
    QHeaderView *header = p->treeWidget->header();
    QString text;
    if(isCompactView) {
        text = tr("Attributes/Text");
    } else {
        text = tr("Attributes");
    }
    QAbstractItemModel *itemModel = header->model();
    itemModel->setHeaderData(paintInfo.columnForAttributes, header->orientation(), text);
}

void XmlEditWidgetPrivate::updateSearchUI(const FindTextParams &lastSearch)
{
    p->isHiglightAll->setChecked(lastSearch.isHiliteAll());
    p->isMatchExactValue->setChecked(lastSearch.isIsMatchExact());
    p->isCaseSensitive->setChecked(lastSearch.isCaseSensitive());
    p->isOnlyChildren->setChecked(lastSearch.isLookOnlyChildren());
    p->closeUnrelated->setChecked(lastSearch.isCloseUnrelated());
    p->showSize->setChecked(lastSearch.isShowSize());
    Utils::selectComboValue(p->searchLocation, lastSearch.getFindTarget());
    p->lblSize->setVisible(lastSearch.isShowSize());
    p->sizeOfSearch->setVisible(lastSearch.isShowSize());
}

void XmlEditWidgetPrivate::saveSearchSettings(const FindTextParams &search)
{
    search.saveState();
}

void XmlEditWidgetPrivate::onActionShowElementSize(const bool isChecked)
{
    paintInfo.setShowItemSize(isChecked);
    calcColumnState();
    if(NULL != model) {
        model->assignCollectSizeDataFlag(isChecked);
    }
    repaint();
}

void XmlEditWidgetPrivate::on_ok_clicked()
{
    p->emitOkClicked();
}

void XmlEditWidgetPrivate::on_cancel_clicked()
{
    p->emitCancelClicked();
}

QString XmlEditWidgetPrivate::getContentAsText()
{
    if(NULL != model) {
        return model->getAsText();
    }
    return "";
}

bool XmlEditWidgetPrivate::isCDATA()
{
    return p->cdataElement->isChecked();
}

void XmlEditWidgetPrivate::setCDATA(const bool isCData)
{
    return p->cdataElement->setChecked(isCData);
}

void XmlEditWidgetPrivate::onActionZoomIn()
{
    if(paintInfo.zoomIn()) {
        DomItem::setZoomFactor(paintInfo.zoom());
        QFont font = p->treeWidget->font();
        int newSize = VStyle::getZoomFontSize(mainFontSize, paintInfo.zoom());
        if(newSize > 0) {
            font.setPointSize(newSize);
            p->treeWidget->setFont(font);
        }
        p->emitEnableZoom();
        repaint();
    }
}

void XmlEditWidgetPrivate::onActionZoomOut()
{
    if(paintInfo.zoomOut()) {
        DomItem::setZoomFactor(paintInfo.zoom());
        QFont font = p->treeWidget->font();
        int newSize = VStyle::getZoomFontSize(mainFontSize, paintInfo.zoom());
        if(newSize > 0) {
            font.setPointSize(VStyle::getZoomFontSize(mainFontSize, paintInfo.zoom()));
            p->treeWidget->setFont(font);
        }
        p->emitEnableZoom();
        repaint();
    }
}

void XmlEditWidgetPrivate::onActionCopyPathToClipboard()
{
    if((NULL != model) && !model->fileName().isEmpty()) {
        QClipboard *clipboard = QApplication::clipboard();
        if(NULL != clipboard) {
            clipboard->setText(model->fileName());
        }
    }
}

void XmlEditWidgetPrivate::onActionValidate()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        return ;
    }
    QByteArray dataXml = model->getAsText().toUtf8();
    QXmlSchema schemaHandler;
    ValidatorMessageHandler messageHandler;
    schemaHandler.setMessageHandler(&messageHandler);
    QXmlSchemaValidator SchemaValidator(schemaHandler);
    if(SchemaValidator.validate(dataXml)) {
        Utils::message(p, tr("XML is valid."));
    } else {
        Utils::error(p, tr("XML does not conform to schema. Validation failed"));
        showValidationResults(model->getAsText(), messageHandler, p);
    }
}

void XmlEditWidgetPrivate::onActionValidateFile()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        return ;
    }
    if(!model->userDefinedXsd().isEmpty()) {
        validateWithFile(model->userDefinedXsd());
    }
}

void XmlEditWidgetPrivate::validateWithFile(const QString &filePath)
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        return ;
    }
    if(!filePath.isEmpty()) {
        QFile schemaFile(filePath);
        schemaFile.unsetError();
        schemaFile.open(QIODevice::ReadOnly);
        QByteArray schema = schemaFile.readAll();
        if(schemaFile.error()) {
            Utils::error(tr("Error opening schema file"));
            return ;
        }
        QByteArray dataXml = model->getAsText().toUtf8();
        QXmlSchema schemaHandler;
        ValidatorMessageHandler messageHandler;
        schemaHandler.load(schema);
        schemaHandler.setMessageHandler(&messageHandler);
        if(!schemaHandler.isValid()) {
            Utils::error(p, tr("Schema is invalid"));
        } else {
            QXmlSchemaValidator schemaValidator(schemaHandler);
            if(schemaValidator.validate(dataXml)) {
                Utils::message(p, tr("XML is valid."));
            } else {
                Utils::error(p, tr("XML does not conform to schema. Validation failed."));
                showValidationResults(QString::fromUtf8(dataXml), messageHandler, getMainTreeWidget());
            }
        }
    }
}

void XmlEditWidgetPrivate::onActionValidateNewFile()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        return ;
    }
    QString filePath = QFileDialog::getOpenFileName(p, tr("Open Schema File"),
                                                    model->fileName(), tr("XML Schema files (*.xsd);; All files(*);;"));
    if(!filePath.isEmpty()) {
        model->setUserDefinedXsd(filePath);
        validateWithFile(filePath);
        computeSelectionState();
    }
}

void XmlEditWidgetPrivate::insertSnippet(DomModel *newModel)
{
    if(NULL != newModel) {
        model->pasteXML(p, p->treeWidget, newModel);
        computeSelectionState();
    }
}

void XmlEditWidgetPrivate::onActionDeleteBookmarked()
{

}

void XmlEditWidgetPrivate::onActionCleanBookmarkedContent()
{

}

bool XmlEditWidgetPrivate::isActionMode()
{
    return (_displayMode == qxmledit::NORMAL) || (_displayMode == qxmledit::SCAN);
}

bool XmlEditWidgetPrivate::isActionNoScanMode()
{
    return _displayMode == qxmledit::NORMAL;
}

void XmlEditWidgetPrivate::setDisplayMode(const qxmledit::EDisplayMode value)
{
    _displayMode = value;
    p->treeWidget->setUniformRowHeights(value == qxmledit::EXPLORE);
    p->treeWidget->setVisible(value != qxmledit::BLIND);
}

void XmlEditWidgetPrivate::loadText(const QString &text, const bool isChangeState, const bool isAskForReview)
{
    if(!text.isEmpty()) {
        QDomDocument document;
        if(document.setContent(text)) {
          //  setDocumentPara(document, "", isChangeState);
            setDocument(document, QString(""), isChangeState);
            autoLoadValidation();
        } else {
            if(isAskForReview) {
                if(Utils::askYN(tr("Unable to parse XML. Sometimes this is caused by parser informations.\n Do you want to examine data as text?"))) {
                   // ShowTextInDialog(p, text);
                    Utils::message(p, text);
                }
            } else {
                Utils::error(tr("Unable to parse XML"));
            }
        }
    } else {
        Utils::error(tr("Data empty. Unable to load"));
    }
}

void XmlEditWidgetPrivate::doLoadFileXplore(const QString &filePath)
{
    DomModel *newModel = new DomModel();
    if(!newModel->loadXplore(filePath)) {
        Utils::error(tr("Unable to load XML"));
    }
    setDisplayMode(qxmledit::EXPLORE);
    p->emitDataReadyMessage(tr("Data loaded"));
    deleteModel();
    model = newModel;
    model->setModified(false);
    resetTree();
    p->treeWidget->setUniformRowHeights(true);
    display();
    startUIState();
    modelIsModified();
    if(isExpandTreeOnLoad()) {
        onActionExpandAll();
    }
    resizeTreeColumns();
    showControls(true);
}

void XmlEditWidgetPrivate::setDocument(QDomDocument &document, const QString &filePath, const bool isSetState)
{
//    DomModel *newModel = new DomModel(document, filePath);

//    newModel->setPaintInfo(&paintInfo);

    setModel_thread = new SetModelThread();
    setModel_thread->setTarget(document, filePath);

    connect(setModel_thread, SIGNAL(setModelOvered()), this, SLOT(setModelCompleted()));

    p->setModelLoadingLabel();
    setModel_thread->start();

//    p->emitDataReadyMessage(tr("Data loaded"));
////    deleteModel();
////    model = newModel;
//    model->assignCollectSizeDataFlag(paintInfo.showItemSize());
//    docTypeChanged(model->docType());
//    if(isSetState) {
//        setDisplayMode(qxmledit::NORMAL);
//    }
//    connect(model, SIGNAL(wasModified()), this, SLOT(modelIsModified()));
//    connect(model, SIGNAL(undoStateChanged()), this, SLOT(modelUndoChanged()));
//    connect(model, SIGNAL(docTypeChanged(QString)), this, SLOT(docTypeChanged(QString)));
//    resetTree();
//    display();
//    startUIState();
//    modelIsModified();
//    if(isExpandTreeOnLoad()) {
//        onActionExpandAll();
//    }
//    resizeTreeColumns();
//    showControls(true);
}

void XmlEditWidgetPrivate::setModelCompleted()
{
    setModel_thread->quit();
    model = setModel_thread->getModel();
    setModel_thread->deleteLater();

    p->setModelCompleted();

    p->emitDataReadyMessage(tr("Data loaded"));
//    deleteModel();
//    model = newModel;
    model->assignCollectSizeDataFlag(paintInfo.showItemSize());
    docTypeChanged(model->docType());
//    if(isSetState) {
        setDisplayMode(qxmledit::NORMAL);
//    }
    connect(model, SIGNAL(wasModified()), this, SLOT(modelIsModified()));
    connect(model, SIGNAL(undoStateChanged()), this, SLOT(modelUndoChanged()));
    connect(model, SIGNAL(docTypeChanged(QString)), this, SLOT(docTypeChanged(QString)));
    resetTree();
    display();
    startUIState();
    modelIsModified();
    if(isExpandTreeOnLoad()) {
        onActionExpandAll();
    }
    resizeTreeColumns();
    showControls(true);
}

void XmlEditWidgetPrivate::docTypeChanged(const QString &docType)
{
    if(docType.isEmpty()) {
        p->docTypeLabel->setVisible(false);
        p->docTypeLabel->setText("");
    } else {
        p->docTypeLabel->setText(tr("doc type: %1").arg(docType));
        p->docTypeLabel->setVisible(true);
    }
}

void XmlEditWidgetPrivate::showControls(const bool how)
{
    p->treeWidget->setVisible(how);
    p->addBrotherButton->setVisible(how);
    p->addChildButton->setVisible(how);
    p->deleteItem->setVisible(how);
    p->editItemButton->setVisible(how);
    p->moveUpButton->setVisible(how);
    p->moveDownButton->setVisible(how);
}

void XmlEditWidgetPrivate::onActionHideView(const bool isChecked)
{
    paintInfo.setHideView(isChecked);
    showControls(!paintInfo.hideView());
    if(!paintInfo.hideView()) {
        display();
    }
}

bool XmlEditWidgetPrivate::isValidXsd()
{
    if(NULL != model) {
        return model->isValidXsd();
    }
    return false;
}

void XmlEditWidgetPrivate::on_viewAsXsdCmd_clicked()
{
    p->emitViewAsXsdRequested();
}

DomModel *XmlEditWidgetPrivate::getModel()
{
    return model;
}

void XmlEditWidgetPrivate::onActionViewAsXsd()
{
    XsdPlugin plugin;
    plugin.go(p->parentWidget(), model);
}

void XmlEditWidgetPrivate::loadSchema(const QString &schemaURL)
{
    if(NULL == _appData) {
        return ;
    }
    deleteSchema();
    XSchemaLoader *loader = NULL;
    if((loader = new XSchemaLoader(NULL, NULL)) != NULL) {
        try {
            connect(loader, SIGNAL(loadComplete(XSchemaLoader*,XSDSchema*,bool)), this, SLOT(schemaLoadComplete(XSchemaLoader*,XSDSchema*,bool)));

            QString fileName;
            if(NULL != model) {
                fileName = model->fileName();
            }
            QFile file(fileName);
            QString dirPath = QFileInfo(file).absolutePath();

            loader->readFromURL(NULL, schemaURL, _appData->xsdNetworkAccessManager(), dirPath);
        } catch(XsdException *ex) {
            Utils::error(tr("Error loading schema.\n%1").arg(ex->cause()));
        } catch(...) {
            Utils::error(tr("Unknown exception."));
        }
    } else {
        Utils::error(tr("No root item"));
    }
}

void XmlEditWidgetPrivate::schemaLoadComplete(XSchemaLoader *loader, XSDSchema *schema, const bool isError)
{
    if(NULL != loader) {
        loader->deleteLater();
    }
    if(isError) {
        p->emitSchemaLabelChanged(tr("error loading schema"));
        if(NULL != schema) {
            delete schema;
        }
    } else {
        _schemaRoot = schema;
        if(NULL == model) {
            p->emitSchemaLabelChanged(tr("schema: ?"));
        } else {
            p->emitSchemaLabelChanged(tr("schema: %1").arg(model->documentXsd()));
        }
    }
}

void XmlEditWidgetPrivate::onActionAllowedSchemaElements()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    insertAllowedItems(getSelectedItem());
}

bool XmlEditWidgetPrivate::findAllowedItemsElement(XElementContent *content, DomItem *element, bool &startAsRoot)
{
    SchemaValidator validator;
    bool go = false;
    startAsRoot = false;

    if(NULL == model->root()) {
        go = true;
        startAsRoot = true;
    } else if((NULL != element) && (DomItem::ET_ELEMENT == element->getType())) {
        go = true;
    }

    if(go) {
        if(validator.getInsertionPointAllowedItems(content, _schemaRoot, element, startAsRoot)) {
            return true;
        }
    }
    return false;
}

void XmlEditWidgetPrivate::insertAllowedItems(DomItem *item)
{
    XElementContent content;
    bool startAsRoot = false;
    if(findAllowedItemsElement(&content, item, startAsRoot)) {
        bool isModified = false;
        model->emptyUndoStack();
        QList<XSchemaObject*> result;
        if(ChooseItemsBySchema(p, &content, &result)) {
            foreach (XSchemaObject *object, result) {
                if(startAsRoot) {
                    model->addChildToItem(p, p->getMainTreeWidget(), NULL, object->name(), false);
                    isModified = true;
                    break;
                }
                model->addChildToItem(p, p->treeWidget, item, object->name(), false);
                isModified = true;
            }
            if(isModified) {
                p->emitDocumentIsModified(model->isModified());
            }
        }
    }
}

void XmlEditWidgetPrivate::onActionNewUsingXMLSchema(const QString &schemaURL)
{
    doNew();
    model->setUserAndDocumentXsd(schemaURL);
    loadSchema(schemaURL);
}

void XmlEditWidgetPrivate::doNew()
{
    deleteModel();;
    model = newModel();
    setDisplayMode(qxmledit::NORMAL);
    model->assignCollectSizeDataFlag(paintInfo.showItemSize());
    p->treeWidget->clear();
    startUIState();
    setClipBoardActoinsState();
    p->emitDocumentIsModified(model->isModified());
    p->emitSchemaLabelChanged(tr(""));
}

void XmlEditWidgetPrivate::onActionTransformInComment()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    QTreeWidgetItem *currItem = getSelItem();
    if(NULL == currItem) {
        Utils::errorNoSel(p);
        return;
    }
    DomItem *itemToTransform = DomItem::fromItemData(currItem);
    model->transformInComment(p, p->treeWidget, itemToTransform);
}

void XmlEditWidgetPrivate::onActionExtractElementsFromComment()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    QTreeWidgetItem *currItem = getSelItem();
    if(NULL == currItem) {
        Utils::errorNoSel(p);
        return;
    }
    DomItem *itemToRetransform = DomItem::fromItemData(currItem);
    model->generateFromComment(p->treeWidget, itemToRetransform);
}

void XmlEditWidgetPrivate::autoLoadValidation()
{
    if(_appData->isAutovalidationOn()) {
        if(!model->documentXsd().isEmpty()) {
            if(model->hasMoreThanOneXsdFile()) {
                Utils::message(tr("Currently QXmlEdit handles only one XML Schema file, even if data file has reference to more schemas."));
            }
            p->emitSchemaLabelChanged(tr("schema: loading %1").arg(model->documentXsd()));
            loadSchema(model->documentXsd());
        } else {
            p->emitSchemaLabelChanged(tr("No schema"));
        }
    } else {
        p->emitSchemaLabelChanged(tr(""));
    }
}

void XmlEditWidgetPrivate::onActionInsertNoNamespaceSchemaReferenceAttributes()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    DomModel::EInsSchemaRefInfo error;
    error = model->insertNoNamespaceSchemaReferenceAttributes();
    decodeXsdInsertError(error);
}

void XmlEditWidgetPrivate::decodeXsdInsertError(const DomModel::EInsSchemaRefInfo error)
{
    switch(error) {
    default:
    case DomModel::INSERT_SCHEMA_ATTR_ERROR_NOROOT:
        Utils::error(p, tr("A root element is needed"));
        break;
    case DomModel::INSERT_SCHEMA_ATTR_INFO_SCHEMAPRESENT:
        Utils::message(p, tr("Schema definition already present."));
        break;
    case DomModel::INSERT_SCHEMA_ATTR_INFO_REFPRESENT:
        Utils::message(p, tr("Schema reference already present."));
        break;
    case DomModel::INSERT_SCHEMA_ATTR_NOERROR:
        return ;
    }
}

void XmlEditWidgetPrivate::onActionInsertSchemaReferenceAttributes()
{
    if(!isActionMode()) {
        return ;
    }
    if(NULL == model) {
        errorNoRule();
        return ;
    }
    DomModel::EInsSchemaRefInfo error;
    error = model->insertSchemaReferenceAttributes();
    decodeXsdInsertError(error);
}

void XmlEditWidgetPrivate::error(const QString &message)
{
    Utils::error(p, message);
}

void XmlEditWidgetPrivate::warning(const QString &message)
{
    Utils::warning(p, message);
}

void XmlEditWidgetPrivate::message(const QString &message)
{
    Utils::message(p, message);
}

bool XmlEditWidgetPrivate::askYN(const QString &message)
{
    return Utils::askYN(p, message);
}

QTreeWidget *XmlEditWidgetPrivate::getMainTreeWidget()
{
    return p->treeWidget;
}

void XmlEditWidgetPrivate::onActionHideAllLeafChildren()
{
    if(NULL != model) {
        p->treeWidget->setUpdatesEnabled(false);
        Utils::showWaitCursor();
        model->hideLeafNodes();;
        p->treeWidget->setUpdatesEnabled(true);
        Utils::restoreCursor();
    }
}

DomItem *XmlEditWidgetPrivate::onActionHideLeafChildren()
{
    DomItem *item = getSelectedItem();
    if(NULL != item) {
        p->treeWidget->setUpdatesEnabled(false);
        Utils::showWaitCursor();
        item->hideChildrenLeaves();
        p->treeWidget->setUpdatesEnabled(true);
        Utils::restoreCursor();
    }
    return item;
}

DomItem *XmlEditWidgetPrivate::onActionShowLeafChildren()
{
    DomItem *item = getSelectedItem();
    if(NULL != item) {
        p->treeWidget->setUpdatesEnabled(false);
        Utils::showWaitCursor();
        item->showChildrenLeaves();
        p->treeWidget->setUpdatesEnabled(true);
        Utils::restoreCursor();
    }
    return item;
}

void XmlEditWidgetPrivate::onActionShowAllLeafChildren()
{
    if(NULL != model) {
        p->treeWidget->setUpdatesEnabled(false);
        Utils::showWaitCursor();
        model->showLeafNodes();
        p->treeWidget->setUpdatesEnabled(true);
        Utils::restoreCursor();
    }
}

XSDSchema *XmlEditWidgetPrivate::schema()
{
    return _schemaRoot;
}

bool XmlEditWidgetPrivate::isExpandTreeOnLoad()
{
    return Config::getBool(Config::KEY_MAIN_EXPANDONLOAD, true);
}

bool XmlEditWidgetPrivate::isUndoPossible()
{
    return model->canUndo();
}

bool XmlEditWidgetPrivate::isRedoPossible()
{
    return model->canRedo();
}

void XmlEditWidgetPrivate::undo()
{
    model->undo();
}

void XmlEditWidgetPrivate::redo()
{
    model->redo();
}

void XmlEditWidgetPrivate::notifyUndo()
{
    emit p->undoStateUpdated(isUndoPossible(), isRedoPossible());
}

void XmlEditWidgetPrivate::modelUndoChanged()
{
    notifyUndo();
}

void XmlEditWidgetPrivate::setCurrentItem(DomItem *newSelection)
{
    if(NULL != newSelection) {
        p->treeWidget->setCurrentItem(newSelection->getUI());
    }
}
