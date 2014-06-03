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
 *	\file processThread.cpp
 *	\brief process Thread
 *	\author David Tran [ HSR ]
 *	\version 0.7
 *	\date 13/06/14
 */

#include "ogr2ogrThread.h"

Ogr2ogrThread::Ogr2ogrThread(QString &command, QPushButton *btnExecute) : command(command), btnExecute(btnExecute) {
}

Ogr2ogrThread::~Ogr2ogrThread(void) {
}

void Ogr2ogrThread::run() {
    btnExecute->setEnabled(false);
    process = new QProcess();
    process->setProcessChannelMode(QProcess::MergedChannels);
    process->start(command);
    while(process->waitForFinished());
    process->close();
    wait();
    btnExecute->setEnabled(true);
}
