#include "UICustomPositionControl.h"

UICustomPositionControl::UICustomPositionControl(QWidget* parent)
    :UICustomCombineControlBase(parent)
{
    m_pPositionWidget = new UICustomPositionWidget;
    m_pMainLayout->addWidget(m_pPositionWidget);

    this->setWidth(400);
    this->setHeight(150);

    QObject::connect(m_pPositionWidget, &UICustomPositionWidget::positionValueChanged, \
                     this, &UICustomPositionControl::positionValueChanged);
}

UICustomPositionControl::~UICustomPositionControl()
{

}

// 设置当前映射的尺寸
void UICustomPositionControl::setCurrentMapSize(int width, int height)
{
    m_nMapWidth = width;
    m_nMapHeight = height;
}

// 设置当前的位置
void UICustomPositionControl::setCurrentXPt(int xValue)
{
    qreal val = xValue * 1.0 / m_nMapWidth * 100;
    m_pPositionWidget->setPositionXValue(val);
}

void UICustomPositionControl::setCurrentYPt(int yValue)
{
    qreal val = yValue * 1.0 / m_nMapHeight * 100;
    m_pPositionWidget->setPositionYValue(val);
}

void UICustomPositionControl::setCurrentPosition(int xValue, int yValue)
{
    qreal xVal = xValue * 1.0 / m_nMapWidth * 100;
    qreal yVal = yValue * 1.0 / m_nMapHeight * 100;
    m_pPositionWidget->setPositionValue(xVal, yVal);
}

// 获取当前位置
int UICustomPositionControl::getCurrentXPt()
{
    qreal xVal = m_pPositionWidget->getPositionXValue();
    return xVal / 100.0 * m_nMapWidth;
}

int UICustomPositionControl::getCurrentYPt()
{
    qreal yVal = m_pPositionWidget->getPositionYValue();
    return yVal / 100.0 * m_nMapHeight;
}

void UICustomPositionControl::getCurrentPosition(int& xValue, int& yValue)
{
    qreal xVal, yVal;
    m_pPositionWidget->getPositionValue(xVal, yVal);

    xValue = xVal / 100.0 * m_nMapWidth;
    yValue = yVal / 100.0 * m_nMapHeight;
}
