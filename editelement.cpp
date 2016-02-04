
#include "editelement.h"
#include "edittextnode.h"
#include "dommodel.h"
#include "utils.h"
#include <QItemSelectionModel>

#define MOD_WIDTH   (8)

EditElement::EditElement(QWidget * parent) : QDialog(parent)
{
    isStarted = false;
    modColor = QColor::fromRgb(255, 128, 128);
    isMixedContent = false ;
    init();
    elementTable->setColumnWidth(T_COLUMN_MOD, MOD_WIDTH);
    attrTable->setColumnWidth(A_COLUMN_MOD, MOD_WIDTH);
    target = NULL;
    enableOK();
    if(noUseAttrTable->rowCount() > 0)
        newAttribute->setEnabled(true);
    else
        newAttribute->setEnabled(false);
}

EditElement::~EditElement()
{
}

void EditElement::init()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QString::fromUtf8("Dialog"));
    resize(857, 701);
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    setSizePolicy(sizePolicy);
    actionEditItem = new QAction(this);
    actionEditItem->setObjectName(QString::fromUtf8("actionEditItem"));
    horizontalLayout_5 = new QHBoxLayout(this);
    horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
    verticalLayout_3 = new QVBoxLayout();
    verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    label_2 = new QLabel(this);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
    label_2->setSizePolicy(sizePolicy1);
    label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

    horizontalLayout->addWidget(label_2);

    path = new QLabel(this);
    path->setObjectName(QString::fromUtf8("path"));

    horizontalLayout->addWidget(path);


    verticalLayout_3->addLayout(horizontalLayout);

    groupBox = new QGroupBox(this);
    groupBox->setObjectName(QString::fromUtf8("groupBox"));
    QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Minimum);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
    groupBox->setSizePolicy(sizePolicy2);
    groupBox->setMinimumSize(QSize(0, 0));
    verticalLayout_5 = new QVBoxLayout(groupBox);
    verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
    horizontalLayout_4 = new QHBoxLayout();
    horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
    label = new QLabel(groupBox);
    label->setObjectName(QString::fromUtf8("label"));
    QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Preferred);
    sizePolicy3.setHorizontalStretch(0);
    sizePolicy3.setVerticalStretch(0);
    sizePolicy3.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
    label->setSizePolicy(sizePolicy3);
    label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

    horizontalLayout_4->addWidget(label);

    editTag = new QLineEdit(groupBox);
    editTag->setObjectName(QString::fromUtf8("editTag"));
    QSizePolicy sizePolicy4(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    sizePolicy4.setHorizontalStretch(0);
    sizePolicy4.setVerticalStretch(0);
    sizePolicy4.setHeightForWidth(editTag->sizePolicy().hasHeightForWidth());
    editTag->setSizePolicy(sizePolicy4);

    horizontalLayout_4->addWidget(editTag);

    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_4->addItem(horizontalSpacer);


    verticalLayout_5->addLayout(horizontalLayout_4);

    label_6 = new QLabel(groupBox);
    label_6->setObjectName(QString::fromUtf8("label_6"));

    verticalLayout_5->addWidget(label_6);

    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    horizontalLayout_3 = new QHBoxLayout();
    horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
    horizontalLayout_3->setSizeConstraint(QLayout::SetMaximumSize);
    elementTable = new QTableWidget(groupBox);
    if (elementTable->columnCount() < 3)
        elementTable->setColumnCount(3);
    QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
    elementTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
    QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
    elementTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
    QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
    elementTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
    elementTable->setObjectName(QString::fromUtf8("elementTable"));
    sizePolicy2.setHeightForWidth(elementTable->sizePolicy().hasHeightForWidth());
    elementTable->setSizePolicy(sizePolicy2);
    elementTable->setMinimumSize(QSize(0, 0));
    elementTable->setCornerButtonEnabled(true);
    elementTable->setColumnCount(3);
    elementTable->horizontalHeader()->setVisible(true);
    elementTable->horizontalHeader()->setCascadingSectionResizes(false);
    elementTable->horizontalHeader()->setStretchLastSection(true);

    horizontalLayout_3->addWidget(elementTable);


    horizontalLayout_2->addLayout(horizontalLayout_3);

    verticalLayout_4 = new QVBoxLayout();
    verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
    verticalLayout_4->setSizeConstraint(QLayout::SetMaximumSize);
    textAdd = new QPushButton(groupBox);
    textAdd->setObjectName(QString::fromUtf8("textAdd"));

    verticalLayout_4->addWidget(textAdd);

    textDel = new QPushButton(groupBox);
    textDel->setObjectName(QString::fromUtf8("textDel"));
    textDel->setEnabled(false);

    verticalLayout_4->addWidget(textDel);

    textEdit = new QPushButton(groupBox);
    textEdit->setObjectName(QString::fromUtf8("textEdit"));
    textEdit->setEnabled(false);

    verticalLayout_4->addWidget(textEdit);

    textUp = new QPushButton(groupBox);
    textUp->setObjectName(QString::fromUtf8("textUp"));
    textUp->setEnabled(false);

    verticalLayout_4->addWidget(textUp);

    textDown = new QPushButton(groupBox);
    textDown->setObjectName(QString::fromUtf8("textDown"));
    textDown->setEnabled(false);

    verticalLayout_4->addWidget(textDown);

    verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Minimum);

    verticalLayout_4->addItem(verticalSpacer_2);


    horizontalLayout_2->addLayout(verticalLayout_4);


    verticalLayout_5->addLayout(horizontalLayout_2);


    verticalLayout_3->addWidget(groupBox);

    horizontalLayout_1 = new QHBoxLayout();
    horizontalLayout_1->setObjectName(QString::fromUtf8("horizontalLayout_1"));
    verticalLayout_2 = new QVBoxLayout();
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    label_3 = new QLabel(this);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    verticalLayout_2->addWidget(label_3);

    attrTable = new QTableWidget(this);
    if (attrTable->columnCount() < 3)
        attrTable->setColumnCount(3);
    QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
    attrTable->setHorizontalHeaderItem(0, __qtablewidgetitem3);
    QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
    attrTable->setHorizontalHeaderItem(1, __qtablewidgetitem4);
    QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
    attrTable->setHorizontalHeaderItem(2, __qtablewidgetitem5);
    attrTable->setObjectName(QString::fromUtf8("attrTable"));
    attrTable->setAlternatingRowColors(true);
    attrTable->setShowGrid(true);
    attrTable->setSortingEnabled(true);
    attrTable->setColumnCount(3);
    attrTable->horizontalHeader()->setCascadingSectionResizes(false);
    attrTable->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
    attrTable->horizontalHeader()->setStretchLastSection(true);

    label_4 = new QLabel(this);
    label_4->setObjectName(QString::fromUtf8("label_4"));
    noUseAttrTable = new QTableWidget(this);
    if (noUseAttrTable->columnCount() < 1)
        noUseAttrTable->setColumnCount(1);
    QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
    noUseAttrTable->setHorizontalHeaderItem(0, __qtablewidgetitem6);
    noUseAttrTable->setObjectName(QString::fromUtf8("noUseAttrTable"));
    noUseAttrTable->setAlternatingRowColors(true);
    noUseAttrTable->setShowGrid(true);
    noUseAttrTable->setSortingEnabled(true);
    noUseAttrTable->setColumnCount(1);
    noUseAttrTable->horizontalHeader()->setCascadingSectionResizes(false);
    noUseAttrTable->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
    noUseAttrTable->horizontalHeader()->setStretchLastSection(true);

    verticalLayout_2->addWidget(attrTable);

    verticalLayout_2->addWidget(label_4);
    verticalLayout_2->addWidget(noUseAttrTable);

    layBox1 = new QHBoxLayout();
    layBox1->setObjectName(QString::fromUtf8("layBox1"));

    verticalLayout_2->addLayout(layBox1);


    horizontalLayout_1->addLayout(verticalLayout_2);

    verticalLayout = new QVBoxLayout();
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    newAttribute = new QPushButton(this);
    newAttribute->setObjectName(QString::fromUtf8("newAttribute"));

    verticalLayout->addWidget(newAttribute);

    delAttribute = new QPushButton(this);
    delAttribute->setObjectName(QString::fromUtf8("delAttribute"));
    delAttribute->setEnabled(false);

    verticalLayout->addWidget(delAttribute);

    attrUp = new QPushButton(this);
    attrUp->setObjectName(QString::fromUtf8("attrUp"));
    attrUp->setEnabled(false);

    verticalLayout->addWidget(attrUp);

    attrDown = new QPushButton(this);
    attrDown->setObjectName(QString::fromUtf8("attrDown"));
    attrDown->setEnabled(false);

    verticalLayout->addWidget(attrDown);

    verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout->addItem(verticalSpacer);


    horizontalLayout_1->addLayout(verticalLayout);


    verticalLayout_3->addLayout(horizontalLayout_1);


    horizontalLayout_5->addLayout(verticalLayout_3);

    verticalLayout_6 = new QVBoxLayout();
    verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy5.setHorizontalStretch(0);
    sizePolicy5.setVerticalStretch(0);
    sizePolicy5.setHeightForWidth(buttonBox->sizePolicy().hasHeightForWidth());
    buttonBox->setSizePolicy(sizePolicy5);
    buttonBox->setOrientation(Qt::Vertical);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    buttonBox->setCenterButtons(false);

    verticalLayout_6->addWidget(buttonBox);

    verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout_6->addItem(verticalSpacer_3);


    horizontalLayout_5->addLayout(verticalLayout_6);

#ifndef QT_NO_SHORTCUT
    label->setBuddy(editTag);
    label_6->setBuddy(elementTable);
    label_3->setBuddy(attrTable);
    label_4->setBuddy(noUseAttrTable);
#endif // QT_NO_SHORTCUT
    QWidget::setTabOrder(textDel, newAttribute);
    QWidget::setTabOrder(newAttribute, delAttribute);
    QWidget::setTabOrder(delAttribute, buttonBox);

    retranslate();
    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QMetaObject::connectSlotsByName(this);
}

void EditElement::retranslate()
{
    setWindowTitle(QApplication::translate("Dialog", "Edit Element", 0, QApplication::UnicodeUTF8));
    actionEditItem->setText(QApplication::translate("Dialog", "editItem", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("Dialog", "Path:", 0, QApplication::UnicodeUTF8));
    path->setText(QApplication::translate("Dialog", "------", 0, QApplication::UnicodeUTF8));
    groupBox->setTitle(QApplication::translate("Dialog", "Element Text", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("Dialog", "Ta&g:", 0, QApplication::UnicodeUTF8));
    label_6->setText(QApplication::translate("Dialog", "Text &Nodes:", 0, QApplication::UnicodeUTF8));
    QTableWidgetItem *___qtablewidgetitem = elementTable->horizontalHeaderItem(1);
    ___qtablewidgetitem->setText(QApplication::translate("Dialog", "CDATA Section", 0, QApplication::UnicodeUTF8));
    QTableWidgetItem *___qtablewidgetitem1 = elementTable->horizontalHeaderItem(2);
    ___qtablewidgetitem1->setText(QApplication::translate("Dialog", "Text Content", 0, QApplication::UnicodeUTF8));
    textAdd->setText(QApplication::translate("Dialog", "+", 0, QApplication::UnicodeUTF8));
    textDel->setText(QApplication::translate("Dialog", "-", 0, QApplication::UnicodeUTF8));
    textEdit->setText(QApplication::translate("Dialog", "Mod...", 0, QApplication::UnicodeUTF8));
    textUp->setText(QApplication::translate("Dialog", "Up", 0, QApplication::UnicodeUTF8));
    textDown->setText(QApplication::translate("Dialog", "Down", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("Dialog", "&Attributes", 0, QApplication::UnicodeUTF8));
    QTableWidgetItem *___qtablewidgetitem2 = attrTable->horizontalHeaderItem(1);
    ___qtablewidgetitem2->setText(QApplication::translate("Dialog", "Name", 0, QApplication::UnicodeUTF8));
    QTableWidgetItem *___qtablewidgetitem3 = attrTable->horizontalHeaderItem(2);
    ___qtablewidgetitem3->setText(QApplication::translate("Dialog", "Value", 0, QApplication::UnicodeUTF8));
    newAttribute->setText(QApplication::translate("Dialog", "+", 0, QApplication::UnicodeUTF8));
    delAttribute->setText(QApplication::translate("Dialog", "-", 0, QApplication::UnicodeUTF8));
    attrUp->setText(QApplication::translate("Dialog", "Up", 0, QApplication::UnicodeUTF8));
    attrDown->setText(QApplication::translate("Dialog", "Down", 0, QApplication::UnicodeUTF8));
    label_4->setText(QApplication::translate("Dialog", "A&viable Attributes", 0, QApplication::UnicodeUTF8));
    QTableWidgetItem *___qtablewidgetitem4 = attrTable->horizontalHeaderItem(0);
    ___qtablewidgetitem4->setText(QApplication::translate("Dialog", "Name", 0, QApplication::UnicodeUTF8));
}

void EditElement::enableOK()
{
    bool isEnabled = true ;
    QString theTag = editTag->text();
    if(theTag.isEmpty()) {
        isEnabled = false ;
    } else {
        isEnabled = checkTagSyntax(theTag) ;
    }
    buttonBox->button(QDialogButtonBox::Ok)->setEnabled(isEnabled);
}


bool EditElement::checkTagSyntax(const QString &theTag)
{
    return Utils::checkXMLName(theTag);
}

void EditElement::on_editTag_textChanged(const QString & /*theText*/)
{
    enableOK();
}

void EditElement::setTarget(DomItem* pTarget)
{
    target = pTarget ;
    isMixedContent = target->isMixedContent();
    QStringList pathList = target->path();
    QString setPath = pathList.join("/");
    setPath = "/" + setPath ;
    path->setText(setPath);
    show();
    editTag->setText(target->tag());
    attrTable->setUpdatesEnabled(false);
    QVector<Attribute*>::iterator it;
    for(it = target->attributes.begin(); it != target->attributes.end(); ++it) {
        Attribute* attr = *it;
        appendAttrNodeInTable(attrTable, -1, attr->name, attr->value);
    }
    attrTable->setUpdatesEnabled(true);

    noUseAttrTable->setUpdatesEnabled(false);
    setAviableAttrbutes(noUseAttrTable);
    noUseAttrTable->setUpdatesEnabled(true);
    // to free resources
    elementTable->setUpdatesEnabled(false);
    if(!isMixedContent) {
        QVectorIterator<TextChunk*> tt(target->getTextChunks());
        while(tt.hasNext()) {
            TextChunk *tOrig = tt.next();
            appendTextNodeInTable(elementTable, true, -1, tOrig->isCDATA, tOrig->text, NULL);
        }
    }
    foreach(DomItem * child, target->getItems()) {
        if(child->getType() == DomItem::ET_TEXT) {
            appendTextNodeInTable(elementTable, true, -1, child->isCDATA(), child->text, child);
        } else {
            QString textToShow ;
            switch(child->getType()) {
            default:
                textToShow = tr("** child **");
                break;
            case DomItem::ET_COMMENT:
                textToShow = tr("** comment **");
                break;
            case DomItem::ET_ELEMENT:
                textToShow = tr("** element: <%1>").arg(child->tag());
                break;
            case DomItem::ET_PROCESSING_INSTRUCTION:
                textToShow = tr("** processing instruction: %1").arg(child->getPITarget());
                break;
            }
            appendTextNodeInTable(elementTable, false, -1, false, textToShow, child);
        }
    }
    elementTable->setUpdatesEnabled(true);
    elementTable->resizeRowsToContents();
    enableOK();
    isStarted = true ;
}

void EditElement::accept()
{
    if(NULL == target) {
        error(tr("No target"));
        return;
    }
    QString tag = editTag->text();
    if(0 == tag.length()) {
        error(tr("Tag text is invalid"));
        return ;
    }
    target->_tag = target->getParentRule()->addNameToPool(tag) ;
    // rebuild attributes
    target->clearAttributes();
    int rows = attrTable->rowCount();
    for(int row = 0 ; row < rows ; row ++) {
        QTableWidgetItem *itemName = attrTable->item(row, A_COLUMN_NAME);
        QString name = itemName->text().trimmed() ;
        if(!validateAttr(name)) {
            error(tr("An attribute is invalid at row %1").arg(row));
            return ;
        }
    }

    for(int row = 0 ; row < rows ; row ++) {
        QTableWidgetItem *itemName = attrTable->item(row, A_COLUMN_NAME);
        QTableWidgetItem *itemValue = attrTable->item(row, A_COLUMN_TEXT);
        QString name = itemName->text().trimmed() ;
        QString value = itemValue->text().trimmed() ;
        target->addAttribute(name, value);
    }
    target->clearTextNodes();

    isMixedContent = false ;
    bool isElement = false;
    bool isText = false;

    rows = elementTable->rowCount();
    for(int row = 0 ; row < rows ; row ++) {
        QTableWidgetItem *itemCDATA = elementTable->item(row, T_COLUMN_CDATA);
        DomItem *element = getUserData(itemCDATA);
        if((NULL == element) || ((NULL != element) && (element->getType() == DomItem::ET_TEXT))) {
            isText = true ;
            if(isElement) {
                break;
            }
        } else {
            isElement = true ;
            if(isText) {
                break;
            }
        }
    }
    if(isElement && isText) {
        isMixedContent = true ;
    }
    foreach(DomItem * child, target->getItems()) {
        if(child->getType() == DomItem::ET_TEXT) {
            child->autoDelete(true);
        }
    }

    if(isMixedContent) {
        target->getChildItems()->clear();
        rows = elementTable->rowCount();
        for(int row = 0 ; row < rows ; row ++) {
            QTableWidgetItem *itemCDATA = elementTable->item(row, T_COLUMN_CDATA);
            QTableWidgetItem *itemValue = elementTable->item(row, T_COLUMN_TEXT);
            DomItem *element = getUserData(itemCDATA);
            if((NULL == element) || ((NULL != element) && (element->getType() == DomItem::ET_TEXT))) {
                DomItem *newElement = new DomItem(target->getParentRule(), DomItem::ET_TEXT, target);
                newElement->setTextOfTextNode(itemValue->text(), itemCDATA->checkState() == Qt::Checked);
                target->getItems().append(newElement);
                newElement->setChildItem(target->getUI()->treeWidget(), target->getUI(), target->getParentRule()->getPaintInfo(), true, row);
            } else {
                target->getItems().append(element);
            }
        }
    } else {
        rows = elementTable->rowCount();
        for(int row = 0 ; row < rows ; row ++) {
            QTableWidgetItem *itemCDATA = elementTable->item(row, T_COLUMN_CDATA);
            QTableWidgetItem *itemValue = elementTable->item(row, T_COLUMN_TEXT);
            DomItem *element = getUserData(itemCDATA);
            if((NULL == element) || ((NULL != element) && (element->getType() == DomItem::ET_TEXT))) {
                TextChunk *newText = new TextChunk(itemCDATA->checkState() == Qt::Checked, itemValue->text());
                target->addTextNode(newText);
            }
        }
    }
    QDialog::accept();
}

void EditElement::error(const QString& message)
{
    Utils::error(this, message);
}

bool EditElement::validateAttr(const QString &name)
{
    return Utils::checkXMLName(name);
}

void EditElement::setUpdatedAttr(const int row)
{
    if(isStarted && (row >= 0)) {
        QTableWidgetItem * item = attrTable->item(row, A_COLUMN_MOD);
        if(NULL != item) {
            item->setBackgroundColor(modColor);
        }
    }
}

void EditElement::setUpdatedElement(const int row)
{
    if(isStarted && (row >= 0)) {
        QTableWidgetItem * item = elementTable->item(row, A_COLUMN_MOD);
        if(NULL != item) {
            item->setBackgroundColor(modColor);
        }
    }
}

void EditElement::on_newAttribute_clicked()
{
    int currentRow = attrTable->currentRow();
    int newRow = getNextRow(currentRow);
    int currAviableTableRow = noUseAttrTable->currentRow();
    if(currAviableTableRow < 0)
        currAviableTableRow = noUseAttrTable->rowCount() - 1;
    noUseAttrTable->setCurrentItem(noUseAttrTable->item(currAviableTableRow, 0));
    QString newAttrName = noUseAttrTable->currentItem()->text();
    newRow = appendAttrNodeInTable(attrTable, newRow, newAttrName, "");
    setUpdatedAttr(newRow);
    noUseAttrTable->removeRow(currAviableTableRow);
    if(noUseAttrTable->rowCount() > 0)
        newAttribute->setEnabled(true);
    else
        newAttribute->setEnabled(false);

}

void EditElement::on_attrTable_itemChanged(QTableWidgetItem * item)
{
    setUpdatedAttr(attrTable->row(item));
}

void EditElement::on_delAttribute_clicked()
{
    int currentRow = attrTable->currentRow();
    QString currAttrName = attrTable->item(currentRow, 1)->text();
    int noUseAttrTableRow = noUseAttrTable->rowCount();
    if(currentRow >= 0) {       
        attrTable->removeRow(currentRow);
        noUseAttrTable->setRowCount(noUseAttrTableRow + 1);
        noUseAttrTable->setItem(noUseAttrTableRow, 0, new QTableWidgetItem(currAttrName));
    } else {
        Utils::error(this, tr("No attribute selected"));
    }
    if(noUseAttrTable->rowCount() > 0)
        newAttribute->setEnabled(true);
    else
        newAttribute->setEnabled(false);
}

void EditElement::errorNoAttrSel()
{
    Utils::error(this, tr("No attribute selected, can't execute command."));
}

void EditElement::errorNoAttrData()
{
    Utils::error(this, tr("Please, insert name and value for attribute."));
}


void EditElement::on_textEdit_clicked()
{
    int currentRow = elementTable->currentRow();
    if(currentRow >= 0) {
        EditTextNode editDialog(false, this);
        editDialog.setModal(true);
        editDialog.setText(elementTable->item(currentRow, T_COLUMN_TEXT)->text());
        if(editDialog.exec() == QDialog::Accepted) {
            elementTable->item(currentRow, T_COLUMN_TEXT)->setText(editDialog.getText());
            setUpdatedElement(currentRow);
            elementTable->resizeRowToContents(currentRow);
        }
    }
}

void EditElement::on_elementTable_itemSelectionChanged()
{
    int currentRow = elementTable->currentRow();
    int rows = elementTable->rowCount();
    bool isSelected = false;
    if(currentRow >= 0) {
        isSelected = true ;
    }
    textEdit->setEnabled(isSelected);
    if(isMixedContent) {
        QTableWidgetItem *item = elementTable->item(currentRow, 0);
        if(isElementText(item)) {
            textDel->setEnabled(isSelected);
        } else {
            textDel->setEnabled(false);
        }
    } else {
        textDel->setEnabled(isSelected);
    }

    if(currentRow > 0) {
        textUp->setEnabled(true);
    } else {
        textUp->setEnabled(false);
    }
    if((currentRow >= 0) && (rows > 0) && (currentRow < (rows - 1)))   {
        textDown->setEnabled(true);
    } else {
        textDown->setEnabled(false);
    }
}

void EditElement::on_attrTable_itemSelectionChanged()
{
    int currentRow = attrTable->currentRow();
    int rows = attrTable->rowCount();
    if(currentRow >= 0) {
        delAttribute->setEnabled(true);
    } else {
        delAttribute->setEnabled(false);
    }

    if(currentRow > 0) {
        attrUp->setEnabled(true);
    } else {
        attrUp->setEnabled(false);
    }
    if((currentRow >= 0) && (rows > 0) && (currentRow < (rows - 1)))   {
        attrDown->setEnabled(true);
    } else {
        attrDown->setEnabled(false);
    }
}

void EditElement::on_textDel_clicked()
{
    int currentRow = elementTable->currentRow();
    if(currentRow >= 0) {
        if(isMixedContent) {
            QTableWidgetItem *item = elementTable->item(currentRow, 0);
            if(! isElementText(item)) {
                return ;
            }
        }
        elementTable->removeRow(currentRow);
    } else {
        Utils::error(this, tr("No text node selected"));
    }
}

void EditElement::on_textAdd_clicked()
{
    int currentRow = elementTable->currentRow();
    int newRow = getNextRow(currentRow);
    newRow = appendTextNodeInTable(elementTable, true, newRow, false, "", NULL);
    setUpdatedElement(newRow);
}

int EditElement::appendTextNodeInTable(QTableWidget *table, const bool isEditable, const int desiredRow, const bool isCDATA, const QString &text, void *userData)
{
    int row = desiredRow;
    if(row >= 0) {
        table->insertRow(row);
    } else {
        row = table->rowCount();
        table->setRowCount(row + 1);
    }
    QTableWidgetItem *itemMod = new QTableWidgetItem("");
    QTableWidgetItem *itemCDATA = new QTableWidgetItem();
    itemCDATA->setCheckState(isCDATA ? Qt::Checked : Qt::Unchecked);
    itemCDATA->setFlags(itemCDATA->flags() & (~Qt::ItemIsEditable));
    itemCDATA->setData(Qt::UserRole, qVariantFromValue((void*)userData));
    itemMod->setFlags(itemMod->flags()& ~(Qt::ItemIsEnabled | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable));
    itemMod->setData(Qt::UserRole, qVariantFromValue((void*)userData));
    if(!isEditable) {
        itemCDATA->setFlags(itemCDATA->flags()& ~(Qt::ItemIsEnabled | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable));
        itemCDATA->setBackgroundColor(QColor::fromRgb(0xC0, 0xC0, 0xC0));
    }

    QTableWidgetItem *itemText = new QTableWidgetItem(text);
    itemText->setFlags(itemText->flags() & (~Qt::ItemIsEditable));
    table->setItem(row, T_COLUMN_CDATA, itemCDATA);
    table->setItem(row, T_COLUMN_TEXT, itemText);
    table->setItem(row, T_COLUMN_MOD, itemMod);
    itemText->setData(Qt::UserRole, qVariantFromValue((void*)userData));
    if(!isEditable) {
        itemText->setFlags(itemCDATA->flags()& ~(Qt::ItemIsEnabled | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable));
        itemText->setBackgroundColor(QColor::fromRgb(0xC0, 0xC0, 0xC0));
    }
    return row ;
}

int EditElement::appendAttrNodeInTable(QTableWidget *table, const int desiredRow, const QString &name, const QString &value)
{
    int row = desiredRow;
    if(row >= 0) {
        table->insertRow(row);
    } else {
        row = table->rowCount();
        table->setRowCount(row + 1);
    }
    QTableWidgetItem *itemName = new QTableWidgetItem(name);
    QTableWidgetItem *itemValue = new QTableWidgetItem(value);
    QTableWidgetItem *itemMod = new QTableWidgetItem("");
    itemMod->setFlags(itemMod->flags()& ~(Qt::ItemIsEnabled | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable));
    table->setItem(row, A_COLUMN_NAME, itemName);
    table->setItem(row, A_COLUMN_TEXT, itemValue);
    table->setItem(row, A_COLUMN_MOD, itemMod);
    return row ;
}

void EditElement::on_elementTable_cellClicked(int row, int column)
{
    QTableWidgetItem *itemText = elementTable->itemAt(row, column);
    if(NULL != itemText) {
        if(isMixedContent) {
            DomItem * element = getUserData(itemText);
            if(NULL != element) {
                if(element->getType() == DomItem::ET_TEXT) {
                    on_textEdit_clicked();
                }
            }
        } else {
            on_textEdit_clicked();
        }
    }
}

void EditElement::on_attrUp_clicked()
{
    moveUp(attrTable);
}

void EditElement::on_attrDown_clicked()
{
    moveDown(attrTable);
}


void EditElement::on_textUp_clicked()
{
    moveUp(elementTable);
}

void EditElement::on_textDown_clicked()
{
    moveDown(elementTable);
}


void EditElement::swapRow2(QTableWidget *table, const int rowStart, const int rowEnd)
{
    QTableWidgetItem *i1 = table->takeItem(rowStart, 0);
    QTableWidgetItem *i2 = table->takeItem(rowStart, 1);
    QTableWidgetItem *i3 = table->takeItem(rowStart, 2);
    table->setItem(rowStart, 0, table->takeItem(rowEnd, 0));
    table->setItem(rowStart, 1, table->takeItem(rowEnd, 1));
    table->setItem(rowStart, 2, table->takeItem(rowEnd, 2));
    table->setItem(rowEnd, 0, i1);
    table->setItem(rowEnd, 1, i2);
    table->setItem(rowEnd, 2, i3);
}

void EditElement::moveDown(QTableWidget *table)
{
    int currentRow = table->currentRow();
    int rows = table->rowCount();
    if((currentRow >= 0) && (rows > 0) && (currentRow < (rows - 1)))   {
        QTableWidgetItem *currentItem = table->currentItem();
        swapRow2(table, currentRow, currentRow + 1);
        table->setCurrentCell(currentRow + 1, T_COLUMN_CDATA);
        table->setCurrentItem(currentItem);
        setUpdatedElement(currentRow + 1);
    }
}

void EditElement::moveUp(QTableWidget *table)
{
    int currentRow = table->currentRow();
    if(currentRow >= 0) {
        QTableWidgetItem *currentItem = table->currentItem();
        swapRow2(table, currentRow, currentRow - 1);
        table->setCurrentCell(currentRow - 1, T_COLUMN_CDATA);
        table->setCurrentItem(currentItem);
        setUpdatedElement(currentRow - 1);
    }
}

int EditElement::getNextRow(const int currentRow)
{
    if(currentRow < 0) {
        return -1 ;
    }
    return currentRow + 1;
}

DomItem * EditElement::getUserData(QTableWidgetItem *item)
{
    QVariant data = item->data(Qt::UserRole);
    DomItem *pElement = (DomItem *)data.value<void*>();
    return pElement ;
}

bool EditElement::isElementText(QTableWidgetItem *item)
{
    if(NULL != item) {
        DomItem * element = getUserData(item);
        if(NULL != element) {
            if(element->getType() == DomItem::ET_TEXT) {
                return true ;
            }
        } else {
            return true ;
        }
    }
    return false;
}

void EditElement::sendSelect(const int row)
{
    this->elementTable->setCurrentCell(row, 1/*, QItemSelectionModel::Select*/);
}

void EditElement::sendDeleteCommand()
{
    on_textDel_clicked();
}

void EditElement::sendModifyCommand(const QString &newData)
{
    int currentRow = elementTable->currentRow();
    if(currentRow >= 0) {
        elementTable->item(currentRow, T_COLUMN_TEXT)->setText(newData);
        elementTable->resizeRowToContents(currentRow);
    }
}

void EditElement::sendAddCommand(const QString &newData)
{
    int currentRow = elementTable->currentRow();
    appendTextNodeInTable(elementTable, true, getNextRow(currentRow), false, newData, NULL);
}

void EditElement::sendMoveUpCommand()
{
    on_textUp_clicked();
}

void EditElement::sendMoveDownCommand()
{
    on_textDown_clicked();
}

void EditElement::setAviableAttrbutes(QTableWidget *table)
{
    switch(target->getNodeType()) {
    case DomItem::ICD_HEADER: {
        int row = 0;
        int totalAttributeNum = 5;
        table->setRowCount(totalAttributeNum - target->getAttributesList().count());
        if(!target->hasAttrOfName("id")) {
            table->setItem(row++, 0, new QTableWidgetItem("id"));
        }
        if(!target->hasAttrOfName("version")) {
            table->setItem(row++, 0, new QTableWidgetItem("version"));
        }
        if(!target->hasAttrOfName("revision")) {
            table->setItem(row++, 0, new QTableWidgetItem("revision"));
        }
        if(!target->hasAttrOfName("toolID")) {
            table->setItem(row++, 0, new QTableWidgetItem("toolID"));
        }
        if(!target->hasAttrOfName("nameStructure")) {
            table->setItem(row++, 0, new QTableWidgetItem("nameStructure"));
        }
        break;
    }
    case DomItem::ICD_HITEM:{
        int row = 0;
        int totalAttributeNum = 6;
        table->setRowCount(totalAttributeNum - target->getAttributesList().count());
        if(!target->hasAttrOfName("version")) {
            table->setItem(row++, 0, new QTableWidgetItem("version"));
        }
        if(!target->hasAttrOfName("revision")) {
            table->setItem(row++, 0, new QTableWidgetItem("revision"));
        }
        if(!target->hasAttrOfName("when")) {
            table->setItem(row++, 0, new QTableWidgetItem("when"));
        }
        if(!target->hasAttrOfName("who")) {
            table->setItem(row++, 0, new QTableWidgetItem("who"));
        }
        if(!target->hasAttrOfName("what")) {
            table->setItem(row++, 0, new QTableWidgetItem("what"));
        }
        if(!target->hasAttrOfName("why")) {
            table->setItem(row++, 0, new QTableWidgetItem("why"));
        }
        break;
    }
    case DomItem::ICD_COMMUNICATION: {
        int row = 0;
        int totalAttributeNum = 1;
        table->setRowCount(totalAttributeNum - target->getAttributesList().count());
        if(!target->hasAttrOfName("desc")) {
            table->setItem(row++, 0, new QTableWidgetItem("desc"));
        }
        break;
    }
    case DomItem::ICD_SUBNETWORK: {
        int row = 0;
        int totalAttributeNum = 3;
        table->setRowCount(totalAttributeNum - target->getAttributesList().count());
        if(!target->hasAttrOfName("name")) {
            table->setItem(row++, 0, new QTableWidgetItem("name"));
        }
        if(!target->hasAttrOfName("type")) {
            table->setItem(row++, 0, new QTableWidgetItem("type"));
        }
        if(!target->hasAttrOfName("desc")) {
            table->setItem(row++, 0, new QTableWidgetItem("desc"));
        }
        break;
    }
    case DomItem::ICD_BITRATE:
    case DomItem::ICD_MINTIME:
    case DomItem::ICD_MAXTIME: {
        int row = 0;
        int totalAttributeNum = 2;
        table->setRowCount(totalAttributeNum - target->getAttributesList().count());
        if(!target->hasAttrOfName("unit")) {
            table->setItem(row++, 0, new QTableWidgetItem("unit"));
        }
        if(!target->hasAttrOfName("multiplier")) {
            table->setItem(row++, 0, new QTableWidgetItem("multiplier"));
        }
        break;
    }
    case DomItem::ICD_CONNECTEDAP: {
        int row = 0;
        int totalAttributeNum = 3;
        table->setRowCount(totalAttributeNum - target->getAttributesList().count());
        if(!target->hasAttrOfName("iedName")) {
            table->setItem(row++, 0, new QTableWidgetItem("iedName"));
        }
        if(!target->hasAttrOfName("apName")) {
            table->setItem(row++, 0, new QTableWidgetItem("apName"));
        }
        if(!target->hasAttrOfName("desc")) {
            table->setItem(row++, 0, new QTableWidgetItem("desc"));
        }
        break;
    }
    case DomItem::ICD_GSE:
    case DomItem::ICD_SMV: {
        int row = 0;
        int totalAttributeNum = 3;
        table->setRowCount(totalAttributeNum - target->getAttributesList().count());
        if(!target->hasAttrOfName("ldInst")) {
            table->setItem(row++, 0, new QTableWidgetItem("ldInst"));
        }
        if(!target->hasAttrOfName("cbName")) {
            table->setItem(row++, 0, new QTableWidgetItem("cbName"));
        }
        if(!target->hasAttrOfName("desc")) {
            table->setItem(row++, 0, new QTableWidgetItem("desc"));
        }
        break;
    }
    case DomItem::ICD_PHYSCONN: {
        int row = 0;
        int totalAttributeNum = 2;
        table->setRowCount(totalAttributeNum - target->getAttributesList().count());
        if(!target->hasAttrOfName("type")) {
            table->setItem(row++, 0, new QTableWidgetItem("type"));
        }
        if(!target->hasAttrOfName("desc")) {
            table->setItem(row++, 0, new QTableWidgetItem("desc"));
        }
        break;
    }
    case DomItem::ICD_IP: {
        int row = 0;
        int totalAttributeNum = 1;
        table->setRowCount(totalAttributeNum - target->getAttributesList().count());
        if(!target->hasAttrOfName("type")) {
            table->setItem(row++, 0, new QTableWidgetItem("type"));
        }
        break;
    }
    case DomItem::ICD_IED: {
        int row = 0;
        int totalAttributeNum = 5;
        table->setRowCount(totalAttributeNum - target->getAttributesList().count());
        if(!target->hasAttrOfName("name")) {
            table->setItem(row++, 0, new QTableWidgetItem("name"));
        }
        if(!target->hasAttrOfName("type")) {
            table->setItem(row++, 0, new QTableWidgetItem("type"));
        }
        if(!target->hasAttrOfName("desc")) {
            table->setItem(row++, 0, new QTableWidgetItem("desc"));
        }
        if(!target->hasAttrOfName("manufacturer")) {
            table->setItem(row++, 0, new QTableWidgetItem("manufacturer"));
        }
        if(!target->hasAttrOfName("configVersion")) {
            table->setItem(row++, 0, new QTableWidgetItem("configVersion"));
        }
        break;
    }
    case DomItem::ICD_ACCESSPOINT: {
        int row = 0;
        int totalAttributeNum = 4;
        table->setRowCount(totalAttributeNum - target->getAttributesList().count());
        if(!target->hasAttrOfName("name")) {
            table->setItem(row++, 0, new QTableWidgetItem("name"));
        }
        if(!target->hasAttrOfName("desc")) {
            table->setItem(row++, 0, new QTableWidgetItem("desc"));
        }
        if(!target->hasAttrOfName("router")) {
            table->setItem(row++, 0, new QTableWidgetItem("router"));
        }
        if(!target->hasAttrOfName("clock")) {
            table->setItem(row++, 0, new QTableWidgetItem("clock"));
        }
        break;
    }
    case DomItem::ICD_SERVER: {
        int row = 0;
        int totalAttributeNum = 2;
        table->setRowCount(totalAttributeNum - target->getAttributesList().count());
        if(!target->hasAttrOfName("timeout")) {
            table->setItem(row++, 0, new QTableWidgetItem("timeout"));
        }
        if(!target->hasAttrOfName("desc")) {
            table->setItem(row++, 0, new QTableWidgetItem("desc"));
        }
        break;
    }
    case DomItem::ICD_AUTHENTICATION: {
        int row = 0;
        int totalAttributeNum = 5;
        table->setRowCount(totalAttributeNum - target->getAttributesList().count());
        if(!target->hasAttrOfName("none")) {
            table->setItem(row++, 0, new QTableWidgetItem("none"));
        }
        if(!target->hasAttrOfName("password")) {
            table->setItem(row++, 0, new QTableWidgetItem("password"));
        }
        if(!target->hasAttrOfName("weak")) {
            table->setItem(row++, 0, new QTableWidgetItem("weak"));
        }
        if(!target->hasAttrOfName("strong")) {
            table->setItem(row++, 0, new QTableWidgetItem("strong"));
        }
        if(!target->hasAttrOfName("certificate")) {
            table->setItem(row++, 0, new QTableWidgetItem("certificate"));
        }
        break;
    }
    case DomItem::ICD_LDEVICE: {
        int row = 0;
        int totalAttributeNum = 2;
        table->setRowCount(totalAttributeNum - target->getAttributesList().count());
        if(!target->hasAttrOfName("inst")) {
            table->setItem(row++, 0, new QTableWidgetItem("inst"));
        }
        if(!target->hasAttrOfName("desc")) {
            table->setItem(row++, 0, new QTableWidgetItem("desc"));
        }
        break;
    }
    case DomItem::ICD_LN0: {
        int row = 0;
        int totalAttributeNum = 4;
        table->setRowCount(totalAttributeNum - target->getAttributesList().count());
        if(!target->hasAttrOfName("lnClass")) {
            table->setItem(row++, 0, new QTableWidgetItem("lnClass"));
        }
        if(!target->hasAttrOfName("lnType")) {
            table->setItem(row++, 0, new QTableWidgetItem("lnType"));
        }
        if(!target->hasAttrOfName("inst")) {
            table->setItem(row++, 0, new QTableWidgetItem("inst"));
        }
        if(!target->hasAttrOfName("desc")) {
            table->setItem(row++, 0, new QTableWidgetItem("desc"));
        }
        break;
    }
    case DomItem::ICD_LN: {
        int row = 0;
        int totalAttributeNum = 5;
        table->setRowCount(totalAttributeNum - target->getAttributesList().count());
        if(!target->hasAttrOfName("prefix")) {
            table->setItem(row++, 0, new QTableWidgetItem("prefix"));
        }
        if(!target->hasAttrOfName("lnClass")) {
            table->setItem(row++, 0, new QTableWidgetItem("lnClass"));
        }
        if(!target->hasAttrOfName("lnType")) {
            table->setItem(row++, 0, new QTableWidgetItem("lnType"));
        }
        if(!target->hasAttrOfName("inst")) {
            table->setItem(row++, 0, new QTableWidgetItem("inst"));
        }
        if(!target->hasAttrOfName("desc")) {
            table->setItem(row++, 0, new QTableWidgetItem("desc"));
        }
        break;
    }
    case DomItem::ICD_DOI: {
        int row = 0;
        int totalAttributeNum = 4;
        table->setRowCount(totalAttributeNum - target->getAttributesList().count());
        if(!target->hasAttrOfName("name")) {
            table->setItem(row++, 0, new QTableWidgetItem("name"));
        }
        if(!target->hasAttrOfName("desc")) {
            table->setItem(row++, 0, new QTableWidgetItem("desc"));
        }
        if(!target->hasAttrOfName("ix")) {
            table->setItem(row++, 0, new QTableWidgetItem("ix"));
        }
        if(!target->hasAttrOfName("accessControl")) {
            table->setItem(row++, 0, new QTableWidgetItem("accessControl"));
        }
        break;
    }
    case DomItem::ICD_DAI: {
        int row = 0;
        int totalAttributeNum = 5;
        table->setRowCount(totalAttributeNum - target->getAttributesList().count());
        if(!target->hasAttrOfName("name")) {
            table->setItem(row++, 0, new QTableWidgetItem("name"));
        }
        if(!target->hasAttrOfName("desc")) {
            table->setItem(row++, 0, new QTableWidgetItem("desc"));
        }
        if(!target->hasAttrOfName("sAddr")) {
            table->setItem(row++, 0, new QTableWidgetItem("sAddr"));
        }
        if(!target->hasAttrOfName("valKind")) {
            table->setItem(row++, 0, new QTableWidgetItem("valKind"));
        }
        if(!target->hasAttrOfName("ix")) {
            table->setItem(row++, 0, new QTableWidgetItem("ix"));
        }
        break;
    }
    case DomItem::ICD_SDI: {
        int row = 0;
        int totalAttributeNum = 3;
        table->setRowCount(totalAttributeNum - target->getAttributesList().count());

        if(!target->hasAttrOfName("name")) {
            table->setItem(row++, 0, new QTableWidgetItem("name"));
        }
        if(!target->hasAttrOfName("desc")) {
            table->setItem(row++, 0, new QTableWidgetItem("desc"));
        }
        if(!target->hasAttrOfName("ix")) {
            table->setItem(row++, 0, new QTableWidgetItem("ix"));
        }
        break;
    }
    case DomItem::ICD_DATASET: {
        int row = 0;
        int totalAttributeNum = 2;
        table->setRowCount(totalAttributeNum - target->getAttributesList().count());
        if(!target->hasAttrOfName("name")) {
            table->setItem(row++, 0, new QTableWidgetItem("name"));
        }
        if(!target->hasAttrOfName("desc")) {
            table->setItem(row++, 0, new QTableWidgetItem("desc"));
        }
        break;
    }
    case DomItem::ICD_FCDA: {
        int row = 0;
        int totalAttributeNum = 7;
        table->setRowCount(totalAttributeNum - target->getAttributesList().count());
        if(!target->hasAttrOfName("ldInst")) {
            table->setItem(row++, 0, new QTableWidgetItem("ldInst"));
        }
        if(!target->hasAttrOfName("prefix")) {
            table->setItem(row++, 0, new QTableWidgetItem("prefix"));
        }
        if(!target->hasAttrOfName("lnClass")) {
            table->setItem(row++, 0, new QTableWidgetItem("lnClass"));
        }
        if(!target->hasAttrOfName("lnInst")) {
            table->setItem(row++, 0, new QTableWidgetItem("lnInst"));
        }
        if(!target->hasAttrOfName("doName")) {
            table->setItem(row++, 0, new QTableWidgetItem("doName"));
        }
        if(!target->hasAttrOfName("daName")) {
            table->setItem(row++, 0, new QTableWidgetItem("daName"));
        }
        if(!target->hasAttrOfName("fc")) {
            table->setItem(row++, 0, new QTableWidgetItem("fc"));
        }
        break;
    }
    case DomItem::ICD_REPORTCONTROL: {
        int row = 0;
        int totalAttributeNum = 8;
        table->setRowCount(totalAttributeNum - target->getAttributesList().count());
        if(!target->hasAttrOfName("name")) {
            table->setItem(row++, 0, new QTableWidgetItem("name"));
        }
        if(!target->hasAttrOfName("desc")) {
            table->setItem(row++, 0, new QTableWidgetItem("desc"));
        }
        if(!target->hasAttrOfName("datSet")) {
            table->setItem(row++, 0, new QTableWidgetItem("datSet"));
        }
        if(!target->hasAttrOfName("intgPd")) {
            table->setItem(row++, 0, new QTableWidgetItem("intgPd"));
        }
        if(!target->hasAttrOfName("rptID")) {
            table->setItem(row++, 0, new QTableWidgetItem("rptID"));
        }
        if(!target->hasAttrOfName("confRev")) {
            table->setItem(row++, 0, new QTableWidgetItem("confRev"));
        }
        if(!target->hasAttrOfName("Buffered")) {
            table->setItem(row++, 0, new QTableWidgetItem("Buffered"));
        }
        if(!target->hasAttrOfName("bufTime")) {
            table->setItem(row++, 0, new QTableWidgetItem("bufTime"));
        }
        break;
    }
    case DomItem::ICD_TRGOPS: {
        int row = 0;
        int totalAttributeNum = 4;
        table->setRowCount(totalAttributeNum - target->getAttributesList().count());
        if(!target->hasAttrOfName("dchg")) {
            table->setItem(row++, 0, new QTableWidgetItem("dchg"));
        }
        if(!target->hasAttrOfName("qchg")) {
            table->setItem(row++, 0, new QTableWidgetItem("qchg"));
        }
        if(!target->hasAttrOfName("dupd")) {
            table->setItem(row++, 0, new QTableWidgetItem("dupd"));
        }
        if(!target->hasAttrOfName("period")) {
            table->setItem(row++, 0, new QTableWidgetItem("period"));
        }
        break;
    }
    case DomItem::ICD_OPTFIELDS: {
        int row = 0;
        int totalAttributeNum = 9;
        table->setRowCount(totalAttributeNum - target->getAttributesList().count());
        if(!target->hasAttrOfName("seqNum")) {
            table->setItem(row++, 0, new QTableWidgetItem("seqNum"));
        }
        if(!target->hasAttrOfName("timeStamp")) {
            table->setItem(row++, 0, new QTableWidgetItem("timeStamp"));
        }
        if(!target->hasAttrOfName("dataSet")) {
            table->setItem(row++, 0, new QTableWidgetItem("dataSet"));
        }
        if(!target->hasAttrOfName("reasonCode")) {
            table->setItem(row++, 0, new QTableWidgetItem("reasonCode"));
        }
        if(!target->hasAttrOfName("dataRef")) {
            table->setItem(row++, 0, new QTableWidgetItem("dataRef"));
        }
        if(!target->hasAttrOfName("bufOvfl")) {
            table->setItem(row++, 0, new QTableWidgetItem("bufOvfl"));
        }
        if(!target->hasAttrOfName("entryID")) {
            table->setItem(row++, 0, new QTableWidgetItem("entryID"));
        }
        if(!target->hasAttrOfName("configRef")) {
            table->setItem(row++, 0, new QTableWidgetItem("configRef"));
        }
        if(!target->hasAttrOfName("segmentation")) {
            table->setItem(row++, 0, new QTableWidgetItem("segmentation"));
        }
        break;
    }
    case DomItem::ICD_RPTENABLED: {
        int row = 0;
        int totalAttributeNum = 2;
        table->setRowCount(totalAttributeNum - target->getAttributesList().count());
        if(!target->hasAttrOfName("desc")) {
            table->setItem(row++, 0, new QTableWidgetItem("desc"));
        }
        if(!target->hasAttrOfName("max")) {
            table->setItem(row++, 0, new QTableWidgetItem("max"));
        }
        break;
    }
    case DomItem::ICD_CLIENTLN: {
        int row = 0;
        int totalAttributeNum = 4;
        table->setRowCount(totalAttributeNum - target->getAttributesList().count());
        if(!target->hasAttrOfName("iedName")) {
            table->setItem(row++, 0, new QTableWidgetItem("iedName"));
        }
        if(!target->hasAttrOfName("ldInst")) {
            table->setItem(row++, 0, new QTableWidgetItem("ldInst"));
        }
        if(!target->hasAttrOfName("prefix")) {
            table->setItem(row++, 0, new QTableWidgetItem("prefix"));
        }
        if(!target->hasAttrOfName("lnClass")) {
            table->setItem(row++, 0, new QTableWidgetItem("lnClass"));
        }
        if(!target->hasAttrOfName("lnInst")) {
            table->setItem(row++, 0, new QTableWidgetItem("lnInst"));
        }
        break;
    }
    case DomItem::ICD_LOGCONTROL: {
        int row = 0;
        int totalAttributeNum = 7;
        table->setRowCount(totalAttributeNum - target->getAttributesList().count());
        if(!target->hasAttrOfName("name")) {
            table->setItem(row++, 0, new QTableWidgetItem("name"));
        }
        if(!target->hasAttrOfName("desc")) {
            table->setItem(row++, 0, new QTableWidgetItem("desc"));
        }
        if(!target->hasAttrOfName("datSet")) {
            table->setItem(row++, 0, new QTableWidgetItem("datSet"));
        }
        if(!target->hasAttrOfName("intgPd")) {
            table->setItem(row++, 0, new QTableWidgetItem("intgPd"));
        }
        if(!target->hasAttrOfName("logName")) {
            table->setItem(row++, 0, new QTableWidgetItem("logName"));
        }
        if(!target->hasAttrOfName("logEna")) {
            table->setItem(row++, 0, new QTableWidgetItem("logEna"));
        }
        if(!target->hasAttrOfName("reasonCode")) {
            table->setItem(row++, 0, new QTableWidgetItem("reasonCode"));
        }
        break;
    }
    case DomItem::ICD_GSECONTROL: {
        int row = 0;
        int totalAttributeNum = 6;
        table->setRowCount(totalAttributeNum - target->getAttributesList().count());
        if(!target->hasAttrOfName("name")) {
            table->setItem(row++, 0, new QTableWidgetItem("name"));
        }
        if(!target->hasAttrOfName("desc")) {
            table->setItem(row++, 0, new QTableWidgetItem("desc"));
        }
        if(!target->hasAttrOfName("datSet")) {
            table->setItem(row++, 0, new QTableWidgetItem("datSet"));
        }
        if(!target->hasAttrOfName("confRev")) {
            table->setItem(row++, 0, new QTableWidgetItem("confRev"));
        }
        if(!target->hasAttrOfName("type")) {
            table->setItem(row++, 0, new QTableWidgetItem("type"));
        }
        if(!target->hasAttrOfName("appID")) {
            table->setItem(row++, 0, new QTableWidgetItem("appID"));
        }
        break;
    }
    case DomItem::ICD_SVCONTROL: {
        int row = 0;
        int totalAttributeNum = 8;
        table->setRowCount(totalAttributeNum - target->getAttributesList().count());
        if(!target->hasAttrOfName("name")) {
            table->setItem(row++, 0, new QTableWidgetItem("name"));
        }
        if(!target->hasAttrOfName("desc")) {
            table->setItem(row++, 0, new QTableWidgetItem("desc"));
        }
        if(!target->hasAttrOfName("datSet")) {
            table->setItem(row++, 0, new QTableWidgetItem("datSet"));
        }
        if(!target->hasAttrOfName("confRev")) {
            table->setItem(row++, 0, new QTableWidgetItem("confRev"));
        }
        if(!target->hasAttrOfName("smvID")) {
            table->setItem(row++, 0, new QTableWidgetItem("smvID"));
        }
        if(!target->hasAttrOfName("multicast")) {
            table->setItem(row++, 0, new QTableWidgetItem("multicast"));
        }
        if(!target->hasAttrOfName("smpRate")) {
            table->setItem(row++, 0, new QTableWidgetItem("smpRate"));
        }
        if(!target->hasAttrOfName("nofASDU")) {
            table->setItem(row++, 0, new QTableWidgetItem("nofASDU"));
        }
        break;
    }
    case DomItem::ICD_SMVOPTS: {
        int row = 0;
        int totalAttributeNum = 5;
        table->setRowCount(totalAttributeNum - target->getAttributesList().count());
        if(!target->hasAttrOfName("refreshTime")) {
            table->setItem(row++, 0, new QTableWidgetItem("refreshTime"));
        }
        if(!target->hasAttrOfName("samplesSynchronized")) {
            table->setItem(row++, 0, new QTableWidgetItem("samplesSynchronized"));
        }
        if(!target->hasAttrOfName("sampleRate")) {
            table->setItem(row++, 0, new QTableWidgetItem("sampleRate"));
        }
        if(!target->hasAttrOfName("security")) {
            table->setItem(row++, 0, new QTableWidgetItem("security"));
        }
        if(!target->hasAttrOfName("dataRef")) {
            table->setItem(row++, 0, new QTableWidgetItem("dataRef"));
        }
        break;
    }
    case DomItem::ICD_SETTINGCONTROL: {
        int row = 0;
        int totalAttributeNum = 3;
        table->setRowCount(totalAttributeNum - target->getAttributesList().count());
        if(!target->hasAttrOfName("desc")) {
            table->setItem(row++, 0, new QTableWidgetItem("desc"));
        }
        if(!target->hasAttrOfName("numOfSGs")) {
            table->setItem(row++, 0, new QTableWidgetItem("numOfSGs"));
        }
        if(!target->hasAttrOfName("actSG")) {
            table->setItem(row++, 0, new QTableWidgetItem("actSG"));
        }
        break;
    }
    case DomItem::ICD_EXTREFS: {
        int row = 0;
        int totalAttributeNum = 8;
        table->setRowCount(totalAttributeNum - target->getAttributesList().count());
        if(!target->hasAttrOfName("iedName")) {
            table->setItem(row++, 0, new QTableWidgetItem("iedName"));
        }
        if(!target->hasAttrOfName("ldInst")) {
            table->setItem(row++, 0, new QTableWidgetItem("ldInst"));
        }
        if(!target->hasAttrOfName("prefix")) {
            table->setItem(row++, 0, new QTableWidgetItem("prefix"));
        }
        if(!target->hasAttrOfName("lnClass")) {
            table->setItem(row++, 0, new QTableWidgetItem("lnClass"));
        }
        if(!target->hasAttrOfName("lnInst")) {
            table->setItem(row++, 0, new QTableWidgetItem("lnInst"));
        }
        if(!target->hasAttrOfName("doName")) {
            table->setItem(row++, 0, new QTableWidgetItem("doName"));
        }
        if(!target->hasAttrOfName("daName")) {
            table->setItem(row++, 0, new QTableWidgetItem("daName"));
        }
        if(!target->hasAttrOfName("intAddr")) {
            table->setItem(row++, 0, new QTableWidgetItem("intAddr"));
        }
        break;
    }
    case DomItem::ICD_ASSOCIATION: {
        int row = 0;
        int totalAttributeNum = 7;
        table->setRowCount(totalAttributeNum - target->getAttributesList().count());
        if(!target->hasAttrOfName("kind")) {
            table->setItem(row++, 0, new QTableWidgetItem("kind"));
        }
        if(!target->hasAttrOfName("associationID")) {
            table->setItem(row++, 0, new QTableWidgetItem("associationID"));
        }
        if(!target->hasAttrOfName("iedName")) {
            table->setItem(row++, 0, new QTableWidgetItem("iedName"));
        }
        if(!target->hasAttrOfName("ldInst")) {
            table->setItem(row++, 0, new QTableWidgetItem("ldInst"));
        }
        if(!target->hasAttrOfName("lnClass")) {
            table->setItem(row++, 0, new QTableWidgetItem("lnClass"));
        }
        if(!target->hasAttrOfName("prefix")) {
            table->setItem(row++, 0, new QTableWidgetItem("prefix"));
        }
        if(!target->hasAttrOfName("lnInst")) {
            table->setItem(row++, 0, new QTableWidgetItem("lnInst"));
        }
        break;
    }
    case DomItem::ICD_TEXT: {
        int row = 0;
        int totalAttributeNum = 1;
        table->setRowCount(totalAttributeNum - target->getAttributesList().count());
        if(!target->hasAttrOfName("source")) {
            table->setItem(row++, 0, new QTableWidgetItem("source"));
        }
        break;
    }
    case DomItem::ICD_PRIVATE: {
        int row = 0;
        int totalAttributeNum = 2;
        table->setRowCount(totalAttributeNum - target->getAttributesList().count());
        if(!target->hasAttrOfName("type")) {
            table->setItem(row++, 0, new QTableWidgetItem("type"));
        }
        if(!target->hasAttrOfName("source")) {
            table->setItem(row++, 0, new QTableWidgetItem("source"));
        }
        break;
    }
    default:
        break;
    }
}

void EditElement::on_noUseAttrTable_itemClicked(QTableWidgetItem *item)
{
    if(noUseAttrTable->rowCount() > 0)
        newAttribute->setEnabled(true);
    else
        newAttribute->setEnabled(false);
}
