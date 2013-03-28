#-------------------------------------------------
#
# Project created by QtCreator 2013-03-25T21:12:23
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GradeCalc
TEMPLATE = app

LIBS += -L/usr/local/lib
LIBS += -lboost_program_options

SOURCES += main.cpp\
        mainwindow.cpp \
    model/studycourse.cpp \
    model/institution.cpp \
    model/course.cpp \
    exceptions/illegalxmlexception.cpp \
    exceptions/exception.cpp \
    programoptions.cpp \
    exceptions/uninitializedexception.cc

HEADERS  += mainwindow.h \
    model/studycourse.h \
    model/institution.h \
    model/course.h \
    exceptions/illegalxmlexception.h \
    exceptions/exception.h \
    programoptions.h \
    exceptions/uninitializedexception.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    data.xml
