#ifndef VIEWGRAPHICS_H
#define VIEWGRAPHICS_H

#include <QSet>
#include <QGraphicsView>

#include "graphicsobject/graphicsitem.h"
//#include "utils/exceptions.h"

const static double ZOOM_FACTOR = 1.05;

enum AlignType
{
    TOP_ALIGN = 0,
    BOTTOM_ALIGN,
    LEFT_ALIGN,
    RIGHT_ALIGN,
    HCENTER_ALIGN,
    VCENTER_ALIGN,
    CENTER_ALIGN,
    HORZEVEN_ALIGN,
    VERTEVEN_ALIGN,
    WIDTH_ALIGN,
    HEIGHT_ALIGN,
    ALL_ALIGN
};

class QUndoView;
class QUndoStack;
class SceneGraphics;
class AttributeBase;
class UndoCmdManager;
class GraphicsItemManager;
class GraphicsSelectionManager;

class ViewGraphics : public QGraphicsView
{
    Q_OBJECT
public:
    explicit ViewGraphics(QWidget *parent = nullptr);

    ~ViewGraphics();

    // Create Items
    void createItemByCmd(GraphicsItemType type);

    GraphicsItem *createItem(GraphicsItemType type);

    void addItem(GraphicsItem *item);

    // remove Items
    void deleteItemsByCmd();

    void deleteItem(GraphicsItem *item, bool isFreeMemory = true);

    void deleteItems(const QList<GraphicsItem *> &items, bool isFreeMemory = true);

    // move Items
    void moveItemsByCmd(const QList<GraphicsItem *> &items,
                   const QPointF &pos, bool isMoved = true);

    void moveItems(const QList<GraphicsItem *> &items,
                   const QPointF &pos);

    // resize Items
    void resizeItemByCmd(int handleType, GraphicsItem *item,
                         const QPointF &scale, bool isResized);

    void resizeItem(int handleType, GraphicsItem *item, const QPointF &scale);

    // rotate Items
    void rotateItemByCmd(GraphicsItem *item, const qreal angle);

    void rotateItem(GraphicsItem *item, const qreal angle);

    // duplicate Items
    void duplicateItemsByCmd();
    QList<GraphicsItem *> duplicateItems(QList<GraphicsItem *> items);

    // group Items
    void groupItemsByCmd();

    GraphicsItem *groupItems(QList<GraphicsItem *> items);

    // ungroup Items
    void ungroupItemsByCmd();

    void ungroupItems(QList<GraphicsItem *> items, bool isFreeMemory = true);

    // align Items
    void alignItems(AlignType alignType);

    QString getItemDisplayName(GraphicsItemType type);

    QAction *createUndoAction();

    QAction *createRedoAction();

    bool canUndo() const;

    bool canRedo() const;

    bool isUndoCmdEnabled() const;

    void setUndoCmdEnabled(bool newIsUndoCmdEnabled);

    QUndoStack *getUndoStack() const;

    bool isControlModifier() const;

    void setIsControlModifier(bool newIsControlModifier);

    void cleanAllSelected();

    QPointF opposite(GraphicsItem *item, int handleType) const;

    void updateHandle(GraphicsItem *item);

    NodeBase *getCurrentSelectedNode();

    void setModified(bool value);

    bool isModified() const;

    bool save();
    bool saveAs();
    bool saveFile(QString *errorString, const QString &fileName);

    bool loadFile(QString *errorString, const QString &fileName);

    QList<GraphicsItem *> items();

    QList<GraphicsItem *> selectedItems();

//    void loadCanvas(QXmlStreamReader *xml);
signals:
    void itemSelectedChanged();
    void changed();
    void zoomIn(const QPoint &zoomOrigin);
    void zoomOut(const QPoint &zoomOrigin);

protected:
    void wheelEvent(QWheelEvent *wheelEvent) override;
//    void mouseMoveEvent(QMouseEvent *event) override;
//    void mousePressEvent(QMouseEvent *event) override;
//    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void onAttributeValueChanged(AttributeBase *attribute, const QVariant& value, bool cmd);

//    void removeItemsByCmd(const QList<GraphicsItem *> &items);
//    void selectedStateChange(GraphicsItem *item, bool checked);
//    void updateItemHandle(GraphicsItem *item);
//    void handleStateSwitch(GraphicsItem *item, bool isHide);

private:
//    void setZValue(GraphicsItem *item, int increment);
    void removeItem(GraphicsItem *item);
    void addGroupItems(GraphicsItem *item);
//    bool trySelectItem(GraphicsItem *item);
    void addItemToSelectionManager(GraphicsItem *item);

private:
    bool m_isUndoCmdEnabled = true;
    SceneGraphics *m_scene = nullptr;
//    GraphicsItemManager *m_itemManager = nullptr;
    GraphicsSelectionManager *m_selectionManager = nullptr;
    QUndoStack *m_undoStack = nullptr;
    bool m_modified = false;
//    mutable bool m_modified = false;

//    QSet<GraphicsItem *> m_manageItem;
//    bool m_isMousePress = false;
//    GraphicsItem  *m_currentItem = nullptr;
};

#endif // VIEWGRAPHICS_H
