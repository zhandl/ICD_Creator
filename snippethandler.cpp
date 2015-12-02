/**************************************************************************
 *  This file is part of QXmlEdit                                         *
 *  Copyright (C) 2011 by Luca Bellonda and individual contributors       *
 *    as indicated in the AUTHORS file                                    *
 *  lbellonda _at_ gmail.com                                              *
 *                                                                        *
 * This library is free software; you can redistribute it and/or          *
 * modify it under the terms of the GNU Library General Public            *
 * License as published by the Free Software Foundation; either           *
 * version 2 of the License, or (at your option) any later version.       *
 *                                                                        *
 * This library is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU      *
 * Library General Public License for more details.                       *
 *                                                                        *
 * You should have received a copy of the GNU Library General Public      *
 * License along with this library; if not, write to the                  *
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,       *
 * Boston, MA  02110-1301  USA                                            *
 **************************************************************************/
#include "snippethandler.h"
#include "snippet_interface.h"
#include "editsnippet.h"
#include "utils.h"

#define COLUMN_DATA_TAG (0)
#define COLUMN_DATA_SNIPPET (1)


void editSnippets(QXmlEditData *data, QWidget *parent)
{
    SnippetHandler handler(data, true, parent);
    handler.setModal(true);
    handler.exec();
}

DomModel* chooseSnippets(QXmlEditData *data, QWidget *parent)
{
    SnippetHandler handler(data, false, parent);
    handler.setModal(true);
    if(handler.exec() == QDialog::Accepted) {
        return handler.model();
    }
    return NULL;
}

void insertFragmentInSnippets(QWidget *parent, QXmlEditData *data, const QString &text)
{
    SnippetHandler handler(data, true, parent);
    handler.insertFragment(parent, text);
}

SnippetHandler::SnippetHandler(QXmlEditData *data, const bool setEditMode, QWidget *parent) :
    QDialog(parent),
    _isEditMode(setEditMode),
    _model(NULL),
    _data(data)
{
    init();
    refineUI();
    loadSnippets();
    fillTree();
}

SnippetHandler::~SnippetHandler()
{
    Snippet::resetSnippetContainer(_snippets);
}

void SnippetHandler::init()
{
    if (objectName().isEmpty())
        setObjectName(QString::fromUtf8("SnippetHandler"));
    resize(485, 465);
    horizontalLayout = new QHBoxLayout(this);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    verticalLayout = new QVBoxLayout();
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    snippets = new QTreeWidget(this);
    QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
    __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
    snippets->setHeaderItem(__qtreewidgetitem);
    snippets->setObjectName(QString::fromUtf8("snippets"));

    verticalLayout->addWidget(snippets);


    horizontalLayout->addLayout(verticalLayout);

    verticalLayout_2 = new QVBoxLayout();
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setOrientation(Qt::Vertical);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Close|QDialogButtonBox::Ok);

    verticalLayout_2->addWidget(buttonBox);

    verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout_2->addItem(verticalSpacer);

    newCmd = new QPushButton(this);
    newCmd->setObjectName(QString::fromUtf8("newCmd"));

    verticalLayout_2->addWidget(newCmd);

    modifyCmd = new QPushButton(this);
    modifyCmd->setObjectName(QString::fromUtf8("modifyCmd"));

    verticalLayout_2->addWidget(modifyCmd);

    deleteCmd = new QPushButton(this);
    deleteCmd->setObjectName(QString::fromUtf8("deleteCmd"));

    verticalLayout_2->addWidget(deleteCmd);

    verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout_2->addItem(verticalSpacer_2);


    horizontalLayout->addLayout(verticalLayout_2);


    retranslateUi();
    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QMetaObject::connectSlotsByName(this);
}

void SnippetHandler::retranslateUi()
{
    setWindowTitle(QApplication::translate("SnippetHandler", "Snippets", 0, QApplication::UnicodeUTF8));
    newCmd->setText(QApplication::translate("SnippetHandler", "&New", 0, QApplication::UnicodeUTF8));
    modifyCmd->setText(QApplication::translate("SnippetHandler", "&Modify", 0, QApplication::UnicodeUTF8));
    deleteCmd->setText(QApplication::translate("SnippetHandler", "&Delete", 0, QApplication::UnicodeUTF8));
}

void SnippetHandler::refineUI()
{
    snippets->setColumnCount(2);
    snippets->clear();
    QStringList headers;
    headers << tr("Name");
    headers << tr("Description");
    snippets->setHeaderLabels(headers);
    evaluateSelection();
}

DomModel *SnippetHandler::model()
{
    return _model;
}

void SnippetHandler::changeEvent(QEvent *e)
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

void SnippetHandler::loadSnippets()
{
    //Snippet::loadMockSnippet(_snippets);
    if(! scanDirectory(_data->snippetsLocalDir(), false)) {
        Utils::error(this, tr("Error reading user's snippets."));
    }
    if(! scanDirectory(_data->snippetsProgramDir(), true)) {
        Utils::error(this, tr("Error reading snippets."));
    }
}

void SnippetHandler::accept()
{
    bool isOk = false ;
    if(!_isEditMode) {
        QDomDocument document ;
        Snippet *snippet = NULL ;
#ifdef  _TEST
        snippet = _snippets.values().at(0);
#else
        snippet = getSelSnippet();
#endif
        if(NULL != snippet) {
            if(document.setContent(snippet->payload())) {
                _model = new DomModel(document, "");
                isOk = true;
            }
        } else {
            Utils::error(this, tr("No snippet selected."));
            return ;
        }
    } else {
        // if in edit, close window.
        isOk = true ;
    }
    if(isOk) {
        QDialog::accept();
    } else {
        Utils::error(this, tr("Error performing operation."));
    }
}


void SnippetHandler::fillTree()
{
    bool isOk = true;
    foreach(Snippet * entry, _snippets.values()) {
        if(!insertSnippetInUI(entry)) {
            isOk = false;
        }
    }
    if(!isOk) {
        Utils::error(this, tr("An error occurred")) ;
    }
}

void SnippetHandler::deleteSnippet(Snippet* snippet)
{
    if(snippet->isReadOnly()) {
        Utils::error(this, tr("This snipped can't be deleted")) ;
        return ;
    }
    bool isOk = true;
    if(deleteSnippetFromPersistence(snippet)) {
        if(!deleteSnippetFromUI(snippet, false)) {
            isOk = false;
        }
        _snippets.remove(snippet->id());
        delete snippet;
    } else {
        isOk = false ;
    }
    if(!isOk) {
        Utils::error(this, tr("An error occurred")) ;
    }
}

//togli lo s. elimina il tag padre sse e vuoto e non cmopreso nei nuovi tags.
bool SnippetHandler::deleteSnippetFromUI(Snippet* snippet, const bool shouldReInsert)
{
    bool isOk = true;
    foreach(QTreeWidgetItem * item, _snippetItems.values(snippet->id())) {
        QTreeWidgetItem *parent = item->parent();
        parent->takeChild(parent->indexOfChild(item));
        delete item ;
        QString tagLiteral = parent->data(COLUMN_DATA_TAG, Qt::UserRole).toString();
        if((parent->childCount() == 0)
                && (!shouldReInsert || (shouldReInsert && !snippet->tags().contains(tagLiteral)))) {
            int topLevelIndex = snippets->indexOfTopLevelItem(parent);
            if(topLevelIndex > -1) {
                snippets->takeTopLevelItem(topLevelIndex);
                delete parent;
                _topLevelItems.remove(tagLiteral);
            } else {
                isOk = false;
            }
        }
    } // foreach items

    // forget items
    _snippetItems.remove(snippet->id());

    /*if( !isOk ) { TODO
        Utils::error( this, tr("An error occurred") ) ;
    }*/
    return isOk ;
}


bool SnippetHandler::insertSnippetInUI(Snippet* snippet)
{
    //--------------- codice ----
    bool isOk = true;
    foreach(QString tag, snippet->tags()) {
        QTreeWidgetItem* tagItem ;
        if(! _topLevelItems.contains(tag)) {
            tagItem = new QTreeWidgetItem(snippets);
            if(NULL == tagItem) {
                isOk = false;
            } else {
                _topLevelItems.insert(tag, tagItem);
                tagItem->setText(0, tag);
                tagItem->setData(COLUMN_DATA_TAG, Qt::UserRole, tag);
                tagItem->setData(COLUMN_DATA_SNIPPET, Qt::UserRole, qVariantFromValue((void*)NULL));
                snippets->addTopLevelItem(tagItem);
            }
        } else {
            tagItem = _topLevelItems[tag];
        }
        // post top level processing
        QTreeWidgetItem* item = new QTreeWidgetItem(tagItem);
        if(NULL == item) {
            isOk = false;
        } else {
            item->setText(0, snippet->name());
            item->setText(1, snippet->description());
            tagItem->addChild(item);
            item->setData(COLUMN_DATA_TAG, Qt::UserRole, QVariant(""));
            item->setData(COLUMN_DATA_SNIPPET, Qt::UserRole, qVariantFromValue((void*)snippet));
            _snippetItems.insertMulti(snippet->id(), item);
        }
    } // foreach tags
    /*if( !isOk ) { TODO
       Utils::error( this, tr("An error occurred processing informations." ) ) ;
    }*/
    return isOk ;
}

void SnippetHandler::updateSnippetInUI(Snippet* snippet)
{
    bool isOk = true ;
    if(!deleteSnippetFromUI(snippet, true)) {
        isOk = false;
    }
    if(!insertSnippetInUI(snippet)) {
        isOk = false ;
    }
    if(!isOk) {
        Utils::error(this, tr("An error occurred")) ;
    }
}

void SnippetHandler::deleteCurrentSnippet()
{
    Snippet *snippet = getSelSnippet();
    if(NULL == snippet) {
        return ;
    }
    deleteSnippet(snippet);
}

void SnippetHandler::updateCurentSnippet()
{
    Snippet *snippet = getSelSnippet();
    if(NULL == snippet) {
        return ;
    }
    if(snippet->isReadOnly()) {
        Utils::error(this, tr("This snipped can't be modified.")) ;
        return ;
    }
    if(editSnippet(false, snippet)) {
        if(!persistSnippet(this, snippet)) {
            Utils::error(this, tr("Error saving snippet. Data not saved."));
        }
        updateSnippetInUI(snippet);
    }
}

void SnippetHandler::insertSnippet()
{
    Snippet *snippet = new Snippet();
    if(NULL == snippet) {
        Utils::error(this, tr("Unable to create new snippet."));
        return ;
    }

    if(editSnippet(true, snippet)) {
        if(!persistSnippet(this, snippet)) {
            Utils::error(this, tr("Error saving snippet. Data not saved."));
        }
        _snippets.insert(snippet->id(), snippet);
        updateSnippetInUI(snippet);
    }
}

void SnippetHandler::insertFragment(QWidget *parent, const QString &text)
{
    Snippet *snippet = new Snippet();
    if(NULL == snippet) {
        Utils::error(parent, tr("Unable to create new snippet."));
        return ;
    }
    snippet->setPayload(text);
    if(::editSnippet(true, snippet, parent)) {
        if(!persistSnippet(parent, snippet)) {
            Utils::error(parent, tr("Error saving snippet. Data not saved."));
        }
    }
}


bool SnippetHandler::persistSnippet(QWidget *parent, Snippet *snippet)
{
    QString dataDir = _data->snippetsLocalDir();
    QDir dir(dataDir);
    if(!dir.exists()) {
        if(!dir.mkpath(dataDir)) {
            Utils::error(parent, tr("Error creating data directory."));
            return false;
        }
    }
    QString filePath = buildFilePath(dataDir, snippet) ;
    // scrivi il nuovo con il nome vecchio+estensione
    QString newFilePath = filePath + ".new~" ;
    if(!snippet->save(newFilePath)) {
        Utils::error(parent, tr("Error saving data. Old file is still intact."));
        return false ;
    }
    // rinomina il vecchio
    QString backupFilePath = filePath + "~"  ;
    if(QFile::exists(backupFilePath)) {
        if(!QFile::remove(backupFilePath)) {
            Utils::error(parent, tr("Error saving data: cleaning backup file."));
            return false ;
        }
    }
    if(QFile::exists(filePath)) {
        if(!QFile::rename(filePath, backupFilePath)) {
            Utils::error(parent, tr("Error renaming old file. You can access written data at file '%1'. Old data are untouched").arg(newFilePath));
            return false ;
        }
    }
    // rinomina il nuovo nel nome vecchio
    if(!QFile::rename(newFilePath, filePath)) {
        Utils::error(parent, tr("Error renaming new file. You can access written data at file '%1'. You can find old data in the backup file").arg(newFilePath));
        return false ;
    }
    return true;
}

bool SnippetHandler::deleteSnippetFromPersistence(Snippet *snippet)
{
    QString dataDir = _data->snippetsLocalDir();
    QDir dir(dataDir);
    if(!dir.exists()) {
        if(!dir.mkpath(dataDir)) {
            Utils::error(this, tr("Error creating data directory."));
            return false;
        }
    }
    QString filePath = buildFilePath(dataDir, snippet);
    return snippet->remove(filePath);
}

bool SnippetHandler::editSnippet(const bool isInsert, Snippet *snippet)
{
#ifdef  _TEST
    QStringList list = snippet->tags();
    QStringList newList ;
    bool isFirst = true;
    foreach(QString s, list) {
        if(isFirst) {
            isFirst = false ;
            newList.append(s);
        } else {
            QString n = s + "_x";
            newList.append(n);
        }
    }
    snippet->setTags(newList);
    return true;
#endif
    return ::editSnippet(isInsert, snippet, this);
}

Snippet *SnippetHandler::getSelSnippet()
{
    if(snippets->selectedItems().size() > 0) {
        QTreeWidgetItem *item = snippets->selectedItems().at(0);
        // att ai top level TODO i top lvevel hanno un NULL
//        if(NULL != ui)
        {
            QVariant data = item->data(COLUMN_DATA_SNIPPET, Qt::UserRole);
            Snippet *snippet = (Snippet *)data.value<void*>();
            return snippet ;
        }
    }
    return NULL;
}


void SnippetHandler::on_newCmd_clicked()
{
    insertSnippet();
}

void SnippetHandler::on_modifyCmd_clicked()
{
    updateCurentSnippet();
}

void SnippetHandler::on_deleteCmd_clicked()
{
    deleteCurrentSnippet();
}

bool SnippetHandler::scanDirectory(const QString &dirName, const bool isReadOnly)
{
    bool isOK = true ;
    QDir dir(dirName);
    if(!dir.exists()) {
        return true;
    }
    dir.setFilter(QDir::Files);
    dir.setSorting(QDir::Name);
    QStringList names;
    names.append("*.xml");
    dir.setNameFilters(names);
    QFileInfoList fileList = dir.entryInfoList();
    foreach(QFileInfo info, fileList) {
        Snippet *snippet = new Snippet();
        if(NULL == snippet) {
            isOK = false;
        } else {
            snippet->setReadOnly(isReadOnly);
            if(!snippet->read(info.absoluteFilePath())) {
                isOK = false ;
                delete snippet;
            } else {
                _snippets.insert(snippet->id(), snippet);
            }
        }
    }
    return isOK;
}

void SnippetHandler::on_snippets_itemSelectionChanged()
{
    evaluateSelection();
}

void SnippetHandler::evaluateSelection()
{
    Snippet *snippet = getSelSnippet();
    if(_isEditMode) {
        bool isEnabledSel = false ;
        if(NULL != snippet) {
            isEnabledSel = !snippet->isReadOnly();
        }
        buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        buttonBox->button(QDialogButtonBox::Ok)->setVisible(false);
        buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(false);
        buttonBox->button(QDialogButtonBox::Cancel)->setVisible(false);
        buttonBox->button(QDialogButtonBox::Close)->setEnabled(true);
        buttonBox->button(QDialogButtonBox::Close)->setVisible(true);
        deleteCmd->setEnabled(isEnabledSel);
        modifyCmd->setEnabled(isEnabledSel);
    } else {
        bool isEnabledOk = false ;
        if(NULL != snippet) {
            isEnabledOk = true ;
        }
        buttonBox->button(QDialogButtonBox::Ok)->setEnabled(isEnabledOk);
        buttonBox->button(QDialogButtonBox::Ok)->setVisible(true);
        buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);
        buttonBox->button(QDialogButtonBox::Cancel)->setVisible(true);
        buttonBox->button(QDialogButtonBox::Close)->setEnabled(false);
        buttonBox->button(QDialogButtonBox::Close)->setVisible(false);
        deleteCmd->setEnabled(false);
        modifyCmd->setEnabled(false);
        newCmd->setEnabled(false);
        deleteCmd->setVisible(false);
        modifyCmd->setVisible(false);
        newCmd->setVisible(false);

    }
}

QString SnippetHandler::buildFilePath(const QString &dirPath, Snippet* snippet)
{
    QString filePath = dirPath + QDir::separator() + snippet->id() + ".xml";
    return filePath ;
}

void SnippetHandler::on_snippets_itemDoubleClicked(QTreeWidgetItem * /*item*/, int /*column*/)
{
    if(_isEditMode) {
        updateCurentSnippet();
    } else {
        accept();
    }
}
