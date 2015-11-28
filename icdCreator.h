#ifndef ICDCREATOR_H
#define ICDCREATOR_H

#define DECL_CONSTRUCTOR(clazz) clazz(); virtual ~clazz();
#define IMPL_CONSTRUCTOR(clazz) clazz::clazz() {} \
    clazz::~clazz() {}

// Version numbers are divided like that: 0x0005.02.00

#define VERSION_ID "$VER 0.0.1"
#define VERSION_NUMBER 0x00000100
// this is the version number of the welcome dialog
#define VERSION_NUMBER_WELCOME 0x00010200

#define VERSION_STRING "ICD_Creator " VERSION_ID


//debug switches
//#define _DEBUG_BALSAMIQ
//#define QXML_DEBUG
#define XSD_INTEGRATION

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

extern const char VERSION[] ;

//TODO:
#define ORGANIZATION_NAME   "GDWY"
#define ORGANIZATION_DOMAIN "GDWY"
#define APPLICATION_NAME    "ICD_Creator"


void msgBoxDebug(const QString message);

#ifdef  QXML_DEBUG
#define D(x)    x
#else
#define D(x)
#endif

#define STRINGIZE_(x)    #x
#define STRINGIZE(x)    STRINGIZE_(x)


//-------- logging (enabled by define)----------------
#ifdef LOG_CONSOLE
#include <stdio.h>
#define TRACEQ(x) do{printf("%s\n", x.toAscii().data() ); fflush(stdout);} while(0)
#define TRACE(x) do{printf("%s\n", x); fflush(stdout);} while(0)
#define TRACE2(x, y) do{printf(x, y); fflush(stdout);} while(0)
#else
#define TRACEQ(x)
#define TRACE(x)
#define TRACE2(x, y)
#endif


#endif // ICDCREATOR_H
