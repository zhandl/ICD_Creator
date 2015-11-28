#include "edittextnode.h"

#include "icdCreator.h"
#include "edittextnode.h"
#include "utils.h"

const int EditTextNode::InputSizeLimit = 1024 * 1024;

EditTextNode::EditTextNode(const bool isBase64Value, QWidget * parent) : QDialog(parent)
{
    init();
    target = "";
    connect(wrapText, SIGNAL(stateChanged(int)), this, SLOT(onWrapChanged(int)));
    wrapText->setChecked(false);
    isBase64 = isBase64Value ;
    if(isBase64) {
        fromBase64->setVisible(false);
        fromBase64->setEnabled(false);
        toBase64->setVisible(false);
        toBase64->setEnabled(false);
    }
}

EditTextNode::~EditTextNode()
{
    disconnect(wrapText, SIGNAL(stateChanged(int)), this, SLOT(onWrapChanged(int)));
}

void EditTextNode::init()
{
    if(objectName().isEmpty())
        setObjectName(QString::fromUtf8("EditTN"));
    resize(712, 546);
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    setSizePolicy(sizePolicy);
    setSizeGripEnabled(false);
    horizontalLayout_2 = new QHBoxLayout(this);
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    editor = new QPlainTextEdit(this);
    editor->setObjectName(QString::fromUtf8("editor"));
    editor->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    editor->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    editor->setLineWrapMode(QPlainTextEdit::NoWrap);

    horizontalLayout->addWidget(editor);

    verticalLayout = new QVBoxLayout();
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(buttonBox->sizePolicy().hasHeightForWidth());
    buttonBox->setSizePolicy(sizePolicy1);
    buttonBox->setCursor(QCursor(Qt::ArrowCursor));
    buttonBox->setOrientation(Qt::Vertical);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    buttonBox->setCenterButtons(true);

    verticalLayout->addWidget(buttonBox);

    verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout->addItem(verticalSpacer);

    wrapText = new QCheckBox(this);
    wrapText->setObjectName(QString::fromUtf8("wrapText"));

    verticalLayout->addWidget(wrapText);

    verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout->addItem(verticalSpacer_2);

    label = new QLabel(this);
    label->setObjectName(QString::fromUtf8("label"));
    QFont font;
    font.setBold(true);
    font.setWeight(75);
    label->setFont(font);
    label->setAlignment(Qt::AlignCenter);

    verticalLayout->addWidget(label);

    fromBase64 = new QPushButton(this);
    fromBase64->setObjectName(QString::fromUtf8("fromBase64"));

    verticalLayout->addWidget(fromBase64);

    toBase64 = new QPushButton(this);
    toBase64->setObjectName(QString::fromUtf8("toBase64"));

    verticalLayout->addWidget(toBase64);

    label_2 = new QLabel(this);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setFont(font);
    label_2->setAlignment(Qt::AlignCenter);

    verticalLayout->addWidget(label_2);

    loadFromBinaryFile = new QPushButton(this);
    loadFromBinaryFile->setObjectName(QString::fromUtf8("loadFromBinaryFile"));

    verticalLayout->addWidget(loadFromBinaryFile);

    saveBase64IntoFile = new QPushButton(this);
    saveBase64IntoFile->setObjectName(QString::fromUtf8("saveBase64IntoFile"));

    verticalLayout->addWidget(saveBase64IntoFile);


    horizontalLayout->addLayout(verticalLayout);


    horizontalLayout_2->addLayout(horizontalLayout);


    retranslate();
    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QMetaObject::connectSlotsByName(this);
}

void EditTextNode::retranslate()
{
    setWindowTitle(QApplication::translate("EditTN", "Edit Text Node", 0, QApplication::UnicodeUTF8));
    wrapText->setText(QApplication::translate("EditTN", "wrap text", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("EditTN", "Base 64 Text", 0, QApplication::UnicodeUTF8));
    fromBase64->setText(QApplication::translate("EditTN", "From Base 64", 0, QApplication::UnicodeUTF8));
    fromBase64->setShortcut(QApplication::translate("EditTN", "Ctrl+S", 0, QApplication::UnicodeUTF8));
    toBase64->setText(QApplication::translate("EditTN", "To Base 64", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("EditTN", "Binary to Base 64", 0, QApplication::UnicodeUTF8));
    loadFromBinaryFile->setText(QApplication::translate("EditTN", "Load from file...", 0, QApplication::UnicodeUTF8));
    saveBase64IntoFile->setText(QApplication::translate("EditTN", "Save to file...", 0, QApplication::UnicodeUTF8));
} // retranslateUi

void EditTextNode::setWrapMode(const bool wrap)
{
    editor->setLineWrapMode(wrap ? QPlainTextEdit::WidgetWidth : QPlainTextEdit::NoWrap);
}

void EditTextNode::onWrapChanged(int newState)
{
    setWrapMode((Qt::Checked == newState)) ;
}

void EditTextNode::setText(const QString &theText)
{
    target = theText ;
    editor->setPlainText(target);
}

QString EditTextNode::getText() const
{
    return target ;
}

void EditTextNode::accept()
{
    target = editor->toPlainText();
    QDialog::accept();
}

void EditTextNode::error(const QString& message)
{
    Utils::error(this, message);
}


void EditTextNode::on_fromBase64_clicked()
{
    QString text = editor->toPlainText();
    QByteArray array(text.toAscii());
    QByteArray array2 = QByteArray::fromBase64(array);
    editor->setPlainText(array2.data());
    /*QByteArray array(ui.editor->toPlainText());
    array.fromBase64();
    ui.editor->setPlainText(array.data());*/
}

void EditTextNode::on_toBase64_clicked()
{
    QByteArray array(editor->toPlainText().toAscii());
    QByteArray converted = array.toBase64();
    QString strBase64 = converted.data();
    editor->setPlainText(strBase64);
}


void EditTextNode::on_loadFromBinaryFile_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,
                       tr("Choose a File to be Transformed in Base 64 Encoded Text"),
                       "", tr("All files (*);;XML files (*.xml);;XML Schema files (*.xsd);;"));
    if(!filePath.isEmpty()) {
        onLoadFromBinaryFile(filePath);
    }
}

bool EditTextNode::onLoadFromBinaryFile(const QString &filePath)
{
    bool isError = true ;
    bool isAbort = false ;
    QFile file(filePath);
    QByteArray data ;
    if(file.open(QIODevice::ReadOnly)) {
        qint64 fileSize = file.size();
        if(fileSize > InputSizeLimit) {
            if(!Utils::askYN(this, tr("Warning: the size of the file to import is %1. Do you want to continue?").arg(Utils::getSizeForPresentation(fileSize)))) {
                isAbort = true ;
                isError = false ;
            }
        }
        if(!isAbort) {
            data = file.readAll();
            if(file.error() == QFile::NoError) {
                isError = false ;
            }
        }
        file.close();
        if(isError) {
            Utils::error(tr("Error reading file."));
        } else {
            QByteArray converted = data.toBase64();
            QString strBase64 = converted.data();
            editor->setPlainText(strBase64);
        }
    } else {
        Utils::error(QString(tr("Unable to load file.\nError code is '%1'")).arg(file.error()));
    }
    return !isError ;
}

void EditTextNode::on_saveBase64IntoFile_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save Base 64 Coded Data to File"),
                       "", tr("XML files (*.xml);;XML Schema files (*.xsd);;All files (*);;"));
    if(!filePath.isEmpty()) {
        saveToBinaryFile(filePath);
    }
}

void EditTextNode::saveToBinaryFile(const QString &filePath)
{
    bool isError = true ;
    QFile file(filePath);
    if(file.open(QIODevice::WriteOnly)) {
        QString text = editor->toPlainText();
        QByteArray array(text.toAscii());
        QByteArray binaryArray = QByteArray::fromBase64(array);
        if(-1 != file.write(binaryArray)) {
            isError = false ;
        }
        file.close();
        if(file.error() != QFile::NoError) {
            isError = true ;
        }

        if(isError) {
            Utils::error(tr("Error writing to file."));
        }
    } else {
        Utils::error(QString(tr("Unable to open file.\n Error code is '%1'")).arg(file.error()));
    }
}

bool EditTextNode::testLoadBinaryFile(const QString &filePath)
{
    return onLoadFromBinaryFile(filePath);
}
