#include "worksheet.h"

Worksheet::Worksheet() :
    mInstitutionId(-1), mStudyCourseId(-1), mGrades()
{
    // TEST
    mInstitutionId = 1;
    mStudyCourseId = 2;
    mGrades.insert(0, 3);
    mGrades.insert(1, 2);
    // TEST
}

Worksheet::Worksheet(const QString &sourceFile) throw (IllegalArgumentException) :
    mInstitutionId(-1), mStudyCourseId(-1), mGrades()
{
    QFile f(sourceFile);
    if (!f.exists() || !f.isReadable() || !f.open(QIODevice::ReadOnly))
        throw IllegalArgumentException(QString("File %1 can not be opened").arg(sourceFile));

    QDataStream stream(&f);
    stream >> mInstitutionId >> mStudyCourseId;
    while (!stream.atEnd()) {
        int id = 0;
        int grade = 0;
        stream >> id >> grade;
        mGrades.insert(id, grade);
    }

    f.close();
}

int Worksheet::institutionId() const
{
    return mInstitutionId;
}

int Worksheet::studyCourseId() const
{
    return mStudyCourseId;
}

QHash<int,int> Worksheet::grades() const
{
    return QHash<int,int>(mGrades);
}

void Worksheet::toFile(const QString &targetFile) const
{
    QFile f(targetFile);
    if (!f.isWritable() || !f.open(QIODevice::WriteOnly))
        throw IllegalArgumentException(
                QString("File %1 can not be opened").arg(targetFile));

    QDataStream stream(&f);
    stream << mInstitutionId << mStudyCourseId;
    foreach (int k, mGrades.keys()) {
        stream << k << mGrades.value(k);
    }

    f.close();
}
