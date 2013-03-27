#include "institution.h"

Institution::Institution() :
    mName(QString()), mDescription(QString()), mCity(QString())
{
}

Institution::Institution(const char *filename) throw (QString) :
    mName(""), mDescription(""), mCity("")
{
    Q_UNIMPLEMENTED();
    Q_UNUSED(filename);
    throw QString("Not implemented");
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
