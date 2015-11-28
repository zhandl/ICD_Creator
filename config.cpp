/**************************************************************************
 *  This file is part of QXmlEdit                                         *
 *  Copyright (C) 2011 by Luca Bellonda and individual contributors       *
 *    as indicated in the AUTHORS file                                    *
 *  lbellonda _at_ gmail.com                                              *
 *                                                                        *
 * This library is free software; you can redistribute it and/or          *
 * modify it under the terms of the GNU Library General Public            *
 * License as published by the Free Software Foundation; either           *
 * version 2 of the License, or (at your option) any later version.       *
 *                                                                        *
 * This library is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU      *
 * Library General Public License for more details.                       *
 *                                                                        *
 * You should have received a copy of the GNU Library General Public      *
 * License along with this library; if not, write to the                  *
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,       *
 * Boston, MA  02110-1301  USA                                            *
 **************************************************************************/

#include <QtGui>
#include "utils.h"
#include "config.h"
#include <QSettings>


//general
const QString Config::KEY_GENERAL_AUTOSCROLL_ENABLED("generalConfiguration/autoScrollEnabled");
// element
const QString Config::KEY_ELEMENT_FONTFIXEDWIDTHFAMILY("element/fontFidexWidthFamily");
const QString Config::KEY_ELEMENT_FONTFIXEDWIDTHSIZE("element/fontFidexWidthSize");
const QString Config::KEY_ELEMENT_FONTFIXEDWIDTHENABLED("element/fontFixedWidthEnabled");

const QString Config::KEY_ELEMENT_ELEMENTFONTENABLED("element/elementFontEnabled");
const QString Config::KEY_ELEMENT_ELEMENTFONTFAMILY("element/elementFontFamily");
const QString Config::KEY_ELEMENT_ELEMENTFONTSIZE("element/elementFontSize");
const QString Config::KEY_ELEMENT_ELEMENTFONTITALIC("element/elementFontItalic");
const QString Config::KEY_ELEMENT_ELEMENTFONTBOLD("element/elementFontBold");

// mainview
const QString Config::KEY_MAIN_COMPACTVIEW("main/compactView");
const QString Config::KEY_MAIN_ONEATTRLINE("main/oneAttrPerLine");
const QString Config::KEY_MAIN_SHOWATTRLEN("main/showAttrLen");
const QString Config::KEY_MAIN_ATTRFIXEDS("main/attrFixedFonts");
const QString Config::KEY_MAIN_INDEXPERCHILD("main/indexPerChild");
const QString Config::KEY_MAIN_SHOWBASE64("main/showBase64");
const QString Config::KEY_MAIN_SHOWZOOM("main/zoom");
const QString Config::KEY_MAIN_RECENTFILES("main/recentFiles");
const QString Config::KEY_MAIN_PREFDIRS("main/preferredDirs");
const QString Config::KEY_MAIN_SHOWELTEXTLEN("main/showElementTextLen");
const QString Config::KEY_MAIN_SHOWELSIZE("main/showElementSize");
const QString Config::KEY_MAIN_HIDEVIEW("main/hideView");
const QString Config::KEY_MAIN_EXPANDONLOAD("main/expandOnLoad");
// style
const QString Config::KEY_VIEW_STYLE("view/styleSelected");
const QString Config::KEY_VIEW_ITEMRENDERERATTR("view/itemRendererAttr");
// test (private use)
const QString Config::KEY_TEST_BALSAMIQ_INPUT("test/balsamiqInput");
const QString Config::KEY_TEST_BALSAMIQ_OUTPUT("test/balsamiqOutput");
const QString Config::KEY_TEST_SHOW_XSD_EDITOR("test/showXsdEditor");
const QString Config::KEY_TEST_SAMPLE_FILE_XSD("test/xsdFileSample");
const QString Config::SAMPLE_SCHEMA_FILE_READ("test/xsdFileMainTest");
// search
const QString Config::KEY_SEARCH_CLOSEUNRELATED("search/closeUnrelated");
const QString Config::KEY_SEARCH_HIGHLIGHALL("search/hiliteAll");
const QString Config::KEY_SEARCH_MATCHEXACT("search/matchExact");
const QString Config::KEY_SEARCH_CASEUNSITIVE("search/caseSensitive");
const QString Config::KEY_SEARCH_ONLYCHILDREN("search/onlyChildren");
const QString Config::KEY_SEARCH_SEL2BOOKMARK("search/selToBoorkmark");
const QString Config::KEY_SEARCH_FINDTARGET("search/findTarget");
const QString Config::KEY_SEARCH_SHOWSIZE("search/showSize");
//
const QString Config::KEY_STYLE_DATADIR("styles/dataDir");
const QString Config::KEY_STYLE_DIRLOCATION("styles/choicer");
// balsamiq translaltor
const QString Config::KEY_BALSAMIQ_OVERWRITEFILES("balsamiq/overwriteFiles");
const QString Config::KEY_BALSAMIQ_OUTPUTDIR("balsamiq/outputDir");
const QString Config::KEY_BALSAMIQ_INPUTDIR("balsamiq/inputDir");
// search in files
const QString Config::KEY_SEARCHINFILES_INPUTFILE("searchinFiles/inputFile");
const QString Config::KEY_SEARCHINFILES_PATTERN("searchinFiles/pattern");
const QString Config::KEY_SEARCHINFILES_GROUP("searchinFiles/group");
// schemas
const QString Config::KEY_SCHEMA_LAST("schemas/last");
const QString Config::KEY_SCHEMA_PREFERITES("schemas/favorites");
const QString Config::KEY_AUTOLOAD_VALIDATION("schemas/autoloadValidation");
// schema cache
const QString Config::KEY_XSDCACHE_ENABLED("xsdcache/enabled");
const QString Config::KEY_XSDCACHE_LIMIT("xsdcache/limit");
// extractFragments
const QString Config::KEY_FRAGMENTS_INPUTFILE("extractFragments/inputFile");
const QString Config::KEY_FRAGMENTS_SPLITPATH("extractFragments/splitPath");
const QString Config::KEY_FRAGMENTS_EXTRACTIONTYPE("extractFragments/extractionType");
const QString Config::KEY_FRAGMENTS_MINDOC("extractFragments/minDoc");
const QString Config::KEY_FRAGMENTS_MAXDOC("extractFragments/maxDoc");
const QString Config::KEY_FRAGMENTS_EXTRACTFOLDER("extractFragments/extractFolder");
const QString Config::KEY_FRAGMENTS_MAKESUBFOLDERS("extractFragments/makeSubfolders");
const QString Config::KEY_FRAGMENTS_SUBFOLDERSEACH("extractFragments/subFoldersEach");
const QString Config::KEY_FRAGMENTS_FILESNAMEPATTERN("extractFragments/filenamesPattern");
const QString Config::KEY_FRAGMENTS_SUBFOLDERSNAMEPATTERN("extractFragments/subFoldersNamePattern");
const QString Config::KEY_FRAGMENTS_REVERSERANGE("extractFragments/reverseRange");
const QString Config::KEY_FRAGMENTS_ISAFILTER("extractFragments/isAFilter");
const QString Config::KEY_FRAGMENTS_ATTRIBUTENAME("extractFragments/attributeName");
const QString Config::KEY_FRAGMENTS_COMPARISONTERM("extractFragments/comparisonTerm");
const QString Config::KEY_FRAGMENTS_COMPARISONTYPE("extractFragments/comparisonType");
const QString Config::KEY_FRAGMENTS_DEPTH("extractFragments/depth");
const QString Config::KEY_FRAGMENTS_SPLITTYPE("extractFragments/splitType");

// welcome dialog
const QString Config::KEY_WELCOMEDIALOG_ENABLED("welcomeDialog/enabled");
const QString Config::KEY_WELCOMEDIALOG_VERSION("welcomeDialog/version");

// sessions
const QString Config::KEY_SESSIONS_ENABLED("sessions/sessionsEnabled");
const QString Config::KEY_SESSIONS_ACTIVECODE("sessions/activeSessionCode");
const QString Config::KEY_SESSIONS_ACTIVESTATE("sessions/activeState");
//const QString Config::KEY_SESSIONS_DBCONFIG("sessions/dbConfig");

//logs
const QString Config::KEY_LOGS_ENABLED("logs/enabled");
const QString Config::KEY_LOGS_LEVEL("logs/level");

static QSettings *config = NULL ;

static QMap<QString, QVariant> *theBackend = NULL ;

bool Config::init()
{
    if(NULL == config) {
        config = new QSettings();
    }
    if(NULL != config) {
        return true ;
    }
    return false;
}

bool Config::end()
{
    bool isOK = true;
    if(NULL != config) {
        isOK = false ;
        config->sync();
        if(config->status() == QSettings::NoError) {
            isOK = true ;
        }
        delete config;
        config = NULL;
    }
    return isOK;
}

void Config::setBackend(QMap<QString, QVariant> *newBackend)
{
    theBackend = newBackend ;
    end();
}

bool Config::getBool(const QString &key, const bool defaultValue)
{
    if(NULL != theBackend) {
        if(!theBackend->contains(key)) {
            return defaultValue ;
        }
        return theBackend->value(key).toBool();
    }
    if(NULL != config) {
        return config->value(key, defaultValue).toBool();
    }
    return defaultValue ;
}

const QString Config::getString(const QString &key, const QString &defaultValue)
{
    if(NULL != theBackend) {
        if(!theBackend->contains(key)) {
            return defaultValue ;
        }
        return theBackend->value(key).toString();
    }
    if(NULL != config) {
        QVariant result = config->value(key, defaultValue);
        QString value = result.toString();
        return value ;
    }
    return defaultValue ;
}

int Config::getInt(const QString &key, const int defaultValue)
{
    if(NULL != theBackend) {
        if(!theBackend->contains(key)) {
            return defaultValue ;
        }
        return theBackend->value(key).toInt();
    }
    if(NULL != config) {
        QVariant result = config->value(key, defaultValue);
        int value = result.toInt();
        return value ;
    }
    return defaultValue ;
}

bool Config::saveBool(const QString &key, const bool value)
{
    if(NULL != theBackend) {
        theBackend->insert(key, QVariant(value));
        return true ;
    }
    if(NULL != config) {
        config->setValue(key, value);
        return true;
    }
    return false ;
}

bool Config::saveString(const QString &key, const QString &value)
{
    if(NULL != theBackend) {
        theBackend->insert(key, QVariant(value));
        return true ;
    }
    if(NULL != config) {
        config->setValue(key, value);
        return true ;
    }
    return false ;
}

bool Config::saveInt(const QString &key, const int value)
{
    if(NULL != theBackend) {
        theBackend->insert(key, QVariant(value));
        return true ;
    }
    if(NULL != config) {
        config->setValue(key, value);
        return true ;
    }
    return false ;
}

bool Config::loadStringArray(const QString &keyBase, QStringList &result)
{
    int numValues = getInt(QString("%1_num").arg(keyBase), 0);
    for(int i = 0 ; i < numValues ; i ++) {
        QString key = QString("%1_%2").arg(keyBase).arg(i);
        QString value = getString(key, "");
        result.append(value);
    }
    return true;
}

bool Config::saveStringArray(const QString &keyBase, QStringList &values)
{
    bool isOk = true;
    int numValues = values.size() ;
    if(!saveInt(QString("%1_num").arg(keyBase), numValues)) {
        isOk  = false ;
    }
    for(int i = 0 ; i < numValues ; i ++) {
        QString key = QString("%1_%2").arg(keyBase).arg(i);
        if(! saveString(key, values.at(i))) {
            isOk = false;
        }
    }
    return isOk;
}

bool Config::saveIntArray(const QString &keyBase, QList<int> &values)
{
    bool isOk = true;
    int numValues = values.size() ;
    if(!saveInt(QString("%1_num").arg(keyBase), numValues)) {
        isOk  = false ;
    }
    for(int i = 0 ; i < numValues ; i ++) {
        QString key = QString("%1_%2").arg(keyBase).arg(i);
        if(! saveInt(key, values.at(i))) {
            isOk = false;
        }
    }
    return isOk;
}

bool Config::loadIntArray(const QString &keyBase, QList<int> &result)
{
    int numValues = getInt(QString("%1_num").arg(keyBase), 0);
    for(int i = 0 ; i < numValues ; i ++) {
        QString key = QString("%1_%2").arg(keyBase).arg(i);
        int value = getInt(key, 0);
        result.append(value);
    }
    return true;
}
