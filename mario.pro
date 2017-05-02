#-------------------------------------------------
#
# Project created by QtCreator 2017-03-20T17:49:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mario
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myscene.cpp \
    update.cpp \
    degat.cpp \
    key_event_release.cpp

HEADERS  += mainwindow.h \
    myscene.h

FORMS    += mainwindow.ui

DISTFILES += \
    pas_fait \
    coeur.png \
    ../Bureau/tails.png

RESOURCES += \
    ressources.qrc
