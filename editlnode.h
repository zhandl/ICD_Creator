#ifndef EDITLNODE_H
#define EDITLNODE_H

#include <QDialog>

#include <QtGui>
#include "domitem.h"
#include <QHash>

class EditLNode : public QDialog
{
    Q_OBJECT
    DomItem *target;
    bool isMixedContent;
    QColor modColor;
    bool isStarted;
public:
    explicit EditLNode(QWidget *parent = 0);
    ~EditLNode();

    void setTarget(DomItem *pItem);

public slots:
    void accept();

private:
    void init();

    void error(const QString& message);
    void errorNoAttrData();
    void errorNoAttrSel();
    bool validateAttr(const QString &name);
    bool checkTagSyntax(const QString &theTag);

    QHash<QString, QString> LNodeClass;

    QGridLayout *editLNodeGridLayout;
    QLabel *path;
    QGroupBox *LNodeGroupBox;
    QGridLayout *LNodeGridLayout;

    QLabel *LNodeInstLabel;
    QLineEdit *LNodeInstText;
    QLabel *LNodeLnClassLabel;
    QLineEdit *LNodeLnClassText;
    QLabel *LNodeLnTypeLabel;
//    QLineEdit *LNodeLnTypeText;
    QComboBox *LNodeLnTypeComboBox;
    QCheckBox *LNodeDescCheckBox;
    QLabel *LNodeDescLabel;
    QLineEdit *LNodeDescText;

    QDialogButtonBox *buttonBox;

private slots:
    void setLNodeLnClass(QString lnClass);
};

#endif // EDITLNODE_H
