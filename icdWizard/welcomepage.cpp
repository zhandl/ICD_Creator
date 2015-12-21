#include "welcomepage.h"
#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>

WelcomePage::WelcomePage(QString &text, QWidget *parent) :
    QWizardPage(parent)
{
    setTitle(tr("Welcome Create ICD"));

    label = new QLabel();
    label->setText(text);//tr("This wizard will generate a ICD file"));
    label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(label);
}

WelcomePage::~WelcomePage()
{

}
