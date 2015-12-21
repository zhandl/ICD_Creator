#ifndef DATATYPEITEM_H
#define DATATYPEITEM_H


#include <QtXml/QDomNode>
#include <QHash>
#include <QtGui>
#include <QRegExp>
#include <QFont>

#include "global.h"
#include "paintinfo.h"
#include "domitem.h"

class DataTypeModel;
class TextChunk;
class Attribute;
class ItemInfo;

class DataTypeItem : public QObject
{
    Q_OBJECT


public:

    enum ItemType { ET_ELEMENT, ET_TEXT, ET_PROCESSING_INSTRUCTION, ET_COMMENT};

    DataTypeItem(const QString newTag, const QString &text, DataTypeModel *model, DataTypeItem *parent = 0);
    DataTypeItem(DataTypeModel *model, ItemType newType, DataTypeItem *parent);
    DataTypeItem(DataTypeModel *model);
    ~DataTypeItem();
    DataTypeItem *child(int i);
    DataTypeItem *parent();

    static int renameIdCount;

    void setText(const QString &data);
    void setTextOfTextNode(const QString &data, const bool isCData);

    void registerState();
    void displayChildItemSelected(QTreeWidget *pTree, QTreeWidgetItem *parentItem, PaintInfo *paintInfo);
    void displayChildItem(QTreeWidget *pTree, QTreeWidgetItem *parentItem, PaintInfo *paintInfo);
    void display(QTreeWidgetItem *me, PaintInfo *paintInfo, bool isNewTemplate);
    void displayRecursive(PaintInfo *paintInfo);
    void displayWithPaintInfo(PaintInfo *paintInfo);

    static DataTypeItem *fromItemData(QTreeWidgetItem *item);
    static DataTypeItem *fromModelIndex(const QModelIndex &index);

    DataTypeItem *copyTo(DataTypeItem &newItem);
    DataTypeItem *copyTo(DataTypeItem &newItem, const bool isRecursive);
    void copyHeader(DataTypeItem &newItem);
    void copyHeaderAndDirectNodes(DataTypeItem &newItem);
    DataTypeItem *copyToNewTemplate(DataTypeModel *newModel, DataTypeItem &newItem);

    void calcCheckState();
    void autoDelete(const bool isAuto = true);
    void deleteUI();
    void zeroUI();
    void zeroUISelf();

    QString attributeValueOfName(const QString &name);

    ItemType getType() const {
        return type;
    }

    QVector<DataTypeItem*> *getChildItems() {
        return &childItems;
    }

    int getChildItemsNumber() {
        return childItems.size();
    }

    QVector<DataTypeItem*> &getItems() {
        return childItems;
    }

    DataTypeItem *getChildAt(const int childIndex);
    int childIndex(DataTypeItem *child);

    long getInstanceId() const {
        return instanceId;
    }

    bool isElement() const {
        return (ET_ELEMENT == type);
    }

    const QString &getPITarget();
    const QString getPIData();
    void setPITarget(const QString &target);
    void setPIData(const QString &data);

    const QString &getComment();
    void setComment(const QString &comment);

    //Attributes
    QList<Attribute*> getAttributesList();
    QVector<Attribute*> attributes;

    void addChild(DataTypeItem *newChild);
    void addAttribute(const QString &name, const QString &value);
    void addTextNode(TextChunk *text);

    void generateId();

    QVector<TextChunk*> textNodes;
    ItemType type;
    QString text;
    QString _tag;
    QString tag();

    bool isSelected;

    ItemInfo selfInfo;
    ItemInfo childrenInfo;
    bool wasOpen;
    bool _isCData;

    bool generateDom(QDomDocument &document, QDomNode &parent);

    QTreeWidgetItem *getUI() const {
        return ui;
    }
private:
    static const int ShowDataRole;
    static long instances;

    long instanceId;
    DataTypeItem *parentItem;
    DataTypeModel *parentModel;
    QTreeWidgetItem *ui;


    QVector<DataTypeItem*> childItems;

public:
    const QString styleItemTagSting(PaintInfo *paintInfo);
    QFont styleItemTagFont(PaintInfo *paintInfo);
    QBrush styleItemTagColor(PaintInfo *paintInfo);
    QIcon styleItemTagIcon();
    QVariant tooltipData();
    QVariant displayData(PaintInfo *paintInfo, const int rowOrdinal);

    void addSelected();
    void unSelected();

    void setChecked();
    void setUnchecked();

//    void checkSelectedState();
signals:


public slots:

//    void toggleSelection();
};

#endif // DATATYPEITEM_H
