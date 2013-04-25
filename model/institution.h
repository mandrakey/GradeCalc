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

#ifndef INSTITUTION_H
#define INSTITUTION_H

#include <QString>
#include <QList>
#include <QtXml/QDomNode>
#include <QtXml/QDomElement>
#include <QtXml/QDomNodeList>

#include "exceptions/illegalxmlexception.h"
#include "studycourse.h"

/**
 * Holds information about a stuy/course institution.
 * @ingroup model
 */
class Institution
{
public:
    /**
     * Create an empty institution.
     * @deprecated
     * @todo Remove sometime
     */
    Institution();

    /**
     * Create an institution from an XML document node.
     * An institution <b>must</b> have the attributes
     * - id
     * @param node The <Institution>-node to use
     */
    Institution(const QDomNode &node) throw (IllegalXmlException);

    /**
     * Deletes all study courses at this institution.
     */
    ~Institution();

    // Getter / Setter
    int getId() const;
    const QString& getName() const;
    const QString& getDescription() const;
    const QString& getCity() const;
    QList<StudyCourse *> getStudyCourses() const;

    QString toString() const;

private:
    int mId;
    QString mName;
    QString mDescription;
    QString mCity;
    QList<StudyCourse*> mStudyCourses;
};

#endif // INSTITUTION_H
