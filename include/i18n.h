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
    /**
         *	\fn void getInstance(void);
         *	\brief Get I18N instance
         */
    static I18N* getInstance(void);

    /**
         *	\fn ~I18N(void);
         *	\brief Destructor
         */
    ~I18N(void);

    /**
         *	\fn void translate(QString);
         *	\brief translate user interface
         *  \param QString : language file
         */
    void translate(const QString lang);
private:
    static bool instanceExists;
    static I18N* instance;
    QString lang, path;
    QTranslator apTranslator, qtTranslator;

    /**
         *	\fn I18N(void);
         *	\brief Constructor
         */
    I18N(void);
    /**
         *	\fn I18N(const I18N&);
         *	\brief Copy constructor
         */
    I18N(const I18N&);
    /**
         *	\fn I18N& operator=(const I18N&);
         *	\brief overwrite equal operator
         */
    I18N& operator=(const I18N&);
};

#endif // _I18N_H
