#ifndef VIEWGRAPHICS_H
#define VIEWGRAPHICS_H

#include <QGraphicsView>
#include <QGraphicsScene>

class SceneGraphics;
class GraphicsItem;

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
    bool isManaged(GraphicsItem *item);
    void manageItem(GraphicsItem *item);
    void unmanageItem(GraphicsItem *item);

    int collidesWithHandle(GraphicsItem *item, const QPointF & point ) const;
    bool isItemSelected(GraphicsItem *item) const;
    QPointF opposite(GraphicsItem *item, int handleType) const;

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

signals:
private slots:
    void selectedStateChange(GraphicsItem *item, bool checked);
    void removeItemFormScene(GraphicsItem *item);
    void updateItemHandle(GraphicsItem *item);
    void handleStateSwitch(GraphicsItem *item, bool isHide);

private:
    bool trySelectItem(GraphicsItem *item);
    void addItemToScene(GraphicsItem *item);
    class Selection;
    Selection *m_selection;
    SceneGraphics *m_scene;
    QSet<GraphicsItem *> m_manageItem;
    bool m_isMousePress = false;
    GraphicsItem  *m_currentItem = nullptr;
};

#endif // VIEWGRAPHICS_H
