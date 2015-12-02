#include "mainwindow.h"
#include "icdCreator.h"
#include <QApplication>

#include "config.h"
#include "utils.h"
#include "global.h"

#include "StartParams.h"
#include "services/loghandler.h"

#if !defined(QXMLEDIT_NOMAIN)

const char *APP_TITLE = QT_TR_NOOP("ICD Creator");

#define QXMLEDIT_TRANSLATIONS_PREFIX "ICD_Creator_"
#define QXMLEDITWIDGET_TRANSLATIONS_PREFIX  "ICD_Creator_Widget_"

static bool decodeCommandLine(QApplication &app, StartParams *params);
static void startTanslator(QApplication *app);
static void initLogger();

static QTranslator qtLibTranslator;
static QTranslator qIcdCreatorTranslator;
static QTranslator qIcdCreatorWidgetTranslator;

static LogHandler logHandler;
static StartParams startParams ;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Q_INIT_RESOURCE(risorse);


    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    QCoreApplication::setOrganizationName(ORGANIZATION_NAME);
    QCoreApplication::setOrganizationDomain(ORGANIZATION_DOMAIN);
    QCoreApplication::setApplicationName(APPLICATION_NAME);
    QXmlEditGlobals::setAppTitle(APP_TITLE);

    qInstallMsgHandler(LogHandler::msgHandler);

    if(!Config::init()) {
        Utils::errorReadingUserSettings();
    }

    QXmlEditData appData;
    appData.setLogger(&logHandler);
    initLogger();
    appData.init();
    startTanslator(&a);

    DomItem::loadIcons();
    a.setWindowIcon(QIcon(":/tree/icon.png"));

    decodeCommandLine(a, &startParams);
    MainWindow w(false, &a, &appData);
    w.showMaximized();

    int result = a.exec();
    appData.end();

    if(!Config::end()) {
        Utils::errorSavingUserSettings();
    }

    return result;
}

static void initLogger()
{
    bool isEnabled = Config::getBool(Config::KEY_LOGS_ENABLED, false);
    int logLevel = Config::getInt(Config::KEY_LOGS_LEVEL, FrwLogger::INFO);
    logHandler.setLevel((FrwLogger::ELogLevel)logLevel);
    logHandler.setEnabled(isEnabled);
}

static bool decodeCommandLine(QApplication &app, StartParams *params)
{
    QStringList args = app.arguments();
    if(args.size() > 1) {
        QString arg1 = args.at(1);

        if(arg1 == QString("-vis")) {
            if(args.size() > 2) {
                params->fileName = args.at(2);
                if(!params->fileName.isEmpty()) {
                    params->type = StartParams::VisFile ;
                    return true;
                } else {
                    params->parametersError = true ;
                }
            }
        } else {
            params->fileName = args.at(1);
            if(!params->fileName.isEmpty()) {
                params->type = StartParams::OpenFile ;
                return true;
            } else {
                params->parametersError = true ;
            }
        }
    }
    return false;
}

void msgBoxDebug(const QString message)
{
    QMessageBox msgBox;
    msgBox.setText(message);
    msgBox.exec();
}


static void startTanslator(QApplication *app)
{
    if(qtLibTranslator.load("qt_" + QLocale::system().name(),
                            QLibraryInfo::location(QLibraryInfo::TranslationsPath))) {
        app->installTranslator(&qtLibTranslator);
    }
    if(qIcdCreatorTranslator.load(QXMLEDIT_TRANSLATIONS_PREFIX + QLocale::system().name(), QXmlEditData::getResourceDir() + QString("/") + QString(STRINGIZE(TRANLASTION_DIR)))) {
        app->installTranslator(&qIcdCreatorTranslator);
    }
    if(qIcdCreatorWidgetTranslator.load(QXMLEDITWIDGET_TRANSLATIONS_PREFIX + QLocale::system().name(), QXmlEditData::getResourceDir() + QString("/") + QString(STRINGIZE(TRANLASTION_DIR)))) {
        app->installTranslator(&qIcdCreatorWidgetTranslator);
    }
}

#endif
