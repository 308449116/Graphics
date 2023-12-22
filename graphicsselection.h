#ifndef GRAPHICSSELECTION_H
#define GRAPHICSSELECTION_H

#include <QObject>
#include <QGraphicsScene>

class QGraphicsScene;
class GraphicsItem;
class GraphicsHandle;

const static int ROTATE_HANDLE_MARGIN = 20;

class GraphicsSelection : public QObject
{
    Q_OBJECT
public:
    explicit GraphicsSelection(QGraphicsScene *parent);
    void setItem(GraphicsItem *item);
    bool isUsed() const;

    void updateActive();
    void updateGeometry();
    void hide();
    void show();
    void update();
    void setOpacity(qreal opacity);

    int collidesWithHandle( const QPointF & point ) const;
    QPointF handlePos(int handleType) const;

    GraphicsItem *item() const;
    QPointF opposite(int handle) const;
    int swapHandle(int handle, const QPointF &scale) const;
private:
    QList<GraphicsHandle *> m_handleList;
    QGraphicsScene *m_scene;
    GraphicsItem *m_item;
};

#endif // GRAPHICSSELECTION_H
