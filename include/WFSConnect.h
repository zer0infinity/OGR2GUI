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
 *	\file wfsConnect.h
 *	\brief WFS Connection
 *	\author David Tran [ HSR ]
 *	\version 0.7
 *	\date 13/06/14
 */

#ifndef WFSCONNECT_H
#define WFSCONNECT_H

#include <QtWidgets>
#include "Ogr.h"

QT_BEGIN_NAMESPACE

class WFSConnect : public QDialog
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
    QRadioButton *radAllTables;
    QRadioButton *radNonTables;

    QListWidget *lstTables;

    QHBoxLayout *lytDialog;
    QPushButton *btnAccept;
    QPushButton *btnCancel;

    /*!
         *	\fn void InitInterface( void );
         *	\brief Inits Interface
         */
    void InitInterface( void );

    /*!
         *	\fn void InitSlots( void );
         *	\brief Inits Slots
         */
    void InitSlots( void );

    /*!
         *	\fn void TranslateInterface( void );
         *	\brief Translates Interface
         */
    void TranslateInterface( void );

public slots:
    void evtBtnConnect( void );
    void evtRadAllLayers( void );
    void evtRadNonLayers( void );
    void evtBtnAccept( void );
    void evtBtnCancel( void );

public:

    /*!
         *	\fn Frm( const QWidget & );
         *	\brief Constructor
         */
    WFSConnect( QWidget * = 0 );

    /*!
         *	\fn ~Frm
         *	\brief Destructor
         */
    ~WFSConnect( void );

    /*!
         *	\fn void setConnectionType( QString )
         *	\brief Sets connection type
         */
    void setConnectionType( QString );

    /*!
         *	\fn QString getConnectionString( void )
         *	\brief returns connection string
         */
    QString getConnectionString( void ) const;

    /*!
         *	\fn QSring getSelectedTables( void )
         *	\brief returns selected layers
         */
    QString getSelectedLayers( void ) const;

    /*!
         *	\fn QSringList getSelectedTables( void )
         *	\brief returns selected layers
         */
    QStringList getSelectedLayersAsList( void ) const;
};

QT_END_NAMESPACE

#endif // WFSCONNECT_H
