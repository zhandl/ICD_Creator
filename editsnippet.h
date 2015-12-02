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
#ifndef EDITSNIPPET_H
#define EDITSNIPPET_H

#include <QDialog>
#include <QHash>
#include "snippet.h"

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

class EditSnippet : public QDialog
{
    Q_OBJECT
public:
    EditSnippet(const bool isInsert, Snippet *snippet, QWidget *parent = 0);
    ~EditSnippet();

protected:
    void changeEvent(QEvent *e);

private:

    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *name;
    QLabel *label_2;
    QLineEdit *description;
    QLabel *label_3;
    QLineEdit *tags;
    QHBoxLayout *horizontalLayout;
    QLabel *label_5;
    QLabel *creationDate;
    QSpacerItem *horizontalSpacer;
    QLabel *label_6;
    QLabel *updateDate;
    QLabel *label_4;
    QPlainTextEdit *payload;
    QVBoxLayout *verticalLayout_3;
    QDialogButtonBox *buttonBox;
    QSpacerItem *verticalSpacer;

    void init();
    void retranslateUi();

    Snippet* _snippet ;
    bool _isInsert;


    bool areDataOK();
    void setUpData();
    void accept();
};

bool editSnippet(const bool isInsert, Snippet *snippet, QWidget *parent);

#endif // EDITSNIPPET_H
