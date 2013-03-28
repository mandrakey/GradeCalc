#include "uninitializedexception.h"

UninitializedException::UninitializedException() :
    Exception()
{
}

UninitializedException::UninitializedException(const QString &message) :
    Exception(message)
{
}
