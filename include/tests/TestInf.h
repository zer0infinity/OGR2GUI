/*****************************************************************************
 * ogr2gui is an application used to convert and manipulate geospatial
 * data. It is based on the "OGR Simple Feature Library" from the
 * "Geospatial Data Abstraction Library" <http://gdal.org>.
 *
 * Copyright (c) 2014 Faculty of Computer Science,
 * University of Applied Sciences Rapperswil (HSR),
 * 8600 Rapperswil, Switzerland
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
 *	\file TestInf.h
 *	\brief Qt Test Inf
 *	\author David Tran [ HSR ]
 *	\version 0.1
 *	\date 13/06/14
 */

#ifndef TESTINF_H
#define TESTINF_H

#include <QtTest/QtTest>
#include "Inf.h"

class TestInf: public QObject
{
    Q_OBJECT
public:
    TestInf();
    Inf *inf;
private slots:
    void testConnection();
    void testSelectedTables();
};

#endif // TESTINF_H
