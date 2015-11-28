/**************************************************************************
 *  This file is part of QXmlEdit                                         *
 *  Copyright (C) 2012 by Luca Bellonda and individual contributors       *
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

#include "undomovedowncommand.h"

UndoMoveDownCommand::UndoMoveDownCommand(QTreeWidget *theWidget, DomModel *newRegola, QList<int> newPath) : UndoCommand(theWidget, newRegola, newPath)
{
}

UndoMoveDownCommand::~UndoMoveDownCommand()
{
}

void UndoMoveDownCommand::undo()
{
    if(_done) {
        QList<int> selPath(path);
        int size = selPath.size() ;
        if(size > 0) {
            int lastPos = selPath.at(size - 1);
            lastPos ++ ;
            selPath.removeLast();
            selPath.append(lastPos);
        }
        DomItem *element = regola->findItemByArray(selPath);
        regola->internalMoveUp(element, false);
    }
}

void UndoMoveDownCommand::redo()
{
    DomItem *element = regola->findItemByArray(path);
    _done = regola->internalMoveDown(element, false);
}

bool UndoMoveDownCommand::done()
{
    return _done ;
}
