#ifndef ALLOWEDITEMSINSERT_H
#define ALLOWEDITEMSINSERT_H

#include <QDialog>
#include <QTreeWidgetItem>
#include <QStack>
#include <QSet>

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>

#include "xsdeditor/validator/xelementcontent.h"

class AllowedItemsInsert : public QDialog
{
    Q_OBJECT

    XElementContent *_content;
    QList<XSchemaObject*> *_selection;

    void collectSelected(QTreeWidgetItem *parentItem);
    void addItem(XSingleElementContent *target, QTreeWidgetItem *parentItem);
    void unselectRecursive(QTreeWidgetItem *item);
    bool isSameItem(QTreeWidgetItem *item, XSingleElementContent *reference);
    void saveState();
    void enableControls();
    void restoreState();
public:
    explicit AllowedItemsInsert(XElementContent *content, QList<XSchemaObject*>*result, QWidget *parent = 0);
    ~AllowedItemsInsert();

private:

    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTreeWidget *allowedItems;
    QHBoxLayout *horizontalLayout;
    QToolButton *undo;
    QToolButton *redo;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void init();
    void retranslateUi();
    void accept();

public slots:
    void on_allowedItems_itemClicked(QTreeWidgetItem * item, int column);
    void on_undo_clicked();
    void on_redo_clicked();
};

bool ChooseItemsBySchema(QWidget *parent, XElementContent *content, QList<XSchemaObject*> *result);

#endif // ALLOWEDITEMSINSERT_H
