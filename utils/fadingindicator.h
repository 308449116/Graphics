#ifndef FADINGINDICATOR_H
#define FADINGINDICATOR_H

#include <QtGlobal>

QT_BEGIN_NAMESPACE
class QString;
class QWidget;
QT_END_NAMESPACE

namespace Utils {
namespace FadingIndicator {

enum TextSize {
    SmallText,
    LargeText
};

void showText(QWidget *parent, const QString &text, TextSize size = LargeText);
void showPixmap(QWidget *parent, const QString &pixmap);

} // FadingIndicator
} // Utils

#endif //FADINGINDICATOR_H
