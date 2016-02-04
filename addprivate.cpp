#include "addprivate.h"
#include "domitem.h"

AddPrivate::AddPrivate(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle(tr("Add Private"));
    target = NULL;
    init();
}


AddPrivate::~AddPrivate()
{

}

void AddPrivate::init()
{
    layout = new QGridLayout(this);
    layout->setObjectName(tr("layout"));

    privateLabel = new QLabel(this);
    privateLabel->setObjectName(tr("privateLabel"));
    privateLabel->setText(tr("请输入private内容： "));
    privateText = new QLineEdit(this);
    privateText->setObjectName(tr("privateText"));

    typeLabel = new QLabel(this);
    typeLabel->setObjectName(tr("typeLabel"));
    typeLabel->setText(tr("type: "));
    typeText = new QLineEdit(this);
    typeText->setObjectName(tr("typeText"));

    sourceCheckBox = new QCheckBox(this);
    sourceCheckBox->setObjectName(tr("sourceCheckBox"));
    sourceCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sourceLabel = new QLabel(this);
    sourceLabel->setObjectName(tr("sourceLabel"));
    sourceLabel->setText(tr("source: "));
    sourceText = new QLineEdit(this);
    sourceText->setObjectName(tr("sourceText"));

    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName(tr("buttonBox"));

    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    buttonBox->setCenterButtons(false);

    layout->addWidget(privateLabel, 0, 1, 1, 1);
    layout->addWidget(privateText, 0, 2, 1, 1);
    layout->addWidget(typeLabel, 1, 1, 1, 1);
    layout->addWidget(typeText, 1, 2, 1, 1);
    layout->addWidget(sourceCheckBox, 2, 0, 1, 1);
    layout->addWidget(sourceLabel, 2, 1, 1, 1);
    layout->addWidget(sourceText, 2, 2, 1, 1);
    layout->addWidget(buttonBox, 3, 2, 1, 1);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

void AddPrivate::setTarget(DomItem *item)
{
    target = item;
}

void AddPrivate::accept()
{
    target->addAttribute("type", typeText->text());
    if(sourceCheckBox->isChecked()) {
        target->addAttribute("source", sourceText->text());
    }
    TextChunk *textContent = new TextChunk(false, privateText->text());
    target->addTextNode(textContent);

    QDialog::accept();
}
