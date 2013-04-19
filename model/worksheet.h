#ifndef WORKSHEET_H
#define WORKSHEET_H

#include <QHash>
#include <QFile>
#include <QDataStream>

#include "exceptions/illegalargumentexception.h"

class Worksheet
{
public:
    Worksheet();
    Worksheet(const QString &sourceFile) throw (IllegalArgumentException);

    int institutionId() const;
    int studyCourseId() const;
    QHash<int, int> grades() const;

    void toFile(const QString &targetFile) const;

private:
    int mInstitutionId;
    int mStudyCourseId;
    QHash<int, int> mGrades;
};

#endif // WORKSHEET_H
