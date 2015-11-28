#include "editprocessinginstruction.h"
#include "utils.h"

bool editProcessingInstruction(QWidget *parent, DomItem *pTarget)
{
    EditProcessingInstruction edit(parent);
    edit.setTarget(pTarget);
    return (edit.exec() == QDialog::Accepted);
}

EditProcessingInstruction::EditProcessingInstruction(QWidget *parent) :
    QDialog(parent)
{
    init();
    target = NULL;
    buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

EditProcessingInstruction::~EditProcessingInstruction()
{
}

void EditProcessingInstruction::init()
{
    if (objectName().isEmpty())
        setObjectName(QString::fromUtf8("EditProcessing"));
    setWindowModality(Qt::WindowModal);
    resize(445, 165);
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    setSizePolicy(sizePolicy);
    setAutoFillBackground(false);
    setModal(true);
    verticalLayout_2 = new QVBoxLayout(this);
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    verticalLayout = new QVBoxLayout();
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    verticalLayout->setSizeConstraint(QLayout::SetNoConstraint);
    label = new QLabel(this);
    label->setObjectName(QString::fromUtf8("label"));

    verticalLayout->addWidget(label);

    editTarget = new QLineEdit(this);
    editTarget->setObjectName(QString::fromUtf8("editTarget"));

    verticalLayout->addWidget(editTarget);

    label_2 = new QLabel(this);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    verticalLayout->addWidget(label_2);

    editData = new QLineEdit(this);
    editData->setObjectName(QString::fromUtf8("editData"));

    verticalLayout->addWidget(editData);

    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

    verticalLayout->addWidget(buttonBox);


    verticalLayout_2->addLayout(verticalLayout);

#ifndef QT_NO_SHORTCUT
    label->setBuddy(editTarget);
    label_2->setBuddy(editData);
#endif // QT_NO_SHORTCUT

    retranslateUi();
    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QMetaObject::connectSlotsByName(this);
}

void EditProcessingInstruction::checkOKEnabled()
{
    QString target = editTarget->text();
    QString data = editData->text();
    bool isEnabled = true;
    isEnabled = !(target.isEmpty() || data.isEmpty());
    buttonBox->button(QDialogButtonBox::Ok)->setEnabled(isEnabled);
}

void EditProcessingInstruction::on_editTarget_textChanged()
{
    checkOKEnabled();
}

void EditProcessingInstruction::on_editData_textChanged()
{
    checkOKEnabled();
}

void EditProcessingInstruction::setTarget(DomItem *pTarget)
{
    target = pTarget;
    editTarget->setText(target->getPITarget());
    editData->setText(target->getPIData());
}

void EditProcessingInstruction::accept()
{
    if(NULL == target) {
        error(tr("No target"));
        return;
    }
    QString textTarget = editTarget->text();
    if(0 == textTarget.length()) {
        error(tr("Target text is invalid"));
        return;
    }
    QString textData = editData->text();
    if(0 == textTarget.length()) {
        error(tr("Data text is invalid"));
        return;
    }
    target->setPITarget(textTarget);
    target->setPIData(textData);
    QDialog::accept();
}

void EditProcessingInstruction::error(const QString &message)
{
    Utils::error(this, message);
}
