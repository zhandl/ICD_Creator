#include "navigationbox.h"

NavigationBox::NavigationBox(QWidget *parent) :
    QWidget(parent)
{
    _minValue = 0;
    _maxValue = 0;
    _value = 0;
    init();
    setValues();
}

NavigationBox::~NavigationBox()
{
}

void NavigationBox::init()
{
    if (objectName().isEmpty())
        setObjectName(QString::fromUtf8("NavigationBox"));
    resize(208, 136);
    QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    setSizePolicy(sizePolicy);
    verticalLayout = new QVBoxLayout(this);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    title = new QLabel(this);
    title->setObjectName(QString::fromUtf8("title"));
    QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(title->sizePolicy().hasHeightForWidth());
    title->setSizePolicy(sizePolicy1);
    title->setAlignment(Qt::AlignCenter);

    verticalLayout->addWidget(title);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    goPrev = new QPushButton(this);
    goPrev->setObjectName(QString::fromUtf8("goPrev"));
    QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(goPrev->sizePolicy().hasHeightForWidth());
    goPrev->setSizePolicy(sizePolicy2);
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/arrows/images/go-previous.png"), QSize(), QIcon::Normal, QIcon::Off);
    goPrev->setIcon(icon);

    horizontalLayout->addWidget(goPrev);

    valueBox = new QSpinBox(this);
    valueBox->setObjectName(QString::fromUtf8("valueBox"));
    sizePolicy1.setHeightForWidth(valueBox->sizePolicy().hasHeightForWidth());
    valueBox->setSizePolicy(sizePolicy1);

    horizontalLayout->addWidget(valueBox);

    go = new QPushButton(this);
    go->setObjectName(QString::fromUtf8("go"));
    sizePolicy2.setHeightForWidth(go->sizePolicy().hasHeightForWidth());
    go->setSizePolicy(sizePolicy2);

    horizontalLayout->addWidget(go);

    goNext = new QPushButton(this);
    goNext->setObjectName(QString::fromUtf8("goNext"));
    sizePolicy2.setHeightForWidth(goNext->sizePolicy().hasHeightForWidth());
    goNext->setSizePolicy(sizePolicy2);
    QIcon icon1;
    icon1.addFile(QString::fromUtf8(":/arrows/images/go-next.png"), QSize(), QIcon::Normal, QIcon::Off);
    goNext->setIcon(icon1);

    horizontalLayout->addWidget(goNext);


    verticalLayout->addLayout(horizontalLayout);

    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    minVal = new QLabel(this);
    minVal->setObjectName(QString::fromUtf8("minVal"));
    sizePolicy1.setHeightForWidth(minVal->sizePolicy().hasHeightForWidth());
    minVal->setSizePolicy(sizePolicy1);

    horizontalLayout_2->addWidget(minVal);

    slider = new QSlider(this);
    slider->setObjectName(QString::fromUtf8("slider"));
    QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Preferred);
    sizePolicy3.setHorizontalStretch(0);
    sizePolicy3.setVerticalStretch(0);
    sizePolicy3.setHeightForWidth(slider->sizePolicy().hasHeightForWidth());
    slider->setSizePolicy(sizePolicy3);
    slider->setOrientation(Qt::Horizontal);
    slider->setInvertedControls(false);
    slider->setTickPosition(QSlider::TicksBelow);
    slider->setTickInterval(10);

    horizontalLayout_2->addWidget(slider);

    maxVal = new QLabel(this);
    maxVal->setObjectName(QString::fromUtf8("maxVal"));
    sizePolicy1.setHeightForWidth(maxVal->sizePolicy().hasHeightForWidth());
    maxVal->setSizePolicy(sizePolicy1);

    horizontalLayout_2->addWidget(maxVal);


    verticalLayout->addLayout(horizontalLayout_2);


    retranslateUi();

    QMetaObject::connectSlotsByName(this);
}

void NavigationBox::retranslateUi()
{
    setWindowTitle(QApplication::translate("NavigationBox", "Form", 0, QApplication::UnicodeUTF8));
    title->setText(QApplication::translate("NavigationBox", "Current fragment", 0, QApplication::UnicodeUTF8));
    goPrev->setText(QString());
    go->setText(QApplication::translate("NavigationBox", "Go", 0, QApplication::UnicodeUTF8));
    goNext->setText(QString());
    minVal->setText(QApplication::translate("NavigationBox", "1", 0, QApplication::UnicodeUTF8));
    maxVal->setText(QApplication::translate("NavigationBox", "2000", 0, QApplication::UnicodeUTF8));
}

void NavigationBox::setRange(const int minValue, const int maxValue)
{
    _minValue = minValue ;
    _maxValue = maxValue ;
    setValues();
}

void NavigationBox::setValues()
{
    valueBox->setRange(_minValue, _maxValue);
    minVal->setText(QString::number(_minValue));
    maxVal->setText(QString::number(_maxValue));
    slider->setRange(_minValue, _maxValue);
    valueBox->setValue(_value);
    _value = valueBox->value();
    slider->setValue(_value);
    enableButtons();
}

void NavigationBox::enableButtons()
{
    goPrev->setEnabled(_value > _minValue);
    goNext->setEnabled(_value < _maxValue);
}

void NavigationBox::notify()
{
    _value = valueBox->value();
    emit navigateTo(_value);
}

void NavigationBox::updateValue()
{
    _value = valueBox->value();
    enableButtons();
}


//------------------------------------------------------------------------

void NavigationBox::on_goPrev_clicked()
{
    _value = valueBox->value() - 1;
    valueBox->setValue(_value);
    updateValue();
    notify();
}

void NavigationBox::on_goNext_clicked()
{
    _value = valueBox->value() + 1;
    valueBox->setValue(_value);
    updateValue();
    notify();
}

void NavigationBox::on_go_clicked()
{
    updateValue();
    notify();
}

void NavigationBox::on_slider_valueChanged(int value)
{
    valueBox->setValue(value);
    updateValue();
}

void NavigationBox::on_valueBox_valueChanged(int value)
{
    updateValue();
    slider->setValue(value);
}

