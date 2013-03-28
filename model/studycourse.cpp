#include "studycourse.h"

StudyCourse::StudyCourse() :
    mName(QString()), mTitle(QString()), mCourses(QList<Course>())
{
}

StudyCourse::StudyCourse(const QString &name) :
    mName(name), mCourses(QList<Course>())
{
}

StudyCourse::StudyCourse(QDomNode *node) throw (IllegalXmlException) :
    StudyCourse()
{
    if (!node)
        throw IllegalXmlException("Given node is null pointer");

    QDomElement element = node->toElement();
    if (!element.hasAttribute("name"))
        throw IllegalXmlException("StudyCourse needs a name");
    if (!element.hasAttribute("title"))
        throw IllegalXmlException("StudyCourse needs a resulting title");
    this->mName = element.attribute("name");

}

const QString& StudyCourse::getName() const
{
    return mName;
}

const QList<Course>& StudyCourse::getCourses() const
{
    return mCourses;
}

const Course& StudyCourse::getCourse(const QString &name) const throw (QString)
{
    int index = 0;
    foreach (Course c, mCourses) {
        if (c.getShortname().compare(name) == 0 ||
                c.getName().compare(name) == 0)
            return mCourses.at(index);
        ++index;
    }

    throw QString("Course with name '%1' not found").arg(name);
}

const Course& StudyCourse::getCourse(int index) const throw (QString)
{
    if (index < 0 || index > mCourses.size())
        throw QString("Index %1 is out of boundary").arg(index);

    return mCourses.at(index);
}

void StudyCourse::addCourse(const Course &c)
{
    mCourses.push_back(c);
}
