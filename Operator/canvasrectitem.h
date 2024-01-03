#ifndef CANVASRECTITEM_H
#define CANVASRECTITEM_H

#include "canvasitembase.h"

//class NDBoolAttribute;
//class NDColorAttribute;
class CanvasRectItem : public CanvasItemBase
{
    Q_OBJECT

public:
    CanvasRectItem(QGraphicsItem* parentItem = nullptr);
    ~CanvasRectItem();

    // 设置尺寸
    void setSize(int width, int height);

protected:
    void customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    // 属性相关
//    void initAttribute();

//    NDBoolAttribute* m_pBRoundAttribute = nullptr;          // 是否为圆形

//    NDBoolAttribute* m_pBFillAttribute = nullptr;                // 是否为填充颜色
//    NDColorAttribute* m_pFillColorAttribute = nullptr;          // 填充的颜色

//    NDBoolAttribute* m_pBOutLineAttribute = nullptr;                // 是否显示轮廓线
//    NDIntAttribute* m_pOutLineWidthAttribute = nullptr;             // 轮廓线宽度
//    NDColorAttribute* m_pOutLineColorAttribute = nullptr;           // 轮廓线颜色

private slots:
    void onValueChanged(void);
    void onRoundValueChanged(const QVariant& value);
};

#endif
