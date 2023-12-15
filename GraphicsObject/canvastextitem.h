#ifndef CANVASTEXTITEM_H
#define CANVASTEXTITEM_H

#include <QGraphicsItem>
#include <QFont>
#include "canvasitembase.h"
//#include "NDNodeManager.h"
//#include "NDNodeBase.h"

//class NDBoolAttribute;
//class NDIntAttribute;
//class NDColorAttribute;
class QTextLayout;
class CanvasTextItem : public CanvasItemBase
{
    Q_OBJECT

public:
    CanvasTextItem(QGraphicsItem* parentItem = nullptr);
    ~CanvasTextItem();

    // 设置文本
    void setCurrentText(const QString& text);
    QString getCurrentText() const;

    // 设置字体
    void setCurrentFont(const QFont& font);
    QFont getCurrentFont() const;

protected:
    // 自定义元素绘制
    void customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
//    void mouseMoveResizeOperator(const QPointF& scenePos, const QPointF& loacalPos) override;

private:
    QString m_Text;
    QFont m_font;
    int m_descent;
//    void initAttribute(void);

//    NDBoolAttribute* m_pBOutLineAttribute = nullptr;                // 是否显示轮廓线
//    NDIntAttribute* m_pOutLineWidthAttribute = nullptr;             // 轮廓线宽度
//    NDColorAttribute* m_pOutLineColorAttribute = nullptr;           // 轮廓线颜色

//    NDIntAttribute* m_pFontSizeAttribute = nullptr;                 // 字体大小
//    NDIntAttribute* m_pPenSizeAttribute = nullptr;                  // 画笔大小
//    NDColorAttribute* m_pTtextColorAttribute = nullptr;               // 文字颜色
//    NDBoolAttribute* m_pBFillColorAttribute = nullptr;              // 是否填充颜色
//    NDColorAttribute* m_pFillColorAttribute = nullptr;              // 填充颜色

//    NDStringAttribute* m_pTextValueAttribute = nullptr;             // 文本内容
private slots:
    void onValueChanged(void);
    void onTextValueChanged(const QVariant& text);
    void onFontSizeValueChanged(const QVariant& fontSize);
};

#endif
