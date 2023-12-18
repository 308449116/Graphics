#ifndef CANVASBARCODEITEM_H
#define CANVASBARCODEITEM_H

#include "canvasitembase.h"
#include "Barcode.h"

namespace sojet {
    namespace barcode {
        class Barcode;
    }
}

class CanvasBarcodeItem : public CanvasItemBase
{
    Q_OBJECT

public:
    CanvasBarcodeItem(QGraphicsItem* parentItem = nullptr);
    ~CanvasBarcodeItem();

    // 属性相关
    // 设置尺寸
//    void setSize(int width, int height);

protected:
    void customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    void encode();
private slots:
    void onValueChanged(void);
    void onRoundValueChanged(const QVariant& value);
private:
    QSharedPointer<sojet::barcode::Barcode> m_barcode;
};

#endif
