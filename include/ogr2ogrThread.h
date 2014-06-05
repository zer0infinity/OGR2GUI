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
 *	\file processThread.h
 *	\brief process Thread
 *	\author David Tran [ HSR ]
 *	\version 0.7
 *	\date 13/06/14
 */

#ifndef OGR2OGRTHREAD_H
#define OGR2OGRTHREAD_H

#include <QThread>
#include <QProcess>
#include <QPushButton>

class Ogr2ogrThread : public QThread {
public:
    Ogr2ogrThread(QString&, QPushButton*);
    ~Ogr2ogrThread();
protected:
    void run();
private:
    QString &command;
    QProcess *process;
    QPushButton *btnExecute;
};

#endif
