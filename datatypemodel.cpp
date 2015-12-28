#include "datatypemodel.h"
#include "domitem.h"
#include "paintinfo.h"
#include "documenttype.h"

#include <QtGui>
#include <QtXml/qdom.h>
#include <QtXml/QDomAttr>
#include <QtXml/QXmlAttributes>
#include <QtXml/QDomDocumentType>

#include "utils.h"

int DataTypeModel::renameCounter = 0;

DataTypeModel::DataTypeModel(QDomDocument &document, const QString &name)
{
    _docType = new DocumentType();
    paintInfo = new PaintInfo();
    _fileName = name;

    processDocument(document);
    rootItem = setItem(document, NULL, &childItems);
}

DataTypeModel::DataTypeModel()
{
    _docType = new DocumentType();
    paintInfo = new PaintInfo();

    rootItem = NULL;
}


DataTypeModel::~DataTypeModel()
{
    selection.clear();
    QVectorIterator<DataTypeItem*> it(childItems);
    while(it.hasNext())
    {
        delete it.next();
    }
    rootItem = NULL;
    if(NULL != _docType)
    {
        delete _docType;
    }
}

void DataTypeModel::setTreeValue(QTreeWidget *pTree)
{
    pTree->clear();
    QVectorIterator<DataTypeItem*> it(childItems);
    while(it.hasNext()) {
        DataTypeItem *item = it.next();
        if(item->type == DataTypeItem::ET_ELEMENT) {
            item->registerState();
            item->displayChildItem(pTree, NULL, paintInfo);
        } else
            continue;
    }
//    pTree->setSelectionMode(QAbstractItemView::MultiSelection);
//    connect(pTree, SIGNAL(item(QTreeWidgetItem*,int)), this, SLOT(toggleSelection(QTreeWidgetItem*,int)));
}

void DataTypeModel::setNewTemplateTreeValue(QTreeWidget *pTree)
{
    pTree->clear();
    QVectorIterator<DataTypeItem*> it(childItems);
    while(it.hasNext()) {
        DataTypeItem *item = it.next();
        item->registerState();
        item->displayChildItemSelected(pTree, NULL, paintInfo);
    }
//    pTree->setSelectionMode(QAbstractItemView::MultiSelection);
//    connect(pTree, SIGNAL(item(QTreeWidgetItem*,int)), this, SLOT(toggleSelection(QTreeWidgetItem*,int)));
}

void DataTypeModel::redisplay()
{
    QVectorIterator<DataTypeItem*> it(childItems);
    while(it.hasNext()) {
        DataTypeItem *item = it.next();
        item->displayRecursive(paintInfo);
    }
}

DataTypeItem *DataTypeModel::setItem(QDomNode &node, DataTypeItem *parent, QVector<DataTypeItem*> *collection)
{
    int nodeChildCount = node.childNodes().count();
    DataTypeItem *item = NULL;
    bool isMixedcontent = false;
    bool isElement = false;
    bool isText = false;
    QDomNodeList childNodes = node.childNodes();

    for(int i = 0; i < nodeChildCount; i++) {
        QDomNode childNode = childNodes.item(i);
        if(childNode.isElement()) {
            isElement = true;
        } else if(childNode.isText()) {
            isText = true;
        }
    }

    for(int i = 0; i < nodeChildCount; i++) {
        QDomNode childNode = childNodes.item(i);
        if(childNode.isElement()) {
            if(isText) {
                isMixedcontent = true;
                break;
            }
            isElement = true;
        } else if(childNode.isText()) {
            if(isElement) {
                isMixedcontent = true;
                break;
            }
            isText = true;
        }
    }

    for(int i = 0; i < nodeChildCount; i++) {
        QDomNode childNode = childNodes.item(i);

        if(childNode.isElement()) {
            QDomElement element = childNode.toElement();
            item = new DataTypeItem(addNameToPool(element.tagName()), "", this, parent);

            if(element.hasAttributes()) {
                QDomNamedNodeMap attrList = element.attributes();
                int attrMax = attrList.count();
                for(int a = 0; a < attrMax; a++) {
                    QDomAttr attr = attrList.item(a).toAttr();
                    Attribute *attribute = new Attribute(getAttributeString(attr.name()), getAttributeString(attr.value()));
                    item->attributes.append(attribute);
                    if(attr.name() == tr("MO") && attr.value() == tr("O"))
                        item->setUnchecked();
                }
            }
            if(item->tag() == tr("DOType"))
                DoTypeItemPool.append(item);
            if(item->tag() == tr("DAType"))
                DaTypeItemPool.append(item);
            if(item->tag() == "EnumType")
                EnumItemPool.append(item);
            collection->append(item);
            setItem(childNode, item, item->getChildItems());
        } else if(childNode.isCDATASection()) {
            QDomCDATASection text = childNode.toCDATASection();
            if(isMixedcontent) {
                assignMixedContentText(parent, text.data(), true, collection);
            } else {
                TextChunk *txt = new TextChunk(true, text.data());
                parent->addTextNode(txt);
            }
        } else if(childNode.isText()) {
            QDomText text = childNode.toText();
            if(isMixedcontent) {
                assignMixedContentText(parent, text.data(), false, collection);
            } else {
                TextChunk *txt = new TextChunk(false, text.data());
                parent->addTextNode(txt);
            }
        } else if(childNode.isProcessingInstruction()) {
            QDomProcessingInstruction procInstrNode = childNode.toProcessingInstruction();
            DataTypeItem *procInstr = new DataTypeItem(this, DataTypeItem::ET_PROCESSING_INSTRUCTION, parent);
            procInstr->setPIData(procInstrNode.data());
            procInstr->setPITarget(procInstrNode.target());
            collection->append(procInstr);
            setItem(childNode, procInstr, procInstr->getChildItems());
        } else if(childNode.isComment()) {
            QDomComment commentNode = childNode.toComment();
            DataTypeItem *comment = new DataTypeItem(this, DataTypeItem::ET_COMMENT, parent);
            comment->setText(commentNode.data());
            collection->append(comment);
            setItem(childNode, comment, comment->getChildItems());
        } else if(childNode.isEntityReference()) {
            QDomEntityReference reference = childNode.toEntityReference();
            QString refStr = QString("&%1;").arg(reference.nodeName());
            if(isMixedcontent) {
                assignMixedContentText(parent, refStr, false, collection);
            } else {
                TextChunk *txt = new TextChunk(false, refStr);
                parent->addTextNode(txt);
            }
        }
    }
    return item;
}

void DataTypeModel::assignMixedContentText(DataTypeItem *parent, const QString &text, const bool isCData, QVector<DataTypeItem*> *collection)
{
    DataTypeItem *textItem = new DataTypeItem(this, DataTypeItem::ET_TEXT, parent);
    textItem->setTextOfTextNode(text, isCData);
    collection->append(textItem);
}

DataTypeItem *DataTypeModel::root() const
{
    return rootItem;
}

void DataTypeModel::setRootItem(DataTypeItem *root)
{
    rootItem = root;
}

DataTypeItem *DataTypeModel::newItem(const QString &tagName)
{
    DataTypeItem *newItem = new DataTypeItem(this);
    newItem->_tag = addNameToPool(tagName);
    return newItem;
}

QString &DataTypeModel::fileName()
{
    return _fileName;
}

QTreeWidgetItem *DataTypeModel::getSelItem(QTreeWidget *tree)
{
    QList<QTreeWidgetItem *>selItems = tree->selectedItems();
    if(selItems.count() < 1)
        return NULL;
    return selItems.at(0);
}

void DataTypeModel::addSelected(DataTypeItem *item)
{
    selection.insert(item->getInstanceId(), item);
}

void DataTypeModel::unSelected(DataTypeItem *item)
{
    selection.remove(item->getInstanceId());
}

void DataTypeModel::setSelectedItemChecked()
{
    QHashIterator<int, DataTypeItem*> sel(selection);
    while(sel.hasNext()) {
        sel.next();
        DataTypeItem *item = sel.value();
        item->setChecked();
        item->unSelected();
    }
}

void DataTypeModel::setSelectedItemUnchecked()
{
    QHashIterator<int, DataTypeItem*> sel(selection);
    while(sel.hasNext()) {
        sel.next();
        DataTypeItem *item = sel.value();
        item->setUnchecked();
        item->unSelected();
    }
}

void DataTypeModel::deleteItem(DataTypeItem *item)
{
    if(NULL == item) {
        return ;
    }
    item->autoDelete(true);
}

void DataTypeModel::takeOutItem(DataTypeItem *item)
{
    int id = item->getInstanceId();
    if(selection.contains(id))
        selection.remove(id);
}

void DataTypeModel::notifyDeletionTopItem(DataTypeItem *item)
{
    int elementIndex = childItems.indexOf(item);
    if(-1 != elementIndex) {
        childItems.remove(elementIndex);
    }
    if(item->getType() == DomItem::ET_ELEMENT) {
        rootItem = NULL ;
    }
}

void DataTypeModel::setPaintInfo(PaintInfo *newValue)
{
    if(NULL != paintInfo)
        delete paintInfo;
    paintInfo = newValue;
}

PaintInfo *DataTypeModel::getPaintInfo()
{
    if(NULL == paintInfo)
        paintInfo = new PaintInfo();
    return paintInfo;
}

void DataTypeModel::redisplayItem(DataTypeItem *item)
{
    item->displayWithPaintInfo(paintInfo);
}

QString DataTypeModel::addNameToPool(const QString &inputString)
{
    QSet<QString>::const_iterator it = _namesPool.insert(inputString);
    return *it;
}

QString DataTypeModel::addIdToPool(const QString &inputString)
{
    QString idName = inputString;
    if(_LNodeIdPool.contains(idName)) {
        renameCounter++;
        idName.append("_");
        idName += QString::number(renameCounter,10);
    }

    QSet<QString>::const_iterator it = _LNodeIdPool.insert(idName);
    return *it;
}

QVariant DataTypeModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();
    DataTypeItem *item = static_cast<DataTypeItem*>(index.internalPointer());
    if(NULL != item) {
        switch(role) {
        case Qt::ToolTipRole:
            return item->tooltipData();
            break;
        case Qt::DisplayRole:
            return item->displayData(paintInfo, index.row() + 1);
            break;
        case Qt::FontRole:
            return item->styleItemTagFont(paintInfo);
            break;
        case Qt::ForegroundRole:
            return item->styleItemTagColor(paintInfo);
            break;
        case Qt::DecorationRole:
            return item->styleItemTagIcon();
            break;
        default:
            break;
        }
    }
    return QVariant();
}

Qt::ItemFlags DataTypeModel::flags(const QModelIndex &index) const
{
    if(!index.isValid()) {
        return QAbstractItemModel::flags(index);
    }
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

QVariant DataTypeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return  QVariant();
}

QModelIndex DataTypeModel::index(int row, int column, const QModelIndex &parent) const
{
    if((row < 0) || (column < 0) || (parent.isValid())) {
        return QModelIndex();
    }

    if(!parent.isValid()) {
    //    if(row < childItems.size()) {
        if(childItems.at(row)->tag() == tr("LNodeType")) {
            return createIndex(row, column, childItems.at(row));
        } else {
            DataTypeItem *parentItem = static_cast<DataTypeItem*>(parent.internalPointer());
            DataTypeItem *item = parentItem->getChildAt(row);
//            if(NULL != item) {
            if(item->tag() == tr("LNodeType")) {
                return createIndex(row, column, item);
            }
        }
    }

    return QModelIndex();
}

int DataTypeModel::rowCount(const QModelIndex &parent) const
{
    if(parent.column() > 0)
        return 0;

    int resRowCount = 0;
    DataTypeItem *parentItem;
    if(!parent.isValid()) {
        resRowCount = childItems.size();
    } else {
        parentItem = static_cast<DataTypeItem*>(parent.internalPointer());
        if(NULL != parentItem) {
            resRowCount = parentItem->getChildItemsNumber();
        } else {
            resRowCount = childItems.size();
        }
    }
    return resRowCount;
}

int DataTypeModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QModelIndex DataTypeModel::parent(const QModelIndex &index) const
{
    if(!index.isValid()) {
        DataTypeItem *item = static_cast<DataTypeItem*>(index.internalPointer());
        if(NULL != item) {
            DataTypeItem *parentItem = item->parent();
            int row;
            if(NULL != parentItem) {
                DataTypeItem *grandParentItem = parentItem->parent();
                if(NULL != grandParentItem) {
                    row = grandParentItem->childIndex(parentItem);
                } else {
                    row = childItems.indexOf(parentItem);
                }
                return createIndex(row, 0, parentItem);
            }
        }
    }
    return QModelIndex();
}

void DataTypeModel::processDocument(QDomDocument &document)
{
    QDomDocumentType dtype = document.doctype();
    setDocType(dtype.name(), dtype.systemId(), dtype.publicId());
}

void DataTypeModel::setDocType(const QString& newDocType, const QString &systemId, const QString &publicId)
{
    _docType->setDocType(newDocType);
    _docType->setPublicId(publicId);
    _docType->setSystemId(systemId);

}

QString DataTypeModel::getAttributeString(const QString &attributeName)
{
    QSet<QString>::const_iterator it = _attributeValuesPool.insert(attributeName);
    return *it ;
}


void DataTypeModel::insertItemInternal(DataTypeItem *theNewElement, DataTypeItem *parentElement, QTreeWidget *tree)
{
    if(NULL != parentElement) {
        parentElement->addChild(theNewElement, -1);
        theNewElement->displayChildItem(tree, parentElement->getUI(), paintInfo);
    } else {
//        addTopItem(theNewElement);
        theNewElement->displayChildItem(tree, NULL, paintInfo);
    }

    QTreeWidgetItem *item = theNewElement->getUI();
    tree->setCurrentItem(item);
    QTreeWidgetItem *parentItem = item->parent();
    if(NULL != parentItem) {
        tree->expandItem(parentItem);
    }

    if(theNewElement->tag() == tr("DOType"))
        DoTypeItemPool.append(theNewElement);
    if(theNewElement->tag() == tr("DAType"))
        DaTypeItemPool.append(theNewElement);
    if(theNewElement->tag() == tr("EnumType"))
        EnumItemPool.append(theNewElement);
}

DataTypeItem *DataTypeModel::insertToNewTemplate(QTreeWidget *tree, DataTypeItem *parentElement, DataTypeItem *pasteElement, int pos)
{
    //if not selected, at the root iif rule is empty
    //sse extists an item
    //append l'item ( o lo inserisce, con tutti i figli e poi ricarica la lista)
    DataTypeItem *theNewElement = NULL ;
    if(NULL == pasteElement) {
        return NULL;
    } else {
        theNewElement = pasteElement->copyToNewTemplate(this, *new DataTypeItem(this));

        if(!parentElement->isElement()) {
            return NULL;
        }

        parentElement->addChild(theNewElement, pos);

        theNewElement->displayChildItemSelected(tree, parentElement->getUI(), paintInfo);

    }

    return theNewElement;
}

DataTypeItem *DataTypeModel::insertToNewTemplateInternal(DataTypeItem *parentElement, DataTypeItem *pasteElement, int pos)
{
    DataTypeItem *theNewElement = NULL ;
    if(NULL == pasteElement) {
        return NULL;
    } else {
        theNewElement = pasteElement->copyToNewTemplate(this, *new DataTypeItem(this));

        if(!parentElement->isElement()) {
            return NULL;
        }

        parentElement->addChild(theNewElement, pos);

//        foreach (DataTypeItem* item, theNewElement->getItems()) {
//            if(item->isSelected) {
//                insertToNewTemplateInternal(theNewElement, item);
//            }
//        }
    }

    return theNewElement;
}

bool DataTypeModel::write(const QString &filePath)
{
    QDomDocument    document = createNewDocument();
    //document.setInvalidDataPolicy(QDomImplementation::ReturnNullNode); TODO
    QVectorIterator<DataTypeItem*> it(childItems);
    while(it.hasNext()) {
        if(!it.next()->generateDom(document, document))
            return false;
    }
    //aggiungi le processunit
    QFile   file(filePath);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        Utils::error(tr("Error writing data: %1").arg(file.error()));
        return false;
    }
    QTextStream streamOut(&file);
    streamOut.setCodec("UTF-8");
    //streamOut << "<?xml version=\"1.0\" encoding=\"utf-8\" ?>\n";
    streamOut << document.toString(4);
    streamOut.flush();
    file.close();

    // TODO: repaint only if modified, and only if visible
    redisplay();

    return true;
}

QByteArray DataTypeModel::writeMemory()
{
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    QDomDocument document;
    QVectorIterator<DataTypeItem*> it(childItems);
    while(it.hasNext()) {
        if(!it.next()->generateDom(document, document))
            return NULL;
    }
    if(!buffer.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return NULL;
    }
    QTextStream streamOut(&buffer);
    streamOut.setCodec("UTF-8");
    streamOut << document.toString(4);
    streamOut.flush();
    buffer.close();
    return byteArray;
}

QDomDocument DataTypeModel::createNewDocument()
{
    if(_docType->hasDocType()) {
        QDomDocument document = _docType->createDocument();
        return document;
    } else {
        QDomDocument document;
        return document;
    }
}

