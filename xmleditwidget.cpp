
#include <QXmlSchema>
#include <QXmlSchemaValidator>

#include "xmleditwidget.h"
#include "xsdeditor/xschemaloader.h"
#include "schemavalidator.h"

#include "config.h"
#include "findtextparams.h"
#include "dommodel.h"
#include "utils.h"
#include "xsdeditor/xsdplugin.h"
#include "xmleditwidgetprivate.h"

#define CS_ELEMENT_TEXT "E"
#define CS_ELEMENT_TAG "T"
#define CS_ATTRIBUTE_NAME "N"
#define CS_ATTRIBUTE_VALUE "V"

//const char *APP_TITLE = QT_TR_NOOP("ICD Creator");

XmlEditWidget::XmlEditWidget(QWidget *parent) :
    QWidget(parent),
    d(new XmlEditWidgetPrivate(this))
{
    setupUi();
    if(NULL != d) {
        d->secondStepConstructor();
    }
}

XmlEditWidget::~XmlEditWidget()
{
    if(NULL != d) {
        delete d;
    }
}

void XmlEditWidget::setupUi()
{
    if (objectName().isEmpty())
        setObjectName(QString::fromUtf8("XmlEditWidget"));
    resize(967, 673);
    QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    setSizePolicy(sizePolicy);
    verticalLayout_2 = new QVBoxLayout(this);
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    searchGroup = new QGroupBox(this);
    searchGroup->setObjectName(QString::fromUtf8("searchGroup"));
    searchGroup->setFlat(false);
    ricercaLayout = new QVBoxLayout(searchGroup);
    ricercaLayout->setObjectName(QString::fromUtf8("ricercaLayout"));
    searchTop = new QHBoxLayout();
    searchTop->setObjectName(QString::fromUtf8("searchTop"));
    closeSearchPanel = new QPushButton(searchGroup);
    closeSearchPanel->setObjectName(QString::fromUtf8("closeSearchPanel"));
    sizePolicy.setHeightForWidth(closeSearchPanel->sizePolicy().hasHeightForWidth());
    closeSearchPanel->setSizePolicy(sizePolicy);
    closeSearchPanel->setFocusPolicy(Qt::ClickFocus);
    closeSearchPanel->setAutoFillBackground(false);
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/quit/images/window-close.png"), QSize(), QIcon::Normal, QIcon::Off);
    closeSearchPanel->setIcon(icon);
    closeSearchPanel->setFlat(true);

    searchTop->addWidget(closeSearchPanel);

    label_2 = new QLabel(searchGroup);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

    searchTop->addWidget(label_2);

    searchEditBox = new QLineEdit(searchGroup);
    searchEditBox->setObjectName(QString::fromUtf8("searchEditBox"));

    searchTop->addWidget(searchEditBox);

    clearText = new QToolButton(searchGroup);
    clearText->setObjectName(QString::fromUtf8("clearText"));
    QIcon icon1;
    icon1.addFile(QString::fromUtf8(":/editText/images/edit-clear-locationbar-rtl.png"), QSize(), QIcon::Normal, QIcon::Off);
    clearText->setIcon(icon1);

    searchTop->addWidget(clearText);

    findButton = new QPushButton(searchGroup);
    findButton->setObjectName(QString::fromUtf8("findButton"));

    searchTop->addWidget(findButton);

    counting = new QPushButton(searchGroup);
    counting->setObjectName(QString::fromUtf8("counting"));

    searchTop->addWidget(counting);

    horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

    searchTop->addItem(horizontalSpacer_2);

    label = new QLabel(searchGroup);
    label->setObjectName(QString::fromUtf8("label"));
    label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

    searchTop->addWidget(label);

    searchLocation = new QComboBox(searchGroup);
    searchLocation->setObjectName(QString::fromUtf8("searchLocation"));
    searchLocation->setEditable(false);

    searchTop->addWidget(searchLocation);


    ricercaLayout->addLayout(searchTop);

    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    labelScope = new QLabel(searchGroup);
    labelScope->setObjectName(QString::fromUtf8("labelScope"));
    labelScope->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

    horizontalLayout_2->addWidget(labelScope);

    searchScope = new QLineEdit(searchGroup);
    searchScope->setObjectName(QString::fromUtf8("searchScope"));

    horizontalLayout_2->addWidget(searchScope);


    ricercaLayout->addLayout(horizontalLayout_2);

    searchBottom = new QHBoxLayout();
    searchBottom->setObjectName(QString::fromUtf8("searchBottom"));
    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    searchBottom->addItem(horizontalSpacer);

    closeUnrelated = new QCheckBox(searchGroup);
    closeUnrelated->setObjectName(QString::fromUtf8("closeUnrelated"));

    searchBottom->addWidget(closeUnrelated);

    isMatchExactValue = new QCheckBox(searchGroup);
    isMatchExactValue->setObjectName(QString::fromUtf8("isMatchExactValue"));

    searchBottom->addWidget(isMatchExactValue);

    isCaseSensitive = new QCheckBox(searchGroup);
    isCaseSensitive->setObjectName(QString::fromUtf8("isCaseSensitive"));

    searchBottom->addWidget(isCaseSensitive);

    isHiglightAll = new QCheckBox(searchGroup);
    isHiglightAll->setObjectName(QString::fromUtf8("isHiglightAll"));

    searchBottom->addWidget(isHiglightAll);

    isOnlyChildren = new QCheckBox(searchGroup);
    isOnlyChildren->setObjectName(QString::fromUtf8("isOnlyChildren"));

    searchBottom->addWidget(isOnlyChildren);

    showSize = new QCheckBox(searchGroup);
    showSize->setObjectName(QString::fromUtf8("showSize"));

    searchBottom->addWidget(showSize);


    ricercaLayout->addLayout(searchBottom);

    searchResultsLayout = new QHBoxLayout();
    searchResultsLayout->setObjectName(QString::fromUtf8("searchResultsLayout"));
    searchResult = new QLabel(searchGroup);
    searchResult->setObjectName(QString::fromUtf8("searchResult"));
    QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(searchResult->sizePolicy().hasHeightForWidth());
    searchResult->setSizePolicy(sizePolicy1);
    QFont font;
    font.setBold(true);
    font.setWeight(75);
    searchResult->setFont(font);
    searchResult->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

    searchResultsLayout->addWidget(searchResult);

    occNumber = new QLabel(searchGroup);
    occNumber->setObjectName(QString::fromUtf8("occNumber"));

    searchResultsLayout->addWidget(occNumber);

    lblSize = new QLabel(searchGroup);
    lblSize->setObjectName(QString::fromUtf8("lblSize"));
    lblSize->setFont(font);

    searchResultsLayout->addWidget(lblSize);

    sizeOfSearch = new QLabel(searchGroup);
    sizeOfSearch->setObjectName(QString::fromUtf8("sizeOfSearch"));

    searchResultsLayout->addWidget(sizeOfSearch);

    horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    searchResultsLayout->addItem(horizontalSpacer_3);


    ricercaLayout->addLayout(searchResultsLayout);

    verticalLayout_2->addWidget(searchGroup);

    cdataElement = new QCheckBox(this);
    cdataElement->setObjectName(QString::fromUtf8("cdataElement"));

    verticalLayout_2->addWidget(cdataElement);

    mainLayout = new QHBoxLayout();
    mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
    treeWidget = new QTreeWidget(this);
    treeWidget->setObjectName(QString::fromUtf8("treeWidget"));

    mainLayout->addWidget(treeWidget);

    verticalLayout = new QVBoxLayout();
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    docTypeLabel = new QLabel(this);
    docTypeLabel->setObjectName(QString::fromUtf8("docTypeLabel"));

    verticalLayout->addWidget(docTypeLabel);

    encoding = new QLabel(this);
    encoding->setObjectName(QString::fromUtf8("encoding"));
    encoding->setAlignment(Qt::AlignCenter);

    verticalLayout->addWidget(encoding);

    ok = new QPushButton(this);
    ok->setObjectName(QString::fromUtf8("ok"));

    verticalLayout->addWidget(ok);

    cancel = new QPushButton(this);
    cancel->setObjectName(QString::fromUtf8("cancel"));

    verticalLayout->addWidget(cancel);

    addChildButton = new QPushButton(this);
    addChildButton->setObjectName(QString::fromUtf8("addChild"));
    addChildButton->setStyleSheet(QString::fromUtf8("text-align:left;"));
    QIcon icon2;
    icon2.addFile(QString::fromUtf8(":/images/addchild"), QSize(), QIcon::Normal, QIcon::Off);
    addChildButton->setIcon(icon2);

    verticalLayout->addWidget(addChildButton);

    addBrotherButton = new QPushButton(this);
    addBrotherButton->setObjectName(QString::fromUtf8("addBrother"));
    addBrotherButton->setStyleSheet(QString::fromUtf8("text-align:left;"));
    QIcon icon3;
    icon3.addFile(QString::fromUtf8(":/images/addbrother"), QSize(), QIcon::Normal, QIcon::Off);
    addBrotherButton->setIcon(icon3);

    verticalLayout->addWidget(addBrotherButton);

    editItemButton = new QPushButton(this);
    editItemButton->setObjectName(QString::fromUtf8("editItem"));
    editItemButton->setStyleSheet(QString::fromUtf8("text-align:left;"));
    QIcon icon4;
    icon4.addFile(QString::fromUtf8(":/commands/modify"), QSize(), QIcon::Normal, QIcon::Off);
    editItemButton->setIcon(icon4);

    verticalLayout->addWidget(editItemButton);

    deleteItem = new QPushButton(this);
    deleteItem->setObjectName(QString::fromUtf8("deleteItem"));
    deleteItem->setStyleSheet(QString::fromUtf8("text-align:left;"));
    QIcon icon5;
    icon5.addFile(QString::fromUtf8(":/images/edit-delete"), QSize(), QIcon::Normal, QIcon::Off);
    deleteItem->setIcon(icon5);

    verticalLayout->addWidget(deleteItem);

    moveUpButton = new QPushButton(this);
    moveUpButton->setObjectName(QString::fromUtf8("moveUp"));
    moveUpButton->setStyleSheet(QString::fromUtf8("text-align:left;"));
    QIcon icon6;
    icon6.addFile(QString::fromUtf8(":/arrows/images/go-up.png"), QSize(), QIcon::Normal, QIcon::Off);
    moveUpButton->setIcon(icon6);

    verticalLayout->addWidget(moveUpButton);

    moveDownButton = new QPushButton(this);
    moveDownButton->setObjectName(QString::fromUtf8("moveDown"));
    moveDownButton->setStyleSheet(QString::fromUtf8("text-align:left;"));
    QIcon icon7;
    icon7.addFile(QString::fromUtf8(":/arrows/images/go-down.png"), QSize(), QIcon::Normal, QIcon::Off);
    moveDownButton->setIcon(icon7);

    verticalLayout->addWidget(moveDownButton);

    viewAsXsdCmd = new QPushButton(this);
    viewAsXsdCmd->setObjectName(QString::fromUtf8("viewAsXsdCmd"));

    verticalLayout->addWidget(viewAsXsdCmd);

    testPrev = new QPushButton(this);
    testPrev->setObjectName(QString::fromUtf8("testPrev"));
    testPrev->setEnabled(false);

    verticalLayout->addWidget(testPrev);

    testNext = new QPushButton(this);
    testNext->setObjectName(QString::fromUtf8("testNext"));
    testNext->setEnabled(false);

    verticalLayout->addWidget(testNext);

    parentNav = new QHBoxLayout();
    parentNav->setObjectName(QString::fromUtf8("parentNav"));
    parentNav->setSizeConstraint(QLayout::SetDefaultConstraint);
    parentNav->setContentsMargins(0, 0, -1, -1);

    verticalLayout->addLayout(parentNav);

    verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout->addItem(verticalSpacer);

    horizontalLowLayout = new QHBoxLayout();
    horizontalLowLayout->setObjectName(QString::fromUtf8("horizontalLowLayout"));
    horizontalLowLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
    styleButton = new QToolButton(this);
    styleButton->setObjectName(QString::fromUtf8("styleButton"));
    QIcon icon8;
    icon8.addFile(QString::fromUtf8(":/special/style"), QSize(), QIcon::Normal, QIcon::Off);
    styleButton->setIcon(icon8);
    styleButton->setPopupMode(QToolButton::InstantPopup);
    styleButton->setArrowType(Qt::NoArrow);

    horizontalLowLayout->addWidget(styleButton);

    copySpecial = new QToolButton(this);
    copySpecial->setObjectName(QString::fromUtf8("copySpecial"));
    QIcon icon9;
    icon9.addFile(QString::fromUtf8(":/copy/images/edit-copy.png"), QSize(), QIcon::Normal, QIcon::Off);
    copySpecial->setIcon(icon9);
    copySpecial->setPopupMode(QToolButton::InstantPopup);
    copySpecial->setArrowType(Qt::NoArrow);

    horizontalLowLayout->addWidget(copySpecial);
    verticalLayout->addLayout(horizontalLowLayout);
    mainLayout->addLayout(verticalLayout);

    verticalLayout_2->addLayout(mainLayout);

#ifndef QT_NO_SHORTCUT
    label_2->setBuddy(searchEditBox);
#endif // QT_NO_SHORTCUT

    retranslateUi();

    QMetaObject::connectSlotsByName(this);
}

void XmlEditWidget::retranslateUi()
{
    setWindowTitle(QApplication::translate("XmlEditWidget", "Form", 0, QApplication::UnicodeUTF8));
    searchGroup->setTitle(QApplication::translate("XmlEditWidget", "search", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    closeSearchPanel->setToolTip(QApplication::translate("XmlEditWidget", "Close search panel", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    closeSearchPanel->setStyleSheet(QApplication::translate("XmlEditWidget", "border-color:transparent;\n"
"", 0, QApplication::UnicodeUTF8));
    closeSearchPanel->setText(QString());
    label_2->setText(QApplication::translate("XmlEditWidget", "Text to Search", 0, QApplication::UnicodeUTF8));
    clearText->setText(QApplication::translate("XmlEditWidget", "...", 0, QApplication::UnicodeUTF8));
    findButton->setText(QApplication::translate("XmlEditWidget", "Find", 0, QApplication::UnicodeUTF8));
    counting->setText(QApplication::translate("XmlEditWidget", "Conta", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("XmlEditWidget", "Search in:", 0, QApplication::UnicodeUTF8));
    labelScope->setText(QApplication::translate("XmlEditWidget", "scope:", 0, QApplication::UnicodeUTF8));
    closeUnrelated->setText(QApplication::translate("XmlEditWidget", "Close Unrelated", 0, QApplication::UnicodeUTF8));
    isMatchExactValue->setText(QApplication::translate("XmlEditWidget", "Match Exact Value", 0, QApplication::UnicodeUTF8));
    isCaseSensitive->setText(QApplication::translate("XmlEditWidget", "Case Sensitive", 0, QApplication::UnicodeUTF8));
    isHiglightAll->setText(QApplication::translate("XmlEditWidget", "Find All", 0, QApplication::UnicodeUTF8));
    isOnlyChildren->setText(QApplication::translate("XmlEditWidget", "Only in Children", 0, QApplication::UnicodeUTF8));
    showSize->setText(QApplication::translate("XmlEditWidget", "Show Size", 0, QApplication::UnicodeUTF8));
    searchResult->setText(QApplication::translate("XmlEditWidget", "searchResults:", 0, QApplication::UnicodeUTF8));
    occNumber->setText(QString());
    lblSize->setText(QApplication::translate("XmlEditWidget", "Size:", 0, QApplication::UnicodeUTF8));
    sizeOfSearch->setText(QApplication::translate("XmlEditWidget", "---", 0, QApplication::UnicodeUTF8));
    cdataElement->setText(QApplication::translate("XmlEditWidget", "CDATA", 0, QApplication::UnicodeUTF8));
    QTreeWidgetItem *_qtreewidgetitem = treeWidget->headerItem();
    _qtreewidgetitem->setText(0, QApplication::translate("XmlEditWidget", "1", 0, QApplication::UnicodeUTF8));
    docTypeLabel->setText(QApplication::translate("XmlEditWidget", "---", 0, QApplication::UnicodeUTF8));
    encoding->setText(QApplication::translate("XmlEditWidget", "encoding:UTF8", 0, QApplication::UnicodeUTF8));
    ok->setText(QApplication::translate("XmlEditWidget", "OK", 0, QApplication::UnicodeUTF8));
    cancel->setText(QApplication::translate("XmlEditWidget", "Cancel", 0, QApplication::UnicodeUTF8));
    addChildButton->setText(QApplication::translate("XmlEditWidget", "Add &Child...", 0, QApplication::UnicodeUTF8));
    addBrotherButton->setText(QApplication::translate("XmlEditWidget", "&Append...", 0, QApplication::UnicodeUTF8));
    editItemButton->setText(QApplication::translate("XmlEditWidget", "&Edit...", 0, QApplication::UnicodeUTF8));
    deleteItem->setText(QApplication::translate("XmlEditWidget", "&Delete", 0, QApplication::UnicodeUTF8));
    moveUpButton->setText(QApplication::translate("XmlEditWidget", "Move &Up", 0, QApplication::UnicodeUTF8));
    moveDownButton->setText(QApplication::translate("XmlEditWidget", "Move &Down", 0, QApplication::UnicodeUTF8));
    viewAsXsdCmd->setText(QApplication::translate("XmlEditWidget", "View as XSD...", 0, QApplication::UnicodeUTF8));
    testPrev->setText(QApplication::translate("XmlEditWidget", "testPrev", 0, QApplication::UnicodeUTF8));
    testNext->setText(QApplication::translate("XmlEditWidget", "testNext", 0, QApplication::UnicodeUTF8));
    styleButton->setText(QApplication::translate("XmlEditWidget", "...", 0, QApplication::UnicodeUTF8));
    copySpecial->setText(QString());
}

//----------------  model
void XmlEditWidget::emitReevalueSelectionState()
{
    emit reevaluateSelectionState();
}

void XmlEditWidget::emitDocumentIsModified(const bool isModified)
{
    emit documentIsModified(isModified);
}

void XmlEditWidget::emitTreeContextMenuRequested(const QPoint &p)
{
    emit treeContextMenuRequested(p);
}

void XmlEditWidget::emitSignalSetClipBoardActionsState(const bool isAction)
{
    emit signalSetClipBoardActionsState(isAction);
}

void XmlEditWidget::emitOkClicked()
{
    emit okClicked();
}

void XmlEditWidget::emitCancelClicked()
{
    emit cancelClicked();
}

void XmlEditWidget::emitEnableZoom()
{
    emit enableZoom();
}

void XmlEditWidget::emitViewAsXsdRequested()
{
    emit viewAsXsdRequested();
}

void XmlEditWidget::emitSchemaLabelChanged(const QString &newLabel)
{
    emit schemaLabelChanged(newLabel);
}

void XmlEditWidget::emitShowStatusMessage(const QString &message, const bool isLongTimeout)
{
    emit showStatusMessage(message, isLongTimeout);
}

void XmlEditWidget::emitDataReadyMessage(const QString &newLabel)
{
    emit dataReadyMessage(newLabel);
}

void XmlEditWidget::emitLoadCurrentPage(const int page)
{
    emit loadCurrentPage(page);
}

//----- model(emit)

bool XmlEditWidget::isReady()
{
    if(NULL == d) {
        return false;
    }
    return d->isReady();
}

void XmlEditWidget::setData(QApplication *newApplication, QXmlEditData *newData, const bool newIsSlave)
{
    d->setData(newApplication, newData, newIsSlave);
}

bool XmlEditWidget::init()
{
    return d->init();
}

void XmlEditWidget::deleteSchema()
{
    d->deleteSchema();
}

void XmlEditWidget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch(e->type()) {
    case QEvent::StyleChange:
        VStyle::changeDefaultBrush(QApplication::palette().text());
        break;
    default:
        break;
    }
}

qxmledit::EDisplayMode XmlEditWidget::displayMode()
{
    return d->displayMode();
}

void XmlEditWidget::repaint()
{
    d->repaint();
}


PaintInfo* XmlEditWidget::getPaintInfo()
{
    return d->getPaintInfo();
}

void XmlEditWidget::display()
{
    d->display();
}


void XmlEditWidget::computeSelectionState()
{
    d->computeSelectionState();
}

DomItem *XmlEditWidget::getSelectedItem()
{
    return d->getSelectedItem();
}

void XmlEditWidget::resetTree()
{
    d->resetTree();
}


void XmlEditWidget::onActionNewFromClipboard()
{
    d->onActionNewFromClipboard();
}

void XmlEditWidget::onActionResizeToContents()
{
    d->onActionResizeToContents();
}

void XmlEditWidget::setEncodingLabelVisible(bool isShow)
{
    d->setEncodingLabelVisible(isShow);
}

bool XmlEditWidget::isEncodingLabelVisible()
{
    return d->isEncodingLabelVisible();
}

void XmlEditWidget::setDocTypeVisible(bool isShow)
{
    d->setDocTypeVisible(isShow);
}

bool XmlEditWidget::isDocTypeVisible()
{
    return d->isDocTypeVisible();
}

void XmlEditWidget::setViewAsXSDButtonVisible(bool isShow)
{
    d->setViewAsXSDButtonVisible(isShow);
}

bool XmlEditWidget::isViewAsXSDButtonVisible()
{
    return d->isViewAsXSDButtonVisible();
}

void XmlEditWidget::setMoveButtonsVisible(bool isShow)
{
    d->setMoveButtonsVisible(isShow);
}

bool XmlEditWidget::areMoveButtonsVisible()
{
    return d->areMoveButtonsVisible();
}

ulong XmlEditWidget::versionNumber()
{
    return d->versionNumber();
}

void XmlEditWidget::resizeTreeColumns()
{
    d->resizeTreeColumns();
}

bool XmlEditWidget::editItem(QTreeWidgetItem *item)
{
    return d->editItem(item);
}


void XmlEditWidget::addChild()
{
    d->addChild();
}

void XmlEditWidget::addBrother()
{
    d->addBrother();
}

void XmlEditWidget::errorNoRule()
{
    d->errorNoRule();
}

void XmlEditWidget::onActionAddChildItem()
{
    d->onActionAddChildElement();
}

void XmlEditWidget::onActionAppendChildItem()
{
    d->onActionAppendChildElement();
}

void XmlEditWidget::onActionEdit()
{
    d->onActionEdit();
}

void XmlEditWidget::onActionDelete()
{
    d->onActionDelete();
}

void XmlEditWidget::onActionMoveUp()
{
    d->onActionMoveUp();
}

void XmlEditWidget::onActionMoveDown()
{
    d->onActionMoveDown();
}

void XmlEditWidget::cleanClipBoard()
{
    d->cleanClipBoard();
}

void XmlEditWidget::setClipBoardItem(DomItem *pElement)
{
    d->setClipBoardItem(pElement);
}

void XmlEditWidget::onActionCut()
{
    d->onActionCut();
}

void XmlEditWidget::onActionCopy()
{
    d->onActionCopy();
}

void XmlEditWidget::onActionPaste()
{
    d->onActionPaste();
}

DomItem *XmlEditWidget::getClipBoardItem() const
{
    return d->getClipBoardItem();
}

void XmlEditWidget::onActionExpandAll()
{
    d->onActionExpandAll();
}

void XmlEditWidget::onActionShowAttrLine(const bool state)
{
    d->onActionShowAttrLine(state);
}

void XmlEditWidget::onActionAddComment()
{
    d->onActionAddComment();
}

void XmlEditWidget::onActionAppendComment()
{
    d->onActionAppendComment();
}

void XmlEditWidget::onActionAppendProcessingInstruction()
{
    d->onActionAppendProcessingInstruction();
}

void XmlEditWidget::onActionAddProcessingInstruction()
{
    d->onActionAddProcessingInstruction();
}

void XmlEditWidget::onActionFind()
{
    d->onActionFind();
}

void XmlEditWidget::onActionGoToParent()
{
    d->onActionGoToParent();
}

void XmlEditWidget::onActionGoToPreviousBrother()
{
    d->onActionGoToPreviousBrother();
}

void XmlEditWidget::onActionGoToNextBrother()
{
    d->onActionGoToNextBrother();
}

void XmlEditWidget::onActionShowChildIndex(const bool isChecked)
{
    d->onActionShowChildIndex(isChecked);
}

void XmlEditWidget::onActionCompactView(const bool isChecked)
{
    d->onActionCompactView(isChecked);
}

void XmlEditWidget::onActionFixedSizeAttributes(const bool isChecked)
{
    d->onActionFixedSizeAttributes(isChecked);
}

void XmlEditWidget::onActionShowAttributesLength(const bool isChecked)
{
    d->onActionShowAttributesLength(isChecked);
}

void XmlEditWidget::onActionShowItemTextLength(const bool isChecked)
{
    d->onActionShowElementTextLength(isChecked);
}

void XmlEditWidget::onActionCloseThisAllBrothers()
{
    d->onActionCloseThisAllBrothers();
}


void XmlEditWidget::onActionHideBrothers()
{
    d->onActionHideBrothers();
}

//void XmlEditWidget::onActionShowCurrentItemTextBase64(const bool isChecked)
//{
//    d->onActionShowCurrentElementTextBase64(isChecked);
//}

//void XmlEditWidget::onActionShowBase64(const bool isChecked)
//{
//    d->onActionShowBase64(isChecked);
//}

void XmlEditWidget::onActionShowItemSize(const bool isChecked)
{
    d->onActionShowElementSize(isChecked);
}

QString XmlEditWidget::getContentAsText()
{
    return d->getContentAsText();
}

bool XmlEditWidget::isCDATA()
{
    return d->isCDATA();
}

void XmlEditWidget::setCDATA(const bool isCData)
{
    d->setCDATA(isCData);
}

void XmlEditWidget::onActionZoomIn()
{
    d->onActionZoomIn();
}

void XmlEditWidget::onActionZoomOut()
{
    d->onActionZoomOut();
}
//da decidere se emette o torna un flag

void XmlEditWidget::onActionCopyPathToClipboard()
{
    d->onActionCopyPathToClipboard();
}

void XmlEditWidget::onActionValidate()
{
    d->onActionValidate();
}

void XmlEditWidget::onActionValidateFile()
{
    d->onActionValidateFile();
}

void XmlEditWidget::validateWithFile(const QString &filePath)
{
    d->validateWithFile(filePath);
}

bool XmlEditWidget::isUndoPossible()
{
    return d->isUndoPossible();
}

bool XmlEditWidget::isRedoPossible()
{
    return d->isRedoPossible();
}

void XmlEditWidget::undo()
{
    d->undo();
}

void XmlEditWidget::redo()
{
    d->redo();
}


XSDSchema* XmlEditWidget::schema()
{
    return d->schema();
}

void XmlEditWidget::onActionValidateNewFile()
{
    d->onActionValidateNewFile();
}

void XmlEditWidget::insertSnippet(DomModel *newModel)
{
    d->insertSnippet(newModel);
}

bool XmlEditWidget::isActionMode()
{
    return d->isActionMode();
}

bool XmlEditWidget::isActionNoScanMode()
{
    return d->isActionNoScanMode();
}

bool XmlEditWidget::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == searchEditBox) {
        if(event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            if(!keyEvent->isAutoRepeat()
                    && ((keyEvent->key() == Qt::Key_Enter) || (keyEvent->key() == Qt::Key_Return))) {
                findButton->animateClick();
                return true ;
            }
        }
        return false;
    }
    return XmlEditWidget::eventFilter(obj, event);
}

void XmlEditWidget::setDisplayMode(const qxmledit::EDisplayMode value)
{
    d->setDisplayMode(value);
}


/**
  changestate if the state is to be reset to normal after loading new document
  */
void XmlEditWidget::loadText(const QString &text, const bool isChangeState, const bool isAskForReview)
{
    d->loadText(text, isChangeState, isAskForReview);

}

//---------------------- load data

//TODO: error checking
void XmlEditWidget::doLoadFileXplore(const QString &filePath)
{
    d->doLoadFileXplore(filePath);
}

//TODO: error checking
void XmlEditWidget::setDocument(QDomDocument &document, const QString &filePath, const bool isSetState)
{
    d->setDocument(document, filePath, isSetState);
}

void XmlEditWidget::onActionHideView(const bool isChecked)
{
    d->onActionHideView(isChecked);
}

bool XmlEditWidget::isValidXsd()
{
    return d->isValidXsd();
}


DomModel *XmlEditWidget::getModel()
{
    return d->getModel();
}


void XmlEditWidget::onActionViewAsXsd()
{
    d->onActionViewAsXsd();
}

void XmlEditWidget::loadSchema(const QString &schemaURL)
{
    d->loadSchema(schemaURL);
}

void XmlEditWidget::setCurrentItem(DomItem *newSelection)
{
    d->setCurrentItem(newSelection);
}

void XmlEditWidget::onActionAllowedSchemaItems()
{
    d->onActionAllowedSchemaElements();
}

void XmlEditWidget::insertAllowedItem(DomItem *item)
{
    d->insertAllowedItems(item);
}


void XmlEditWidget::onActionNewUsingXMLSchema(const QString &schemaURL)
{
    d->onActionNewUsingXMLSchema(schemaURL);
}

void XmlEditWidget::doNew()
{
    d->doNew();
}

void XmlEditWidget::onActionTransformInComment()
{
    d->onActionTransformInComment();
}

void XmlEditWidget::onActionExtractItemsFromComment()
{
    d->onActionExtractElementsFromComment();
}

void XmlEditWidget::autoLoadValidation()
{
    d->autoLoadValidation();
}

void XmlEditWidget::onActionInsertNoNamespaceSchemaReferenceAttributes()
{
    d->onActionInsertNoNamespaceSchemaReferenceAttributes();
}

void XmlEditWidget::onActionInsertSchemaReferenceAttributes()
{
    d->onActionInsertSchemaReferenceAttributes();
}

void XmlEditWidget::error(const QString& message)
{
    Utils::error(this, message);
}

void XmlEditWidget::warning(const QString& message)
{
    Utils::warning(this, message);
}

void XmlEditWidget::message(const QString& message)
{
    Utils::message(this, message);
}

bool XmlEditWidget::askYN(const QString & message)
{
    return Utils::askYN(this, message);
}

QTreeWidget *XmlEditWidget::getMainTreeWidget()
{
    return d->getMainTreeWidget();
}

void XmlEditWidget::onActionHideAllLeafChildren()
{
    d->onActionHideAllLeafChildren();
}

DomItem* XmlEditWidget::onActionHideLeafChildren()
{
    return d->onActionHideLeafChildren();
}

DomItem* XmlEditWidget::onActionShowLeafChildren()
{
    return d->onActionShowLeafChildren();
}

void XmlEditWidget::onActionShowAllLeafChildren()
{
    d->onActionShowAllLeafChildren();
}

XmlEditWidgetPrivate *XmlEditWidget::getPrivate()
{
    return d;
}
