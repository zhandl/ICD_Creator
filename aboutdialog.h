#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include "authorinfo.h"

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QTabWidget>
#include <QtGui/QTreeWidget>
#include <QtGui/QWidget>

class AboutDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AboutDialog(QWidget *parent,
                         const QString &appName, const QString &setVersion,
                         const QString &copyRight, const QString &setLicense, const QString &otherLicense,
                         const QList<AuthorInfo*> &authors);
    ~AboutDialog();
    QString contactInfo(const QString &info);

private:

    QDialogButtonBox *buttonBox;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLabel *copyR;
    QLabel *label_5;
    QLabel *label_3;
    QLabel *icons;
    QLabel *license;
    QWidget *tab_2;
    QLabel *label_4;
    QTreeWidget *authorsWidget;
    QLabel *label;
    QLabel *applicationName;
    QFrame *line;
    QLabel *version;
    QLabel *envir;
    QLabel *label_2;

    void init();
    void retranslateUi();

};

#endif // ABOUTDIALOG_H
