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

#ifndef DOMITEM_H
#define DOMITEM_H

#include <QtXml/QDomNode>
#include <QHash>
#include <QtGui>
#include <QRegExp>

#include "global.h"
#include "paintinfo.h"

class DomModel;
class FindTextParams;

// Descripe the textNode child of a XML node
// relative to QDomText node
class TextChunk
{
public:
    QString text;
    bool isCDATA;

    TextChunk(const bool isCDATASection, const QString &txt);

    TextChunk *clone();
};

#define NO_ERROR (0)
#define ERROR_1 (1)
class QXmlException
{
public:
    QString cause;
    int code;
    QXmlException(const int newCode, const QString &theCause) {
        code = newCode;
        cause = theCause;
    }
};

// Attribute of a XML node
// relative to QDomAttribute
class Attribute
{
public:
    QString name;
    QString value;

    Attribute();
    Attribute(const QString &newName, const QString &newValue);
    ~Attribute();
};

// Node information
class ItemInfo
{
public:
    int numItems;
    int totalSize;

    ItemInfo();
    ~ItemInfo();

    void reset();
};

// the Node description class
// relative to QDomNode
class DomItem
{
    Q_DECLARE_TR_FUNCTIONS(DomItem)
public:
    static const int MAX_LIMIT_TEXTLEN = 100;
    static const int ATTR_PER_COLUMN = 5;
    static const int WIDTH_LEN_CHARS = 6;

#define DEFAULT_FIXEDWIDTHFONT "Courier"

    enum EViewModes {
        E_VM_NONE,
        E_VM_BASE64TEXT,        //a base 64 text
        E_VM_BASE64XML,         //Base 64 coded XML
        E_VM_XML,               //an XML as payload
    };

    QString text;
    QString _tag;
    QString tag();
//    bool isShowTextBase64;
    bool wasOpen;
    ItemInfo selfInfo;
    ItemInfo childrenInfo;
    bool _isCData;

    static QFont fixedWidthFont;
    static QFont *attrFont;
    static int defaultAttrFonts;
    static int fixedSizeAttrFonts;

    enum ItemType { ET_ELEMENT, ET_PROCESSING_INSTRUCTION, ET_COMMENT, ET_TEXT};
    enum NodeType { ICD_SCL, ICD_HEADER, ICD_TEXT, ICD_SUBSTATION, ICD_COMMUNICATION, ICD_IED, ICD_DATATYPETEMPLATES};

    DomItem(const QString newTag, const QString &text, DomModel *model, DomItem *parent = 0);
    DomItem(DomModel *model, const ItemType newType, DomItem *parent);
    DomItem(DomModel *model);
    ~DomItem();
    DomItem *child(int i);
    DomItem *parent();

    void namespaceofItem(QString &itemNamesapce, QString &itemLocalName);

    static QRegExp terminatorSearch;
    static bool firstTimeFixedWidthFont;
    static QString textCompactViewPrefix;

    void setChildItem(QTreeWidget *pTree, QTreeWidgetItem *parent, PaintInfo *panitInfo, const bool isGUI = true, const int pos = -1);
    void display(QTreeWidgetItem *me, PaintInfo *paintInfo);
    void displayRecursive(PaintInfo *paintInfo);
    void displayWithPaintInfo(PaintInfo *paintInfo);
    void refreshUI();

    bool isEmpty() const;
    bool generateDom(QDomDocument &document, QDomNode &parent);

    void clearAttributes();
    void addAttribute(const QString &name, const QString &value);
    void addChild(DomItem *newChild);
    void addChildAt(DomItem *newItem, const int position);
    int addChildAfter(DomItem *newItem, DomItem *brotherItem);

    bool hasChildOfName(const QString &name);

    bool moveDown(DomItem *item);
    bool moveUp(DomItem *item);

    static bool moveDown(QVector<DomItem*> &items, DomItem *item);
    static bool moveUp(QVector<DomItem*> &items, DomItem *item);

    void autoDelete(const bool deleteMe);
    void autoDeleteRecursive();

    static DomItem *fromItemData(QTreeWidgetItem *item);
    static DomItem *fromModelIndex(const QModelIndex & index);

    DomItem *copyToClipboard();
    DomItem *cutTOClipboard();
    DomItem *copyTo(DomItem &newItem);
    DomItem *copyTo(DomItem &newItem, const bool isRecursive);
    void copyHeader(DomItem &newItem);
    void copyHeaderAndDirectNodes(DomItem &newItem);

    QTreeWidgetItem *getUI() const {
        return ui;
    }
    bool isFirstChild();
    bool isLastChild();

    void expand(QTreeWidget *tree);
    void deleteUI();

    void setText(const QString &data);
    void setTextOfTextNode(const QString &data, const bool isCData);

    ItemType getType() const {
        return type;
    }

    NodeType getNodeType() const {
        return nodeType;
    }
    QVector<DomItem*> *getChildItems() {
        return &childItems;
    }
    int getChildItemsNumber() {
        return childItems.size();
    }

    QVector<DomItem *> &getItems() {
        return childItems;
    }

    DomItem *getChildAt(const int childIndex);
    int childIndex(DomItem *child);

    QVector<TextChunk*> &getTextChunks() {
        return textNodes;
    }

    int getTextChunksNumber() {
        return textNodes.size();
    }

    bool hasChildren() {
        return !childItems.isEmpty();
    }

    const QString &getComment();
    void setComment(const QString &Comment);
    static void loadIcons();

    //Attributes
    QVector<Attribute*> attributes;

    void addTextNode(TextChunk *text);
    void clearTextNodes();
    bool isElement() const {
        return (ET_ELEMENT == type);
    }

    QString attributeValueOfName(const QString &name);

    const QString &getPITarget();
    const QString getPIData();
    void setPITarget(const QString &target);
    void setPIData(const QString &data);

    bool findText(FindTextParams &findArgs);
    bool searchInScope(FindTextParams &findArgs);

    void unselected();
    void selected();

    long getInstanceId() const {
        return instanceId;
    }

    QTreeWidgetItem *goToPreviousBrother();
    QTreeWidgetItem *goToNextBrother();
    void isFirstOrLastChild(bool &isFirst, bool &isLast);
    QString getRow();
    DomModel *getParentRule();

    //-- hide / show
    void hideBrothers();
    void showBrothers();
    bool isNormalViewState();
    void registerState();

//    bool isShownBase64() const;
//    void setShownBase64(const bool shownAs);

    QList<Attribute*> getAttributesList();
    Attribute *getAttribute(const QString &attributeName);

    QString getAsText();
    QString getAsSimpleText(const bool isBase64);
    QString getAsSimpleTextXml(const bool isBase64);

    bool isCDATA();
    void setAsSingleTextNode(const QString &newText, const bool isBase64, const bool isCData);

    EViewModes viewMode() const;
    void setViewMode(const EViewModes newMode);

    bool edited();
    bool saved();

    void recalcSize();
    int textSize();

    void updateSizeInfo();
    void modifiedChildInfo();
    void addChildInfo(DomItem *child);
    void removeChildInfo(DomItem *childToRemove);
    void recalcSize(const bool isRecursive);
    void incrementSizeInfo(const int size);
    int setItemLike(DomItem *newItem, DomItem *oldItem);
    QString transformToText();
    int indexOfSelfAsChild();
    bool isMixedContent();

    //returns the postion of the item
    QList<int> indexPath();
    QStringList path();
    // copy the firsth level attributes, text nodes and attributes to the target
    bool copyTextNodesToTarget(DomItem *target);

private:
    static const int ShowDataRole;
    static long instances;

    long instanceId;
    DomItem *parentItem;
    DomModel *parentRule;
    QTreeWidgetItem * ui;
    EViewModes _viewMode;
    bool _edited;
    bool _saved;

    void initItem(DomModel *model, DomItem *parent);

    void zeroUI();
    void zeroUISelf(const bool emitMe);

    QVector<TextChunk*> textNodes;
    ItemType type;
    NodeType nodeType;
    QVector<DomItem*> childItems;

    //***************************************
    enum EVisibilityState {
        EVN_NORMAL,
        EVN_SHOW,
        EVN_HIDDEN,
        EVN_ELLIPSIS
    };
    EVisibilityState visibilityState;

    //*****************************************
    static QBrush commentBrush;
    static QBrush defaultBrush;
    static QBrush procInstrBrush;
    static QBrush attrBrush;

    static bool isLoadedIcons;
    static QIcon procInstrIcon;
    static QIcon commentIcon;
    static QIcon elementIcon;
    static QIcon procInstrBkmIcon;
    static QIcon commentBkmIcon;
    static QIcon elementBkmIcon;
    static QIcon textIcon;
    static QIcon textBkmIcon;
    static QIcon childrenHiddenIcon;
    static QIcon childrenHiddenBkmIcon;

    static QIcon sclIcon;
    static QIcon headerIcon;
    static QIcon substationIcon;
    static QIcon communicationIcon;
    static QIcon iedIcon;
    static QIcon dataTypeIcon;

    void generateId();

    QTreeWidgetItem *findPreviousBrother(QVector<DomItem*> &items);
    QTreeWidgetItem *findNextBrother(QVector<DomItem*> &items);
    QVector<DomItem*> &getParentChildren();
    void findFirstAndLast(QVector<DomItem*> &items, bool &isFirst, bool &isLast);
    static QString formatRowNumber(const int index);
    QString topLevelItemIndex(QTreeWidgetItem *topLevelItem);
    void resetVisibilityState();
    void setVisibilityStateEllipsis();
    void setVisibilityStateHidden();
    void setVisibilityStateShow();
    bool isVisibilityStateEllipsis();
    void createFixedWidthFonts();
    QFont createItemFonts(QFont defaultFont);
    const QString styleItemTag(QTreeWidgetItem *me, PaintInfo *PaintInfo);

    void collectChildInfo(DomItem *child, const bool isAdd);
    void propagateChildInfoChange();
    void recalcChildSize();

    static QString limitTextWithEllipsis(const QString &inputText);
    void autoDeleteRecursiveInner();

    void setChildrenLeavesHiddenState(QTreeWidgetItem *twi, const bool newState);

public:
    bool areChildrenLeavesHidden(QTreeWidgetItem *twi);

    static void setZoomFactor(const int zoom);
    void hideChildrenLeaves();
    void showChildrenLeaves();
    bool isALeaf();
    bool hasItemInChildren();

    const QString styleItemTagString(PaintInfo *paintInfo);
    QFont styleItemTagFont(PaintInfo *paintInfo);
    QBrush styleItemTagColor(PaintInfo *paintInfo);
    QIcon styleItemTagIcon();
    QVariant columnViewTooltipData();
    QVariant columnViewDisplayData(PaintInfo *paintInfo, const int rowOrdinal);

    QIcon iconForNode();
};

#endif
