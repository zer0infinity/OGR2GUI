/*****************************************************************************
 *	ogr2gui is an application used to convert and manipulate geospatial
 *	data. It is based on the "OGR Simple Feature Library" from the 
 *	"Geospatial Data Abstraction Library" <http://gdal.org>.
 *
 *	Copyright (c) 2009 Inventis <mailto:developpement@inventis.ca>
 *
 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <http://www.gnu.org/licenses/>
 *****************************************************************************/

/*!
 *	\file Ogr.h
 *	\brief OGR C API
 *	\author Olivier Pilotte [ Inventis ], David Tran [ HSR ]
 *	\version 0.7
 *	\date 30/05/14
 */

#ifndef OGR
#define OGR

#include "sys/types.h"
#include "sys/stat.h"
#include "ogr_api.h"
#include "ogr_srs_api.h"

#include <string>
#include <QStringList>

using std::string;

/*!
 *	\class Ogr
 *	\brief OGR C API
 *	\author Olivier Pilotte
 */

class Ogr
{
	private :

		OGRSFDriverH formatDriver;

		OGRDataSourceH sourceData;
		OGRDataSourceH targetData;

		OGRLayerH squeryLayer;
		OGRLayerH sourceLayer;
		OGRLayerH targetLayer;

		OGRSpatialReferenceH sourceSRS;
		OGRSpatialReferenceH targetSRS;

		OGRFeatureDefnH sourceLayerDefn;
		OGRwkbGeometryType sourceLayerGeom;

		OGRGeometryH sourceGeom;

		string sourceName;
        string layerName;
		string sourceLayerName;
		string targetName;

		string error;

		/*!
		 *	\fn bool Error( OGRErr e, string &s );
		 *	\brief OGR errors
		 *	\param e : OGR error
		 *	\param &s : error text
		 *	\returns true if error
		 */
		bool Error( OGRErr e, string &s );
		
	public:
		
		/*!
		 *	\fn Ogr( void );
		 *	\brief Constructor
		 */
		Ogr( void );

		/*!
		 *	\fn ~Ogr( void );
		 *	\brief Destructor
		 */
		~Ogr( void );

        void OpenWFS(QStringList &fileList);

        bool OpenSource(string filename, string layername, string &epsg, string &query, string &error);

		/*!
		 *	\fn bool OpenSource( string filename, string &epsg = 0, string &query = 0, string &error = 0 );
		 *	\brief Opens source data
         *	\param filename : source filename
		 *	\param &epsg : epsg code
		 *	\param &query : sql query
		 *	\param &error : error text
		 *	\returns true on success
		 */
        bool OpenSource(string filename, string &epsg, string &query, string &error);

		/*!
		 *	\fn bool CloseSource( void );
		 *	\brief Closes source data
		 *	\returns true on success
		 */
		bool CloseSource( void );

		/*!
		 *	\fn bool OpenDriver( string drivername, string error = 0 );
		 *	\brief Opens target driver
		 *	\param drivername : selected driver
		 *	\param error : error text
		 *	\returns true on success
		 */
		bool OpenDriver( string drivername, string error = 0 );

		/*!
		 *	\fn bool OpenTarget( string filename, int projection = 0, bool update = 0 );
		 *	\brief Opens target
		 *	\param filename : target filename
		 *	\param projection : epsg code
		 *	\param update : update mode
		 *	\returns true on success
		*/
		bool OpenTarget( string filename, int projection = 0, bool update = 0 );

		/*!
		 *	\fn bool CloseTarget( void );
		 *	\brief Closes Target
		 *	\returns true on success
		 */
		bool CloseTarget( void );

		/*!
		 *	\fn bool Execute( string query = 0 );
		 *	\brief Execute conversion
		 *	\param query : source sql query
		 *	\returns true on success
		 */
		bool Execute( string = 0 );

		/*!
		 *	\fn bool Prepare( int &nbFeat, string query );
		 *	\brief Prepare data for conversion
		 *	\param nbFeat : number of features
		 *	\param query : source sql query
		 *	\returns true on success
		 */
		bool Prepare( int &nbFeat, string = 0 );

		/*!
		 *	\fn bool Process( void );
		 *	\brief Process a feature
		 *	\returns true on success
		 */
		bool Process( void );
};

#endif
