#ifndef UNINITIALIZEDEXCEPTION_H
#define UNINITIALIZEDEXCEPTION_H

#include "exception.h"

class UninitializedException : public Exception
{
public:
    UninitializedException();
    UninitializedException(const QString& message);
};

#endif // UNINITIALIZEDEXCEPTION_H
