#ifndef APPLICATION_H
#define APPLICATION_H

#include <QList>
#include <QFile>
#include <QTextStream>

#include <iostream>
using std::cerr;
using std::endl;

#include "institution.h"

class Application
{
public:
    Application();

    QList<Institution*> institutions() const;
    const QString appName() const;
    const QString version() const;
    const QString copyright() const;
    const QString license() const;

    void loadDatabase();
    void cleanup();

private:
    static bool INITIALIZED;
    static QList<Institution *> INSTITUTIONS;

    static const char *APPNAME;
    static const char *VERSION;
    static const char *COPYRIGHT;
    static QString LICENSE;
};

#endif // APPLICATION_H
