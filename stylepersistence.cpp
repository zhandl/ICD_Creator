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

//#include "xmlEdit.h"
#include "utils.h"
#include "stylepersistence.h"

#include <QFile>
#include <QDir>

#define STYLE_ROOT_ELEMENT          "style"
#define STYLESETENTRY_TAGNAME       "styles"
#define KEYWORDSETENTRY_TAGNAME     "keywords"
#define IDS_TAGNAME                 "ids"
//-----------------------------------------------------------------------
#define STYLE_TAGNAME   "style"
#define STYLE_ID "id"
#define STYLE_COLOR "color"
#define STYLE_FONTFAMILY "family"
#define STYLE_FONTSIZE "size"
#define STYLE_FONTBOLD "bold"
#define STYLE_FONTITALIC "italic"

//-----------------------------------------------------------------------

#define KEYWORD_TAGNAME "keyword"
#define KEYWORD_IDSTYLE  "idStyle"
#define KEYWORD_KEYW     "keyword"

//-----------------------------------------------------------------------
#define IDATTRS_TAGNAME  "id"
#define ST_ID_STYLE      "id"
#define ST_ID_ALPHA      "alpha"
//-----------------------------------------------------------------------

StylePersistence::StylePersistence()
{
}

StylePersistence::~StylePersistence()
{

}

//-----------------------------------------------------------------------

bool StylePersistence::collectAnId(VStyle *style, QDomElement *element)
{
    QString id = element->attribute(ST_ID_STYLE, "");
    QString alpha = element->attribute(ST_ID_ALPHA, "");

    return style->addId(id, Utils::decodeBoolean(alpha));
}

bool StylePersistence::collectIds(VStyle *style, QDomNodeList &nodes)
{
    bool isOk = true ;
    int nodi = nodes.count();
    for(int i = 0 ; i < nodi ; i ++) {
        QDomNode childNode = nodes.item(i) ;
        D(printf("K1 trovato %d %s=%s\n", childNode.nodeType(), childNode.nodeName().toAscii().data(), childNode.nodeValue().toAscii().data()));

        if(childNode.isElement()) {
            QDomElement element = childNode.toElement();
            if(IDATTRS_TAGNAME == element.tagName()) {
                if(!collectAnId(style, &element)) {
                    isOk = false;
                }
            }
        }
    }
    return isOk ;
} // collectIds

//-----------------------------------------------------------------------------------------------------

bool StylePersistence::collectAKeyword(VStyle *style, QDomElement *element)
{
    QString idStyle = element->attribute(KEYWORD_IDSTYLE, "");
    QString keyword = element->attribute(KEYWORD_KEYW, "");

    TokenEntry *token = new TokenEntry(keyword, NULL);
    if(NULL != token) {
        mapTokens.insertMulti(idStyle, token);
        if(style->addToken(token)) {
            return true ;
        }
    }
    return false;
}//()


bool StylePersistence::collectKeywords(VStyle *style, QDomNodeList &nodes)
{
    bool isOk = true ;
    int nodi = nodes.count();
    for(int i = 0 ; i < nodi ; i ++) {
        QDomNode childNode = nodes.item(i) ;
        D(printf("K1 trovato %d %s=%s\n", childNode.nodeType(), childNode.nodeName().toAscii().data(), childNode.nodeValue().toAscii().data()));

        if(childNode.isElement()) {
            QDomElement element = childNode.toElement();
            if(KEYWORD_TAGNAME == element.tagName()) {
                if(!collectAKeyword(style, &element)) {
                    isOk = false;
                }
            }
        }
    }
    return isOk ;
} // collectKeywords

//-----------------------------------------------------------------------------------------------------

bool StylePersistence::collectAStyle(VStyle *style, QDomElement *element)
{
    QString id = element->attribute(STYLE_ID, "");
    QString color = element->attribute(STYLE_COLOR, "");
    QString fontFamily = element->attribute(STYLE_FONTFAMILY, "");
    QString fontSize = element->attribute(STYLE_FONTSIZE, "");
    QString bold = element->attribute(STYLE_FONTBOLD, "");
    QString italic = element->attribute(STYLE_FONTITALIC, "");

    StyleEntry *styleEntry = new StyleEntry(id);
    if(NULL != styleEntry) {
        if(!style->addEntry(styleEntry)) {
            return false;
        }
        styleEntry->setBold(Utils::decodeBoolean(bold));
        styleEntry->setItalic(Utils::decodeBoolean(italic));
        styleEntry->setFontSize(Utils::decodeInt(fontSize, 0));
        styleEntry->setFontFamily(fontFamily);
        styleEntry->setColor(color);

        return true ;
    }
    return false;
}//()

bool StylePersistence::collectStyles(VStyle *style, QDomNodeList &nodes)
{
    bool isOk = true ;
    int nodi = nodes.count();
    for(int i = 0 ; i < nodi ; i ++) {
        QDomNode childNode = nodes.item(i) ;
        D(printf("K1 trovato %d %s=%s\n", childNode.nodeType(), childNode.nodeName().toAscii().data(), childNode.nodeValue().toAscii().data()));

        if(childNode.isElement()) {
            QDomElement element = childNode.toElement();
            if(STYLE_TAGNAME == element.tagName()) {
                if(!collectAStyle(style, &element)) {
                    isOk = false;
                }
            }
        }
    }
    return isOk ;
} // collectStyles


bool StylePersistence::scanStyleData(VStyle *style, QDomNode &rootNode)
{
    bool isOk = true ;
    int nodi = rootNode.childNodes().count();
    for(int i = 0 ; i < nodi ; i ++) {
        QDomNode childNode = rootNode.childNodes().item(i) ;
        if(childNode.isElement()) {
            QDomElement element = childNode.toElement();
            QDomNodeList childs = element.childNodes();
            if(STYLESETENTRY_TAGNAME == element.tagName()) {
                if(!collectStyles(style, childs)) {
                    isOk = false;
                }
            } else if(KEYWORDSETENTRY_TAGNAME == element.tagName()) {
                if(!collectKeywords(style, childs)) {
                    isOk = false;
                }
            } else if(IDS_TAGNAME == element.tagName()) {
                if(!collectIds(style, childs)) {
                    isOk = false;
                }
            }
        }//if
    }//for
    return isOk ;
}//scanStyleData()


bool StylePersistence::scanData(QVector<VStyle*> *styles, QDomNode &rootNode)
{
    bool isOk = true ;
    mapTokens.clear();
    int nodi = rootNode.childNodes().count();
    //D(printf("sono in assegna con %d nodi\n", nodi));
    for(int i = 0 ; i < nodi ; i ++) {
        QDomNode childNode = rootNode.childNodes().item(i) ;

        if(childNode.isElement()) {
            QDomElement element = childNode.toElement();
            QString name = element.attribute("name", "");
            QString description = element.attribute("description", "");
            VStyle *style = new VStyle(name, description);
            styles->append(style);
            if(STYLE_ROOT_ELEMENT == element.tagName()) {
                if(!scanStyleData(style, element)) {
                    isOk = false;
                }
            }
            if(isOk) {
                completeStyle(style);
            }
        }
    }//for
    return isOk ;
}//scanData()

void StylePersistence::completeStyle(VStyle *style)
{
    foreach(QString key, mapTokens.keys()) {
        QList<TokenEntry*>values = mapTokens.values(key);
        StyleEntry *e = style->getStyleEntry(key);
        foreach(TokenEntry * token, values) {
            token->setStyle(e);
        }
    }
}

bool StylePersistence::readStyleFile(QVector<VStyle*> *styles, const QString & filePath)
{
    bool isOk = false;
    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly)) {
        QDomDocument document;
        if(document.setContent(&file)) {
            isOk = scanData(styles, document);
        } else {
            Utils::error(tr("Unable to parse XML"));
        }
        file.close();
    } else {
        Utils::error(QString(tr("Unable to load file.\n Error code is '%1'")).arg(file.error()));
    }
    return isOk ;
}

bool StylePersistence::scanDirectory(const QString &dirName, QVector<VStyle*> *styles)
{
    bool isOK = true ;
    QDir dir(dirName);
    dir.setFilter(QDir::Files);
    dir.setSorting(QDir::Name);
    QStringList names;
    names.append("*.style");
    dir.setNameFilters(names);
    QFileInfoList fileList = dir.entryInfoList();
    foreach(QFileInfo info, fileList) {
        if(!readStyleFile(styles, info.absoluteFilePath())) {
            isOK = false ;
        }
    }
    return isOK;
}

