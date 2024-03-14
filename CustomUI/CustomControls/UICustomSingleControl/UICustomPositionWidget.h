#ifndef UICUSTOMPOSITIONWIDGET_H
#define UICUSTOMPOSITIONWIDGET_H

#include "UICustomWidgtes/CustomWidget.h"
#include <QWidget>
class UICustomPositionWidget : public CustomWidget
{
    Q_OBJECT

public:
    UICustomPositionWidget(QWidget* parent = nullptr);
    ~UICustomPositionWidget();

    // 设置位置
    void setPositionValue(qreal xValue, qreal yValue);
    void setPositionXValue(qreal xValue);
    void setPositionYValue(qreal yValue);

    // 获取位置
    void getPositionValue(qreal& xValue, qreal &yValue);
    qreal getPositionXValue();
    qreal getPositionYValue();

protected:
    // Custom Paint Event
    void customPaint(QPainter* painter) override;
    QSize sizeHint() const override;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    bool m_isPressed = false;
    int m_nRadius = 4;

    qreal m_xValue = 0;     // 百分比值
    qreal m_yValue = 0;
    QPoint transToThisPosition();
    void transToThisValue(QPoint pos);

signals:
    void positionValueChanged(qreal xValue, qreal yValue);
};

#endif
