#include "nullpointerexception.h"

NullPointerException::NullPointerException() :
    Exception()
{
}

NullPointerException::NullPointerException(const QString &message) :
    Exception(message)
{
}
