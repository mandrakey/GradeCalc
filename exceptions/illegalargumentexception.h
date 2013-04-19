#ifndef ILLEGALARGUMENTEXCEPTION_H
#define ILLEGALARGUMENTEXCEPTION_H

#include "exception.h"

class IllegalArgumentException : public Exception
{
public:
    IllegalArgumentException();
    IllegalArgumentException(const QString& message);
};

#endif // ILLEGALARGUMENTEXCEPTION_H
