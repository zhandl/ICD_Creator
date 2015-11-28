#include "qxmleditdata.h"

#include <QDesktopServices>
#include <QDir>
#include "config.h"
#include "utils.h"
#include "stylepersistence.h"
//#include "balsamiqsrc/balsamiqplugin.h"
#include "xsdeditor/xsdplugin.h"

QXmlEditData::QXmlEditData()
{
   _defaultStyle = NULL;
   init();
}

QXmlEditData::~QXmlEditData()
{
    foreach(VStyle *style, _styles) {
        delete style;
    }
}

VStyle* QXmlEditData::defaultStyle() const
{
    return _defaultStyle;
}

VStyle* QXmlEditData::getStyle(const QString &tag) const
{
    if((NULL == tag) || (tag.length() == 0)) {
        return NULL;
    }
    foreach(VStyle *style, _styles) {
        if(style->name() == tag) {
            return style;
        }
    }
    return NULL;
}

VStyle *QXmlEditData::creatDefaultStyle()
{
    VStyle *defaultStyle = new VStyle(QString("predefined"), QString("this is the predefined style"));
    defaultStyle->addId("name", true);
    defaultStyle->addId("id", false);
    defaultStyle->addId("build", false);
    StyleEntry *entry1 = new StyleEntry("1");
    entry1->setColor("FF0000");
    StyleEntry *entry2 = new StyleEntry("2");
    entry2->setColor("4040FF");
    StyleEntry *entry3 = new StyleEntry("3");
    entry3->setColor("40E040");
    defaultStyle->addEntry(entry1);
    defaultStyle->addEntry(entry2);
    defaultStyle->addEntry(entry3);
    TokenEntry *tk1 = new TokenEntry("class", entry1);
    TokenEntry *tk2 = new TokenEntry("item", entry2);
    TokenEntry *tk3 = new TokenEntry("widget", entry1);
    TokenEntry *tk4 = new TokenEntry("action", entry3);
    defaultStyle->addToken(tk1);
    defaultStyle->addToken(tk2);
    defaultStyle->addToken(tk3);
    defaultStyle->addToken(tk4);

    _styles.append(defaultStyle);
    return defaultStyle;
}

void QXmlEditData::init()
{
    if(NULL == _defaultStyle) {
        _defaultStyle = creatDefaultStyle();
        if(!loadStyles()) {
            Utils::error(tr("Error loading styles"));
        }
    }
}

void QXmlEditData::end()
{
}

const QVector<VStyle*> &QXmlEditData::getStyles() const
{
    return _styles;
}

EStylesDir QXmlEditData::getStylesDirLocation()
{
    QString setting = Config::getString(Config::KEY_STYLE_DIRLOCATION, STYLE_DIR_USESTD);
    if(setting == STYLE_DIR_USEDIR) {
        return ESTYLE_DIR_USEDIR;
    }
    if(setting == STYLE_DIR_USEAPPL) {
        return ESTYLE_DIR_USEAPPL;
    }
    return ESTYLE_DIR_USESTD;
}

void QXmlEditData::setStylesDirLocation(const EStylesDir type)
{
    switch(type) {
    case ESTYLE_DIR_USEAPPL:
        Config::saveString(Config::KEY_STYLE_DIRLOCATION, STYLE_DIR_USEAPPL);
        break;
    case ESTYLE_DIR_USEDIR:
        Config::saveString(Config::KEY_STYLE_DIRLOCATION, STYLE_DIR_USEDIR);
        break;
    default:
        Config::saveString(Config::KEY_STYLE_DIRLOCATION, STYLE_DIR_USESTD);
        break;
    }
}

QString QXmlEditData::getStylesDirSpecific()
{
    return Config::getString(Config::KEY_STYLE_DATADIR, "");
}

QString QXmlEditData::getStylesDirStandard()
{
    return QDesktopServices::storageLocation(QDesktopServices::DataLocation);
}

QString QXmlEditData::getStylesDirApplication()
{
    QString toReturn = getResourceDir();
    return toReturn;
}

bool QXmlEditData::loadStyles()
{
    EStylesDir type = getStylesDirLocation();
    QString stylesDirectory;
    switch(type) {
    case ESTYLE_DIR_USEAPPL:
        stylesDirectory = getStylesDirApplication();
        break;
    case ESTYLE_DIR_USEDIR:
        stylesDirectory = getStylesDirSpecific();
        break;
    default:
        stylesDirectory = getStylesDirStandard();
        break;
    }
    StylePersistence persistence;
    return persistence.scanDirectory(stylesDirectory, &_styles);
}

QString QXmlEditData::snippetsLocalDir()
{
    return QDesktopServices::storageLocation(QDesktopServices::DataLocation);
}

QString QXmlEditData::snippetsProgramDir()
{
    QString toReturn = getResourceDir() + QDir::separator() + "snippets";
    return toReturn;
}

QString QXmlEditData::getResourceDir()
{
#ifdef Q_WS_MAC
    QString toReturn;
    toReturn = QApplication::applicationDirPath() + QDir::separator() + ".." + QDir::separator() + "SharedSupport" ;
    return toReturn;
#else

#ifdef UNIX_RESOURCES
    QString toReturn = QString(STRINGIZE(UNIX_DOC_PATH));
    return toReturn;
#else

    return QApplication::applicationDirPath();
#endif

#endif
}

bool QXmlEditData::isAutovalidationOn()
{
    return Config::getBool(Config::KEY_AUTOLOAD_VALIDATION, false);
}

void QXmlEditData::setAutovalidationOn(const bool newState)
{
    Config::saveBool(Config::KEY_AUTOLOAD_VALIDATION, newState);
}

void QXmlEditData::enableAutoscroll(const bool enabled)
{
    Config::saveBool(Config::KEY_GENERAL_AUTOSCROLL_ENABLED, enabled);
}

bool QXmlEditData::isAutoScroll()
{
    return Config::getBool(Config::KEY_GENERAL_AUTOSCROLL_ENABLED, true);
}

QNetworkAccessManager *QXmlEditData::xsdNetworkAccessManager()
{
    return &_networkAccessManager;
}
