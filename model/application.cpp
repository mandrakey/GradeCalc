#include "application.h"

QList<Institution*> Application::INSTITUTIONS;

const char *Application::APPNAME = "GradeCalc";
const char *Application::VERSION = "1.0";
const char *Application::COPYRIGHT = "Copyright (C) 2013 Maurice Bleuel";
const char *Application::LICENSE = "GPL or so...";

Application::Application()
{
}

QList<Institution *> Application::institutions() const
{
    return QList<Institution *>(INSTITUTIONS);
}

const QString Application::appName() const
{
    return APPNAME;
}

const QString Application::version() const
{
    return VERSION;
}

const QString Application::copyright() const {
    return COPYRIGHT;
}

const QString Application::license() const {
    return LICENSE;
}

void Application::loadDatabase()
{
    QDomDocument d("data");
    QFile f("./data.xml");

    if (!f.open(QIODevice::ReadOnly)) {
        cerr << "Failed to open file '" << f.fileName().toStdString() << "'" << endl;
        return;
    }

    if (!d.setContent(&f)) {
        cerr << "Failed to load XML content" << endl;
        f.close();
        return;
    }

    // Get root node
    QDomElement root = d.documentElement();
    QDomNodeList l = root.elementsByTagName("Institution");

    for (int i = 0; i < l.size(); ++i) {
        INSTITUTIONS.push_back(new Institution(l.at(i)));
    }
}

void Application::cleanup()
{
    foreach (Institution* i, INSTITUTIONS)
        delete i;
    INSTITUTIONS.clear();
}
