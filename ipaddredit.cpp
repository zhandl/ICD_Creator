#include <QRegExpValidator>
#include <QLabel>

#include "ippartlineedit.h"
#include "ipaddredit.h"

CIpAddrEdit::CIpAddrEdit(QWidget *parent) :
    QWidget(parent)
{
    m_pIpPart1 = new CIpPartLineEdit(this);
    m_pIpPart2 = new CIpPartLineEdit(this);
    m_pIpPart3 = new CIpPartLineEdit(this);
    m_pIpPart4 = new CIpPartLineEdit(this);

    m_pDot1 = new QLabel(this);
    m_pDot2 = new QLabel(this);
    m_pDot3 = new QLabel(this);

    m_pIpPart1->setGeometry(QRect(0, 0, 42, 20));
    m_pIpPart2->setGeometry(QRect(70, 0, 42, 20));
    m_pIpPart3->setGeometry(QRect(140, 0, 42, 20));
    m_pIpPart4->setGeometry(QRect(210, 0, 42, 20));

    m_pDot1->setText(".");
    m_pDot1->setGeometry(QRect(48, 5, 16, 16));
    m_pDot1->setAlignment(Qt::AlignCenter);

    m_pDot2->setText(".");
    m_pDot2->setGeometry(QRect(118, 5, 16, 16));
    m_pDot2->setAlignment(Qt::AlignCenter);

    m_pDot3->setText(".");
    m_pDot3->setGeometry(QRect(188, 5, 16, 16));
    m_pDot3->setAlignment(Qt::AlignCenter);

    QWidget::setTabOrder(m_pIpPart1, m_pIpPart2);
    QWidget::setTabOrder(m_pIpPart2, m_pIpPart3);
    QWidget::setTabOrder(m_pIpPart3, m_pIpPart4);

    m_pIpPart1->m_vSetNextEdit(m_pIpPart2);
    m_pIpPart2->m_vSetNextEdit(m_pIpPart3);
    m_pIpPart3->m_vSetNextEdit(m_pIpPart4);

    m_pIpPart2->m_vSetPreEdit(m_pIpPart1);
    m_pIpPart3->m_vSetPreEdit(m_pIpPart2);
    m_pIpPart4->m_vSetPreEdit(m_pIpPart3);

    connect(m_pIpPart1, SIGNAL(textChanged(const QString&)), this, SLOT(slot_text_Changed(const QString&)));
    connect(m_pIpPart2, SIGNAL(textChanged(const QString&)), this, SLOT(slot_text_Changed(const QString&)));
    connect(m_pIpPart3, SIGNAL(textChanged(const QString&)), this, SLOT(slot_text_Changed(const QString&)));
    connect(m_pIpPart4, SIGNAL(textChanged(const QString&)), this, SLOT(slot_text_Changed(const QString&)));

    connect(m_pIpPart1, SIGNAL(textEdited(const QString&)), this, SLOT(slot_text_Edited(const QString&)));
    connect(m_pIpPart2, SIGNAL(textEdited(const QString&)), this, SLOT(slot_text_Edited(const QString&)));
    connect(m_pIpPart3, SIGNAL(textEdited(const QString&)), this, SLOT(slot_text_Edited(const QString&)));
    connect(m_pIpPart4, SIGNAL(textEdited(const QString&)), this, SLOT(slot_text_Edited(const QString&)));
}

CIpAddrEdit::~CIpAddrEdit()
{

}

void CIpAddrEdit::slot_text_Changed(const QString &/*text*/)
{
    QString strIpPart1 = m_pIpPart1->text();
    QString strIpPart2 = m_pIpPart1->text();
    QString strIpPart3 = m_pIpPart1->text();
    QString strIpPart4 = m_pIpPart1->text();

    QString strIpAddr = QString("%1.%2.%3.%4")
            .arg(strIpPart1)
            .arg(strIpPart2)
            .arg(strIpPart3)
            .arg(strIpPart4);

    emit sigTextChanged(strIpAddr);
}

void CIpAddrEdit::slot_text_Edited(const QString &/*text*/)
{
    QString strIpPart1 = m_pIpPart1->text();
    QString strIpPart2 = m_pIpPart1->text();
    QString strIpPart3 = m_pIpPart1->text();
    QString strIpPart4 = m_pIpPart1->text();

    QString strIpAddr = QString("%1.%2.%3.%4")
            .arg(strIpPart1)
            .arg(strIpPart2)
            .arg(strIpPart3)
            .arg(strIpPart4);

    emit sigTextEdited(strIpAddr);
}

void CIpAddrEdit::m_vSetText(const QString &text)
{
    QString strIpAddr = text;

    QRegExp regexp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
    QRegExpValidator regexp_validator(regexp, this);

    int iPos = 0;

    QValidator::State state = regexp_validator.validate(strIpAddr, iPos);
    if(state != QValidator::Acceptable)
    {
        return ;
    }

    QStringList ipAddrList = text.split(".");
    //int iCount = ipAddrList.size();

    QString strIpPart1 = ipAddrList.at(0);
    QString strIpPart2 = ipAddrList.at(1);
    QString strIpPart3 = ipAddrList.at(2);
    QString strIpPart4 = ipAddrList.at(3);

    m_pIpPart1->setText(strIpPart1);
    m_pIpPart2->setText(strIpPart2);
    m_pIpPart3->setText(strIpPart3);
    m_pIpPart4->setText(strIpPart4);
}

QString CIpAddrEdit::m_strGetText()
{
    QString strIpPart1 = m_pIpPart1->text();
    QString strIpPart2 = m_pIpPart2->text();
    QString strIpPart3 = m_pIpPart3->text();
    QString strIpPart4 = m_pIpPart4->text();

    return QString("%1.%2.%3.%4")
            .arg(strIpPart1)
            .arg(strIpPart2)
            .arg(strIpPart3)
            .arg(strIpPart4);
}

void CIpAddrEdit::m_vSetStyleSheet(const QString &styleSheet)
{
    m_pIpPart1->setStyleSheet(styleSheet);
    m_pIpPart2->setStyleSheet(styleSheet);
    m_pIpPart3->setStyleSheet(styleSheet);
    m_pIpPart4->setStyleSheet(styleSheet);
}
