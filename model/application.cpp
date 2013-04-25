#include "application.h"

bool Application::INITIALIZED = false;
QList<Institution*> Application::INSTITUTIONS;

const char *Application::APPNAME = "GradeCalc";
const char *Application::VERSION = "1.0";
const char *Application::COPYRIGHT = "Copyright (C) 2013 Maurice Bleuel";
QString Application::LICENSE = QString();

Application::Application()
{
    if (INITIALIZED)
        return;
    INITIALIZED = true;

    QFile licenseFile("./COPYING");
    if (!licenseFile.exists()) {
        cerr << "Warning: License file is not present.";
        LICENSE = "License file is not present. Illegal use.";
        return;
    }

    if (!licenseFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        cerr << "Warning: License file could not be opened.";
        LICENSE = "License file coult not be opened.";
        return;
    }

    QTextStream in(&licenseFile);
    LICENSE = in.readAll();
}

QList<Institution *> Application::institutions() const
{
    return QList<Institution *>(INSTITUTIONS);
}

const QString Application::appName() const
{
    return QString(APPNAME);
}

const QString Application::version() const
{
    return QString(VERSION);
}

const QString Application::copyright() const {
    return QString(COPYRIGHT);
}

const QString Application::license() const {
    return QString(LICENSE);
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
