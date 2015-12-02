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

#ifndef SNIPPETHANDLER_H
#define SNIPPETHANDLER_H

#include <QDialog>
#include <QMap>

#include "snippet.h"
#include "dommodel.h"
#include "qxmleditdata.h"

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>


class SnippetHandler : public QDialog
{
    Q_OBJECT
public:
    SnippetHandler(QXmlEditData *data, const bool setEditMode, QWidget *parent = 0);
    ~SnippetHandler();

    DomModel *model();

    void insertFragment(QWidget *parent, const QString &text);

protected:
    void changeEvent(QEvent *e);
    void loadSnippets();
    void accept();
    void fillTree();
    void refineUI();

private:

    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QTreeWidget *snippets;
    QVBoxLayout *verticalLayout_2;
    QDialogButtonBox *buttonBox;
    QSpacerItem *verticalSpacer;
    QPushButton *newCmd;
    QPushButton *modifyCmd;
    QPushButton *deleteCmd;
    QSpacerItem *verticalSpacer_2;

    void init();
    void retranslateUi();

    bool _isEditMode;
    QMap<QString, Snippet*> _snippets;
    QMultiMap<QString, QTreeWidgetItem*> _snippetItems;
    QMap<QString, QTreeWidgetItem*> _topLevelItems;
    DomModel *_model;
    QXmlEditData *_data;


    //-------------- methods -------------------
    void deleteSnippet(Snippet* snippet);


    void updateSnippetInUI(Snippet* snippet);
    bool deleteSnippetFromUI(Snippet* snippet, const bool shouldReInsert);
    bool insertSnippetInUI(Snippet* snippet);

    bool deleteSnippetFromPersistence(Snippet *snippet);
    bool persistSnippet(QWidget *parent, Snippet *snippet);

    void insertSnippet();
    void updateCurentSnippet();
    void deleteCurrentSnippet();

    Snippet *getSelSnippet();
    bool editSnippet(const bool isInsert, Snippet *snippet);
    bool scanDirectory(const QString &dirName, const bool isReadOnly);

    void evaluateSelection();
    QString buildFilePath(const QString &dirPath, Snippet* snippet);


private slots:
    void on_newCmd_clicked();
    void on_modifyCmd_clicked();
    void on_deleteCmd_clicked();
    void on_snippets_itemSelectionChanged();
    void on_snippets_itemDoubleClicked(QTreeWidgetItem * item, int column);

};

#endif // SNIPPETHANDLER_H
