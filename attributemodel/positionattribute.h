#ifndef POSITIONATTRIBUTE_H
#define POSITIONATTRIBUTE_H

#include "attributebase.h"
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

signals:
    void valueChanged(const QPoint& value);

private:
    QPoint m_value;
};

#endif
