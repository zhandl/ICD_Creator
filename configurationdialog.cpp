
#include "configurationdialog.h"
#include "utils.h"


void ConfigurationDialog::doOptions(QWidget * const parentWindow, QXmlEditData *data)
{
    ConfigurationDialog options(data, parentWindow);
    options.setModal(true);
    options.exec();
}


ConfigurationDialog::ConfigurationDialog(QXmlEditData *data, QWidget *parent) :
    QDialog(parent),
    _data(data),
    _configureStyle(NULL),
    _configureValidation(NULL)
{
    setupUi();
    _data = new QXmlEditData();
    _generalOptions = new ConfigurationGeneralOptions(this);
    _configureStyle = new ConfigureStyle(this);
    _configureValidation = new ConfigValidation(this);

    generalIcon.addPixmap(QPixmap(QString::fromUtf8(":/configuration/general")), QIcon::Normal, QIcon::Off);
    styleIcon.addPixmap(QPixmap(QString::fromUtf8(":/configuration/style")), QIcon::Normal, QIcon::Off);
    validationIcon.addPixmap(QPixmap(QString::fromUtf8(":/configuration/validation")), QIcon::Normal, QIcon::Off);
    sessionsIcon.addPixmap(QPixmap(QString::fromUtf8(":/configuration/sessions")), QIcon::Normal, QIcon::Off);

    setTab(TAB_GENERAL, _generalOptions, generalIcon, tr("General"), tr("General Options"));
    setTab(TAB_STYLE, _configureStyle, styleIcon, tr("Style"), tr("Configure style"));
    setTab(TAB_VALIDATION, _configureValidation, validationIcon, tr("Validation"), tr("Configure schema and validation parameters"));

    init(data);
}

ConfigurationDialog::~ConfigurationDialog()
{

}

void ConfigurationDialog::setupUi()
{
    if (objectName().isEmpty())
        setObjectName(QString::fromUtf8("ConfigurationDialog"));
    resize(670, 505);
    verticalLayout = new QVBoxLayout(this);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
    tabWidget = new QTabWidget(this);
    tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
    tabWidget->setTabShape(QTabWidget::Rounded);
    tabWidget->setIconSize(QSize(32, 32));
    tabWidget->setTabsClosable(false);
    tabWidget->setMovable(false);

    horizontalLayout->addWidget(tabWidget);


    verticalLayout->addLayout(horizontalLayout);

    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Ok);

    verticalLayout->addWidget(buttonBox);

    retranslateUi();

    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    tabWidget->setCurrentIndex(-1);


    QMetaObject::connectSlotsByName(this);
}

void ConfigurationDialog::retranslateUi()
{
    setWindowTitle(QApplication::translate("ConfigurationDialog", "Configuration", 0, QApplication::UnicodeUTF8));
}

void ConfigurationDialog::setTab(const ETabs tab, QWidget *widget, QIcon &icon, const QString &title, const QString &tooltip)
{
    tabWidget->insertTab(tab, widget, icon, title);
    tabWidget->setTabToolTip(tab, tooltip);
}

void ConfigurationDialog::init(QXmlEditData *data)
{
    _generalOptions->init(data);
    _configureStyle->init(data);
    _configureValidation->init(data);
}

void ConfigurationDialog::on_buttonBox_accepted()
{
    accept();
}

void ConfigurationDialog::accept()
{
    _generalOptions->saveIfChanged();
    _configureStyle->saveIfChanged();
    _configureValidation->saveIfChanged();
    QDialog::accept();
}
