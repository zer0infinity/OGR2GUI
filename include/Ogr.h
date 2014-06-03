/*****************************************************************************
 * ogr2gui is an application used to convert and manipulate geospatial
 * data. It is based on the "OGR Simple Feature Library" from the
 * "Geospatial Data Abstraction Library" <http://gdal.org>.
 *
 * Copyright (c) 2009 Inventis <mailto:developpement@inventis.ca>
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
 *	\file Ogr.h
 *	\brief OGR C API
 *	\author Olivier Pilotte [ Inventis ], David Tran [ HSR ]
 *	\version 0.7
 *	\date 13/06/14
 */

#ifndef OGR
#define OGR

#include "ogr_api.h"
#include "ogr_srs_api.h"
#include "utils.h"
#include "ogr2ogrThread.h"

#include <string>
#include <QStringList>
#include <QPushButton>

using std::string;

class Ogr
{
private :

    Ogr2ogrThread *ogr2ogr;

    QProcess *process;

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

    /*!
     * \brief OpenOgr2ogr(QString &command)
     * \param command : command with arguments
     * \param btnExecute : btnExecute
     * \return true on success
     */
    bool OpenOgr2ogr(QString command, QPushButton *btnExecute);

    /*!
         * \fn OpenWFS(QStringList &fileList)
         * \brief Open WFS data
         * \param uri : source uri
         * \param &fileList : layer list
         * \return true on success
         */
    bool OpenWFS(QString uri, QStringList &fileList);

    /*!
         * \fn OpenSource(string filename, string layername, string &epsg, string &query, string &error);
         * \brief Opens souorce data
         * \param filename : source filename
         * \param layername : layername
         * \param &epsg : epsg code
         * \param &query : sql query
         * \param &error : error text
         * \return true on success
         */
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
         *	\returns true on success
         */
    bool OpenDriver( string drivername);

    /*!
     *	\fn bool Process( void );
     *	\brief Process a feature
     */
    void TestFeature( void );

    /*!
     * \brief OpenProjection(int projection)
     * \param projection : projection
     */
    void TestProjection(int projection);
};

#endif
