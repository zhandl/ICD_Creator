#ifndef ICDDATATYPETEMPLATENEW_H
#define ICDDATATYPETEMPLATENEW_H

#include <QWizardPage>
#include <QtGui/QComboBox>
#include <QtGui/QTreeWidget>
#include <QtGui/QPushButton>
#include <QtGui/QTextBrowser>
#include <QtGui/QSplitter>
#include <QtGui/QGridLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QWidget>
#include <QAction>
#include <QBrush>

#include <QDomDocument>

#include "datatypemodel.h"

class newTemplateLNodeModel;


class icdDataTypeTemplateNew : public QWizardPage
{
    Q_OBJECT
public:
    explicit icdDataTypeTemplateNew(QWidget *parent = 0);



    QComboBox *standardComboBox;
    QComboBox *LNodeFilter;
    QTreeWidget *LNodeTree;
    QTextBrowser *LNodeDescText;
    QTreeWidget *newTemplateLNodeTree;
    QPushButton *addLNode;
    QPushButton *delLNode;
    QPushButton *addAll;
    QPushButton *delAll;
    QSplitter *hSplitter;
    QSplitter *vSplitter;

    QWidget *buttonGroupBox;
    QVBoxLayout *buttonVLayout;

    QGridLayout *newDataTypeGridLayout;

    QAction *checkItems;
    QAction *uncheckItems;

    QAction *expandedAll;
    QAction *unexpandedAll;


    DataTypeModel *model;
    DataTypeModel *selectedModel;

    QDomDocument *doc;

private:

    void init();
    void createDoc(QDomDocument *document);

    void setStandardDLT860();
    void setStandardUserRCD();
    void setStandardUserNETA();

    void registerData();

private:

    QVector<DataTypeItem*> _LNodeItemPool;
    QVector<DataTypeItem*> _DoTypeItemPool;
    QVector<DataTypeItem*> _DaTypeItemPool;
    QSet<QString> _DoTypeNamePool;
    QSet<QString> _DaTypeNamePool;
    QSet<QString> _EnumTypeNamePool;

signals:

public slots:
    void selecteDataTypeStandard(int);
    void treeContextMenu(const QPoint& pos);
    void checkSelecteItems();
    void uncheckSelecteItems();
    void expandedAllItems();
    void unexpandedAllItems();

    void showDesc(QTreeWidgetItem *item, int column);
//    void setSelectedItemsBackground();
    void setLNodeSelected(QTreeWidgetItem* item, int column);
    void calcCheckState(QTreeWidgetItem *, int);

    void on_addLNode_clicked();
    void on_delLNode_clicked();
    void on_addAll_clicked();
    void on_delAll_clicked();

    void on_newTemplateLNodeTree_itemDoubleClicked(QTreeWidgetItem* item, int column);

};

#endif // ICDDATATYPETEMPLATENEW_H
