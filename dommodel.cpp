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

#include <QtGui>
#include <QtXml/qdom.h>
#include <QtXml/QDomAttr>
#include <QtXml/QXmlAttributes>

#include "domitem.h"
#include "dommodel.h"
#include "mainwindow.h"

#include "xmlutils.h"
#include "utils.h"
#include "findtextparams.h"
#include "documenttype.h"
#include "edittextnode.h"
#include "editelement.h"
#include "xsaxhandler.h"
#include "editattribute.h"
#include "editlnode.h"
#include "editdataset.h"
#include "addtext.h"
#include "addprivate.h"
#include "editreportcontrol.h"
#include "editservices.h"

#include "undo/undomoveupcommand.h"
#include "undo/undomovedowncommand.h"
#include "undo/undodeletecommand.h"
#include "undo/undoinsertcommand.h"
#include "undo/undoeditcommand.h"

#define XMLNS_PREFIX    "xmlns"
#define ATTRIBUTE_SCHEMA_LOCATION    "xsi:schemaLocation"
#define SCHEMA_LOCATION    "schemaLocation"
#define ATTRIBUTE_SCHEMA_NONS_LOCATION    "xsi:noNamespaceSchemaLocation"
#define SCHEMA_NONS_LOCATION    "noNamespaceSchemaLocation"
#define SCHEMA_URI "http://www.w3.org/2001/XMLSchema-instance"
#define XSI_NAMESPACE   "xsi"
#define XSI_NAMESPACE_COMPLETE   "xmlns:xsi"

QBrush DomModel::setBkBrush(QColor(0xFF, 0xC0, 0x40));

DomModel::DomModel(QDomDocument &document, const QString &name)
{
    init();
    paintInfo = new PaintInfo();
    modified = false;
    _collectSizeData = false;
    xmlFileName = name;

    processDocument(document);
    rootItem = setItem(document, NULL, &childItems);
    checkValidationReference();
}

DomModel::DomModel()
{
    init();
    paintInfo = new PaintInfo();
    modified = false;
    rootItem = NULL;
    _collectSizeData = false;
}

DomModel::~DomModel()
{
    clear();
    if(NULL != _docType)
    {
        delete _docType;
    }
}

void DomModel::init()
{
    _undoStack.setUndoLimit(UndoLimitCount);
    connect(&_undoStack, SIGNAL(canRedoChanged(bool)), this, SIGNAL(undoStateChanged()));
    connect(&_undoStack, SIGNAL(canUndoChanged(bool)), this, SIGNAL(undoStateChanged()));
    _docType = new DocumentType();
}

void DomModel::clear()
{
    clearUndo();
    selection.clear();
    QVectorIterator<DomItem*> it(childItems);
    while(it.hasNext())
    {
        delete it.next();
    }
    rootItem = NULL;
    modified = false;
}

void DomModel::clearUndo()
{
    _undoStack.clear();
}

void DomModel::setTreeValue(QTreeWidget *pTree)
{
    pTree->clear();
    pTree->setIconSize(QSize(20, 20));
    QVectorIterator<DomItem*> it(childItems);
    while(it.hasNext())
    {
        DomItem *item = it.next();
        item->registerState();
        item->setChildItem(pTree, NULL, paintInfo, true);
    }
}

void DomModel::redisplay()
{
    QVectorIterator<DomItem*> it(childItems);
    while(it.hasNext())
    {
        DomItem *item = it.next();
        item->displayRecursive(paintInfo);
    }
}

DomItem *DomModel::setItem(QDomNode &node, DomItem *parent, QVector<DomItem *> *collection)
{
    int nodeChildCount = node.childNodes().count();
    DomItem *item = NULL;
    bool isMixedcontent = false;
    bool isElement = false;
    bool isText = false;
    QDomNodeList childNodes = node.childNodes();

    for(int i = 0; i < nodeChildCount; i++)    {
        QDomNode childNode = childNodes.item(i);
        if(childNode.isElement())   {
            if(isText)   {
                isMixedcontent = true;
                break;
            }
            isElement = true;
        } else if(childNode.isText()) {
            if(isElement)  {
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
            item = new DomItem(addNameToPool(element.tagName()), "", this, parent);

            if(element.hasAttributes()) {
                QDomNamedNodeMap attrList = element.attributes();
                int attrMax = attrList.count();
                for(int a = 0; a < attrMax; a ++) {
                    QDomAttr attr = attrList.item(a).toAttr();
                    Attribute *attribute = new Attribute(getAttributeString(attr.name()), getAttributeString(attr.value()));
                    item->attributes.append(attribute);
                }
            }
            collection->append(item);
            setItem(childNode, item, item->getChildItems());       

            if(item->tag() == tr("LNodeType"))
                _dataTypeItems.append(item);

            if(item->tag() == tr("DOType"))
                _doTypeItems.append(item);

            if((item->tag() == tr("DAType")) | (item->tag() == tr("EnumType")))
                _daEnumTypeItems.append(item);

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
            DomItem *procInstr = new DomItem(this, DomItem::ET_PROCESSING_INSTRUCTION, parent);
            procInstr->setPIData(procInstrNode.data());
            procInstr->setPITarget(procInstrNode.target());
            collection->append(procInstr);
            setItem(childNode, procInstr, procInstr->getChildItems());
        } else if(childNode.isComment()) {
            QDomComment commentNode = childNode.toComment();
            DomItem *comment = new DomItem(this, DomItem::ET_COMMENT, parent);
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
}//setItem;

void DomModel::assignMixedContentText(DomItem *parent, const QString &text, const bool isCData, QVector<DomItem *> *collection)
{
    DomItem *textItem = new DomItem(this, DomItem::ET_TEXT, parent);
    textItem->setTextOfTextNode(text, isCData);
    collection->append(textItem);
}

QDomDocument DomModel::createNewDocument()
{
    if(_docType->hasDocType()) {
        QDomDocument document = _docType->createDocument();
        return document;
    } else {
        QDomDocument document;
        return document;
    }
}

bool DomModel::write(const QString &filePath)
{
    QDomDocument    document = createNewDocument();
    //document.setInvalidDataPolicy(QDomImplementation::ReturnNullNode); TODO
    QVectorIterator<DomItem*> it(childItems);
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

QByteArray DomModel::writeMemory()
{
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    QDomDocument document;
    QVectorIterator<DomItem*> it(childItems);
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

QString DomModel::getAsText()
{
    QDomDocument document = createNewDocument();
    QVectorIterator<DomItem*> it(childItems);
    while(it.hasNext()) {
        if(!it.next()->generateDom(document, document))
            return "";
    }
    QString result = document.toString(4);
    return result;
}

bool DomModel::isEmpty(const bool isRealElement)
{
    if(isRealElement) {
        return (NULL == rootItem);
    } else {
        return (childItems.isEmpty());
    }
}

DomItem *DomModel::root() const
{
    return rootItem;
}

void DomModel::setRootItem(DomItem *newRoot)
{
    clear();
    addTopItem(newRoot);
}

bool DomModel::addTopItem(DomItem *theNewItem, const int position)
{
    bool wasExisted = false;
    bool newIsElement = (theNewItem->getType() == DomItem::ET_ELEMENT);
    bool isOutOfSync = (NULL != rootItem) && (rootItem->getType() == DomItem::ET_ELEMENT) && newIsElement;

    Q_ASSERT_X(!isOutOfSync, "setFirstChild", "rootItem is out of sync");
    if(newIsElement) {
        rootItem = theNewItem;
    }
    if(-1 == position) {
        childItems.append(theNewItem);
    } else {
        childItems.insert(position, theNewItem);
    }
    if(collectSizeData()) {
        theNewItem->recalcSize(true);
    }
    setModified(true);
    return wasExisted;
}

DomItem *DomModel::newItem()
{
    DomItem *newItem = new DomItem(this);
    return newItem;
}

DomItem *DomModel::newItem(const QString &tagName)
{
    DomItem *newItem = new DomItem(this);
    newItem->_tag = addNameToPool(tagName);
    newItem->setNodeType();
    return newItem;
}

DomItem *DomModel::newItem(const DomItem::ItemType newType)
{
    DomItem *newItem = new DomItem(this, newType, NULL);
    return newItem;
}

void DomModel::setModified(const bool state)
{
    if(state != modified) {
        modified = state;
        checkValidationReference();
        emit wasModified();
    }
}

bool DomModel::isModified() const
{
    return modified;
}

void DomModel::setEmptyRoot()
{
    clear();
}

QString &DomModel::fileName()
{
    return xmlFileName;
}

void DomModel::setFileName(const QString &newFileName)
{
    xmlFileName = newFileName;
    setModified(true);
}


bool DomModel::editTextNodeItem(QWidget * const parentWindow, const bool isBase64Coded, DomItem *pItem)
{
    EditTextNode editDialog(isBase64Coded, parentWindow);
    editDialog.setModal(true);
    editDialog.setText(pItem->getAsSimpleText(isBase64Coded));
    if(editDialog.exec() == QDialog::Accepted) {
        pItem->setAsSingleTextNode(editDialog.getText(), isBase64Coded, pItem->isCDATA());
        return true;
    }
    return false;
}

bool DomModel::editServicesItem(QWidget * const parentWindow, DomItem *pItem)
{
    EditServices element(parentWindow);
    element.setModal(true);
    element.setTarget(pItem);
    if(element.exec() == QDialog::Accepted) {
        return true;
    }
    return false;
}

bool DomModel::editNodeItem(QWidget * const parentWindow, DomItem *pItem)
{
    EditElement element(parentWindow);
    element.setModal(true);
    element.setTarget(pItem);
    if(element.exec() == QDialog::Accepted) {
        return true;
    }
    return false;
}

bool DomModel::editDataSetItem(QWidget * const parentWindow, DomItem *pItem)
{
    EditDataSet element(parentWindow);
    element.setModal(true);
    element.setTarget(pItem);
    if(element.exec() == QDialog::Accepted) {
        return true;
    }
    return false;
}

bool DomModel::editReportControlItem(QWidget * const parentWindow, DomItem *pItem)
{
    EditReportControl element(parentWindow);
    element.setModal(true);
    element.setTarget(pItem);
    if(element.exec() == QDialog::Accepted) {
        return true;
    }
    return false;
}

bool DomModel::editLNodeItem(QWidget * const parentWindow, DomItem *pItem)
{
    EditLNode element(parentWindow);
    element.setModal(true);
    element.setTarget(pItem);
    if(element.exec() == QDialog::Accepted) {
        return true;
    }
    return false;
}

void DomModel::editServices(QWidget *const window, QTreeWidgetItem *pItem)
{
    DomItem *item = DomItem::fromItemData(pItem);

    bool updateInfo = false;
    UndoEditCommand *undoCommand = new UndoEditCommand(pItem->treeWidget(), this, item->indexPath());
    EditServices element(window);
    element.setModal(true);
    element.setTarget(item);
    if(element.exec() == QDialog::Accepted) {
        updateInfo = true;
    }
    if(updateInfo) {
        pItem->takeChildren();
        foreach(DomItem *child, item->getItems()) {
            child->setChildItem(NULL, item->getUI(), paintInfo, true, -1);
        }
  //      item->setChildItem(pTree, item->getUI(), paintInfo, true, -1);
        item->updateSizeInfo();
        item->display(pItem, paintInfo);
//        item->displayRecursive(paintInfo);
        setModified(true);

        undoCommand->setModifiedElement(item);
        _undoStack.push(undoCommand);
    } else {
        delete undoCommand;
    }


}

void DomModel::editAttribute(QWidget *const window, QTreeWidgetItem *pItem)
{
    DomItem *item = DomItem::fromItemData(pItem);

    bool updateInfo = false;
    UndoEditCommand *undoCommand = new UndoEditCommand(pItem->treeWidget(), this, item->indexPath());
    EditElement element(window);
    element.setModal(true);
    element.setTarget(item);
    if(element.exec() == QDialog::Accepted) {
        updateInfo = true;
    }
    if(updateInfo) {
        item->updateSizeInfo();
        item->display(pItem, paintInfo);
        setModified(true);

        undoCommand->setModifiedElement(item);
        _undoStack.push(undoCommand);
    } else {
        delete undoCommand;
    }

    return;

}


bool DomModel::editNodeComment(QWidget * const parentWindow, DomItem *pItem)
{
    return EditCommentNode(parentWindow, pItem);
}

bool DomModel::editAndSubstituteTextInNodeItemInternal(QWidget *const parentWindow, DomItem *pElement)
{
    switch(pElement->getType()) {
    case DomItem::ET_ELEMENT:
        if(pElement->isMixedContent()) {

            return false;
        }
        // pass through
    case DomItem::ET_TEXT:
        if(editTextNodeItem(parentWindow, false, pElement)) {
            pElement->updateSizeInfo();
            pElement->display(pElement->getUI(), paintInfo);
            setModified(true);
            return true;
        }
        break;
    default:
        return false;
    }
    return false;
}


bool DomModel::editItem(QWidget *const parentWindow, QTreeWidgetItem *item)
{
    try {
        bool result = false;
        bool updateInfo = false;
        DomItem *pItem = DomItem::fromItemData(item);
        UndoEditCommand *undoCommand = new UndoEditCommand(item->treeWidget(), this, pItem->indexPath());
        if(NULL == undoCommand) {
            throw new std::exception();
            return false;
        }
        undoCommand->setOriginalElement(pItem);

       {

            switch(pItem->getType()) {
            case DomItem::ET_TEXT:
                result = editAndSubstituteTextInNodeItemInternal(parentWindow, pItem);
                break;

            case DomItem::ET_ELEMENT:
                if(pItem->getNodeType() == DomItem::ICD_SERVICES)
                    result = editServicesItem(parentWindow, pItem);
                else
                    result = editNodeItem(parentWindow, pItem);
                if(result) {
                    updateInfo = true ;
                }
                break;

            case DomItem::ET_PROCESSING_INSTRUCTION:
                result = editProcessingInstruction(parentWindow, pItem);
                if(result) {
                    updateInfo = true ;
                }
                break;
            case DomItem::ET_COMMENT:
                result = editNodeComment(parentWindow, pItem);
                if(result) {
                    updateInfo = true ;
                }
                break;

            default:
                Utils::error(parentWindow, tr("Unknown node type"));
                break;
            }
        }
        if(result) {
            if(updateInfo) {
                item->takeChildren();
                if(pItem->getNodeType() == DomItem::ICD_SERVICES) {
                    foreach (DomItem *child, pItem->getItems()) {
                        child->setChildItem(NULL, pItem->getUI(), paintInfo, true, -1);
                    }
                }
                pItem->updateSizeInfo();
                pItem->display(item, paintInfo);
                setModified(true);
            }
            undoCommand->setModifiedElement(pItem);
            _undoStack.push(undoCommand);
        } else {
            delete undoCommand;
        }
        return result ;
    } catch(...) {
        Utils::error(parentWindow, tr("A fatal error occurred"));
    }
    return false ;
}

bool DomModel::editEntry(QWidget * const parentWindow, const QString &title, const QString &label, const QString &actualText, QString &result)
{
    bool ok = false ;
    QString text = QInputDialog::getText(parentWindow, title, label, QLineEdit::Normal, actualText, &ok);
    if(ok && !text.isEmpty()) {
        result = text ;
    }
    return ok;
}

void DomModel::addText(QWidget *window, QTreeWidget *tree)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(true);
    DomItem *parentItem = NULL;
    if(NULL != currItem) {
        parentItem = DomItem::fromItemData(currItem);
        if(parentItem->getType() != DomItem::ET_ELEMENT)
            return ;
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return;
        }
    }    

    DomItem *theNewItem = new DomItem(addNameToPool(tr("Text")), "", this, parentItem);
    theNewItem->setNodeType();

    AddText element(window);
    element.setModal(true);
    element.setTarget(theNewItem);
    if(element.exec() == QDialog::Accepted) {
        insertItemInternal(theNewItem, parentItem, tree, true, 0);
    }
}

void DomModel::addPrivate(QWidget *window, QTreeWidget *tree)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(true);
    DomItem *parentItem = NULL;
    if(NULL != currItem) {
        parentItem = DomItem::fromItemData(currItem);
        if(parentItem->getType() != DomItem::ET_ELEMENT)
            return ;
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return;
        }
    }

    int pos = 0;
    if(parentItem->hasChildOfName(tr("Text")))
        pos++;

    DomItem *theNewItem = new DomItem(addNameToPool(tr("Private")), "", this, parentItem);
    theNewItem->setNodeType();

    AddPrivate element(window);
    element.setModal(true);
    element.setTarget(theNewItem);
    if(element.exec() == QDialog::Accepted) {
        insertItemInternal(theNewItem, parentItem, tree, true, pos);
    }
}

void DomModel::addSubstation(QWidget *window, QTreeWidget *tree)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(true);
    DomItem *parentItem = NULL;
    if(NULL != currItem) {
        parentItem = DomItem::fromItemData(currItem);
        if(parentItem->getType() != DomItem::ET_ELEMENT)
            return ;
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return;
        }
    }
    int pos = 0;
    for(int i = 0 ; i < parentItem->getItems().count(); i++) {
        if(parentItem->getItems().at(i)->tag() == "Header")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "Substation")
            pos ++;
    }

    addChildToItem(window, tree, parentItem, tr("Substation"), true, pos);
}

void DomModel::addCommunication(QWidget *window, QTreeWidget *tree)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(true);
    DomItem *parentItem = NULL;
    if(NULL != currItem) {
        parentItem = DomItem::fromItemData(currItem);
        if(parentItem->getType() != DomItem::ET_ELEMENT)
            return ;
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return;
        }
    }
    int pos = 0;
    for(int i = 0 ; i < parentItem->getItems().count(); i++) {
        if(parentItem->getItems().at(i)->tag() == "Header")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "Substation")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "Communication")
            pos ++;
    }

    addChildToItem(window, tree, parentItem, tr("Communication"), true, pos);
}

void DomModel::addIED(QWidget *window, QTreeWidget *tree)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(true);
    DomItem *parentItem = NULL;
    if(NULL != currItem) {
        parentItem = DomItem::fromItemData(currItem);
        if(parentItem->getType() != DomItem::ET_ELEMENT)
            return ;
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return;
        }
    }
    int pos = 0;
    for(int i = 0 ; i < parentItem->getItems().count(); i++) {
        if(parentItem->getItems().at(i)->tag() == "Header")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "Substation")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "Communication")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "IED")
            pos ++;
    }

    addChildToItem(window, tree, parentItem, tr("IED"), true, pos);
}

void DomModel::addDataTypeTemplates(QWidget *window, QTreeWidget *tree)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(true);
    DomItem *parentItem = NULL;
    if(NULL != currItem) {
        parentItem = DomItem::fromItemData(currItem);
        if(parentItem->getType() != DomItem::ET_ELEMENT)
            return ;
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return;
        }
    }
    int pos = 0;
    for(int i = 0 ; i < parentItem->getItems().count(); i++) {
        if(parentItem->getItems().at(i)->tag() == "Header")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "Substation")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "Communication")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "IED")
            pos ++;
    }

    addChildToItem(window, tree, parentItem, tr("DataTypeTemplates"), true, pos);
}


void DomModel::addHistory(QWidget *window, QTreeWidget *tree)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(true);
    DomItem *parentItem = NULL;
    if(NULL != currItem) {
        parentItem = DomItem::fromItemData(currItem);
        if(parentItem->getType() != DomItem::ET_ELEMENT)
            return ;
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return;
        }
    }

    DomItem *theNewItem = new DomItem(addNameToPool(tr("History")), "", this, parentItem);
    DomItem *hitem = new DomItem(addNameToPool("Hitem"), "", this, theNewItem);
    hitem->addAttribute("version", "1.00");
    hitem->addAttribute("revision", "1.01");
    hitem->addAttribute("when", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    hitem->addAttribute("who", "ICD Creator");
    theNewItem->addChild(hitem);
    if(NULL != theNewItem) {
        insertItemInternal(theNewItem, isEmptyE ? NULL : parentItem, tree, true, -1);
    }
}

void DomModel::addHitem(QWidget *window, QTreeWidget *tree)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(true);
    DomItem *parentItem = NULL;
    if(NULL != currItem) {
        parentItem = DomItem::fromItemData(currItem);
        if(parentItem->getType() != DomItem::ET_ELEMENT)
            return ;
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return;
        }
    }

    addChildToItem(window, tree, parentItem, tr("Hitem"), true, -1);
}

void DomModel::addSubNetwork(QWidget *window, QTreeWidget *tree)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(true);
    DomItem *parentItem = NULL;
    if(NULL != currItem) {
        parentItem = DomItem::fromItemData(currItem);
        if(parentItem->getType() != DomItem::ET_ELEMENT)
            return ;
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return;
        }
    }

    addChildToItem(window, tree, parentItem, tr("SubNetwork"), true, -1);
}

void DomModel::addBitRate(QWidget *window, QTreeWidget *tree)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(true);
    DomItem *parentItem = NULL;
    if(NULL != currItem) {
        parentItem = DomItem::fromItemData(currItem);
        if(parentItem->getType() != DomItem::ET_ELEMENT)
            return ;
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return;
        }
    }

    addChildToItem(window, tree, parentItem, tr("BitRate"), true, 0);
}

void DomModel::addConnectedAP(QWidget *window, QTreeWidget *tree)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(true);
    DomItem *parentItem = NULL;
    if(NULL != currItem) {
        parentItem = DomItem::fromItemData(currItem);
        if(parentItem->getType() != DomItem::ET_ELEMENT)
            return ;
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return;
        }
    }

    addChildToItem(window, tree, parentItem, tr("ConnectedAP"), true, -1);
}

void DomModel::addAddress(QWidget *window, QTreeWidget *tree)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(true);
    DomItem *parentItem = NULL;
    if(NULL != currItem) {
        parentItem = DomItem::fromItemData(currItem);
        if(parentItem->getType() != DomItem::ET_ELEMENT)
            return ;
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return;
        }
    }

    addChildToItem(window, tree, parentItem, tr("Address"), true, 0);
}

void DomModel::addGSE(QWidget *window, QTreeWidget *tree)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(true);
    DomItem *parentItem = NULL;
    if(NULL != currItem) {
        parentItem = DomItem::fromItemData(currItem);
        if(parentItem->getType() != DomItem::ET_ELEMENT)
            return ;
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return;
        }
    }

    addChildToItem(window, tree, parentItem, tr("GSE"), true, -1);
}

void DomModel::addSMV(QWidget *window, QTreeWidget *tree)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(true);
    DomItem *parentItem = NULL;
    if(NULL != currItem) {
        parentItem = DomItem::fromItemData(currItem);
        if(parentItem->getType() != DomItem::ET_ELEMENT)
            return ;
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return;
        }
    }

    addChildToItem(window, tree, parentItem, tr("SMV"), true, -1);
}

void DomModel::addPhysconn(QWidget *window, QTreeWidget *tree)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(true);
    DomItem *parentItem = NULL;
    if(NULL != currItem) {
        parentItem = DomItem::fromItemData(currItem);
        if(parentItem->getType() != DomItem::ET_ELEMENT)
            return ;
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return;
        }
    }

    addChildToItem(window, tree, parentItem, tr("PhysConn"), true, -1);
}

void DomModel::addP(QWidget *window, QTreeWidget *tree)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(true);
    DomItem *parentItem = NULL;
    if(NULL != currItem) {
        parentItem = DomItem::fromItemData(currItem);
        if(parentItem->getType() != DomItem::ET_ELEMENT)
            return ;
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return;
        }
    }

    addChildToItem(window, tree, parentItem, tr("P"), true, -1);
}

void DomModel::addMinTime(QWidget *window, QTreeWidget *tree)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(true);
    DomItem *parentItem = NULL;
    if(NULL != currItem) {
        parentItem = DomItem::fromItemData(currItem);
        if(parentItem->getType() != DomItem::ET_ELEMENT)
            return ;
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return;
        }
    }

    addChildToItem(window, tree, parentItem, tr("MinTime"), true, 0);
}

void DomModel::addMaxTime(QWidget *window, QTreeWidget *tree)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(true);
    DomItem *parentItem = NULL;
    if(NULL != currItem) {
        parentItem = DomItem::fromItemData(currItem);
        if(parentItem->getType() != DomItem::ET_ELEMENT)
            return ;
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return;
        }
    }

    addChildToItem(window, tree, parentItem, tr("MaxTime"), true, -1);
}

void DomModel::addServices(QWidget *window, QTreeWidget *tree)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(true);
    DomItem *parentItem = NULL;
    if(NULL != currItem) {
        parentItem = DomItem::fromItemData(currItem);
        if(parentItem->getType() != DomItem::ET_ELEMENT)
            return ;
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return;
        }
    }

    addChildToItem(window, tree, parentItem, tr("Services"), true, 0);
}

void DomModel::addAccessPoint(QWidget *window, QTreeWidget *tree)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(true);
    DomItem *parentItem = NULL;
    if(NULL != currItem) {
        parentItem = DomItem::fromItemData(currItem);
        if(parentItem->getType() != DomItem::ET_ELEMENT)
            return ;
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return;
        }
    }

    addChildToItem(window, tree, parentItem, tr("AccessPoint"), true, -1);
}

void DomModel::addServer(QWidget *window, QTreeWidget *tree)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(true);
    DomItem *parentItem = NULL;
    if(NULL != currItem) {
        parentItem = DomItem::fromItemData(currItem);
        if(parentItem->getType() != DomItem::ET_ELEMENT)
            return ;
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return;
        }
    }

    addChildToItem(window, tree, parentItem, tr("Server"), true, 0);
}

void DomModel::addServerAt(QWidget *window, QTreeWidget *tree)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(true);
    DomItem *parentItem = NULL;
    if(NULL != currItem) {
        parentItem = DomItem::fromItemData(currItem);
        if(parentItem->getType() != DomItem::ET_ELEMENT)
            return ;
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return;
        }
    }

    addChildToItem(window, tree, parentItem, tr("ServerAt"), true, -1);
}

void DomModel::addGOOSESecurity(QWidget *window, QTreeWidget *tree)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(true);
    DomItem *parentItem = NULL;
    if(NULL != currItem) {
        parentItem = DomItem::fromItemData(currItem);
        if(parentItem->getType() != DomItem::ET_ELEMENT)
            return ;
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return;
        }
    }

    addChildToItem(window, tree, parentItem, tr("GOOSESecurity"), true, -1);
}

void DomModel::addSMVSecurity(QWidget *window, QTreeWidget *tree)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(true);
    DomItem *parentItem = NULL;
    if(NULL != currItem) {
        parentItem = DomItem::fromItemData(currItem);
        if(parentItem->getType() != DomItem::ET_ELEMENT)
            return ;
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return;
        }
    }

    addChildToItem(window, tree, parentItem, tr("SMVSecurity"), true, -1);
}

void DomModel::addSubject(QWidget *window, QTreeWidget *tree)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(true);
    DomItem *parentItem = NULL;
    if(NULL != currItem) {
        parentItem = DomItem::fromItemData(currItem);
        if(parentItem->getType() != DomItem::ET_ELEMENT)
            return ;
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return;
        }
    }

    addChildToItem(window, tree, parentItem, tr("Subject"), true, -1);
}

void DomModel::addIssuerName(QWidget *window, QTreeWidget *tree)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(true);
    DomItem *parentItem = NULL;
    if(NULL != currItem) {
        parentItem = DomItem::fromItemData(currItem);
        if(parentItem->getType() != DomItem::ET_ELEMENT)
            return ;
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return;
        }
    }

    addChildToItem(window, tree, parentItem, tr("IssuerName"), true, -1);
}

void DomModel::addAuthentication(QWidget *window, QTreeWidget *tree)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(true);
    DomItem *parentItem = NULL;
    if(NULL != currItem) {
        parentItem = DomItem::fromItemData(currItem);
        if(parentItem->getType() != DomItem::ET_ELEMENT)
            return ;
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return;
        }
    }

    addChildToItem(window, tree, parentItem, tr("Authentication"), true, 0);
}


void DomModel::addLDevice(QWidget *window, QTreeWidget *tree)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(true);
    DomItem *parentItem = NULL;
    if(NULL != currItem) {
        parentItem = DomItem::fromItemData(currItem);
        if(parentItem->getType() != DomItem::ET_ELEMENT)
            return ;
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return;
        }
    }

    addChildToItem(window, tree, parentItem, tr("LDevice"), true, -1);
}


void DomModel::addAssociation(QWidget *window, QTreeWidget *tree)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(true);
    DomItem *parentItem = NULL;
    if(NULL != currItem) {
        parentItem = DomItem::fromItemData(currItem);
        if(parentItem->getType() != DomItem::ET_ELEMENT)
            return ;
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return;
        }
    }

    addChildToItem(window, tree, parentItem, tr("Association"), true, -1);
}

void DomModel::addLN0(QWidget *window, QTreeWidget *tree)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(currItem);
    DomItem *parentItem = NULL;
    if(NULL != currItem) {
        parentItem = DomItem::fromItemData(currItem);
        if(parentItem->getType() != DomItem::ET_ELEMENT)
            return ;
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return;
        }
    }

    DomItem *theNewElement = new DomItem(addNameToPool(tr("LN0")), "", this, parentItem);
    theNewElement->setNodeType();
//    theNewElement->addAttribute("lnClass", "LLN0");

    if(!editLNodeItem(window, theNewElement)) {
        delete theNewElement;
        theNewElement = NULL ;
    }

    if(NULL != theNewElement) {
        insertItemInternal(theNewElement, isEmptyE ? NULL : parentItem, tree, true, 0);
    }

}

void DomModel::addLN(QWidget *window, QTreeWidget *tree)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(true);
    DomItem *parentItem = NULL;
    if(NULL != currItem) {
        parentItem = DomItem::fromItemData(currItem);
        if(parentItem->getType() != DomItem::ET_ELEMENT)
            return ;
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return;
        }
    }

    DomItem *theNewElement = new DomItem(addNameToPool(tr("LN")), "", this, parentItem);
    theNewElement->setNodeType();

    if(!editLNodeItem(window, theNewElement)) {
        delete theNewElement;
        theNewElement = NULL ;
    }
    if(NULL != theNewElement) {
        insertItemInternal(theNewElement, isEmptyE ? NULL : parentItem, tree, true, -1);
    }

}

void DomModel::addAccessControl(QWidget *window, QTreeWidget *tree)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(true);
    DomItem *parentItem = NULL;
    if(NULL != currItem) {
        parentItem = DomItem::fromItemData(currItem);
        if(parentItem->getType() != DomItem::ET_ELEMENT)
            return ;
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return;
        }
    }

    addChildToItem(window, tree, parentItem, tr("AccessControl"), true, -1);
}

void DomModel::addDataSet(QWidget *window, QTreeWidget *tree)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(true);
    DomItem *parentItem = NULL;
    if(NULL != currItem) {
        parentItem = DomItem::fromItemData(currItem);
        if(parentItem->getType() != DomItem::ET_ELEMENT)
            return ;
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return;
        }
    }

    DomItem *theNewElement = new DomItem(addNameToPool(tr("DataSet")), "", this, parentItem);
    if(!editDataSetItem(window, theNewElement)) {
        delete theNewElement;
        theNewElement = NULL ;
    }    

    int pos = 0;
    for(int i = 0 ; i < parentItem->getItems().count(); i++) {
        if(parentItem->getItems().at(i)->tag() == "Text")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "Private")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "DataSet")
            pos ++;
    }
    if(NULL != theNewElement) {
        insertItemInternal(theNewElement, isEmptyE ? NULL : parentItem, tree, true, pos);
    }

}

void DomModel::addReportControl(QWidget *window, QTreeWidget *tree)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(true);
    DomItem *parentItem = NULL;
    if(NULL != currItem) {
        parentItem = DomItem::fromItemData(currItem);
        if(parentItem->getType() != DomItem::ET_ELEMENT)
            return ;
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return;
        }
    }
    DomItem *theNewElement = new DomItem(addNameToPool(tr("ReportControl")), "", this, parentItem);
    if(!editReportControlItem(window, theNewElement)) {
        delete theNewElement;
        theNewElement = NULL ;
    }

    int pos = 0;
    for(int i = 0 ; i < parentItem->getItems().count(); i++) {
        if(parentItem->getItems().at(i)->tag() == "Text")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "Private")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "DataSet")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "ReportControl")
            pos ++;
    }

    if(NULL != theNewElement) {
        insertItemInternal(theNewElement, isEmptyE ? NULL : parentItem, tree, true, pos);
    }
}

void DomModel::addLogControl(QWidget *window, QTreeWidget *tree)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(true);
    DomItem *parentItem = NULL;
    if(NULL != currItem) {
        parentItem = DomItem::fromItemData(currItem);
        if(parentItem->getType() != DomItem::ET_ELEMENT)
            return ;
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return;
        }
    }

    int pos = 0;
    for(int i = 0 ; i < parentItem->getItems().count(); i++) {
        if(parentItem->getItems().at(i)->tag() == "Text")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "Private")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "DataSet")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "ReportControl")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "LogControl")
            pos ++;
    }

    addChildToItem(window, tree, parentItem, tr("LogControl"), true, pos);
}

void DomModel::addInputs(QWidget *window, QTreeWidget *tree)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(true);
    DomItem *parentItem = NULL;
    if(NULL != currItem) {
        parentItem = DomItem::fromItemData(currItem);
        if(parentItem->getType() != DomItem::ET_ELEMENT)
            return ;
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return;
        }
    }

    int pos = 0;
    for(int i = 0 ; i < parentItem->getItems().count(); i++) {
        if(parentItem->getItems().at(i)->tag() == "Text")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "Private")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "DataSet")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "ReportControl")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "LogControl")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "DOI")
            pos ++;
    }

    addChildToItem(window, tree, parentItem, tr("Inputs"), true, pos);
}

void DomModel::addLog(QWidget *window, QTreeWidget *tree)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(true);
    DomItem *parentItem = NULL;
    if(NULL != currItem) {
        parentItem = DomItem::fromItemData(currItem);
        if(parentItem->getType() != DomItem::ET_ELEMENT)
            return ;
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return;
        }
    }

    int pos = 0;
    for(int i = 0 ; i < parentItem->getItems().count(); i++) {
        if(parentItem->getItems().at(i)->tag() == "Text")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "Private")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "DataSet")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "ReportControl")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "LogControl")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "DOI")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "Inputs")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "Log")
            pos ++;
    }

    addChildToItem(window, tree, parentItem, tr("Log"), true, pos);
}

void DomModel::addGSEControl(QWidget *window, QTreeWidget *tree)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(true);
    DomItem *parentItem = NULL;
    if(NULL != currItem) {
        parentItem = DomItem::fromItemData(currItem);
        if(parentItem->getType() != DomItem::ET_ELEMENT)
            return ;
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return;
        }
    }

    int pos = 0;
    for(int i = 0 ; i < parentItem->getItems().count(); i++) {
        if(parentItem->getItems().at(i)->tag() == "Text")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "Private")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "DataSet")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "ReportControl")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "LogControl")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "DOI")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "Inputs")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "Log")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "GSEControl")
            pos ++;
    }
    addChildToItem(window, tree, parentItem, tr("GSEControl"), true, pos);
}

void DomModel::addSMVControl(QWidget *window, QTreeWidget *tree)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(true);
    DomItem *parentItem = NULL;
    if(NULL != currItem) {
        parentItem = DomItem::fromItemData(currItem);
        if(parentItem->getType() != DomItem::ET_ELEMENT)
            return ;
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return;
        }
    }

    int pos = 0;
    for(int i = 0 ; i < parentItem->getItems().count(); i++) {
        if(parentItem->getItems().at(i)->tag() == "Text")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "Private")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "DataSet")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "ReportControl")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "LogControl")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "DOI")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "Inputs")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "Log")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "GSEControl")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "SampledValueControl")
            pos ++;
    }

    addChildToItem(window, tree, parentItem, tr("SampledValueControl"), true, pos);
}

void DomModel::addSettingControl(QWidget *window, QTreeWidget *tree)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(true);
    DomItem *parentItem = NULL;
    if(NULL != currItem) {
        parentItem = DomItem::fromItemData(currItem);
        if(parentItem->getType() != DomItem::ET_ELEMENT)
            return ;
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return;
        }
    }

    int pos = 0;
    for(int i = 0 ; i < parentItem->getItems().count(); i++) {
        if(parentItem->getItems().at(i)->tag() == "Text")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "Private")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "DataSet")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "ReportControl")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "LogControl")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "DOI")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "Inputs")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "Log")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "GSEControl")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "SampledValueControl")
            pos ++;
        if(parentItem->getItems().at(i)->tag() == "SettingControl")
            pos ++;
    }
    addChildToItem(window, tree, parentItem, tr("SettingControl"), true, pos);
}

void DomModel::addChild(QWidget *window, QTreeWidget *tree)
{
    addChild(window, tree, NULL);
}

// if empty, add, else add only to element
void DomModel::addChild(QWidget *window, QTreeWidget *tree, DomItem *preElement)
{
    bool execAddChild = false;
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(true);
    DomItem *parentElement = NULL ;
    if(NULL != currItem) {
        parentElement = DomItem::fromItemData(currItem);
        if(parentElement->getType() != DomItem::ET_ELEMENT)
            return ;
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return;
        }
    }
    DomItem *theNewElement = preElement ;
    if(NULL == theNewElement) {
        theNewElement = newItem();
        if(!editNodeItem(window, theNewElement)) {
            delete theNewElement;
            theNewElement = NULL ;
        }
    } else {
        EditElement element(window);
        element.setModal(true);
        element.setTarget(theNewElement);
        if(element.exec() == QDialog::Accepted)
            execAddChild = true;
    }

    if(NULL != theNewElement && execAddChild) {
        insertItemInternal(theNewElement, isEmptyE ? NULL : parentElement, tree);
    }
}

// TODO: check for the root item
DomItem* DomModel::addChildToItem(QWidget *window, QTreeWidget *tree, DomItem *parentElement, const QString &elementTag, const bool useUndo, int position)
{
    bool isEmptyE = isEmpty(true);
    if(NULL != parentElement) {
        if(parentElement->getType() != DomItem::ET_ELEMENT)
            return NULL ;
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return NULL ;
        }
    }
    DomItem *theNewElement = new DomItem(addNameToPool(elementTag), "", this, parentElement);
    if(NULL != theNewElement) {
        insertItemInternal(theNewElement, isEmptyE ? NULL : parentElement, tree, useUndo, position);
    }
    return theNewElement ;
}

QTreeWidgetItem *DomModel::getSelItem(QTreeWidget *tree)
{
    QList<QTreeWidgetItem *>selItems =  tree->selectedItems();
    if(selItems.count() < 1)
        return NULL;
    return selItems.at(0);
}

void DomModel::addBrother(QWidget *window, QTreeWidget *tree)
{
    addBrother(window, tree, NULL);
}

// added for testability
void DomModel::addBrother(QWidget *window, QTreeWidget *tree, DomItem* aNewElement)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(true);
    // DomModel vuota, aggiungo il primo ed ultimo
    if(!isEmptyE && (NULL == currItem)) {
        Utils::errorNoSel(window);
        return;
    }
    // Check the root of the tree.
    DomItem *brotherElement = DomItem::fromItemData(currItem);

    if(!isEmptyE && (NULL != currItem)) {
        if((currItem->parent() == NULL) && (NULL != root())) {
            Utils::error(window, tr("Only one root item in permitted in XML syntax."));
            return;
        }
    }
    bool canGo = false;
    DomItem *theNewElement = NULL;
    if(NULL == aNewElement) {
        theNewElement = newItem();
        if(editNodeItem(window, theNewElement)) {
            canGo = true;
        }
    } else {
        canGo = true ;
        theNewElement = aNewElement ;
    }
    if(canGo) {
        appendItemInternal(theNewElement, brotherElement, tree);
    } else {
        if(NULL != theNewElement) {
            delete theNewElement;
        }
    }
}

void DomModel::paste(QWidget *window, QTreeWidget *tree, DomItem *pasteElement)
{
    // lo inserisce come figlio dell'item corrente
    QTreeWidgetItem *currItem = getSelItem(tree);
    if(NULL == currItem) {
        Utils::errorNoSel(window);
        return;
    }
    DomItem *parentElement = DomItem::fromItemData(currItem);
    pasteInternals(tree, parentElement, pasteElement, -1);
}

void DomModel::pasteInternals(QTreeWidget *tree, DomItem *parentElement, DomItem *pasteElement, const int position)
{
    //if not sel, at the root iif rule is empty
    //sse extists an item
    //append l'item ( o lo inserisce, con tutti i figli e poi ricarica la lista)
    DomItem *theNewElement = NULL ;
    if(NULL == pasteElement) {
        return ;
    }
    if(isEmpty(true)) {
        theNewElement = pasteElement->copyTo(*new DomItem(this));
        addTopItem(theNewElement, position);
        theNewElement->setChildItem(tree, NULL, paintInfo, true, -1);
    } else {
        theNewElement = pasteElement->copyTo(*new DomItem(this));
        if(!parentElement->isElement()) {
            return ;
        }
        if(-1 == position) {
            parentElement->addChild(theNewElement);
        } else {
            parentElement->addChildAt(theNewElement, position);
        }
        theNewElement->setChildItem(tree, parentElement->getUI(), paintInfo, true, position);
    }
    addUndoInsert(tree, theNewElement);
    setModified(true);
}

void DomModel::pasteNoUI(DomItem *pasteItem, DomItem *pasteTo)
{
    DomItem *theNewItem = NULL ;
    if(NULL == pasteItem) {
        return ;
    }
    if(NULL == pasteTo) {
        theNewItem = pasteItem->copyTo(*new DomItem(this));
        addTopItem(theNewItem);
        theNewItem->setChildItem(NULL, NULL, paintInfo, false, -1);
    } else {
        // lo inserisce come figlio dell'item corrente
        theNewItem = pasteItem->copyTo(*new DomItem(this));
        DomItem *parentElement = pasteTo;
        if(!parentElement->isElement())
            return ;
        parentElement->addChild(theNewItem);
        theNewItem->setChildItem(NULL, parentElement->getUI(), paintInfo, false, -1);
    }
    _undoStack.clear();
    Utils::TODO_NEXT_RELEASE("undo");
    setModified(true);
}

void DomModel::insertInternal(QTreeWidget *tree, DomItem *parentElement, DomItem *pasteElement, const int position)
{
    //if not selected, at the root iif rule is empty
    //sse extists an item
    //append l'item ( o lo inserisce, con tutti i figli e poi ricarica la lista)
    DomItem *theNewElement = NULL ;
    if(NULL == pasteElement) {
        return ;
    }
    if(NULL == parentElement) {
        theNewElement = pasteElement->copyTo(*new DomItem(this));
        addTopItem(theNewElement, position);
        theNewElement->setChildItem(tree, NULL, paintInfo, true, -1);
    } else {
        theNewElement = pasteElement->copyTo(*new DomItem(this));
        // serve???
        if(!parentElement->isElement()) {
            return ;
        }
        if(-1 == position) {
            parentElement->addChild(theNewElement);
        } else {
            parentElement->addChildAt(theNewElement, position);
        }
        theNewElement->setChildItem(tree, parentElement->getUI(), paintInfo, true, position);
    }
    setModified(true);
}

void DomModel::expand(QTreeWidget *tree)
{
    if(NULL != rootItem) {
        rootItem->expand(tree);
    }
}

void DomModel::notifyDeletionTopItem(DomItem *pEl)
{
    //if (pEl->getType() == DomItem::ET_ELEMENT) {
    //Q_ASSERT_X(rootItem == pEl, "notifyDeletionTopElement", "rootItem is out of sync");
    // take out element from vector
    int elementIndex = childItems.indexOf(pEl);
    if(-1 != elementIndex) {
        childItems.remove(elementIndex);
    }
    if(pEl->getType() == DomItem::ET_ELEMENT) {
        rootItem = NULL ;
    }
}

// empty-> top, else append to element
void DomModel::addComment(QWidget *window, QTreeWidget *tree)
{
    addComment(window, tree, NULL);
}
// empty-> top, else append to element
void DomModel::addComment(QWidget *window, QTreeWidget *tree, DomItem *newComment)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(false);
    DomItem *parentElement = NULL ;
    if(NULL != currItem) {
        parentElement = DomItem::fromItemData(currItem);
        if(NULL != parentElement) {
            if(parentElement->getType() != DomItem::ET_ELEMENT) {
                Utils::error(tr("Comments can be added only to elements, consider appending, instead"));
                return ;
            }
        }
    } else {
        if(!isEmptyE) {
            Utils::error(tr("Please, select an element to append the comment"));
            return ;
        }
    }

    if(NULL == newComment) {
        DomItem *theNewElement = newItem(DomItem::ET_COMMENT);
        if(editNodeComment(window, theNewElement)) {
            newComment = theNewElement;
        } else {
            delete theNewElement;
            theNewElement = NULL ;
        }
    }
    if(NULL != newComment) {
        insertItemInternal(newComment, parentElement, tree);
    }
}

void DomModel::appendComment(QWidget *window, QTreeWidget *tree)
{
    appendComment(window, tree, NULL);
}

void DomModel::appendComment(QWidget *window, QTreeWidget *tree, DomItem *newComment)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(false);
    DomItem *parentElement = NULL ;
    DomItem *brotherElement  = NULL;
    if(NULL != currItem) {
        brotherElement  = DomItem::fromItemData(currItem);
        parentElement = brotherElement->parent();
        if(NULL != parentElement) {
            if(parentElement->getType() != DomItem::ET_ELEMENT) {
                Utils::error(tr("Comments can be added only to elements, consider appending, instead"));
                return ;
            }
        }
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return ;
        }
    }
    // DomModel vuota, aggiungo il primo ed ultimo
    DomItem *theNewElement = NULL;
    if(NULL == newComment) {
        theNewElement = newItem(DomItem::ET_COMMENT);
        if(!editNodeComment(window, theNewElement)) {
            delete theNewElement;
            theNewElement = NULL;
        }
    } else {
        theNewElement = newComment;
    }

    if(NULL != theNewElement) {
        appendItemInternal(theNewElement, brotherElement, tree);
    } else {
        delete theNewElement;
    }
}

void DomModel::appendProcessingInstruction(QWidget *window, QTreeWidget *tree)
{
    appendProcessingInstruction(window, tree, NULL);
}

void DomModel::appendProcessingInstruction(QWidget *window, QTreeWidget *tree, DomItem *newPI)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(false);
    DomItem *parentElement = NULL ;
    DomItem *brotherElement  = NULL;
    if(NULL != currItem) {
        brotherElement  = DomItem::fromItemData(currItem);
        parentElement = brotherElement->parent();
        if(NULL != parentElement) {
            if(parentElement->getType() != DomItem::ET_ELEMENT) {
                Utils::error(tr("Processing instructions can be added only to elements, consider appending, instead"));
                return ;
            }
        }
    } else {
        if(!isEmptyE) {
            Utils::errorNoSel(window);
            return ;
        }
    }
    // DomModel vuota, aggiungo il primo ed ultimo
    DomItem *piToIns = NULL ;
    if(NULL == newPI) {
        DomItem *theNewElement = newItem(DomItem::ET_PROCESSING_INSTRUCTION);
        if(editProcessingInstruction(window, theNewElement)) {
            piToIns = theNewElement ;
        } else {
            delete theNewElement ;
        }
    } else {
        piToIns = newPI ;
    }
    if(NULL != piToIns) {
        appendItemInternal(piToIns, brotherElement, tree);
    }
}

void DomModel::addProcessingInstruction(QWidget *window, QTreeWidget *tree)
{
    addProcessingInstruction(window, tree, NULL);
}

void DomModel::addProcessingInstruction(QWidget *window, QTreeWidget *tree, DomItem *newPI)
{
    QTreeWidgetItem *currItem = getSelItem(tree);
    bool isEmptyE = isEmpty(false);
    DomItem *parentElement = NULL ;
    if(NULL != currItem) {
        parentElement = DomItem::fromItemData(currItem);
        if(NULL != parentElement) {
            if(parentElement->getType() != DomItem::ET_ELEMENT) {
                Utils::error(tr("Processing instructions can be added only to elements, consider appending, instead"));
                return ;
            }
        }
    } else {
        if(!isEmptyE) {
            Utils::error(tr("Please, select an element to append the processing instruction"));
            return ;
        }
    }
    DomItem *piToIns = NULL ;
    if(NULL == newPI) {
        DomItem *theNewElement = newItem(DomItem::ET_PROCESSING_INSTRUCTION);
        if(editProcessingInstruction(window, theNewElement)) {
            piToIns = theNewElement ;
        } else {
            delete theNewElement ;
        }
    } else {
        piToIns = newPI ;
    }
    if(NULL != piToIns) {
        insertItemInternal(piToIns, parentElement, tree);
    }
}


void DomModel::findText(FindTextParams &findArgs, DomItem *selectedItem)
{
    unseletedAll();
    if((NULL != selectedItem) && findArgs.isLookOnlyChildren()) {
        selectedItem->findText(findArgs);
    } else {
        bool isHiliteAll = findArgs.isHiliteAll();
        QVectorIterator<DomItem*> it(childItems);
        while(it.hasNext()) {
            if(it.next()->findText(findArgs)) {
                if(!isHiliteAll) {
                    break;
                }
            }
        }// while next
    }
}

void DomModel::unseletedAll()
{
    QHashIterator<int, DomItem*> sel(selection);
    while(sel.hasNext()) {
        sel.next();
        DomItem *element = sel.value() ;
        element->unselected();
    }
    selection.clear();
//    D(printf("cleared\n"));
}


void DomModel::addSelected(DomItem *element)
{
    selection.insert(element->getInstanceId(), element);
//    D(printf("new element, total is %d \n", selection.size()));
}


void DomModel::takeOutItem(DomItem* element)
{
//    D(printf("before %d elements\n", selection.size()));
    int id = element->getInstanceId();
    if(selection.contains(id)) {
        selection.remove(id);
    }
//    D(printf("after %d elements\n", selection.size()));
}

void DomModel::setPaintInfo(PaintInfo *newValue)
{
    if(NULL != paintInfo) {
        delete paintInfo;
    }
    paintInfo = newValue ;
}

PaintInfo *DomModel::getPaintInfo()
{
    if(NULL == paintInfo) {
        paintInfo = new PaintInfo();
    }
    return paintInfo;
}

//void DomModel::setEditHook(EditHook theEditHook)
//{
//    _editHook = theEditHook ;
//}

//void DomModel::setEditTextHook(EditTextHook theEditTextHook)
//{
//    _editTextHook = theEditTextHook ;
//}

void DomModel::redisplayItem(DomItem *element)
{
    element->displayWithPaintInfo(paintInfo);
//    element->displayRecursive(paintInfo);
}



void DomModel::setUserDefinedXsd(const QString &path)
{
    _userDefinedXsd = path ;
}

void DomModel::checkValidationReference()
{
    _noNameSpaceXsd = "" ;
    _documentXsd = "" ;
    _namespacesByPrefixAndName.clear();
    _namespacesByNameAndPrefix.clear();
    _schemaLocationsByNamespace.clear();
    DomItem *theRoot = root();
    if(NULL != theRoot) {
        QString attrNSName ;
        QString attrNSNoNamespace ;
        QList<Attribute*> attrs = theRoot->getAttributesList();
        Attribute *schemaURIAttr = NULL ;
        QString namespaceXsi = "" ;
        // collect all namespaces along with declarations
        foreach(Attribute * attr, attrs) {
            if(attr->name.startsWith("xmlns:") || (attr->name == "xmlns")) {
                // add a namespace
                int pos = attr->name.indexOf(":");
                QString ns ;
                if(pos >= 0) {
                    if(pos < attr->name.length()) {
                        ns = attr->name.mid(pos + 1);
                    }
                }
                // ns can be empty
                _namespacesByPrefixAndName.insert(ns, attr->value);
                _namespacesByNameAndPrefix.insert(attr->value, ns);
                // look for special value to identify schema namespace
                if(attr->value == SCHEMA_URI) {
                    schemaURIAttr = attr ;
                    namespaceXsi = ns ;
                }
            }
        } // end of scan for namespaces

        // found the namespace of xsi, lookup for locations
        if(NULL != schemaURIAttr) {
            attrNSName = namespaceXsi + ":";
            attrNSName += SCHEMA_LOCATION;
            attrNSNoNamespace = namespaceXsi + ":";
            attrNSNoNamespace += SCHEMA_NONS_LOCATION ;

            Attribute * attrNoNs = theRoot->getAttribute(attrNSNoNamespace);
            if(NULL != attrNoNs) {
                _noNameSpaceXsd = attrNoNs->value;
                _documentXsd = _noNameSpaceXsd ;
            }
            // ---------------------------------------------------
            // get all the attributes
            Attribute * attr = theRoot->getAttribute(attrNSName);
            if(NULL != attr) {
                QString value = attr->value;
                decodeASchema(value);
                // set the first
                if(_schemaLocationsByNamespace.size() > 0) {
                    if(_documentXsd.isEmpty()) {
                        QString nsDocument = _namespacesByPrefixAndName[""];
                        _documentXsd = _schemaLocationsByNamespace[nsDocument];
                    }
                }
            }
        } else {
            // we not consider using xsi:etc alone, because it is off specifications.
            /****************************************************
                        Attribute * attrNs = theRoot->getAttribute(ATTRIBUTE_SCHEMA_LOCATION);
                        if(NULL != attrNs) {
                            decodeASchema(attrNs->value);
                            if(_namespacesLocationXsd.size() > 0) {
                                if( _documentXsd.isEmpty() ) {
                                    _documentXsd = _namespacesLocationXsd.values().at(0);
                                }
                                _namespacesNamesXsd.insert(XSI_NAMESPACE, _documentXsd);
                                _namespacesNsNamesXsd.insert(_documentXsd, XSI_NAMESPACE);
                            }
                        }

                        Attribute * attrNoNs = theRoot->getAttribute(ATTRIBUTE_SCHEMA_LOCATION);
                        if(NULL != attrNoNs) {
                            decodeASchema(attrNs->value);
                            if(_namespacesLocationXsd.size() > 0) {
                                if( _documentXsd.isEmpty() ) {
                                    _documentXsd = _namespacesLocationXsd.values().at(0);
                                }
                                _noNameSpaceXsd = _documentXsd ;
                                _namespacesNamesXsd.insert(XSI_NAMESPACE, _documentXsd);
                                _namespacesNsNamesXsd.insert(_documentXsd, XSI_NAMESPACE);
                            }
                        }
            **************************************************/
        }
    }
} // checkValidationReference()

void DomModel::decodeASchema(const QString &value)
{
    // this grummy piece of code follows w3c specifications
    QString normalizedValue = Utils::normalizeStringXML(value);

    //if(value.indexOf(" ")) {
    QStringList schemas = normalizedValue.split(" ");
    int schemasNumber = schemas.size() / 2;
    for(int i = 0 ; i < schemasNumber ; i ++) {
        _schemaLocationsByNamespace.insert(schemas.at(2 * i), schemas.at(2 * i + 1));
    }
    //} else {
    //   _documentXsd = value ;
    //}
}

bool DomModel::hasMoreThanOneXsdFile()
{
    if((_schemaLocationsByNamespace.size() > 1) || ((_schemaLocationsByNamespace.size() == 1) && !_noNameSpaceXsd.isEmpty())) {
        return true ;
    }
    return false ;
}

void DomModel::setUserAndDocumentXsd(const QString &newXsd)
{
    _documentXsd = newXsd ;
    _userDefinedXsd = newXsd;
}


void DomModel::pasteXML(QWidget *window, QTreeWidget *tree, DomModel *newDomModel)
{
    QVectorIterator<DomItem*> it(newDomModel->childItems);
    while(it.hasNext()) {
        DomItem* element = it.next() ;
        paste(window, tree, element);
    }
}

bool DomModel::collectSizeData()
{
    return _collectSizeData;
}

void DomModel::setCollectSizeData(const bool isCollect)
{
    _collectSizeData = isCollect ;
}

void DomModel::recalcSize()
{
    if(NULL != rootItem) {
        rootItem->recalcSize(true);
    }
}

void DomModel::assignCollectSizeDataFlag(const bool isCollect)
{
    bool toRecalc = !collectSizeData();
    setCollectSizeData(isCollect);
    if(isCollect && toRecalc) {
        recalcSize();
    }
}



//-------------------------------------------------------------------------------------------------------------------------------------------------

bool DomModel::loadXplore(const QString &fileName)
{
    modified = false;
    _collectSizeData = false ;
    xmlFileName = fileName ;

    XSaxHandler handler(this);
    QXmlSimpleReader reader;
    reader.setFeature("http://xml.org/sax/features/namespaces", false);
    reader.setFeature("http://xml.org/sax/features/namespace-prefixes", true);
    reader.setContentHandler(&handler);
    reader.setErrorHandler(&handler);

    QFile file(fileName);
    if(!file.open(QFile::ReadOnly | QFile::Text)) {
        return false;
    }
    bool isOk = true ;
    QXmlInputSource xmlInput(&file);
    if(!reader.parse(xmlInput)) {
        isOk = false  ;
    }
    file.close();
    return isOk ;
}

bool DomModel::isValidXsd()
{
    if(NULL == rootItem) {
        return false;
    }
    // Search in attributes.
    QString elNamespace;
    QString elLocalName;
    rootItem->namespaceofItem(elNamespace, elLocalName);
    Attribute *attribute = NULL ;
    if(!elNamespace.isEmpty()) {
        attribute = rootItem->getAttribute(QString("%1:%2").arg(XMLNS_PREFIX).arg(elNamespace));
    } else {
        attribute = rootItem->getAttribute(QString(XMLNS_PREFIX));
    }
    if(NULL == attribute) {
        return false ;
    }
    return XmlUtils::IsXsdValid(attribute->value, elLocalName);
}

int DomModel::indexOfTopLevelItem(DomItem *element)
{
    return childItems.indexOf(element);
}


int DomModel::setTopLevelItemLike(DomItem *newElement, DomItem* oldElement)
{
    int pos = childItems.indexOf(oldElement);
    if(pos >= 0) {
        childItems.insert(pos, newElement);
    }
    return pos ;
}


int DomModel::swapAndDeleteItem(DomItem *newElement, DomItem* oldElement)
{
    int pos = 1 ;
    DomItem *parentElement = oldElement->parent();
    if(NULL == parentElement) {
        pos = setTopLevelItemLike(newElement, oldElement);
    } else {
        pos = parentElement->setItemLike(newElement, oldElement);
    }
    oldElement->autoDeleteRecursive();
    return pos ;
}


// sostituisce elment con il commento
void DomModel::transformInComment(QWidget *window, QTreeWidget *tree, DomItem *elementToTransform)
{
    if(NULL == elementToTransform) {
        Utils::errorNoSel(window);
        return ;
    }
    DomItem *parentElement = elementToTransform->parent();
    DomItem *comment = new DomItem(this, DomItem::ET_COMMENT, parentElement) ;
    comment->setComment(elementToTransform->transformToText());
    int pos = swapAndDeleteItem(comment, elementToTransform);

    QTreeWidgetItem *parentUI = NULL ;
    if(NULL != parentElement) {
        parentUI = parentElement->getUI();
    }
    comment->setChildItem(tree, parentUI, paintInfo, true, pos);
//    comment->markEditedRecursive();
    clearUndo();
    setModified(true);
    return ;
}


// creates xml elements from a comment, if possible

/**
  * if  ! is possible to convert from string -> warn the user
  * if the root element exists -> error
  */
bool DomModel::generateFromComment(QTreeWidget *tree, DomItem *elementToTransform)
{
    if(NULL == elementToTransform) {

        return false;
    }
    DomItem *parentElement = elementToTransform->parent();
    if((NULL == parentElement) && (rootItem != NULL)) {

        return false ;
    }

    if(elementToTransform->getType() != DomItem::ET_COMMENT) {

        return false ;
    }
    int position = elementToTransform->indexOfSelfAsChild();
    QDomDocument document;
    if(document.setContent(elementToTransform->getComment())) {
        DomModel newModel(document, "");
        // reverse copy to have the elements inserted in the correct order
        QVectorIterator<DomItem*> reverseElementIterator(newModel.childItems);
        reverseElementIterator.toBack();
        while(reverseElementIterator.hasPrevious()) {
            DomItem * toCopyElement = reverseElementIterator.previous();
            pasteInternals(tree, parentElement, toCopyElement, position);
        }
        // note that this operation cannot be done if a valid root already exists
        elementToTransform->autoDeleteRecursive();
        clearUndo();
        return true ;
    } else {

        return false;
    }
}

DomItem *DomModel::findItemByArray(QList<int> &selection)
{
    int pos = selection.at(0);
    if(pos >= childItems.size()) {
        return NULL ;
    }

    DomItem *element = childItems.at(pos);
    if(selection.size() == 1) {
        return element ;
    }
    return findChildItemByArray(element, selection, 1);
}

DomItem *DomModel::findChildItemByArray(DomItem *element, QList<int> &selection, const int listPos)
{
    int pos = selection.at(listPos);
    QVector<DomItem*>& chs = element->getItems();
    if(pos >= chs.size()) {
        return NULL ;
    }
    DomItem *thisElement = chs.at(pos);
    if(selection.size() <= (listPos + 1)) {
        return thisElement ;
    }
    return findChildItemByArray(thisElement, selection, listPos + 1);
}

DomModel::EInsSchemaRefInfo DomModel::insertNoNamespaceSchemaReferenceAttributes()
{
    clearUndo();
    DomItem* theRoot = root();
    if(NULL == theRoot) {
        return INSERT_SCHEMA_ATTR_ERROR_NOROOT ;
    }
    DomModel::EInsSchemaRefInfo returnCode = INSERT_SCHEMA_ATTR_NOERROR;
    Attribute * attrNSSchema = root()->getAttribute(XSI_NAMESPACE_COMPLETE);
    Attribute * attrNSReference = root()->getAttribute(ATTRIBUTE_SCHEMA_NONS_LOCATION);

    if(NULL == attrNSSchema) {
        theRoot->addAttribute(XSI_NAMESPACE_COMPLETE, SCHEMA_URI);
    } else {
        returnCode = INSERT_SCHEMA_ATTR_INFO_SCHEMAPRESENT;
    }

    if(NULL == attrNSReference) {
        theRoot->addAttribute(ATTRIBUTE_SCHEMA_NONS_LOCATION, "***");
    } else {
        returnCode = INSERT_SCHEMA_ATTR_INFO_REFPRESENT ;
    }
//    theRoot->markEdited();
    QTreeWidgetItem *item = theRoot->getUI();
    if(NULL != item) {
        theRoot->display(item, paintInfo);
    }

    setModified(true);

    return returnCode ;
}

DomModel::EInsSchemaRefInfo DomModel::insertSchemaReferenceAttributes()
{
    clearUndo();
    DomItem* theRoot = root();
    if(NULL == theRoot) {
        return INSERT_SCHEMA_ATTR_ERROR_NOROOT ;
    }
    DomModel::EInsSchemaRefInfo returnCode = INSERT_SCHEMA_ATTR_NOERROR;
    Attribute * attrNSSchema = root()->getAttribute(XSI_NAMESPACE_COMPLETE);
    Attribute * attrNSReference = root()->getAttribute(ATTRIBUTE_SCHEMA_LOCATION);

    if(NULL == attrNSSchema) {
        theRoot->addAttribute(XSI_NAMESPACE_COMPLETE, SCHEMA_URI);
    } else {
        returnCode = INSERT_SCHEMA_ATTR_INFO_SCHEMAPRESENT;
    }

    if(NULL == attrNSReference) {
        theRoot->addAttribute(ATTRIBUTE_SCHEMA_LOCATION, "***");
    } else {
        returnCode = INSERT_SCHEMA_ATTR_INFO_REFPRESENT ;
    }

//    theRoot->markEdited();
    QTreeWidgetItem *item = theRoot->getUI();
    if(NULL != item) {
        theRoot->display(item, paintInfo);
    }

    setModified(true);
    return returnCode ;
}

QString DomModel::textOfCantEditMixedContentItemText()
{
    return tr("When element has mixed contents you must edit text nodes.");
}

void DomModel::hideLeafNodes()
{
    QVectorIterator<DomItem*> it(childItems);
    while(it.hasNext()) {
        DomItem *el = it.next();
        el->hideChildrenLeaves();
    }
}

void DomModel::showLeafNodes()
{
    QVectorIterator<DomItem*> it(childItems);
    while(it.hasNext()) {
        DomItem *el = it.next();
        el->showChildrenLeaves();
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------

/**
  this is an hack to collect strings in a future to lower memory consumption
  */
QString DomModel::addNameToPool(const QString &inputString)
{
    QSet<QString>::const_iterator it = _namesPool.insert(inputString);
    return *it ;
}

QString DomModel::getAttributeString(const QString &attributeString)
{
    QSet<QString>::const_iterator it = _attributeValuesPool.insert(attributeString);
    return *it ;
}

// inline QString DomModel::getName(const int index )

//-----------------------------------------------------------------------------------------------------------------------------------------

const int DomModel::ModelName = 0 ;
const int DomModel::ModelValue = 1 ;
const int DomModel::ModelColumns = 2 ;

QVariant DomModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) {
        return QVariant();
    }
    DomItem *element = static_cast<DomItem*>(index.internalPointer());
    if(NULL != element) {
        switch(role) {
        case Qt::ToolTipRole:
            return element->columnViewTooltipData();
            break;
        case Qt::DisplayRole:
            switch(index.column()) {
            case ModelValue: return QVariant(element->text);
            case ModelName: {
                return element->columnViewDisplayData(paintInfo, index.row() + 1);
            } // if name
            } // switch column
            break;
        case Qt::FontRole:
            return element->styleItemTagFont(paintInfo);
        case Qt::ForegroundRole:
            return element->styleItemTagColor(paintInfo);
        case Qt::DecorationRole:
            return element->styleItemTagIcon();
        default:
            break;
        } // switch displayRole
    }
    return QVariant();
}

Qt::ItemFlags DomModel::flags(const QModelIndex &index) const
{
    if(!index.isValid()) {
        return QAbstractItemModel::flags(index);
    }
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled ;
}

QVariant DomModel::headerData(int section, Qt::Orientation /*orientation*/, int role) const
{
    if(Qt::DisplayRole == role) {
        switch(section) {
        case ModelName:
            return tr("Element");
        case ModelValue:
            return tr("Attributes");
        default:
            return QVariant("");
        }
    }
    return QVariant();
}

QModelIndex DomModel::index(int row, int column, const QModelIndex &parent) const
{
    if((row < 0) || (column < 0) || (column >= ModelColumns) || (parent.isValid() && (parent.column() > 0))) {
        return QModelIndex();
    }

    if(!parent.isValid()) {
//        printf("Parent ROOT NOT VALID created index: %d %d\n", row, column);
//        fflush(stdout);
        if(row < childItems.size()) {
            return createIndex(row, column, childItems.at(row));
        }
    } else {
        DomItem* parentElement = static_cast<DomItem*>(parent.internalPointer());
        DomItem* element = parentElement->getChildAt(row);
        if(NULL != element) {
//           printf("Element %s, created index: %d %d\n", element->tag().toLatin1().data(), row, column);
//          fflush(stdout);
            return createIndex(row, column, element);
        }
    }
    return QModelIndex();
}

int DomModel::rowCount(const QModelIndex &parent) const
{
    if(parent.column() > 0) {
        return 0;
    }

    int resRowCount = 0 ;
    DomItem *parentElement;
    if(!parent.isValid()) {
        resRowCount = childItems.size();
    } else {
        parentElement = static_cast<DomItem*>(parent.internalPointer());
        if(NULL != parentElement) {
            resRowCount = parentElement->getChildItemsNumber();
        } else {
            resRowCount = childItems.size();
        }
    }
    return resRowCount ;
}

int DomModel::columnCount(const QModelIndex & /*parent*/) const
{
    return ModelColumns ;
}

QModelIndex DomModel::parent(const QModelIndex & index) const
{
    if(index.isValid()) {
        DomItem *element = static_cast<DomItem*>(index.internalPointer());
        if(NULL != element) {
            DomItem *parentElement = element->parent() ;
            int row ;
            if(NULL != parentElement) {
                DomItem *grandParentElement = parentElement->parent() ;
                if(NULL != grandParentElement) {
                    row = grandParentElement->childIndex(parentElement);
                } else {
                    row = childItems.indexOf(parentElement);
                }
                return createIndex(row, 0, parentElement);
            }
        }
    }
    return QModelIndex();
}

void DomModel::addUndoInsert(QTreeWidget * tree, DomItem * element)
{
    UndoInsertCommand *undoInsertCommand = new UndoInsertCommand(tree, this, element->indexPath());
    _undoStack.push(undoInsertCommand);
}

void DomModel::insertItemInternal(DomItem *theNewElement, DomItem *parentElement, QTreeWidget *tree)
{
    insertItemInternal(theNewElement, parentElement, tree, true, -1) ;
}

void DomModel::insertItemInternal(DomItem *theNewElement, DomItem *parentElement, QTreeWidget *tree, const bool useUndo, int position)
{
    if(NULL != parentElement) {
        parentElement->addChildAt(theNewElement, position);
        theNewElement->setChildItem(tree, parentElement->getUI(), paintInfo, true, position);
    } else {
        addTopItem(theNewElement);
        theNewElement->setChildItem(tree, NULL, paintInfo);
    }
    afterInsertHousekeeping(theNewElement, tree, useUndo);
}

void DomModel::appendItemInternal(DomItem *theNewElement, DomItem *brotherElement, QTreeWidget *tree, const bool useUndo)
{
    if(NULL == brotherElement) {
        addTopItem(theNewElement);
        theNewElement->setChildItem(tree, NULL, paintInfo);
    } else {
        DomItem *parentElement = brotherElement->parent();
        if(NULL == parentElement) {
            addTopItem(theNewElement);
            theNewElement->setChildItem(tree, NULL, paintInfo);
        } else {
            int pos = parentElement->addChildAfter(theNewElement, brotherElement);
            theNewElement->setChildItem(tree, parentElement->getUI(), paintInfo, true, pos);
        }
    }
    afterInsertHousekeeping(theNewElement, tree, useUndo);
}

void DomModel::afterInsertHousekeeping(DomItem *theNewElement, QTreeWidget *tree)
{
    afterInsertHousekeeping(theNewElement, tree, true);
}

void DomModel::afterInsertHousekeeping(DomItem *theNewElement, QTreeWidget *tree, const bool useUndo)
{
    QTreeWidgetItem *item = theNewElement->getUI();
    tree->setCurrentItem(item);
    QTreeWidgetItem *parentItem = item->parent();
    if(NULL != parentItem) {
        tree->expandItem(parentItem);
    }
    if(useUndo) {
        addUndoInsert(tree, theNewElement);
    }
    setModified(true);
}

bool DomModel::moveUp(DomItem *element)
{
    return internalMoveUp(element, true);
}

// Move up in parent containment.
bool DomModel::moveDown(DomItem *element)
{
    return internalMoveDown(element, true);
}

bool DomModel::internalMoveUp(DomItem *element, const bool registerInUndo)
{
    if(registerInUndo) {
        UndoMoveUpCommand *undoCmd = new UndoMoveUpCommand(element->getUI()->treeWidget(), this, element->indexPath()) ;
        _undoStack.push(undoCmd);
        return undoCmd->done();
    }

    DomItem *parentItem = element->parent();
    bool doneOp = false;
    if(NULL == parentItem) {
        doneOp = DomItem::moveUp(getItems(), element);
    } else {
        doneOp = parentItem->moveUp(element);
    }
    return doneOp;
}

// Move up in parent containment.
bool DomModel::internalMoveDown(DomItem *element, const bool registerInUndo)
{
    if(registerInUndo) {
        UndoMoveDownCommand *undoCmd = new UndoMoveDownCommand(element->getUI()->treeWidget(), this, element->indexPath()) ;
        _undoStack.push(undoCmd);
        return undoCmd->done();

    }
    DomItem *parentItem = NULL ;
    parentItem = element->parent();
    bool doneOp = false;
    if(NULL == parentItem) {
        doneOp = DomItem::moveDown(getItems(), element);
    } else {
        doneOp = parentItem->moveDown(element);
    }
    return doneOp;
}

bool DomModel::canUndo()
{
    return _undoStack.canUndo();
}

bool DomModel::canRedo()
{
    return _undoStack.canRedo();
}

int DomModel::undoCount()
{
    return _undoStack.count();
}

void DomModel::undo()
{
    return _undoStack.undo();
}

void DomModel::redo()
{
    return _undoStack.redo();
}

//--------------------------------------------------------------------------------

bool DomModel::checkIfUIItemsCorrespondToItems(DomItem *target)
{
    if(NULL == target) {
        return false;
    }
    QTreeWidgetItem *item = target->getUI();
    if(NULL == item) {
        return false;
    }
    DomItem *parentElement = NULL ;
    parentElement = target->parent();
    QVector<DomItem*> *elements = NULL ;
    QTreeWidgetItem *parentItem = item->parent();
    int childrenCount ;
    QTreeWidget *tree = NULL ;
    if(NULL == parentElement) {
        tree = item->treeWidget();
        if(NULL == tree) {
            return false;
        }
        elements = &childItems;
        childrenCount = tree->topLevelItemCount();

    } else {
        if(NULL == parentItem) {
            return false;
        }
        elements = parentElement->getChildItems();
        childrenCount = parentItem->childCount() ;
    }
    int count = elements->size();
    if(count != childrenCount) {
        return false;
    }
    for(int i = 0 ; i < count ; i ++) {
        DomItem *e = elements->at(i);
        QTreeWidgetItem *child = NULL;
        if(NULL != tree) {
            child = tree->topLevelItem(i);
        } else {
            child = parentItem->child(i) ;
        }
        if(e->getUI() != child) {
            return false;
        }
    }
    return true;
}

bool DomModel::addUndoDeleteItem(DomItem* element)
{
    if(NULL != element) {
        UndoDeleteCommand *undoCmd = new UndoDeleteCommand(element->getUI()->treeWidget(), this, element->indexPath());
        _undoStack.push(undoCmd);
        emit undoStateChanged();
        return true;
    }
    return false;
}

bool DomModel::deleteItem(DomItem* element, const bool isAutoDelete)
{
    if(NULL == element) {
        return false;
    }
    addUndoDeleteItem(element) ;
    element->autoDelete(isAutoDelete);
    return true;
}

bool DomModel::deleteItem(DomItem* element)
{
    return deleteItem(element, true);
}

void DomModel::emptyUndoStack()
{
    _undoStack.clear();
}

void DomModel::dumpDocument(QDomDocument &document)
{
    QString s;
    QDomDocumentType dtype = document.doctype();

    s += QString("internal subset:%1\n").arg(dtype.internalSubset());
    s += QString("name:%1\n").arg(dtype.name());
    s += QString("node type:%1\n").arg(dtype.nodeType());
    s += QString("publicId:%1\n").arg(dtype.publicId());
    s += QString("systemId:%1\n").arg(dtype.systemId());

    QDomNamedNodeMap    docEntities = dtype.entities();

    s += "entities:\n";
    int size = docEntities.size();
    for(int i = 0 ; i < size ; i ++) {
        QDomNode node = docEntities.item(i);
        QDomEntity entity = node.toEntity();
        s += QString("---publicId %1, systemId %2, notationName %3, name %4\n").arg(entity.publicId()).arg(entity.systemId()).arg(entity.notationName()).arg(node.nodeName());
    }
    s += "notations:\n";
    size = dtype.notations().size();
    for(int i = 0 ; i < size ; i ++) {
        QDomNode node = dtype.notations().item(i);
        QDomNotation notation = node.toNotation();
        s += QString("----publicId %1, systemId %2, name %3\n").arg(notation.publicId()).arg(notation.systemId()).arg(node.nodeName());
    }
    Utils::error(s);
    QString result = document.toString(4);
    Utils::error(result);
    printf("%s\n", result.toLatin1().data());
    fflush(stdout);

}

QString DomModel::docType()
{
    return _docType->docType() ;
}

void DomModel::setDocType(const QString& newDocType, const QString &systemId, const QString &publicId)
{
    bool changed = false ;
    if(newDocType != _docType->docType()) {
        changed = true ;
    }
    if(systemId != _docType->systemId()) {
        changed = true ;
    }
    if(publicId != _docType->publicId()) {
        changed = true ;
    }

    _docType->setDocType(newDocType) ;
    _docType->setPublicId(publicId);
    _docType->setSystemId(systemId);
    if(changed) {
        emit docTypeChanged(_docType->docType());
    }
}


void DomModel::processDocument(QDomDocument &document)
{
    QDomDocumentType dtype = document.doctype();
    setDocType(dtype.name(), dtype.systemId(), dtype.publicId());
}

DomItem *DomModel::getDataTypeItemWithId(const QString &lnType)
{
    foreach (DomItem *item, _dataTypeItems) {
        if(item->attributeValueOfName("id") == lnType)
            return item;
    }

    return NULL;
}
