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
    meshviewwidget.cpp \
    loadmeshthread.cpp \
    ComputerGraphics/matrix.cpp \
    ComputerGraphics/linalg.cpp \
    glextensions.cpp

HEADERS  += mainwindow.h \
    meshviewwidget.h \
    loadmeshthread.h \
    ComputerGraphics/matrix.h \
    ComputerGraphics/linalg.h \
    glextensions.h
