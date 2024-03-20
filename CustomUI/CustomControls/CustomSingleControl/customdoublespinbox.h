#ifndef CUSTOMDOUBLESPINBOX_H
#define CUSTOMDOUBLESPINBOX_H

#include <QWidget>
#include <QDoubleSpinBox>

class CustomDoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT

public:
    CustomDoubleSpinBox(QWidget *parent = nullptr);
    ~CustomDoubleSpinBox();

protected:
    virtual QSize sizeHint() const override;

    void keyPressEvent(QKeyEvent *event) override;
};

#endif
