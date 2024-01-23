#include "graphicstextitem.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QStaticText>
#include <QApplication>
#include <QFontMetricsF>
#include <QDebug>

GraphicsTextItem::GraphicsSimpleTextItem::GraphicsSimpleTextItem(QGraphicsItem *parent) :
    QGraphicsSimpleTextItem{parent}
{

}

GraphicsTextItem::GraphicsSimpleTextItem::GraphicsSimpleTextItem(const QString &text, QGraphicsItem *parent) :
    QGraphicsSimpleTextItem{text, parent}
{

}

void GraphicsTextItem::GraphicsSimpleTextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //    qDebug () << "============= m_itemBoundingRect:" << m_itemBoundingRect;
        Q_UNUSED(widget)
        Q_UNUSED(option)
    //    painter->save();
    //    QPointF centerPos(0, 0);
    //    QRectF textRect =  QRectF(centerPos.x(), centerPos.y(), \
    //                             m_originSize.width(), m_originSize.height());
        painter->translate(m_itemBoundingRect.topLeft().x(), m_itemBoundingRect.topLeft().y());
        painter->scale(m_scaleX, 1);
        painter->translate(-m_itemBoundingRect.topLeft().x(), -m_itemBoundingRect.topLeft().y());

        // 绘制
        painter->setFont(this->font());
    //    painter->drawText(m_itemBoundingRect, 0, m_text);
        painter->drawStaticText(m_itemBoundingRect.topLeft(), QStaticText(this->text()));

    //    painter->drawText(QPointF(m_itemBoundingRect.bottomLeft().x(), m_itemBoundingRect.bottomLeft().y() - m_descent), m_text);
    //    painter->setPen(Qt::blue);
    //    painter->drawLine(QLine(QPoint(m_originPos.x()-6, m_originPos.y()),QPoint(m_originPos.x()+6, m_originPos.y())));
    //    painter->drawLine(QLine(QPoint(m_originPos.x(), m_originPos.y()-6),QPoint(m_originPos.x(), m_originPos.y()+6)));
        //    painter->restore();
}

void GraphicsTextItem::GraphicsSimpleTextItem::setScale(qreal scaleX, qreal scaleY)
{
    m_scaleX = scaleX;
    m_scaleY = scaleY;
}

qreal GraphicsTextItem::GraphicsSimpleTextItem::scaleY() const
{
    return m_scaleX;
}

qreal GraphicsTextItem::GraphicsSimpleTextItem::scaleX() const
{
    return m_scaleY;
}

void GraphicsTextItem::GraphicsSimpleTextItem::setItemBoundingRect(const QRectF &newItemBoundingRect)
{
    m_itemBoundingRect = newItemBoundingRect;
}

QRectF GraphicsTextItem::GraphicsSimpleTextItem::boundingRect() const
{
    return m_itemBoundingRect;
}





GraphicsTextItem::GraphicsTextItem(QObject *parent)
    : GraphicsItem(parent)
{
    m_item = m_textItem = new GraphicsSimpleTextItem();
    m_initialFontSize = m_lastFontSize = 100;
    m_font = qApp->font();
    m_font.setPixelSize(m_initialFontSize);
    m_text = "jpkg";

    m_textItem->setFont(m_font);
    m_textItem->setText(m_text);
    updateLocalRect();
}

GraphicsTextItem::GraphicsTextItem(const QString &text, const QFont &font, QObject *parent)
    : GraphicsItem(parent), m_text(text), m_font(font)
{
    m_item = m_textItem = new GraphicsSimpleTextItem(text);
    m_textItem->setFont(m_font);
    updateLocalRect();
}

void GraphicsTextItem::stretch(qreal sx, qreal sy, const QPointF &origin)
{
    if (qRound(m_initialFontSize * sy) < 10) {
        return;
    }

    QTransform trans;
    trans.translate(origin.x(),origin.y());
    trans.scale(sx,sy);
    trans.translate(-origin.x(),-origin.y());
    qDebug () << "sx:" << sx << "sy:" << sy;
    //    qDebug () << "============= transformOriginPoint:" << this->transformOriginPoint();
    m_originPos = origin;

    //    prepareGeometryChange();
    m_localRect = trans.mapRect(m_initialRect);
    m_textItem->setItemBoundingRect(m_localRect);

    qDebug () << "m_initialRect:" << m_initialRect;
    qDebug () << "m_localRect:" << m_localRect;

    m_width = m_localRect.width();
    m_height = m_localRect.height();
    if (sx != 1 && sy == 1) {
        m_scaleX = m_width / getSizeByFontSize(m_initialFontSize).width();
        qDebug () << "m_width:" << m_width;
        qDebug () << "getSizeByFontSize:" << getSizeByFontSize(m_initialFontSize).width();
        qDebug () << "m_initialFontSize:" << m_initialFontSize;
    } else {
        m_lastFontSize = qRound(m_initialFontSize * sy);
        m_font.setPixelSize(m_lastFontSize);
        m_scaleX = m_width / getSizeByFontSize(m_lastFontSize).width();
        m_textItem->setFont(m_font);
    }

    m_textItem->setScale(m_scaleX, m_scaleY);
    m_textItem->update();
    qDebug () << "m_scaleX:" << m_scaleX;

}

void GraphicsTextItem::updateCoordinate()
{
    if (!m_textItem->parentItem()) {
        auto angle = qDegreesToRadians(m_textItem->rotation());

        auto p1 = m_localRect.center();
        auto origin = m_textItem->transformOriginPoint();
        QPointF p2 = QPointF(0, 0);

        p2.setX(origin.x() + qCos(angle)*(p1.x() - origin.x()) - qSin(angle)*(p1.y() - origin.y()));
        p2.setY(origin.y() + qSin(angle)*(p1.x() - origin.x()) + qCos(angle)*(p1.y() - origin.y()));

        auto diff = p1 - p2;
        m_textItem->moveBy(-diff.x(), -diff.y());
        m_textItem->setTransformOriginPoint(m_localRect.center());
    } else {
        m_textItem->setTransformOriginPoint(m_localRect.center());
    }

    m_initialRect = m_localRect;
    m_initialFontSize = m_lastFontSize;
}

QSharedPointer<GraphicsItem> GraphicsTextItem::duplicate() const
{
    GraphicsTextItem *item = new GraphicsTextItem(m_text, m_font);
    //    item->setFont(m_font);
    //    item->m_width = width();
    //    item->m_height = height();
    //    item->setScaleX(m_scaleX);
    //    item->setPos(pos().x() + width(), pos().y());
    //    item->setTransform(transform());
    //    item->setTransformOriginPoint(transformOriginPoint());
    //    item->setRotation(rotation());
    //    item->setScale(scale());
    //    item->setZValue(zValue()+0.1);
    //    item->setItemName(this->getItemName().append("_copy"));
    //    item->setGroupAngle(groupAngle());
    //    item->updateCoordinate();
    return QSharedPointer<GraphicsItem>(item);
}

void GraphicsTextItem::setText(const QString &text)
{
    m_text = text;
    m_textItem->setText(m_text);
    updateLocalRect();
}

QString GraphicsTextItem::text() const
{
    return m_text;
}

void GraphicsTextItem::setFont(const QFont &font)
{
    m_font = font;
    m_initialFontSize = m_lastFontSize = m_font.pixelSize();
    m_textItem->setFont(m_font);
    updateLocalRect();
}

QFont GraphicsTextItem::font() const
{
    return m_font;
}

void GraphicsTextItem::updateLocalRect()
{
    QFontMetricsF fm(m_font);
    QRectF rect = fm.boundingRect(m_text);
    m_descent = fm.descent();
    qDebug () << " ===========:" << m_font;
    qDebug () << " ===========:" << m_text;
    qDebug () << " ===========:" << rect;

    m_width = rect.width();
    m_height = rect.height();
    qDebug () << " pixelSize:" << m_font.pixelSize()
             << " width:" << m_width
             << " width:" << m_height;

    m_initialRect = m_localRect = QRectF(0, 0, m_width * m_scaleX, m_height * m_scaleY);
    m_textItem->setItemBoundingRect(m_localRect);
    m_textItem->setTransformOriginPoint(m_localRect.center());
}

QSizeF GraphicsTextItem::getSizeByFontSize(int fontSize)
{
    QFont font;
    font.setPixelSize(fontSize);
    QFontMetricsF fm(font);
    QRectF rect = fm.boundingRect(m_text);
    return QSizeF(rect.width(), rect.height());
}

int GraphicsTextItem::type() const
{
    return GraphicsItemType::TextItem;
}

