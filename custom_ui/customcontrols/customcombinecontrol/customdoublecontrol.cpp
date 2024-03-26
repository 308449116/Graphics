#include "customdoublecontrol.h"
#include "custom_ui/customcontrols/customsinglecontrol/customdoublespinbox.h"

CustomDoubleControl::CustomDoubleControl(QWidget *parent)
    :CustomCombineControlBase(parent)
{
    // Double
    m_pDoubleSpinBox = new CustomDoubleSpinBox;
    m_pMainLayout->addWidget(m_pDoubleSpinBox);
    m_pDoubleSpinBox->setSuffix("px");

    m_pSlider = new QSlider(Qt::Horizontal);
    m_pSlider->setMinimum(0);
    m_pSlider->setMaximum(100);
    m_pMainLayout->addWidget(m_pSlider);

    setRangeValue(0, 1.0);
    m_pSlider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QObject::connect(m_pDoubleSpinBox, &CustomDoubleSpinBox::editingFinished, \
                     this, &CustomDoubleControl::onDoubleValueChanged);

    QObject::connect(m_pSlider, &QSlider::valueChanged, this, &CustomDoubleControl::onSliderValueChanged);
    QObject::connect(m_pSlider, &QSlider::sliderPressed, this, &CustomDoubleControl::onSliderPressed);
    QObject::connect(m_pSlider, &QSlider::sliderMoved, this, &CustomDoubleControl::onSliderMoved);
    QObject::connect(m_pSlider, &QSlider::sliderReleased, this, &CustomDoubleControl::onSliderReleased);

    this->setWidth(400);
    this->setHeight(30);
}

CustomDoubleControl::~CustomDoubleControl()
{

}

void CustomDoubleControl::setCurrentValue(qreal value)
{
    if (value == m_pDoubleSpinBox->value() ||
        value < m_MinValue ||
        value > m_MaxValue) {
        return;
    }

    m_pDoubleSpinBox->setValue(value);
    int val = (value - m_MinValue) * 1.0 / (m_MaxValue - m_MinValue) * 100;

    m_pSlider->blockSignals(true);
    m_pSlider->setValue(val);
    m_pSlider->blockSignals(false);
}

qreal CustomDoubleControl::getCurrentValue()
{
    return m_pDoubleSpinBox->value();
}

void CustomDoubleControl::setRangeValue(qreal minValue, qreal maxValue)
{
    m_MinValue = minValue;
    m_MaxValue = maxValue;

    m_pDoubleSpinBox->setMinimum(m_MinValue);
    m_pDoubleSpinBox->setMaximum(m_MaxValue);
}

void CustomDoubleControl::setSuffix(const QString &suffix)
{
    m_pDoubleSpinBox->setSuffix(suffix);
}

void CustomDoubleControl::onSliderPressed()
{
    m_beforeValue = m_pDoubleSpinBox->value();

    qreal valus = getValuesBySlider();
    m_pDoubleSpinBox->setValue(valus);

    emit valueChanged(valus);
}

void CustomDoubleControl::onSliderMoved()
{
    qreal valus = getValuesBySlider();
    m_pDoubleSpinBox->setValue(valus);

    emit valueChanged(valus);
}

void CustomDoubleControl::onSliderReleased()
{
    qreal valus = getValuesBySlider();
    m_pDoubleSpinBox->setValue(valus);

    emit valueChanged(m_beforeValue);
    emit valueChanged(valus, true);
}

void CustomDoubleControl::onSliderValueChanged(int value)
{
    Q_UNUSED(value)

    qreal valus = getValuesBySlider();
    m_pDoubleSpinBox->setValue(valus);
    emit valueChanged(valus);
}

qreal CustomDoubleControl::getValuesBySlider()
{
    int value = m_pSlider->value();
    return m_MinValue + (m_MaxValue - m_MinValue) * value * 1.0 / 100;
}

void CustomDoubleControl::onDoubleValueChanged()
{
    qreal value = m_pDoubleSpinBox->value();
    int val = (value - m_MinValue) * 1.0 / (m_MaxValue - m_MinValue) * 100;

    m_pSlider->blockSignals(true);
    m_pSlider->setValue(val);
    m_pSlider->blockSignals(false);

    emit valueChanged(value, true);
}
