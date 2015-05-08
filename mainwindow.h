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

#include "dommodel.h"
#include "domitem.h"
#include "qitemaction.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QStringList lnClass;
    QStringList fcEnum;
    QStringList cdc;
    QStringList BasicType;

    DomModel *model;
    QMenu *fileMenu;
    QTreeView *view;

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

    /*Document Function Declare*/
    void CreateNewICD(QDomDocument*);

signals:
    void actionClick(QDomNode);

private slots:
    void fileNewAct();
    void fileOpenAct();
    void fileSaveAct();

    void deleteChildren(DomItem*);

    void deleteItem(QPoint);

    void addHeader(QPoint);
    void addSubstation(QPoint);
    void addCommunication(QPoint);
    void addIED(QPoint);
    void addDataTypeTemplates(QPoint);

//    void addHistoryAct(QDomNode);
    void addHistoryAct(QPoint);
    void addTextAct(QPoint);
    void addTextContentAct(QPoint);
    void addHitemAct(QPoint);

    void addServices(QPoint);
    void addAccessPoint(QPoint);

    void addDynAssociation(QPoint);
    void addSettingGroups(QPoint);
    void addGetDirectory(QPoint);
    void addGetDataObjectDefinition(QPoint);
    void addDataObjectDirectory(QPoint);
    void addGetDataSetValue(QPoint);
    void addSetDataSetValue(QPoint);
    void addDataSetDirectory(QPoint);
    void addConfDataSet(QPoint);
    void addDynDataSet(QPoint);
    void addReadWrite(QPoint);
    void addTimerActivatedControl(QPoint);
    void addConfReportControl(QPoint);
    void addGetCBValues(QPoint);
    void addConfLogControl(QPoint);
    void addReportSettings(QPoint);
    void addLogSettings(QPoint);
    void addGSESettings(QPoint);
    void addSMVSettings(QPoint);
    void addGSEDir(QPoint);
    void addGOOSE(QPoint);
    void addGSSE(QPoint);
    void addFileHandling(QPoint);
    void addConfLNs(QPoint);
    void addSGEdit(QPoint);
    void addConfSG(QPoint);

    void addServer(QPoint);
    void addLN(QPoint);

    void addAuthentication(QPoint);
    void addLDevice(QPoint);
    void addAssociation(QPoint);

    void addLN0(QPoint);
    void addAccessControl(QPoint);

    void addGSEControl(QPoint);
    void addSampleValueControl(QPoint);
    void addSettingControl(QPoint);
    void addSCLControl(QPoint);
    void addLog(QPoint);

    void addDataSet(QPoint);
    void addReportControl(QPoint);
    void addLogControl(QPoint);
    void addDOI(QPoint);
    void addInputs(QPoint);

    void addIEDName(QPoint);

    void addSmvOpts(QPoint);

    void addFCDA(QPoint);

    void addOptFields(QPoint);
    void addRptEnabled(QPoint);
    void addTrgOps(QPoint);

    void addClientLN(QPoint);

    void addSDI(QPoint);
    void addDAI(QPoint);

    void addVal(QPoint);
    void addValContent(QPoint);

    void addExtRef(QPoint);


    void addLNodeType(QPoint);
    void addDOType(QPoint);
    void addDAType(QPoint);
    void addEnumType(QPoint);

    void addDO(QPoint);
    void addSDO(QPoint);
    void addDA(QPoint);
    void addBDA(QPoint);
    void addEnumVal(QPoint);

    void refresh();


    void showPopMenu(QPoint cp);

};

#endif // MAINWINDOW_H
