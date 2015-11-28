#ifndef NAVIGATIONBOX_H
#define NAVIGATIONBOX_H

#include <QWidget>

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class NavigationBox : public QWidget
{
    Q_OBJECT

    int _value;
    int _minValue;
    int _maxValue;

public:
    explicit NavigationBox(QWidget *parent = 0);
    ~NavigationBox();

    void setRange(const int minValue, const int maxValue);

private:

    QVBoxLayout *verticalLayout;
    QLabel *title;
    QHBoxLayout *horizontalLayout;
    QPushButton *goPrev;
    QSpinBox *valueBox;
    QPushButton *go;
    QPushButton *goNext;
    QHBoxLayout *horizontalLayout_2;
    QLabel *minVal;
    QSlider *slider;
    QLabel *maxVal;

    void init();
    void retranslateUi();

    void setValues();
    void enableButtons();
    void notify();
    void updateValue();

private slots:
    void on_goPrev_clicked();
    void on_goNext_clicked();
    void on_go_clicked();
    void on_slider_valueChanged(int value);
    void on_valueBox_valueChanged(int value);


signals:
    void navigateTo(const int page);
};

#endif // NAVIGATIONBOX_H
