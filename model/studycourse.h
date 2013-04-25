/*
 * Copyright (C) 2013  Maurice Bleuel (mandrakey@lavabit.com)
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

#ifndef STUDYCOURSE_H
#define STUDYCOURSE_H

#include <QtXml/QDomNode>
#include <QtXml/QDomElement>
#include <QtXml/QDomNodeList>
#include <QList>

#include "course.h"
#include "exceptions/illegalxmlexception.h"

/**
 * Represents one study course.
 * @ingroup model
 */
class StudyCourse
{
public:
    /**
     * Create a new study course from a given XML node.
     * Node <b>must</b> contain the following attributes:
     * - id
     * - name
     * - title
     * @param node The <StudyCourse>-node to use
     * @throws IllegalXmlException
     */
    StudyCourse(const QDomNode &node) throw (IllegalXmlException);

    /**
     * Destruct a study course, deletes all courses within.
     **/
    ~StudyCourse();

    // Getter / Setter
    int getId() const;
    const QString& getName() const;
    const QList<Course *> getCourses() const;

    /**
     * Retrieve a specific course by it's name.
     * @param name Name of the course to search for
     * @return Pointer to the course being searched
     */
    Course* getCourse(const QString& name) const throw (QString);

    /**
     * Retrieve a specific course by it's list index.
     * @param index List index, starting with 0
     * @return Pointer to the requested course
     */
    Course* getCourse(int index) const throw (QString);

    QString toString() const;

    /**
     * Add a course to the courses list.
     * @param c The course to put in the list
     */
    void addCourse(Course* c);

private:
    /**
     * Create an empty study course.
     */
    StudyCourse();

    int mId;
    QString mName;
    QString mTitle;
    QList<Course*> mCourses;
};

#endif // STUDYCOURSE_H
