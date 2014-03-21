# ogr2gui 0.7

#CONFIG   += console
#CONFIG   -= app_bundle

TEMPLATE = app
TARGET = ogr2gui
DEPENDPATH += . inc src $$PWD/cygwin/include
INCLUDEPATH += . inc src $$PWD/cygwin/include

HEADERS += config.h inc/App.h inc/Dta.h inc/Ogr.h inc/Inf.h src/App.cpp src/Ogr.cpp
SOURCES += src/App.cpp src/Ogr.cpp src/Inf.cpp

LIBS += -L$$PWD/cygwin/lib -lgdal -lproj -lpq

CONFIG += static
QT += sql widgets

#QMAKE_CXXFLAGS += "-std=c++11"
#CXXFLAGS="-std=c++11"
