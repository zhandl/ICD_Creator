
#include "authorinfo.h"
#include "icdCreator.h"

QList<AuthorInfo*> authorsInfo()
{
    QList<AuthorInfo*> authors ;
    AuthorInfo *newAuthor;
    newAuthor = new AuthorInfo("Michael", "zhl.debug@gmail.com", AR_DEVELOPER, "");
    authors.append(newAuthor);
    newAuthor = new AuthorInfo("mike", "", AR_CONTRIBUTOR, "");
    authors.append(newAuthor);
    newAuthor = new AuthorInfo("mike", "", AR_TRANSLATOR, "CN");
    authors.append(newAuthor);
    return authors ;
}

void deleteAuthorsInfo(QList<AuthorInfo*> &authors)
{
    foreach(AuthorInfo * author,  authors) {
        delete author;
    }
    authors.clear();
}

const QString AuthorInfo::appName(APPLICATION_NAME) ;
const QString AuthorInfo::version(VERSION_ID) ;
const QString AuthorInfo::copyright = QString::fromUtf8("\u00A9 2014-2016 GDWY");
const QString AuthorInfo::license("GNU Library Public License Version 2");
const QString AuthorInfo::other("Icons by easyicon (www.easyicon.net), covered by LGPLv3 license (see README document)");


