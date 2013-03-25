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
    mGrade = grade;
    mValue = mGrade * mEcts;
}
