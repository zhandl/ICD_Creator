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

#include "xschemaloader.h"
#include <QDir>
#include "utils.h"
#include <QDebug>

XSchemaLoader::XSchemaLoader(XSchemaLoader *parentLoader, SchemaLoaderSpec *newSpec, QObject *parent) :
    QObject(parent)
{
    _spec = newSpec ;
    _root = NULL ;
    _current = NULL ;
    _networkAccessManager = NULL ;
    _mainLoader = (NULL == parentLoader) ? this : parentLoader->_mainLoader ;
    _parentLoader = parentLoader;
    _isError = false;
}


XSchemaLoader::~XSchemaLoader()
{
    if(NULL != _spec) {
        delete _spec;
        _spec = NULL ;
    }
}

void XSchemaLoader::setError(const QString &error)
{
    _isError = true ;
    _errorMessage = error ;
}

bool XSchemaLoader::hasProtocol(const QString& url)
{
    QUrl theUrl(url);
    qDebug()<<theUrl.scheme();
    if(!theUrl.scheme().isEmpty()) {
//    if(!theUrl.isRelative()) {
        return true ;
    }
    return false;
}

bool XSchemaLoader::readFromURL(XSDSchema *root, const QString &inputUrl, QNetworkAccessManager *networkAccessManager, const QString &paramFolderPath)
{
    _folderPath = paramFolderPath;
    _networkAccessManager = networkAccessManager ;
    _mainLoader->_loadedSchemasBySchemaLocation.insert(inputUrl, root);
    QUrl url = QUrl::fromUserInput(inputUrl);
    if(url.isLocalFile()) {
        handleFileAccess(inputUrl);
        return true;
    }
    connect(networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onNetworkAccessFinished(QNetworkReply*)));
    networkAccessManager->get(QNetworkRequest(url));
    return true ;
}

void XSchemaLoader::onNetworkAccessFinished(QNetworkReply* reply)
{
    bool isComplete  = false ;
    _current = internalSchemaLoader(reply);
    if(!_isError) {
        SchemaLoaderSpec *loaderSpec = checkIfComplete();
        if(NULL != loaderSpec) {
            newReading(loaderSpec);
        } else {
            isComplete = true ;
        }
    }
    if(isComplete || _isError) {
        emit loadComplete(this, _current, _isError);
    }
}

void XSchemaLoader::onFileAccessFinished(QFile* inputFile)
{
    bool isComplete  = false ;
    _current = internalSchemaLoader(inputFile);
    if(!_isError) {
        SchemaLoaderSpec *loaderSpec = checkIfComplete();
        if(NULL != loaderSpec) {
            newReading(loaderSpec);
        } else {
            isComplete = true ;
        }
    }
    if(isComplete || _isError) {
        emit loadComplete(this, _current, _isError);
    }
}

void XSchemaLoader::onLoadCompleteDependent(XSchemaLoader *loader, XSDSchema *child, const bool isError)
{
    handleInputSchema(loader, child, isError);
    bool isComplete  = false ;
    if(!_isError) {
        SchemaLoaderSpec *loaderSpec = checkIfComplete();
        if(NULL == loaderSpec) {
            isComplete = true ; // or isError
        } else {
            newReading(loaderSpec);
        }
    }
    disconnect(loader, SIGNAL(loadComplete(XSchemaLoader*, XSDSchema*, const bool)), this, SLOT(onLoadCompleteDependent(XSchemaLoader*, XSDSchema*, const bool)));
    delete loader ;
    if(isComplete || _isError) {
        emit loadComplete(this, _current, isError);
    }
}

void XSchemaLoader::handleInputSchema(XSchemaLoader *loader, XSDSchema *child, const bool isError)
{
    if(!isError) {
        addSchemaToParent(child, loader->_spec);
    } else {
        setError(loader->_errorMessage);
        if(NULL != child) {
            delete child;
        }
    }
}

bool XSchemaLoader::newReading(SchemaLoaderSpec *loaderSpec)
{
    XSchemaLoader * newLoader = new XSchemaLoader(this, loaderSpec);
    if(NULL != newLoader) {
        connect(newLoader, SIGNAL(loadComplete(XSchemaLoader*, XSDSchema*, const bool)), this, SLOT(onLoadCompleteDependent(XSchemaLoader*, XSDSchema*, const bool)));
        newLoader->readFromURL(_current, loaderSpec->url, _networkAccessManager, _folderPath);
        return true;
    } else {
        delete loaderSpec ;
        setError(tr("Cannot allocate schema loader."));
        return false;
    }
}

void XSchemaLoader::addSchemaToParent(XSDSchema *schema, SchemaLoaderSpec *loaderSpec)
{
    if(NULL != loaderSpec) {
        loaderSpec->useSchema(_current, schema);
    } else {
        setError(tr("Invalid state 0100"));
    }
}


/*----------------------------------------------
Algorithm:
load a schema (starting from root)
 for each instruction
    check if schema already loaded.
    load a parser, then load Schema
    add schema to parent
----------------------------------------------------*/
/*
bool XSchemaLoader::readFromURL( XSDSchema *root, const QString &inputUrl, QNetworkAccessManager *networkAccessManager)
{
    _root = root ;
    _current = root ;
    _networkAccessManager = networkAccessManager ;
    _mainLoader->_loadedSchemas.insert(inputUrl, root);
    connect(networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onNetworkAccessFinished(QNetworkReply*)));
    QUrl url = QUrl::fromUserInput(inputUrl);
    // trace( QString("schema loading url: %1" ).arg(url.toString()) );
    networkAccessManager->get(QNetworkRequest(url));
    return true ;
}

void XSchemaLoader::onNetworkAccessFinishedMainSchema(QNetworkReply* reply)
{
    bool isComplete  = false ;
    XSDSchema *schema = internalSchemaLoader(reply);
    if(!_isError) {
        _current = schema ;
        examineDependentSchemas();
        isComplete = checkIfComplete();
        SchemaLoaderSpec *loaderSpec = getLoaderSpec();
        if( NULL == loaderSpec ) {
            isError = true ;
        } else {
            XSchemaLoader * newLoader = new XSchemaLoader(this, loaderSpec );
            if(NULL != newLoader ) {
                this->connect( newLoader, loadComplete, onLoadCompleteDependent );
                newLoader->readFromURLDependency( _current, inputUrl, _networkAccessManager);
            }
        }
    }
    if(isComplete) {
        emit loadComplete(this, isError);
    }
}

void XSchemaLoader::onLoadCompleteDependent(QNetworkReply* reply)
{
    bool isComplete  = false ;
    XSDSchema *schema = internalSchemaLoader(reply);
    if(!_isError) {
        _current = schema ;
        examineDependentSchemas();
        isComplete = checkIfComplete();
        SchemaLoaderSpec *loaderSpec = getLoaderSpec();
        switch( spec ) {
        case ELS_Include:
            _main.addInclude(schema);
            break;
        case ELS_Import:
            _main.addImport(schema);
            break;
        case ELS_Redefine:
            _main.addRedefine(schema);
            break;
        default:
            setError(tr("Unknown scheam relation: %1").arg(spec));
            break;
        }
        if( NULL == loaderSpec ) {
            isError = true ;
        } else {
            XSchemaLoader * newLoader = new XSchemaLoader(this, loaderSpec );
            if(NULL != newLoader ) {
                this->connect( newLoader, loadComplete, loadCompleteDependent );
                newLoader->readFromURL( _current, inputUrl, _networkAccessManager);
            }
        }
    }
    if(isComplete) {
        emit loadComplete(this, isError);
    }
}

bool XSchemaLoader::readFromURLDependency( XSDSchema *schema, const QString &inputUrl)
{
    _loadedSchemas.insert(inputUrl, schema);
    QUrl url = QUrl::fromUserInput(inputUrl);
    // trace( QString("schema loading url: %1" ).arg(url.toString()) );
    connect(_networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onNetworkAccessFinishedDependendency(QNetworkReply*)));
    _networkAccessManager->get(QNetworkRequest(url));
    return true ;
}
*/
/*
    if(NULL != _networkAccessManager) {
        disconnect(_networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onNetworkAccessFinished(QNetworkReply*)));
        _networkAccessManager = NULL ;
    }
    // trace( QString("schema loading error: %1" ).arg(reply->error() );
    if(reply->error() == QNetworkReply::NoError) {
        XSDSchema *schema = new XSDSchema();
        if( NULL == schema ) {
            isError = true ;
        }
        if( ! isError ) {
            if(schema->readFromIoDevice(reply)) {
                isError = false ;
            }
        }
        reply->close();
    }
    if(isError) {
        Utils::error(tr("Failed to load XML Schema, error is:'%1'").arg(reply->errorString()));
    } else {
        if( _current != _root ) {
            _root->addSchema(_current);
        }
        // examine queue for further schema loading
        s
        // avoid circular references
        ssss
    }
    if(NULL != _networkAccessManager) {
        disconnect(_networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onNetworkAccessFinished(QNetworkReply*)));
        _networkAccessManager = NULL ;
    }
    reply->deleteLater();
    if complete
    emit loadComplete(this, isError);
}
*/

XSDSchema *XSchemaLoader::internalSchemaLoader(QNetworkReply* reply)
{
    XSDSchema *schema = NULL ;
    if(NULL != _networkAccessManager) {
        disconnect(_networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onNetworkAccessFinished(QNetworkReply*)));
        _networkAccessManager = NULL ;
    }
    // trace( QString("schema loading error: %1" ).arg(reply->error() );
    if(reply->error() == QNetworkReply::NoError) {
        schema = new XSDSchema();
        if(NULL == schema) {
            setError(tr("Unable to allocate a schema"));
        }
        if(!_isError) {
            if(!schema->readFromIoDevice(reply)) {
                setError(tr("Error reading schema data."));
            }
        }
        reply->close();
    } else {
        setError(tr("Failed to load XML Schema, error is:'%1'").arg(reply->errorString()));
        Utils::error(reply->errorString());
    }
    reply->deleteLater();
    return schema ;
}

XSDSchema *XSchemaLoader::internalSchemaLoader(QFile *inputFile)
{
    XSDSchema *schema = NULL ;
    if(inputFile->open(QFile::ReadOnly)) {
        schema = new XSDSchema();
        if(NULL == schema) {
            setError(tr("Unable to allocate a schema"));
        }
        if(!_isError) {
            if(!schema->readFromIoDevice(inputFile)) {
                setError(tr("Error reading schema data."));
            }
        }
        inputFile->close();
        // this segment has some bug.
        // pc can enter the segment when debuging
        // but the if is false(error == NoError)
        // 2015.5.3
        if(inputFile->error() != QFile::NoError) {
            setError(tr("Error accessing file, error is:'%1'").arg(inputFile->errorString()));
            Utils::error(inputFile->errorString());
            delete schema ;
            schema = NULL ;
        }
    } else {
        setError(tr("Failed to load XML Schema, error is:'%1'").arg(inputFile->errorString()));
        Utils::error(inputFile->errorString());
    }
    return schema ;
}

void XSchemaLoader::handleFileAccess(const QString &schemaUrl)
{
    QFile inputFile;
    QString fileName = _folderPath;
    fileName += QDir::separator();
    fileName += schemaUrl ;
    inputFile.setFileName(fileName);
    if(inputFile.exists()) {
        onFileAccessFinished(&inputFile);
        return ;
    }
    // try it as a absolute path
    fileName = schemaUrl;
    inputFile.setFileName(fileName);
    if(inputFile.exists()) {
        onFileAccessFinished(&inputFile);
        return ;
    }
    // error
    setError(tr("Error accessing schema file"));
    emit loadComplete(this, NULL, true);
}


/*
void XSchemaLoader::onNetworkAccessFinished(QNetworkReply* reply)
{
    bool isError = true ;
    if(NULL != _networkAccessManager) {
        disconnect(_networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onNetworkAccessFinished(QNetworkReply*)));
        _networkAccessManager = NULL ;
    }
    // trace( QString("schema loading error: %1" ).arg(reply->error() );
    if(reply->error() == QNetworkReply::NoError) {
        XSDSchema *schema = new XSDSchema();
        if( NULL == schema ) {
            isError = true ;
        }
        if( ! isError ) {
            if(schema->readFromIoDevice(reply)) {
                isError = false ;
            }
        }
        reply->close();
    }
    if(isError) {
        Utils::error(tr("Failed to load XML Schema, error is:'%1'").arg(reply->errorString()));
    } else {
        if( _current != _root ) {
            _root->addSchema(_current);
        }
        // examine queue for further schema loading
        s
        // avoid circular references
        ssss
    }
    reply->deleteLater();
    if complete
    emit loadComplete(this, isError);
}
*/
/*
bool XSchemaLoader::readFromURL( XSDSchema *root, const QString &inputUrl, QNetworkAccessManager *networkAccessManager)
{
    _root = root ;
    _current = root ;
    _networkAccessManager = networkAccessManager ;
    _loadedSchemas.insert(inputUrl, root);
    add itself to
    connect(networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onNetworkAccessFinished(QNetworkReply*)));
    QUrl url = QUrl::fromUserInput(inputUrl);
    // trace( QString("schema loading url: %1" ).arg(url.toString()) );
    networkAccessManager->get(QNetworkRequest(url));
    return true ;
}

void XSchemaLoader::onNetworkAccessFinished(QNetworkReply* reply)
{
    bool isError = true ;
    if(NULL != _networkAccessManager) {
        disconnect(_networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onNetworkAccessFinished(QNetworkReply*)));
        _networkAccessManager = NULL ;
    }
    // trace( QString("schema loading error: %1" ).arg(reply->error() );
    if(reply->error() == QNetworkReply::NoError) {
        if( NULL == _current ) {
            _current = new XSDSchema();
            if( NULL == _current ) {
                isError = true ;
            }
        }
        if( ! isError ) {
            if(_current->readFromIoDevice(reply)) {
                isError = false ;
            }
        }
        reply->close();
    }
    if(isError) {
        Utils::error(tr("Failed to load XML Schema, error is:'%1'").arg(reply->errorString()));
    } else {
        if( _current != _root ) {
            _root->addSchema(_current);
        }
        // examine queue for further schema loading
        s
        // avoid circular references
        ssss
    }
    reply->deleteLater();
    if complete
    emit loadComplete(this, isError);
}

bool XSchemaLoader::whatNext(XSDSchema *schema)
{
    collectNext(schema);
    _includesQueue.addAll(schema->includes()); // TODO: fare overloaded o altro
    _importQueue.addAll(schema->import());
    _redefineQueue.addAll(schema->redefine());
}

bool XSchemaLoader::collectNext(XSDSchema *schema)
{
    collectQueue(_includesQueue, schema->includesUrlList() ) ;
    collectQueue(_importQueue, schema->importList() );
    collectQueue(_redefineQueue,  schema->redefineList() );
}

bool XSchemaLoader::collectQueue(QStringList &newUrls, QStringList &urls)
{
    foreach( QString newUrl, newUrls ) {
        addItemToQueue(urls, newUrl);
    }
}

bool XSchemaLoader::addItemToQueue(QStringList &urls, const QString &url)
{
    if( _loadedSchemasBySchemaLocation.contains(url) ) {
        return ;
    }
    urls.append(url);
}
*/

/**
  /brief returns NULL iif no items exists or there is an error
 */
SchemaLoaderSpec *XSchemaLoader::checkIfComplete()
{
    SchemaLoaderSpec *spec;
    spec = checkIfCompleteQueue(_includesQueue, &XSchemaLoader::includeLFactory);
    if(NULL != spec) {
        return spec;
    } else {
        if(_isError) {
            return NULL;
        }
    }
    spec = checkIfCompleteQueue(_importQueue, &XSchemaLoader::importLFactory);
    if(NULL != spec) {
        return spec;
    } else {
        if(_isError) {
            return NULL;
        }
    }
    spec = checkIfCompleteQueue(_redefineQueue, &XSchemaLoader::redefineLFactory);
    if(NULL != spec) {
        return spec;
    } else {
        if(_isError) {
            return NULL;
        }
    }
    return NULL ;
}

bool XSchemaLoader::hasUrl(const QString &url)
{
    if(_loadedSchemasBySchemaLocation.contains(url)) {
        return true ;
    }
    return false;
}

SchemaLoaderSpec *XSchemaLoader::checkIfCompleteQueue(QStringList &list, SchemaLoaderSpec * (XSchemaLoader::*specFactory)(const QString &url))
{
    while(!list.isEmpty()) {
        QString url = list.at(0);
        list.removeAt(0);
        if(_mainLoader->hasUrl(url/*dove? include????*/)) {
            continue;
        } else {
            SchemaLoaderSpec *newSpec = (this->*specFactory)(url);
            if(NULL != newSpec) {
                return newSpec ;
            }
            setError(tr("Error loading schema."));
        }
    }
    return NULL ;
}

SchemaLoaderSpec* XSchemaLoader::includeLFactory(const QString &url)
{
    return new IncludeSchemaLoaderSpec(url);
}

SchemaLoaderSpec* XSchemaLoader::importLFactory(const QString &url)
{
    return new ImportSchemaLoaderSpec(url);
}
SchemaLoaderSpec* XSchemaLoader::redefineLFactory(const QString &url)
{
    return new RedefineSchemaLoaderSpec(url);
}

/*
bool XSchemaLoader::readFromURL( XSDSchema *schema, const QString &inputUrl)
{
    _loadedSchemas.insert(inputUrl, schema);
    QUrl url = QUrl::fromUserInput(inputUrl);
    // trace( QString("schema loading url: %1" ).arg(url.toString()) );
    networkAccessManager->get(QNetworkRequest(url));
    return true ;
}

void XSchemaLoader::onNetworkAccessFinished(QNetworkReply* reply)
{
    bool isError = true ;
    if(NULL != _networkAccessManager) {
        disconnect(_networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onNetworkAccessFinished(QNetworkReply*)));
        _networkAccessManager = NULL ;
    }
    // trace( QString("schema loading error: %1" ).arg(reply->error() );
    if(reply->error() == QNetworkReply::NoError) {
        if( NULL == _current ) {
            _current = new XSDSchema();
            if( NULL == _current ) {
                isError = true ;
            }
        }
        if( ! isError ) {
            if(_current->readFromIoDevice(reply)) {
                isError = false ;
            }
        }
        reply->close();
    }
    if(isError) {
        Utils::error(tr("Failed to load XML Schema, error is:'%1'").arg(reply->errorString()));
    } else {
        if( _current != _root ) {
            _root->addSchema(_current);
        }
        // examine queue for further schema loading
        s
        // avoid circular references
        ssss
    }
    reply->deleteLater();
    if complete
    emit loadComplete(this, isError);
}
*/

/*---------------------------------------------------------------*/
SchemaLoaderSpec::SchemaLoaderSpec(const QString &newUrl)
{
    url = newUrl ;
}

SchemaLoaderSpec::~SchemaLoaderSpec()
{
}

IncludeSchemaLoaderSpec::IncludeSchemaLoaderSpec(const QString &newUrl) : SchemaLoaderSpec(newUrl)
{
}

IncludeSchemaLoaderSpec::~IncludeSchemaLoaderSpec()
{
}

void IncludeSchemaLoaderSpec::useSchema(XSDSchema *parent, XSDSchema *child)
{
    parent->setIncludedSchema(child);
}

ImportSchemaLoaderSpec::ImportSchemaLoaderSpec(const QString &newUrl) : SchemaLoaderSpec(newUrl)
{
}

ImportSchemaLoaderSpec::~ImportSchemaLoaderSpec()
{
}

void ImportSchemaLoaderSpec::useSchema(XSDSchema *parent, XSDSchema *child)
{
    parent->setImportedSchema(child);
}

RedefineSchemaLoaderSpec::RedefineSchemaLoaderSpec(const QString &newUrl) : SchemaLoaderSpec(newUrl)
{
}

RedefineSchemaLoaderSpec::~RedefineSchemaLoaderSpec()
{
}

void RedefineSchemaLoaderSpec::useSchema(XSDSchema *parent, XSDSchema *child)
{
    parent->setRedefinedSchema(child);
}
