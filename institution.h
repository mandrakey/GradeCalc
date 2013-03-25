#ifndef INSTITUTION_H
#define INSTITUTION_H

#include <QString>

/**
 * Holds information about a stuy/course institution.
 * @author Maurice Bleuel <mbleuel@bleuelmedia.com>
 */
class Institution
{
public:
    Institution();

    /**
     * Construct institution from a given XML file.
     * @param filename XML file to load
     * @throws QString
     */
    explicit Institution(const char* filename) throw (QString);

    // Getter / Setter
    const QString& getName() const;
    const QString& getDescription() const;
    const QString& getCity() const;

private:
    QString mName;
    QString mDescription;
    QString mCity;
};

#endif // INSTITUTION_H
