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
/*****************************************************************************************************
the procedure to make classification work is based on the fact that the items of the
path are visited in order.
Initially all the counters are set to zero.
When we encounter the father , we reset the child
When we run into an end element, we close the item-1 counting and we reset the item
Next time we access an element, all counters are consitent.
*******************************************************************************************************/

#include "searchinfiles.h"
#include <QThreadPool>
#include "utils.h"
#include "config.h"
#include <QFileDialog>
#include <QLineEdit>
#include <QtConcurrentRun>
#include <QCloseEvent>
#include <QTimer>

const int POLL_TIMEOUT = 500 ;
const int MAX_PATTERN_SIZE = 10 ;

void searchInFiles(QWidget * parent)
{
    SearchInFiles edit(parent);
    edit.exec() ;
}


SearchInFiles::SearchInFiles(QWidget *parent) :
    QDialog(parent)
{
    numberIcon.addPixmap(QPixmap(QString::fromUtf8(":/editText/number")), QIcon::Normal, QIcon::Off);
    groupIcon.addPixmap(QPixmap(QString::fromUtf8(":/editText/group")), QIcon::Normal, QIcon::Off);
    running = false ;
    init();
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    if(Config::loadStringArray(Config::KEY_SEARCHINFILES_INPUTFILE, previousSearch)) {
        foreach(QString item, previousSearch) {
            pattern2Search->addItem(item);
        }
    }
    filePath->setText(Config::getString(Config::KEY_SEARCHINFILES_PATTERN, ""));
    progressBar->setTextVisible(false);
    groupChk->setChecked(Config::getBool(Config::KEY_SEARCHINFILES_GROUP, false));
    enableButtons(true);
    clearTable();
}

SearchInFiles::~SearchInFiles()
{
}

void SearchInFiles::init()
{
    if (objectName().isEmpty())
        setObjectName(QString::fromUtf8("SearchInFiles"));
    resize(575, 449);
    verticalLayout_2 = new QVBoxLayout(this);
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    frame = new QFrame(this);
    frame->setObjectName(QString::fromUtf8("frame"));
    frame->setFrameShape(QFrame::NoFrame);
    frame->setFrameShadow(QFrame::Plain);
    verticalLayout_3 = new QVBoxLayout(frame);
    verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
    verticalLayout = new QVBoxLayout();
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    label = new QLabel(frame);
    label->setObjectName(QString::fromUtf8("label"));

    verticalLayout->addWidget(label);

    pattern2Search = new QComboBox(frame);
    pattern2Search->setObjectName(QString::fromUtf8("pattern2Search"));
    pattern2Search->setEditable(true);
    pattern2Search->setMaxVisibleItems(16);

    verticalLayout->addWidget(pattern2Search);

    label_2 = new QLabel(frame);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    verticalLayout->addWidget(label_2);


    verticalLayout_3->addLayout(verticalLayout);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    label_3 = new QLabel(frame);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    horizontalLayout->addWidget(label_3);

    filePath = new QLineEdit(frame);
    filePath->setObjectName(QString::fromUtf8("filePath"));

    horizontalLayout->addWidget(filePath);

    cmdOpenFile = new QPushButton(frame);
    cmdOpenFile->setObjectName(QString::fromUtf8("cmdOpenFile"));
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/open/images/document-open.png"), QSize(), QIcon::Normal, QIcon::Off);
    cmdOpenFile->setIcon(icon);

    horizontalLayout->addWidget(cmdOpenFile);


    verticalLayout_3->addLayout(horizontalLayout);


    verticalLayout_2->addWidget(frame);

    groupChk = new QCheckBox(this);
    groupChk->setObjectName(QString::fromUtf8("groupChk"));

    verticalLayout_2->addWidget(groupChk);

    progressBar = new QProgressBar(this);
    progressBar->setObjectName(QString::fromUtf8("progressBar"));
    progressBar->setValue(24);
    progressBar->setInvertedAppearance(false);

    verticalLayout_2->addWidget(progressBar);

    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_2->addItem(horizontalSpacer);

    cmdCancel = new QPushButton(this);
    cmdCancel->setObjectName(QString::fromUtf8("cmdCancel"));
    cmdCancel->setEnabled(false);

    horizontalLayout_2->addWidget(cmdCancel);

    horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_2->addItem(horizontalSpacer_2);


    verticalLayout_2->addLayout(horizontalLayout_2);

    horizontalLayout_3 = new QHBoxLayout();
    horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
    horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_3->addItem(horizontalSpacer_3);

    cmdStart = new QPushButton(this);
    cmdStart->setObjectName(QString::fromUtf8("cmdStart"));

    horizontalLayout_3->addWidget(cmdStart);

    horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_3->addItem(horizontalSpacer_4);


    verticalLayout_2->addLayout(horizontalLayout_3);

    results = new QTableWidget(this);
    results->setObjectName(QString::fromUtf8("results"));
    results->setSelectionMode(QAbstractItemView::SingleSelection);
    results->setSelectionBehavior(QAbstractItemView::SelectRows);
    results->setGridStyle(Qt::DotLine);

    verticalLayout_2->addWidget(results);

    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Close);

    verticalLayout_2->addWidget(buttonBox);


    retranslateUi();
    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QMetaObject::connectSlotsByName(this);
}

void SearchInFiles::retranslateUi()
{
    setWindowTitle(QApplication::translate("SearchInFiles", "Search in files", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("SearchInFiles", "Pattern to search in files:", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("SearchInFiles", "hint: the pattern to search is like this: /a/b/c", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("SearchInFiles", "File path:", 0, QApplication::UnicodeUTF8));
    cmdOpenFile->setText(QString());
    groupChk->setText(QApplication::translate("SearchInFiles", "&Grouping", 0, QApplication::UnicodeUTF8));
    groupChk->setShortcut(QApplication::translate("SearchInFiles", "Alt+G", 0, QApplication::UnicodeUTF8));
    cmdCancel->setText(QApplication::translate("SearchInFiles", "Cancel", 0, QApplication::UnicodeUTF8));
    cmdStart->setText(QApplication::translate("SearchInFiles", "Start", 0, QApplication::UnicodeUTF8));
}

void SearchInFiles::clearTable()
{
    results->clear();
    results->setColumnCount(2);
    results->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("Item")));
    results->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("Occurrences")));
}


void SearchInFiles::on_cmdOpenFile_clicked()
{
    QString newfilePath = QFileDialog::getOpenFileName(this, tr("File to scan"),
                       filePath->text(), tr("XML files (*.xml);;All files (*);;"));
    if(!newfilePath.isEmpty()) {
        filePath->setText(newfilePath);
    }
}

void SearchInFiles::on_cmdStart_clicked()
{
    startProcessing();
}

void SearchInFiles::on_cmdCancel_clicked()
{
    if(running) {
        info.isAbort = true ;
        if(QThreadPool::globalInstance()->activeThreadCount() > 0) {
            QThreadPool::globalInstance()->waitForDone();
        }
        enableButtons(false);
        running = false ;
    }
}


void SearchInFiles::startProcessing()
{
    bool isGroup = groupChk->isChecked() ;
    QString pattern = pattern2Search->currentText();
    if(!info.init(pattern, isGroup)) {
        Utils::error(tr("Unable to begin the search"));
        return ;
    }
    if(!info.check()) {
        Utils::error(tr("The pattern to search is not well formed."));
        return ;
    }

    Config::saveString(Config::KEY_SEARCHINFILES_PATTERN, filePath->text());

    if(!previousSearch.contains(pattern)) {
        previousSearch.insert(0, pattern);
        if(previousSearch.size() > MAX_PATTERN_SIZE) {
            previousSearch.removeAt(previousSearch.size() - 1);
        }
        Config::saveStringArray(Config::KEY_SEARCHINFILES_INPUTFILE, previousSearch);
    }

    Config::saveBool(Config::KEY_SEARCHINFILES_GROUP, isGroup);
    clearTable();

    enableButtons(false);
    running = true ;
    /*QFuture<void> future = */QtConcurrent::run(searchInFileWorking, &running, &info, filePath->text());

    checkIfDone();
}

void SearchInFiles::closeEvent(QCloseEvent *event)
{
    on_cmdCancel_clicked();
    event->accept();
}

void SearchInFiles::checkIfDone()
{
    QThreadPool *gInst = QThreadPool::globalInstance();
    if(gInst->activeThreadCount() > 0) {
        QTimer::singleShot(POLL_TIMEOUT, this, SLOT(checkIfDone()));
        progressBar->setValue((progressBar->value() + 5) % 100);
    } else {
        endOfSearch();
    }
}

void SearchInFiles::enableButtons(const bool how)
{
    cmdStart->setEnabled(how);
    cmdStart->setVisible(how);
    cmdCancel->setEnabled(!how);
    cmdCancel->setVisible(!how);
    progressBar->setVisible(!how);
    progressBar->setValue(0);
    frame->setEnabled(how);
}

void SearchInFiles::endOfSearch()
{
    running = false;
    enableButtons(true);
    clearTable();
    if(! info.isError && !info.isAbort) {
        int numRows = info.size ;
        results->setRowCount(numRows);
        for(int i = 0 ; i < info.size ; i ++) {
            results->setItem(i, 0, new QTableWidgetItem(numberIcon, info.tokens.at(i))) ;
            results->setItem(i, 1, new QTableWidgetItem(QString("%1\n").arg(info.occurrences[i])));
        }
        int index = numRows;
        if(info.isGroup) {
            for(int i = 0 ; i < info.size ; i ++) {
                numRows += info.groups[i].count();
                results->setRowCount(numRows);
                QMapIterator<int, int> iterator(info.groups[i]);
                // build the string
                QString itemId ;
                for(int ic = 0 ; ic <= i ; ic ++) {
                    itemId += "/" ;
                    itemId += info.tokens.at(ic) ;
                }
                while(iterator.hasNext()) {
                    iterator.next();
                    results->setItem(index, 0, new QTableWidgetItem(groupIcon,  tr("Gr.%1 - %2 having count: %3").arg(i).arg(itemId).arg(iterator.key())));
                    results->setItem(index, 1, new QTableWidgetItem(QString("%1\n").arg(iterator.value())));
                    index ++ ;
                }
            }
        }
        results->resizeColumnsToContents();
        results->resizeRowsToContents();
    } else {
        if(info.isAbort) {
            Utils::message(tr("Operation aborted by user."));
        } else if(info.isError) {
            Utils::error(tr("Operation interrupted with error :'%1'").arg(info.errorMessage));
        }
    }
}

void SearchInFiles::searchInFileWorking(volatile bool *running, XmlScanInfo *info, const QString &filePath)
{
    if(!*running) {
        info->isError = true ;
        return  ;
    }

    ScanSax handler(*info);
    QXmlSimpleReader reader;
    reader.setFeature("http://xml.org/sax/features/namespaces", false);
    reader.setFeature("http://xml.org/sax/features/namespace-prefixes", true);
    reader.setContentHandler(&handler);
    reader.setErrorHandler(&handler);

    QFile file(filePath);
    if(!file.open(QFile::ReadOnly | QFile::Text)) {
        info->isError = true ;
        info->errorMessage = tr("Error opening input file.");
        return ;
    }
    QXmlInputSource xmlInput(&file);
    if(!reader.parse(xmlInput)) {
        info->isError = true ;
    }
    file.close();
    return ;
}


void SearchInFiles::accept()
{
    on_cmdCancel_clicked();
    QDialog::accept();
}

void SearchInFiles::reject()
{
    on_cmdCancel_clicked();
    QDialog::reject();
}
