#-------------------------------------------------
#
# Project created by QtCreator 2013-03-25T21:12:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GradeCalc
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    institution.cpp \
    course.cpp \
    studycourse.cpp

HEADERS  += mainwindow.h \
    institution.h \
    course.h \
    studycourse.h

FORMS    += mainwindow.ui
