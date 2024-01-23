#ifndef GRAPHICSTEXTITEM_H
#define GRAPHICSTEXTITEM_H

#include <QFont>

#include "graphicsitem.h"

class GraphicsTextItem : public GraphicsItem
{
public:
    explicit GraphicsTextItem(QObject *parent = nullptr);
    explicit GraphicsTextItem(const QString &text, const QFont &font, QObject *parent = nullptr);

    void stretch(qreal sx, qreal sy, const QPointF &origin) override;

    QSharedPointer<GraphicsItem> duplicate() const override;

    void updateCoordinate() override;

    int type() const override;

    // 设置文本
    void setText(const QString& text);
    QString text() const;

    // 设置字体
    void setFont(const QFont& font);
    QFont font() const;

private:
    void updateLocalRect();
    QSizeF getSizeByFontSize(int fontSize);

private:
    class GraphicsSimpleTextItem : public QGraphicsSimpleTextItem
    {
    public:
        explicit GraphicsSimpleTextItem(QGraphicsItem *parent = nullptr);
        explicit GraphicsSimpleTextItem(const QString &text, QGraphicsItem *parent = nullptr);

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

        QRectF boundingRect() const override;

        void setScale(qreal scaleX, qreal scaleY);
        qreal scaleY() const;
        qreal scaleX() const;

        void setItemBoundingRect(const QRectF &newItemBoundingRect);

    private:
        QRectF m_itemBoundingRect;
        qreal m_scaleX = 1;
        qreal m_scaleY = 1;
    };

    GraphicsSimpleTextItem *m_textItem = nullptr;
    QString m_text;
    QFont m_font;
    int m_initialFontSize;
    int m_lastFontSize;
    int m_descent;
    QPointF m_originPos;
    QPointF m_textPos;
};

#endif // GRAPHICSTEXTITEM_H
