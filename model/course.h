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

#ifndef COURSE_H
#define COURSE_H

#include <QString>
#include <QtXml/QDomNode>
#include <QtXml/QDomElement>

#include "exceptions/illegalxmlexception.h"

/**
 * Represents one course in a study course.
 * @ingroup model
 */
class Course
{
public:
    /**
     * Construct an empty course.
     * @deprecated Do not use
     * @todo Remove sometime
     */
    Course();

    /**
     * Construct a course from an XML document node in database file.
     * Node <b>must</b> have the attributes
     * - shortname
     * - ects
     * - semester
     * @param node The <Course>-node to load
     */
    Course(const QDomNode &node) throw (IllegalXmlException);
    explicit Course(int semester, const QString &name, const QString &shortname,
                    double ects);

    // Getter / Setter
    int getSemester() const;
    const QString& getName() const;
    const QString& getShortname() const;
    double getEcts() const;
    double getGrade() const;
    double getValue() const;

    /**
     * Set grade and retrieve score value using the new grade.
     * @param grade Grade to set, must be in between 1.0 and 5.0
     * @return Score value calculated after setting grade
     * @throw QString
     */
    double getValue(double grade) throw (QString);

    /**
     * Set a grade for this course.
     * Calculates the aquired core value using mEcts.
     * @param grade The grade to set, must be in between 1.0 and 5.0.
     * @throws QString If something went wrong, throws a message
     */
    void setGrade(double grade) throw (QString);

    /**
     * Clear grade and calculated score value.
     */
    void clear();

    QString toString() const;

private:
    int mSemester;
    QString mName;
    QString mShortname;
    double mEcts;
    double mGrade;

    /** Calculated value (mGrade * mECTS). */
    double mValue;
};

#endif // COURSE_H
