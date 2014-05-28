/*****************************************************************************
 * ogr2gui is an application used to convert and manipulate geospatial
 * data.
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
 *	\file Ogr.c
 *	\brief OGR C API
 *	\author Olivier Pilotte [ Inventis ], David Tran [ HSR ]
 *	\version 0.7
 *	\date 13/06/14
 */

#include "Ogr.h"

Ogr::Ogr( void )
{
    OGRRegisterAll();
}

Ogr::~Ogr( void )
{

}

bool Ogr::OpenWFS(QString uri, QStringList &fileList) {
    sourceName = uri.toStdString();
    OGRDataSourceH sourceData = OGROpen(sourceName.c_str(), 0, NULL);
    if(sourceData != NULL) {
        for(int i = 0; i < OGR_DS_GetLayerCount(sourceData); ++i) {
            OGRLayerH sourceLayer = OGR_DS_GetLayer(sourceData, i);
            if(sourceLayer != NULL) {
                OGRFeatureDefnH sourceLayerDefn = OGR_L_GetLayerDefn(sourceLayer);
                fileList.append(OGR_FD_GetName(sourceLayerDefn));
            }
        }
        return true;
    }
    return false;
}

bool Ogr::OpenSource(string filename, string layername, string &epsg, string &query, string &error) {
    layerName = layername;
    return OpenSource(filename, epsg, query, error);
}

bool Ogr::OpenSource(string filename, string &epsg, string &query, string &error)
{
    sourceSRS = NULL;
    sourceName = filename;
    sourceData = OGROpen( sourceName.c_str(), 0, NULL );
    if( sourceData != NULL ) {
        if(layerName != "")
            sourceLayer = OGR_DS_GetLayerByName(sourceData, layerName.c_str());
        else
            sourceLayer = OGR_DS_GetLayer(sourceData, 0);
        if( sourceLayer != NULL ) {
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
                perror("unable to open source spatial reference");
            }
            query = "SELECT * FROM " + sourceLayerName;
        } else {
            perror("unable to open source layer");
            return false;
        }
    } else {
        perror("unable to open source data");
        return false;
    }
    return true;
}

bool Ogr::CloseSource( void )
{
    if( sourceData != NULL ) {
        OGR_DS_Destroy( sourceData );
        return true;
    }
    return false;
}

bool Ogr::OpenDriver(string drivername)
{
    formatDriver = OGRGetDriverByName( drivername.c_str() );
    if( formatDriver == NULL )
    {
        perror("unable to find driver");
        return false;
    }
    return true;
}

bool Ogr::OpenTarget(string filename, int projection) {
    targetSRS = NULL;
    targetName = filename;
    if(projection > 0) {
        targetSRS = OSRNewSpatialReference( NULL );
        if(Error( OSRImportFromEPSG( targetSRS, projection ), error)) {
            error.insert(0, "unable to create spatial reference : ");
        }
    }
    targetData = OGR_Dr_CreateDataSource(formatDriver, targetName.c_str(), 0);
    if(targetData == NULL) {
        perror("unable to create target data");
        return false;
    }
    return true;
}

bool Ogr::CloseTarget(void) {
    if(targetData != NULL) {
        OGR_DS_Destroy(targetData);
        return true;
    }
    return false;
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
