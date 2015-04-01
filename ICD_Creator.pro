#-------------------------------------------------
#
# Project created by QtCreator 2015-03-23T15:20:08
#
#-------------------------------------------------

QT       += core gui
QT       += core xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ICD_Creator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    domitem.cpp \
    dommodel.cpp

HEADERS  += mainwindow.h \
    domitem.h \
    dommodel.h
