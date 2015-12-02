#include "aboutdialog.h"
#include "qxmledit.h"
#include "icdCreator.h"

AboutDialog::AboutDialog(QWidget *parent,
                         const QString &appName, const QString &setVersion,
                         const QString &copyRight, const QString &setLicense, const QString &otherLicenses,
                         const QList<AuthorInfo*> &authors) :
    QDialog(parent)
{
    init();
    applicationName->setText(appName);
    version->setText(setVersion);
    copyR->setText(copyRight);
    license->setText(tr("License: %1").arg(setLicense));
    icons->setText(otherLicenses);
    envir->setText(tr("Compiled with Qt version: %1, runtime Qt version: %2").arg(QT_VERSION_STR).arg(qVersion()));

    QTreeWidgetItem *developers = new QTreeWidgetItem(0);
    developers->setText(0, tr("Developers"));
    authorsWidget->addTopLevelItem(developers);

    QTreeWidgetItem *translators = new QTreeWidgetItem(0);
    translators->setText(0, tr("Translators"));
    authorsWidget->addTopLevelItem(translators);

    QTreeWidgetItem *contributors = new QTreeWidgetItem(0);
    contributors->setText(0, tr("Contributors"));
    authorsWidget->addTopLevelItem(contributors);


    foreach(AuthorInfo *author, authors) {
        QTreeWidgetItem *item = new QTreeWidgetItem(0);

        if(author->role == AR_DEVELOPER) {
            item->setText(0, QString("%1 %2").arg(author->name).arg(contactInfo(author->contactInfo)));
            developers->addChild(item);
        } else if(author->role == AR_TRANSLATOR) {
            item->setText(0, QString("%1: %2 %3").arg(author->specialities).arg(author->name).arg(contactInfo(author->contactInfo)));
            translators->addChild(item);
        } else if(author->role == AR_CONTRIBUTOR) {
            item->setText(0, QString("%1 %2").arg(author->name).arg(contactInfo(author->contactInfo)));
            contributors->addChild(item);
        }
    }
    authorsWidget->expandAll();

}

void AboutDialog::init()
{
    if (objectName().isEmpty())
        setObjectName(QString::fromUtf8("AboutDialog"));
    setWindowModality(Qt::ApplicationModal);
    resize(652, 478);
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    setSizePolicy(sizePolicy);
    setMinimumSize(QSize(652, 478));
    setMaximumSize(QSize(652, 478));
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/icon/images/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
    setWindowIcon(icon);
    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setGeometry(QRect(290, 430, 341, 32));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Close);

    tabWidget = new QTabWidget(this);
    tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
    tabWidget->setGeometry(QRect(20, 130, 601, 291));
    tabWidget->setTabShape(QTabWidget::Rounded);

    tab = new QWidget();
    tab->setObjectName(QString::fromUtf8("tab"));

    copyR = new QLabel(tab);
    copyR->setObjectName(QString::fromUtf8("copyR"));
    copyR->setGeometry(QRect(30, 60, 411, 16));

    label_5 = new QLabel(tab);
    label_5->setObjectName(QString::fromUtf8("label_5"));
    label_5->setGeometry(QRect(30, 100, 521, 41));

    QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
    label_5->setSizePolicy(sizePolicy1);

    label_3 = new QLabel(tab);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    label_3->setGeometry(QRect(30, 20, 531, 20));
    QFont font;
    font.setFamily(QString::fromUtf8("Sans Serif"));
    font.setItalic(true);
    label_3->setFont(font);
    label_3->setAlignment(Qt::AlignCenter);

    icons = new QLabel(tab);
    icons->setObjectName(QString::fromUtf8("icons"));
    icons->setGeometry(QRect(30, 200, 531, 51));
    icons->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
    icons->setWordWrap(true);

    license = new QLabel(tab);
    license->setObjectName(QString::fromUtf8("license"));
    license->setGeometry(QRect(30, 150, 441, 16));

    tabWidget->addTab(tab, QString());
    tab_2 = new QWidget();
    tab_2->setObjectName(QString::fromUtf8("tab_2"));
    label_4 = new QLabel(tab_2);
    label_4->setObjectName(QString::fromUtf8("label_4"));
    label_4->setGeometry(QRect(20, 10, 511, 16));
    label_4->setOpenExternalLinks(true);
    label_4->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    authorsWidget = new QTreeWidget(tab_2);
    QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
    __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
    authorsWidget->setHeaderItem(__qtreewidgetitem);
    authorsWidget->setObjectName(QString::fromUtf8("authorsWidget"));
    authorsWidget->setGeometry(QRect(10, 30, 571, 221));
    authorsWidget->header()->setVisible(false);
    tabWidget->addTab(tab_2, QString());
    label = new QLabel(this);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(40, 20, 61, 51));
    label->setPixmap(QPixmap(QString::fromUtf8(":/icon/images/icon.png")));
    label->setScaledContents(true);
    applicationName = new QLabel(this);
    applicationName->setObjectName(QString::fromUtf8("applicationName"));
    applicationName->setGeometry(QRect(120, 0, 191, 91));
    QFont font1;
    font1.setFamily(QString::fromUtf8("Sans Serif"));
    font1.setPointSize(24);
    font1.setBold(true);
    font1.setWeight(75);
    applicationName->setFont(font1);
    line = new QFrame(this);
    line->setObjectName(QString::fromUtf8("line"));
    line->setGeometry(QRect(100, 80, 491, 16));
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    version = new QLabel(this);
    version->setObjectName(QString::fromUtf8("version"));
    version->setGeometry(QRect(331, 27, 311, 41));
    QFont font2;
    font2.setFamily(QString::fromUtf8("Sans Serif"));
    font2.setPointSize(18);
    version->setFont(font2);
    envir = new QLabel(this);
    envir->setObjectName(QString::fromUtf8("envir"));
    envir->setGeometry(QRect(100, 100, 511, 16));
    label_2 = new QLabel(this);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setGeometry(QRect(0, 0, 651, 81));
    label_2->setAutoFillBackground(false);
    label_2->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0.469613, y1:1, x2:0.48563, y2:0.477, stop:0 rgba(187, 228, 255, 255), stop:1 rgba(255, 255, 255, 255));"));
    label_2->raise();
    buttonBox->raise();
    tabWidget->raise();
    label->raise();
    applicationName->raise();
    line->raise();
    version->raise();
    envir->raise();

    retranslateUi();
    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    tabWidget->setCurrentIndex(0);


    QMetaObject::connectSlotsByName(this);
}

void AboutDialog::retranslateUi()
{
    setWindowTitle(QApplication::translate("AboutDialog", "About ICD Creator", 0, QApplication::UnicodeUTF8));
    copyR->setText(QApplication::translate("AboutDialog", "(c) 2015-2016 GDWY", 0, QApplication::UnicodeUTF8));
    label_5->setText(QApplication::translate("AboutDialog","This program is based on the open source project QXmlEdit", 0, QApplication::UnicodeUTF8));
//    label_5->setText(QApplication::translate("AboutDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
//"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
//"p, li { white-space: pre-wrap; }\n"
//"</style></head><body style=\" font-family:'Arial'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
//"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><a href=\"http://code.google.com/p/qxmledit\"><span style=\" text-decoration: underline; color:#507e41;\">http://code.google.com/p/qxmledit</span></a></p></body></html>", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("AboutDialog", "A ICD file Creator and Editor", 0, QApplication::UnicodeUTF8));
    icons->setText(QApplication::translate("AboutDialog", "Icons by Easyicon (www.easyicon.net), covered by LGPLv3 license ", 0, QApplication::UnicodeUTF8));
    license->setText(QApplication::translate("AboutDialog", "License: GNU Public License Version 2", 0, QApplication::UnicodeUTF8));
    tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("AboutDialog", "About", 0, QApplication::UnicodeUTF8));
//    label_4->setText(QApplication::translate("AboutDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
//"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
//"p, li { white-space: pre-wrap; }\n"
//"</style></head><body style=\" font-family:'Arial'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
//"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt;\">Please use </span><a href=\"http://code.google.com/p/qxmledit/issues\"><span style=\" text-decoration: underline; color:#507e41;\">http://code.google.com/p/qxmledit/issues</span></a><span style=\" font-size:9pt;\"> to report bugs.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
    tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("AboutDialog", "Authors", 0, QApplication::UnicodeUTF8));
    label->setText(QString());
    applicationName->setText(QApplication::translate("AboutDialog", "ICD Creator", 0, QApplication::UnicodeUTF8));
    version->setText(QApplication::translate("AboutDialog", "x.xx", 0, QApplication::UnicodeUTF8));
    envir->setText(QApplication::translate("AboutDialog", "environment", 0, QApplication::UnicodeUTF8));
    label_2->setText(QString());
}

QString AboutDialog::contactInfo(const QString &info)
{
    if(info.isEmpty()) {
        return tr("");
    }
    return QString("(%1)").arg(info);
}

AboutDialog::~AboutDialog()
{

}
