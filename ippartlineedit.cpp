#include <QIntValidator>
#include <QKeyEvent>

#include "ippartlineedit.h"

CIpPartLineEdit::CIpPartLineEdit(QWidget *parent)
    : QLineEdit(parent)
{
    m_preEdit = NULL;
    m_nextEdit = NULL;

    this->setMaxLength(3);
    //this->setFrame(false);
    this->setAlignment(Qt::AlignCenter);
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    QValidator *validator = new QIntValidator(0, 255, this);
    this->setValidator(validator);

    connect(this, SIGNAL(textEdited(const QString&)),
            this, SLOT(slot_text_Edited(const QString&)));
}

CIpPartLineEdit::~CIpPartLineEdit()
{

}

void CIpPartLineEdit::m_vSetPreEdit(QLineEdit *preEdit)
{
    m_preEdit = preEdit;
}

void CIpPartLineEdit::m_vSetNextEdit(QLineEdit *nextEdit)
{
    m_nextEdit = nextEdit;
}

void CIpPartLineEdit::focusInEvent(QFocusEvent *event)
{
    this->selectAll();
    QLineEdit::focusInEvent(event);
}

void CIpPartLineEdit::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Period)
    {
        if(m_nextEdit && 
           (this->text().size()!=0) &&
           (!this->hasSelectedText()))
        {
            m_nextEdit->setFocus();
            m_nextEdit->selectAll();
        }
    }
    if(event->key() == Qt::Key_Backspace)
    {
        if(m_preEdit &&
           (this->text().size() == 0))
        {
            m_preEdit->setFocus();
            m_preEdit->setCursorPosition( m_preEdit->text().size() );
        }
    }
    QLineEdit::keyPressEvent(event);
}

void CIpPartLineEdit::slot_text_Edited(const QString & text)
{
    QIntValidator v(0, 255, this);
    QString ipAddr = text;
    int iPos = 0;

    QValidator::State state = v.validate(ipAddr, iPos);
    if(state != QValidator::Acceptable)
    {
        return ;
    }
    if(ipAddr.size() <= 1)
    {
        return ;
    }

    if(ipAddr.size() == 2)
    {
        int iIpNum = ipAddr.toInt();
        if(iIpNum > 25)
        {
            if(m_nextEdit)
            {
                m_nextEdit->setFocus();
                m_nextEdit->selectAll();
            }
        }
    }
    else
    {
        if(m_nextEdit)
        {
            m_nextEdit->setFocus();
            m_nextEdit->selectAll();
        }
    }
}
