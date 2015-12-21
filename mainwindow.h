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
#include "qxmleditdata.h"

class XsdPlugin;

class MainWindow : public QMainWindow
{
    Q_OBJECT    
    bool    started;
    bool    internalStateOk;
    bool    isAutoDelete;

    static int pluginCode;
    QMap<QString, IQXmlEditPlugIn*> _plugins;
    XsdPlugin *_xsdPlugin ;

    QApplication *app;    
    QLabel *labelSchema;
    QXmlEditData *data;

    bool isSlave; // use and forward
    QEventLoop *eventLoop;    
    int maxLastFiles;
    int maxPrefDirs;
    QList<QAction*> lastFiles;
    QList<QAction*> preferredDirs;
    QList<QAction*> pluginsCmds;

    QStringList lastFilesNames;
    QStringList preferredDirsNames;

public:
    MainWindow(const bool setIsSlave, QApplication *newApp, QXmlEditData *data, QWidget *parent = 0);
    ~MainWindow();

    void loadFile(const QString &filePath);

    void openTest();
    void setEventLoop(QEventLoop *eventLoop);
    QString getContentAsText();

    DomModel *getModel();

    void autoLoadValidation();

    void error(const QString &message);
    void warning(const QString &message);
    void message(const QString &message);
    bool askYN(const QString &message);

    QTreeWidget *getMainTreeWidget();
    XmlEditWidget *getEditor();

    virtual QWidget *getMainWidget();
    virtual QString getAppTitle();

private:


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
    QAction *actionConfigure;
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
    QAction *actionNewUsingXMLSchema;
    QAction *actionTransformInComment;
    QAction *actionExtractElementsFromComment;
    QAction *actionInsertNoNamespaceSchemaReferenceAttributes;
    QAction *actionInsertSchemaReferenceAttributes;
    QAction *actionExtractFragmentsFromFile;
    QAction *actionSaveACopyAs;
    QAction *actionHideAllLeafChildren;
    QAction *actionShowAllLeafChildren;
    QAction *actionHideLeafChildren;
    QAction *actionShowLeafChildren;
    QAction *actionViewAsXsd;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionViewData;
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

    //** Add the action
    //** generate the RCD and NET ICD using wizard
    QAction *actionNewRcdICDWizard;
    QAction *actionNewNetICDWizard;

    QStringList lnClass;
    QStringList fcEnum;
    QStringList cdc;
    QStringList BasicType;

    DomModel *model;

    /*Document Variable Declare*/
    QDomDocument *doc;
    QDomElement root;
    QFile *newFile;

    /*UI Function Declare*/
//    void CreateActions();
    void CreateMenus();
    void retranslateUi();

    /*Document Function Declare*/
    void CreateNewICD(QDomDocument*);

signals:
    void actionClick(QDomNode);
    void deleteNode(QModelIndex);

private slots:

    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSaveAs_triggered();
    void on_actionAbout_triggered();
    void on_actionPaste_triggered();
    void on_actionCopy_triggered();
    void on_actionCut_triggered();
    void on_actionExpandAll_triggered();
    void on_actionShowAttrLine_triggered();
    void on_actionAppendComment_triggered();
    void on_actionAddComment_triggered();
    void on_actionAppendProcessingInstruction_triggered();
    void on_actionAddProcessingInstruction_triggered();
    void on_actionResizeToContents_triggered();
    void on_actionAddChildElement_triggered();
    void on_actionAppendChildElement_triggered();
    void on_actionEdit_triggered();
    void on_actionFind_triggered();
    void on_actionDelete_triggered();
    void on_actionMoveUp_triggered();
    void on_actionMoveDown_triggered();
    void on_actionGo_To_Parent_triggered();
    void on_actionGo_to_Previous_Brother_triggered();
    void on_actionGo_to_Next_Brother_triggered();
    void on_actionShowChildIndex_triggered();
    void on_actionCloseThisAllBrothers_triggered();
    void on_actionNewFromClipboard_triggered();
    void on_actionQuit_triggered();
    void on_actionCompactView_triggered();
    void on_actionHideBrothers_triggered();
    void on_actionFixedSizeAttributes_triggered();
    void on_actionShowAttributesLength_triggered();
    void on_actionConfigure_triggered();
    void on_actionZoomIn_triggered();
    void on_actionZoomOut_triggered();
    void on_actionCompare_triggered();
    void on_actionReload_triggered();
    void on_actionCopyPathToClipboard_triggered();
    void on_actionAddCurrentDirectory_triggered();
    void on_actionEditPreferredDirectories_triggered();
    void on_actionValidate_triggered();
    void on_actionValidateFile_triggered();
    void on_actionValidateNewFile_triggered();
    void on_actionInsertSnippet_triggered();
    void on_actionConfigureSnippets_triggered();
    void on_actionExecuteAutoTest_triggered();
    void on_actionTransforminSnippet_triggered();
    void on_actionShowElementTextLength_triggered();
    void on_actionShowElementSize_triggered();
    void on_actionXplore_triggered();
    void on_actionHideView_triggered();
    void on_actionSearchInFiles_triggered();
    void on_actionHelpOnQXmlEdit_triggered();
    void on_actionViewAsXsd_triggered();
    void on_actionAllowedSchemaElements_triggered();
    void on_actionNewUsingXMLSchema_triggered();
    void on_actionTransformInComment_triggered();
    void on_actionExtractElementsFromComment_triggered();
    void on_actionInsertNoNamespaceSchemaReferenceAttributes_triggered();
    void on_actionInsertSchemaReferenceAttributes_triggered();
    void on_actionSaveACopyAs_triggered();
    void on_actionHideLeafChildren_triggered();
    void on_actionHideAllLeafChildren_triggered();
    void on_actionShowLeafChildren_triggered();
    void on_actionShowAllLeafChildren_triggered();

    void on_actionUndo_triggered();
    void on_actionRedo_triggered();

//    void on_actionBase64Tools_triggered();
    void on_actionEncodingTools_triggered();

    void on_actionNewRcdICDWizard_triggered();
    void on_actionNewNetICDWizard_triggered();

    //----- other slots ------------------

    void onDocumentIsModified(const bool isModified);

    void treeContextMenu(const QPoint& position);

    void on_ok_clicked();
    void on_cancel_clicked();

    void onRecentFile();
    void onPreferredDir();
    void onPlugin();
    void schemaLoadComplete(const QString &newLabel);
    void onComputeSelectionState();
    void onNewMessage(const QString &newMessage);
    void setClipBoardActionsState(const bool isAction);
    void onShowStatusMessage(const QString &message, const bool isLongTimeout);
    void onUndoStateUpdated(const bool isUndo, const bool isRedo);

    //------------------- slots

    void autoTest();

    bool finishSetUpUi();
    bool buildPluginsMenu(const char *method, QMenu *parent);

    QString askFileName(const QString &actualName);
    void errorNoRule();

    void setFileTitle();

    void closeEvent(QCloseEvent *event);
    void startUIState();
    void resetTree();
//    void calcColumnState();

    void enableZoom();

    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

//    void computeSelectionState();
    void openFileUsingDialog(const QString folderPath);

    DomItem *getSelectedItem();

    void setDocument(QDomDocument &document, const QString &filePath, const bool isSetState);

    bool checkAbandonChanges();

    QAction *createAnAction(QMenu *menu, const QString &label, const QString &tag, const QString &tooltip);

    void deleteSchema();

    void repaint();
    void display();

    void wheelEvent(QWheelEvent *event);
    bool buildLastObjects(const int maxObjects, QList<QAction*> &cmdList, const char *method, QMenu *parent);
    void updateRecentFilesMenu(const QString &filePath);
    void updatePreferredDirs(QStringList &entries, QList<QAction*>actions);
    void updateMRU(QStringList &entries, const QString &entry, QList<QAction*>actions);
    void updateEntriesMenu(QStringList &entries, QList<QAction*>actions);

    void loadRecentFilesSettings();
    void loadPreferredDirsSettings();

//    void validateWithFile(const QString &filePath);

    void doLoadFileXplore(const QString &filePath);
    void loadFileXplore(const QString &filePath);

    void setDisplayMode(const qxmledit::EDisplayMode value);
//    void doLoadFileBlindMode(QDomDocument &document, const QString &filePath);
//    void loadFileBlindMode(const QString &filePath);

    bool isValidXsd();
    bool verifyAbandonChanges();

    void setSchemaLabel(const QString &newLabel);
    void evaluateSingleItemLeaves(DomItem *item);
    void updateUndoState(const bool isUndo, const bool isRedo);


protected:
    virtual void changeEvent(QEvent *e);
};


void searchInFiles(QWidget * parent);
#endif // MAINWINDOW_H
