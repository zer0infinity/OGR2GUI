#/*****************************************************************************
# * ogr2gui is an application used to convert and manipulate geospatial
# * data. It is based on the "OGR Simple Feature Library" from the
# * "Geospatial Data Abstraction Library" <http://gdal.org>.
# *
# * Copyright (c) 2014 Faculty of Computer Science,
# * University of Applied Sciences Rapperswil (HSR),
# * 8600 Rapperswil, Switzerland
# *
# * This program is free software: you can redistribute it and/or modify
# * it under the terms of the GNU General Public License as published by
# * the Free Software Foundation, either version 3 of the License, or
# * (at your option) any later version.
# *
# * This program is distributed in the hope that it will be useful,
# * but WITHOUT ANY WARRANTY; without even the implied warranty of
# * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# * GNU General Public License for more details.
# *
# * You should have received a copy of the GNU General Public License
# * along with this program.  If not, see <http://www.gnu.org/licenses/>.
# *****************************************************************************/
# ogr2gui 0.7

TEMPLATE = app
TARGET = ogr2gui_test
INCLUDEPATH += $$PWD/include $$PWD/include/ogr $$PWD/include/tests
#DESTDIR += $$PWD/bin
LIBS += -L$$PWD/lib -lgdal_i

HEADERS += \
    include/App.h \
    include/Dta.h \
    include/Ogr.h \
    include/Inf.h \
    include/utils.h \
    include/wfsConnect.h \
    include/ogr2ogrThread.h \
    include/tests/TestInf.h \
    include/tests/TestOgr.h

SOURCES += \
    src/Ogr.cpp \
    src/Inf.cpp \
    src/App.cpp \
    src/utils/ogr2ogr.cpp \
    src/utils/commonutils.cpp \
    src/wfsConnect.cpp \
    src/ogr2ogrThread.cpp \
    src/tests/TestInf.cpp \
    src/tests/TestMain.cpp \
    src/tests/TestOgr.cpp
SOURCES -= src/main.cpp

CONFIG += c++11
QT += sql widgets testlib
