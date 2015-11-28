#include "validationresults.h"
#include "texteditutils.h"

void showValidationResults(const QString text, ValidatorMessageHandler &validator, QWidget *parent)
{
    ValidationResults dialog(text, validator, parent);
    dialog.setModal(true);
    dialog.exec();
}

ValidationResults::ValidationResults(const QString text, ValidatorMessageHandler &validator, QWidget *parent) :
    QDialog(parent),
    _validator(validator)
{
    init();
    textBrowser->setText(text);
    TextEditUtils::gotoPos(textBrowser, validator.column(), validator.line());
    TextEditUtils::hiliteCurrentPos(textBrowser);
    error->setText(QString(tr("Line:%1, Col:%2 :%3"))
                   .arg(validator.line())
                   .arg(validator.column())
                   .arg(validator.description()));
}

ValidationResults::~ValidationResults()
{

}

void ValidationResults::init()
{
    if (objectName().isEmpty())
        setObjectName(QString::fromUtf8("ValidationResults"));
    resize(585, 459);
    horizontalLayout = new QHBoxLayout(this);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    verticalLayout = new QVBoxLayout();
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    textBrowser = new QTextBrowser(this);
    textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

    verticalLayout->addWidget(textBrowser);

    error = new QLabel(this);
    error->setObjectName(QString::fromUtf8("error"));

    verticalLayout->addWidget(error);


    horizontalLayout->addLayout(verticalLayout);

    verticalLayout_2 = new QVBoxLayout();
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setOrientation(Qt::Vertical);
    buttonBox->setStandardButtons(QDialogButtonBox::Close);
    buttonBox->setCenterButtons(false);

    verticalLayout_2->addWidget(buttonBox);

    verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout_2->addItem(verticalSpacer);


    horizontalLayout->addLayout(verticalLayout_2);


    retranslateUi();
    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QMetaObject::connectSlotsByName(this);
}

void ValidationResults::retranslateUi()
{
    setWindowTitle(QApplication::translate("ValidationResults", "Validation Results", 0, QApplication::UnicodeUTF8));
    error->setText(QApplication::translate("ValidationResults", "------", 0, QApplication::UnicodeUTF8));
}

void ValidationResults::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch(e->type()) {
    case QEvent::LanguageChange:
        retranslateUi();
        break;
    default:
        break;
    }
}
