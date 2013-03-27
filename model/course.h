#ifndef COURSE_H
#define COURSE_H

#include <QString>

class Course
{
public:
    Course();
    explicit Course(int semester, const QString &name, const QString &shortname,
                    double ects);

    // Getter / Setter
    int getSemester() const;
    const QString& getName() const;
    const QString& getShortname() const;
    double getEcts() const;
    double getGrade() const;
    double getValue() const;

    void setGrade(double grade) throw (QString);

    // Methods
    /**
     * Retrieve value while setting grade at the same time.
     * @param grade The grade to set for calculation
     * @return Calculated value from grade and ects
     */
    double getValue(double grade) throw (QString);

private:
    int mSemester;
    QString mName;
    QString mShortname;
    double mEcts;
    double mGrade;
    double mValue;
};

#endif // COURSE_H
