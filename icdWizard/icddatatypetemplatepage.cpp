#include "icddatatypetemplatepage.h"

icdDataTypeTemplatePage::icdDataTypeTemplatePage(QWidget *parent) :
    QWizardPage(parent)
{
    setTitle(tr("DataType Template Selected"));
    setSubTitle(tr("This page introduce user to select the dataType template file"));

    init();
}


void icdDataTypeTemplatePage::init()
{
    setObjectName(tr("icdDataTypeTemplate"));
    resize(800, 600);

    dataTypeTemplateGridLayout = new QGridLayout(this);
    dataTypeTemplateGridLayout->setAlignment(Qt::AlignCenter);
    dataTypeTemplateGridLayout->setContentsMargins(50, 20, 50, 20);


    fileSelectRadio = new QRadioButton(this);
    fileSelectRadio->setObjectName(tr("fileSelectRadio"));
    fileSelectRadio->setText(tr("use the exist DataType template file"));
    fileSelectLabel = new QLabel(this);
    fileSelectLabel->setObjectName(tr("fileSelectLabel"));
    fileSelectLabel->setText(tr("choose the template file: "));
    fileSelectText = new QLineEdit(this);
    fileSelectText->setObjectName(tr("fileSelectText"));
    fileSelectButton = new QPushButton(this);
    fileSelectButton->setObjectName(tr("fileSelectButton"));
    fileSelectButton->setText(tr("..."));

    newTemplateRadio = new QRadioButton(this);
    newTemplateRadio->setObjectName(tr("newTemplateRadio"));
    newTemplateRadio->setText(tr("create a new template"));
    newTemplateText = new QTextBrowser(this);
    newTemplateText->setObjectName(tr("newTemplateText"));
    newTemplateText->setHtml(QApplication::translate("icdDataTypeTemplate", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
                             "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
                             "p, li { white-space: pre-wrap; }\n"
                             "</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
                             "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">This wizard will lead user to create a new DataType template file based on the IEC 61850-7</p></body></html>", 0, QApplication::UnicodeUTF8));
    newTemplateText->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    dataTypeTemplateGridLayout->addWidget(fileSelectRadio, 1, 0, 1, 4);
    dataTypeTemplateGridLayout->addWidget(fileSelectLabel, 2, 1, 1, 1);
    dataTypeTemplateGridLayout->addWidget(fileSelectText, 2, 2, 1, 1);
    dataTypeTemplateGridLayout->addWidget(fileSelectButton, 2, 3, 1, 1);
    dataTypeTemplateGridLayout->addWidget(newTemplateRadio, 4, 0, 1, 4);
    dataTypeTemplateGridLayout->addWidget(newTemplateText, 5, 1, 1, 3);
    dataTypeTemplateGridLayout->setRowStretch(0, 1);
    dataTypeTemplateGridLayout->setRowStretch(3, 1);
    dataTypeTemplateGridLayout->setRowStretch(6, 1);
}
