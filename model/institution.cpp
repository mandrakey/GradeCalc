#include "institution.h"
#include <iostream>
Institution::Institution() :
    mName(QString()), mDescription(QString()), mCity(QString()),
    mStudyCourses(QList<StudyCourse *>())
{
}

Institution::Institution(const QDomNode &node) throw (IllegalXmlException) :
    Institution()
{
    QDomElement element = node.toElement();
    QDomNodeList children = element.childNodes();

    for (int i = 0; i < children.size(); ++i) {
        QDomElement e = children.at(i).toElement();

        if (e.tagName().compare("name") == 0)
            this->mName = e.text();
        else if (e.tagName().compare("city") == 0)
            this->mCity = e.text();
        else if (e.tagName().compare("description") == 0)
            this->mDescription = e.text();
        else if (e.tagName().compare("StudyCourse") == 0)
            this->mStudyCourses.push_back(new StudyCourse(children.at(i)));
    }
    /*std::cout << QString("Institution[%1, %2, %3]").arg(mName, mCity, mDescription).
                 toStdString() << std::endl;*/
}

Institution::~Institution()
{
    foreach (StudyCourse *s, mStudyCourses)
        delete s;
}

const QString& Institution::getName() const
{
    return mName;
}

const QString& Institution::getDescription() const
{
    return mDescription;
}

const QString& Institution::getCity() const
{
    return mCity;
}

QList<StudyCourse *> Institution::getStudyCourses() const
{
    return QList<StudyCourse *>(mStudyCourses);
}

QString Institution::toString() const
{
    QString res = QString("> Institution %1 in %2 (%3):\n").
            arg(mName, mCity, mDescription);

    foreach (StudyCourse *s, mStudyCourses) {
        res.append(s->toString());
    }

    res.append("< Institution.\n");
    return res;
}
