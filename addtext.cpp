#include "addtext.h"
#include "domitem.h"

AddText::AddText(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle(tr("Add Text"));
    target = NULL;
    init();
}


AddText::~AddText()
{

}

void AddText::init()
{
    layout = new QGridLayout(this);
    layout->setObjectName(tr("layout"));

    textLabel = new QLabel(this);
    textLabel->setObjectName(tr("textLabel"));
    textLabel->setText(tr("请输入Text内容： "));
    textText = new QLineEdit(this);
    textText->setObjectName(tr("textText"));

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

    layout->addWidget(textLabel, 0, 1, 1, 1);
    layout->addWidget(textText, 0, 2, 1, 1);
    layout->addWidget(sourceCheckBox, 1, 0, 1, 1);
    layout->addWidget(sourceLabel, 1, 1, 1, 1);
    layout->addWidget(sourceText, 1, 2, 1, 1);
    layout->addWidget(buttonBox, 2, 2, 1, 1);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

void AddText::setTarget(DomItem *item)
{
    target = item;
}

void AddText::accept()
{
    if(sourceCheckBox->isChecked()) {
        target->addAttribute("source", sourceText->text());
    }
    TextChunk *textContent = new TextChunk(false, textText->text());
    target->addTextNode(textContent);
//    target->isMixedContent() = true;

    QDialog::accept();
}
