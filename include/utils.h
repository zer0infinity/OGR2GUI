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

/**
 *	\file utils.h
 *	\brief Utilities
 *	\author David Tran [HSR]
 *	\version 0.7
 */

#ifndef UTIL_H
#define UTIL_H

    /**
     *	\fn int ogr2ogr(int nArgc, char ** papszArgv)
     *	\brief ogr2ogr command line
     *  \param nArgc : arguments count
     *  \param  papszArgv : arguments
     */
int ogr2ogr(int nArgc, char ** papszArgv);

#endif
