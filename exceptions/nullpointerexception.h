#ifndef NULLPOINTEREXCEPTION_H
#define NULLPOINTEREXCEPTION_H

#include "exception.h"

class NullPointerException : public Exception
{
public:
    NullPointerException();
    NullPointerException(const QString& message);
};

#endif // NULLPOINTEREXCEPTION_H
