#ifndef AUTHORINFO_H
#define AUTHORINFO_H

#include <QString>
#include <QList>

enum EAuthorRole {
    AR_DEVELOPER,
    AR_TRANSLATOR,
    AR_CONTRIBUTOR
};

class AuthorInfo
{
public:
    QString name;
    QString contactInfo;
    QString specialities;
    EAuthorRole role;

    AuthorInfo(const QString &newName, const QString &newContactInfo, const EAuthorRole newRole, const QString &newSpecialities) {
        name = newName ;
        contactInfo = newContactInfo;
        role = newRole;
        specialities = newSpecialities;
    }

    static const QString appName;
    static const QString version;
    static const QString copyright;
    static const QString license;
    static const QString other;

};


QList<AuthorInfo*> authorsInfo();
void deleteAuthorsInfo(QList<AuthorInfo*> &authors);

#endif // AUTHORINFO_H
