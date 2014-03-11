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
 *	\file Ogr.cpp
 *	\brief OGR C API
 *	\author Olivier Pilotte [ Inventis ]
 *	\version 0.6
 *	\date 27/10/09
 */

#include "../inc/Ogr.h"

Ogr::Ogr( void )
{
	OGRRegisterAll();
}

Ogr::~Ogr( void )
{

}

bool Ogr::OpenSource( string filename, string &epsg, string &query, string &error )
{
	sourceSRS = NULL;

	sourceName = filename;

	sourceData = OGROpen( sourceName.c_str(), 0, NULL );

	if( sourceData != NULL )
	{
		sourceLayer = OGR_DS_GetLayer( sourceData, 0 );

		if( sourceLayer != NULL )
		{
			sourceLayerDefn = OGR_L_GetLayerDefn( sourceLayer );

			sourceLayerName = OGR_FD_GetName( sourceLayerDefn );

			sourceLayerGeom = OGR_FD_GetGeomType( sourceLayerDefn );

			sourceGeom = OGR_L_GetSpatialFilter( sourceLayer );

			sourceSRS = OGR_L_GetSpatialRef( sourceLayer );

			if( sourceSRS != NULL && ! Error( OSRAutoIdentifyEPSG( sourceSRS ), error ) )
			{
				epsg = OSRGetAttrValue( sourceSRS, "AUTHORITY", 1 );
			}
			else
			{
				error = "unable to open source spatial reference";
			}

			query = "SELECT * FROM " + sourceLayerName;
		}
		else
		{
			error = "unable to open source layer";

			return false;
		}
	}
	else
	{
		error = "unable to open source data";

		return false;
	}

	return true;
}

bool Ogr::CloseSource( void )
{
	if( sourceData != NULL )
	{
		OGR_DS_Destroy( sourceData );
	}
	else
	{
		return false;
	}

	return true;
}

bool Ogr::OpenDriver( string drivername, string error )
{
	formatDriver = OGRGetDriverByName( drivername.c_str() );

	if( formatDriver == NULL )
	{
		error = "unable to find driver";

		return false;
	}

	return true;
}

bool Ogr::OpenTarget( string filename, int projection, bool update )
{
	struct stat fileInfo;

	targetSRS = NULL;
	
	targetName = filename;

	if( projection > 0 )
	{
		targetSRS = OSRNewSpatialReference( NULL );

		if( Error( OSRImportFromEPSG( targetSRS, projection ), error ) )
		{
			error.insert( 0, "unable to create spatial reference : " );
		}
	}

	if( update )
	{
		if( stat( targetName.c_str(), &fileInfo ) == 0 )
		{
			targetData = OGR_Dr_Open( formatDriver, targetName.c_str(), 1 );
		}
		else
		{
			error = "file doesn't exist";

			return false;
		}
	}
	else
	{	
		if( stat( targetName.c_str(), &fileInfo ) == 0 )
		{
			if( remove( targetName.c_str() ) != 0 )
			{
				error = "unable to delete source data";
			}
		}

		targetData = OGR_Dr_CreateDataSource( formatDriver, targetName.c_str(), 0 );		
	}

	if( targetData != NULL )
	{
		if( update )
		{
			targetLayer = OGR_DS_GetLayer( targetData, 0 );
		}
		else
		{
			if( targetSRS != NULL )
			{
				targetLayer = OGR_DS_CreateLayer( targetData, sourceLayerName.c_str(), targetSRS, sourceLayerGeom, NULL );
			}
			else
			{
				targetLayer = OGR_DS_CreateLayer( targetData, sourceLayerName.c_str(), sourceSRS, sourceLayerGeom, NULL );
			}
		}
	}
	else
	{
		error = "unable to create target data";

		return false;
	}

	return true;
}

bool Ogr::CloseTarget( void )
{
	if( targetData != NULL )
	{
		OGR_DS_Destroy( targetData );
	}
	else
	{
		return false;
	}

	return true;
}

bool Ogr::Execute( string query )
{
	int featuresCount = 0;

	if( Prepare( featuresCount, query ) )
	{
		while( Process() ) ;

		CloseTarget();
		
		CloseSource();
	}
	else
	{
		return false;
	}

	return true;
}

bool Ogr::Prepare( int &featuresCount, string query )
{
	OGRFeatureDefnH featDefn = OGR_L_GetLayerDefn( sourceLayer );

	for( int i = 0; i < OGR_FD_GetFieldCount( sourceLayerDefn ); i ++ )
	{
		OGRFieldDefnH field = OGR_FD_GetFieldDefn( featDefn, i );

		if( Error( OGR_L_CreateField( targetLayer, field, 0 ), error ) )
		{
			return false;
		}
	}

	if( query.size() > 0 )
	{
		OGRLayerH squeryLayer = OGR_DS_ExecuteSQL( sourceData, query.c_str(), NULL, "" );

		if( squeryLayer != NULL )
		{
			sourceLayer = squeryLayer;
		}
	}

	OGR_L_ResetReading( sourceLayer );

	featuresCount = OGR_L_GetFeatureCount( sourceLayer, 1 );

	return true;
}

bool Ogr::Process( void )
{
	OGRFeatureH feature;

	if( ( ( feature = OGR_L_GetNextFeature( sourceLayer ) ) != NULL ) )
	{
		if( targetSRS )
		{
			Error( OGR_G_TransformTo( OGR_F_GetGeometryRef( feature ), targetSRS ), error );
		}

		Error( OGR_L_CreateFeature( targetLayer, feature ), error );

		OGR_F_Destroy( feature );
	}
	else
	{
		return false;
	}

	return true;
}

bool Ogr::Error( OGRErr code, string &type )
{
	switch( code )
	{
		case OGRERR_NONE :
		{
			return false;
		}
		break;

		case OGRERR_NOT_ENOUGH_DATA :
		{
			type = "not enough data";
		}
		break;

		case OGRERR_NOT_ENOUGH_MEMORY :
		{
			type = "not enough memory";
		}
		break;

		case OGRERR_UNSUPPORTED_GEOMETRY_TYPE :
		{
			type = "unsupported geometry type";
		}
		break;

		case OGRERR_UNSUPPORTED_OPERATION :
		{
			type = "unsupported operation";
		}
		break;

		case OGRERR_CORRUPT_DATA :
		{
			type = "corrupt data";
		}
		break;

		case OGRERR_FAILURE :
		{
			type = "failure";
		}
		break;

		case OGRERR_UNSUPPORTED_SRS :
		{
			type = "unsupported srs";
		}
		break;

		default :
		{
			type = "unknown";
		}
		break;
	}

	return true;
}
