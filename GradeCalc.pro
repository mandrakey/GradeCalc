#-------------------------------------------------
#
# Project created by QtCreator 2013-03-25T21:12:23
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11

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
    exceptions/uninitializedexception.cc \
    model/gradetablemodel.cpp \
    exceptions/nullpointerexception.cpp

HEADERS  += mainwindow.h \
    model/studycourse.h \
    model/institution.h \
    model/course.h \
    exceptions/illegalxmlexception.h \
    exceptions/exception.h \
    programoptions.h \
    exceptions/uninitializedexception.h \
    model/gradetablemodel.h \
    exceptions/nullpointerexception.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    data.xml
