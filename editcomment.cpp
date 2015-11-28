#include "editcomment.h"
#include "utils.h"

bool EditCommentNode(QWidget *parent, DomItem *pTarget)
{
    EditComment edit(parent);
    edit.setTarget(pTarget);
    return (edit.exec() == QDialog::Accepted);
}

EditComment::EditComment(QWidget *parent) :
    QDialog(parent)
{
    init();
    target = NULL;
    buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

EditComment::~EditComment()
{
}

void EditComment::on_commentText_textChange()
{
    QString comment = commentText->toPlainText();
    bool isEnabled = true ;
    isEnabled = !comment.isEmpty();
    buttonBox->button(QDialogButtonBox::Ok)->setEnabled(isEnabled);
}

void EditComment::init()
{
    if (objectName().isEmpty())
        setObjectName(QString::fromUtf8("EditComment"));
    setWindowModality(Qt::WindowModal);
    resize(445, 243);
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
    commentText = new QPlainTextEdit(this);
    commentText->setObjectName(QString::fromUtf8("commentText"));

    verticalLayout->addWidget(commentText);

    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

    verticalLayout->addWidget(buttonBox);

    verticalLayout_2->addLayout(verticalLayout);

    retranslateUi();
    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QMetaObject::connectSlotsByName(this);
}

void EditComment::setTarget(DomItem* pTarget)
{
    target = pTarget;
    commentText->setPlainText(target->text);
}

void EditComment::accept()
{
    if(NULL == target) {
        error(tr("No target"));
        return;
    }
    QString text = commentText->toPlainText();
    if(0 == text.length()) {
        error(tr("text is invalid"));
        return;
    }
    target->setComment(text);
    QDialog::accept();
}

void EditComment::error(const QString &message)
{
    Utils::error(this, message);
}
