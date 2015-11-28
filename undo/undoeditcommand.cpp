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

#include "undoeditcommand.h"
#include "utils.h"

UndoEditCommand::UndoEditCommand(QTreeWidget *theWidget, DomModel *newRegola, QList<int> newPath) : UndoCommand(theWidget, newRegola, newPath)
{
    _firstShot = true ;
    _originalElement = NULL ;
    _modifiedElement = NULL ;
}

UndoEditCommand::~UndoEditCommand()
{
    if(NULL != _originalElement) {
        delete _originalElement;
    }
    if(NULL != _modifiedElement) {
        delete _modifiedElement;
    }
}

void UndoEditCommand::setOriginalElement(DomItem *beforeEdit)
{
    if(NULL != beforeEdit) {
        // copy data
        _originalElement = new DomItem(NULL);
        if(NULL != _originalElement) {
            // full copy
            beforeEdit->copyTo(*_originalElement, false);
        }
    }
}

void UndoEditCommand::setModifiedElement(DomItem *afterEdit)
{
    if(NULL != afterEdit) {
        // copy data
        _modifiedElement = new DomItem(NULL);
        if(NULL != _modifiedElement) {
            // full copy
            afterEdit->copyTo(*_modifiedElement, false);
        }
    }
}


void UndoEditCommand::undo()
{
    makeACopy(_originalElement);
}

void UndoEditCommand::redo()
{
    if(_firstShot) {
        _firstShot = false ;
    } else {
        makeACopy(_modifiedElement);
    }
}


/**
  algorithm:
  strip any attributes, text nodes and text children from current
  copy the attributes, text nodes from the original
  paste new text nodes placing them between elements (that does not change)
  */
void UndoEditCommand::makeACopy(DomItem *source)
{
    DomItem *target = regola->findItemByArray(path);
    if(NULL != target) {
        if(!source->copyTextNodesToTarget(target)) {
            Utils::error(tr("An error occurred applying undo/redo feature."));
        }
    }
}












