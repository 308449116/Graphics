#ifndef CUSTOMSWITCHCONTROL_H
#define CUSTOMSWITCHCONTROL_H

#include "customcombinecontrolbase.h"
#include "CustomSingleControl/customswitchwidget.h"
#include <QLabel>

class CustomSwitchControl : public CustomCombineControlBase
{
    Q_OBJECT

public:
    CustomSwitchControl(QWidget *parent = nullptr);
    ~CustomSwitchControl();

    // 设置/获取当前值
    void setCurrentValue(bool isOn, bool hasAnim = true);
    bool getCurrentValue();

    // 设置右侧文本
    void setRightText(const QString& text);

private:
    CustomSwitchWidget *m_pSwitchWidget = nullptr;
    QLabel *m_pLabel = nullptr;

signals:
    void valueChanged(bool isOn, bool cmd = false);
};

#endif
