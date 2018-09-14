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
    can.cpp \
    rankingui.cpp \
    game1.cpp \
    game2.cpp

HEADERS  += mainwindow.h \
    visual.h \
    button.h \
    can.h \
    rankingui.h \
    game1.h \
    game2.h

FORMS    += mainwindow.ui
