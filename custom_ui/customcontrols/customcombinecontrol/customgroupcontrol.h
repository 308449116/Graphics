#ifndef CUSTOMGROUPCONTROL_H
#define CUSTOMGROUPCONTROL_H

#include <QWidget>
#include <QVBoxLayout>
#include "custom_ui/customwidgtes/customwidget.h"

class CustomGroupTitleItem;
class CustomGroupContentItem;

// 组控件
class CustomGroupControl : public CustomWidget
{
    Q_OBJECT

public:
    CustomGroupControl(QWidget *parent = nullptr);
    ~CustomGroupControl();

    // 添加内容
    void addContentWidget(QWidget *widget);
    void insertContentWidget(int index, QWidget *widget);

    // 设置标题文本
    void setTitleText(const QString& string);

protected:
    virtual QSize sizeHint() const override;

private slots:
    void onClickedGroupTitleItem(bool isExpanded);

private:
    QVBoxLayout *m_mainLayout = nullptr;
    CustomGroupTitleItem *m_titleItemWidget = nullptr;
    CustomGroupContentItem *m_contentItemWidget = nullptr;
};

// -----------------------------------------------------------------------------
// 标题
class CustomGroupTitleItem : public CustomWidget
{
    Q_OBJECT

public:
    CustomGroupTitleItem(QWidget *parent = nullptr);
    ~CustomGroupTitleItem();

    // 设置Title内容
    void setTitleText(const QString& titleNameString);

    friend class CustomGroupControl;

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void customPaint(QPainter *painter) override;
    virtual QSize sizeHint() const override;

signals:
    void clickedTitle(bool isExpanded);

private:
    QString m_titleName;
    bool m_isExpanding = true;
};

// -----------------------------------------------------------------------------
// 组件内容
class CustomGroupContentItem : public CustomWidget
{
    Q_OBJECT

public:
    CustomGroupContentItem(QWidget *parent = nullptr);
    ~CustomGroupContentItem();

    void addWidget(QWidget *widget);
    void insertWidget(int index, QWidget *widget);

    friend class CustomGroupControl;

protected:
    virtual QSize sizeHint() const override;

private:
    QVBoxLayout *m_layout = nullptr;
};

#endif
