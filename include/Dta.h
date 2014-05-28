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
 *	\file Dta.h
 *	\brief Formats & Projections
 *	\author Olivier Pilotte [ Inventis ], David Tran [ HSR ]
 *	\version 0.7
 *	\date 13/06/14
 */
//read/write
formats[0 ][0] = "ESRI Shapefile";      formats[0 ][1] = "shp";
formats[1 ][0] = "MapInfo File";        formats[1 ][1] = "tab";
formats[2 ][0] = "TIGER";               formats[2 ][1] = "tiger";
formats[3 ][0] = "S57";                 formats[3 ][1] = "s57";
formats[4 ][0] = "DGN";                 formats[4 ][1] = "dgn";
formats[5 ][0] = "Memory";              formats[5 ][1] = "memory";
formats[6 ][0] = "BNA";                 formats[6 ][1] = "bna";
formats[7 ][0] = "CSV";                 formats[7 ][1] = "csv";
formats[8 ][0] = "GML";                 formats[8 ][1] = "gml";
formats[9 ][0] = "GPX";                 formats[9 ][1] = "gpx";
formats[10][0] = "LIBKML";              formats[10][1] = "kmz";
formats[11][0] = "KML";                 formats[11][1] = "kml";
formats[12][0] = "GeoJSON";             formats[12][1] = "geojson";
formats[13][0] = "Interlis 1";          formats[13][1] = "itf";
formats[14][0] = "Interlis 2";          formats[14][1] = "xml";
formats[15][0] = "GMT";                 formats[15][1] = "gmt";
formats[16][0] = "PCIDSK";              formats[16][1] = "pix";
formats[17][0] = "DXF";                 formats[17][1] = "dxf";
formats[18][0] = "Geoconcept";          formats[18][1] = "gxt";
formats[19][0] = "GeoRSS";              formats[19][1] = "georss";
formats[20][0] = "GPSTrackMaker";       formats[20][1] = "gtm";
formats[21][0] = "PGDump";              formats[21][1] = "sql";
formats[22][0] = "GPSBabel";            formats[22][1] = "gpsbabel";
formats[23][0] = "GFT";                 formats[23][1] = "gft";
formats[24][0] = "ODS";                 formats[24][1] = "ods";
formats[25][0] = "XLSX";                formats[25][1] = "xlsx";
formats[26][0] = "PDF";                 formats[26][1] = "pdf";
//readonly
formats[27][0] = "UK .NTF";             formats[27][1] = "ntf";
formats[28][0] = "SDTS";                formats[28][1] = "sdts";
formats[29][0] = "VRT";                 formats[29][1] = "vrt";
formats[30][0] = "REC";                 formats[30][1] = "rec";
formats[31][0] = "NAS";                 formats[31][1] = "nas";
formats[32][0] = "PGeo";                formats[32][1] = "pgeo";
formats[33][0] = "OpenFileGDB";         formats[33][1] = "gdb";
formats[34][0] = "XPlane";              formats[34][1] = "dat";
formats[35][0] = "AVCBin";              formats[35][1] = "avcbin";
formats[36][0] = "AVCE00";              formats[36][1] = "avce00";
formats[37][0] = "VFK";                 formats[37][1] = "vkf";
formats[38][0] = "OSM";                 formats[38][1] = "osm";
formats[39][0] = "SUA";                 formats[39][1] = "sua";
formats[40][0] = "OpenAir";             formats[40][1] = "openair";
formats[41][0] = "PDS";                 formats[41][1] = "pds";
formats[42][0] = "HTF";                 formats[42][1] = "htf";
formats[43][0] = "AeronavFAA";          formats[43][1] = "faa";
formats[44][0] = "Geomedia";            formats[44][1] = "mdb";
formats[45][0] = "EDIGEO";              formats[45][1] = "edigeo";
formats[46][0] = "SVG";                 formats[46][1] = "svg";
formats[47][0] = "Idrisi";              formats[47][1] = "idrisi";
formats[48][0] = "ARCGEN";              formats[48][1] = "arcgen";
formats[49][0] = "SEGUKOOA";            formats[49][1] = "segukooa";
formats[50][0] = "SEGY";                formats[50][1] = "segy";

databases[0][0] = "PostgreSQL";			databases[0][1] = "QPSQL";
databases[1][0] = "SQLite";				databases[1][1] = "QSQLITE";
databases[2][0] = "MySQL";				databases[2][1] = "QMYSQL";
databases[3][0] = "ODBC";				databases[3][1] = "QODBC";

webservices[0][0] = "WFS";              webservices[0][1] = "WFS:";
