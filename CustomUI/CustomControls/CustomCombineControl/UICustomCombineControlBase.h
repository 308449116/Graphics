#ifndef UICUSTOMCOMBINECONTROLBASE_H
#define UICUSTOMCOMBINECONTROLBASE_H

#include "UICustomWidgtes/CustomWidget.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>

class UICustomCombineControlBase : public CustomWidget
{
    Q_OBJECT

public:
    UICustomCombineControlBase(QWidget* parent = nullptr);
    ~UICustomCombineControlBase();

    // 设置某一列的宽度
    void setColumnWidth(int column, int width);

    // 设置某一列显示/隐藏
    void setColumnVisible(int column, bool visible);

    // 设置某一列伸缩性
    void setColumnExpingVisible(int column, bool isExping);

    // 设置文本内容
    void setTagText(const QString& tagText);

    // 设置文本的对齐方式
    void setTextAlign(Qt::Alignment alignment);

    // 设置宽度和高度
    void setWidth(int width);
    void setHeight(int height);

protected:
    QHBoxLayout *m_pMainLayout = nullptr;
    QLabel* m_pTagLabel = nullptr;

    QSize sizeHint() const override;

private:
    int m_nWidth = 400;
    int m_nHeight = 30;
};

#endif
