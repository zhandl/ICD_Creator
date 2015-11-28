#include "alloweditemsinsert.h"
#include "xsdeditor/xschema.h"
#include "utils.h"

bool ChooseItemsBySchema(QWidget *parent, XElementContent *content, QList<XSchemaObject *> *result)
{
    AllowedItemsInsert dialog(content, result, parent);
    if(dialog.exec() == QDialog::Accepted) {
        return true;
    }
    return false;
}

AllowedItemsInsert::AllowedItemsInsert(XElementContent *content, QList<XSchemaObject*>*result, QWidget *parent) :
    QDialog(parent)
{
    Utils::TODO_NEXT_RELEASE("Gestione memoria su clear, unselect");
    Utils::TODO_NEXT_RELEASE("fare gestore di undo");

    _selection = result;
    _content = content;
    init();
    allowedItems->setColumnCount(2);

    foreach (XSingleElementContent *targetContent, content->allowedItems()) {
        addItem(targetContent, NULL);
    }
    allowedItems->expandAll();
    allowedItems->resizeColumnToContents(0);
    allowedItems->resizeColumnToContents(1);
    enableControls();
}

AllowedItemsInsert::~AllowedItemsInsert()
{

}

void AllowedItemsInsert::init()
{
    if (objectName().isEmpty())
        setObjectName(QString::fromUtf8("AllowedItemsInsert"));
    resize(766, 579);
    setSizeGripEnabled(false);
    setModal(true);
    verticalLayout = new QVBoxLayout(this);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    label = new QLabel(this);
    label->setObjectName(QString::fromUtf8("label"));

    verticalLayout->addWidget(label);

    allowedItems = new QTreeWidget(this);
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/tree/el_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
    QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
    __qtreewidgetitem->setIcon(0, icon);
    allowedItems->setHeaderItem(__qtreewidgetitem);
    allowedItems->setObjectName(QString::fromUtf8("allowedItems"));
    allowedItems->setAlternatingRowColors(true);

    verticalLayout->addWidget(allowedItems);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    undo = new QToolButton(this);
    undo->setObjectName(QString::fromUtf8("undo"));
    QIcon icon1;
    icon1.addFile(QString::fromUtf8(":/edit/undo"), QSize(), QIcon::Normal, QIcon::Off);
    undo->setIcon(icon1);

    horizontalLayout->addWidget(undo);

    redo = new QToolButton(this);
    redo->setObjectName(QString::fromUtf8("redo"));
    QIcon icon2;
    icon2.addFile(QString::fromUtf8(":/edit/redo"), QSize(), QIcon::Normal, QIcon::Off);
    redo->setIcon(icon2);

    horizontalLayout->addWidget(redo);

    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer);

    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

    horizontalLayout->addWidget(buttonBox);


    verticalLayout->addLayout(horizontalLayout);


    retranslateUi();
    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QMetaObject::connectSlotsByName(this);
}

void AllowedItemsInsert::retranslateUi()
{
    setWindowTitle(QApplication::translate("AllowedItemsInsert", "Allowed Elements", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("AllowedItemsInsert", "Choose elements to insert coherent with the schema", 0, QApplication::UnicodeUTF8));
    QTreeWidgetItem *___qtreewidgetitem = allowedItems->headerItem();
    ___qtreewidgetitem->setText(1, QApplication::translate("AllowedItemsInsert", "Description", 0, QApplication::UnicodeUTF8));
    ___qtreewidgetitem->setText(0, QApplication::translate("AllowedItemsInsert", "Elements", 0, QApplication::UnicodeUTF8));
    undo->setText(QApplication::translate("AllowedItemsInsert", "undo", 0, QApplication::UnicodeUTF8));
    redo->setText(QApplication::translate("AllowedItemsInsert", "redo", 0, QApplication::UnicodeUTF8));
}

void AllowedItemsInsert::addItem(XSingleElementContent *target, QTreeWidgetItem *parentItem)
{
    QTreeWidgetItem *uiItem = new QTreeWidgetItem();

    QString name = target->item()->name();
    if(name.isEmpty()) {
        name = target->item()->descriptionForProposal();
    }
    if(name.isEmpty()) {
        name = target->item()->description();
    }
    uiItem->setText(0, name);
    XSchemaAnnotation *annotation = target->item()->annotation();
    if(NULL != annotation) {
        uiItem->setText(1, annotation->text());
    }
    uiItem->setData(0, Qt::UserRole, qVariantFromValue((void*)target));
    uiItem->setCheckState(0, Qt::Unchecked);

    if(parentItem) {
        parentItem->addChild(uiItem);
    } else {
        allowedItems->addTopLevelItem(uiItem);
    }
    uiItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    foreach (XSingleElementContent *child, target->children()) {
        addItem(child, uiItem);
    }
}

void AllowedItemsInsert::unselectRecursive(QTreeWidgetItem *item)
{
    item->setCheckState(0, Qt::Unchecked);
    int childrenCount = item->childCount();
    for(int i = 0; i < childrenCount; i++) {
        QTreeWidgetItem *child = item->child(i);
        unselectRecursive(child);
    }
}

bool AllowedItemsInsert::isSameItem(QTreeWidgetItem *item, XSingleElementContent *reference)
{
    QVariant data = item->data(0, Qt::UserRole);
    XSingleElementContent *pObject = (XSingleElementContent*)data.value<void*>();
    if(pObject->id() == reference->id()) {
        return true;
    }
    return false;
}

void AllowedItemsInsert::on_allowedItems_itemClicked(QTreeWidgetItem *item, int column)
{
    QVariant data = item->data(0, Qt::UserRole);
    XSingleElementContent *pObject = (XSingleElementContent*)data.value<void*>();
    QTreeWidgetItem *parentItem = item->parent();
    if(NULL != parentItem) {
        QVariant dataParent = parentItem->data(0, Qt::UserRole);
        XSingleElementContent *pParent = (XSingleElementContent*)dataParent.value<void*>();
        if(pParent->isChoice() && (item->checkState(0) == Qt::Checked)) {
            int childrenCount = parentItem->childCount();
            for(int i = 0; i < childrenCount; i++) {
                QTreeWidgetItem *child = parentItem->child(i);
                if(!isSameItem(child, pObject)) {
                    unselectRecursive(child);
                }
            }
        }
    }
    saveState();
    enableControls();
}

void AllowedItemsInsert::saveState()
{

}

void AllowedItemsInsert::restoreState()
{

}

void AllowedItemsInsert::enableControls()
{
    undo->setVisible(false);
    redo->setVisible(false);
}

void AllowedItemsInsert::collectSelected(QTreeWidgetItem *parentItem)
{
    if(parentItem->checkState(0) == Qt::Checked) {
        QVariant data = parentItem->data(0, Qt::UserRole);
        XSingleElementContent *pObject = (XSingleElementContent*)data.value<void*>();
        if(pObject->isCollectable()) {
            _selection->append(pObject->item());
        }
    }
    int childCount = parentItem->childCount();
    for(int i = 0; i < childCount; i++) {
        QTreeWidgetItem *item = parentItem->child(i);
        collectSelected(item);
    }
}

void AllowedItemsInsert::accept()
{
    _selection->clear();
    int childCount = allowedItems->topLevelItemCount();
    for(int i = 0; i < childCount; i++) {
        QTreeWidgetItem *item = allowedItems->topLevelItem(i);
        collectSelected(item);
    }

    QDialog::accept();
}

void AllowedItemsInsert::on_undo_clicked()
{

}

void AllowedItemsInsert::on_redo_clicked()
{

}
