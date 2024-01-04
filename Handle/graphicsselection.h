#ifndef GRAPHICSSELECTION_H
#define GRAPHICSSELECTION_H

#include <QRectF>
#include <QObject>
#include <QSharedPointer>

class ViewGraphics;
class GraphicsItem;
class GraphicsHandle;

class GraphicsSelection : public QObject
{
    Q_OBJECT
public:
    explicit GraphicsSelection(ViewGraphics *view);

    void setItem(QSharedPointer<GraphicsItem> item);

    bool isUsed() const;

    void updateGeometry();

    void hide(bool isHideDragHandle = true);

    void show();

    void update();

    void setOpacity(qreal opacity);

    int collidesWithHandle( const QPointF & point ) const;

    QPointF handlePos(int handleType) const;

    QSharedPointer<GraphicsItem> item() const;

    QPointF opposite(int handle) const;

    int swapHandle(int handle, const QPointF &scale) const;

private:
    ViewGraphics *m_view;
    QSharedPointer<GraphicsItem> m_item;
    QList<GraphicsHandle *> m_handleList;
};

#endif // GRAPHICSSELECTION_H
