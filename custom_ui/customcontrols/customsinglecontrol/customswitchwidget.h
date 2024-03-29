#ifndef CUSTOMSWITCHWIDGET_H
#define CUSTOMSWITCHWIDGET_H

#include <QWidget>
#include <QTimer>
#include "custom_ui/customwidgtes/customwidget.h"

class CustomSwitchWidget : public CustomWidget
{
    Q_OBJECT

public:
    CustomSwitchWidget(QWidget *parent = nullptr);
    ~CustomSwitchWidget();

    void setSwitchStatus(bool isOn, bool hasAnimation = true, bool cmd = false);
    bool getSwitchStatus();

protected:
    // Custom Paint Event
    virtual void customPaint(QPainter *painter) override;
    virtual QSize sizeHint() const override;
    virtual void mousePressEvent(QMouseEvent *event) override;

private:
    bool m_isSwitchOn = false;

    QMargins m_margin;
    QColor m_cBgColor;                  // 背景色
    QColor m_cSliderColor;              // 滑块的颜色
    int m_nCurrentXPos = 0;             // 当前的X的位置
    int m_nSliderWidth = 40;             // 滑块大小
    int m_nSliderHeight = 22;
    int m_nAnimationInterval = 5;

    QColor m_cOnBgColor;            // 打开时背景色
    QColor m_cOnSliderColor;        // 打开时滑块颜色

    QColor m_cOffBgColor;           // 关闭时背景颜色
    QColor m_cOffSliderColor;       // 关闭时滑块颜色

    QTimer *m_pTimer = nullptr;

private slots:
    void onTimeout();

signals:
    void valueChanged(bool isOn, bool cmd = false);
};

#endif
