
#include "configurationgeneraloptions.h"
#include "utils.h"
#include "config.h"
#include "domitem.h"

ConfigurationGeneralOptions::ConfigurationGeneralOptions(QWidget *parent) :
    QWidget(parent)
{
    _started = false;
    setupUi();

    _elementFontSize = 0 ;
    _elementFontItalic = false ;
    _elementFontBold = false ;
}

ConfigurationGeneralOptions::~ConfigurationGeneralOptions()
{
}

void ConfigurationGeneralOptions::setupUi()
{
    if (objectName().isEmpty())
        setObjectName(QString::fromUtf8("ConfigurationGeneralOptions"));
    resize(799, 426);
    verticalLayout_2 = new QVBoxLayout(this);
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    label = new QLabel(this);
    label->setObjectName(QString::fromUtf8("label"));
    QFont font;
    font.setPointSize(12);
    font.setBold(true);
    font.setWeight(75);
    label->setFont(font);

    verticalLayout_2->addWidget(label);

    verticalLayout = new QVBoxLayout();
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    verticalLayout->setContentsMargins(20, -1, -1, -1);
    showWelcomePage = new QCheckBox(this);
    showWelcomePage->setObjectName(QString::fromUtf8("showWelcomePage"));

    verticalLayout->addWidget(showWelcomePage);

    autoscroll = new QCheckBox(this);
    autoscroll->setObjectName(QString::fromUtf8("autoscroll"));

    verticalLayout->addWidget(autoscroll);


    verticalLayout_2->addLayout(verticalLayout);

    label_2 = new QLabel(this);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setFont(font);

    verticalLayout_2->addWidget(label_2);

    gridLayout = new QGridLayout();
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    enableEFontSize = new QCheckBox(this);
    enableEFontSize->setObjectName(QString::fromUtf8("enableEFontSize"));

    gridLayout->addWidget(enableEFontSize, 0, 0, 1, 1);

    elementFontSummary = new QLabel(this);
    elementFontSummary->setObjectName(QString::fromUtf8("elementFontSummary"));
    elementFontSummary->setFrameShape(QFrame::Panel);
    elementFontSummary->setFrameShadow(QFrame::Sunken);
    elementFontSummary->setLineWidth(2);

    gridLayout->addWidget(elementFontSummary, 0, 1, 1, 1);

    changeElementsFont = new QPushButton(this);
    changeElementsFont->setObjectName(QString::fromUtf8("changeElementsFont"));

    gridLayout->addWidget(changeElementsFont, 0, 2, 1, 1);

    enableFWAFont = new QCheckBox(this);
    enableFWAFont->setObjectName(QString::fromUtf8("enableFWAFont"));

    gridLayout->addWidget(enableFWAFont, 1, 0, 1, 1);

    fixedSizeAttrComboFont = new QFontComboBox(this);
    fixedSizeAttrComboFont->setObjectName(QString::fromUtf8("fixedSizeAttrComboFont"));
    fixedSizeAttrComboFont->setEnabled(true);
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(fixedSizeAttrComboFont->sizePolicy().hasHeightForWidth());
    fixedSizeAttrComboFont->setSizePolicy(sizePolicy);

    gridLayout->addWidget(fixedSizeAttrComboFont, 1, 1, 1, 1);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    label_4 = new QLabel(this);
    label_4->setObjectName(QString::fromUtf8("label_4"));

    horizontalLayout->addWidget(label_4);

    fixedSizeAttributeFontSize = new QSpinBox(this);
    fixedSizeAttributeFontSize->setObjectName(QString::fromUtf8("fixedSizeAttributeFontSize"));
    fixedSizeAttributeFontSize->setEnabled(true);
    fixedSizeAttributeFontSize->setMinimum(1);

    horizontalLayout->addWidget(fixedSizeAttributeFontSize);


    gridLayout->addLayout(horizontalLayout, 1, 2, 1, 1);


    verticalLayout_2->addLayout(gridLayout);

    enableAdvancedAttributesDisplay = new QCheckBox(this);
    enableAdvancedAttributesDisplay->setObjectName(QString::fromUtf8("enableAdvancedAttributesDisplay"));

    verticalLayout_2->addWidget(enableAdvancedAttributesDisplay);

    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    enableLogs = new QCheckBox(this);
    enableLogs->setObjectName(QString::fromUtf8("enableLogs"));

    horizontalLayout_2->addWidget(enableLogs);

    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

    horizontalLayout_2->addItem(horizontalSpacer);

    label_3 = new QLabel(this);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    horizontalLayout_2->addWidget(label_3);

    logLevelCombo = new QComboBox(this);
    logLevelCombo->setObjectName(QString::fromUtf8("logLevelCombo"));

    horizontalLayout_2->addWidget(logLevelCombo);

    horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_2->addItem(horizontalSpacer_2);


    verticalLayout_2->addLayout(horizontalLayout_2);

    expandTreeAfterLoad = new QCheckBox(this);
    expandTreeAfterLoad->setObjectName(QString::fromUtf8("expandTreeAfterLoad"));

    verticalLayout_2->addWidget(expandTreeAfterLoad);

    label_7 = new QLabel(this);
    label_7->setObjectName(QString::fromUtf8("label_7"));
    label_7->setEnabled(true);
    QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
    label_7->setSizePolicy(sizePolicy1);

    verticalLayout_2->addWidget(label_7);


    retranslateUi();

    QMetaObject::connectSlotsByName(this);
}

void ConfigurationGeneralOptions::retranslateUi()
{
    setWindowTitle(QApplication::translate("ConfigurationGeneralOptions", "Form", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("ConfigurationGeneralOptions", "Behavior", 0, QApplication::UnicodeUTF8));
    showWelcomePage->setText(QApplication::translate("ConfigurationGeneralOptions", "Show welcome page", 0, QApplication::UnicodeUTF8));
    autoscroll->setText(QApplication::translate("ConfigurationGeneralOptions", "Autoscroll in the elements tree", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("ConfigurationGeneralOptions", "Appearance", 0, QApplication::UnicodeUTF8));
    enableEFontSize->setText(QApplication::translate("ConfigurationGeneralOptions", "Override the font for elements display", 0, QApplication::UnicodeUTF8));
    elementFontSummary->setText(QApplication::translate("ConfigurationGeneralOptions", "<Not Set>", 0, QApplication::UnicodeUTF8));
    changeElementsFont->setText(QApplication::translate("ConfigurationGeneralOptions", "change font...", 0, QApplication::UnicodeUTF8));
    enableFWAFont->setText(QApplication::translate("ConfigurationGeneralOptions", "Override the font for fixed spacing attributes ", 0, QApplication::UnicodeUTF8));
    label_4->setText(QApplication::translate("ConfigurationGeneralOptions", "size", 0, QApplication::UnicodeUTF8));
    enableAdvancedAttributesDisplay->setText(QApplication::translate("ConfigurationGeneralOptions", "Advanced attributes display (experimental)", 0, QApplication::UnicodeUTF8));
    enableLogs->setText(QApplication::translate("ConfigurationGeneralOptions", "Enable Logs", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("ConfigurationGeneralOptions", "Level:", 0, QApplication::UnicodeUTF8));
    expandTreeAfterLoad->setText(QApplication::translate("ConfigurationGeneralOptions", "Automatically expand editor tree when loading data", 0, QApplication::UnicodeUTF8));
    label_7->setText(QApplication::translate("ConfigurationGeneralOptions", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Arial'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<table border=\"0\" style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; font-weight:600;\">Warning</span><span style=\" font-size:9pt;\">: changes will be applied only after a program restart.</span></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
}

void ConfigurationGeneralOptions::init(QXmlEditData *data)
{
    _data = data;
    _started = true ;
    fixedSizeAttrComboFont->setFontFilters(QFontComboBox::MonospacedFonts);
    showWelcomePage->setChecked(data->isWelcomeDialogEnabled());
    autoscroll->setChecked(data->isAutoScroll());

    int fontIndex;
    QString font = Config::getString(Config::KEY_ELEMENT_FONTFIXEDWIDTHFAMILY, DEFAULT_FIXEDWIDTHFONT);
    fontIndex = fixedSizeAttrComboFont->findText(font);
    if(fontIndex >= 0) {
        fixedSizeAttrComboFont->setCurrentIndex(fontIndex);
    }
    enableFWAFont->setCheckState(Config::getBool(Config::KEY_ELEMENT_FONTFIXEDWIDTHENABLED, false) ? Qt::Checked : Qt::Unchecked);
    fixedSizeAttributeFontSize->setValue(Config::getInt(Config::KEY_ELEMENT_FONTFIXEDWIDTHSIZE, 0));

    enableEFontSize->setChecked(Config::getBool(Config::KEY_ELEMENT_ELEMENTFONTENABLED, false));
    _elementFontName = Config::getString(Config::KEY_ELEMENT_ELEMENTFONTFAMILY, "");
    _elementFontSize = Config::getInt(Config::KEY_ELEMENT_ELEMENTFONTSIZE, 0);
    _elementFontItalic = Config::getBool(Config::KEY_ELEMENT_ELEMENTFONTITALIC, false);
    _elementFontBold = Config::getBool(Config::KEY_ELEMENT_ELEMENTFONTBOLD, false);

    setElementFontInfo();
    checkEnablingStatus();

    enableAdvancedAttributesDisplay->setChecked(Config::getBool(Config::KEY_VIEW_ITEMRENDERERATTR, false));

    enableLogs->setChecked(Config::getBool(Config::KEY_LOGS_ENABLED, false));
    logLevelCombo->addItem(tr("debug"), FrwLogger::DEBUG);
    logLevelCombo->addItem(tr("info"), FrwLogger::INFO);
    logLevelCombo->addItem(tr("warning"), FrwLogger::WARNING);
    logLevelCombo->addItem(tr("error"), FrwLogger::ERROR);
    Utils::selectComboValue(logLevelCombo, Config::getInt(Config::KEY_LOGS_LEVEL, FrwLogger::INFO));
    expandTreeAfterLoad->setChecked(Config::getBool(Config::KEY_MAIN_EXPANDONLOAD, true));
}

void ConfigurationGeneralOptions::checkEnablingStatus()
{
    bool isEFChecked = enableEFontSize->isChecked();
    changeElementsFont->setEnabled(isEFChecked);
    elementFontSummary->setEnabled(isEFChecked);
    bool isFWAttrFontEnabled = enableFWAFont->isChecked();
    fixedSizeAttrComboFont->setEnabled(isFWAttrFontEnabled);
    fixedSizeAttributeFontSize->setEnabled(isFWAttrFontEnabled);
}

void ConfigurationGeneralOptions::save()
{
    _data->enableWelcomeDialog(showWelcomePage->isChecked());
    _data->enableAutoscroll(autoscroll->isChecked());
    Config::saveBool(Config::KEY_MAIN_EXPANDONLOAD, expandTreeAfterLoad->isChecked()) ;
}

void ConfigurationGeneralOptions::saveIfChanged()
{
    save();
}

void ConfigurationGeneralOptions::on_enableAdvancedAttributesDisplay_stateChanged(int status)
{
    if(!_started) {
        return ;
    }
    bool isEnabled = (status == Qt::Checked) ? true : false;
    Config::saveBool(Config::KEY_VIEW_ITEMRENDERERATTR, isEnabled) ;
}

void ConfigurationGeneralOptions::on_logLevelCombo_currentIndexChanged(int index)
{
    if(!_started) {
        return ;
    }
    int newLevel = logLevelCombo->itemData(index).toInt();
    Config::saveInt(Config::KEY_LOGS_LEVEL, newLevel);
    if(NULL != _data->logger()) {
        _data->logger()->setLevel((FrwLogger::ELogLevel)newLevel);
    }

}

void ConfigurationGeneralOptions::on_enableLogs_stateChanged(int state)
{
    if(!_started) {
        return ;
    }
    bool isEnabled = (state == Qt::Checked) ? true : false;
    Config::saveBool(Config::KEY_LOGS_ENABLED, isEnabled);
    if(NULL != _data->logger()) {
        _data->logger()->setEnabled(isEnabled);
    }
}

void ConfigurationGeneralOptions::on_fixedSizeAttrComboFont_currentFontChanged(const QFont & font)
{
    if(!_started) {
        return ;
    }
    Config::saveString(Config::KEY_ELEMENT_FONTFIXEDWIDTHFAMILY, font.family());
}

void ConfigurationGeneralOptions::on_enableFWAFont_stateChanged(int state)
{
    if(!_started) {
        return ;
    }
    bool isEnabled = (state == Qt::Checked) ? true : false;
    Config::saveBool(Config::KEY_ELEMENT_FONTFIXEDWIDTHENABLED, isEnabled);
    checkEnablingStatus();
}

void ConfigurationGeneralOptions::on_fixedSizeAttributeFontSize_valueChanged(int value)
{
    if(!_started) {
        return ;
    }
    Config::saveInt(Config::KEY_ELEMENT_FONTFIXEDWIDTHSIZE, value);
}

void ConfigurationGeneralOptions::on_enableEFontSize_stateChanged(int state)
{
    if(!_started) {
        return ;
    }
    bool isEnabled = (state == Qt::Checked);
    Config::saveBool(Config::KEY_ELEMENT_ELEMENTFONTENABLED, isEnabled);
    checkEnablingStatus();
}

void ConfigurationGeneralOptions::on_changeElementsFont_clicked()
{
    if(!_started) {
        return ;
    }

    bool isOk;
    QFont selectedFont = QFontDialog::getFont(&isOk, QFont(_elementFontName, _elementFontSize, _elementFontBold ? QFont::Bold : -1, _elementFontItalic), this, tr("Select the font for elements text display")) ;
    if(isOk) {
        _elementFontName = selectedFont.family();
        _elementFontSize = selectedFont.pointSize();
        _elementFontItalic = selectedFont.italic();
        _elementFontBold = selectedFont.bold();
        // save
        Config::saveString(Config::KEY_ELEMENT_ELEMENTFONTFAMILY, _elementFontName);
        Config::saveInt(Config::KEY_ELEMENT_ELEMENTFONTSIZE, _elementFontSize);
        Config::saveBool(Config::KEY_ELEMENT_ELEMENTFONTITALIC, _elementFontItalic);
        Config::saveBool(Config::KEY_ELEMENT_ELEMENTFONTBOLD, _elementFontBold);
        setElementFontInfo();
    }
}

void ConfigurationGeneralOptions::setElementFontInfo()
{
    if(!_started) {
        return ;
    }
    QString fontName ;
    if(_elementFontName .isEmpty()) {
        fontName  = tr("<Not set>");
    } else {
        fontName = QString(tr("%1%2%3, %4")).arg(_elementFontName).arg((_elementFontBold ? tr(" bold") : "")).arg((_elementFontItalic ? tr(" italic") : "")).arg(_elementFontSize);
    }
    elementFontSummary->setText(fontName);
}

