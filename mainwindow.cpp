#include <QtXml/QDomDocument>
#include <QFile>
#include <QtGui>
#include <QClipboard>
#include <QXmlSchema>
#include <QXmlSchemaValidator>

#include "mainwindow.h"

#include "config.h"
#include "utils.h"
#include "qxmledit.h"
#include "schemavalidator.h"
#include "SchemaInterface.h"

#define MAX_LAST_FILES  (20)
#define SHORT_TIMEOUT  1000
#define LONG_TIMEOUT   5000

extern const char *APP_TITLE;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
//    CreateActions();

    maxLastFiles = MAX_LAST_FILES;
    maxPrefDirs = QXmlEditParameters::NUM_PREF_DIRS;

    CreateMenus();

    QString windowTitle = APP_TITLE;
    setWindowTitle(windowTitle);
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
    connect(qDeleteItem, SIGNAL(clicked(QModelIndex)), this, SLOT(deleteItem(const QModelIndex&)));

    qAddHeader = new QItemAction(tr("插入Header字段"),this);
    connect(qAddHeader, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addHeader(const QModelIndex&)));

    qAddCommunication = new QItemAction(tr("插入Communication字段"), this);
    connect(qAddCommunication, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addCommunication(const QModelIndex&)));

    qAddSubstation = new QItemAction(tr("插入Substation字段"), this);
    connect(qAddSubstation, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addSubstation(const QModelIndex&)));

    qAddIED = new QItemAction(tr("插入IED字段"), this);
    connect(qAddIED, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addIED(const QModelIndex&)));

    qAddDataTypeTemplates = new QItemAction(tr("插入DataTypeTemplates字段"), this);
    connect(qAddDataTypeTemplates, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addDataTypeTemplates(const QModelIndex&)));

    qAddText = new QItemAction(tr("插入Text字段"),this);
    connect(qAddText, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addTextAct(const QModelIndex&)));

    qAddTextContent = new QItemAction(tr("插入Text内容"),this);
    connect(qAddTextContent, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addTextContentAct(const QModelIndex&)));

    qAddHistory = new QItemAction(this);
    qAddHistory->setText(tr("插入History字段"));
    connect(qAddHistory, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addHistoryAct(const QModelIndex&)));

    qAddHitem = new QItemAction(tr("插入Hitem项"),this);
    connect(qAddHitem, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addHitemAct(const QModelIndex&)));

    qAddVoltageLevel = new QItemAction(tr("插入VoltageLevel项"),this);
    connect(qAddVoltageLevel, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addVoltageLevel(QModelIndex)));

    qAddFunction = new QItemAction(tr("插入Function项"),this);
    connect(qAddFunction, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addFunction(QModelIndex)));

    qAddPowerTransformer = new QItemAction(tr("插入PowerTransformer项"), this);
    connect(qAddPowerTransformer, SIGNAL(clicked(QModelIndex)), this, SLOT(addPowerTransformer(QModelIndex)));

    qAddGeneralEquipment = new QItemAction(tr("插入GeneralEquipment项"), this);
    connect(qAddGeneralEquipment , SIGNAL(clicked(QModelIndex)), this, SLOT(addGeneralEquipment(QModelIndex)));

    qAddLNode = new QItemAction(tr("插入LNode项"), this);
    connect(qAddLNode , SIGNAL(clicked(QModelIndex)), this, SLOT(addLNode(QModelIndex)));

    qAddServices = new QItemAction(tr("插入Services字段"), this);
    connect(qAddServices, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addServices(const QModelIndex&)));

    qAddAccessPoint = new QItemAction(tr("插入AccessPoint字段"), this);
    connect(qAddAccessPoint, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addAccessPoint(const QModelIndex&)));

    qAddDynAssociation = new QItemAction(tr("插入DynAssociation"),this);
    connect(qAddDynAssociation, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addDynAssociation(const QModelIndex&)));
    qAddSettingGroups = new QItemAction(tr("插入SettingGroups"), this);
    connect(qAddSettingGroups, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addSettingGroups(const QModelIndex&)));
    qAddGetDirectory = new QItemAction(tr("插入GetDirectory"), this);
    connect(qAddGetDirectory, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addGetDirectory(const QModelIndex&)));
    qAddGetDataObjectDefinition = new QItemAction(tr("插入DataObjectDefinition"), this);
    connect(qAddGetDataObjectDefinition, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addGetDataObjectDefinition(const QModelIndex&)));
    qAddDataObjectDirectory = new QItemAction(tr("插入DataObjectDirectory"), this);
    connect(qAddDataObjectDirectory, SIGNAL(clicked(QModelIndex)), this, SLOT(addDataObjectDirectory(QModelIndex)));
    qAddGetDataSetValue = new QItemAction(tr("插入GetDataSetValue"), this);
    connect(qAddGetDataSetValue, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addGetDataSetValue(const QModelIndex&)));
    qAddSetDataSetValue = new QItemAction(tr("插入SetDataSetValue"), this);
    connect(qAddSetDataSetValue, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addSetDataSetValue(const QModelIndex&)));
    qAddDataSetDirectory = new QItemAction(tr("插入DataSetDirectory"),this);
    connect(qAddDataSetDirectory, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addDataSetDirectory(const QModelIndex&)));
    qAddConfDataSet = new QItemAction(tr("插入ConfDataSet"),this);
    connect(qAddConfDataSet, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addConfDataSet(const QModelIndex&)));
    qAddDynDataSet = new QItemAction(tr("插入DynDataSet"),this);
    connect(qAddDynDataSet, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addDynDataSet(const QModelIndex&)));
    qAddReadWrite = new QItemAction(tr("插入ReadWrite"),this);
    connect(qAddReadWrite, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addReadWrite(const QModelIndex&)));
    qAddTimerActivatedControl = new QItemAction(tr("插入TimerActivatedControl"),this);
    connect(qAddTimerActivatedControl, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addTimerActivatedControl(const QModelIndex&)));
    qAddConfReportControl = new QItemAction(tr("插入ConfReportControl"),this);
    connect(qAddConfReportControl, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addConfReportControl(const QModelIndex&)));
    qAddGetCBValues = new QItemAction(tr("插入GetCBValues"),this);
    connect(qAddGetCBValues, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addGetCBValues(const QModelIndex&)));
    qAddConfLogControl = new QItemAction(tr("插入ConfLogControl"),this);
    connect(qAddConfLogControl, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addConfLogControl(const QModelIndex&)));
    qAddReportSettings = new QItemAction(tr("插入ReportSettings"),this);
    connect(qAddReportSettings, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addReportSettings(const QModelIndex&)));
    qAddLogSettings = new QItemAction(tr("插入LogSettings"),this);
    connect(qAddLogSettings, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addLogSettings(const QModelIndex&)));
    qAddGSESettings = new QItemAction(tr("插入GSESettings"),this);
    connect(qAddGSESettings, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addGSESettings(const QModelIndex&)));
    qAddSMVSettings = new QItemAction(tr("插入SMVSettings"),this);
    connect(qAddSMVSettings, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addSMVSettings(const QModelIndex&)));
    qAddGSEDir = new QItemAction(tr("插入GSEDir"),this);
    connect(qAddGSEDir, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addGSEDir(const QModelIndex&)));
    qAddGOOSE = new QItemAction(tr("插入GOOSE"),this);
    connect(qAddGOOSE, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addGOOSE(const QModelIndex&)));
    qAddGSSE = new QItemAction(tr("插入GSSE"),this);
    connect(qAddGSSE, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addGSSE(const QModelIndex&)));
    qAddFileHandling = new QItemAction(tr("插入FileHandling"),this);
    connect(qAddFileHandling, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addFileHandling(const QModelIndex&)));
    qAddConfLNs = new QItemAction(tr("插入ConfLNs"),this);
    connect(qAddConfLNs, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addConfLNs(const QModelIndex&)));
    qAddSGEdit = new QItemAction(tr("插入SGEdit"),this);
    connect(qAddSGEdit, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addSGEdit(const QModelIndex&)));
    qAddConfSG = new QItemAction(tr("插入ConfSG"),this);
    connect(qAddConfSG, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addConfSG(const QModelIndex&)));

    qAddServer = new QItemAction(tr("插入Server"),this);
    connect(qAddServer, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addServer(const QModelIndex&)));
    qAddLN = new QItemAction(tr("插入LN"),this);
    connect(qAddLN, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addLN(const QModelIndex&)));

    qAddAuthentication = new QItemAction(tr("插入Authentication"),this);
    connect(qAddAuthentication, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addAuthentication(const QModelIndex&)));
    qAddLDevice = new QItemAction(tr("插入LDevice"),this);
    connect(qAddLDevice, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addLDevice(const QModelIndex&)));
    qAddAssociation = new QItemAction(tr("插入Association"),this);
    connect(qAddAssociation, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addAssociation(const QModelIndex&)));

    qAddLN0 = new QItemAction(tr("插入LN0"),this);
    connect(qAddLN0, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addLN0(const QModelIndex&)));
    qAddAccessControl = new QItemAction(tr("插入AccessControl"),this);
    connect(qAddAccessControl, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addAccessControl(const QModelIndex&)));

    qAddGSEControl = new QItemAction(tr("插入GSEControl"),this);
    connect(qAddGSEControl, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addGSEControl(const QModelIndex&)));
    qAddSampleValueControl = new QItemAction(tr("插入SampleValueControl"),this);
    connect(qAddSampleValueControl, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addSampleValueControl(const QModelIndex&)));
    qAddSettingControl = new QItemAction(tr("插入SettingControl"),this);
    connect(qAddSettingControl, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addSettingControl(const QModelIndex&)));
    qAddSCLControl = new QItemAction(tr("插入SCLControl"),this);
    connect(qAddSCLControl, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addSCLControl(const QModelIndex&)));
    qAddLog = new QItemAction(tr("插入Log"),this);
    connect(qAddLog, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addLog(const QModelIndex&)));

    qAddDataSet = new QItemAction(tr("插入DataSet"),this);
    connect(qAddDataSet, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addDataSet(const QModelIndex&)));
    qAddReportControl = new QItemAction(tr("插入ReportControl"),this);
    connect(qAddReportControl, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addReportControl(const QModelIndex&)));
    qAddLogControl = new QItemAction(tr("插入LogControl"),this);
    connect(qAddLogControl, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addLogControl(const QModelIndex&)));
    qAddDOI = new QItemAction(tr("插入DOI"),this);
    connect(qAddDOI, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addDOI(const QModelIndex&)));
    qAddInputs = new QItemAction(tr("插入Inputs"),this);
    connect(qAddInputs, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addInputs(const QModelIndex&)));

    qAddIEDName = new QItemAction(tr("插入IEDName"),this);
    connect(qAddIEDName, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addIEDName(const QModelIndex&)));

    qAddSmvOpts = new QItemAction(tr("插入SmvOpts"),this);
    connect(qAddSmvOpts, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addSmvOpts(const QModelIndex&)));

    qAddFCDA = new QItemAction(tr("插入FCDA"),this);
    connect(qAddFCDA, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addFCDA(const QModelIndex&)));

    qAddOptFields = new QItemAction(tr("插入OptFields"),this);
    connect(qAddOptFields, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addOptFields(const QModelIndex&)));
    qAddRptEnabled = new QItemAction(tr("插入RptEnabled"),this);
    connect(qAddRptEnabled, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addRptEnabled(const QModelIndex&)));
    qAddTrgOps = new QItemAction(tr("插入TrgOps"),this);
    connect(qAddTrgOps, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addTrgOps(const QModelIndex&)));

    qAddClientLN = new QItemAction(tr("插入ClientLN"),this);
    connect(qAddClientLN, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addClientLN(const QModelIndex&)));

    qAddSDI = new QItemAction(tr("插入SDI"),this);
    connect(qAddSDI, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addSDI(const QModelIndex&)));
    qAddDAI = new QItemAction(tr("插入DAI"),this);
    connect(qAddDAI, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addDAI(const QModelIndex&)));

    qAddVal = new QItemAction(tr("插入Val"),this);
    connect(qAddVal, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addVal(const QModelIndex&)));
    qAddValContent = new QItemAction(tr("插入Val值"),this);
    connect(qAddValContent, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addValContent(const QModelIndex&)));

    qAddExtRef = new QItemAction(tr("插入ExtRef"),this);
    connect(qAddExtRef, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addExtRef(const QModelIndex&)));


    qAddLNodeType = new QItemAction(tr("插入LNodeType"),this);
    connect(qAddLNodeType, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addLNodeType(const QModelIndex&)));
    qAddDOType = new QItemAction(tr("插入DOType"),this);
    connect(qAddDOType, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addDOType(const QModelIndex&)));
    qAddDAType = new QItemAction(tr("插入DAType"),this);
    connect(qAddDAType, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addDAType(const QModelIndex&)));
    qAddEnumType = new QItemAction(tr("插入EnumType"),this);
    connect(qAddEnumType, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addEnumType(const QModelIndex&)));

    qAddDO = new QItemAction(tr("插入DO"),this);
    connect(qAddDO, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addDO(const QModelIndex&)));
    qAddSDO = new QItemAction(tr("插入SDO"),this);
    connect(qAddSDO, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addSDO(const QModelIndex&)));
    qAddDA = new QItemAction(tr("插入DA"),this);
    connect(qAddDA, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addDA(const QModelIndex&)));
    qAddBDA = new QItemAction(tr("插入BDA"),this);
    connect(qAddBDA, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addBDA(const QModelIndex&)));
    qAddEnumVal = new QItemAction(tr("插入EnumVal"),this);
    connect(qAddEnumVal, SIGNAL(clicked(const QModelIndex&)), this, SLOT(addEnumVal(const QModelIndex&)));

    qMoveUp = new QItemAction(tr("上移"), this);
    connect(qMoveUp, SIGNAL(clicked(QModelIndex)), this, SLOT(ItemMoveUp(QModelIndex)));

    qMoveDown = new QItemAction(tr("下移"), this);
    connect(qMoveDown, SIGNAL(clicked(QModelIndex)), this, SLOT(ItemMoveDown(QModelIndex)));

    qRefresh = new QAction(tr("刷新"),this);
    connect(qRefresh, SIGNAL(triggered()), this, SLOT(refresh()));
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


    if(objectName().isEmpty())
        setObjectName(QString::fromUtf8("Mainwindow"));
    resize(906, 725);
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/icon/images/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
    setWindowIcon(icon);

    actionNew = new QAction(this);
    actionNew->setObjectName(QString::fromUtf8("actionNew"));
    QIcon icon1;
    icon1.addFile(QString::fromUtf8(":/new/images/document-new.png"), QSize(), QIcon::Normal, QIcon::Off);
    actionNew->setIcon(icon1);
//    connect(actionNew, SIGNAL(triggered()), this, SLOT(onAc)

    actionQuit = new QAction(this);
    actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
    QIcon icon2;
    icon2.addFile(QString::fromUtf8(":/quit/images/window-close.png"), QSize(), QIcon::Normal, QIcon::Off);
    actionQuit->setIcon(icon2);

    actionOpen = new QAction(this);
    actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
    QIcon icon3;
    icon3.addFile(QString::fromUtf8(":/open/images/document-open.png"), QSize(), QIcon::Normal, QIcon::Off);
    actionOpen->setIcon(icon3);

    actionSave = new QAction(this);
    actionSave->setObjectName(QString::fromUtf8("actionSave"));
    QIcon icon4;
    icon4.addFile(QString::fromUtf8(":/save/images/document-save.png"), QSize(), QIcon::Normal, QIcon::Off);
    actionSave->setIcon(icon4);

    actionSaveAs = new QAction(this);
    actionSaveAs->setObjectName(QString::fromUtf8("actionSaveAs"));
    QIcon icon5;
    icon5.addFile(QString::fromUtf8(":/save-as/images/document-save-as.png"), QSize(), QIcon::Normal, QIcon::Off);
    actionSaveAs->setIcon(icon5);

    actionCut = new QAction(this);
    actionCut->setObjectName(QString::fromUtf8("actionCut"));
    QIcon icon6;
    icon6.addFile(QString::fromUtf8(":/cut/images/edit-cut.png"), QSize(), QIcon::Normal, QIcon::Off);
    actionCut->setIcon(icon6);

    actionCopy = new QAction(this);
    actionCopy->setObjectName(QString::fromUtf8("actionCopy"));
    QIcon icon7;
    icon7.addFile(QString::fromUtf8(":/copy/images/edit-copy.png"), QSize(), QIcon::Normal, QIcon::Off);
    actionCopy->setIcon(icon7);

    actionPaste = new QAction(this);
    actionPaste->setObjectName(QString::fromUtf8("actionPaste"));
    QIcon icon8;
    icon8.addFile(QString::fromUtf8(":/paste/images/edit-paste.png"), QSize(), QIcon::Normal, QIcon::Off);
    actionPaste->setIcon(icon8);

    actionExpandAll = new QAction(this);
    actionExpandAll->setObjectName(QString::fromUtf8("actionExpandAll"));

    actionShowAttrLine = new QAction(this);
    actionShowAttrLine->setObjectName(QString::fromUtf8("actionShowAttrLine"));
    actionShowAttrLine->setCheckable(true);

    actionAbout = new QAction(this);
    actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
    actionAbout->setIcon(icon);

    actionAddComment = new QAction(this);
    actionAddComment->setObjectName(QString::fromUtf8("actionAddComment"));

    actionAppendComment = new QAction(this);
    actionAppendComment->setObjectName(QString::fromUtf8("actionAppendComment"));

    actionAddProcessingInstruction = new QAction(this);
    actionAddProcessingInstruction->setObjectName(QString::fromUtf8("actionAddProcessingInstruction"));

    actionAppendProcessingInstruction = new QAction(this);
    actionAppendProcessingInstruction->setObjectName(QString::fromUtf8("actionAppendProcessingInstruction"));

    actionResizeToContents = new QAction(this);
    actionResizeToContents->setObjectName(QString::fromUtf8("actionResizeToContents"));

    actionAddChildElement = new QAction(this);
    actionAddChildElement->setObjectName(QString::fromUtf8("actionAddChildElement"));

    actionAppendChildElement = new QAction(this);
    actionAppendChildElement->setObjectName(QString::fromUtf8("actionAppendChildElement"));

    actionEdit = new QAction(this);
    actionEdit->setObjectName(QString::fromUtf8("actionEdit"));

    actionDelete = new QAction(this);
    actionDelete->setObjectName(QString::fromUtf8("actionDelete"));

    actionMoveUp = new QAction(this);
    actionMoveUp->setObjectName(QString::fromUtf8("actionMoveUp"));
    QIcon icon9;
    icon9.addFile(QString::fromUtf8(":/arrows/images/go-up.png"), QSize(), QIcon::Normal, QIcon::Off);
    actionMoveUp->setIcon(icon9);

    actionMoveDown = new QAction(this);
    actionMoveDown->setObjectName(QString::fromUtf8("actionMoveDown"));
    QIcon icon10;
    icon10.addFile(QString::fromUtf8(":/arrows/images/go-down.png"), QSize(), QIcon::Normal, QIcon::Off);
    actionMoveDown->setIcon(icon10);

    actionFind = new QAction(this);
    actionFind->setObjectName(QString::fromUtf8("actionFind"));
    QIcon icon11;
    icon11.addFile(QString::fromUtf8(":/editText/edit-find"), QSize(), QIcon::Normal, QIcon::Off);
    actionFind->setIcon(icon11);

    actionGo_To_Parent = new QAction(this);
    actionGo_To_Parent->setObjectName(QString::fromUtf8("actionGo_To_Parent"));
    QIcon icon12;
    icon12.addFile(QString::fromUtf8(":/goto/images/gotoparent.png"), QSize(), QIcon::Normal, QIcon::Off);
    actionGo_To_Parent->setIcon(icon12);

    actionGo_to_Previous_Brother = new QAction(this);
    actionGo_to_Previous_Brother->setObjectName(QString::fromUtf8("actionGo_to_Previous_Brother"));
    QIcon icon13;
    icon13.addFile(QString::fromUtf8(":/goto/images/gotoprevbro.png"), QSize(), QIcon::Normal, QIcon::Off);
    actionGo_to_Previous_Brother->setIcon(icon13);

    actionGo_to_Next_Brother = new QAction(this);
    actionGo_to_Next_Brother->setObjectName(QString::fromUtf8("actionGo_to_Next_Brother"));
    QIcon icon14;
    icon14.addFile(QString::fromUtf8(":/goto/images/gotonextbro.png"), QSize(), QIcon::Normal, QIcon::Off);
    actionGo_to_Next_Brother->setIcon(icon14);

    actionShowChildIndex = new QAction(this);
    actionShowChildIndex->setObjectName(QString::fromUtf8("actionShowChildIndex"));
    actionShowChildIndex->setCheckable(true);

    actionCloseThisAllBrothers = new QAction(this);
    actionCloseThisAllBrothers->setObjectName(QString::fromUtf8("actionCloseThisAllBrothers"));

    actionNewFromClipboard = new QAction(this);
    actionNewFromClipboard->setObjectName(QString::fromUtf8("actionNewFromClipboard"));

    actionCompactView = new QAction(this);
    actionCompactView->setObjectName(QString::fromUtf8("actionCompactView"));

    actionHideBrothers = new QAction(this);
    actionHideBrothers->setObjectName(QString::fromUtf8("actionHideBrothers"));
    actionHideBrothers->setCheckable(true);

    actionFixedSizeAttributes = new QAction(this);
    actionFixedSizeAttributes->setObjectName(QString::fromUtf8("actionFixedSizeAttributes"));
    actionFixedSizeAttributes->setCheckable(true);

    actionShowAttributesLength = new QAction(this);
    actionShowAttributesLength->setObjectName(QString::fromUtf8("actionShowAttributesLength"));
    actionShowAttributesLength->setCheckable(true);

    actionShowBase64 = new QAction(this);
    actionShowBase64->setObjectName(QString::fromUtf8("actionShowBase64"));
    actionShowBase64->setCheckable(true);

    actionShowCurrentElementTextBase64 = new QAction(this);
    actionShowCurrentElementTextBase64->setObjectName(QString::fromUtf8("actionShowCurrentElementTextBase64"));
    actionShowCurrentElementTextBase64->setCheckable(true);

    actionConfigure = new QAction(this);
    actionConfigure->setObjectName(QString::fromUtf8("actionConfigure"));
    actionConfigure->setMenuRole(QAction::PreferencesRole);

    actionEditInnerXML = new QAction(this);
    actionEditInnerXML->setObjectName(QString::fromUtf8("actionEditInnerXML"));

    actionEditInnerXMLBase64 = new QAction(this);
    actionEditInnerXMLBase64->setObjectName(QString::fromUtf8("actionEditInnerXMLBase64"));

    actionEditInnerBase64Text = new QAction(this);
    actionEditInnerBase64Text->setObjectName(QString::fromUtf8("actionEditInnerBase64Text"));

    actionZoomIn = new QAction(this);
    actionZoomIn->setObjectName(QString::fromUtf8("actionZoomIn"));

    actionZoomOut = new QAction(this);
    actionZoomOut->setObjectName(QString::fromUtf8("actionZoomOut"));

    actionCompare = new QAction(this);
    actionCompare->setObjectName(QString::fromUtf8("actionCompare"));

    actionReload = new QAction(this);
    actionReload->setObjectName(QString::fromUtf8("actionReload"));

    actionLastFiles = new QAction(this);
    actionLastFiles->setObjectName(QString::fromUtf8("actionLastFiles"));

    actionCopyPathToClipboard = new QAction(this);
    actionCopyPathToClipboard->setObjectName(QString::fromUtf8("actionCopyPathToClipboard"));

    actionAddCurrentDirectory = new QAction(this);
    actionAddCurrentDirectory->setObjectName(QString::fromUtf8("actionAddCurrentDirectory"));

    actionEditPreferredDirectories = new QAction(this);
    actionEditPreferredDirectories->setObjectName(QString::fromUtf8("actionEditPreferredDirectories"));

    actionValidate = new QAction(this);
    actionValidate->setObjectName(QString::fromUtf8("actionValidate"));
    QIcon icon16;
    icon16.addFile(QString::fromUtf8(":/configuration/validation"), QSize(), QIcon::Normal, QIcon::Off);
    actionValidate->setIcon(icon16);

    actionValidateFile = new QAction(this);
    actionValidateFile->setObjectName(QString::fromUtf8("actionValidateFile"));

    actionValidateNewFile = new QAction(this);
    actionValidateNewFile->setObjectName(QString::fromUtf8("actionValidateNewFile"));

    actionInsertSnippet = new QAction(this);
    actionInsertSnippet->setObjectName(QString::fromUtf8("actionInsertSnippet"));

    actionConfigureSnippets = new QAction(this);
    actionConfigureSnippets->setObjectName(QString::fromUtf8("actionConfigureSnippets"));

    actionExecuteAutoTest = new QAction(this);
    actionExecuteAutoTest->setObjectName(QString::fromUtf8("actionExecuteAutoTest"));

    actionPlugins = new QAction(this);
    actionPlugins->setObjectName(QString::fromUtf8("actionPlugins"));

    actionTransforminSnippet = new QAction(this);
    actionTransforminSnippet->setObjectName(QString::fromUtf8("actionTransforminSnippet"));

    actionShowElementTextLength = new QAction(this);
    actionShowElementTextLength->setObjectName(QString::fromUtf8("actionShowElementTextLength"));
    actionShowElementTextLength->setCheckable(true);

    actionShowElementSize = new QAction(this);
    actionShowElementSize->setObjectName(QString::fromUtf8("actionShowElementSize"));
    actionShowElementSize->setCheckable(true);

    actionXplore = new QAction(this);
    actionXplore->setObjectName(QString::fromUtf8("actionXplore"));

    actionBlindLoadFile = new QAction(this);
    actionBlindLoadFile->setObjectName(QString::fromUtf8("actionBlindLoadFile"));

    actionHideView = new QAction(this);
    actionHideView->setObjectName(QString::fromUtf8("actionHideView"));
    actionHideView->setCheckable(true);

    actionSearchInFiles = new QAction(this);
    actionSearchInFiles->setObjectName(QString::fromUtf8("actionSearchInFiles"));
    QIcon icon17;
    icon17.addFile(QString::fromUtf8(":/editText/searchInFiles"), QSize(), QIcon::Normal, QIcon::Off);
    actionSearchInFiles->setIcon(icon17);

    actionHelpOnQXmlEdit = new QAction(this);
    actionHelpOnQXmlEdit->setObjectName(QString::fromUtf8("actionHelpOnQXmlEdit"));
    QIcon icon18;
    icon18.addFile(QString::fromUtf8(":/commands/images/help-contents.png"), QSize(), QIcon::Normal, QIcon::Off);
    actionHelpOnQXmlEdit->setIcon(icon18);

    actionAllowedSchemaElements = new QAction(this);
    actionAllowedSchemaElements->setObjectName(QString::fromUtf8("actionAllowedSchemaElements"));

    actionPasteAndSubstituteText = new QAction(this);
    actionPasteAndSubstituteText->setObjectName(QString::fromUtf8("actionPasteAndSubstituteText"));

    actionNewUsingXMLSchema = new QAction(this);
    actionNewUsingXMLSchema->setObjectName(QString::fromUtf8("actionNewUsingXMLSchema"));

    actionTransformInComment = new QAction(this);
    actionTransformInComment->setObjectName(QString::fromUtf8("actionTransformInComment"));

    actionExtractElementsFromComment = new QAction(this);
    actionExtractElementsFromComment->setObjectName(QString::fromUtf8("actionExtractElementsFromComment"));

    actionInsertNoNamespaceSchemaReferenceAttributes = new QAction(this);
    actionInsertNoNamespaceSchemaReferenceAttributes->setObjectName(QString::fromUtf8("actionInsertNoNamespaceSchemaReferenceAttributes"));

    actionInsertSchemaReferenceAttributes = new QAction(this);
    actionInsertSchemaReferenceAttributes->setObjectName(QString::fromUtf8("actionInsertSchemaReferenceAttributes"));

    actionExtractFragmentsFromFile = new QAction(this);
    actionExtractFragmentsFromFile->setObjectName(QString::fromUtf8("actionExtractFragmentsFromFile"));
    QIcon icon19;
    icon19.addFile(QString::fromUtf8(":/tools/images/split.png"), QSize(), QIcon::Normal, QIcon::Off);
    actionExtractFragmentsFromFile->setIcon(icon19);

    actionWelcomeDialog = new QAction(this);
    actionWelcomeDialog->setObjectName(QString::fromUtf8("actionWelcomeDialog"));

    actionSaveACopyAs = new QAction(this);
    actionSaveACopyAs->setObjectName(QString::fromUtf8("actionSaveACopyAs"));
    actionSaveACopyAs->setIcon(icon5);

    actionHideAllLeafChildren = new QAction(this);
    actionHideAllLeafChildren->setObjectName(QString::fromUtf8("actionHideAllLeafChildren"));
    QIcon icon20;
    icon20.addFile(QString::fromUtf8(":/tree/hidden_children"), QSize(), QIcon::Normal, QIcon::Off);
    actionHideAllLeafChildren->setIcon(icon20);

    actionShowAllLeafChildren = new QAction(this);
    actionShowAllLeafChildren->setObjectName(QString::fromUtf8("actionShowAllLeafChildren"));
    QIcon icon21;
    icon21.addFile(QString::fromUtf8(":/tree/show_children"), QSize(), QIcon::Normal, QIcon::Off);
    actionShowAllLeafChildren->setIcon(icon21);

    actionHideLeafChildren = new QAction(this);
    actionHideLeafChildren->setObjectName(QString::fromUtf8("actionHideLeafChildren"));
    actionHideLeafChildren->setIcon(icon20);

    actionShowLeafChildren = new QAction(this);
    actionShowLeafChildren->setObjectName(QString::fromUtf8("actionShowLeafChildren"));
    actionShowLeafChildren->setIcon(icon21);

    actionViewAsXsd = new QAction(this);
    actionViewAsXsd->setObjectName(QString::fromUtf8("actionViewAsXsd"));

    actionColumnView = new QAction(this);
    actionColumnView->setObjectName(QString::fromUtf8("actionColumnView"));
    QIcon icon22;
    icon22.addFile(QString::fromUtf8(":/commands/view_columns"), QSize(), QIcon::Normal, QIcon::Off);
    actionColumnView->setIcon(icon22);

    actionShowCurrentSessionPanel = new QAction(this);
    actionShowCurrentSessionPanel->setObjectName(QString::fromUtf8("actionShowCurrentSessionPanel"));
    actionShowCurrentSessionPanel->setCheckable(true);
    QIcon icon23;
    icon23.addFile(QString::fromUtf8(":/sessions/images/sessions_view.png"), QSize(), QIcon::Normal, QIcon::Off);
    actionShowCurrentSessionPanel->setIcon(icon23);

    actionNewSession = new QAction(this);
    actionNewSession->setObjectName(QString::fromUtf8("actionNewSession"));

    actionPauseSession = new QAction(this);
    actionPauseSession->setObjectName(QString::fromUtf8("actionPauseSession"));

    actionResumeSession = new QAction(this);
    actionResumeSession->setObjectName(QString::fromUtf8("actionResumeSession"));

    actionCloseSession = new QAction(this);
    actionCloseSession->setObjectName(QString::fromUtf8("actionCloseSession"));

    actionManageSessions = new QAction(this);
    actionManageSessions->setObjectName(QString::fromUtf8("actionManageSessions"));

    actionSessionDetails = new QAction(this);
    actionSessionDetails->setObjectName(QString::fromUtf8("actionSessionDetails"));

    actionUndo = new QAction(this);
    actionUndo->setObjectName(QString::fromUtf8("actionUndo"));

    actionRedo = new QAction(this);
    actionRedo->setObjectName(QString::fromUtf8("actionRedo"));

    actionNewWindow = new QAction(this);
    actionNewWindow->setObjectName(QString::fromUtf8("actionNewWindow"));

    actionViewData = new QAction(this);
    actionViewData->setObjectName(QString::fromUtf8("actionViewData"));
    QIcon icon24;
    icon24.addFile(QString::fromUtf8(":/tools/images/view-structure-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
    actionViewData->setIcon(icon24);

    actionBase64Tools = new QAction(this);
    actionBase64Tools->setObjectName(QString::fromUtf8("actionBase64Tools"));

    actionEncodingTools = new QAction(this);
    actionEncodingTools->setObjectName(QString::fromUtf8("actionEncodingTools"));

    centralwidget = new QWidget(this);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));

    horizontalLayout = new QHBoxLayout(centralwidget);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));

    editor = new XmlEditWidget(centralwidget);
    editor->setObjectName(QString::fromUtf8("editor"));

    horizontalLayout->addWidget(editor);

    setCentralWidget(centralwidget);

    menubar = new QMenuBar(this);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 906 ,21));

    menu_Navigation = new QMenu(menubar);
    menu_Navigation->setObjectName(QString::fromUtf8("menu_Navigation"));

    menuHelp = new QMenu(menubar);
    menuHelp->setObjectName(QString::fromUtf8("menuHelp"));

    menuEdit = new QMenu(menubar);
    menuEdit->setObjectName(QString::fromUtf8("menuEdit"));

    menuFile = new QMenu(menubar);
    menuFile->setObjectName(QString::fromUtf8("menuFile"));

    menu_XML = new QMenu(menubar);
    menu_XML->setObjectName(QString::fromUtf8("menu_XML"));

    menuXML_Schema = new QMenu(menubar);
    menuXML_Schema->setObjectName(QString::fromUtf8("menuXML_Schema"));

    menuTools = new QMenu(menubar);
    menuTools->setObjectName(QString::fromUtf8("menuTools"));

    menuView = new QMenu(menubar);
    menuView->setObjectName(QString::fromUtf8("statusbar"));

    setMenuBar(menubar);

    statusbar = new QStatusBar(this);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    setStatusBar(statusbar);

    toolBar = new QToolBar(this);
    toolBar->setObjectName(QString::fromUtf8("toolBar"));
    addToolBar(Qt::TopToolBarArea, toolBar);

    menubar->addAction(menuFile->menuAction());
    menubar->addAction(menuEdit->menuAction());
    menubar->addAction(menu_XML->menuAction());
    menubar->addAction(menu_Navigation->menuAction());
    menubar->addAction(menuView->menuAction());
    menubar->addAction(menuTools->menuAction());
    menubar->addAction(menuHelp->menuAction());
    menu_Navigation->addAction(actionGo_To_Parent);
    menu_Navigation->addAction(actionGo_to_Previous_Brother);
    menu_Navigation->addAction(actionGo_to_Next_Brother);
    menu_Navigation->addAction(actionCloseThisAllBrothers);
    menuHelp->addAction(actionExecuteAutoTest);
    menuHelp->addAction(actionHelpOnQXmlEdit);
    menuHelp->addAction(actionAbout);
    menuEdit->addAction(actionUndo);
    menuEdit->addAction(actionRedo);
    menuEdit->addAction(actionCut);
    menuEdit->addAction(actionDelete);
    menuEdit->addAction(actionCopy);
    menuEdit->addAction(actionPaste);
    menuEdit->addSeparator();
    menuEdit->addAction(actionFind);
    menuEdit->addSeparator();
    menuEdit->addAction(actionCopyPathToClipboard);
    menuEdit->addAction(actionConfigure);
    menuEdit->addAction(actionConfigureSnippets);
    menuFile->addAction(actionNewWindow);
    menuFile->addAction(actionNew);
    menuFile->addAction(actionNewFromClipboard);
    menuFile->addAction(actionNewUsingXMLSchema);
    menuFile->addAction(actionOpen);
    menuFile->addAction(actionXplore);
    menuFile->addAction(actionSave);
    menuFile->addAction(actionSaveAs);
    menuFile->addAction(actionSaveACopyAs);
    menuFile->addAction(actionReload);
    menuFile->addAction(actionCompare);
    menuFile->addAction(actionLastFiles);
    menuFile->addSeparator();
    menuFile->addAction(actionQuit);
    menuFile->addSeparator();
    menu_XML->addAction(actionAddChildElement);
    menu_XML->addAction(actionAppendChildElement);
    menu_XML->addAction(actionAddComment);
    menu_XML->addAction(actionAppendComment);
    menu_XML->addAction(actionAddProcessingInstruction);
    menu_XML->addAction(actionAppendProcessingInstruction);
    menu_XML->addAction(actionTransformInComment);
    menu_XML->addAction(actionExtractElementsFromComment);
    menu_XML->addAction(actionInsertSnippet);
    menu_XML->addAction(menuXML_Schema->menuAction());
    menu_XML->addSeparator();
    menu_XML->addAction(actionEdit);
    menu_XML->addAction(actionEditInnerXMLBase64);
    menu_XML->addAction(actionEditInnerXML);
    menu_XML->addAction(actionEditInnerBase64Text);
    menu_XML->addAction(actionPasteAndSubstituteText);
    menu_XML->addAction(actionTransforminSnippet);
    menu_XML->addSeparator();
    menu_XML->addAction(actionMoveUp);
    menu_XML->addAction(actionMoveDown);
    menu_XML->addSeparator();
    menu_XML->addAction(actionValidate);
    menu_XML->addAction(actionValidateFile);
    menu_XML->addAction(actionValidateNewFile);
    menuXML_Schema->addAction(actionInsertNoNamespaceSchemaReferenceAttributes);
    menuXML_Schema->addAction(actionInsertSchemaReferenceAttributes);
    menuTools->addAction(actionPlugins);
    menuTools->addAction(actionSearchInFiles);
    menuTools->addAction(actionExtractFragmentsFromFile);
    menuTools->addAction(actionViewData);
    menuTools->addAction(actionBase64Tools);
    menuTools->addAction(actionEncodingTools);
    menuView->addAction(actionShowCurrentSessionPanel);
    menuView->addAction(actionColumnView);
    menuView->addAction(actionHideView);
    menuView->addAction(actionResizeToContents);
    menuView->addAction(actionExpandAll);
    menuView->addAction(actionHideBrothers);
    menuView->addAction(actionHideAllLeafChildren);
    menuView->addAction(actionShowAllLeafChildren);
    menuView->addSeparator();
    menuView->addAction(actionCompactView);
    menuView->addAction(actionShowAttrLine);
    menuView->addAction(actionShowChildIndex);
    menuView->addAction(actionFixedSizeAttributes);
    menuView->addAction(actionShowAttributesLength);
    menuView->addAction(actionShowElementTextLength);
    menuView->addAction(actionShowElementSize);
    menuView->addAction(actionShowBase64);
    menuView->addAction(actionShowCurrentElementTextBase64);
    menuView->addAction(actionHideLeafChildren);
    menuView->addAction(actionShowLeafChildren);
    menuView->addSeparator();
    menuView->addAction(actionZoomIn);
    menuView->addAction(actionZoomOut);
    menuView->addSeparator();
    toolBar->addAction(actionNew);
    toolBar->addAction(actionOpen);
    toolBar->addAction(actionSave);
    toolBar->addSeparator();
    toolBar->addAction(actionCut);
    toolBar->addAction(actionCopy);
    toolBar->addAction(actionPaste);
    toolBar->addSeparator();
    toolBar->addAction(actionShowCurrentSessionPanel);
    toolBar->addAction(actionColumnView);
    toolBar->addSeparator();
    toolBar->addAction(actionFind);
    toolBar->addAction(actionValidate);
    toolBar->addSeparator();
    toolBar->addAction(actionGo_To_Parent);
    toolBar->addAction(actionGo_to_Previous_Brother);
    toolBar->addAction(actionGo_to_Next_Brother);
    toolBar->addSeparator();
    toolBar->addAction(actionHelpOnQXmlEdit);

    retranslateUi();

    QMetaObject::connectSlotsByName(this);

}

void MainWindow::retranslateUi()
{
    setWindowTitle(QApplication::translate("MainWindow", "ICD Creator", 0, QApplication::UnicodeUTF8));
    actionNew->setText(QApplication::translate("MainWindow", "&New", 0, QApplication::UnicodeUTF8));
    actionNew->setIconText(QApplication::translate("MainWindow", "New", 0, QApplication::UnicodeUTF8));
    actionNew->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0, QApplication::UnicodeUTF8));
    actionQuit->setText(QApplication::translate("MainWindow", "&Quit", 0, QApplication::UnicodeUTF8));
    actionQuit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
    actionOpen->setText(QApplication::translate("MainWindow", "&Open...", 0, QApplication::UnicodeUTF8));
    actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0, QApplication::UnicodeUTF8));
    actionSave->setText(QApplication::translate("MainWindow", "&Save", 0, QApplication::UnicodeUTF8));
    actionSave->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0, QApplication::UnicodeUTF8));
    actionSaveAs->setText(QApplication::translate("MainWindow", "Save &As...", 0, QApplication::UnicodeUTF8));
    actionSaveAs->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+S", 0, QApplication::UnicodeUTF8));
    actionCut->setText(QApplication::translate("MainWindow", "&Cut", 0, QApplication::UnicodeUTF8));
    actionCut->setShortcut(QApplication::translate("MainWindow", "Ctrl+X", 0, QApplication::UnicodeUTF8));
    actionCopy->setText(QApplication::translate("MainWindow", "Cop&y", 0, QApplication::UnicodeUTF8));
    actionCopy->setShortcut(QApplication::translate("MainWindow", "Ctrl+C", 0, QApplication::UnicodeUTF8));
    actionPaste->setText(QApplication::translate("MainWindow", "&Paste", 0, QApplication::UnicodeUTF8));
    actionPaste->setShortcut(QApplication::translate("MainWindow", "Ctrl+V", 0, QApplication::UnicodeUTF8));
    actionExpandAll->setText(QApplication::translate("MainWindow", "&Expand", 0, QApplication::UnicodeUTF8));
    actionExpandAll->setShortcut(QApplication::translate("MainWindow", "Ctrl+E", 0, QApplication::UnicodeUTF8));
    actionShowAttrLine->setText(QApplication::translate("MainWindow", "Show &One Attribute per Line", 0, QApplication::UnicodeUTF8));
    actionAbout->setText(QApplication::translate("MainWindow", "&About ICD Creator...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionAbout->setToolTip(QApplication::translate("MainWindow", "About ICD Creator", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionAddComment->setText(QApplication::translate("MainWindow", "Add &Comment as Child...", 0, QApplication::UnicodeUTF8));
    actionAddComment->setShortcut(QApplication::translate("MainWindow", "F3", 0, QApplication::UnicodeUTF8));
    actionAppendComment->setText(QApplication::translate("MainWindow", "Append C&omment as Brother...", 0, QApplication::UnicodeUTF8));
    actionAppendComment->setShortcut(QApplication::translate("MainWindow", "F4", 0, QApplication::UnicodeUTF8));
    actionAddProcessingInstruction->setText(QApplication::translate("MainWindow", "Add Processing Instruction as Child...", 0, QApplication::UnicodeUTF8));
    actionAddProcessingInstruction->setShortcut(QApplication::translate("MainWindow", "F5", 0, QApplication::UnicodeUTF8));
    actionAppendProcessingInstruction->setText(QApplication::translate("MainWindow", "Append Processing Instruction as Brother...", 0, QApplication::UnicodeUTF8));
    actionAppendProcessingInstruction->setShortcut(QApplication::translate("MainWindow", "F6", 0, QApplication::UnicodeUTF8));
    actionResizeToContents->setText(QApplication::translate("MainWindow", "&Resize to Contents", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionResizeToContents->setToolTip(QApplication::translate("MainWindow", "Auto resize the columns", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionResizeToContents->setShortcut(QApplication::translate("MainWindow", "Ctrl+R", 0, QApplication::UnicodeUTF8));
    actionAddChildElement->setText(QApplication::translate("MainWindow", "Add a Child Element...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionAddChildElement->setToolTip(QApplication::translate("MainWindow", "Add a new element", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionAddChildElement->setShortcut(QApplication::translate("MainWindow", "Ctrl+1", 0, QApplication::UnicodeUTF8));
    actionAppendChildElement->setText(QApplication::translate("MainWindow", "Append a Brother Element...", 0, QApplication::UnicodeUTF8));
    actionAppendChildElement->setShortcut(QApplication::translate("MainWindow", "Ctrl+2", 0, QApplication::UnicodeUTF8));
    actionEdit->setText(QApplication::translate("MainWindow", "&Properties...", 0, QApplication::UnicodeUTF8));
    actionEdit->setShortcut(QApplication::translate("MainWindow", "Alt+Return", 0, QApplication::UnicodeUTF8));
    actionDelete->setText(QApplication::translate("MainWindow", "Delete", 0, QApplication::UnicodeUTF8));
    actionDelete->setShortcut(QApplication::translate("MainWindow", "Ctrl+D", 0, QApplication::UnicodeUTF8));
    actionMoveUp->setText(QApplication::translate("MainWindow", "Move &Up", 0, QApplication::UnicodeUTF8));
    actionMoveUp->setShortcut(QApplication::translate("MainWindow", "Ctrl+K", 0, QApplication::UnicodeUTF8));
    actionMoveDown->setText(QApplication::translate("MainWindow", "Move Do&wn", 0, QApplication::UnicodeUTF8));
    actionMoveDown->setShortcut(QApplication::translate("MainWindow", "Ctrl+M", 0, QApplication::UnicodeUTF8));
    actionFind->setText(QApplication::translate("MainWindow", "&Find...", 0, QApplication::UnicodeUTF8));
    actionFind->setShortcut(QApplication::translate("MainWindow", "Ctrl+F", 0, QApplication::UnicodeUTF8));
    actionGo_To_Parent->setText(QApplication::translate("MainWindow", "Go To Parent", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionGo_To_Parent->setToolTip(QApplication::translate("MainWindow", "Move to the parent", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionGo_To_Parent->setShortcut(QApplication::translate("MainWindow", "F11", 0, QApplication::UnicodeUTF8));
    actionGo_to_Previous_Brother->setText(QApplication::translate("MainWindow", "Go to Previous Brother", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionGo_to_Previous_Brother->setToolTip(QApplication::translate("MainWindow", "Go to Previous Brother", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionGo_to_Previous_Brother->setShortcut(QApplication::translate("MainWindow", "F9", 0, QApplication::UnicodeUTF8));
    actionGo_to_Next_Brother->setText(QApplication::translate("MainWindow", "Go to Next Brother", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionGo_to_Next_Brother->setToolTip(QApplication::translate("MainWindow", "Go to Previous Brother", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionGo_to_Next_Brother->setShortcut(QApplication::translate("MainWindow", "F10", 0, QApplication::UnicodeUTF8));
    actionShowChildIndex->setText(QApplication::translate("MainWindow", "Show Child &Index", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionShowChildIndex->setToolTip(QApplication::translate("MainWindow", "Show Child Index", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionCloseThisAllBrothers->setText(QApplication::translate("MainWindow", "Close This and All Brothers", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionCloseThisAllBrothers->setToolTip(QApplication::translate("MainWindow", "Close This and All Brothers", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionCloseThisAllBrothers->setShortcut(QApplication::translate("MainWindow", "F12", 0, QApplication::UnicodeUTF8));
    actionNewFromClipboard->setText(QApplication::translate("MainWindow", "New From &Clipboard", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionNewFromClipboard->setToolTip(QApplication::translate("MainWindow", "import XML from clipboard", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionCompactView->setText(QApplication::translate("MainWindow", "&Compact View", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionCompactView->setToolTip(QApplication::translate("MainWindow", "Compact View", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionHideBrothers->setText(QApplication::translate("MainWindow", "&Hide Brothers", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionHideBrothers->setToolTip(QApplication::translate("MainWindow", "Hide Brothers", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionFixedSizeAttributes->setText(QApplication::translate("MainWindow", "&Fixed Size Attributes", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionFixedSizeAttributes->setToolTip(QApplication::translate("MainWindow", "Show Attributes with Fixed Size Font", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionShowAttributesLength->setText(QApplication::translate("MainWindow", "Show Attributes &Length", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionShowAttributesLength->setToolTip(QApplication::translate("MainWindow", "Show Attributes Length", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionShowBase64->setText(QApplication::translate("MainWindow", "Show Text as Base 64 Coded", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionShowBase64->setToolTip(QApplication::translate("MainWindow", "Show Text as Base 64 Coded", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionShowCurrentElementTextBase64->setText(QApplication::translate("MainWindow", "Show Current Element Text Base 64", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionShowCurrentElementTextBase64->setToolTip(QApplication::translate("MainWindow", "Show Current Element Text Base 64", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionConfigure->setText(QApplication::translate("MainWindow", "Confi&gure...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionConfigure->setToolTip(QApplication::translate("MainWindow", "Configure", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionEditInnerXML->setText(QApplication::translate("MainWindow", "Edit Inner XML...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionEditInnerXML->setToolTip(QApplication::translate("MainWindow", "Edit inner XML", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionEditInnerXMLBase64->setText(QApplication::translate("MainWindow", "Edit Inner XML Base 64 Coded...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionEditInnerXMLBase64->setToolTip(QApplication::translate("MainWindow", "Edit inner XML Base 64 Coded", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionEditInnerBase64Text->setText(QApplication::translate("MainWindow", "Edit inner Base 64 Text...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionEditInnerBase64Text->setToolTip(QApplication::translate("MainWindow", "Edit inner Base 64 Text", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionZoomIn->setText(QApplication::translate("MainWindow", "Zoom In", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionZoomIn->setToolTip(QApplication::translate("MainWindow", "Zoom In", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionZoomOut->setText(QApplication::translate("MainWindow", "Zoom Out", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionZoomOut->setToolTip(QApplication::translate("MainWindow", "Zoom Out", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionCompare->setText(QApplication::translate("MainWindow", "Compare...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionCompare->setToolTip(QApplication::translate("MainWindow", "Compare with another XML file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionReload->setText(QApplication::translate("MainWindow", "Reload", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionReload->setToolTip(QApplication::translate("MainWindow", "Reload the current file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionLastFiles->setText(QApplication::translate("MainWindow", "Last Files", 0, QApplication::UnicodeUTF8));
    actionCopyPathToClipboard->setText(QApplication::translate("MainWindow", "Copy Path to Clipboard", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionCopyPathToClipboard->setToolTip(QApplication::translate("MainWindow", "Copy path to clipboard", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionAddCurrentDirectory->setText(QApplication::translate("MainWindow", "Add Current Directory to Preferred Ones", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionAddCurrentDirectory->setToolTip(QApplication::translate("MainWindow", "Add the current directory to Preferred Ones", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionEditPreferredDirectories->setText(QApplication::translate("MainWindow", "Edit Preferred Directories...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionEditPreferredDirectories->setToolTip(QApplication::translate("MainWindow", "Edit Preferred Directories", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionValidate->setText(QApplication::translate("MainWindow", "Validate Using Document References", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionValidate->setToolTip(QApplication::translate("MainWindow", "Validate against a XSD", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionValidateFile->setText(QApplication::translate("MainWindow", "Validate Using Specified File", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionValidateFile->setToolTip(QApplication::translate("MainWindow", "Validate using specified file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionValidateNewFile->setText(QApplication::translate("MainWindow", "Validate Using New Schema File...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionValidateNewFile->setToolTip(QApplication::translate("MainWindow", "Validate using new XSD File...", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionInsertSnippet->setText(QApplication::translate("MainWindow", "Insert Snippet...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionInsertSnippet->setToolTip(QApplication::translate("MainWindow", "Insert a XML fragment", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionConfigureSnippets->setText(QApplication::translate("MainWindow", "Configure Snippets...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionConfigureSnippets->setToolTip(QApplication::translate("MainWindow", "Configure Snippets", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionExecuteAutoTest->setText(QApplication::translate("MainWindow", "Execute Auto Test", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionExecuteAutoTest->setToolTip(QApplication::translate("MainWindow", "Execute Auto Test", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionPlugins->setText(QApplication::translate("MainWindow", "Plugins", 0, QApplication::UnicodeUTF8));
    actionTransforminSnippet->setText(QApplication::translate("MainWindow", "Transform in Snippet...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionTransforminSnippet->setToolTip(QApplication::translate("MainWindow", "Transform in Snippet", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionShowElementTextLength->setText(QApplication::translate("MainWindow", "Show Element Text Length", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionShowElementTextLength->setToolTip(QApplication::translate("MainWindow", "Show Element Text Length", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionShowElementSize->setText(QApplication::translate("MainWindow", "Show Element Size", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionShowElementSize->setToolTip(QApplication::translate("MainWindow", "Show element size", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionXplore->setText(QApplication::translate("MainWindow", "Explore Structure...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionXplore->setToolTip(QApplication::translate("MainWindow", "Explore structure loading only partial informations about a file.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionBlindLoadFile->setText(QApplication::translate("MainWindow", "Blind Load File...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionBlindLoadFile->setToolTip(QApplication::translate("MainWindow", "load a file in blind mode", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionHideView->setText(QApplication::translate("MainWindow", "Hide View", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionHideView->setToolTip(QApplication::translate("MainWindow", "Hide graphics view", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionSearchInFiles->setText(QApplication::translate("MainWindow", "Search in Files...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionSearchInFiles->setToolTip(QApplication::translate("MainWindow", "Search in files", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionHelpOnQXmlEdit->setText(QApplication::translate("MainWindow", "Help on ICD Creator", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionHelpOnQXmlEdit->setToolTip(QApplication::translate("MainWindow", "Help on ICD Creator", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionAllowedSchemaElements->setText(QApplication::translate("MainWindow", "Allowed Schema Elements", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionAllowedSchemaElements->setToolTip(QApplication::translate("MainWindow", "Allowed Schema Elements", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionPasteAndSubstituteText->setText(QApplication::translate("MainWindow", "Edit Inner Text as One Node...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionPasteAndSubstituteText->setToolTip(QApplication::translate("MainWindow", "Paste and substitute element text", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionNewUsingXMLSchema->setText(QApplication::translate("MainWindow", "New Using XML Schema...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionNewUsingXMLSchema->setToolTip(QApplication::translate("MainWindow", "Creates a new XML Document using a XML Schema", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionTransformInComment->setText(QApplication::translate("MainWindow", "Transform in Comment", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionTransformInComment->setToolTip(QApplication::translate("MainWindow", "Transform in comment", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionExtractElementsFromComment->setText(QApplication::translate("MainWindow", "Extract Elements from Comment", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionExtractElementsFromComment->setToolTip(QApplication::translate("MainWindow", "Extract elements from comment.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionInsertNoNamespaceSchemaReferenceAttributes->setText(QApplication::translate("MainWindow", "Insert No Namespace Schema Reference Attributes", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionInsertNoNamespaceSchemaReferenceAttributes->setToolTip(QApplication::translate("MainWindow", "Insert No Namespace Schema Reference Attributes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionInsertSchemaReferenceAttributes->setText(QApplication::translate("MainWindow", "Insert Schema Reference Attributes", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionInsertSchemaReferenceAttributes->setToolTip(QApplication::translate("MainWindow", "Insert Schema Reference Attributes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionExtractFragmentsFromFile->setText(QApplication::translate("MainWindow", "Extract Fragments From a File...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionExtractFragmentsFromFile->setToolTip(QApplication::translate("MainWindow", "Extract XML fragments from a huge file...", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionWelcomeDialog->setText(QApplication::translate("MainWindow", "Welcome Dialog...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionWelcomeDialog->setToolTip(QApplication::translate("MainWindow", "Show the welcome dialog.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionSaveACopyAs->setText(QApplication::translate("MainWindow", "Save a Copy As...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionSaveACopyAs->setToolTip(QApplication::translate("MainWindow", "Saves a copy of the current file. Current file path will not be affected.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionHideAllLeafChildren->setText(QApplication::translate("MainWindow", "Hide All the Leaf Children", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionHideAllLeafChildren->setToolTip(QApplication::translate("MainWindow", "Hide all the nodes that does not have children, revealing the structure.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionShowAllLeafChildren->setText(QApplication::translate("MainWindow", "Show All the Leaf Children", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionShowAllLeafChildren->setToolTip(QApplication::translate("MainWindow", "Show all the leaf nodes that was previously hidden.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionHideLeafChildren->setText(QApplication::translate("MainWindow", "Hide Leaf Children", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionHideLeafChildren->setToolTip(QApplication::translate("MainWindow", "Hide the children of the current node that does not have children, revealing the structure.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionShowLeafChildren->setText(QApplication::translate("MainWindow", "Show Leaf Children", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionShowLeafChildren->setToolTip(QApplication::translate("MainWindow", "Show the leaf nodes of the current node that was previously hidden.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionViewAsXsd->setText(QApplication::translate("MainWindow", "View As Xsd", 0, QApplication::UnicodeUTF8));
    actionColumnView->setText(QApplication::translate("MainWindow", "Columnar View...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionColumnView->setToolTip(QApplication::translate("MainWindow", "View as columns.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionShowCurrentSessionPanel->setText(QApplication::translate("MainWindow", "Show Current Session Panel", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionShowCurrentSessionPanel->setToolTip(QApplication::translate("MainWindow", "Opens the session panel.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionNewSession->setText(QApplication::translate("MainWindow", "New...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionNewSession->setToolTip(QApplication::translate("MainWindow", "Creates a new session.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionPauseSession->setText(QApplication::translate("MainWindow", "Pause", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionPauseSession->setToolTip(QApplication::translate("MainWindow", "Pauses the current session.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionResumeSession->setText(QApplication::translate("MainWindow", "Resume", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionResumeSession->setToolTip(QApplication::translate("MainWindow", "Resume the current session.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionCloseSession->setText(QApplication::translate("MainWindow", "Close", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionCloseSession->setToolTip(QApplication::translate("MainWindow", "Closes the current session.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionManageSessions->setText(QApplication::translate("MainWindow", "Manage...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionManageSessions->setToolTip(QApplication::translate("MainWindow", "Manage the sessions.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionSessionDetails->setText(QApplication::translate("MainWindow", "Details...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionSessionDetails->setToolTip(QApplication::translate("MainWindow", "Details about the current session.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionUndo->setText(QApplication::translate("MainWindow", "Undo", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionUndo->setToolTip(QApplication::translate("MainWindow", "Undo last action.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionUndo->setShortcut(QApplication::translate("MainWindow", "Ctrl+Z", 0, QApplication::UnicodeUTF8));
    actionRedo->setText(QApplication::translate("MainWindow", "Redo", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionRedo->setToolTip(QApplication::translate("MainWindow", "Redo last action.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionRedo->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+Z", 0, QApplication::UnicodeUTF8));
    actionNewWindow->setText(QApplication::translate("MainWindow", "New Window", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionNewWindow->setToolTip(QApplication::translate("MainWindow", "Opens a new window.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionViewData->setText(QApplication::translate("MainWindow", "View data...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionViewData->setToolTip(QApplication::translate("MainWindow", "Navigates a data file.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionBase64Tools->setText(QApplication::translate("MainWindow", "Base 64 Tools...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionBase64Tools->setToolTip(QApplication::translate("MainWindow", "Base 64 tools", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    actionEncodingTools->setText(QApplication::translate("MainWindow", "Encoding Tools...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionEncodingTools->setToolTip(QApplication::translate("MainWindow", "Encoding Tools.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    menu_Navigation->setTitle(QApplication::translate("MainWindow", "&Navigation", 0, QApplication::UnicodeUTF8));
    menuHelp->setTitle(QApplication::translate("MainWindow", "&Help", 0, QApplication::UnicodeUTF8));
    menuEdit->setTitle(QApplication::translate("MainWindow", "&Edit", 0, QApplication::UnicodeUTF8));
    menuFile->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
    menu_XML->setTitle(QApplication::translate("MainWindow", "&XML", 0, QApplication::UnicodeUTF8));
    menuXML_Schema->setTitle(QApplication::translate("MainWindow", "XML Schema", 0, QApplication::UnicodeUTF8));
    menuTools->setTitle(QApplication::translate("MainWindow", "&Tools", 0, QApplication::UnicodeUTF8));
    menuView->setTitle(QApplication::translate("MainWindow", "&View", 0, QApplication::UnicodeUTF8));
    toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));

}

QString MainWindow::editNodeElementAsXML(const bool isBase64Coded, DomItem *pItem, const QString &text, const bool isCData, bool &isCDataOut, bool &isOk)
{
    return tr("");
}

void MainWindow::cleanExtractResults()
{
}

void MainWindow::deleteSchema()
{
    editor->deleteSchema();
}

void MainWindow::autoTest()
{

}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch(e->type()) {
    case QEvent::StyleChange:
        VStyle::changeDefaultBrush(QApplication::palette().text());
        break;
    default:
        break;
    }
}

void MainWindow::on_actionNew_triggered()
{
    if(!verifyAbandonChanges()) {
        return ;
    }
    editor->doNew();
}

void MainWindow::startUIState()
{
    actionPaste->setEnabled(false);
    actionResizeToContents->setEnabled(true);
}

bool MainWindow::finishSetUpUi()
{
    if(editor->versionNumber() != VERSION_NUMBER) {
        Utils::error(this, tr("The XML Editor component is not correct (%1)").arg(editor->versionNumber()));
        return false;
    }
//    editor->setData(appl);
    if(editor->init()) {
        Utils::error(this, tr("XML Editor initialization failed"));
        return false;
    }

    connect(editor, SIGNAL(documentIsModified(bool)), this, SLOT(onDocumentIsModified(bool)));
    connect(editor, SIGNAL(reevaluateSelectionState()), this, SLOT(onComputeSelectionState()));
    connect(editor, SIGNAL(signalSetClipBoardActionsState(bool)), this, SLOT(setClipBoardActionsState(bool)));
    connect(editor, SIGNAL(okClicked()), this, SLOT(on_ok_clicked()));
    connect(editor, SIGNAL(cancelClicked()), this, SLOT(on_cancel_clicked()));
    connect(editor, SIGNAL(viewAsXsdRequested()), this, SLOT(on_actionViewAsXsd_triggered()));
    connect(editor, SIGNAL(schemaLabelChanged(QString)), this, SLOT(schemaLoadComplete(QString)));
    connect(editor, SIGNAL(dataReadyMessage(QString)), this, SLOT(onNewMessage(QString)));
    connect(editor, SIGNAL(loadCurrentPage(int)), this, SLOT(navigateToPage(int)));
    connect(editor, SIGNAL(showStatusMessage(QString,bool)), this, SLOT(onShowStatusMessage(QString,bool)));
    connect(editor, SIGNAL(undoStateUpdated(bool,bool)), this, SLOT(onUndoStateUpdated(bool,bool)));

    startUIState();
    actionShowAttrLine->setCheckable(true);
    actionShowChildIndex->setCheckable(true);
    actionCompactView->setCheckable(true);
    actionHideBrothers->setCheckable(true);
    actionShowBase64->setCheckable(true);
    actionShowCurrentElementTextBase64->setCheckable(true);
    actionShowElementSize->setCheckable(true);

    actionFixedSizeAttributes->setCheckable(true);
    actionShowAttributesLength->setCheckable(true);
    actionShowElementTextLength->setCheckable(true);
    actionHideView->setCheckable(true);
    PaintInfo *paintInfo = editor->getPaintInfo();
    actionShowAttrLine->setChecked(paintInfo->oneAttrPerLine());
    actionShowElementTextLength->setChecked(paintInfo->showItemTextLength());
    actionShowChildIndex->setChecked(paintInfo->indexPerChild());
    actionCompactView->setChecked(paintInfo->compactView());
    actionFixedSizeAttributes->setChecked(paintInfo->userFixedLengthFont());
    actionShowAttributesLength->setChecked(paintInfo->showAttributesLength());
    actionShowBase64->setChecked(paintInfo->showUnBase64());
    actionShowElementSize->setChecked(paintInfo->showItemSize());
    actionHideView->setChecked(paintInfo->hideView());

    updateUndoState(false, false);

    connect(editor, SIGNAL(treeContextMenuRequested(QPoint)), this, SLOT(treeContextMenu(QPoint)));

    menu_XML->setTearOffEnabled(true);

    bool isOk = true;
    QToolButton *editTextButton = new QToolButton(this);
    QMenu *editTextMenu = new QMenu(this);
    if((NULL == editTextButton) || (editTextMenu == NULL)) {
        isOk = true;
    } else {
        editTextMenu->addAction(actionPasteAndSubstituteText);
        editTextMenu->addAction(actionEditInnerBase64Text);
        editTextMenu->addAction(actionEditInnerXML);
        editTextMenu->addAction(actionEditInnerXMLBase64);
        editTextButton->setMenu(editTextMenu);
        editTextButton->setPopupMode(QToolButton::InstantPopup);
        editTextButton->setIcon(QIcon(":/commands/modify"));
        toolBar->insertWidget(actionHelpOnQXmlEdit, editTextButton);
        toolBar->insertSeparator(actionHelpOnQXmlEdit);
    }

    actionLastFiles->setVisible(false);
    QMenu *recentFiles = new QMenu(this);
    if(NULL == recentFiles) {
        isOk = false;
    } else {
        recentFiles->setTitle(tr("Recent Files"));
        menuFile->insertMenu(actionLastFiles, recentFiles);

        if(!buildLastObjects(maxLastFiles, lastFiles, SLOT(onRecentFile()), recentFiles)) {
            isOk = false;
        }
    }

    QMenu *preferredDirsMenu = new QMenu(this);
    if(NULL == preferredDirsMenu) {
        isOk = false;
    } else {
        preferredDirsMenu->setTitle(tr("Preferred Directories"));
        menuFile->insertMenu(actionLastFiles, preferredDirsMenu);
        preferredDirsMenu->addAction(actionEditPreferredDirectories);
        preferredDirsMenu->addAction(actionAddCurrentDirectory);
        preferredDirsMenu->addSeparator();

        if(!buildLastObjects(maxPrefDirs, preferredDirs, SLOT(onPreferredDir()), preferredDirsMenu)) {
            isOk = false;
        }
    }

    QMenu *pluginsMenu = new QMenu(this);
    if(NULL == pluginsMenu) {
        isOk = false;
    } else {
        actionPlugins->setMenu(pluginsMenu);
        if(!buildPluginsMenu(SLOT(onPlugin()), pluginsMenu)) {
            isOk = false;
        }
    }

    return isOk;
}

bool MainWindow::buildLastObjects(const int maxObjects, QList<QAction*> &cmdList, const char *method, QMenu *parent)
{
    bool isOk = true ;
    //--- last files and dirs
    for(int i = 0 ; i < maxObjects ; i++) {
        QAction *action = new QAction(this);
        if(NULL != action) {
            cmdList.append(action);
            action->setVisible(false);
            connect(action, SIGNAL(triggered()), this, method);
            parent->addAction(action);
        } else {
            isOk = false;
        }
    }
    return isOk;
}


QAction *MainWindow::createAnAction(QMenu *menu, const QString &label, const QString &tag, const QString &tooltip)
{
    QAction *action = new QAction(menu);
    action->setText(label);
    action->setData(tag);
    action->setToolTip(tooltip);
    return action ;
    //TODO -14-
}

void MainWindow::repaint()
{
    editor->repaint();
}

void MainWindow::display()
{
    editor->display();
}

void MainWindow::treeContextMenu(const QPoint& position)
{
    QMenu contextMenu(this);
    contextMenu.addAction(actionCut);
    contextMenu.addAction(actionCopy);
    bool isActionMode = editor->isActionMode();
    if(isActionMode) {
        contextMenu.addAction(actionPaste);
    }
    contextMenu.addSeparator() ;
    if(isActionMode) {
        contextMenu.addAction(actionPasteAndSubstituteText);
        contextMenu.addAction(actionEditInnerBase64Text);
    }
//    if(!isSlave && isActionMode) {
    if(isActionMode) {
        contextMenu.addAction(actionEditInnerXML);
    }
    if(isActionMode) {
        contextMenu.addAction(actionEditInnerXMLBase64);
        contextMenu.addAction(actionTransforminSnippet);
        contextMenu.addSeparator() ;
        contextMenu.addAction(actionMoveUp);
        contextMenu.addAction(actionMoveDown);
    }
    DomItem *element = getSelectedItem();
    if(NULL != element) {
        if(element->areChildrenLeavesHidden(element->getUI())) {
            contextMenu.addAction(actionShowLeafChildren);
        } else {
            contextMenu.addAction(actionHideLeafChildren);
        }
    }

#ifdef XSD_INTEGRATION
    if(NULL != editor->schema()) {
        //SchemaValidator validator;
        // TODO: redo
        /*QStringList options = validator.checkInsertionPoint(_schemaRoot, regola, getSelectedItem());
        QMenu *menu = new QMenu(&contextMenu);
        if(NULL != menu) {
            ui.actionAllowedSchemaElements->setMenu(menu);
            foreach( QString item, options ) {
                QAction *action = new QAction( item, &contextMenu );
                menu->addAction( action );
            }
        }*/
        contextMenu.addSeparator() ;
        contextMenu.addAction(actionAllowedSchemaElements);
    }
#endif
    contextMenu.exec(editor->getMainTreeWidget()->mapToGlobal(position));
}

// Solo il salva come...
void MainWindow::onDocumentIsModified(const bool isModified)
{
    TRACEQ(QString("MainWindow::onDocumentIsModified(%1)").arg(isModified));
    bool isFileName = false;
    DomModel *model = editor->getModel();
    if(!model->fileName().isEmpty()) {
        isFileName = true ;
    }
    actionSave->setEnabled(isFileName && editor->isActionNoScanMode());
    bool modelIsEmpty = model->isEmpty(false);
    actionSaveAs->setEnabled(!modelIsEmpty);
    actionSaveACopyAs->setEnabled(!modelIsEmpty);
    setFileTitle();
    setWindowModified(isModified);
}

//cambia la sel clipb.
void MainWindow::setClipBoardActionsState(const bool isAction)
{
    actionPaste->setEnabled(isAction && editor->isActionMode());
}

void MainWindow::onComputeSelectionState()
{
    DomModel *model = getModel();
    bool isSomeItemSelected = false;
    bool selectSpecials = false;
    bool selectSpecialsUp = false;
    bool selectSpecialsDown = false;
    bool isNormalViewState = true;
    bool canAddChild = false;
    bool isShownAsBase64 = false ;
    qxmledit::EDisplayMode displayMode = editor->displayMode();
    bool isExplore = (displayMode != qxmledit::NORMAL) && (displayMode != qxmledit::SCAN) ;
    int numberSelected = editor->getMainTreeWidget()->selectedItems().size();
    if(numberSelected > 0) {
        selectSpecials = true ;
        selectSpecialsUp = true ;
        selectSpecialsDown = true ;
        DomItem *item = DomItem::fromItemData(editor->getMainTreeWidget()->selectedItems().at(0));
        selectSpecialsUp = !item->isFirstChild();
        selectSpecialsDown = !item->isLastChild();
        if(item->getType() == DomItem::ET_ELEMENT)
            canAddChild = true;
        isNormalViewState = item->isNormalViewState();
        isSomeItemSelected = true ;
        isShownAsBase64 = item->isShownBase64();
        //if il primo item
        //disabilita accoda, mvup e down
        //altrimenti se il selected si trova al primo o ultimo posto della catena deselezmv up o down
    } else {
        if(model->isEmpty(true))
            canAddChild = true;
    }
    bool enableGoToParent = false;
    bool enableNextBrother = false;
    bool enablePreviousBrother = false;
    bool isComment = false ;
    DomItem *item = NULL ;
    if(1 == numberSelected) {
        item = getSelectedItem();
        if(NULL != item) {
            if(item->getType() == DomItem::ET_COMMENT) {
                isComment = true ;
            }
            if(NULL != item->parent()) {
                enableGoToParent = true;
            }
            bool isLast = false;
            bool isFirst = false;
            item->isFirstOrLastChild(isFirst, isLast);
            enableNextBrother = !isLast;
            enablePreviousBrother = !isFirst ;
        }
    }
    actionAddChildElement->setEnabled(canAddChild && !isExplore);
    actionAppendChildElement->setEnabled(selectSpecials && !isExplore);
    actionAddComment->setEnabled(!isExplore);
    actionAppendComment->setEnabled(selectSpecials && !isExplore);
    actionAppendProcessingInstruction->setEnabled(selectSpecials && !isExplore);
    actionAddProcessingInstruction->setEnabled(!isExplore);
    actionDelete->setEnabled(isSomeItemSelected && !isExplore);
    actionEditInnerBase64Text->setEnabled(isSomeItemSelected && !isExplore);
//    actionEditInnerXML->setEnabled(isSomeItemSelected && !isSlave && !isExplore);
    actionEditInnerXML->setEnabled(isSomeItemSelected);
    actionEditInnerXMLBase64->setEnabled(isSomeItemSelected && !isExplore);
    actionEdit->setEnabled(isSomeItemSelected);
    actionMoveUp->setEnabled(selectSpecialsUp && !isExplore);
    actionMoveDown->setEnabled(selectSpecialsDown && !isExplore);
    actionCut->setEnabled(isSomeItemSelected);
    actionCopy->setEnabled(isSomeItemSelected);
    actionGo_to_Next_Brother->setEnabled(enableNextBrother);
    actionGo_to_Previous_Brother->setEnabled(enablePreviousBrother);
    actionGo_To_Parent->setEnabled(enableGoToParent);

    actionHideBrothers->setEnabled(isSomeItemSelected);
    actionHideBrothers->setChecked(!isNormalViewState);
    actionShowCurrentElementTextBase64->setEnabled(isSomeItemSelected && !isExplore);
    actionShowCurrentElementTextBase64->setChecked(isShownAsBase64);
    actionReload->setEnabled((NULL != model) && !model->fileName().isEmpty());
    enableZoom();
    actionCopyPathToClipboard->setEnabled((NULL != model) && !model->fileName().isEmpty());
    actionAddCurrentDirectory->setEnabled((NULL != model) && !model->fileName().isEmpty());
    // TODO: test
    //ui.testNext->setEnabled((NULL!=regola)?regola->nextBookmark()>=0:false);
    //ui.testPrev->setEnabled((NULL!=regola)?regola->previousBookmark()>=0:false);

    actionValidate->setEnabled((NULL != model) && !isExplore);

    actionValidateFile->setEnabled((NULL != model) && ! model->userDefinedXsd().isEmpty() && !isExplore);
    actionValidateNewFile->setEnabled((NULL != model) && !isExplore);
    actionTransforminSnippet->setEnabled(isSomeItemSelected && !isExplore);

    actionViewAsXsd->setEnabled(isValidXsd() && !isExplore);

    actionTransformInComment->setEnabled(isSomeItemSelected && !isExplore && !isComment);
    actionExtractElementsFromComment->setEnabled(isSomeItemSelected && !isExplore && isComment);

    actionInsertNoNamespaceSchemaReferenceAttributes->setEnabled((NULL != model) && !isExplore);
    actionInsertSchemaReferenceAttributes->setEnabled((NULL != model) && !isExplore);
    //TODO: always???? ui.actionExtractFragmentsFromFile->setEnabled(XXX);

    actionNewUsingXMLSchema->setEnabled(true);
    actionNewUsingXMLSchema->setVisible(true);

    evaluateSingleItemLeaves(item);
}

void MainWindow::evaluateSingleItemLeaves(DomItem *item)
{
    bool isHiddenLeaves = false;
    bool isVisibleLeaves = false;
    if(NULL != item) {
        if(!item->isALeaf()) {
            if(item->areChildrenLeavesHidden(item->getUI())) {
                isHiddenLeaves = true ;
            } else {
                isVisibleLeaves = true;
            }
        }
    }
    actionHideLeafChildren->setEnabled(isVisibleLeaves);
    actionShowLeafChildren->setEnabled(isHiddenLeaves);
}

void MainWindow::enableZoom()
{
    PaintInfo *paintInfo = editor->getPaintInfo();
    actionZoomIn->setEnabled(paintInfo->canZoomIn());
    actionZoomOut->setEnabled(paintInfo->canZoomOut());
}

DomItem *MainWindow::getSelectedItem()
{
    return editor->getSelectedItem();
}

void MainWindow::resetTree()
{
    editor->resetTree();
}

void MainWindow::on_actionOpen_triggered()
{
    openFileUsingDialog(getModel()->fileName());
}

void MainWindow::openFileUsingDialog(const QString folderPath)
{
    if(!MainWindow::checkAbandonChanges()) {
        return ;
    }
    QString filePath = QFileDialog::getOpenFileName(
                           this, tr("Open File"),
                           folderPath,
                           tr("XML files (*.xml);;XML Schema files (*.xsd);;All files (*);;")
                       );
    if(!filePath.isEmpty()) {
        loadFile(filePath);
    }
}

void MainWindow::on_actionNewFromClipboard_triggered()
{
    if(!MainWindow::checkAbandonChanges()) {
        return ;
    }
    editor->onActionNewFromClipboard();
}


void MainWindow::on_actionResizeToContents_triggered()
{
    editor->resizeTreeColumns();
}

void MainWindow::on_actionSaveAs_triggered()
{
    DomModel * model = getModel();
    if(NULL == model) {
        error(tr("No data to save."));
        return ;
    }
    if(model->isEmpty(false)) {
        error(tr("Cannot write an empty file."));
        return ;
    }
    QString newFilePath = askFileName(model->fileName());
    if(newFilePath.isEmpty()) {
        return ;
    }
    if(!model->write(newFilePath)) {
        error(tr("Error saving data. Old file is still intact."));
        return ;
    }
    if(editor->displayMode() != qxmledit::SCAN) {
        model->setFileName(newFilePath);
    }
    updateRecentFilesMenu(newFilePath);
    model->setModified(false);
    statusBar()->showMessage(tr("File saved"), SHORT_TIMEOUT);
}

void MainWindow::on_actionSaveACopyAs_triggered()
{
    DomModel * model = getModel();
    if(NULL == model) {
        error(tr("No data to save."));
        return ;
    }
    if(model->isEmpty(false)) {
        error(tr("Cannot write an empty file."));
        return ;
    }
    bool modifiedStatus = model->isModified();
    QString newFilePath = askFileName(model->fileName());
    if(newFilePath.isEmpty()) {
        return ;
    }
//    if(!model->write(newFilePath, false)) {
//        error(tr("Error saving data. Old file is still intact."));
//        return ;
//    }
    updateRecentFilesMenu(newFilePath);
    model->setModified(modifiedStatus);
    statusBar()->showMessage(tr("File saved"), SHORT_TIMEOUT);
}

void MainWindow::on_actionSave_triggered()
{
    DomModel * model = getModel();
    if(!editor->isActionNoScanMode()) {
        return ;
    }
    if(editor->displayMode() == qxmledit::SCAN) {
        return ;
    }
    if(model->fileName().isEmpty()) {
        on_actionSaveAs_triggered();
        return ;
    }
    if(model->isEmpty(false)) {
        error(tr("Cannot write empty file."));
        return ;
    }

    // scrivi il nuovo con il nome vecchio+estensione
    QString newFilePath = model->fileName() + ".new_new~"  ;
    if(!model->write(newFilePath)) {
        error(tr("Error saving data. Old file is still intact."));
        return ;
    }
    // rinomina il vecchio
    QString backupFilePath = model->fileName() + "~"  ;
    if(QFile::exists(backupFilePath)) {
        if(!QFile::remove(backupFilePath)) {
            error(tr("Error saving data: cleaning backup file."));
            return ;
        }
    }
    if(!QFile::rename(model->fileName(), backupFilePath)) {
        error(tr("Error renaming old file. You can access written data at file '%1'. Old data are untouched").arg(newFilePath));
        return ;
    }
    // rinomina il nuovo nel nome vecchio
    if(!QFile::rename(newFilePath, model->fileName())) {
        error(tr("Error renaming new file. You can access written data at file '%1'. You can find old data in the backup file").arg(newFilePath));
        return ;
    }
    model->setModified(false);
    Utils::message(this, tr("Operation terminated"));
    statusBar()->showMessage(tr("File saved"), SHORT_TIMEOUT);
}

QString MainWindow::askFileName(const QString &actualName)
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save Data"),
                       actualName, tr("XML files (*.xml);;XML Schema files (*.xsd);;All files (*);;"));

    if(!filePath.isEmpty()) {
        return filePath;
    }
    return "";
}

void MainWindow::errorNoRule()
{
    error(tr("No main structure"));
}

void MainWindow::on_actionAddChildElement_triggered()
{
    editor->onActionAddChildItem();
}

void MainWindow::on_actionAppendChildElement_triggered()
{
    editor->onActionAppendChildItem();
}

void MainWindow::on_actionEdit_triggered()
{
    editor->onActionEdit();
}

void MainWindow::on_actionDelete_triggered()
{
    editor->onActionDelete();
}
void MainWindow::on_actionMoveUp_triggered()
{
    editor->onActionMoveUp();
}

void MainWindow::on_actionMoveDown_triggered()
{
    editor->onActionMoveDown();
}

void MainWindow::on_actionCut_triggered()
{
    editor->onActionCut();
}

void MainWindow::on_actionCopy_triggered()
{
    editor->onActionCopy();
}

void MainWindow::on_actionPaste_triggered()
{
    editor->onActionPaste();
}

void MainWindow::on_actionAbout_triggered()
{
//    QList<AuthorInfo*> authors = authorsInfo() ;
//    AboutDialog about(this,
//                      AuthorInfo::appName, AuthorInfo::version, AuthorInfo::copyright,
//                      AuthorInfo::license,
//                      AuthorInfo::other,
//                      authors);
//    about.setModal(true);
//    about.exec() ;
//    deleteAuthorsInfo(authors);
}


void MainWindow::onShowStatusMessage(const QString &message, const bool isLongTimeout)
{
    statusBar()->showMessage(message, isLongTimeout ? LONG_TIMEOUT : SHORT_TIMEOUT);
}

void MainWindow::setFileTitle()
{
    QString windowTitle = APP_TITLE;
//    if(!isSlave)
    {
        windowTitle.append(" - ");
        if(!getModel()->fileName().isEmpty()) {
            windowTitle.append(getModel()->fileName());
        } else {
            windowTitle.append(tr("--No file--"));
        }
        windowTitle.append(" [*]");
    }
    setWindowTitle(windowTitle);
}

void MainWindow::closeEvent(QCloseEvent * event)
{
    if(!MainWindow::checkAbandonChanges()) {
        event->ignore();
        return ;
    }
    event->accept();
//    if(isAutoDelete) {
        deleteLater();
//    }
}

void MainWindow::on_actionQuit_triggered()
{
    if(MainWindow::checkAbandonChanges()) {
//        application->quit();
        close();
    }
}

bool MainWindow::checkAbandonChanges()
{
    DomModel *model = getModel();
    if(NULL == model) {
        return false;
    }

    if(model->isModified()) {
        if(QMessageBox::Yes != QMessageBox::question(this, APP_TITLE,
                tr("Abandon changes?"),
                QMessageBox::Yes | QMessageBox::No)) {
            return false ;
        }
    }
    return true ;
}


void MainWindow::on_actionExpandAll_triggered()
{
    editor->onActionExpandAll();
}

void MainWindow::on_actionShowAttrLine_triggered()
{
    editor->onActionShowAttrLine(actionShowAttrLine->isChecked());
}

void MainWindow::on_actionAddComment_triggered()
{
    editor->onActionAddComment();
}


void MainWindow::on_actionAppendComment_triggered()
{
    editor->onActionAppendComment();
}

void MainWindow::on_actionAppendProcessingInstruction_triggered()
{
    editor->onActionAppendProcessingInstruction();
}


void MainWindow::on_actionAddProcessingInstruction_triggered()
{
    editor->onActionAddProcessingInstruction();
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasFormat("text/uri-list"))
        event->acceptProposedAction();
}

void MainWindow::dropEvent(QDropEvent *event)
{
    if(event->mimeData()->hasFormat("text/uri-list")) {
        QString filePath = "" ;
        event->acceptProposedAction();
        if(event->mimeData()->hasUrls()) {
            foreach(QUrl url, event->mimeData()->urls()) {
                filePath = url.toLocalFile();
                break;
            }
        }
        if(filePath.length() > 0) {
            if(!MainWindow::checkAbandonChanges()) {
                event->ignore();
                return ;
            }
            loadFile(filePath);
        }
        event->acceptProposedAction();
    }
}

void MainWindow::on_actionFind_triggered()
{
    editor->onActionFind();
}

void MainWindow::on_actionGo_To_Parent_triggered()
{
    editor->onActionGoToParent();
}

void MainWindow::on_actionGo_to_Previous_Brother_triggered()
{
    editor->onActionGoToPreviousBrother();
}

void MainWindow::on_actionGo_to_Next_Brother_triggered()
{
    editor->onActionGoToNextBrother();
}


void MainWindow::on_actionShowChildIndex_triggered()
{
    editor->onActionShowChildIndex(actionShowChildIndex->isChecked());
}

void MainWindow::on_actionCompactView_triggered()
{
    editor->onActionCompactView(actionCompactView->isChecked());
}

void MainWindow::on_actionFixedSizeAttributes_triggered()
{
    editor->onActionFixedSizeAttributes(actionFixedSizeAttributes->isChecked());
}

void MainWindow::on_actionShowAttributesLength_triggered()
{
    editor->onActionShowAttributesLength(actionShowAttributesLength->isChecked());
}

void MainWindow::on_actionShowElementTextLength_triggered()
{
    editor->onActionShowItemTextLength(actionShowElementTextLength->isChecked());
}

void MainWindow::on_actionCloseThisAllBrothers_triggered()
{
    editor->onActionCloseThisAllBrothers();
}

void MainWindow::on_actionHideBrothers_triggered()
{
    editor->onActionHideBrothers();
}

void MainWindow::on_actionShowCurrentElementTextBase64_triggered()
{
    editor->onActionShowCurrentItemTextBase64(actionShowCurrentElementTextBase64->isChecked());
}

void MainWindow::on_actionShowBase64_triggered()
{
    editor->onActionShowBase64(actionShowBase64->isChecked());
}

void MainWindow::on_actionShowElementSize_triggered()
{
    editor->onActionShowItemSize(actionShowElementSize->isChecked());
}

void MainWindow::on_actionConfigure_triggered()
{
 //   ConfigurationDialog::doOptions(this, data) ;
}

void MainWindow::on_ok_clicked()
{
    if(NULL != eventLoop) {
        eventLoop->exit(1);
    }
}

void MainWindow::on_cancel_clicked()
{
    if(NULL != eventLoop) {
        eventLoop->exit(0);
    }
}

void MainWindow::setEventLoop(QEventLoop *value)
{
    eventLoop = value ;
}

void MainWindow::on_actionEditInnerXML_triggered()
{
    editor->onActionEditInnerXML();
}

void MainWindow::on_actionEditInnerXMLBase64_triggered()
{
    editor->onActionEditInnerXMLBase64();
}


void MainWindow::on_actionEditInnerBase64Text_triggered()
{
    editor->onActionEditInnerBase64Text();
}

QString MainWindow::getContentAsText()
{
    return editor->getContentAsText();
}

void MainWindow::on_actionZoomIn_triggered()
{
    editor->onActionZoomIn();
    enableZoom();
}

void MainWindow::on_actionZoomOut_triggered()
{
    editor->onActionZoomOut();
    enableZoom();
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    if((event->modifiers() & Qt::ControlModifier) == Qt::ControlModifier) {
        int numDegrees = event->delta() / 8;
        if(numDegrees > 10) {
            on_actionZoomIn_triggered();
        } else if(numDegrees < -10) {
            on_actionZoomOut_triggered();
        }
        event->accept();
    } else {
        event->ignore();
    }
}



void MainWindow::on_actionCompare_triggered()
{
#ifdef DEBUG_COMPARE
#define FILE_TEST_C   "~/devel/qxmledit/qxmledit/src/data/compare_base.xml"
    loadFile(FILE_TEST_C);
#endif
    DomModel *model = getModel();
    if(NULL == model) {
        errorNoRule();
        return ;
    }
//    CompareBridge::doCompare(this, model);
}

void MainWindow::on_actionReload_triggered()
{
    DomModel *model = getModel();
    if(NULL == model) {
        return;
    }
    QString filePath = model->fileName();
    if(filePath.isEmpty()) {
        return ;
    }
    if(!MainWindow::checkAbandonChanges()) {
        return ;
    }
    loadFile(filePath);
}

void MainWindow::onRecentFile()
{
    QAction *actionFile = qobject_cast<QAction*>(sender());
    if(NULL != actionFile) {
        QString filePath = actionFile->data().toString();
        if(!filePath.isEmpty()) {
            if(!MainWindow::checkAbandonChanges()) {
                return ;
            }
            loadFile(filePath);
        }
    }
}

void MainWindow::onPreferredDir()
{
    QAction *actionFile = qobject_cast<QAction*>(sender());
    if(NULL != actionFile) {
        QString dirPath = actionFile->data().toString();
        if(!MainWindow::checkAbandonChanges()) {
            return ;
        }
        QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"),
                           dirPath, tr("XML files (*.xml);;XML Schema files (*.xsd);;All files (*);;"));
        if(!filePath.isEmpty()) {
            loadFile(filePath);
        }
    }
}

void MainWindow::updateMRU(QStringList &entries, const QString &entry, QList<QAction*>actions)
{
    if(entry.isEmpty()) {
        return;
    }
    entries.removeOne(entry);
    entries.insert(0, entry);
    updateEntriesMenu(entries, actions);
    if(!Config::saveStringArray(Config::KEY_MAIN_RECENTFILES, lastFilesNames)) {
        Utils::error(tr("Error registering last open files."));
    }
}

void MainWindow::updateEntriesMenu(QStringList &entries, QList<QAction*>actions)
{
    int listSize = entries.size();
    int nMaxActions = actions.size();
    for(int i = 0 ; i < nMaxActions ; i ++) {
        QAction *action = actions.at(i);
        if(i < listSize) {
            QString data = entries.at(i);
            action->setData(data);
            action->setText(data);
            action->setVisible(true);
        } else {
            action->setVisible(false);
        }
    }
}

void MainWindow::updateRecentFilesMenu(const QString &filePath)
{
    updateMRU(lastFilesNames, filePath, lastFiles);
}

void MainWindow::loadRecentFilesSettings()
{
    lastFilesNames.clear();
    Config::loadStringArray(Config::KEY_MAIN_RECENTFILES, lastFilesNames);
    updateEntriesMenu(lastFilesNames, lastFiles);
}

void MainWindow::on_actionCopyPathToClipboard_triggered()
{
    editor->onActionCopyPathToClipboard();
}

void MainWindow::on_actionAddCurrentDirectory_triggered()
{
    DomModel *model = getModel();
    if((NULL != model) && !model->fileName().isEmpty()) {
//        if(!PreferredDirs::checkNewDir(preferredDirsNames.size(), true)) {
//            return;
//        }
        QFileInfo fileInfo(model->fileName());
        QString dirPath = fileInfo.path();
//        if(!PreferredDirs::checkDuplicateDir(preferredDirsNames, dirPath, true)) {
//            return ;
//        }
        preferredDirsNames.append(dirPath);
        updatePreferredDirs(preferredDirsNames, preferredDirs);
    }
}

void MainWindow::on_actionEditPreferredDirectories_triggered()
{
//    if(configurePreferredDirs(this, preferredDirsNames)) {
        updatePreferredDirs(preferredDirsNames, preferredDirs);
//    }
}

void MainWindow::updatePreferredDirs(QStringList &entries, QList<QAction*>actions)
{
    entries.sort();
    updateEntriesMenu(entries, actions);
    if(!Config::saveStringArray(Config::KEY_MAIN_PREFDIRS, preferredDirsNames)) {
        Utils::error(tr("Error registering preferred directories."));
    }
}
void MainWindow::loadPreferredDirsSettings()
{
    preferredDirsNames.clear();
    Config::loadStringArray(Config::KEY_MAIN_PREFDIRS, preferredDirsNames);
    preferredDirsNames.sort();
    updateEntriesMenu(preferredDirsNames, preferredDirs);
}

void MainWindow::on_actionValidate_triggered()
{
    editor->onActionValidate();
}

void MainWindow::on_actionValidateFile_triggered()
{
    editor->onActionValidateFile();
}

void MainWindow::on_actionValidateNewFile_triggered()
{
    editor->onActionValidateNewFile();
}

void MainWindow::on_actionInsertSnippet_triggered()
{
//    DomModel* model = getModel();
//    if(NULL == model) {
//        return;
//    }
//    DomModel* newModel = chooseSnippets(data, this) ;
//    if(NULL != newModel) {
//        editor->insertSnippet(newModel);
//        delete newModel;
//    }
}

void MainWindow::on_actionConfigureSnippets_triggered()
{
//    editSnippets(data, this);
}

void MainWindow::on_actionExecuteAutoTest_triggered()
{
//    Test::executeTests(this);
}

void MainWindow::on_actionTransforminSnippet_triggered()
{
//    if(!editor->isActionMode()) {
//        return ;
//    }

//    DomItem *item = getSelectedItem();
//    if(NULL != item) {
//        QDomDocument    document;
//        if(item->generateDom(document, document)) {
//            QString clipboardText = document.toString(4);
//            insertFragmentInSnippets(this, data, clipboardText) ;
//        }
//    }
}

void MainWindow::onPlugin()
{
//    QAction *actionFile = qobject_cast<QAction*>(sender());
//    if(NULL != actionFile) {
//        QString pluginId = actionFile->data().toString();
//        if(!pluginId .isEmpty()) {
//            IQXmlEditPlugIn* plugin = data->plugins()[pluginId];
//            if(NULL != plugin) {
//                plugin->go(this, getModel());
//            }
//        }
//    }
}

bool MainWindow::buildPluginsMenu(const char *method, QMenu *parent)
{
//    bool isOk = true;
//    pluginsCmds.clear();
//    QMapIterator<QString, IQXmlEditPlugIn*> pluginsIterator(data->plugins());
//    while(pluginsIterator.hasNext()) {
//        pluginsIterator.next();
//        QAction *action = new QAction(this);
//        if(NULL != action) {
//            pluginsCmds.append(action);
//            connect(action, SIGNAL(triggered()), this, method);
//            IQXmlEditPlugIn* plugin = pluginsIterator.value();
//            action->setData(pluginsIterator.key());
//            action->setText(plugin->name());
//            action->setVisible(true);
//            parent->addAction(action);
//        } else {
//            isOk = false ;
//        }
//    }
//    return isOk ;
}



void MainWindow::setDisplayMode(const qxmledit::EDisplayMode value)
{
    editor->setDisplayMode(value);
//    navigationModeIndicator->setExploreMode(value);
}


//---------------------- load trigger

void MainWindow::on_actionXplore_triggered()
{
    if(!MainWindow::checkAbandonChanges()) {
        return ;
    }
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"),
                       getModel()->fileName(), tr("XML files (*.xml);;XML Schema files (*.xsd);;All files (*);;"));
    if(!filePath.isEmpty()) {
        loadFileXplore(filePath);
    }
}

void MainWindow::loadFileXplore(const QString &filePath)
{
    if(!filePath.isEmpty()) {
        doLoadFileXplore(filePath);
        updateRecentFilesMenu(filePath);
    } else {
        Utils::error(tr("File name empty. Unable to load it."));
    }
}


void MainWindow::loadFile(const QString &filePath)
{
    if(!filePath.isEmpty()) {
        QFile file(filePath);
        if(file.open(QIODevice::ReadOnly)) {
            QDomDocument document;
            if(document.setContent(&file)) {
//                data->sessionManager()->enrollFile(filePath);
                setDocument(document, filePath, true);
                updateRecentFilesMenu(filePath);
                autoLoadValidation();
            } else {
                Utils::error(tr("Unable to parse XML"));
            }
            file.close();
        } else {
            Utils::error(QString(tr("Unable to load file.\n Error code is '%1'")).arg(file.error()));
        }
    } else {
        Utils::error(tr("File name empty. Unable to load it."));
    }
}


//---------------------- load data

//TODO: error checking
void MainWindow::doLoadFileXplore(const QString &filePath)
{
    editor->doLoadFileXplore(filePath);
    statusBar()->showMessage(tr("Data loaded"), SHORT_TIMEOUT);
}

//TODO: error checking
void MainWindow::onNewMessage(const QString &newMessage)
{
    statusBar()->showMessage(newMessage, SHORT_TIMEOUT);
}

//TODO: error checking
void MainWindow::setDocument(QDomDocument &document, const QString &filePath, const bool isSetState)
{
    editor->setDocument(document, filePath, isSetState);
    statusBar()->showMessage(tr("Data loaded"), SHORT_TIMEOUT);
}

void MainWindow::on_actionHideView_triggered()
{
    editor->onActionHideView(actionHideView->isChecked());
}

void MainWindow::on_actionSearchInFiles_triggered()
{
    searchInFiles(this);
}

void MainWindow::on_actionHelpOnQXmlEdit_triggered()
{
//    QString resourceHelp = data->getDocsDir() + "/" + HELP_FILE ;
//    QDesktopServices::openUrl(QUrl::fromLocalFile(resourceHelp));
}

bool MainWindow::isValidXsd()
{
    DomModel * model = getModel();
    if(NULL != model) {
        return model->isValidXsd();
    }
    return false;
}

void MainWindow::on_actionViewAsXsd_triggered()
{
    editor->onActionViewAsXsd();
}

DomModel *MainWindow::getModel()
{
    return editor->getModel();
}


//void MainWindow::loadSchema(const QString &schemaURL)
//{
//    ui.editor->loadSchema(schemaURL);
//} TODO: controllare se spostato

void MainWindow::schemaLoadComplete(const QString &newLabel)
{
    setSchemaLabel(newLabel);
    statusBar()->update();
}

void MainWindow::on_actionAllowedSchemaElements_triggered()
{
    editor->onActionAllowedSchemaItems();
}

/** Substitute the element text
  */
void MainWindow::on_actionPasteAndSubstituteText_triggered()
{
    editor->onActionPasteAndSubstituteText();
}


void MainWindow::on_actionNewUsingXMLSchema_triggered()
{
    if(!verifyAbandonChanges()) {
        return ;
    }
    bool isOk = false;
    QString schemaURL;
//    schemaURL = chooseSchemaFile(this, isOk) ;
    if(isOk) {
        editor->onActionNewUsingXMLSchema(schemaURL);
    }
}

bool MainWindow::verifyAbandonChanges()
{
    DomModel *model = getModel();
    if(!model->isEmpty(false) && model->isModified()) {
        if(QMessageBox::Yes != QMessageBox::question(this, APP_TITLE,
                tr("Abandon changes?"),
                QMessageBox::Yes | QMessageBox::No)) {
            return false ;
        }
    }
    return true ;
}

QWidget *MainWindow::getMainWidget()
{
    return this ;
}

QString MainWindow::getAppTitle()
{
    return APP_TITLE ;
}


void MainWindow::on_actionTransformInComment_triggered()
{
    editor->onActionTransformInComment();
}

void MainWindow::on_actionExtractElementsFromComment_triggered()
{
    editor->onActionExtractItemsFromComment();
}

void MainWindow::autoLoadValidation()
{
    editor->autoLoadValidation();
}

void MainWindow::setSchemaLabel(const QString &newLabel)
{
//    labelSchema->setText(newLabel);
}


void MainWindow::on_actionInsertNoNamespaceSchemaReferenceAttributes_triggered()
{
    editor->onActionInsertNoNamespaceSchemaReferenceAttributes();
}

void MainWindow::on_actionInsertSchemaReferenceAttributes_triggered()
{
    editor->onActionInsertSchemaReferenceAttributes();
}

void MainWindow::on_actionExtractFragmentsFromFile_triggered()
{
//    if(!verifyAbandonChanges()) {
//        return ;
//    }
//    ExtractResults *results = new  ExtractResults();
//    if(NULL == results) {
//        Utils::errorOutOfMem(this);
//        return ;
//    }
//    extractFragments(results, this);
//    if(!(results->isError() || results->isAborted())) {
//        if(results->_optimizeSpeed) {
//            delete results ;
//            return ;
//        }
//        if(results->numFragments() == 0) {
//            Utils::message(tr("No fragments found"));
//            delete results ;
//            return ;
//        }
//        cleanExtractResults();
//        _extractResult = results ;
//        editor->setNavigationDataAndEnable(1, _extractResult->numFragments());
//        showNavigationBox();
//    } else {
//        delete results ;
//    }
}

void MainWindow::showNavigationBox()
{
    editor->showNavigationBox();
}

void MainWindow::navigateToPage(const int page)
{
    /********************************** test code **************************
    Utils::todo(QString("Navigate to %1").arg(page));
    setWindowTitle(QString::number(page));
    ***********************************************************************/
    loadCurrentPage(page);
}

void MainWindow::loadCurrentPage(const int page)
{
//    if(NULL != _extractResult) {
//        StringOperationResult result;
//        _extractResult->loadFragment(page, result);
//        if(!result.isError()) {
//            editor->loadText(result.result(), false, true);
//            // printf("xml is:'%s'\n", result.result().toAscii().data());
//        } else {
//            Utils::error(this, tr("Error loading data."));
//        }
//    }
}


void MainWindow::error(const QString& message)
{
    Utils::error(this, message);
}

void MainWindow::warning(const QString& message)
{
    Utils::warning(this, message);
}

void MainWindow::message(const QString& message)
{
    Utils::message(this, message);
}

bool MainWindow::askYN(const QString & message)
{
    return Utils::askYN(this, message);
}

QTreeWidget *MainWindow::getMainTreeWidget()
{
    return editor->getMainTreeWidget();
}

XmlEditWidget *MainWindow::getEditor()
{
    return editor ;
}

void MainWindow::on_actionHideAllLeafChildren_triggered()
{
    editor->onActionHideAllLeafChildren();
}

void MainWindow::on_actionHideLeafChildren_triggered()
{
    evaluateSingleItemLeaves(editor->onActionHideLeafChildren());
}

void MainWindow::on_actionShowLeafChildren_triggered()
{
    evaluateSingleItemLeaves(editor->onActionShowLeafChildren());
}

void MainWindow::on_actionShowAllLeafChildren_triggered()
{
    editor->onActionShowAllLeafChildren();
}

void MainWindow::on_actionColumnView_triggered()
{
//    DomModel *model = getModel();
//    if(NULL != model) {
//        ColumnarView::showModal(this, model);
//    }
}



void MainWindow::on_actionUndo_triggered()
{
    editor->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    editor->redo();
}

void MainWindow::onUndoStateUpdated(const bool isUndo, const bool isRedo)
{
    updateUndoState(isUndo, isRedo);
}

void MainWindow::updateUndoState(const bool isUndo, const bool isRedo)
{
    actionUndo->setEnabled(isUndo) ;
    actionRedo->setEnabled(isRedo) ;
}


void MainWindow::on_actionNewWindow_triggered()
{
    MainWindow *newWindow = new MainWindow();//false, application, data);
    if(NULL != newWindow) {
//        newWindow->isAutoDelete = true ;
        newWindow->show();
    } else {
        Utils::error(tr("Error opening a new window."));
    }

}

void MainWindow::on_actionViewData_triggered()
{
//    DataVisualization::viewData(this, "");
}

void MainWindow::loadVisFile(const QString &fileName)
{
//    DataVisualization::viewData(this, fileName);
}

void MainWindow::on_actionBase64Tools_triggered()
{
//    data->uiServices()->doBase64Dialog();
}

void MainWindow::on_actionEncodingTools_triggered()
{
//    data->uiServices()->doEncodingDialog();
}

void MainWindow::fileNewAct()
{


}

void MainWindow::fileOpenAct()
{


}


void MainWindow::fileSaveAct()
{


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

void MainWindow::showPopMenu(const QModelIndex& currentItem)
{
//    QMenu *qPopMenu = new QMenu(this);
//    QModelIndex *currentItem = new QModelIndex();

//    currentItem = index;

//    if(currentItem.data().isNull() && newFileName == NULL)
//        return;

//    if(currentItem.data().isNull() && newFileName != NULL)
//    {
//        qPopMenu->addAction(qRefresh);
//        qPopMenu->exec(QCursor::pos());
//        return;
//    }

//    DomItem *Item = static_cast<DomItem*>(currentItem.internalPointer());
//    QDomNode currentNode = Item->node();

//    if(currentItem.data().toString() == tr("SCL"))
//    {
//        qAddHeader->setIndex(currentItem);
//        qPopMenu->addAction(qAddHeader);
//        qAddSubstation->setIndex(currentItem);
//        qPopMenu->addAction(qAddSubstation);
//        qAddCommunication->setIndex(currentItem);
//        qPopMenu->addAction(qAddCommunication);
//        qAddIED->setIndex(currentItem);
//        qPopMenu->addAction(qAddIED);
//        qAddDataTypeTemplates->setIndex(currentItem);
//        qPopMenu->addAction(qAddDataTypeTemplates);

//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("Header"))
//            {
//                qAddHeader->setDisabled(1);
//                break;
//            }
//        }
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("Communication"))
//            {
//                qAddCommunication->setDisabled(1);
//                break;
//            }
//        }
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("DataTypeTemplates"))
//            {
//                qAddDataTypeTemplates->setDisabled(1);
//                break;
//            }
//        }

//    }

//    if(currentItem.data().toString() == tr("Header"))
//    {
//        qAddText->setDisabled(0);
//        qAddText->setIndex(currentItem);
//        qPopMenu->addAction(qAddText);
//        qAddHistory->setDisabled(0);
//        qAddHistory->setIndex(currentItem);
//        qPopMenu->addAction(qAddHistory);
//        qDebug()<<currentNode.childNodes().count();
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("Text"))
//            {
//                qAddText->setDisabled(1);
//                break;
//            }
//        }
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("History"))
//            {
//                qAddHistory->setDisabled(1);
//                break;
//            }
//        }

//    }
//    if(currentItem.data().toString() == tr("History"))
//    {
//        qDebug()<<tr("Add Hitem Menu");
//        qAddHitem->setIndex(currentItem);
//        qPopMenu->addAction(qAddHitem);
//    }
//    if(currentItem.data().toString() == tr("Text"))
//    {
//        qAddTextContent->setIndex(currentItem);
//        qPopMenu->addAction(qAddTextContent);
//    }

//    if(currentItem.data().toString() == tr("Substation"))
//    {
//        qAddVoltageLevel->setIndex(currentItem);
//        qPopMenu->addAction(qAddVoltageLevel);
//        qAddFunction->setIndex(currentItem);
//        qPopMenu->addAction(qAddFunction);
//        qAddPowerTransformer->setIndex(currentItem);
//        qPopMenu->addAction(qAddPowerTransformer);
//        qAddGeneralEquipment->setIndex(currentItem);
//        qPopMenu->addAction(qAddGeneralEquipment);
//        qAddLNode->setIndex(currentItem);
//        qPopMenu->addAction(qAddLNode);

//    }

//    if(currentItem.data().toString() == tr("IED"))
//    {
//        qAddServices->setDisabled(0);
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("Services"))
//            {
//                qAddServices->setDisabled(1);
//                break;
//            }
//        }
//        qAddServices->setIndex(currentItem);
//        qPopMenu->addAction(qAddServices);
//        qAddAccessPoint->setIndex(currentItem);
//        qPopMenu->addAction(qAddAccessPoint);
//    }

//    if(currentItem.data().toString() == tr("Services"))
//    {
//        qAddDynAssociation->setIndex(currentItem);
//        qPopMenu->addAction(qAddDynAssociation);

//        qAddSettingGroups->setIndex(currentItem);
//        qPopMenu->addAction(qAddSettingGroups);

//        qAddGetDirectory->setIndex(currentItem);
//        qPopMenu->addAction(qAddGetDirectory);
//        qAddGetDataObjectDefinition->setIndex(currentItem);
//        qPopMenu->addAction(qAddGetDataObjectDefinition);
//        qAddDataObjectDirectory->setIndex(currentItem);
//        qPopMenu->addAction(qAddDataObjectDirectory);
//        qAddGetDataSetValue->setIndex(currentItem);
//        qPopMenu->addAction(qAddGetDataSetValue);
//        qAddSetDataSetValue->setIndex(currentItem);
//        qPopMenu->addAction(qAddSetDataSetValue);
//        qAddDataSetDirectory->setIndex(currentItem);
//        qPopMenu->addAction(qAddDataSetDirectory);
//        qAddConfDataSet->setIndex(currentItem);
//        qPopMenu->addAction(qAddConfDataSet);
//        qAddDynDataSet->setIndex(currentItem);
//        qPopMenu->addAction(qAddDynDataSet);
//        qAddReadWrite->setIndex(currentItem);
//        qPopMenu->addAction(qAddReadWrite);
//        qAddTimerActivatedControl->setIndex(currentItem);
//        qPopMenu->addAction(qAddTimerActivatedControl);
//        qAddConfReportControl->setIndex(currentItem);
//        qPopMenu->addAction(qAddConfReportControl);
//        qAddGetCBValues->setIndex(currentItem);
//        qPopMenu->addAction(qAddGetCBValues);
//        qAddConfLogControl->setIndex(currentItem);
//        qPopMenu->addAction(qAddConfLogControl);
//        qAddReportSettings->setIndex(currentItem);
//        qPopMenu->addAction(qAddReportSettings);
//        qAddLogSettings->setIndex(currentItem);
//        qPopMenu->addAction(qAddLogSettings);
//        qAddGSESettings->setIndex(currentItem);
//        qPopMenu->addAction(qAddGSESettings);
//        qAddSMVSettings->setIndex(currentItem);
//        qPopMenu->addAction(qAddSMVSettings);
//        qAddGSEDir->setIndex(currentItem);
//        qPopMenu->addAction(qAddGSEDir);
//        qAddGOOSE->setIndex(currentItem);
//        qPopMenu->addAction(qAddGOOSE);
//        qAddGSSE->setIndex(currentItem);
//        qPopMenu->addAction(qAddGSSE);
//        qAddFileHandling->setIndex(currentItem);
//        qPopMenu->addAction(qAddFileHandling);
//        qAddConfLNs->setIndex(currentItem);
//        qPopMenu->addAction(qAddConfLNs);

//        qAddDynAssociation->setDisabled(0);
//        qAddSettingGroups->setDisabled(0);
//        qAddGetDirectory->setDisabled(0);
//        qAddGetDataObjectDefinition->setDisabled(0);
//        qAddDataObjectDirectory->setDisabled(0);
//        qAddGetDataSetValue->setDisabled(0);
//        qAddSetDataSetValue->setDisabled(0);
//        qAddDataSetDirectory->setDisabled(0);
//        qAddConfDataSet->setDisabled(0);
//        qAddDynDataSet->setDisabled(0);
//        qAddReadWrite->setDisabled(0);
//        qAddTimerActivatedControl->setDisabled(0);
//        qAddConfReportControl->setDisabled(0);
//        qAddGetCBValues->setDisabled(0);
//        qAddConfLogControl->setDisabled(0);
//        qAddReportSettings->setDisabled(0);
//        qAddLogSettings->setDisabled(0);
//        qAddGSESettings->setDisabled(0);
//        qAddSMVSettings->setDisabled(0);
//        qAddGSEDir->setDisabled(0);

//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("DynAssociation"))
//            {
//                qAddDynAssociation->setDisabled(1);
//                break;
//            }
//        }
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("SettingGroups"))
//            {
//                qAddSettingGroups->setDisabled(1);
//                break;
//            }
//        }
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("GetDirectory"))
//            {
//                qAddGetDirectory->setDisabled(1);
//                break;
//            }
//        }
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("GetDataObjectDefinition"))
//            {
//                qAddGetDataObjectDefinition->setDisabled(1);
//                break;
//            }
//        }
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("DataObjectDirectory"))
//            {
//                qAddDataObjectDirectory->setDisabled(1);
//                break;
//            }
//        }
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("GetDataSetValue"))
//            {
//                qAddGetDataSetValue->setDisabled(1);
//                break;
//            }
//        }
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("SetDataSetValue"))
//            {
//                qAddSetDataSetValue->setDisabled(1);
//                break;
//            }
//        }
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("DataSetDirectory"))
//            {
//                qAddDataSetDirectory->setDisabled(1);
//                break;
//            }
//        }
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("ConfDataSet"))
//            {
//                qAddConfDataSet->setDisabled(1);
//                break;
//            }
//        }
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("DynDataSet"))
//            {
//                qAddDynDataSet->setDisabled(1);
//                break;
//            }
//        }
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("ReadWrite"))
//            {
//                qAddReadWrite->setDisabled(1);
//                break;
//            }
//        }
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("TimerActivatedControl"))
//            {
//                qAddTimerActivatedControl->setDisabled(1);
//                break;
//            }
//        }
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("ConfReportControl"))
//            {
//                qAddConfReportControl->setDisabled(1);
//                break;
//            }
//        }
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("GetCBValues"))
//            {
//                qAddGetCBValues->setDisabled(1);
//                break;
//            }
//        }
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("ConfLogControl"))
//            {
//                qAddConfLogControl->setDisabled(1);
//                break;
//            }
//        }
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("ReportSettings"))
//            {
//                qAddReportSettings->setDisabled(1);
//                break;
//            }
//        }
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("LogSettings"))
//            {
//                qAddLogSettings->setDisabled(1);
//                break;
//            }
//        }
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("GSESettings"))
//            {
//                qAddGSESettings->setDisabled(1);
//                break;
//            }
//        }
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("SMVSettings"))
//            {
//                qAddSMVSettings->setDisabled(1);
//                break;
//            }
//        }
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("GSEDir"))
//            {
//                qAddGSEDir->setDisabled(1);
//                break;
//            }
//        }
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("GOOSE"))
//            {
//                qAddGOOSE->setDisabled(1);
//                break;
//            }
//        }
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("GSSE"))
//            {
//                qAddGSSE->setDisabled(1);
//                break;
//            }
//        }
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("FileHandling"))
//            {
//                qAddFileHandling->setDisabled(1);
//                break;
//            }
//        }
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("ConfLNs"))
//            {
//                qAddConfLNs->setDisabled(1);
//                break;
//            }
//        }
//    }
//    if(currentItem.data().toString() == tr("SettingGroups"))
//    {
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("SGEdit"))
//            {
//                qAddSGEdit->setDisabled(1);
//                break;
//            }
//        }
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("ConfSG"))
//            {
//                qAddConfSG->setDisabled(1);
//                break;
//            }
//        }
//        qAddSGEdit->setIndex(currentItem);
//        qPopMenu->addAction(qAddSGEdit);
//        qAddConfSG->setIndex(currentItem);
//        qPopMenu->addAction(qAddConfSG);
//    }
//    if(currentItem.data().toString() == tr("SettingGroups"))
//    {
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("Server"))
//            {
//                qAddSGEdit->setDisabled(1);
//                break;
//            }
//        }
//        qAddSGEdit->setIndex(currentItem);
//        qPopMenu->addAction(qAddSGEdit);
//        qAddConfSG->setIndex(currentItem);
//        qPopMenu->addAction(qAddConfSG);
//    }

//    if(currentItem.data().toString() == tr("AccessPoint"))
//    {
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("Server"))
//            {
//                qAddServer->setDisabled(1);
//                break;
//            }
//        }
//        qAddServer->setIndex(currentItem);
//        qPopMenu->addAction(qAddServer);
//        qAddLN->setIndex(currentItem);
//        qPopMenu->addAction(qAddLN);
//    }

//    if(currentItem.data().toString() == tr("Server"))
//    {
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("Authentication"))
//            {
//                qAddAuthentication->setDisabled(1);
//                break;
//            }
//        }

//        qAddAuthentication->setIndex(currentItem);
//        qPopMenu->addAction(qAddAuthentication);
//        qAddLDevice->setIndex(currentItem);
//        qPopMenu->addAction(qAddLDevice);
//        qAddAssociation->setIndex(currentItem);
//        qPopMenu->addAction(qAddAssociation);
//    }

//    if(currentItem.data().toString() == tr("LDevice"))
//    {
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("LN0"))
//            {
//                qAddLN0->setDisabled(1);
//                break;
//            }
//        }
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("AccessControl"))
//            {
//                qAddAccessControl->setDisabled(1);
//                break;
//            }
//        }

//        qAddLN0->setIndex(currentItem);
//        qPopMenu->addAction(qAddLN0);
//        qAddLN->setIndex(currentItem);
//        qPopMenu->addAction(qAddLN);
//        qAddAccessControl->setIndex(currentItem);
//        qPopMenu->addAction(qAddAccessControl);
//    }

//    if(currentItem.data().toString() == tr("LN0"))
//    {
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("SettingControl"))
//            {
//                qAddSettingControl->setDisabled(1);
//                break;
//            }
//        }
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("SCLControl"))
//            {
//                qAddSCLControl->setDisabled(1);
//                break;
//            }
//        }
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("Log"))
//            {
//                qAddLog->setDisabled(1);
//                break;
//            }
//        }
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("Inputs"))
//            {
//                qAddInputs->setDisabled(1);
//                break;
//            }
//        }

//        qAddGSEControl->setIndex(currentItem);
//        qPopMenu->addAction(qAddGSEControl);
//        qAddSampleValueControl->setIndex(currentItem);
//        qPopMenu->addAction(qAddSampleValueControl);
//        qAddSettingControl->setIndex(currentItem);
//        qPopMenu->addAction(qAddSettingControl);
//        qAddSCLControl->setIndex(currentItem);
//        qPopMenu->addAction(qAddSCLControl);
//        qAddLog->setIndex(currentItem);
//        qPopMenu->addAction(qAddLog);

//        qAddDataSet->setIndex(currentItem);
//        qPopMenu->addAction(qAddDataSet);
//        qAddReportControl->setIndex(currentItem);
//        qPopMenu->addAction(qAddReportControl);
//        qAddLogControl->setIndex(currentItem);
//        qPopMenu->addAction(qAddLogControl);
//        qAddDOI->setIndex(currentItem);
//        qPopMenu->addAction(qAddDOI);
//        qAddInputs->setIndex(currentItem);
//        qPopMenu->addAction(qAddInputs);
//    }

//    if(currentItem.data().toString() == tr("LN"))
//    {
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("Inputs"))
//            {
//                qAddInputs->setDisabled(1);
//                break;
//            }
//        }

//        qAddDataSet->setIndex(currentItem);
//        qPopMenu->addAction(qAddDataSet);
//        qAddReportControl->setIndex(currentItem);
//        qPopMenu->addAction(qAddReportControl);
//        qAddLogControl->setIndex(currentItem);
//        qPopMenu->addAction(qAddLogControl);
//        qAddDOI->setIndex(currentItem);
//        qPopMenu->addAction(qAddDOI);
//        qAddInputs->setIndex(currentItem);
//        qPopMenu->addAction(qAddInputs);
//    }

//    if(currentItem.data().toString() == tr("GSEControl"))
//    {
//        qAddIEDName->setIndex(currentItem);
//        qPopMenu->addAction(qAddIEDName);
//    }

//    if(currentItem.data().toString() == tr("SampleValueControl"))
//    {
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("SmvOpts"))
//            {
//                qAddInputs->setDisabled(1);
//                break;
//            }
//        }

//        qAddSmvOpts->setIndex(currentItem);
//        qPopMenu->addAction(qAddSmvOpts);
//        qAddIEDName->setIndex(currentItem);
//        qPopMenu->addAction(qAddIEDName);
//    }

//    if(currentItem.data().toString().contains(tr("DataSet")))
//    {
//        qAddFCDA->setIndex(currentItem);
//        qPopMenu->addAction(qAddFCDA);
//    }

//    if(currentItem.data().toString().contains(tr("ReportControl")))
//    {
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("OptFields"))
//            {
//                qAddSGEdit->setDisabled(1);
//                break;
//            }
//        }
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("RptEnabled"))
//            {
//                qAddConfSG->setDisabled(1);
//                break;
//            }
//        }
//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            if(currentNode.childNodes().at(i).toElement().tagName() == tr("TrgOps"))
//            {
//                qAddConfSG->setDisabled(1);
//                break;
//            }
//        }
//        qAddOptFields->setIndex(currentItem);
//        qPopMenu->addAction(qAddOptFields);
//        qAddRptEnabled->setIndex(currentItem);
//        qPopMenu->addAction(qAddRptEnabled);
//        qAddTrgOps->setIndex(currentItem);
//        qPopMenu->addAction(qAddTrgOps);
//    }

//    if(currentItem.data().toString().contains(tr("DOI")))
//    {

//        qAddSDI->setIndex(currentItem);
//        qPopMenu->addAction(qAddSDI);
//        qAddDAI->setIndex(currentItem);
//        qPopMenu->addAction(qAddDAI);
//    }

//    if(currentItem.data().toString().contains(tr("SDI")))
//    {

//        qAddSDI->setIndex(currentItem);
//        qPopMenu->addAction(qAddSDI);
//        qAddDAI->setIndex(currentItem);
//        qPopMenu->addAction(qAddDAI);
//    }

//    if(currentItem.data().toString().contains(tr("DAI")))
//    {
//        qAddVal->setIndex(currentItem);
//        qPopMenu->addAction(qAddVal);
//    }

//    if(currentItem.data().toString().contains(tr("Val")))
//    {
//        qAddValContent->setIndex(currentItem);
//        qPopMenu->addAction(qAddValContent);
//    }

//    if(currentItem.data().toString().contains(tr("Inputs")))
//    {
//        qAddExtRef->setIndex(currentItem);
//        qPopMenu->addAction(qAddExtRef);
//    }

//    if(currentItem.data().toString() == tr("DataTypeTemplates"))
//    {
//        qAddLNodeType->setIndex(currentItem);
//        qPopMenu->addAction(qAddLNodeType);
//        qAddDOType->setIndex(currentItem);
//        qPopMenu->addAction(qAddDOType);
//        qAddDAType->setIndex(currentItem);
//        qPopMenu->addAction(qAddDAType);
//        qAddEnumType->setIndex(currentItem);
//        qPopMenu->addAction(qAddEnumType);
//    }

//    if(currentItem.data().toString().contains(tr("LNodeType")))
//    {
//        qAddDO->setIndex(currentItem);
//        qPopMenu->addAction(qAddDO);
//    }

//    if(currentItem.data().toString().contains(tr("DOType")))
//    {
//        qAddSDO->setIndex(currentItem);
//        qPopMenu->addAction(qAddSDO);
//        qAddDA->setIndex(currentItem);
//        qPopMenu->addAction(qAddDA);
//    }

//    if(currentItem.data().toString().contains(tr("DAType")))
//    {
//        qAddBDA->setIndex(currentItem);
//        qPopMenu->addAction(qAddBDA);
//    }

//    if(currentItem.data().toString().contains(tr("EnumType")))
//    {
//        qAddEnumVal->setIndex(currentItem);
//        qPopMenu->addAction(qAddEnumVal);
//    }

//    if(currentItem.data().toString() == tr("DA"))
//    {
//        qAddVal->setIndex(currentItem);
//        qPopMenu->addAction(qAddVal);
//    }

//    if(currentItem.data().toString() == tr("BDA"))
//    {
//        qAddVal->setIndex(currentItem);
//        qPopMenu->addAction(qAddVal);
//    }

//    if(currentItem.data().toString() != tr("SCL"))
//    {
//        qDeleteItem->setIndex(currentItem);
//        qPopMenu->addAction(qDeleteItem);

//        qMoveUp->setIndex(currentItem);
//        qPopMenu->addAction(qMoveUp);


//        qMoveDown->setIndex(currentItem);
//        qPopMenu->addAction(qMoveDown);
//    }

//    qDebug()<<"this row number is"<<currentItem.row();
//    if(currentItem.row()==0)
//        qMoveUp->setEnabled(0);
//    else
//        qMoveUp->setEnabled(1);

//    if(!currentItem.sibling(currentItem.row()+1, 0).isValid())
//        qMoveDown->setEnabled(0);
//    else
//        qMoveDown->setEnabled(1);

//    if(newFileName == NULL)
//    {
//        qPopMenu->setDisabled(1);
//    }

//    qPopMenu->exec(QCursor::pos());
}
//
void MainWindow::addHistoryAct(const QModelIndex& currentIndex)
{
}


void MainWindow::addHeader(const QModelIndex& currentIndex)
{
}

void MainWindow::addSubstation(const QModelIndex& currentIndex)
{
}

void MainWindow::addCommunication(const QModelIndex& currentIndex)
{
}

void MainWindow::addIED(const QModelIndex& currentIndex)
{
}

void MainWindow::addDataTypeTemplates(const QModelIndex& currentIndex)
{

}

void MainWindow::addTextAct(const QModelIndex& currentIndex)
{
}

void MainWindow::addTextContentAct(const QModelIndex& currentIndex)
{

}

void MainWindow::addHitemAct(const QModelIndex& currentIndex)
{
//    qDebug()<<tr("Add Hitem Action");
//    QModelIndex *currentIndex = new QModelIndex();
//        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - Hitem"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(6,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)version")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("(*)revision")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(2,0,new QTableWidgetItem(tr("(*)when")));
//    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(3,0,new QTableWidgetItem(tr("who")));
//    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(4,0,new QTableWidgetItem(tr("what")));
//    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(4,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(5,0,new QTableWidgetItem(tr("why")));
//    AttrTable->item(5,0)->setFlags(AttrTable->item(5,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(5,0)->setCheckState(Qt::Unchecked);

//    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(1,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(2,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(3,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(4,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(5,1,new QTableWidgetItem(tr("")));

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    while(AttrDlg->exec() == QDialog::Accepted)
//    {
//        bool VersionCollide = 0;
//        qDebug()<<tr("Attr Dialog Confirm");
//        QDomElement qNewElement = doc->createElement(tr("Hitem"));
//        if(AttrTable->item(0,1)->text()==tr(""))
//        {
//            QMessageBox::warning(NULL,tr("警告"),tr("version项为必需项，不能为空!"));
//            continue;
//        }
//        if(AttrTable->item(1,1)->text()==tr(""))
//        {
//            QMessageBox::warning(NULL,tr("警告"),tr("revision项为必需项，不能为空!"));
//            continue;
//        }
//        if(AttrTable->item(2,1)->text()==tr(""))
//        {
//            QMessageBox::warning(NULL,tr("警告"),tr("when项为必需项，不能为空!"));
//            continue;
//        }

//        for(int i=0; i<currentNode.childNodes().count(); i++)
//        {
//            QDomNamedNodeMap oldAttr = currentNode.childNodes().at(i).attributes();
//            qDebug()<<oldAttr.namedItem(tr("version")).nodeValue();
//            if(oldAttr.namedItem(tr("version")).nodeValue() == AttrTable->item(0,1)->text()
//             && oldAttr.namedItem(tr("revision")).nodeValue() == AttrTable->item(1,1)->text())
//            {
//                QMessageBox::warning(NULL,tr("警告"),tr("version, revision不能重复!"));
//                VersionCollide = 1;
//                break;
//            }
//        }

//        if(VersionCollide)
//            continue;

//        qNewElement.setAttribute(tr("version"), AttrTable->item(0,1)->text());
//        qNewElement.setAttribute(tr("revision"), AttrTable->item(1,1)->text());
//        qNewElement.setAttribute(tr("when"), AttrTable->item(2,1)->text());
//        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("who"), AttrTable->item(3,1)->text());
//        if(AttrTable->item(4,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("what"), AttrTable->item(4,1)->text());
//        if(AttrTable->item(5,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("why"), AttrTable->item(5,1)->text());

//        currentNode.appendChild(qNewElement);
//        DomItem newItem = DomItem(qNewElement, 0, 0);
//        currentItem->insertChildren(currentItem->childNum(), newItem);
//    //        currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//        break;
//        qDebug()<<currentItem->node().toElement().tagName();
//    }
}

void MainWindow::addVoltageLevel(const QModelIndex& currentIndex)
{
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - VoltageLevel"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(2,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)name")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & ~Qt::ItemIsEditable);
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("desc")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & ~Qt::ItemIsEditable);
//    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);

//    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(1,1,new QTableWidgetItem(tr("")));

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    while(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("VoltageLevel"));
//        if(AttrTable->item(0,1)->text()==tr(""))
//        {
//            QMessageBox::warning(NULL,tr("警告"),tr("name项为必需项，不能为空!"));
//            continue;
//        }

//        qNewElement.setAttribute(tr("name"), AttrTable->item(0,1)->text());
//        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("desc"), AttrTable->item(1,1)->text());

//        currentNode.appendChild(qNewElement);
//        DomItem newItem = DomItem(qNewElement, 0, 0);
//        currentItem->insertChildren(currentItem->childNum(), newItem);
//    //        currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//        break;
//    }
}

void MainWindow::addFunction(const QModelIndex& currentIndex)
{
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - Function"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(2,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)name")));
//    AttrTable->item(0,0)->setFlags(Qt::ItemIsEnabled);
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("desc")));
//    AttrTable->item(1,0)->setFlags(Qt::ItemIsEnabled);
//    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);

//    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(1,1,new QTableWidgetItem(tr("")));

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    while(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("Function"));
//        if(AttrTable->item(0,1)->text()==tr(""))
//        {
//            QMessageBox::warning(NULL,tr("警告"),tr("name项为必需项，不能为空!"));
//            continue;
//        }

//        qNewElement.setAttribute(tr("name"), AttrTable->item(0,1)->text());
//        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("desc"), AttrTable->item(1,1)->text());

//        currentNode.appendChild(qNewElement);
//        DomItem newItem = DomItem(qNewElement, 0, 0);
//        currentItem->insertChildren(currentItem->childNum(), newItem);
//    //        currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//        break;
//    }
}

void MainWindow::addPowerTransformer(const QModelIndex& currentIndex)
{
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - PowerTransformer"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(4,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)type")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & ~Qt::ItemIsEditable);
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("vitual")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & ~Qt::ItemIsEditable);
//    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(2,0,new QTableWidgetItem(tr("(*)name")));
//    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & ~Qt::ItemIsEditable);
//    AttrTable->setItem(3,0,new QTableWidgetItem(tr("desc")));
//    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & ~Qt::ItemIsEditable);
//    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);

//    AttrTable->setItem(0,1,new QTableWidgetItem(tr("PTR")));
//    AttrTable->item(0,1)->setFlags(AttrTable->item(0,1)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setCellWidget(1,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(1,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
//    ((QComboBox*)(AttrTable->cellWidget(1,1)))->setCurrentIndex(1);
//    AttrTable->setItem(2,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(3,1,new QTableWidgetItem(tr("")));

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    while(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("PowerTransformer"));
//        if(AttrTable->item(2,1)->text()==tr(""))
//        {
//            QMessageBox::warning(NULL,tr("警告"),tr("name项为必需项，不能为空!"));
//            continue;
//        }

//        qNewElement.setAttribute(tr("type"), AttrTable->item(0,1)->text());
//        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("vitural"), ((QComboBox*)(AttrTable->cellWidget(1,1)))->currentText());
//        qNewElement.setAttribute(tr("name"), AttrTable->item(2,1)->text());
//        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("desc"), AttrTable->item(3,1)->text());

//        currentNode.appendChild(qNewElement);
//        DomItem newItem = DomItem(qNewElement, 0, 0);
//        currentItem->insertChildren(currentItem->childNum(), newItem);
//    //        currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//        break;
//    }
}

void MainWindow::addGeneralEquipment(const QModelIndex& currentIndex)
{
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - GeneralEquipment"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(4,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)type")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & ~Qt::ItemIsEditable);
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("vitual")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & ~Qt::ItemIsEditable);
//    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(2,0,new QTableWidgetItem(tr("(*)name")));
//    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & ~Qt::ItemIsEditable);
//    AttrTable->setItem(3,0,new QTableWidgetItem(tr("desc")));
//    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & ~Qt::ItemIsEditable);
//    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);

//    AttrTable->setCellWidget(0,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(0,1)))->addItems(QStringList()<<tr("AXN")<<tr("BAT")<<tr("MOT"));
//    AttrTable->setCellWidget(1,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(1,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
//    ((QComboBox*)(AttrTable->cellWidget(1,1)))->setCurrentIndex(1);
//    AttrTable->setItem(2,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(3,1,new QTableWidgetItem(tr("")));

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    while(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("GeneralEquipment"));
//        if(((QComboBox*)(AttrTable->cellWidget(0,1)))->currentText()==tr(""))
//        {
//            QMessageBox::warning(NULL,tr("警告"),tr("type项为必需项，不能为空!"));
//            continue;
//        }
//        if(AttrTable->item(2,1)->text()==tr(""))
//        {
//            QMessageBox::warning(NULL,tr("警告"),tr("name项为必需项，不能为空!"));
//            continue;
//        }

//        qNewElement.setAttribute(tr("type"), ((QComboBox*)(AttrTable->cellWidget(0,1)))->currentText());
//        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("vitural"), ((QComboBox*)(AttrTable->cellWidget(1,1)))->currentText());
//        qNewElement.setAttribute(tr("name"), AttrTable->item(2,1)->text());
//        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("desc"), AttrTable->item(3,1)->text());

//        currentNode.appendChild(qNewElement);
//        DomItem newItem = DomItem(qNewElement, 0, 0);
//        currentItem->insertChildren(currentItem->childNum(), newItem);
//    //        currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//        break;
//    }

}

void MainWindow::addLNode(const QModelIndex& currentIndex)
{
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - LNode"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(7,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("lnInst")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("(*)lnClass")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(2,0,new QTableWidgetItem(tr("iedName")));
//    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(3,0,new QTableWidgetItem(tr("ldInst")));
//    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(4,0,new QTableWidgetItem(tr("prefix")));
//    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(4,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(5,0,new QTableWidgetItem(tr("lnType")));
//    AttrTable->item(5,0)->setFlags(AttrTable->item(5,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(5,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(6,0,new QTableWidgetItem(tr("desc")));
//    AttrTable->item(6,0)->setFlags(AttrTable->item(6,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(6,0)->setCheckState(Qt::Unchecked);

//    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
//    AttrTable->setCellWidget(1,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(1,1)))->addItems(lnClass);
//    AttrTable->setItem(2,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(3,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(4,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(5,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(6,1,new QTableWidgetItem(tr("")));

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    if(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("LNode"));
//        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("lnInst"), AttrTable->item(0,1)->text());
//        qNewElement.setAttribute(tr("lnClass"), ((QComboBox*)(AttrTable->cellWidget(1,1)))->currentText());
//        if(AttrTable->item(2,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("iedName"), AttrTable->item(2,1)->text());
//        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("ldInst"), AttrTable->item(3,1)->text());
//        if(AttrTable->item(4,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("prefix"), AttrTable->item(4,1)->text());
//        if(AttrTable->item(5,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("lnType"), AttrTable->item(5,1)->text());
//        if(AttrTable->item(6,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("desc"), AttrTable->item(6,1)->text());


//        currentNode.appendChild(qNewElement);
//        DomItem newItem = DomItem(qNewElement, 0, 0);
//        currentItem->insertChildren(currentItem->childNum(), newItem);
//    //        currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//    }
}

void MainWindow::addBay(const QModelIndex& currentIndex)
{

}

void MainWindow::addSubFunction(const QModelIndex& currentIndex)
{

}

void MainWindow::addConductingEquipment(const QModelIndex& currentIndex)
{

}

void MainWindow::addSubEquipment(const QModelIndex& currentIndex)
{

}

void MainWindow::addVoltage(const QModelIndex& currentIndex)
{

}

void MainWindow::addConnectivityNode(const QModelIndex& currentIndex)
{

}

void MainWindow::addTerminal(const QModelIndex& currentIndex)
{

}

void MainWindow::addServices(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();
//    qDebug()<<currentNode.toElement().tagName();

//    QModelIndex parentIndex = currentIndex.parent();

//    QDomElement qNewElement = doc->createElement(tr("Services"));
//    currentNode.appendChild(qNewElement);
//    DomItem newItem = DomItem(qNewElement, 0, 0);
//    currentItem->insertChildren(currentItem->childNum(), newItem);
////        currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//    view->setExpanded(parentIndex,0);
//    view->setExpanded(parentIndex,1);
//    view->setExpanded(currentIndex,1);
}

void MainWindow::addAccessPoint(const QModelIndex& currentIndex)
{
//    qDebug()<<tr("Add AccessPoint Action");
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - AccessPoint"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(4,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)name")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("desc")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(2,0,new QTableWidgetItem(tr("route")));
//    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(3,0,new QTableWidgetItem(tr("clock")));
//    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);

//    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(1,1,new QTableWidgetItem(tr("")));
////    AttrTable->setCellWidget(2,1,new QCalendarWidget(this));
//    AttrTable->setItem(2,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(3,1,new QTableWidgetItem(tr("")));

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    while(AttrDlg->exec() == QDialog::Accepted)
//    {
//        qDebug()<<tr("Attr Dialog Confirm");
//        QDomElement qNewElement = doc->createElement(tr("AccessPoint"));

//        if(AttrTable->item(0,1)->text()==tr(""))
//        {
//            QMessageBox::warning(NULL,tr("警告"),tr("name项为必需项，不能为空!"));
//            continue;
//        }

//        qNewElement.setAttribute(tr("name"), AttrTable->item(0,1)->text());
//        if((AttrTable->item(1,0))->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("desc"), AttrTable->item(1,1)->text());
//        if((AttrTable->item(2,0))->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("route"), AttrTable->item(2,1)->text());
//        if((AttrTable->item(3,0))->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("clock"), AttrTable->item(3,1)->text());

//        currentNode.appendChild(qNewElement);
//        DomItem newItem = DomItem(qNewElement, 0, 0);
//        currentItem->insertChildren(currentItem->childNum(), newItem);
//    //        currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//        break;
//    }
}

void MainWindow::addDynAssociation(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();
//    qDebug()<<currentNode.toElement().tagName();

//    QDomElement qNewElement = doc->createElement(tr("DynAssociation"));
//    currentNode.appendChild(qNewElement);
//    DomItem newItem = DomItem(qNewElement, 0, 0);
//    currentItem->insertChildren(currentItem->childNum(), newItem);
////        currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//    QModelIndex parentIndex = currentIndex.parent();
//    view->setExpanded(parentIndex,0);
//    view->setExpanded(parentIndex,1);
//    view->setExpanded(currentIndex,1);
}

void MainWindow::addSettingGroups(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////    //        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();
//    qDebug()<<currentNode.toElement().tagName();

//    QDomElement qNewElement = doc->createElement(tr("SettingGroups"));
//    currentNode.appendChild(qNewElement);
//    DomItem newItem = DomItem(qNewElement, 0, 0);
//    currentItem->insertChildren(currentItem->childNum(), newItem);
////        currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//    QModelIndex parentIndex = currentIndex.parent();
//    view->setExpanded(parentIndex,0);
//    view->setExpanded(parentIndex,1);
//    view->setExpanded(currentIndex,1);
}

void MainWindow::addGetDirectory(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();
//    qDebug()<<currentNode.toElement().tagName();

//    QDomElement qNewElement = doc->createElement(tr("GetDirectory"));
//    currentNode.appendChild(qNewElement);
//    DomItem newItem = DomItem(qNewElement, 0, 0);
//    currentItem->insertChildren(currentItem->childNum(), newItem);
////        currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//    QModelIndex parentIndex = currentIndex.parent();
//    view->setExpanded(parentIndex,0);
//    view->setExpanded(parentIndex,1);
//    view->setExpanded(currentIndex,1);
}

void MainWindow::addGetDataObjectDefinition(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();
//    qDebug()<<currentNode.toElement().tagName();

//    QDomElement qNewElement = doc->createElement(tr("GetDataObjectDefinition"));
//    currentNode.appendChild(qNewElement);
//    DomItem newItem = DomItem(qNewElement, 0, 0);
//    currentItem->insertChildren(currentItem->childNum(), newItem);
////        currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//    QModelIndex parentIndex = currentIndex.parent();
//    view->setExpanded(parentIndex,0);
//    view->setExpanded(parentIndex,1);
//    view->setExpanded(currentIndex,1);
}

void MainWindow::addDataObjectDirectory(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();
//    qDebug()<<currentNode.toElement().tagName();

//    QDomElement qNewElement = doc->createElement(tr("DataObjectDirectory"));
//    currentNode.appendChild(qNewElement);
//    DomItem newItem = DomItem(qNewElement, 0, 0);
//    currentItem->insertChildren(currentItem->childNum(), newItem);
////        currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//    QModelIndex parentIndex = currentIndex.parent();
//    view->setExpanded(parentIndex,0);
//    view->setExpanded(parentIndex,1);
//    view->setExpanded(currentIndex,1);
}

void MainWindow::addGetDataSetValue(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();
//    qDebug()<<currentNode.toElement().tagName();

//    QDomElement qNewElement = doc->createElement(tr("GetDataSetValue"));
//    currentNode.appendChild(qNewElement);
//    DomItem newItem = DomItem(qNewElement, 0, 0);
//    currentItem->insertChildren(currentItem->childNum(), newItem);
////        currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//    QModelIndex parentIndex = currentIndex.parent();
//    view->setExpanded(parentIndex,0);
//    view->setExpanded(parentIndex,1);
//    view->setExpanded(currentIndex,1);
}

void MainWindow::addSetDataSetValue(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();
//    qDebug()<<currentNode.toElement().tagName();

//    QDomElement qNewElement = doc->createElement(tr("SetDataSetValue"));
//    currentNode.appendChild(qNewElement);
//    DomItem newItem = DomItem(qNewElement, 0, 0);
//    currentItem->insertChildren(currentItem->childNum(), newItem);
////        currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//    QModelIndex parentIndex = currentIndex.parent();
//    view->setExpanded(parentIndex,0);
//    view->setExpanded(parentIndex,1);
//    view->setExpanded(currentIndex,1);
}

void MainWindow::addDataSetDirectory(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();
//    qDebug()<<currentNode.toElement().tagName();

//    QDomElement qNewElement = doc->createElement(tr("DataSetDirectory"));
//    currentNode.appendChild(qNewElement);
//    DomItem newItem = DomItem(qNewElement, 0, 0);
//    currentItem->insertChildren(currentItem->childNum(), newItem);
////        currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//    QModelIndex parentIndex = currentIndex.parent();
//    view->setExpanded(parentIndex,0);
//    view->setExpanded(parentIndex,1);
//    view->setExpanded(currentIndex,1);
}

void MainWindow::addConfDataSet(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - ConfDataSet"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(2,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)max")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("maxAttributes")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);

////    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
////    AttrTable->setCellWidget(0,1,new QLineEdit(tr("请输入数字"),this));
//    AttrTable->setCellWidget(0,1,new QSpinBox(this));
////    ((QSpinBox*)(AttrTable->cellWidget(0,1)))->setMinimum(0);
////    ((QLineEdit*)(AttrTable->cellWidget(0,1)))->setValidator(new QIntValidator(1,65536,this));

////    AttrTable->setCellWidget(0,1,new QComboBox(this));
////    (QComboBox*)(AttrTable->cellWidget(0,1))->addItems(
////    AttrTable->setItem(1,1,new QTableWidgetItem(tr("")));
//    AttrTable->setCellWidget(1,1,new QSpinBox(this));
////    ((QSpinBox*)(AttrTable->cellWidget(1,1)))->setMinimum(0);

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    if(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("ConfDataSet"));

//        qNewElement.setAttribute(tr("max"), ((QSpinBox*)(AttrTable->cellWidget(0,1)))->text());
//        if((AttrTable->item(1,0))->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("maxAttributes"), ((QSpinBox*)(AttrTable->cellWidget(1,1)))->text());

//        currentNode.appendChild(qNewElement);
//        DomItem newItem = DomItem(qNewElement, 0, 0);
//        currentItem->insertChildren(currentItem->childNum(), newItem);
//    //        currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//    }
}

void MainWindow::addDynDataSet(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - DynDataSet"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(2,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)max")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("maxAttributes")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);

//    AttrTable->setCellWidget(0,1,new QSpinBox(this));
//    AttrTable->setCellWidget(1,1,new QSpinBox(this));

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    if(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("DynDataSet"));

//        qNewElement.setAttribute(tr("max"), ((QSpinBox*)(AttrTable->cellWidget(0,1)))->text());
//        if((AttrTable->item(1,0))->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("maxAttributes"), ((QSpinBox*)(AttrTable->cellWidget(1,1)))->text());

//        currentNode.appendChild(qNewElement);
//        DomItem newItem = DomItem(qNewElement, 0, 0);
//        currentItem->insertChildren(currentItem->childNum(), newItem);
//    //        currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//    }
}

void MainWindow::addReadWrite(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();
//    qDebug()<<currentNode.toElement().tagName();

//    QDomElement qNewElement = doc->createElement(tr("ReadWrite"));
//    currentNode.appendChild(qNewElement);
//DomItem newItem = DomItem(qNewElement, 0, 0);
//	currentItem->insertChildren(currentItem->childNum(), newItem);
//// 	currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//    QModelIndex parentIndex = currentIndex.parent();
//    view->setExpanded(parentIndex,0);
//    view->setExpanded(parentIndex,1);
//    view->setExpanded(currentIndex,1);
}

void MainWindow::addTimerActivatedControl(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();
//    qDebug()<<currentNode.toElement().tagName();

//    QDomElement qNewElement = doc->createElement(tr("TimerActivatedControl"));
//    currentNode.appendChild(qNewElement);
//    DomItem newItem = DomItem(qNewElement, 0, 0);
//    currentItem->insertChildren(currentItem->childNum(), newItem);
////        currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//    QModelIndex parentIndex = currentIndex.parent();
//    view->setExpanded(parentIndex,0);
//    view->setExpanded(parentIndex,1);
//    view->setExpanded(currentIndex,1);
}

void MainWindow::addConfReportControl(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - ConfReportControl"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(1,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)max")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));

//    AttrTable->setCellWidget(0,1,new QSpinBox(this));

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    if(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("ConfReportControl"));

//        qNewElement.setAttribute(tr("max"), ((QSpinBox*)(AttrTable->cellWidget(0,1)))->text());

//        currentNode.appendChild(qNewElement);
//        DomItem newItem = DomItem(qNewElement, 0, 0);
//        currentItem->insertChildren(currentItem->childNum(), newItem);
//    //        currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//    }
}

void MainWindow::addGetCBValues(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();
//    qDebug()<<currentNode.toElement().tagName();

//    QDomElement qNewElement = doc->createElement(tr("GetCBValues"));
//    currentNode.appendChild(qNewElement);
//    DomItem newItem = DomItem(qNewElement, 0, 0);
//    currentItem->insertChildren(currentItem->childNum(), newItem);
////        currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//    QModelIndex parentIndex = currentIndex.parent();
//    view->setExpanded(parentIndex,0);
//    view->setExpanded(parentIndex,1);
//    view->setExpanded(currentIndex,1);
}

void MainWindow::addConfLogControl(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - ConfLogControl"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(1,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)max")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));

//    AttrTable->setCellWidget(0,1,new QSpinBox(this));

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    if(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("ConfLogControl"));

//        qNewElement.setAttribute(tr("max"), ((QSpinBox*)(AttrTable->cellWidget(0,1)))->text());

//        currentNode.appendChild(qNewElement);
//        DomItem newItem = DomItem(qNewElement, 0, 0);
//        currentItem->insertChildren(currentItem->childNum(), newItem);
//    //        currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//    }
}

void MainWindow::addReportSettings(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - ReportSettings"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(7,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("cbname")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("datset")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(2,0,new QTableWidgetItem(tr("rptID")));
//    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(3,0,new QTableWidgetItem(tr("optFields")));
//    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(4,0,new QTableWidgetItem(tr("bufTime")));
//    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(4,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(5,0,new QTableWidgetItem(tr("trgOps")));
//    AttrTable->item(5,0)->setFlags(AttrTable->item(5,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(5,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(6,0,new QTableWidgetItem(tr("intgPd")));
//    AttrTable->item(6,0)->setFlags(AttrTable->item(6,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(6,0)->setCheckState(Qt::Unchecked);

//    AttrTable->setCellWidget(0,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(0,1)))->addItems(QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix"));
//    ((QComboBox*)(AttrTable->cellWidget(0,1)))->setCurrentIndex(2);
//    AttrTable->setCellWidget(1,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(1,1)))->addItems(QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix"));
//    ((QComboBox*)(AttrTable->cellWidget(1,1)))->setCurrentIndex(2);
//    AttrTable->setCellWidget(2,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(2,1)))->addItems(QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix"));
//    ((QComboBox*)(AttrTable->cellWidget(2,1)))->setCurrentIndex(2);
//    AttrTable->setCellWidget(3,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(3,1)))->addItems(QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix"));
//    ((QComboBox*)(AttrTable->cellWidget(3,1)))->setCurrentIndex(2);
//    AttrTable->setCellWidget(4,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(4,1)))->addItems(QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix"));
//    ((QComboBox*)(AttrTable->cellWidget(4,1)))->setCurrentIndex(2);
//    AttrTable->setCellWidget(5,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(5,1)))->addItems(QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix"));
//    ((QComboBox*)(AttrTable->cellWidget(5,1)))->setCurrentIndex(2);
//    AttrTable->setCellWidget(6,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(6,1)))->addItems(QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix"));
//    ((QComboBox*)(AttrTable->cellWidget(6,1)))->setCurrentIndex(2);

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    if(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("ReportSettings"));

//        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("cbname"), ((QComboBox*)(AttrTable->cellWidget(0,1)))->currentText());
//        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("datset"), ((QComboBox*)(AttrTable->cellWidget(1,1)))->currentText());
//        if(AttrTable->item(2,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("rptID"), ((QComboBox*)(AttrTable->cellWidget(2,1)))->currentText());
//        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("optFields"), ((QComboBox*)(AttrTable->cellWidget(3,1)))->currentText());
//        if(AttrTable->item(4,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("bufTime"), ((QComboBox*)(AttrTable->cellWidget(4,1)))->currentText());
//        if(AttrTable->item(5,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("trgOps"), ((QComboBox*)(AttrTable->cellWidget(5,1)))->currentText());
//        if(AttrTable->item(6,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("intgPd"), ((QComboBox*)(AttrTable->cellWidget(6,1)))->currentText());

//        currentNode.appendChild(qNewElement);
//        DomItem newItem = DomItem(qNewElement, 0, 0);
//        currentItem->insertChildren(currentItem->childNum(), newItem);
//    //        currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//    }
}

void MainWindow::addLogSettings(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - LogSettings"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(5,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("cbname")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("datset")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(2,0,new QTableWidgetItem(tr("logEna")));
//    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(3,0,new QTableWidgetItem(tr("trgOps")));
//    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(4,0,new QTableWidgetItem(tr("intgPd")));
//    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(4,0)->setCheckState(Qt::Unchecked);

//    AttrTable->setCellWidget(0,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(0,1)))->addItems(QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix"));
//    ((QComboBox*)(AttrTable->cellWidget(0,1)))->setCurrentIndex(2);
//    AttrTable->setCellWidget(1,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(1,1)))->addItems(QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix"));
//    ((QComboBox*)(AttrTable->cellWidget(1,1)))->setCurrentIndex(2);
//    AttrTable->setCellWidget(2,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(2,1)))->addItems(QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix"));
//    ((QComboBox*)(AttrTable->cellWidget(2,1)))->setCurrentIndex(2);
//    AttrTable->setCellWidget(3,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(3,1)))->addItems(QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix"));
//    ((QComboBox*)(AttrTable->cellWidget(3,1)))->setCurrentIndex(2);
//    AttrTable->setCellWidget(4,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(4,1)))->addItems(QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix"));
//    ((QComboBox*)(AttrTable->cellWidget(4,1)))->setCurrentIndex(2);

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    if(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("LogSettings"));

//        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("cbname"), ((QComboBox*)(AttrTable->cellWidget(0,1)))->currentText());
//        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("datset"), ((QComboBox*)(AttrTable->cellWidget(1,1)))->currentText());
//        if(AttrTable->item(2,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("logEna"), ((QComboBox*)(AttrTable->cellWidget(2,1)))->currentText());
//        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("trgOps"), ((QComboBox*)(AttrTable->cellWidget(3,1)))->currentText());
//        if(AttrTable->item(4,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("intgPd"), ((QComboBox*)(AttrTable->cellWidget(4,1)))->currentText());

//        currentNode.appendChild(qNewElement);
//        DomItem newItem = DomItem(qNewElement, 0, 0);
//        currentItem->insertChildren(currentItem->childNum(), newItem);
//    //        currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//    }
}

void MainWindow::addGSESettings(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - GSESettings"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(4,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("cbname")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("datset")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(2,0,new QTableWidgetItem(tr("appID")));
//    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(3,0,new QTableWidgetItem(tr("dataLabel")));
//    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);

//    AttrTable->setCellWidget(0,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(0,1)))->addItems(QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix"));
//    ((QComboBox*)(AttrTable->cellWidget(0,1)))->setCurrentIndex(2);
//    AttrTable->setCellWidget(1,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(1,1)))->addItems(QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix"));
//    ((QComboBox*)(AttrTable->cellWidget(1,1)))->setCurrentIndex(2);
//    AttrTable->setCellWidget(2,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(2,1)))->addItems(QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix"));
//    ((QComboBox*)(AttrTable->cellWidget(2,1)))->setCurrentIndex(2);
//    AttrTable->setCellWidget(3,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(3,1)))->addItems(QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix"));
//    ((QComboBox*)(AttrTable->cellWidget(3,1)))->setCurrentIndex(2);

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    if(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("GSESettings"));

//        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("cbname"), ((QComboBox*)(AttrTable->cellWidget(0,1)))->currentText());
//        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("datset"), ((QComboBox*)(AttrTable->cellWidget(1,1)))->currentText());
//        if(AttrTable->item(2,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("appID"), ((QComboBox*)(AttrTable->cellWidget(2,1)))->currentText());
//        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("dataLevel"), ((QComboBox*)(AttrTable->cellWidget(3,1)))->currentText());

//        currentNode.appendChild(qNewElement);
//        DomItem newItem = DomItem(qNewElement, 0, 0);
//        currentItem->insertChildren(currentItem->childNum(), newItem);
//    //        currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//    }
}

void MainWindow::addSMVSettings(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - SMVSettings"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(5,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("cbname")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("datset")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(2,0,new QTableWidgetItem(tr("svID")));
//    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(3,0,new QTableWidgetItem(tr("optFields")));
//    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(4,0,new QTableWidgetItem(tr("smpRate")));
//    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(4,0)->setCheckState(Qt::Unchecked);

//    AttrTable->setCellWidget(0,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(0,1)))->addItems(QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix"));
//    ((QComboBox*)(AttrTable->cellWidget(0,1)))->setCurrentIndex(2);
//    AttrTable->setCellWidget(1,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(1,1)))->addItems(QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix"));
//    ((QComboBox*)(AttrTable->cellWidget(1,1)))->setCurrentIndex(2);
//    AttrTable->setCellWidget(2,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(2,1)))->addItems(QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix"));
//    ((QComboBox*)(AttrTable->cellWidget(2,1)))->setCurrentIndex(2);
//    AttrTable->setCellWidget(3,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(3,1)))->addItems(QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix"));
//    ((QComboBox*)(AttrTable->cellWidget(3,1)))->setCurrentIndex(2);
//    AttrTable->setCellWidget(4,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(4,1)))->addItems(QStringList()<<tr("Dyn")<<tr("Conf")<<tr("Fix"));
//    ((QComboBox*)(AttrTable->cellWidget(4,1)))->setCurrentIndex(2);

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    if(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("SMVSettings"));

//        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("cbname"), ((QComboBox*)(AttrTable->cellWidget(0,1)))->currentText());
//        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("datset"), ((QComboBox*)(AttrTable->cellWidget(1,1)))->currentText());
//        if(AttrTable->item(2,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("svID"), ((QComboBox*)(AttrTable->cellWidget(2,1)))->currentText());
//        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("optFields"), ((QComboBox*)(AttrTable->cellWidget(3,1)))->currentText());
//        if(AttrTable->item(4,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("smpRate"), ((QComboBox*)(AttrTable->cellWidget(4,1)))->currentText());

//        currentNode.appendChild(qNewElement);
//        DomItem newItem = DomItem(qNewElement, 0, 0);
//        currentItem->insertChildren(currentItem->childNum(), newItem);
//    //        currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//    }
}

void MainWindow::addGSEDir(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();
//    qDebug()<<currentNode.toElement().tagName();

//    QDomElement qNewElement = doc->createElement(tr("GSEDir"));
//    currentNode.appendChild(qNewElement);
//    DomItem newItem = DomItem(qNewElement, 0, 0);
//    currentItem->insertChildren(currentItem->childNum(), newItem);
////        currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//    QModelIndex parentIndex = currentIndex.parent();
//    view->setExpanded(parentIndex,0);
//    view->setExpanded(parentIndex,1);
//    view->setExpanded(currentIndex,1);
}

void MainWindow::addGOOSE(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - GOOSE"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(1,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)max")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));

//    AttrTable->setCellWidget(0,1,new QSpinBox(this));

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    if(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("GOOSE"));

//        qNewElement.setAttribute(tr("max"), ((QSpinBox*)(AttrTable->cellWidget(0,1)))->text());

//        currentNode.appendChild(qNewElement);
//        DomItem newItem = DomItem(qNewElement, 0, 0);
//        currentItem->insertChildren(currentItem->childNum(), newItem);
//    //        currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//    }
}

void MainWindow::addGSSE(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - GSSE"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(1,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)max")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));

//    AttrTable->setCellWidget(0,1,new QSpinBox(this));

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    if(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("GSSE"));


//        qNewElement.setAttribute(tr("max"), ((QSpinBox*)(AttrTable->cellWidget(0,1)))->text());

//        currentNode.appendChild(qNewElement);
//DomItem newItem = DomItem(qNewElement, 0, 0);
//	currentItem->insertChildren(currentItem->childNum(), newItem);
//// 	currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//    }
}

void MainWindow::addFileHandling(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();
//    qDebug()<<currentNode.toElement().tagName();

//    QDomElement qNewElement = doc->createElement(tr("FileHandling"));
//    currentNode.appendChild(qNewElement);
//DomItem newItem = DomItem(qNewElement, 0, 0);
//	currentItem->insertChildren(currentItem->childNum(), newItem);
//// 	currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//    QModelIndex parentIndex = currentIndex.parent();
//    view->setExpanded(parentIndex,0);
//    view->setExpanded(parentIndex,1);
//    view->setExpanded(currentIndex,1);
}

void MainWindow::addConfLNs(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - ConfLNs"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(2,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("fixPrefix")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("fixLnInst")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);

//    AttrTable->setCellWidget(0,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(0,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
//    ((QComboBox*)(AttrTable->cellWidget(0,1)))->setCurrentIndex(1);
//    AttrTable->setCellWidget(1,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(1,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
//    ((QComboBox*)(AttrTable->cellWidget(1,1)))->setCurrentIndex(1);
//    AttrTable->setCellWidget(2,1,new QComboBox(this));

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    if(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("ConfLNs"));

//        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("fixPrefix"), ((QComboBox*)(AttrTable->cellWidget(0,1)))->currentText());
//        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("fixLnInst"), ((QComboBox*)(AttrTable->cellWidget(1,1)))->currentText());

//        currentNode.appendChild(qNewElement);
//DomItem newItem = DomItem(qNewElement, 0, 0);
//	currentItem->insertChildren(currentItem->childNum(), newItem);
//// 	currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//     }
}

void MainWindow::addSGEdit(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();
//    qDebug()<<currentNode.toElement().tagName();

//    QDomElement qNewElement = doc->createElement(tr("SGEdit"));
//    currentNode.appendChild(qNewElement);
//DomItem newItem = DomItem(qNewElement, 0, 0);
//	currentItem->insertChildren(currentItem->childNum(), newItem);
//// 	currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//    QModelIndex parentIndex = currentIndex.parent();
//    view->setExpanded(parentIndex,0);
//    view->setExpanded(parentIndex,1);
//    view->setExpanded(currentIndex,1);
}

void MainWindow::addConfSG(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();
//    qDebug()<<currentNode.toElement().tagName();

//    QDomElement qNewElement = doc->createElement(tr("ConfSG"));
//    currentNode.appendChild(qNewElement);
//DomItem newItem = DomItem(qNewElement, 0, 0);
//	currentItem->insertChildren(currentItem->childNum(), newItem);
//// 	currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//    QModelIndex parentIndex = currentIndex.parent();
//    view->setExpanded(parentIndex,0);
//    view->setExpanded(parentIndex,1);
//    view->setExpanded(currentIndex,1);
}

void MainWindow::addServer(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - Server"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(2,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("desc")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("timeout")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);

//    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
//    AttrTable->setCellWidget(1,1,new QSpinBox(this));

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    if(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("Server"));
//        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("desc"), AttrTable->item(0,1)->text());
//        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("timeout"), ((QSpinBox*)(AttrTable->cellWidget(1,1)))->text());

//        currentNode.appendChild(qNewElement);
//DomItem newItem = DomItem(qNewElement, 0, 0);
//	currentItem->insertChildren(currentItem->childNum(), newItem);
//// 	currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);

//    }
}

void MainWindow::addLN(const QModelIndex& currentIndex)
{
//    qDebug()<<"Add LN";
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - LN"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(5,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)lnClass")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("(*)inst")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(2,0,new QTableWidgetItem(tr("(*)lnType")));
//    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(3,0,new QTableWidgetItem(tr("prefix")));
//    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(4,0,new QTableWidgetItem(tr("desc")));
//    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(4,0)->setCheckState(Qt::Unchecked);

//    AttrTable->setCellWidget(0,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(0,1)))->addItems(lnClass);
//    AttrTable->setCellWidget(1,1,new QSpinBox(this));
//    AttrTable->setCellWidget(2,1,new QComboBox(this));
//    AttrTable->setItem(3,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(4,1,new QTableWidgetItem(tr("")));

//    QDomNode SCLNode;
//    if(currentNode.parentNode().parentNode().parentNode().toElement().tagName() == tr("IED"))
//    {
//        SCLNode = currentNode.parentNode().parentNode().parentNode().parentNode();
//    }
//    else if(currentNode.parentNode().parentNode().toElement().tagName() == tr("IED"))
//        SCLNode = currentNode.parentNode().parentNode().parentNode();

//    //if(IEDNode.nextSiblingElement("DataTypeTemplates"))

//    QDomNode TypeNode;
//    for(int i=0; i<SCLNode.childNodes().count(); i++)
//    {
//        if(SCLNode.childNodes().at(i).toElement().tagName() == tr("DataTypeTemplates"))
//        {
//            TypeNode = SCLNode.childNodes().at(i);
//            qDebug()<<TypeNode.toElement().tagName();
//            for(int i=0; i<TypeNode.childNodes().count(); i++)
//            {
//                if(TypeNode.childNodes().at(i).toElement().tagName() == tr("LNodeType"))
//                {
//                    QStringList lnType;
//                    QDomNode LNodeTypeNode = TypeNode.childNodes().at(i);

//                    qDebug()<<LNodeTypeNode.toElement().tagName();
//                    if(LNodeTypeNode.attributes().contains(tr("id")))
//                    {
//                        qDebug()<<LNodeTypeNode.attributes().namedItem("id").toAttr().value();
//                        lnType.append(LNodeTypeNode.attributes().namedItem("id").toAttr().value());
//                    }
//                    ((QComboBox*)(AttrTable->cellWidget(2,1)))->addItems(lnType);
//                }
//            }
//        }
//    }

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    if(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("LN"));
//        qNewElement.setAttribute(tr("lnClass"), ((QComboBox*)(AttrTable->cellWidget(0,1)))->currentText());
//        qNewElement.setAttribute(tr("inst"), ((QSpinBox*)(AttrTable->cellWidget(1,1)))->text());
//        qNewElement.setAttribute(tr("lnType"), ((QComboBox*)(AttrTable->cellWidget(2,1)))->currentText());
//        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("prefix"), AttrTable->item(3,1)->text());
//        if(AttrTable->item(4,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("desc"), AttrTable->item(4,1)->text());

//        currentNode.appendChild(qNewElement);
//DomItem newItem = DomItem(qNewElement, 0, 0);
//	currentItem->insertChildren(currentItem->childNum(), newItem);
//// 	currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);

//    }
}

void MainWindow::addAuthentication(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - Authentication"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(5,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("none")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("password")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(2,0,new QTableWidgetItem(tr("weak")));
//    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(3,0,new QTableWidgetItem(tr("strong")));
//    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(4,0,new QTableWidgetItem(tr("certificate")));
//    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(4,0)->setCheckState(Qt::Unchecked);

//    AttrTable->setCellWidget(0,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(0,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
//    ((QComboBox*)(AttrTable->cellWidget(0,1)))->setCurrentIndex(0);
//    AttrTable->setCellWidget(1,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(1,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
//    ((QComboBox*)(AttrTable->cellWidget(1,1)))->setCurrentIndex(1);
//    AttrTable->setCellWidget(2,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(2,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
//    ((QComboBox*)(AttrTable->cellWidget(2,1)))->setCurrentIndex(1);
//    AttrTable->setCellWidget(3,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(3,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
//    ((QComboBox*)(AttrTable->cellWidget(3,1)))->setCurrentIndex(1);
//    AttrTable->setCellWidget(4,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(4,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
//    ((QComboBox*)(AttrTable->cellWidget(4,1)))->setCurrentIndex(1);

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    if(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("Authentication"));

//        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("none"), ((QComboBox*)(AttrTable->cellWidget(0,1)))->currentText());
//        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("password"), ((QComboBox*)(AttrTable->cellWidget(1,1)))->currentText());
//        if(AttrTable->item(2,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("weak"), ((QComboBox*)(AttrTable->cellWidget(2,1)))->currentText());
//        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("strong"), ((QComboBox*)(AttrTable->cellWidget(3,1)))->currentText());
//        if(AttrTable->item(4,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("certificate"), ((QComboBox*)(AttrTable->cellWidget(4,1)))->currentText());

//        currentNode.appendChild(qNewElement);
//DomItem newItem = DomItem(qNewElement, 0, 0);
//	currentItem->insertChildren(currentItem->childNum(), newItem);
//// 	currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//    }
}

void MainWindow::addLDevice(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - LDevice"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(2,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)inst")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));

//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("desc")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));

//    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(1,1,new QTableWidgetItem(tr("")));

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    while(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("LDevice"));

//        if(AttrTable->item(0,1)->text()==tr(""))
//        {
//            QMessageBox::warning(NULL,tr("警告"),tr("inst项为必需项，不能为空!"));
//            continue;
//        }

//        qNewElement.setAttribute(tr("inst"), AttrTable->item(0,1)->text());
//        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("desc"), AttrTable->item(1,1)->text());

//        currentNode.appendChild(qNewElement);
//DomItem newItem = DomItem(qNewElement, 0, 0);
//	currentItem->insertChildren(currentItem->childNum(), newItem);
//// 	currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//        break;
//    }
}

void MainWindow::addAssociation(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - Association"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(7,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)kind")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("associationID")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(2,0,new QTableWidgetItem(tr("(*)lnInst")));
//    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(3,0,new QTableWidgetItem(tr("(*)lnClass")));
//    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(4,0,new QTableWidgetItem(tr("prefix")));
//    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(4,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(5,0,new QTableWidgetItem(tr("(*)iedName")));
//    AttrTable->item(5,0)->setFlags(AttrTable->item(5,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(6,0,new QTableWidgetItem(tr("(*)ldInst")));
//    AttrTable->item(6,0)->setFlags(AttrTable->item(6,0)->flags() & (~Qt::ItemIsEditable));

//    AttrTable->setCellWidget(0,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(0,1)))->addItems(QStringList()<<tr("pre-established")<<tr("predefined"));
//    AttrTable->setItem(1,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(2,1,new QTableWidgetItem(tr("")));
//    AttrTable->setCellWidget(3,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(3,1)))->addItems(lnClass);
//    AttrTable->setItem(4,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(5,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(6,1,new QTableWidgetItem(tr("")));

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    while(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("Association"));

//        if(AttrTable->item(2,1)->text()==tr(""))
//        {
//            QMessageBox::warning(NULL,tr("警告"),tr("lnInst项为必需项，不能为空!"));
//            continue;
//        }
//        if(AttrTable->item(5,1)->text()==tr(""))
//        {
//            QMessageBox::warning(NULL,tr("警告"),tr("iedName项为必需项，不能为空!"));
//            continue;
//        }
//        if(AttrTable->item(6,1)->text()==tr(""))
//        {
//            QMessageBox::warning(NULL,tr("警告"),tr("ldInst项为必需项，不能为空!"));
//            continue;
//        }

//        qNewElement.setAttribute(tr("kind"), ((QComboBox*)(AttrTable->cellWidget(0,1)))->currentText());
//        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("associationID"), AttrTable->item(1,1)->text());
//        qNewElement.setAttribute(tr("lnInst"), AttrTable->item(2,1)->text());
//        qNewElement.setAttribute(tr("lnClss"), ((QComboBox*)(AttrTable->cellWidget(3,1)))->currentText());
//        if(AttrTable->item(4,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("prefix"), AttrTable->item(4,1)->text());
//        qNewElement.setAttribute(tr("iedName"), AttrTable->item(5,1)->text());
//        qNewElement.setAttribute(tr("ldInst"), AttrTable->item(6,1)->text());

//        currentNode.appendChild(qNewElement);
//DomItem newItem = DomItem(qNewElement, 0, 0);
//	currentItem->insertChildren(currentItem->childNum(), newItem);
//// 	currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//        break;
//    }
}

void MainWindow::addLN0(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - LN0"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(4,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)lnClass")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("(*)inst")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(2,0,new QTableWidgetItem(tr("(*)lnType")));
//    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(3,0,new QTableWidgetItem(tr("desc")));
//    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);

//    AttrTable->setItem(0,1,new QTableWidgetItem(tr("LLN0")));
//    AttrTable->item(0,1)->setFlags(AttrTable->item(0,1)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setCellWidget(1,1,new QSpinBox(this));
//    AttrTable->setCellWidget(2,1,new QComboBox(this));
//    AttrTable->setItem(3,1,new QTableWidgetItem(tr("")));

//    QDomNode SCLNode;
//    if(currentNode.parentNode().parentNode().parentNode().toElement().tagName() == tr("IED"))
//    {
//        SCLNode = currentNode.parentNode().parentNode().parentNode().parentNode();
//    }
//    else if(currentNode.parentNode().parentNode().toElement().tagName() == tr("IED"))
//        SCLNode = currentNode.parentNode().parentNode().parentNode();

//    //if(IEDNode.nextSiblingElement("DataTypeTemplates"))

//    QDomNode TypeNode;
//    for(int i=0; i<SCLNode.childNodes().count(); i++)
//    {
//        if(SCLNode.childNodes().at(i).toElement().tagName() == tr("DataTypeTemplates"))
//        {
//            TypeNode = SCLNode.childNodes().at(i);
//            qDebug()<<TypeNode.toElement().tagName();
//            for(int i=0; i<TypeNode.childNodes().count(); i++)
//            {
//                if(TypeNode.childNodes().at(i).toElement().tagName() == tr("LNodeType"))
//                {
//                    QStringList lnType;
//                    QDomNode LNodeTypeNode = TypeNode.childNodes().at(i);

//                    qDebug()<<LNodeTypeNode.toElement().tagName();
//                    if(LNodeTypeNode.attributes().contains(tr("id")))
//                    {
//                        qDebug()<<LNodeTypeNode.attributes().namedItem("id").toAttr().value();
//                        lnType.append(LNodeTypeNode.attributes().namedItem("id").toAttr().value());
//                    }
//                    ((QComboBox*)(AttrTable->cellWidget(2,1)))->addItems(lnType);
//                }
//            }
//        }
//    }

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    if(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("LN0"));

//        qNewElement.setAttribute(tr("lnClass"), AttrTable->item(0,1)->text());
//        qNewElement.setAttribute(tr("inst"), ((QSpinBox*)(AttrTable->cellWidget(1,1)))->text());
//        qNewElement.setAttribute(tr("lnType"), ((QComboBox*)(AttrTable->cellWidget(2,1)))->currentText());
//        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("desc"), AttrTable->item(3,1)->text());

//        currentNode.appendChild(qNewElement);
//DomItem newItem = DomItem(qNewElement, 0, 0);
//	currentItem->insertChildren(currentItem->childNum(), newItem);
//// 	currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//    }
}

void MainWindow::addAccessControl(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();
//    qDebug()<<currentNode.toElement().tagName();

//    QDomElement qNewElement = doc->createElement(tr("AccessControl"));
//    currentNode.appendChild(qNewElement);
//DomItem newItem = DomItem(qNewElement, 0, 0);
//	currentItem->insertChildren(currentItem->childNum(), newItem);
//// 	currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//    QModelIndex parentIndex = currentIndex.parent();
//    view->setExpanded(parentIndex,0);
//    view->setExpanded(parentIndex,1);
//    view->setExpanded(currentIndex,1);
}

void MainWindow::addGSEControl(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - GSEControl"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(6,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("type")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("(*)appID")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(2,0,new QTableWidgetItem(tr("confRev")));
//    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(3,0,new QTableWidgetItem(tr("(*)datSet")));
//    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(4,0,new QTableWidgetItem(tr("(*)name")));
//    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(5,0,new QTableWidgetItem(tr("desc")));
//    AttrTable->item(5,0)->setFlags(AttrTable->item(5,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(5,0)->setCheckState(Qt::Unchecked);

//    AttrTable->setCellWidget(0,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(0,1)))->addItems(QStringList()<<tr("GSSE")<<tr("GOOSE"));
//    AttrTable->setItem(1,1,new QTableWidgetItem(tr("")));
//    AttrTable->setCellWidget(2,1,new QSpinBox(this));
//    AttrTable->setCellWidget(3,1,new QComboBox(this));
//    AttrTable->setItem(4,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(5,1,new QTableWidgetItem(tr("")));

//    QStringList DatSet;
//    for(int i=0; i<currentNode.childNodes().count(); i++)
//    {
//        if(currentNode.childNodes().at(i).toElement().tagName() == tr("DataSet"))
//        {
//            QDomNode DataSetNode = currentNode.childNodes().at(i);

//            if(DataSetNode.attributes().contains(tr("name")))
//                DatSet.append(DataSetNode.attributes().namedItem("name").toAttr().value());
//        }
//    }
//    if(DatSet.isEmpty())
//        DatSet.append(tr(""));
//    ((QComboBox*)(AttrTable->cellWidget(3,1)))->addItems(DatSet);

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    while(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("GSEControl"));

//        if(AttrTable->item(1,1)->text()==tr(""))
//        {
//            QMessageBox::warning(NULL,tr("警告"),tr("appID项为必需项，不能为空!"));
//            continue;
//        }

//        if(AttrTable->item(4,1)->text()==tr(""))
//        {
//            QMessageBox::warning(NULL,tr("警告"),tr("name项为必需项，不能为空!"));
//            continue;
//        }

//        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("type"), ((QComboBox*)(AttrTable->cellWidget(0,1)))->currentText());
//        qNewElement.setAttribute(tr("appID"), AttrTable->item(1,1)->text());
//        if(AttrTable->item(2,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("confRev"), ((QSpinBox*)(AttrTable->cellWidget(2,1)))->text());
//        qNewElement.setAttribute(tr("datSet"), ((QComboBox*)(AttrTable->cellWidget(3,1)))->currentText());
//        qNewElement.setAttribute(tr("name"), AttrTable->item(4,1)->text());
//        if(AttrTable->item(5,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("desc"), AttrTable->item(5,1)->text());

//        currentNode.appendChild(qNewElement);
//DomItem newItem = DomItem(qNewElement, 0, 0);
//	currentItem->insertChildren(currentItem->childNum(), newItem);
//// 	currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//        break;
//    }
}

void MainWindow::addSampleValueControl(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - SampleValueControl"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(8,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)smvID")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("multicast")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(2,0,new QTableWidgetItem(tr("(*)smpRate")));
//    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(3,0,new QTableWidgetItem(tr("(*)nofASDU")));
//    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(4,0,new QTableWidgetItem(tr("confRev")));
//    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(4,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(5,0,new QTableWidgetItem(tr("(*)datSet")));
//    AttrTable->item(5,0)->setFlags(AttrTable->item(5,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(6,0,new QTableWidgetItem(tr("(*)name")));
//    AttrTable->item(6,0)->setFlags(AttrTable->item(6,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(7,0,new QTableWidgetItem(tr("desc")));
//    AttrTable->item(7,0)->setFlags(AttrTable->item(7,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(7,0)->setCheckState(Qt::Unchecked);

//    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
//    AttrTable->setCellWidget(1,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(1,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
//    AttrTable->setCellWidget(2,1,new QSpinBox(this));
//    AttrTable->setCellWidget(3,1,new QSpinBox(this));
//    AttrTable->setCellWidget(4,1,new QSpinBox(this));
//    AttrTable->setCellWidget(5,1,new QComboBox(this));
//    AttrTable->setItem(6,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(7,1,new QTableWidgetItem(tr("")));

//    QStringList DatSet;
//    for(int i=0; i<currentNode.childNodes().count(); i++)
//    {
//        if(currentNode.childNodes().at(i).toElement().tagName() == tr("DataSet"))
//        {
//            QDomNode DataSetNode = currentNode.childNodes().at(i);

//            if(DataSetNode.attributes().contains(tr("name")))
//                DatSet.append(DataSetNode.attributes().namedItem("name").toAttr().value());
//        }
//    }
//    if(DatSet.isEmpty())
//        DatSet.append(tr(" "));
//    ((QComboBox*)(AttrTable->cellWidget(5,1)))->addItems(DatSet);

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    while(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("SampleValueControl"));

//        if(AttrTable->item(0,1)->text()==tr(""))
//        {
//            QMessageBox::warning(NULL,tr("警告"),tr("smvID项为必需项，不能为空!"));
//            continue;
//        }

//        if(AttrTable->item(6,1)->text()==tr(""))
//        {
//            QMessageBox::warning(NULL,tr("警告"),tr("name项为必需项，不能为空!"));
//            continue;
//        }


//        qNewElement.setAttribute(tr("smvID"), AttrTable->item(0,1)->text());
//        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("multicast"), ((QComboBox*)(AttrTable->cellWidget(1,1)))->currentText());
//        qNewElement.setAttribute(tr("smpRate"), ((QSpinBox*)(AttrTable->cellWidget(2,1)))->text());
//        qNewElement.setAttribute(tr("nofASDU"), ((QSpinBox*)(AttrTable->cellWidget(3,1)))->text());
//        if(AttrTable->item(4,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("confRev"), ((QSpinBox*)(AttrTable->cellWidget(4,1)))->text());
//        qNewElement.setAttribute(tr("datSet"), ((QComboBox*)(AttrTable->cellWidget(5,1)))->currentText());
//        qNewElement.setAttribute(tr("name"), AttrTable->item(6,1)->text());
//        if(AttrTable->item(7,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("desc"), AttrTable->item(7,1)->text());

//        currentNode.appendChild(qNewElement);
//DomItem newItem = DomItem(qNewElement, 0, 0);
//	currentItem->insertChildren(currentItem->childNum(), newItem);
//// 	currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//        break;
//    }
}

void MainWindow::addSettingControl(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - SettingControl"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(3,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)numOfSGs")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("actSG")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(2,0,new QTableWidgetItem(tr("desc")));
//    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);

//    AttrTable->setCellWidget(0,1,new QSpinBox(this));
//    AttrTable->setCellWidget(1,1,new QSpinBox(this));
//    ((QSpinBox*)(AttrTable->cellWidget(1,1)))->setValue(1);
//    AttrTable->setItem(2,1,new QTableWidgetItem(tr("")));

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    if(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("SettingControl"));

//        qNewElement.setAttribute(tr("numOfSGs"), ((QSpinBox*)(AttrTable->cellWidget(0,1)))->text());
//        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("actSG"), ((QSpinBox*)(AttrTable->cellWidget(1,1)))->text());
//        if(AttrTable->item(2,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("desc"), AttrTable->item(2,1)->text());

//        currentNode.appendChild(qNewElement);
//DomItem newItem = DomItem(qNewElement, 0, 0);
//	currentItem->insertChildren(currentItem->childNum(), newItem);
//// 	currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);

//    }
}

void MainWindow::addSCLControl(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - SettingControl"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(1,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("desc")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);

//    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    if(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("SettingControl"));

//        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("desc"), AttrTable->item(0,1)->text());

//        currentNode.appendChild(qNewElement);
//DomItem newItem = DomItem(qNewElement, 0, 0);
//	currentItem->insertChildren(currentItem->childNum(), newItem);
//// 	currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//    }
}

void MainWindow::addLog(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();
//    qDebug()<<currentNode.toElement().tagName();

//    QDomElement qNewElement = doc->createElement(tr("Log"));
//    currentNode.appendChild(qNewElement);
//DomItem newItem = DomItem(qNewElement, 0, 0);
//	currentItem->insertChildren(currentItem->childNum(), newItem);
//// 	currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//    QModelIndex parentIndex = currentIndex.parent();
//    view->setExpanded(parentIndex,0);
//    view->setExpanded(parentIndex,1);
//    view->setExpanded(currentIndex,1);

}

void MainWindow::addDataSet(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - DataSet"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(2,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)name")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("desc")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);

//    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(1,1,new QTableWidgetItem(tr("")));

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    while(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("DataSet"));

//        if(AttrTable->item(0,1)->text()==tr(""))
//        {
//            QMessageBox::warning(NULL,tr("警告"),tr("name项为必需项，不能为空!"));
//            continue;
//        }

//        qNewElement.setAttribute(tr("name"), AttrTable->item(0,1)->text());
//        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("desc"), AttrTable->item(1,1)->text());

//        currentNode.appendChild(qNewElement);
//DomItem newItem = DomItem(qNewElement, 0, 0);
//	currentItem->insertChildren(currentItem->childNum(), newItem);
//// 	currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);

//        break;
//    }
}

void MainWindow::addReportControl(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - ReportControl"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(8,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)rptID")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("(*)confRev")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(2,0,new QTableWidgetItem(tr("buffered")));
//    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(3,0,new QTableWidgetItem(tr("bufTime")));
//    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(4,0,new QTableWidgetItem(tr("intgPd")));
//    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(4,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(5,0,new QTableWidgetItem(tr("(*)datSet")));
//    AttrTable->item(5,0)->setFlags(AttrTable->item(5,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(6,0,new QTableWidgetItem(tr("(*)name")));
//    AttrTable->item(6,0)->setFlags(AttrTable->item(6,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(7,0,new QTableWidgetItem(tr("desc")));
//    AttrTable->item(7,0)->setFlags(AttrTable->item(7,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(7,0)->setCheckState(Qt::Unchecked);

//    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
//    AttrTable->setCellWidget(1,1,new QSpinBox(this));
//    AttrTable->setCellWidget(2,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(2,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
//    ((QComboBox*)(AttrTable->cellWidget(2,1)))->setCurrentIndex(1);
//    AttrTable->setCellWidget(3,1,new QSpinBox(this));
//    AttrTable->setCellWidget(4,1,new QSpinBox(this));
//    AttrTable->setCellWidget(5,1,new QComboBox(this));
//    AttrTable->setItem(6,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(7,1,new QTableWidgetItem(tr("")));

//    QStringList DatSet;
//    for(int i=0; i<currentNode.childNodes().count(); i++)
//    {
//        if(currentNode.childNodes().at(i).toElement().tagName() == tr("DataSet"))
//        {
//            QDomNode DataSetNode = currentNode.childNodes().at(i);

//            if(DataSetNode.attributes().contains(tr("name")))
//                DatSet.append(DataSetNode.attributes().namedItem("name").toAttr().value());
//        }
//    }
//    if(DatSet.isEmpty())
//        DatSet.append(tr(" "));
//    ((QComboBox*)(AttrTable->cellWidget(5,1)))->addItems(DatSet);

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    while(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("ReportControl"));

//        if(AttrTable->item(0,1)->text()==tr(""))
//        {
//            QMessageBox::warning(NULL,tr("警告"),tr("rptID项为必需项，不能为空!"));
//            continue;
//        }

//        if(AttrTable->item(6,1)->text()==tr(""))
//        {
//            QMessageBox::warning(NULL,tr("警告"),tr("name项为必需项，不能为空!"));
//            continue;
//        }

//        qNewElement.setAttribute(tr("rptID"), AttrTable->item(0,1)->text());
//        qNewElement.setAttribute(tr("confRev"), ((QSpinBox*)(AttrTable->cellWidget(1,1)))->text());
//        if(AttrTable->item(2,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("buffered"), ((QSpinBox*)(AttrTable->cellWidget(2,1)))->text());
//        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("bufTime"), ((QSpinBox*)(AttrTable->cellWidget(3,1)))->text());
//        if(AttrTable->item(4,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("intgPd"), ((QSpinBox*)(AttrTable->cellWidget(4,1)))->text());
//        qNewElement.setAttribute(tr("datSet"), ((QComboBox*)(AttrTable->cellWidget(5,1)))->currentText());
//        qNewElement.setAttribute(tr("name"), AttrTable->item(6,1)->text());
//        if(AttrTable->item(7,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("desc"), AttrTable->item(7,1)->text());

//        currentNode.appendChild(qNewElement);
//DomItem newItem = DomItem(qNewElement, 0, 0);
//	currentItem->insertChildren(currentItem->childNum(), newItem);
//// 	currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//        break;
//    }
}

void MainWindow::addLogControl(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - LogControl"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(7,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)logName")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("logEna")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(2,0,new QTableWidgetItem(tr("reasonCode")));
//    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(3,0,new QTableWidgetItem(tr("intgPd")));
//    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(4,0,new QTableWidgetItem(tr("(*)datSet")));
//    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(5,0,new QTableWidgetItem(tr("(*)name")));
//    AttrTable->item(5,0)->setFlags(AttrTable->item(5,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(6,0,new QTableWidgetItem(tr("desc")));
//    AttrTable->item(6,0)->setFlags(AttrTable->item(6,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(6,0)->setCheckState(Qt::Unchecked);

//    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
//    AttrTable->setCellWidget(1,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(1,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
//    AttrTable->setCellWidget(2,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(2,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
//    AttrTable->setCellWidget(3,1,new QSpinBox(this));
//    AttrTable->setCellWidget(4,1,new QComboBox(this));
//    AttrTable->setItem(5,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(6,1,new QTableWidgetItem(tr("")));

//    QStringList DatSet;
//    for(int i=0; i<currentNode.childNodes().count(); i++)
//    {
//        if(currentNode.childNodes().at(i).toElement().tagName() == tr("DataSet"))
//        {
//            QDomNode DataSetNode = currentNode.childNodes().at(i);

//            if(DataSetNode.attributes().contains(tr("name")))
//                DatSet.append(DataSetNode.attributes().namedItem("name").toAttr().value());
//        }
//    }
//    if(DatSet.isEmpty())
//        DatSet.append(tr(""));
//    ((QComboBox*)(AttrTable->cellWidget(4,1)))->addItems(DatSet);

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    while(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("LogControl"));

//        if(AttrTable->item(0,1)->text()==tr(""))
//        {
//            QMessageBox::warning(NULL,tr("警告"),tr("logName项为必需项，不能为空!"));
//            continue;
//        }

//        if(AttrTable->item(5,1)->text()==tr(""))
//        {
//            QMessageBox::warning(NULL,tr("警告"),tr("name项为必需项，不能为空!"));
//            continue;
//        }

//        qNewElement.setAttribute(tr("logName"), AttrTable->item(0,1)->text());
//        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("logEna"), ((QComboBox*)(AttrTable->cellWidget(1,1)))->currentText());
//        if(AttrTable->item(2,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("reasonCode"), ((QComboBox*)(AttrTable->cellWidget(2,1)))->currentText());
//        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("intgPd"), ((QSpinBox*)(AttrTable->cellWidget(3,1)))->text());
//        qNewElement.setAttribute(tr("datSet"), ((QComboBox*)(AttrTable->cellWidget(4,1)))->currentText());
//        qNewElement.setAttribute(tr("name"), AttrTable->item(5,1)->text());
//        if(AttrTable->item(6,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("desc"), AttrTable->item(6,1)->text());

//        currentNode.appendChild(qNewElement);
//DomItem newItem = DomItem(qNewElement, 0, 0);
//	currentItem->insertChildren(currentItem->childNum(), newItem);
//// 	currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//        break;
//    }
}

void MainWindow::addDOI(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - DOI"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(4,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)name")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("ix")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(2,0,new QTableWidgetItem(tr("accessControl")));
//    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(3,0,new QTableWidgetItem(tr("desc")));
//    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);

//    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
//    AttrTable->setCellWidget(1,1,new QSpinBox(this));
//    AttrTable->setItem(2,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(3,1,new QTableWidgetItem(tr("")));

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    while(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("DOI"));

//        if(AttrTable->item(0,1)->text()==tr(""))
//        {
//            QMessageBox::warning(NULL,tr("警告"),tr("name项为必需项，不能为空!"));
//            continue;
//        }

//        qNewElement.setAttribute(tr("name"), AttrTable->item(0,1)->text());
//        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("ix"), ((QSpinBox*)(AttrTable->cellWidget(1,1)))->text());
//        if(AttrTable->item(2,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("accessControl"), AttrTable->item(2,1)->text());
//        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("desc"), AttrTable->item(3,1)->text());

//        currentNode.appendChild(qNewElement);
//DomItem newItem = DomItem(qNewElement, 0, 0);
//	currentItem->insertChildren(currentItem->childNum(), newItem);
//// 	currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//        break;
//    }
}

void MainWindow::addInputs(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - Inputs"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(1,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("desc")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);

//    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    if(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("Inputs"));

//        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("desc"), AttrTable->item(0,1)->text());

//        currentNode.appendChild(qNewElement);
//DomItem newItem = DomItem(qNewElement, 0, 0);
//	currentItem->insertChildren(currentItem->childNum(), newItem);
//// 	currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//    }
}

void MainWindow::addIEDName(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();
//    qDebug()<<currentNode.toElement().tagName();

//    QDomElement qNewElement = doc->createElement(tr("IEDName"));
//    currentNode.appendChild(qNewElement);
//DomItem newItem = DomItem(qNewElement, 0, 0);
//	currentItem->insertChildren(currentItem->childNum(), newItem);
//// 	currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//    QModelIndex parentIndex = currentIndex.parent();
//    view->setExpanded(parentIndex,0);
//    view->setExpanded(parentIndex,1);
//    view->setExpanded(currentIndex,1);
}

void MainWindow::addSmvOpts(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - SmvOpts"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(5,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("refreshTime")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("sampleSynchronized")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(2,0,new QTableWidgetItem(tr("sampleRate")));
//    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(3,0,new QTableWidgetItem(tr("security")));
//    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(4,0,new QTableWidgetItem(tr("dataRef")));
//    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(4,0)->setCheckState(Qt::Unchecked);

//    AttrTable->setCellWidget(0,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(0,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
//    ((QComboBox*)(AttrTable->cellWidget(0,1)))->setCurrentIndex(1);
//    AttrTable->setCellWidget(1,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(1,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
//    ((QComboBox*)(AttrTable->cellWidget(1,1)))->setCurrentIndex(1);
//    AttrTable->setCellWidget(2,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(2,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
//    ((QComboBox*)(AttrTable->cellWidget(2,1)))->setCurrentIndex(1);
//    AttrTable->setCellWidget(3,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(3,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
//    ((QComboBox*)(AttrTable->cellWidget(3,1)))->setCurrentIndex(1);
//    AttrTable->setCellWidget(4,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(4,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
//    ((QComboBox*)(AttrTable->cellWidget(4,1)))->setCurrentIndex(1);

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    if(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("SmvOpts"));

//        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("refreshTime"), ((QComboBox*)(AttrTable->cellWidget(0,1)))->currentText());
//        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("sampleSynchronized"), ((QComboBox*)(AttrTable->cellWidget(1,1)))->currentText());
//        if(AttrTable->item(2,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("sampleRate"), ((QComboBox*)(AttrTable->cellWidget(2,1)))->currentText());
//        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("security"), ((QComboBox*)(AttrTable->cellWidget(3,1)))->currentText());
//        if(AttrTable->item(4,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("dataRef"), ((QComboBox*)(AttrTable->cellWidget(4,1)))->currentText());

//        currentNode.appendChild(qNewElement);
//DomItem newItem = DomItem(qNewElement, 0, 0);
//	currentItem->insertChildren(currentItem->childNum(), newItem);
//// 	currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//    }
}

void MainWindow::addFCDA(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - FCDA"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(7,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("ldInst")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("prefix")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(2,0,new QTableWidgetItem(tr("lnClass")));
//    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(3,0,new QTableWidgetItem(tr("lnInst")));
//    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(4,0,new QTableWidgetItem(tr("doName")));
//    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(4,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(5,0,new QTableWidgetItem(tr("daName")));
//    AttrTable->item(5,0)->setFlags(AttrTable->item(5,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(5,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(6,0,new QTableWidgetItem(tr("fc")));
//    AttrTable->item(6,0)->setFlags(AttrTable->item(6,0)->flags() & (~Qt::ItemIsEditable));

//    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(1,1,new QTableWidgetItem(tr("")));
//    AttrTable->setCellWidget(2,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(2,1)))->addItems(lnClass);
//    AttrTable->setItem(3,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(4,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(5,1,new QTableWidgetItem(tr("")));
//    AttrTable->setCellWidget(6,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(6,1)))->addItems(fcEnum);

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    if(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("FCDA"));

//        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("ldInst"), AttrTable->item(0,1)->text());
//        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("prefix"), AttrTable->item(1,1)->text());
//        if(AttrTable->item(2,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("lnClass"), ((QComboBox*)(AttrTable->cellWidget(2,1)))->currentText());
//        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("lnInst"), AttrTable->item(3,1)->text());
//        if(AttrTable->item(4,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("doName"), AttrTable->item(4,1)->text());
//        if(AttrTable->item(5,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("daName"), AttrTable->item(5,1)->text());
//        qNewElement.setAttribute(tr("fc"), ((QComboBox*)(AttrTable->cellWidget(6,1)))->currentText());

//        currentNode.appendChild(qNewElement);
//DomItem newItem = DomItem(qNewElement, 0, 0);
//	currentItem->insertChildren(currentItem->childNum(), newItem);
//// 	currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//    }
}

void MainWindow::addOptFields(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - OptFields"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(9,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("seqNum")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("timeStamp")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(2,0,new QTableWidgetItem(tr("dataSet")));
//    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(3,0,new QTableWidgetItem(tr("reasonCode")));
//    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(4,0,new QTableWidgetItem(tr("dataRef")));
//    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(4,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(5,0,new QTableWidgetItem(tr("bufOvfl")));
//    AttrTable->item(5,0)->setFlags(AttrTable->item(5,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(5,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(6,0,new QTableWidgetItem(tr("entryID")));
//    AttrTable->item(6,0)->setFlags(AttrTable->item(6,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(6,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(7,0,new QTableWidgetItem(tr("configRef")));
//    AttrTable->item(7,0)->setFlags(AttrTable->item(7,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(7,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(8,0,new QTableWidgetItem(tr("segmentation")));
//    AttrTable->item(8,0)->setFlags(AttrTable->item(8,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(8,0)->setCheckState(Qt::Unchecked);

//    AttrTable->setCellWidget(0,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(0,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
//    ((QComboBox*)(AttrTable->cellWidget(0,1)))->setCurrentIndex(1);
//    AttrTable->setCellWidget(1,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(1,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
//    ((QComboBox*)(AttrTable->cellWidget(1,1)))->setCurrentIndex(1);
//    AttrTable->setCellWidget(2,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(2,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
//    ((QComboBox*)(AttrTable->cellWidget(2,1)))->setCurrentIndex(1);
//    AttrTable->setCellWidget(3,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(3,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
//    ((QComboBox*)(AttrTable->cellWidget(3,1)))->setCurrentIndex(1);
//    AttrTable->setCellWidget(4,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(4,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
//    ((QComboBox*)(AttrTable->cellWidget(4,1)))->setCurrentIndex(1);
//    AttrTable->setCellWidget(5,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(5,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
//    ((QComboBox*)(AttrTable->cellWidget(5,1)))->setCurrentIndex(1);
//    AttrTable->setCellWidget(6,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(6,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
//    ((QComboBox*)(AttrTable->cellWidget(6,1)))->setCurrentIndex(1);
//    AttrTable->setCellWidget(7,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(7,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
//    ((QComboBox*)(AttrTable->cellWidget(7,1)))->setCurrentIndex(1);
//    AttrTable->setCellWidget(8,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(8,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
//    ((QComboBox*)(AttrTable->cellWidget(8,1)))->setCurrentIndex(1);


//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    if(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("OptFields"));

//        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("refreshTime"), ((QComboBox*)(AttrTable->cellWidget(0,1)))->currentText());
//        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("sampleSynchronized"), ((QComboBox*)(AttrTable->cellWidget(1,1)))->currentText());
//        if(AttrTable->item(2,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("sampleRate"), ((QComboBox*)(AttrTable->cellWidget(2,1)))->currentText());
//        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("security"), ((QComboBox*)(AttrTable->cellWidget(3,1)))->currentText());
//        if(AttrTable->item(4,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("dataRef"), ((QComboBox*)(AttrTable->cellWidget(4,1)))->currentText());
//        if(AttrTable->item(5,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("bufOvfl"), ((QComboBox*)(AttrTable->cellWidget(5,1)))->currentText());
//        if(AttrTable->item(6,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("entryID"), ((QComboBox*)(AttrTable->cellWidget(6,1)))->currentText());
//        if(AttrTable->item(7,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("configRef"), ((QComboBox*)(AttrTable->cellWidget(7,1)))->currentText());
//        if(AttrTable->item(8,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("segmentation"), ((QComboBox*)(AttrTable->cellWidget(8,1)))->currentText());

//        currentNode.appendChild(qNewElement);
//DomItem newItem = DomItem(qNewElement, 0, 0);
//	currentItem->insertChildren(currentItem->childNum(), newItem);
//// 	currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//    }
}

void MainWindow::addRptEnabled(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - RptEnabled"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(2,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("max")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("desc")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);

//    AttrTable->setCellWidget(0,1,new QSpinBox(this));
//    ((QSpinBox*)(AttrTable->cellWidget(0,1)))->setValue(1);
//    AttrTable->setItem(1,1,new QTableWidgetItem(tr("")));

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    if(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("RptEnabled"));

//        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("max"), ((QSpinBox*)(AttrTable->cellWidget(0,1)))->text());
//        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("desc"), AttrTable->item(1,1)->text());

//        currentNode.appendChild(qNewElement);
//DomItem newItem = DomItem(qNewElement, 0, 0);
//	currentItem->insertChildren(currentItem->childNum(), newItem);
//// 	currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//    }
}

void MainWindow::addTrgOps(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - TrgOps"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(4,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("dchg")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("qchg")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(2,0,new QTableWidgetItem(tr("dupd")));
//    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(3,0,new QTableWidgetItem(tr("period")));
//    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);

//    AttrTable->setCellWidget(0,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(0,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
//    ((QComboBox*)(AttrTable->cellWidget(0,1)))->setCurrentIndex(1);
//    AttrTable->setCellWidget(1,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(1,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
//    ((QComboBox*)(AttrTable->cellWidget(1,1)))->setCurrentIndex(1);
//    AttrTable->setCellWidget(2,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(2,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
//    ((QComboBox*)(AttrTable->cellWidget(2,1)))->setCurrentIndex(1);
//    AttrTable->setCellWidget(3,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(3,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
//    ((QComboBox*)(AttrTable->cellWidget(3,1)))->setCurrentIndex(1);

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    if(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("TrgOps"));

//        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("dchg"), ((QComboBox*)(AttrTable->cellWidget(0,1)))->currentText());
//        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("qchg"), ((QComboBox*)(AttrTable->cellWidget(1,1)))->currentText());
//        if(AttrTable->item(2,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("dupd"), ((QComboBox*)(AttrTable->cellWidget(2,1)))->currentText());
//        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("period"), ((QComboBox*)(AttrTable->cellWidget(3,1)))->currentText());

//        currentNode.appendChild(qNewElement);
//DomItem newItem = DomItem(qNewElement, 0, 0);
//	currentItem->insertChildren(currentItem->childNum(), newItem);
//// 	currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//    }
}

void MainWindow::addClientLN(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - ClientLN"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(5,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("prefix")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("(*)lnClass")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(2,0,new QTableWidgetItem(tr("(*)lnInst")));
//    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(3,0,new QTableWidgetItem(tr("(*)iedName")));
//    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(4,0,new QTableWidgetItem(tr("(*)ldInst")));
//    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));

//    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
//    AttrTable->setCellWidget(1,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(1,1)))->addItems(lnClass);
//    AttrTable->setItem(2,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(3,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(4,1,new QTableWidgetItem(tr("")));

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    while(AttrDlg->exec() == QDialog::Accepted)
//    {
//        if(AttrTable->item(2,1)->text()==tr(""))
//        {
//            QMessageBox::warning(NULL,tr("警告"),tr("lnInst项为必需项，不能为空!"));
//            continue;
//        }
//        if(AttrTable->item(3,1)->text()==tr(""))
//        {
//            QMessageBox::warning(NULL,tr("警告"),tr("iedName项为必需项，不能为空!"));
//            continue;
//        }
//        if(AttrTable->item(4,1)->text()==tr(""))
//        {
//            QMessageBox::warning(NULL,tr("警告"),tr("ldInst项为必需项，不能为空!"));
//            continue;
//        }

//        QDomElement qNewElement = doc->createElement(tr("ClientLN"));

//        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("prefix"), AttrTable->item(0,1)->text());
//        qNewElement.setAttribute(tr("lnClass"), ((QComboBox*)(AttrTable->cellWidget(1,1)))->currentText());
//        qNewElement.setAttribute(tr("lnInst"), AttrTable->item(2,1)->text());
//        qNewElement.setAttribute(tr("iedName"), AttrTable->item(3,1)->text());
//        qNewElement.setAttribute(tr("ldInst"), AttrTable->item(4,1)->text());

//        currentNode.appendChild(qNewElement);
//DomItem newItem = DomItem(qNewElement, 0, 0);
//	currentItem->insertChildren(currentItem->childNum(), newItem);
//// 	currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//        break;
//    }
}

void MainWindow::addSDI(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - SDI"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(3,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("name")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("ix")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(2,0,new QTableWidgetItem(tr("desc")));
//    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);

//    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
//    AttrTable->setCellWidget(1,1,new QSpinBox(this));
//    AttrTable->setItem(2,1,new QTableWidgetItem(tr("")));

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    while(AttrDlg->exec() == QDialog::Accepted)
//    {
//        if(AttrTable->item(0,1)->text()==tr(""))
//        {
//            QMessageBox::warning(NULL,tr("警告"),tr("name项为必需项，不能为空!"));
//            continue;
//        }

//        QDomElement qNewElement = doc->createElement(tr("SDI"));

//        qNewElement.setAttribute(tr("name"), AttrTable->item(0,1)->text());
//        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("ix"), ((QSpinBox*)(AttrTable->cellWidget(1,1)))->text());
//        if(AttrTable->item(2,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("desc"), AttrTable->item(2,1)->text());

//        currentNode.appendChild(qNewElement);
//DomItem newItem = DomItem(qNewElement, 0, 0);
//	currentItem->insertChildren(currentItem->childNum(), newItem);
//// 	currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//        break;
//    }
}

void MainWindow::addDAI(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - DAI"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(5,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("name")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("sAddr")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(2,0,new QTableWidgetItem(tr("valKind")));
//    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(3,0,new QTableWidgetItem(tr("ix")));
//    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(4,0,new QTableWidgetItem(tr("desc")));
//    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(4,0)->setCheckState(Qt::Unchecked);

//    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(1,1,new QTableWidgetItem(tr("")));
//    AttrTable->setCellWidget(2,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(2,1)))->addItems(QStringList()<<tr("Spec")<<tr("Conf")<<tr("RO")<<tr("Set"));
//    ((QComboBox*)(AttrTable->cellWidget(2,1)))->setCurrentIndex(3);
//    AttrTable->setCellWidget(3,1,new QSpinBox(this));
//    AttrTable->setItem(4,1,new QTableWidgetItem(tr("")));

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    while(AttrDlg->exec() == QDialog::Accepted)
//    {
//        if(AttrTable->item(0,1)->text()==tr(""))
//        {
//            QMessageBox::warning(NULL,tr("警告"),tr("name项为必需项，不能为空!"));
//            continue;
//        }

//        QDomElement qNewElement = doc->createElement(tr("DAI"));

//        qNewElement.setAttribute(tr("name"), AttrTable->item(0,1)->text());
//        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("sAddr"), AttrTable->item(1,1)->text());
//        if(AttrTable->item(2,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("valKind"), ((QComboBox*)(AttrTable->cellWidget(2,1)))->currentText());
//        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("ix"), ((QSpinBox*)(AttrTable->cellWidget(1,1)))->text());
//        if(AttrTable->item(4,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("desc"), AttrTable->item(2,1)->text());

//        currentNode.appendChild(qNewElement);
//        DomItem newItem = DomItem(qNewElement, 0, 0);
//currentItem->insertChildren(currentItem->childNum(), newItem);
//// currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//        break;
//    }
}

void MainWindow::addVal(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - Val"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(1,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("sGroup")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);

//    AttrTable->setCellWidget(0,1,new QSpinBox(this));

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    if(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("Val"));

//        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("sGroup"), ((QSpinBox*)(AttrTable->cellWidget(0,1)))->text());

//        currentNode.appendChild(qNewElement);
//        DomItem newItem = DomItem(qNewElement, 0, 0);
//	currentItem->insertChildren(currentItem->childNum(), newItem);
//// 	currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        qDebug()<<"Add Item";
//        qDebug()<<currentNode.toElement().tagName();
//        qDebug()<<qNewElement.tagName();
//        qDebug()<<currentIndex.parent().data().toString();
//        model->update();
//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//    }
}

void MainWindow::addValContent(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *ContentDlg = new QDialog(this);
//    ContentDlg->setWindowTitle(tr("Val值输入"));
//    QGridLayout *ContentDlgLayout = new QGridLayout(ContentDlg);
//    QLabel *ContentLabel = new QLabel(tr("请输入Val值："));
//    QLineEdit *ContentEdit = new QLineEdit(this);

//    QPushButton *qContentDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qContentDlgConfirm, SIGNAL(clicked()), ContentDlg, SLOT(accept()));
//    QPushButton *qContentDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qContentDlgCancel, SIGNAL(clicked()), ContentDlg, SLOT(close()));
//    ContentDlgLayout->addWidget(ContentLabel,0,0,1,1);
//    ContentDlgLayout->addWidget(ContentEdit,0,1,1,3);
//    ContentDlgLayout->addWidget(qContentDlgConfirm,2,2);
//    ContentDlgLayout->addWidget(qContentDlgCancel,2,3);

//    if(ContentDlg->exec() == QDialog::Accepted)
//    {
//        QDomText qNewText = doc->createTextNode(ContentEdit->text());

//        currentNode.appendChild(qNewText);
//        DomItem newItem = DomItem(qNewText, 0, 0);
//	currentItem->insertChildren(currentItem->childNum(), newItem);
//// 	currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewText);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//    }
}

void MainWindow::addExtRef(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - ExtRef"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(8,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("daName")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("intAddr")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(2,0,new QTableWidgetItem(tr("(*)doName")));
//    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(3,0,new QTableWidgetItem(tr("prefix")));
//    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(4,0,new QTableWidgetItem(tr("(*)lnClass")));
//    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(5,0,new QTableWidgetItem(tr("(*)lnInst")));
//    AttrTable->item(5,0)->setFlags(AttrTable->item(5,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(6,0,new QTableWidgetItem(tr("(*)iedName")));
//    AttrTable->item(6,0)->setFlags(AttrTable->item(6,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(7,0,new QTableWidgetItem(tr("(*)ldInst")));
//    AttrTable->item(7,0)->setFlags(AttrTable->item(7,0)->flags() & (~Qt::ItemIsEditable));

//    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(1,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(2,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(3,1,new QTableWidgetItem(tr("")));
//    AttrTable->setCellWidget(4,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(4,1)))->addItems(lnClass);
//    AttrTable->setItem(5,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(6,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(7,1,new QTableWidgetItem(tr("")));

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    while(AttrDlg->exec() == QDialog::Accepted)
//    {
//        if(AttrTable->item(2,1)->text()==tr(""))
//        {
//            QMessageBox::warning(NULL,tr("警告"),tr("doName项为必需项，不能为空!"));
//            continue;
//        }
//        if(AttrTable->item(5,1)->text()==tr(""))
//        {
//            QMessageBox::warning(NULL,tr("警告"),tr("lnInst项为必需项，不能为空!"));
//            continue;
//        }
//        if(AttrTable->item(6,1)->text()==tr(""))
//        {
//            QMessageBox::warning(NULL,tr("警告"),tr("iedName项为必需项，不能为空!"));
//            continue;
//        }
//        if(AttrTable->item(7,1)->text()==tr(""))
//        {
//            QMessageBox::warning(NULL,tr("警告"),tr("ldInst项为必需项，不能为空!"));
//            continue;
//        }
//        QDomElement qNewElement = doc->createElement(tr("ExtRef"));

//        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("daName"), AttrTable->item(0,1)->text());
//        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("intAddr"), AttrTable->item(1,1)->text());
//        qNewElement.setAttribute(tr("doName"), AttrTable->item(2,1)->text());
//        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("prefix"), AttrTable->item(3,1)->text());
//        qNewElement.setAttribute(tr("lnClass"), ((QComboBox*)(AttrTable->cellWidget(4,1)))->currentText());
//        qNewElement.setAttribute(tr("lnInst"), AttrTable->item(5,1)->text());
//        qNewElement.setAttribute(tr("iedName"), AttrTable->item(6,1)->text());
//        qNewElement.setAttribute(tr("ldInst"), AttrTable->item(7,1)->text());

//        currentNode.appendChild(qNewElement);
//        DomItem newItem = DomItem(qNewElement, 0, 0);
//        currentItem->insertChildren(currentItem->childNum(), newItem);
////      currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//        break;
//    }
}

void MainWindow::addLNodeType(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - LNodeType"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(4,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("iedType")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("(*)lnClass")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(2,0,new QTableWidgetItem(tr("(*)id")));
//    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(3,0,new QTableWidgetItem(tr("desc")));
//    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);

//    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
//    AttrTable->setCellWidget(1,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(1,1)))->addItems(lnClass);
//    AttrTable->setItem(2,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(3,1,new QTableWidgetItem(tr("")));

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    while(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("LNodeType"));

//        if(AttrTable->item(2,1)->text()==tr(""))
//        {
//            QMessageBox::warning(NULL,tr("警告"),tr("id项为必需项，不能为空!"));
//            continue;
//        }

//        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("iedType"), ((QComboBox*)(AttrTable->cellWidget(0,1)))->currentText());
//        qNewElement.setAttribute(tr("lnClss"), ((QComboBox*)(AttrTable->cellWidget(1,1)))->currentText());
//        qNewElement.setAttribute(tr("id"), AttrTable->item(2,1)->text());
//        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("desc"), AttrTable->item(3,1)->text());

//        currentNode.appendChild(qNewElement);
//DomItem newItem = DomItem(qNewElement, 0, 0);
//	currentItem->insertChildren(currentItem->childNum(), newItem);
//// 	currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//        break;
//    }
}

void MainWindow::addDOType(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - DOType"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(4,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("iedType")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("(*)cdc")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(2,0,new QTableWidgetItem(tr("(*)id")));
//    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(3,0,new QTableWidgetItem(tr("desc")));
//    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);

//    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
//    AttrTable->setCellWidget(1,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(1,1)))->addItems(cdc);
//    ((QComboBox*)(AttrTable->cellWidget(1,1)))->setEditable(1);
//    AttrTable->setItem(2,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(3,1,new QTableWidgetItem(tr("")));

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    while(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("DOType"));

//        if(AttrTable->item(2,1)->text()==tr(""))
//        {
//            QMessageBox::warning(NULL,tr("警告"),tr("id项为必需项，不能为空!"));
//            continue;
//        }

//        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("iedType"), AttrTable->item(0,1)->text());
//        qNewElement.setAttribute(tr("cdc"), ((QComboBox*)(AttrTable->cellWidget(1,1)))->currentText());
//        qNewElement.setAttribute(tr("id"), AttrTable->item(2,1)->text());
//        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("desc"), AttrTable->item(3,1)->text());

//        currentNode.appendChild(qNewElement);
//        DomItem newItem = DomItem(qNewElement, 0, 0);
//	currentItem->insertChildren(currentItem->childNum(), newItem);
//// 	currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//        break;
//    }
}

void MainWindow::addDAType(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - DAType"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(3,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("iedType")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(0,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("(*)id")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(2,0,new QTableWidgetItem(tr("desc")));
//    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);

//    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(1,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(2,1,new QTableWidgetItem(tr("")));

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    while(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("DAType"));

//        if(AttrTable->item(1,1)->text()==tr(""))
//        {
//            QMessageBox::warning(NULL,tr("警告"),tr("id项为必需项，不能为空!"));
//            continue;
//        }

//        if(AttrTable->item(0,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("iedType"), AttrTable->item(0,1)->text());
//        qNewElement.setAttribute(tr("id"), AttrTable->item(1,1)->text());
//        if(AttrTable->item(2,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("desc"), AttrTable->item(2,1)->text());

//        currentNode.appendChild(qNewElement);
//        DomItem newItem = DomItem(qNewElement, 0, 0);
//	currentItem->insertChildren(currentItem->childNum(), newItem);
//// 	currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//        break;
//    }
}

void MainWindow::addEnumType(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - EnumType"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(2,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)id")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("desc")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);

//    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(1,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(2,1,new QTableWidgetItem(tr("")));

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    while(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("EnumType"));

//        if(AttrTable->item(0,1)->text()==tr(""))
//        {
//            QMessageBox::warning(NULL,tr("警告"),tr("id项为必需项，不能为空!"));
//            continue;
//        }

//        qNewElement.setAttribute(tr("id"), AttrTable->item(0,1)->text());
//        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("desc"), AttrTable->item(1,1)->text());

//        currentNode.appendChild(qNewElement);
//        DomItem newItem = DomItem(qNewElement, 0, 0);
//	currentItem->insertChildren(currentItem->childNum(), newItem);
//// 	currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//        break;
//    }
}

void MainWindow::addDO(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - DO"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(5,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)name")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("(*)type")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(2,0,new QTableWidgetItem(tr("accessControl")));
//    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(3,0,new QTableWidgetItem(tr("transient")));
//    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(4,0,new QTableWidgetItem(tr("desc")));
//    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(4,0)->setCheckState(Qt::Unchecked);

//    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
//    AttrTable->setCellWidget(1,1,new QComboBox(this));
//    AttrTable->setItem(2,1,new QTableWidgetItem(tr("")));
//    AttrTable->setCellWidget(3,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(3,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
//    ((QComboBox*)(AttrTable->cellWidget(3,1)))->setCurrentIndex(1);
//    AttrTable->setItem(4,1,new QTableWidgetItem(tr("")));

//    QStringList DAType;
//    QDomNode DataTypeNode = currentNode.parentNode();
//    for(int i=0; i<DataTypeNode.childNodes().count(); i++)
//    {
//        if(DataTypeNode.childNodes().at(i).toElement().tagName().contains(tr("DAType")))
//        {
//            QDomNode DATypeNode = DataTypeNode.childNodes().at(i);

//            if(DATypeNode.attributes().contains(tr("id")))
//                DAType.append(DATypeNode.attributes().namedItem("id").toAttr().value());
//        }
//    }
//    if(DAType.isEmpty())
//        DAType.append(tr(""));
//    ((QComboBox*)(AttrTable->cellWidget(1,1)))->addItems(DAType);

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    while(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("DO"));

//        if(AttrTable->item(0,1)->text()==tr(""))
//        {
//            QMessageBox::warning(NULL,tr("警告"),tr("name项为必需项，不能为空!"));
//            continue;
//        }

//        qNewElement.setAttribute(tr("name"), AttrTable->item(0,1)->text());
//        qNewElement.setAttribute(tr("type"), ((QComboBox*)(AttrTable->cellWidget(1,1)))->currentText());
//        if(AttrTable->item(2,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("accessControl"), AttrTable->item(2,1)->text());
//        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("transient"), ((QComboBox*)(AttrTable->cellWidget(3,1)))->currentText());
//        if(AttrTable->item(4,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("desc"), AttrTable->item(4,1)->text());

//        currentNode.appendChild(qNewElement);
//        DomItem newItem = DomItem(qNewElement, 0, 0);
//	currentItem->insertChildren(currentItem->childNum(), newItem);
//// 	currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//        break;
//    }
}

void MainWindow::addSDO(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - SDO"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(3,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)type")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("(*)name")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(2,0,new QTableWidgetItem(tr("desc")));
//    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);

//    AttrTable->setItem(0,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(1,1,new QTableWidgetItem(tr("")));
//    AttrTable->setItem(2,1,new QTableWidgetItem(tr("")));

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    while(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("SDO"));

//        if(AttrTable->item(0,1)->text()==tr(""))
//        {
//            QMessageBox::warning(NULL,tr("警告"),tr("type项为必需项，不能为空!"));
//            continue;
//        }
//        if(AttrTable->item(1,1)->text()==tr(""))
//        {
//            QMessageBox::warning(NULL,tr("警告"),tr("name项为必需项，不能为空!"));
//            continue;
//        }

//        qNewElement.setAttribute(tr("type"), AttrTable->item(0,1)->text());
//        qNewElement.setAttribute(tr("name"), AttrTable->item(1,1)->text());
//        if(AttrTable->item(2,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("desc"), AttrTable->item(2,1)->text());

//        currentNode.appendChild(qNewElement);
//        DomItem newItem = DomItem(qNewElement, 0, 0);
//	currentItem->insertChildren(currentItem->childNum(), newItem);
//// 	currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//        break;
//    }
}

void MainWindow::addDA(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - DA"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(11,2,this);
//    AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)fc")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("dchg")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(2,0,new QTableWidgetItem(tr("qchg")));
//    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(3,0,new QTableWidgetItem(tr("dupds")));
//    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(4,0,new QTableWidgetItem(tr("(*)name")));
//    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(5,0,new QTableWidgetItem(tr("sAddr")));
//    AttrTable->item(5,0)->setFlags(AttrTable->item(5,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(5,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(6,0,new QTableWidgetItem(tr("(*)bType")));
//    AttrTable->item(6,0)->setFlags(AttrTable->item(6,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(6,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(7,0,new QTableWidgetItem(tr("valKind")));
//    AttrTable->item(7,0)->setFlags(AttrTable->item(7,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(7,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(8,0,new QTableWidgetItem(tr("type")));
//    AttrTable->item(8,0)->setFlags(AttrTable->item(8,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(8,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(9,0,new QTableWidgetItem(tr("count")));
//    AttrTable->item(9,0)->setFlags(AttrTable->item(9,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(9,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(10,0,new QTableWidgetItem(tr("desc")));
//    AttrTable->item(10,0)->setFlags(AttrTable->item(10,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(10,0)->setCheckState(Qt::Unchecked);

//    AttrTable->setCellWidget(0,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(0,1)))->addItems(fcEnum);
//    AttrTable->setCellWidget(1,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(1,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
//    ((QComboBox*)(AttrTable->cellWidget(1,1)))->setCurrentIndex(1);
//    AttrTable->setCellWidget(2,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(2,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
//    ((QComboBox*)(AttrTable->cellWidget(2,1)))->setCurrentIndex(1);
//    AttrTable->setCellWidget(3,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(3,1)))->addItems(QStringList()<<tr("true")<<tr("false"));
//    ((QComboBox*)(AttrTable->cellWidget(3,1)))->setCurrentIndex(1);
//    AttrTable->setCellWidget(4,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(4,1)))->addItems(QStringList()<<tr("T")<<tr("Test")<<tr("Check")<<tr("SIUnit"));
//    ((QComboBox*)(AttrTable->cellWidget(4,1)))->setEditable(1);
//    AttrTable->setItem(5,1,new QTableWidgetItem(tr("")));
//    AttrTable->setCellWidget(6,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(6,1)))->addItems(BasicType);
//    ((QComboBox*)(AttrTable->cellWidget(6,1)))->setEditable(1);
//    AttrTable->setCellWidget(7,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(7,1)))->addItems(QStringList()<<tr("Spec")<<tr("Conf")<<tr("RO")<<tr("Set"));
//    ((QComboBox*)(AttrTable->cellWidget(7,1)))->setCurrentIndex(3);
//    AttrTable->setItem(8,1,new QTableWidgetItem(tr("")));
//    AttrTable->setCellWidget(9,1,new QSpinBox(this));
//    AttrTable->setItem(10,1,new QTableWidgetItem(tr("")));

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    if(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("DA"));

//        qNewElement.setAttribute(tr("fc"), ((QComboBox*)(AttrTable->cellWidget(0,1)))->currentText());
//        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("dchg"), ((QComboBox*)(AttrTable->cellWidget(1,1)))->currentText());
//        if(AttrTable->item(2,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("qchg"), ((QComboBox*)(AttrTable->cellWidget(2,1)))->currentText());
//        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("dupd"), ((QComboBox*)(AttrTable->cellWidget(3,1)))->currentText());
//        qNewElement.setAttribute(tr("name"), ((QComboBox*)(AttrTable->cellWidget(4,1)))->currentText());
//        if(AttrTable->item(5,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("sAddr"), AttrTable->item(5,1)->text());
//        qNewElement.setAttribute(tr("bType"), ((QComboBox*)(AttrTable->cellWidget(6,1)))->currentText());
//        if(AttrTable->item(7,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("valKind"), ((QComboBox*)(AttrTable->cellWidget(7,1)))->currentText());
//        if(AttrTable->item(8,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("type"), AttrTable->item(8,1)->text());
//        if(AttrTable->item(9,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("count"), ((QSpinBox*)(AttrTable->cellWidget(9,1)))->text());
//        if(AttrTable->item(10,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("desc"), AttrTable->item(10,1)->text());

//        currentNode.appendChild(qNewElement);
//        DomItem newItem = DomItem(qNewElement, 0, 0);
//	currentItem->insertChildren(currentItem->childNum(), newItem);
//// 	currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//    }
}

void MainWindow::addBDA(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - BDA"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(7,2,this);

//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)name")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->setItem(1,0,new QTableWidgetItem(tr("sAddr")));
//    AttrTable->item(1,0)->setFlags(AttrTable->item(1,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(1,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(2,0,new QTableWidgetItem(tr("(*)bType")));
//    AttrTable->item(2,0)->setFlags(AttrTable->item(2,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(2,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(3,0,new QTableWidgetItem(tr("valKind")));
//    AttrTable->item(3,0)->setFlags(AttrTable->item(3,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(3,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(4,0,new QTableWidgetItem(tr("type")));
//    AttrTable->item(4,0)->setFlags(AttrTable->item(4,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(4,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(5,0,new QTableWidgetItem(tr("count")));
//    AttrTable->item(5,0)->setFlags(AttrTable->item(5,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(5,0)->setCheckState(Qt::Unchecked);
//    AttrTable->setItem(6,0,new QTableWidgetItem(tr("desc")));
//    AttrTable->item(6,0)->setFlags(AttrTable->item(6,0)->flags() & (~Qt::ItemIsEditable));
//    AttrTable->item(6,0)->setCheckState(Qt::Unchecked);

//    AttrTable->setCellWidget(0,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(0,1)))->addItems(QStringList()<<tr("T")<<tr("Test")<<tr("Check")<<tr("SIUnit"));
//    ((QComboBox*)(AttrTable->cellWidget(0,1)))->setEditable(1);
//    AttrTable->setItem(1,1,new QTableWidgetItem(tr("")));
//    AttrTable->setCellWidget(2,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(2,1)))->addItems(BasicType);
//    ((QComboBox*)(AttrTable->cellWidget(2,1)))->setEditable(1);
//    AttrTable->setCellWidget(3,1,new QComboBox(this));
//    ((QComboBox*)(AttrTable->cellWidget(3,1)))->addItems(QStringList()<<tr("Spec")<<tr("Conf")<<tr("RO")<<tr("Set"));
//    ((QComboBox*)(AttrTable->cellWidget(3,1)))->setCurrentIndex(3);
//    AttrTable->setItem(4,1,new QTableWidgetItem(tr("")));
//    AttrTable->setCellWidget(5,1,new QSpinBox(this));
//    AttrTable->setItem(6,1,new QTableWidgetItem(tr("")));

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    if(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("BDA"));

//        qNewElement.setAttribute(tr("name"), ((QComboBox*)(AttrTable->cellWidget(0,1)))->currentText());
//        if(AttrTable->item(1,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("sAddr"), AttrTable->item(1,1)->text());
//        qNewElement.setAttribute(tr("bType"), ((QComboBox*)(AttrTable->cellWidget(2,1)))->currentText());
//        if(AttrTable->item(3,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("valKind"), ((QComboBox*)(AttrTable->cellWidget(3,1)))->currentText());
//        if(AttrTable->item(4,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("type"), AttrTable->item(4,1)->text());
//        if(AttrTable->item(5,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("count"), ((QSpinBox*)(AttrTable->cellWidget(5,1)))->text());
//        if(AttrTable->item(6,0)->checkState() == Qt::Checked)
//            qNewElement.setAttribute(tr("desc"), AttrTable->item(6,1)->text());

//        currentNode.appendChild(qNewElement);
//        DomItem newItem = DomItem(qNewElement, 0, 0);
//	currentItem->insertChildren(currentItem->childNum(), newItem);
//// 	currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);
//    }
}

void MainWindow::addEnumVal(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    QDialog *AttrDlg = new QDialog(this);
//    AttrDlg->setWindowTitle(tr("属性编辑器 - EnumVal"));
//    QGridLayout *AttrDlgLayout = new QGridLayout(AttrDlg);
//    QTableWidget *AttrTable = new QTableWidget(1,2,this);

//    AttrTable->setItem(0,0,new QTableWidgetItem(tr("(*)ord")));
//    AttrTable->item(0,0)->setFlags(AttrTable->item(0,0)->flags() & (~Qt::ItemIsEditable));

//    AttrTable->setCellWidget(0,1,new QSpinBox(this));
//    ((QSpinBox*)(AttrTable->cellWidget(0,1)))->setMinimum(-65535);

//    QPushButton *qAttrDlgConfirm = new QPushButton(tr("确认"),this);
//    connect(qAttrDlgConfirm, SIGNAL(clicked()), AttrDlg, SLOT(accept()));
//    QPushButton *qAttrDlgCancel = new QPushButton(tr("放弃"),this);
//    connect(qAttrDlgCancel, SIGNAL(clicked()), AttrDlg, SLOT(close()));
//    AttrDlgLayout->addWidget(AttrTable,0,0,1,4);
//    AttrDlgLayout->addWidget(qAttrDlgConfirm,9,2);
//    AttrDlgLayout->addWidget(qAttrDlgCancel,9,3);

//    if(AttrDlg->exec() == QDialog::Accepted)
//    {
//        QDomElement qNewElement = doc->createElement(tr("EnumVal"));

//        qNewElement.setAttribute(tr("ord"), ((QSpinBox*)(AttrTable->cellWidget(0,1)))->text());

//        currentNode.appendChild(qNewElement);
//        DomItem newItem = DomItem(qNewElement, 0, 0);
//	currentItem->insertChildren(currentItem->childNum(), newItem);
//// 	currentItem->insertChildren(currentItem->childNum(), (QDomNode)qNewElement);

//        QModelIndex parentIndex = currentIndex.parent();
//        view->setExpanded(parentIndex,0);
//        view->setExpanded(parentIndex,1);
//        view->setExpanded(currentIndex,1);

//    }
}

void MainWindow::deleteItem(const QModelIndex& currentIndex)
{
////    QModelIndex *currentIndex = new QModelIndex();
////        *currentIndex = currentIndex;
//    DomItem *currentItem = static_cast<DomItem*>(currentIndex.internalPointer());
//    QDomNode currentNode = currentItem->node();

//    qDebug()<<"Delete Item";
//    qDebug()<<currentNode.nodeName();
//    qDebug()<<currentNode.childNodes().count();

//    DomItem* parentItem = currentItem->parent();
//    QDomNode parentNode = parentItem->node();
//    qDebug()<<parentNode.nodeName();
//    qDebug()<<parentNode.childNodes().count();

//    QModelIndex parentIndex;


////     if(parentNode.childNodes().count()>1)
//         parentIndex = currentIndex.parent();//.parent();
////     else
////         parentIndex = currentIndex.parent().parent();

////    for(int i=0; i<currentNode.childNodes().count(); i++)
////    {
////        currentNode.removeChild(currentNode.childNodes().at(i));
////    }


////    if(view->model()->hasChildren(currentIndex))
////        view->model()->removeRows(0,view->model()->rowCount(currentIndex),currentIndex);
////     parentItem->removeChildren(currentItem->childNum(),1);

//    view->model()->removeRows(currentIndex.row(),1,currentIndex.parent());
////    parentItem->removeChildren(currentItem->row(),1);
//    parentNode.removeChild(currentNode);
////    refresh();
////    view->setExpanded(parentIndex,0);
////    view->setExpanded(parentIndex,1);
////    refresh();
////    view->selectionModel()->setCurrentIndex(model->index(0,0,parentIndex), QItemSelectionModel::ClearAndSelect);
//    emit deleteNode(currentIndex);


}

void MainWindow::deleteChildren(DomItem* item)
{
/*//    item->removeChildren(item);

    qDebug()<<item->node().nodeName();

    int i = 0;
    int childCount = item->node().childNodes().count();
//    if(childCount)

    while(childCount)
    {
        for(int j=0; j<item->node().childNodes().count(); j++)
            if(item->node().childNodes().at(j).nodeType() == QDomNode::TextNode)
                childCount--;
//        for(i=0; i<item->node().childNodes().count();i++)
        qDebug()<<childCount;
        qDebug()<<i;
        if(item->child(i)->node().nodeType() != QDomNode::TextNode)
        {
            deleteChildren(item->child(i));
            childCount--;
            i--;
        }
//        i++;
//        else
//            break;
//        for(int i=0; i<item->node().childNodes().count(); i++)
//        {
//            qDebug()<<i<<'\t'<<item->child(i)->node().nodeName();
//            deleteChildren(item->child(i));
//        }

    }
//    else
//    {
//    qDebug()<<item->parent()->node().nodeName();
//    qDebug()<<item->node().nodeName();
//    for(int j=0; j<item->parent()->node().childNodes().count();j++)
//    {
        qDebug()<<item->node().nodeName();
        qDebug()<<item->parent()->node().nodeName();
//        item->parent()->node().removeChild(item->node());
//        item->parent()->removeChild(i);
        if(i>0)
            i--;
//    }
        //node.parentNode().removeChild(node);
//        item->parent()->node().removeChild(item->node());
//        for(int j=0; j<item->parent()->node().childNodes().count(); j++)
//            if(item->parent()->node().childNodes().at(j).nodeName() == item->node().nodeName())
//                item->parent()->removeChild(j);
//    }*/
}

void MainWindow::refresh()
{
//    model->update();
//    DomModel *newModel = new DomModel(*doc);
//    view->setModel(newModel);
//    model = newModel;

//    qDebug()<<view->model()->index(2,0);
//    view->setExpanded(view->model()->index(2,0),true);
}



void MainWindow::showAttributes(const QModelIndex& index)
{
//    DomItem* item = static_cast<DomItem*>(index.internalPointer());
//    QDomNode node = item->node();

////    if(node.nodeName() == tr("IED"))
//    {
//        qDebug()<<"Here Click IED";
///*        if(!AttrTable)
//        {
//            AttrTable = new QTableWidget(node.attributes().count(),2,this);
//            AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//        }
//        else*/
//        if(AttrTable)
//        {
//            AttrTable->deleteLater();
//            AttrTable = NULL;
//        }


//        {
////            AttrTable->setRowCount(node.attributes().count());

//            AttrTable = new NodeTableWidget(node.attributes().count(),2,qSplitterMain);
////            qSplitterMain->addWidget(AttrTable);
//            AttrTable->setModelIndex(index);
//            qSplitterMain->setStretchFactor(0,4);
//            AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//            for(int i=0; i<node.attributes().count(); i++)
//            {
//                AttrTable->setItem(i,0,new QTableWidgetItem(node.attributes().item(i).toAttr().name()));
//                AttrTable->item(i,0)->setFlags(AttrTable->item(i,0)->flags() & (~Qt::ItemIsEditable));
//                AttrTable->setItem(i,1,new QTableWidgetItem(node.attributes().item(i).toAttr().value()));
//            }

//            connect(AttrTable, SIGNAL(nodeCellChanged(const QModelIndex&,int,int)), this, SLOT(changeAttributes(QModelIndex, int, int)), Qt::UniqueConnection);

//        }

////        for(int i=0; i<node.attributes().count(); i++)
////        {
////            node.attributes().item(i).toAttr().value() = AttrTable->item(i,1)->text();
////            AttrTable->item(i,0)->setFlags(AttrTable->item(i,0)->flags() & (~Qt::ItemIsEditable));
////            AttrTable->setItem(i,1,new QTableWidgetItem(node.attributes().item(i).toAttr().value()));
////        }

//    }
}

void MainWindow::changeAttributes(const QModelIndex& index, int row, int column)
{
//    if(column == 0)
//        return;

//    DomItem* item = static_cast<DomItem*>(index.internalPointer());
//    QDomNode node = item->node();

//    node.toElement().setAttribute(AttrTable->item(row,0)->text(),AttrTable->item(row,1)->text());

///*    for(int i=0; i<node.attributes().count(); i++)
//    {
//        if(node.attributes().item(i).toAttr().name() == AttrTable->item(row,0)->text())
//        {
//            node.toElement().setNodeValue(AttrTable->item(row,1)->text());
//            return;
//        }
//    }*/

}

void MainWindow::hideAttributes(const QModelIndex& index)
{
//    if(AttrTable->getModelIndex() == index)
//    {
//        AttrTable->setParent(NULL);
////        AttrTable = new NodeTableWidget(0,2,qSplitterMain);
////        qSplitterMain->setStretchFactor(0,4);
////        AttrTable->setHorizontalHeaderLabels(QStringList()<<tr("名称")<<tr("值"));
//    }

//    return;
}

void MainWindow::ItemMoveUp(const QModelIndex& index)
{
//    ((DomModel*)(view->model()))->moveUpRows(index);
}

void MainWindow::ItemMoveDown(const QModelIndex& index)
{

}
