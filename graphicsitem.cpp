#include "graphicsitem.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>

GraphicsItem::GraphicsItem(QGraphicsItem *parent)
    : GraphicsAbstractItem(parent)
{
//    setFlag(QGraphicsItem::ItemIsMovable, true);
//    setFlag(QGraphicsItem::ItemIsSelectable, true);
//    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

int GraphicsItem::type() const
{
    return Type;
}

QRectF GraphicsItem::boundingRect() const
{
    QRectF rect = getRect();
//    if (isSelected()) {
//        rect.adjust(-3.0, -3.0, 3.0, 3.0);
//        rect.adjust(0, 0, 0, 20);
//    }
    return rect;
}

void GraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter->setRenderHint(QPainter::TextAntialiasing, true);

    // 自定义绘制
    customPaint(painter, option, widget);

    //高亮选中
    if (option->state & QStyle::State_Selected) {
        qt_graphicsItem_highlightSelected(this, painter, option);
    }
}

//QVariant GraphicsItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
//{
//    if ( change == QGraphicsItem::ItemSelectedHasChanged ) {
//        QGraphicsItemGroup *group = dynamic_cast<QGraphicsItemGroup*>(parentItem());
//        if (!group) {
//            emit selectedChange(this, value.toBool());
//        } else {
//            setSelected(false);
//            return QVariant::fromValue<bool>(false);
//        }
//    }

//    return QGraphicsItem::itemChange(change, value);
//}

//void GraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
//{
//    QGraphicsItem::mousePressEvent(event);
//}

//void GraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
//{
////    if (!m_hideHandleSended) {
////        emit handleStateSwitch(false);
////        m_hideHandleSended = true;
////    }
//    QGraphicsItem::mouseMoveEvent(event);
//}

//void GraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
//{
////    m_hideHandleSended = false;
////    emit handleStateSwitch(true);
//    QGraphicsItem::mouseReleaseEvent(event);
//}
