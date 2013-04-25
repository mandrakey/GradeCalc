/* Copyright (C) 2013  Maurice Bleuel (mandrakey@lavabit.com)
 *
 * This file is part of GradeCalc.
 *
 * GradeCalc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GradeCalc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GradeCalc.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
  * Application entry point.
  * Initializes ProgramOptions and shows MainWindow.
  * @file main.cpp
  */

#include <QApplication>
#include <QtXml/QDomDocument>
#include <QFile>
#include <QList>
#include <QString>
#include <QTranslator>

#include <boost/program_options.hpp>

#include <iostream>

#include "view/mainwindow.h"
#include "qprogramoptions.h"
#include "model/course.h"
#include "model/studycourse.h"
#include "model/institution.h"

using std::cout;
using std::cerr;
using std::endl;
using std::string;

const bool TRYOUT_MODE = false;

void initProgramOptions()
{
    QProgramOptions po;

    // Create Options
    QProgramOptions::Option helpOption("help", "?", "display this help");
    QProgramOptions::Option worksheetOption(QVariant::String, "worksheet", "w",
                                           "worksheet to load on startup",
                                           QVariant(), true, 1);

    po << helpOption << worksheetOption;
}

int main(int argc, char *argv[])
{
    initProgramOptions();
    QProgramOptions po;
    po.parse(argc, argv);

    if (po.recognized("help")) {
        po.printHelp();
        return 1;
    }

    QApplication a(argc, argv);

    QTranslator translator;
    translator.load("en_US");
    a.installTranslator(&translator);

    MainWindow w;
    w.show();

    return a.exec();
}
