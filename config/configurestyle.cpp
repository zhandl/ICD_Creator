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

#include "configurestyle.h"
#include "utils.h"
#include "config.h"
#include <QDir>
#include <QUrl>
#include <QDesktopServices>
#include "qxmleditdata.h"

ConfigureStyle::ConfigureStyle(QWidget *parent) :
    QWidget(parent),
    _data(NULL)
{
    setupUi();
    _group.addButton(pgmLocation);
    _group.addButton(pgmThisDirectory);
    _group.addButton(pgmDefault);
    //connect( &_group, SIGNAL(buttonClicked ( QAbstractButton * button )), this, SLOT(buttonClicked ( QAbstractButton * button )) );
}

ConfigureStyle::~ConfigureStyle()
{
}

void ConfigureStyle::setupUi()
{
    if (objectName().isEmpty())
        setObjectName(QString::fromUtf8("ConfigureStyle"));
    resize(584, 427);
    verticalLayout = new QVBoxLayout(this);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    label = new QLabel(this);
    label->setObjectName(QString::fromUtf8("label"));
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
    label->setSizePolicy(sizePolicy);
    QFont font;
    font.setBold(true);
    font.setWeight(75);
    label->setFont(font);
    label->setAlignment(Qt::AlignCenter);

    verticalLayout->addWidget(label);

    pgmLocation = new QRadioButton(this);
    pgmLocation->setObjectName(QString::fromUtf8("pgmLocation"));

    verticalLayout->addWidget(pgmLocation);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer);

    label_2 = new QLabel(this);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

    horizontalLayout->addWidget(label_2);

    pgmDirValue = new QLabel(this);
    pgmDirValue->setObjectName(QString::fromUtf8("pgmDirValue"));
    QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(pgmDirValue->sizePolicy().hasHeightForWidth());
    pgmDirValue->setSizePolicy(sizePolicy1);
    QFont font1;
    font1.setBold(false);
    font1.setItalic(true);
    font1.setWeight(50);
    pgmDirValue->setFont(font1);
    pgmDirValue->setMouseTracking(false);
    pgmDirValue->setFrameShape(QFrame::NoFrame);
    pgmDirValue->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

    horizontalLayout->addWidget(pgmDirValue);


    verticalLayout->addLayout(horizontalLayout);

    pgmDefault = new QRadioButton(this);
    pgmDefault->setObjectName(QString::fromUtf8("pgmDefault"));

    verticalLayout->addWidget(pgmDefault);

    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

    horizontalLayout_2->addItem(horizontalSpacer_2);

    label_3 = new QLabel(this);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

    horizontalLayout_2->addWidget(label_3);

    stdDirValue = new QLabel(this);
    stdDirValue->setObjectName(QString::fromUtf8("stdDirValue"));
    sizePolicy1.setHeightForWidth(stdDirValue->sizePolicy().hasHeightForWidth());
    stdDirValue->setSizePolicy(sizePolicy1);
    QFont font2;
    font2.setItalic(true);
    stdDirValue->setFont(font2);
    stdDirValue->setFrameShape(QFrame::NoFrame);
    stdDirValue->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

    horizontalLayout_2->addWidget(stdDirValue);


    verticalLayout->addLayout(horizontalLayout_2);

    pgmThisDirectory = new QRadioButton(this);
    pgmThisDirectory->setObjectName(QString::fromUtf8("pgmThisDirectory"));

    verticalLayout->addWidget(pgmThisDirectory);

    horizontalLayout_3 = new QHBoxLayout();
    horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
    horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

    horizontalLayout_3->addItem(horizontalSpacer_3);

    aDirectory = new QLineEdit(this);
    aDirectory->setObjectName(QString::fromUtf8("aDirectory"));
    QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(aDirectory->sizePolicy().hasHeightForWidth());
    aDirectory->setSizePolicy(sizePolicy2);

    horizontalLayout_3->addWidget(aDirectory);


    verticalLayout->addLayout(horizontalLayout_3);

    horizontalLayout_4 = new QHBoxLayout();
    horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
    horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_4->addItem(horizontalSpacer_4);

    openLocation = new QPushButton(this);
    openLocation->setObjectName(QString::fromUtf8("openLocation"));

    horizontalLayout_4->addWidget(openLocation);


    verticalLayout->addLayout(horizontalLayout_4);

    label_4 = new QLabel(this);
    label_4->setObjectName(QString::fromUtf8("label_4"));
    sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
    label_4->setSizePolicy(sizePolicy1);

    verticalLayout->addWidget(label_4);


    retranslateUi();

    QMetaObject::connectSlotsByName(this);
}

void ConfigureStyle::retranslateUi()
{
    setWindowTitle(QApplication::translate("ConfigureStyle", "Form", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("ConfigureStyle", "Style Files Location", 0, QApplication::UnicodeUTF8));
    pgmLocation->setText(QApplication::translate("ConfigureStyle", "Use the &program directory", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("ConfigureStyle", "value:", 0, QApplication::UnicodeUTF8));
    pgmDirValue->setText(QApplication::translate("ConfigureStyle", "-", 0, QApplication::UnicodeUTF8));
    pgmDefault->setText(QApplication::translate("ConfigureStyle", "Use the &standard Operating System location", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("ConfigureStyle", "value:", 0, QApplication::UnicodeUTF8));
    stdDirValue->setText(QApplication::translate("ConfigureStyle", "-", 0, QApplication::UnicodeUTF8));
    pgmThisDirectory->setText(QApplication::translate("ConfigureStyle", "Use the &following directory:", 0, QApplication::UnicodeUTF8));
    openLocation->setText(QApplication::translate("ConfigureStyle", "&Open Location in the Browser", 0, QApplication::UnicodeUTF8));
    label_4->setText(QApplication::translate("ConfigureStyle", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Arial'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<table border=\"0\" style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; font-weight:600;\">Warning</span><span style=\" font-size:9pt;\">: changes will be applied only after a program restart.</span></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
}

void ConfigureStyle::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch(e->type()) {
    case QEvent::LanguageChange:
        retranslateUi();
        break;
    default:
        break;
    }
}


void ConfigureStyle::init(QXmlEditData *data)
{
    _data = data;
    QString stylesDirectory = _data->getStylesDirSpecific();
    aDirectory->setText(stylesDirectory);
    stylesDirectory = _data->getStylesDirStandard();
    stdDirValue->setText(stylesDirectory);
    stylesDirectory = _data->getStylesDirApplication();
    pgmDirValue->setText(stylesDirectory);
    EStylesDir type = _data->getStylesDirLocation();
    switch(type) {
    case ESTYLE_DIR_USEAPPL:
        pgmLocation->setChecked(true);
        break;
    case ESTYLE_DIR_USEDIR:
        pgmThisDirectory->setChecked(true);
        break;
    default:
        pgmDefault->setChecked(true);
        break;
    }
}


void ConfigureStyle::save()
{
    if(pgmLocation->isChecked()) {
        _data->setStylesDirLocation(ESTYLE_DIR_USEAPPL);
    } else if(pgmThisDirectory->isChecked()) {
        QString dir = aDirectory->text();
        if(dir.isEmpty()) {
            Utils::error(tr("Data directory not specified"));
            return ;
        }
        _data->setStylesDirLocation(ESTYLE_DIR_USEDIR);
        Config::saveString(Config::KEY_STYLE_DATADIR, dir);
    } else {
        _data->setStylesDirLocation(ESTYLE_DIR_USESTD);
    }
}

void ConfigureStyle::saveIfChanged()
{
    save();
}

void ConfigureStyle::on_openLocation_clicked()
{
    bool isOk = false;
    if(pgmLocation->isChecked()) {
        QDir dir(_data->getStylesDirApplication());
        if(!dir.exists()) {
            dir.mkpath(_data->getStylesDirApplication());
        }
        isOk = QDesktopServices::openUrl(QUrl::fromLocalFile(_data->getStylesDirApplication()));
    } else if(pgmThisDirectory->isChecked()) {
        if(aDirectory->text().isEmpty()) {
            Utils::error(this, tr("The directory name is empty."));
            return ;
        }
        isOk = QDesktopServices::openUrl(QUrl::fromLocalFile(aDirectory->text()));
    } else {
        QDir dir(_data->getStylesDirStandard());
        if(!dir.exists()) {
            dir.mkpath(_data->getStylesDirStandard());
        }
        isOk = QDesktopServices::openUrl(QUrl::fromLocalFile(_data->getStylesDirStandard()));
    }
    if(!isOk) {
        Utils::error(this, tr("An error occurred while opening location."));
    }
}

