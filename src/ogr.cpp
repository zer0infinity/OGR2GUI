/*****************************************************************************
 * OGR2GUI is an application used to convert and manipulate geospatial
 * data. It is based on the "OGR Simple Feature Library" from the
 * "Geospatial Data Abstraction Library" <http://gdal.org>.
 *
 * Copyright (c) 2009 Inventis <mailto:developpement@inventis.ca>
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
 *	\file ogr.cpp
 *	\brief OGR API
 *	\author Olivier Pilotte [Inventis], David Tran [HSR]
 *	\version 0.7
 *	\date 13/06/14
 */

#include "ogr.h"
#include <QtCore/QSysInfo>
#include <windows.h>

typedef enum { Win_64, Win_32, WOW64, Error, Other } OsType;

typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);

OsType checkOS() {
#ifndef Q_OS_WIN32
    return Other;
#else
    if (QSysInfo::WordSize == 64)
        return Win_64;
    BOOL isWOW64 = FALSE;
    LPFN_ISWOW64PROCESS fnIsWow64Process;
    fnIsWow64Process = (LPFN_ISWOW64PROCESS) GetProcAddress(GetModuleHandle(TEXT("kernel32")),"IsWow64Process");
    if(fnIsWow64Process == NULL)
        return Win_32;
    if(!IsWow64Process(GetCurrentProcess(), &isWOW64))
        return Error;
    return isWOW64? WOW64 : Win_32;
#endif
}

Ogr::Ogr(void) {
    OGRRegisterAll();
}

Ogr::~Ogr(void) {
}

bool Ogr::openOgr2ogr(QString command, QPushButton *btnExecute) {
    bool resVal = false;
    if(checkOS() == Win_64) {
        ogr2ogr = new Ogr2ogrThread(command, btnExecute);
        ogr2ogr->start();
        resVal = ogr2ogr->isRunning();
    } else if(checkOS() == WOW64) {
        const QString logPath = QDir::toNativeSeparators(QCoreApplication::applicationDirPath() + QDir::separator() + "ogr2ogr.log");
        btnExecute->setEnabled(false);
        btnExecute->setText("Please wait...");
        process = new QProcess();
        process->setProcessChannelMode(QProcess::MergedChannels);
        process->setStandardOutputFile(logPath);
        process->start(command);
        process->waitForStarted();
        resVal = process->waitForFinished();
        btnExecute->setEnabled(true);
        btnExecute->setText("Execute");
    } else if(checkOS() == Win_32){
        std::string cmd = command.toStdString();
        std::wstring widestring = std::wstring(cmd.begin(), cmd.end());
        LPWSTR lpwstr = const_cast<LPWSTR>(widestring.c_str());
        STARTUPINFO si;
        PROCESS_INFORMATION pi;
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));
        resVal = CreateProcess(NULL, lpwstr, 0, 0, FALSE, CREATE_NO_WINDOW, 0, 0, &si, &pi);
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    return resVal;
}

bool Ogr::openWFS(const QString uri, QStringList &fileList) {
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

bool Ogr::openSource(const string filename, const string layername, string &epsg, string &query, string &error) {
    layerName = layername;
    return openSource(filename, epsg, query, error);
}

bool Ogr::openSource(const string filename, string &epsg, string &query, string &error) {
    sourceSRS = NULL;
    sourceName = filename;
    sourceData = OGROpen(sourceName.c_str(), 0, NULL);
    if(sourceData != NULL) {
        if(layerName != "")
            sourceLayer = OGR_DS_GetLayerByName(sourceData, layerName.c_str());
        else
            sourceLayer = OGR_DS_GetLayer(sourceData, 0);
        OGR_L_ResetReading(sourceLayer);
        if(sourceLayer != NULL) {
            sourceLayerDefn = OGR_L_GetLayerDefn(sourceLayer);
            sourceLayerName = OGR_FD_GetName(sourceLayerDefn);
            sourceLayerGeom = OGR_FD_GetGeomType(sourceLayerDefn);
            sourceGeom = OGR_L_GetSpatialFilter(sourceLayer);
            sourceSRS = OGR_L_GetSpatialRef(sourceLayer);
            if(sourceSRS != NULL && ! Error(OSRAutoIdentifyEPSG(sourceSRS), error)) {
                epsg = OSRGetAttrValue(sourceSRS, "AUTHORITY", 1);
            } else {
                query = "SELECT * FROM " + sourceLayerName;
            }
        } else {
            return false;
        }
    } else {
        return false;
    }
    return true;
}

bool Ogr::closeSource(void) const {
    if(sourceData != NULL) {
        OGR_DS_Destroy(sourceData);
        return true;
    }
    return false;
}

bool Ogr::openDriver(const string drivername) {
    formatDriver = OGRGetDriverByName(drivername.c_str());
    return formatDriver != NULL;
}

bool Ogr::testSpatialReference(const int projection) {
    targetSRS = NULL;
    if(projection > 0) {
        targetSRS = OSRNewSpatialReference(NULL);
        if(Error(OSRImportFromEPSG(targetSRS, projection), error)) {
            return false;
        }
    }
    return true;
}

bool Ogr::testFeatureProjection(void) {
    OGR_L_ResetReading(sourceLayer);
    OGRFeatureH feature;
    while((feature = OGR_L_GetNextFeature(sourceLayer)) != NULL) {
        if(targetSRS)
            if(Error(OGR_G_TransformTo(OGR_F_GetGeometryRef(feature), targetSRS), error)) {
                OGR_F_Destroy(feature);
                return false;
            }
        OGR_F_Destroy(feature);
    }
    return true;
}

bool Ogr::testExecuteSQL(const string query) const {
    OGRLayerH squeryLayer = OGR_DS_ExecuteSQL(sourceData, query.c_str(), NULL, "");
    return squeryLayer != NULL;
}

bool Ogr::Error(OGRErr code, string &type)
{
    switch(code)
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
