#ifndef EDITREPORTCONTROL_H
#define EDITREPORTCONTROL_H

#include <QDialog>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QCheckBox>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGroupBox>
#include <QtGui/QGridLayout>
#include <QtGui/QSpinBox>
#include <QtGui/QComboBox>

class DomItem;

class EditReportControl : public QDialog
{
    Q_OBJECT
public:
    EditReportControl(QWidget *parent = 0);
    ~EditReportControl();

    void setTarget(DomItem *item);

private:
    QLabel *nameLabel;
    QLineEdit *nameText;
    QLabel *confRevLabel;
    QSpinBox *confRevSpinBox;
    QCheckBox *rptIdCheckBox;
    QLabel *rptIdLabel;
    QLineEdit *rptIdText;
    QCheckBox *bufferedCheckBox;
    QLabel *bufferedLabel;
    QComboBox *bufferedComboBox;
    QCheckBox *bufTimeCheckBox;
    QLabel *bufTimeLabel;
    QSpinBox *bufTimeSpinBox;
    QCheckBox *indexedCheckBox;
    QLabel *indexedLabel;
    QComboBox *indexedComboBox;
    QCheckBox *datSetCheckBox;
    QLabel *datSetLabel;
    QLineEdit *datSetText;
    QCheckBox *descCheckBox;
    QLabel *descLabel;
    QLineEdit *descText;

    QDialogButtonBox *buttonBox;

    QGridLayout *layout;

    DomItem *target;

    void init();

    void accept();
signals:

public slots:

};
#endif // EDITREPORTCONTROL_H
