/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtXml>
#include "dommodel.h"
#include "domitem.h"
#include "findtextparams.h"
#include "config.h"
#include "utils.h"

QBrush DomItem::commentBrush(QColor(0xC0, 0xC0, 0xC0));
QBrush DomItem::defaultBrush(QColor(0xC0, 0x00, 0x00));
QBrush DomItem::procInstrBrush(QColor(0x00, 0xC0, 0xC0));
QBrush DomItem::attrBrush(QColor(0xC0, 0x00, 0x00));

bool DomItem::isLoadedIcons = false;
QIcon DomItem::procInstrIcon;
QIcon DomItem::commentIcon;
QIcon DomItem::elementIcon;
QIcon DomItem::procInstrBkmIcon;
QIcon DomItem::commentBkmIcon;
QIcon DomItem::elementBkmIcon;
QIcon DomItem::textIcon;
QIcon DomItem::textBkmIcon;
QIcon DomItem::childrenHiddenIcon;
QIcon DomItem::childrenHiddenBkmIcon;

const int DomItem::ShowDataRole = Qt::UserRole + 1;

QRegExp DomItem::terminatorSearch("[\\n\\r]");

QFont DomItem::fixedWidthFont(DEFAULT_FIXEDWIDTHFONT);
QFont *DomItem::attrFont = NULL;

int DomItem::defaultAttrFonts = 0;
int DomItem::fixedSizeAttrFonts = 0;

bool DomItem::firstTimeFixedWidthFont = true ;
QString DomItem::textCompactViewPrefix ;


ItemInfo::ItemInfo()
{
    reset();
}

ItemInfo::~ItemInfo()
{
}

void ItemInfo::reset()
{
    numItems = 0;
    totalSize = 0;
}


TextChunk::TextChunk(const bool isCDATASection, const QString &txt)
{
    isCDATA = isCDATASection;
    text = txt;
}

TextChunk *TextChunk::clone()
{
    TextChunk *cloned = new TextChunk(isCDATA, text);
    return cloned;
}

long DomItem::instances = 0;

DomItem::DomItem(const QString newTag, const QString &itext, DomModel *model, DomItem *parent)
{
    initItem(model, parent);
    _tag = newTag;
    type = ET_ELEMENT;
    text = itext;
}

DomItem::DomItem(DomModel *model)
{
    initItem(model, NULL);
    type = ET_ELEMENT;
}

DomItem::DomItem(DomModel *model, const ItemType newType, DomItem *parent)
{
    initItem(model, parent);
    type = newType;
}

DomItem::~DomItem()
{
    QVectorIterator<DomItem*> it(childItems);
    while(it.hasNext()) {
        delete it.next();
    }
    clearTextNodes();
    clearAttributes();
    parentRule = NULL;
    parentItem = NULL;
}

void DomItem::generateId()
{
    instanceId = instances++;
}

void DomItem::initItem(DomModel *model, DomItem *parent)
{
    generateId();
    visibilityState = EVN_NORMAL;
//    isShowTextBase64 = false;
    ui = NULL;
    parentRule = model;
    parentItem = parent;
    wasOpen = false;
    _isCData = false;
    _viewMode = E_VM_NONE;
    _edited = false;
    _saved = false;
}

DomItem *DomItem::parent()
{
    return parentItem;
}

void DomItem::loadIcons()
{
    if(isLoadedIcons)
        return;
    isLoadedIcons = true ;
    procInstrIcon.addPixmap(QPixmap(QString::fromUtf8(":/tree/pi_icon.png")), QIcon::Normal, QIcon::Off);
    commentIcon.addPixmap(QPixmap(QString::fromUtf8(":/tree/comm_icon.png")), QIcon::Normal, QIcon::Off);
    elementIcon.addPixmap(QPixmap(QString::fromUtf8(":/tree/el_icon.png")), QIcon::Normal, QIcon::Off);
    procInstrBkmIcon.addPixmap(QPixmap(QString::fromUtf8(":/tree/pi_bkm_icon.png")), QIcon::Normal, QIcon::Off);
    commentBkmIcon.addPixmap(QPixmap(QString::fromUtf8(":/tree/comm_bk_icon.png")), QIcon::Normal, QIcon::Off);
    elementBkmIcon.addPixmap(QPixmap(QString::fromUtf8(":/tree/el_bkm.png")), QIcon::Normal, QIcon::Off);
    textIcon.addPixmap(QPixmap(QString::fromUtf8(":/tree/text.png")), QIcon::Normal, QIcon::Off);
    textBkmIcon.addPixmap(QPixmap(QString::fromUtf8(":/tree/el_bkm.png")), QIcon::Normal, QIcon::Off);
    childrenHiddenIcon.addPixmap(QPixmap(QString::fromUtf8(":/tree/hidden_children")), QIcon::Normal, QIcon::Off);
    childrenHiddenBkmIcon.addPixmap(QPixmap(QString::fromUtf8(":/tree/hidden_children_bm")), QIcon::Normal, QIcon::Off);
    textCompactViewPrefix =  "     ";
}

//bool DomItem::isShownBase64() const
//{
//    return isShowTextBase64;
//}

//void DomItem::setShownBase64(const bool shownAs)
//{
//    isShowTextBase64 = shownAs;
//}

DomItem::EViewModes DomItem::viewMode() const
{
    return _viewMode;
}

void DomItem::setViewMode(const EViewModes newMode)
{
    _viewMode = newMode;
}

// instead of the over length part of a string to ellipsis
// for example:
// input String is inputStringAndABCDEFG, but the MAX_LIMIT_TEXTLEN is 10,
// using this fuction instead input string to inputStrin...
QString DomItem::limitTextWithEllipsis(const QString &inputText)
{
    bool appendEllipsis = false;
    QString result;
    if(inputText.length() > MAX_LIMIT_TEXTLEN) {
        result = inputText.left(MAX_LIMIT_TEXTLEN);
        appendEllipsis = true;
    } else {
        result = inputText;
    }
    int indexOfLF = result.indexOf(terminatorSearch, 0);
    if(indexOfLF >= 0) {
        result = result.left(indexOfLF);
        appendEllipsis = true;
    }
    if(appendEllipsis) {
        result.append(tr("..."));
    }
    return result;
}

// load the view state(expand or not)
void DomItem::registerState()
{
    if(NULL != ui) {
        wasOpen = ui->isExpanded();
    } else {
        wasOpen = false;
    }
    foreach(DomItem *item, childItems) {
        item->registerState();
    }
}

// display the item and its children
void DomItem::displayRecursive(PaintInfo *paintInfo)
{
    if(NULL == ui) {
        return;
    }
    display(ui, paintInfo);
    foreach(DomItem *item, childItems) {
        item->displayRecursive(paintInfo);
    }
}


const QString DomItem::styleItemTag(QTreeWidgetItem *me, PaintInfo *paintInfo)
{
    if(!VStyle::globalInitFlag) {
        VStyle::globalActivate(createItemFonts(me->font(0)), QApplication::palette().text());
    }
    QString qualifiedInfo;
    bool isFont = false ;
    bool isBrush = false ;
    VStyle* style = paintInfo->currentStyle();
    if(NULL != style) {
        foreach(Attribute * attribute, attributes) {
            IdEntry *id = style->getIdEntry(attribute->name);
            if(NULL != id) {
                if(id->isAlpha()) {
                    qualifiedInfo.append(" '");
                    qualifiedInfo.append(attribute->value);
                    qualifiedInfo.append("'");
                } else {
                    qualifiedInfo.append(" ");
                    qualifiedInfo.append(attribute->value);
                }
            }
        }
        StyleEntry *se = style->getStyleOfKeyword(tag()) ;
        if(NULL != se) {
            if(se->isColor()) {
                me->setForeground(0, se->brush());
                isBrush = true ;
            }
            QFont *styleFont = se->font();
            if(NULL != styleFont) {
                me->setFont(0, *styleFont);
                isFont = true ;
            }
        }
    }
    //use default brush if no assignment
    if(!isBrush) {
        me->setForeground(0, VStyle::defaultBrush());
    }
    if(!isFont) {
        me->setFont(0, VStyle::defaultFont());
    }
    return qualifiedInfo;
}


const QString DomItem::styleItemTagString(PaintInfo *paintInfo)
{
    QString qualifiedInfo;
    VStyle* style = paintInfo->currentStyle();
    if(NULL != style) {
        foreach(Attribute * attribute, attributes) {
            IdEntry *id = style->getIdEntry(attribute->name);
            if(NULL != id) {
                if(id->isAlpha()) {
                    qualifiedInfo.append(" '");
                    qualifiedInfo.append(attribute->value);
                    qualifiedInfo.append("'");
                } else {
                    qualifiedInfo.append(" ");
                    qualifiedInfo.append(attribute->value);
                }
            }
        }
    }
    return qualifiedInfo;
}

QFont DomItem::styleItemTagFont(PaintInfo *paintInfo)
{
    VStyle* style = paintInfo->currentStyle();
    if(NULL != style) {
        StyleEntry *se = style->getStyleOfKeyword(tag()) ;
        if(NULL != se) {
            QFont *styleFont = se->font();
            if(NULL != styleFont) {
                return *styleFont;
            }
        }
    }
    return VStyle::defaultFont();
}

QBrush DomItem::styleItemTagColor(PaintInfo *paintInfo)
{
    VStyle* style = paintInfo->currentStyle();
    if(NULL != style) {
        StyleEntry *se = style->getStyleOfKeyword(tag()) ;
        if(NULL != se) {
            if(se->isColor()) {
                return se->brush();
            }
        }
    }

    return VStyle::defaultBrush();
}

QIcon DomItem::styleItemTagIcon()
{
    switch(type) {
    case ET_ELEMENT:
        return elementIcon;
    case ET_PROCESSING_INSTRUCTION:
        return procInstrIcon;
    case ET_COMMENT:
        return commentIcon;
    case ET_TEXT:
        return textIcon;
    default:
        return QIcon();
    }
}

QVariant DomItem::columnViewTooltipData()
{
    switch(getType()) {
    case DomItem::ET_ELEMENT: {
        QString tooltip;
        foreach(Attribute *attribute, getAttributesList()) {
            QString attrValue = QString("%1=\"%2\"\n").arg(attribute->name).arg(attribute->value);
            tooltip += attrValue;
        }
        return QVariant(tooltip);
    }
    default:
        break;
    }
    return QVariant();
}

QVariant DomItem::columnViewDisplayData(PaintInfo *paintInfo, const int rowOrdinal)
{
    switch(getType()) {
    case DomItem::ET_COMMENT:
        return QVariant(QString("%1 Comment: %2").arg(rowOrdinal).arg(getComment()));
        break;
    case DomItem::ET_PROCESSING_INSTRUCTION:
        return QVariant(QString("%1 P.I.: %2 %3").arg(rowOrdinal).arg(getPITarget()).arg(getPIData()));
        break;
    case DomItem::ET_TEXT:{
        QString txt = text;
        if(txt.length() > 10) {
            txt = txt.left(10);
            txt += "...";
        }
        return QVariant(QString("%1 Text: %2").arg(rowOrdinal).arg(txt));
        break;
    }
    case DomItem::ET_ELEMENT: {
        int totalChildrenNumber = selfInfo.numItems + childrenInfo.numItems;
        QString childInfo;
        if(totalChildrenNumber > 0) {
            childInfo = QString("(%1)").arg(totalChildrenNumber);
        }
        QString elmInfo = styleItemTagString(paintInfo);
        return QVariant(QString("%1 %2 %3 %4").arg(rowOrdinal).arg(tag()).arg(elmInfo).arg(childInfo));
    }
    default:
        return QVariant(QString("%1 ???").arg(rowOrdinal));
        break;
    }
    return QVariant("");
}

void DomItem::display(QTreeWidgetItem *me, PaintInfo *paintInfo)
{
    if(ui != me) {
        ui = me;
        setChildrenLeavesHiddenState(me, false);
    }
    me->setData(0, Qt::UserRole, qVariantFromValue((void*)this));

    switch(visibilityState) {
    case EVN_ELLIPSIS:
        me->setIcon(paintInfo->columnForTag, QIcon());
        me->setText(paintInfo->columnForTag, tr("..."));
        me->setText(paintInfo->columnForAttributes, tr("..."));
        me->setText(paintInfo->columnForText, tr("..."));
        me->setText(paintInfo->columnForDecodedText, tr("..."));
        return;
    case EVN_HIDDEN:
        me->setHidden(true);
        return;
    default:
        break;
    }

    if(paintInfo->exploreMode()) {
        QString firstColText = QString("<%1> #%2, data: %L3")
                               .arg(tag())
                               .arg(this->childItems.size())
                               .arg(selfInfo.totalSize + childrenInfo.totalSize);
        me->setText(0, firstColText);
        return;
    }

    bool isShowAttributesLength = paintInfo->showAttributesLength();
    bool isUseFixedFonts = paintInfo->userFixedLengthFont();
    bool isOneAttributePerLine = paintInfo->oneAttrPerLine();
    bool isShowChildIndex = paintInfo->indexPerChild();
    bool isCompactView = paintInfo->compactView();
    QString firstColText;
    if(isShowChildIndex && (NULL != parentItem)) {
        QTreeWidgetItem *pItem = parentItem->getUI();
        if(NULL != pItem) {
            int childIndex = pItem->indexOfChild(ui);
            firstColText = QString("%1 -").arg(childIndex + 1);
        }
    }
    QString attrTxt = "";
    switch(type) {
    case ET_ELEMENT:
        firstColText += tag();
        if(!areChildrenLeavesHidden(me)) {
            me->setIcon(0, elementIcon);
        } else {
            me->setIcon(0, childrenHiddenIcon);
        }
        {
            QString qualifiedInfo = styleItemTag(me, paintInfo);
            if(qualifiedInfo.length() > 0) {
                firstColText.append(" - ");
                firstColText.append(qualifiedInfo);
            }
            me->setText(paintInfo->columnForTag, firstColText);
            if(paintInfo->showItemSize()) {
                QString children = QString("%1 (%2)")
                                   .arg(selfInfo.numItems)
                                   .arg(selfInfo.numItems + childrenInfo.numItems);
                me->setText(paintInfo->columnForChildren, children);
                QString size = QString("%L1")
                               .arg(selfInfo.totalSize + childrenInfo.totalSize);
                me->setText(paintInfo->columnForSize, size);
            }
            QString textToShow;
            QString textToShowBase64;
            bool collectBase64Text = paintInfo->showUnBase64();
            QVectorIterator<TextChunk*> tt(textNodes);
            while(tt.hasNext()) {
                TextChunk *tx = tt.next();
                if(tx->isCDATA) {
                    textToShow.append(" [[CDATA:");
                    if(isCompactView) {
                        textToShow.append(tx->text.trimmed());
                    } else {
                        textToShow.append(tx->text);
                    }
                    textToShow.append(" ]]");
                } else {
                    if(isCompactView) {
                        if(collectBase64Text) {
                            if(!textToShowBase64.isEmpty()) {
                                textToShowBase64.append("\n ---\n");
                            }
                            //textToShowBase64.append()
                        }
                        textToShow.append(tx->text.trimmed());
                    } else {
                        if(collectBase64Text) {
                            if(!textToShowBase64.isEmpty()) {
                                textToShowBase64.append(("\n ---\n"));
                            }
                        }
                        textToShow.append(tx->text);
                    }
                }
            }
            QString originalText = textToShow;
            if(isCompactView) {
                textToShow = limitTextWithEllipsis(textToShow);
            }
            if(paintInfo->showItemTextLength()) {
                textToShow = QString("(%1)- %2").arg(originalText.length()).arg(textToShow);
            }

            if(isCompactView && attributes.isEmpty()) {
                me->setText(paintInfo->columnForText, "");
                attrTxt = textCompactViewPrefix;
                attrTxt.append(textToShow);
            } else {
                me->setText(paintInfo->columnForText, textToShow);
            }
            me->setText(paintInfo->columnForDecodedText, textToShowBase64);
        }
        break;
    case ET_PROCESSING_INSTRUCTION: {
        firstColText += tr("*Processing Instruction* <? ?>") ;
        me->setText(0, firstColText);
        me->setForeground(0, procInstrBrush);
        me->setIcon(0, procInstrIcon);
        QString pI = getPITarget();
        pI.append("(");
        pI.append(getPIData());
        pI.append(")");
        me->setText(paintInfo->columnForAttributes, pI);
        me->setText(paintInfo->columnForText, tr(""));
    }
        break;
    case ET_COMMENT: {
        firstColText += tr("*comment*");
        me->setText(0, firstColText);
        me->setForeground(0, commentBrush);
        me->setIcon(0, commentIcon);
        QString textToShow = text;
        if(isCompactView) {
            textToShow = limitTextWithEllipsis(text);
        }
        me->setText(paintInfo->columnForText, textToShow);
    }
        break;
    case ET_TEXT: {
        firstColText += tr("*text*");
        me->setText(0, firstColText);
        me->setForeground(0, commentBrush);
        me->setIcon(0, textIcon);
        QString textToShow = text;
        if(isCompactView) {
            textToShow = limitTextWithEllipsis(text);
        }
        me->setText(paintInfo->columnForText, textToShow);
    }
        break;
    default:
        firstColText += tr("unknown node");
        me->setText(0, firstColText);
        me->setForeground(0, defaultBrush);
        me->setIcon(0, QIcon());
        break;
    }

    if(!attributes.isEmpty()) {
        bool isFirst = true;
        QString attrList;
        if(paintInfo->attributesHTML()) {
            attrList = "<html><body bgcolor=\"transparent\">";
            int attrIndex = 1;
            int size = attributes.size();
            for(int attr = 0; attr < size; attr++) {
                Attribute *attribute = attributes.at(attr);
                QString key = attribute->name;
                QString value = attribute->value;
                if(isFirst) {
                    isFirst = false;
                } else {
                    if(isOneAttributePerLine) {
                        if(isCompactView) {
                            if(attrIndex > ATTR_PER_COLUMN) {
                                attrIndex = 1;
                                attrList.append("<br/>\n");
                            } else {
                                attrList.append(", ");
                            }
                        } else {
                            attrList.append("<br/>\n");
                        }
                    } else {
                        attrList.append(", ");
                    }
                }
                attrList.append("<FONT COLOR=\"green\">");
                attrList.append(key);
                if(isShowAttributesLength) {
                    int attrLen = value.length();
                    attrList.append("(");
                    if(isUseFixedFonts) {
                        attrList.append(QString("%1").arg(attrLen, WIDTH_LEN_CHARS));
                    } else {
                        attrList.append(QString("%1").arg(attrLen));
                    }
                    attrList.append(")=\"");
                } else {
                    attrList.append("=\"");
                }
                attrList.append("</FONT><FONT COLOR=\"blue\">");
                attrList.append(value);
                attrList.append("</FONT>");
                attrList.append("\"");
                attrIndex++;
            }
            attrList.append("</body><html>");
        } else {
            int attrIndex = 1;
            int size = attributes.size();
            for(int attr = 0; attr < size; attr++) {
                Attribute *attribute = attributes.at(attr);
                QString key = attribute->name;
                QString value = attribute->value;
                if(isFirst) {
                    isFirst = false;
                } else {
                    if(isOneAttributePerLine) {
                        if(isCompactView) {
                            if(attrIndex > ATTR_PER_COLUMN) {
                                attrIndex = 1;
                                attrList.append("\n");
                            } else {
                                attrList.append(", ");
                            }
                        } else {
                            attrList.append("\n");
                        }
                    } else {
                        attrList.append(", ");
                    }
                }
                attrList.append(key);
                if(isShowAttributesLength) {
                    int attrLen = value.length();
                    attrList.append("(");
                    if(isUseFixedFonts) {
                        attrList.append(QString("%1").arg(attrLen, WIDTH_LEN_CHARS));
                    } else {
                        attrList.append(QString("%1").arg(attrLen));
                    }
                    attrList.append(")=\"");
                } else {
                    attrList.append("=\"");
                }
                attrList.append(value);
                attrList.append("\"");
                attrIndex++;
            }
        }
        me->setText(paintInfo->columnForAttributes, attrList);
        me->setForeground(paintInfo->columnForAttributes, attrBrush);
        if(isUseFixedFonts) {
            if(firstTimeFixedWidthFont) {
                firstTimeFixedWidthFont = false ;
                createFixedWidthFonts();
            }
            me->setFont(paintInfo->columnForAttributes, fixedWidthFont);
        } else {
            if(NULL == attrFont) {
                QFontInfo info(ui->font(0));
                QString family = info.family();
                attrFont = new QFont(family);
                defaultAttrFonts = attrFont->pointSize();
            }
            me->setFont(paintInfo->columnForAttributes, *attrFont);
        }

    } else if(ET_ELEMENT == type) {
        me->setText(paintInfo->columnForAttributes, attrTxt);
        if(attrTxt.length() > 0) {
            if(NULL == attrFont) {
                QFontInfo info(ui->font(0));
                QString family = info.family();
                attrFont = new QFont(family);
                defaultAttrFonts = attrFont->pointSize();
            }
            me->setFont(paintInfo->columnForAttributes, *attrFont);
        }
    }
    if(wasOpen) {
        ui->setExpanded(true);
    }
}

void DomItem::createFixedWidthFonts()
{
    firstTimeFixedWidthFont = false;
    fixedWidthFont.setFamily(DEFAULT_FIXEDWIDTHFONT);
    if(Config::getBool(Config::KEY_ELEMENT_FONTFIXEDWIDTHENABLED, false)) {
        QString family = Config::getString(QString(Config::KEY_ELEMENT_FONTFIXEDWIDTHFAMILY), DEFAULT_FIXEDWIDTHFONT);
        if(family.isEmpty()) {
            family = DEFAULT_FIXEDWIDTHFONT;
        }
        fixedWidthFont.setFamily(family);
        int fixedWidthFontPoints = Config::getInt(Config::KEY_ELEMENT_FONTFIXEDWIDTHSIZE, 0);
        if(fixedWidthFontPoints > 0) {
            fixedWidthFont.setPointSize(fixedWidthFontPoints);
        }
    }
    fixedSizeAttrFonts = fixedWidthFont.pointSize();
}

QFont DomItem::createItemFonts(QFont defaultFont)
{
    if(Config::getBool(Config::KEY_ELEMENT_ELEMENTFONTENABLED, false)) {
        QString itemFontName = Config::getString(Config::KEY_ELEMENT_ELEMENTFONTFAMILY, "");
        int itemFontSize = Config::getInt(Config::KEY_ELEMENT_ELEMENTFONTSIZE, 0);
        bool itemFontItalic = Config::getBool(Config::KEY_ELEMENT_ELEMENTFONTITALIC, false);
        bool itemFontBlod = Config::getBool(Config::KEY_ELEMENT_ELEMENTFONTBOLD, false);
        if(itemFontName.isEmpty()) {
            itemFontName = defaultFont.family();
        }
        if(itemFontSize <= 0) {
            itemFontSize = defaultFont.pointSize();
        }
        QFont newDefaultFont(itemFontName, itemFontSize, itemFontBlod ? QFont::Bold : -1, itemFontItalic);
        return newDefaultFont;
    } else {
        return defaultFont;
    }
}

QString DomItem::getAsText()
{
    QString textToShow;
    QVectorIterator<TextChunk*> tt(textNodes);
    while(tt.hasNext()) {
        TextChunk *tx = tt.next();
        if(tx->isCDATA) {
            textToShow.append(" [[CDATA:");
            textToShow.append(tx->text);
            textToShow.append(" ]]");
        } else {
            textToShow.append(tx->text);
        }
    }
    return textToShow;
}

QString DomItem::getAsSimpleText(const bool isBase64)
{
    QString textToShow;
    if(type == ET_TEXT) {
        textToShow = text;
    } else {
        QVectorIterator<TextChunk*> tt(textNodes);
        while(tt.hasNext()) {
            TextChunk *tx = tt.next();
            textToShow.append(tx->text);
        }
    }
    if(isBase64) {
        textToShow = Utils::fromBase64(textToShow);
    }
    return textToShow;
}

QString DomItem::getAsSimpleTextXml(const bool isBase64)
{
    QString textToShow;
    if(type == ET_TEXT) {
        textToShow = text;
    } else {
        QVectorIterator<TextChunk*> tt(textNodes);
        while(tt.hasNext()) {
            TextChunk *tx = tt.next();
            textToShow.append(tx->text);
        }
    }
    if(isBase64) {
        textToShow = Utils::fromBase64Xml(textToShow);
    }
    return textToShow;
}

bool DomItem::isCDATA()
{
    if(type == ET_TEXT) {
        return _isCData;
    }
    QVectorIterator<TextChunk*> tt(textNodes);
    while(tt.hasNext()) {
        TextChunk *tx = tt.next();
        return tx->isCDATA;
    }
    return false;
}

void DomItem::setAsSingleTextNode(const QString &newText, const bool isBase64, const bool isCData)
{
    clearTextNodes();
    QString text = newText;
    if(isBase64) {
        text = Utils::toBase64(newText);
    }
    if(type == ET_TEXT) {
        setTextOfTextNode(text, isCData);
    } else {
        TextChunk *textChunk = new TextChunk(isCData, text);
        addTextNode(textChunk);
    }
}

bool DomItem::edited()
{
    return _edited;
}

bool DomItem::saved()
{
    return _saved;
}

void DomItem::setChildItem(QTreeWidget *pTree, QTreeWidgetItem *parent, PaintInfo *paintInfo, const bool isGUI, const int pos)
{
    QTreeWidgetItem *me = NULL;
    bool isTop = false;
    if(isGUI) {
        if(NULL == parent) {
            me = new QTreeWidgetItem(0);
            isTop = true;
        } else {
            if(pos >= 0) {
                me = new QTreeWidgetItem();
                parent->insertChild(pos, me);
            } else {
                me = new QTreeWidgetItem(parent);
            }
        }
        display(me, paintInfo);
    }
    foreach(DomItem *item, childItems) {
        item->setChildItem(NULL, me, paintInfo, isGUI);
    }
    if(isTop) {
        if(pos >= 0) {
            pTree->insertTopLevelItem(pos, me);
        } else {
            pTree->addTopLevelItem(me);
        }
    }
}

bool DomItem::generateDom(QDomDocument &document, QDomNode &parent)
{
    switch(type) {
    default:
    case ET_ELEMENT: {
        QDomElement node = document.createElement(tag());

        QVectorIterator<TextChunk*> tt(textNodes);
        while(tt.hasNext()) {
            TextChunk *tx = tt.next();
            if(tx->isCDATA) {
                QDomCDATASection nodeCData = document.createCDATASection(tx->text);
                node.appendChild(nodeCData);
            } else {
                QDomText nodeText = document.createTextNode(tx->text);
                node.appendChild(nodeText);
            }
        }

        QVectorIterator<Attribute*> attrs(attributes);
        while(attrs.hasNext()) {
            Attribute *attribute = attrs.next();
            node.setAttribute(attribute->name, attribute->value);
        }

        parent.appendChild(node);
        foreach(DomItem *value, childItems) {
            if(!value->generateDom(document, node))
                return false;
        }
        return true;
    }
        break;

    case ET_PROCESSING_INSTRUCTION: {
        QDomProcessingInstruction node = document.createProcessingInstruction(getPITarget(), getPIData());
        parent.appendChild(node);
        return true;
    }
        break;

    case ET_COMMENT: {
        QDomComment node = document.createComment(getComment());
        parent.appendChild(node);
        return true;
    }
        break;

    case ET_TEXT: {
        if(_isCData) {
            QDomCDATASection nodeCData = document.createCDATASection(text);
            parent.appendChild(nodeCData);
        } else {
            QDomText nodeText = document.createTextNode(text);
            parent.appendChild(nodeText);
        }
        return true;
    }
        break;
    }
    return false;
}

bool DomItem::isEmpty() const
{
    return childItems.isEmpty();
}

void DomItem::clearAttributes()
{
    QVectorIterator<Attribute*> it(attributes);
    while(it.hasNext()) {
        delete it.next();
    }
    attributes.clear();
}

void DomItem::addAttribute(const QString &name, const QString &value)
{
    if(!name.isEmpty()) {
        Attribute *attribute = new Attribute(name, value);
        attributes.append(attribute);
    }
}

DomItem *DomItem::fromItemData(QTreeWidgetItem *item)
{
    if(NULL == item) {
        return NULL;
    }
    QVariant data = item->data(0, Qt::UserRole);
    DomItem *pItem = (DomItem*)data.value<void*>();
    return pItem;
}

DomItem *DomItem::fromModelIndex(const QModelIndex &index)
{
    if(!index.isValid()) {
        return NULL;
    }
    QVariant data = index.data(Qt::UserRole);
    DomItem *pItem = (DomItem*)data.value<void*>();
    return pItem;
}

void DomItem::addChild(DomItem *newChild)
{
    newChild->parentItem = this;
    childItems.append(newChild);
    addChildInfo(newChild);
}

void DomItem::addChildAt(DomItem *newItem, const int position)
{
    newItem->parentItem = this;
    childItems.insert(position, newItem);
    addChildInfo(newItem);
}

int DomItem::addChildAfter(DomItem *newItem, DomItem *brotherItem)
{
    newItem->parentItem = this;
    if(NULL == brotherItem) {
        childItems.append(newItem);
        return childItems.size() - 1;
    }
    QVectorIterator<DomItem*> it(childItems);
    int index = 0;
    while(it.hasNext()) {
        if(it.next() == brotherItem) {
            childItems.insert(index + 1, newItem);
            return index + 1;
        }
        index++;
    }
    childItems.append(newItem);
    addChildInfo(newItem);
    parentRule->setModified(true);
    return childItems.size() - 1;
}

bool DomItem::moveUp(QVector<DomItem *> &items, DomItem *item)
{
    int indexOf = items.indexOf(item);
    if(indexOf <= 0)
        return false;
    DomItem *pToSwap = items.at(indexOf-1);
    items.replace(indexOf-1, item);
    items.replace(indexOf, pToSwap);

    QTreeWidget *tree = item->ui->treeWidget();
    QTreeWidgetItem *pItem = NULL;
    DomItem *parent = item->parentItem;
    if(NULL == parent) {
        pItem = tree->takeTopLevelItem(indexOf);
        QTreeWidgetItem *item1p = tree->takeTopLevelItem(indexOf - 1);
        tree->insertTopLevelItem(indexOf-1, pItem);
        tree->insertTopLevelItem(indexOf, item1p);
    } else {
        QTreeWidgetItem *parentUI = parent->ui;
        pItem = parentUI->takeChild(indexOf);
        QTreeWidgetItem *item1p = parentUI->takeChild(indexOf - 1);
        parentUI->insertChild(indexOf - 1, pItem);
        parentUI->insertChild(indexOf, item1p);
    }
    tree->setCurrentItem(pItem);
    item->parentRule->setModified(true);
    return true;
}

bool DomItem::moveUp(DomItem *item)
{
    return moveUp(childItems, item);
}

bool DomItem::moveDown(QVector<DomItem*> &items, DomItem *item)
{
    int indexOf = items.indexOf(item);
    if((indexOf < 0) || (indexOf >= (items.size() - 1)))
        return false;
    DomItem *pToSwap = items.at(indexOf + 1);
    items.replace(indexOf + 1, item);
    items.replace(indexOf, pToSwap);
    // user interface
    /*
        QTreeWidgetItem *item1p = ui->takeChild(indexOf+1);
        QTreeWidgetItem *item1 = ui->takeChild(indexOf);
        ui->insertChild(indexOf, item1p);
        ui->insertChild(indexOf+1, item1);
        return true;
    */
    QTreeWidget *tree = item->ui->treeWidget();
    QTreeWidgetItem *pItem = NULL;
    QTreeWidgetItem *item1p ;
    DomItem *parent = item->parentItem;
    if(NULL == parent) {
        item1p = tree->takeTopLevelItem(indexOf + 1);
        pItem = tree->takeTopLevelItem(indexOf);
        tree->insertTopLevelItem(indexOf, item1p);
        tree->insertTopLevelItem(indexOf + 1, pItem);
    } else {
        QTreeWidgetItem *parentUI = parent->ui;

        item1p = parentUI->takeChild(indexOf + 1);
        pItem = parentUI->takeChild(indexOf);
        parentUI->insertChild(indexOf, item1p);
        parentUI->insertChild(indexOf + 1, pItem);
    }
    tree->setCurrentItem(pItem);
    item->parentRule->setModified(true) ;
    return true;
}

bool DomItem::moveDown(DomItem *item)
{
    return moveDown(childItems, item);
}

void DomItem::zeroUI()
{
    zeroUISelf(true);
    foreach(DomItem *item, childItems) {
        item->zeroUI();
    }
}

void DomItem::zeroUISelf(const bool emitMe)
{
    parentRule->takeOutItem(this);
    ui = NULL;
    if(emitMe) {
//        parentRule->notifyUIDeleted(this);
    }
}

DomModel *DomItem::getParentRule()
{
    return parentRule;
}

void DomItem::deleteUI()
{
    if(NULL != ui) {
        QTreeWidgetItem *parentWItem = ui->parent();
        int index;
        if(NULL != parentWItem) {
            index = parentWItem->indexOfChild(ui);
            delete parentWItem->takeChild(index);
        } else {
            index = ui->treeWidget()->indexOfTopLevelItem(ui);
            delete ui->treeWidget()->takeTopLevelItem(index);
        }

        zeroUI();
    }
}

void DomItem::autoDelete(const bool deleteMe)
{
    if(NULL != parentItem) {
        int indexOf = parentItem->childItems.indexOf(this);
        parentItem->childItems.remove(indexOf);
    } else {
        parentRule->notifyDeletionTopItem(this);
    }
    parentRule->takeOutItem(this);

    deleteUI();
    parentRule->setModified(true);
    parentRule = NULL;
    if(deleteMe) {
        delete this;
    }
}

void DomItem::autoDeleteRecursiveInner()
{
    foreach(DomItem *child, childItems) {
        child->autoDeleteRecursiveInner();
    }

    zeroUISelf(false);
    ui = NULL;
    parentRule = NULL;
}

void DomItem::autoDeleteRecursive()
{
    foreach(DomItem *child, childItems) {
        child->autoDeleteRecursiveInner();
        delete child;
    }
    childItems.clear();
    if(NULL != parentItem) {
        int indexOf = parentItem->childItems.indexOf(this);
        parentItem->childItems.remove(indexOf);
    } else {
        parentRule->notifyDeletionTopItem(this);
    }
    parentRule->takeOutItem(this);
    if(NULL != ui) {
        deleteUI();
    } else {
        zeroUISelf(false);
    }
    parentRule->setModified(true);
    parentRule = NULL;
    delete this;
}

DomItem *DomItem::copyTo(DomItem &newItem)
{
    return copyTo(newItem, true);
}

DomItem *DomItem::copyTo(DomItem &newItem, const bool isRecursive)
{
    copyHeaderAndDirectNodes(newItem);
    QVectorIterator<DomItem*> it(childItems);
    while(it.hasNext()) {
        DomItem *newEl = new DomItem(newItem.parentRule);
        newItem.addChild(newEl);
        it.next()->copyTo(*newEl, isRecursive);
    }
    return &newItem;
}

void DomItem::copyHeader(DomItem &newItem)
{
    if(NULL != newItem.parentRule) {
        newItem._tag = newItem.parentRule->addNameToPool(_tag);
    } else {
        newItem._tag = _tag;
    }
    newItem.text = text;
    newItem.type = type;
    newItem._viewMode = _viewMode;
    newItem._isCData = _isCData;
}

void DomItem::copyHeaderAndDirectNodes(DomItem &newItem)
{
    copyHeader(newItem);
    newItem.clearTextNodes();
    newItem.clearAttributes();

    QVectorIterator<Attribute*> attr(attributes);
    while(attr.hasNext()) {
        Attribute *src = attr.next();
        Attribute *dst = new Attribute(src->name, src->value);
        newItem.attributes.append(dst);
    }

    QVectorIterator<TextChunk*> tt(textNodes);
    while(tt.hasNext()) {
        TextChunk *tx = tt.next();
        TextChunk *newText = tx->clone();
        newItem.textNodes.append(newText);
    }
}

DomItem *DomItem::copyToClipboard()
{
    DomItem *newItem = new DomItem(NULL);
    if(NULL != newItem) {
        copyTo(*newItem);
    }
    return newItem;
}

DomItem *DomItem::cutTOClipboard()
{
    if(NULL != parentItem) {
        parentItem->removeChildInfo(this);
    }
    parentRule->deleteItem(this, false);
    return this;
}

bool DomItem::isFirstChild()
{
    if(NULL == parentItem) {
        return (parentRule->getItems().indexOf(this) <= 0) ? true : false;
    }
    return (parentItem->childItems.indexOf(this) <= 0) ? true : false;
}

bool DomItem::isLastChild()
{
    int indexOf = -1 ;
    int size = 0;
    if(NULL == parentItem) {
        QVector<DomItem*> &items = parentRule->getItems();
        size = items.size();
        indexOf = items.indexOf(this);
    } else {
        indexOf = parentItem->childItems.indexOf(this);
        size = parentItem->childItems.size();
    }
    if((indexOf < 0) || (indexOf >= (size - 1)))
        return true;
    return false;
}

void DomItem::expand(QTreeWidget *tree)
{
    if(NULL != ui)
        tree->expandItem(ui);
    QVectorIterator<DomItem*> it(childItems);
    while(it.hasNext()) {
        it.next()->expand(tree);
    }
}

DomItem* DomItem::getChildAt(const int childIndex)
{
    if((childIndex >= 0) && (childIndex < childItems.size())) {
        return childItems.at(childIndex);
    }
    return NULL ;
}

int DomItem::childIndex(DomItem *child)
{
    int index = 0 ;
    foreach(DomItem * aChild, childItems) {
        if(aChild == child) {
            return index ;
        }
        index ++ ;
    }
    return -1;
}


void DomItem::setText(const QString &data)
{
    text = data ;
}

void DomItem::setTextOfTextNode(const QString &data, const bool isCData)
{
    text = data ;
    _isCData = isCData ;
}

const QString &DomItem::getComment()
{
    return text ;
}

void DomItem::setComment(const QString & comment)
{
    text = comment ;
}

void DomItem::addTextNode(TextChunk *text)
{
    textNodes.append(text);
}

void DomItem::clearTextNodes()
{
    QVectorIterator<TextChunk*> tt(textNodes);
    while(tt.hasNext()) {
        delete tt.next();
    }
    textNodes.clear();
}

const QString &DomItem::getPITarget()
{
    return text;
}

const QString DomItem::getPIData()
{
    return tag();
}

void DomItem::setPITarget(const QString & target)
{
    text = target ;
}

void DomItem::setPIData(const QString & data)
{
    _tag = parentRule->addNameToPool(data);
}

// nuovo algoritmo: ambito di ricerca

bool DomItem::searchInScope(FindTextParams &findArgs)
{
    if(!findArgs.isSearchWithScope()) {
        return true;
    }
    QString scope = findArgs.mainScope();
    if(scope.isEmpty() || (tag() == scope)) {
        QStringList scopes = findArgs.getScopes(); //get a reference!
        int scopeCount = scopes.count();
        DomItem *el = this ;
        for(int i = scopeCount - 1 ; i >= 0 ; i--) {
            el = el->parentItem ;
            if(NULL == el) {
                return false;
            }
            QString thisScope = scopes.at(i) ;
            if(!thisScope.isEmpty() && (el->tag() != thisScope)) {
                return false;
            }
        }
        return true;
    }
    return false ;
}

bool DomItem::findText(FindTextParams &findArgs)
{
    bool isFound = false;
    bool isFoundInChild = false;
    bool isHiliteAll = findArgs.isHiliteAll();
    bool isCloseUnrelated = findArgs.isCloseUnrelated();
    FindTextParams::EFindTarget findTarget = findArgs.getFindTarget();
    if(findArgs.isCountingOnly()) {
        isCloseUnrelated = false;
    }

    switch(type) {
    default:
    case ET_ELEMENT: {

        if(searchInScope(findArgs)) {
            if((FindTextParams::FIND_ALL == findTarget) || (FindTextParams::FIND_TAG == findTarget)) {
                if(findArgs.isTextMatched(tag()))
                    isFound = true ;
            }
            if(!isFound) {
                if((FindTextParams::FIND_ALL == findTarget) || (FindTextParams::FIND_TEXT == findTarget)) {
                    foreach(TextChunk * chunk, textNodes) {
                        if(findArgs.isTextMatched(chunk->text)) {
                            isFound = true ;
                        }
                    }
                }
            }
            if(!isFound) {
                QVectorIterator<Attribute*>  attrs(attributes);
                while(attrs.hasNext()) {
                    Attribute* a = attrs.next();
                    if((FindTextParams::FIND_ALL == findTarget) || (FindTextParams::FIND_ATTRIBUTE_NAME == findTarget)) {
                        if(findArgs.isTextMatched(a->name)) {
                            isFound = true ;
                        }
                    }
                    if(!isFound) {
                        if((FindTextParams::FIND_ALL == findTarget) || (FindTextParams::FIND_ATTRIBUTE_VALUE == findTarget)) {
                            if(findArgs.isSearchInAttribute()) {
                                if((a->name == findArgs.attributeName())
                                        && (FindTextParams::FIND_ATTRIBUTE_VALUE == findTarget)) {
                                    isFound = true ;
                                }
                            } else if(findArgs.isTextMatched(a->value)) {
                                isFound = true ;
                            }
                        }
                    }
                }
            }
        }
    }
    break;
    case ET_TEXT:
        if((FindTextParams::FIND_ALL == findTarget) || (FindTextParams::FIND_TEXT == findTarget)) {
            if(findArgs.isTextMatched(text)) {
                isFound = true ;
            }
        }
        break;
    case ET_PROCESSING_INSTRUCTION: {
        if(FindTextParams::FIND_ALL == findTarget) {
            if(findArgs.isTextMatched(getPITarget()) || findArgs.isTextMatched(getPIData())) {
                isFound = true ;
            }
        }
    }
    break;
    case ET_COMMENT: {
        if(FindTextParams::FIND_ALL == findTarget) {
            if(findArgs.isTextMatched(getComment())) {
                isFound = true ;
            }
        }
    }
    break;
    }
    if(isFound) {
        findArgs.newOccurence(selfInfo.totalSize + childrenInfo.totalSize);
        if(!findArgs.isCountingOnly()) {
            selected();

        }
    }
    //append children
    if(isHiliteAll) {
        foreach(DomItem * value, childItems) {
            if(value->findText(findArgs)) {
                isFoundInChild = true ;
            }
        }
    }

    bool isFoundSomeWhere = isFoundInChild || isFound ;
    if(!findArgs.isCountingOnly()) {
        if(isCloseUnrelated && (NULL != ui)) {
            if(isFoundInChild) {
                if(!ui->isExpanded()) {
                    ui->setExpanded(true);
                }
            } else {
                if(ui->isExpanded()) {
                    ui->setExpanded(false);
                }
            }
        }
    }
    return isFoundSomeWhere  ;
}

void DomItem::unselected()
{
    QTreeWidgetItem *theUi = getUI();
    if(NULL != theUi) {
        theUi->setBackgroundColor(0, QColor(0xFF, 0xFF, 0xFF, 0));
    }
}

void DomItem::selected()
{
    QTreeWidgetItem *theUi = getUI();
    if(NULL != theUi) {
        theUi->setBackgroundColor(0, QColor(0xFF, 0xC0, 0x40));
    }
    parentRule->addSelected(this);
}

bool DomItem::isMixedContent()
{
    foreach(DomItem * value, childItems) {
        if(value->type == ET_TEXT) {
            return true ;
        }
    }
    return false;
}

QVector<DomItem*> & DomItem::getParentChildren()
{
    if(NULL == parentItem) {
        return parentRule->getItems();
    } else {
        return parentItem->childItems;
    }
}

QTreeWidgetItem *DomItem::findNextBrother(QVector<DomItem*> &items)
{
    int indexOfSelf = items.indexOf(this);
    int size = items.size();
    if((indexOfSelf >= 0) && (indexOfSelf < (size - 1))) {
        return items.at(indexOfSelf + 1)->ui ;
    }
    return NULL;
}

QTreeWidgetItem *DomItem::goToNextBrother()
{
    return findNextBrother(getParentChildren());
}

QTreeWidgetItem *DomItem::findPreviousBrother(QVector<DomItem*> &items)
{
    int indexOfSelf = items.indexOf(this);
    if(indexOfSelf > 0) {
        return items.at(indexOfSelf - 1)->ui ;
    }
    return NULL;
}

QTreeWidgetItem *DomItem::goToPreviousBrother()
{
    return findPreviousBrother(getParentChildren());
}

void DomItem::isFirstOrLastChild(bool &isFirst, bool &isLast)
{
    findFirstAndLast(getParentChildren(), isFirst, isLast);
}

void DomItem::findFirstAndLast(QVector<DomItem*> &items, bool &isFirst, bool &isLast)
{
    int indexOfSelf = items.indexOf(this);
    if(indexOfSelf > 0) {
        isFirst = false;
    } else {
        isFirst = true ;
    }
    int size = items.size();
    if(indexOfSelf < (size - 1)) {
        isLast = false;
    } else {
        isLast = true ;
    }
}

void DomItem::refreshUI()
{
    parentRule->redisplayItem(this);
}

void DomItem::displayWithPaintInfo(PaintInfo *paintInfo)
{
    if(NULL != ui) {
        display(ui, paintInfo);
    }
}

QString DomItem::formatRowNumber(const int index)
{
    QString str = QString::number(index, 16);
    return str.rightJustified(6, '0', true);
}

QString DomItem::topLevelItemIndex(QTreeWidgetItem *topLevelItem)
{
    int position = ui->treeWidget()->indexOfTopLevelItem(topLevelItem);
    return formatRowNumber(position);
}

/**
  * swaps a child with a new element ans return its position
  */
int DomItem::setItemLike(DomItem *newItem, DomItem* oldItem)
{
    int pos = childItems.indexOf(oldItem);
    if(pos >= 0) {
        childItems.insert(pos, newItem);
    }
    return pos;
}

QString DomItem::getRow()
{
    QString result = "";
    if(NULL != ui) {
        QTreeWidgetItem *parent = ui->parent();
        if(NULL == parent) {
            return topLevelItemIndex(ui);
        }
        QTreeWidgetItem *child = ui;
        while(NULL != parent) {
            result = formatRowNumber(parent->indexOfChild(child)) + result;
            child = parent;
            parent = parent->parent();
        }
        result = topLevelItemIndex(child) + result;
    }
    return result;
}

void DomItem::hideBrothers()
{
    int indexOfThis = -1 ;
    int size = 0;
    QVector<DomItem*> *elems = NULL ;
    if(NULL == parentItem) {
        QVector<DomItem*> *items = parentRule->getChildItems();
        size = items->size();
        indexOfThis = items->indexOf(this);
        elems = items;
    } else {
        indexOfThis = parentItem->childItems.indexOf(this);
        size = parentItem->childItems.size();
        elems = this->parentItem->getChildItems();
    }
    if((indexOfThis < 0) || (indexOfThis >= size))
        return ;
    int previousIndex = indexOfThis - 1 ;
    int nextIndex = indexOfThis + 1 ;

    QVectorIterator<DomItem*> it(*elems);
    PaintInfo *paintInfo = parentRule->getPaintInfo();
    int index = 0 ;
    while(it.hasNext()) {
        DomItem *elm = it.next();
        if(indexOfThis == index) {
            elm->setVisibilityStateShow();
        } else if((index == previousIndex) || (index == nextIndex)) {
            elm->setVisibilityStateEllipsis();
            if(elm->ui->isExpanded()) {
                elm->ui->setExpanded(false);
            }
            QVectorIterator<DomItem*> it(elm->childItems);
            while(it.hasNext()) {
                DomItem *el = it.next();
                if(NULL != el->ui) {
                    el->ui->setHidden(true);
                }
            }
        } else {
            elm->setVisibilityStateHidden();
        }
        elm->displayWithPaintInfo(paintInfo);
        index ++ ;
    }
}

void DomItem::showBrothers()
{
    int indexOfThis = -1 ;
    int size = 0;
    QVector<DomItem*> *elems = NULL ;
    if(NULL == parentItem) {
        QVector<DomItem*> *items = parentRule->getChildItems();
        size = items->size();
        indexOfThis = items->indexOf(this);
        elems = items;
    } else {
        indexOfThis = parentItem->childItems.indexOf(this);
        size = parentItem->childItems.size();
        elems = this->parentItem->getChildItems();
    }
    if((indexOfThis < 0) || (indexOfThis >= size))
        return ;

    QVectorIterator<DomItem*> it(*elems);
    PaintInfo *paintInfo = parentRule->getPaintInfo();
    int index = 0 ;
    while(it.hasNext()) {
        DomItem *elm = it.next();
        if(elm->isVisibilityStateEllipsis()) {
            QVectorIterator<DomItem*> it(elm->childItems);
            while(it.hasNext()) {
                DomItem *el = it.next();
                if(NULL != el->ui) {
                    el->ui->setHidden(false);
                }
            }
        }
        elm->resetVisibilityState();
        if(elm->ui->isHidden()) {
            elm->ui->setHidden(false);
        }
        elm->displayWithPaintInfo(paintInfo);
        index ++ ;
    }
}

bool DomItem::isNormalViewState()
{
    return visibilityState == EVN_NORMAL ;
}

void DomItem::resetVisibilityState()
{
    visibilityState = EVN_NORMAL ;
}

void DomItem::setVisibilityStateEllipsis()
{
    visibilityState = EVN_ELLIPSIS ;
}

void DomItem::setVisibilityStateHidden()
{
    visibilityState = EVN_HIDDEN;
}

void DomItem::setVisibilityStateShow()
{
    visibilityState = EVN_SHOW ;
}

bool DomItem::isVisibilityStateEllipsis()
{
    return visibilityState == EVN_ELLIPSIS ;
}

QList<Attribute*>DomItem::getAttributesList()
{
    QList<Attribute*>attrList;
    attrList = attributes.toList();
    return attrList ;
}

Attribute* DomItem::getAttribute(const QString &attributeName)
{
    foreach(Attribute * attribute, attributes) {
        if(attribute->name == attributeName) {
            return attribute;
        }
    }
    return NULL ;
}


void DomItem::setZoomFactor(const int zoom)
{
    if(NULL != attrFont) {
        attrFont->setPointSize(VStyle::getZoomFontSize(defaultAttrFonts, zoom));
    }
    int newSize = VStyle::getZoomFontSize(fixedSizeAttrFonts, zoom) ;
    if(newSize > 0) {
        fixedWidthFont.setPointSize(VStyle::getZoomFontSize(fixedSizeAttrFonts, zoom));
    }
}


int DomItem::textSize()
{
    int size = 0;
    QVectorIterator<TextChunk*> tt(textNodes);
    while(tt.hasNext()) {
        TextChunk   *tx = tt.next();
        size += tx->text.length();
    }
    return size;
}

void DomItem::recalcSize(const bool isRecursive)
{
    int sizeOfData ;
    selfInfo.reset();
    if(isRecursive) {
        childrenInfo.reset();
    }

    selfInfo.numItems = childItems.size();

    switch(type) {
    default:
    case ET_ELEMENT: {
        // appends itself
        sizeOfData = textSize();
        selfInfo.totalSize += tag().length() * 2 + 5;
        selfInfo.totalSize += sizeOfData ;

        //itera sulla lista e prendi i valori dalla chiabe
        QVectorIterator<Attribute*>  attrs(attributes);
        while(attrs.hasNext()) {
            Attribute* attribute = attrs.next();
            selfInfo.totalSize += attribute->name.length() * 2 + 5;
            selfInfo.totalSize += attribute->value.length() ;
        }

        //append children
        if(isRecursive) {
            foreach(DomItem * value, childItems) {
                value->recalcSize(true);
                collectChildInfo(value, true);
            }
        }
    }
    break;

    case ET_PROCESSING_INSTRUCTION: {
        sizeOfData = getPITarget().length() + getPIData().length();
        selfInfo.totalSize = 5 + sizeOfData ;
    }
    break;

    case ET_COMMENT: {
        sizeOfData = getComment().length();
        selfInfo.totalSize = 7 + sizeOfData ;
    }
    break;
    case ET_TEXT:
        sizeOfData = text.length();
        selfInfo.totalSize = sizeOfData ;
        break;
    }
}

void DomItem::recalcChildSize()
{
    childrenInfo.reset();
    selfInfo.numItems = childItems.size();

    switch(type) {
    default:
        break;
    case ET_ELEMENT: {
        foreach(DomItem * child, childItems) {
            collectChildInfo(child, true);
        }
    }
    break;
    }
}


void DomItem::propagateChildInfoChange()
{
    if(parentRule->collectSizeData()) {
        if(NULL != parentItem) {
            parentItem->recalcChildSize();
            parentItem->displayWithPaintInfo(parentRule->getPaintInfo());
            parentItem->propagateChildInfoChange();
        }
    }
}

void DomItem::collectChildInfo(DomItem *child, const bool isAdd)
{
    if(isAdd) {
        childrenInfo.numItems += child->selfInfo.numItems;
        childrenInfo.totalSize += child->selfInfo.totalSize;
        childrenInfo.numItems += child->childrenInfo.numItems;
        childrenInfo.totalSize += child->childrenInfo.totalSize;
    } else {
        childrenInfo.numItems -= child->selfInfo.numItems;
        childrenInfo.totalSize -= child->selfInfo.totalSize;
        childrenInfo.numItems -= child->childrenInfo.numItems;
        childrenInfo.totalSize -= child->childrenInfo.totalSize;
    }
}


void DomItem::removeChildInfo(DomItem *childToRemove)
{
    if((parentRule != NULL) && parentRule->collectSizeData()) {
        collectChildInfo(childToRemove, false);
        propagateChildInfoChange();
    }
}

void DomItem::addChildInfo(DomItem *child)
{
    if((parentRule != NULL) && parentRule->collectSizeData()) {
        collectChildInfo(child, true);
        propagateChildInfoChange();
    }
}


void DomItem::updateSizeInfo()
{
    if((parentRule != NULL) && parentRule->collectSizeData()) {
        recalcSize(false);
        propagateChildInfoChange();
    }
}

void DomItem::incrementSizeInfo(const int size)
{
    selfInfo.totalSize += size ;
}

QString DomItem::tag()
{
    return _tag;
}

void DomItem::namespaceofItem(QString &elNamespace, QString &elLocalName)
{
    QStringList ns = _tag.split(':');
    if(ns.length() < 2) {
        elNamespace = "" ;
        elLocalName = _tag;
    } else {
        elNamespace = ns.at(0);
        elLocalName = ns.at(1);
    }
}

QString DomItem::transformToText()
{
    QDomDocument    document;
    QString text ;
    if(generateDom(document, document)) {
        text = document.toString(4);
    }
    return text ;
}

int DomItem::indexOfSelfAsChild()
{
    if(NULL != parentItem) {
        return parentItem->childItems.indexOf(this);
    } else {
        if(NULL != parentRule) {
            return parentRule->indexOfTopLevelItem(this);
        } else {
            return -1 ;
        }
    }
}

bool DomItem::areChildrenLeavesHidden(QTreeWidgetItem *twi)
{
    if(NULL == twi) {
        return false;
    }
    QVariant res = twi->data(0, ShowDataRole);
    return res.toBool();
    //return twi->data(0, ShowDataRole).toBool();
}

void DomItem::setChildrenLeavesHiddenState(QTreeWidgetItem *twi, const bool newState)
{
    if(NULL != twi) {
        QVariant vState(newState);
        twi->setData(0, ShowDataRole, vState);
        //twi->setData(0, ShowDataRole, QVariant(newState));
    }
}

bool DomItem::hasItemInChildren()
{
    foreach(DomItem * child, getItems()) {
        if(child->getType() == DomItem::ET_ELEMENT) {
            return true ;
        }
    }
    return false;
}

bool DomItem::isALeaf()
{
    return !hasItemInChildren();
}

void DomItem::hideChildrenLeaves()
{
    setChildrenLeavesHiddenState(ui, true);
    if(!hasChildren()) {
        if(NULL != ui) {
            ui->setHidden(true);
        }
    } else {
        displayWithPaintInfo(parentRule->getPaintInfo());
    }
    foreach(DomItem * theChild, childItems) {
        theChild->hideChildrenLeaves();
    }
}

void DomItem::showChildrenLeaves()
{
    setChildrenLeavesHiddenState(ui, false);
    if(!hasChildren()) {
        if(NULL != ui) {
            ui->setHidden(false);
        }
    } else {
        displayWithPaintInfo(parentRule->getPaintInfo());
    }
    foreach(DomItem * theChild, childItems) {
        theChild->showChildrenLeaves();
    }
}

//returns the position of the element
QList<int> DomItem::indexPath()
{
    QList<int> list ;

    DomItem *parentE = parentItem;
    DomItem *target = this ;
    while(parentE != NULL) {
        list.prepend(parentE->childIndex(target));
        target = parentE ;
        parentE = parentE->parentItem ;
    }
    list.prepend(parentRule->getChildItems()->indexOf(target));

    return list ;
}

QStringList DomItem::path()
{
    QStringList list ;

    DomItem *parentE = parentItem;
    while(parentE != NULL) {
        list.prepend(parentE->tag());
        parentE = parentE->parentItem ;
    }
    return list ;
}

bool DomItem::copyTextNodesToTarget(DomItem *target)
{
    if(NULL != target) {
        copyHeaderAndDirectNodes(*target);
        QList<DomItem*> ItemsToRemove;
        QList<DomItem*> ItemsToMaintain;

        foreach(DomItem * e, target->childItems) {
            if(e->getType() == DomItem::ET_TEXT) {
                ItemsToRemove.append(e);
            } else {
                ItemsToMaintain.append(e);
            }
        }
        foreach(DomItem * e, ItemsToRemove) {
            e->autoDelete(true);
            // delete it from the user interface too
        }
        // now the second list has elements only, no text nodes.
        int index = 0 ; // This is the index of the second list.
        int sourceIndex = 0 ; // This is the index of the second list.

        foreach(DomItem * e, childItems) {
            if(e->getType() == DomItem::ET_TEXT) {

                DomItem *textItem = new DomItem(target->getParentRule(), DomItem::ET_TEXT, target);
                textItem->setTextOfTextNode(e->text, e->isCDATA()) ;
                //textItem->markEdited();
                target->getItems().insert(sourceIndex, textItem);
                textItem->setChildItem(target->getUI()->treeWidget(), target->getUI(), target->getParentRule()->getPaintInfo(), true, sourceIndex);
            }
            index ++;
        } // foreach
        target->display(target->getUI(), target->getParentRule()->getPaintInfo());
        // Now, check if the elements correspond between the two implementations
        int numChildrenSource = getChildItemsNumber();
        int numChildrenTarget = target->getChildItemsNumber();
        if(numChildrenSource  != numChildrenTarget) {
            return false;
        }

        // Now, make sure that the new list is the current one for the target element.
        for(int i = 0 ; i < numChildrenSource ; i ++) {
            DomItem * sourceItem = childItems.at(i) ;
            DomItem * targetItem = target->childItems.at(i) ;
            // check for synchronization
            if((sourceItem->getType() != targetItem->getType())
                    || (sourceItem->tag() != targetItem->tag())
                    || (sourceItem->text != targetItem->text)) {
                return false;
            }
        } // for children
        return true;
    }
    return false;
}


//----------------------------------------------------------------

Attribute::Attribute()
{
}

Attribute::Attribute(const QString &newName, const QString &newValue)
{
    name = newName;
    value = newValue ;
}


Attribute::~Attribute()
{
}


