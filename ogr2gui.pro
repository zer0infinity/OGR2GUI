# ogr2gui 0.7

TEMPLATE = app
TARGET = ogr2gui
DEPENDPATH += . inc src $$PWD/include
INCLUDEPATH += . inc src $$PWD/include
LIBS += -L$$PWD/lib/ -lgdal -lproj -lpq

HEADERS += config.h \
    inc/App.h \
    inc/Dta.h \
    inc/Ogr.h \
    inc/Inf.h

SOURCES += \
    src/Ogr.cpp \
    src/Inf.cpp \
    src/App.cpp

CONFIG += -static
QT += sql widgets
