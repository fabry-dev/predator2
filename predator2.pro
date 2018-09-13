#-------------------------------------------------
#
# Project created by QtCreator 2018-09-12T21:52:20
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++14
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = predator2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    visual.cpp \
    button.cpp \
    game.cpp

HEADERS  += mainwindow.h \
    visual.h \
    button.h \
    game.h

FORMS    += mainwindow.ui
