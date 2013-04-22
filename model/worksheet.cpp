#include "worksheet.h"

Worksheet::Worksheet() :
    mInstitutionId(-1), mStudyCourseId(-1), mGrades()
{
    /*// TEST
    mInstitutionId = 1;
    mStudyCourseId = 2;
    mGrades.insert(0, 3.0);
    mGrades.insert(1, 2.3);
    // TEST*/
}

Worksheet::Worksheet(const QString &sourceFile) throw (IllegalArgumentException) :
    mInstitutionId(-1), mStudyCourseId(-1), mGrades()
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

    qDebug() << mInstitutionId << "," << mStudyCourseId;
    qDebug() << mGrades;
}
