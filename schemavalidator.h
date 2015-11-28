#ifndef SCHEMAVALIDATOR_H
#define SCHEMAVALIDATOR_H

#include "dommodel.h"
#include "xsdeditor/xschema.h"
#include "xsdeditor/validator/xelementcontent.h"

class SchemaValidator
{
private:
    QList<SchemaSearchContext*> getPathFromItem(DomItem *item);
    XElementContent *getAvailableContent(XElementContent *content, XSDSchema *root, DomItem *currentItem, const bool startAtRoot);
public:
    SchemaValidator();
    ~SchemaValidator();
    QStringList checkInsertionPoint(XSDSchema *root, DomItem *currentItem);
    bool getInsertionPointAllowedItems(XElementContent *content, XSDSchema *root, DomItem *currentItem, const bool startAsRoot);
    QStringList getInsertionPointList(XSDSchema *root, DomItem *currentItem, const bool startAsRoot);
};

#endif // SCHEMAVALIDATOR_H
