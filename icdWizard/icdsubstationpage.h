#ifndef ICDSUBSTATIONPAGE_H
#define ICDSUBSTATIONPAGE_H

#include <QWizardPage>

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

class icdSubstationPage : public QWizardPage
{
    Q_OBJECT
public:
    icdSubstationPage(QWidget *parent = 0);
    ~icdSubstationPage();


    QVBoxLayout *verticalLayout;
    QVBoxLayout *substationVLayout;
    QGroupBox *substationGroupBox;
    QGridLayout *substationGridLayout;
    QLabel *substationNameLabel;
    QLineEdit *subStationNameText;
    QCheckBox *substationDescCheckBox;
    QLabel *substationDescLabel;
    QLineEdit *substationDescText;
    QGroupBox *voltageLevelGroupBox;
    QGridLayout *voltageLevelGridLayout;
    QLabel *voltageLevelNameLabel;
    QLineEdit *voltageLevelNameText;
    QGroupBox *voltageGroupBox;
    QGridLayout *voltageGridLayout;
    QLabel *voltageUnitLabel;
    QComboBox *voltageUnitComboBox;
    QCheckBox *voltageMultiplierCheckBox;
    QLabel *voltageMultiplierLabel;
    QComboBox *voltageMultiplierComboBox;
    QGroupBox *bayGroupBox;
    QGridLayout *bayGridLayout;
    QLabel *bayNameLabel;
    QLineEdit *bayNameText;
    QCheckBox *bayDescCheckBox;
    QLabel *bayDescLabel;
    QLineEdit *bayDescText;

private:

    void init();
    void retranslateUi();

    void registerData();

signals:

public slots:


};

#endif // ICDSUBSTATIONPAGE_H
