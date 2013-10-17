#-------------------------------------------------
#
# Project created by QtCreator 2013-03-30T19:17:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = map_gen
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    mgscene.cpp \
    mtailgenerator.cpp \
    msettingsdialog.cpp \
    matrixer.cpp

HEADERS  += mainwindow.h \
    mgscene.h \
    mtailgenerator.h \
    msettingsdialog.h \
    mdefault.h \
    tail.h \
    matrixer.h

FORMS    += mainwindow.ui \
    msettingsdialog.ui
