#ifndef ADDVAL_H
#define ADDVAL_H


#include <QDialog>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QCheckBox>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>

class DomItem;

class AddVal : public QDialog
{
    Q_OBJECT
public:
    AddVal(QWidget *parent = 0);
    ~AddVal();

    void setTarget(DomItem *item);

private:
    QLabel *valLabel;
    QLineEdit *valText;
    QDialogButtonBox *buttonBox;

    QGridLayout *layout;

    DomItem *target;

    void init();

    void accept();
signals:

public slots:

};


#endif // ADDVAL_H
