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

#include "institution.h"
#include <iostream>

Institution::Institution() :
    mId(-1), mName(QString()), mDescription(QString()), mCity(QString()),
    mStudyCourses(QList<StudyCourse *>())
{
}

Institution::Institution(const QDomNode &node) throw (IllegalXmlException) :
    Institution()
{
    QDomElement element = node.toElement();
    QDomNodeList children = element.childNodes();

    if (element.hasAttribute("id"))
        mId = element.attribute("id").toInt();

    for (int i = 0; i < children.size(); ++i) {
        QDomElement e = children.at(i).toElement();

        if (e.tagName().compare("name") == 0)
            this->mName = e.text();
        else if (e.tagName().compare("city") == 0)
            this->mCity = e.text();
        else if (e.tagName().compare("description") == 0)
            this->mDescription = e.text();
        else if (e.tagName().compare("StudyCourse") == 0)
            this->mStudyCourses.push_back(new StudyCourse(children.at(i)));
    }

    // Check validity
    if (mId == -1)
        throw IllegalXmlException(QString("Institution %1 has no ID attribute").arg(mName));
}

Institution::~Institution()
{
    foreach (StudyCourse *s, mStudyCourses)
        delete s;
}

int Institution::getId() const
{
    return mId;
}

const QString& Institution::getName() const
{
    return mName;
}

const QString& Institution::getDescription() const
{
    return mDescription;
}

const QString& Institution::getCity() const
{
    return mCity;
}

QList<StudyCourse *> Institution::getStudyCourses() const
{
    return QList<StudyCourse *>(mStudyCourses);
}

QString Institution::toString() const
{
    QString res = QString("> Institution %1 in %2 (%3):\n").
            arg(mName, mCity, mDescription);

    foreach (StudyCourse *s, mStudyCourses) {
        res.append(s->toString());
    }

    res.append("< Institution.\n");
    return res;
}
