#include "exception.h"

Exception::Exception() :
    mMessage(QString("Exception"))
{
}

Exception::Exception(const QString &message) :
    mMessage(QString(message))
{
}
