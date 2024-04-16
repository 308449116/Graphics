#ifndef CUSTOMINTCONTROL_H
#define CUSTOMINTCONTROL_H

#include "customcombinecontrolbase.h"
#include <QWidget>
#include <QSpinBox>
#include <QSlider>

class CustomIntSpinBox;
class CustomIntControl : public CustomCombineControlBase
{
    Q_OBJECT

public:
    CustomIntControl(QWidget *parent = nullptr);
    ~CustomIntControl();

    // 设置/获取当前的值
    void setCurrentValue(int value);
    int getCurrentValue();

    // 设置范围
    void setRangeValue(int minValue, int maxValue);
    void setSuffix(const QString &suffix);

    void setEnabled(bool enabled);

private slots:
    void onSliderPressed();
    void onSliderMoved();
    void onSliderReleased();
    void onSliderValueChanged(int);
    void onIntValueChanged();

signals:
    void valueChanged(int value, bool cmd = false);

private:
    int getValuesBySlider();

private:
    CustomIntSpinBox *m_intValue = nullptr;
    QSlider *m_slider = nullptr;

    int m_MaxValue = 100;
    int m_MinValue = 0;
    int m_tempValue = 0;
};

#endif
