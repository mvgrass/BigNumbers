#-------------------------------------------------
#
# Project created by QtCreator 2017-03-13T20:39:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BigNumbers
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    rational.cpp \
    polinom.cpp \
    natural.cpp \
    integer.cpp \
    reference.cpp

HEADERS  += mainwindow.h \
    rational.h \
    polinom.h \
    natural.h \
    integer.h \
    reference.h

FORMS    += mainwindow.ui \
    reference.ui
