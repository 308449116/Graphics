#include "abstractgraphicstemplate.h"

template<typename BaseType>
AbstractGraphicsTemplate<BaseType>::AbstractGraphicsTemplate(QGraphicsItem *parent)
    : BaseType (parent)
{

}

template<typename BaseType>
QRectF AbstractGraphicsTemplate<BaseType>::rect() const
{
   return m_localRect;
}

template<typename BaseType>
qreal AbstractGraphicsTemplate<BaseType>::width() const
{
    return m_width;
}

template<typename BaseType>
void AbstractGraphicsTemplate<BaseType>::setWidth(qreal width)
{
    m_width = width;
}

template<typename BaseType>
qreal AbstractGraphicsTemplate<BaseType>::height() const
{
    return m_height;
}

template<typename BaseType>
void AbstractGraphicsTemplate<BaseType>::setHeight(qreal height)
{
    m_height = height;
}
