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

#ifndef WORKSHEET_H
#define WORKSHEET_H

#include <QHash>
#include <QFile>
#include <QDataStream>

#include <QDebug>

#include "exceptions/illegalargumentexception.h"
#include "model/studycourse.h"
#include "model/course.h"

/**
 * Represents a worksheet.
 * One worksheet consists of a selected institution and study course as well
 * as grades entered by the user.
 * @ingroup model
 */
class Worksheet
{
public:
    /**
     * Create a worksheet loading the given file.
     * @param sourceFile Path to the file to load.
     * @throws IllegalArgumentException
     */
    explicit Worksheet(const QString &sourceFile) throw (IllegalArgumentException);

    /**
     * Create a worksheet using an institution id and a study course object.
     * @param institutionId ID of the currently selected institution
     * @param studyCourse Pointer to the currently selected study course. The
     * study course contains all courses with their entered grades.
     */
    Worksheet(int institutionId, const StudyCourse *studyCourse);

    int institutionId() const;
    int studyCourseId() const;
    QHash<int, double> grades() const;
    void setInstitutionId(int institutionId);
    void setStudyCourseId(int studyCourseId);
    void setGrade(int key, double value);

    /**
     * Save current worksheet dataset to a file.
     * @param targetFile Path of the file to write to.
     */
    void toFile(const QString &targetFile) const;

private:
    /**
     * Create an empty worksheet.
     */
    Worksheet();

    int mInstitutionId;
    int mStudyCourseId;
    QHash<int, double> mGrades;
};

#endif // WORKSHEET_H
