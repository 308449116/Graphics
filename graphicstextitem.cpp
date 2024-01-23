#include "graphicstextitem.h"
//#include "common.h"

//#include <QPainter>
//#include <QStyleOptionGraphicsItem>
//#include <QStaticText>
#include <QApplication>
#include <QFontMetricsF>
#include <QDebug>

GraphicsTextItem::GraphicsTextItem(QObject *parent)
    : GraphicsItem(parent)
{
    m_item = m_textItem = new QGraphicsSimpleTextItem();
    m_initialFontSize = m_lastFontSize = 100;
    m_font = qApp->font();
    m_font.setPixelSize(m_initialFontSize);
    m_text = "jpkg";
    updateLocalRect();
}

GraphicsTextItem::GraphicsTextItem(const QString &text, QObject *parent)
    : GraphicsItem(parent)
{
    m_item = m_textItem = new QGraphicsSimpleTextItem(text);
    m_initialFontSize = m_lastFontSize = 100;
    m_font = qApp->font();
    m_font.setPixelSize(m_initialFontSize);
    m_text = "jpkg";
    setFont(m_font);
    setRotation(30);

    QTransform transform;
    qDebug() << "m_translationPos========:" << m_translationPos;
    qDebug() << "boundingRect()========:" << boundingRect();
    transform.translate(boundingRect().center().x(), boundingRect().center().y());
    transform.rotate(30);
    transform.scale(2, 1);
      //  transform.translate(-boundingRect().center().x()*0.5, -boundingRect().center().y()*0.5);
    this->item()->setTransform(transform);

//    this->item()->setTransformOriginPoint(boundingRect().center()*2);
//    this->item()->setRotation(30);
//    this->item()->setScale(2);

}

void GraphicsTextItem::stretch(qreal sx, qreal sy, const QPointF &origin)
{
    if (qRound(m_initialFontSize * sy) < 10) {
        return;
    }

    //    const QPointF &origin = this->oppositePos();

    QTransform trans;
    trans.translate(origin.x(),origin.y());
    trans.rotate(this->rotation());
    trans.scale(sx,sy);
    trans.translate(-origin.x(),-origin.y());
    qDebug () << "sx:" << sx << "sy:" << sy;
    //    qDebug () << "============= transformOriginPoint:" << this->transformOriginPoint();
//    m_translationPos = origin;

    //    prepareGeometryChange();
    m_localRect = trans.mapRect(m_initialRect);
    qDebug () << "m_initialRect:" << m_initialRect;
    qDebug () << "m_localRect:" << m_localRect;

    m_width = m_localRect.width();
    m_height = m_localRect.height();
    if (sx != 1 && sy == 1) {
        m_scaleX = m_width / getSizeByFontSize(m_initialFontSize).width();
        qDebug () << "m_width:" << m_width;
        qDebug () << "getSizeByFontSize:" << getSizeByFontSize(m_initialFontSize).width();
        qDebug () << "m_initialFontSize:" << m_initialFontSize;

        m_translationPos = origin;
        QTransform transform;
        transform.translate(origin.x(), origin.y());
//        qDebug () << "origin.x():" << transform.map(m_translationPos);
        transform.rotate(m_angle);
        transform.scale(m_scaleX, m_scaleY);
        transform.translate(-origin.x(), -origin.y());
//        qDebug () << "-origin.x():" << transform.map(m_translationPos);
        m_item->setTransform(transform);
        m_fontChange = false;
    } else {
        m_fontChange = true;
        m_lastFontSize = qRound(m_initialFontSize * sy);
        m_font.setPixelSize(m_lastFontSize);
        m_scaleX = m_width / getSizeByFontSize(m_lastFontSize).width();
        m_textItem->setFont(m_font);
        qDebug () << "m_width:" << m_width;
        qDebug () << "getSizeByFontSize:" << getSizeByFontSize(m_lastFontSize).width();
        qDebug () << "m_initialFontSize:" << m_initialFontSize;
        QTransform transform;
        //        transform.translate(origin.x(), origin.y());
        qDebug () << "origin.x():" << transform.map(origin);

        transform.rotate(m_angle);
        transform.scale(m_scaleX, m_scaleY);
        //        transform.translate(-origin.x(), -origin.y());
        qDebug () << "-origin.x():" << transform.map(origin);

        m_item->setTransform(transform);
    }

    qDebug () << "m_scaleX:" << m_scaleX;
    qDebug () << "m_scaleY:" << m_scaleY;
    qDebug () << "m_angle:" << m_angle;
    qDebug () << "transformOriginPoint:" << m_item->transformOriginPoint();
    //    this->setScaleX(m_scaleX);
}

void GraphicsTextItem::updateCoordinate()
{
    if (!m_textItem->parentItem()) {
        auto angle = qDegreesToRadians(m_textItem->rotation());
//        auto p1 = m_textItem->mapToScene(transform.map(m_textItem->boundingRect().center()));
//        auto origin = m_textItem->mapToScene(m_translationPos);
//        auto p1 = m_textItem->sceneBoundingRect().center();
        qDebug () << "1111 m_translationPos:" << m_translationPos;
        qDebug () << "1111 m_scaleY:" << m_scaleY;

        QTransform transform;
//        transform.translate(m_translationPos.x(), m_translationPos.y());
        transform.rotate(m_angle);
        transform.scale(m_scaleX, m_scaleY);

        auto p1 = m_textItem->boundingRect().center();
        auto origin = m_translationPos;
        QPointF p2 = QPointF(0, 0);
        qDebug () << "p1:"<< p1;
        qDebug () << "origin:" << origin;

        p2.setX(origin.x() + qCos(angle)*(p1.x() - origin.x()) - qSin(angle)*(p1.y() - origin.y()));
        p2.setY(origin.y() + qSin(angle)*(p1.x() - origin.x()) + qCos(angle)*(p1.y() - origin.y()));
        qDebug () << "p2:" << p2;

        auto diff = p1 - p2;
        qDebug () << "diff:" << diff;
        m_textItem->moveBy(-diff.x(), -diff.y());
//        m_textItem->setTransformOriginPoint(m_textItem->boundingRect().center());
        m_translationPos = p1;
        qDebug () << "m_translationPos:" << m_translationPos;
        qDebug () << "boundingRect center:" << m_textItem->boundingRect().center();
        qDebug () << "sceneBoundingRect center:" <<m_textItem->sceneBoundingRect().center();
//        m_translationPos = m_textItem->mapToScene(p1);
//        qDebug () << "updateCoordinate sceneBoundingRect:" << m_textItem->sceneBoundingRect();
//        qDebug () << "updateCoordinate m_translationPos:" << m_textItem->sceneBoundingRect();
    } else {
        //        m_textItem->setTransformOriginPoint(m_textItem->boundingRect().center());
    }

    m_initialRect = m_localRect;
    m_initialFontSize = m_lastFontSize;
}
//void GraphicsTextItem::updateCoordinate()
//{
//    if (!m_textItem->parentItem()) {
//        auto angle = qDegreesToRadians(m_textItem->rotation());

//        auto p1 = m_textItem->mapToScene(m_textItem->boundingRect().center());
//        auto origin = m_textItem->mapToScene(m_translationPos);
//        QPointF p2 = QPointF(0, 0);
//        qDebug () << "p1:" << p1;
//        qDebug () << "origin:" << origin;

//        p2.setX(origin.x() + qCos(angle)*(p1.x() - origin.x()) - qSin(angle)*(p1.y() - origin.y()));
//        p2.setY(origin.y() + qSin(angle)*(p1.x() - origin.x()) + qCos(angle)*(p1.y() - origin.y()));
//        qDebug () << "p2:" << p2;

//        auto diff = p1 - p2;
//        qDebug () << "diff:" << diff;
//        m_textItem->moveBy(-diff.x(), -diff.y());
//        //                m_textItem->setTransformOriginPoint(m_textItem->boundingRect().center());
//        m_translationPos = m_textItem->boundingRect().center();
//        qDebug () << "updateCoordinate m_translationPos:" << m_translationPos;
//    } else {
//        //        m_textItem->setTransformOriginPoint(m_textItem->boundingRect().center());
//    }

//    m_initialRect = m_localRect;
//    m_initialFontSize = m_lastFontSize;
//}

QSharedPointer<GraphicsItem> GraphicsTextItem::duplicate() const
{
    GraphicsTextItem *item = new GraphicsTextItem(m_text);
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

//void GraphicsTextItem::customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
//{
////    qDebug () << "============= m_localRect:" << m_localRect;
//    Q_UNUSED(widget)
//    Q_UNUSED(option)
////    painter->save();
////    QPointF centerPos(0, 0);
////    QRectF textRect =  QRectF(centerPos.x(), centerPos.y(), \
////                                                           m_originSize.width(), m_originSize.height());
//    painter->translate(m_localRect.topLeft().x(), m_localRect.topLeft().y());
//    //scale
//    painter->scale(m_scaleX, 1);
//    painter->translate(-m_localRect.topLeft().x(), -m_localRect.topLeft().y());

//    // 绘制
//    painter->setFont(m_font);
////    painter->drawText(m_localRect, 0, m_text);
//    painter->drawStaticText(m_localRect.topLeft(), QStaticText(m_text));

////    painter->drawText(QPointF(m_localRect.bottomLeft().x(), m_localRect.bottomLeft().y() - m_descent), m_text);

////    painter->setPen(Qt::blue);
////    painter->drawLine(QLine(QPoint(m_translationPos.x()-6, m_translationPos.y()),QPoint(m_translationPos.x()+6, m_translationPos.y())));
////    painter->drawLine(QLine(QPoint(m_translationPos.x(), m_translationPos.y()-6),QPoint(m_translationPos.x(), m_translationPos.y()+6)));
////    painter->restore();
//}

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

    m_initialRect = m_localRect = m_textItem->boundingRect();
    m_translationPos = m_textItem->boundingRect().center();
    //    m_textItem->setTransformOriginPoint(m_textItem->boundingRect().center());
    //    m_initialRect = m_localRect = QRectF(-m_width/2, -m_height/2, m_width, m_height);
    //    m_startSize = m_size = QSizeF(rect.width(), rect.height());
    //    m_originSize = m_startSize;
    //    this->prepareGeometryChange();
    //    this->update();
}

QSizeF GraphicsTextItem::getSizeByFontSize(int fontSize)
{
    QFont font;
    font.setPixelSize(fontSize);
    QFontMetricsF fm(font);
    QRectF rect = fm.boundingRect(m_text);
    return QSizeF(rect.width(), rect.height());
}

//qreal GraphicsTextItem::scaleX() const
//{
//    return m_scaleX;
//}

//void GraphicsTextItem::setScaleX(qreal newScaleX)
//{
//    m_scaleX = newScaleX;
//}

int GraphicsTextItem::type() const
{
    return GraphicsItemType::TextItem;
}
