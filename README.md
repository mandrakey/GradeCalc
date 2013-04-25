# GradeCalc
GradeCals is a simple application to manage and calculate a student's average
grade for a given study course at a given institution.

The program focuses on the european bachelor/master system with ECTS credit
points. You can select a study institution (e.g. some university) and a
study course. Every possible course or module then is displayed in a table
where you can enter your respective grades.

If you set a grade value to **0**, it will be ignored so you have a
current time average and support for optional courses.

The UI state (aka "Worksheet", containing selected institution, study course
and entered grades) can be saved to a file and loaded again later. This way,
you can manage your progress over time.

**Goal:**  
This application was created mainly for two reasons:

1. I wanted to try creating a GUI application with C++ / Qt
2. I thought an excel sheet for calculating grades was tiresome

## Course database
The course database is a simple XML file. The path to that file currently
is hard-coded to "./data.xml". This aspect should be changed some time.  
The course database file has the following structure:

    <GradeCalc>
        <Institution id="0">
            <name>Some university</name>
            <city>Some city</city>
            <description>Some description</description>

            <StudyCourse id="0" name="Some study course name" title="B.Sc.">
                <Course shortname="SC1" ects="10" semester="1">
                    Some Course I
                </Course>
            </StudyCourse>

        </Institution>
   </GradeCalc>

... and so on.

## Building GradeCalc
Currently, only building on Linux (Ubuntu 12.10) has been tested.

### Build on Linux
To build your own copy of GradeCalc, you will need the following prerequisites:

* Qt5 must be installed (developed with Qt 5.0.2). You can get Qt5 from 
    [here](https://qt-project.org/downloads) or install it from your 
    distributions software sources
* You will need the Boost program_options library, which should be available 
    via your package manager. For Ubuntu, the package is called 
    *libboost-program-options1.49-dev* (the version number might differ).

It is recommended to use **Qt Creator** to develop and build the program since 
you just have to load the project file *GradeCalc.pro*.

## License
Copyright (C) 2013 Maurice Bleuel <mandrakey@lavabit.com>

GradeCalc is free software; you can redistribute it and/or modify it 
under the terms of the GNU General Public License as published by the Free 
Software Foundation, either version 3 of the license, or (at your option) 
any later version.

GradeCalc is distributed in the hope that it will be useful, but 
WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTIBILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General 
Public License for more details.

You should have received a copy of the GNU General Public License 
along with GradeCalc. If not, see
[http://www.gnu.org/licenses/](http://www.gnu.org/licenses/).

![GPLv3](http://www.gnu.org/graphics/gplv3-127x51.png)
