#include "mainwindow.h"
#include <QApplication>

#include "course.h"
#include "studycourse.h"

#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
