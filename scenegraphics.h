#ifndef SCENEGRAPHICS_H
#define SCENEGRAPHICS_H

#include <QGraphicsScene>

#include "graphicsabstracttemplate.h"

class SceneGraphics : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit SceneGraphics(QObject* parent = nullptr);

    ~SceneGraphics();

    bool isControlModifier() const;

    void setIsControlModifier(bool newIsControlModifier);

    void addItem(QGraphicsItem *item);

    void addItem(QSharedPointer<GraphicsAbstractItem> item);

    void removeItem(QGraphicsItem *item);

    void removeItem(QSharedPointer<GraphicsAbstractItem> item);

signals:
    void deleteGraphicsItems();

//    void deleteGraphicsItems(QList<QSharedPointer<GraphicsAbstractItem> > items);

//    void updateItemHandle(GraphicsItem *item);

//    void handleStateChange(GraphicsItem *item, bool isHide);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

//    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;
private:
    void deselectItems();

private:
    bool m_isControlModifier = false;
    QSet<QSharedPointer<GraphicsAbstractItem> > m_items;
};

#endif // SCENEGRAPHICS_H
