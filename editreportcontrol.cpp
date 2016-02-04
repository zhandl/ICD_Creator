#include "editreportcontrol.h"
#include "domitem.h"

EditReportControl::EditReportControl(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle(tr("Add Text"));
    target = NULL;
    init();
}


EditReportControl::~EditReportControl()
{

}

void EditReportControl::init()
{
    layout = new QGridLayout(this);
    layout->setObjectName(tr("layout"));

    nameLabel = new QLabel(this);
    nameLabel->setObjectName(tr("nameLabel"));
    nameLabel->setText(tr("name: "));
    nameText = new QLineEdit(this);
    nameText->setObjectName(tr("nameText"));

    confRevLabel = new QLabel(this);
    confRevLabel->setObjectName(tr("confRevLabel"));
    confRevLabel->setText(tr("confRev: "));
    confRevSpinBox = new QSpinBox(this);
    confRevSpinBox->setObjectName(tr("confRevText"));
    confRevSpinBox->setMinimum(0);

    rptIdCheckBox = new QCheckBox(this);
    rptIdCheckBox->setObjectName(tr("rptIdCheckBox"));
    rptIdLabel = new QLabel(this);
    rptIdLabel->setObjectName(tr("rptIdLabel"));
    rptIdLabel->setText(tr("rptID: "));
    rptIdText = new QLineEdit(this);
    rptIdText->setObjectName(tr("rptIdText"));

    bufferedCheckBox = new QCheckBox(this);
    bufferedCheckBox->setObjectName(tr("bufferedCheckBox"));
    bufferedLabel = new QLabel(this);
    bufferedLabel->setObjectName(tr("bufferedLabel"));
    bufferedLabel->setText(tr("buffered: "));
    bufferedComboBox = new QComboBox(this);
    bufferedComboBox->setObjectName(tr("bufferedComboBox"));

    bufTimeCheckBox = new QCheckBox(this);
    bufTimeCheckBox->setObjectName(tr("bufTimeCheckBox"));
    bufTimeLabel = new QLabel(this);
    bufTimeLabel->setObjectName(tr("bufTimeLabel"));
    bufTimeLabel->setText(tr("bufTime: "));
    bufTimeSpinBox = new QSpinBox(this);
    bufTimeSpinBox->setObjectName(tr("bufTimeSpinBox"));
    bufTimeSpinBox->setMinimum(0);

    indexedCheckBox = new QCheckBox(this);
    indexedCheckBox->setObjectName(tr("indexedCheckBox"));
    indexedLabel = new QLabel(this);
    indexedLabel->setObjectName(tr("indexedLabel"));
    indexedLabel->setText(tr("indexed: "));
    indexedComboBox = new QComboBox(this);
    indexedComboBox->setObjectName(tr("indexedComboBox"));

    datSetCheckBox = new QCheckBox(this);
    datSetCheckBox->setObjectName(tr("datSetCheckBox"));
    datSetLabel = new QLabel(this);
    datSetLabel->setObjectName(tr("datSetLabel"));
    datSetLabel->setText(tr("datSet: "));
    datSetText = new QLineEdit(this);
    datSetText->setObjectName(tr("datSetText"));

    descCheckBox = new QCheckBox(this);
    descCheckBox->setObjectName(tr("descCheckBox"));
    descLabel = new QLabel(this);
    descLabel->setObjectName(tr("descLabel"));
    descLabel->setText(tr("desc: "));
    descText = new QLineEdit(this);
    descText->setObjectName(tr("descText"));

    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName(tr("buttonBox"));

    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    buttonBox->setCenterButtons(false);

    layout->addWidget(nameLabel, 0, 1, 1, 1);
    layout->addWidget(nameText, 0, 2, 1, 1);
    layout->addWidget(confRevLabel, 0, 4, 1, 1);
    layout->addWidget(confRevSpinBox, 0, 5, 1, 1);
    layout->addWidget(rptIdCheckBox, 1, 0, 1, 1);
    layout->addWidget(rptIdLabel, 1, 1, 1, 1);
    layout->addWidget(rptIdText, 1, 2, 1, 1);
    layout->addWidget(bufferedCheckBox, 1, 3, 1, 1);
    layout->addWidget(bufferedLabel, 1, 4, 1, 1);
    layout->addWidget(bufferedComboBox, 1, 5, 1, 1);
    layout->addWidget(bufTimeCheckBox, 2, 0, 1, 1);
    layout->addWidget(bufTimeLabel, 2, 1, 1, 1);
    layout->addWidget(bufTimeSpinBox, 2, 2, 1, 1);
    layout->addWidget(indexedCheckBox, 2, 3, 1, 1);
    layout->addWidget(indexedLabel, 2, 4, 1, 1);
    layout->addWidget(indexedComboBox, 2, 5, 1, 1);
    layout->addWidget(datSetCheckBox, 3, 0, 1, 1);
    layout->addWidget(datSetLabel, 3, 1, 1, 1);
    layout->addWidget(datSetText, 3, 2, 1, 1);
    layout->addWidget(descCheckBox, 3, 3, 1, 1);
    layout->addWidget(descLabel, 3, 4, 1, 1);
    layout->addWidget(descText, 3, 5, 1, 1);
    layout->addWidget(buttonBox, 4, 5, 1, 1);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

void EditReportControl::setTarget(DomItem *item)
{
    target = item;
}

void EditReportControl::accept()
{
    if(descCheckBox->isChecked()) {
        target->addAttribute("desc", descText->text());
    }

//    target->isMixedContent() = true;

    QDialog::accept();
}
