#include "schemachooser.h"
#include "SchemaInterface.h"
#include "config.h"
#include "utils.h"
#include <QInputDialog>
#include <QFileDialog>

QString chooseSchemaFile(QWidget *parent, bool &isOk)
{
    QString result;
    isOk = false;
    SchemaChooser dialog(parent);
    if(dialog.exec() == QDialog::Accepted) {
        isOk = true;
        result = dialog.selection();
    }
    return result;
}

SchemaChooser::SchemaChooser(QWidget *parent) :
    QDialog(parent),
    _started(false)
{
    init();
    enableOK(false);
    remPrefsSchema->setEnabled(false);
    favoritesList->setSelectionMode(QAbstractItemView::SingleSelection);
    lastUsedList->setSelectionMode(QAbstractItemView::SingleSelection);
    loadPreferredData();
    loadLastUsedData();
    _started = true;
}

SchemaChooser::~SchemaChooser()
{

}

void SchemaChooser::init()
{
    if (objectName().isEmpty())
        setObjectName(QString::fromUtf8("SchemaChooser"));
    resize(815, 537);
    verticalLayout_2 = new QVBoxLayout(this);
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    label = new QLabel(this);
    label->setObjectName(QString::fromUtf8("label"));

    verticalLayout_2->addWidget(label);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    favoritesList = new QListWidget(this);
    favoritesList->setObjectName(QString::fromUtf8("favoritesList"));

    horizontalLayout->addWidget(favoritesList);

    verticalLayout = new QVBoxLayout();
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    addPrefsSchema = new QPushButton(this);
    addPrefsSchema->setObjectName(QString::fromUtf8("addPrefsSchema"));

    verticalLayout->addWidget(addPrefsSchema);

    remPrefsSchema = new QPushButton(this);
    remPrefsSchema->setObjectName(QString::fromUtf8("remPrefsSchema"));

    verticalLayout->addWidget(remPrefsSchema);


    horizontalLayout->addLayout(verticalLayout);


    verticalLayout_2->addLayout(horizontalLayout);

    horizontalLayout_3 = new QHBoxLayout();
    horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
    label_3 = new QLabel(this);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    horizontalLayout_3->addWidget(label_3);

    textSelection = new QLineEdit(this);
    textSelection->setObjectName(QString::fromUtf8("textSelection"));

    horizontalLayout_3->addWidget(textSelection);

    browseFile = new QPushButton(this);
    browseFile->setObjectName(QString::fromUtf8("browseFile"));

    horizontalLayout_3->addWidget(browseFile);


    verticalLayout_2->addLayout(horizontalLayout_3);

    label_2 = new QLabel(this);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    verticalLayout_2->addWidget(label_2);

    lastUsedList = new QListWidget(this);
    lastUsedList->setObjectName(QString::fromUtf8("lastUsedList"));

    verticalLayout_2->addWidget(lastUsedList);

    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_2->addItem(horizontalSpacer);

    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

    horizontalLayout_2->addWidget(buttonBox);


    verticalLayout_2->addLayout(horizontalLayout_2);


    retranslateUi();
    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QMetaObject::connectSlotsByName(this);
}

void SchemaChooser::retranslateUi()
{
    setWindowTitle(QApplication::translate("SchemaChooser", "Choose a Schema", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("SchemaChooser", "Favorites:", 0, QApplication::UnicodeUTF8));
    addPrefsSchema->setText(QApplication::translate("SchemaChooser", "Add...", 0, QApplication::UnicodeUTF8));
    remPrefsSchema->setText(QApplication::translate("SchemaChooser", "Remove", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("SchemaChooser", "Selection:", 0, QApplication::UnicodeUTF8));
    browseFile->setText(QApplication::translate("SchemaChooser", "...", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("SchemaChooser", "Last used schema:", 0, QApplication::UnicodeUTF8));
}

QString SchemaChooser::selection()
{
    return _selection;
}

void SchemaChooser::loadPreferredData()
{
    Config::loadStringArray(Config::KEY_SCHEMA_PREFERITES, _preferitesFilesNames);
    foreach(QString file, _preferitesFilesNames) {
        new QListWidgetItem(file, favoritesList);
    }
}

void SchemaChooser::loadLastUsedData()
{
    Config::loadStringArray(Config::KEY_SCHEMA_LAST, _lastFilesNames);
    foreach (QString file, _lastFilesNames) {
        new QListWidgetItem(file, lastUsedList);
    }
}

void SchemaChooser::saveSelection()
{
    _lastFilesNames.removeAll(_selection);
    _lastFilesNames.insert(0, _selection);
    while(_lastFilesNames.size() > MAX_LAST_FILES) {
        _lastFilesNames.removeLast();
    }
    Config::saveStringArray(Config::KEY_SCHEMA_LAST, _lastFilesNames);
}

void SchemaChooser::on_lastUsedList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(NULL != current) {
        setSelection(current->text());
    }
}

void SchemaChooser::on_lastUsedList_itemClicked(QListWidgetItem *item)
{
    if(_started) {
        if(NULL != item) {
            setSelection(item->text());
        }
    }
}

void SchemaChooser::on_lastUsedList_itemDoubleClicked(QListWidgetItem *item)
{
    if(NULL != item) {
        setSelection(item->text());
        accept();
    }
}

void SchemaChooser::on_favoritesList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *)
{
    if(!_started) {
        if(NULL != current) {
            setSelection(current->text());
        }
    }
    remPrefsSchema->setEnabled(NULL != current);
}

void SchemaChooser::on_favoritesList_itemClicked(QListWidgetItem *item)
{
    if(NULL != item) {
        setSelection(item->text());
    }
}

void SchemaChooser::on_favoritesList_itemDoubleClicked(QListWidgetItem *item)
{
    if(NULL != item) {
        setSelection(item->text());
        accept();
    }
}

void SchemaChooser::setSelection(const QString &newSelection)
{
    _selection = newSelection;
    textSelection->setText(_selection);
}

void SchemaChooser::on_addPrefsSchema_clicked()
{
    bool isOk;
    QString newUrl = QInputDialog::getText(this,
                                           tr("Add a new schema URL to Preferites"),
                                           tr("Schema URL:"),
                                           QLineEdit::Normal,
                                           "",
                                           &isOk);
    if(isOk && !newUrl.isEmpty()) {
        if(_preferitesFilesNames.contains(newUrl)) {
            Utils::error(this, tr("The URL is already present in the favorite ones."));
            return ;
        }
        _preferitesFilesNames.append(newUrl);
        QListWidgetItem *newItem = new QListWidgetItem(newUrl, favoritesList);
        favoritesList->setCurrentItem(newItem);
        Config::saveStringArray(Config::KEY_SCHEMA_PREFERITES, _preferitesFilesNames);
    }
}

void SchemaChooser::on_remPrefsSchema_clicked()
{
    QString urlToRemove;
    QListWidgetItem *item = favoritesList->currentItem();
    if(NULL != item) {
        urlToRemove = item->text();
    }
    if(!urlToRemove.isEmpty()) {
        Utils::errorNoSel(this);
        return ;
    }
    _preferitesFilesNames.removeAll(urlToRemove);
    Config::saveStringArray(Config::KEY_SCHEMA_PREFERITES, _preferitesFilesNames);
    favoritesList->clear();
    loadPreferredData();
}

void SchemaChooser::accept()
{
    if(!_selection.isEmpty()) {
        saveSelection();
        QDialog::accept();
    } else {
        Utils::errorNoSel(this);
    }
}

void SchemaChooser::on_browseFile_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Choose a File "),
                                                   textSelection->text(), tr("XSD files (*.xsd);;All files (*);;"));
    if(!filePath.isEmpty()) {
        textSelection->setText(filePath);
    }
}

void SchemaChooser::enableOK(const bool isEnabled)
{
    buttonBox->button(QDialogButtonBox::Ok)->setEnabled(isEnabled);
}

void SchemaChooser::on_textSelection_textChanged(const QString &text)
{
    enableOK(!text.isEmpty());
    _selection = text;
}
