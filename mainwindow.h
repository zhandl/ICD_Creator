#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextCodec>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QDebug>
#include <QFile>
#include <QWidget>
#include <QMessageBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QTreeView>
#include <QTableView>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTabWidget>
#include <QCheckBox>
#include <QPushButton>
#include <QStringList>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QValidator>
#include <QTextDocument>
#include <QTextBrowser>
#include <QSplitter>
#include <QTextStream>
#include <QtXml>
#include <QSyntaxHighlighter>
#include <QHeaderView>

#include "dommodel.h"
#include "domitem.h"
#include "qitemaction.h"
#include "nodetablewidget.h"
#include "icdtreeview.h"

#include "xmleditwidget.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QAction *actionNew;
    QAction *actionQuit;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSaveAs;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionExpandAll;
    QAction *actionShowAttrLine;
    QAction *actionAbout;
    QAction *actionAddComment;
    QAction *actionAppendComment;
    QAction *actionAddProcessingInstruction;
    QAction *actionAppendProcessingInstruction;
    QAction *actionResizeToContents;
    QAction *actionAddChildElement;
    QAction *actionAppendChildElement;
    QAction *actionEdit;
    QAction *actionDelete;
    QAction *actionMoveUp;
    QAction *actionMoveDown;
    QAction *actionFind;
    QAction *actionGo_To_Parent;
    QAction *actionGo_to_Previous_Brother;
    QAction *actionGo_to_Next_Brother;
    QAction *actionShowChildIndex;
    QAction *actionCloseThisAllBrothers;
    QAction *actionNewFromClipboard;
    QAction *actionCompactView;
    QAction *actionHideBrothers;
    QAction *actionFixedSizeAttributes;
    QAction *actionShowAttributesLength;
    QAction *actionShowBase64;
    QAction *actionShowCurrentElementTextBase64;
    QAction *actionConfigure;
    QAction *actionEditInnerXML;
    QAction *actionEditInnerXMLBase64;
    QAction *actionEditInnerBase64Text;
    QAction *actionZoomIn;
    QAction *actionZoomOut;
    QAction *actionCompare;
    QAction *actionReload;
    QAction *actionLastFiles;
    QAction *actionCopyPathToClipboard;
    QAction *actionAddCurrentDirectory;
    QAction *actionEditPreferredDirectories;
    QAction *actionValidate;
    QAction *actionValidateFile;
    QAction *actionValidateNewFile;
    QAction *actionInsertSnippet;
    QAction *actionConfigureSnippets;
    QAction *actionExecuteAutoTest;
    QAction *actionPlugins;
    QAction *actionTransforminSnippet;
    QAction *actionShowElementTextLength;
    QAction *actionShowElementSize;
    QAction *actionXplore;
    QAction *actionBlindLoadFile;
    QAction *actionHideView;
    QAction *actionSearchInFiles;
    QAction *actionHelpOnQXmlEdit;
    QAction *actionAllowedSchemaElements;
    QAction *actionPasteAndSubstituteText;
    QAction *actionNewUsingXMLSchema;
    QAction *actionTransformInComment;
    QAction *actionExtractElementsFromComment;
    QAction *actionInsertNoNamespaceSchemaReferenceAttributes;
    QAction *actionInsertSchemaReferenceAttributes;
    QAction *actionExtractFragmentsFromFile;
    QAction *actionWelcomeDialog;
    QAction *actionSaveACopyAs;
    QAction *actionHideAllLeafChildren;
    QAction *actionShowAllLeafChildren;
    QAction *actionHideLeafChildren;
    QAction *actionShowLeafChildren;
    QAction *actionViewAsXsd;
    QAction *actionColumnView;
    QAction *actionShowCurrentSessionPanel;
    QAction *actionNewSession;
    QAction *actionPauseSession;
    QAction *actionResumeSession;
    QAction *actionCloseSession;
    QAction *actionManageSessions;
    QAction *actionSessionDetails;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionNewWindow;
    QAction *actionViewData;
    QAction *actionBase64Tools;
    QAction *actionEncodingTools;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    XmlEditWidget *editor;
    QMenuBar *menubar;
    QMenu *menu_Navigation;
    QMenu *menuHelp;
    QMenu *menuEdit;
    QMenu *menuFile;
    QMenu *menu_XML;
    QMenu *menuXML_Schema;
    QMenu *menuTools;
    QMenu *menuView;
    QStatusBar *statusbar;
    QToolBar *toolBar;

private:
    QStringList lnClass;
    QStringList fcEnum;
    QStringList cdc;
    QStringList BasicType;

    DomModel *model;
    QMenu *fileMenu;
//    QTreeView *view;
    ICDTreeView *view;
    QTableView *tab;
    QSplitter *qSplitterMain;
    NodeTableWidget *AttrTable;

    /*UI Variable Declare*/
    QMenuBar *qMenuBar;
    QMenu *qFileMenu;
    QAction *qFileNew;
    QAction *qFileOpen;
    QAction *qFileSave;
    QAction *qFileClose;

    QItemAction *qDeleteItem;

    QItemAction *qAddHeader;
    QItemAction *qAddSubstation;
    QItemAction *qAddCommunication;
    QItemAction *qAddIED;
    QItemAction *qAddDataTypeTemplates;

    QItemAction *qAddText;
    QItemAction *qAddTextContent;
    QItemAction *qAddHistory;
    QItemAction *qAddHitem;

    QItemAction *qAddVoltageLevel;
    QItemAction *qAddFunction;
    QItemAction *qAddPowerTransformer;
    QItemAction *qAddGeneralEquipment;
    QItemAction *qAddLNode;

    QItemAction *qAddVoltage;
    QItemAction *qAddBay;
    QItemAction *qAddSubFunction;

    QItemAction *qAddConductingEquipment;
    QItemAction *qAddConnectivityNode;

    QItemAction *qAddSubEquipment;

    QItemAction *qAddServices;
    QItemAction *qAddAccessPoint;

    QItemAction *qAddDynAssociation;
    QItemAction *qAddSettingGroups;
    QItemAction *qAddGetDirectory;
    QItemAction *qAddGetDataObjectDefinition;
    QItemAction *qAddDataObjectDirectory;
    QItemAction *qAddGetDataSetValue;
    QItemAction *qAddSetDataSetValue;
    QItemAction *qAddDataSetDirectory;
    QItemAction *qAddConfDataSet;
    QItemAction *qAddDynDataSet;
    QItemAction *qAddReadWrite;
    QItemAction *qAddTimerActivatedControl;
    QItemAction *qAddConfReportControl;
    QItemAction *qAddGetCBValues;
    QItemAction *qAddConfLogControl;
    QItemAction *qAddReportSettings;
    QItemAction *qAddLogSettings;
    QItemAction *qAddGSESettings;
    QItemAction *qAddSMVSettings;
    QItemAction *qAddGSEDir;
    QItemAction *qAddGOOSE;
    QItemAction *qAddGSSE;
    QItemAction *qAddFileHandling;
    QItemAction *qAddConfLNs;
    QItemAction *qAddSGEdit;
    QItemAction *qAddConfSG;

    QItemAction *qAddServer;
    QItemAction *qAddLN;

    QItemAction *qAddAuthentication;
    QItemAction *qAddLDevice;
    QItemAction *qAddAssociation;

    QItemAction *qAddLN0;
    QItemAction *qAddAccessControl;

    QItemAction *qAddGSEControl;
    QItemAction *qAddSampleValueControl;
    QItemAction *qAddSettingControl;
    QItemAction *qAddSCLControl;
    QItemAction *qAddLog;

    QItemAction *qAddDataSet;
    QItemAction *qAddReportControl;
    QItemAction *qAddLogControl;
    QItemAction *qAddDOI;
    QItemAction *qAddInputs;

    QItemAction *qAddIEDName;

    QItemAction *qAddSmvOpts;

    QItemAction *qAddFCDA;

    QItemAction *qAddOptFields;
    QItemAction *qAddRptEnabled;
    QItemAction *qAddTrgOps;

    QItemAction *qAddClientLN;

    QItemAction *qAddSDI;
    QItemAction *qAddDAI;

    QItemAction *qAddVal;
    QItemAction *qAddValContent;

    QItemAction *qAddExtRef;


    QItemAction *qAddLNodeType;
    QItemAction *qAddDOType;
    QItemAction *qAddDAType;
    QItemAction *qAddEnumType;

    QItemAction *qAddDO;
    QItemAction *qAddSDO;
    QItemAction *qAddDA;
    QItemAction *qAddBDA;
    QItemAction *qAddEnumVal;

    QItemAction *qMoveUp;
    QItemAction *qMoveDown;

    QAction *qRefresh;

    QString newFileName;
    QString openFileName;


    /*Declare the top Widget*/
    QTreeWidget *qTree;
    QTextDocument *qTextDocument;
//    QSyntaxHighlighter *qText;
    QTextBrowser *qText;

    /*Declare the Root of Tree*/
    QTreeWidgetItem *qSCLRoot;

    /*Declare the child Node of Root*/
    QTreeWidgetItem *qHeaderNode;
    QTreeWidgetItem *qSubstationNode;
    QTreeWidgetItem *qCommnicationNode;
    QTreeWidgetItem *qIEDNode;
    QTreeWidgetItem *qDataTypeTemplates;

    /*Document Variable Declare*/
    QDomDocument *doc;
    QDomElement root;
    QFile *newFile;

    /*UI Function Declare*/
    void CreateActions();
    void CreateMenus();
    void retranslateUi();

    /*Document Function Declare*/
    void CreateNewICD(QDomDocument*);

signals:
    void actionClick(QDomNode);
    void deleteNode(QModelIndex);

private slots:
    void fileNewAct();
    void fileOpenAct();
    void fileSaveAct();

    void deleteChildren(DomItem*);

    void deleteItem(const QModelIndex&);

    void addHeader(const QModelIndex&);
    void addSubstation(const QModelIndex&);
    void addCommunication(const QModelIndex&);
    void addIED(const QModelIndex&);
    void addDataTypeTemplates(const QModelIndex&);

//    void addHistoryAct(QDomNode);
    void addHistoryAct(const QModelIndex&);
    void addTextAct(const QModelIndex&);
    void addTextContentAct(const QModelIndex&);
    void addHitemAct(const QModelIndex&);

    void addVoltageLevel(const QModelIndex&);
    void addFunction(const QModelIndex&);
    void addPowerTransformer(const QModelIndex&);
    void addGeneralEquipment(const QModelIndex&);
    void addLNode(const QModelIndex &);

    void addVoltage(const QModelIndex&);
    void addBay(const QModelIndex&);
    void addSubFunction(const QModelIndex&);

    void addConductingEquipment(const QModelIndex&);
    void addSubEquipment(const QModelIndex&);
    void addConnectivityNode(const QModelIndex&);

    void addTerminal(const QModelIndex&);

    void addServices(const QModelIndex&);
    void addAccessPoint(const QModelIndex&);

    void addDynAssociation(const QModelIndex&);
    void addSettingGroups(const QModelIndex&);
    void addGetDirectory(const QModelIndex&);
    void addGetDataObjectDefinition(const QModelIndex&);
    void addDataObjectDirectory(const QModelIndex&);
    void addGetDataSetValue(const QModelIndex&);
    void addSetDataSetValue(const QModelIndex&);
    void addDataSetDirectory(const QModelIndex&);
    void addConfDataSet(const QModelIndex&);
    void addDynDataSet(const QModelIndex&);
    void addReadWrite(const QModelIndex&);
    void addTimerActivatedControl(const QModelIndex&);
    void addConfReportControl(const QModelIndex&);
    void addGetCBValues(const QModelIndex&);
    void addConfLogControl(const QModelIndex&);
    void addReportSettings(const QModelIndex&);
    void addLogSettings(const QModelIndex&);
    void addGSESettings(const QModelIndex&);
    void addSMVSettings(const QModelIndex&);
    void addGSEDir(const QModelIndex&);
    void addGOOSE(const QModelIndex&);
    void addGSSE(const QModelIndex&);
    void addFileHandling(const QModelIndex&);
    void addConfLNs(const QModelIndex&);
    void addSGEdit(const QModelIndex&);
    void addConfSG(const QModelIndex&);

    void addServer(const QModelIndex&);
    void addLN(const QModelIndex&);

    void addAuthentication(const QModelIndex&);
    void addLDevice(const QModelIndex&);
    void addAssociation(const QModelIndex&);

    void addLN0(const QModelIndex&);
    void addAccessControl(const QModelIndex&);

    void addGSEControl(const QModelIndex&);
    void addSampleValueControl(const QModelIndex&);
    void addSettingControl(const QModelIndex&);
    void addSCLControl(const QModelIndex&);
    void addLog(const QModelIndex&);

    void addDataSet(const QModelIndex&);
    void addReportControl(const QModelIndex&);
    void addLogControl(const QModelIndex&);
    void addDOI(const QModelIndex&);
    void addInputs(const QModelIndex&);

    void addIEDName(const QModelIndex&);

    void addSmvOpts(const QModelIndex&);

    void addFCDA(const QModelIndex&);

    void addOptFields(const QModelIndex&);
    void addRptEnabled(const QModelIndex&);
    void addTrgOps(const QModelIndex&);

    void addClientLN(const QModelIndex&);

    void addSDI(const QModelIndex&);
    void addDAI(const QModelIndex&);

    void addVal(const QModelIndex&);
    void addValContent(const QModelIndex&);

    void addExtRef(const QModelIndex&);


    void addLNodeType(const QModelIndex&);
    void addDOType(const QModelIndex&);
    void addDAType(const QModelIndex&);
    void addEnumType(const QModelIndex&);

    void addDO(const QModelIndex&);
    void addSDO(const QModelIndex&);
    void addDA(const QModelIndex&);
    void addBDA(const QModelIndex&);
    void addEnumVal(const QModelIndex&);

    void ItemMoveUp(const QModelIndex&);
    void ItemMoveDown(const QModelIndex&);

    void refresh();

    void showPopMenu(const QModelIndex&);

    void showAttributes(const QModelIndex&);
    void hideAttributes(const QModelIndex&);
    void changeAttributes(const QModelIndex&, int, int);

};

#endif // MAINWINDOW_H
