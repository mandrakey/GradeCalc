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
    model/studycourse.cpp \
    model/institution.cpp \
    model/course.cpp \
    exceptions/illegalxmlexception.cpp \
    exceptions/exception.cpp \
    exceptions/uninitializedexception.cc \
    #model/gradetablemodel.cpp \
    exceptions/nullpointerexception.cpp \
    view/mainwindow.cpp \
    model/application.cpp \
    model/worksheet.cpp \
    exceptions/illegalargumentexception.cpp \
    view/aboutwindow.cpp \
    qprogramoptions.cpp

HEADERS  += \
    model/studycourse.h \
    model/institution.h \
    model/course.h \
    exceptions/illegalxmlexception.h \
    exceptions/exception.h \
    exceptions/uninitializedexception.h \
    #model/gradetablemodel.h \
    exceptions/nullpointerexception.h \
    view/mainwindow.h \
    model/application.h \
    model/worksheet.h \
    exceptions/illegalargumentexception.h \
    view/aboutwindow.h \
    qprogramoptions.h

FORMS    +=

OTHER_FILES += \
    data.xml \
    en_US.ts \
    README.md

TRANSLATIONS = en_US.ts
