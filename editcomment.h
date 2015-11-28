#ifndef EDITCOMMENT_H
#define EDITCOMMENT_H

#include <QtGui>

#include <QDialog>
#include "domitem.h"

class EditComment : public QDialog
{
    Q_OBJECT

    DomItem *target;

public:
    EditComment(QWidget *parent = 0);
    ~EditComment();

    void setTarget(DomItem *pTarget);

private:
    void error(const QString& message);
    void init();

    void retranslateUi()
    {
        setWindowTitle(QApplication::translate("EditComment", "Edit Comment", 0, QApplication::UnicodeUTF8));
    }

    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *commentText;
    QDialogButtonBox *buttonBox;

private slots:
    void accept();
    void on_commentText_textChange();


};

#endif // EDITCOMMENT_H
