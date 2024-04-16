#include "graphicsdraghandle.h"
#include "graphicsselection.h"
#include "viewgraphics.h"
//#include "graphicsobject/graphicstextitem.h"

#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QInputDialog>
#include <QMessageBox>

GraphicsDragHandle::GraphicsDragHandle(int handleType, ViewGraphics *view,
                                       GraphicsSelection *selection, QGraphicsItem *parent)
    :GraphicsHandle(handleType, selection, parent), m_view(view)
{
    setState(GraphicsHandleState::HandleActive);
    setSelected(false);
//    setFocus();
//    setActive(true);
//    setSelected(true);
}

void GraphicsDragHandle::customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

//    qDebug() << "GraphicsDragHandle boundingRect" << m_item->boundingRect();
//    qDebug() << "GraphicsDragHandle boundingRect" << boundingRect();
//    if ((getState() & GraphicsHandleState::HandleActive) ||
//        m_item->type() == GraphicsItemType::GroupItem) {
        painter->save();
        painter->setPen(Qt::DashLine);
        QRectF rect = mapRectFromItem(m_item->subItem(), m_item->getRect());
//        qDebug() << "GraphicsDragHandle customPaint rect:"
//                 << rect;

        painter->drawRect(rect);
        painter->restore();
//    }
}

void GraphicsDragHandle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug() << "111 GraphicsDragHandle mousePressEvent event->modifiers:" << event->modifiers();
//    qDebug() << "111 GraphicsDragHandle mousePressEvent multiSelect:" << ((event->modifiers() & Qt::ControlModifier) != 0);
    QGraphicsItem::mousePressEvent(event);
    qDebug () << "pos:" << m_item->subItem()->pos();
    qDebug () << "boundingRect:" << m_item->subItem()->boundingRect();
    qDebug () << "scenePos:" << m_item->subItem()->scenePos();
    qDebug () << "sceneBoundingRect:" << m_item->subItem()->sceneBoundingRect();
    qDebug () << "mapRectToScene:" << m_item->subItem()->mapRectToScene(m_item->getRect());
    qDebug () << "uid:" << m_item->uid();
    qDebug () << "zValue:" << m_selection->zValue();

//    qDebug() << "========= mousePressEvent getRect:" << m_item->getRect();
//    qDebug() << "========= mousePressEvent sceneBoundingRect:" << m_item->subItem()->sceneBoundingRect();
//    qDebug() << "========= mousePressEvent pos:" << m_item->pos();
//    qDebug() << "========= mousePressEvent scenePos:" << m_item->subItem()->scenePos();

//    qDebug() << "========= mousePressEvent zValue:" << m_selection->zValue();
//    qDebug() << "========= mousePressEvent rotation:" << m_item->rotation();
//    qDebug() << "========= mousePressEvent groupAngle:" << m_item->groupAngle();
//    qDebug() << "========= mousePressEvent initAngle:" << m_item->initAngle();
//    qDebug() << "========= mousePressEvent transformOriginPoint:" << m_item->subItem()->transformOriginPoint();
//    qDebug("========= mousePressEvent parentItem:%p" , m_item->subItem()->parentItem());
//    qDebug("========= mousePressEvent group:%p" , m_item->subItem()->group());
//    qDebug("========= mousePressEvent subItem:%p" , m_item->subItem());

//    qDebug() << "========= mousePressEvent pos:" << m_item->pos();
//    qDebug() << "========= mousePressEvent scenePos:" << m_item->subItem()->scenePos();
    qDebug();

    if (m_item->subItem()->parentItem()) {
        m_lastPos = m_pressedPos = m_item->subItem()->parentItem()->mapFromScene(event->scenePos());
    } else {
        m_lastPos = m_pressedPos = event->scenePos();
    }
//    qDebug() << "m_pressedPos:" << m_lastPos;
//    m_initialPos = m_item->pos();
    m_itemPosHash.clear();

    QList<QGraphicsItem *> items = m_view->scene()->selectedItems();
    for (auto item : items) {
        GraphicsHandle *handle = qgraphicsitem_cast<GraphicsHandle *>(item);
        if (handle->handleType() == GraphicsHandle::Drag) {
            m_itemPosHash.insert(handle->item(), handle->item()->pos());
        }
    }
}

void GraphicsDragHandle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_item->subItem()->parentItem()) {
        m_lastPos = m_item->subItem()->parentItem()->mapFromScene(event->scenePos());
    } else {
        m_lastPos = event->scenePos();
    }

    m_selection->setOpacity(0);
//    qDebug() << "m_lastPos:" << m_lastPos;
//    qDebug() << "m_pressedPos:" << m_pressedPos;
//    qDebug() << "m_lastPos - m_pressedPos:" << m_lastPos - m_pressedPos;

    //移动处理
    qreal xV = round((m_lastPos - m_pressedPos).x() / GRID_SIZE) * GRID_SIZE;
    qreal yV = round((m_lastPos - m_pressedPos).y() / GRID_SIZE) * GRID_SIZE;
    m_offsetPos = QPointF(xV, yV);
    for (const auto &[item, initPos] : m_itemPosHash.asKeyValueRange()) {
        item->setPos(initPos + m_offsetPos);
//        item->setPos(initPos + m_lastPos - m_pressedPos);
        m_view->updateHandle(item);
    }
//    m_view->moveItems(m_itemPosHash, m_lastPos - m_pressedPos);
//    m_item->setPos(m_initialPos + (m_lastPos - m_pressedPos));
//    m_selection->updateHandle();
    QGraphicsItem::mouseMoveEvent(event);
}

void GraphicsDragHandle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_selection->setOpacity(1);

    //Undo/Redo 移动处理
    if (m_itemPosHash.count() > 0 && m_lastPos != m_pressedPos) {
        m_view->moveItemsByCmd(m_itemPosHash.keys(), m_offsetPos, true);
    }

    QGraphicsItem::mouseReleaseEvent(event);
}

//void GraphicsDragHandle::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
//{
//    if (m_item->type() == GraphicsItemType::TextItem) {
//        // 弹出文本输入框
//        bool ok;
//        QString text = QInputDialog::getText(nullptr, "输入对话框", "请输入文本:", QLineEdit::Normal, "", &ok);

//        if (ok && !text.isEmpty()) {
//            GraphicsTextItem *textItem = dynamic_cast<GraphicsTextItem *>(m_item);
////            qDebug() << "========= 11111111111111111111 pixelSize:" << textItem->font().pixelSize();

//            if (textItem) {
//                QFont font = textItem->font();
////                qDebug() << "========= 2222222222222222222 input Size:" << text.toInt();
////                font.setPixelSize(text.toInt());
////                qDebug() << "========= 444444444444444 font Size:" << font.pixelSize();
//                textItem->setText(text);
////                textItem->setFont(font);
//                m_selection->updateHandle();
//            }
////            qDebug() << "========= 3333333333 pixelSize:" << textItem->font().pixelSize();

//        }
//    }
//    QGraphicsItem::mouseDoubleClickEvent(event);
//}

QVariant GraphicsDragHandle::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if ( change == QGraphicsItem::ItemSelectedHasChanged ) {
        QGraphicsItemGroup *group = dynamic_cast<QGraphicsItemGroup*>(parentItem());
        if (!group) {
            if (value.toBool()) {
                setState(GraphicsHandleState::HandleActive);
                m_selection->show();
            } else {
                setState(GraphicsHandleState::HandleOff);
                m_selection->hide(false);
            }
        } else {
            setSelected(false);
            return QVariant::fromValue<bool>(false);
        }
    }

    return QGraphicsItem::itemChange(change, value);
}
