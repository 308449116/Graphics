#ifndef SCENEGRAPHICS_H
#define SCENEGRAPHICS_H

#include <QGraphicsScene>

class SceneGraphics : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit SceneGraphics(QObject* parent = nullptr);
//    void mouseEvent(QGraphicsSceneMouseEvent *mouseEvent);

    bool isControlModifier() const;
    void setIsControlModifier(bool newIsControlModifier);

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
    bool m_isControlModifier = false;
//    Operator *m_operator;
};

#endif // SCENEGRAPHICS_H
