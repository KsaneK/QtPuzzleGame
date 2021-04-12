#-------------------------------------------------
#
# Project created by QtCreator 2021-03-24T22:08:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = puzzle
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    board.cpp \
    tile.cpp \
    gamemanager.cpp \
    tilewidget.cpp \
    player.cpp \
    pixmaptile.cpp \
    dfssolver.cpp \
    iddfssolver.cpp \
    idastarsolver.cpp

HEADERS += \
        mainwindow.h \
    board.h \
    tile.h \
    gamemanager.h \
    tilewidget.h \
    player.h \
    pixmaptile.h \
    simplevector.h \
    solver.h \
    dfssolver.h \
    iddfssolver.h \
    idastarsolver.h

FORMS += \
        mainwindow.ui
