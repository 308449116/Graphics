#ifndef VIEWGRAPHICS_H
#define VIEWGRAPHICS_H

#include <QGraphicsView>
#include <QGraphicsScene>

class SceneGraphics;
class QGraphicsItem;

class ViewGraphics : public QGraphicsView
{
    Q_OBJECT
public:
    explicit ViewGraphics(QWidget* parent = nullptr);
    ~ViewGraphics();
    // Create Items
    void createTextItem(void);
    void createRectItem(void);
    void createBarcoedItem(void);

    //Manage Items
    bool isManaged(QGraphicsItem *item);
    void manageItem(QGraphicsItem *item);
    void unmanageItem(QGraphicsItem *item);

    int collidesWithHandle(QGraphicsItem *item, const QPointF & point ) const;
    bool isItemSelected(QGraphicsItem *item) const;
    QPointF opposite(QGraphicsItem *item, int handleType) const;

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
signals:
private:
    bool trySelectItem(QGraphicsItem *item);
    class Selection;
    Selection *m_selection;
    SceneGraphics *m_scene;
    QSet<QGraphicsItem *> m_manageItem;
    bool m_isMousePress = false;
    QGraphicsItem  *m_currentItem = nullptr;
};

#endif // VIEWGRAPHICS_H
