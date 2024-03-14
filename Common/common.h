#ifndef COMMON_H
#define COMMON_H

#include <QGraphicsItem>

constexpr const char *X = "xPt";
constexpr const char *Y = "yPt";
constexpr const char *Z = "zPt";
constexpr const char *WIDTH = "width";
constexpr const char *HEIGHT = "height";
constexpr const char *ROTATE = "rotate";

constexpr const char *TEXT = "text";
constexpr const char *FONTSIZE = "fontSize";

const static int ROTATE_HANDLE_WIDTH = 14;
const static int SIZE_HANDLE_WIDTH = 6;
const static int LINE_HANDLE_WIDTH = 20;
const static int GRID_SIZE = 10;

enum GraphicsItemType
{
    GroupItem = QGraphicsItem::UserType + 1,
    RectItem,
    TextItem,
    BarcodeItem,
    EllipseItem,
    ImageItem,
    TypeCount
};

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

#endif // COMMON_H
