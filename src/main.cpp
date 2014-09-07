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

/*!
 *	\file main.cpp
 *	\brief main
 *	\author David Tran [HSR]
 *	\version 0.7
 *	\date 13/06/14
 */

//#pragma comment(linker, "/SUBSYSTEM:CONSOLE")
#include "app.h"
#include "cpl_conv.h"
#include "i18n.h"
#include <iostream>
#include <QSettings>

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    string dataPath = QDir::toNativeSeparators(QCoreApplication::applicationDirPath() + QDir::separator() + "data").toStdString();
    CPLSetConfigOption("GDAL_DATA", dataPath.c_str());
    if(1 < argc) {
        for(int i=0;i<argc;++i)
            std::cout << argv[i] << " ";
        std::cout << std::endl;
        return ogr2ogr(argc, argv);
    } else {
        QSettings settings("ogr2gui.ini", QSettings::IniFormat);
        QVariant language = settings.value("language");
        if(language.isNull() || !language.isValid()) {
            settings.setValue("language", "en_GB");
            language = "en_GB";
        }
        I18N *i18n = I18N::getInstance();
        i18n->translate(language.toString());
        new App();
    }
    return app.exec();
}
