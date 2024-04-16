#include "customgroupcontrol.h"
//#include "CustomCore/customstyleconfig.h"
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>

CustomGroupTitleItem::CustomGroupTitleItem(QWidget *parent)
    :CustomWidget(parent)
{
//    g_StyleConfig->setCurrentStyle(this, "GroupTitle");
    this->setMinimumHeight(30);
}

CustomGroupTitleItem::~CustomGroupTitleItem()
{

}

void CustomGroupTitleItem::mousePressEvent(QMouseEvent *event)
{
    m_isExpanding = !m_isExpanding;
    this->update();
    event->accept();
    emit clickedTitle(m_isExpanding);
}

void CustomGroupTitleItem::customPaint(QPainter *painter)
{
    QTextOption option;
    option.setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    QPen pen;
//    pen.setColor(QColor(230, 230, 230));
    pen.setColor(Qt::black);
    painter->setPen(pen);

    int leftSpacing = 4;
    int drawMargin = 2;
    int expandWidth = 12;

    // 绘制展开
    qreal topHeight = (this->rect().height() - expandWidth) / 2.0;
    QRectF spandRect(leftSpacing + drawMargin, topHeight, expandWidth, expandWidth);
    painter->drawRect(spandRect);
    QLineF line1(spandRect.x(), spandRect.center().y(), spandRect.right(), spandRect.center().y());
    QLineF line2(spandRect.center().x(), spandRect.top(), spandRect.center().x(), spandRect.bottom());
    painter->drawLine(line1);
    if (!m_isExpanding)
        painter->drawLine(line2);


    // 绘制Title
    qreal leftWidth = spandRect.x() + leftSpacing + drawMargin * 2 + expandWidth;
    QRectF rect(leftWidth, 0, this->width() - leftWidth, this->height());
    painter->drawText(rect, m_titleName, option);
}

void CustomGroupTitleItem::setTitleText(const QString& titleNameString)
{
    m_titleName = titleNameString;
    this->update();
}

QSize CustomGroupTitleItem::sizeHint() const
{
    QSize size(400, 30);
    return size;
}

// -----------------------------------------------------------------------------
// 组件内容
CustomGroupContentItem::CustomGroupContentItem(QWidget *parent)
    :CustomWidget(parent)
{
    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(2, 2, 2, 2);
    m_layout->setSpacing(2);

//    g_StyleConfig->setCurrentStyle(this, "GroupContent");
}

CustomGroupContentItem::~CustomGroupContentItem()
{

}

void CustomGroupContentItem::addWidget(QWidget *widget)
{
    m_layout->addWidget(widget);
}

void CustomGroupContentItem::insertWidget(int index, QWidget *widget)
{
    m_layout->insertWidget(index, widget);
}

QSize CustomGroupContentItem::sizeHint() const
{
    int count = m_layout->count();

    // 高度
    int height = 0;
    for (int i=0; i<count; ++i)
    {
        QWidget *pWidget = m_layout->itemAt(i)->widget();
        if (pWidget == nullptr)
            continue;

        height += pWidget->sizeHint().height();
    }

    height += 4 + 2  *count;
    QSize size(400, height);
    return size;
}

// -----------------------------------------------------------------------------
CustomGroupControl::CustomGroupControl(QWidget *parent)
    :CustomWidget(parent)
{
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setContentsMargins(2, 2, 2, 2);
    m_mainLayout->setSpacing(0);

    m_titleItemWidget = new CustomGroupTitleItem;
    m_contentItemWidget = new CustomGroupContentItem;

    m_mainLayout->addWidget(m_titleItemWidget);
    m_mainLayout->addWidget(m_contentItemWidget);

//    g_StyleConfig->setCurrentStyle(this, "GroupWidget");

    QObject::connect(m_titleItemWidget, &CustomGroupTitleItem::clickedTitle, \
                     this, &CustomGroupControl::onClickedGroupTitleItem);
}

CustomGroupControl::~CustomGroupControl()
{

}

void CustomGroupControl::addContentWidget(QWidget *widget)
{
    m_contentItemWidget->addWidget(widget);
}

void CustomGroupControl::insertContentWidget(int index, QWidget *widget)
{
    m_contentItemWidget->insertWidget(index, widget);
}

void CustomGroupControl::setTitleText(const QString& string)
{
    m_titleItemWidget->setTitleText(string);
}

void CustomGroupControl::onClickedGroupTitleItem(bool isExpanded)
{
    m_contentItemWidget->setVisible(isExpanded);
}

QSize CustomGroupControl::sizeHint() const
{
    int height = 4;
    height += m_titleItemWidget->sizeHint().height();

    if (m_contentItemWidget->isVisible())
        height += m_contentItemWidget->sizeHint().height();

    return QSize(400, height);
}
