#include "editdataset.h"
#include "domitem.h"
#include "dommodel.h"

EditDataSet::EditDataSet(QWidget *parent) :
    QDialog(parent)
{
    init();
    target = NULL;
    model = NULL;
    dataSetItems.clear();
    FC.clear();

    _fcItems.clear();
    _doItems.clear();

    resize(600, 480);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    connect(LNodeTree, SIGNAL(itemChanged(QTreeWidgetItem*,int)), this, SLOT(showFCDA(QTreeWidgetItem*, int)));
}

EditDataSet::~EditDataSet()
{

}

void EditDataSet::init()
{
    dataSetGridLayout = new QGridLayout(this);
    dataSetGridLayout->setObjectName(tr("dataSetGridLayout"));

    dataSetNameLabel = new QLabel(this);
    dataSetNameLabel->setObjectName(tr("dataSetNameLabel"));
    dataSetNameLabel->setText(tr("name"));
    dataSetNameText = new QLineEdit(this);
    dataSetNameText->setObjectName(tr("dataSetNameText"));

    LNodeComboBox = new QComboBox(this);
    LNodeComboBox->setObjectName(tr("LNodeComboBox"));
    fcComboBox = new QComboBox(this);
    fcComboBox->setObjectName(tr("fcComboBox"));
    dataSetSplitter = new QSplitter(Qt::Horizontal, this);
    dataSetSplitter->setObjectName(tr("dataSetSplitter"));
    LNodeTree = new QTreeWidget(this);
    LNodeTree->setObjectName(tr("LNodeTree"));
    LNodeTree->setColumnCount(1);
    fcdaList = new QListWidget(this);
    fcdaList->setObjectName(tr("fcdaList"));

    buttonBox = new QDialogButtonBox(Qt::Horizontal, this);
    buttonBox->setObjectName(tr("buttonBox"));
    buttonBox->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    dataSetSplitter->addWidget(LNodeTree);
    dataSetSplitter->addWidget(fcdaList);

    dataSetGridLayout->addWidget(dataSetNameLabel, 0, 0, 1, 1);
    dataSetGridLayout->addWidget(dataSetNameText, 0, 1, 1, 1);
    dataSetGridLayout->addWidget(LNodeComboBox, 1, 0, 1, 1);
    dataSetGridLayout->addWidget(fcComboBox, 1, 1, 1, 1);
    dataSetGridLayout->addWidget(buttonBox, 1, 3, 1, 1);
    dataSetGridLayout->addWidget(dataSetSplitter, 2, 0, 1, 4);

}

void EditDataSet::setTarget(DomItem *pItem)
{
    target = pItem;
    model = target->getParentRule();
    DomItem *iedItem = target->parent()->parent()->parent()->parent()->parent();
    DomItem *ldItem = target->parent()->parent();

    QTreeWidgetItem *iedTreeItem = new QTreeWidgetItem(0);
    iedTreeItem->setText(0, iedItem->attributeValueOfName("name"));
    LNodeTree->addTopLevelItem(iedTreeItem);

    QTreeWidgetItem *ldTreeItem = new QTreeWidgetItem(0);
    ldTreeItem->setText(0, ldItem->attributeValueOfName("inst"));
    ldTreeItem->setFlags(ldTreeItem->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsTristate);
    ldTreeItem->setCheckState(0, Qt::Unchecked);
    iedTreeItem->addChild(ldTreeItem);

    foreach (DomItem *item, ldItem->getItems()) {
        QTreeWidgetItem *lnodeTreeItem = new QTreeWidgetItem(0);
        QString lnodeTreeName = item->attributeValueOfName("lnClass") + item->attributeValueOfName("inst");
        lnodeTreeItem->setText(0, lnodeTreeName);
//        lnodeTreeItem->setFlags(lnodeTreeItem->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsTristate);
        ldTreeItem->addChild(lnodeTreeItem);

        FC.clear();

        getDataSetItems(item);

        foreach (DomItem *doItem, item->getItems()) {
            if(doItem->tag() == tr("DOI")) {
                QString doName = doItem->attributeValueOfName("name");
                for(int i=0; i<doItem->getChildItems()->size(); i++) {
                    QTreeWidgetItem *daTreeItem = new QTreeWidgetItem(0);
                    daTreeItem->setText(0, doItem->getChildAt(i)->attributeValueOfName("name"));
                    daTreeItem->setFlags(daTreeItem->flags() | Qt::ItemIsUserCheckable);
                    daTreeItem->setCheckState(0, Qt::Unchecked);
                    if(doItem->getChildAt(i)->tag() == tr("SDI")) {
                        foreach(DomItem *daItem, doItem->getChildAt(i)->getItems()) {
                            QTreeWidgetItem *leafTreeItem = new QTreeWidgetItem(0);
                            leafTreeItem->setText(0, daItem->attributeValueOfName("name"));
                            leafTreeItem->setFlags(leafTreeItem->flags() | Qt::ItemIsUserCheckable);
                            leafTreeItem->setCheckState(0, Qt::Unchecked);
                            daTreeItem->addChild(leafTreeItem);
                            daTreeItem->setFlags(daTreeItem->flags()  | Qt::ItemIsTristate);
                        }
                    }
                    QString fcName = dataSetItems.value(doItem->getChildAt(i));
                    if(FC.contains(fcName)) {
                        bool hasDo = false;
                        for(int j = 0 ; j < lnodeTreeItem->childCount(); j++) {
                            QTreeWidgetItem *fcItem = lnodeTreeItem->child(j);
                            _fcItems.append(fcItem);
                            if(fcItem->text(0) == fcName) {
                                //                            if(DO.contains(doName)) {
                                for(int k = 0; k < fcItem->childCount(); k++) {
                                    QTreeWidgetItem *doItem = fcItem->child(k);
                                    _doItems.append(doItem);
                                    if(doItem->text(0) == doName) {
                                        doItem->addChild(daTreeItem);
                                        hasDo = true;
                                        break;
                                    }
                                }
                                if(!hasDo){
                                    QTreeWidgetItem *doTreeItem = new QTreeWidgetItem(0);
                                    _doItems.append(doTreeItem);
                                    doTreeItem->setText(0, doName);
                                    doTreeItem->setFlags(doTreeItem->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsTristate);
                                    doTreeItem->setCheckState(0, Qt::Unchecked);
                                    doTreeItem->addChild(daTreeItem);
                                    fcItem->addChild(doTreeItem);
                                }
                            }
                        }
                    } else {
                        QTreeWidgetItem *fcTreeItem = new QTreeWidgetItem(0);
                        _fcItems.append(fcTreeItem);
                        fcTreeItem->setText(0, fcName);
                        fcTreeItem->setFlags(fcTreeItem->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsTristate);
                        fcTreeItem->setCheckState(0, Qt::Unchecked);
                        FC.insert(fcName);
                        QTreeWidgetItem *doTreeItem = new QTreeWidgetItem(0);
                        _doItems.append(doTreeItem);
                        doTreeItem->setText(0, doName);
                        doTreeItem->setFlags(doTreeItem->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsTristate);
                        doTreeItem->setCheckState(0, Qt::Unchecked);
                        doTreeItem->addChild(daTreeItem);
                        fcTreeItem->addChild(doTreeItem);
                        lnodeTreeItem->addChild(fcTreeItem);
                    }
                }
            }
        }


        LNodeComboBox->addItem(item->attributeValueOfName("lnType"));
    }

}

void EditDataSet::accept()
{
    target->addAttribute("name", dataSetNameText->text());
    foreach (fcda* item, fcdaItems) {
        DomItem *fcdaItem = new DomItem(target->getParentRule());
        fcdaItem->_tag = target->getParentRule()->addNameToPool(tr("FCDA"));
        if(item->hasLdInst)
            fcdaItem->addAttribute("ldInst", item->ldInst);
        if(item->hasLnInst)
            fcdaItem->addAttribute("lnInst", item->lnInst);
        if(item->hasLnClass)
            fcdaItem->addAttribute("lnClass", item->lnClass);
        fcdaItem->addAttribute("fc", item->fc);
        if(item->hasDoName)
            fcdaItem->addAttribute("doName", item->doName);
        if(item->hasDaName)
            fcdaItem->addAttribute("daName", item->daName);

        fcdaItem->setNodeType();
        target->addChild(fcdaItem);
    }
    QDialog::accept();
}

void EditDataSet::getDataSetItems(DomItem *item)
{
    if(NULL == item)
        return ;

    DomModel *itemModel = item->getParentRule();

    if(item->tag() == tr("DAI") || item->tag() == tr("SDI")) {
        QString itemName = item->attributeValueOfName("name");
        DomItem *lnodeTypeItem = itemModel->getDataTypeItemWithId(item->parent()->parent()->attributeValueOfName("lnType"));
        QString itemType;
        for(int i = 0; i < lnodeTypeItem->getChildItems()->size(); i++) {
            if(lnodeTypeItem->getChildAt(i)->attributeValueOfName("name") == item->parent()->attributeValueOfName("name")) {
                itemType = lnodeTypeItem->getChildAt(i)->attributeValueOfName("type");
               // break;
            }
        }

        foreach (DomItem *doItem, itemModel->getDoTypeItems()) {
            if(doItem->attributeValueOfName("id") == itemType) {
                for(int j = 0; j < doItem->getChildItems()->size(); j++) {
                    DomItem *daItem = doItem->getChildAt(j);
                    if(daItem->attributeValueOfName("name") == itemName) {
                        dataSetItems.insert(item, daItem->attributeValueOfName("fc"));
//                        FC.insert(daItem->attributeValueOfName("fc"));
                      //  break;
                    }
                }
               // break;
            }
        }
    } else {
        foreach(DomItem *childItem, item->getItems())
            getDataSetItems(childItem);
    }
}

void EditDataSet::showFCDA(QTreeWidgetItem *item, int column)
{
    fcdaList->clear();
    if(_doItems.contains(item)) {
        if(item->checkState(column) == Qt::Checked) {
//            for(int i = 0; i < fcdaItems.count(); i++) {
//                if(fcdaItems.at(i)->doName == item->text(column)) {
//                    fcdaItems.remove(i);
//                }
//            }
            foreach (fcda* fcdaItem, fcdaItems) {
                if(fcdaItem->doName == item->text(column) && fcdaItem->fc == item->parent()->text(column)) {
                    fcdaItems.remove(fcdaItem);
                }
            }

            fcda *fcdaItem = new fcda;
            fcdaItem->hasDaName = false;
            fcdaItem->hasDoName = true;
            fcdaItem->hasLdInst = true;
            fcdaItem->hasLnClass = true;
            fcdaItem->doName = item->text(column);
            fcdaItem->fc = item->parent()->text(0);
            QString lnName = item->parent()->parent()->text(0);
            fcdaItem->hasLnInst = (lnName.count() > 4);
            fcdaItem->lnClass = lnName.left(4);
            if(fcdaItem->hasLnInst)
                fcdaItem->lnInst = lnName.mid(4);
            fcdaItem->ldInst = item->parent()->parent()->parent()->text(0);

            fcdaItems.insert(fcdaItem);
        } else if(item->checkState(column) == Qt::Unchecked) {
//            for(int i = 0; i < fcdaItems.count(); i++) {
//                if(fcdaItems.at(i)->doName == item->text(column)) {
//                    fcdaItems.remove(i);
//                }
//            }
            foreach (fcda* fcdaItem, fcdaItems) {
                if(fcdaItem->doName == item->text(column) && fcdaItem->fc == item->parent()->text(column)) {
                    fcdaItems.remove(fcdaItem);
                }
            }
        } else if(item->checkState(column) == Qt::PartiallyChecked) {
//            for(int i = 0; i < fcdaItems.count(); i++) {
//                if(fcdaItems.at(i)->doName == item->text(column)) {
//                    fcdaItems.remove(i);
//                }
//            }
            foreach (fcda* fcdaItem, fcdaItems) {
                if(fcdaItem->doName == item->text(column) && fcdaItem->fc == item->parent()->text(column)) {
                    fcdaItems.remove(fcdaItem);
                }
            }
            for(int i = 0; i < item->childCount(); i++) {
                if(item->child(i)->checkState(0) == Qt::Checked) {
                    fcda *fcdaItem = new fcda;
                    fcdaItem->hasDaName = true;
                    fcdaItem->hasDoName = true;
                    fcdaItem->hasLdInst = true;
                    fcdaItem->hasLnClass = true;
                    fcdaItem->doName = item->text(column);
                    fcdaItem->daName = item->child(i)->text(0);
                    fcdaItem->fc = item->parent()->text(0);
                    QString lnName = item->parent()->parent()->text(0);
                    fcdaItem->hasLnInst = (lnName.count() > 4);
                    fcdaItem->lnClass = lnName.left(4);
                    if(fcdaItem->hasLnInst)
                        fcdaItem->lnInst = lnName.mid(4);
                    fcdaItem->ldInst = item->parent()->parent()->parent()->text(0);

                    fcdaItems.insert(fcdaItem);
                }
            }
        }
    }

    foreach (fcda* fcdaItem, fcdaItems) {
        QListWidgetItem *fcdaListItem = new QListWidgetItem(0);
        QString fcdaText = fcdaItem->ldInst + "/" +
                           fcdaItem->lnClass + fcdaItem->lnInst + "." +
                           fcdaItem->fc + "." +
                           fcdaItem->doName;
        if(fcdaItem->hasDaName) {
            fcdaText += fcdaItem->daName;
        }
        fcdaListItem->setText(fcdaText);
        fcdaList->addItem(fcdaListItem);
    }
}
