#include "customswitchwidget.h"
//#include "CustomCore/customstyleconfig.h"
#include <QPainter>

CustomSwitchWidget::CustomSwitchWidget(QWidget *parent)
    :CustomWidget(parent)
    ,m_margin(1, 1, 1, 1)
    ,m_BgColor(223, 105, 20)
    ,m_sliderColor(243, 125, 40)
    , m_onBgColor(155, 78, 15)
    , m_onSliderColor(226, 105, 5)
    , m_offBgColor(138, 138, 138)
    , m_offSliderColor(160, 160, 160)
{
//    g_StyleConfig->setCurrentStyle(this, "Transparent");
    this->setCursor(Qt::PointingHandCursor);
    setSwitchStatus(true, false);

    m_timer = new QTimer;
    m_timer->setInterval(20);
    QObject::connect(m_timer, &QTimer::timeout, this, &CustomSwitchWidget::onTimeout);
}

CustomSwitchWidget::~CustomSwitchWidget()
{

}

void CustomSwitchWidget::setSwitchStatus(bool isOn, bool hasAnimation, bool cmd)
{
    if (isOn)
    {
        m_BgColor = m_onBgColor;
        m_sliderColor = m_onSliderColor;
    }
    else
    {
        m_BgColor = m_offBgColor;
        m_sliderColor = m_offSliderColor;
    }

    if (m_isSwitchOn != isOn)
    {
        m_isSwitchOn = isOn;
        emit valueChanged(isOn, cmd);
    }

    // 开启动画
    if (hasAnimation)
        m_timer->start();

    this->update();
}

bool CustomSwitchWidget::getSwitchStatus()
{
    return m_isSwitchOn;
}

void CustomSwitchWidget::customPaint(QPainter *painter)
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);

    QRect rect = this->rect();
    rect = rect.adjusted(m_margin.left(), m_margin.top(), -m_margin.right(), -m_margin.bottom());

    // 绘制背景
    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(m_BgColor));
    painter->drawRoundedRect(rect, 4, 4);

    // 绘制滑块
    painter->setBrush(QBrush(m_sliderColor));
    qreal interval = (rect.height() - m_sliderHeight) / 2.0;
    QRect sliderRect(interval + m_currentXPos, rect.y() + interval, m_sliderWidth, m_sliderHeight);
    painter->drawRoundedRect(sliderRect, 4, 4);
    painter->restore();
}

QSize CustomSwitchWidget::sizeHint() const
{
    QSize size(80, 30);
    return size;
}

void CustomSwitchWidget::mousePressEvent(QMouseEvent *event)
{
    setSwitchStatus(!m_isSwitchOn, true, true);
}

void CustomSwitchWidget::onTimeout()
{
    QRect rect = this->rect();
    rect = rect.adjusted(m_margin.left(), m_margin.top(), -m_margin.right(), -m_margin.bottom());
    qreal interval = (rect.height() - m_sliderHeight) / 2.0;

    int startPos = 0;
    int endXPos = rect.right() - interval - m_sliderWidth;
    if (m_isSwitchOn)
    {
        // 向左移动
        m_currentXPos -= m_animationInterval;
        if (m_currentXPos <= startPos)
        {
            m_currentXPos = 0;
            m_timer->stop();
        }
    }
    else
    {
        // 向右移动
        m_currentXPos += m_animationInterval;
        if (m_currentXPos >= endXPos)
        {
            m_currentXPos = endXPos;
            m_timer->stop();
        }
    }
    this->update();
}
