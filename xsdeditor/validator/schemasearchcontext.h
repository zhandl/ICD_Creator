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
#ifndef SCHEMASEARCHCONTEXT_H
#define SCHEMASEARCHCONTEXT_H

#include <QObject>

class XSingleElementContent;
class DomItem;

class SchemaSearchPosition
{

    bool isEof;
    int  currentPos;
    XSingleElementContent *current;

    SchemaSearchPosition();
    ~SchemaSearchPosition();

    void copyTo(SchemaSearchPosition &copy);
};

class SchemaSearchContextPosition
{
    DomItem *_source;
    int _pos;
public:
    explicit SchemaSearchContextPosition();
    ~SchemaSearchContextPosition();

    DomItem* source();
    void setSource(DomItem* value);
    int pos();
    void setPos(const int value);
};

class SchemaSearchContext
{
public:
    enum ESearchState {
        OK,
        NOK,
        FOUND, // found, stop search
        NOTFOUND, // definitevly not found in this branch of search
        SKIP, // skip an optional element, transparent no-op
        ERROR // stop the search
    };
private:
    // we explore more branches returning to starting point on failure.
    // it is a FSA similar to those of a compiler, but we have already the
    // grammar: it is the schema itself.
    XSingleElementContent *_foundItem;
    XSingleElementContent *_current;
    XSingleElementContent *_lastMatched;
    DomItem *_currentSource;
    int _currentIndex;
    DomItem *_target;
    DomItem *_parentElement;
    int _targetIndex;


public:
    explicit SchemaSearchContext();
    ~SchemaSearchContext();

    bool initScan();
    /**
      set the target of the search
      */
    void setTarget(DomItem *parent, DomItem *source, const int sourceIndex);
    QString targetTag();
    bool advanceSource();
    bool isEof();
    bool sourceIsTarget();

    //---- save the parsing position
    void savePosition(SchemaSearchContextPosition& position);
    void restorePosition(SchemaSearchContextPosition& position);

    //---- properties
    XSingleElementContent* foundItem();
    void setFoundItem(XSingleElementContent* value);

};



#endif // SCHEMASEARCHCONTEXT_H
