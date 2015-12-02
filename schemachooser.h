#ifndef SCHEMACHOOSER_H
#define SCHEMACHOOSER_H

#include <QDialog>
#include <QListWidget>

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

class SchemaChooser : public QDialog
{
    Q_OBJECT

    static const int MAX_LAST_FILES = 10;

    bool _started;
    QString _selection;
    QStringList _lastFilesNames;
    QStringList _preferitesFilesNames;
public:
    explicit SchemaChooser(QWidget *parent = 0);
    ~SchemaChooser();

    QString selection();

private:

    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QListWidget *favoritesList;
    QVBoxLayout *verticalLayout;
    QPushButton *addPrefsSchema;
    QPushButton *remPrefsSchema;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *textSelection;
    QPushButton *browseFile;
    QLabel *label_2;
    QListWidget *lastUsedList;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void init();
    void retranslateUi();

    void loadData();
    void saveSelection();
    void loadPreferredData();
    void loadLastUsedData();
    void setSelection(const QString &newSelection);
    void enableOK(const bool isEnabled);

private slots:
    void accept();
    void on_lastUsedList_currentItemChanged(QListWidgetItem* current, QListWidgetItem *previous);
    void on_lastUsedList_itemClicked(QListWidgetItem *item);
    void on_favoritesList_currentItemChanged(QListWidgetItem *current, QListWidgetItem * /*privious*/);
    void on_favoritesList_itemClicked(QListWidgetItem *item);
    void on_addPrefsSchema_clicked();
    void on_remPrefsSchema_clicked();
    void on_browseFile_clicked();
    void on_textSelection_textChanged(const QString &text);
    void on_favoritesList_itemDoubleClicked(QListWidgetItem *item);
    void on_lastUsedList_itemDoubleClicked(QListWidgetItem *item);
};

#endif // SCHEMACHOOSER_H
