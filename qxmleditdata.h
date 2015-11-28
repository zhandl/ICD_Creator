#ifndef QXMLEDITDATA_H
#define QXMLEDITDATA_H

#include <QObject>

#include "global.h"

//#include "xmlEdit.h"
#include "style.h"
#include "plugin.h"

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

    QNetworkAccessManager *xsdNetworkAccessManager();

};

#endif // QXMLEDITDATA_H
