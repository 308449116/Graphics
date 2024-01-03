#ifndef COMMON_H
#define COMMON_H

#include <QGraphicsItem>

const static int ROTATE_HANDLE_WIDTH = 14;
const static int SIZE_HANDLE_WIDTH = 6;
const static int LINE_HANDLE_WIDTH = 20;

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
