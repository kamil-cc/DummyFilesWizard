#-------------------------------------------------
#
# Project created by QtCreator 2019-08-24T18:52:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DummyFilesWizard
TEMPLATE = app


SOURCES += main.cpp\
        dummywizard.cpp \
    templates/model.cpp \
    templates/view.cpp \
    templates/controller.cpp \
    text/statictext.cpp \
    console/console.cpp \
    settings/appsettings.cpp \
    settings/fileparser.cpp \
    settings/settingsbase.cpp \
    settings/cmdparser.cpp

HEADERS  += dummywizard.h \
    templates/model.h \
    templates/view.h \
    templates/controller.h \
    text/statictext.h \
    console/console.h \
    settings/appsettings.h \
    settings/fileparser.h \
    settings/settingsbase.h \
    settings/cmdparser.h

FORMS    += dummywizard.ui

RESOURCES += \
    resources/resources.qrc
