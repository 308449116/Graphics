#include "graphicstextitem.h"
#include "attributemodel/textnode.h"
#include "utils/attribute_constants.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QStaticText>
#include <QApplication>
#include <QFontMetricsF>
#include <QXmlStreamWriter>
#include <QDebug>

using namespace Utils::Constants;

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
}

//GraphicsTextItem::GraphicsTextItem(const QString &text, const QFont &font, qreal scaleX,
//                                   QGraphicsItem *parentItem, QObject *parent)
//    : GraphicsItem(parent), m_text(text), m_font(font)
//{
//    m_AtrributeNode = new TextNode(this);
//    m_subItem = m_textItem = new GraphicsSimpleTextItem(text, parentItem);
//    m_initialFontSize = m_lastFontSize = m_font.pixelSize();
//    m_scaleX = scaleX;
//    setFont(m_font);
//    m_textItem->setScale(m_scaleX, m_scaleY);

//    getTextSize();
//    m_initialRect = m_localRect = QRectF(0, 0, m_fontWidth * m_scaleX, m_fontHeight * m_scaleY);
//    m_textItem->setItemBoundingRect(m_localRect);
//    m_textItem->setTransformOriginPoint(m_localRect.center());
//}

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

    m_localRect = trans.mapRect(m_initialRect);
    m_textItem->setItemBoundingRect(m_localRect);

//    qDebug () << "m_initialRect:" << m_initialRect;
//    qDebug () << "m_localRect:" << m_localRect;

    if (sx != 1 && sy == 1) {
        m_scaleX = m_localRect.width() / m_fontWidth;
//        qDebug () << "m_fontWidth:" << m_fontWidth;
//        qDebug () << "getTextSize:" << getTextSize().width();
//        qDebug () << "m_initialFontSize:" << m_initialFontSize;
    } else {
//        QFont font = m_font;
        m_lastFontSize = qRound(m_initialFontSize * sy);
        m_font.setPixelSize(m_lastFontSize);
        m_scaleX = m_localRect.width() / getTextSize().width();
        m_textItem->setFont(m_font);

        m_AtrributeNode->getAttribute(QString::fromUtf8(FONTSIZE))->setValue(m_font.pixelSize());
//        if (m_AtrributeNode->getAttribute(FONTSIZE)->getValue().toInt() != m_font.pixelSize()) {
//            m_AtrributeNode->getAttribute(FONTSIZE)->setValue(m_font.pixelSize());
//        }
    }

    m_textItem->setScale(m_scaleX, m_scaleY);
    m_textItem->update();
//    qDebug () << "pos:" << m_textItem->pos();
//    qDebug () << "boundingRect:" << m_textItem->boundingRect();
//    qDebug () << "scenePos:" << m_textItem->scenePos();
//    qDebug () << "sceneBoundingRect:" << m_textItem->sceneBoundingRect();

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
    updateBaseAttribute();
//    qDebug() << "============= m_textItem->pos:" << m_textItem->pos();
//    qDebug() << "diff:" << diff;
}

bool GraphicsTextItem::loadFromXml(QXmlStreamReader *xml)
{
    if (xml == nullptr) {
        return false;
    }

    readBaseAttributes(xml);
    m_AtrributeNode->loadFromXml(xml);
    return true;
}

bool GraphicsTextItem::saveToXml(QXmlStreamWriter *xml)
{
    if (xml == nullptr) {
        return false;
    }

    xml->writeStartElement(TEXT);
    writeBaseAttributes(xml);
    m_AtrributeNode->saveToXml(xml);
    xml->writeEndElement();
    return true;
}

GraphicsItem *GraphicsTextItem::duplicate() const
{
    GraphicsTextItem *item = new GraphicsTextItem();
    item->setFont(m_font);
    item->setText(m_text);
    item->setScale(m_scaleX, m_scaleY);
//    GraphicsSimpleTextItem *textItem = qgraphicsitem_cast<GraphicsSimpleTextItem *>(item->subItem());
//    qDebug () << "duplicate m_scaleX:" << m_scaleX;
//    qDebug () << "duplicate width:" << width();
//    qDebug () << "duplicate height:" << height();

    if (m_localRect.topLeft().x() < 0 || m_localRect.topLeft().y() < 0) {
        item->setPos(m_textItem->pos().x() + width() + m_localRect.topLeft().x(),
                                m_textItem->pos().y() + m_localRect.topLeft().y());
    } else {
        item->setPos(m_textItem->pos().x() + width(), m_textItem->pos().y());
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
    if (text.isNull() || text.isEmpty()) {
        return;
    }

    m_text = text;
    m_textItem->setText(m_text);
    updateLocalRect();

    m_AtrributeNode->getAttribute(QString::fromUtf8(TEXTCONTENT))->setValue(m_text);
//    if (m_AtrributeNode->getAttribute(TEXTCONTENT)->getValue().toString() != m_text) {
//        m_AtrributeNode->getAttribute(TEXTCONTENT)->setValue(m_text);
//    }
}

QString GraphicsTextItem::text() const
{
    return m_text;
}

void GraphicsTextItem::setFont(const QFont &font)
{
    m_font = font;
    m_textItem->setFont(m_font);
    updateLocalRect();

    m_AtrributeNode->getAttribute(QString::fromUtf8(FONTSIZE))->setValue(font.pixelSize());
//    if (m_AtrributeNode->getAttribute(FONTSIZE)->getValue().toInt() != font.pixelSize()) {
//        m_AtrributeNode->getAttribute(FONTSIZE)->setValue(font.pixelSize());
//    }
}

QFont GraphicsTextItem::font() const
{
    return m_font;
}

void GraphicsTextItem::onTextValueChanged(const QVariant &text)
{
    QString textItem = text.toString();
    if (textItem == m_text) {
        return;
    }

    setText(textItem);
    emit sendUpdateHandle();
}

void GraphicsTextItem::onFontSizeValueChanged(const QVariant &fontSize)
{
    int pixelSize = fontSize.toInt();
    if (pixelSize == m_font.pixelSize()) {
        return;
    }

    m_font.setPixelSize(pixelSize);
    setFont(m_font);
    emit sendUpdateHandle();
}

void GraphicsTextItem::updateLocalRect()
{
    QSizeF size = getTextSize();
    //参考点,对参考点进行拉伸后，需要获取新的参考点位置
    //左 QPointF(0, 40) 右 QPointF(120, 40) 上 QPointF(60, 0) 下 QPointF(60, 80)
    //左上 QPointF(0, 0) 左下 QPointF(0, 80) 右上 QPointF(120, 0) 右下 QPointF(120, 80)
    //中心 QPointF(60, 40)
//    m_referencePoint = m_localRect.bottomRight();
//    m_referencePoint = QPointF(m_localRect.topRight().x(), m_localRect.topRight().y() + m_localRect.height() / 2);
//    qDebug () << " =========== m_referencePoint:" << m_referencePoint;

    stretch(size.width() / m_localRect.width(), size.height() / m_localRect.height(), m_localRect.topLeft());
    updateCoordinate();
}

QSizeF GraphicsTextItem::getTextSize()
{
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
    return QSizeF(m_fontWidth, m_fontHeight);
}

int GraphicsTextItem::type() const
{
    return GraphicsItemType::TextItem;
}

void GraphicsTextItem::init()
{
    m_AtrributeNode = new TextNode(this);
    m_text = "jpkg";
    m_initialFontSize = m_lastFontSize = 60;
    m_font = qApp->font();
    m_font.setPixelSize(m_initialFontSize);
    QSizeF size = getTextSize();
    m_initialRect = m_localRect = QRectF(0, 0, size.width() * m_scaleX, size.height() * m_scaleY);

    setFont(m_font);
    setText(m_text);
    //        m_textItem->setItemBoundingRect(m_localRect);
    //        m_textItem->setTransformOriginPoint(m_localRect.center());
}
