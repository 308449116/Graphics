#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H
#include <QObject>
#include "abstractgraphicstemplate.h"

class GraphicsItem : public QObject,
        public AbstractGraphicsTemplate<QGraphicsItem>
{
    Q_OBJECT
public:
    enum {
        Type = UserType + 1
    };

    explicit GraphicsItem(QGraphicsItem *parent = nullptr);
    int  type() const;

signals:
    void selectedChange(QGraphicsItem *item);
};

#endif // GRAPHICSITEM_H
