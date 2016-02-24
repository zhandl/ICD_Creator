#ifndef EDITELEMENT_H
#define EDITELEMENT_H

#include <QtGui>

#include <QDialog>
#include "domitem.h"

class EditElement : public QDialog
{
    enum {
        T_COLUMN_CDATA = 1,
        T_COLUMN_TEXT = 2,
        T_COLUMN_MOD = 0
    };
    enum {
        A_COLUMN_NAME = 1,
        A_COLUMN_TEXT = 2,
        A_COLUMN_MOD = 0
    };

    Q_OBJECT

    DomItem *target;
    bool isMixedContent;
    QColor modColor;
    bool isStarted ;

public:
    EditElement(QWidget * parent = NULL);
    ~EditElement();

    void setTarget(DomItem *pTarget);

    void sendDeleteCommand();
    void sendSelect(const int row);
    void sendModifyCommand(const QString &newData);
    void sendAddCommand(const QString &newData);
    void sendMoveUpCommand();
    void sendMoveDownCommand();

    bool setAttributeOfName(QTableWidget *table, int &row, const QString AttrName);
private:

    QListWidgetItem *loadTextNode(QListWidget *list, TextChunk *text);
    int appendTextNodeInTable(QTableWidget *table, const bool isEditable, const int desiredRow, const bool isCDATA, const QString &text, void * userData);
    int appendAttrNodeInTable(QTableWidget *table, const int desiredRow, const QString &name, const QString &value);
    void clearTextNodes();
    void addTextNode(TextChunk *text);

    void setAttrText(QListWidgetItem *item, const QString &name, const QString &value);
    void setUpdatedAttr(const int row);
    void setUpdatedElement(const int row);

public slots:
    void accept();
private slots:
    void on_newAttribute_clicked();
    void on_delAttribute_clicked();
    void on_editTag_textChanged(const QString &);
    void on_attrTable_itemSelectionChanged();
    void on_elementTable_itemSelectionChanged();
    void on_textAdd_clicked();
    void on_textDel_clicked();
    void on_attrUp_clicked();
    void on_attrDown_clicked();
    void on_textUp_clicked();
    void on_textDown_clicked();
    void on_textEdit_clicked();
    void on_elementTable_cellClicked(int row, int column);
    void on_attrTable_itemChanged(QTableWidgetItem * item);

    void on_noUseAttrTable_itemClicked(QTableWidgetItem *item);
    void on_noUseAttrTable_itemDoubleClicked(QTableWidgetItem *item);

private:
//    Ui::Dialog ui;
    void init();
    void error(const QString& message);
    void errorNoAttrData();
    void errorNoAttrSel();
    bool validateAttr(const QString &name);
    bool checkTagSyntax(const QString &theTag);
    void enableOK();

    void moveDown(QTableWidget *table);
    void moveUp(QTableWidget *table);
    static void swapRow2(QTableWidget *table, const int rowStart, const int rowEnd);
    int getNextRow(const int currentRow);
    DomItem * getUserData(QTableWidgetItem *item);
    bool isElementText(QTableWidgetItem *item);

    void retranslate();

    void setAviableAttrbutes(QTableWidget *table);

    /*********************************************
     *************** UI  *************************
     *************** ****************************/
    QAction *actionEditItem;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLabel *path;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QLineEdit *editTag;
    QSpacerItem *horizontalSpacer;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QTableWidget *elementTable;
    QVBoxLayout *verticalLayout_4;
    QPushButton *textAdd;
    QPushButton *textDel;
    QPushButton *textEdit;
    QPushButton *textUp;
    QPushButton *textDown;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_1;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QTableWidget *attrTable;
    QHBoxLayout *layBox1;
    QVBoxLayout *verticalLayout;
    QPushButton *newAttribute;
    QPushButton *delAttribute;
    QPushButton *attrUp;
    QPushButton *attrDown;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_6;
    QDialogButtonBox *buttonBox;
    QSpacerItem *verticalSpacer_3;

    QLabel *label_4;
    QTableWidget *noUseAttrTable;
};

#endif // EDITELEMENT_H
