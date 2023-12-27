#ifndef GRAPHICSSELECTION_H
#define GRAPHICSSELECTION_H

#include <QObject>
#include <QGraphicsScene>
#include <QSharedPointer>

class QGraphicsScene;
class GraphicsItem;
class GraphicsHandle;

const static int ROTATE_HANDLE_MARGIN = 20;

class GraphicsSelection : public QObject
{
    Q_OBJECT
public:
    explicit GraphicsSelection(QGraphicsScene *parent);

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
    QList<GraphicsHandle *> m_handleList;
    QGraphicsScene *m_scene;
    QSharedPointer<GraphicsItem> m_item;
};

#endif // GRAPHICSSELECTION_H
