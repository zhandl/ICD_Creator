#ifndef ICDDATATYPETEMPLATEPAGE_H
#define ICDDATATYPETEMPLATEPAGE_H

#include <QWizardPage>
#include <QtGui/QApplication>
#include <QtGui/QLabel>
#include <QtGui/QGroupBox>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QTextBrowser>
#include <QtGui/QGridLayout>
#include <QtGui/QVBoxLayout>

class icdDataTypeTemplatePage : public QWizardPage
{
    Q_OBJECT
public:
    explicit icdDataTypeTemplatePage(QWidget *parent = 0);

private:    
    QLineEdit *fileSelectText;
    QPushButton *fileSelectButton;
    QRadioButton *fileSelectRadio;
    QLabel *fileSelectLabel;
    QRadioButton *newTemplateRadio;
    QTextBrowser *newTemplateText;
    QGridLayout *dataTypeTemplateGridLayout;

    void init();

signals:

public slots:

};

#endif // ICDDATATYPETEMPLATEPAGE_H
