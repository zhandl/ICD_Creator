#include "addval.h"
#include "domitem.h"

AddVal::AddVal(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle(tr("Add Val"));
    target = NULL;
    init();
}


AddVal::~AddVal()
{

}

void AddVal::init()
{
    layout = new QGridLayout(this);
    layout->setObjectName(tr("layout"));

    valLabel = new QLabel(this);
    valLabel->setObjectName(tr("valLabel"));
    valLabel->setText(tr("请输入val值： "));
    valText = new QLineEdit(this);
    valText->setObjectName(tr("valText"));

    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName(tr("buttonBox"));

    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    buttonBox->setCenterButtons(false);

    layout->addWidget(valLabel, 0, 1, 1, 1);
    layout->addWidget(valText, 0, 2, 1, 1);
    layout->addWidget(buttonBox, 2, 2, 1, 1);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

void AddVal::setTarget(DomItem *item)
{
    target = item;
}

void AddVal::accept()
{
    TextChunk *valContent = new TextChunk(false, valText->text());
    target->addTextNode(valContent);
//    target->isMixedContent() = true;

    QDialog::accept();
}
