#ifndef GRAPHICSTEXTITEM_H
#define GRAPHICSTEXTITEM_H

#include "graphicsitem.h"
#include <QFont>

class GraphicsTextItem : public GraphicsItem
{
public:
    explicit GraphicsTextItem(const QString &text, GraphicsItem *parent = nullptr);
    void move(const QPointF &point) override;
    void stretch(qreal sx , qreal sy , const QPointF &origin) override;
    GraphicsItem *duplicate () const override;
    void updateCoordinate() override;

    // 设置文本
    void setText(const QString& text);
    QString text() const;

    // 设置字体
    void setFont(const QFont& font);
    QFont font() const;

protected:
    void customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    void updateLocalRect();
    QString m_text;
    QFont m_font;
    int m_initialFontSize;
    int m_descent;
    qreal m_scaleX = 1;
    qreal m_scaleY = 1;
    QTransform m_transform;
    QPointF m_originPos;
};

#endif // GRAPHICSTEXTITEM_H
