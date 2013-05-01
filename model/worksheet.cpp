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

#include "worksheet.h"

Worksheet::Worksheet() :
    mInstitutionId(-1), mStudyCourseId(-1), mGrades()
{
}

Worksheet::Worksheet(const QString &sourceFile) throw (IllegalArgumentException) :
    Worksheet()
{
    QFile f(sourceFile);
    if (!f.exists() || !f.open(QIODevice::ReadOnly))
        throw IllegalArgumentException(QString("File %1 can not be opened").arg(sourceFile));

    QDataStream stream(&f);
    stream >> mInstitutionId >> mStudyCourseId;
    while (!stream.atEnd()) {
        int id = 0;
        double grade = 0;
        stream >> id >> grade;
        mGrades.insert(id, grade);
    }

    f.close();
}

Worksheet::Worksheet(int institutionId, const StudyCourse *studyCourse) :
    mInstitutionId(institutionId), mStudyCourseId(studyCourse->getId()),
    mGrades()
{
    QList<Course *> courses = studyCourse->getCourses();
    int i = 0;
    foreach (Course *c, courses)
        mGrades.insert(i++, c->getGrade());
}

int Worksheet::institutionId() const
{
    return mInstitutionId;
}

int Worksheet::studyCourseId() const
{
    return mStudyCourseId;
}

QHash<int,double> Worksheet::grades() const
{
    return QHash<int,double>(mGrades);
}

void Worksheet::setInstitutionId(int institutionId)
{
    mInstitutionId = institutionId;
}

void Worksheet::setStudyCourseId(int studyCourseId)
{
    mStudyCourseId = studyCourseId;
}

void Worksheet::setGrade(int key, double value)
{
    mGrades.insert(key, value);
}

void Worksheet::toFile(const QString &targetFile) const
{
    QFile f(targetFile);
    if (!f.open(QIODevice::WriteOnly))
        throw IllegalArgumentException(
                QString("File %1 can not be opened").arg(targetFile));

    QDataStream stream(&f);
    stream << quint32(mInstitutionId) << quint32(mStudyCourseId);
    foreach (int k, mGrades.keys()) {
        stream << quint32(k) << qreal(mGrades.value(k));
    }

    f.close();
}
