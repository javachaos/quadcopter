#-------------------------------------------------
#
# Project created by QtCreator 2016-03-10T21:27:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtquadview
TEMPLATE = app


SOURCES += main.cpp\
        quadview.cpp \
    ../SocketIO.cpp

HEADERS  += quadview.h

FORMS    += quadview.ui
