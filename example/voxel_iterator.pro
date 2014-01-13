QT += core gui widgets
CONFIG += c++11
TARGET = voxel_iterator
TEMPLATE = app

SOURCES += main.cpp \
           mainwindow.cpp \
           grid_view.cpp \
           ../voxel_iterator.cpp

HEADERS += mainwindow.hpp \
           grid_view.hpp \
           ../voxel_iterator.hpp

FORMS   += mainwindow.ui

INCLUDEPATH += /usr/local/include
