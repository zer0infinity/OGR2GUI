# ogr2gui 0.7

TEMPLATE = app
TARGET = ogr2gui
DEPENDPATH += $$PWD/src $$PWD/include $$PWD/include/msvc-x64
INCLUDEPATH += $$PWD/src $$PWD/include $$PWD/include/msvc-x64
LIBS += -L$$PWD/lib/msvc-x64 -lgdal_i

HEADERS += \
    include/App.h \
    include/Dta.h \
    include/Ogr.h \
    include/Inf.h

SOURCES += \
    src/Ogr.cpp \
    src/Inf.cpp \
    src/App.cpp \
    src/main.cpp

CONFIG += c++11
QT += sql widgets

static {
    CONFIG += static
    DEFINES += STATIC
    win32: TARGET = $$join(TARGET,,,msvc2010-x64s)
}

CONFIG(debug, debug|release) {
     win32: TARGET = $$join(TARGET,,,msvc2010-x64d)
}
