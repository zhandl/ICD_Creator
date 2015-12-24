#include "modifylnodeid.h"
#include "datatypemodel.h"

ModifyLNodeId::ModifyLNodeId(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle(tr("Modify the LNode Id"));
    HLayout = new QHBoxLayout(this);
    HLayout->setObjectName(tr("HLayout"));

    LNodeIdLabel = new QLabel(tr("Modify the LNode Id: "));
    LNodeIdLabel->setObjectName(tr("LNodeIdLabel"));

    LNodeIdText = new QLineEdit(tr(""));
    LNodeIdText->setObjectName(tr("LNodeIdText"));

    acceptButton = new QPushButton(tr("OK"));
    acceptButton->setObjectName(tr("acceptButton"));

    HLayout->addWidget(LNodeIdLabel);
    HLayout->addWidget(LNodeIdText);
    HLayout->addWidget(acceptButton);

    target = NULL;

    connect(acceptButton, SIGNAL(clicked()), this, SLOT(accept()));

}

void ModifyLNodeId::setTarget(DataTypeItem *item)
{
    if(item ==NULL)
        return ;

    target = item;
    LNodeIdText->setText(target->attributeValueOfName("id"));
}

void ModifyLNodeId::accept()
{
    if(NULL == target) {
        return;
    }
    QString tag = LNodeIdText->text();
    if(0 == tag.length()) {
        return ;
    }

    if(target->getParentModel()->getLNodeIdNamePool().contains(tag))
        return ;

    foreach (Attribute *attr, target->attributes) {
        if(attr->name == "id") {
            attr->value = tag;
            target->getParentModel()->getLNodeIdNamePool().insert(tag);
        }
    }

    QDialog::accept();
}
