#include "illegalargumentexception.h"

IllegalArgumentException::IllegalArgumentException() :
    Exception()
{
}

IllegalArgumentException::IllegalArgumentException(const QString &message) :
    Exception(message)
{
}
