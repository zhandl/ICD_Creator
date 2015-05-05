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

    qFileSave = new QAction(tr("&Save"), this);
    qFileSave->setShortcut(QKeySequence::Save);
    qFileSave->setToolTip(tr("Save this file"));
    connect(qFileSave, SIGNAL(triggered()), this, SLOT(fileSaveAct()));

    qDeleteItem = new QItemAction(tr("删除"),this);
    connect(qDeleteItem, SIGNAL(clicked(QPoint)), this, SLOT(deleteItem(QPoint)));

    qAddHeader = new QItemAction(tr("插入Header字段"),this);
    connect(qAddHeader, SIGNAL(clicked(QPoint)), this, SLOT(addHeader(QPoint)));

    qAddCommunication = new QItemAction(tr("插入Communication字段"), this);
    connect(qAddCommunication, SIGNAL(clicked(QPoint)), this, SLOT(addCommunication(QPoint)));

    qAddSubstation = new QItemAction(tr("插入Substation字段"), this);
    connect(qAddSubstation, SIGNAL(clicked(QPoint)), this, SLOT(addSubstation(QPoint)));

    qAddIED = new QItemAction(tr("插入IED字段"), this);
    connect(qAddIED, SIGNAL(clicked(QPoint)), this, SLOT(addIED(QPoint)));

    qAddDataTypeTemplates = new QItemAction(tr("插入DataTypeTemplates字段"), this);
    connect(qAddDataTypeTemplates, SIGNAL(clicked(QPoint)), this, SLOT(addDataTypeTemplates(QPoint)));

    qAddText = new QItemAction(tr("插入Text字段"),this);
    connect(qAddText, SIGNAL(clicked(QPoint)), this, SLOT(addTextAct(QPoint)));

    qAddTextContent = new QItemAction(tr("插入Text内容"),this);
    connect(qAddTextContent, SIGNAL(clicked(QPoint)), this, SLOT(addTextContentAct(QPoint)));

    qAddHistory = new QItemAction(this);
    qAddHistory->setText(tr("插入History字段"));
    connect(qAddHistory, SIGNAL(clicked(QPoint)), this, SLOT(addHistoryAct(QPoint)));

    qAddHitem = new QItemAction(tr("插入Hitem项"),this);
    connect(qAddHitem, SIGNAL(clicked(QPoint)), this, SLOT(addHitemAct(QPoint)));

    qAddServices = new QItemAction(tr("插入Services字段"), this);
    connect(qAddServices, SIGNAL(clicked(QPoint)), this, SLOT(addServices(QPoint)));

    qAddAccessPoint = new QItemAction(tr("插入AccessPoint字段"), this);
    connect(qAddAccessPoint, SIGNAL(clicked(QPoint)), this, SLOT(addAccessPoint(QPoint)));

    qAddDynAssociation = new QItemAction(tr("插入DynAssociation"),this);
    connect(qAddDynAssociation, SIGNAL(clicked(QPoint)), this, SLOT(addDynAssociation(QPoint)));
    qAddSettingGroups = new QItemAction(tr("插入SettingGroups"), this);
    connect(qAddSettingGroups, SIGNAL(clicked(QPoint)), this, SLOT(addSettingGroups(QPoint)));
    qAddGetDirectory = new QItemAction(tr("插入GetDirectory"), this);
    connect(qAddGetDirectory, SIGNAL(clicked(QPoint)), this, SLOT(addGetDirectory(QPoint)));
    qAddGetDataObjectDefinition = new QItemAction(tr("插入DataObjectDefinition"), this);
    connect(qAddGetDataObjectDefinition, SIGNAL(clicked(QPoint)), this, SLOT(addGetDataObjectDefinition(QPoint)));
    qAddGetDataSetValue = new QItemAction(tr("插入GetDataSetValue"), this);
    connect(qAddGetDataSetValue, SIGNAL(clicked(QPoint)), this, SLOT(addGetDataSetValue(QPoint)));
    qAddSetDataSetValue = new QItemAction(tr("插入SetDataSetValue"), this);
    connect(qAddSetDataSetValue, SIGNAL(clicked(QPoint)), this, SLOT(addSetDataSetValue(QPoint)));
    qAddDataSetDirectory = new QItemAction(tr("插入DataSetDirectory"),this);
    connect(qAddDataSetDirectory, SIGNAL(clicked(QPoint)), this, SLOT(addDataSetDirectory(QPoint)));
    qAddConfDataSet = new QItemAction(tr("插入ConfDataSet"),this);
    connect(qAddConfDataSet, SIGNAL(clicked(QPoint)), this, SLOT(addConfDataSet(QPoint)));
    qAddDynDataSet = new QItemAction(tr("插入DynDataSet"),this);
    connect(qAddDynDataSet, SIGNAL(clicked(QPoint)), this, SLOT(addDynDataSet(QPoint)));
    qAddReadWrite = new QItemAction(tr("插入ReadWrite"),this);
    connect(qAddReadWrite, SIGNAL(clicked(QPoint)), this, SLOT(addReadWrite(QPoint)));
    qAddTimerActivatedControl = new QItemAction(tr("插入TimerActivatedControl"),this);
    connect(qAddTimerActivatedControl, SIGNAL(clicked(QPoint)), this, SLOT(addTimerActivatedControl(QPoint)));
    qAddConfReportControl = new QItemAction(tr("插入ConfReportControl"),this);
    connect(qAddConfReportControl, SIGNAL(clicked(QPoint)), this, SLOT(addConfReportControl(QPoint)));
    qAddGetCBValues = new QItemAction(tr("插入GetCBValues"),this);
    connect(qAddGetCBValues, SIGNAL(clicked(QPoint)), this, SLOT(addGetCBValues(QPoint)));
    qAddConfLogControl = new QItemAction(tr("插入ConfLogControl"),this);
    connect(qAddConfLogControl, SIGNAL(clicked(QPoint)), this, SLOT(addConfLogControl(QPoint)));
    qAddReportSettings = new QItemAction(tr("插入ReportSettings"),this);
    connect(qAddReportSettings, SIGNAL(clicked(QPoint)), this, SLOT(addReportSettings(QPoint)));
    qAddLogSettings = new QItemAction(tr("插入LogSettings"),this);
    connect(qAddLogSettings, SIGNAL(clicked(QPoint)), this, SLOT(addLogSettings(QPoint)));
    qAddGSESettings = new QItemAction(tr("插入GSESettings"),this);
    connect(qAddGSESettings, SIGNAL(clicked(QPoint)), this, SLOT(addGSESettings(QPoint)));
    qAddSMVSettings = new QItemAction(tr("插入SMVSettings"),this);
    connect(qAddSMVSettings, SIGNAL(clicked(QPoint)), this, SLOT(addSMVSettings(QPoint)));
    qAddGSEDir = new QItemAction(tr("插入GSEDir"),this);
    connect(qAddGSEDir, SIGNAL(clicked(QPoint)), this, SLOT(addGSEDir(QPoint)));
    qAddGOOSE = new QItemAction(tr("插入GOOSE"),this);
    connect(qAddGOOSE, SIGNAL(clicked(QPoint)), this, SLOT(addGOOSE(QPoint)));
    qAddGSSE = new QItemAction(tr("插入GSSE"),this);
    connect(qAddGSSE, SIGNAL(clicked(QPoint)), this, SLOT(addGSSE(QPoint)));
    qAddFileHandling = new QItemAction(tr("插入FileHandling"),this);
    connect(qAddFileHandling, SIGNAL(clicked(QPoint)), this, SLOT(addFileHandling(QPoint)));
    qAddConfLNs = new QItemAction(tr("插入ConfLNs"),this);
    connect(qAddConfLNs, SIGNAL(clicked(QPoint)), this, SLOT(addConfLNs(QPoint)));
    qAddSGEdit = new QItemAction(tr("插入SGEdit"),this);
    connect(qAddSGEdit, SIGNAL(clicked(QPoint)), this, SLOT(addSGEdit(QPoint)));
    qAddConfSG = new QItemAction(tr("插入ConfSG"),this);
    connect(qAddConfSG, SIGNAL(clicked(QPoint)), this, SLOT(addConfSG(QPoint)));

    qAddServer = new QItemAction(tr("插入Server"),this);
    connect(qAddServer, SIGNAL(clicked(QPoint)), this, SLOT(addServer(QPoint)));
    qAddLN = new QItemAction(tr("插入LN"),this);
    connect(qAddLN, SIGNAL(clicked(QPoint)), this, SLOT(addLN(QPoint)));

    qAddAuthentication = new QItemAction(tr("插入Authentication"),this);
    connect(qAddAuthentication, SIGNAL(clicked(QPoint)), this, SLOT(addAuthentication(QPoint)));
    qAddLDevice = new QItemAction(tr("插入LDevice"),this);
    connect(qAddLDevice, SIGNAL(clicked(QPoint)), this, SLOT(addLDevice(QPoint)));
    qAddAssociation = new QItemAction(tr("插入Association"),this);
    connect(qAddAssociation, SIGNAL(clicked(QPoint)), this, SLOT(addAssociation(QPoint)));

    qAddLN0 = new QItemAction(tr("插入LN0"),this);
    connect(qAddLN0, SIGNAL(clicked(QPoint)), this, SLOT(addLN0(QPoint)));
    qAddAccessControl = new QItemAction(tr("插入AccessControl"),this);
    connect(qAddAccessControl, SIGNAL(clicked(QPoint)), this, SLOT(addAccessControl(QPoint)));

    qAddGSEControl = new QItemAction(tr("插入GSEControl"),this);
    connect(qAddGSEControl, SIGNAL(clicked(QPoint)), this, SLOT(addGSEControl(QPoint)));
    qAddSampleValueControl = new QItemAction(tr("插入SampleValueControl"),this);
    connect(qAddSampleValueControl, SIGNAL(clicked(QPoint)), this, SLOT(addSampleValueControl(QPoint)));
    qAddSettingControl = new QItemAction(tr("插入SettingControl"),this);
    connect(qAddSettingControl, SIGNAL(clicked(QPoint)), this, SLOT(addSettingControl(QPoint)));
    qAddSCLControl = new QItemAction(tr("插入SCLControl"),this);
    connect(qAddSCLControl, SIGNAL(clicked(QPoint)), this, SLOT(addSCLControl(QPoint)));
    qAddLog = new QItemAction(tr("插入Log"),this);
    connect(qAddLog, SIGNAL(clicked(QPoint)), this, SLOT(addLog(QPoint)));

    qAddDataSet = new QItemAction(tr("插入DataSet"),this);
    connect(qAddDataSet, SIGNAL(clicked(QPoint)), this, SLOT(addDataSet(QPoint)));
    qAddReportControl = new QItemAction(tr("插入ReportControl"),this);
    connect(qAddReportControl, SIGNAL(clicked(QPoint)), this, SLOT(addReportControl(QPoint)));
    qAddLogControl = new QItemAction(tr("插入LogControl"),this);
    connect(qAddLogControl, SIGNAL(clicked(QPoint)), this, SLOT(addLogControl(QPoint)));
    qAddDOI = new QItemAction(tr("插入DOI"),this);
    connect(qAddDOI, SIGNAL(clicked(QPoint)), this, SLOT(addDOI(QPoint)));
    qAddInputs = new QItemAction(tr("插入Inputs"),this);
    connect(qAddInputs, SIGNAL(clicked(QPoint)), this, SLOT(addInputs(QPoint)));

    qAddIEDName = new QItemAction(tr("插入IEDName"),this);
    connect(qAddIEDName, SIGNAL(clicked(QPoint)), this, SLOT(addIEDName(QPoint)));

    qAddSmvOpts = new QItemAction(tr("插入SmvOpts"),this);
    connect(qAddSmvOpts, SIGNAL(clicked(QPoint)), this, SLOT(addSmvOpts(QPoint)));

    qAddFCDA = new QItemAction(tr("插入FCDA"),this);
    connect(qAddFCDA, SIGNAL(clicked(QPoint)), this, SLOT(addFCDA(QPoint)));

    qAddOptFields = new QItemAction(tr("插入OptFields"),this);
    connect(qAddOptFields, SIGNAL(clicked(QPoint)), this, SLOT(addOptFields(QPoint)));
    qAddRptEnabled = new QItemAction(tr("插入RptEnabled"),this);
    connect(qAddRptEnabled, SIGNAL(clicked(QPoint)), this, SLOT(addRptEnabled(QPoint)));
    qAddTrgOps = new QItemAction(tr("插入TrgOps"),this);
    connect(qAddTrgOps, SIGNAL(clicked(QPoint)), this, SLOT(addTrgOps(QPoint)));

    qAddClientLN = new QItemAction(tr("插入ClientLN"),this);
    connect(qAddClientLN, SIGNAL(clicked(QPoint)), this, SLOT(addClientLN(QPoint)));

    qAddSDI = new QItemAction(tr("插入SDI"),this);
    connect(qAddSDI, SIGNAL(clicked(QPoint)), this, SLOT(addSDI(QPoint)));
    qAddDAI = new QItemAction(tr("插入DAI"),this);
    connect(qAddDAI, SIGNAL(clicked(QPoint)), this, SLOT(addDAI(QPoint)));

    qAddVal = new QItemAction(tr("插入Val"),this);
    connect(qAddVal, SIGNAL(clicked(QPoint)), this, SLOT(addVal(QPoint)));
    qAddValContent = new QItemAction(tr("插入Val值"),this);
    connect(qAddValContent, SIGNAL(clicked(QPoint)), this, SLOT(addValContent(QPoint)));

    qAddExtRef = new QItemAction(tr("插入ExtRef"),this);
    connect(qAddExtRef, SIGNAL(clicked(QPoint)), this, SLOT(addExtRef(QPoint)));


    qAddLNodeType = new QItemAction(tr("插入LNodeType"),this);
    connect(qAddLNodeType, SIGNAL(clicked(QPoint)), this, SLOT(addLNodeType(QPoint)));
    qAddDOType = new QItemAction(tr("插入DOType"),this);
    connect(qAddDOType, SIGNAL(clicked(QPoint)), this, SLOT(addDOType(QPoint)));
    qAddDAType = new QItemAction(tr("插入DAType"),this);
    connect(qAddDAType, SIGNAL(clicked(QPoint)), this, SLOT(addDAType(QPoint)));
    qAddEnumType = new QItemAction(tr("插入EnumType"),this);
    connect(qAddEnumType, SIGNAL(clicked(QPoint)), this, SLOT(addEnumType(QPoint)));

    qAddDO = new QItemAction(tr("插入DO"),this);
    connect(qAddDO, SIGNAL(clicked(QPoint)), this, SLOT(addDO(QPoint)));
    qAddSDO = new QItemAction(tr("插入SDO"),this);
    connect(qAddSDO, SIGNAL(clicked(QPoint)), this, SLOT(addSDO(QPoint)));
    qAddDA = new QItemAction(tr("插入DA"),this);
    connect(qAddDA, SIGNAL(clicked(QPoint)), this, SLOT(addDA(QPoint)));
    qAddBDA = new QItemAction(tr("插入BDA"),this);
    connect(qAddBDA, SIGNAL(clicked(QPoint)), this, SLOT(addBDA(QPoint)));
    qAddEnumVal = new QItemAction(tr("插入EnumVal"),this);
    connect(qAddEnumVal, SIGNAL(clicked(QPoint)), this, SLOT(addEnumVal(QPoint)));
}

void MainWindow::CreateMenus()
{

lnClass << "LPHD" << "LLN0" << \
           "ANCR" << "ARCO" << "ATCC" << "AVCO" << \
           "CILO" << "CSWI" << "CALH" << "CCGR" << "CPOW" << \
           "GAPC" << "GGIO" << "GSAL" << \
           "IHMI" << "IARC" << "ITCI" << "ITMI" << \
           "MMXU" << "MDIF" << "MHAI" << "MHAN" << "MMTR" << "MMXN" << "MSQI" << "MSTA" << \
           "PDIF" << "PDIS" << "PDIR" << "PDOP" << "PDUP" << "PFRC" << "PHAR" << "PHIZ" << "PIOC" << "PMRI" << \
           "PMSS" << "POPF" << "PPAM" << "PSCH" << "PSDE" << "PTEF" << "PTOC" << "PTOF" << "PTOV" << "PTRC" << \
           "PTTR" << "PTUC" << "PTUV" << "PUPF" << "PTUF" << "PVOC" << "PVPH" << "PZSU" << \
           "RSYN" << "RDRE" << "RADR" << "RBDR" << "RDRS" << "RBRF" << "RDIR" << "RFLO" << "RPSB" << "RREC" << \
           "SARC" << "SIMG" << "SIML" << "SPDC" << \
           "TCTR" << "TVTR" << \
           "XCBR" << "XSWI" << \
           "YPTR" << "YEFN" << "YLTC" << "YPSH" << \
           "ZAXN" << "ZBAT" << "ZBSH" << "ZCAB" << "ZCAP" << "ZCON" << "ZGEN" << \
           "ZGIL" << "ZLIN" << "ZMOT" << "ZREA" << "ZRRC" << "ZSAR" << "ZTCF" << "ZTCR";

fcEnum << "ST" << "MX" << "CO" << "SP" << "SG" << "SE" << "SV" << "CF" << "DC" << "EX";

cdc << "SPS" << "DPS" << "INS" << "ACT" << "ACD" << "SEC" << "BCR" << "MV" << "CMV" << "SAV" << \
       "WYE" << "DEL" << "SEQ" << "HMV" << "HWYE" << "HDEL" << "SPC" << "DPC" << "INC" << "BSC" << \
       "ISC" << "APC" << "SPG" << "ING" << "ASG" << "CURVE" << "DPL" << "LPL" << "CSD";

BasicType << "BOOLEAN" << "INT8" << "INT16" << "INT24" << "INT32" << "INT128" << \
             "INT8U" << "INT16U" << "INT24U" << "INT32U" << "FLOAT32" << "FLOAT64" << \
             "Enum" << "Dbops" << "Tcmd" << "Quality" << "Timestamp" << \
             "VisString32" << "VisString64" << "VisString255" << "Octet64" << "Struct" << "EntryTime" << "Unicode255";

    qFileMenu = menuBar()->addMenu(tr("&File"));
    qFileMenu->addAction(qFileNew);
    qFileMenu->addAction(qFileOpen);
    qFileMenu->addAction(qFileSave);

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

    doc = new QDomDocument();
    CreateNewICD(doc);



//    if (doc->setContent(newFile)) {
        DomModel *newModel = new DomModel(*doc, this);
        qDebug()<<newModel->getRootItem()->child(2)->node().toElement().tagName();
        view->setModel(newModel);
//        view->setRootIndex(newModel->index(2,0));
//        view->setRootIsDecorated(true);
        delete model;
        model = newModel;

        view->setExpanded(model->index(2,0),1);
//        view->expandAll();
//    }


    QTextStream out(newFile);
    doc->save(out,4);
//    delete doc;

    newFile->close();

}

void MainWindow::fileOpenAct()
{
//    QFileDialog *fileOpenDlg = new QFileDialog(this, tr("打开文件"));
//    fileOpenDlg->setFilters(QStringList()<<tr("ICD files (*.icd, *.cid)")<<tr("SCD files (*.scd)")<<tr("All files (*.*)"));
//    fileOpenDlg->exec();
      openFileName = QFileDialog::getOpenFileName(this, tr("打开文件"),NULL,tr("ICD files(*.icd);;SCD files(*.scd);;All files(*.*)"));
      qDebug()<<openFileName;
      newFileName = openFileName;
//      if(newFile)
//      {
//          qDebug()<<tr("newFile is not Empty!");
//          delete newFile;
//      }

      newFile = new QFile(newFileName);
      qDebug()<<newFileName;

      if(!newFile->open(QIODevice::ReadWrite))
      {
          QMessageBox::information(this,tr("Save File Warning"),tr("Save File Error"));
          return;
      }

//      if(doc)
//          delete doc;

      doc = new QDomDocument();
      doc->setContent(newFile);


          qDebug()<<doc->childNodes().at(2).toElement().tagName();
          DomModel *newModel = new DomModel(*doc, this);
          view->setModel(newModel);
  //        view->setRootIndex(newModel->index(2,0));
  //        view->setRootIsDecorated(true);
          delete model;
          model = newModel;

          view->setExpanded(model->index(2,0),1);
  //        view->expandAll();
//      }


}


void MainWindow::fileSaveAct()
{

//    delete newFile;
    if(newFileName.isEmpty())
    {
        return;
    }
    qDebug()<<newFileName;
    qDebug()<<doc->childNodes().at(2).toElement().tagName();
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
     SubNetwork.setAttributeNode(subNetwork_desc);

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

     /****************************************************/
     /****  Add DataTypeTemplates Section  ***********************/
     /****************************************************/
     QDomElement DataTypeTemplates = doc->createElement(tr("DataTypeTemplates"));
     root.appendChild(DataTypeTemplates);

     /***  Add LNodeType section ***************************/
     QDomElement LNodeType = doc->createElement(tr("LNodeType"));
     QDomAttr LNodeType_id = doc->createAttribute(tr("id"));
     QDomAttr LNodeType_lnClass = doc->createAttribute(tr("lnClass"));
     QDomAttr LNodeType_iedType = doc->createAttribute(tr("iedType"));
     QDomAttr LNodeType_desc = doc->createAttribute(tr("desc"));

     LNodeType_id.setValue(tr("GDWY_LLN0"));
     LNodeType_lnClass.setValue(tr("LLN0"));
     LNodeType_iedType.setValue(tr(""));
     LNodeType_desc.setValue(tr(""));
     LNodeType.setAttributeNode(LNodeType_id);
     LNodeType.setAttributeNode(LNodeType_lnClass);
     LNodeType.setAttributeNode(LNodeType_iedType);
     LNodeType.setAttributeNode(LNodeType_desc);

     DataTypeTemplates.appendChild(LNodeType);
}

void MainWindow::showPopMenu(QPoint cp)
{
    QMenu *qPopMenu = new QMenu(this);
    QModelIndex *currentItem = new QModelIndex();

    *currentItem = view->indexAt(cp);

    if(currentItem->data().isNull())
        return;

    DomItem *Item = static_cast<DomItem*>(currentItem->internalPointer());
    QDomNode currentNode = Item->node();

    if(currentItem->data().toString() == tr("SCL"))
    {
        qAddHeader->setCP(cp);
        qPopMenu->addAction(qAddHeader);
        qAddSubstation->setCP(cp);
        qPopMenu->addAction(qAddSubstation);
        qAddCommunication->setCP(cp);
        qPopMenu->addAction(qAddCommunication);
        qAddIED->setCP(cp);
        qPopMenu->addAction(qAddIED);
        qAddDataTypeTemplates->setCP(cp);
        qPopMenu->addAction(qAddDataTypeTemplates);

        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("Header"))
            {
                qAddHeader->setDisabled(1);
                break;
            }
        }
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("Communication"))
            {
                qAddCommunication->setDisabled(1);
                break;
            }
        }
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("DataTypeTemplates"))
            {
                qAddDataTypeTemplates->setDisabled(1);
                break;
            }
        }

    }

    if(currentItem->data().toString() == tr("Header"))
    {
        qAddText->setCP(cp);
        qPopMenu->addAction(qAddText);
        qAddHistory->setCP(cp);
        qPopMenu->addAction(qAddHistory);
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("Text"))
            {
                qAddText->setDisabled(1);
                break;
            }
        }
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("History"))
            {
                qAddHistory->setDisabled(1);
                break;
            }
        }

    }
    if(currentItem->data().toString() == tr("History"))
    {
        qDebug()<<tr("Add Hitem Menu");
        qAddHitem->setCP(cp);
        qPopMenu->addAction(qAddHitem);
    }
    if(currentItem->data().toString() == tr("Text"))
    {
        qAddTextContent->setCP(cp);
        qPopMenu->addAction(qAddTextContent);
    }

    if(currentItem->data().toString() == tr("IED"))
    {
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("Services"))
            {
                qAddServices->setDisabled(1);
                break;
            }
        }
        qAddServices->setCP(cp);
        qPopMenu->addAction(qAddServices);
        qAddAccessPoint->setCP(cp);
        qPopMenu->addAction(qAddAccessPoint);
    }

    if(currentItem->data().toString() == tr("Services"))
    {
        qAddDynAssociation->setCP(cp);
        qPopMenu->addAction(qAddDynAssociation);
        qAddSettingGroups->setCP(cp);
        qPopMenu->addAction(qAddSettingGroups);
        qAddGetDirectory->setCP(cp);
        qPopMenu->addAction(qAddGetDirectory);
        qAddGetDataObjectDefinition->setCP(cp);
        qPopMenu->addAction(qAddGetDataObjectDefinition);
        qAddGetDataSetValue->setCP(cp);
        qPopMenu->addAction(qAddGetDataSetValue);
        qAddSetDataSetValue->setCP(cp);
        qPopMenu->addAction(qAddSetDataSetValue);
        qAddDataSetDirectory->setCP(cp);
        qPopMenu->addAction(qAddDataSetDirectory);
        qAddConfDataSet->setCP(cp);
        qPopMenu->addAction(qAddConfDataSet);
        qAddDynDataSet->setCP(cp);
        qPopMenu->addAction(qAddDynDataSet);
        qAddReadWrite->setCP(cp);
        qPopMenu->addAction(qAddReadWrite);
        qAddTimerActivatedControl->setCP(cp);
        qPopMenu->addAction(qAddTimerActivatedControl);
        qAddConfReportControl->setCP(cp);
        qPopMenu->addAction(qAddConfReportControl);
        qAddGetCBValues->setCP(cp);
        qPopMenu->addAction(qAddGetCBValues);
        qAddConfLogControl->setCP(cp);
        qPopMenu->addAction(qAddConfLogControl);
        qAddReportSettings->setCP(cp);
        qPopMenu->addAction(qAddReportSettings);
        qAddLogSettings->setCP(cp);
        qPopMenu->addAction(qAddLogSettings);
        qAddGSESettings->setCP(cp);
        qPopMenu->addAction(qAddGSESettings);
        qAddSMVSettings->setCP(cp);
        qPopMenu->addAction(qAddSMVSettings);
        qAddGSEDir->setCP(cp);
        qPopMenu->addAction(qAddGSEDir);
        qAddGOOSE->setCP(cp);
        qPopMenu->addAction(qAddGOOSE);
        qAddGSSE->setCP(cp);
        qPopMenu->addAction(qAddGSSE);
        qAddFileHandling->setCP(cp);
        qPopMenu->addAction(qAddFileHandling);
        qAddConfLNs->setCP(cp);
        qPopMenu->addAction(qAddConfLNs);

        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("DynAssociation"))
            {
                qAddDynAssociation->setDisabled(1);
                break;
            }
        }
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("SettingGroups"))
            {
                qAddSettingGroups->setDisabled(1);
                break;
            }
        }
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("GetDirectory"))
            {
                qAddGetDirectory->setDisabled(1);
                break;
            }
        }
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("GetDataObjectDefinition"))
            {
                qAddGetDataObjectDefinition->setDisabled(1);
                break;
            }
        }
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("DataObjectDirectory"))
            {
                qAddDataObjectDirectory->setDisabled(1);
                break;
            }
        }
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("GetDataSetValue"))
            {
                qAddGetDataSetValue->setDisabled(1);
                break;
            }
        }
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("SetDataSetValue"))
            {
                qAddSetDataSetValue->setDisabled(1);
                break;
            }
        }
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("DataSetDirectory"))
            {
                qAddDataSetDirectory->setDisabled(1);
                break;
            }
        }
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("ConfDataSet"))
            {
                qAddConfDataSet->setDisabled(1);
                break;
            }
        }
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("DynDataSet"))
            {
                qAddDynDataSet->setDisabled(1);
                break;
            }
        }
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("ReadWrite"))
            {
                qAddReadWrite->setDisabled(1);
                break;
            }
        }
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("TimerActivatedControl"))
            {
                qAddTimerActivatedControl->setDisabled(1);
                break;
            }
        }
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("ConfReportControl"))
            {
                qAddConfReportControl->setDisabled(1);
                break;
            }
        }
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("GetCBValues"))
            {
                qAddGetCBValues->setDisabled(1);
                break;
            }
        }
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("ConfLogControl"))
            {
                qAddConfLogControl->setDisabled(1);
                break;
            }
        }
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("ReportSettings"))
            {
                qAddReportSettings->setDisabled(1);
                break;
            }
        }
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("LogSettings"))
            {
                qAddLogSettings->setDisabled(1);
                break;
            }
        }
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("GSESettings"))
            {
                qAddGSESettings->setDisabled(1);
                break;
            }
        }
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("SMVSettings"))
            {
                qAddSMVSettings->setDisabled(1);
                break;
            }
        }
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("GSEDir"))
            {
                qAddGSEDir->setDisabled(1);
                break;
            }
        }
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("GOOSE"))
            {
                qAddGOOSE->setDisabled(1);
                break;
            }
        }
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("GSSE"))
            {
                qAddGSSE->setDisabled(1);
                break;
            }
        }
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("FileHandling"))
            {
                qAddFileHandling->setDisabled(1);
                break;
            }
        }
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("ConfLNs"))
            {
                qAddConfLNs->setDisabled(1);
                break;
            }
        }
    }
    if(currentItem->data().toString() == tr("SettingGroups"))
    {
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("SGEdit"))
            {
                qAddSGEdit->setDisabled(1);
                break;
            }
        }
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("ConfSG"))
            {
                qAddConfSG->setDisabled(1);
                break;
            }
        }
        qAddSGEdit->setCP(cp);
        qPopMenu->addAction(qAddSGEdit);
        qAddConfSG->setCP(cp);
        qPopMenu->addAction(qAddConfSG);
    }
    if(currentItem->data().toString() == tr("SettingGroups"))
    {
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("Server"))
            {
                qAddSGEdit->setDisabled(1);
                break;
            }
        }
        qAddSGEdit->setCP(cp);
        qPopMenu->addAction(qAddSGEdit);
        qAddConfSG->setCP(cp);
        qPopMenu->addAction(qAddConfSG);
    }

    if(currentItem->data().toString() == tr("AccessPoint"))
    {
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("Server"))
            {
                qAddServer->setDisabled(1);
                break;
            }
        }
        qAddServer->setCP(cp);
        qPopMenu->addAction(qAddServer);
        qAddLN->setCP(cp);
        qPopMenu->addAction(qAddLN);
    }

    if(currentItem->data().toString() == tr("Server"))
    {
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("Authentication"))
            {
                qAddAuthentication->setDisabled(1);
                break;
            }
        }

        qAddAuthentication->setCP(cp);
        qPopMenu->addAction(qAddAuthentication);
        qAddLDevice->setCP(cp);
        qPopMenu->addAction(qAddLDevice);
        qAddAssociation->setCP(cp);
        qPopMenu->addAction(qAddAssociation);
    }

    if(currentItem->data().toString() == tr("LDevice"))
    {
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("LN0"))
            {
                qAddLN0->setDisabled(1);
                break;
            }
        }
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("AccessControl"))
            {
                qAddAccessControl->setDisabled(1);
                break;
            }
        }

        qAddLN0->setCP(cp);
        qPopMenu->addAction(qAddLN0);
        qAddLN->setCP(cp);
        qPopMenu->addAction(qAddLN);
        qAddAccessControl->setCP(cp);
        qPopMenu->addAction(qAddAccessControl);
    }

    if(currentItem->data().toString() == tr("LN0"))
    {
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("SettingControl"))
            {
                qAddSettingControl->setDisabled(1);
                break;
            }
        }
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("SCLControl"))
            {
                qAddSCLControl->setDisabled(1);
                break;
            }
        }
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("Log"))
            {
                qAddLog->setDisabled(1);
                break;
            }
        }
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("Inputs"))
            {
                qAddInputs->setDisabled(1);
                break;
            }
        }

        qAddGSEControl->setCP(cp);
        qPopMenu->addAction(qAddGSEControl);
        qAddSampleValueControl->setCP(cp);
        qPopMenu->addAction(qAddSampleValueControl);
        qAddSettingControl->setCP(cp);
        qPopMenu->addAction(qAddSettingControl);
        qAddSCLControl->setCP(cp);
        qPopMenu->addAction(qAddSCLControl);
        qAddLog->setCP(cp);
        qPopMenu->addAction(qAddLog);

        qAddDataSet->setCP(cp);
        qPopMenu->addAction(qAddDataSet);
        qAddReportControl->setCP(cp);
        qPopMenu->addAction(qAddReportControl);
        qAddLogControl->setCP(cp);
        qPopMenu->addAction(qAddLogControl);
        qAddDOI->setCP(cp);
        qPopMenu->addAction(qAddDOI);
        qAddInputs->setCP(cp);
        qPopMenu->addAction(qAddInputs);
    }

    if(currentItem->data().toString() == tr("LN"))
    {
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("Inputs"))
            {
                qAddInputs->setDisabled(1);
                break;
            }
        }

        qAddDataSet->setCP(cp);
        qPopMenu->addAction(qAddDataSet);
        qAddReportControl->setCP(cp);
        qPopMenu->addAction(qAddReportControl);
        qAddLogControl->setCP(cp);
        qPopMenu->addAction(qAddLogControl);
        qAddDOI->setCP(cp);
        qPopMenu->addAction(qAddDOI);
        qAddInputs->setCP(cp);
        qPopMenu->addAction(qAddInputs);
    }

    if(currentItem->data().toString() == tr("GSEControl"))
    {
        qAddIEDName->setCP(cp);
        qPopMenu->addAction(qAddIEDName);
    }

    if(currentItem->data().toString() == tr("SampleValueControl"))
    {
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("SmvOpts"))
            {
                qAddInputs->setDisabled(1);
                break;
            }
        }

        qAddSmvOpts->setCP(cp);
        qPopMenu->addAction(qAddSmvOpts);
        qAddIEDName->setCP(cp);
        qPopMenu->addAction(qAddIEDName);
    }

    if(currentItem->data().toString().contains(tr("DataSet")))
    {
        qAddFCDA->setCP(cp);
        qPopMenu->addAction(qAddFCDA);
    }

    if(currentItem->data().toString().contains(tr("ReportControl")))
    {
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("OptFields"))
            {
                qAddSGEdit->setDisabled(1);
                break;
            }
        }
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("RptEnabled"))
            {
                qAddConfSG->setDisabled(1);
                break;
            }
        }
        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            if(currentNode.childNodes().at(i).toElement().tagName() == tr("TrgOps"))
            {
                qAddConfSG->setDisabled(1);
                break;
            }
        }
        qAddOptFields->setCP(cp);
        qPopMenu->addAction(qAddOptFields);
        qAddRptEnabled->setCP(cp);
        qPopMenu->addAction(qAddRptEnabled);
        qAddTrgOps->setCP(cp);
        qPopMenu->addAction(qAddTrgOps);
    }

    if(currentItem->data().toString().contains(tr("DOI")))
    {

        qAddSDI->setCP(cp);
        qPopMenu->addAction(qAddSDI);
        qAddDAI->setCP(cp);
        qPopMenu->addAction(qAddDAI);
    }

    if(currentItem->data().toString().contains(tr("SDI")))
    {

        qAddSDI->setCP(cp);
        qPopMenu->addAction(qAddSDI);
        qAddDAI->setCP(cp);
        qPopMenu->addAction(qAddDAI);
    }

    if(currentItem->data().toString().contains(tr("DAI")))
    {
        qAddVal->setCP(cp);
        qPopMenu->addAction(qAddVal);
    }

    if(currentItem->data().toString().contains(tr("Val")))
    {
        qAddValContent->setCP(cp);
        qPopMenu->addAction(qAddValContent);
    }

    if(currentItem->data().toString().contains(tr("Inputs")))
    {
        qAddExtRef->setCP(cp);
        qPopMenu->addAction(qAddExtRef);
    }

    if(currentItem->data().toString() == tr("DataTypeTemplates"))
    {
        qAddLNodeType->setCP(cp);
        qPopMenu->addAction(qAddLNodeType);
        qAddDOType->setCP(cp);
        qPopMenu->addAction(qAddDOType);
        qAddDAType->setCP(cp);
        qPopMenu->addAction(qAddDAType);
        qAddEnumType->setCP(cp);
        qPopMenu->addAction(qAddEnumType);
    }

    if(currentItem->data().toString().contains(tr("LNodeType")))
    {
        qAddDO->setCP(cp);
        qPopMenu->addAction(qAddDO);
    }

    if(currentItem->data().toString().contains(tr("DOType")))
    {
        qAddSDO->setCP(cp);
        qPopMenu->addAction(qAddSDO);
        qAddDA->setCP(cp);
        qPopMenu->addAction(qAddDA);
    }

    if(currentItem->data().toString().contains(tr("DAType")))
    {
        qAddBDA->setCP(cp);
        qPopMenu->addAction(qAddBDA);
    }

    if(currentItem->data().toString().contains(tr("EnumType")))
    {
        qAddEnumVal->setCP(cp);
        qPopMenu->addAction(qAddEnumVal);
    }

    if(currentItem->data().toString() == tr("DA"))
    {
        qAddVal->setCP(cp);
        qPopMenu->addAction(qAddVal);
    }

    if(currentItem->data().toString() == tr("BDA"))
    {
        qAddVal->setCP(cp);
        qPopMenu->addAction(qAddVal);
    }

    if(currentItem->data().toString() != tr("SCL"))
    {
        qDeleteItem->setCP(cp);
        qPopMenu->addAction(qDeleteItem);
    }

    if(newFileName == NULL)
    {
        qPopMenu->setDisabled(1);
    }
    qPopMenu->exec(QCursor::pos());
}
/*
void MainWindow::addHistoryAct(QDomNode data)
{
//    QDomDocument *doc = new QDomDocument();
//    doc->setContent(newFile);
    QDomElement qNewElement = doc->createElement(tr("History"));

    data.appendChild(qNewElement);

    qDebug()<<tr("Add Completed!");

//    root.firstChild().appendChild(qNewElement);

    DomModel *newModel = new DomModel(*doc, this);
    view->setModel(newModel);
//    view->setRootIndex(newModel->index(2,0));
     delete model;
    model = newModel;


//    DomItem *tempItem = static_cast<DomItem*>(view->currentIndex().internalPointer());
//    QDomNode tempNode = tempItem->node();
//    qDebug()<<tempNode.toElement().tagName();
//    view->setExpanded(view->currentIndex(),1);

//    delete newFile;
//    newFile = new QFile(newFileName);
//    newFile->open(QIODevice::WriteOnly|QIODevice::Truncate);
//    QTextStream out(newFile);
//    doc->save(out,4);
//    newFile->close();

}
*/

void MainWindow::addHeader(QPoint cp)
{
    qDebug()<<tr("Add Header Action");
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - Header"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(6,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)id")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(1,0,new QTableWidgetItem(tr("(*)nameStructure")));
    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(2,0,new QTableWidgetItem(tr("version")));
    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(3,0,new QTableWidgetItem(tr("revision")));
    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(4,0,new QTableWidgetItem(tr("toolID")));
    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(4,0)->setCheckState(Qt::Unchecked);

    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(1,1,new QTableWidgetItem(tr("")));
//    AttrTable->setCellWidget(2,1,new QCalendarWidget(this));
    AttrTable->setItem(2,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(3,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(4,1,new QTableWidgetItem(tr("")));

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    while(AttrDlg->exec() == QDialog::Accepted)
    {
        qDebug()<<tr("Attr Dialog Confirm");
        QDomElement qNewElement = doc->createElement(tr("Header"));
        if(AttrTable->item(0,1)->text()==tr(""))
        {
            QMessageBox::warning(NULL,tr("警告"),tr("id项为必需项，不能为空!"));
            continue;
        }
        if(AttrTable->item(1,1)->text()==tr(""))
        {
            QMessageBox::warning(NULL,tr("警告"),tr("nameStructure项为必需项，不能为空!"));
            continue;
        }

        qNewElement.setAttribute(tr("id"), AttrTable->item(0,1)->text());
        qNewElement.setAttribute(tr("nameStructure"), AttrTable->item(1,1)->text());
        if((AttrTable->item(2,0))->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("version"), AttrTable->item(2,1)->text());
        if((AttrTable->item(3,0))->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("revision"), AttrTable->item(3,1)->text());
        if((AttrTable->item(4,0))->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("toolID"), AttrTable->item(4,1)->text());

        currentNode.appendChild(qNewElement);
        model->update();
        view->setExpanded(model->index(2,0),1);
//        view->setExpanded(model->index(0,0,model->index(2,0)),1);
        view->setExpanded(view->indexAt(cp),1);
        currentItem = static_cast<DomItem*>(view->indexAt(cp).internalPointer());
        qDebug()<<view->indexAt(cp).data().toString();
        break;
//        qDebug()<<currentItem->node().toElement().tagName();
    }
}

void MainWindow::addSubstation(QPoint cp)
{

}

void MainWindow::addCommunication(QPoint cp)
{

}

void MainWindow::addIED(QPoint cp)
{
    qDebug()<<tr("Add IED Action");
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - IED"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(5,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)name")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(1,0,new QTableWidgetItem(tr("desc")));
    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(2,0,new QTableWidgetItem(tr("type")));
    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(3,0,new QTableWidgetItem(tr("manufacturer")));
    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(4,0,new QTableWidgetItem(tr("configVersion")));
    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(4,0)->setCheckState(Qt::Unchecked);

    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(1,1,new QTableWidgetItem(tr("")));
//    AttrTable->setCellWidget(2,1,new QCalendarWidget(this));
    AttrTable->setItem(2,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(3,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(4,1,new QTableWidgetItem(tr("")));

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    while(AttrDlg->exec() == QDialog::Accepted)
    {
        qDebug()<<tr("Attr Dialog Confirm");
        QDomElement qNewElement = doc->createElement(tr("IED"));

        if(AttrTable->item(0,1)->text()==tr(""))
        {
            QMessageBox::warning(NULL,tr("警告"),tr("name项为必需项，不能为空!"));
            continue;
        }

        qNewElement.setAttribute(tr("name"), AttrTable->item(0,1)->text());
        if((AttrTable->item(1,0))->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("desc"), AttrTable->item(1,1)->text());
        if((AttrTable->item(2,0))->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("type"), AttrTable->item(2,1)->text());
        if((AttrTable->item(3,0))->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("manufacturer"), AttrTable->item(3,1)->text());
        if((AttrTable->item(4,0))->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("configVersion"), AttrTable->item(4,1)->text());

        currentNode.appendChild(qNewElement);
        model->update();
        view->setExpanded(model->index(2,0),1);
//        view->setExpanded(model->index(0,0,model->index(2,0)),1);
        view->setExpanded(view->indexAt(cp),1);
        currentItem = static_cast<DomItem*>(view->indexAt(cp).internalPointer());
        qDebug()<<view->indexAt(cp).data().toString();
        break;
//        qDebug()<<currentItem->node().toElement().tagName();
    }
}

void MainWindow::addDataTypeTemplates(QPoint cp)
{

}

void MainWindow::addHistoryAct(QPoint cp)
{
    qDebug()<<tr("add history act");
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();
    qDebug()<<currentNode.toElement().tagName();

    QDomElement qNewElement = doc->createElement(tr("History"));
    currentNode.appendChild(qNewElement);
    qDebug()<<tr("Add Completed!");

    QModelIndex parentIndex = view->indexAt(cp).parent();
    view->setExpanded(parentIndex,0);
    view->setExpanded(parentIndex,1);
    view->setExpanded(view->indexAt(cp),1);
}

void MainWindow::addTextAct(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - Text"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(1,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("source")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));

    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,6,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,6,3);
    AttrDlgLayout->addWidget(qAttrDlgCancel,6,4);
    if(AttrDlg->exec()==QDialog::Accepted)
    {
        qDebug()<<tr("Attr Dialog Confirm");
        QDomElement qNewElement = doc->createElement(tr("Text"));

        if(((QCheckBox *)(AttrTable->cellWidget(0,0)))->isChecked())
            qNewElement.setAttribute(tr("source"), AttrTable->item(0,1)->text());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
    }
    else
        return;
}

void MainWindow::addTextContentAct(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *ContentDlg = new QDialog(this);
    ContentDlg->setWindowTitle(tr("Text内容输入"));
    QGridLayout *ContentDlgLayout = new QGridLayout(ContentDlg);
    QLabel *ContentLabel = new QLabel(tr("请输入Text内容："));
    QLineEdit *ContentEdit = new QLineEdit(this);

    QPushButton *qContentDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qContentDlgConfirm, SIGNAL(clicked()), ContentDlg, SLOT(accept()));
    QPushButton *qContentDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qContentDlgCancel, SIGNAL(clicked()), ContentDlg, SLOT(close()));
    ContentDlgLayout->addWidget(ContentLabel,0,0,1,1);
    ContentDlgLayout->addWidget(ContentEdit,0,1,1,3);
    ContentDlgLayout->addWidget(qContentDlgConfirm,2,2);
    ContentDlgLayout->addWidget(qContentDlgCancel,2,3);

    if(ContentDlg->exec() == QDialog::Accepted)
    {
        QDomText qNewText = doc->createTextNode(ContentEdit->text());

        currentNode.appendChild(qNewText);
        model->update();
        view->setExpanded(model->index(2,0),1);
        view->setExpanded(model->index(0,0,model->index(2,0)),1);
        view->setExpanded(view->indexAt(cp),1);
        currentItem = static_cast<DomItem*>(view->indexAt(cp).internalPointer());
        qDebug()<<view->indexAt(cp).data().toString();
//        qDebug()<<currentItem->node().toElement().tagName();
    }
}

void MainWindow::addHitemAct(QPoint cp)
{
    qDebug()<<tr("Add Hitem Action");
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - Hitem"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(6,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)version")));
    AttrTable->item(0,0)->setFlags(Qt::ItemIsEnabled);
    AttrTable->setItem(1,0,new QTableWidgetItem(tr("(*)revision")));
    AttrTable->item(1,0)->setFlags(Qt::ItemIsEnabled);
    AttrTable->setItem(2,0,new QTableWidgetItem(tr("(*)when")));
    AttrTable->item(2,0)->setFlags(Qt::ItemIsEnabled);
    AttrTable->setItem(3,0,new QTableWidgetItem(tr("who")));
    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(4,0,new QTableWidgetItem(tr("what")));
    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(4,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(5,0,new QTableWidgetItem(tr("why")));
    AttrTable->item(5,0)->setFlags(AttrTable->item(5,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(5,0)->setCheckState(Qt::Unchecked);

    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(1,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(2,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(3,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(4,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(5,1,new QTableWidgetItem(tr("")));

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    while(AttrDlg->exec() == QDialog::Accepted)
    {
        bool VersionCollide = 0;
        qDebug()<<tr("Attr Dialog Confirm");
        QDomElement qNewElement = doc->createElement(tr("Hitem"));
        if(AttrTable->item(0,1)->text()==tr(""))
        {
            QMessageBox::warning(NULL,tr("警告"),tr("version项为必需项，不能为空!"));
            continue;
        }
        if(AttrTable->item(1,1)->text()==tr(""))
        {
            QMessageBox::warning(NULL,tr("警告"),tr("revision项为必需项，不能为空!"));
            continue;
        }
        if(AttrTable->item(2,1)->text()==tr(""))
        {
            QMessageBox::warning(NULL,tr("警告"),tr("when项为必需项，不能为空!"));
            continue;
        }

        for(int i=0; i<currentNode.childNodes().count(); i++)
        {
            QDomNamedNodeMap oldAttr = currentNode.childNodes().at(i).attributes();
            qDebug()<<oldAttr.namedItem(tr("version")).nodeValue();
            if(oldAttr.namedItem(tr("version")).nodeValue() == AttrTable->item(0,1)->text()
             && oldAttr.namedItem(tr("revision")).nodeValue() == AttrTable->item(1,1)->text())
            {
                QMessageBox::warning(NULL,tr("警告"),tr("version, revision不能重复!"));
                VersionCollide = 1;
                break;
            }
        }

        if(VersionCollide)
            continue;

        qNewElement.setAttribute(tr("version"), AttrTable->item(0,1)->text());
        qNewElement.setAttribute(tr("revision"), AttrTable->item(1,1)->text());
        qNewElement.setAttribute(tr("when"), AttrTable->item(2,1)->text());
        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("who"), AttrTable->item(3,1)->text());
        if(AttrTable->item(4,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("what"), AttrTable->item(4,1)->text());
        if(AttrTable->item(5,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("why"), AttrTable->item(5,1)->text());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
        break;
//        qDebug()<<currentItem->node().toElement().tagName();
    }
//    else
//        return;

}

void MainWindow::addServices(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();
    qDebug()<<currentNode.toElement().tagName();

    QDomElement qNewElement = doc->createElement(tr("Services"));
    currentNode.appendChild(qNewElement);

    QModelIndex parentIndex = view->indexAt(cp).parent();
    view->setExpanded(parentIndex,0);
    view->setExpanded(parentIndex,1);
    view->setExpanded(view->indexAt(cp),1);
}

void MainWindow::addAccessPoint(QPoint cp)
{
    qDebug()<<tr("Add AccessPoint Action");
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - AccessPoint"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(4,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)name")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(1,0,new QTableWidgetItem(tr("desc")));
    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(2,0,new QTableWidgetItem(tr("route")));
    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(3,0,new QTableWidgetItem(tr("clock")));
    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);

    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(1,1,new QTableWidgetItem(tr("")));
//    AttrTable->setCellWidget(2,1,new QCalendarWidget(this));
    AttrTable->setItem(2,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(3,1,new QTableWidgetItem(tr("")));

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    while(AttrDlg->exec() == QDialog::Accepted)
    {
        qDebug()<<tr("Attr Dialog Confirm");
        QDomElement qNewElement = doc->createElement(tr("AccessPoint"));

        if(AttrTable->item(0,1)->text()==tr(""))
        {
            QMessageBox::warning(NULL,tr("警告"),tr("name项为必需项，不能为空!"));
            continue;
        }

        qNewElement.setAttribute(tr("name"), AttrTable->item(0,1)->text());
        if((AttrTable->item(1,0))->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("desc"), AttrTable->item(1,1)->text());
        if((AttrTable->item(2,0))->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("route"), AttrTable->item(2,1)->text());
        if((AttrTable->item(3,0))->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("clock"), AttrTable->item(3,1)->text());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
        break;
    }
}

void MainWindow::addDynAssociation(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();
    qDebug()<<currentNode.toElement().tagName();

    QDomElement qNewElement = doc->createElement(tr("DynAssociation"));
    currentNode.appendChild(qNewElement);

    QModelIndex parentIndex = view->indexAt(cp).parent();
    view->setExpanded(parentIndex,0);
    view->setExpanded(parentIndex,1);
    view->setExpanded(view->indexAt(cp),1);
}

void MainWindow::addSettingGroups(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();
    qDebug()<<currentNode.toElement().tagName();

    QDomElement qNewElement = doc->createElement(tr("SettingGroups"));
    currentNode.appendChild(qNewElement);

    QModelIndex parentIndex = view->indexAt(cp).parent();
    view->setExpanded(parentIndex,0);
    view->setExpanded(parentIndex,1);
    view->setExpanded(view->indexAt(cp),1);
}

void MainWindow::addGetDirectory(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();
    qDebug()<<currentNode.toElement().tagName();

    QDomElement qNewElement = doc->createElement(tr("GetDirectory"));
    currentNode.appendChild(qNewElement);

    QModelIndex parentIndex = view->indexAt(cp).parent();
    view->setExpanded(parentIndex,0);
    view->setExpanded(parentIndex,1);
    view->setExpanded(view->indexAt(cp),1);
}

void MainWindow::addGetDataObjectDefinition(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();
    qDebug()<<currentNode.toElement().tagName();

    QDomElement qNewElement = doc->createElement(tr("GetDataObjectDefinition"));
    currentNode.appendChild(qNewElement);

    QModelIndex parentIndex = view->indexAt(cp).parent();
    view->setExpanded(parentIndex,0);
    view->setExpanded(parentIndex,1);
    view->setExpanded(view->indexAt(cp),1);
}

void MainWindow::addDataObjectDirectory(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();
    qDebug()<<currentNode.toElement().tagName();

    QDomElement qNewElement = doc->createElement(tr("DataObjectDirectory"));
    currentNode.appendChild(qNewElement);

    QModelIndex parentIndex = view->indexAt(cp).parent();
    view->setExpanded(parentIndex,0);
    view->setExpanded(parentIndex,1);
    view->setExpanded(view->indexAt(cp),1);
}

void MainWindow::addGetDataSetValue(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();
    qDebug()<<currentNode.toElement().tagName();

    QDomElement qNewElement = doc->createElement(tr("GetDataSetValue"));
    currentNode.appendChild(qNewElement);

    QModelIndex parentIndex = view->indexAt(cp).parent();
    view->setExpanded(parentIndex,0);
    view->setExpanded(parentIndex,1);
    view->setExpanded(view->indexAt(cp),1);
}

void MainWindow::addSetDataSetValue(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();
    qDebug()<<currentNode.toElement().tagName();

    QDomElement qNewElement = doc->createElement(tr("SetDataSetValue"));
    currentNode.appendChild(qNewElement);

    QModelIndex parentIndex = view->indexAt(cp).parent();
    view->setExpanded(parentIndex,0);
    view->setExpanded(parentIndex,1);
    view->setExpanded(view->indexAt(cp),1);
}

void MainWindow::addDataSetDirectory(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();
    qDebug()<<currentNode.toElement().tagName();

    QDomElement qNewElement = doc->createElement(tr("DataSetDirectory"));
    currentNode.appendChild(qNewElement);

    QModelIndex parentIndex = view->indexAt(cp).parent();
    view->setExpanded(parentIndex,0);
    view->setExpanded(parentIndex,1);
    view->setExpanded(view->indexAt(cp),1);
}

void MainWindow::addConfDataSet(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - ConfDataSet"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(2,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)max")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(1,0,new QTableWidgetItem(tr("maxAttributes")));
    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);

//    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
//    AttrTable->setCellWidget(0,1,new QLineEdit(tr("请输入数字"),this));
    AttrTable->setCellWidget(0,1,new QSpinBox(this));
//    ((QSpinBox*)(AttrTable->cellWidget(0,1)))->setMinimum(0);
//    ((QLineEdit*)(AttrTable->cellWidget(0,1)))->setValidator(new QIntValidator(1,65536,this));

//    AttrTable->setCellWidget(0,1,new QComboBox(this));
//    (QComboBox*)(AttrTable->cellWidget(0,1))->addItems(
//    AttrTable->setItem(1,1,new QTableWidgetItem(tr("")));
    AttrTable->setCellWidget(1,1,new QSpinBox(this));
//    ((QSpinBox*)(AttrTable->cellWidget(1,1)))->setMinimum(0);

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    if(AttrDlg->exec() == QDialog::Accepted)
    {
        QDomElement qNewElement = doc->createElement(tr("ConfDataSet"));

        qNewElement.setAttribute(tr("max"), ((QSpinBox*)(AttrTable->cellWidget(0,1)))->text());
        if((AttrTable->item(1,0))->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("maxAttributes"), ((QSpinBox*)(AttrTable->cellWidget(1,1)))->text());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
    }
}

void MainWindow::addDynDataSet(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - DynDataSet"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(2,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)max")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(1,0,new QTableWidgetItem(tr("maxAttributes")));
    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);

    AttrTable->setCellWidget(0,1,new QSpinBox(this));
    AttrTable->setCellWidget(1,1,new QSpinBox(this));

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    if(AttrDlg->exec() == QDialog::Accepted)
    {
        QDomElement qNewElement = doc->createElement(tr("DynDataSet"));

        qNewElement.setAttribute(tr("max"), ((QSpinBox*)(AttrTable->cellWidget(0,1)))->text());
        if((AttrTable->item(1,0))->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("maxAttributes"), ((QSpinBox*)(AttrTable->cellWidget(1,1)))->text());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
    }
}

void MainWindow::addReadWrite(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();
    qDebug()<<currentNode.toElement().tagName();

    QDomElement qNewElement = doc->createElement(tr("ReadWrite"));
    currentNode.appendChild(qNewElement);

    QModelIndex parentIndex = view->indexAt(cp).parent();
    view->setExpanded(parentIndex,0);
    view->setExpanded(parentIndex,1);
    view->setExpanded(view->indexAt(cp),1);
}

void MainWindow::addTimerActivatedControl(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();
    qDebug()<<currentNode.toElement().tagName();

    QDomElement qNewElement = doc->createElement(tr("TimerActivatedControl"));
    currentNode.appendChild(qNewElement);

    QModelIndex parentIndex = view->indexAt(cp).parent();
    view->setExpanded(parentIndex,0);
    view->setExpanded(parentIndex,1);
    view->setExpanded(view->indexAt(cp),1);
}

void MainWindow::addConfReportControl(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - ConfReportControl"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(1,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)max")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));

    AttrTable->setCellWidget(0,1,new QSpinBox(this));

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    if(AttrDlg->exec() == QDialog::Accepted)
    {
        QDomElement qNewElement = doc->createElement(tr("ConfReportControl"));

        qNewElement.setAttribute(tr("max"), ((QSpinBox*)(AttrTable->cellWidget(0,1)))->text());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
    }
}

void MainWindow::addGetCBValues(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();
    qDebug()<<currentNode.toElement().tagName();

    QDomElement qNewElement = doc->createElement(tr("GetCBValues"));
    currentNode.appendChild(qNewElement);

    QModelIndex parentIndex = view->indexAt(cp).parent();
    view->setExpanded(parentIndex,0);
    view->setExpanded(parentIndex,1);
    view->setExpanded(view->indexAt(cp),1);
}

void MainWindow::addConfLogControl(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - ConfLogControl"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(1,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)max")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));

    AttrTable->setCellWidget(0,1,new QSpinBox(this));

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    if(AttrDlg->exec() == QDialog::Accepted)
    {
        QDomElement qNewElement = doc->createElement(tr("ConfLogControl"));

        qNewElement.setAttribute(tr("max"), ((QSpinBox*)(AttrTable->cellWidget(0,1)))->text());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
    }
}

void MainWindow::addReportSettings(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - ReportSettings"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(7,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("cbname")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(1,0,new QTableWidgetItem(tr("datset")));
    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(2,0,new QTableWidgetItem(tr("rptID")));
    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(3,0,new QTableWidgetItem(tr("optFields")));
    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(4,0,new QTableWidgetItem(tr("bufTime")));
    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(4,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(5,0,new QTableWidgetItem(tr("trgOps")));
    AttrTable->item(5,0)->setFlags(AttrTable->item(5,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(5,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(6,0,new QTableWidgetItem(tr("intgPd")));
    AttrTable->item(6,0)->setFlags(AttrTable->item(6,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(6,0)->setCheckState(Qt::Unchecked);

    AttrTable->setCellWidget(0,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(0,1)))->addItems(QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix"));
    ((QComboBox*)(AttrTable->cellWidget(0,1)))->setCurrentIndex(2);
    AttrTable->setCellWidget(1,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(1,1)))->addItems(QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix"));
    ((QComboBox*)(AttrTable->cellWidget(1,1)))->setCurrentIndex(2);
    AttrTable->setCellWidget(2,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(2,1)))->addItems(QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix"));
    ((QComboBox*)(AttrTable->cellWidget(2,1)))->setCurrentIndex(2);
    AttrTable->setCellWidget(3,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(3,1)))->addItems(QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix"));
    ((QComboBox*)(AttrTable->cellWidget(3,1)))->setCurrentIndex(2);
    AttrTable->setCellWidget(4,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(4,1)))->addItems(QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix"));
    ((QComboBox*)(AttrTable->cellWidget(4,1)))->setCurrentIndex(2);
    AttrTable->setCellWidget(5,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(5,1)))->addItems(QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix"));
    ((QComboBox*)(AttrTable->cellWidget(5,1)))->setCurrentIndex(2);
    AttrTable->setCellWidget(6,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(6,1)))->addItems(QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix"));
    ((QComboBox*)(AttrTable->cellWidget(6,1)))->setCurrentIndex(2);

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    if(AttrDlg->exec() == QDialog::Accepted)
    {
        QDomElement qNewElement = doc->createElement(tr("ReportSettings"));

        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("cbname"), ((QComboBox*)(AttrTable->cellWidget(0,1)))->currentText());
        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("datset"), ((QComboBox*)(AttrTable->cellWidget(1,1)))->currentText());
        if(AttrTable->item(2,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("rptID"), ((QComboBox*)(AttrTable->cellWidget(2,1)))->currentText());
        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("optFields"), ((QComboBox*)(AttrTable->cellWidget(3,1)))->currentText());
        if(AttrTable->item(4,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("bufTime"), ((QComboBox*)(AttrTable->cellWidget(4,1)))->currentText());
        if(AttrTable->item(5,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("trgOps"), ((QComboBox*)(AttrTable->cellWidget(5,1)))->currentText());
        if(AttrTable->item(6,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("intgPd"), ((QComboBox*)(AttrTable->cellWidget(6,1)))->currentText());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
    }
}

void MainWindow::addLogSettings(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - LogSettings"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(5,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("cbname")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(1,0,new QTableWidgetItem(tr("datset")));
    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(2,0,new QTableWidgetItem(tr("logEna")));
    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(3,0,new QTableWidgetItem(tr("trgOps")));
    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(4,0,new QTableWidgetItem(tr("intgPd")));
    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(4,0)->setCheckState(Qt::Unchecked);

    AttrTable->setCellWidget(0,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(0,1)))->addItems(QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix"));
    ((QComboBox*)(AttrTable->cellWidget(0,1)))->setCurrentIndex(2);
    AttrTable->setCellWidget(1,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(1,1)))->addItems(QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix"));
    ((QComboBox*)(AttrTable->cellWidget(1,1)))->setCurrentIndex(2);
    AttrTable->setCellWidget(2,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(2,1)))->addItems(QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix"));
    ((QComboBox*)(AttrTable->cellWidget(2,1)))->setCurrentIndex(2);
    AttrTable->setCellWidget(3,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(3,1)))->addItems(QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix"));
    ((QComboBox*)(AttrTable->cellWidget(3,1)))->setCurrentIndex(2);
    AttrTable->setCellWidget(4,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(4,1)))->addItems(QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix"));
    ((QComboBox*)(AttrTable->cellWidget(4,1)))->setCurrentIndex(2);

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    if(AttrDlg->exec() == QDialog::Accepted)
    {
        QDomElement qNewElement = doc->createElement(tr("LogSettings"));

        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("cbname"), ((QComboBox*)(AttrTable->cellWidget(0,1)))->currentText());
        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("datset"), ((QComboBox*)(AttrTable->cellWidget(1,1)))->currentText());
        if(AttrTable->item(2,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("logEna"), ((QComboBox*)(AttrTable->cellWidget(2,1)))->currentText());
        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("trgOps"), ((QComboBox*)(AttrTable->cellWidget(3,1)))->currentText());
        if(AttrTable->item(4,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("intgPd"), ((QComboBox*)(AttrTable->cellWidget(4,1)))->currentText());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
    }
}

void MainWindow::addGSESettings(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - GSESettings"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(4,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("cbname")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(1,0,new QTableWidgetItem(tr("datset")));
    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(2,0,new QTableWidgetItem(tr("appID")));
    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(3,0,new QTableWidgetItem(tr("dataLabel")));
    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);

    AttrTable->setCellWidget(0,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(0,1)))->addItems(QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix"));
    ((QComboBox*)(AttrTable->cellWidget(0,1)))->setCurrentIndex(2);
    AttrTable->setCellWidget(1,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(1,1)))->addItems(QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix"));
    ((QComboBox*)(AttrTable->cellWidget(1,1)))->setCurrentIndex(2);
    AttrTable->setCellWidget(2,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(2,1)))->addItems(QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix"));
    ((QComboBox*)(AttrTable->cellWidget(2,1)))->setCurrentIndex(2);
    AttrTable->setCellWidget(3,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(3,1)))->addItems(QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix"));
    ((QComboBox*)(AttrTable->cellWidget(3,1)))->setCurrentIndex(2);

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    if(AttrDlg->exec() == QDialog::Accepted)
    {
        QDomElement qNewElement = doc->createElement(tr("GSESettings"));

        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("cbname"), ((QComboBox*)(AttrTable->cellWidget(0,1)))->currentText());
        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("datset"), ((QComboBox*)(AttrTable->cellWidget(1,1)))->currentText());
        if(AttrTable->item(2,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("appID"), ((QComboBox*)(AttrTable->cellWidget(2,1)))->currentText());
        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("dataLevel"), ((QComboBox*)(AttrTable->cellWidget(3,1)))->currentText());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
    }
}

void MainWindow::addSMVSettings(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - SMVSettings"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(5,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("cbname")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(1,0,new QTableWidgetItem(tr("datset")));
    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(2,0,new QTableWidgetItem(tr("svID")));
    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(3,0,new QTableWidgetItem(tr("optFields")));
    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(4,0,new QTableWidgetItem(tr("smpRate")));
    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(4,0)->setCheckState(Qt::Unchecked);

    AttrTable->setCellWidget(0,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(0,1)))->addItems(QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix"));
    ((QComboBox*)(AttrTable->cellWidget(0,1)))->setCurrentIndex(2);
    AttrTable->setCellWidget(1,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(1,1)))->addItems(QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix"));
    ((QComboBox*)(AttrTable->cellWidget(1,1)))->setCurrentIndex(2);
    AttrTable->setCellWidget(2,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(2,1)))->addItems(QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix"));
    ((QComboBox*)(AttrTable->cellWidget(2,1)))->setCurrentIndex(2);
    AttrTable->setCellWidget(3,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(3,1)))->addItems(QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix"));
    ((QComboBox*)(AttrTable->cellWidget(3,1)))->setCurrentIndex(2);
    AttrTable->setCellWidget(4,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(4,1)))->addItems(QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix"));
    ((QComboBox*)(AttrTable->cellWidget(4,1)))->setCurrentIndex(2);

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    if(AttrDlg->exec() == QDialog::Accepted)
    {
        QDomElement qNewElement = doc->createElement(tr("SMVSettings"));

        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("cbname"), ((QComboBox*)(AttrTable->cellWidget(0,1)))->currentText());
        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("datset"), ((QComboBox*)(AttrTable->cellWidget(1,1)))->currentText());
        if(AttrTable->item(2,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("svID"), ((QComboBox*)(AttrTable->cellWidget(2,1)))->currentText());
        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("optFields"), ((QComboBox*)(AttrTable->cellWidget(3,1)))->currentText());
        if(AttrTable->item(4,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("smpRate"), ((QComboBox*)(AttrTable->cellWidget(4,1)))->currentText());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
    }
}

void MainWindow::addGSEDir(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();
    qDebug()<<currentNode.toElement().tagName();

    QDomElement qNewElement = doc->createElement(tr("GSEDir"));
    currentNode.appendChild(qNewElement);

    QModelIndex parentIndex = view->indexAt(cp).parent();
    view->setExpanded(parentIndex,0);
    view->setExpanded(parentIndex,1);
    view->setExpanded(view->indexAt(cp),1);
}

void MainWindow::addGOOSE(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - GOOSE"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(1,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)max")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));

    AttrTable->setCellWidget(0,1,new QSpinBox(this));

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    if(AttrDlg->exec() == QDialog::Accepted)
    {
        QDomElement qNewElement = doc->createElement(tr("GOOSE"));

        qNewElement.setAttribute(tr("max"), ((QSpinBox*)(AttrTable->cellWidget(0,1)))->text());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
    }
}

void MainWindow::addGSSE(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - GSSE"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(1,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)max")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));

    AttrTable->setCellWidget(0,1,new QSpinBox(this));

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    if(AttrDlg->exec() == QDialog::Accepted)
    {
        QDomElement qNewElement = doc->createElement(tr("GSSE"));


        qNewElement.setAttribute(tr("max"), ((QSpinBox*)(AttrTable->cellWidget(0,1)))->text());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
    }
}

void MainWindow::addFileHandling(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();
    qDebug()<<currentNode.toElement().tagName();

    QDomElement qNewElement = doc->createElement(tr("FileHandling"));
    currentNode.appendChild(qNewElement);

    QModelIndex parentIndex = view->indexAt(cp).parent();
    view->setExpanded(parentIndex,0);
    view->setExpanded(parentIndex,1);
    view->setExpanded(view->indexAt(cp),1);
}

void MainWindow::addConfLNs(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - ConfLNs"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(2,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("fixPrefix")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(1,0,new QTableWidgetItem(tr("fixLnInst")));
    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);

    AttrTable->setCellWidget(0,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(0,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
    ((QComboBox*)(AttrTable->cellWidget(0,1)))->setCurrentIndex(1);
    AttrTable->setCellWidget(1,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(1,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
    ((QComboBox*)(AttrTable->cellWidget(1,1)))->setCurrentIndex(1);
    AttrTable->setCellWidget(2,1,new QComboBox(this));

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    if(AttrDlg->exec() == QDialog::Accepted)
    {
        QDomElement qNewElement = doc->createElement(tr("ConfLNs"));

        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("fixPrefix"), ((QComboBox*)(AttrTable->cellWidget(0,1)))->currentText());
        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("fixLnInst"), ((QComboBox*)(AttrTable->cellWidget(1,1)))->currentText());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
     }
}

void MainWindow::addSGEdit(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();
    qDebug()<<currentNode.toElement().tagName();

    QDomElement qNewElement = doc->createElement(tr("SGEdit"));
    currentNode.appendChild(qNewElement);

    QModelIndex parentIndex = view->indexAt(cp).parent();
    view->setExpanded(parentIndex,0);
    view->setExpanded(parentIndex,1);
    view->setExpanded(view->indexAt(cp),1);
}

void MainWindow::addConfSG(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();
    qDebug()<<currentNode.toElement().tagName();

    QDomElement qNewElement = doc->createElement(tr("ConfSG"));
    currentNode.appendChild(qNewElement);

    QModelIndex parentIndex = view->indexAt(cp).parent();
    view->setExpanded(parentIndex,0);
    view->setExpanded(parentIndex,1);
    view->setExpanded(view->indexAt(cp),1);
}

void MainWindow::addServer(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - Server"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(2,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("desc")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(1,0,new QTableWidgetItem(tr("timeout")));
    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);

    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
    AttrTable->setCellWidget(1,1,new QSpinBox(this));

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    if(AttrDlg->exec() == QDialog::Accepted)
    {
        QDomElement qNewElement = doc->createElement(tr("Server"));
        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("desc"), AttrTable->item(0,1)->text());
        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("timeout"), ((QSpinBox*)(AttrTable->cellWidget(1,1)))->text());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);

    }
}

void MainWindow::addLN(QPoint cp)
{
    qDebug()<<"Add LN";
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - LN"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(5,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)lnClass")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(1,0,new QTableWidgetItem(tr("(*)inst")));
    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(2,0,new QTableWidgetItem(tr("(*)lnType")));
    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(3,0,new QTableWidgetItem(tr("prefix")));
    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(4,0,new QTableWidgetItem(tr("desc")));
    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(4,0)->setCheckState(Qt::Unchecked);

    AttrTable->setCellWidget(0,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(0,1)))->addItems(lnClass);
    AttrTable->setCellWidget(1,1,new QSpinBox(this));
    AttrTable->setCellWidget(2,1,new QComboBox(this));
    AttrTable->setItem(3,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(4,1,new QTableWidgetItem(tr("")));

    QDomNode SCLNode;
    if(currentNode.parentNode().parentNode().parentNode().toElement().tagName() == tr("IED"))
    {
        SCLNode = currentNode.parentNode().parentNode().parentNode().parentNode();
    }
    else if(currentNode.parentNode().parentNode().toElement().tagName() == tr("IED"))
        SCLNode = currentNode.parentNode().parentNode().parentNode();

    //if(IEDNode.nextSiblingElement("DataTypeTemplates"))

    QDomNode TypeNode;
    for(int i=0; i<SCLNode.childNodes().count(); i++)
    {
        if(SCLNode.childNodes().at(i).toElement().tagName() == tr("DataTypeTemplates"))
        {
            TypeNode = SCLNode.childNodes().at(i);
            qDebug()<<TypeNode.toElement().tagName();
            for(int i=0; i<TypeNode.childNodes().count(); i++)
            {
                if(TypeNode.childNodes().at(i).toElement().tagName() == tr("LNodeType"))
                {
                    QStringList lnType;
                    QDomNode LNodeTypeNode = TypeNode.childNodes().at(i);

                    qDebug()<<LNodeTypeNode.toElement().tagName();
                    if(LNodeTypeNode.attributes().contains(tr("id")))
                    {
                        qDebug()<<LNodeTypeNode.attributes().namedItem("id").toAttr().value();
                        lnType.append(LNodeTypeNode.attributes().namedItem("id").toAttr().value());
                    }
                    ((QComboBox*)(AttrTable->cellWidget(2,1)))->addItems(lnType);
                }
            }
        }
    }

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    if(AttrDlg->exec() == QDialog::Accepted)
    {
        QDomElement qNewElement = doc->createElement(tr("LN"));
        qNewElement.setAttribute(tr("lnClass"), ((QComboBox*)(AttrTable->cellWidget(0,1)))->currentText());
        qNewElement.setAttribute(tr("inst"), ((QSpinBox*)(AttrTable->cellWidget(1,1)))->text());
        qNewElement.setAttribute(tr("lnType"), ((QComboBox*)(AttrTable->cellWidget(2,1)))->currentText());
        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("prefix"), AttrTable->item(3,1)->text());
        if(AttrTable->item(4,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("desc"), AttrTable->item(4,1)->text());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);

    }
}

void MainWindow::addAuthentication(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - Authentication"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(5,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("none")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(1,0,new QTableWidgetItem(tr("password")));
    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(2,0,new QTableWidgetItem(tr("weak")));
    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(3,0,new QTableWidgetItem(tr("strong")));
    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(4,0,new QTableWidgetItem(tr("certificate")));
    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(4,0)->setCheckState(Qt::Unchecked);

    AttrTable->setCellWidget(0,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(0,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
    ((QComboBox*)(AttrTable->cellWidget(0,1)))->setCurrentIndex(0);
    AttrTable->setCellWidget(1,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(1,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
    ((QComboBox*)(AttrTable->cellWidget(1,1)))->setCurrentIndex(1);
    AttrTable->setCellWidget(2,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(2,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
    ((QComboBox*)(AttrTable->cellWidget(2,1)))->setCurrentIndex(1);
    AttrTable->setCellWidget(3,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(3,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
    ((QComboBox*)(AttrTable->cellWidget(3,1)))->setCurrentIndex(1);
    AttrTable->setCellWidget(4,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(4,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
    ((QComboBox*)(AttrTable->cellWidget(4,1)))->setCurrentIndex(1);

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    if(AttrDlg->exec() == QDialog::Accepted)
    {
        QDomElement qNewElement = doc->createElement(tr("Authentication"));

        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("none"), ((QComboBox*)(AttrTable->cellWidget(0,1)))->currentText());
        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("password"), ((QComboBox*)(AttrTable->cellWidget(1,1)))->currentText());
        if(AttrTable->item(2,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("weak"), ((QComboBox*)(AttrTable->cellWidget(2,1)))->currentText());
        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("strong"), ((QComboBox*)(AttrTable->cellWidget(3,1)))->currentText());
        if(AttrTable->item(4,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("certificate"), ((QComboBox*)(AttrTable->cellWidget(4,1)))->currentText());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
    }
}

void MainWindow::addLDevice(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - LDevice"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(2,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)inst")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));

    AttrTable->setItem(1,0,new QTableWidgetItem(tr("desc")));
    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));

    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(1,1,new QTableWidgetItem(tr("")));

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    while(AttrDlg->exec() == QDialog::Accepted)
    {
        QDomElement qNewElement = doc->createElement(tr("LDevice"));

        if(AttrTable->item(0,1)->text()==tr(""))
        {
            QMessageBox::warning(NULL,tr("警告"),tr("inst项为必需项，不能为空!"));
            continue;
        }

        qNewElement.setAttribute(tr("inst"), AttrTable->item(0,1)->text());
        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("desc"), AttrTable->item(1,1)->text());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
        break;
    }
}

void MainWindow::addAssociation(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - Association"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(7,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)kind")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(1,0,new QTableWidgetItem(tr("associationID")));
    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(2,0,new QTableWidgetItem(tr("(*)lnInst")));
    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(3,0,new QTableWidgetItem(tr("(*)lnClass")));
    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(4,0,new QTableWidgetItem(tr("prefix")));
    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(4,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(5,0,new QTableWidgetItem(tr("(*)iedName")));
    AttrTable->item(5,0)->setFlags(AttrTable->item(5,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(6,0,new QTableWidgetItem(tr("(*)ldInst")));
    AttrTable->item(6,0)->setFlags(AttrTable->item(6,0)->flags() & (~Qt::ItemIsEditable));

    AttrTable->setCellWidget(0,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(0,1)))->addItems(QStringList()<<tr("pre-established")<<tr("predefined"));
    AttrTable->setItem(1,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(2,1,new QTableWidgetItem(tr("")));
    AttrTable->setCellWidget(3,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(3,1)))->addItems(lnClass);
    AttrTable->setItem(4,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(5,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(6,1,new QTableWidgetItem(tr("")));

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    while(AttrDlg->exec() == QDialog::Accepted)
    {
        QDomElement qNewElement = doc->createElement(tr("Association"));

        if(AttrTable->item(2,1)->text()==tr(""))
        {
            QMessageBox::warning(NULL,tr("警告"),tr("lnInst项为必需项，不能为空!"));
            continue;
        }
        if(AttrTable->item(5,1)->text()==tr(""))
        {
            QMessageBox::warning(NULL,tr("警告"),tr("iedName项为必需项，不能为空!"));
            continue;
        }
        if(AttrTable->item(6,1)->text()==tr(""))
        {
            QMessageBox::warning(NULL,tr("警告"),tr("ldInst项为必需项，不能为空!"));
            continue;
        }

        qNewElement.setAttribute(tr("kind"), ((QComboBox*)(AttrTable->cellWidget(0,1)))->currentText());
        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("associationID"), AttrTable->item(1,1)->text());
        qNewElement.setAttribute(tr("lnInst"), AttrTable->item(2,1)->text());
        qNewElement.setAttribute(tr("lnClss"), ((QComboBox*)(AttrTable->cellWidget(3,1)))->currentText());
        if(AttrTable->item(4,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("prefix"), AttrTable->item(4,1)->text());
        qNewElement.setAttribute(tr("iedName"), AttrTable->item(5,1)->text());
        qNewElement.setAttribute(tr("ldInst"), AttrTable->item(6,1)->text());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
        break;
    }
}

void MainWindow::addLN0(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - LN0"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(4,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)lnClass")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(1,0,new QTableWidgetItem(tr("(*)inst")));
    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(2,0,new QTableWidgetItem(tr("(*)lnType")));
    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(3,0,new QTableWidgetItem(tr("desc")));
    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);

    AttrTable->setItem(0,1,new QTableWidgetItem(tr("LLN0")));
    AttrTable->item(0,1)->setFlags(AttrTable->item(0,1)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setCellWidget(1,1,new QSpinBox(this));
    AttrTable->setCellWidget(2,1,new QComboBox(this));
    AttrTable->setItem(3,1,new QTableWidgetItem(tr("")));

    QDomNode SCLNode;
    if(currentNode.parentNode().parentNode().parentNode().toElement().tagName() == tr("IED"))
    {
        SCLNode = currentNode.parentNode().parentNode().parentNode().parentNode();
    }
    else if(currentNode.parentNode().parentNode().toElement().tagName() == tr("IED"))
        SCLNode = currentNode.parentNode().parentNode().parentNode();

    //if(IEDNode.nextSiblingElement("DataTypeTemplates"))

    QDomNode TypeNode;
    for(int i=0; i<SCLNode.childNodes().count(); i++)
    {
        if(SCLNode.childNodes().at(i).toElement().tagName() == tr("DataTypeTemplates"))
        {
            TypeNode = SCLNode.childNodes().at(i);
            qDebug()<<TypeNode.toElement().tagName();
            for(int i=0; i<TypeNode.childNodes().count(); i++)
            {
                if(TypeNode.childNodes().at(i).toElement().tagName() == tr("LNodeType"))
                {
                    QStringList lnType;
                    QDomNode LNodeTypeNode = TypeNode.childNodes().at(i);

                    qDebug()<<LNodeTypeNode.toElement().tagName();
                    if(LNodeTypeNode.attributes().contains(tr("id")))
                    {
                        qDebug()<<LNodeTypeNode.attributes().namedItem("id").toAttr().value();
                        lnType.append(LNodeTypeNode.attributes().namedItem("id").toAttr().value());
                    }
                    ((QComboBox*)(AttrTable->cellWidget(2,1)))->addItems(lnType);
                }
            }
        }
    }

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    if(AttrDlg->exec() == QDialog::Accepted)
    {
        QDomElement qNewElement = doc->createElement(tr("LN0"));

        qNewElement.setAttribute(tr("lnClass"), AttrTable->item(0,1)->text());
        qNewElement.setAttribute(tr("inst"), ((QSpinBox*)(AttrTable->cellWidget(1,1)))->text());
        qNewElement.setAttribute(tr("lnType"), ((QComboBox*)(AttrTable->cellWidget(2,1)))->currentText());
        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("desc"), AttrTable->item(3,1)->text());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
    }
}

void MainWindow::addAccessControl(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();
    qDebug()<<currentNode.toElement().tagName();

    QDomElement qNewElement = doc->createElement(tr("AccessControl"));
    currentNode.appendChild(qNewElement);

    QModelIndex parentIndex = view->indexAt(cp).parent();
    view->setExpanded(parentIndex,0);
    view->setExpanded(parentIndex,1);
    view->setExpanded(view->indexAt(cp),1);
}

void MainWindow::addGSEControl(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - GSEControl"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(6,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("type")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(1,0,new QTableWidgetItem(tr("(*)appID")));
    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(2,0,new QTableWidgetItem(tr("confRev")));
    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(3,0,new QTableWidgetItem(tr("(*)datSet")));
    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(4,0,new QTableWidgetItem(tr("(*)name")));
    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(5,0,new QTableWidgetItem(tr("desc")));
    AttrTable->item(5,0)->setFlags(AttrTable->item(5,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(5,0)->setCheckState(Qt::Unchecked);

    AttrTable->setCellWidget(0,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(0,1)))->addItems(QStringList()<<tr("GSSE")<<tr("GOOSE"));
    AttrTable->setItem(1,1,new QTableWidgetItem(tr("")));
    AttrTable->setCellWidget(2,1,new QSpinBox(this));
    AttrTable->setCellWidget(3,1,new QComboBox(this));
    AttrTable->setItem(4,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(5,1,new QTableWidgetItem(tr("")));

    QStringList DatSet;
    for(int i=0; i<currentNode.childNodes().count(); i++)
    {
        if(currentNode.childNodes().at(i).toElement().tagName() == tr("DataSet"))
        {
            QDomNode DataSetNode = currentNode.childNodes().at(i);

            if(DataSetNode.attributes().contains(tr("name")))
                DatSet.append(DataSetNode.attributes().namedItem("name").toAttr().value());
        }
    }
    if(DatSet.isEmpty())
        DatSet.append(tr(""));
    ((QComboBox*)(AttrTable->cellWidget(3,1)))->addItems(DatSet);

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    while(AttrDlg->exec() == QDialog::Accepted)
    {
        QDomElement qNewElement = doc->createElement(tr("GSEControl"));

        if(AttrTable->item(1,1)->text()==tr(""))
        {
            QMessageBox::warning(NULL,tr("警告"),tr("appID项为必需项，不能为空!"));
            continue;
        }

        if(AttrTable->item(4,1)->text()==tr(""))
        {
            QMessageBox::warning(NULL,tr("警告"),tr("name项为必需项，不能为空!"));
            continue;
        }

        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("type"), ((QComboBox*)(AttrTable->cellWidget(0,1)))->currentText());
        qNewElement.setAttribute(tr("appID"), AttrTable->item(1,1)->text());
        if(AttrTable->item(2,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("confRev"), ((QSpinBox*)(AttrTable->cellWidget(2,1)))->text());
        qNewElement.setAttribute(tr("datSet"), ((QComboBox*)(AttrTable->cellWidget(3,1)))->currentText());
        qNewElement.setAttribute(tr("name"), AttrTable->item(4,1)->text());
        if(AttrTable->item(5,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("desc"), AttrTable->item(5,1)->text());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
        break;
    }
}

void MainWindow::addSampleValueControl(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - SampleValueControl"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(8,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)smvID")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(1,0,new QTableWidgetItem(tr("multicast")));
    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(2,0,new QTableWidgetItem(tr("(*)smpRate")));
    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(3,0,new QTableWidgetItem(tr("(*)nofASDU")));
    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(4,0,new QTableWidgetItem(tr("confRev")));
    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(4,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(5,0,new QTableWidgetItem(tr("(*)datSet")));
    AttrTable->item(5,0)->setFlags(AttrTable->item(5,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(6,0,new QTableWidgetItem(tr("(*)name")));
    AttrTable->item(6,0)->setFlags(AttrTable->item(6,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(7,0,new QTableWidgetItem(tr("desc")));
    AttrTable->item(7,0)->setFlags(AttrTable->item(7,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(7,0)->setCheckState(Qt::Unchecked);

    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
    AttrTable->setCellWidget(1,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(1,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
    AttrTable->setCellWidget(2,1,new QSpinBox(this));
    AttrTable->setCellWidget(3,1,new QSpinBox(this));
    AttrTable->setCellWidget(4,1,new QSpinBox(this));
    AttrTable->setCellWidget(5,1,new QComboBox(this));
    AttrTable->setItem(6,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(7,1,new QTableWidgetItem(tr("")));

    QStringList DatSet;
    for(int i=0; i<currentNode.childNodes().count(); i++)
    {
        if(currentNode.childNodes().at(i).toElement().tagName() == tr("DataSet"))
        {
            QDomNode DataSetNode = currentNode.childNodes().at(i);

            if(DataSetNode.attributes().contains(tr("name")))
                DatSet.append(DataSetNode.attributes().namedItem("name").toAttr().value());
        }
    }
    if(DatSet.isEmpty())
        DatSet.append(tr(" "));
    ((QComboBox*)(AttrTable->cellWidget(5,1)))->addItems(DatSet);

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    while(AttrDlg->exec() == QDialog::Accepted)
    {
        QDomElement qNewElement = doc->createElement(tr("SampleValueControl"));

        if(AttrTable->item(0,1)->text()==tr(""))
        {
            QMessageBox::warning(NULL,tr("警告"),tr("smvID项为必需项，不能为空!"));
            continue;
        }

        if(AttrTable->item(6,1)->text()==tr(""))
        {
            QMessageBox::warning(NULL,tr("警告"),tr("name项为必需项，不能为空!"));
            continue;
        }


        qNewElement.setAttribute(tr("smvID"), AttrTable->item(0,1)->text());
        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("multicast"), ((QComboBox*)(AttrTable->cellWidget(1,1)))->currentText());
        qNewElement.setAttribute(tr("smpRate"), ((QSpinBox*)(AttrTable->cellWidget(2,1)))->text());
        qNewElement.setAttribute(tr("nofASDU"), ((QSpinBox*)(AttrTable->cellWidget(3,1)))->text());
        if(AttrTable->item(4,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("confRev"), ((QSpinBox*)(AttrTable->cellWidget(4,1)))->text());
        qNewElement.setAttribute(tr("datSet"), ((QComboBox*)(AttrTable->cellWidget(5,1)))->currentText());
        qNewElement.setAttribute(tr("name"), AttrTable->item(6,1)->text());
        if(AttrTable->item(7,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("desc"), AttrTable->item(7,1)->text());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
        break;
    }
}

void MainWindow::addSettingControl(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - SettingControl"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(3,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)numOfSGs")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(1,0,new QTableWidgetItem(tr("actSG")));
    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(2,0,new QTableWidgetItem(tr("desc")));
    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);

    AttrTable->setCellWidget(0,1,new QSpinBox(this));
    AttrTable->setCellWidget(1,1,new QSpinBox(this));
    ((QSpinBox*)(AttrTable->cellWidget(1,1)))->setValue(1);
    AttrTable->setItem(2,1,new QTableWidgetItem(tr("")));

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    if(AttrDlg->exec() == QDialog::Accepted)
    {
        QDomElement qNewElement = doc->createElement(tr("SettingControl"));

        qNewElement.setAttribute(tr("numOfSGs"), ((QSpinBox*)(AttrTable->cellWidget(0,1)))->text());
        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("actSG"), ((QSpinBox*)(AttrTable->cellWidget(1,1)))->text());
        if(AttrTable->item(2,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("desc"), AttrTable->item(2,1)->text());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);

    }
}

void MainWindow::addSCLControl(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - SettingControl"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(1,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("desc")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);

    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    if(AttrDlg->exec() == QDialog::Accepted)
    {
        QDomElement qNewElement = doc->createElement(tr("SettingControl"));

        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("desc"), AttrTable->item(0,1)->text());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
    }
}

void MainWindow::addLog(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();
    qDebug()<<currentNode.toElement().tagName();

    QDomElement qNewElement = doc->createElement(tr("Log"));
    currentNode.appendChild(qNewElement);

    QModelIndex parentIndex = view->indexAt(cp).parent();
    view->setExpanded(parentIndex,0);
    view->setExpanded(parentIndex,1);
    view->setExpanded(view->indexAt(cp),1);

}

void MainWindow::addDataSet(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - DataSet"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(2,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)name")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(1,0,new QTableWidgetItem(tr("desc")));
    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);

    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(1,1,new QTableWidgetItem(tr("")));

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    while(AttrDlg->exec() == QDialog::Accepted)
    {
        QDomElement qNewElement = doc->createElement(tr("DataSet"));

        if(AttrTable->item(0,1)->text()==tr(""))
        {
            QMessageBox::warning(NULL,tr("警告"),tr("name项为必需项，不能为空!"));
            continue;
        }

        qNewElement.setAttribute(tr("name"), AttrTable->item(0,1)->text());
        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("desc"), AttrTable->item(1,1)->text());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);

        break;
    }
}

void MainWindow::addReportControl(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - ReportControl"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(8,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)rptID")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(1,0,new QTableWidgetItem(tr("(*)confRev")));
    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(2,0,new QTableWidgetItem(tr("buffered")));
    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(3,0,new QTableWidgetItem(tr("bufTime")));
    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(4,0,new QTableWidgetItem(tr("intgPd")));
    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(4,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(5,0,new QTableWidgetItem(tr("(*)datSet")));
    AttrTable->item(5,0)->setFlags(AttrTable->item(5,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(6,0,new QTableWidgetItem(tr("(*)name")));
    AttrTable->item(6,0)->setFlags(AttrTable->item(6,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(7,0,new QTableWidgetItem(tr("desc")));
    AttrTable->item(7,0)->setFlags(AttrTable->item(7,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(7,0)->setCheckState(Qt::Unchecked);

    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
    AttrTable->setCellWidget(1,1,new QSpinBox(this));
    AttrTable->setCellWidget(2,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(2,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
    ((QComboBox*)(AttrTable->cellWidget(2,1)))->setCurrentIndex(1);
    AttrTable->setCellWidget(3,1,new QSpinBox(this));
    AttrTable->setCellWidget(4,1,new QSpinBox(this));
    AttrTable->setCellWidget(5,1,new QComboBox(this));
    AttrTable->setItem(6,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(7,1,new QTableWidgetItem(tr("")));

    QStringList DatSet;
    for(int i=0; i<currentNode.childNodes().count(); i++)
    {
        if(currentNode.childNodes().at(i).toElement().tagName() == tr("DataSet"))
        {
            QDomNode DataSetNode = currentNode.childNodes().at(i);

            if(DataSetNode.attributes().contains(tr("name")))
                DatSet.append(DataSetNode.attributes().namedItem("name").toAttr().value());
        }
    }
    if(DatSet.isEmpty())
        DatSet.append(tr(" "));
    ((QComboBox*)(AttrTable->cellWidget(5,1)))->addItems(DatSet);

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    while(AttrDlg->exec() == QDialog::Accepted)
    {
        QDomElement qNewElement = doc->createElement(tr("ReportControl"));

        if(AttrTable->item(0,1)->text()==tr(""))
        {
            QMessageBox::warning(NULL,tr("警告"),tr("rptID项为必需项，不能为空!"));
            continue;
        }

        if(AttrTable->item(6,1)->text()==tr(""))
        {
            QMessageBox::warning(NULL,tr("警告"),tr("name项为必需项，不能为空!"));
            continue;
        }

        qNewElement.setAttribute(tr("rptID"), AttrTable->item(0,1)->text());
        qNewElement.setAttribute(tr("confRev"), ((QSpinBox*)(AttrTable->cellWidget(1,1)))->text());
        if(AttrTable->item(2,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("buffered"), ((QSpinBox*)(AttrTable->cellWidget(2,1)))->text());
        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("bufTime"), ((QSpinBox*)(AttrTable->cellWidget(3,1)))->text());
        if(AttrTable->item(4,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("intgPd"), ((QSpinBox*)(AttrTable->cellWidget(4,1)))->text());
        qNewElement.setAttribute(tr("datSet"), ((QComboBox*)(AttrTable->cellWidget(5,1)))->currentText());
        qNewElement.setAttribute(tr("name"), AttrTable->item(6,1)->text());
        if(AttrTable->item(7,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("desc"), AttrTable->item(7,1)->text());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
        break;
    }
}

void MainWindow::addLogControl(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - LogControl"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(7,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)logName")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(1,0,new QTableWidgetItem(tr("logEna")));
    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(2,0,new QTableWidgetItem(tr("reasonCode")));
    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(3,0,new QTableWidgetItem(tr("intgPd")));
    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(4,0,new QTableWidgetItem(tr("(*)datSet")));
    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(5,0,new QTableWidgetItem(tr("(*)name")));
    AttrTable->item(5,0)->setFlags(AttrTable->item(5,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(6,0,new QTableWidgetItem(tr("desc")));
    AttrTable->item(6,0)->setFlags(AttrTable->item(6,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(6,0)->setCheckState(Qt::Unchecked);

    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
    AttrTable->setCellWidget(1,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(1,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
    AttrTable->setCellWidget(2,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(2,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
    AttrTable->setCellWidget(3,1,new QSpinBox(this));
    AttrTable->setCellWidget(4,1,new QComboBox(this));
    AttrTable->setItem(5,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(6,1,new QTableWidgetItem(tr("")));

    QStringList DatSet;
    for(int i=0; i<currentNode.childNodes().count(); i++)
    {
        if(currentNode.childNodes().at(i).toElement().tagName() == tr("DataSet"))
        {
            QDomNode DataSetNode = currentNode.childNodes().at(i);

            if(DataSetNode.attributes().contains(tr("name")))
                DatSet.append(DataSetNode.attributes().namedItem("name").toAttr().value());
        }
    }
    if(DatSet.isEmpty())
        DatSet.append(tr(""));
    ((QComboBox*)(AttrTable->cellWidget(4,1)))->addItems(DatSet);

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    while(AttrDlg->exec() == QDialog::Accepted)
    {
        QDomElement qNewElement = doc->createElement(tr("LogControl"));

        if(AttrTable->item(0,1)->text()==tr(""))
        {
            QMessageBox::warning(NULL,tr("警告"),tr("logName项为必需项，不能为空!"));
            continue;
        }

        if(AttrTable->item(5,1)->text()==tr(""))
        {
            QMessageBox::warning(NULL,tr("警告"),tr("name项为必需项，不能为空!"));
            continue;
        }

        qNewElement.setAttribute(tr("logName"), AttrTable->item(0,1)->text());
        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("logEna"), ((QComboBox*)(AttrTable->cellWidget(1,1)))->currentText());
        if(AttrTable->item(2,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("reasonCode"), ((QComboBox*)(AttrTable->cellWidget(2,1)))->currentText());
        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("intgPd"), ((QSpinBox*)(AttrTable->cellWidget(3,1)))->text());
        qNewElement.setAttribute(tr("datSet"), ((QComboBox*)(AttrTable->cellWidget(4,1)))->currentText());
        qNewElement.setAttribute(tr("name"), AttrTable->item(5,1)->text());
        if(AttrTable->item(6,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("desc"), AttrTable->item(6,1)->text());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
        break;
    }
}

void MainWindow::addDOI(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - DOI"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(4,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)name")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(1,0,new QTableWidgetItem(tr("ix")));
    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(2,0,new QTableWidgetItem(tr("accessControl")));
    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(3,0,new QTableWidgetItem(tr("desc")));
    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);

    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
    AttrTable->setCellWidget(1,1,new QSpinBox(this));
    AttrTable->setItem(2,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(3,1,new QTableWidgetItem(tr("")));

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    while(AttrDlg->exec() == QDialog::Accepted)
    {
        QDomElement qNewElement = doc->createElement(tr("DOI"));

        if(AttrTable->item(0,1)->text()==tr(""))
        {
            QMessageBox::warning(NULL,tr("警告"),tr("name项为必需项，不能为空!"));
            continue;
        }

        qNewElement.setAttribute(tr("name"), AttrTable->item(0,1)->text());
        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("ix"), ((QSpinBox*)(AttrTable->cellWidget(1,1)))->text());
        if(AttrTable->item(2,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("accessControl"), AttrTable->item(2,1)->text());
        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("desc"), AttrTable->item(3,1)->text());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
        break;
    }
}

void MainWindow::addInputs(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - Inputs"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(1,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("desc")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);

    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    if(AttrDlg->exec() == QDialog::Accepted)
    {
        QDomElement qNewElement = doc->createElement(tr("Inputs"));

        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("desc"), AttrTable->item(0,1)->text());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
    }
}

void MainWindow::addIEDName(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();
    qDebug()<<currentNode.toElement().tagName();

    QDomElement qNewElement = doc->createElement(tr("IEDName"));
    currentNode.appendChild(qNewElement);

    QModelIndex parentIndex = view->indexAt(cp).parent();
    view->setExpanded(parentIndex,0);
    view->setExpanded(parentIndex,1);
    view->setExpanded(view->indexAt(cp),1);
}

void MainWindow::addSmvOpts(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - SmvOpts"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(5,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("refreshTime")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(1,0,new QTableWidgetItem(tr("sampleSynchronized")));
    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(2,0,new QTableWidgetItem(tr("sampleRate")));
    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(3,0,new QTableWidgetItem(tr("security")));
    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(4,0,new QTableWidgetItem(tr("dataRef")));
    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(4,0)->setCheckState(Qt::Unchecked);

    AttrTable->setCellWidget(0,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(0,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
    ((QComboBox*)(AttrTable->cellWidget(0,1)))->setCurrentIndex(1);
    AttrTable->setCellWidget(1,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(1,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
    ((QComboBox*)(AttrTable->cellWidget(1,1)))->setCurrentIndex(1);
    AttrTable->setCellWidget(2,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(2,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
    ((QComboBox*)(AttrTable->cellWidget(2,1)))->setCurrentIndex(1);
    AttrTable->setCellWidget(3,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(3,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
    ((QComboBox*)(AttrTable->cellWidget(3,1)))->setCurrentIndex(1);
    AttrTable->setCellWidget(4,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(4,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
    ((QComboBox*)(AttrTable->cellWidget(4,1)))->setCurrentIndex(1);

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    if(AttrDlg->exec() == QDialog::Accepted)
    {
        QDomElement qNewElement = doc->createElement(tr("SmvOpts"));

        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("refreshTime"), ((QComboBox*)(AttrTable->cellWidget(0,1)))->currentText());
        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("sampleSynchronized"), ((QComboBox*)(AttrTable->cellWidget(1,1)))->currentText());
        if(AttrTable->item(2,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("sampleRate"), ((QComboBox*)(AttrTable->cellWidget(2,1)))->currentText());
        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("security"), ((QComboBox*)(AttrTable->cellWidget(3,1)))->currentText());
        if(AttrTable->item(4,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("dataRef"), ((QComboBox*)(AttrTable->cellWidget(4,1)))->currentText());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
    }
}

void MainWindow::addFCDA(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - FCDA"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(7,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("ldInst")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(1,0,new QTableWidgetItem(tr("prefix")));
    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(2,0,new QTableWidgetItem(tr("lnClass")));
    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(3,0,new QTableWidgetItem(tr("lnInst")));
    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(4,0,new QTableWidgetItem(tr("doName")));
    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(4,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(4,0,new QTableWidgetItem(tr("daName")));
    AttrTable->item(5,0)->setFlags(AttrTable->item(5,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(5,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(6,0,new QTableWidgetItem(tr("fc")));
    AttrTable->item(6,0)->setFlags(AttrTable->item(6,0)->flags() & (~Qt::ItemIsEditable));

    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(1,1,new QTableWidgetItem(tr("")));
    AttrTable->setCellWidget(2,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(2,1)))->addItems(lnClass);
    AttrTable->setItem(3,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(4,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(5,1,new QTableWidgetItem(tr("")));
    AttrTable->setCellWidget(6,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(6,1)))->addItems(fcEnum);

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    if(AttrDlg->exec() == QDialog::Accepted)
    {
        QDomElement qNewElement = doc->createElement(tr("FCDA"));

        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("ldInst"), AttrTable->item(0,1)->text());
        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("prefix"), AttrTable->item(1,1)->text());
        if(AttrTable->item(2,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("lnClass"), ((QComboBox*)(AttrTable->cellWidget(2,1)))->currentText());
        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("lnInst"), AttrTable->item(3,1)->text());
        if(AttrTable->item(4,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("doName"), AttrTable->item(4,1)->text());
        if(AttrTable->item(5,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("daName"), AttrTable->item(5,1)->text());
        qNewElement.setAttribute(tr("fc"), ((QComboBox*)(AttrTable->cellWidget(5,1)))->currentText());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
    }
}

void MainWindow::addOptFields(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - OptFields"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(9,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("seqNum")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(1,0,new QTableWidgetItem(tr("timeStamp")));
    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(2,0,new QTableWidgetItem(tr("dataSet")));
    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(3,0,new QTableWidgetItem(tr("reasonCode")));
    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(4,0,new QTableWidgetItem(tr("dataRef")));
    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(4,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(5,0,new QTableWidgetItem(tr("bufOvfl")));
    AttrTable->item(5,0)->setFlags(AttrTable->item(5,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(5,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(6,0,new QTableWidgetItem(tr("entryID")));
    AttrTable->item(6,0)->setFlags(AttrTable->item(6,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(6,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(7,0,new QTableWidgetItem(tr("configRef")));
    AttrTable->item(7,0)->setFlags(AttrTable->item(7,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(7,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(8,0,new QTableWidgetItem(tr("segmentation")));
    AttrTable->item(8,0)->setFlags(AttrTable->item(8,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(8,0)->setCheckState(Qt::Unchecked);

    AttrTable->setCellWidget(0,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(0,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
    ((QComboBox*)(AttrTable->cellWidget(0,1)))->setCurrentIndex(1);
    AttrTable->setCellWidget(1,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(1,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
    ((QComboBox*)(AttrTable->cellWidget(1,1)))->setCurrentIndex(1);
    AttrTable->setCellWidget(2,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(2,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
    ((QComboBox*)(AttrTable->cellWidget(2,1)))->setCurrentIndex(1);
    AttrTable->setCellWidget(3,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(3,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
    ((QComboBox*)(AttrTable->cellWidget(3,1)))->setCurrentIndex(1);
    AttrTable->setCellWidget(4,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(4,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
    ((QComboBox*)(AttrTable->cellWidget(4,1)))->setCurrentIndex(1);
    AttrTable->setCellWidget(5,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(5,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
    ((QComboBox*)(AttrTable->cellWidget(5,1)))->setCurrentIndex(1);
    AttrTable->setCellWidget(6,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(6,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
    ((QComboBox*)(AttrTable->cellWidget(6,1)))->setCurrentIndex(1);
    AttrTable->setCellWidget(7,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(7,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
    ((QComboBox*)(AttrTable->cellWidget(7,1)))->setCurrentIndex(1);
    AttrTable->setCellWidget(8,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(8,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
    ((QComboBox*)(AttrTable->cellWidget(8,1)))->setCurrentIndex(1);


    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    if(AttrDlg->exec() == QDialog::Accepted)
    {
        QDomElement qNewElement = doc->createElement(tr("OptFields"));

        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("refreshTime"), ((QComboBox*)(AttrTable->cellWidget(0,1)))->currentText());
        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("sampleSynchronized"), ((QComboBox*)(AttrTable->cellWidget(1,1)))->currentText());
        if(AttrTable->item(2,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("sampleRate"), ((QComboBox*)(AttrTable->cellWidget(2,1)))->currentText());
        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("security"), ((QComboBox*)(AttrTable->cellWidget(3,1)))->currentText());
        if(AttrTable->item(4,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("dataRef"), ((QComboBox*)(AttrTable->cellWidget(4,1)))->currentText());
        if(AttrTable->item(5,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("bufOvfl"), ((QComboBox*)(AttrTable->cellWidget(5,1)))->currentText());
        if(AttrTable->item(6,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("entryID"), ((QComboBox*)(AttrTable->cellWidget(6,1)))->currentText());
        if(AttrTable->item(7,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("configRef"), ((QComboBox*)(AttrTable->cellWidget(7,1)))->currentText());
        if(AttrTable->item(8,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("segmentation"), ((QComboBox*)(AttrTable->cellWidget(8,1)))->currentText());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
    }
}

void MainWindow::addRptEnabled(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - RptEnabled"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(2,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("max")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(1,0,new QTableWidgetItem(tr("desc")));
    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);

    AttrTable->setCellWidget(0,1,new QSpinBox(this));
    ((QSpinBox*)(AttrTable->cellWidget(0,1)))->setValue(1);
    AttrTable->setItem(1,1,new QTableWidgetItem(tr("")));

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    if(AttrDlg->exec() == QDialog::Accepted)
    {
        QDomElement qNewElement = doc->createElement(tr("RptEnabled"));

        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("max"), ((QSpinBox*)(AttrTable->cellWidget(0,1)))->text());
        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("desc"), AttrTable->item(1,1)->text());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
    }
}

void MainWindow::addTrgOps(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - TrgOps"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(4,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("dchg")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(1,0,new QTableWidgetItem(tr("qchg")));
    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(2,0,new QTableWidgetItem(tr("dupd")));
    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(3,0,new QTableWidgetItem(tr("period")));
    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);

    AttrTable->setCellWidget(0,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(0,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
    ((QComboBox*)(AttrTable->cellWidget(0,1)))->setCurrentIndex(1);
    AttrTable->setCellWidget(1,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(1,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
    ((QComboBox*)(AttrTable->cellWidget(1,1)))->setCurrentIndex(1);
    AttrTable->setCellWidget(2,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(2,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
    ((QComboBox*)(AttrTable->cellWidget(2,1)))->setCurrentIndex(1);
    AttrTable->setCellWidget(3,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(3,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
    ((QComboBox*)(AttrTable->cellWidget(3,1)))->setCurrentIndex(1);

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    if(AttrDlg->exec() == QDialog::Accepted)
    {
        QDomElement qNewElement = doc->createElement(tr("TrgOps"));

        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("dchg"), ((QComboBox*)(AttrTable->cellWidget(0,1)))->currentText());
        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("qchg"), ((QComboBox*)(AttrTable->cellWidget(1,1)))->currentText());
        if(AttrTable->item(2,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("dupd"), ((QComboBox*)(AttrTable->cellWidget(2,1)))->currentText());
        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("period"), ((QComboBox*)(AttrTable->cellWidget(3,1)))->currentText());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
    }
}

void MainWindow::addClientLN(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - ClientLN"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(5,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("prefix")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(1,0,new QTableWidgetItem(tr("(*)lnClass")));
    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(2,0,new QTableWidgetItem(tr("(*)lnInst")));
    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(3,0,new QTableWidgetItem(tr("(*)iedName")));
    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(4,0,new QTableWidgetItem(tr("(*)ldInst")));
    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));

    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
    AttrTable->setCellWidget(1,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(1,1)))->addItems(lnClass);
    AttrTable->setItem(2,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(3,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(4,1,new QTableWidgetItem(tr("")));

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    while(AttrDlg->exec() == QDialog::Accepted)
    {
        if(AttrTable->item(2,1)->text()==tr(""))
        {
            QMessageBox::warning(NULL,tr("警告"),tr("lnInst项为必需项，不能为空!"));
            continue;
        }
        if(AttrTable->item(3,1)->text()==tr(""))
        {
            QMessageBox::warning(NULL,tr("警告"),tr("iedName项为必需项，不能为空!"));
            continue;
        }
        if(AttrTable->item(4,1)->text()==tr(""))
        {
            QMessageBox::warning(NULL,tr("警告"),tr("ldInst项为必需项，不能为空!"));
            continue;
        }

        QDomElement qNewElement = doc->createElement(tr("ClientLN"));

        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("prefix"), AttrTable->item(0,1)->text());
        qNewElement.setAttribute(tr("lnClass"), ((QComboBox*)(AttrTable->cellWidget(1,1)))->currentText());
        qNewElement.setAttribute(tr("lnInst"), AttrTable->item(2,1)->text());
        qNewElement.setAttribute(tr("iedName"), AttrTable->item(3,1)->text());
        qNewElement.setAttribute(tr("ldInst"), AttrTable->item(4,1)->text());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
        break;
    }
}

void MainWindow::addSDI(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - SDI"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(3,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("name")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(1,0,new QTableWidgetItem(tr("ix")));
    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(2,0,new QTableWidgetItem(tr("desc")));
    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);

    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
    AttrTable->setCellWidget(1,1,new QSpinBox(this));
    AttrTable->setItem(2,1,new QTableWidgetItem(tr("")));

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    while(AttrDlg->exec() == QDialog::Accepted)
    {
        if(AttrTable->item(0,1)->text()==tr(""))
        {
            QMessageBox::warning(NULL,tr("警告"),tr("name项为必需项，不能为空!"));
            continue;
        }

        QDomElement qNewElement = doc->createElement(tr("SDI"));

        qNewElement.setAttribute(tr("name"), AttrTable->item(0,1)->text());
        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("ix"), ((QSpinBox*)(AttrTable->cellWidget(1,1)))->text());
        if(AttrTable->item(2,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("desc"), AttrTable->item(2,1)->text());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
        break;
    }
}

void MainWindow::addDAI(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - DAI"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(5,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("name")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(1,0,new QTableWidgetItem(tr("sAddr")));
    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(2,0,new QTableWidgetItem(tr("valKind")));
    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(3,0,new QTableWidgetItem(tr("ix")));
    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(4,0,new QTableWidgetItem(tr("desc")));
    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(4,0)->setCheckState(Qt::Unchecked);

    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(1,1,new QTableWidgetItem(tr("")));
    AttrTable->setCellWidget(2,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(2,1)))->addItems(QStringList()<<tr("Spec")<<tr("Conf")<<tr("RO")<<tr("Set"));
    ((QComboBox*)(AttrTable->cellWidget(2,1)))->setCurrentIndex(3);
    AttrTable->setCellWidget(3,1,new QSpinBox(this));
    AttrTable->setItem(4,1,new QTableWidgetItem(tr("")));

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    while(AttrDlg->exec() == QDialog::Accepted)
    {
        if(AttrTable->item(0,1)->text()==tr(""))
        {
            QMessageBox::warning(NULL,tr("警告"),tr("name项为必需项，不能为空!"));
            continue;
        }

        QDomElement qNewElement = doc->createElement(tr("DAI"));

        qNewElement.setAttribute(tr("name"), AttrTable->item(0,1)->text());
        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("sAddr"), AttrTable->item(1,1)->text());
        if(AttrTable->item(2,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("valKind"), ((QComboBox*)(AttrTable->cellWidget(2,1)))->currentText());
        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("ix"), ((QSpinBox*)(AttrTable->cellWidget(1,1)))->text());
        if(AttrTable->item(4,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("desc"), AttrTable->item(2,1)->text());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
        break;
    }
}

void MainWindow::addVal(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - Val"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(1,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("sGroup")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);

    AttrTable->setCellWidget(0,1,new QSpinBox(this));

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    if(AttrDlg->exec() == QDialog::Accepted)
    {
        QDomElement qNewElement = doc->createElement(tr("Val"));

        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("sGroup"), ((QSpinBox*)(AttrTable->cellWidget(0,1)))->text());

        currentNode.appendChild(qNewElement);
        qDebug()<<"Add Item";
        qDebug()<<currentNode.toElement().tagName();
        qDebug()<<qNewElement.tagName();
        qDebug()<<view->indexAt(cp).parent().data().toString();
        model->update();
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
    }
}

void MainWindow::addValContent(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *ContentDlg = new QDialog(this);
    ContentDlg->setWindowTitle(tr("Val值输入"));
    QGridLayout *ContentDlgLayout = new QGridLayout(ContentDlg);
    QLabel *ContentLabel = new QLabel(tr("请输入Val值："));
    QLineEdit *ContentEdit = new QLineEdit(this);

    QPushButton *qContentDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qContentDlgConfirm, SIGNAL(clicked()), ContentDlg, SLOT(accept()));
    QPushButton *qContentDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qContentDlgCancel, SIGNAL(clicked()), ContentDlg, SLOT(close()));
    ContentDlgLayout->addWidget(ContentLabel,0,0,1,1);
    ContentDlgLayout->addWidget(ContentEdit,0,1,1,3);
    ContentDlgLayout->addWidget(qContentDlgConfirm,2,2);
    ContentDlgLayout->addWidget(qContentDlgCancel,2,3);

    if(ContentDlg->exec() == QDialog::Accepted)
    {
        QDomText qNewText = doc->createTextNode(ContentEdit->text());

        currentNode.appendChild(qNewText);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
    }
}

void MainWindow::addExtRef(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - ExtRef"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(8,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("daName")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(1,0,new QTableWidgetItem(tr("intAddr")));
    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(2,0,new QTableWidgetItem(tr("(*)doName")));
    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(3,0,new QTableWidgetItem(tr("prefix")));
    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(4,0,new QTableWidgetItem(tr("(*)lnClass")));
    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(5,0,new QTableWidgetItem(tr("(*)lnInst")));
    AttrTable->item(5,0)->setFlags(AttrTable->item(5,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(6,0,new QTableWidgetItem(tr("(*)iedName")));
    AttrTable->item(6,0)->setFlags(AttrTable->item(6,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(7,0,new QTableWidgetItem(tr("(*)ldInst")));
    AttrTable->item(7,0)->setFlags(AttrTable->item(7,0)->flags() & (~Qt::ItemIsEditable));

    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(1,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(2,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(3,1,new QTableWidgetItem(tr("")));
    AttrTable->setCellWidget(4,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(4,1)))->addItems(lnClass);
    AttrTable->setItem(5,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(6,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(7,1,new QTableWidgetItem(tr("")));

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    while(AttrDlg->exec() == QDialog::Accepted)
    {
        if(AttrTable->item(2,1)->text()==tr(""))
        {
            QMessageBox::warning(NULL,tr("警告"),tr("doName项为必需项，不能为空!"));
            continue;
        }
        if(AttrTable->item(5,1)->text()==tr(""))
        {
            QMessageBox::warning(NULL,tr("警告"),tr("lnInst项为必需项，不能为空!"));
            continue;
        }
        if(AttrTable->item(6,1)->text()==tr(""))
        {
            QMessageBox::warning(NULL,tr("警告"),tr("iedName项为必需项，不能为空!"));
            continue;
        }
        if(AttrTable->item(7,1)->text()==tr(""))
        {
            QMessageBox::warning(NULL,tr("警告"),tr("ldInst项为必需项，不能为空!"));
            continue;
        }
        QDomElement qNewElement = doc->createElement(tr("ExtRef"));

        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("daName"), AttrTable->item(0,1)->text());
        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("intAddr"), AttrTable->item(1,1)->text());
        qNewElement.setAttribute(tr("doName"), AttrTable->item(2,1)->text());
        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("prefix"), AttrTable->item(3,1)->text());
        qNewElement.setAttribute(tr("lnClass"), ((QComboBox*)(AttrTable->cellWidget(4,1)))->currentText());
        qNewElement.setAttribute(tr("lnInst"), AttrTable->item(5,1)->text());
        qNewElement.setAttribute(tr("iedName"), AttrTable->item(6,1)->text());
        qNewElement.setAttribute(tr("ldInst"), AttrTable->item(7,1)->text());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
        break;
    }
}

void MainWindow::addLNodeType(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - LNodeType"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(4,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("iedType")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(1,0,new QTableWidgetItem(tr("(*)lnClass")));
    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(2,0,new QTableWidgetItem(tr("(*)id")));
    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(3,0,new QTableWidgetItem(tr("desc")));
    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);

    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
    AttrTable->setCellWidget(1,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(1,1)))->addItems(lnClass);
    AttrTable->setItem(2,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(3,1,new QTableWidgetItem(tr("")));

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    while(AttrDlg->exec() == QDialog::Accepted)
    {
        QDomElement qNewElement = doc->createElement(tr("LNodeType"));

        if(AttrTable->item(2,1)->text()==tr(""))
        {
            QMessageBox::warning(NULL,tr("警告"),tr("id项为必需项，不能为空!"));
            continue;
        }

        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("iedType"), ((QComboBox*)(AttrTable->cellWidget(0,1)))->currentText());
        qNewElement.setAttribute(tr("lnClss"), ((QComboBox*)(AttrTable->cellWidget(1,1)))->currentText());
        qNewElement.setAttribute(tr("id"), AttrTable->item(2,1)->text());
        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("desc"), AttrTable->item(3,1)->text());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
        break;
    }
}

void MainWindow::addDOType(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - DOType"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(4,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("iedType")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(1,0,new QTableWidgetItem(tr("(*)cdc")));
    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(2,0,new QTableWidgetItem(tr("(*)id")));
    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(3,0,new QTableWidgetItem(tr("desc")));
    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);

    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
    AttrTable->setCellWidget(1,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(1,1)))->addItems(cdc);
    ((QComboBox*)(AttrTable->cellWidget(1,1)))->setEditable(1);
    AttrTable->setItem(2,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(3,1,new QTableWidgetItem(tr("")));

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    while(AttrDlg->exec() == QDialog::Accepted)
    {
        QDomElement qNewElement = doc->createElement(tr("DOType"));

        if(AttrTable->item(2,1)->text()==tr(""))
        {
            QMessageBox::warning(NULL,tr("警告"),tr("id项为必需项，不能为空!"));
            continue;
        }

        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("iedType"), AttrTable->item(0,1)->text());
        qNewElement.setAttribute(tr("cdc"), ((QComboBox*)(AttrTable->cellWidget(1,1)))->currentText());
        qNewElement.setAttribute(tr("id"), AttrTable->item(2,1)->text());
        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("desc"), AttrTable->item(3,1)->text());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
        break;
    }
}

void MainWindow::addDAType(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - DAType"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(3,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("iedType")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(1,0,new QTableWidgetItem(tr("(*)id")));
    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(2,0,new QTableWidgetItem(tr("desc")));
    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);

    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(1,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(2,1,new QTableWidgetItem(tr("")));

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    while(AttrDlg->exec() == QDialog::Accepted)
    {
        QDomElement qNewElement = doc->createElement(tr("DAType"));

        if(AttrTable->item(1,1)->text()==tr(""))
        {
            QMessageBox::warning(NULL,tr("警告"),tr("id项为必需项，不能为空!"));
            continue;
        }

        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("iedType"), AttrTable->item(0,1)->text());
        qNewElement.setAttribute(tr("id"), AttrTable->item(1,1)->text());
        if(AttrTable->item(2,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("desc"), AttrTable->item(2,1)->text());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
        break;
    }
}

void MainWindow::addEnumType(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - EnumType"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(2,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)id")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(1,0,new QTableWidgetItem(tr("desc")));
    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);

    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(1,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(2,1,new QTableWidgetItem(tr("")));

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    while(AttrDlg->exec() == QDialog::Accepted)
    {
        QDomElement qNewElement = doc->createElement(tr("EnumType"));

        if(AttrTable->item(0,1)->text()==tr(""))
        {
            QMessageBox::warning(NULL,tr("警告"),tr("id项为必需项，不能为空!"));
            continue;
        }

        qNewElement.setAttribute(tr("id"), AttrTable->item(0,1)->text());
        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("desc"), AttrTable->item(1,1)->text());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
        break;
    }
}

void MainWindow::addDO(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - DO"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(5,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)name")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(1,0,new QTableWidgetItem(tr("(*)type")));
    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(2,0,new QTableWidgetItem(tr("accessControl")));
    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(3,0,new QTableWidgetItem(tr("transient")));
    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(4,0,new QTableWidgetItem(tr("desc")));
    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(4,0)->setCheckState(Qt::Unchecked);

    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
    AttrTable->setCellWidget(1,1,new QComboBox(this));
    AttrTable->setItem(2,1,new QTableWidgetItem(tr("")));
    AttrTable->setCellWidget(3,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(3,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
    ((QComboBox*)(AttrTable->cellWidget(3,1)))->setCurrentIndex(1);
    AttrTable->setItem(4,1,new QTableWidgetItem(tr("")));

    QStringList DAType;
    QDomNode DataTypeNode = currentNode.parentNode();
    for(int i=0; i<DataTypeNode.childNodes().count(); i++)
    {
        if(DataTypeNode.childNodes().at(i).toElement().tagName().contains(tr("DAType")))
        {
            QDomNode DATypeNode = DataTypeNode.childNodes().at(i);

            if(DATypeNode.attributes().contains(tr("id")))
                DAType.append(DATypeNode.attributes().namedItem("id").toAttr().value());
        }
    }
    if(DAType.isEmpty())
        DAType.append(tr(""));
    ((QComboBox*)(AttrTable->cellWidget(1,1)))->addItems(DAType);

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    while(AttrDlg->exec() == QDialog::Accepted)
    {
        QDomElement qNewElement = doc->createElement(tr("DO"));

        if(AttrTable->item(0,1)->text()==tr(""))
        {
            QMessageBox::warning(NULL,tr("警告"),tr("name项为必需项，不能为空!"));
            continue;
        }

        qNewElement.setAttribute(tr("name"), AttrTable->item(0,1)->text());
        qNewElement.setAttribute(tr("type"), ((QComboBox*)(AttrTable->cellWidget(1,1)))->currentText());
        if(AttrTable->item(2,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("accessControl"), AttrTable->item(2,1)->text());
        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("transient"), ((QComboBox*)(AttrTable->cellWidget(3,1)))->currentText());
        if(AttrTable->item(4,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("desc"), AttrTable->item(4,1)->text());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
        break;
    }
}

void MainWindow::addSDO(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - SDO"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(3,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)type")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(1,0,new QTableWidgetItem(tr("(*)name")));
    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(2,0,new QTableWidgetItem(tr("desc")));
    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);

    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(1,1,new QTableWidgetItem(tr("")));
    AttrTable->setItem(2,1,new QTableWidgetItem(tr("")));

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    while(AttrDlg->exec() == QDialog::Accepted)
    {
        QDomElement qNewElement = doc->createElement(tr("SDO"));

        if(AttrTable->item(0,1)->text()==tr(""))
        {
            QMessageBox::warning(NULL,tr("警告"),tr("type项为必需项，不能为空!"));
            continue;
        }
        if(AttrTable->item(1,1)->text()==tr(""))
        {
            QMessageBox::warning(NULL,tr("警告"),tr("name项为必需项，不能为空!"));
            continue;
        }

        qNewElement.setAttribute(tr("type"), AttrTable->item(0,1)->text());
        qNewElement.setAttribute(tr("name"), AttrTable->item(1,1)->text());
        if(AttrTable->item(2,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("desc"), AttrTable->item(2,1)->text());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
        break;
    }
}

void MainWindow::addDA(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - DA"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(11,2,this);
    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)fc")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(1,0,new QTableWidgetItem(tr("dchg")));
    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(2,0,new QTableWidgetItem(tr("qchg")));
    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(3,0,new QTableWidgetItem(tr("dupds")));
    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(4,0,new QTableWidgetItem(tr("(*)name")));
    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(5,0,new QTableWidgetItem(tr("sAddr")));
    AttrTable->item(5,0)->setFlags(AttrTable->item(5,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(5,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(6,0,new QTableWidgetItem(tr("(*)bType")));
    AttrTable->item(6,0)->setFlags(AttrTable->item(6,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(6,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(7,0,new QTableWidgetItem(tr("valKind")));
    AttrTable->item(7,0)->setFlags(AttrTable->item(7,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(7,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(8,0,new QTableWidgetItem(tr("type")));
    AttrTable->item(8,0)->setFlags(AttrTable->item(8,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(8,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(9,0,new QTableWidgetItem(tr("count")));
    AttrTable->item(9,0)->setFlags(AttrTable->item(9,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(9,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(10,0,new QTableWidgetItem(tr("desc")));
    AttrTable->item(10,0)->setFlags(AttrTable->item(10,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(10,0)->setCheckState(Qt::Unchecked);

    AttrTable->setCellWidget(0,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(0,1)))->addItems(fcEnum);
    AttrTable->setCellWidget(1,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(1,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
    ((QComboBox*)(AttrTable->cellWidget(1,1)))->setCurrentIndex(1);
    AttrTable->setCellWidget(2,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(2,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
    ((QComboBox*)(AttrTable->cellWidget(2,1)))->setCurrentIndex(1);
    AttrTable->setCellWidget(3,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(3,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
    ((QComboBox*)(AttrTable->cellWidget(3,1)))->setCurrentIndex(1);
    AttrTable->setCellWidget(4,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(4,1)))->addItems(QStringList()<<tr("T")<<tr("Test")<<tr("Check")<<tr("SIUnit"));
    ((QComboBox*)(AttrTable->cellWidget(4,1)))->setEditable(1);
    AttrTable->setItem(5,1,new QTableWidgetItem(tr("")));
    AttrTable->setCellWidget(6,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(6,1)))->addItems(BasicType);
    ((QComboBox*)(AttrTable->cellWidget(6,1)))->setEditable(1);
    AttrTable->setCellWidget(7,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(7,1)))->addItems(QStringList()<<tr("Spec")<<tr("Conf")<<tr("RO")<<tr("Set"));
    ((QComboBox*)(AttrTable->cellWidget(7,1)))->setCurrentIndex(3);
    AttrTable->setItem(8,1,new QTableWidgetItem(tr("")));
    AttrTable->setCellWidget(9,1,new QSpinBox(this));
    AttrTable->setItem(10,1,new QTableWidgetItem(tr("")));

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    if(AttrDlg->exec() == QDialog::Accepted)
    {
        QDomElement qNewElement = doc->createElement(tr("DA"));

        qNewElement.setAttribute(tr("fc"), ((QComboBox*)(AttrTable->cellWidget(0,1)))->currentText());
        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("dchg"), ((QComboBox*)(AttrTable->cellWidget(1,1)))->currentText());
        if(AttrTable->item(2,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("qchg"), ((QComboBox*)(AttrTable->cellWidget(2,1)))->currentText());
        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("dupd"), ((QComboBox*)(AttrTable->cellWidget(3,1)))->currentText());
        qNewElement.setAttribute(tr("name"), ((QComboBox*)(AttrTable->cellWidget(4,1)))->currentText());
        if(AttrTable->item(5,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("sAddr"), AttrTable->item(5,1)->text());
        qNewElement.setAttribute(tr("bType"), ((QComboBox*)(AttrTable->cellWidget(6,1)))->currentText());
        if(AttrTable->item(7,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("valKind"), ((QComboBox*)(AttrTable->cellWidget(7,1)))->currentText());
        if(AttrTable->item(8,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("type"), AttrTable->item(8,1)->text());
        if(AttrTable->item(9,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("count"), ((QSpinBox*)(AttrTable->cellWidget(9,1)))->text());
        if(AttrTable->item(10,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("desc"), AttrTable->item(10,1)->text());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
    }
}

void MainWindow::addBDA(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - BDA"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(7,2,this);

    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)name")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->setItem(1,0,new QTableWidgetItem(tr("sAddr")));
    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(2,0,new QTableWidgetItem(tr("(*)bType")));
    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(3,0,new QTableWidgetItem(tr("valKind")));
    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(4,0,new QTableWidgetItem(tr("type")));
    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(4,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(5,0,new QTableWidgetItem(tr("count")));
    AttrTable->item(5,0)->setFlags(AttrTable->item(5,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(5,0)->setCheckState(Qt::Unchecked);
    AttrTable->setItem(6,0,new QTableWidgetItem(tr("desc")));
    AttrTable->item(6,0)->setFlags(AttrTable->item(6,0)->flags() & (~Qt::ItemIsEditable));
    AttrTable->item(6,0)->setCheckState(Qt::Unchecked);

    AttrTable->setCellWidget(0,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(0,1)))->addItems(QStringList()<<tr("T")<<tr("Test")<<tr("Check")<<tr("SIUnit"));
    ((QComboBox*)(AttrTable->cellWidget(0,1)))->setEditable(1);
    AttrTable->setItem(1,1,new QTableWidgetItem(tr("")));
    AttrTable->setCellWidget(2,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(2,1)))->addItems(BasicType);
    ((QComboBox*)(AttrTable->cellWidget(2,1)))->setEditable(1);
    AttrTable->setCellWidget(3,1,new QComboBox(this));
    ((QComboBox*)(AttrTable->cellWidget(3,1)))->addItems(QStringList()<<tr("Spec")<<tr("Conf")<<tr("RO")<<tr("Set"));
    ((QComboBox*)(AttrTable->cellWidget(3,1)))->setCurrentIndex(3);
    AttrTable->setItem(4,1,new QTableWidgetItem(tr("")));
    AttrTable->setCellWidget(5,1,new QSpinBox(this));
    AttrTable->setItem(6,1,new QTableWidgetItem(tr("")));

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    if(AttrDlg->exec() == QDialog::Accepted)
    {
        QDomElement qNewElement = doc->createElement(tr("BDA"));

        qNewElement.setAttribute(tr("name"), ((QComboBox*)(AttrTable->cellWidget(0,1)))->currentText());
        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("sAddr"), AttrTable->item(1,1)->text());
        qNewElement.setAttribute(tr("bType"), ((QComboBox*)(AttrTable->cellWidget(2,1)))->currentText());
        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("valKind"), ((QComboBox*)(AttrTable->cellWidget(3,1)))->currentText());
        if(AttrTable->item(4,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("type"), AttrTable->item(4,1)->text());
        if(AttrTable->item(5,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("count"), ((QSpinBox*)(AttrTable->cellWidget(5,1)))->text());
        if(AttrTable->item(6,0)->checkState() == Qt::Checked)
            qNewElement.setAttribute(tr("desc"), AttrTable->item(6,1)->text());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);
    }
}

void MainWindow::addEnumVal(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    QDialog *AttrDlg = new QDialog(this);
    AttrDlg->setWindowTitle(tr("属性编辑器 - EnumVal"));
    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
    QTableWidget *AttrTable = new QTableWidget(1,2,this);

    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)ord")));
    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));

    AttrTable->setCellWidget(0,1,new QSpinBox(this));
    ((QSpinBox*)(AttrTable->cellWidget(0,1)))->setMinimum(-65535);

    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

    if(AttrDlg->exec() == QDialog::Accepted)
    {
        QDomElement qNewElement = doc->createElement(tr("EnumVal"));

        qNewElement.setAttribute(tr("ord"), ((QSpinBox*)(AttrTable->cellWidget(0,1)))->text());

        currentNode.appendChild(qNewElement);
        QModelIndex parentIndex = view->indexAt(cp).parent();
        view->setExpanded(parentIndex,0);
        view->setExpanded(parentIndex,1);
        view->setExpanded(view->indexAt(cp),1);

    }
}

void MainWindow::deleteItem(QPoint cp)
{
    QModelIndex *currentIndex = new QModelIndex();
    *currentIndex = view->indexAt(cp);
    DomItem *currentItem = static_cast<DomItem*>(currentIndex->internalPointer());
    QDomNode currentNode = currentItem->node();

    qDebug()<<"Delete Item";
    qDebug()<<currentNode.nodeName();
    qDebug()<<currentNode.childNodes().count();

    DomItem* parentItem = currentItem->parent();
    QDomNode parentNode = parentItem->node();
    qDebug()<<parentNode.nodeName();
    qDebug()<<parentNode.childNodes().count();

    QModelIndex parentIndex;
    if(parentNode.childNodes().count()>1)
        parentIndex = view->indexAt(cp).parent();//.parent();
    else
        parentIndex = view->indexAt(cp).parent().parent();
    qDebug()<<cp<<'\t'<<parentIndex.data().toString();
//    for(int i=0; i<currentNode.childNodes().count(); i++)
//    {
//        currentNode.removeChild(currentNode.childNodes().at(i));
//    }
    deleteChildren(currentNode);
//    for(int i=0; i<parentNode.childNodes().count(); i++)
//    {
//        if(parentNode.childNodes().at(i).nodeName() == currentNode.nodeName())
//        {
//            parentNode.removeChild(parentNode.childNodes().at(i));
//            break;
//        }
//    }
//    parentNode.removeChild(currentNode);

    view->setExpanded(parentIndex,0);
    view->setExpanded(parentIndex,1);
//    delete currentIndex;
//    currentNode.clear();

}

void MainWindow::deleteChildren(QDomNode node)
{
    qDebug()<<node.nodeName();
    while(node.hasChildNodes())
    {
        deleteChildren(node.firstChild());
//        for(int i=0; i<item->node().childNodes().count(); i++)
//        {
//            qDebug()<<i<<'\t'<<item->child(i)->node().nodeName();
//            deleteChildren(item->child(i));
//        }

    }
//    else
//    {
        node.parentNode().removeChild(node);
        //item->parent()->node().removeChild(item->node());
//    }
}
