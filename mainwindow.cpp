#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    CreateActions();
    CreateMenus();

}

MainWindow::~MainWindow()
{
}

void MainWindow::CreateActions()
{
    qFileNew = new QAction(tr("&New"), this);
    qFileNew->setShortcut(QKeySequence::New);
    qFileNew->setStatusTip(tr("Create a new file"));
    connect(qFileNew, SIGNAL(triggered()), this, SLOT(fileNewAct()));

    qFileOpen = new QAction(tr("&Open..."), this);
    qFileOpen->setShortcut(QKeySequence::Open);
    qFileOpen->setToolTip(tr("Open an existing file"));
    connect(qFileOpen, SIGNAL(triggered()), this, SLOT(fileOpenAct()));

    qAddHistory = new QAction(tr("插入History字段"),this);
    connect(qAddHistory, SIGNAL(triggered()), this, SLOT(addHistoryAct()));
}

void MainWindow::CreateMenus()
{
    qFileMenu = menuBar()->addMenu(tr("&File"));
    qFileMenu->addAction(qFileNew);
    qFileMenu->addAction(qFileOpen);

//    QWidget *ICDWidget = new QWidget(this);
//    QGridLayout *qLayout = new QGridLayout(ICDWidget);
    setWindowState(Qt::WindowMaximized);
//    setCentralWidget(ICDWidget);

    QSplitter *qSplitterMain = new QSplitter(Qt::Horizontal,this);
    setCentralWidget(qSplitterMain);
//    QVBoxLayout *qTreeLayout = new QVBoxLayout();   //generate the Tree Layout -- Left in the widow
//    QVBoxLayout *qTextLayout =  new QVBoxLayout();  //generate the View Layout -- Right in the window

//    qSplitterMain->setStretchFactor(0,0);


//    qLayout->addLayout(qTreeLayout,0,0,1,1);
//    qLayout->addLayout(qTextLayout,0,1,1,1);
//    qLayout->setColumnStretch(0,1);                 //set the column width of the layout
//    qLayout->setColumnStretch(1,4);                 //set the column width of the layout

/*    qTree = new QTreeWidget();
    qTree->setHeaderHidden(true);
    qTree->setContextMenuPolicy(Qt::CustomContextMenu);
//    qTreeLayout->addWidget(qTree);
    qTree->setMinimumWidth(240);
    connect(qTree, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showPopMenu(QPoint)));


//    qTextDocument = new QTextDocument();
//    qText = new QSyntaxHighlighter(qTextDocument);
    qText = new QTextBrowser();

    qSplitterMain->addWidget(qTree);
    qSplitterMain->addWidget(qText);

    qSplitterMain->setStretchFactor(0,1);
    qSplitterMain->setStretchFactor(1,4);*/

    model = new DomModel(QDomDocument(), this);
    view = new QTreeView(qSplitterMain);
    view->setModel(model);
    view->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(view, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showPopMenu(QPoint)));


/*
    qSCLRoot = new QTreeWidgetItem(qTree, QStringList()<<tr("SCL"));    //Tree Root : SCL
    qSCLRoot->setExpanded(true);

    qHeaderNode = new QTreeWidgetItem(qSCLRoot, QStringList()<<tr("Header"));  //Header Node : child of SCL
    qSubstationNode = new QTreeWidgetItem(qSCLRoot, QStringList()<<tr("Substation")); //Substation Node : child of SCL
    qCommnicationNode = new QTreeWidgetItem(qSCLRoot, QStringList()<<tr("Communication")); //Communication Node : child of SCL
    qIEDNode = new QTreeWidgetItem(qSCLRoot, QStringList()<<tr("IED"));    //IED Node : child of SCL
    qDataTypeTemplates = new QTreeWidgetItem(qSCLRoot, QStringList()<<tr("DataTypeTemplates"));
*/
}

void MainWindow::fileNewAct()
{
    newFileName = QFileDialog::getSaveFileName(this, tr("新建文件"),NULL,tr("ICD files(*.icd);;SCD files(*.scd);;All files(*.*)"));
    qDebug()<<newFileName;


    if(newFileName.isEmpty())
    {
        QMessageBox::information(this,tr("Save File Warning"),tr("File Name is Empty"));
        return;
    }

    newFile = new QFile(newFileName);

    if(!newFile->open(QIODevice::ReadWrite|QIODevice::Truncate))
    {
        QMessageBox::information(this,tr("Save File Warning"),tr("Save File Error"));
        return;
    }

    QDomDocument *doc = new QDomDocument();
    CreateNewICD(doc);



//    if (doc->setContent(newFile)) {
        DomModel *newModel = new DomModel(*doc, this);
        view->setModel(newModel);
        view->setRootIndex(newModel->index(2,0));
        delete model;
        model = newModel;
//    }


    QTextStream out(newFile);
    doc->save(out,4);
    delete doc;

    newFile->close();

}

void MainWindow::fileOpenAct()
{
//    QFileDialog *fileOpenDlg = new QFileDialog(this, tr("打开文件"));
//    fileOpenDlg->setFilters(QStringList()<<tr("ICD files (*.icd, *.cid)")<<tr("SCD files (*.scd)")<<tr("All files (*.*)"));
//    fileOpenDlg->exec();
      openFileName = QFileDialog::getOpenFileName(this, tr("打开文件"),NULL,tr("ICD files(*.icd);;SCD files(*.scd);;All files(*.*)"));
}

void MainWindow::addHistoryAct()
{
//    qHeaderNode->addChild(new QTreeWidgetItem(QStringList()<<tr("History")));
//    qHeaderNode->setExpanded(1);

//    QFile *newFile = new QFile(newFileName);

//    if(!newFile->open(QIODevice::ReadWrite))
//    {
//        QMessageBox::information(this,tr("Save File Warning"),tr("Save File Error"));
//        return;
//    }
//    newFile->close();

    QDomDocument *doc = new QDomDocument();
    doc->setContent(newFile);
    QDomElement qNewElement = doc->createElement(tr("Histroy"));
    root = doc->documentElement();
    root.firstChild().appendChild(qNewElement);

    DomModel *newModel = new DomModel(*doc, this);
    view->setModel(newModel);
    view->setRootIndex(newModel->index(2,0));
    delete model;
    model = newModel;

    delete newFile;
    newFile = new QFile(newFileName);
    newFile->open(QIODevice::WriteOnly|QIODevice::Truncate);
    QTextStream out(newFile);
    doc->save(out,4);
    newFile->close();

}

void MainWindow::CreateNewICD(QDomDocument *doc)
{
    QDateTime DateTime;

    /****************************************************/
    /****  Add standard xml instruction ***********************/
    /****************************************************/
     QDomProcessingInstruction instruction;
     instruction = doc->createProcessingInstruction("xml", "version=\"1.0\" encoding = \"UTF_8\"");
     doc->appendChild(instruction);


     /****************************************************/
     /****  Add Comment***********************************/
     /****************************************************/
    QDomComment comment;
    comment = doc->createComment("edited with XMLSpy v2008 rel.2  (http://www.altova.com)");
    doc->appendChild(comment);


    /****************************************************/
    /****  Add SCL  element(ROOT)  **************************/
    /****************************************************/
     root = doc->createElement(tr("SCL"));
     QDomAttr xmlns = doc->createAttribute(tr("xmlns"));
     xmlns.setValue(tr("http://www.iec.ch/61850/2003/SCL"));
     QDomAttr xsi = doc->createAttribute(tr("xmlns:xsi"));
     xsi.setValue(tr("http://www.w3.org/2001/XMLSchema-instance"));
     QDomAttr schemaLocation = doc->createAttribute(tr("xsi:schemaLocation"));
     schemaLocation.setValue(tr("http://www.iec.ch/61850/2003/SCL\\ SCL.xsd"));

     root.setAttributeNode(xmlns);
     root.setAttributeNode(xsi);
     root.setAttributeNode(schemaLocation);
     doc->appendChild(root);


     /****************************************************/
     /****  Add Header section  ******************************/
     /****************************************************/
     QDomElement Header = doc->createElement(tr("Header"));
     QDomAttr Header_Ref = doc->createAttribute(tr("Ref"));
     QDomAttr Header_id = doc->createAttribute(tr("id"));
     QDomAttr Header_version = doc->createAttribute(tr("version"));
     QDomAttr Header_revision = doc->createAttribute(tr("revision"));
     QDomAttr Header_toolID = doc->createAttribute(tr("toolID"));
     QDomAttr Header_nameStructure = doc->createAttribute(tr("nameStructure"));

     Header_version.setValue(tr("3.6.3"));
     Header_nameStructure.setValue(tr("IEDName"));

     Header.setAttributeNode(Header_Ref);
     Header.setAttributeNode(Header_id);
     Header.setAttributeNode(Header_version);
     Header.setAttributeNode(Header_revision);
     Header.setAttributeNode(Header_toolID);
     Header.setAttributeNode(Header_nameStructure);

     root.appendChild(Header);

     /****  Header Histroy section ************************
     QDomElement History = doc->createElement(tr("History"));
     Header.appendChild(History);

     /**** History Hitem section  ************************
     QDomElement Hitem = doc->createElement(tr("Hitem"));
     QDomAttr Hitem_version = doc->createAttribute(tr("version"));
     QDomAttr Hitem_revision = doc->createAttribute(tr("revision"));
     QDomAttr Hitem_when = doc->createAttribute(tr("when"));
     QDomAttr Hitem_who = doc->createAttribute(tr("who"));
     QDomAttr Hitem_what = doc->createAttribute(tr("what"));
     QDomAttr Hitem_why = doc->createAttribute(tr("why"));

     Hitem_version.setValue(tr("1.00"));
     Hitem_revision.setValue(tr("1.01"));
     Hitem_when.setValue(DateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
     Hitem_who.setValue(tr("mike"));
     Hitem_what.setValue(tr("Create this file"));
     Hitem_why.setValue(tr("Demo"));

     Hitem.setAttributeNode(Hitem_version);
     Hitem.setAttributeNode(Hitem_revision);
     Hitem.setAttributeNode(Hitem_when);
     Hitem.setAttributeNode(Hitem_who);
     Hitem.setAttributeNode(Hitem_what);
     Hitem.setAttributeNode(Hitem_why);

     History.appendChild(Hitem);



     /****************************************************/
     /****  Add Communication Section  ***********************/
     /****************************************************/
     QDomElement Communication = doc->createElement(tr("Communication"));
     root.appendChild(Communication);

     /***  Add SubNetwork section ***************************/
     QDomElement SubNetwork = doc->createElement(tr("SubNetwork"));
     QDomAttr subNetwork_name = doc->createAttribute(tr("name"));
     QDomAttr subNetwork_type = doc->createAttribute(tr("type"));
     QDomAttr subNetwork_desc = doc->createAttribute(tr("desc"));

     subNetwork_name.setValue(tr("MMS"));
     subNetwork_type.setValue(tr("8-MMS"));
     subNetwork_desc.setValue(tr("子网1"));

     SubNetwork.setAttributeNode(subNetwork_name);
     SubNetwork.setAttributeNode(subNetwork_type);
     SubNetwork.setAttributeNode(subNetwork_desc);;

     Communication.appendChild(SubNetwork);

     QDomElement SN_Text = doc->createElement(tr("Text"));
     QDomText bus = doc->createTextNode(tr("Station bus"));
     SN_Text.appendChild(bus);

     QDomElement SN_BitRate = doc->createElement(tr("BitRate"));
     QDomAttr BR_unit = doc->createAttribute(tr("unit"));
     BR_unit.setValue(tr("b/s"));
     QDomText BitRate = doc->createTextNode(tr("10"));
     SN_BitRate.setAttributeNode(BR_unit);
     SN_BitRate.appendChild(BitRate);

     QDomElement connectAP = doc->createElement(tr("ConnectAP"));
     QDomAttr AP_iedName  = doc->createAttribute(tr("iedName"));
     QDomAttr AP_apName = doc->createAttribute(tr("apName"));
     QDomAttr AP_desc = doc->createAttribute(tr("desc"));

     AP_iedName.setValue(tr("WY9D"));
     AP_apName.setValue(tr("S1"));
     AP_desc.setValue(tr("AP1"));

     connectAP.setAttributeNode(AP_iedName);
     connectAP.setAttributeNode(AP_apName);
     connectAP.setAttributeNode(AP_desc);

     QDomElement AP_Address = doc->createElement(tr("Address"));
     connectAP.appendChild(AP_Address);

     QDomElement AP_Addr_p1 = doc->createElement(tr("P"));
     QDomAttr P1_type = doc->createAttribute(tr("type"));
     P1_type.setValue(tr("IP"));
     QDomText P1_text = doc->createTextNode(tr("0.0.0.0"));
     AP_Addr_p1.setAttributeNode(P1_type);
     AP_Addr_p1.appendChild(P1_text);

     QDomElement AP_Addr_p2 = doc->createElement(tr("P"));
     QDomAttr P2_type = doc->createAttribute(tr("type"));
     P2_type.setValue(tr("IP-SUBNET"));
     QDomText P2_text = doc->createTextNode(tr("255.255.255.0"));
     AP_Addr_p2.setAttributeNode(P2_type);
     AP_Addr_p2.appendChild(P2_text);

     QDomElement AP_Addr_p3 = doc->createElement(tr("P"));
     QDomAttr P3_type = doc->createAttribute(tr("type"));
     P3_type.setValue(tr("IP-GATEWAY"));
     QDomText P3_text = doc->createTextNode(tr("0.0.0.0"));
     AP_Addr_p3.setAttributeNode(P3_type);
     AP_Addr_p3.appendChild(P3_text);


     QDomElement AP_Addr_p4 = doc->createElement(tr("P"));
     QDomAttr P4_type = doc->createAttribute(tr("type"));
     P4_type.setValue(tr("OSI-TSEL"));
     QDomText P4_text = doc->createTextNode(tr("0001"));
     AP_Addr_p4.setAttributeNode(P4_type);
     AP_Addr_p4.appendChild(P4_text);


     QDomElement AP_Addr_p5 = doc->createElement(tr("P"));
     QDomAttr P5_type = doc->createAttribute(tr("type"));
     P5_type.setValue(tr("OSI-PSEL"));
     QDomText P5_text = doc->createTextNode(tr("00000001"));
     AP_Addr_p5.setAttributeNode(P5_type);
     AP_Addr_p5.appendChild(P5_text);


     QDomElement AP_Addr_p6 = doc->createElement(tr("P"));
     QDomAttr P6_type = doc->createAttribute(tr("type"));
     P6_type.setValue(tr("OSI-SSEL"));
     QDomText P6_text = doc->createTextNode(tr("0001"));
     AP_Addr_p6.setAttributeNode(P6_type);
     AP_Addr_p6.appendChild(P6_text);

     AP_Address.appendChild(AP_Addr_p1);
     AP_Address.appendChild(AP_Addr_p2);
     AP_Address.appendChild(AP_Addr_p3);
     AP_Address.appendChild(AP_Addr_p4);
     AP_Address.appendChild(AP_Addr_p5);
     AP_Address.appendChild(AP_Addr_p6);

     connectAP.appendChild(AP_Address);

     SubNetwork.appendChild(SN_Text);
     SubNetwork.appendChild(SN_BitRate);
     SubNetwork.appendChild(connectAP);
}

void MainWindow::showPopMenu(QPoint cp)
{
    QMenu *qPopMenu = new QMenu(this);
    QModelIndex *currentItem = new QModelIndex();
    *currentItem = view->indexAt(cp);
    qDebug()<<currentItem->data();
    if(currentItem->data() == tr("Header"))
    {
        qPopMenu->addAction(qAddHistory);
    }

    if(newFileName == NULL)
    {
        qPopMenu->setDisabled(1);
    }
    qPopMenu->exec(QCursor::pos());
}
