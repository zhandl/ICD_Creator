#include "editattribute.h"

bool EditAttribute::attributeIsChanged = false;

EditAttribute::EditAttribute(QWidget *parent) :
    QDialog(parent)
{
    layout = new QGridLayout(this);
    layout->setObjectName(tr("layout"));

    treeGroupBox = new QGroupBox(this);
    treeGroupBox->setObjectName(tr("treeGroupBox"));
    treeGroupBox->setTitle(tr("Element"));

    QGridLayout *treeGroupBoxLayout = new QGridLayout();
    treeGroupBox->setLayout(treeGroupBoxLayout);

    attrTree = new QTreeWidget(treeGroupBox);
    attrTree->setObjectName(tr("attrTree"));

    treeGroupBoxLayout->addWidget(attrTree,0,0,1,1);

    buttonBox = new QDialogButtonBox(Qt::Horizontal, this);
    buttonBox->setObjectName(tr("buttonBox"));

//    applyButton = new QPushButton(tr("Apply"));
//    applyButton->setObjectName(tr("applyButton"));
//    okButton = new QPushButton(tr("OK"));
//    okButton->setObjectName(tr("okButton"));
//    cancelButton = new QPushButton(tr("cancel"));
//    cancelButton->setObjectName(tr("cancelButton"));

//    buttonBox->addButton(applyButton, QDialogButtonBox::ApplyRole);
//    buttonBox->addButton(okButton, QDialogButtonBox::AcceptRole);
//    buttonBox->addButton(cancelButton, QDialogButtonBox::RejectRole);

    buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);
    buttonBox->setCenterButtons(false);

    layout->addWidget(treeGroupBox, 0, 0, 1, 1);
    layout->addWidget(buttonBox, 1, 0, 1, 1);

    setLayout(layout);
    resize(600, 480);

    attrTree->setHeaderLabels(QStringList()<<tr("name")<<tr("value"));/*
    attrTree->header()->setResizeMode(QHeaderView::ResizeToContents);
    attrTree->header()->setResizeMode(QHeaderView::Interactive);*/
    attrTree->setColumnWidth(0, 200);
    attrTree->header()->setStretchLastSection(true);
//    QFile file("./qss/treeView.qss");
//    file.open(QFile::ReadOnly);
//    QTextStream fileText(&file);
//    QString styleSheet = fileText.readAll();
//    this->setStyleSheet(styleSheet);
//    file.close();

//    attrTree->setIndentation(0);
//    attrTree->setStyleSheet("QTreeWidget::item{border-top: 1px solid light-gray;border-left: 1px solid light-gray;border-right: 1px solid light-gray;border-bottom: 1px solid light-gray;}");

    target = NULL;
    attrTree->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    connect(attrTree, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showMenu(QPoint)));
    connect(attrTree, SIGNAL(itemChanged(QTreeWidgetItem*,int)), this, SLOT(attributeChanged(QTreeWidgetItem*, int)));
    QMetaObject::connectSlotsByName(this);
}

EditAttribute::~EditAttribute()
{

}

void EditAttribute::setTarget(DomItem *item)
{
    target = item;

    titleText = tr("Attributes for ");

    switch(target->getNodeType()) {
    case DomItem::ICD_IED:
        titleText += target->attributeValueOfName(tr("name"));
        break;
    default:
        break;
    }


    setWindowTitle(titleText);
    if(target == NULL)
        return;

//    QStringList topItemList = QStringList()<<target->tag()<<tr(" ");
    QString targetName = target->tag();
    QString targetValue = tr(" ");
    if(target->getTextChunksNumber() > 0) {
        targetValue = target->getTextChunks().at(0)->text;
    }

    QTreeWidgetItem *me = new QTreeWidgetItem(QStringList()<<targetName<<targetValue);
    me->setBackgroundColor(0, QColor(178, 178, 178));
    me->setBackgroundColor(1, QColor(178, 178, 178));
    attrTree->addTopLevelItem(me);
    foreach (Attribute *attr, target->attributes) {
        QTreeWidgetItem *temp = new QTreeWidgetItem(QStringList()<<attr->name<<attr->value);
        temp->setIcon(0, QIcon(":/nodeType/images/Attribute.png"));
        me->addChild(temp);
        temp->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled);

    }
    me->setExpanded(true);
}

//void EditAttribute::on_okButton_clicked()
//{
//    QDialog::accept();
//}

//void EditAttribute::on_cancelButton_clicked()
//{
//    QDialog::reject();
//}

//void EditAttribute::on_applyButton_clicked()
//{

//}

void EditAttribute::accept()
{
    if(!attributeIsChanged) {
        QDialog::accept();
        return ;
    }

    target->clearAttributes();

    QTreeWidgetItem *topItem = attrTree->topLevelItem(0);
    for(int i = 0; i < topItem->childCount(); i++) {
        QTreeWidgetItem *attrItem = topItem->child(i);
        target->addAttribute(attrItem->text(0), attrItem->text(1));
    }

    QDialog::accept();
}

void EditAttribute::showMenu(QPoint pos)
{
    QMenu contextMenu(this);

    QAction *deleteAttr = new QAction(tr("Del"), this);
    deleteAttr->setObjectName(tr("deleteAttr"));
    connect(deleteAttr, SIGNAL(triggered()), this, SLOT(deleteAttribute()));

    contextMenu.addAction(deleteAttr);

    contextMenu.exec(attrTree->mapToGlobal(pos));

}

void EditAttribute::attributeChanged(QTreeWidgetItem *item, int column)
{
    attributeIsChanged = true;
}

void EditAttribute::deleteAttribute()
{
    QTreeWidgetItem *currItem = attrTree->currentItem();
    attrTree->topLevelItem(0)->removeChild(currItem);
}
