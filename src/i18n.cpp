/*****************************************************************************
 * OGR2GUI is an application used to convert and manipulate geospatial
 * data. It is based on the "OGR Simple Feature Library" from the
 * "Geospatial Data Abstraction Library" <http://gdal.org>.
 *
 * Copyright (c) 2014 Faculty of Computer Science,
 * University of Applied Sciences Rapperswil (HSR),
 * 8640 Rapperswil, Switzerland
 * Copyright (c) 2016 David Tran, Switzerland
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
 *	\file i18n.cpp
 *	\brief I18N
 *	\author David Tran
 *	\version 0.8
 */

#include "i18n.h"

bool I18N::instanceExists;
I18N* I18N::instance;

I18N::I18N(void) : path(":/translations") {
}

I18N::~I18N(void) {
}

void I18N::translate(const QString lang) {
    translator.load(lang, path);
    QCoreApplication::installTranslator(&translator);
}

I18N* I18N::getInstance(void) {
    if(instanceExists) {
        return instance;
    } else {
        instance = new I18N();
        instanceExists = true;
        return instance;
    }
}
