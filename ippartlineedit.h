#ifndef IPPARTLINEEDIT_H
#define IPPARTLINEEDIT_H

#include <QLineEdit>

class QWidget;
class QFocusEvent;
class QKeyEvent;

class CIpPartLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    CIpPartLineEdit(QWidget *parent = 0);
    ~CIpPartLineEdit();

    void m_vSetPreEdit(QLineEdit *preEdit);
    void m_vSetNextEdit(QLineEdit *nextEdit);

protected:
    void focusInEvent(QFocusEvent *event);
    void keyPressEvent(QKeyEvent *event);

private slots:
    void slot_text_Edited(const QString & text);

private:
    QLineEdit *m_preEdit;
    QLineEdit *m_nextEdit;
};

#endif // IPPARTLINEEDIT_H