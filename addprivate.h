#ifndef ADDPRIVATE_H
#define ADDPRIVATE_H

#include <QDialog>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QCheckBox>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>

class DomItem;

class AddPrivate : public QDialog
{
    Q_OBJECT
public:
    AddPrivate(QWidget *parent = 0);
    ~AddPrivate();

    void setTarget(DomItem *item);

private:
    QLabel *privateLabel;
    QLineEdit *privateText;
    QLabel *typeLabel;
    QLineEdit *typeText;
    QCheckBox *sourceCheckBox;
    QLabel *sourceLabel;
    QLineEdit *sourceText;
    QDialogButtonBox *buttonBox;

    QGridLayout *layout;

    DomItem *target;

    void init();

    void accept();
signals:

public slots:

};

#endif // ADDPRIVATE_H
