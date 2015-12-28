#include <QtXml/QDomDocument>
#include <QFile>
#include <QtGui>
#include <QClipboard>
#include <QXmlSchema>
#include <QXmlSchemaValidator>
#include <QDebug>
#include <QVector>

#include "mainwindow.h"

#include "config.h"
#include "utils.h"
#include "qxmledit.h"
#include "schemavalidator.h"
#include "SchemaInterface.h"
#include "aboutdialog.h"
#include "balsamiqsrc/balsamiqplugin.h"
#include "xsdeditor/xsdplugin.h"
#include "compare.h"
#include "preferreddirs.h"
#include "configurationdialog.h"
#include "snippet_interface.h"
#include "test.h"
#include "recodericdwizard.h"

#define MAX_LAST_FILES  (20)
#define SHORT_TIMEOUT  2000
#define LONG_TIMEOUT   10000

void doOptions(QWidget * const parentWindow, QXmlEditData* data);
//void executeTests(QWidget *parent);
//void extractFragments(ExtractResults *extractResult, QWidget *parent);
void ShowTextInDialoog(QWidget *parent, const QString &text);

#define CS_ELEMENT_TEXT "E"
#define CS_ELEMENT_TAG "T"
#define CS_ATTRIBUTE_NAME "N"
#define CS_ATTRIBUTE_VALUE "V"

extern const char *APP_TITLE;

int MainWindow::pluginCode = 0;

MainWindow::MainWindow(const bool setIsSlave, QApplication *newApp, QXmlEditData *newData, QWidget *parent)
    : QMainWindow(parent)
{
    isAutoDelete = false;
    started = false ;
    internalStateOk = false;

    maxLastFiles = MAX_LAST_FILES;
    maxPrefDirs = QXmlEditParameters::NUM_PREF_DIRS;

    app = newApp;
    data = newData;
    isSlave = setIsSlave;

    pluginCode = 0;
    BalsamiqPlugin *plugin = new BalsamiqPlugin();

    labelSchema = NULL;

    if(NULL == plugin) {
        Utils::error(tr("Unable to load Balsamiq plugin"));
    } else {
        pluginCode ++;
        _plugins.insert(QString(pluginCode), plugin);
    }

    XsdPlugin *xsdPlugin = new XsdPlugin();
    _xsdPlugin = xsdPlugin;
    if(NULL == xsdPlugin) {
        Utils::error(tr("Unable to load XSD Plugin"));
    } else {
        pluginCode ++;
        _plugins.insert(QString(pluginCode), xsdPlugin);
    }

    CreateMenus();
    internalStateOk = finishSetUpUi();
    if(!internalStateOk) {
        Utils::error(tr("Error preparing user interface."));
    }
    if(!editor->isReady()) {
        Utils::error(tr("Error preparing edit widget."));
    }

    loadRecentFilesSettings();
    loadPreferredDirsSettings();
    setAcceptDrops(true);
    setUnifiedTitleAndToolBarOnMac(true);

    QString windowTitle = APP_TITLE;
    setWindowTitle(windowTitle);

//    autoTest();

    started = true ;
}

MainWindow::~MainWindow()
{
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
//    resize(906, 725);
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/icon/images/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
    setWindowIcon(icon);

    actionNew = new QAction(this);
    actionNew->setObjectName(QString::fromUtf8("actionNew"));
    QIcon icon1;
    icon1.addFile(QString::fromUtf8(":/new/images/document-new.png"), QSize(), QIcon::Normal, QIcon::Off);
    actionNew->setIcon(icon1);

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
    QIcon icon100;
    icon100.addFile(QString::fromUtf8(":/images/edit-delete"), QSize(), QIcon::Normal, QIcon::Off);
    actionDelete->setIcon(icon100);
//    actionDelete->setIcon(QIcon(tr(":/images/images/edit-delete.png")));

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

    actionConfigure = new QAction(this);
    actionConfigure->setObjectName(QString::fromUtf8("actionConfigure"));
    actionConfigure->setMenuRole(QAction::PreferencesRole);

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

    actionUndo = new QAction(this);
    actionUndo->setObjectName(QString::fromUtf8("actionUndo"));

    actionRedo = new QAction(this);
    actionRedo->setObjectName(QString::fromUtf8("actionRedo"));

    actionEncodingTools = new QAction(this);
    actionEncodingTools->setObjectName(QString::fromUtf8("actionEncodingTools"));

    actionNewRcdICDWizard = new QAction(this);
    actionNewRcdICDWizard->setObjectName(QString::fromUtf8("actionNewRcdICDWizard"));

    actionNewNetICDWizard = new QAction(this);
    actionNewNetICDWizard->setObjectName(QString::fromUtf8("actionNewNetICDWizard"));

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
    menuFile->addAction(actionNew);
    menuFile->addAction(actionNewFromClipboard);
    menuFile->addAction(actionNewUsingXMLSchema);
    menuFile->addAction(actionNewRcdICDWizard);
    menuFile->addAction(actionNewNetICDWizard);
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
    menuTools->addAction(actionEncodingTools);
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
    toolBar->addAction(actionFind);
    toolBar->addAction(actionValidate);
    toolBar->addSeparator();
    toolBar->addAction(actionGo_To_Parent);
    toolBar->addAction(actionGo_to_Previous_Brother);
    toolBar->addAction(actionGo_to_Next_Brother);
    toolBar->addSeparator();
    toolBar->addAction(actionHelpOnQXmlEdit);


    actionEditAttribute = new QAction(this);
    actionEditAttribute->setObjectName(tr("actionEditAttribute"));

    actionAddText = new QAction(this);
    actionAddText->setObjectName(tr("actionAddText"));

    menuAddLN0 = new QMenu(this);
    menuAddLN0->setObjectName(tr("menuAddLN0"));

    menuAddLN = new QMenu(this);
    menuAddLN->setObjectName(tr("menuAddLN"));

    actionAddLLN0 = new QAction(this);
    actionAddLLN0->setObjectName(tr("actionAddLLN0"));

    actionAddLN = new QAction(this);
    actionAddLN->setObjectName(tr("actionAddLN"));

//    actionAddLPHD = new QAction(this);
//    actionAddLPHD->setObjectName(tr("actionAddLPHD"));

//    actionAddGGIO = new QAction(this);
//    actionAddGGIO->setObjectName(tr("actionAddGGIO"));

//    actionAddLTSM = new QAction(this);
//    actionAddLTSM->setObjectName(tr("actionAddLTSM"));

    actionAddDataSet = new QAction(this);
    actionAddDataSet->setObjectName(tr("actionAddDataSet"));

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
    actionConfigure->setText(QApplication::translate("MainWindow", "Confi&gure...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionConfigure->setToolTip(QApplication::translate("MainWindow", "Configure", 0, QApplication::UnicodeUTF8));
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

    actionEncodingTools->setText(QApplication::translate("MainWindow", "Encoding Tools...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
    actionEncodingTools->setToolTip(QApplication::translate("MainWindow", "Encoding Tools.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP

    actionNewRcdICDWizard->setText(QApplication::translate("MainWindow", "New Recoder ICD file wizard", 0, QApplication::UnicodeUTF8));
    actionNewNetICDWizard->setText(QApplication::translate("MainWindow", "New NetAnalyzer ICD file wizard", 0, QApplication::UnicodeUTF8));

    menu_Navigation->setTitle(QApplication::translate("MainWindow", "&Navigation", 0, QApplication::UnicodeUTF8));
    menuHelp->setTitle(QApplication::translate("MainWindow", "&Help", 0, QApplication::UnicodeUTF8));
    menuEdit->setTitle(QApplication::translate("MainWindow", "&Edit", 0, QApplication::UnicodeUTF8));
    menuFile->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
    menu_XML->setTitle(QApplication::translate("MainWindow", "&XML", 0, QApplication::UnicodeUTF8));
    menuXML_Schema->setTitle(QApplication::translate("MainWindow", "XML Schema", 0, QApplication::UnicodeUTF8));
    menuTools->setTitle(QApplication::translate("MainWindow", "&Tools", 0, QApplication::UnicodeUTF8));
    menuView->setTitle(QApplication::translate("MainWindow", "&View", 0, QApplication::UnicodeUTF8));
    toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));


    actionEditAttribute->setText(tr("EditAttributes"));
    actionEditAttribute->setIcon(QIcon(":/commands/images/EditAttributes.png"));

    actionAddText->setText(tr("text"));
    actionAddText->setIcon(QIcon(":/commands/images/AddText.png"));

    menuAddLN0->setTitle(tr("LN0"));
    menuAddLN->setTitle(tr("LN"));

    actionAddDataSet->setText(tr("DataSet"));

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
    if(!editor->init()) {
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
    connect(editor, SIGNAL(showStatusMessage(QString,bool)), this, SLOT(onShowStatusMessage(QString,bool)));
    connect(editor, SIGNAL(undoStateUpdated(bool,bool)), this, SLOT(onUndoStateUpdated(bool,bool)));

    startUIState();
    actionShowAttrLine->setCheckable(true);
    actionShowChildIndex->setCheckable(true);
    actionCompactView->setCheckable(true);
    actionHideBrothers->setCheckable(true);
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
//    actionShowBase64->setChecked(paintInfo->showUnBase64());
    actionShowElementSize->setChecked(paintInfo->showItemSize());
    actionHideView->setChecked(paintInfo->hideView());

    updateUndoState(false, false);

    connect(editor, SIGNAL(treeContextMenuRequested(QPoint)), this, SLOT(treeContextMenu(QPoint)));

    menu_XML->setTearOffEnabled(false);

    bool isOk = true;
    QToolButton *editTextButton = new QToolButton(this);
    QMenu *editTextMenu = new QMenu(this);
    if((NULL == editTextButton) || (editTextMenu == NULL)) {
        isOk = true;
    } else {
        editTextButton->setMenu(editTextMenu);
        editTextButton->setPopupMode(QToolButton::InstantPopup);
        editTextButton->setIcon(QIcon(":/commands/modify"));
        toolBar->insertWidget(actionHelpOnQXmlEdit, editTextButton);
        toolBar->insertSeparator(actionHelpOnQXmlEdit);
    }

    labelSchema = new QLabel(statusBar());
    if(NULL == labelSchema) {
        Utils::error(tr("Error creating user interface"));
        return false;
    }
    setSchemaLabel(tr(""));
    statusBar()->addPermanentWidget(labelSchema);

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

    contextMenu.addAction(actionEditAttribute);
    contextMenu.addAction(actionAddText);

    if(editor->getSelectedItem()->tag() == tr("LDevice")) {

        QVector<DomItem*> lnItems = getModel()->getDataTypeItems();
        foreach(DomItem *item, lnItems) {
            QString LNActionName = item->attributeValueOfName("lnClass") + tr(": ") + item->attributeValueOfName("id");
            if(item->attributeValueOfName(tr("lnClass")) == tr("LLN0")) {
                actionAddLLN0->setText(LNActionName);
                menuAddLN0->addAction(actionAddLLN0);
            } else {
                actionAddLN->setText(LNActionName);
                menuAddLN->addAction(actionAddLN);
            }
//            connect(actionAddLNNode, SIGNAL(triggered()), this, SLOT(on_actionAddLNNode_triggered()));
        }

        if(!(editor->getSelectedItem()->hasChildOfName(tr("LN0")))) {
            contextMenu.addMenu(menuAddLN0);
        }
        contextMenu.addMenu(menuAddLN);
    }

    if(editor->getSelectedItem()->tag() == tr("LN0")) {

//        QVector<DomItem*> lnItems = getModel()->getDataTypeItems();
//        foreach(DomItem *item, lnItems) {

//        }

//        if(!(editor->getSelectedItem()->hasChildOfName(tr("LN0")))) {
//            contextMenu.addMenu(menuAddLN0);
//        }
        contextMenu.addAction(actionAddDataSet);
    }

    contextMenu.addSeparator();

    contextMenu.addAction(actionCut);
    contextMenu.addAction(actionCopy);
    bool isActionMode = editor->isActionMode();
    if(isActionMode) {
        contextMenu.addAction(actionPaste);
    }
    contextMenu.addSeparator() ;

    if(isActionMode) {
        contextMenu.addAction(actionTransforminSnippet);
        contextMenu.addSeparator() ;
        contextMenu.addAction(actionMoveUp);
        contextMenu.addAction(actionMoveDown);
        contextMenu.addAction(actionDelete);
    }
    DomItem *item = getSelectedItem();
    if(NULL != item) {
        if(item->areChildrenLeavesHidden(item->getUI())) {
            contextMenu.addAction(actionShowLeafChildren);
        } else {
            contextMenu.addAction(actionHideLeafChildren);
        }
    }

#ifdef XSD_INTEGRATION
    if(NULL != editor->schema()) {

        contextMenu.addSeparator() ;
        contextMenu.addAction(actionAllowedSchemaElements);
    }
#endif
    contextMenu.exec(editor->getMainTreeWidget()->mapToGlobal(position));
}

// only save as...
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

//
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
//    bool isShownAsBase64 = false ;
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
    actionReload->setEnabled((NULL != model) && !model->fileName().isEmpty());
    enableZoom();
    actionCopyPathToClipboard->setEnabled((NULL != model) && !model->fileName().isEmpty());
    actionAddCurrentDirectory->setEnabled((NULL != model) && !model->fileName().isEmpty());

    actionValidate->setEnabled((NULL != model) && !isExplore);

    actionValidateFile->setEnabled((NULL != model) && ! model->userDefinedXsd().isEmpty() && !isExplore);
    actionValidateNewFile->setEnabled((NULL != model) && !isExplore);
    actionTransforminSnippet->setEnabled(isSomeItemSelected && !isExplore);

    actionViewAsXsd->setEnabled(isValidXsd() && !isExplore);

    actionTransformInComment->setEnabled(isSomeItemSelected && !isExplore && !isComment);
    actionExtractElementsFromComment->setEnabled(isSomeItemSelected && !isExplore && isComment);

    actionInsertNoNamespaceSchemaReferenceAttributes->setEnabled((NULL != model) && !isExplore);
    actionInsertSchemaReferenceAttributes->setEnabled((NULL != model) && !isExplore);

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
                           tr("ICD files (*.icd);;SCD files (*.scd);;XML files (*.xml);;XML Schema files (*.xsd);;All files (*);;")
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
    if(!model->write(newFilePath)) {
        error(tr("Error saving data. Old file is still intact."));
        return ;
    }
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

    // set new extension name
    QString newFilePath = model->fileName() + ".new_new~"  ;
    if(!model->write(newFilePath)) {
        error(tr("Error saving data. Old file is still intact."));
        return ;
    }
    // backup the old file
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
    // rename the new file
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
    QList<AuthorInfo*> authors = authorsInfo() ;
    AboutDialog about(this,
                      AuthorInfo::appName, AuthorInfo::version, AuthorInfo::copyright,
                      AuthorInfo::license,
                      AuthorInfo::other,
                      authors);
    about.setModal(true);
    about.exec() ;
    deleteAuthorsInfo(authors);
}


void MainWindow::onShowStatusMessage(const QString &message, const bool isLongTimeout)
{
    statusBar()->showMessage(message, isLongTimeout ? LONG_TIMEOUT : SHORT_TIMEOUT);
}

void MainWindow::setFileTitle()
{
    QString windowTitle = APP_TITLE;
    if(!isSlave)
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
    if(isAutoDelete) {
        deleteLater();
    }
}

void MainWindow::on_actionQuit_triggered()
{
    if(MainWindow::checkAbandonChanges()) {
        app->quit();
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

void MainWindow::on_actionShowElementSize_triggered()
{
    editor->onActionShowItemSize(actionShowElementSize->isChecked());
}

void MainWindow::on_actionConfigure_triggered()
{
    ConfigurationDialog::doOptions(this, data);
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
    Compare::doCompare(this, model);
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
        if(!PreferredDirs::checkNewDir(preferredDirsNames.size(), true)) {
            return;
        }
        QFileInfo fileInfo(model->fileName());
        QString dirPath = fileInfo.path();
        if(!PreferredDirs::checkDuplicateDir(preferredDirsNames, dirPath, true)) {
            return ;
        }
        preferredDirsNames.append(dirPath);
        updatePreferredDirs(preferredDirsNames, preferredDirs);
    }
}

void MainWindow::on_actionEditPreferredDirectories_triggered()
{
    if(configurePreferredDirs(this, preferredDirsNames)) {
        updatePreferredDirs(preferredDirsNames, preferredDirs);
    }
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
    DomModel* model = getModel();
    if(NULL == model) {
        return;
    }
    DomModel* newModel = chooseSnippets(data, this) ;
    if(NULL != newModel) {
        editor->insertSnippet(newModel);
        delete newModel;
    }
}

void MainWindow::on_actionConfigureSnippets_triggered()
{
    editSnippets(data, this);
}

void MainWindow::on_actionExecuteAutoTest_triggered()
{
    Test::executeTests(this);
}

void MainWindow::on_actionTransforminSnippet_triggered()
{
    if(!editor->isActionMode()) {
        return ;
    }

    DomItem *item = getSelectedItem();
    if(NULL != item) {
        QDomDocument    document;
        if(item->generateDom(document, document)) {
            QString clipboardText = document.toString(4);
            insertFragmentInSnippets(this, data, clipboardText) ;
        }
    }
}

void MainWindow::onPlugin()
{
    QAction *actionFile = qobject_cast<QAction*>(sender());
    if(NULL != actionFile) {
        QString pluginId = actionFile->data().toString();
        if(!pluginId .isEmpty()) {
            IQXmlEditPlugIn* plugin = _plugins[pluginId];
            if(NULL != plugin) {
                plugin->go(this, getModel());
            }
        }
    }
}

bool MainWindow::buildPluginsMenu(const char *method, QMenu *parent)
{
    bool isOk = true;
    pluginsCmds.clear();
    QMapIterator<QString, IQXmlEditPlugIn*> pluginsIterator(_plugins);
    while(pluginsIterator.hasNext()) {
        pluginsIterator.next();
        QAction *action = new QAction(this);
        if(NULL != action) {
            pluginsCmds.append(action);
            connect(action, SIGNAL(triggered()), this, method);
            IQXmlEditPlugIn* plugin = pluginsIterator.value();
            action->setData(pluginsIterator.key());
            action->setText(plugin->name());
            action->setVisible(true);
            parent->addAction(action);
        } else {
            isOk = false ;
        }
    }
    return isOk ;
}



void MainWindow::setDisplayMode(const qxmledit::EDisplayMode value)
{
    editor->setDisplayMode(value);
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



void MainWindow::on_actionNewUsingXMLSchema_triggered()
{
    if(!verifyAbandonChanges()) {
        return ;
    }
    bool isOk = false;
    QString schemaURL;
    schemaURL = chooseSchemaFile(this, isOk) ;
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
    labelSchema->setText(newLabel);
}


void MainWindow::on_actionInsertNoNamespaceSchemaReferenceAttributes_triggered()
{
    editor->onActionInsertNoNamespaceSchemaReferenceAttributes();
}

void MainWindow::on_actionInsertSchemaReferenceAttributes_triggered()
{
    editor->onActionInsertSchemaReferenceAttributes();
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

void MainWindow::on_actionEncodingTools_triggered()
{
//    data->uiServices()->doEncodingDialog();
}

void MainWindow::on_actionNewRcdICDWizard_triggered()
{
    RecoderIcdWizard recoderICDWizard(this);
    if(recoderICDWizard.exec() == QDialog::Accepted) {
        QDomDocument *document = recoderICDWizard.document;
        setDocument(*document, "", true);
    }
}

void MainWindow::on_actionNewNetICDWizard_triggered()
{

}

void MainWindow::on_actionEditAttribute_triggered()
{
    editor->editAttribute();

}

void MainWindow::on_actionAddText_triggered()
{
    editor->addText();
}

void MainWindow::on_actionAddLNNode_triggered()
{

}

void MainWindow::on_actionAddLLN0_triggered()
{
    editor->addLLN0();
}

void MainWindow::on_actionAddLN_triggered()
{
    editor->addLNode();
}

void MainWindow::on_actionAddDataSet_triggered()
{
    editor->addDataSet();
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

