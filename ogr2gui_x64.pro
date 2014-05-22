# ogr2gui 0.7

TEMPLATE = app
TARGET = ogr2gui
DEPENDPATH += $$PWD/src $$PWD/src/utils $$PWD/include $$PWD/include/ogr
INCLUDEPATH += $$PWD/src $$PWD/src/utils $$PWD/include $$PWD/include/ogr
LIBS += -L$$PWD/lib -lgdal_i_x64

HEADERS += \
    include/App.h \
    include/Dta.h \
    include/Ogr.h \
    include/Inf.h \
    include/utils.h

SOURCES += \
    src/Ogr.cpp \
    src/Inf.cpp \
    src/App.cpp \
    src/main.cpp \
    src/utils/ogr2ogr.cpp \
    src/utils/commonutils.cpp

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
