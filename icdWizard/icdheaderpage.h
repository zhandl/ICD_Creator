#ifndef ICDHEADERPAGE_H
#define ICDHEADERPAGE_H

#include <QWizardPage>

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>
#include <QtGui/QGridLayout>
#include <QtGui/QVBoxLayout>
#include <QHeaderView>

//namespace Ui
//{
//class icdHeaderPage;
//}

class icdHeaderPage : public QWizardPage
{
    Q_OBJECT
public:
    icdHeaderPage(QWidget *parent = 0);
    ~icdHeaderPage();

//    Ui::icdHeaderPage *ui;
    QVBoxLayout *headerVLayout;
    QGroupBox *headerGroupBox;
    QGridLayout *headerGridLayout;
    QLabel *headerToolIdLabel;
    QCheckBox *headerToolIdCheckBox;
    QComboBox *headerNameStructureCombo;
    QLabel *headerNameStructureLabel;
    QLineEdit *headerIdText;
    QLabel *headerIdLabel;
    QCheckBox *headerRevisionCheckBox;
    QLineEdit *headerToolIdText;
    QLineEdit *headerRevisionText;
    QCheckBox *headerRefCheckBox;
    QLineEdit *headerRefText;
    QLabel *headerRefLabel;
    QLabel *headerRevisionLabel;
    QCheckBox *headerVersionCheckBox;
    QLineEdit *headerVersionText;
    QLabel *headerVersionLabel;
    QGroupBox *historyGroupBox;
    QGridLayout *historyGridLayout;
    QTableWidget *hitemTableWidget;
    QPushButton *addHitemButton;
    QPushButton *deleteHitemButton;

private:

    void init();
    void retranslateUi();
    void registerData();

protected:

signals:

public slots:
    void on_addHitemButton_clicked();
    void on_deleteHitemButton_clicked();

};

#endif // ICDHEADERPAGE_H
