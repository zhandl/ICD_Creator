#include "datatypeitem.h"
#include "domitem.h"
#include "datatypemodel.h"


long DataTypeItem::instances = 0;
int  DataTypeItem::renameIdCount = 0;

DataTypeItem::DataTypeItem(const QString newTag, const QString &itext, DataTypeModel *model, DataTypeItem *parent)
{
    generateId();
    ui = NULL;
    wasOpen = false;
    parentModel = model;
    parentItem = parent;
    _tag = newTag;
    text = itext;
    type = ET_ELEMENT;
    isSelected = true;
    _isCData = false;

}

DataTypeItem::DataTypeItem(DataTypeModel *model, ItemType newType, DataTypeItem *parent)
{
    generateId();
    ui = NULL;
    wasOpen = false;
    parentModel = model;
    parentItem = parent;
    _tag = tr("");
    text = tr("");
    type = newType;
    isSelected = true;
    _isCData = false;
}

DataTypeItem::DataTypeItem(DataTypeModel *model)
{
    generateId();
    ui = NULL;
    wasOpen = false;
    parentModel = model;
    parentItem = NULL;
    type = ET_ELEMENT;
    isSelected = true;
    _isCData = false;
}

DataTypeItem::~DataTypeItem()
{
    QVectorIterator<DataTypeItem*> it(childItems);
    while(it.hasNext()) {
        delete it.next();
    }
    parentModel = NULL;
    parentItem = NULL;
}

void DataTypeItem::generateId()
{
    instanceId = instances++;
}

DataTypeItem *DataTypeItem::parent()
{
    return parentItem;
}

void DataTypeItem::registerState()
{
    if(NULL != ui) {
        wasOpen = ui->isExpanded();
    } else {
        wasOpen = false;
    }
    foreach (DataTypeItem *item, childItems) {
        item->registerState();
    }
}

void DataTypeItem::displayRecursive(PaintInfo *paintInfo)
{
    if(NULL == ui)
        return ;
    display(ui, paintInfo, false);
    foreach (DataTypeItem *item, childItems) {
        item->displayRecursive(paintInfo);
    }
}

const QString DataTypeItem::styleItemTagSting(PaintInfo *paintInfo)
{
    QString qualifiedInfo;
    VStyle *style = paintInfo->currentStyle();
    if(NULL != style) {
        foreach (Attribute *attribute, attributes)  {
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

QFont DataTypeItem::styleItemTagFont(PaintInfo *paintInfo)
{
    VStyle *style = paintInfo->currentStyle();
    if(NULL != style) {
        StyleEntry *se = style->getStyleOfKeyword(tag());
        if(NULL != se) {
            QFont *styleFont = se->font();
            if(NULL != styleFont) {
                return *styleFont;
            }
        }
    }
    return VStyle::defaultFont();
}

QBrush DataTypeItem::styleItemTagColor(PaintInfo *paintInfo)
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

QIcon DataTypeItem::styleItemTagIcon()
{
    return QIcon();
}

QList<Attribute*>DataTypeItem::getAttributesList()
{
    QList<Attribute*>attrList;
    attrList = attributes.toList();
    return attrList ;
}

QVariant DataTypeItem::tooltipData()
{
    QString tooltip;
    foreach (Attribute *attribute, getAttributesList()) {
        QString attrValue = QString("%1=\"%2\"\n").arg(attribute->name).arg(attribute->value);
        tooltip += attrValue;
    }
    return QVariant(tooltip);
}

QVariant DataTypeItem::displayData(PaintInfo *paintInfo, const int rowOrdinal)
{
    switch(getType()) {
    case DataTypeItem::ET_TEXT: {
        QString txt = text;
        if(txt.length() > 10) {
            txt = txt.left(10);
            txt += "...";
        }
        return QVariant(QString("%1 Text: %2").arg(rowOrdinal).arg(txt));
        break;
    }
    case DataTypeItem::ET_ELEMENT: {
        int totalChildrenNumber = selfInfo.numItems + childrenInfo.numItems;
        QString childInfo;
        if(totalChildrenNumber > 0) {
            childInfo = QString("(%1)").arg(totalChildrenNumber);
        }
        QString elmInfo = styleItemTagSting(paintInfo);
        return QVariant(QString("%1 %2 %3 %4").arg(rowOrdinal).arg(tag()).arg(elmInfo).arg(childInfo));
    }
    default:
        return QVariant(QString("%1 ???").arg(rowOrdinal));
        break;

    }
    return QVariant("");
}

void DataTypeItem::updateDisplay(QTreeWidgetItem *me)
{
    if(ui != me) {
        ui = me;
    }
    QString showText;
    if(tag() == "LNodeType") {
        showText += attributeValueOfName("lnClass");
        showText.append(": ");
        showText += attributeValueOfName("id");
    }
    me->setText(0, showText);
}

void DataTypeItem::display(QTreeWidgetItem *me, PaintInfo *paintInfo, bool isNewTemplate)
{
    if(ui != me) {
        ui = me;
    }
    QFont font;
    font.setFamily("Calibri");
    font.setPointSize(9);
    me->setFont(0, font);

    me->setData(0, Qt::UserRole, qVariantFromValue((void*)this));
    QString showText;
    if(type == ET_ELEMENT) {
        if(tag() == tr("DataTypeTemplates")) {
            if(isNewTemplate)
                showText = tr("DataTypeTemplates");
            else
                showText = tr("DLT860-74");

            wasOpen = true;

        } else if(tag() == tr("LNodeType")) {
            me->setIcon(0, QIcon(":/dataType/images/LNode.png"));

            showText += attributeValueOfName("lnClass");
            showText.append(": ");
            showText += attributeValueOfName("id");

            me->setFlags(me->flags() & ~Qt::ItemIsUserCheckable);

            wasOpen = false;


        } else if(tag() == tr("DO")) {
            me->setIcon(0, QIcon(":/dataType/images/DO.png"));
            QString doName = attributeValueOfName("name");
            QString doType = attributeValueOfName("type");
            QString doMO = attributeValueOfName("MO");

            showText += doName;
            showText.append(": ");
            showText += doType;

            if(!isNewTemplate) {
                showText.append(" <");
                showText += doMO;
                showText.append(">");
            }

            if(isNewTemplate) {
                me->setFlags(me->flags() & ~Qt::ItemIsUserCheckable);
            } else if(doMO == tr("M")) {
                me->setCheckState(0,Qt::Checked);
                me->setFlags(me->flags() & ~Qt::ItemIsSelectable & ~Qt::ItemIsUserCheckable);
                me->setBackground(0,QColor(255, 255, 200));
                isSelected = true;
            } else {
                me->setCheckState(0, Qt::Unchecked);
                isSelected = false;
            }
            wasOpen = false;
        } else if(tag() == tr("DOType") && isNewTemplate) {
            me->setIcon(0, QIcon(":/dataType/images/DOTypeNode.png"));

            showText += attributeValueOfName("cdc");
            showText.append(": ");
            showText += attributeValueOfName("id");

            me->setFlags(me->flags() & ~Qt::ItemIsUserCheckable);

            wasOpen = true;
        } else if(tag() == tr("DA") && isNewTemplate) {
            me->setIcon(0, QIcon(":/dataType/images/DANode.png"));

            showText += attributeValueOfName("name");
            showText.append(": ");
            showText += attributeValueOfName("bType");
            showText.append(": ");
            showText += attributeValueOfName("fc");

            me->setFlags(me->flags() & ~Qt::ItemIsUserCheckable);

            wasOpen = false;
        } else if(tag() == tr("DAType") && isNewTemplate) {
            me->setIcon(0, QIcon(":/dataType/images/DATypeNode.png"));

            showText += attributeValueOfName("id");

            me->setFlags(me->flags() & ~Qt::ItemIsUserCheckable);

            wasOpen = true;
        } else if(tag() == tr("BDA") && isNewTemplate) {
            me->setIcon(0, QIcon(":/dataType/images/DATypeNode.png"));

            showText += attributeValueOfName("name");
            showText.append(": ");
            QString BDAType = attributeValueOfName("type");
            if(BDAType != tr("")){
                showText += attributeValueOfName("type");
            } else {
                showText += attributeValueOfName("bType");
            }

            me->setFlags(me->flags() & ~Qt::ItemIsUserCheckable);

            wasOpen = true;
        } else if(tag() == tr("EnumType") && isNewTemplate) {
            me->setIcon(0, QIcon(":/dataType/images/DATypeNode.png"));

            showText += attributeValueOfName("id");

            me->setFlags(me->flags() & ~Qt::ItemIsUserCheckable);

            wasOpen = true;
        } else if(tag() == tr("EnumVal") && isNewTemplate) {
            me->setIcon(0, QIcon(":/dataType/images/DATypeNode.png"));

            showText += attributeValueOfName("ord");
            showText.append(": ");
            showText += textNodes.at(0)->text;

            me->setFlags(me->flags() & ~Qt::ItemIsUserCheckable);

            wasOpen = false;
        }
        me->setText(paintInfo->columnForTag, showText);
    }
    if(wasOpen)
        ui->setExpanded(true);

}

void DataTypeItem::displayWithPaintInfo(PaintInfo *paintInfo)
{
    if(NULL != ui)
        display(ui, paintInfo, false);
}

void DataTypeItem::addAttribute(const QString &name, const QString &value)
{
    if(!name.isEmpty()) {
        Attribute *attribute = new Attribute(name, value);
        attributes.append(attribute);
    }
}

DataTypeItem *DataTypeItem::fromItemData(QTreeWidgetItem *item)
{
    if(NULL == item) {
        return NULL;
    }
    QVariant data = item->data(0, Qt::UserRole);
    DataTypeItem *pItem = (DataTypeItem*)data.value<void*>();
    return pItem;
}

DataTypeItem *DataTypeItem::fromModelIndex(const QModelIndex &index)
{
    if(!index.isValid()) {
        return NULL;
    }
    QVariant data = index.data(Qt::UserRole);
    DataTypeItem *pItem = (DataTypeItem*)data.value<void*>();
    return pItem;
}

void DataTypeItem::addChild(DataTypeItem *newChild, int pos)
{
    newChild->parentItem = this;
    if(pos >= 0) {
        childItems.insert(pos, newChild);
    } else {
        childItems.append(newChild);
    }
}

void DataTypeItem::setText(const QString &data)
{
    text = data;
}

void DataTypeItem::setTextOfTextNode(const QString &data, const bool isCData)
{
    text = data;
    _isCData = isCData;
}

const QString &DataTypeItem::getComment()
{
    return text;
}

void DataTypeItem::setComment(const QString &comment)
{
    text = comment;
}

void DataTypeItem::addTextNode(TextChunk *text)
{
    textNodes.append(text);
}

const QString DataTypeItem::getPIData()
{
    return tag();
}

const QString &DataTypeItem::getPITarget()
{
    return text;
}

void DataTypeItem::setPIData(const QString &data)
{
    _tag = parentModel->addNameToPool(data);
}

void DataTypeItem::setPITarget(const QString &target)
{
    text = target;
}

QString DataTypeItem::tag()
{
    return _tag;
}

void DataTypeItem::displayChildItem(QTreeWidget *pTree, QTreeWidgetItem *parentItem, PaintInfo *paintInfo)
{
    QTreeWidgetItem *me = NULL;
    bool isTop = false;
    if(NULL == parentItem) {
        me = new QTreeWidgetItem(0);
        isTop = true;
    } else {
        me = new QTreeWidgetItem(parentItem);
    }
    display(me, paintInfo, false);

    foreach (DataTypeItem *item, childItems) {
        if(item->tag() == tr("LNodeType") || (item->tag() == tr("DO"))) {
            item->displayChildItem(NULL, me, paintInfo);
        }
    }

    if(isTop)
        pTree->addTopLevelItem(me);
}

void DataTypeItem::displayChildItemSelected(QTreeWidget *pTree, QTreeWidgetItem *parentItem, PaintInfo *paintInfo)
{
    QTreeWidgetItem *me = NULL;
    bool isTop = false;
    if(NULL == parentItem) {
//        if(_tag == tr("LNodeType"))
//            me = new QTreeWidgetItem(pTree->topLevelItem(0));
//        else if(_tag == tr("DOType"))
//            me = new QTreeWidgetItem(pTree->topLevelItem(1));
//        else if(_tag == tr("DAType"))
//            me = new QTreeWidgetItem(pTree->topLevelItem(2));
//        else if(_tag == tr("EnumType"))
//            me = new QTreeWidgetItem(pTree->topLevelItem(3));
        me = new QTreeWidgetItem(0);
        isTop = true;
    } else {
        me = new QTreeWidgetItem(parentItem);
    }
    display(me, paintInfo, true);

    foreach (DataTypeItem *item, childItems) {
        if(item->isSelected) {
            item->displayChildItemSelected(NULL, me, paintInfo);
        }
    }

    if(isTop)
        pTree->addTopLevelItem(me);
}

DataTypeItem *DataTypeItem::getChildAt(const int childIndex)
{
    if((childIndex > 0) && (childIndex < childItems.size())) {
        return childItems.at(childIndex);
    }
    return NULL;
}

int DataTypeItem::childIndex(DataTypeItem *child)
{
    int index = 0;
    foreach (DataTypeItem *item, childItems) {
        if(item == child) {
            return index;
        }
        index ++;
    }
    return -1;
}

void DataTypeItem::addSelected()
{
    QTreeWidgetItem *theUi = getUI();
    if(NULL != theUi) {
        theUi->setBackground(0, QColor(0xFF, 0xC0, 0x40));
    }
    parentModel->addSelected(this);
}

void DataTypeItem::unSelected()
{
    QTreeWidgetItem *theUi = getUI();
    if(NULL != theUi) {
        theUi->setBackground(0, QColor(0xFF, 0xFF, 0xFF, 0));
    }
    parentModel->unSelected(this);
}

void DataTypeItem::setChecked()
{
    QTreeWidgetItem *theUi = getUI();

    if(_tag != tr("DO")) {
        isSelected = true;
        if(NULL != theUi) {
            theUi->setBackgroundColor(0, QColor(0xFF, 0xC0, 0xFF));
        }
        return ;
    }

    if(NULL != theUi) {
        theUi->setCheckState(0, Qt::Checked);
    }
    isSelected = true;
}

void DataTypeItem::setUnchecked()
{
    QTreeWidgetItem *theUi = getUI();
    if(_tag != tr("DO")) {
        isSelected = false;
        theUi->setBackgroundColor(0, QColor(0xFF, 0xFF, 0xFF));
        return ;
    }
    if(NULL != theUi) {
        theUi->setCheckState(0, Qt::Unchecked);
    }
    isSelected = false;
}

DataTypeItem *DataTypeItem::copyTo(DataTypeItem &newItem)
{
    return copyTo(newItem, true);
}

DataTypeItem *DataTypeItem::copyTo(DataTypeItem &newItem, const bool isRecursive)
{
    copyHeaderAndDirectNodes(newItem);
    QVectorIterator<DataTypeItem*> it(childItems);
    while(it.hasNext()) {
        DataTypeItem *newEl = new DataTypeItem(newItem.parentModel);
        newItem.addChild(newEl, -1);
        it.next()->copyTo(*newEl, isRecursive);
    }
    return &newItem;
}

void DataTypeItem::copyHeader(DataTypeItem &newItem)
{
    if(NULL != newItem.parentModel) {
        newItem._tag = newItem.parentModel->addNameToPool(_tag);
    } else {
        newItem._tag = _tag;
    }
    newItem.text = text;
    newItem.type = type;
}

void DataTypeItem::copyHeaderAndDirectNodes(DataTypeItem &newItem)
{
    copyHeader(newItem);
//    newItem.clearTextNodes();
//    newItem.clearAttributes();

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

void DataTypeItem::calcCheckState()
{
   if(NULL == ui)
       return;
   if(ui->checkState(0) == Qt::Checked)
       isSelected = true;
   else
       isSelected = false;

   foreach (DataTypeItem *item, childItems) {
       if(item->ui->checkState(0) == Qt::Checked)
           item->isSelected = true;
       else
           item->isSelected = false;
   }
}

QString DataTypeItem::attributeValueOfName(const QString &name)
{
    foreach (Attribute *attr, attributes) {
        if(attr->name == name)
            return attr->value;
    }
    return "";
}

DataTypeItem *DataTypeItem::copyToNewTemplate(DataTypeModel *newModel, DataTypeItem &newItem)
{
    newItem._tag = newModel->addNameToPool(_tag);
    newItem.text = text;
    newItem.type = type;
    if(_tag == tr("DO"))
        newItem.isSelected = isSelected;
    else
        newItem.isSelected = true;

    QVectorIterator<Attribute*> attr(attributes);
    while(attr.hasNext()) {
        Attribute *src = attr.next();
        if(src->name == "MO")
            continue;
        Attribute *dst = new Attribute(src->name, src->value);
        if(dst->name == "id") {
            dst->value = newModel->addIdToPool(dst->value);
        }
        newItem.attributes.append(dst);
    }

    QVectorIterator<TextChunk*> tt(textNodes);
    while(tt.hasNext()) {
        TextChunk *tx = tt.next();
        TextChunk *newText = tx->clone();
        newItem.textNodes.append(newText);
    }

    QVectorIterator<DataTypeItem*> it(childItems);
    while(it.hasNext()) {
        DataTypeItem *childItem = it.next();
        if(childItem->isSelected) {
            DataTypeItem *newEl = new DataTypeItem(newItem.parentModel);
            newItem.addChild(newEl, -1);
            childItem->copyToNewTemplate(newModel, *newEl);
        }
    }
    return &newItem;
}

void DataTypeItem::autoDelete(const bool isAuto)
{
    if(NULL != parentItem) {
        int indexOf = parentItem->childItems.indexOf(this);
        parentItem->childItems.remove(indexOf);
    } else {
        parentModel->notifyDeletionTopItem(this);
    }
    parentModel->takeOutItem(this);

    deleteUI();
    parentModel = NULL;
    if(isAuto) {
        delete this;
    }
}

void DataTypeItem::deleteUI()
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

void DataTypeItem::zeroUI()
{
    zeroUISelf();
    foreach(DataTypeItem *item, childItems) {
        item->zeroUI();
    }
}

void DataTypeItem::zeroUISelf()
{
    parentModel->takeOutItem(this);
    ui = NULL;
}

bool DataTypeItem::generateDom(QDomDocument &document, QDomNode &parent)
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
        foreach(DataTypeItem *value, childItems) {
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
