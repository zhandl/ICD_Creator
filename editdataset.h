#ifndef EDITDATASET_H
#define EDITDATASET_H

#include <QDialog>
#include <QtGui>

class DomItem;
class DomModel;

class EditDataSet : public QDialog
{
    Q_OBJECT

    DomItem *target;
public:
    EditDataSet(QWidget *parent = 0);
    ~EditDataSet();

    void setTarget(DomItem *pItem);

signals:

public slots:
    void accept();

private:

    QLabel *dataSetNameLabel;
    QLineEdit *dataSetNameText;

    QGridLayout *dataSetGridLayout;
    QComboBox *LNodeComboBox;
    QComboBox *fcComboBox;
    QSplitter *dataSetSplitter;
    QTreeWidget *LNodeTree;
    QListWidget *fcdaList;

    QDialogButtonBox *buttonBox;

    DomModel *model;

    QHash<DomItem*, QString> dataSetItems;
    QSet<QString> FC;
    void init();

    QVector<QTreeWidgetItem*> _fcItems;
    QVector<QTreeWidgetItem*> _doItems;

    void getDataSetItems(DomItem *item);

    typedef struct _fcda{
        bool hasDaName;
        QString daName;
        bool hasDoName;
        QString doName;
        QString fc;
        bool hasLdInst;
        QString ldInst;
        bool hasLnInst;
        QString lnInst;
        bool hasLnClass;
        QString lnClass;
    }fcda;

//    QVector<fcda*> fcdaItems;
    QSet<fcda*> fcdaItems;

private slots:
    void showFCDA(QTreeWidgetItem*, int);

};

#endif // EDITDATASET_H
