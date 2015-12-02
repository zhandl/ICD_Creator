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
#include "editsnippet.h"
#include "utils.h"

#define MAXCHARS_NAME   40
#define MAXCHARS_DESCR  100


bool editSnippet(const bool isInsert, Snippet *snippet, QWidget *parent)
{
    EditSnippet editDialog(isInsert, snippet, parent);
    editDialog.setModal(true);
    if(editDialog.exec() == QDialog::Accepted) {
        return true;
    }
    return false ;
}

EditSnippet::EditSnippet(const bool isInsert, Snippet *snippet, QWidget *parent) :
    QDialog(parent),
    _snippet(snippet),
    _isInsert(isInsert)
{
    init();
    name->setMaxLength(MAXCHARS_NAME);
    description->setMaxLength(MAXCHARS_DESCR);
    setUpData();
}

EditSnippet::~EditSnippet()
{

}

void EditSnippet::init()
{
    if (objectName().isEmpty())
        setObjectName(QString::fromUtf8("EditSnippet"));
    resize(562, 528);
    horizontalLayout_2 = new QHBoxLayout(this);
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    verticalLayout_2 = new QVBoxLayout();
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    verticalLayout = new QVBoxLayout();
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    label = new QLabel(this);
    label->setObjectName(QString::fromUtf8("label"));

    verticalLayout->addWidget(label);

    name = new QLineEdit(this);
    name->setObjectName(QString::fromUtf8("name"));
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(name->sizePolicy().hasHeightForWidth());
    name->setSizePolicy(sizePolicy);
    name->setMaxLength(40);

    verticalLayout->addWidget(name);

    label_2 = new QLabel(this);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    verticalLayout->addWidget(label_2);

    description = new QLineEdit(this);
    description->setObjectName(QString::fromUtf8("description"));

    verticalLayout->addWidget(description);

    label_3 = new QLabel(this);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    verticalLayout->addWidget(label_3);

    tags = new QLineEdit(this);
    tags->setObjectName(QString::fromUtf8("tags"));

    verticalLayout->addWidget(tags);


    verticalLayout_2->addLayout(verticalLayout);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    label_5 = new QLabel(this);
    label_5->setObjectName(QString::fromUtf8("label_5"));

    horizontalLayout->addWidget(label_5);

    creationDate = new QLabel(this);
    creationDate->setObjectName(QString::fromUtf8("creationDate"));

    horizontalLayout->addWidget(creationDate);

    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer);

    label_6 = new QLabel(this);
    label_6->setObjectName(QString::fromUtf8("label_6"));

    horizontalLayout->addWidget(label_6);

    updateDate = new QLabel(this);
    updateDate->setObjectName(QString::fromUtf8("updateDate"));
    QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(updateDate->sizePolicy().hasHeightForWidth());
    updateDate->setSizePolicy(sizePolicy1);

    horizontalLayout->addWidget(updateDate);


    verticalLayout_2->addLayout(horizontalLayout);

    label_4 = new QLabel(this);
    label_4->setObjectName(QString::fromUtf8("label_4"));

    verticalLayout_2->addWidget(label_4);

    payload = new QPlainTextEdit(this);
    payload->setObjectName(QString::fromUtf8("payload"));

    verticalLayout_2->addWidget(payload);


    horizontalLayout_2->addLayout(verticalLayout_2);

    verticalLayout_3 = new QVBoxLayout();
    verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    sizePolicy.setHeightForWidth(buttonBox->sizePolicy().hasHeightForWidth());
    buttonBox->setSizePolicy(sizePolicy);
    buttonBox->setOrientation(Qt::Vertical);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    buttonBox->setCenterButtons(true);

    verticalLayout_3->addWidget(buttonBox);

    verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout_3->addItem(verticalSpacer);


    horizontalLayout_2->addLayout(verticalLayout_3);

#ifndef QT_NO_SHORTCUT
    label->setBuddy(name);
    label_2->setBuddy(description);
    label_3->setBuddy(tags);
    label_4->setBuddy(payload);
#endif // QT_NO_SHORTCUT

    retranslateUi();
    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QMetaObject::connectSlotsByName(this);
}

void EditSnippet::retranslateUi()
{
    setWindowTitle(QApplication::translate("EditSnippet", "Edit XML Snippet", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("EditSnippet", "&Name:", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("EditSnippet", "&Description:", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("EditSnippet", "&Tags (comma separed:)", 0, QApplication::UnicodeUTF8));
    label_5->setText(QApplication::translate("EditSnippet", "created on:", 0, QApplication::UnicodeUTF8));
    creationDate->setText(QApplication::translate("EditSnippet", "------", 0, QApplication::UnicodeUTF8));
    label_6->setText(QApplication::translate("EditSnippet", "last modified on:", 0, QApplication::UnicodeUTF8));
    updateDate->setText(QApplication::translate("EditSnippet", "---", 0, QApplication::UnicodeUTF8));
    label_4->setText(QApplication::translate("EditSnippet", "&Snippet", 0, QApplication::UnicodeUTF8));
}

void EditSnippet::changeEvent(QEvent *e)
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


bool EditSnippet::areDataOK()
{
    if(name->text().trimmed().isEmpty()
            ||  description->text().isEmpty()
            ||  tags->text().trimmed().isEmpty()
            ||  payload->toPlainText().trimmed().isEmpty()) {
        return false;
    }
    return true;
}

void EditSnippet::setUpData()
{
    name->setText(_snippet->name());
    description->setText(_snippet->description());
    payload->setPlainText(_snippet->payload());
    // convert tags in qstring
    tags->setText(_snippet->tags().join(","));
    creationDate->setText(_snippet->creationDate().toString());
    updateDate->setText(_snippet->updateDate().toString());
}

void EditSnippet::accept()
{
    // save data into snippet
    QStringList uiTags = tags->text().trimmed().split(',');
    QStringList newTags;
    foreach(QString tg, uiTags) {
        QString tx = tg.trimmed();
        if(!tx.isEmpty()) {
            newTags.append(tx);
        }
    }

    //check data consistency
    if(!areDataOK() || newTags.isEmpty()) {
        Utils::error(this, tr("Mandatory fields empty or invalid."));
        return ;
    }

    _snippet->setName(name->text().trimmed());
    _snippet->setDescription(description->text().trimmed());
    _snippet->setPayload(payload->toPlainText().trimmed());

    _snippet->setTags(newTags);

    //snippet->setUpdateUser(getUser());
    QDateTime now = QDateTime::currentDateTime() ;
    _snippet->setUpdateDate(now);
    if(_isInsert) {
        //snippet->setCreationUser(getUser());
        _snippet->setCreationDate(now);
    }
    QDialog::accept();
}
