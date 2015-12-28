#ifndef EDITATTRIBUTE_H
#define EDITATTRIBUTE_H

#include <QDialog>

#include <QtGui>
#include "domitem.h"

class EditAttribute : public QDialog
{
    Q_OBJECT
public:
    EditAttribute(QWidget *parent = 0);
    ~EditAttribute();

    QColor modColor;

    void setTarget(DomItem *item);

private:

    DomItem *target;

    QGridLayout *layout;
    QGroupBox *treeGroupBox;
    QPushButton *applyButton;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QDialogButtonBox *buttonBox;
    QTreeWidget *attrTree;

    QString titleText;

    static bool attributeIsChanged;


signals:

public slots:
    void accept();
//    void on_okButton_clicked();
//    void on_applyButton_clicked();
//    void on_cancelButton_clicked();

    void showMenu(QPoint pos);
    void attributeChanged(QTreeWidgetItem *item, int column);
    void deleteAttribute();
};

#endif // EDITATTRIBUTE_H
