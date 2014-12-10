#/*****************************************************************************
# * OGR2GUI is an application used to convert and manipulate geospatial
# * data. It is based on the "OGR Simple Feature Library" from the
# * "Geospatial Data Abstraction Library" <http://gdal.org>.
# *
# * Copyright (c) 2014 Faculty of Computer Science,
# * University of Applied Sciences Rapperswil (HSR),
# * 8640 Rapperswil, Switzerland
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

TEMPLATE = app
TARGET = OGR2GUI_test
INCLUDEPATH += $$PWD/include $$PWD/include/ogr $$PWD/include/tests
LIBS += -L$$PWD/lib -lgdal_i
#DESTDIR += $$PWD/bin

HEADERS += \
    include/app.h \
    include/ogr.h \
    include/dbConnect.h \
    include/utils.h \
    include/webServiceConnect.h \
    include/ogr2ogrThread.h \
    include/i18n.h \
    include/settings.h \
    include/tests/testDBConnect.h \
    include/tests/testOgr.h

SOURCES += \
    src/ogr.cpp \
    src/dbConnect.cpp \
    src/app.cpp \
    src/webServiceConnect.cpp \
    src/ogr2ogrThread.cpp \
    src/i18n.cpp \
    src/settings.cpp \
    src/utils/ogr2ogr.cpp \
    src/utils/commonutils.cpp \
    src/tests/testDBConnect.cpp \
    src/tests/testMain.cpp \
    src/tests/testOgr.cpp
SOURCES -= src/main.cpp

CONFIG += c++11
QT += sql widgets testlib
