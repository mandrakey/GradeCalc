#include "illegalxmlexception.h"

IllegalXmlException::IllegalXmlException() :
    Exception()
{
}

IllegalXmlException::IllegalXmlException(QString message) :
    Exception(message)
{
}
