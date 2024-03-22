#include "customintcontrol.h"
#include "customintspinbox.h"
#include <QDebug>

CustomIntControl::CustomIntControl(QWidget *parent)
    :CustomCombineControlBase(parent)
{
    m_pIntValue = new CustomIntSpinBox;
    m_pMainLayout->addWidget(m_pIntValue);
    m_pIntValue->setSuffix(" px");

    m_pSlider = new QSlider(Qt::Horizontal);
    m_pMainLayout->addWidget(m_pSlider);
    m_pSlider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    setRangeValue(0, 100);
    m_pSlider->setMinimum(0);
    m_pSlider->setMaximum(100);

    QObject::connect(m_pIntValue, &CustomIntSpinBox::editingFinished, \
                     this, &CustomIntControl::onIntValueChanged);

    QObject::connect(m_pSlider, &QSlider::valueChanged, this, &CustomIntControl::onSliderValueChanged);
    QObject::connect(m_pSlider, &QSlider::sliderPressed, this, &CustomIntControl::onSliderPressed);
    QObject::connect(m_pSlider, &QSlider::sliderMoved, this, &CustomIntControl::onSliderMoved);
    QObject::connect(m_pSlider, &QSlider::sliderReleased, this, &CustomIntControl::onSliderReleased);

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

    m_pIntValue->setMinimum(m_MinValue);
    m_pIntValue->setMaximum(m_MaxValue);
}

void CustomIntControl::setSuffix(const QString &suffix)
{
    m_pIntValue->setSuffix(suffix);
}


void CustomIntControl::setCurrentValue(int value)
{
    if (value == m_pIntValue->value() ||
        value < m_MinValue ||
        value > m_MaxValue)
        return;

    m_pIntValue->setValue(value);

    int val = (value - m_MinValue) * 1.0 / (m_MaxValue - m_MinValue) * 100;

    m_pSlider->blockSignals(true);
    m_pSlider->setValue(val);
    m_pSlider->blockSignals(false);
}

int CustomIntControl::getCurrentValue()
{
    return m_pIntValue->value();
}

int CustomIntControl::getValuesBySlider()
{
    int value = m_pSlider->value();
    return m_MinValue + value * 1.0 / 100 * (m_MaxValue - m_MinValue);
}

void CustomIntControl::onSliderPressed()
{
    m_tempValue = m_pIntValue->value();

    int value = getValuesBySlider();
    m_pIntValue->setValue(value);

    emit valueChanged(value);
}

void CustomIntControl::onSliderMoved()
{
    int value = getValuesBySlider();
    m_pIntValue->setValue(value);

    emit valueChanged(value);
}

void CustomIntControl::onSliderReleased()
{
    int value = getValuesBySlider();
    m_pIntValue->setValue(value);

    emit valueChanged(m_tempValue);
    emit valueChanged(value, true);
}

void CustomIntControl::onSliderValueChanged(int val)
{
    int value = getValuesBySlider();
    m_pIntValue->setValue(value);

    emit valueChanged(value);
}

void CustomIntControl::onIntValueChanged()
{
    int value = m_pIntValue->value();
    m_pSlider->blockSignals(true);
    m_pSlider->setValue(value * 1.0 / (m_MaxValue - m_MinValue) * 100);
    m_pSlider->blockSignals(false);

    emit valueChanged(value, true);
}
