#ifndef IPADDREDIT_H
#define IPADDREDIT_H

#include <QWidget>

class QLineEdit;
class QLabel;
class CIpPartLineEdit;

class CIpAddrEdit : public QWidget
{
    Q_OBJECT

public:
    CIpAddrEdit(QWidget *parent = 0);
    ~CIpAddrEdit();

    void m_vSetText(const QString &text);
    QString m_strGetText();
    void m_vSetStyleSheet(const QString &styleSheet);

signals:
    void sigTextChanged(const QString &text);
    void sigTextEdited(const QString &text);

private slots:
    void slot_text_Changed(const QString &text);
    void slot_text_Edited(const QString &text);

private:
    CIpPartLineEdit * m_pIpPart1;
    CIpPartLineEdit * m_pIpPart2;
    CIpPartLineEdit * m_pIpPart3;
    CIpPartLineEdit * m_pIpPart4;

    QLabel * m_pDot1;
    QLabel * m_pDot2;
    QLabel * m_pDot3;
};

#endif // IPADDREDIT_H