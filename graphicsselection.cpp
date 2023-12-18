#include "graphicsselection.h"
#include "graphicshandle.h"

GraphicsSelection::GraphicsSelection(QGraphicsScene *parent)
    : m_scene(parent), m_item(nullptr)
{
    for (int i = GraphicsHandle::LeftTop; i < GraphicsHandle::HandleTypeEnd; ++i) {
        GraphicsHandle *handle = new GraphicsHandle(m_scene, static_cast<GraphicsHandle::HandleType>(i));
        m_handleList.push_back(handle);
    }
    //    hide();
}

void GraphicsSelection::setItem(QGraphicsItem *item)
{
    if (item == nullptr) {
        hide();
        m_item = nullptr;
        return;
    }

    m_item = item;

    updateActive();
    updateGeometry();
    show();
}

bool GraphicsSelection::isUsed() const
{
    return m_item != nullptr;
}

void GraphicsSelection::updateActive()
{

}

void GraphicsSelection::updateGeometry()
{
    if (!m_item) return;
    const QRectF r =  m_item->mapRectToScene(m_item->boundingRect());
//    const int w = GRAPHICS_HANDLE_SIZE;
//    const int h = GRAPHICS_HANDLE_SIZE;

    foreach (GraphicsHandle *hndl, m_handleList) {
        if (!hndl)
            continue;
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
        case GraphicsHandle::Rotate:
            hndl->move(r.x() + r.width() / 2, r.y() + r.height() + ROTATE_HANDLE_MARGIN);
            break;
        default:
            break;
        }
    }
}

void GraphicsSelection::hide()
{
    for (GraphicsHandle *h : m_handleList) {
        if (h) {
            h->hide();
        }
    }
}

void GraphicsSelection::show()
{
    for (GraphicsHandle *h : m_handleList) {
        if (h) {
            h->show();
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
    foreach (GraphicsHandle *handle, m_handleList) {
        if (handle->contains(point)) {
            return handle->handleType();
        }
    }
    return GraphicsHandle::Handle_None;
}

QPointF GraphicsSelection::handlePos(int handleType) const
{
    foreach (GraphicsHandle *handle, m_handleList) {
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
    case GraphicsHandle::Right:
        pt = m_handleList[GraphicsHandle::Left - 1]->pos();
        break;
    case GraphicsHandle::RightTop:
        pt = m_handleList[GraphicsHandle::GraphicsHandle::LeftBottom - 1]->pos();
        break;
    case GraphicsHandle::RightBottom:
        pt = m_handleList[GraphicsHandle::LeftTop - 1]->pos();
        break;
    case GraphicsHandle::LeftBottom:
        pt = m_handleList[GraphicsHandle::RightTop - 1]->pos();
        break;
    case GraphicsHandle::Bottom:
        pt = m_handleList[GraphicsHandle::Top - 1]->pos();
        break;
    case GraphicsHandle::LeftTop:
        pt = m_handleList[GraphicsHandle::RightBottom - 1]->pos();
        break;
    case GraphicsHandle::Left:
        pt = m_handleList[GraphicsHandle::Right - 1]->pos();
        break;
    case GraphicsHandle::Top:
        pt = m_handleList[GraphicsHandle::Bottom - 1]->pos();
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
QGraphicsItem *GraphicsSelection::item() const
{
    return m_item;
}

