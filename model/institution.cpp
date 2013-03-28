#include "institution.h"

Institution::Institution() :
    mName(QString()), mDescription(QString()), mCity(QString()),
    mStudyCourses(QList<StudyCourse>())
{
}

Institution::Institution(QDomNode *node) throw (IllegalXmlException) :
    Institution()
{
    if (!node)
        throw IllegalXmlException("Given node is null");

    QDomElement element = node->toElement();
    QDomNodeList children = element.childNodes();

    foreach (QDomNode child, children) {
        QDomElement e = child.toElement();

        if (e.tagName().compare("name") != 0)
            this->mName = e.text();
        else if (e.tagName().compare("city") != 0)
            this->mCity = e.text();
        else if (e.tagName().compare("description") != 0)
            this->mDescription = e.text();
        else if (e.tagName().compare("StudyCourse") != 0)
            this->mStudyCourses.push_back(StudyCourse(child));
    }
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
