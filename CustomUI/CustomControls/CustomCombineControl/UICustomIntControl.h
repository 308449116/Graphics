#ifndef UICUSTOMINTCONTROL_H
#define UICUSTOMINTCONTROL_H

#include "UICustomCombineControlBase.h"
#include <QWidget>
#include <QSpinBox>
#include <QSlider>

class UICustomIntSpinBox;
class UICustomIntControl : public UICustomCombineControlBase
{
    Q_OBJECT

public:
    UICustomIntControl(QWidget *parent = nullptr);
    ~UICustomIntControl();

    // 设置/获取当前的值
    void setCurrentValue(int value);
    int getCurrentValue();

    // 设置范围
    void setRangeValue(int minValue, int maxValue);
    void setSuffix(const QString &suffix);

private slots:
    void onSliderPressed();
    void onSliderMoved();
    void onSliderReleased();
    void onSliderValueChanged(int);
    void onIntValueChanged();

signals:
    void valueChanged(int value, bool cmd = false);

private:
    UICustomIntSpinBox *m_pIntValue = nullptr;
    QSlider *m_pSlider = nullptr;

    int m_MaxValue = 100;
    int m_MinValue = 0;
    int m_tempValue = 0;

    int getValuesBySlider();
};

#endif
