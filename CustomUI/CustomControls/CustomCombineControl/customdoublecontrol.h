#ifndef CUSTOMDOUBLECONTROL_H
#define CUSTOMDOUBLECONTROL_H

#include "customcombinecontrolbase.h"
#include <QWidget>
#include <QDoubleSpinBox>
#include <QSlider>

class CustomDoubleSpinBox;
class CustomDoubleControl : public CustomCombineControlBase
{
    Q_OBJECT

public:
    CustomDoubleControl(QWidget *parent = nullptr);
    ~CustomDoubleControl();

    // 设置/获取当前值
    void setCurrentValue(qreal value);
    qreal getCurrentValue();

    // 设置范围
    void setRangeValue(qreal minValue, qreal maxValue);
    void setSuffix(const QString &suffix);

private slots:
    void onSliderPressed();
    void onSliderMoved();
    void onSliderReleased();
    void onSliderValueChanged(int value);
    void onDoubleValueChanged();

signals:
    void valueChanged(qreal value, bool cmd = false);

private:
    CustomDoubleSpinBox *m_pDoubleSpinBox = nullptr;
    QSlider *m_pSlider = nullptr;

    qreal m_beforeValue = 0;
    qreal m_MaxValue = 0;
    qreal m_MinValue = 1;

    qreal getValuesBySlider();
};

#endif
