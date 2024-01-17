#include "graphicstextitem.h"
#include "common.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QApplication>
#include <QStaticText>
#include <QDebug>

GraphicsTextItem::GraphicsTextItem(const QString &text, QGraphicsItem *parent)
    : GraphicsItem(parent)
{
    m_initialFontSize = m_lastFontSize = 100;
    m_font = qApp->font();
    m_font.setPixelSize(m_initialFontSize);
    setText(text);
}

void GraphicsTextItem::stretch(qreal sx, qreal sy)
{
    if (qRound(m_initialFontSize * sy) < 10) {
        return;
    }

    const QPointF &origin = this->oppositePos();

    QTransform trans;
    trans.translate(origin.x(),origin.y());
    trans.scale(sx,sy);
    trans.translate(-origin.x(),-origin.y());
//    qDebug () << "sx:" << sx << "sy:" << sy;
//    qDebug () << "============= transformOriginPoint:" << this->transformOriginPoint();
    m_originPos = origin;

    prepareGeometryChange();
    m_localRect = trans.mapRect(m_initialRect);
    m_width = m_localRect.width();
    m_height = m_localRect.height();
    if (sx != 1 && sy == 1) {
        m_scaleX = m_width / getSizeByFontSize(m_initialFontSize).width();
    } else {
        m_lastFontSize = qRound(m_initialFontSize * sy);
        m_font.setPixelSize(m_lastFontSize);
        m_scaleX = m_width / getSizeByFontSize(m_lastFontSize).width();
    }
}

void GraphicsTextItem::updateCoordinate(bool isGroup)
{
    if (!parentItem()) {
        QPointF pt1, pt2, delta;
        pt1 = mapToScene(transformOriginPoint());
        pt2 = mapToScene(m_localRect.center());
        delta = pt1 - pt2;

        prepareGeometryChange();
        m_localRect = QRectF(-m_width / 2, -m_height / 2, m_width, m_height);
        m_width = m_localRect.width();
        m_height = m_localRect.height();
        setTransform(transform().translate(delta.x(), delta.y()));
        setTransformOriginPoint(m_localRect.center());
        moveBy(-delta.x(), -delta.y());
        setTransform(transform().translate(-delta.x(), -delta.y()));
        m_originPos = QPoint(0, 0);

        m_initialFontSize = m_font.pixelSize();
    } else {
        setTransformOriginPoint(m_localRect.center());
    }

    m_initialRect = m_localRect;
    m_ratio = m_width / m_height;
}

void GraphicsTextItem::move(const QPointF &point)
{
    moveBy(point.x(),point.y());
}

QSharedPointer<GraphicsAbstractItem> GraphicsTextItem::duplicate() const
{
    GraphicsTextItem *item = new GraphicsTextItem(m_text);
    item->setFont(m_font);
    item->m_width = width();
    item->m_height = height();
    item->setScaleX(m_scaleX);
    item->setPos(pos().x() + width(), pos().y());
    item->setTransform(transform());
    item->setTransformOriginPoint(transformOriginPoint());
    item->setRotation(rotation());
    item->setScale(scale());
    item->setZValue(zValue()+0.1);
    item->setItemName(this->getItemName().append("_copy"));
    item->setGroupAngle(groupAngle());
    item->updateCoordinate();
    return QSharedPointer<GraphicsAbstractItem>(item);
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
    m_initialFontSize = m_lastFontSize = m_font.pixelSize();
    updateLocalRect();
}

QFont GraphicsTextItem::font() const
{
    return m_font;
}

void GraphicsTextItem::customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    qDebug () << "============= m_localRect:" << m_localRect;
    Q_UNUSED(widget)
    Q_UNUSED(option)
//    painter->save();
//    QPointF centerPos(0, 0);
//    QRectF textRect =  QRectF(centerPos.x(), centerPos.y(), \
//                                                           m_originSize.width(), m_originSize.height());
    painter->translate(m_localRect.topLeft().x(), m_localRect.topLeft().y());
    //scale
    painter->scale(m_scaleX, 1);
    painter->translate(-m_localRect.topLeft().x(), -m_localRect.topLeft().y());

    // 绘制
    painter->setFont(m_font);
//    painter->drawText(m_localRect, 0, m_text);
    painter->drawStaticText(m_localRect.topLeft(), QStaticText(m_text));

//    painter->drawText(QPointF(m_localRect.bottomLeft().x(), m_localRect.bottomLeft().y() - m_descent), m_text);

//    painter->setPen(Qt::blue);
//    painter->drawLine(QLine(QPoint(m_originPos.x()-6, m_originPos.y()),QPoint(m_originPos.x()+6, m_originPos.y())));
//    painter->drawLine(QLine(QPoint(m_originPos.x(), m_originPos.y()-6),QPoint(m_originPos.x(), m_originPos.y()+6)));
//    painter->restore();
}

void GraphicsTextItem::updateLocalRect()
{
    QFontMetricsF fm(m_font);
    QRectF rect = fm.boundingRect(m_text);
    m_descent = fm.descent();

    m_width = rect.width();
    m_height = rect.height();
    qDebug () << " pixelSize:" << m_font.pixelSize()
                << " width:" << m_width
                << " width:" << m_height;

    m_initialRect = m_localRect = QRectF(-m_width/2, -m_height/2, m_width, m_height);
    //    m_startSize = m_size = QSizeF(rect.width(), rect.height());
    //    m_originSize = m_startSize;
    this->prepareGeometryChange();
    this->update();
}

QSizeF GraphicsTextItem::getSizeByFontSize(int fontSize)
{
    QFont font;
    font.setPixelSize(fontSize);
    QFontMetricsF fm(font);
    QRectF rect = fm.boundingRect(m_text);
    return QSizeF(rect.width(), rect.height());
}

qreal GraphicsTextItem::scaleX() const
{
    return m_scaleX;
}

void GraphicsTextItem::setScaleX(qreal newScaleX)
{
    m_scaleX = newScaleX;
}

int GraphicsTextItem::type() const
{
    return GraphicsItemType::TextItem;
}
