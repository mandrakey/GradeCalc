#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QString>
#include <QException>

class Exception : public QException
{
public:
    Exception();
    Exception(const QString &message);

protected:
    const QString mMessage;
};

#endif // EXCEPTION_H
