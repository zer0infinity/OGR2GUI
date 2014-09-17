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

/**
 *	\file dbConnect.h
 *	\brief Database Connect
 *	\author Olivier Pilotte [Inventis], David Tran [HSR]
 *	\version 0.7
 */

#ifndef DBCONNECT_H
#define DBCONNECT_H

#include <QtWidgets>
#include <QtSql>

QT_BEGIN_NAMESPACE

class DBConnect : public QDialog
{
    Q_OBJECT

private:

    QString host;
    QString port;
    QString name;
    QString user;
    QString pass;

    QString connectionType;

    QString connectionString;

    QStringList selectedTables;

    QVBoxLayout *theLayout;
    QGridLayout *lytInfo;
    QLabel *lblHost;
    QHBoxLayout *lytHost;
    QLineEdit *txtHost;
    QLabel *lblPort;
    QLineEdit *txtPort;
    QLabel *lblName;
    QLineEdit *txtName;
    QLabel *lblUser;
    QLineEdit *txtUser;
    QLabel *lblPass;
    QLineEdit *txtPass;

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
         *	\fn void InitInterface(void);
         *	\brief Inits Interface
         */
    void initInterface(void);

    /**
         *	\fn void InitSlots(void);
         *	\brief Inits Slots
         */
    void initSlots(void);

public slots:
    void evtBtnConnect(void);
    void evtRadAllTables(void);
    void evtRadNonTables(void);
    void evtBtnOK(void);
    void evtBtnCancel(void);

public:

    /**
         *	\fn DBConnect(const QWidget &);
         *	\brief Constructor
         */
    DBConnect(QWidget * = 0);

    /**
         *	\fn ~DBConnect
         *	\brief Destructor
         */
    ~DBConnect(void);

    /**
         *	\fn void TranslateInterface(void);
         *	\brief Translates Interface
         */
    void translateInterface(void);

    /**
         * \fn void showTables(bool enable)
         * \brief show tables
         * \param enable : show tables
         */
    void showTables(const bool enable) const;

    /**
         *	\fn void setConnectionType(QString type)
         *	\brief Sets connection type
         */
    void setConnectionType(const QString type);

    /**
         *	\fn QString getConnectionString(void)
         *	\brief returns connection string
         */
    QString getConnectionString(void) const;

    /**
         *	\fn QSringList getSelectedTables(void)
         *	\brief returns selected tables
         */
    QStringList getSelectedTables(void) const;
};

QT_END_NAMESPACE

#endif
