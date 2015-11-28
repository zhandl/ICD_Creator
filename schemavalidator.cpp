#define LOG_CONSOLE
#include "schemavalidator.h"
#include "xsdeditor/validator/xvalidationcontext.h"
#include "utils.h"

SchemaValidator::SchemaValidator()
{
}

SchemaValidator::~SchemaValidator()
{
}

XElementContent *SchemaValidator::getAvailableContent(XElementContent *content, XSDSchema *root, DomItem *currentItem, const bool startAsRoot)
{
    if(NULL == root) {
        TRACE("No schema yet");
        return NULL;
    }
    TRACE("0: starting search\n");
    XSchemaObject *object = root;
    if(!startAsRoot) {
        if(NULL == currentItem) {
            TRACE("No element");
            return NULL;
        }

        QList<SchemaSearchContext*> path = getPathFromItem(currentItem);
        foreach(SchemaSearchContext *component, path) {
            object = object->findComponentInValidationPath(component);
            if(NULL == object) {
                break;
            }
            if(NULL != object) {
                QString resultString = QString("Found element path: %1").arg(component->targetTag());
                TRACEQ(resultString);
            }
        }
        foreach (SchemaSearchContext* searchItem, path) {
            delete searchItem;
        }
        path.clear();
    } else {
        TRACE("0: starting from root\n");
    }

    if(NULL == object) {
        TRACE("1: path not found\n");
    } else {
        TRACE2("2: found %s\n", object->name().toAscii().data());
        XValidationContext context(content);
        if(object->findSchemaChildComponents(&context, content)) {
            return content;
        }
    }
    return NULL;
}

QStringList SchemaValidator::getInsertionPointList(XSDSchema *root, DomItem *currentItem, const bool startAsRoot)
{
    QStringList result;
    XElementContent content;
    if(NULL != getAvailableContent(&content, root, currentItem, startAsRoot)) {
        foreach (XSingleElementContent *targetContent, content.allowedItems()) {
            result.append(targetContent->item()->name());
        }
    }
    return result;
}

bool SchemaValidator::getInsertionPointAllowedItems(XElementContent *content, XSDSchema *root, DomItem *currentItem, const bool startAsRoot)
{
    if(NULL != getAvailableContent(content, root, currentItem, startAsRoot)) {
        return true;
    }
    return false;
}

QList<SchemaSearchContext*> SchemaValidator::getPathFromItem(DomItem *item)
{
    QList<SchemaSearchContext*> path;
    DomItem *theItem = item;
    TRACEQ(QString("Entering getPathFromElementn for %1\n").arg(item->tag()));
    int level = 0;
    while(NULL != theItem) {
        level++;
        TRACE("Element test\n");
        DomItem *theParent = theItem->parent();
        if(theItem->isElement()) {
            Utils::TODO_NEXT_RELEASE("Do Error checking");

            int index = 0;
            if(NULL != theParent) {
                bool found = false;
                foreach(DomItem *aChild, theParent->getItems()) {
                    if(aChild == item) {
                        found = true;
                        break;
                    } else {
                        if(aChild->getType() == DomItem::ET_ELEMENT)
                            index ++;
                    }
                }
                if(!found) {
                    TRACEQ(QString("ERROR*** not found at level: %1\n").arg(level));
                }
            }

            TRACEQ(QString("Found the element at index:%1, level:%2\n").arg(index).arg(level));

            SchemaSearchContext *newContext = new SchemaSearchContext();
            newContext->setTarget(theParent, theItem, index);
            path.insert(0, newContext);
        }
        theItem = theParent;
    }
    TRACEQ(QString("Exiting getPathFromElement for %1\n").arg(item->tag()));
    return path;
}

XSchemaObject *XSDSchema::findComponentInValidationPath(const QString &component)
{
    foreach(XSchemaObject *child, _children) {
        if(child->getType() == SchemaTypeElement) {
            XSchemaElement *element = (XSchemaElement*) child;
            if(element->name() == component) {
                return element;
            }
        }
    }
    return NULL;
}

XSchemaObject *XSDSchema::findComponentInValidationPath(SchemaSearchContext *context)
{
    foreach(XSchemaObject *child, _children) {
        if(child->getType() == SchemaTypeElement) {
            XSchemaElement *element = (XSchemaElement*) child;
            if(element->name() == context->targetTag()) {
                return element;
            }
        }
    }
    return NULL;
}

bool XSDSchema::findSchemaChildComponents(XValidationContext *context, XElementContent *content)
{
    bool atLeastOne = false;
    foreach(XSchemaObject *child, _children) {
        if(child->getType() == SchemaTypeElement) {
            XSchemaElement *element = (XSchemaElement*) child;
            content->addAllowed(context, element);
            atLeastOne = true;
        }
    }
    return atLeastOne;
}

XSchemaObject *XSchemaChoice::findComponentInValidationPath(const QString &component)
{
    return NULL;
}

bool XSchemaChoice::findSchemaChildComponents(XValidationContext *context, XElementContent *content)
{
    return false;
}

XSchemaObject *XSchemaObject::findComponentInValidationPath(SchemaSearchContext *searchContext)
{
    XElementContent content;
    XValidationContext context(&content);
    TRACEQ(QString("Begin findComponentInValidationPath for %1").arg(description()));
    if(!searchContext->initScan()) {
        TRACEQ(QString("..init failed"));
        return NULL;
    }

    if(findSchemaChildComponents(&context, &content)) {
        foreach(XSingleElementContent *child, content.allowedItems()) {
            TRACEQ(QString("..Scanning in %1").arg(child->item()->name()));
            if(SchemaSearchContext::FOUND == child->scanForPosition(searchContext, child->isAll())) {
                TRACEQ(QString("..Found\n"));
                XSingleElementContent *itemFound = searchContext->foundItem();
                if(NULL != itemFound) {
                    TRACEQ(QString("..Found element %1").arg(itemFound->item()->name()));
                    return itemFound->item();
                }
            }
        }
    }
    TRACEQ(QString("INVALID findComponentInValidationPath\n"));
    return NULL;
}

bool XSchemaObject::findSchemaChildComponents(XValidationContext *context, XElementContent *content)
{
    return false;
}

bool XSchemaElement::examineType(XValidationContext *context, XSingleElementContent *parent)
{
    foreach (XSchemaObject *child, _children) {
        if(child->getType() == SchemaTypeAll) {
            XSchemaAll *elementAll = (XSchemaAll*) child;
            if(!elementAll->collect(context, parent)) {
                return false;
            }
        } else if(child->getType() == SchemaTypeSequence) {
            XSchemaSequence *sequence = (XSchemaSequence *) child;
            if(!sequence->collect(context, parent)) {
                return false;
            }
        } else if(child->getType() == SchemaTypeChoice) {
            XSchemaChoice *choice = (XSchemaChoice *)child;
            if(!choice->collect(context, parent)) {
                return false;
            }
        } else if(child->getType() == SchemaTypeGroup) {
            XSchemaGroup *group = (XSchemaGroup*) child;
            if(!group->collect(context, parent)) {
                return false;
            }
        }
    }
    return true;
}

bool XSchemaComplexContent::examineType(XValidationContext *context, XSingleElementContent *parent)
{
    foreach (XSchemaObject *child, _children) {
        if(child->getType() == SchemaTypeAll) {
            XSchemaAll *elementAll = (XSchemaAll *)child;
            if(!elementAll->collect(context, parent)) {
                return false;
            }
        } else if(child->getType() == SchemaTypeSequence) {
            XSchemaSequence *sequence = (XSchemaSequence*) child;
            if(!sequence->collect(context, parent)) {
                return false;
            }
        } else if(child->getType() == SchemaTypeChoice) {
            XSchemaChoice *choice = (XSchemaChoice*) child;
            if(!choice->collect(context, parent)) {
                return false;
            }
        } else if(child->getType() == SchemaTypeGroup) {
            XSchemaGroup *group = (XSchemaGroup*) child;
            if(!group->collect(context, parent)) {
                return false;
            }
        }
    }
    return true;
}

bool XSchemaElement::elabTypeForCollect(XValidationContext *context, XElementContent *content)
{
    if(!xsdType().isEmpty()) {
        XSchemaElement *baseType = _root->schema()->rootType(xsdType());

        if(NULL == baseType) {
            return false;
        }
        if(!baseType->examineType(context, NULL)) {
            return false;
        }
    }
    return true;
}

bool XSchemaElement::findSchemaChildComponents(XValidationContext *context, XElementContent *content)
{
    if(isTypeOrElement()) {
        if(!examineType(context, NULL)) {
            return false;
        }
    } else {
        switch(_elementCategory) {
        default:
            if(!examineType(context, NULL)) {
                return false;
            }
            break;
        case EES_EMPTY:
            if(!elabTypeForCollect(context, content)) {
                return false;
            }
            break;
        case EES_SIMPLETYPE_ONLY:
        case EES_SIMPLETYPE_WITHATTRIBUTES:
            break;
        case EES_REFERENCE: {
            XSchemaElement *referencedElement = _root->schema()->rootElement(_ref);
            if(NULL != referencedElement->findSchemaChildComponents(context, content)) {
                return true;
            }
            return false;
        }

        case EES_COMPLEX_DERIVED: {
            if(isExtension()) {
                if(!elabTypeForCollect(context, content)) {
                    return false;
                }
                XSchemaComplexContentExtension *extension = (XSchemaComplexContentExtension*)_children.at(0);
                if(!extension->examineType(context, NULL)) {
                    return false;
                }
            } else {
                XSchemaComplexContentRestriction *restriction = (XSchemaComplexContentRestriction*)_children.at(0);
                if(!restriction->examineType(context, NULL)) {
                    return false;
                }
            }
            break;
        }
        }
    }
}
