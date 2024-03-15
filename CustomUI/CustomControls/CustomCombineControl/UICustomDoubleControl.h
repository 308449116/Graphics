#ifndef UICUSTOMDOUBLECONTROL_H
#define UICUSTOMDOUBLECONTROL_H

#include "UICustomCombineControlBase.h"
#include <QWidget>
#include <QDoubleSpinBox>
#include <QSlider>

class UICustomDoubleSpinBox;
class UICustomDoubleControl : public UICustomCombineControlBase
{
    Q_OBJECT

public:
    UICustomDoubleControl(QWidget *parent = nullptr);
    ~UICustomDoubleControl();

    // 设置/获取当前值
    void setCurrentValue(qreal value);
    qreal getCurrentValue();

    // 设置范围
    void setRangeValue(qreal minValue, qreal maxValue);

private:
    UICustomDoubleSpinBox *m_pDoubleSpinBox = nullptr;
    QSlider *m_pSlider = nullptr;

    qreal m_beforeValue = 0;
    qreal m_qMaxValue = 0;
    qreal m_qMinValue = 1;

    qreal getValuesBySlider();

private slots:
    void onSliderPressed();
    void onSliderMoved();
    void onSliderReleased();
    void onSliderValueChanged(int value);

    void onDoubleValueChanged();

signals:
    void valueChanged(qreal value, bool cmd = false);
};

#endif
