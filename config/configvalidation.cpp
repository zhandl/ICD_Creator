
#include "configvalidation.h"

ConfigValidation::ConfigValidation(QWidget *parent) :
    QWidget(parent)
{
    setupUi();
}

ConfigValidation::~ConfigValidation()
{
}

void ConfigValidation::setupUi()
{
    if (objectName().isEmpty())
        setObjectName(QString::fromUtf8("ConfigValidation"));
    resize(500, 306);
    verticalLayout = new QVBoxLayout(this);
    verticalLayout->setSpacing(20);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    verticalLayout->setContentsMargins(20, 20, 4, 20);
    label_2 = new QLabel(this);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    QFont font;
    font.setBold(true);
    font.setWeight(75);
    label_2->setFont(font);
    label_2->setAlignment(Qt::AlignCenter);

    verticalLayout->addWidget(label_2);

    chbAutomaticValidationLoading = new QCheckBox(this);
    chbAutomaticValidationLoading->setObjectName(QString::fromUtf8("chbAutomaticValidationLoading"));

    verticalLayout->addWidget(chbAutomaticValidationLoading);

    chkEnableDiskCache = new QCheckBox(this);
    chkEnableDiskCache->setObjectName(QString::fromUtf8("chkEnableDiskCache"));

    verticalLayout->addWidget(chkEnableDiskCache);

    label = new QLabel(this);
    label->setObjectName(QString::fromUtf8("label"));
    label->setEnabled(false);
    QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
    label->setSizePolicy(sizePolicy);

    verticalLayout->addWidget(label);

    extValidationProgram = new QLineEdit(this);
    extValidationProgram->setObjectName(QString::fromUtf8("extValidationProgram"));
    extValidationProgram->setEnabled(false);

    verticalLayout->addWidget(extValidationProgram);

    verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout->addItem(verticalSpacer_4);

    verticalLayout->setStretch(1, 1);
    verticalLayout->setStretch(2, 1);
    verticalLayout->setStretch(3, 1);

    retranslateUi();

    QMetaObject::connectSlotsByName(this);
}

void ConfigValidation::retranslateUi()
{
    setWindowTitle(QApplication::translate("ConfigValidation", "Form", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("ConfigValidation", "XSD Validation and Loading", 0, QApplication::UnicodeUTF8));
    chbAutomaticValidationLoading->setText(QApplication::translate("ConfigValidation", "Enable automatic loading of XML Schema associated to file edited", 0, QApplication::UnicodeUTF8));
    chkEnableDiskCache->setText(QApplication::translate("ConfigValidation", "Enable disk cache (maximum size: 1 Mega)", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("ConfigValidation", "External validation program", 0, QApplication::UnicodeUTF8));
}

void ConfigValidation::init(QXmlEditData *data)
{
    _data = data;
    chbAutomaticValidationLoading->setChecked(_data->isAutovalidationOn());
    chkEnableDiskCache->setChecked(_data->isXsdCacheEnabled());
}

void ConfigValidation::save()
{
    _data->setAutovalidationOn(chbAutomaticValidationLoading->isChecked());
    _data->setXsdCacheEnabled(chkEnableDiskCache->isChecked());
}

void ConfigValidation::saveIfChanged()
{
    save();
}
