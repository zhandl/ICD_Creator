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

#ifndef CONFIGVALIDATION_H
#define CONFIGVALIDATION_H

#include <QWidget>
#include "global.h"
#include "qxmleditdata.h"

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class ConfigValidation : public QWidget
{
    Q_OBJECT

    QXmlEditData *_data;

public:
    explicit ConfigValidation(QWidget *parent = 0);
    ~ConfigValidation();

    void init(QXmlEditData *data);
    void saveIfChanged();

private:

    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QCheckBox *chbAutomaticValidationLoading;
    QCheckBox *chkEnableDiskCache;
    QLabel *label;
    QLineEdit *extValidationProgram;
    QSpacerItem *verticalSpacer_4;

    void setupUi();
    void retranslateUi();

    void save();
};

#endif // CONFIGVALIDATION_H
