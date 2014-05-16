# ogr2gui 0.7

TEMPLATE = app
TARGET = ogr2gui
DEPENDPATH += $$PWD/src $$PWD/src/ogr $$PWD/src/tests $$PWD/include $$PWD/include/ogr $$PWD/include/tests
INCLUDEPATH += $$PWD/src $$PWD/src/ogr $$PWD/src/tests $$PWD/include $$PWD/include/ogr $$PWD/include/tests
LIBS += -L$$PWD/lib -lgdal_i

HEADERS += \
    include/App.h \
    include/Dta.h \
    include/Ogr.h \
    include/Inf.h \
    include/tests/TestInf.h \
    include/tests/TestOgr.h

SOURCES += \
    src/Ogr.cpp \
    src/Inf.cpp \
    src/App.cpp \
    src/tests/TestInf.cpp \
    src/tests/TestMain.cpp \
    src/tests/TestOgr.cpp
SOURCES -= src/Main.cpp

CONFIG += c++11
QT += sql widgets testlib
