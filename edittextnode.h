#ifndef EDITTEXTNODE_H
#define EDITTEXTNODE_H

#include <QtGui>

#include <QDialog>

class EditTextNode : public QDialog
{
    Q_OBJECT

    static const int InputSizeLimit;
    QString target;

public:
    EditTextNode(const bool isBase64Value, QWidget * parent = NULL);
    ~EditTextNode();

    void setText(const QString &pTarget);
    QString getText() const ;

    bool testLoadBinaryFile(const QString &filePath);

public slots:
    void accept();

private slots:
    void on_fromBase64_clicked();
    void on_toBase64_clicked();
    void onWrapChanged(int newState);
    void on_loadFromBinaryFile_clicked();
    void on_saveBase64IntoFile_clicked();

private:

    void setWrapMode(const bool show);
    void error(const QString& message);

    bool onLoadFromBinaryFile(const QString &filePath);
    void saveToBinaryFile(const QString &filePath);

//    Ui::EditTN ui;
    bool  isBase64;
    void  init();
    void  retranslate();

    /***************************************
    ************   UI   *********************
    ****************************************/
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPlainTextEdit *editor;
    QVBoxLayout *verticalLayout;
    QDialogButtonBox *buttonBox;
    QSpacerItem *verticalSpacer;
    QCheckBox *wrapText;
    QSpacerItem *verticalSpacer_2;
    QLabel *label;
    QPushButton *fromBase64;
    QPushButton *toBase64;
    QLabel *label_2;
    QPushButton *loadFromBinaryFile;
    QPushButton *saveBase64IntoFile;
 };

#endif // EDITTEXTNODE_H
