#ifndef WELCOMEPAGE_H
#define WELCOMEPAGE_H

#include <QWizardPage>

class QLabel;

class WelcomePage : public QWizardPage
{
    Q_OBJECT
public:
    WelcomePage(QString &text, QWidget *parent = 0);
    ~WelcomePage();

private:

    QLabel *label;
signals:

public slots:

};

#endif // RCDWELCOMEPAGE_H
