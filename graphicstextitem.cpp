#include "graphicstextitem.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QApplication>
#include <QStaticText>
#include <QDebug>

GraphicsTextItem::GraphicsTextItem(const QString &text, GraphicsItem *parent)
    : GraphicsItem(parent)
{
    m_initialFontSize = 100;
    m_font = qApp->font();
    m_font.setPixelSize(m_initialFontSize);
    setText(text);
}

bool falg = false;
void GraphicsTextItem::stretch(qreal sx, qreal sy, const QPointF &origin)
{
    QTransform trans;
    trans.translate(origin.x(),origin.y());
    trans.scale(sx,sy);
    trans.translate(-origin.x(),-origin.y());
//    qDebug () << "sx:" << sx << "sy:" << sy;

    m_scaleX = sx;
    m_scaleY = sy;
    m_originPos = origin;
//    m_scaleX = sx;
//    qDebug () << "111111111 pixelSize:" << m_initialFontSize;
//    int fontSize = m_initialFontSize * sy;
//    qDebug () << "222222222 pixelSize:" << fontSize;
//    m_font.setPixelSize(fontSize);
    falg = true;
    m_transform = trans;

    qDebug () << "111111111 pixelSize:" << m_initialFontSize;

    this->setTransformOriginPoint(m_originPos);
    prepareGeometryChange();
//    this->setTransform(trans);
    m_localRect = trans.mapRect(m_initialRect);
    m_width = m_localRect.width();
    m_height = m_localRect.height();
    qDebug () << "2222222222222 pixelSize:" << m_initialFontSize;

}

void GraphicsTextItem::updateCoordinate()
{
    QPointF pt1, pt2, delta;
    pt1 = mapToScene(transformOriginPoint());
    pt2 = mapToScene(m_localRect.center());
    delta = pt1 - pt2;

    if (!parentItem()) {
        prepareGeometryChange();
        m_localRect = QRectF(-m_width / 2, -m_height / 2, m_width, m_height);
        m_width = m_localRect.width();
        m_height = m_localRect.height();
        setTransform(transform().translate(delta.x(), delta.y()));
        setTransformOriginPoint(m_localRect.center());
        moveBy(-delta.x(), -delta.y());
        setTransform(transform().translate(-delta.x(), -delta.y()));
        m_originPos = QPoint(0, 0);
    }

    m_initialFontSize = m_font.pixelSize();
    m_initialRect = m_localRect;
    m_ratio = m_width / m_height;
}

void GraphicsTextItem::move(const QPointF &point)
{
    moveBy(point.x(),point.y());
}

GraphicsItem *GraphicsTextItem::duplicate() const
{
    GraphicsTextItem *item = new GraphicsTextItem(m_text);
    item->m_width = width();
    item->m_height = height();
    item->setPos(pos().x(),pos().y());
    item->setTransform(transform());
    item->setTransformOriginPoint(transformOriginPoint());
    item->setRotation(rotation());
    item->setScale(scale());
    item->setZValue(zValue()+0.1);
    item->setFont(m_font);
    item->updateCoordinate();
    return item;
}

void GraphicsTextItem::setText(const QString &text)
{
    m_text = text;
    updateLocalRect();
}

QString GraphicsTextItem::text() const
{
    return m_text;
}

void GraphicsTextItem::setFont(const QFont &font)
{
    m_font = font;
    m_initialFontSize = m_font.pixelSize();
    updateLocalRect();
}

QFont GraphicsTextItem::font() const
{
    return m_font;
}

void GraphicsTextItem::customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qDebug () << "============= m_localRect:" << m_localRect;
    Q_UNUSED(widget)
    Q_UNUSED(option)
    painter->save();
//    QPointF centerPos(0, 0);
//    QRectF textRect =  QRectF(centerPos.x(), centerPos.y(), \
//                                                           m_originSize.width(), m_originSize.height());
    painter->translate(m_originPos.x(), m_originPos.y());
    //scale
    painter->scale(m_scaleX, m_scaleY);
    painter->translate(-m_originPos.x(), -m_originPos.y());

//    if (falg)
//    painter->setTransform(m_transform);
    // 绘制
    painter->setFont(m_font);
//    painter->drawText(m_localRect, 0, m_text);
    painter->drawStaticText(m_localRect.topLeft(), QStaticText(m_text));

//    painter->drawText(QPointF(m_localRect.bottomLeft().x(), m_localRect.bottomLeft().y() - m_descent), m_text);

    painter->setPen(Qt::blue);
    painter->drawLine(QLine(QPoint(m_originPos.x()-6, m_originPos.y()),QPoint(m_originPos.x()+6, m_originPos.y())));
    painter->drawLine(QLine(QPoint(m_originPos.x(), m_originPos.y()-6),QPoint(m_originPos.x(), m_originPos.y()+6)));
    painter->restore();
}

void GraphicsTextItem::updateLocalRect()
{
    QFontMetricsF fm(m_font);
    QRectF rect = fm.boundingRect(m_text);
    m_descent = fm.descent();

    m_width = rect.width();
    m_height = rect.height();
    m_initialRect = m_localRect = QRectF(-m_width/2, -m_height/2, m_width, m_height);
    //    m_startSize = m_size = QSizeF(rect.width(), rect.height());
    //    m_originSize = m_startSize;

    this->prepareGeometryChange();
    this->update();
}
