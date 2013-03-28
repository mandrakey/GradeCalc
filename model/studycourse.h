#ifndef STUDYCOURSE_H
#define STUDYCOURSE_H

#include <QtXml/QDomNode>
#include <QtXml/QDomElement>
#include <QtXml/QDomNodeList>
#include <QList>

#include "course.h"
#include "exceptions/illegalxmlexception.h"

class StudyCourse
{
public:
    StudyCourse();
    StudyCourse(const QDomNode &node) throw (IllegalXmlException);
    explicit StudyCourse(const QString& name);

    // Getter / Setter
    const QString& getName() const;
    const QList<Course>& getCourses() const;

    /**
     * Retrieve a specific course by it's name.
     * @param name Name of the course to search for
     * @return Reference to the course being searched
     */
    const Course& getCourse(const QString& name) const throw (QString);

    /**
     * Retrieve a specific course by it's list index.
     * @param index List index, starting with 0
     * @return Reference to the requested course
     */
    const Course& getCourse(int index) const throw (QString);

    QString toString() const;

    void addCourse(const Course& c);

private:
    QString mName;
    QString mTitle;
    QList<Course> mCourses;
};

#endif // STUDYCOURSE_H
