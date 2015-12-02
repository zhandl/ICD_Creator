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


#ifndef CONFIGURATIONDIALOG_H
#define CONFIGURATIONDIALOG_H

#include <QDialog>
#include <QIcon>

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>

#include "config/configurestyle.h"
#include "config/configvalidation.h"
#include "config/configurationgeneraloptions.h"


class ConfigurationDialog : public QDialog
{
    Q_OBJECT

    enum ETabs {
        TAB_GENERAL = 0,
        TAB_STYLE ,
        TAB_VALIDATION,
        TAB_SESSIONS
    };

    QXmlEditData *_data;

    ConfigurationGeneralOptions *_generalOptions;
    ConfigureStyle  *_configureStyle;
    ConfigValidation* _configureValidation;

    QIcon generalIcon;
    QIcon styleIcon;
    QIcon validationIcon;
    QIcon sessionsIcon;

    void setTab(const ETabs tab, QWidget *widget, QIcon &icon, const QString &title, const QString &tooltip);
    void init(QXmlEditData *data);

public:
    explicit ConfigurationDialog(QXmlEditData *data, QWidget *parent = 0);
    ~ConfigurationDialog();

    static void doOptions(QWidget * const parentWindow, QXmlEditData *data);

private:

    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QDialogButtonBox *buttonBox;


    void setupUi();
    void retranslateUi();

private slots:
    void on_buttonBox_accepted();
    void accept();
};

#endif // CONFIGURATIONDIALOG_H
