#include "studycourse.h"
#include <iostream>
StudyCourse::StudyCourse() :
    mName(QString()), mTitle(QString()), mCourses(QList<Course*>())
{
}

StudyCourse::StudyCourse(const QDomNode &node) throw (IllegalXmlException) :
    StudyCourse()
{
    QDomElement element = node.toElement();

    if (!element.hasAttribute("name"))
        throw IllegalXmlException("StudyCourse needs a name");
    if (!element.hasAttribute("title"))
        throw IllegalXmlException("StudyCourse needs a resulting title");

    this->mName = element.attribute("name");
    this->mTitle = element.attribute("title");

    QDomNodeList courses = element.elementsByTagName("Course");
    for (int i = 0; i < courses.size(); ++i)
        this->mCourses.push_back(new Course(courses.at(i)));

    //std::cout << QString("StudyCourse[%1, %2]").arg(mName, mTitle).toStdString() << std::endl;
}

StudyCourse::~StudyCourse()
{
    foreach (Course *c, mCourses)
        delete c;
}

const QString& StudyCourse::getName() const
{
    return mName;
}

const QList<Course *> StudyCourse::getCourses() const
{
    return QList<Course *>(mCourses);
}

const Course* StudyCourse::getCourse(const QString &name) const throw (QString)
{
    int index = 0;
    foreach (Course* c, mCourses) {
        if (c->getShortname().compare(name) == 0 ||
                c->getName().compare(name) == 0)
            return mCourses.at(index);
        ++index;
    }

    throw QString("Course with name '%1' not found").arg(name);
}

const Course* StudyCourse::getCourse(int index) const throw (QString)
{
    if (index < 0 || index > mCourses.size())
        throw QString("Index %1 is out of boundary").arg(index);

    return mCourses.at(index);
}

void StudyCourse::addCourse(Course *c)
{
    mCourses.push_back(c);
}

QString StudyCourse::toString() const
{
    QString res = QString("\tStudyCourse %1 (%2):\n").
            arg(mName, mTitle);

    foreach (Course* c, mCourses) {
        res.append(c->toString());
    }

    res.append("\t< StudyCourse.\n");
    return res;
}
