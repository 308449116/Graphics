#ifndef POSITIONATTRIBUTE_H
#define POSITIONATTRIBUTE_H

#include "AttributeBase.h"
#include <QPoint>

class PositionAttribute : public AttributeBase
{
    Q_OBJECT
public:
    PositionAttribute(AttributeType type, NodeBase *parentNode = nullptr);
    ~PositionAttribute();

    // 设置/获取 当前值
    void setCurrentValue(const QPoint& value);
    QPoint getCurrentValue();

private:
    QPoint m_value;

signals:
    void valueChanged(const QPoint& value);
};

#endif
