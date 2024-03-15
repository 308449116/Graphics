#include "UICustomIntControl.h"
#include "UICustomSingleControl/UICustomIntSpinBox.h"
#include <QDebug>

UICustomIntControl::UICustomIntControl(QWidget *parent)
    :UICustomCombineControlBase(parent)
{
    m_pIntValue = new UICustomIntSpinBox;
    m_pMainLayout->addWidget(m_pIntValue);

    m_pSlider = new QSlider(Qt::Horizontal);
    m_pMainLayout->addWidget(m_pSlider);
    m_pSlider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    setRangeValue(0, 100);
    m_pSlider->setMinimum(0);
    m_pSlider->setMaximum(100);

    QObject::connect(m_pIntValue, &UICustomIntSpinBox::editingFinished, \
                     this, &UICustomIntControl::onIntValueChanged);

    QObject::connect(m_pSlider, &QSlider::valueChanged, this, &UICustomIntControl::onSliderValueChanged);
    QObject::connect(m_pSlider, &QSlider::sliderPressed, this, &UICustomIntControl::onSliderPressed);
    QObject::connect(m_pSlider, &QSlider::sliderMoved, this, &UICustomIntControl::onSliderMoved);
    QObject::connect(m_pSlider, &QSlider::sliderReleased, this, &UICustomIntControl::onSliderReleased);

    this->setWidth(400);
    this->setHeight(30);
}

UICustomIntControl::~UICustomIntControl()
{

}

void UICustomIntControl::setRangeValue(int minValue, int maxValue)
{
    m_MaxValue = maxValue;
    m_MinValue = minValue;

    m_pIntValue->setMinimum(m_MinValue);
    m_pIntValue->setMaximum(m_MaxValue);
}


void UICustomIntControl::setCurrentValue(int value)
{
    if (value < m_MinValue || value > m_MaxValue)
        return;

    m_pIntValue->setValue(value);

    int val = (value - m_MinValue) * 1.0 / (m_MaxValue - m_MinValue) * 100;

    m_pSlider->blockSignals(true);
    m_pSlider->setValue(val);
    m_pSlider->blockSignals(false);
}

int UICustomIntControl::getCurrentValue()
{
    return m_pIntValue->value();
}

int UICustomIntControl::getValuesBySlider()
{
    int value = m_pSlider->value();
    return m_MinValue + value * 1.0 / 100 * (m_MaxValue - m_MinValue);
}

void UICustomIntControl::onSliderPressed()
{
    m_tempValue = m_pIntValue->value();

    int value = getValuesBySlider();
    m_pIntValue->setValue(value);

    emit valueChanged(value);
}

void UICustomIntControl::onSliderMoved()
{
    int value = getValuesBySlider();
    m_pIntValue->setValue(value);

    emit valueChanged(value);
}

void UICustomIntControl::onSliderReleased()
{
    int value = getValuesBySlider();
    m_pIntValue->setValue(value);

    emit valueChanged(m_tempValue);
    emit valueChanged(value, true);
}

void UICustomIntControl::onSliderValueChanged(int val)
{
    int value = getValuesBySlider();
    m_pIntValue->setValue(value);

    emit valueChanged(value);
}

void UICustomIntControl::onIntValueChanged()
{
    int value = m_pIntValue->value();
    m_pSlider->blockSignals(true);
    m_pSlider->setValue(value * 1.0 / (m_MaxValue - m_MinValue) * 100);
    m_pSlider->blockSignals(false);

    emit valueChanged(value, true);
}
