#ifndef CANVASITEMMANAGER_H
#define CANVASITEMMANAGER_H

#include <QObject>

class CanvasItemManager : public QObject
{
    Q_OBJECT
public:
    enum CanvasItemType
    {
        ITEM_NONE,
        ITEM_CANVAS,
        ITEM_RECT,
        ITEM_TEXT,
        ITEM_ELLIPSE,
        ITEM_IMAGE,
        ITEM_PATH,
        ITEM_END
    };
    explicit CanvasItemManager(QObject *parent = nullptr);
    ~CanvasItemManager();

signals:

};

#endif // CANVASITEMMANAGER_H
