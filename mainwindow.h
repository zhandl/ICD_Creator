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
#include <QTextDocument>
#include <QTextBrowser>
#include <QSplitter>
#include <QTextStream>
#include <QtXml>
#include <QSyntaxHighlighter>

#include "dommodel.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    DomModel *model;
    QMenu *fileMenu;
    QTreeView *view;

    /*UI Variable Declare*/
    QMenuBar *qMenuBar;
    QMenu *qFileMenu;
    QAction *qFileNew;
    QAction *qFileOpen;
    QAction *qFileClose;

    QAction *qAddHistory;

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
//    QDomDocument *doc;
    QDomElement root;
    QFile *newFile;


    /*UI Function Declare*/
    void CreateActions();
    void CreateMenus();

    /*Document Function Declare*/
    void CreateNewICD(QDomDocument*);

private slots:
    void fileNewAct();
    void fileOpenAct();
    void addHistoryAct();

    void showPopMenu(QPoint cp);

};

#endif // MAINWINDOW_H
