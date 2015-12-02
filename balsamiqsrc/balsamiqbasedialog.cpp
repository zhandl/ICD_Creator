
#include "balsamiqbasedialog.h"
#include <QFileDialog>
#include "utils.h"
#include "config.h"
#include "balsamiqwork.h"
#include <QUrl>
#include <QDesktopServices>


BalsamiqBaseDialog::BalsamiqBaseDialog(QWidget *parent) :
    QDialog(parent)
{
    init();
    loadSettings();
    checkConditions();
}

BalsamiqBaseDialog::~BalsamiqBaseDialog()
{
}

void BalsamiqBaseDialog::init()
{
    if (objectName().isEmpty())
        setObjectName(QString::fromUtf8("BalsamiqUI"));
    resize(438, 541);
    setModal(true);
    verticalLayout = new QVBoxLayout(this);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    label = new QLabel(this);
    label->setObjectName(QString::fromUtf8("label"));
    label->setAlignment(Qt::AlignCenter);

    verticalLayout->addWidget(label);

    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    label_2 = new QLabel(this);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    horizontalLayout_2->addWidget(label_2);

    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_2->addItem(horizontalSpacer);

    cmdChooseFiles = new QPushButton(this);
    cmdChooseFiles->setObjectName(QString::fromUtf8("cmdChooseFiles"));
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/open/images/document-open.png"), QSize(), QIcon::Normal, QIcon::Off);
    cmdChooseFiles->setIcon(icon);

    horizontalLayout_2->addWidget(cmdChooseFiles);


    verticalLayout->addLayout(horizontalLayout_2);

    files = new QListWidget(this);
    files->setObjectName(QString::fromUtf8("files"));

    verticalLayout->addWidget(files);

    overwriteFiles = new QCheckBox(this);
    overwriteFiles->setObjectName(QString::fromUtf8("overwriteFiles"));

    verticalLayout->addWidget(overwriteFiles);

    label_3 = new QLabel(this);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    verticalLayout->addWidget(label_3);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    outputDir = new QLineEdit(this);
    outputDir->setObjectName(QString::fromUtf8("outputDir"));

    horizontalLayout->addWidget(outputDir);

    cmdOutputDir = new QPushButton(this);
    cmdOutputDir->setObjectName(QString::fromUtf8("cmdOutputDir"));
    QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(cmdOutputDir->sizePolicy().hasHeightForWidth());
    cmdOutputDir->setSizePolicy(sizePolicy);
    cmdOutputDir->setMinimumSize(QSize(0, 0));
    cmdOutputDir->setIcon(icon);
    cmdOutputDir->setFlat(false);

    horizontalLayout->addWidget(cmdOutputDir);


    verticalLayout->addLayout(horizontalLayout);

    horizontalLayout_3 = new QHBoxLayout();
    horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
    horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_3->addItem(horizontalSpacer_2);

    cmdOpenDestinationDir = new QPushButton(this);
    cmdOpenDestinationDir->setObjectName(QString::fromUtf8("cmdOpenDestinationDir"));

    horizontalLayout_3->addWidget(cmdOpenDestinationDir);


    verticalLayout->addLayout(horizontalLayout_3);

    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Close);

    verticalLayout->addWidget(buttonBox);

#ifndef QT_NO_SHORTCUT
    label_2->setBuddy(files);
    label_3->setBuddy(outputDir);
#endif // QT_NO_SHORTCUT

    retranslateUi();
    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QMetaObject::connectSlotsByName(this);
}

void BalsamiqBaseDialog::retranslateUi()
{
    setWindowTitle(QApplication::translate("BalsamiqUI", "Balsamiq Translator", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("BalsamiqUI", "Warning: only a subset of Balsamiq objects is supported", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("BalsamiqUI", "&Files to translate", 0, QApplication::UnicodeUTF8));
    cmdChooseFiles->setText(QString());
    overwriteFiles->setText(QApplication::translate("BalsamiqUI", "&Overwrite files", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("BalsamiqUI", "Output &directory:", 0, QApplication::UnicodeUTF8));
    cmdOutputDir->setText(QString());
    cmdOpenDestinationDir->setText(QApplication::translate("BalsamiqUI", "Open destination directory", 0, QApplication::UnicodeUTF8));
}

void BalsamiqBaseDialog::loadSettings()
{
    overwriteFiles->setChecked(Config::getBool(Config::KEY_BALSAMIQ_OVERWRITEFILES, false));
    outputDir->setText(Config::getString(Config::KEY_BALSAMIQ_OUTPUTDIR, ""));
    _inputDir = Config::getString(Config::KEY_BALSAMIQ_INPUTDIR, "");
}

void BalsamiqBaseDialog::changeEvent(QEvent *e)
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

void BalsamiqBaseDialog::on_cmdOpenDestinationDir_clicked()
{
    if(outputDir->text().isEmpty()) {
        Utils::error(this, tr("The directory name is empty."));
        return ;
    }
    if(!QDesktopServices::openUrl(QUrl::fromLocalFile(outputDir->text()))) {
        Utils::error(this, tr("An error occurred opening location."));
    }
}

void BalsamiqBaseDialog::on_buttonBox_clicked(QAbstractButton * button)
{
    bool isDisabled = false;
    try {
        if((NULL != button) && (buttonBox->buttonRole(button) == QDialogButtonBox::ApplyRole)) {
            this->setEnabled(false);
            isDisabled = true;
            BalsamiqWork work;
            work.exec(this, overwriteFiles->isChecked(), _files, outputDir->text());
        }
    } catch(...) {
        Utils::error(tr("Error performing operation"));
    }
    if(isDisabled) {
        this->setEnabled(true);
    }
}

void BalsamiqBaseDialog::on_cmdOutputDir_clicked()
{
    QString dirPath = QFileDialog::getExistingDirectory(this, tr("Choose the directory"),
                      outputDir->text(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(!dirPath.isEmpty()) {
        outputDir->setText(dirPath);
        Config::saveString(Config::KEY_BALSAMIQ_OUTPUTDIR, dirPath);
    }
    checkConditions();
}

void BalsamiqBaseDialog::on_overwriteFiles_clicked()
{
    Config::saveBool(Config::KEY_BALSAMIQ_OVERWRITEFILES, overwriteFiles->isChecked());
}

void BalsamiqBaseDialog::on_cmdChooseFiles_clicked()
{
    QStringList filesPath = QFileDialog::getOpenFileNames(this, tr("Source Files"),
                            _inputDir, tr("BMML files (*.bmml);;All files (*);;"));
    if(!filesPath.empty()) {
        _files = filesPath;
        files->clear();
        bool isFirst = true ;
        foreach(QString file, _files) {
            files->addItem(new QListWidgetItem(file, files));
            if(isFirst) {
                isFirst = false ;
                // salvare la directory di uscita
                QFileInfo fileInfo(file);
                _inputDir = fileInfo.path();
                Config::saveString(Config::KEY_BALSAMIQ_INPUTDIR, _inputDir);
            }
        }
    }
    checkConditions();
}

void BalsamiqBaseDialog::on_outputDir_textEdited(const QString & /*text*/)
{
    checkConditions();
}

void BalsamiqBaseDialog::checkConditions()
{
    bool isEnabled = false;
    if((_files.size() > 0) && !outputDir->text().isEmpty()) {
        isEnabled = true ;
    }
    buttonBox->button(QDialogButtonBox::Apply)->setEnabled(isEnabled);
}
