#ifndef ILLEGALXMLEXCEPTION_H
#define ILLEGALXMLEXCEPTION_H

#include <QString>

#include "exception.h"

class IllegalXmlException : public Exception
{
public:
    IllegalXmlException();
    IllegalXmlException(QString message);
};

#endif // ILLEGALXMLEXCEPTION_H
