#ifndef SCENEGRAPHICS_H
#define SCENEGRAPHICS_H

#include <QSet>
#include <QGraphicsScene>

class GraphicsItem;
class SceneGraphics : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit SceneGraphics(QObject* parent = nullptr);

    ~SceneGraphics();

    bool isControlModifier() const;

    void setIsControlModifier(bool newIsControlModifier);

    void addItem(QGraphicsItem *item);

    void addItem(GraphicsItem *item);

    void removeItem(QGraphicsItem *item);

    void removeItem(GraphicsItem *item);

    int gridSize() const;

signals:
    void deleteGraphicsItems();

    //    void deleteGraphicsItems(QList<GraphicsItem *> items);

    //    void updateItemHandle(GraphicsItem *item);

    //    void handleStateChange(GraphicsItem *item, bool isHide);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    //    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;

    void drawBackground(QPainter *painter, const QRectF &rect) override;

private:
    void deselectItems();

private:
    bool m_isControlModifier = false;
    QSet<GraphicsItem *> m_items;
    int m_gridSize = 10;
};

#endif // SCENEGRAPHICS_H
