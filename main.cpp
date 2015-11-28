#include "mainwindow.h"
#include "icdCreator.h"
#include <QApplication>

//const char *APP_TITLE = QT_TR_NOOP("ICD Creator");

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName(ORGANIZATION_NAME);
    QCoreApplication::setOrganizationDomain(ORGANIZATION_DOMAIN);
    QCoreApplication::setApplicationName(APPLICATION_NAME);

    MainWindow w;
    w.show();

    return a.exec();
}
