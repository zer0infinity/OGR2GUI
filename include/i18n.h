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
 *	\file i18n.h
 *	\brief I18N
 *	\author David Tran [HSR]
 *	\version 0.7
 *	\date 13/06/14
 */

#ifndef _I18N_H
#define _I18N_H

#include <QTranslator>
#include <QCoreApplication>
#include <QLibraryInfo>

class I18N {
public:
    static I18N* getInstance();
    ~I18N();
    void translate(QString lang = "en_GB");
private:
    QString lang, path;
    QTranslator apTranslator, qtTranslator;
    I18N();
    I18N(const I18N&);
    I18N& operator=(const I18N&);
    static bool instanceExists;
    static I18N* instance;
};

#endif // _I18N_H
