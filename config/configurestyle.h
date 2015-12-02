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
#ifndef CONFIGURESTYLE_H
#define CONFIGURESTYLE_H

#include <QWidget>
#include "global.h"
#include "qxmleditdata.h"

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>


class ConfigureStyle : public QWidget
{
    Q_OBJECT

    QButtonGroup _group;
    QXmlEditData *_data;

public:
    explicit ConfigureStyle(QWidget *parent = 0);
    ~ConfigureStyle();

    void init(QXmlEditData *data);
    void saveIfChanged();

protected:
    void changeEvent(QEvent *e);

private:

    QVBoxLayout *verticalLayout;
    QLabel *label;
    QRadioButton *pgmLocation;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QLabel *pgmDirValue;
    QRadioButton *pgmDefault;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_3;
    QLabel *stdDirValue;
    QRadioButton *pgmThisDirectory;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *aDirectory;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *openLocation;
    QLabel *label_4;

    void setupUi();
    void retranslateUi();

    void save();

private slots:
    void on_openLocation_clicked();

};

#endif // CONFIGURESTYLE_H
