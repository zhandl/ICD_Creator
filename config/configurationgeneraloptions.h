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

#ifndef CONFIGURATIONGENERALOPTIONS_H
#define CONFIGURATIONGENERALOPTIONS_H

#include <QWidget>
#include "global.h"
#include "qxmleditdata.h"

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QFontComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>


class ConfigurationGeneralOptions : public QWidget
{
    Q_OBJECT

    QXmlEditData *_data;
    QString _elementFontName;
    int _elementFontSize;
    bool _elementFontItalic;
    bool _elementFontBold;
    bool _started;

public:
    explicit ConfigurationGeneralOptions(QWidget *parent = 0);
    ~ConfigurationGeneralOptions();

    void init(QXmlEditData *data);
    void checkEnablingStatus();
    void setElementFontInfo();
    void saveIfChanged();

private:

    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QVBoxLayout *verticalLayout;
    QCheckBox *showWelcomePage;
    QCheckBox *autoscroll;
    QLabel *label_2;
    QGridLayout *gridLayout;
    QCheckBox *enableEFontSize;
    QLabel *elementFontSummary;
    QPushButton *changeElementsFont;
    QCheckBox *enableFWAFont;
    QFontComboBox *fixedSizeAttrComboFont;
    QHBoxLayout *horizontalLayout;
    QLabel *label_4;
    QSpinBox *fixedSizeAttributeFontSize;
    QCheckBox *enableAdvancedAttributesDisplay;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *enableLogs;
    QSpacerItem *horizontalSpacer;
    QLabel *label_3;
    QComboBox *logLevelCombo;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *expandTreeAfterLoad;
    QLabel *label_7;

    void setupUi();
    void retranslateUi();

    void save();
private slots:
    void on_fixedSizeAttributeFontSize_valueChanged(int value);
    void on_enableFWAFont_stateChanged(int state);
    void on_fixedSizeAttrComboFont_currentFontChanged(const QFont & font);
    void on_enableAdvancedAttributesDisplay_stateChanged(int status);
    void on_changeElementsFont_clicked();
    void on_enableEFontSize_stateChanged(int state);
    void on_enableLogs_stateChanged(int state);
    void on_logLevelCombo_currentIndexChanged(int index);
};

#endif // CONFIGURATIONGENERALOPTIONS_H
