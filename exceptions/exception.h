#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QString>

class Exception
{
public:
    Exception();
    Exception(const QString &message);

    virtual const QString& getMessage() const;

protected:
    const QString mMessage;
};

#endif // EXCEPTION_H
