#ifndef GRAPHICSTEXTITEM_H
#define GRAPHICSTEXTITEM_H

#include <QFont>

#include "graphicsitem.h"

class GraphicsTextItem : public GraphicsItem
{
public:
    explicit GraphicsTextItem(QObject *parent = nullptr);
    explicit GraphicsTextItem(const QString &text, QObject *parent = nullptr);

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

    //protected:
    //    void customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    void updateLocalRect();
    QSizeF getSizeByFontSize(int fontSize);

private:
    QGraphicsSimpleTextItem *m_textItem = nullptr;
    QString m_text;
    QFont m_font;
    qreal m_initialFontSize;
    int m_lastFontSize;
    int m_descent;
    QPointF m_textPos;
    QTransform m_transform;
    bool m_fontChange;
};

#endif // GRAPHICSTEXTITEM_H
