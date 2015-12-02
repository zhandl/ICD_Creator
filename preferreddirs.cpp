#include "preferreddirs.h"
#include "utils.h"
#include "qxmledit.h"
#include <QFileDialog>
#include <QVariant>

bool configurePreferredDirs(QWidget *parent, QStringList &originalValues)
{
    PreferredDirs editDirs(originalValues, parent);
    editDirs.setModal(true);
    if(editDirs.exec() == QDialog::Accepted) {
        return true;
    }
    return false;
}

PreferredDirs::PreferredDirs(QStringList &theOriginalValues, QWidget *parent) :
    QDialog(parent),
    originalValues(theOriginalValues),
    dirs(theOriginalValues),
    model(NULL)
{
    init();
    dirList->setSelectionMode(QAbstractItemView::SingleSelection);
    fillData();
    handleSelects(false);
}

PreferredDirs::~PreferredDirs()
{

}


void PreferredDirs::init()
{
    if (objectName().isEmpty())
        setObjectName(QString::fromUtf8("PreferredDirs"));
    resize(510, 318);
    horizontalLayout = new QHBoxLayout(this);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    verticalLayout_2 = new QVBoxLayout();
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    label = new QLabel(this);
    label->setObjectName(QString::fromUtf8("label"));

    verticalLayout_2->addWidget(label);

    dirList = new QListView(this);
    dirList->setObjectName(QString::fromUtf8("dirList"));
    dirList->setModelColumn(0);
    dirList->setUniformItemSizes(false);

    verticalLayout_2->addWidget(dirList);


    horizontalLayout->addLayout(verticalLayout_2);

    verticalLayout = new QVBoxLayout();
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setOrientation(Qt::Vertical);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

    verticalLayout->addWidget(buttonBox);

    verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout->addItem(verticalSpacer);

    add = new QPushButton(this);
    add->setObjectName(QString::fromUtf8("add"));

    verticalLayout->addWidget(add);

    remove = new QPushButton(this);
    remove->setObjectName(QString::fromUtf8("remove"));

    verticalLayout->addWidget(remove);


    horizontalLayout->addLayout(verticalLayout);


    retranslateUi();
    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QMetaObject::connectSlotsByName(this);
}

void PreferredDirs::retranslateUi()
{
    setWindowTitle(QApplication::translate("PreferredDirs", "Preferred directories", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("PreferredDirs", "Preferred directories", 0, QApplication::UnicodeUTF8));
    add->setText(QApplication::translate("PreferredDirs", "Add...", 0, QApplication::UnicodeUTF8));
    remove->setText(QApplication::translate("PreferredDirs", "Remove", 0, QApplication::UnicodeUTF8));
}

void PreferredDirs::changeEvent(QEvent *e)
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

void PreferredDirs::fillData()
{
    model = new QStringListModel(this);
    model->setStringList(dirs);
    dirList->setModel(model);
}

bool PreferredDirs::checkNewDir(const int size, const bool isUI)
{
    if(size >= QXmlEditParameters::NUM_PREF_DIRS) {
        if(isUI) {
            Utils::error(tr("Reached the maxmimum number of directories. Cannot add another one"));
        }
        return false;
    }
    return true;
}

bool PreferredDirs::checkDuplicateDir(QStringList &list, const QString &newDir, const bool isUI)
{
    if(list.contains(newDir)) {
        if(isUI) {
            Utils::error(tr("Directory is already in the list"));
        }
        return false;
    }
    return true;
}

void PreferredDirs::on_add_clicked()
{
    if(!PreferredDirs::checkNewDir(model->rowCount(), true)) {
        return ;
    }
    QString dirPath = QFileDialog::getExistingDirectory(this, tr("Choose the directory"),
                                                        "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(!dirPath.isEmpty()) {
        QStringList dirList = model->stringList();
        if(!checkDuplicateDir(dirList, dirPath, true)) {
            return ;
        }
        if(model->insertRow(model->rowCount())) {
            QModelIndex index = model->index(model->rowCount() - 1, 0);
            if(!(model->setData(index, QVariant(dirPath)))) {
                Utils::error(this, tr("Unable to register data"));
            }
        } else {
            Utils::error(this, tr("Unable to make room for data"));
        }
    }
}

void PreferredDirs::on_dirList_clicked(const QModelIndex &index)
{
    bool isValid = index.isValid();
    handleSelects(isValid);
}

void PreferredDirs::handleSelects(const bool isItemValid)
{
    remove->setEnabled(isItemValid);
}

void PreferredDirs::on_remove_clicked()
{
    QModelIndex index = dirList->currentIndex();
    if(index.isValid()) {
        if(Utils::askYN(this, tr("Really delete selected item?"))) {
            model->removeRow(index.row());
            handleSelects(dirList->currentIndex().isValid());
        }
    }
}

void PreferredDirs::accept()
{
    originalValues = model->stringList();
    QDialog::accept();
}
