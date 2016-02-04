#include "editlnode.h"
#include "dommodel.h"

EditLNode::EditLNode(QWidget *parent) :
    QDialog(parent)
{
    isStarted = false;
    modColor = QColor::fromRgb(255, 128, 128);
    isMixedContent = false ;
    init();
//    elementTable->setColumnWidth(T_COLUMN_MOD, MOD_WIDTH);
//    attrTable->setColumnWidth(A_COLUMN_MOD, MOD_WIDTH);
    target = NULL;
//    enableOK();
    resize(600, 480);
    LNodeClass.clear();

    connect(LNodeLnTypeComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(setLNodeLnClass(QString)));
}

EditLNode::~EditLNode()
{

}

void EditLNode::init()
{
    editLNodeGridLayout = new QGridLayout(this);
    editLNodeGridLayout->setObjectName(tr("editLNodeGridLayout"));

    path = new QLabel(this);
    path->setObjectName(tr("path"));
    path->setText("-----");

    LNodeGroupBox = new QGroupBox(this);
    LNodeGroupBox->setObjectName(tr("LNodeGroupBox"));
    LNodeGroupBox->setTitle("LNode Attributes");

    buttonBox = new QDialogButtonBox(Qt::Horizontal, this);
    buttonBox->setObjectName(tr("buttonBox"));
//    buttonBox->setOrientation();
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);
    buttonBox->setCenterButtons(false);

    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    editLNodeGridLayout->addWidget(path, 0, 0, 1, 1);
    editLNodeGridLayout->addWidget(LNodeGroupBox, 1, 0, 4, 1);
    editLNodeGridLayout->addWidget(buttonBox, 5, 0, 1, 1);

    LNodeGridLayout = new QGridLayout(LNodeGroupBox);
    LNodeGridLayout->setObjectName(tr("LNodeGridLayout"));

    LNodeInstLabel = new QLabel(LNodeGroupBox);
    LNodeInstLabel->setObjectName(tr("LNodeInstLabel"));
    LNodeInstLabel->setText(tr("inst: "));
    LNodeInstText = new QLineEdit(LNodeGroupBox);
    LNodeInstText->setObjectName(tr("LNodeInstText"));

    LNodeLnClassLabel = new QLabel(LNodeGroupBox);
    LNodeLnClassLabel->setObjectName(tr("LNodeLnClassLabel"));
    LNodeLnClassLabel->setText(tr("lnClass: "));
    LNodeLnClassText = new QLineEdit(LNodeGroupBox);
    LNodeLnClassText->setObjectName(tr("LNodeLnClassText"));

    LNodeLnTypeLabel = new QLabel(LNodeGroupBox);
    LNodeLnTypeLabel->setObjectName(tr("LNodeLnTypeLabel"));
    LNodeLnTypeLabel->setText(tr("lnType: "));
//    LNodeLnTypeText = new QLineEdit(LNodeGroupBox);
//    LNodeLnTypeText->setObjectName(tr("LNodeLnTypeText"));
    LNodeLnTypeComboBox = new QComboBox(LNodeGroupBox);
    LNodeLnTypeComboBox->setObjectName(tr("LNodeLnTypeComboBox"));

    LNodeDescCheckBox = new QCheckBox(LNodeGroupBox);
    LNodeDescCheckBox->setObjectName(tr("LNodeDescCheckBox"));
    LNodeDescLabel = new QLabel(LNodeGroupBox);
    LNodeDescLabel->setObjectName(tr("LNodeDescLabel"));
    LNodeDescLabel->setText(tr("desc: "));
    LNodeDescText = new QLineEdit(LNodeGroupBox);
    LNodeDescText->setObjectName(tr("LNodeDescText"));

    LNodeGridLayout->addWidget(LNodeInstLabel, 0, 1, 1, 1);
    LNodeGridLayout->addWidget(LNodeInstText, 0, 2, 1, 1);
    LNodeGridLayout->addWidget(LNodeLnClassLabel, 1, 1, 1, 1);
    LNodeGridLayout->addWidget(LNodeLnClassText, 1, 2, 1, 1);
    LNodeGridLayout->addWidget(LNodeLnTypeLabel, 2, 1, 1, 1);
    LNodeGridLayout->addWidget(LNodeLnTypeComboBox, 2, 2, 1, 1);
    LNodeGridLayout->addWidget(LNodeDescCheckBox, 3, 0, 1, 1);
    LNodeGridLayout->addWidget(LNodeDescLabel, 3, 1, 1, 1);
    LNodeGridLayout->addWidget(LNodeDescText, 3, 2, 1, 1);
}

void EditLNode::setTarget(DomItem *pItem)
{
    target = pItem;
    isMixedContent = target->isMixedContent();
    QStringList pathList = target->path();
    QString setPath = pathList.join(".");
    path->setText(setPath);
    show();

//    if(target->tag() == tr("LN0")) {
//        LNodeLnClassText->setText("LLN0");
//    } else {
//        LNodeLnClassText->setText("");
//    }

    LNodeLnClassText->setEnabled(false);
    QStringList lnTypeList;
    QVector<DomItem*> lnTypeItems;
    lnTypeItems = target->getParentRule()->getDataTypeItems();
    foreach (DomItem *item , lnTypeItems) {
        QString lnType = item->attributeValueOfName("id");
        QString lnClass = item->attributeValueOfName("lnClass");
        if((target->tag() == tr("LN0")) == (lnClass == tr("LLN0"))) {
            lnTypeList.append(lnType);
            LNodeClass.insert(lnType, lnClass);
        }
    }
    LNodeLnTypeComboBox->addItems(lnTypeList);

}

void EditLNode::accept()
{
    target->addAttribute("inst", LNodeInstText->text());
    target->addAttribute("lnClass", LNodeLnClassText->text());
    target->addAttribute("lnType", LNodeLnTypeComboBox->currentText());
    if(LNodeDescCheckBox->isChecked()) {
        target->addAttribute("desc", LNodeDescText->text());
    }

//    QString lnClass = target->attributeValueOfName("lnClass");
//    QString ldInst = target->parent()->attributeValueOfName("inst");
//    QString lnInst = target->attributeValueOfName("inst");
    QVector<DomItem*> lnTypeItems;
    lnTypeItems = target->getParentRule()->getDataTypeItems();
    foreach (DomItem *item, lnTypeItems) {
        if(item->attributeValueOfName("id") == LNodeLnTypeComboBox->currentText()) {
            for(int i = 0; i < item->getItems().size(); i++) {
                DomItem *childItem = new DomItem(target->getParentRule());
                childItem->_tag = target->getParentRule()->addNameToPool("DOI");
                childItem->setNodeType();
                childItem->addAttribute("name", item->getChildItems()->at(i)->attributeValueOfName("name"));
                QString childItemType = item->getChildItems()->at(i)->attributeValueOfName("type");

//                QString doName = childItem->attributeValueOfName("name");

                foreach (DomItem *item, target->getParentRule()->getDoTypeItems()) {
                    if(childItemType == item->attributeValueOfName("id")) {
                        for(int i = 0; i < item->getItems().size(); i++) {
                            DomItem* doChildItem = new DomItem(target->getParentRule());
                            if(item->getItems().at(i)->attributeValueOfName("bType") == tr("Struct")) {
                                doChildItem->_tag = target->getParentRule()->addNameToPool("SDI");
                                doChildItem->setNodeType();
                                doChildItem->addAttribute("name", item->getItems().at(i)->attributeValueOfName("name"));
                                foreach (DomItem *daItem, target->getParentRule()->getDaEnumItems()) {
                                    if(item->getItems().at(i)->attributeValueOfName("type") == daItem->attributeValueOfName("id")) {
                                        for(int j = 0; j < daItem->getItems().size(); j++) {
                                            DomItem *daChildItem = new DomItem(target->getParentRule());
                                            daChildItem->_tag = target->getParentRule()->addNameToPool("DAI");
                                            daChildItem->setNodeType();
                                            daChildItem->addAttribute("name", daItem->getItems().at(j)->attributeValueOfName("name"));
                                            doChildItem->addChild(daChildItem);
                                        }
                                    }
                                }
                            } else {
                                doChildItem->_tag = target->getParentRule()->addNameToPool("DAI");
                                doChildItem->setNodeType();
                                doChildItem->addAttribute("name", item->getItems().at(i)->attributeValueOfName("name"));
                            }
                            childItem->addChild(doChildItem);

//                            DomModel::_fcda *dataSetItem;
//                            dataSetItem->fc = item->getItems().at(i)->attributeValueOfName("fc");
//                            dataSetItem->daName = item->getItems().at(i)->attributeValueOfName("name");
//                            dataSetItem->doName = doName;
//                            dataSetItem->ldInst = ldInst;
//                            dataSetItem->lnInst = lnInst;
//                            dataSetItem->lnClass = lnClass;
//                            target->getParentRule()->getDataSetItems().append(dataSetItem);
                       }
                    }
                }
                target->addChild(childItem);
            }
        }
    }

    QDialog::accept();
}

void EditLNode::setLNodeLnClass(QString lnClass)
{
    LNodeLnClassText->setText(LNodeClass.value(lnClass));
}
