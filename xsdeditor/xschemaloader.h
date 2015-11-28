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

#ifndef XSCHEMALOADER_H
#define XSCHEMALOADER_H

#include <QObject>
#include <QFile>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include "global.h"
#include "xsdeditor/xschema.h"


class SchemaLoaderSpec
{

public:
    /*enum ELoaderSpec {
        ELS_Include,
        ELS_Import,
        ELS_Redefine
    };*/
    QString url;

    SchemaLoaderSpec(const QString &url);
    ~SchemaLoaderSpec();
    virtual void useSchema(XSDSchema *parent, XSDSchema *child) = 0;
};

class IncludeSchemaLoaderSpec : public SchemaLoaderSpec
{

public:
    IncludeSchemaLoaderSpec(const QString &url);
    ~IncludeSchemaLoaderSpec();
    virtual void useSchema(XSDSchema *parent, XSDSchema *child);
};

class ImportSchemaLoaderSpec : public SchemaLoaderSpec
{

public:
    ImportSchemaLoaderSpec(const QString &url);
    ~ImportSchemaLoaderSpec();
    virtual void useSchema(XSDSchema *parent, XSDSchema *child);
};

class RedefineSchemaLoaderSpec : public SchemaLoaderSpec
{

public:
    RedefineSchemaLoaderSpec(const QString &url);
    ~RedefineSchemaLoaderSpec();
    virtual void useSchema(XSDSchema *parent, XSDSchema *child);
};

class LIBQXMLEDITSHARED_EXPORT XSchemaLoader : public QObject
{
    Q_OBJECT

    XSchemaLoader *_mainLoader;
    XSchemaLoader *_parentLoader;
    QString _folderPath;
    /** the main schema */
    XSDSchema *_root;
    /** the current parent*/
    XSDSchema *_current;
    QStringList _includesQueue;
    QStringList _importQueue;
    QStringList _redefineQueue;
    QMap<QString, XSDSchema*> _loadedSchemasBySchemaLocation;
    QNetworkAccessManager *_networkAccessManager ;
    bool _isError ;
    QString _errorMessage;
    SchemaLoaderSpec *_spec;

    void setError(const QString & error);
    void addSchemaToParent(XSDSchema *schema, SchemaLoaderSpec *loaderSpec);
    bool newReading(SchemaLoaderSpec *loaderSpec);
    SchemaLoaderSpec *checkIfComplete();
    SchemaLoaderSpec *checkIfCompleteQueue(QStringList &list, SchemaLoaderSpec * (XSchemaLoader::*specFactory)(const QString &url));
    void handleInputSchema(XSchemaLoader *loader, XSDSchema *child, const bool isError);
    bool hasUrl(const QString &url);

    SchemaLoaderSpec* includeLFactory(const QString &url);
    SchemaLoaderSpec* importLFactory(const QString &url);
    SchemaLoaderSpec* redefineLFactory(const QString &url);

    XSDSchema *internalSchemaLoader(QNetworkReply* reply);
    XSDSchema *internalSchemaLoader(QFile *inputFile);

    void handleFileAccess(const QString &schemaUrl);

    bool hasProtocol(const QString& url);
    void onFileAccessFinished(QFile* inputFile);

public:
    explicit XSchemaLoader(XSchemaLoader *parentLoader, SchemaLoaderSpec *newSpec, QObject *parent = 0);
    ~XSchemaLoader();

    bool readFromURL(XSDSchema *root, const QString &inputUrl, QNetworkAccessManager *networkAccessManager, const QString &paramFolderPath);
signals:

private slots:
    void onLoadCompleteDependent(XSchemaLoader *loader, XSDSchema *child, const bool isError);

public slots:
signals:
    void loadComplete(XSchemaLoader *target, XSDSchema *schema, const bool isError);

private slots:
    void onNetworkAccessFinished(QNetworkReply* reply);

};

#endif // XSCHEMALOADER_H
