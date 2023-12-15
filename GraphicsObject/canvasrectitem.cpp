#include "canvasrectitem.h"
//#include "NDNodeBase.h"
//#include "NDBoolAttribute.h"
//#include "NDIntAttribute.h"
//#include "NDColorAttribute.h"
#include <QPainter>

CanvasRectItem::CanvasRectItem(QGraphicsItem* parentItem)
    : CanvasItemBase (parentItem)
{
//    initAttribute();
}

CanvasRectItem::~CanvasRectItem()
{

}

void CanvasRectItem::setSize(int width, int height)
{
    m_size.setWidth(width);
    m_size.setHeight(height);

    this->prepareGeometryChange();
}

void CanvasRectItem::customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->save();
    // 设置画笔
    if (1)
    {
        QPen pen;
        pen.setWidth(2);
        pen.setColor("black");
        painter->setPen(pen);
    }
    else {
        painter->setPen(Qt::NoPen);
    }

    // 设置画刷
//    if (0)
//    {
//        painter->setBrush(QBrush("red"));
//    }
//    else {
//        painter->setBrush(Qt::red);
//    }

    QRectF rect = this->getCustomRect();
    painter->drawRect(rect);
    painter->restore();
}

//void CanvasRectItem::initAttribute()
//{
//    QString groupName = tr("Item Attribute");
//    m_pNode->addAttributeGroup(groupName);

//    // 是否为圆形
//    m_pBRoundAttribute = new NDBoolAttribute;
//    m_pBRoundAttribute->setValue(true);
//    m_pBRoundAttribute->setDisplayName(tr("Is Rounded: "));
//    m_pBRoundAttribute->setName("bRounded");
//    m_pNode->addAttribute(groupName, m_pBRoundAttribute);

//    // 添加是否填充属性
//    m_pBFillAttribute = new NDBoolAttribute;
//    m_pBFillAttribute->setValue(false);
//    m_pBFillAttribute->setDisplayName(tr("Is Fill Color: "));
//    m_pBFillAttribute->setName("bFillColor");
//    m_pNode->addAttribute(groupName, m_pBFillAttribute);

//    // 添加填充颜色
//    m_pFillColorAttribute = new NDColorAttribute;
//    m_pFillColorAttribute->setEnable(false);
//    m_pFillColorAttribute->setValue(QColor(150, 150, 150));
//    m_pFillColorAttribute->setDisplayName(tr("Fill Color: "));
//    m_pFillColorAttribute->setName("fillColor");
//    m_pNode->addAttribute(groupName, m_pFillColorAttribute);

//    // 添加是否显示轮廓线
//    m_pBOutLineAttribute = new NDBoolAttribute;
//    m_pBOutLineAttribute->setValue(true);
//    m_pBOutLineAttribute->setDisplayName(tr("Show OutLine: "));
//    m_pBOutLineAttribute->setName("bOutline");
//    m_pNode->addAttribute(groupName, m_pBOutLineAttribute);

//    // 轮廓线宽度
//    m_pOutLineWidthAttribute = new NDIntAttribute;
//    m_pOutLineWidthAttribute->setValue(1);
//    m_pOutLineWidthAttribute->setValueRange(1, 20);
//    m_pOutLineWidthAttribute->setDisplayName(tr("OutLine Width: "));
//    m_pOutLineWidthAttribute->setName("outlineWidth");
//    m_pNode->addAttribute(groupName, m_pOutLineWidthAttribute);

//    // 轮廓线颜色
//    m_pOutLineColorAttribute = new NDColorAttribute;
//    m_pOutLineColorAttribute->setValue(QColor(10, 10, 10));
//    m_pOutLineColorAttribute->setDisplayName(tr("OutLine Color: "));
//    m_pOutLineColorAttribute->setName("outlineColor");
//    m_pNode->addAttribute(groupName, m_pOutLineColorAttribute);

//    // 连接信号和槽
//    QObject::connect(m_pBRoundAttribute, &NDBoolAttribute::valueChanged, this, &CanvasRectItem::onRoundValueChanged);
//    QObject::connect(m_pBFillAttribute, &NDBoolAttribute::valueChanged, this, &CanvasRectItem::onValueChanged);
//    QObject::connect(m_pFillColorAttribute, &NDColorAttribute::valueChanged, this, &CanvasRectItem::onValueChanged);
//    QObject::connect(m_pBOutLineAttribute, &NDBoolAttribute::valueChanged, this, &CanvasRectItem::onValueChanged);
//    QObject::connect(m_pOutLineWidthAttribute, &NDIntAttribute::valueChanged, this, &CanvasRectItem::onValueChanged);
//    QObject::connect(m_pOutLineColorAttribute, &NDColorAttribute::valueChanged, this, &CanvasRectItem::onValueChanged);
//}

void CanvasRectItem::onValueChanged(void)
{
    this->update();
}

void CanvasRectItem::onRoundValueChanged(const QVariant& value)
{
    this->setItemResizeable(true);
    this->setItemResizeRatio(value.toBool(), 1.0);

    if (value.toBool())
    {
        int width = m_size.width();
        m_size.setHeight(width);
        this->prepareGeometryChange();
    }
}

