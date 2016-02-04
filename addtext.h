#ifndef ADDTEXT_H
#define ADDTEXT_H

#include <QDialog>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QCheckBox>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>

class DomItem;

class AddText : public QDialog
{
    Q_OBJECT
public:
    AddText(QWidget *parent = 0);
    ~AddText();

    void setTarget(DomItem *item);

private:
    QLabel *textLabel;
    QLineEdit *textText;
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

#endif // ADDTEXT_H
