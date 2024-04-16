#include "exceptions.h"
#include "messageeditortr.h"

namespace MessageEditor {

Exception::Exception(const QString &errorMessage)
    : m_errorMessage(errorMessage)
{
}

NullPointerException::NullPointerException()
    : Exception(Tr::tr("Unacceptable null object."))
{
}

}
