#include "application.h"

QList<Institution*> Application::INSTITUTIONS;

Application::Application()
{
}

QList<Institution *>& Application::institutions()
{
    return INSTITUTIONS;
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
