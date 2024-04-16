#include "customdoublecontrol.h"
#include "custom_ui/customcontrols/customsinglecontrol/customdoublespinbox.h"

CustomDoubleControl::CustomDoubleControl(QWidget *parent)
    :CustomCombineControlBase(parent)
{
    // Double
    m_doubleSpinBox = new CustomDoubleSpinBox;
    m_mainLayout->addWidget(m_doubleSpinBox);
    m_doubleSpinBox->setSuffix("px");

    m_slider = new QSlider(Qt::Horizontal);
    m_slider->setMinimum(0);
    m_slider->setMaximum(100);
    m_mainLayout->addWidget(m_slider);

    setRangeValue(0, 1.0);
    m_slider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QObject::connect(m_doubleSpinBox, &CustomDoubleSpinBox::editingFinished, \
                     this, &CustomDoubleControl::onDoubleValueChanged);

    QObject::connect(m_slider, &QSlider::valueChanged, this, &CustomDoubleControl::onSliderValueChanged);
    QObject::connect(m_slider, &QSlider::sliderPressed, this, &CustomDoubleControl::onSliderPressed);
    QObject::connect(m_slider, &QSlider::sliderMoved, this, &CustomDoubleControl::onSliderMoved);
    QObject::connect(m_slider, &QSlider::sliderReleased, this, &CustomDoubleControl::onSliderReleased);

    this->setWidth(400);
    this->setHeight(30);
}

CustomDoubleControl::~CustomDoubleControl()
{

}

void CustomDoubleControl::setCurrentValue(qreal value)
{
    if (value == m_doubleSpinBox->value() ||
        value < m_MinValue ||
        value > m_MaxValue) {
        return;
    }

    m_doubleSpinBox->setValue(value);
    int val = (value - m_MinValue) * 1.0 / (m_MaxValue - m_MinValue) * 100;

    m_slider->blockSignals(true);
    m_slider->setValue(val);
    m_slider->blockSignals(false);
}

qreal CustomDoubleControl::getCurrentValue()
{
    return m_doubleSpinBox->value();
}

void CustomDoubleControl::setRangeValue(qreal minValue, qreal maxValue)
{
    m_MinValue = minValue;
    m_MaxValue = maxValue;

    m_doubleSpinBox->setMinimum(m_MinValue);
    m_doubleSpinBox->setMaximum(m_MaxValue);
}

void CustomDoubleControl::setSuffix(const QString &suffix)
{
    m_doubleSpinBox->setSuffix(suffix);
}

void CustomDoubleControl::setEnabled(bool enabled)
{
    m_doubleSpinBox->setEnabled(enabled);
    m_slider->setEnabled(enabled);
}

void CustomDoubleControl::onSliderPressed()
{
    m_beforeValue = m_doubleSpinBox->value();

    qreal valus = getValuesBySlider();
    m_doubleSpinBox->setValue(valus);

    emit valueChanged(valus);
}

void CustomDoubleControl::onSliderMoved()
{
    qreal valus = getValuesBySlider();
    m_doubleSpinBox->setValue(valus);

    emit valueChanged(valus);
}

void CustomDoubleControl::onSliderReleased()
{
    qreal valus = getValuesBySlider();
    m_doubleSpinBox->setValue(valus);

    emit valueChanged(m_beforeValue);
    emit valueChanged(valus, true);
}

void CustomDoubleControl::onSliderValueChanged(int value)
{
    Q_UNUSED(value)

    qreal valus = getValuesBySlider();
    m_doubleSpinBox->setValue(valus);
    emit valueChanged(valus);
}

qreal CustomDoubleControl::getValuesBySlider()
{
    int value = m_slider->value();
    return m_MinValue + (m_MaxValue - m_MinValue) * value * 1.0 / 100;
}

void CustomDoubleControl::onDoubleValueChanged()
{
    qreal value = m_doubleSpinBox->value();
    int val = (value - m_MinValue) * 1.0 / (m_MaxValue - m_MinValue) * 100;

    m_slider->blockSignals(true);
    m_slider->setValue(val);
    m_slider->blockSignals(false);

    emit valueChanged(value, true);
}
