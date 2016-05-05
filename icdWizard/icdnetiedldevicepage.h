#ifndef ICDNETIEDLDEVICEPAGE_H
#define ICDNETIEDLDEVICEPAGE_H

#include <QWizardPage>

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QTreeWidget>
#include <QtGui/QMovie>

#include <QAction>
#include <QMenu>
#include <QPoint>

#include <QTimer>
#include <QTreeWidgetItem>
#include "parsescdthread.h"


class icdNETIedLDevicePage : public QWizardPage
{
    Q_OBJECT
public:
    explicit icdNETIedLDevicePage(QWidget *parent = 0);

    QGridLayout *gridLayout;

    QGroupBox *AUNoGroupBox;
    QHBoxLayout *auNoHLayout;

    QLabel *auNoLabel;
    QComboBox *auNoComboBox;

    QGroupBox *linkGroupBox;
    QGridLayout *linkGridLayout;

    QLabel *scdFileLabel;
    QLineEdit *scdFileSelectText;
    QPushButton *scdFileSeletcButton;

    QTreeWidget *scdTree;
    QTreeWidgetItem *headerItem;
    QTreeWidgetItem *_gcbItem;
    QTreeWidgetItem *_svcbItem;
    QTreeWidgetItem *_mmsItem;
    QTreeWidgetItem *_104Item;

    int getGocbNum() {
        return _gcbItem->childCount();
    }
    int getSvcbNum() {
        return _svcbItem->childCount();
    }
    int getMMSNum() {
        return _mmsItem->childCount();
    }
    int getIec104Num() {
        return _104Item->childCount();
    }

    QList<controlBlock*> getGseItemList() {
        return gseItemList;
    }
    QList<controlBlock*> getSvItemList() {
        return svItemList;
    }
    QList<controlBlock*> getMmsItemList() {
        return mmsItemList;
    }
    QList<controlBlock*> getIec104ItemList() {
        return iec104ItemList;
    }


private:
    ParseSCDThread *parseSCD_thread;

    QLabel *loading;
    QMovie *movie;
    QLabel *loadText;
    QTimer *timer;
    int timerIndex;

    QList<controlBlock*> gseItemList;
    QList<controlBlock*> svItemList;
    QList<controlBlock*> mmsItemList;
    QList<controlBlock*> iec104ItemList;

    void init();

    virtual bool isComplete() const;

signals:

public slots:

    void changeText();
    void openSCDFile();

    void changeIcon(QTreeWidgetItem *item);
    void setCheckedView(QTreeWidgetItem *item, int column);
    void treeContextMenu(QPoint pos);
    void selectAll();
    void unSelectAll();
//    void updateSCDTree(QTreeWidgetItem *item, QString tag) {
//        scdTree->setUpdatesEnabled(true);
//        if(tag == tr("GSE")) {
//            item->setIcon(0, QIcon(":/nodeType/images/gseControl.png"));
//            _gcbItem->addChild(item);
//        }
//        else if(tag == tr("SMV")) {
//            item->setIcon(0, QIcon(":/nodeType/images/smvControl.png"));
//            _svcbItem->addChild(item);
//        }
//    }

    void endParseThread();
};

#endif // ICDNETIEDLDEVICEPAGE_H
