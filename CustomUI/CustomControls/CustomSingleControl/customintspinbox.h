#ifndef CUSTOMINTSPINBOX_H
#define CUSTOMINTSPINBOX_H

#include <QSpinBox>

class CustomIntSpinBox : public QSpinBox
{
    Q_OBJECT

public:
    CustomIntSpinBox(QWidget *parent = nullptr);
    ~CustomIntSpinBox();

protected:
    virtual QSize sizeHint() const override;
    void keyPressEvent(QKeyEvent *event) override;
};

#endif
