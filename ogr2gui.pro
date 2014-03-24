# ogr2gui 0.7

TEMPLATE = app
TARGET = ogr2gui
DEPENDPATH += . inc src \
#            $$PWD/cygwin/include
            $$PWD/mingw/include
INCLUDEPATH += . inc src \
#            $$PWD/cygwin/include
            $$PWD/mingw/include
#LIBS += -L$$PWD/cygwin/lib -lgdal -lproj -lpq
LIBS += -L$$PWD/mingw/lib -lgdal -lproj -lpq

HEADERS += config.h \
           inc/App.h \
           inc/Dta.h \
#           inc/Ogr.h \
           inc/Inf.h

SOURCES += src/App.cpp \
#           src/Ogr.cpp \
           src/Inf.cpp

CONFIG += static
QT += sql widgets

#QMAKE_CXXFLAGS += "-std=c++11"
#CXXFLAGS="-std=c++11"
