#-------------------------------------------------
#
# Project created by QtCreator 2015-04-03T18:08:42
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = untitled1
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += c++11
LIBS += -L/usr/lib64 -larmadillo
TEMPLATE = app
INCLUDEPATH += math

SOURCES += main.cpp \
    math/runge_stoch4.cpp

HEADERS += \
    math/runge_stoch4.hpp \
    math/vect.hpp
