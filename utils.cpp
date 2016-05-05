#include "utils.h"

#include <QtGui>
#include <QXmlInputSource>
#include "icdCreator.h"
#include "xmleditglobals.h"
#include "utils.h"

const int Utils::ReasonableIterationCount = 100 ;
bool Utils::isUnitTest = false ;
bool Utils::silenceMessages1 = false ;
bool Utils::filler1 = false ; // filler to avoid memory corruption if possible
bool Utils::filler2 = false ;
bool Utils::silenceMessages2 = false ;

void Utils::error(const QString & message)
{
    Utils::error(NULL, message) ;
}

void Utils::error(QWidget *parent, const QString & message)
{
//    qWarning(message.toLatin1().data());
    qWarning(message.toUtf8().data());
    if(isUnitTest && silenceMessages1 && !filler1  && !filler2 && silenceMessages2) {
        return ;
    }
    QMessageBox::critical(parent, QXmlEditGlobals::appTitle(), message) ;
}

void Utils::warning(const QString & message)
{
    Utils::warning(NULL, message) ;
}

void Utils::warning(QWidget *parent, const QString & message)
{
    qWarning(message.toLatin1().data());
    if(isUnitTest && silenceMessages1 && !filler1  && !filler2 && silenceMessages2) {
        return ;
    }
    QMessageBox::warning(parent, QXmlEditGlobals::appTitle(), message) ;
}

void Utils::message(const QString & message)
{
#ifdef Q_DEBUG
    qDebug(message.toLatin1().data());
#endif
    Utils::message(NULL, message);
}

void Utils::message(QWidget *parent, const QString & message)
{
    if(isUnitTest && silenceMessages1 && !filler1  && !filler2 && silenceMessages2) {
        return ;
    }
    QMessageBox::information(parent, QXmlEditGlobals::appTitle(), message) ;
}

bool Utils::askYN(QWidget *parent, const QString & message)
{
    if(QMessageBox::Yes == QMessageBox::question(parent, QXmlEditGlobals::appTitle(), message, QMessageBox::Yes | QMessageBox::No)) {
        return true ;
    }
    return false;
}

bool Utils::askYN(const QString & message)
{
    return askYN(NULL, message);
}

void Utils::errorNoSel(QWidget *parent)
{
    error(parent, errorNoSelString());
}

QString Utils::errorNoSelString()
{
    return tr("No item selected");
}

void Utils::errorOutOfMem(QWidget *parent)
{
    error(parent, tr("Not enough memory to complete the operation"));
}

void Utils::errorReadingUserSettings()
{
    error(NULL, tr("error reading user settings"));
}

void Utils::errorSavingUserSettings()
{
    error(NULL, tr("error saving user settings"));
}

void Utils::showWaitCursor()
{
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
}

void Utils::restoreCursor()
{
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif
}


void Utils::selectComboValue(QComboBox *combo, const int value)
{
    int items = combo->count();
    for(int itemIndex = 0 ; itemIndex < items ; itemIndex++) {
        if(combo->itemData(itemIndex).toInt() == value) {
            combo->setCurrentIndex(itemIndex);
            return;
        }
    }
}

int Utils::comboSelectedCodeAsInt(QComboBox *combo, const int defaultValue)
{
    int itemIndex = combo->currentIndex();
    if(itemIndex >= 0) {
        int returnValue = combo->itemData(itemIndex).toInt() ;
        return returnValue ;
    }
    return defaultValue ;
}


void Utils::setupComboEncoding(QComboBox *combo)
{
    combo->clear();
    QList<int> mibsCodec = QTextCodec::availableMibs();
    QMap<QString, QTextCodec*> sortMap;

    foreach(int mib, mibsCodec) {
        QTextCodec *codec = QTextCodec::codecForMib(mib) ;
        sortMap.insert(codec->name().toUpper(), codec);
    }
    foreach(QString key, sortMap.keys()) {
        QTextCodec *codec = sortMap[key] ;
        combo->addItem(codec->name(), codec->mibEnum());
    }
}


bool Utils::decodeBoolean(const QString &str)
{
    bool isOk ;
    if(0 == str.compare("false", Qt::CaseInsensitive)) {
        return false;
    }
    if(0 == str.compare("true", Qt::CaseInsensitive)) {
        return true;
    }
    int val = str.toInt(&isOk, 10);
    if(!isOk) {
        return false;
    }
    if(val != 0) {
        return true;
    }
    return false;
}

int Utils::decodeInt(const QString &str, const int defaultVale)
{
    bool isOk ;
    int val = str.toInt(&isOk, 10);
    if(!isOk) {
        return defaultVale ;
    }
    return val ;
}

//-------------------------------------------------------

QString Utils::fromBase64Xml(const QString &text)
{
    QByteArray array(text.toAscii());
    QByteArray array2 = QByteArray::fromBase64(array);
    // safe string
    QXmlInputSource xmlInputSource;
    xmlInputSource.setData(array2);
    QString strText = xmlInputSource.data();
    return strText;
}

QString Utils::fromBase64(const QString &text)
{
    QByteArray array(text.toAscii());
    QByteArray array2 = QByteArray::fromBase64(array);
    // safe string
    QString strText = QString::fromUtf8(array2.data(), array2.length());
    return strText;
}

QString Utils::toBase64(const QString &text)
{
    QByteArray array;
    array.append(text.toUtf8());
    QByteArray converted = array.toBase64();
    QString strBase64 = converted.data();
    return strBase64 ;
}

//-------------------------------------------------------

void Utils::errorQtVersion(QWidget *parent)
{
    Utils::error(parent, tr("This feature is supported only if compiled with QT version specified in the manual."));
}

//-------------------------------------------------------

void Utils::appendTextNode(QDomDocument &document, QDomElement &parent, const QString &tag, const QString &text)
{
    QDomElement nameNode = document.createElement(tag);
    QDomText textNode = document.createTextNode(text);
    nameNode.appendChild(textNode);
    parent.appendChild(nameNode);
}

QDomElement Utils::appendNode(QDomDocument &document, QDomElement &parent, const QString &tag)
{
    QDomElement nameNode = document.createElement(tag);
    parent.appendChild(nameNode);
    return nameNode ;
}

//-------------------------------------------------------

QStringList Utils::readUTF8FileStringList(const QString &filePath, bool& error)
{
    error = false;
    QStringList result;
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        error = true;
        return result;
    }

    QTextStream inStream(&file);
    inStream.setCodec(QTextCodec::codecForName("UTF-8"));
    while(!inStream.atEnd()) {
        QString line = inStream.readLine();
        result.append(line);
    }
    if(file.error() != QFile::NoError) {
        error = true ;
    }
    file.close();
    return result;
}

QString Utils::readUTF8FileString(const QString &filePath, bool& error)
{
    error = false;
    QString result;
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        error = true;
        return result;
    }

    QTextStream inStream(&file);
    inStream.setCodec(QTextCodec::codecForName("UTF-8"));
    while(!inStream.atEnd()) {
        QString line = inStream.readLine();
        result.append(line);
        result.append("\n");
    }
    if(file.error() != QFile::NoError) {
        error = true ;
    }
    file.close();
    return result;
}

//-----------------------------------------------------------------

bool Utils::writeXDocumentToFile(QDomDocument &document, const QString &filePath, const bool isOverWrite)
{
    QFile file(filePath);
    if(!isOverWrite && file.exists()) {
        Utils::error(tr("File already exists"));
        return false;
    }
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        Utils::error(tr("Error writing data"));
        return false ;
    }
    QTextStream streamOut(&file);
    streamOut.setCodec("UTF-8");
    streamOut << document.toString(4);
    streamOut.flush();
    file.close();
    return (file.error() == QFile::NoError);
}


//-----------------------------------------------------------------

// reference http://www.w3.org/XML/xml-V10-4e-errata#E09
//1-An Nmtoken (name token) is any mixture of name characters.
//2-A Name is an Nmtoken with a restricted set of initial characters

bool Utils::checkXMLName(const QString &theTag)
{
    if(theTag.isEmpty()) {
        return false ;
    }

    bool isFirst = true;
    const QChar *data = theTag.data();
    // Name ::= NameStartChar (NameChar)*
    while(!data->isNull()) {
        ushort code = data->unicode() ;
        // NameStartChar

        //":" | [A-Z] | "_" | [a-z] | [#xC0-#xD6] | [#xD8-#xF6] | [#xF8-#x2FF] | [#x370-#x37D] | [#x37F-#x1FFF]
        // [#x200C-#x200D] | [#x2070-#x218F] | [#x2C00-#x2FEF] | [#x3001-#xD7FF] | [#xF900-#xFDCF] | [#xFDF0-#xFFFD] | [#x10000-#xEFFFF]

        if((':' == code)
                || ((code >= 'A') && (code <= 'Z'))
                || ((code >= 'a') && (code <= 'z'))
                || ('_' == code)
                || ((code >= 0xC0) && (code <= 0xD6))
                || ((code >= 0xD8) && (code <= 0xF6))
                || ((code >= 0xF8) && (code <= 0x2FF))
                || ((code >= 0x370) && (code <= 0x37D))
                || ((code >= 0x37F) && (code <= 0x1FFF))
                || ((code >= 0x200C) && (code <= 0x200D))
                || ((code >= 0x2070) && (code <= 0x218F))
                || ((code >= 0x2C00) && (code <= 0x2FEF))
                || ((code >= 0x3001) && (code <= 0xD7FF))
                || ((code >= 0xF900) && (code <= 0xFDCF))
                || ((code >= 0xFDF0) && (code <= 0xFFFD))     //range #x10000-#xEFFFF excluded
          ) {
            if(isFirst) {
                isFirst = false ;
            }
        } else {
            if(isFirst) {
                return false;
            }
            // NameChar
            //| "-" | "." | [0-9] | #xB7 | [#x0300-#x036F] | [#x203F-#x2040]
            if(!(('-' == code)
                    || ((code >= '0') && (code <= '9'))
                    || ('.' == code)
                    || (0xB7 == code)
                    || ((code >= 0x0300) && (code <= 0x036F))
                    || ((code >= 0x203F) && (code <= 0x2040))
                )) {
                return false ;
            }
        }
        ++data;
    }
    return true ;
}

//--------------------

void Utils::deleteQWIList(QList<QTreeWidgetItem *> &list)
{
    foreach(QTreeWidgetItem * item, list) {
        delete item ;
    }
}

/*
void Utils::todo(const QString &inputMessage)
{
    if(isUnitTest) {
        printf("TODO:%s\n", inputMessage.toLatin1().data());
    } else {
        error(QString("TODO : %1").arg(inputMessage));
    }
}
*/

/*
void Utils::TODO_THIS_RELEASE(const QString &inputMessage)
{
    if(isUnitTest) {
        printf("TODO_THIS_RELEASE:%s\n", inputMessage.toLatin1().data());
    } else {
        message(QString("TODO IN THIS RELEASE: %1").arg(inputMessage));
    }
}
*/
void Utils::TODO_NEXT_RELEASE(const QString &/*inputMessage*/)
{
    // This body intentionally blank.
}

/**
  use this function to mark fixes until automated tests are written.
  Don't make releases until there are marks on the current version.
  */

void Utils::TODO_CHECK_FIX(const QString & fix)
{
    printf("CHECK FIX:%s\n", fix.toLatin1().data());
}

/**
  Returns the new file name with the newExtension as estension.
  If there is already an extension it is changed
  */
QString Utils::changeFileType(const QString &inputString, const QString &newExtension)
{
    int index = inputString.lastIndexOf(".");
    if(index >= 0) {
        QString newName = inputString.left(index);
        newName += newExtension;
        return newName;
    }
    return inputString + newExtension;
}

// W3C Normalizaed string
QString Utils::normalizeStringXML(const QString &value)
{
    // canonical substitutions
    QString work = value;
    work = work.replace('\t', ' ');
    work = work.replace('\n', ' ');
    work = work.replace('\r', ' ');
    work = work.trimmed();
    // collapse spaces
    QString result;
    bool prevSpace = false ;
    int len = work.length();
    for(int i = 0 ; i < len ; i ++) {
        QChar ch = work.at(i);
        if(ch == ' ') {
            if(prevSpace) {
                continue ; // whitespace collapsing
            } else {
                prevSpace = true ;
                result.append(ch);
            }
        } else {
            prevSpace = false ;
            result.append(ch);
        }
    }
    return result;

}


void Utils::loadComboTextArray(QStringList strings, QList<QComboBox*> &combos)
{
    int index = 0;
    foreach(QString str, strings) {
        if(index < combos.size()) {
            combos.at(index)->setEditText(str);
        } else {
            break;
        }
        index ++;
    }
}

QString Utils::getSizeForPresentation(const qint64 size)
{
    if(size >= (1024 * 1024 * 1024)) {
        qint64 div = 1024 * 1024 ;
        div *= 1024 ;
        int userSize = size / (div) ;
        return QString(tr("%1 Gb").arg(userSize));
    }
    if(size >= 1024 * 1024) {
        int userSize = size / (1024 * 1024) ;
        return QString(tr("%1 Mb").arg(userSize));
    }
    if(size >= 1024) {
        int userSize = size / 1024 ;
        return QString(tr("%1 Kb").arg(userSize));
    }
    return QString(tr("%1").arg(size));
}
