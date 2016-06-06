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
 *	\file webServiceConnect.h
 *	\brief Web Service Connect
 *	\author David Tran
 *	\version 0.8
 */

#ifndef WFSCONNECT_H
#define WFSCONNECT_H

#include <QtWidgets>
#include "ogr.h"

QT_BEGIN_NAMESPACE

class WebServiceConnect : public QDialog
{
    Q_OBJECT

private:

    QString connectionType;

    QString connectionString;

    QString selectedLayers;
    QStringList selectedLayersList;

    QVBoxLayout *theLayout;
    QGridLayout *lytInfo;
    QLabel *lblHost;
    QHBoxLayout *lytHost;
    QLineEdit *txtHost;

    QPushButton *btnConnect;

    QVBoxLayout *lytTables;
    QLabel *lblTables;
    QPushButton *radAllTables;
    QPushButton *radNonTables;

    QListWidget *lstTables;

    QHBoxLayout *lytDialog;
    QPushButton *btnOK;
    QPushButton *btnCancel;

    /**
         *	\fn void initInterface(void);
         *	\brief Inits Interface
         */
    void initInterface(void);

    /**
         *	\fn void initSlots(void);
         *	\brief Inits Slots
         */
    void initSlots(void);

public slots:
    void evtBtnConnect(void);
    void evtRadAllLayers(void);
    void evtRadNonLayers(void);
    void evtBtnOK(void);
    void evtBtnCancel(void);

public:

    /**
         *	\fn WebServiceConnect(QWidget * = 0);
         *	\brief Constructor
         */
    WebServiceConnect(QWidget * = 0);

    /**
         *	\fn ~WebServiceConnect(void);
         *	\brief Destructor
         */
    ~WebServiceConnect(void);

    /**
         *	\fn void translateInterface(void);
         *	\brief Translates Interface
         */
    void translateInterface(void);

    /**
         *	\fn void setConnectionType(QString)
         *	\brief Sets connection type
         */
    void setConnectionType(const QString);

    /**
         *	\fn QString getConnectionString(void)
         *	\brief returns connection string
         */
    QString getConnectionString(void) const;

    /**
         *	\fn QSring getSelectedLayers(void)
         *	\brief returns selected layers
         */
    QString getSelectedLayers(void) const;

    /**
         *	\fn QSringList getSelectedLayersAsList(void)
         *	\brief returns selected layers
         */
    QStringList getSelectedLayersAsList(void) const;
};

QT_END_NAMESPACE

#endif // WFSCONNECT_H
