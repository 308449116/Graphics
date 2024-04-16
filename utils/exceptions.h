#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QString>
#include <QCoreApplication>

namespace MessageEditor {

class Exception
{
public:
    explicit Exception(const QString &errorMessage);
    virtual ~Exception() = default;

    QString errorMessage() const { return m_errorMessage; }
    void setErrorMessage(const QString &errorMessage) { m_errorMessage = errorMessage; }

private:
    QString m_errorMessage;
};

class NullPointerException : public Exception
{
public:
    NullPointerException();
};

}
#endif
