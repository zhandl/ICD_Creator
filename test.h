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

#ifndef TEST_H
#define TEST_H

#include <QWidget>
#include <QtGui>
#include "dommodel.h"
#include "global.h"

class LIBQXMLEDITSHARED_EXPORT   Test
{
    Q_DECLARE_TR_FUNCTIONS(Test)

    DomModel *loadRule(const QString &filePath);
    bool testSaveAs(QWidget *parent, DomModel *source);
    bool testFailure(QWidget *parent, DomModel *source);
    bool testCopyAndPaste(QWidget *parent);

public:
    Test();
    ~Test();

    void doTest(QWidget *parent);
    static void executeTests(QWidget *parent);

};

#endif // TEST_H
