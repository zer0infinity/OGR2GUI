# ogr2gui 0.7

TEMPLATE = app
TARGET = ogr2gui
DEPENDPATH += . inc src
INCLUDEPATH += . inc src /usr/local/include C:\OSGeo4W64\include

# Input
HEADERS += config.h \
	   inc/App.h \
           inc/Dta.h \
           inc/Ogr.h \
	   inc/Inf.h \
           src/App.cpp \
           src/Ogr.cpp

SOURCES += src/App.cpp \
	   src/Ogr.cpp \
	   src/Inf.cpp

LIBS += -L/usr/local/lib -lgdal -lproj -lpq

CONFIG += static

QT += gui
QT += sql

QMAKE_CXXFLAGS += "-std=c++11"
CXXFLAGS="-std=c++11"
