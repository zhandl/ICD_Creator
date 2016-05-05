#include "icdnetiedldevicepage.h"

#include <QFile>
#include <QFileDialog>


icdNETIedLDevicePage::icdNETIedLDevicePage(QWidget *parent) :
    QWizardPage(parent)
{
    setTitle(tr("IED LDevice Setting"));
    setSubTitle(tr("This page can set the LDevice of ied segment."));

    init();
}

void icdNETIedLDevicePage::init()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QString::fromUtf8("icdNETIedLDevicePage"));
    this->resize(800, 600);
    QFont font;
    font.setFamily(QString::fromUtf8("Calibri"));
    font.setPointSize(12);
    setFont(font);

    gridLayout = new QGridLayout(this);
    gridLayout->setObjectName(tr("gridLayout"));
    setLayout(gridLayout);

    AUNoGroupBox = new QGroupBox(this);
    AUNoGroupBox->setObjectName(tr("AUNoGroupBox"));
    auNoHLayout = new QHBoxLayout(AUNoGroupBox);
    auNoHLayout->setObjectName(tr("auNoHLayout"));

    linkGroupBox = new QGroupBox(this);
    linkGroupBox->setObjectName(tr("linkGroupBox"));
    linkGridLayout = new QGridLayout(linkGroupBox);
    linkGridLayout->setObjectName(tr("linkGridLayout"));

    gridLayout->addWidget(AUNoGroupBox, 0, 0, 1, 7);
    gridLayout->addWidget(linkGroupBox, 1, 0, 4, 7);
    gridLayout->setRowStretch(1, 5);
    gridLayout->setRowStretch(2, 1);
    gridLayout->setRowStretch(3, 1);
    gridLayout->setRowStretch(4, 5);

    auNoLabel = new QLabel(AUNoGroupBox);
    auNoLabel->setObjectName(tr("auNoLabel"));
    auNoLabel->setText(tr("请选择采集单元数目： "));
    auNoComboBox = new QComboBox(AUNoGroupBox);
    auNoComboBox->setObjectName(tr("auNoComboBox"));
    auNoComboBox->addItems(QStringList()<<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8");
    auNoComboBox->setCurrentIndex(0);
    auNoComboBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    auNoHLayout->addWidget(auNoLabel);
    auNoHLayout->addWidget(auNoComboBox);

    scdFileLabel = new QLabel(linkGroupBox);
    scdFileLabel->setObjectName(tr("scdFileLabel"));
    scdFileLabel->setText(tr("导入SCD文件："));
    scdFileSelectText = new QLineEdit(linkGroupBox);
    scdFileSelectText->setObjectName(tr("scdFileSelectText"));
    scdFileSeletcButton = new QPushButton(linkGroupBox);
    scdFileSeletcButton->setObjectName(tr("scdFileSeletcButton"));
    scdFileSeletcButton->setText(tr("..."));

    scdTree = new QTreeWidget(linkGroupBox);
    scdTree->setObjectName(tr("scdTree"));

    headerItem = new QTreeWidgetItem(QStringList()<<tr("IEDName")<<tr("CBName")<<tr("MAC/IP-C")<<tr("APPID/IP-S")<<tr("Desc"));
    scdTree->setHeaderItem(headerItem);
    scdTree->setColumnWidth(0, 200);
    scdTree->setColumnWidth(1, 100);
    _gcbItem = new QTreeWidgetItem(QStringList()<<tr("GOOS控制块"));
    _gcbItem->setIcon(0, QIcon(":/scdTree/images/Folder.png"));
    _svcbItem = new QTreeWidgetItem(QStringList()<<tr("SV控制块"));
    _svcbItem->setIcon(0, QIcon(":/scdTree/images/Folder.png"));
    _mmsItem = new QTreeWidgetItem(QStringList()<<tr("MMS链路"));
    _mmsItem->setIcon(0, QIcon(":/scdTree/images/Folder.png"));
    _104Item = new QTreeWidgetItem(QStringList()<<tr("104链路"));
    _104Item->setIcon(0, QIcon(":/scdTree/images/Folder.png"));

    scdTree->addTopLevelItem(_gcbItem);
    scdTree->addTopLevelItem(_svcbItem);
    scdTree->addTopLevelItem(_mmsItem);
    scdTree->addTopLevelItem(_104Item);

    _gcbItem->setExpanded(false);
    _svcbItem->setExpanded(false);
    _mmsItem->setExpanded(false);
    _104Item->setExpanded(false);


    linkGridLayout->addWidget(scdFileLabel, 0, 0, 1, 1);
    linkGridLayout->addWidget(scdFileSelectText, 0, 1, 1, 5);
    linkGridLayout->addWidget(scdFileSeletcButton, 0, 6, 1, 1);
    linkGridLayout->addWidget(scdTree, 1, 0, 4 ,7);

    linkGridLayout->setRowStretch(1, 5);
    linkGridLayout->setRowStretch(2, 1);
    linkGridLayout->setRowStretch(3, 1);
    linkGridLayout->setRowStretch(4, 5);

    scdTree->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(scdTree, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(treeContextMenu(QPoint)));
    connect(scdFileSeletcButton, SIGNAL(clicked()), this, SLOT(openSCDFile()));
    connect(scdTree, SIGNAL(itemCollapsed(QTreeWidgetItem*)), this, SLOT(changeIcon(QTreeWidgetItem*)));
    connect(scdTree, SIGNAL(itemExpanded(QTreeWidgetItem*)), this, SLOT(changeIcon(QTreeWidgetItem*)));
//    connect(scdTree, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(setCheckedView(QTreeWidgetItem*,int)));
//    connect(scdTree, SIGNAL(itemExpanded(QTreeWidgetItem*), this, SLOT(changeIcon(QTreeWidgetItem*)));
}


void icdNETIedLDevicePage::openSCDFile()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this, tr("打开SCD文件"),
                                            "",
                                            tr("SCD文件(*.scd);;所有文件(*.*)"));

    if(fileName.isEmpty())
        return ;

    scdFileSelectText->setText(fileName);


    timerIndex = 0;
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(changeText()));
    timer->start(500);

    loading = new QLabel(linkGroupBox);
    loading->setObjectName(tr("loading"));
    movie = new QMovie(":/images/loading.gif");
    movie->setObjectName(tr("movie"));
    loading->setMovie(movie);
    loadText = new QLabel(linkGroupBox);
    loadText->setObjectName(tr("loadText"));
    loadText->setText(tr("解析SCD，请稍候"));

    linkGridLayout->addWidget(loading, 2, 3, 1, 1, Qt::AlignHCenter);
    linkGridLayout->addWidget(loadText, 3, 3, 1, 2, Qt::AlignLeft);

    movie->start();


    _gcbItem->takeChildren();
    _gcbItem->setExpanded(false);
    _svcbItem->takeChildren();
    _svcbItem->setExpanded(false);
    _mmsItem->takeChildren();
    _mmsItem->setExpanded(false);
    _104Item->takeChildren();
    _104Item->setExpanded(false);


    parseSCD_thread = new ParseSCDThread();
    connect(parseSCD_thread, SIGNAL(parseOvered()), this, SLOT(endParseThread()));
    connect(parseSCD_thread, SIGNAL(started()), this, SIGNAL(completeChanged()));
    parseSCD_thread->setFileName(fileName);

    parseSCD_thread->start();


}

//bool icdNETIedLDevicePage::exploreSCDFile(const QString fileName)
//{
//}

//void icdNETIedLDevicePage::showSCDCommunication(QDomNode &node)
//{
//    QString NAME;
//    QString MAC;
//    QString APPID;
//    QDomNodeList childList = node.childNodes();
//    int nodeCount = childList.count();

//    for(int i=0; i < nodeCount; i++) {
//        QDomNode childNode = childList.at(i);
//        if(childNode.isElement()) {
//            QDomElement element = childNode.toElement();
//            QString tag = element.tagName();

//            if(tag == tr("GSE") || tag == tr("SMV")) {
//                NAME = element.attribute(tr("cbName"));
//                QDomElement *addrElement = childNodeOfName(element, tr("Address"));
//                for(int j = 0; j < addrElement->childNodes().count(); j++) {
//                    if(addrElement->childNodes().at(j).toElement().attribute(tr("type")) == tr("MAC-Address"))
//                        MAC = addrElement->childNodes().at(j).toElement().childNodes().at(0).toText().data();
//                    if(addrElement->childNodes().at(j).toElement().attribute(tr("type")) == tr("APPID"))
//                        APPID = addrElement->childNodes().at(j).toElement().childNodes().at(0).toText().data();
//                }
//                QTreeWidgetItem *newItem = new QTreeWidgetItem(QStringList()<<NAME<<MAC<<APPID);
//                if(tag == tr("GSE"))
//                    _gcbItem->addChild(newItem);
//                else if(tag == tr("SMV"))
//                    _svcbItem->addChild(newItem);
//            } else
//                showSCDCommunication(element);
//        }
//    }
//}

void icdNETIedLDevicePage::changeIcon(QTreeWidgetItem *item)
{
    if((item != _gcbItem) && (item != _svcbItem) &&
            (item != _mmsItem) && (item != _104Item))
        return;

    if(item->isExpanded())
        item->setIcon(0, QIcon(":/scdTree/images/OpenFolder.png"));
    else
        item->setIcon(0, QIcon(":/scdTree/images/Folder.png"));
}

//QDomElement *icdNETIedLDevicePage::childNodeOfName(const QDomElement element, const QString name)
//{
//    QDomElement *childElement = new QDomElement();
//    QDomNodeList childList = element.childNodes();
//    for(int i = 0; i < childList.count(); i++)
//        if(childList.item(i).isElement()) {
//            *childElement = childList.at(i).toElement();
//            if(childElement->tagName() == name)
//                return childElement;
//        }
//    return NULL;
//}

void icdNETIedLDevicePage::changeText()
{
    timerIndex++;
    QString signal;
    if(timerIndex == 1)
    {
       signal = QString(".");
    }
    else if(timerIndex == 2)
    {
      signal = QString("..");
    }
    else if(timerIndex == 3)
    {
        signal = QString("...");
    }
    else if(timerIndex == 4)
    {
        signal = QString("....");
    }
    else if(timerIndex == 5)
    {
        signal = QString(".....");
    }
    else if(timerIndex == 6)
    {
        signal = QString("......");
    }
    else
    {
      signal = QString("");
      timerIndex = 0;
    }

    QString tip_info = tr("解析SCD，请稍候") + signal;
    loadText->setText(tip_info);
}

void icdNETIedLDevicePage::endParseThread()
{
    timer->stop();
    timer->deleteLater();
    movie->stop();
    movie->deleteLater();
    loading->deleteLater();
    loadText->deleteLater();

    parseSCD_thread->quit();
    gseItemList = parseSCD_thread->getGSEItemList();
    svItemList = parseSCD_thread->getSMVItemList();
    mmsItemList = parseSCD_thread->getMMSItemList();
    iec104ItemList = parseSCD_thread->get104ItemList();

    scdTree->setUpdatesEnabled(false);
    QListIterator<controlBlock*> gseItem(gseItemList);

    while(gseItem.hasNext()) {
        controlBlock *cbItem = gseItem.next();
        QTreeWidgetItem *item = new QTreeWidgetItem(QStringList()<<cbItem->iedName<<cbItem->cbName<<cbItem->MAC<<cbItem->APPID<<cbItem->iedDesc);
        item->setIcon(0, QIcon(":/nodeType/images/gseControl.png"));
        item->setCheckState(0, Qt::Checked);
        _gcbItem->addChild(item);
    }

    QListIterator<controlBlock*> smvItem(svItemList);//parseSCD_thread->getSMVItemList());
    while(smvItem.hasNext()) {
        controlBlock *cbItem = smvItem.next();
        QTreeWidgetItem *item = new QTreeWidgetItem(QStringList()<<cbItem->iedName<<cbItem->cbName<<cbItem->MAC<<cbItem->APPID<<cbItem->iedDesc);
        item->setIcon(0, QIcon(":/nodeType/images/smvControl.png"));
        item->setCheckState(0, Qt::Checked);
        _svcbItem->addChild(item);
    }

//    scdTree->setUpdatesEnabled(false);
//    _gcbItem->addChildren(parseSCD_thread->getGSEItemList());
//    _svcbItem->addChildren(parseSCD_thread->getSMVItemList());
//    _mmsItem->addChildren(parseSCD_thread->getMMSItemList());
//    _104Item->addChildren(parseSCD_thread->get104ItemList());

    scdTree->setUpdatesEnabled(true);
    parseSCD_thread->deleteLater();
    emit completeChanged();
}

void icdNETIedLDevicePage::setCheckedView(QTreeWidgetItem *item, int column)
{
    if((item == _gcbItem) || (item == _svcbItem) ||
            (item == _mmsItem) || (item == _104Item))
        return;

    if(item->checkState(column) == Qt::Unchecked)
        item->setDisabled(true);
    else
        item->setDisabled(false);
}

void icdNETIedLDevicePage::treeContextMenu(QPoint pos)
{
    QAction *selectAll = new QAction(this);
    selectAll->setObjectName(tr("selectAll"));
    selectAll->setText(tr("全选"));
    connect(selectAll, SIGNAL(triggered()), this, SLOT(selectAll()));

    QAction *unSelectAll = new QAction(this);
    unSelectAll->setObjectName(tr("unSelectAll"));
    unSelectAll->setText(tr("全清"));
    connect(unSelectAll, SIGNAL(triggered()), this, SLOT(unSelectAll()));

    QMenu *menu = new QMenu(this);
    menu->setObjectName(tr("menu"));
    menu->addAction(selectAll);
    menu->addAction(unSelectAll);

    menu->exec(scdTree->mapToGlobal(pos));
}

void icdNETIedLDevicePage::selectAll()
{
    int i = 0;
    for(i = 0 ; i < _gcbItem->childCount(); i++)
        _gcbItem->child(i)->setCheckState(0, Qt::Checked);

    for(i = 0 ; i < _svcbItem->childCount(); i++)
        _svcbItem->child(i)->setCheckState(0, Qt::Checked);
}

void icdNETIedLDevicePage::unSelectAll()
{
    int i = 0;
    for(i = 0 ; i < _gcbItem->childCount(); i++)
        _gcbItem->child(i)->setCheckState(0, Qt::Unchecked);

    for(i = 0 ; i < _svcbItem->childCount(); i++)
        _svcbItem->child(i)->setCheckState(0, Qt::Unchecked);
}

bool icdNETIedLDevicePage::isComplete() const
{
//    if(scdFileSelectText->text().isEmpty()) {
//        emit completeChanged();
//        return false;

    if(_gcbItem->childCount() == 0 &&
            _svcbItem->childCount() == 0 &&
            _mmsItem->childCount() == 0 &&
            _104Item->childCount() == 0)
        return false;
    else
        return true;
}
