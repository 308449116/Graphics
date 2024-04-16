#include "customintcontrol.h"
#include "custom_ui/customcontrols/customsinglecontrol/customintspinbox.h"
#include <QDebug>

CustomIntControl::CustomIntControl(QWidget *parent)
    :CustomCombineControlBase(parent)
{
    m_intValue = new CustomIntSpinBox;
    m_mainLayout->addWidget(m_intValue);
    m_intValue->setSuffix(" px");

    m_slider = new QSlider(Qt::Horizontal);
    m_mainLayout->addWidget(m_slider);
    m_slider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    setRangeValue(0, 100);
    m_slider->setMinimum(0);
    m_slider->setMaximum(100);

    QObject::connect(m_intValue, &CustomIntSpinBox::editingFinished, \
                     this, &CustomIntControl::onIntValueChanged);

    QObject::connect(m_slider, &QSlider::valueChanged, this, &CustomIntControl::onSliderValueChanged);
    QObject::connect(m_slider, &QSlider::sliderPressed, this, &CustomIntControl::onSliderPressed);
    QObject::connect(m_slider, &QSlider::sliderMoved, this, &CustomIntControl::onSliderMoved);
    QObject::connect(m_slider, &QSlider::sliderReleased, this, &CustomIntControl::onSliderReleased);

    this->setWidth(400);
    this->setHeight(30);
}

CustomIntControl::~CustomIntControl()
{

}

void CustomIntControl::setRangeValue(int minValue, int maxValue)
{
    m_MaxValue = maxValue;
    m_MinValue = minValue;

    m_intValue->setMinimum(m_MinValue);
    m_intValue->setMaximum(m_MaxValue);
}

void CustomIntControl::setSuffix(const QString &suffix)
{
    m_intValue->setSuffix(suffix);
}

void CustomIntControl::setEnabled(bool enabled)
{
    m_intValue->setEnabled(enabled);
    m_slider->setEnabled(enabled);
}


void CustomIntControl::setCurrentValue(int value)
{
    if (value == m_intValue->value() ||
        value < m_MinValue ||
        value > m_MaxValue)
        return;

    m_intValue->setValue(value);

    int val = (value - m_MinValue) * 1.0 / (m_MaxValue - m_MinValue) * 100;

    m_slider->blockSignals(true);
    m_slider->setValue(val);
    m_slider->blockSignals(false);
}

int CustomIntControl::getCurrentValue()
{
    return m_intValue->value();
}

int CustomIntControl::getValuesBySlider()
{
    int value = m_slider->value();
    return m_MinValue + value * 1.0 / 100 * (m_MaxValue - m_MinValue);
}

void CustomIntControl::onSliderPressed()
{
    m_tempValue = m_intValue->value();

    int value = getValuesBySlider();
    m_intValue->setValue(value);

    emit valueChanged(value);
}

void CustomIntControl::onSliderMoved()
{
    int value = getValuesBySlider();
    m_intValue->setValue(value);

    emit valueChanged(value);
}

void CustomIntControl::onSliderReleased()
{
    int value = getValuesBySlider();
    m_intValue->setValue(value);

    emit valueChanged(m_tempValue);
    emit valueChanged(value, true);
}

void CustomIntControl::onSliderValueChanged(int val)
{
    int value = getValuesBySlider();
    m_intValue->setValue(value);

    emit valueChanged(value);
}

void CustomIntControl::onIntValueChanged()
{
    int value = m_intValue->value();
    m_slider->blockSignals(true);
    m_slider->setValue(value * 1.0 / (m_MaxValue - m_MinValue) * 100);
    m_slider->blockSignals(false);

    emit valueChanged(value, true);
}
