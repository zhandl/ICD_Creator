#include "compare.h"
#include "utils.h"
#include "compare.h"
#include <QHash>

#define FILE_TEST   "/home/lbell/devel/qxmledit/qxmledit/src/data/compare_to.xml"

#define CSS_TEXT    "\
<style type='text/css'>\
body {                  \
   font-size: 10pt;     \
   background-color:#FFF;\
}                       \
.T0 {                   \
    color: #888;        \
    font-style:italic;  \
}                      \
.T1 {                   \
    color: #F44;        \
    font-style:italic;  \
}                      \
.E0 {                   \
    color: #44F;        \
}                      \
.E1 {                   \
    color: #888;        \
}                      \
.E2 {                   \
    color: #F42;        \
}                      \
.E3 {                   \
    color: #0A0;        \
}                      \
.A0 {                   \
    color: #44F;        \
}                      \
.A1 {                   \
    color: #888;        \
}                      \
.A2 {                   \
    color: #F42;        \
}                      \
.A3 {                   \
    color: #0A0;        \
}                      \
.C0 {                   \
    color: #CCF;        \
    font-style:italic;  \
}                      \
.C1 {                   \
    color: #CCC;        \
    font-style:italic;  \
}                      \
.C2 {                   \
    color: #FCC;        \
    font-style:italic;  \
}                      \
.C3 {                   \
    color: #CFC;        \
    font-style:italic;  \
}                      \
.AV {                   \
    color: #BB92C5;        \
}                      \
</style>"


void Compare::doCompare(QWidget *parent, DomModel *original)
{
    Compare compare(original, parent);
    compare.setModal(true);
    if(!compare.loadData()) {
        return ;
    }
    compare.exec();
}

//----------------------------------------------------------------------


Compare::Compare(DomModel* newOriginal, QWidget *parent) :
    QDialog(parent),
    _areDifferent(false)
{
    toCompare = NULL ;
    original = newOriginal ;
    init();
}

Compare::~Compare()
{
    if(NULL != toCompare) {
        delete toCompare ;
    }
}

void Compare::init()
{
    if (objectName().isEmpty())
        setObjectName(QString::fromUtf8("Compare"));
    resize(494, 567);
    setMinimumSize(QSize(400, 300));
    setMaximumSize(QSize(16777215, 16777215));
    verticalLayout_2 = new QVBoxLayout(this);
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    verticalLayout = new QVBoxLayout();
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    textBrowser = new QTextBrowser(this);
    textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

    verticalLayout->addWidget(textBrowser);


    verticalLayout_2->addLayout(verticalLayout);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    showOldValuesCB = new QCheckBox(this);
    showOldValuesCB->setObjectName(QString::fromUtf8("showOldValues"));
    showOldValuesCB->setEnabled(false);

    horizontalLayout->addWidget(showOldValuesCB);

    ignoreNonElements = new QCheckBox(this);
    ignoreNonElements->setObjectName(QString::fromUtf8("ignoreNonElements"));

    horizontalLayout->addWidget(ignoreNonElements);

    ignoreTextCB = new QCheckBox(this);
    ignoreTextCB->setObjectName(QString::fromUtf8("ignoreText"));
    ignoreTextCB->setEnabled(true);
    ignoreTextCB->setChecked(true);

    horizontalLayout->addWidget(ignoreTextCB);

    copyToClipboard = new QPushButton(this);
    copyToClipboard->setObjectName(QString::fromUtf8("copyToClipboard"));

    horizontalLayout->addWidget(copyToClipboard);


    verticalLayout_2->addLayout(horizontalLayout);

    Legend = new QGroupBox(this);
    Legend->setObjectName(QString::fromUtf8("Legend"));
    horizontalLayout_3 = new QHBoxLayout(Legend);
    horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    widget_3 = new QWidget(Legend);
    widget_3->setObjectName(QString::fromUtf8("widget_3"));
    widget_3->setAutoFillBackground(false);
    widget_3->setStyleSheet(QString::fromUtf8("background-color:rgb(200, 200, 200);\n"
"padding:2px;\n"
"border: 1px solid black;"));

    horizontalLayout_2->addWidget(widget_3);

    label = new QLabel(Legend);
    label->setObjectName(QString::fromUtf8("label"));

    horizontalLayout_2->addWidget(label);

    widget_4 = new QWidget(Legend);
    widget_4->setObjectName(QString::fromUtf8("widget_4"));
    widget_4->setAutoFillBackground(false);
    widget_4->setStyleSheet(QString::fromUtf8("background-color:rgb(0, 85, 255);\n"
"padding:2px;\n"
"border: 1px solid black;"));

    horizontalLayout_2->addWidget(widget_4);

    label_3 = new QLabel(Legend);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    horizontalLayout_2->addWidget(label_3);

    widget_5 = new QWidget(Legend);
    widget_5->setObjectName(QString::fromUtf8("widget_5"));
    widget_5->setAutoFillBackground(false);
    widget_5->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 85, 0);\n"
"padding:2px;\n"
"border: 1px solid black;"));

    horizontalLayout_2->addWidget(widget_5);

    label_2 = new QLabel(Legend);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    horizontalLayout_2->addWidget(label_2);

    widget_6 = new QWidget(Legend);
    widget_6->setObjectName(QString::fromUtf8("widget_6"));
    widget_6->setAutoFillBackground(false);
    widget_6->setStyleSheet(QString::fromUtf8("background-color:rgb(0, 170, 0);\n"
"padding:2px;\n"
"border: 1px solid black;"));

    horizontalLayout_2->addWidget(widget_6);

    label_4 = new QLabel(Legend);
    label_4->setObjectName(QString::fromUtf8("label_4"));

    horizontalLayout_2->addWidget(label_4);


    horizontalLayout_3->addLayout(horizontalLayout_2);


    verticalLayout_2->addWidget(Legend);

    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Close|QDialogButtonBox::Retry);

    verticalLayout_2->addWidget(buttonBox);

    buttonBox->raise();
    Legend->raise();

    retranslateUi();
    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QMetaObject::connectSlotsByName(this);
}

void Compare::retranslateUi()
{
    setWindowTitle(QApplication::translate("Compare", "Compare files", 0, QApplication::UnicodeUTF8));
    showOldValuesCB->setText(QApplication::translate("Compare", "Show old values", 0, QApplication::UnicodeUTF8));
    ignoreNonElements->setText(QApplication::translate("Compare", "Ignore non elements", 0, QApplication::UnicodeUTF8));
    ignoreTextCB->setText(QApplication::translate("Compare", "Ignore text", 0, QApplication::UnicodeUTF8));
    copyToClipboard->setText(QApplication::translate("Compare", "Copy text to clipboard", 0, QApplication::UnicodeUTF8));
    Legend->setTitle(QApplication::translate("Compare", "Legend", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("Compare", "Equals", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("Compare", "Deleted", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("Compare", "Different", 0, QApplication::UnicodeUTF8));
    label_4->setText(QApplication::translate("Compare", "Added", 0, QApplication::UnicodeUTF8));
}

bool Compare::loadData()
{
#ifdef DEBUG_COMPARE
    compare.loadRule(FILE_TEST);
#else
    QString filePath = QFileDialog::getOpenFileName(parentWidget(),  tr("Open File To Compare to"),
                       original->fileName(), tr("ICD files (*.icd);;XML files (*.xml);;All files (*);;"));
    if(!filePath.isEmpty()) {
        loadRule(filePath);
    } else {
        return false ;
    }
#endif
    return true;
}

bool Compare::loadData(const QString &filePath)
{
    if(!filePath.isEmpty()) {
        loadRule(filePath);
    } else {
        return false ;
    }
    return true;
}

bool Compare::areDifferent()
{
    return _areDifferent ;
}
void Compare::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch(e->type()) {
    case QEvent::LanguageChange:
        retranslateUi();
        break;
    default:
        break;
    }
}

bool Compare::loadFile(const QString &filePath)
{
    bool isOk = false;
    if(!filePath.isEmpty()) {
        QFile file(filePath);
        if(file.open(QIODevice::ReadOnly)) {
            if(document.setContent(&file)) {
                isOk = true;
            } else {
                Utils::error(tr("Unable to parse XML"));
            }
            file.close();
        } else {
            Utils::error(QString(tr("Unable to load file.\n Error code is '%1'")).arg(file.error()));
        }
    } else {
        Utils::error(tr("File name empty. Unable to load it."));
    }
    return isOk;
}

bool Compare::loadData(QByteArray dataIn)
{
    QBuffer file(&dataIn);
    if(file.open(QIODevice::ReadOnly)) {
        if(document.setContent(&file)) {
            return true ;
        } else {
            Utils::error(tr("Unable to parse XML"));
        }
    } else {
        Utils::error(QString(tr("Unable to load file.")));
    }
    return false;
}

bool Compare::loadRule(const QString &filePath)
{
    if(!loadFile(filePath)) {
        return false;
    }
    toCompare = new DomModel(document, filePath);
    doCompare();
    return true;
}

bool Compare::loadRule(QByteArray dataIn)
{
    if(!loadData(dataIn)) {
        return false;
    }
    toCompare = new DomModel(document, "");
    doCompare();
    return true;
}

void Compare::doCompare()
{
    _areDifferent = false ;
    ignoreText = ignoreTextCB->isChecked();
    compareOnlyElements = ignoreNonElements->isChecked();
    showOldValues = showOldValuesCB->isChecked();

    textBrowser->clear();
    resultText = "" ;
    if((NULL == original) || (NULL == toCompare)) {
        Utils::error(this, tr("Empty data, impossible to compare."));
        return ;
    }
    resultText = "<html><head>";
    resultText += CSS_TEXT;
    resultText += "</head><body>";
    recurse(original->getItems(), toCompare->getItems(), 0);
    resultText += "</body></html>";
    textBrowser->setHtml(resultText);
}

void Compare::filterItems(QVector<DomItem*> &origItems, QVector<DomItem*> &destItems, const bool isFilter)
{
    // Filter items
    int origItemsSize = origItems.size();
    for(int i = 0; i < origItemsSize ; ++i) {
        DomItem * item = origItems.at(i);
        if(!isFilter || (isFilter && (item->getType() == DomItem ::ET_ELEMENT))) {
            destItems.append(item);
        }
    }
}

bool Compare::compareTwoText(const QString &str1, const QString &str2)
{
    QString s1 = str1 ;
    QString s2 = str2 ;
    s1.replace("\r\n", "\n");
    s2.replace("\r\n", "\n");
    bool equalCond = (s1 == s2);
    return equalCond;
}

void Compare::recurse(QVector<DomItem*> &inputOrigItems, QVector<DomItem*> &inputCompareItems, const int indent)
{
    // Filter elements
    QVector<DomItem*> origItems, compareItems ;

    filterItems(inputOrigItems, origItems, compareOnlyElements);
    filterItems(inputCompareItems, compareItems, compareOnlyElements);

    int origElementsSize = origItems.size();
    int compareElementsSize = compareItems.size();
    for(int elementIndex = 0 ; elementIndex < origElementsSize ; elementIndex ++) {
        EDiffStates state;
        DomItem *orig = origItems.at(elementIndex);
        DomItem* compare = NULL ;
        if(elementIndex < compareElementsSize) {
            compare = compareItems.at(elementIndex);
            state = DF_EQUAL ; // unless found otherwise
            if(orig->getType() != compare->getType()) {
                state = DF_DIFFERENT;
                setDifference();
            } else {
                if(orig->getType() == DomItem::ET_ELEMENT) {
                    if(orig->tag() != compare->tag()) {
                        state = DF_DIFFERENT;
                        setDifference();
                    }
                } else if(orig->getType() == DomItem::ET_COMMENT) {
                    if(!compareTwoText(orig->getComment(), compare->getComment())) {
                        state = DF_DIFFERENT;
                        setDifference();
                    }
                } else if(orig->getType() == DomItem::ET_TEXT) {
                    if(!compareTwoText(orig->text, compare->text)) {
                        state = DF_DIFFERENT;
                        setDifference();
                    }
                } else if(orig->getType() == DomItem::ET_PROCESSING_INSTRUCTION) {
                    if(!compareTwoText(orig->getPIData(), compare->getPIData())
                            ||  !compareTwoText(orig->getPITarget(), compare->getPITarget())) {
                        state = DF_DIFFERENT;
                        setDifference();
                    }
                }
                // confronta gli attributi
            } // end of test on same type
        } else {
            state = DF_ADDED ;
            setDifference();
        }
        if(state == DF_EQUAL) {
            QString text1 = orig->getAsSimpleText(false);
            QString text2 = compare->getAsSimpleText(false);
            if(!ignoreText) {
                if(!compareTwoText(text1, text2)) {
                    state = DF_DIFFERENT ;
                    setDifference();
                }
            }

            dumpElement(indent, orig, state);
            if(orig->getType() == DomItem::ET_ELEMENT) {
                compareAttributes(orig, compare);
            }
            closeTag(orig, state);
            dumpText(text1, state, indent);
            recurse(orig->getItems(), compare->getItems(), indent + 1);
            endElement(indent, orig, state);
        } else if(state == DF_DIFFERENT) {
            recurseAll(orig, DF_DIFFERENT, indent + 1);
        } else {
            recurseAll(orig, DF_ADDED, indent + 1);
        }
    }
    for(int elementIndex = origElementsSize ; elementIndex < compareElementsSize ; elementIndex++) {
        DomItem *element = compareItems.at(elementIndex);
        recurseAll(element, DF_MISSING, indent + 1);
    }
}

void Compare::closeTag(DomItem *item, const EDiffStates state)
{
    if(item->getType() == DomItem::ET_ELEMENT) {
        resultText += QString("<span class='E%1'>&gt;</span><br/>").arg(state);
    }
}

void Compare::recurseAll(DomItem* item, const EDiffStates state, const int indent)
{
    dumpElement(indent, item, state);
    if(item->getType() == DomItem::ET_ELEMENT) {
        dumpAttributes(item, state);
    }
    closeTag(item, state);
    QString text = item->getAsSimpleText(false);
    dumpText(text, state, indent);
    QVector<DomItem*> elements = item->getItems();
    int elementsSize = elements.size();
    for(int elementIndex = 0 ; elementIndex < elementsSize ; elementIndex ++) {
        DomItem *orig = elements.at(elementIndex);
        recurseAll(orig, state, indent + 1);
    }
    endElement(indent, item, state);
}

void Compare::dumpText(const QString text, const EDiffStates state, const int indent)
{
    if(!text.isEmpty()) {
        for(int i = 0 ; i < indent ; i++) {
            resultText += "&nbsp;";
        }
        if(state == DF_DIFFERENT) {
            resultText += "&nbsp;<span class='T1'>";
        } else {
            resultText += "&nbsp;<span class='T0'>";
        }
        resultText += convertTextInHTML(text);
        resultText += "</span><br/>";
    }
}

void Compare::dumpElement(const int indent, DomItem *element, const EDiffStates state)
{
    for(int i = 0 ; i < indent ; i++) {
        resultText += "&nbsp;";
    }
    switch(element->getType()) {
    case DomItem::ET_COMMENT:
        resultText += QString("<span class='C%1'>&lt;--%2--&gt;</span><br/>").arg(state).arg(element->getComment());
        break;
    case DomItem::ET_ELEMENT:
        resultText += QString("<span class='E%1'>&lt;%2</span>").arg(state).arg(element->tag());
        break;
    case DomItem::ET_PROCESSING_INSTRUCTION:
        resultText += QString("<span class='C%1'>&lt;?%2 %3?&gt;</span><br/>").arg(state).arg(element->getPITarget()).arg(element->getPIData());
        break;
    case DomItem::ET_TEXT:
        resultText += QString("<span class='T%1'>%1</span><br/>").arg(state).arg(convertTextInHTML(element->text));
        break;

    }
}

void Compare::endElement(const int indent, DomItem *item, const EDiffStates state)
{
    switch(item->getType()) {
    case DomItem::ET_TEXT:
        break;
    case DomItem::ET_COMMENT:
        break;
    case DomItem::ET_ELEMENT:
        for(int i = 0 ; i < indent ; i++) {
            resultText += "&nbsp;";
        }
        resultText += QString("<span class='E%1'>&lt;/%2&gt;</span><br/>").arg(state).arg(item->tag());
        break;
    case DomItem::ET_PROCESSING_INSTRUCTION:
        break;
    }
}


void Compare::insertAttrInHash(QHash<QString, Attribute*> &hash, DomItem *target)
{
    QVector<Attribute*>::iterator it;
    for(it = target->attributes.begin(); it != target->attributes.end(); ++it) {
        Attribute* attr = *it;
        hash[attr->name] = attr ;
    }
}

void Compare::compareAttributes(DomItem *orig, DomItem *compare)
{
    QHash<QString, Attribute*> hashCompare ;
    insertAttrInHash(hashCompare, compare);
    QVector<Attribute*>::iterator it;
    for(it = orig->attributes.begin(); it != orig->attributes.end(); ++it) {
        Attribute* attr = *it;
        if(hashCompare.contains(attr->name)) {
            Attribute *two = hashCompare[attr->name];
            if(attr->value == two->value) {
                dumpAttr(attr, DF_EQUAL);
            } else {
                dumpAttr(attr, DF_DIFFERENT);
                setDifference();
            }
            hashCompare.remove(attr->name);
        } else {
            dumpAttr(attr, DF_ADDED);
            setDifference();
        }
    }
    QHashIterator<QString, Attribute*> itt(hashCompare);
    while(itt.hasNext()) {
        itt.next();
        dumpAttr(itt.value(), DF_MISSING);
        setDifference();
    }
}

void Compare::dumpAttributes(DomItem *item, const EDiffStates state)
{
    QVector<Attribute*>::iterator it;
    for(it = item->attributes.begin(); it != item->attributes.end(); ++it) {
        Attribute* attr = *it;
        dumpAttr(attr, state);
    }
}

QString Compare::convertTextInHTML(const QString strIn)
{
    QString res ;
    int len = strIn.length();
    for(int i = 0 ; i < len ; i ++) {
        QChar ch = strIn.at(i);
        if(ch.isDigit() || (('a' <= ch) && (ch <= 'z')) || ((ch >= 'A') && (ch <= 'Z'))) {
            res.append(ch) ;
        } else {
            ushort valueInt = ch.unicode();
            res.append(QString("&#%1;"). arg(valueInt));
        }
    }
    return res;
}

void Compare::dumpAttr(Attribute *attr, const EDiffStates state)
{
    if(state == DF_EQUAL) {
        resultText += QString(" <span class='A%1'>%2=&quot;<span class='AV'>%3</span>&quot;</span>").arg(state).arg(attr->name).arg(convertTextInHTML(attr->value));
    } else {
        resultText += QString(" <span class='A%1'>%2=&quot;%3&quot;</span>").arg(state).arg(attr->name).arg(convertTextInHTML(attr->value));
    }

}

void Compare::accept()
{
    doCompare();
}

void Compare::on_copyToClipboard_clicked()
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(resultText);
}

void Compare::setDifference()
{
    _areDifferent = true ;
}
