/*****************************************************************************
 * ogr2gui is an application used to convert and manipulate geospatial
 * data. It is based on the "OGR Simple Feature Library" from the
 * "Geospatial Data Abstraction Library" <http://gdal.org>.
 *
 * Copyright (c) 2014 University of Applied Sciences Rapperswil
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *****************************************************************************/

/*!
 *	\file TestOgr.cpp
 *	\brief Unit Test Ogr
 *	\author David Tran [ HSR ]
 *	\version 0.1
 *	\date 13/06/14
 */

#include "TestOgr.h"

TestOgr::TestOgr() {
    ogr = new Ogr();
}

void TestOgr::testOpenWFS() {
    QString uri = "";
    QStringList fileList;
    bool resVal = ogr->OpenWFS(uri, fileList);
    QCOMPARE(resVal, false);
}

void TestOgr::testOpenSource() {
    string filename = "poly.shp";
    string epsg;
    string query;
    string error;
    bool resVal = ogr->OpenSource(filename, epsg, query, error);
    QCOMPARE(resVal, false);
}

void TestOgr::testCloseSource() {
    bool resVal = ogr->CloseSource();
    QCOMPARE(resVal, false);
}

void TestOgr::testOpenSource2() {
    string path = QDir::toNativeSeparators(QCoreApplication::applicationDirPath() + QDir::separator() + "test" + QDir::separator()).toStdString();
    string filename = "poly.shp";
    string sourcename = path + filename;
    string epsg;
    string query;
    string error;
    bool resVal = ogr->OpenSource(sourcename, epsg, query, error);
    QCOMPARE(resVal, true);
}

void TestOgr::testCloseSource2() {
    bool resVal = ogr->CloseSource();
    QCOMPARE(resVal, true);
}

void TestOgr::testOpenDriver() {
    string drivername = "ESRI Shapefile";
    bool resVal = ogr->OpenDriver("");
    QCOMPARE(resVal, false);
    resVal = ogr->OpenDriver(drivername);
    QCOMPARE(resVal, true);
}
