#ifndef WORKSHEET_H
#define WORKSHEET_H

#include <QHash>
#include <QFile>
#include <QDataStream>

#include <QDebug>

#include "exceptions/illegalargumentexception.h"
#include "model/studycourse.h"
#include "model/course.h"

class Worksheet
{
public:
    Worksheet();
    explicit Worksheet(const QString &sourceFile) throw (IllegalArgumentException);
    Worksheet(int institutionId, const StudyCourse *studyCourse);

    int institutionId() const;
    int studyCourseId() const;
    QHash<int, double> grades() const;
    void setInstitutionId(int institutionId);
    void setStudyCourseId(int studyCourseId);
    void setGrade(int key, double value);

    void toFile(const QString &targetFile) const;

private:
    int mInstitutionId;
    int mStudyCourseId;
    QHash<int, double> mGrades;
};

#endif // WORKSHEET_H
