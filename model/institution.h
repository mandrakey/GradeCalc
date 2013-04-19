#ifndef INSTITUTION_H
#define INSTITUTION_H

#include <QString>
#include <QList>
#include <QtXml/QDomNode>
#include <QtXml/QDomElement>
#include <QtXml/QDomNodeList>

#include "exceptions/illegalxmlexception.h"
#include "studycourse.h"

/**
 * Holds information about a stuy/course institution.
 * @author Maurice Bleuel <mbleuel@bleuelmedia.com>
 */
class Institution
{
public:
    Institution();
    Institution(const QDomNode &node) throw (IllegalXmlException);
    ~Institution();

    // Getter / Setter
    const QString& getName() const;
    const QString& getDescription() const;
    const QString& getCity() const;
    QList<StudyCourse *> getStudyCourses() const;

    QString toString() const;

private:
    QString mName;
    QString mDescription;
    QString mCity;
    QList<StudyCourse*> mStudyCourses;
};

#endif // INSTITUTION_H
