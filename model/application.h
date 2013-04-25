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

#ifndef APPLICATION_H
#define APPLICATION_H

#include <QList>
#include <QFile>
#include <QTextStream>

#include <iostream>
using std::cerr;
using std::endl;

#include "institution.h"

/**
 * Contains application-wide data.
 * Implemented as a monostate object.
 * @ingroup model
 */
class Application
{
public:
    Application();

    QList<Institution*> institutions() const;
    const QString appName() const;
    const QString version() const;
    const QString copyright() const;
    const QString license() const;

    /**
     * Load the data.xml file containing available institutions, courses.
     * @todo Allow change of file path?
     */
    void loadDatabase();

    /**
     * Empty institutions list, delete all pointer targets.
     */
    void cleanup();

private:
    /** Initialization (loading license text etc.) completed? */
    static bool INITIALIZED;

    /** Contains a list of all loaded institutions. */
    static QList<Institution *> INSTITUTIONS;

    static const char *APPNAME;
    static const char *VERSION;
    static const char *COPYRIGHT;
    static QString LICENSE;
};

#endif // APPLICATION_H
