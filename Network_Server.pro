#-------------------------------------------------
#
# Project created by QtCreator 2016-03-05T23:55:34
#
#-------------------------------------------------

QT       += core gui\
         network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Network_Server
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    servers.cpp \
    sendthread.cpp

HEADERS  += mainwindow.h \
    servers.h \
    sendthread.h

FORMS    += mainwindow.ui

DISTFILES += \
    Server
