#include "graphicstextitem.h"
#include "common.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QStaticText>
#include <QApplication>
#include <QFontMetricsF>
#include <QDebug>

class GraphicsTextItem::GraphicsSimpleTextItem : public QGraphicsSimpleTextItem
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

GraphicsTextItem::GraphicsSimpleTextItem::GraphicsSimpleTextItem(QGraphicsItem *parent) :
    QGraphicsSimpleTextItem{parent}
{

}

GraphicsTextItem::GraphicsSimpleTextItem::GraphicsSimpleTextItem(const QString &text, QGraphicsItem *parent) :
    QGraphicsSimpleTextItem{text, parent}
{

}

void GraphicsTextItem::GraphicsSimpleTextItem::paint(
    QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //    qDebug () << "============= m_itemBoundingRect:" << m_itemBoundingRect;
    Q_UNUSED(widget)
    Q_UNUSED(option)
    //    painter->save();
    //    QPointF centerPos(0, 0);
    //    QRectF textRect =  QRectF(centerPos.x(), centerPos.y(), m_originSize.width(), m_originSize.height());
    qreal x = m_itemBoundingRect.topLeft().x();
    qreal y = m_itemBoundingRect.topLeft().y();
//    qreal x = round(m_itemBoundingRect.topLeft().x() / GRID_SIZE) * GRID_SIZE;
//    qreal y = round(m_itemBoundingRect.topLeft().y() / GRID_SIZE) * GRID_SIZE;
//    qDebug() << "x:" << x << " y:" << y;
    painter->translate(x, y);
    painter->scale(m_scaleX, m_scaleY);
    painter->translate(-x, -y);

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

//===============================GraphicsTextItem==============================================
GraphicsTextItem::GraphicsTextItem(QGraphicsItem *parentItem, QObject *parent)
    : GraphicsItem(parent)
{
    m_subItem = m_textItem = new GraphicsSimpleTextItem(parentItem);
    m_initialFontSize = m_lastFontSize = 60;
    m_font = qApp->font();
    m_font.setPixelSize(m_initialFontSize);
    m_text = "jpkg";
    m_textItem->setFont(m_font);
    m_textItem->setText(m_text);

    getSizeByFontSize(m_font.pixelSize());
    m_initialRect = m_localRect = QRectF(0, 0, m_fontWidth * m_scaleX, m_fontHeight * m_scaleY);
    m_textItem->setItemBoundingRect(m_localRect);
    m_textItem->setTransformOriginPoint(m_localRect.center());
}

GraphicsTextItem::GraphicsTextItem(const QString &text, const QFont &font, qreal scaleX,
                                   QGraphicsItem *parentItem, QObject *parent)
    : GraphicsItem(parent), m_text(text), m_font(font)
{
    m_subItem = m_textItem = new GraphicsSimpleTextItem(text, parentItem);
    m_initialFontSize = m_lastFontSize = m_font.pixelSize();
    m_scaleX = scaleX;
    m_textItem->setFont(m_font);
    m_textItem->setScale(m_scaleX, m_scaleY);

    getSizeByFontSize(m_font.pixelSize());
    m_initialRect = m_localRect = QRectF(0, 0, m_fontWidth * m_scaleX, m_fontHeight * m_scaleY);
    m_textItem->setItemBoundingRect(m_localRect);
    m_textItem->setTransformOriginPoint(m_localRect.center());
}

void GraphicsTextItem::stretch(qreal sx, qreal sy, const QPointF &origin)
{
    if (qRound(m_initialFontSize * sy) < 10) {
        return;
    }

    QTransform trans;
    trans.translate(origin.x(), origin.y());
    trans.scale(sx, sy);
    trans.translate(-origin.x(), -origin.y());
//    qDebug () << "sx:" << sx << "sy:" << sy;
//    qDebug () << "pos:" << m_textItem->pos();
//    qDebug () << "origin:" << origin;
    m_oppositePos = origin;

    //    prepareGeometryChange();
    m_localRect = trans.mapRect(m_initialRect);
    m_textItem->setItemBoundingRect(m_localRect);

//    qDebug () << "m_initialRect:" << m_initialRect;
//    qDebug () << "m_localRect:" << m_localRect;

    if (sx != 1 && sy == 1) {
        m_scaleX = m_localRect.width() / m_fontWidth;
//        qDebug () << "m_fontWidth:" << m_fontWidth;
//        qDebug () << "getSizeByFontSize:" << getSizeByFontSize(m_initialFontSize).width();
//        qDebug () << "m_initialFontSize:" << m_initialFontSize;
    } else {
        m_lastFontSize = qRound(m_initialFontSize * sy);
        m_font.setPixelSize(m_lastFontSize);
        m_scaleX = m_localRect.width() / getSizeByFontSize(m_lastFontSize).width();
        m_textItem->setFont(m_font);
    }

    m_textItem->setScale(m_scaleX, m_scaleY);
    m_textItem->update();
//    qDebug () << "m_scaleX:" << m_scaleX << " m_scaleY:" << m_scaleY;
}

void GraphicsTextItem::updateCoordinate()
{
    auto angle = qDegreesToRadians(m_textItem->rotation());

    auto p1 = m_localRect.center();
    auto p2 = QPointF(0, 0);
    auto origin = m_textItem->transformOriginPoint();

    p2.setX(origin.x() + qCos(angle) * (p1.x() - origin.x()) - qSin(angle) * (p1.y() - origin.y()));
    p2.setY(origin.y() + qSin(angle) * (p1.x() - origin.x()) + qCos(angle) * (p1.y() - origin.y()));

    auto diff = p1 - p2;
    m_textItem->moveBy(-diff.x(), -diff.y());
    m_textItem->setTransformOriginPoint(p1);

    m_initialRect = m_localRect;
    m_initialFontSize = m_lastFontSize;
}

GraphicsItem *GraphicsTextItem::duplicate() const
{
    GraphicsTextItem *item = new GraphicsTextItem(m_text, m_font, m_scaleX);
//    GraphicsSimpleTextItem *textItem = qgraphicsitem_cast<GraphicsSimpleTextItem *>(item->subItem());
//    qDebug () << "duplicate m_scaleX:" << m_scaleX;
//    qDebug () << "duplicate width:" << width();
//    qDebug () << "duplicate height:" << height();

    if (m_localRect.topLeft().x() < 0 || m_localRect.topLeft().y() < 0) {
        item->subItem()->setPos(m_textItem->pos().x() + width() + m_localRect.topLeft().x(),
                                m_textItem->pos().y() + m_localRect.topLeft().y());
    } else {
        item->subItem()->setPos(m_textItem->pos().x() + width(), m_textItem->pos().y());
    }
    item->subItem()->setTransform(m_textItem->transform());
    item->setItemName(this->itemName().append("_copy"));
    item->setRotation(rotation());
    item->setGroupAngle(groupAngle());
    item->updateCoordinate();
    return item;
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
//    m_initialFontSize = m_lastFontSize = m_font.pixelSize();
    m_textItem->setFont(m_font);
    updateLocalRect();
}

QFont GraphicsTextItem::font() const
{
    return m_font;
}

void GraphicsTextItem::updateLocalRect()
{
    getSizeByFontSize(m_font.pixelSize());

    //参考点,对参考点进行拉伸后，需要获取新的参考点位置
    //左 QPointF(0, 40) 右 QPointF(120, 40) 上 QPointF(60, 0) 下 QPointF(60, 80)
    //左上 QPointF(0, 0) 左下 QPointF(0, 80) 右上 QPointF(120, 0) 右下 QPointF(120, 80)
    //中心 QPointF(60, 40)
//    m_referencePoint = m_localRect.bottomRight();
    m_referencePoint = QPointF(m_localRect.topRight().x(), m_localRect.topRight().y() + m_localRect.height() / 2);
    qDebug () << " =========== m_referencePoint:" << m_referencePoint;

    stretch(m_fontWidth / m_localRect.width(), m_fontHeight / m_localRect.height(), m_referencePoint);
    updateCoordinate();
}

QSizeF GraphicsTextItem::getSizeByFontSize(int fontSize)
{
    m_font.setPixelSize(fontSize);
//    QTextOption textOption;
//    textOption.setFlags(QTextOption::IncludeTrailingSpaces);
    QFontMetricsF fm(m_font);
//    QRectF rect = fm.boundingRect(m_text);
//    qreal leftBearing = fm.leftBearing(m_text.front());
//    qreal rightBearing = fm.rightBearing(m_text.back());
//    qDebug() << "leftBearing:" << leftBearing << " rightBearing:" << rightBearing;
//    qDebug() << "front:" << m_text.front() << " back:" << m_text.back();
//    m_fontWidth = rect.width();
//    m_fontHeight = rect.height();
//    qDebug() << "boundingRect:" << fm.boundingRect(m_text) << " tightBoundingRect:" << fm.tightBoundingRect(m_text);
//    qDebug() << "size:" << fm.size(Qt::TextSingleLine, m_text);
    QSizeF size = fm.size(Qt::TextSingleLine, m_text);
//    m_fontWidth = size.width();
//    m_fontHeight = size.height();

    m_fontWidth = round(size.width() / GRID_SIZE) * GRID_SIZE;
    m_fontHeight = round(size.height() / GRID_SIZE) * GRID_SIZE;
    return size;
}

int GraphicsTextItem::type() const
{
    return GraphicsItemType::TextItem;
}
