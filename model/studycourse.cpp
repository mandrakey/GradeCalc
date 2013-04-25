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

#include "studycourse.h"
#include <iostream>

StudyCourse::StudyCourse() :
    mId(-1), mName(QString()), mTitle(QString()), mCourses(QList<Course*>())
{
}

StudyCourse::StudyCourse(const QDomNode &node) throw (IllegalXmlException) :
    StudyCourse()
{
    QDomElement element = node.toElement();

    if (!element.hasAttribute("id"))
        throw IllegalXmlException("StudyCourse needs an ID");
    if (!element.hasAttribute("name"))
        throw IllegalXmlException("StudyCourse needs a name");
    if (!element.hasAttribute("title"))
        throw IllegalXmlException("StudyCourse needs a resulting title");

    this->mId = element.attribute("id").toInt();
    this->mName = element.attribute("name");
    this->mTitle = element.attribute("title");

    QDomNodeList courses = element.elementsByTagName("Course");
    for (int i = 0; i < courses.size(); ++i)
        this->mCourses << new Course(courses.at(i));

    //std::cout << QString("StudyCourse[%1, %2]").arg(mName, mTitle).toStdString() << std::endl;
}

StudyCourse::~StudyCourse()
{
    foreach (Course *c, mCourses)
        delete c;
}

int StudyCourse::getId() const
{
    return mId;
}

const QString& StudyCourse::getName() const
{
    return mName;
}

const QList<Course *> StudyCourse::getCourses() const
{
    return QList<Course *>(mCourses);
}

Course* StudyCourse::getCourse(const QString &name) const throw (QString)
{
    int index = 0;
    foreach (Course* c, mCourses) {
        if (c->getShortname().compare(name) == 0 ||
                c->getName().compare(name) == 0)
            return mCourses.at(index);
        ++index;
    }

    throw QString("Course with name '%1' not found").arg(name);
}

Course* StudyCourse::getCourse(int index) const throw (QString)
{
    if (index < 0 || index > mCourses.size())
        throw QString("Index %1 is out of boundary").arg(index);

    return mCourses.at(index);
}

void StudyCourse::addCourse(Course *c)
{
    mCourses << c;
}

QString StudyCourse::toString() const
{
    QString res = QString("\tStudyCourse %1 (%2):\n").
            arg(mName, mTitle);

    foreach (Course* c, mCourses) {
        res.append(c->toString());
    }

    res.append("\t< StudyCourse.\n");
    return res;
}
