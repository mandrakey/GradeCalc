/* Copyright (C) 2013  Maurice Bleuel (mandrakey@lavabit.com)
 *
 * This file is part of GradeCalc.
 *
 * GradeCalc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GradeCalc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GradeCalc.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ILLEGALXMLEXCEPTION_H
#define ILLEGALXMLEXCEPTION_H

#include <QString>

#include "exception.h"

/**
 * Exception thrown when something wrong has been detected in an XML node/file.
 * @ingroup exceptions
 * @see Exception
 */
class IllegalXmlException : public Exception
{
public:
    IllegalXmlException();
    IllegalXmlException(QString message);
};

#endif // ILLEGALXMLEXCEPTION_H
