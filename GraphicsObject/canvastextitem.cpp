#include "canvastextitem.h"
//#include "NDNodeBase.h"
//#include "NDBoolAttribute.h"
//#include "NDIntAttribute.h"
//#include "NDColorAttribute.h"
//#include "NDStringAttribute.h"
#include <QPainter>
#include <QApplication>
#include <QDebug>

CanvasTextItem::CanvasTextItem(QGraphicsItem* parentItem)
    :CanvasItemBase(parentItem)
{
    m_font = qApp->font();
    m_font.setPixelSize(100);
//    QFont font("Arial", 100);
//    this->setItemResizeable(false);
    //    initAttribute();

    setCurrentText("jpkg");
}

CanvasTextItem::~CanvasTextItem()
{

}

void CanvasTextItem::setCurrentText(const QString& text)
{
    m_Text = text;

    //    QObject::disconnect(m_pTextValueAttribute, &NDStringAttribute::valueChanged, this, &CanvasTextItem::onTextValueChanged);
    //    m_pTextValueAttribute->setValue(m_Text);
    //    QObject::connect(m_pTextValueAttribute, &NDStringAttribute::valueChanged, this, &CanvasTextItem::onTextValueChanged);

    QFontMetricsF fm(m_font);
    QRectF rect = fm.boundingRect(m_Text);
    m_descent = fm.descent();
//    qDebug() << "tightBoundingRect:" << fm.tightBoundingRect(m_Text);
//    qDebug() << "boundingRect:" << fm.boundingRect(m_Text);
//    qDebug() << "mapRectFromScene:" << mapRectFromScene(fm.tightBoundingRect(m_Text));
//    qDebug() << "descent:" << fm.descent();
//    qDebug() << "ascent:" << fm.ascent();
//    qDebug() << "height:" << fm.height();
//    qDebug() << "lineSpacing:" << fm.lineSpacing();
//    qDebug() << "underlinePos:" << fm.underlinePos();
//    qDebug() << "overlinePos:" << fm.overlinePos();
//    qDebug() << "strikeOutPos:" << fm.strikeOutPos();
//    qDebug() << "lineWidth:" << fm.lineWidth();
//    qDebug() << "leftBearing:" << fm.leftBearing(m_Text[0]);
//    qDebug() << "minLeftBearing:" << fm.minLeftBearing();

    m_startSize = m_size = QSizeF(rect.width(), rect.height());
    m_originSize = m_startSize;
    this->prepareGeometryChange();

    this->update();
}

QString CanvasTextItem::getCurrentText() const
{
    return m_Text;
}

void CanvasTextItem::setCurrentFont(const QFont& font)
{
    m_font = font;

    QFontMetricsF fm(m_font);
    QRectF rect = fm.boundingRect(m_Text);
    m_descent = fm.descent();

    m_startSize = m_size = QSizeF(rect.width(), rect.height());
    m_originSize = m_startSize;

    this->prepareGeometryChange();

    this->update();
}

QFont CanvasTextItem::getCurrentFont() const
{
    return m_font;
}

void CanvasTextItem::customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();
    QPointF centerPos(0, 0);
    QRectF textRect =  QRectF(centerPos.x(), centerPos.y(), \
                                                           m_originSize.width(), m_originSize.height());
    //scale
    painter->scale(m_scaleX, m_scaleY);

    // 绘制
    painter->setFont(m_font);
    painter->drawText(QPointF(textRect.bottomLeft().x(), textRect.bottomLeft().y() - m_descent), m_Text);
    painter->restore();
}
/*
void CanvasTextItem::customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();
    QPointF centerPos(0, 0);
//    QRectF textRect =  QRectF(centerPos.x() - m_originSize.width() / 2, centerPos.y() - m_originSize.height() / 2, \
//                            m_originSize.width(), m_originSize.height());
    QRectF textRect =  QRectF(centerPos.x(), centerPos.y(), \
                                                           m_originSize.width(), m_originSize.height());
    QPainterPath path;
    path.addText(QPointF(textRect.bottomLeft().x(), textRect.bottomLeft().y() - m_descent), m_font, m_Text);
//    qDebug() << "m_size:" << m_size;
//    qDebug() << "m_startSize:" << m_startSize;
    qDebug() << "m_scaleX:" << m_scaleX<< " m_scaleY:"<<m_scaleY;
//    qDebug();

    // 添加轮廓
    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::black);
//    painter->strokePath(path, pen);
    painter->scale(m_scaleX, m_scaleY);

    // 绘制
    //    pen.setWidth(m_pPenSizeAttribute->getValue().toInt());
    //    pen.setColor(m_pTtextColorAttribute->getValue().value<QColor>());
    painter->setPen(pen);
    //    if (!m_pBFillColorAttribute->getValue().toBool())
    //        painter->setBrush(Qt::NoBrush);
    //    else
    //        painter->setBrush(m_pFillColorAttribute->getValue().value<QColor>());
    painter->setBrush(QBrush(Qt::black));
    painter->drawPath(path);
//    qDebug() << "m_scaleX:" << m_scaleX<< " m_scaleY:"<<m_scaleY;

//    m_size = QSizeF(textRect.width()*1, textRect.height()*2);
//    qDebug() << "m_size:" << m_size;

    painter->restore();
}
*/

//void CanvasTextItem::mouseMoveResizeOperator(const QPointF &scenePos, const QPointF &loacalPos)
//{
////    qreal xInterval = scenePos.x() - m_pressedPos.x();
////    qreal yInterval = scenePos.y() - m_pressedPos.y();

////    this->setPos(m_startPos + QPointF(xInterval, yInterval));
////    m_startPos = this->pos() + QPointF(xInterval, yInterval);
////    qDebug() << "mouseMoveResizeOperator m_startPos:" << m_startPos;
////    qDebug() << "mouseMoveResizeOperator  QPointF(xInterval, yInterval):" <<  QPointF(xInterval, yInterval);
////    qreal ratio = m_ratioValue;
//    qreal itemWidth = abs(loacalPos.x()) * 2 - m_nInterval - m_nEllipseWidth;
//    qreal itemHeight = abs(loacalPos.y()) * 2 - m_nInterval - m_nEllipseWidth;
//    //    if (m_isRatioScale)
//    //        itemHeight = itemWidth * 1.0 / ratio;
//    m_scaleX = itemWidth / m_originSize.width();
//    m_scaleY = itemHeight / m_originSize.height();

////    qDebug() << "m_size:" << m_size;
////    qDebug() << "m_startSize:" << m_startSize;
////    qDebug() << "m_scaleX:" << m_scaleX<< " m_scaleY:"<<m_scaleY;
//    // 设置图片的最小大小为10
//    if (itemWidth < 10 || itemHeight < 10)
//        return;

//    m_size = QSize(m_originSize.width() * m_scaleX, m_originSize.height() * m_scaleY);
//    //    m_pWidthAttribute->setValue(m_size.width());
//    //    m_pHeightAttribute->setValue(m_size.height());

//    this->update();
//}

//void CanvasTextItem::initAttribute(void)
//{
//    QString groupName = tr("Text Attribute");
//    m_pNode->addAttributeGroup(groupName);

//    // 本文内容
//    m_pTextValueAttribute = new NDStringAttribute;
//    m_pTextValueAttribute->setValue(m_Text);
//    m_pTextValueAttribute->setDisplayName(tr("Text: "));
//    m_pTextValueAttribute->setName("text");
//    m_pTextValueAttribute->setShowButton(false);
//    m_pNode->addAttribute(groupName, m_pTextValueAttribute);

//    // 字体大小
//    m_pFontSizeAttribute = new NDIntAttribute;
//    m_pFontSizeAttribute->setValue(m_font.pixelSize());
//    m_pFontSizeAttribute->setValueRange(1, 200);
//    m_pFontSizeAttribute->setDisplayName(tr("Font Size: "));
//    m_pFontSizeAttribute->setName("fontSize");
//    m_pNode->addAttribute(groupName, m_pFontSizeAttribute);

//    // 画笔大小
//    m_pPenSizeAttribute = new NDIntAttribute;
//    m_pPenSizeAttribute->setValue(1);
//    m_pPenSizeAttribute->setValueRange(1, 10);
//    m_pPenSizeAttribute->setDisplayName(tr("Pen Size: "));
//    m_pPenSizeAttribute->setName("penSize");
//    m_pNode->addAttribute(groupName, m_pPenSizeAttribute);

//    // 文字颜色
//    m_pTtextColorAttribute = new NDColorAttribute;
//    m_pTtextColorAttribute->setValue(QColor(10, 10, 10));
//    m_pTtextColorAttribute->setDisplayName(tr("Text Color: "));
//    m_pTtextColorAttribute->setName("textColor");
//    m_pNode->addAttribute(groupName, m_pTtextColorAttribute);

//    // 是否填充颜色
//    m_pBFillColorAttribute = new NDBoolAttribute;
//    m_pBFillColorAttribute->setValue(true);
//    m_pBFillColorAttribute->setDisplayName(tr("Is Fill Color: "));
//    m_pBFillColorAttribute->setName("bFillColorOutline");
//    m_pNode->addAttribute(groupName, m_pBFillColorAttribute);

//    // 文字填充颜色
//    m_pFillColorAttribute = new NDColorAttribute;
//    m_pFillColorAttribute->setValue(QColor(10, 10, 10));
//    m_pFillColorAttribute->setDisplayName(tr("Fill Color: "));
//    m_pFillColorAttribute->setName("fillColor");
//    m_pNode->addAttribute(groupName, m_pFillColorAttribute);

//    QString outLineGroupName = tr("OutLine Attribute");
//    m_pNode->addAttributeGroup(outLineGroupName);
//    // 是否显示轮廓线
//    m_pBOutLineAttribute = new NDBoolAttribute;
//    m_pBOutLineAttribute->setValue(false);
//    m_pBOutLineAttribute->setDisplayName(tr("Is Show Outline: "));
//    m_pBOutLineAttribute->setName("bShowOutline");
//    m_pNode->addAttribute(outLineGroupName, m_pBOutLineAttribute);

//    // 添加填充颜色
//    m_pOutLineColorAttribute = new NDColorAttribute;
//    m_pOutLineColorAttribute->setEnable(false);
//    m_pOutLineColorAttribute->setValue(QColor(200, 200, 200));
//    m_pOutLineColorAttribute->setDisplayName(tr("Outline Color: "));
//    m_pOutLineColorAttribute->setName("outlineColor");
//    m_pNode->addAttribute(outLineGroupName, m_pOutLineColorAttribute);

//    // 轮廓线宽度
//    m_pOutLineWidthAttribute = new NDIntAttribute;
//    m_pOutLineWidthAttribute->setValue(1);
//    m_pOutLineWidthAttribute->setValueRange(1, 20);
//    m_pOutLineWidthAttribute->setDisplayName(tr("OutLine Width: "));
//    m_pOutLineWidthAttribute->setName("outlineWidth");
//    m_pNode->addAttribute(outLineGroupName, m_pOutLineWidthAttribute);

//    // 连接信号和槽
//    QObject::connect(m_pBOutLineAttribute, &NDBoolAttribute::valueChanged, this, &CanvasTextItem::onValueChanged);
//    QObject::connect(m_pOutLineWidthAttribute, &NDIntAttribute::valueChanged, this, &CanvasTextItem::onValueChanged);
//    QObject::connect(m_pOutLineColorAttribute, &NDColorAttribute::valueChanged, this, &CanvasTextItem::onValueChanged);

//    QObject::connect(m_pFontSizeAttribute, &NDIntAttribute::valueChanged, this, &CanvasTextItem::onFontSizeValueChanged);
//    QObject::connect(m_pPenSizeAttribute, &NDIntAttribute::valueChanged, this, &CanvasTextItem::onValueChanged);
//    QObject::connect(m_pTtextColorAttribute, &NDColorAttribute::valueChanged, this, &CanvasTextItem::onValueChanged);
//    QObject::connect(m_pTextValueAttribute, &NDStringAttribute::valueChanged, this, &CanvasTextItem::onTextValueChanged);
//    QObject::connect(m_pBFillColorAttribute, &NDBoolAttribute::valueChanged, this, &CanvasTextItem::onValueChanged);
//    QObject::connect(m_pFillColorAttribute, &NDColorAttribute::valueChanged, this, &CanvasTextItem::onValueChanged);
//}

void CanvasTextItem::onValueChanged(void)
{
    this->update();
}

void CanvasTextItem::onTextValueChanged(const QVariant& text)
{
    setCurrentText(text.toString());
    this->update();
}

void CanvasTextItem::onFontSizeValueChanged(const QVariant& fontSize)
{
    m_font.setPixelSize(fontSize.toInt());
    setCurrentFont(m_font);
    this->update();
}
