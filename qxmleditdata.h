#ifndef QXMLEDITDATA_H
#define QXMLEDITDATA_H

#include <QObject>

#include "global.h"

#include "icdCreator.h"
#include "style.h"
#include "plugin.h"
#include "log.h"

#include <QtNetwork/QNetworkDiskCache>
#include <QtNetwork/QNetworkAccessManager>

#define STYLE_DIR_USESTD "Standard"
#define STYLE_DIR_USEDIR "Directory"
#define STYLE_DIR_USEAPPL "Application"

enum EStylesDir {
    ESTYLE_DIR_USESTD,
    ESTYLE_DIR_USEDIR,
    ESTYLE_DIR_USEAPPL
};

class XsdPlugin;

class LIBQXMLEDITSHARED_EXPORT QXmlEditData : public QObject
{
    Q_OBJECT

    FrwLogger *_logger;

protected:
    QVector<VStyle*> _styles;
    VStyle* _defaultStyle;
    QNetworkAccessManager _networkAccessManager;

    VStyle *creatDefaultStyle();
    bool loadStyles();

public:
    QXmlEditData ();
    virtual ~QXmlEditData();

    virtual void init();
    virtual void end();

    VStyle* getStyle(const QString &tag) const;
    VStyle* defaultStyle() const;
    const QVector<VStyle*> &getStyles() const;

    EStylesDir getStylesDirLocation();
    void setStylesDirLocation(const EStylesDir type);

    QString getStylesDirSpecific();
    QString getStylesDirStandard();
    QString getStylesDirApplication();

    QString snippetsLocalDir();
    QString snippetsProgramDir();
    static QString getResourceDir();
    static QString getDocsDir();

    IQXmlEditPlugIn *xsdPlugin();

    bool isAutovalidationOn();
    void setAutovalidationOn(const bool newState);

    void enableAutoscroll(const bool enabled);
    bool isAutoScroll();


    //--- region(welcomeDialog)
    void enableWelcomeDialog(const bool enabled);
    bool isWelcomeDialogEnabled();
    bool shouldShowWelcomeDialog();
    //--- endregion(welcomeDialog)

    //--- region(log)
    void setLogger(FrwLogger *newLogger);
    FrwLogger *logger();
    //--- end region (log)

    //--- region(xsdCache)
    bool isXsdCacheEnabled();
    void setXsdCacheEnabled(const bool newState);
    int xsdCacheLimit();
    void configureXsdCache();
    //--- endregion(xsdCache)

    QNetworkAccessManager *xsdNetworkAccessManager();

};

#endif // QXMLEDITDATA_H
