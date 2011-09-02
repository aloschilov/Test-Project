#-------------------------------------------------
#
# Project created by QtCreator 2011-08-03T15:35:11
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = 3d_cloud_crop
TEMPLATE = app

RESOURCES = 3d_cloud_crop.qrc


SOURCES += main.cpp\
        mainwindow.cpp \
    ComputerGraphics/matrix.cpp \
    ComputerGraphics/linalg.cpp \
    glextensions.cpp \
    gloperationsthread.cpp \
    glwidget.cpp \
    scale.cpp \
    scalewidget.cpp \
    colormapradiobutton.cpp \
    scaleselectionwidget.cpp

HEADERS  += mainwindow.h \
    ComputerGraphics/matrix.h \
    ComputerGraphics/linalg.h \
    glextensions.h \
    gloperationsthread.h \
    glwidget.h \
    scale.h \
    scalewidget.h \
    colormapradiobutton.h \
    scaleselectionwidget.h
