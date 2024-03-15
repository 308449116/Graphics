#ifndef UICUSTOMCOMBOBOX_H
#define UICUSTOMCOMBOBOX_H

#include <QComboBox>
class UICustomComboBox : public QComboBox
{
    Q_OBJECT

public:
    UICustomComboBox(QWidget *parent = nullptr);
    ~UICustomComboBox() override;

protected:
    QSize sizeHint() const override;
};

#endif // UICUSTOMCOMBOBOX_H
