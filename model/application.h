#ifndef APPLICATION_H
#define APPLICATION_H

#include <QList>
#include <QFile>

#include <iostream>
using std::cerr;
using std::endl;

#include "institution.h"

class Application
{
public:
    Application();

    QList<Institution*> &institutions();

    void loadDatabase();

private:
    static QList<Institution*> INSTITUTIONS;
};

#endif // APPLICATION_H
