#include "PositionAttribute.h"

PositionAttribute::PositionAttribute(AttributeType type, NodeBase *parentNode)
    :AttributeBase(type, parentNode)
{

}

PositionAttribute::~PositionAttribute()
{

}

// 设置/获取 当前值
void PositionAttribute::setCurrentValue(const QPoint& value)
{
    bool needSendSignal = true;
    if (m_value == value)
        needSendSignal = false;

    m_value = value;

    // 发送信号
    if (needSendSignal)
        emit valueChanged(value);
}

QPoint PositionAttribute::getCurrentValue()
{
    return m_value;
}
