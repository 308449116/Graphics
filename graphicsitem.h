#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H
#include <QObject>
#include "abstractgraphicstemplate.h"
#include <QGraphicsItem>

using AbstractGraphicsItem = AbstractGraphicsTemplate<QGraphicsItem>;

class GraphicsItem : public QObject,
        public AbstractGraphicsTemplate<QGraphicsItem>
{
    Q_OBJECT
public:
    enum {
        Type = UserType + 1
    };

    GraphicsItem(QGraphicsItem *parent);
    int  type() const;

signals:
    void selectedChange(QGraphicsItem *item);
};

#endif // GRAPHICSITEM_H
