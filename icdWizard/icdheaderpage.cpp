#include "icdheaderpage.h"
#include "ui_icdHeaderPage.h"
#include <QDateTimeEdit>

icdHeaderPage::icdHeaderPage(QWidget *parent) :
    QWizardPage(parent)
{
    setTitle(tr("ICD Header Setting"));
    setSubTitle(tr("This page can set the attributes of header segment, user can add or delete History Hitem."));

    init();

    connect(headerVersionCheckBox, SIGNAL(toggled(bool)), headerVersionLabel, SLOT(setEnabled(bool)));
    connect(headerVersionCheckBox, SIGNAL(toggled(bool)), headerVersionText, SLOT(setEnabled(bool)));
    connect(headerRevisionCheckBox, SIGNAL(toggled(bool)), headerRevisionLabel, SLOT(setEnabled(bool)));
    connect(headerRevisionCheckBox, SIGNAL(toggled(bool)), headerRevisionText, SLOT(setEnabled(bool)));
    connect(headerToolIdCheckBox, SIGNAL(toggled(bool)), headerToolIdLabel, SLOT(setEnabled(bool)));
    connect(headerToolIdCheckBox, SIGNAL(toggled(bool)), headerToolIdText, SLOT(setEnabled(bool)));
    connect(headerRefCheckBox, SIGNAL(toggled(bool)), headerRefLabel, SLOT(setEnabled(bool)));
    connect(headerRefCheckBox, SIGNAL(toggled(bool)), headerRefText, SLOT(setEnabled(bool)));

    bool headerVersionIsChecked = headerVersionCheckBox->checkState();
    bool headerRevisionIsChecked = headerRevisionCheckBox->checkState();
    bool headerToolIdIsChecked = headerToolIdCheckBox->checkState();
    bool headerRefIsChecked = headerRefCheckBox->checkState();
    headerVersionLabel->setEnabled(headerVersionIsChecked);
    headerVersionText->setEnabled(headerVersionIsChecked);
    headerRevisionLabel->setEnabled(headerRevisionIsChecked);
    headerRevisionText->setEnabled(headerRefIsChecked);
    headerToolIdLabel->setEnabled(headerToolIdIsChecked);
    headerToolIdText->setEnabled(headerToolIdIsChecked);
    headerRefLabel->setEnabled(headerRefIsChecked);
    headerRefText->setEnabled(headerRefIsChecked);
}

icdHeaderPage::~icdHeaderPage()
{

}

void icdHeaderPage::init()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QString::fromUtf8("icdHeaderPage"));
    this->resize(800, 600);
//    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
//    sizePolicy.setHorizontalStretch(0);
//    sizePolicy.setVerticalStretch(9);
//    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
//    this->setSizePolicy(sizePolicy);
    this->setMaximumSize(QSize(800, 600));

    headerVLayout = new QVBoxLayout(this);
    headerVLayout->setObjectName(QString::fromUtf8("headerVLayout"));

    headerGroupBox = new QGroupBox(this);
    headerGroupBox->setObjectName(QString::fromUtf8("headerGroupBox"));
    QFont font;
    font.setFamily(QString::fromUtf8("Calibri"));
    font.setPointSize(11);
    headerGroupBox->setFont(font);

    headerGridLayout = new QGridLayout(headerGroupBox);
    headerGridLayout->setObjectName(QString::fromUtf8("headerGridLayout"));

    headerIdLabel = new QLabel(headerGroupBox);
    headerIdLabel->setObjectName(QString::fromUtf8("headerIdLabel"));
    headerIdLabel->setFont(font);

    headerIdText = new QLineEdit(headerGroupBox);
    headerIdText->setObjectName(QString::fromUtf8("headerIdText"));
    headerIdText->setStyleSheet(tr("background-color:rgba(255, 255, 200, 255)"));

    headerNameStructureLabel = new QLabel(headerGroupBox);
    headerNameStructureLabel->setObjectName(QString::fromUtf8("headerNameStructureLabel"));

    headerNameStructureCombo = new QComboBox(headerGroupBox);
    headerNameStructureCombo->setObjectName(QString::fromUtf8("headerNameStructureCombo"));
    headerNameStructureCombo->setStyleSheet(tr("background-color:rgba(255, 255, 200, 255)"));

    headerVersionCheckBox = new QCheckBox(headerGroupBox);
    headerVersionCheckBox->setObjectName(QString::fromUtf8("headerVersionCheckBox"));

    headerVersionLabel = new QLabel(headerGroupBox);
    headerVersionLabel->setObjectName(QString::fromUtf8("headerVersionLabel"));

    headerVersionText = new QLineEdit(headerGroupBox);
    headerVersionText->setObjectName(QString::fromUtf8("headerVersionText"));

    headerRevisionCheckBox = new QCheckBox(headerGroupBox);
    headerRevisionCheckBox->setObjectName(QString::fromUtf8("headerRevisionCheckBox"));

    headerRevisionLabel = new QLabel(headerGroupBox);
    headerRevisionLabel->setObjectName(QString::fromUtf8("headerRevisionLabel"));

    headerRevisionText = new QLineEdit(headerGroupBox);
    headerRevisionText->setObjectName(QString::fromUtf8("headerRevisionText"));

    headerToolIdCheckBox = new QCheckBox(headerGroupBox);
    headerToolIdCheckBox->setObjectName(QString::fromUtf8("headerToolIdCheckBox"));

    headerToolIdLabel = new QLabel(headerGroupBox);
    headerToolIdLabel->setObjectName(QString::fromUtf8("headerToolIdLabel"));
    headerToolIdLabel->setFont(font);

    headerToolIdText = new QLineEdit(headerGroupBox);
    headerToolIdText->setObjectName(QString::fromUtf8("headerToolIdText"));

    headerRefCheckBox = new QCheckBox(headerGroupBox);
    headerRefCheckBox->setObjectName(QString::fromUtf8("headerRefCheckBox"));

    headerRefLabel = new QLabel(headerGroupBox);
    headerRefLabel->setObjectName(QString::fromUtf8("headerRefLabel"));

    headerRefText = new QLineEdit(headerGroupBox);
    headerRefText->setObjectName(QString::fromUtf8("headerRefText"));

    headerGridLayout->addWidget(headerIdLabel, 0, 1, 1, 1);
    headerGridLayout->addWidget(headerIdText, 0, 2, 1, 1);
    headerGridLayout->addWidget(headerNameStructureLabel, 0, 4, 1, 1);
    headerGridLayout->addWidget(headerNameStructureCombo, 0, 5, 1, 1);
    headerGridLayout->addWidget(headerVersionCheckBox, 1, 0, 1, 1);
    headerGridLayout->addWidget(headerVersionLabel, 1, 1, 1, 1);
    headerGridLayout->addWidget(headerVersionText, 1, 2, 1, 1);
    headerGridLayout->addWidget(headerRevisionCheckBox, 1, 3, 1, 1);
    headerGridLayout->addWidget(headerRevisionLabel, 1, 4, 1, 1);
    headerGridLayout->addWidget(headerRevisionText, 1, 5, 1, 1);
    headerGridLayout->addWidget(headerToolIdCheckBox, 2, 0, 1, 1);
    headerGridLayout->addWidget(headerToolIdLabel, 2, 1, 1, 1);
    headerGridLayout->addWidget(headerToolIdText, 2, 2, 1, 1);
    headerGridLayout->addWidget(headerRefCheckBox, 2, 3, 1, 1);
    headerGridLayout->addWidget(headerRefLabel, 2, 4, 1, 1);
    headerGridLayout->addWidget(headerRefText, 2, 5, 1, 1);

#ifndef QT_NO_SHORTCUT
    headerIdLabel->setBuddy(headerIdText);
    headerNameStructureLabel->setBuddy(headerNameStructureCombo);
    headerRevisionLabel->setBuddy(headerRevisionText);
    headerVersionLabel->setBuddy(headerVersionText);
    headerToolIdLabel->setBuddy(headerToolIdText);
    headerRefLabel->setBuddy(headerRefText);
#endif // QT_NO_SHORTCUT

    historyGroupBox = new QGroupBox(this);
    historyGroupBox->setObjectName(QString::fromUtf8("historyGroupBox"));
//    QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
//    sizePolicy1.setHorizontalStretch(0);
//    sizePolicy1.setVerticalStretch(9);
//    sizePolicy1.setHeightForWidth(historyGroupBox->sizePolicy().hasHeightForWidth());
//    historyGroupBox->setSizePolicy(sizePolicy1);

    historyGroupBox->setFont(font);
    historyGridLayout = new QGridLayout(historyGroupBox);
    historyGridLayout->setObjectName(QString::fromUtf8("historyGridLayout"));

    hitemTableWidget = new QTableWidget(historyGroupBox);
    hitemTableWidget->setColumnCount(6);
    hitemTableWidget->setRowCount(1);

    QFont font2;
    font2.setBold(false);
    font2.setWeight(50);
    hitemTableWidget->setFont(font2);
    hitemTableWidget->setHorizontalHeaderLabels(QStringList()<<tr("version")<<tr("revision")<<tr("when")<<tr("what")<<tr("why")<<tr("who"));

    QBrush brush(QColor(255, 255, 200, 255));
    brush.setStyle(Qt::SolidPattern);
    QLineEdit *hitemVersionText = new QLineEdit(tr("1.0"));
    hitemVersionText->setStyleSheet(tr("background-color:rgba(255, 255, 200, 255)"));
    hitemVersionText->setFrame(false);
    hitemTableWidget->setCellWidget(0, 0, hitemVersionText);
    QLineEdit *__qtablewidgetitem1 = new QLineEdit(tr("0.1"));
    __qtablewidgetitem1->setStyleSheet(tr("background-color:rgba(255, 255, 200, 255)"));
    __qtablewidgetitem1->setFrame(false);
    hitemTableWidget->setCellWidget(0, 1, __qtablewidgetitem1);
    QDateTimeEdit *__qDateTimeItem = new QDateTimeEdit(this);
    __qDateTimeItem->setDateTime(QDateTime::currentDateTime());
    __qDateTimeItem->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
    __qDateTimeItem->setCalendarPopup(true);
    hitemTableWidget->setCellWidget(0, 2, __qDateTimeItem);
    hitemTableWidget->setColumnWidth(2, 150);


//    QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
//    __qtablewidgetitem2->setBackground(brush);
//    hitemTableWidget->setItem(0, 2, __qtablewidgetitem2);
    QLineEdit *__qtablewidgetitem3 = new QLineEdit(tr("create"));
    __qtablewidgetitem3->setFrame(false);
    hitemTableWidget->setCellWidget(0, 3, __qtablewidgetitem3);
    QLineEdit *__qtablewidgetitem4 = new QLineEdit(tr(""));
    __qtablewidgetitem4->setFrame(false);
    hitemTableWidget->setCellWidget(0, 4, __qtablewidgetitem4);
    QLineEdit *__qtablewidgetitem5 = new QLineEdit(tr("ICD Creator"));
    __qtablewidgetitem5->setFrame(false);
    hitemTableWidget->setCellWidget(0, 5, __qtablewidgetitem5);

//    hitemTableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color:lightyellow;color: black;padding-left: 4px;border: 1px solid #6c6c6c;}");


    hitemTableWidget->setObjectName(QString::fromUtf8("hitemTableWidget"));
//    QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    sizePolicy2.setHorizontalStretch(0);
//    sizePolicy2.setVerticalStretch(9);
//    sizePolicy2.setHeightForWidth(hitemTableWidget->sizePolicy().hasHeightForWidth());
//    hitemTableWidget->setSizePolicy(sizePolicy2);
//    hitemTableWidget->verticalHeader()->setVisible(false);


    addHitemButton = new QPushButton(historyGroupBox);
    addHitemButton->setObjectName(QString::fromUtf8("addHitemButton"));

    deleteHitemButton = new QPushButton(historyGroupBox);
    deleteHitemButton->setObjectName(QString::fromUtf8("deleteHitemButton"));

    historyGridLayout->addWidget(hitemTableWidget, 0, 0, 9, 1);
    historyGridLayout->addWidget(addHitemButton, 0, 1, 1, 1);
    historyGridLayout->addWidget(deleteHitemButton, 1, 1, 1, 1);


    headerVLayout->addWidget(headerGroupBox);
    headerVLayout->addWidget(historyGroupBox);
    headerVLayout->setStretch(2, 10);


    retranslateUi();

    QMetaObject::connectSlotsByName(this);
}

void icdHeaderPage::retranslateUi()
{
    setWindowTitle(QApplication::translate("icdHeaderPage", "icdHeaderPage", 0, QApplication::UnicodeUTF8));
    headerGroupBox->setTitle(QApplication::translate("icdHeaderPage", "Header", 0, QApplication::UnicodeUTF8));
    headerToolIdLabel->setText(QApplication::translate("icdHeaderPage", "toolID", 0, QApplication::UnicodeUTF8));
    headerToolIdCheckBox->setText(QString());
    headerToolIdText->setText(tr("ICD Creator"));
    headerNameStructureCombo->clear();
    headerNameStructureCombo->insertItems(0, QStringList()
     << QApplication::translate("icdHeaderPage", "IEDName", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("icdHeaderPage", "FuncName", 0, QApplication::UnicodeUTF8)
    );
    headerNameStructureLabel->setText(QApplication::translate("icdHeaderPage", "nameStructure", 0, QApplication::UnicodeUTF8));
    headerIdLabel->setText(QApplication::translate("icdHeaderPage", "id", 0, QApplication::UnicodeUTF8));
    headerIdText->setText(tr("GDWY"));
    headerRevisionCheckBox->setText(QString());
    headerRefCheckBox->setText(QString());
    headerRefLabel->setText(QApplication::translate("icdHeaderPage", "Ref", 0, QApplication::UnicodeUTF8));
    headerRevisionLabel->setText(QApplication::translate("icdHeaderPage", "revision", 0, QApplication::UnicodeUTF8));
    headerVersionCheckBox->setText(QString());
    headerVersionLabel->setText(QApplication::translate("icdHeaderPage", "vesion", 0, QApplication::UnicodeUTF8));
    historyGroupBox->setTitle(QApplication::translate("icdHeaderPage", "History", 0, QApplication::UnicodeUTF8));

//    QTableWidgetItem *___qtablewidgetitem = hitemTableWidget->horizontalHeaderItem(0);
//    ___qtablewidgetitem->setText(QApplication::translate("icdHeaderPage", "version", 0, QApplication::UnicodeUTF8));
//    QTableWidgetItem *___qtablewidgetitem1 = hitemTableWidget->horizontalHeaderItem(1);
//    ___qtablewidgetitem1->setText(QApplication::translate("icdHeaderPage", "revision", 0, QApplication::UnicodeUTF8));
//    QTableWidgetItem *___qtablewidgetitem2 = hitemTableWidget->horizontalHeaderItem(2);
//    ___qtablewidgetitem2->setText(QApplication::translate("icdHeaderPage", "when", 0, QApplication::UnicodeUTF8));
//    QTableWidgetItem *___qtablewidgetitem3 = hitemTableWidget->horizontalHeaderItem(3);
//    ___qtablewidgetitem3->setText(QApplication::translate("icdHeaderPage", "what", 0, QApplication::UnicodeUTF8));
//    QTableWidgetItem *___qtablewidgetitem4 = hitemTableWidget->horizontalHeaderItem(4);
//    ___qtablewidgetitem4->setText(QApplication::translate("icdHeaderPage", "why", 0, QApplication::UnicodeUTF8));
//    QTableWidgetItem *___qtablewidgetitem5 = hitemTableWidget->horizontalHeaderItem(5);
//    ___qtablewidgetitem5->setText(QApplication::translate("icdHeaderPage", "who", 0, QApplication::UnicodeUTF8));

    const bool __sortingEnabled = hitemTableWidget->isSortingEnabled();
    hitemTableWidget->setSortingEnabled(false);
    hitemTableWidget->setSortingEnabled(__sortingEnabled);

    addHitemButton->setText(QApplication::translate("icdHeaderPage", "+", 0, QApplication::UnicodeUTF8));
    deleteHitemButton->setText(QApplication::translate("icdHeaderPage", "-", 0, QApplication::UnicodeUTF8));
}

void icdHeaderPage::on_addHitemButton_clicked()
{
    int rowCount = hitemTableWidget->rowCount();
    hitemTableWidget->setRowCount(rowCount + 1);

    QBrush brush(QColor(255, 255, 200, 255));
    brush.setStyle(Qt::SolidPattern);
    QLineEdit *newHitemVersionItem = new QLineEdit(tr(""));
    newHitemVersionItem->setStyleSheet(tr("background-color:rgba(255, 255, 200, 255)"));
    newHitemVersionItem->setFrame(false);
    hitemTableWidget->setCellWidget(rowCount, 0, newHitemVersionItem);
    QLineEdit *newHitemRevisionItem = new QLineEdit(tr(""));
    newHitemRevisionItem->setFrame(false);
    newHitemRevisionItem->setStyleSheet(tr("background-color:rgba(255, 255, 200, 255)"));
    hitemTableWidget->setCellWidget(rowCount, 1, newHitemRevisionItem);
    QDateTimeEdit *newHitemWhenItem = new QDateTimeEdit(this);
    newHitemWhenItem->setDateTime(QDateTime::currentDateTime());
    newHitemWhenItem->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
    newHitemWhenItem->setCalendarPopup(true);
    hitemTableWidget->setCellWidget(rowCount, 2, newHitemWhenItem);
    QLineEdit *newHitemWhatItem = new QLineEdit(tr(""));
    newHitemWhatItem->setFrame(false);
    hitemTableWidget->setCellWidget(rowCount, 3, newHitemWhatItem);
    QLineEdit *newHitemWhyItem = new QLineEdit(tr(""));
    newHitemWhyItem->setFrame(false);
    hitemTableWidget->setCellWidget(rowCount, 4, newHitemWhyItem);
    QLineEdit *newHitemWhoItem = new QLineEdit(tr(""));
    newHitemWhoItem->setFrame(false);
    hitemTableWidget->setCellWidget(rowCount, 5, newHitemWhoItem);

}

void icdHeaderPage::on_deleteHitemButton_clicked()
{
    int currentRow = hitemTableWidget->currentRow();
    if(currentRow < 0)
        currentRow = hitemTableWidget->rowCount() - 1;

    hitemTableWidget->removeRow(currentRow);
}

void icdHeaderPage::registerData()
{
    registerField("headerId*", headerIdText);
    registerField("headerNameStructure*", headerNameStructureCombo);
    registerField("headerVersionIsChecked", headerVersionCheckBox);
    if(field("headerVersionIsChecked").toBool())
        registerField("headerVersion", headerVersionText);
    registerField("headerRevisionIsChecked", headerVersionCheckBox);
    if(field("headerRevisionIsChecked").toBool())
        registerField("headerRevision", headerRevisionText);
    registerField("headerTooIdIsChecked", headerVersionCheckBox);
    if(field("headerTooIdIsChecked").toBool())
        registerField("headerToolId", headerToolIdText);
    registerField("headerRefIsChecked", headerVersionCheckBox);
    if(field("headerRefIsChecked").toBool())
        registerField("headerRef", headerRefText);

    QString hitem_suffix = "_";
    for(int i = 0; i < hitemTableWidget->rowCount(); i++) {
        hitem_suffix += QString::number(i, 10);
        registerField("hitemVersion"+hitem_suffix+"*", hitemTableWidget->cellWidget(i,0));
        registerField("hitemRevision"+hitem_suffix+"*", hitemTableWidget->cellWidget(i,1));
        registerField("hitemWhen"+hitem_suffix+"*", hitemTableWidget->cellWidget(i,2));
        registerField("hitemWhat"+hitem_suffix, hitemTableWidget->cellWidget(i,3));
        registerField("hitemWhy"+hitem_suffix, hitemTableWidget->cellWidget(i,4));
        registerField("hitemWho"+hitem_suffix, hitemTableWidget->cellWidget(i,5));
    }

}
