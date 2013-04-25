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

#include "course.h"

Course::Course() :
    mSemester(0), mName(QString("")), mShortname(QString("")),
    mEcts(0.0), mGrade(0.0), mValue(0.0)
{
}

Course::Course(int semester, const QString &name, const QString &shortname,
               double ects) :
    mSemester(semester), mName(name), mShortname(shortname), mEcts(ects),
    mGrade(0.0), mValue(0.0)
{
}

Course::Course(const QDomNode &node) throw (IllegalXmlException) :
    Course()
{
    QDomElement element = node.toElement();

    if (!element.hasAttribute("shortname"))
        throw IllegalXmlException("Course needs a shortname");
    if (!element.hasAttribute("ects"))
        throw IllegalXmlException("Course needs ects points");
    if (!element.hasAttribute("semester"))
        throw IllegalXmlException("Course needs a semester");

    this->mShortname = element.attribute("shortname").trimmed();
    this->mEcts = element.attribute("ects").toDouble();
    this->mSemester = element.attribute("semester").toInt();
    this->mName = element.text().trimmed();
}

int Course::getSemester() const
{
    return mSemester;
}

const QString& Course::getName() const
{
    return mName;
}

const QString& Course::getShortname() const
{
    return mShortname;
}

double Course::getEcts() const
{
    return mEcts;
}

double Course::getGrade() const
{
    return mGrade;
}

double Course::getValue() const
{
    return mValue;
}

double Course::getValue(double grade) throw (QString)
{
    if (grade < 1.0 || grade > 5.0)
        throw QString("Grade %1 is out of boundary").arg(grade);
    setGrade(grade);
    return mValue;
}

void Course::setGrade(double grade) throw (QString)
{
    if (mEcts <= 0.0)
        throw QString("Need ECTS before value can be calculated and grade be "
                      "set");

    if (grade < 1.0 || grade > 5.0)
        throw QString("The value for a grade must be within 1.0 and 5.0. Given"
                      " value: %1").arg(grade);
    mGrade = grade;
    mValue = mGrade * mEcts;
}

void Course::clear()
{
    mGrade = 0;
    mValue = 0;
}

QString Course::toString() const
{
    QString res = QString("\t\t> Course %1 (%2)\n").
            arg(mName.trimmed(), mShortname);
    res.append(QString("\t\t\tSemester: %1\n").arg(mSemester));
    res.append(QString("\t\t\tECTS: %1\n").arg(mEcts));
    res.append(QString("\t\t\tGrade: %1\n").arg(mGrade));
    res.append(QString("\t\t\tValue: %1\n").arg(mValue));
    res.append("\t\t< Course.\n");

    return res;
}
