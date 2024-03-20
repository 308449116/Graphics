#ifndef CUSTOMCOMBOBOX_H
#define CUSTOMCOMBOBOX_H

#include <QComboBox>
class CustomComboBox : public QComboBox
{
    Q_OBJECT

public:
    CustomComboBox(QWidget *parent = nullptr);
    ~CustomComboBox() override;

protected:
    QSize sizeHint() const override;
};

#endif // UICUSTOMCOMBOBOX_H
