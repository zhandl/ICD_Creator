/**************************************************************************
*/

#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>
#include <QString>
#include <QMap>
#include "global.h"

class LIBQXMLEDITSHARED_EXPORT Config
{

public:

    //general
    static const QString KEY_GENERAL_AUTOSCROLL_ENABLED;
    // element
    static const QString KEY_ELEMENT_FONTFIXEDWIDTHFAMILY;
    static const QString KEY_ELEMENT_FONTFIXEDWIDTHSIZE;
    static const QString KEY_ELEMENT_FONTFIXEDWIDTHENABLED;
    //--
    static const QString KEY_ELEMENT_ELEMENTFONTENABLED;
    static const QString KEY_ELEMENT_ELEMENTFONTFAMILY;
    static const QString KEY_ELEMENT_ELEMENTFONTSIZE;
    static const QString KEY_ELEMENT_ELEMENTFONTITALIC;
    static const QString KEY_ELEMENT_ELEMENTFONTBOLD;
    // mainview
    static const QString  KEY_MAIN_COMPACTVIEW;
    static const QString  KEY_MAIN_ONEATTRLINE;
    static const QString  KEY_MAIN_SHOWATTRLEN;
    static const QString  KEY_MAIN_ATTRFIXEDS;
    static const QString  KEY_MAIN_INDEXPERCHILD;
    static const QString  KEY_MAIN_SHOWBASE64;
    static const QString  KEY_MAIN_SHOWZOOM;
    static const QString  KEY_MAIN_RECENTFILES;
    static const QString  KEY_MAIN_PREFDIRS;
    static const QString  KEY_MAIN_SHOWELTEXTLEN;
    static const QString  KEY_MAIN_SHOWELSIZE;
    // style
    static const QString KEY_VIEW_STYLE;
    //search
    static const QString KEY_SEARCH_CLOSEUNRELATED;
    static const QString KEY_SEARCH_HIGHLIGHALL;
    static const QString KEY_SEARCH_MATCHEXACT;
    static const QString KEY_SEARCH_CASEUNSITIVE;
    static const QString KEY_SEARCH_ONLYCHILDREN;
    static const QString KEY_SEARCH_SEL2BOOKMARK;
    static const QString KEY_SEARCH_FINDTARGET;
    static const QString KEY_SEARCH_SHOWSIZE;
    static const QString KEY_MAIN_HIDEVIEW;
    static const QString KEY_MAIN_EXPANDONLOAD;
    // styles
    static const QString KEY_STYLE_DATADIR;
    static const QString KEY_STYLE_DIRLOCATION;
    static const QString KEY_VIEW_ITEMRENDERERATTR;
    // test (private use)
    static const QString KEY_TEST_BALSAMIQ_INPUT;
    static const QString KEY_TEST_BALSAMIQ_OUTPUT;
    static const QString KEY_TEST_SHOW_XSD_EDITOR;
    static const QString KEY_TEST_SAMPLE_FILE_XSD;
    static const QString SAMPLE_SCHEMA_FILE_READ;
    // balsamiq translaltor
    static const QString KEY_BALSAMIQ_OVERWRITEFILES;
    static const QString KEY_BALSAMIQ_OUTPUTDIR;
    static const QString KEY_BALSAMIQ_INPUTDIR;
    // search in files
    static const QString KEY_SEARCHINFILES_INPUTFILE;
    static const QString KEY_SEARCHINFILES_PATTERN;
    static const QString KEY_SEARCHINFILES_GROUP;
    // schemas
    static const QString KEY_SCHEMA_LAST;
    static const QString KEY_SCHEMA_PREFERITES;
    static const QString KEY_AUTOLOAD_VALIDATION;
    // schema cache
    static const QString KEY_XSDCACHE_ENABLED;
    static const QString KEY_XSDCACHE_LIMIT;
    // extractFragments
    static const QString  KEY_FRAGMENTS_INPUTFILE;
    static const QString  KEY_FRAGMENTS_SPLITPATH;
    static const QString  KEY_FRAGMENTS_EXTRACTIONTYPE;
    static const QString  KEY_FRAGMENTS_MINDOC;
    static const QString  KEY_FRAGMENTS_MAXDOC;
    static const QString  KEY_FRAGMENTS_EXTRACTFOLDER;
    static const QString  KEY_FRAGMENTS_MAKESUBFOLDERS;
    static const QString  KEY_FRAGMENTS_SUBFOLDERSEACH;
    static const QString  KEY_FRAGMENTS_FILESNAMEPATTERN;
    static const QString  KEY_FRAGMENTS_SUBFOLDERSNAMEPATTERN;
    static const QString  KEY_FRAGMENTS_REVERSERANGE;
    static const QString  KEY_FRAGMENTS_ISAFILTER;
    static const QString  KEY_FRAGMENTS_ATTRIBUTENAME;
    static const QString  KEY_FRAGMENTS_COMPARISONTERM;
    static const QString  KEY_FRAGMENTS_COMPARISONTYPE;
    static const QString  KEY_FRAGMENTS_DEPTH;
    static const QString  KEY_FRAGMENTS_SPLITTYPE;

    // welcome dialog
    static const QString  KEY_WELCOMEDIALOG_ENABLED;
    static const QString  KEY_WELCOMEDIALOG_VERSION;

    // sessions
    static const QString KEY_SESSIONS_ENABLED;
    static const QString KEY_SESSIONS_ACTIVECODE;
    static const QString KEY_SESSIONS_ACTIVESTATE;

    //logs
    static const QString KEY_LOGS_ENABLED;
    static const QString KEY_LOGS_LEVEL;

    //-----------------------------------------------------

    static bool getBool(const QString &key, const bool defaultValue);
    static const QString getString(const QString &key, const QString &defaultValue);
    static int getInt(const QString &key, const int defaultValue);

    static bool saveBool(const QString &key, const bool value);
    static bool saveString(const QString &key, const QString &value);
    static bool saveInt(const QString &key, const int value);

    static bool loadStringArray(const QString &keyBase, QStringList &result);
    static bool saveStringArray(const QString &keyBase, QStringList &values);

    static bool loadIntArray(const QString &keyBase, QList<int> &result);
    static bool saveIntArray(const QString &keyBase, QList<int> &values);

    static bool init();
    static bool end();

    static void setBackend(QMap<QString, QVariant> *newBackend);

private:
    Config() {}
    ~Config() {}
};


#endif // CONFIG_H

