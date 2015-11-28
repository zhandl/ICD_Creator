#ifndef UTILS_H
#define UTILS_H

#include "global.h"
#include <QObject>
#include <QComboBox>
#include <QDomDocument>
#include <QTreeWidgetItem>

class LIBQXMLEDITSHARED_EXPORT Utils : public QObject
{
    Q_OBJECT
private:
    Utils() {}

public:
    static const int ReasonableIterationCount ;
    static bool isUnitTest ;
    static bool silenceMessages1;
    static bool filler1; // filler to avoid memory corruption if possible
    static bool filler2;
    static bool silenceMessages2;

    static void error(const QString& message);
    static void error(QWidget *parent, const QString & message);
    static void warning(const QString& message);
    static void warning(QWidget *parent, const QString & message);
    static void message(const QString& message);
    static void message(QWidget *parent, const QString & message);
    static bool askYN(QWidget *parent, const QString & message);
    static bool askYN(const QString & message);

    // Specialized errors
    static void errorNoSel(QWidget *parent);
    static void errorOutOfMem(QWidget *parent);
    static void errorReadingUserSettings();
    static void errorSavingUserSettings();
    static void errorQtVersion(QWidget *parent);

    static QString errorNoSelString();

    static void todo(const QString &message);
    //static void TODO_THIS_RELEASE(const QString &message);
    static void TODO_CHECK_FIX(const QString &message);
    static void TODO_NEXT_RELEASE(const QString &inputMessage);
    //------
    static void showWaitCursor();
    static void restoreCursor();

    //-- utility
    static void selectComboValue(QComboBox *combo, const int value);
    static int comboSelectedCodeAsInt(QComboBox *combo, const int defaultValue);

    static bool decodeBoolean(const QString &str);
    static int decodeInt(const QString &str, const int defaultVale);

    static QString fromBase64(const QString &text);
    static QString fromBase64Xml(const QString &text);
    static QString toBase64(const QString &text);

    static void appendTextNode(QDomDocument &document, QDomElement &parent, const QString &tag, const QString &text);
    static QDomElement appendNode(QDomDocument &document, QDomElement &parent, const QString &tag);

    static QString readUTF8FileString(const QString &filePath, bool& error);
    static QStringList readUTF8FileStringList(const QString &filePath, bool& error);
    static bool writeXDocumentToFile(QDomDocument &document, const QString &filePath, const bool isOverWrite);

    static bool checkXMLName(const QString &theTag);

    static void deleteQWIList(QList<QTreeWidgetItem *> &list);

    static QString changeFileType(const QString &inputString, const QString &newExtension);
    static QString normalizeStringXML(const QString &value);

    static void loadComboTextArray(QStringList strings, QList<QComboBox*> &combos);
    static void setupComboEncoding(QComboBox *combo);

    static QString getSizeForPresentation(const qint64 size);
};
#endif // UTILS_H
