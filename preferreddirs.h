#ifndef PREFERREDDIRS_H
#define PREFERREDDIRS_H

#include <QDialog>
#include <QStringListModel>

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

class PreferredDirs : public QDialog
{
    Q_OBJECT
public:
    explicit PreferredDirs(QStringList &theOriginalValues, QWidget *parent = 0);
    ~PreferredDirs();

    static bool checkNewDir(const int size, const bool isUI);
    static bool checkDuplicateDir(QStringList &list, const QString &newDir, const bool isUI);

protected:
    void changeEvent(QEvent *e);

private:

    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QListView *dirList;
    QVBoxLayout *verticalLayout;
    QDialogButtonBox *buttonBox;
    QSpacerItem *verticalSpacer;
    QPushButton *add;
    QPushButton *remove;

    void init();
    void retranslateUi();

    QStringList &originalValues;
    QStringList dirs;
    QStringListModel *model;

    void fillData();
    void handleSelects(const bool isItemValid);

private slots:
    void accept();
    void on_add_clicked();
    void on_remove_clicked();
    void on_dirList_clicked(const QModelIndex &index);

};

bool configurePreferredDirs(QWidget *parent, QStringList &originalValues);

#endif // PREFERREDDIRS_H
