#include "UICustomPositionWidget.h"
//#include "UICustomCore/CustomStyleConfig.h"
#include <QPainter>
#include <QMouseEvent>

UICustomPositionWidget::UICustomPositionWidget(QWidget* parent)
    :CustomWidget(parent)
{
    this->setMouseTracking(true);
//    g_StyleConfig->setCurrentStyle(this, "Transparent");
}

UICustomPositionWidget::~UICustomPositionWidget()
{

}

void UICustomPositionWidget::customPaint(QPainter* painter)
{
    QPoint pos = transToThisPosition();

    painter->save();
//    painter->setPen(QPen(g_StyleConfig->getHighLightColor()));
    painter->setRenderHint(QPainter::Antialiasing);

    // 绘制矩形
    QRect rect = this->rect().adjusted(m_nRadius, m_nRadius, -m_nRadius, -m_nRadius);
    painter->drawRect(rect);

    // 绘制位置
    painter->setPen(QPen(QColor(230, 230, 230)));
    painter->drawEllipse(pos, m_nRadius, m_nRadius);

    painter->restore();
}

QSize UICustomPositionWidget::sizeHint() const
{
    QSize size(150, 150);
    return size;
}

void UICustomPositionWidget::mousePressEvent(QMouseEvent* event)
{
    m_isPressed = true;

    QPoint pos = event->pos();
    transToThisValue(pos);
    this->update();
}

void UICustomPositionWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (!m_isPressed)
        return;

    QPoint pos = event->pos();
    transToThisValue(pos);
    this->update();
}

void UICustomPositionWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if (!m_isPressed)
        return;

    m_isPressed = false;

    QPoint pos = event->pos();
    transToThisValue(pos);
    this->update();
}

QPoint UICustomPositionWidget::transToThisPosition()
{
    QRect rect = this->rect().adjusted(m_nRadius, m_nRadius, -m_nRadius, -m_nRadius);

    qreal xPt = m_xValue / 100.0 * rect.width() + rect.x();
    qreal yPt = m_yValue / 100.0 * rect.height() + rect.y();

    QPoint pos;
    pos.setX(xPt);
    pos.setY(yPt);

    return pos;
}

void UICustomPositionWidget::transToThisValue(QPoint pos)
{
    QRect rect = this->rect().adjusted(m_nRadius, m_nRadius, -m_nRadius, -m_nRadius);
    if (!rect.contains(pos))
        return;

    m_xValue = (pos.x() - rect.x()) * 1.0 / rect.width() * 100;
    m_yValue = (pos.y() - rect.y()) * 1.0 / rect.height() * 100;
    emit positionValueChanged(m_xValue, m_yValue);
}

void UICustomPositionWidget::setPositionValue(qreal xValue, qreal yValue)
{
    m_xValue = xValue;
    m_yValue = yValue;

    this->update();
}

void UICustomPositionWidget::setPositionXValue(qreal xValue)
{
    m_xValue = xValue;
    this->update();
}

void UICustomPositionWidget::setPositionYValue(qreal yValue)
{
    m_yValue = yValue;
    this->update();
}

void UICustomPositionWidget::getPositionValue(qreal& xValue, qreal &yValue)
{
    xValue = m_xValue;
    yValue = m_yValue;
}

qreal UICustomPositionWidget::getPositionXValue()
{
    return m_xValue;
}

qreal UICustomPositionWidget::getPositionYValue()
{
    return m_yValue;
}
