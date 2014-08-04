/*****************************************************************************
 * OGR2GUI is an application used to convert and manipulate geospatial
 * data. It is based on the "OGR Simple Feature Library" from the
 * "Geospatial Data Abstraction Library" <http://gdal.org>.
 *
 * Copyright (c) 2014 Faculty of Computer Science,
 * University of Applied Sciences Rapperswil (HSR),
 * 8640 Rapperswil, Switzerland
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
 *	\file TestOgr.h
 *	\brief Qt Test Ogr
 *	\author David Tran [ HSR ]
 *	\version 0.1
 *	\date 13/06/14
 */

#ifndef TESTOGR_H
#define TESTOGR_H

#include <QtTest>
#include "Ogr.h"

class TestOgr: public QObject {
    Q_OBJECT
public:
    TestOgr();
    Ogr *ogr;
private slots:
    void testOpenWFS();
    void testOpenSourceFalseInput();
    void testCloseSourceFalseInput();
    void testOpenSourceFile();
    void testOpenSourceSQLite();
    void testCloseSource();
    void testOpenDriverFalseInput();
    void testOpenDriverESRIShapefile();
    void testOpenDriverSQLite();
    void testLayerNames();
    void testLayerCount();
    void testFeatureCount();
    void testSQLQueryFalseQuery();
    void testSQLQuery();
private:
    string path;
    string filename;
    string sqlitedb;
    OGRDataSourceH sourceData;
    OGRLayerH sourceLayer;
    OGRFeatureDefnH sourceLayerDefn;
    string sourceLayerName;
    void setSource(string sourcename);
};

#endif // TESTOGR_H
