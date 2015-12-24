#include "icddatatypetemplatenew.h"
#include "datatypemodel.h"
#include "datatypeitem.h"
#include "newtemplatelnodemodel.h"
#include "modifylnodeid.h"

icdDataTypeTemplateNew::icdDataTypeTemplateNew(QWidget *parent) :
    QWizardPage(parent)
{
    setTitle(tr("Create DataType Template"));
    setSubTitle(tr("This page introduce user to create a new dataType template"));

    model = new DataTypeModel();
    selectedModel = new DataTypeModel();
    doc = new QDomDocument();
    init();
    createDoc(doc);

    DataTypeModel *newModel = new DataTypeModel(*doc, "");
    if(selectedModel != NULL) {
        delete selectedModel;
        selectedModel = NULL;
    }
    selectedModel = newModel;
//    foreach (DataTypeItem* item, selectedModel->getItems()) {
//        if(item->tag() == tr("DataTypeTemplates"))
//            selectedModel->setRootItem(item);
//    }

    connect(newTemplateLNodeTree, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(on_newTemplateLNodeTree_itemDoubleClicked(QTreeWidgetItem*, int)));
    connect(standardComboBox, SIGNAL(activated(int)), this, SLOT(selecteDataTypeStandard(int)));
    standardComboBox->setCurrentIndex(0);
    setStandardDLT860();
}

void icdDataTypeTemplateNew::init()
{
    newDataTypeGridLayout = new QGridLayout(this);
    newDataTypeGridLayout->setObjectName(tr("newDataTypeGridLayout"));

    standardComboBox = new QComboBox(this);
    standardComboBox->setObjectName(tr("standardComboBox"));
    standardComboBox->addItems(QStringList()<<tr("DL/T860.74-2006"));

    LNodeFilter = new QComboBox(this);
    LNodeFilter->setObjectName(tr("LNodeFilter"));

    LNodeTree = new QTreeWidget();
    LNodeTree->setObjectName(tr("LNodeTree"));
//    LNodeTree->setStyleSheet(tr("QTreeWidget::item:selected{background-color:rgba(255, 128, 128, 255)}"));
    LNodeTree->setSelectionMode(QAbstractItemView::MultiSelection);

    LNodeDescText = new QTextBrowser();
    LNodeDescText->setObjectName(tr("LNodeDescText"));

    newTemplateLNodeTree = new QTreeWidget();
    newTemplateLNodeTree->setObjectName(tr("newTemplateLNodeTree"));

    buttonGroupBox = new QWidget();
    buttonGroupBox->setObjectName(tr("buttonGroupBox"));
    buttonGroupBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);

    buttonVLayout = new QVBoxLayout(buttonGroupBox);

    addLNode = new QPushButton(buttonGroupBox);
    addLNode->setObjectName(tr("addLNode"));
    addLNode->setText(">");
    delLNode = new QPushButton(buttonGroupBox);
    delLNode->setObjectName(tr("delLNode"));
    delLNode->setText("<");
    addAll = new QPushButton(buttonGroupBox);
    addAll->setObjectName(tr("addAll"));
    addAll->setText(">>");
    delAll = new QPushButton(buttonGroupBox);
    delAll->setObjectName(tr("delAll"));
    delAll->setText("<<");

    buttonVLayout->addWidget(addLNode);
    buttonVLayout->addWidget(delLNode);
    buttonVLayout->addWidget(addAll);
    buttonVLayout->addWidget(delAll);


    hSplitter = new QSplitter();
    hSplitter->setObjectName(tr("hSplitter"));

    vSplitter = new QSplitter(Qt::Vertical);
    vSplitter->setObjectName(tr("vSplitter"));

    hSplitter->addWidget(vSplitter);
    hSplitter->addWidget(buttonGroupBox);
    hSplitter->addWidget(newTemplateLNodeTree);

    vSplitter->addWidget(LNodeTree);
    vSplitter->addWidget(LNodeDescText);

    newDataTypeGridLayout->addWidget(standardComboBox, 0, 0, 1, 1);
    newDataTypeGridLayout->addWidget(LNodeFilter, 0, 2, 1, 1);
    newDataTypeGridLayout->addWidget(hSplitter, 1, 0, 1, 3);

    checkItems = new QAction(this);
    checkItems->setText(tr("selectItems"));
    checkItems->setObjectName(tr("checkItems"));
    uncheckItems = new QAction(this);
    uncheckItems->setText(tr("unselectItems"));
    uncheckItems->setObjectName(tr("uncheckItems"));

    LNodeTree->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(LNodeTree, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(treeContextMenu(QPoint)));
    connect(LNodeTree, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(showDesc(QTreeWidgetItem*, int)));
//    connect(LNodeTree, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(setLNodeSelected(QTreeWidgetItem*, int)));
    connect(LNodeTree, SIGNAL(itemChanged(QTreeWidgetItem*,int)), this, SLOT(calcCheckState(QTreeWidgetItem*, int)));
    connect(checkItems, SIGNAL(triggered()), this, SLOT(checkSelecteItems()));
    connect(uncheckItems, SIGNAL(triggered()), this, SLOT(uncheckSelecteItems()));

    connect(addLNode, SIGNAL(clicked()), this, SLOT(on_addLNode_clicked()));
    connect(delLNode, SIGNAL(clicked()), this, SLOT(on_delLNode_clicked()));
}

void icdDataTypeTemplateNew::selecteDataTypeStandard(int index)
{
    switch(index) {
    default:
        return;
    case 0:
        setStandardDLT860();
        return;
    }
}

void icdDataTypeTemplateNew::setStandardDLT860()
{
    DataTypeModel *newModel;
    QString filePath = tr("dlt860-74.xml");
    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly)) {
        QDomDocument document;
        if(document.setContent(&file)) {

            newModel = new DataTypeModel(document, filePath);
            if(model != NULL) {
                delete model;
                model = NULL;
            }
            model = newModel;
            LNodeTree->setUpdatesEnabled(false);
            model->setTreeValue(LNodeTree);
            LNodeTree->setUpdatesEnabled(true);
            LNodeTree->expandAll();
        }
    }
}


void icdDataTypeTemplateNew::treeContextMenu(const QPoint &pos)
{
    QMenu *contextMenu = new QMenu(this);
    contextMenu->addAction(checkItems);
    contextMenu->addAction(uncheckItems);

    if(LNodeTree->itemAt(pos)->isSelected())
        contextMenu->exec(LNodeTree->mapToGlobal(pos));
}

void icdDataTypeTemplateNew::checkSelecteItems()
{
    QList<QTreeWidgetItem*> itemList = LNodeTree->selectedItems();
    for(int i = 0; i < itemList.count(); i++) {
        DataTypeItem *item = new DataTypeItem(model);
        item = DataTypeItem::fromItemData(itemList.at(i));
        if(item->tag() == tr("DO"))
            item->setChecked();
    }
    LNodeTree->clearSelection();
}

void icdDataTypeTemplateNew::uncheckSelecteItems()
{
    QList<QTreeWidgetItem*> itemList = LNodeTree->selectedItems();
    for(int i = 0; i < itemList.count(); i++) {
        DataTypeItem *item = new DataTypeItem(model);
        item = DataTypeItem::fromItemData(itemList.at(i));
        if(item->tag() == tr("DO"))
            item->setUnchecked();
    }
    LNodeTree->clearSelection();
}

void icdDataTypeTemplateNew::setLNodeSelected(QTreeWidgetItem* item, int column)
{
    DataTypeItem *dataItem = new DataTypeItem(model);
    dataItem = DataTypeItem::fromItemData(item);
    if(dataItem->tag() != tr("LNodeType")) {
        return ;
    } else if(dataItem->isSelected) {
        LNodeTree->clearSelection();
        dataItem->setUnchecked();
    } else {
        LNodeTree->clearSelection();
        LNodeTree->setItemSelected(item, true);
        dataItem->setChecked();
    }
}

void icdDataTypeTemplateNew::showDesc(QTreeWidgetItem *item, int column)
{
    DataTypeItem *dataItem = DataTypeItem::fromItemData(item);
    LNodeDescText->setText(dataItem->attributeValueOfName("desc"));
}

void icdDataTypeTemplateNew::createDoc(QDomDocument *document)
{
//    QDomProcessingInstruction instruction;
//    instruction = document->createProcessingInstruction("xml", "version=\"1.0\" encoding = \"UTF_8\"");
//    document->appendChild(instruction);

    QDomElement root;
    root = document->createElement(tr("SCL"));
    QDomAttr xmlns = document->createAttribute(tr("xmlns"));
    xmlns.setValue(tr("http://www.iec.ch/61850/2003/SCL"));
    QDomAttr xsi = document->createAttribute(tr("xmlns:xsi"));
    xsi.setValue(tr("http://www.w3.org/2001/XMLSchema-instance"));
    QDomAttr schemaLocation = document->createAttribute(tr("xsi:schemaLocation"));
    schemaLocation.setValue(tr("http://www.iec.ch/61850/2003/SCL\\ SCL.xsd"));

//    root.setAttributeNode(xmlns);
//    root.setAttributeNode(xsi);
//    root.setAttributeNode(schemaLocation);
    document->appendChild(root);


}

void icdDataTypeTemplateNew::on_addLNode_clicked()
{

    QList<QTreeWidgetItem*> itemList = LNodeTree->selectedItems();
    for(int i = 0; i < itemList.count(); i++) {
        DataTypeItem *item = NULL;
        item = DataTypeItem::fromItemData(itemList.at(i));
        if(item->tag() == tr("LNodeType")) {
            _LNodeItemPool.append(selectedModel->insertToNewTemplate(newTemplateLNodeTree, selectedModel->root(), item));
        }
    }

    registerData();

}

void icdDataTypeTemplateNew::on_delLNode_clicked()
{
    QList<QTreeWidgetItem*> itemList = newTemplateLNodeTree->selectedItems();
    for(int i = 0; i < itemList.count(); i++) {
        DataTypeItem *item = NULL;
        item = DataTypeItem::fromItemData(itemList.at(i));
        if(item->tag() == tr("LNodeType")) {
            selectedModel->deleteItem(item);
            _LNodeItemPool.remove(_LNodeItemPool.indexOf(item));
        } else if(item->tag() == tr("DOType")) {
            selectedModel->deleteItem(item);
        } else if(item->tag() == tr("DAType")) {
            selectedModel->deleteItem(item);
        } else if(item->tag() == tr("EnumType")) {
            selectedModel->deleteItem(item);
        }
    }
}

void icdDataTypeTemplateNew::calcCheckState(QTreeWidgetItem *item, int column)
{
    DataTypeItem *dataItem = DataTypeItem::fromItemData(item);
    if(item->checkState(column) == Qt::Checked) {
        dataItem->isSelected = true;
    } else {
        dataItem->isSelected = false;
    }
}

void icdDataTypeTemplateNew::registerData()
{
    foreach (DataTypeItem* item, _LNodeItemPool) {
        for(int i = 0; i < item->getItems().count(); i++) {
            QString DoType;
            DoType = item->getItems().at(i)->attributeValueOfName("type");
            if(_DoTypeNamePool.contains(DoType))
                continue;
            foreach (DataTypeItem *doTypeItem, model->getDoTypeItems()) {
                if((doTypeItem->attributeValueOfName("id") == DoType)) {
                    //_DoTypeItemPool.append(selectedModel->insertToNewTemplate(newTemplateLNodeTree, selectedModel->root(), doTypeItem));
                    _DoTypeItemPool.append(selectedModel->insertToNewTemplateInternal(selectedModel->root(), doTypeItem));
                    _DoTypeNamePool.insert(DoType);
                }
            }
        }
    }

    foreach (DataTypeItem *item , _DoTypeItemPool) {
        for(int i = 0 ; i < item->getItems().count(); i++) {
            QString DaType;
            DaType = item->getItems().at(i)->attributeValueOfName("type");
            if(DaType == tr("") || _DaTypeNamePool.contains(DaType))
                continue;
            foreach (DataTypeItem *daTypeItem, model->getDaTypeItems()) {
                if((daTypeItem->attributeValueOfName("id") == DaType)) {
                    //_DaTypeItemPool.append(selectedModel->insertToNewTemplate(newTemplateLNodeTree, selectedModel->root(), daTypeItem));
                    _DaTypeItemPool.append(selectedModel->insertToNewTemplateInternal(selectedModel->root(), daTypeItem));
                    _DaTypeNamePool.insert(DaType);
                }
            }
        }
    }

    foreach (DataTypeItem *item , _DaTypeItemPool) {
        for(int i = 0 ; i < item->getItems().count(); i++) {
            QString EnumType;
            EnumType = item->getItems().at(i)->attributeValueOfName("type");
            if(EnumType == tr("") || _EnumTypeNamePool.contains(EnumType))
                continue;
            foreach (DataTypeItem *enumTypeItem, model->getEnumTypeItems()) {
                if((enumTypeItem->attributeValueOfName("id") == EnumType)) {
                    //selectedModel->insertToNewTemplate(newTemplateLNodeTree, selectedModel->root(), enumTypeItem);
                    selectedModel->insertToNewTemplateInternal(selectedModel->root(), enumTypeItem);
                    _EnumTypeNamePool.insert(EnumType);
                }
            }
        }
    }
}

void icdDataTypeTemplateNew::on_newTemplateLNodeTree_itemDoubleClicked(QTreeWidgetItem* item, int /*column*/)
{
    DataTypeItem *dataItem = new DataTypeItem(selectedModel);
    dataItem = DataTypeItem::fromItemData(item);

    ModifyLNodeId dialog(this);
    dialog.setModal(true);
    dialog.setTarget(dataItem);
    if(dialog.exec() == QDialog::Accepted) {
        dataItem->updateDisplay(item);
    }


}
