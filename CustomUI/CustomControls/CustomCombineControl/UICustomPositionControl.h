#ifndef UICUSTOMPOSITIONCONTROL_H
#define UICUSTOMPOSITIONCONTROL_H

#include "UICustomCombineControlBase.h"
#include "UICustomSingleControl/UICustomPositionWidget.h"
#include <QWidget>

class UICustomPositionControl : public UICustomCombineControlBase
{
    Q_OBJECT

public:
    UICustomPositionControl(QWidget* parent = nullptr);
    ~UICustomPositionControl();

    // 设置当前映射的尺寸
    void setCurrentMapSize(int width, int height);

    // 设置当前的位置
    void setCurrentXPt(int xValue);
    void setCurrentYPt(int yValue);
    void setCurrentPosition(int xValue, int yValue);

    // 获取当前位置
    int getCurrentXPt();
    int getCurrentYPt();
    void getCurrentPosition(int& xValue, int& yValue);

private:
    UICustomPositionWidget* m_pPositionWidget = nullptr;

    int m_nMapWidth = 100;
    int m_nMapHeight = 100;

signals:
    void positionValueChanged(qreal xValue, qreal yValue);
};

#endif
