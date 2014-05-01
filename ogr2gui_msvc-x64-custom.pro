# ogr2gui 0.7

TEMPLATE = app
TARGET = ogr2gui
DEPENDPATH += $$PWD/src $$PWD/include $$PWD/include/msvc-x64-custom
INCLUDEPATH += $$PWD/src $$PWD/include $$PWD/include/msvc-x64-custom
LIBS += -L$$PWD/lib/msvc-x64-custom -lgdal_i

HEADERS += \
    include/App.h \
    include/Dta.h \
    include/Ogr.h \
    include/Inf.h

SOURCES += \
    src/Ogr.cpp \
    src/Inf.cpp \
    src/App.cpp

CONFIG += c++11
QT += sql widgets

static {
    CONFIG += static
    DEFINES += STATIC
    win32: TARGET = $$join(TARGET,,,msvc2010-x64-customs) #this adds an s in the end, so you can seperate static build from non static build
}

CONFIG(debug, debug|release) {
     win32: TARGET = $$join(TARGET,,,msvc2010-x64-customd)
}
