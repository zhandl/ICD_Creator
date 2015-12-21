#ifndef DATATYPEMODEL_H
#define DATATYPEMODEL_H

#include <QAbstractItemModel>
#include <QtXml/QDomDocument>
#include <QtXml/QDomNode>
#include <QVariant>
#include <QtGui>

#include "global.h"
#include "datatypeitem.h"
#include "paintinfo.h"

class DomItem;
class DocumentType;

class DataTypeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit DataTypeModel(QDomDocument &document, const QString &name);
    DataTypeModel();
    ~DataTypeModel();

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
    void setPaintInfo(PaintInfo *newValue);

    void setTreeValue(QTreeWidget *pTree);
    void setNewTemplateTreeValue(QTreeWidget *pTree);
    DataTypeItem *root() const;

    void setRootItem(DataTypeItem *root);

    DataTypeItem *newItem(const QString &tagName);

    QString &fileName();
//    void setFileName(const QString &newFileName);

    void redisplay();
    void redisplayItem(DataTypeItem *item);

    QVector<DataTypeItem*> &getItems() {
        return childItems;
    }

    QVector<DataTypeItem*> *getChildItems() {
        return &childItems;
    }

    QVector<DataTypeItem*> &getDoTypeItems() {
        return DoTypeItemPool;
    }

    QVector<DataTypeItem*> &getDaTypeItems() {
        return DaTypeItemPool;
    }

    QVector<DataTypeItem*> &getEnumTypeItems() {
        return EnumItemPool;
    }

    void notifyDeletionTopItem(DataTypeItem *item);
    void deleteItem(DataTypeItem *item);
    void takeOutItem(DataTypeItem *item);
    QString addNameToPool(const QString &inputString);
    QString getAttributeString(const QString &attributeName);
    QString addIdToPool(const QString &inputString);

    void addSelected(DataTypeItem *);
    void unSelected(DataTypeItem *);

    void setSelectedItemChecked();
    void setSelectedItemUnchecked();

    PaintInfo *getPaintInfo();
    QTreeWidgetItem *getSelItem(QTreeWidget*);
    void insertItemInternal(DataTypeItem *theNewElement, DataTypeItem *parentElement, QTreeWidget *tree);

//    void insertInternal(QTreeWidget *tree, DataTypeItem *parentElement, DataTypeItem *pasteElement);
    DataTypeItem* insertToNewTemplate(QTreeWidget *tree, DataTypeItem *parentElement, DataTypeItem *pasteElement);
    DataTypeItem* insertToNewTemplateInternal(DataTypeItem *parentElement, DataTypeItem *pasteElement);
private:
   DataTypeItem *rootItem;
   QVector<DataTypeItem*> childItems;
   QString _fileName;
   QHash<int, DataTypeItem*> selection;
   PaintInfo *paintInfo;

   QVector<DataTypeItem*> DoTypeItemPool;
   QVector<DataTypeItem*> DaTypeItemPool;
   QVector<DataTypeItem*> EnumItemPool;

   QSet<QString> _namesPool;
   QSet<QString> _attributeValuesPool;
   QSet<QString> _LNodeIdPool;

   DocumentType  *_docType;

   static int renameCounter;

   void setDocType(const QString &newDocType, const QString &systemId, const QString &publicId);
   void processDocument(QDomDocument &document);
   void assignMixedContentText(DataTypeItem *parent, const QString &text, const bool isCData, QVector<DataTypeItem*> *collection);
   DataTypeItem *setItem(QDomNode &node, DataTypeItem *parent, QVector<DataTypeItem*> *collection);

   bool write(const QString &filePath);
   QByteArray writeMemory();

   QDomDocument createNewDocument();
signals:

public slots:
//   void toggleSelection(QTreeWidgetItem *item, int column);

};

#endif // DATATYPEMODEL_H
