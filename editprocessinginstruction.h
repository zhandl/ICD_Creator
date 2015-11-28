#ifndef EDITPROCESSINGINSTRUCTION_H
#define EDITPROCESSINGINSTRUCTION_H

#include <QtGui>

#include <QDialog>
#include "domitem.h"

class EditProcessingInstruction : public QDialog
{
    Q_OBJECT

    DomItem *target;

public:
    EditProcessingInstruction(QWidget *parent = 0);
    ~EditProcessingInstruction();

    void setTarget(DomItem *pTarget);

private:
    void checkOKEnabled();

private slots:
    void accept();
    void on_editTarget_textChanged();
    void on_editData_textChanged();

private:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *editTarget;
    QLabel *label_2;
    QLineEdit *editData;
    QDialogButtonBox *buttonBox;

    void init();
    void retranslateUi()
    {
        setWindowTitle(QApplication::translate("EditProcessing", "Edit Processing Instruction", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("EditProcessing", "&Target", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("EditProcessing", "&Data", 0, QApplication::UnicodeUTF8));
    }

    void error(const QString& message);

};

bool editProcessingInstruction(QWidget *parent, DomItem *pTarget);

#endif // EDITPROCESSINGINSTRUCTION_H
