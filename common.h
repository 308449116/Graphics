#ifndef COMMON_H
#define COMMON_H
#include <QGraphicsItem>

enum GraphicsItemType
{
    RectItem = QGraphicsItem::UserType + 1,
    TextItem,
    BarcodeItem,
    EllipseItem,
    ImageItem,
    TypeCount
};

#endif // COMMON_H
