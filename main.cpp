#include <QApplication>
#include <QtXml/QDomDocument>
#include <QFile>
#include <QList>
#include <QString>

#include <boost/program_options.hpp>

#include <iostream>

#include "mainwindow.h"
#include "programoptions.h"
#include "model/course.h"
#include "model/studycourse.h"
#include "model/institution.h"

using std::cout;
using std::cerr;
using std::endl;
using std::string;

namespace po = boost::program_options;

void test();

int main(int argc, char *argv[])
{
    ProgramOptions po(argc, argv);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();

    //test();
}

void test()
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
    cout << "Read file..." << endl;
    QDomElement root = d.documentElement();
    QList<Institution> institutions;
    QDomNodeList l = root.elementsByTagName("Institution");

    for (int i = 0; i < l.size(); ++i) {
        institutions.push_back(Institution(l.at(i)));
    }

    for (int i = 0; i < institutions.size(); ++i) {
        cout << "# Inst: " << i << endl;
        cout << institutions.at(i).toString().toStdString() << endl;
    }
}
