#ifndef MODIFYLNODEID_H
#define MODIFYLNODEID_H

#include <QDialog>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QHBoxLayout>
#include <QtGui/QPushButton>

#include <datatypeitem.h>

class ModifyLNodeId : public QDialog
{
    Q_OBJECT
public:
    ModifyLNodeId(QWidget *parent = 0);

    DataTypeItem *target;

    void setTarget(DataTypeItem* item);

public slots:
    void accept();
private:

    QHBoxLayout *HLayout;
    QLabel *LNodeIdLabel;
    QLineEdit *LNodeIdText;
    QPushButton *acceptButton;

signals:


};

#endif // MODIFYLNODEID_H
