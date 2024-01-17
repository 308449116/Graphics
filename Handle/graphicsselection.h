#ifndef GRAPHICSSELECTION_H
#define GRAPHICSSELECTION_H

#include <QRectF>
#include <QObject>
#include <QSharedPointer>
#include "graphicsabstracttemplate.h"

class ViewGraphics;
class GraphicsHandle;

class GraphicsSelection : public QObject
{
    Q_OBJECT
public:
    explicit GraphicsSelection(ViewGraphics *view);

    void setItem(QSharedPointer<GraphicsAbstractItem> item);

    bool isUsed() const;

    bool isActived() const;

    void updateHandle();

    void hide(bool isHideDragHandle = true);

    void show();

    void update();

    void setOpacity(qreal opacity);

    int collidesWithHandle( const QPointF & point ) const;

    QPointF handlePos(int handleType) const;

    QSharedPointer<GraphicsAbstractItem> item() const;

    QPointF opposite(int handle) const;

    int swapHandle(int handle, const QPointF &scale) const;

    void setZValue(qreal z);

    qreal zValue();

private:
    ViewGraphics *m_view;
    QSharedPointer<GraphicsAbstractItem> m_item;
    QList<GraphicsHandle *> m_handleList;
};

#endif // GRAPHICSSELECTION_H
