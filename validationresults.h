#ifndef VALIDATIONRESULTS_H
#define VALIDATIONRESULTS_H

#include <QDialog>
#include "validatormessagehandler.h"

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>

class ValidationResults : public QDialog
{
    Q_OBJECT
public:
    ValidationResults(const QString text, ValidatorMessageHandler &validator, QWidget *parent = 0);
    ~ValidationResults();

protected:
    void changeEvent(QEvent *e);

private:

    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QTextBrowser *textBrowser;
    QLabel *error;
    QVBoxLayout *verticalLayout_2;
    QDialogButtonBox *buttonBox;
    QSpacerItem *verticalSpacer;

    void init();
    void retranslateUi();
    ValidatorMessageHandler &_validator;

};

void showValidationResults(const QString text, ValidatorMessageHandler &validator, QWidget *parent);

#endif // VALIDATIONRESULTS_H
