#ifndef GRAPHICSTEXTITEM_H
#define GRAPHICSTEXTITEM_H

#include <QFont>

#include "graphicsitem.h"

class GraphicsTextItem : public GraphicsItem
{
public:
    explicit GraphicsTextItem(QGraphicsItem *parentItem = nullptr, QObject *parent = nullptr);
    explicit GraphicsTextItem(const QString &text, const QFont &font, qreal scaleX,
                              QGraphicsItem *parentItem = nullptr, QObject *parent = nullptr);

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
    class GraphicsSimpleTextItem;
    GraphicsSimpleTextItem *m_textItem = nullptr;

    qreal m_fontWidth;
    qreal m_fontHeight;
    QString m_text;
    QFont m_font;
    int m_initialFontSize;
    int m_lastFontSize;
//    int m_descent;
//    QPointF m_originPos;
};

#endif // GRAPHICSTEXTITEM_H
