#ifndef SCENEGRAPHICS_H
#define SCENEGRAPHICS_H

#include <QGraphicsScene>
#include <QGraphicsItem>

class SceneGraphics : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit SceneGraphics(QObject* parent = nullptr);
    void mouseEvent(QGraphicsSceneMouseEvent *mouseEvent);

signals:
    void deleteGraphicsItem(QGraphicsItem *);

protected:
//    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
//    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
private:
    void deselectItems();
};

#endif // SCENEGRAPHICS_H
