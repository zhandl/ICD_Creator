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

#ifndef SEARCHINFILES_H
#define SEARCHINFILES_H

#include <QDialog>
#include <QIcon>

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>

#include "scansax.h"


class SearchInFiles : public QDialog
{
    Q_OBJECT

    volatile bool running;
    QStringList previousSearch ;
    XmlScanInfo info;
    QIcon numberIcon;
    QIcon groupIcon;

public:
    explicit SearchInFiles(QWidget *parent = 0);
    ~SearchInFiles();

private:

    QVBoxLayout *verticalLayout_2;
    QFrame *frame;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QComboBox *pattern2Search;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QLineEdit *filePath;
    QPushButton *cmdOpenFile;
    QCheckBox *groupChk;
    QProgressBar *progressBar;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *cmdCancel;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *cmdStart;
    QSpacerItem *horizontalSpacer_4;
    QTableWidget *results;
    QDialogButtonBox *buttonBox;

    void init();
    void retranslateUi();

    void startProcessing();
    void endOfSearch();
    void enableButtons(const bool how);
    void clearTable();


    static void searchInFileWorking(volatile bool *running, XmlScanInfo *info, const QString &filePath) ;

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_cmdStart_clicked();
    void on_cmdCancel_clicked();
    void on_cmdOpenFile_clicked();

    void checkIfDone();
    void accept();
    void reject();

};



#endif // SEARCHINFILES_H
