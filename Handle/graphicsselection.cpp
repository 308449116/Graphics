#include "graphicsselection.h"
#include "graphicssizehandle.h"
#include "graphicsdraghandle.h"
#include "graphicsrotatehandle.h"
#include "graphicslinehandle.h"
#include "viewgraphics.h"
#include "common.h"

GraphicsSelection::GraphicsSelection(ViewGraphics *view)
    : m_view(view), m_item(nullptr)
{
    GraphicsHandle *draghandle = new GraphicsDragHandle(GraphicsHandle::Drag, view, this);
    m_view->scene()->addItem(draghandle);
    m_handleList.push_back(draghandle);

    for (int i = GraphicsHandle::LeftTop; i <= GraphicsHandle::Left; ++i) {
        GraphicsHandle *handle = new GraphicsSizeHandle(i, view, this);
        m_view->scene()->addItem(handle);
        m_handleList.push_back(handle);
    }

    GraphicsHandle *rotatehandle = new GraphicsRotateHandle(GraphicsHandle::Rotate, view, this);
    m_view->scene()->addItem(rotatehandle);
    m_handleList.push_back(rotatehandle);

    GraphicsHandle *linehandle = new GraphicsLineHandle(GraphicsHandle::Line, this);
    m_view->scene()->addItem(linehandle);
    m_handleList.push_back(linehandle);
}

void GraphicsSelection::setItem(QSharedPointer<GraphicsItem> item)
{
    if (item.isNull()) {
        hide(true);
//        m_item->setSelection(nullptr);
        disconnect(m_item.data(), nullptr, this, nullptr);
        m_item.clear();
        return;
    }

    m_view->scene()->clearSelection();
    m_item = item;
//    m_item->setSelection(this);
    foreach (auto *h ,m_handleList) {
        h->setItem(m_item);
    }

    updateHandle();
    show();

    connect(item.data(), &GraphicsItem::sendUpdateHandle, this, [this](){
        updateHandle();
    });
//    connect(m_item, &GraphicsItem::handleStateSwitch, this, [this](bool isShow) {
//        if (isShow) {
//            show();
//            updateHandle();
//        } else {
//            hide();
//        }
//    });
}

bool GraphicsSelection::isUsed() const
{
    return m_item.data() != nullptr;
}

bool GraphicsSelection::isActived() const
{
    return (m_handleList[GraphicsHandle::Drag - 1]->getState() == GraphicsHandle::HandleActive);
}

void GraphicsSelection::updateHandle()
{
//    QTransform transform;
//    transform.translate(m_item->getRect().center().x(),m_item->getRect().center().y());
//    transform.rotate(0);
//    transform.translate(-m_item->getRect().center().x(),-m_item->getRect().center().y());

    if (m_item.isNull()) return;

    qreal groupAngle = m_item->groupAngle();
    qreal initAngle = m_item->rotation();

    qreal angle = 0;
    if (groupAngle == 0) {
        angle = initAngle;
        m_item->setRotation(0);
    } else {
        angle = initAngle + groupAngle;
        m_item->setRotation(-groupAngle);

    }

    const QRectF &r = m_item->subItem()->mapRectToScene(m_item->getRect());
//    const QRectF r =  m_handleList[GraphicsHandle::Drag]->mapRectFromItem(m_item.data(), m_item->getRect());
    QPointF originPoint = m_item->subItem()->mapToScene(m_item->getRect().center());
    m_item->setRotation(initAngle);
    qDebug() << "updateHandle r:" << r;
    qDebug() << "updateHandle pos:" << m_item->subItem()->pos();
    qDebug() << "updateHandle scenePos:" << m_item->subItem()->scenePos();
    qDebug() << "updateHandle getRect():" << m_item->getRect();
    qDebug() << "originPoint:" << originPoint;
    qDebug() << "groupAngle:" << groupAngle;
    qDebug() << "initAngle:" << initAngle;
    qDebug() << "angle:" << angle;
    qDebug();
//    const QRectF r2 = m_item->getRect();
//    qDebug() << "updateHandle r:" << r;
//    qDebug() << "updateHandle r2" << r2;
//    qDebug() << "updateHandle r topLeft:" << r.topLeft() << "updateHandle r2 topLeft:" << r2.topLeft();
//    qDebug() << "updateHandle r mapToScene topLeft:"
//             << m_item->mapToScene(r.topLeft()) << "updateHandle r2 mapToScene topLeft:"
//             << m_item->mapToScene(r2.topLeft());

//    const int w = GRAPHICS_HANDLE_SIZE;
//    const int h = GRAPHICS_HANDLE_SIZE;

//    m_handleList[GraphicsHandle::Drag]->setRotation(0);
//    const QRectF &r = m_handleList[GraphicsHandle::Drag]->mapRectFromItem(m_item.data(), m_item->getRect());

    foreach (auto *hndl, m_handleList) {
        if (!hndl)
            continue;
        hndl->setRotation(0);


        switch (hndl->handleType()) {
        case GraphicsHandle::LeftTop:
            hndl->move(r.x(), r.y());
            break;
        case GraphicsHandle::Top:
            hndl->move(r.x() + r.width() / 2, r.y());
            break;
        case GraphicsHandle::RightTop:
            hndl->move(r.x() + r.width(), r.y());
            break;
        case GraphicsHandle::Right:
            hndl->move(r.x() + r.width(), r.y() + r.height() / 2);
            break;
        case GraphicsHandle::RightBottom:
            hndl->move(r.x() + r.width(), r.y() + r.height());
            break;
        case GraphicsHandle::Bottom:
            hndl->move(r.x() + r.width() / 2, r.y() + r.height());
            break;
        case GraphicsHandle::LeftBottom:
            hndl->move(r.x(), r.y() + r.height());
            break;
        case GraphicsHandle::Left:
            hndl->move(r.x(), r.y() + r.height() / 2);
            break;
        case GraphicsHandle::Drag:
//            qDebug() << "updateHandle handleType:" << hndl->handleType()
//                     << "  rect:" << r
//                     << "  originPoint:" << originPoint;
//            qDebug() << "updateHandle setLocalRect rect:"
//                     << hndl->mapRectFromItem(m_item.data(), m_item->getRect());
//            qDebug() << "updateHandle setLocalRect r:"
//                     << r;
            hndl->setLocalRect(r);
//            hndl->move(originPoint.x(), originPoint.y());
            break;
        case GraphicsHandle::Rotate:
            hndl->move(r.x() + r.width() / 2, r.y() + r.height() +
                       LINE_HANDLE_WIDTH + ROTATE_HANDLE_WIDTH / 2);
            break;
        case GraphicsHandle::Line:
            hndl->move(r.x() + r.width() / 2, (r.y() + r.height() +
                       LINE_HANDLE_WIDTH + ROTATE_HANDLE_WIDTH / 2) / 2);
            break;
        default:
            break;
        }

//        qDebug() << "updateHandle handleType:" << hndl->handleType()
//                 << "  pos:" << hndl->pos();

        hndl->setTransformOriginPoint(hndl->mapFromScene(originPoint));
        hndl->setRotation(angle);
//        qDebug() << "updateHandle handleType:" << hndl->handleType()
//                 << "  pos:" << hndl->pos()
//                 << "  scenePos:" << hndl->scenePos();
    }
}

//void GraphicsSelection::updateHandle()
//{
//    if (!m_item) return;
//    const QRectF r =  m_item->mapRectToScene(m_item->getRect());
//    const QRectF r2 = m_item->getRect();
//    qDebug() << "updateHandle r:" << r;
//    qDebug() << "updateHandle r2" << r2;
//    qDebug() << "updateHandle r topLeft:" << r.topLeft() << "updateHandle r2 topLeft:" << r2.topLeft();
//    qDebug() << "updateHandle r mapToScene topLeft:"
//             << m_item->mapToScene(r.topLeft()) << "updateHandle r2 mapToScene topLeft:"
//             << m_item->mapToScene(r2.topLeft());

//    QPointF topLeft = m_item->mapToScene(r2.topLeft());
//    //    QPointF top = r2.top();
//    QPointF topRight = m_item->mapToScene(r2.topRight());
//    //    QPointF left = r2.left();
//    //    QPointF right = r2.right();
//    QPointF bottomLeft = m_item->mapToScene(r2.bottomLeft());
//    //    QPointF bottom = r2.bottom();
//    QPointF bottomRight = m_item->mapToScene(r2.bottomRight());

//    //    const int w = GRAPHICS_HANDLE_SIZE;
//    //    const int h = GRAPHICS_HANDLE_SIZE;

//    foreach (GraphicsHandle *hndl, m_handleList) {
//        if (!hndl)
//            continue;
//        switch (hndl->handleType()) {
//        case GraphicsHandle::LeftTop:
//            hndl->setPos(topLeft);
//            break;
//        case GraphicsHandle::Top:
//            hndl->setPos((topRight.x() + topLeft.x()) / 2, (topRight.y() + topLeft.y()) / 2);
//            break;
//        case GraphicsHandle::RightTop:
//            hndl->setPos(topRight);
//            break;
//        case GraphicsHandle::Right:
//            hndl->setPos((bottomRight.x() +topRight.x()) / 2, (bottomRight.y() + topRight.y()) / 2);
//            break;
//        case GraphicsHandle::RightBottom:
//            hndl->setPos(bottomRight);
//            break;
//        case GraphicsHandle::Bottom:
//            hndl->setPos((bottomRight.x() + bottomLeft.x()) / 2, (bottomRight.y() + bottomLeft.y()) / 2);
//            break;
//        case GraphicsHandle::LeftBottom:
//            hndl->setPos(bottomLeft);
//            break;
//        case GraphicsHandle::Left:
//            hndl->setPos((bottomLeft.x() + topLeft.x()) / 2, (bottomLeft.y() + topLeft.y()) / 2);
//            break;
//        case GraphicsHandle::Drag:
////            qDebug() << "updateHandle handleType:" << hndl->handleType()
////                     << "  rect:" << r
////                     << "  originPoint:" << originPoint;
//            hndl->setLocalRect(QRectF(topLeft, QSizeF(r2.width(), r2.height())));
////            hndl->move(originPoint.x(), originPoint.y());
//            break;
//        case GraphicsHandle::Rotate:
//            hndl->move(r.x() + r.width() / 2, r.y() + r.height() +
//                       LINE_HANDLE_WIDTH + ROTATE_HANDLE_WIDTH / 2);
//            break;
//        case GraphicsHandle::Line:
//            hndl->move(r.x() + r.width() / 2, (r.y() + r.height() +
//                       LINE_HANDLE_WIDTH + ROTATE_HANDLE_WIDTH / 2) / 2);
//            break;
//        default:
//            break;
//        }
//    }
//}

void GraphicsSelection::hide(bool isHideDragHandle)
{
    for (GraphicsHandle *h : m_handleList) {
        if (h && (h->handleType() != GraphicsHandle::Drag || isHideDragHandle)) {
            h->hide();
        }
    }
}

void GraphicsSelection::setOpacity(qreal opacity)
{
    for (GraphicsHandle *h : m_handleList) {
        if (h && h->handleType() != GraphicsHandle::Drag) {
            h->setOpacity(opacity);
        }
    }
}

void GraphicsSelection::show()
{
    for (GraphicsHandle *h : m_handleList) {
        if (h) {
            h->show();
            if (h->handleType() == GraphicsHandle::Drag ) {
                h->setState(GraphicsHandle::HandleActive);
                h->setSelected(true);
            }
        }
    }
}

void GraphicsSelection::update()
{
    for (GraphicsHandle *h : m_handleList) {
        if (h) {
            h->update();
        }
    }
}

int GraphicsSelection::collidesWithHandle(const QPointF &point) const
{
    foreach (auto *handle, m_handleList) {
//        qDebug() << "handleType:" << handle->handleType()
//             << "  pos:" << handle->pos()
//            << "  scene pos:" << point;
        if (handle->contains(handle->mapFromScene(point))) {
            return handle->handleType();
        }
    }
    return GraphicsHandle::Handle_None;
}

QPointF GraphicsSelection::handlePos(int handleType) const
{
    foreach (auto *handle, m_handleList) {
        if (handle->handleType() == handleType) {
            return handle->pos();
        }
    }
    return QPointF();
}

QPointF GraphicsSelection::opposite(int handle) const
{
    QPointF pt;
    switch (handle) {
    case GraphicsHandle::LeftTop:
        pt = m_handleList[GraphicsHandle::RightBottom - 1]->scenePos();
        break;
    case GraphicsHandle::Top:
        pt = m_handleList[GraphicsHandle::Bottom - 1]->scenePos();
        break;
    case GraphicsHandle::RightTop:
        pt = m_handleList[GraphicsHandle::GraphicsHandle::LeftBottom - 1]->scenePos();
        break;
    case GraphicsHandle::Right:
        pt = m_handleList[GraphicsHandle::Left - 1]->scenePos();
        break;
    case GraphicsHandle::RightBottom:
        pt = m_handleList[GraphicsHandle::LeftTop - 1]->scenePos();
        break;
    case GraphicsHandle::Bottom:
        pt = m_handleList[GraphicsHandle::Top - 1]->scenePos();
        break;
    case GraphicsHandle::LeftBottom:
        pt = m_handleList[GraphicsHandle::RightTop - 1]->scenePos();
        break;
    case GraphicsHandle::Left:
        pt = m_handleList[GraphicsHandle::Right - 1]->scenePos();
        break;
    }
    return pt;
}

int GraphicsSelection::swapHandle(int handle, const QPointF& scale ) const
{
    int handleType = GraphicsHandle::Handle_None;
    if ( scale.x() < 0 || scale.y() < 0 ){
        switch (handle) {
        case GraphicsHandle::RightTop:
            if ( scale.x() < 0 && scale.y() < 0 )
                handleType = GraphicsHandle::LeftBottom;
            else if ( scale.x() > 0 && scale.y() < 0 )
                handleType = GraphicsHandle::RightBottom;
            else
                handleType = GraphicsHandle::LeftTop;
            break;
        case GraphicsHandle::RightBottom:
            if ( scale.x() < 0 && scale.y() < 0 )
                handleType = GraphicsHandle::LeftTop;
            else if ( scale.x() > 0 && scale.y() < 0 )
                handleType = GraphicsHandle::RightTop;
            else
                handleType = GraphicsHandle::LeftBottom;
            break;
        case GraphicsHandle::LeftBottom:
            if ( scale.x() < 0 && scale.y() < 0 )
                handleType = GraphicsHandle::RightTop;
            else if ( scale.x() > 0 && scale.y() < 0 )
                handleType = GraphicsHandle::LeftTop;
            else
                handleType = GraphicsHandle::RightBottom;
            break;
        case GraphicsHandle::LeftTop:
            if ( scale.x() < 0 && scale.y() < 0 )
                handleType = GraphicsHandle::RightBottom;
            else if ( scale.x() > 0 && scale.y() < 0 )
                handleType = GraphicsHandle::LeftBottom;
            else
                handleType = GraphicsHandle::RightTop;
            break;
        case GraphicsHandle::Right:
            if (scale.x() < 0 )
                handleType = GraphicsHandle::Left;
            break;
        case GraphicsHandle::Left:
            if (scale.x() < 0 )
                handleType = GraphicsHandle::Right;
            break;
        case GraphicsHandle::Top:
            if (scale.y()<0)
                handleType = GraphicsHandle::Bottom;
            break;
        case GraphicsHandle::Bottom:
            if (scale.y()<0)
                handleType = GraphicsHandle::Top;
            break;
        }
    }
    return handleType;
}

void GraphicsSelection::setZValue(qreal z)
{
    foreach (auto handle, m_handleList) {
        handle->setZValue(z);
    }
}

qreal GraphicsSelection::zValue()
{
//    foreach (auto item, m_handleList) {
//        qDebug() << "GraphicsSelection::zValue: " << item->zValue();
//        qDebug() << "GraphicsSelection::handleType: " << item->handleType();
//    }
    return m_handleList[GraphicsHandle::Drag - 1]->zValue();
}

QSharedPointer<GraphicsItem> GraphicsSelection::item() const
{
    return m_item;
}
