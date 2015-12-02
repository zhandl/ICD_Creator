#ifndef COMPARE_H
#define COMPARE_H

#include <QDialog>
#include "global.h"
#include "dommodel.h"

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Compare : public QDialog
{
    Q_OBJECT

    enum EDiffStates { DF_MISSING, DF_EQUAL, DF_DIFFERENT, DF_ADDED };
public:
    Compare(DomModel *original, QWidget *parent = 0);
    ~Compare();

    static void doCompare(QWidget *parent, DomModel *original);

    bool loadRule(const QString &filePath);
    bool loadRule(QByteArray dataIn);
    bool loadData();
    bool loadData(const QString &filePath);
    bool loadData(QByteArray dataIn);
    bool areDifferent();

protected:
    void changeEvent(QEvent *e);

private:

    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QTextBrowser *textBrowser;
    QHBoxLayout *horizontalLayout;
    QCheckBox *showOldValuesCB;
    QCheckBox *ignoreNonElements;
    QCheckBox *ignoreTextCB;
    QPushButton *copyToClipboard;
    QGroupBox *Legend;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget_3;
    QLabel *label;
    QWidget *widget_4;
    QLabel *label_3;
    QWidget *widget_5;
    QLabel *label_2;
    QWidget *widget_6;
    QLabel *label_4;
    QDialogButtonBox *buttonBox;

    void init();
    void retranslateUi();

    QDomDocument document;
    DomModel *original;
    DomModel *toCompare;
    QString resultText;
    bool ignoreText;
    bool compareOnlyElements;
    bool showOldValues;
    bool _areDifferent;

    void endElement(const int indent, DomItem *item, const EDiffStates state);
    void dumpElement(const int indent, DomItem *item, const EDiffStates state);
    void recurse(QVector<DomItem*> &origItems, QVector<DomItem*> &compareItems, const int indent);
    void recurseAll(DomItem *item, const EDiffStates state, const int indent);
    void doCompare();
    void compareAttributes(DomItem *orig, DomItem *compare);
    void insertAttrInHash(QHash<QString, Attribute*> &hash, DomItem *target);
    void dumpAttr(Attribute *attr, const EDiffStates state);
    void closeTag(DomItem *item, const EDiffStates state);
    void filterItems(QVector<DomItem*> &origItems, QVector<DomItem*> &destItems, const bool isFilter);
    void dumpAttributes(DomItem *item, const EDiffStates state);
    void dumpText(const QString text, const EDiffStates state, const int indent);
    void setDifference();
    bool compareTwoText(const QString &str1, const QString &str2);

    bool loadFile(const QString &filePath);

    static QString convertTextInHTML(const QString strIn);

private slots:
    void accept();
    void on_copyToClipboard_clicked();

};

#endif // COMPARE_H
