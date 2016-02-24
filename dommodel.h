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

#ifndef DOMMODEL_H
#define DOMMODEL_H

#include <QAbstractItemModel>
#include <QtXml/QDomDocument>
#include <QtXml/QDomNode>
#include <QVariant>
#include <QtGui>


#include "global.h"
#include "domitem.h"
#include "paintinfo.h"

class DomItem;
class DocumentType;

class LIBQXMLEDITSHARED_EXPORT DomModel : public QAbstractItemModel
{
    Q_OBJECT

    friend class TestXsd;

    static const int ModelName;
    static const int ModelValue;
    static const int ModelColumns;




    // constants
    enum EConsts {
        // undo limit
        UndoLimitCount = 10
    };
    QUndoStack _undoStack;
public:
    DomModel(QDomDocument & document, const QString &name);
    DomModel();
    ~DomModel();

    //**********************************  Model Interface
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    //******************************** end Model Interface

//    typedef struct fcda {
//        QString doName;
//        QString daName;
//        QString lnInst;
//        QString lnClass;
//        QString fc;
//        QString ldInst;
//    }_fcda;

    QString docType();
    void setDocType(const QString& newDocType, const QString &systemID, const QString &publicId);

    void setPaintInfo(PaintInfo *newValue);
    PaintInfo *getPaintInfo();

    void setTreeValue(QTreeWidget *pTree);
    bool isEmpty(const bool isRealElement);
    DomItem *root() const;
    void setRootItem(DomItem *newRoot);
    bool write(const QString &filePath);
    QByteArray writeMemory();
    QString getAsText();

    DomItem *newItem();
    DomItem *newItem(const QString &tagName);
    DomItem *newItem(const DomItem::ItemType newType);

    void setModified(const bool state);
    bool isModified() const;
    void setEmptyRoot();
    void expand(QTreeWidget *tree);

    QString &fileName();
    void setFileName(const QString &newFileName);

    void editServices(QWidget *const window, QTreeWidgetItem* pItem);

    void editAttribute(QWidget *const window, QTreeWidgetItem* pItem);
    void addText(QWidget *window, QTreeWidget *tree);
    void addPrivate(QWidget *window, QTreeWidget *tree);

    void addSubstation(QWidget *window, QTreeWidget *tree);
    void addCommunication(QWidget *window, QTreeWidget *tree);
    void addIED(QWidget *window, QTreeWidget *tree);
    void addDataTypeTemplates(QWidget *window, QTreeWidget *tree);

    void addHistory(QWidget *window, QTreeWidget *tree);
    void addHitem(QWidget *window, QTreeWidget *tree);

    void addSubNetwork(QWidget *window, QTreeWidget *tree);
    void addBitRate(QWidget *window, QTreeWidget *tree);
    void addConnectedAP(QWidget *window, QTreeWidget *tree);
    void addAddress(QWidget *window, QTreeWidget *tree);
    void addGSE(QWidget *window, QTreeWidget *tree);
    void addSMV(QWidget *window, QTreeWidget *tree);
    void addPhysconn(QWidget *window, QTreeWidget *tree);
    void addP(QWidget *window, QTreeWidget *tree);
    void addMinTime(QWidget *window, QTreeWidget *tree);
    void addMaxTime(QWidget *window, QTreeWidget *tree);

    void addServices(QWidget *window, QTreeWidget *tree);
    void addAccessPoint(QWidget *window, QTreeWidget *tree);
    void addServer(QWidget *window, QTreeWidget *tree);
    void addServerAt(QWidget *window, QTreeWidget *tree);
    void addGOOSESecurity(QWidget *window, QTreeWidget *tree);
    void addSMVSecurity(QWidget *window, QTreeWidget *tree);
    void addSubject(QWidget *window, QTreeWidget *tree);
    void addIssuerName(QWidget *window, QTreeWidget *tree);
    void addAuthentication(QWidget *window, QTreeWidget *tree);
    void addLDevice(QWidget *window, QTreeWidget *tree);
    void addAssociation(QWidget *window, QTreeWidget *tree);

    void addLN0(QWidget *window, QTreeWidget *tree);
    void addLN(QWidget *window, QTreeWidget *tree);
    void addAccessControl(QWidget *window, QTreeWidget *tree);
    void addDataSet(QWidget *window, QTreeWidget *tree);
    void addReportControl(QWidget *window, QTreeWidget *tree);
    void addLogControl(QWidget *window, QTreeWidget *tree);
    void addInputs(QWidget *window, QTreeWidget *tree);
    void addLog(QWidget *window, QTreeWidget *tree);
    void addGSEControl(QWidget *window, QTreeWidget *tree);
    void addSMVControl(QWidget *window, QTreeWidget *tree);
    void addSettingControl(QWidget *window, QTreeWidget *tree);

    void addChild(QWidget *window, QTreeWidget *tree);
    void addChild(QWidget *window, QTreeWidget *tree, DomItem *preItem);
    DomItem* addChildToItem(QWidget *window, QTreeWidget *tree, DomItem *parentItem, const QString &itemTag, const bool useUndo = false, int position = -1);
    void addBrother(QWidget *window, QTreeWidget *tree);
    void addBrother(QWidget *window, QTreeWidget *tree, DomItem *theNewItem);
    void paste(QWidget *window, QTreeWidget *tree, DomItem *pasteItem);
    void pasteInternals(QTreeWidget *tree, DomItem *parentItem, DomItem *pasteItem, const int position);
    void pasteNoUI(DomItem *pasteItem, DomItem *pasteTo);
    void insertInternal(QTreeWidget *tree, DomItem *parentItem, DomItem *pasteItem, const int position);

    void redisplay();
    void redisplayItem(DomItem *domItem);
    bool editItem(QWidget * const parentWindow, QTreeWidgetItem *item);
    bool editEntry(QWidget *const parentWindow, const QString &title, const QString &label, const QString &actualText, QString &result);

    bool addTopItem(DomItem *theNewItem, const int position = -1);
    void notifyDeletionTopItem(DomItem *pEL);
    void appendComment(QWidget *window, QTreeWidget *tree);
    void appendComment(QWidget *window, QTreeWidget *tree, DomItem *newComment);
    void addComment(QWidget *window, QTreeWidget *tree);
    void addComment(QWidget *window, QTreeWidget *tree, DomItem *newComment);
    void appendProcessingInstruction(QWidget *window, QTreeWidget *tree);
    void appendProcessingInstruction(QWidget *window, QTreeWidget *tree, DomItem *newPI);
    void addProcessingInstruction(QWidget *window, QTreeWidget *tree);
    void addProcessingInstruction(QWidget *window, QTreeWidget *tree, DomItem *newPI);

    QVector<DomItem*> &getItems() {
        return childItems;
    }
    QVector<DomItem*> *getChildItems() {
        return &childItems;
    }

    QVector<DomItem*> getDataTypeItems() {
        return _dataTypeItems;
    }

    QVector<DomItem*> getDoTypeItems() {
        return _doTypeItems;
    }

    QVector<DomItem*> getDaEnumItems() {
        return _daEnumTypeItems;
    }

//    QVector<_fcda*> getDataSetItems() {
//        return _dataSetItems;
//    }

    DomItem *getDataTypeItemWithId(const QString &lnType);

    static QBrush setBkBrush;

    void findText(FindTextParams &FindArgs, DomItem *seletedItem);
    void unseleted();

    void takeOutItem(DomItem *item);
    void addSelected(DomItem *item);
    void unseletedAll();

    bool loadXplore(const QString &fileName);

    QString documentXsd() {
        return _documentXsd;
    }

    QString userDefinedXsd() {
        return _userDefinedXsd;
    }



    void setUserAndDocumentXsd(const QString &newXsd);

    void setUserDefinedXsd(const QString &path);
    void pasteXML(QWidget *window, QTreeWidget *tree, DomModel *newModel);

    bool collectSizeData();
    void setCollectSizeData(const bool isCollect);
    void assignCollectSizeDataFlag(const bool isCollect);

    QString addNameToPool(const QString &inputString);
    QString getAttributeString(const QString &attributeName);
    bool isValidXsd();
    void transformInComment(QWidget *window, QTreeWidget *tree, DomItem *itemToTransform);
    bool generateFromComment(QTreeWidget *tree, DomItem* itemToTranform);
    int indexOfTopLevelItem(DomItem *item);
    bool hasMoreThanOneXsdFile();

    DomItem *findChildItemByArray(DomItem *item, QList<int> &selection, const int listPos);
    DomItem *findItemByArray(QList<int> &selection);

    enum EInsSchemaRefInfo {
        INSERT_SCHEMA_ATTR_NOERROR = 0,
        INSERT_SCHEMA_ATTR_ERROR_NOROOT,
        INSERT_SCHEMA_ATTR_INFO_SCHEMAPRESENT,
        INSERT_SCHEMA_ATTR_INFO_REFPRESENT
    };
    EInsSchemaRefInfo insertNoNamespaceSchemaReferenceAttributes();
    EInsSchemaRefInfo insertSchemaReferenceAttributes();

    QString textOfCantEditMixedContentItemText();
    void hideLeafNodes();
    void showLeafNodes();

    bool moveUp(DomItem *item);
    bool moveDown(DomItem *item);
    bool internalMoveUp(DomItem *item, const bool registerInUndo);
    bool internalMoveDown(DomItem *item, const bool registerInUndo);

    void redo();
    void undo();
    bool canUndo();
    bool canRedo();
    int undoCount();

    bool checkIfUIItemsCorrespondToItems(DomItem *target);

    bool deleteItem(DomItem *item);
    bool deleteItem(DomItem *item, const bool isAutoDelete);

    void emptyUndoStack();
    void dumpDocument(QDomDocument &document);

signals:
    void wasModified();
    void undoStateChanged();
    void uiDeleted(DomItem *item);
    void docTypeChanged(const QString &docType);

private:
    DomItem *rootItem;
    // Items
    QVector<DomItem*> childItems;
    QString   xmlFileName;
    bool      modified;
    QHash<int, DomItem*> selection;
    PaintInfo  *paintInfo;


//    QVector<_fcda*> _dataSetItems;

    // XSD file referenced in the document
    QString _noNameSpaceXsd;
    QString _documentXsd;
    QHash<QString, QString> _namespacesByPrefixAndName;  // list of namespaces
    QHash<QString, QString> _namespacesByNameAndPrefix;  // inverse of the previous
    QHash<QString, QString> _schemaLocationsByNamespace; // list of schemas
    QString _userDefinedXsd;

    // collect size information about items while editing
    bool    _collectSizeData;
    QMap<QString, int>  _namesMap;
    QSet<QString>       _namesPool;
    QSet<QString>       _attributeValuesPool;
    DocumentType        *_docType;

    QVector<DomItem *> _dataTypeItems;
    QVector<DomItem *> _doTypeItems;
    QVector<DomItem *> _daEnumTypeItems;

    void clear();
    void clearUndo();
    void addUndoInsert(QTreeWidget *tree, DomItem *item);
    QTreeWidgetItem *getSelItem(QTreeWidget *tree);
    bool editNodeItemAsXML(const bool isBase64Coded, DomItem *pItem);
    bool editNodeItem(QWidget *const parenteWindow, DomItem *pItem);
    bool editNodeComment(QWidget *const parentWindow, DomItem *pItem);
    bool editTextNodeItem(QWidget *const parentWindow, const bool isBase64Coded, DomItem *pItem);
    void recalcSize();

    bool editServicesItem(QWidget *const parentWindow, DomItem *pItem);

    bool editLNodeItem(QWidget *const parenteWindow, DomItem *pItem);
    bool editDataSetItem(QWidget *const parentWindow, DomItem *pItem);
    bool editReportControlItem(QWidget *const parentWindow, DomItem *pItem);

    void checkValidationReference();
    void decodeASchema(const QString &value);

    int setTopLevelItemLike(DomItem *newItem, DomItem *oldItem);
    int swapAndDeleteItem(DomItem *newItem, DomItem *oldItem);

    void insertItemInternal(DomItem *theNewItem, DomItem *parentItem, QTreeWidget *tree);
    void insertItemInternal(DomItem *theNewItem, DomItem *parentItem, QTreeWidget *tree, const bool useUndo, int position);
    void appendItemInternal(DomItem *theNewItem, DomItem *brotherItem, QTreeWidget *tree, const bool useUndo = true);
    void afterInsertHousekeeping(DomItem *theNewItem, QTreeWidget *tree);
    void afterInsertHousekeeping(DomItem *theNewItem, QTreeWidget *tree, const bool useUndo);
    void assignMixedContentText(DomItem *parent, const QString &text, const bool isCData, QVector<DomItem*> *collection);
    DomItem *setItem(QDomNode &node, DomItem *parent, QVector<DomItem*> *collection);
    bool addUndoDeleteItem(DomItem *item);
    bool editAndSubstituteTextInNodeItemInternal(QWidget *const parentWindow, DomItem *pItem);
    void init();
    void processDocument(QDomDocument &document);
    QDomDocument createNewDocument();
};

// external edit
bool EditCommentNode(QWidget *parent, DomItem *pTarget);
bool editProcessingInstruction(QWidget *const parentWindow, DomItem *pItem);

#endif  // DOMMODEL_H
