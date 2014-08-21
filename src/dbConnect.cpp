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
 *	\file dbConnect.cpp
 *	\brief Database Connect
 *	\author Olivier Pilotte [Inventis], David Tran [HSR]
 *	\version 0.7
 *	\date 13/06/14
 */

#include "dbConnect.h"

DBConnect::DBConnect(QWidget *parent) : QDialog(parent) {
    initInterface();
    initSlots();
    translateInterface();

    this->setWindowModality(Qt::ApplicationModal);
    this->setMinimumWidth(380);
}

DBConnect::~DBConnect(void) {
}

void DBConnect::showTables(const bool enable) const {
    if(enable) {
        lblTables->show();
        lstTables->show();
        radAllTables->show();
        radNonTables->show();
    } else {
        lblTables->hide();
        lstTables->hide();
        radAllTables->hide();
        radNonTables->hide();
    }
}

void DBConnect::initInterface(void) {
    theLayout = new QVBoxLayout(this);
    {
        lytInfo = new QGridLayout();
        {
            lblHost = new QLabel();
            lblHost->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
            lblHost->setMinimumSize(70, 20);
            lblHost->setMaximumSize(70, 20);

            lytHost = new QHBoxLayout();
            {
                txtHost = new QLineEdit();

                lytHost->addWidget(txtHost);

                lblPort = new QLabel();
                lblPort->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
                lblPort->setMinimumSize(30, 20);
                lblPort->setMaximumSize(30, 20);

                txtPort = new QLineEdit();
                QValidator *validator = new QIntValidator(0, 65535, this);
                txtPort->setValidator(validator);
                txtPort->setMaxLength(5);
                txtPort->setMinimumSize(50, 20);
                txtPort->setMaximumSize(50, 20);


                lytHost->addWidget(lblPort);
                lytHost->addWidget(txtPort);
            }

            lytInfo->addWidget(lblHost, 0, 0);
            lytInfo->addLayout(lytHost, 0, 1);

            lblName = new QLabel();
            lblName->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
            lblName->setMinimumSize(70, 20);
            lblName->setMaximumSize(70, 20);

            txtName = new QLineEdit();

            lytInfo->addWidget(lblName, 1, 0);
            lytInfo->addWidget(txtName, 1, 1);

            lblUser = new QLabel();
            lblUser->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
            lblUser->setMinimumSize(70, 20);
            lblUser->setMaximumSize(70, 20);

            txtUser = new QLineEdit();

            lytInfo->addWidget(lblUser, 2, 0);
            lytInfo->addWidget(txtUser, 2, 1);

            lblPass = new QLabel();
            lblPass->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
            lblPass->setMinimumSize(70, 20);
            lblPass->setMaximumSize(70, 20);

            txtPass = new QLineEdit();
            txtPass->setEchoMode(QLineEdit::Password);

            lytInfo->addWidget(lblPass, 3, 0);
            lytInfo->addWidget(txtPass, 3, 1);

            btnConnect = new QPushButton();

            lytInfo->addWidget(btnConnect, 4, 1);

            lytTables = new QVBoxLayout();
            {
                lblTables = new QLabel();
                lblTables->setAlignment(Qt::AlignRight);
                lblTables->setMinimumSize(70, 20);
                lblTables->setMaximumSize(70, 20);

                radAllTables = new QPushButton();
                radNonTables = new QPushButton();

                lytTables->addWidget(lblTables);
                lytTables->addWidget(radAllTables);
                lytTables->addWidget(radNonTables);
            }

            lstTables = new QListWidget();

            lytInfo->addLayout(lytTables, 6, 0);
            lytInfo->addWidget(lstTables, 6, 1);
        }

        theLayout->addLayout(lytInfo);


        lytDialog = new QHBoxLayout();
        {
            btnAccept = new QPushButton();
            btnAccept->setEnabled(false);

            btnCancel = new QPushButton();

            lytDialog->addWidget(btnAccept);
            lytDialog->addWidget(btnCancel);
        }

        theLayout->addLayout(lytDialog);
    }

    this->setLayout(theLayout);
}

void DBConnect::initSlots(void) {
    QObject::connect(btnConnect, SIGNAL(clicked()), this, SLOT(evtBtnConnect(void)));
    QObject::connect(radAllTables, SIGNAL(clicked()), this, SLOT(evtRadAllTables(void)));
    QObject::connect(radNonTables, SIGNAL(clicked()), this, SLOT(evtRadNonTables(void)));
    QObject::connect(btnCancel, SIGNAL(clicked()), this, SLOT(evtBtnCancel(void)));
    QObject::connect(btnAccept, SIGNAL(clicked()), this, SLOT(evtBtnAccept(void)));
}

void DBConnect::translateInterface(void) {
    this->setWindowTitle(tr("Database"));

    lblHost->setText(tr("Hostname"));
    lblPort->setText(tr("Port"));
    lblName->setText(tr("Database"));
    lblUser->setText(tr("Username"));
    lblPass->setText(tr("Password"));

    btnConnect->setText(tr("Connect"));

    lblTables->setText(tr("Tables"));

    radAllTables->setText(tr("Select All"));
    radNonTables->setText(tr("Reset"));

    btnAccept->setText(tr("Accept"));
    btnCancel->setText(tr("Cancel"));
}

void DBConnect::evtBtnConnect(void) {
    host = txtHost->text();
    port = txtPort->text();
    name = txtName->text();
    user = txtUser->text();
    pass = txtPass->text();

    QSqlDatabase base = QSqlDatabase::addDatabase(connectionType);
    btnAccept->setEnabled(false);
    if(connectionType.compare(tr("QSQLITE")) == 0) {
        QString type = tr("\" SQLite/SpatiaLite (*.sqlite)\"");
        name = QDir::toNativeSeparators(QFileDialog::getOpenFileName(this, tr("SQLite/SpatiaLite File"), tr(""), type));
        txtName->setText(name);
    } else {
        base.setHostName(host);
        base.setPort(port.toInt());
        base.setUserName(user);
        base.setPassword(pass);
    }
    base.setDatabaseName(name);

    QMessageBox msg;
    char *table;
    lstTables->clear();
    if(base.open()) {
        QStringList list = base.tables();
        QStringList::Iterator it = list.begin();
        while(it != list.end()) {
            table = (char *)(*it).toStdString().c_str();
            if((strcmp(table, "geometry_columns") != 0) && (strcmp(table, "spatial_ref_sys") != 0)) {
                QListWidgetItem *item = new QListWidgetItem(*it);
                lstTables->addItem(item);
                if(connectionType.compare("QSQLITE") != 0) {
                    item->setCheckState(Qt::Unchecked);
                }
            }
            ++it;
        }
        if(lstTables->count() > 0)
            btnAccept->setEnabled(true);
    } else if(!txtName->text().isEmpty()) {
        msg.setText("* Can't connect to database !");
        msg.exec();
    }
    if(lstTables->count() <=0 && base.isOpen()) {
        msg.setText("* Can't find any tables in database !");
        msg.exec();
    }
    base.close();
}

void DBConnect::evtRadAllTables(void) {
    for(int i = 0; i < lstTables->count(); ++i) {
        lstTables->item(i)->setCheckState(Qt::Checked);
    }
}

void DBConnect::evtRadNonTables(void) {
    for(int i = 0; i < lstTables->count(); ++i) {
        lstTables->item(i)->setCheckState(Qt::Unchecked);
    }
}

void DBConnect::evtBtnAccept(void) {
    host = txtHost->text();
    port = txtPort->text();
    name = txtName->text();
    user = txtUser->text();
    pass = txtPass->text();

    QSqlDatabase base = QSqlDatabase::addDatabase(connectionType);
    if(connectionType.compare(tr("QSQLITE")) != 0) {
        base.setHostName(host);
        base.setPort(port.toInt());
        base.setUserName(user);
        base.setPassword(pass);
        base.setDatabaseName(name);
        base.open();
        if(base.isOpenError()) {
            btnAccept->setEnabled(false);
            lstTables->clear();
            QMessageBox msg;
            msg.setText("* Can't connect to database !");
            msg.exec();
            base.close();
            return;
        }
    }

    QString tables;
    QString separator;
    if(connectionType.compare("QPSQL") == 0) {
        separator = " ";
        connectionString = tr("PG:");
        if(name.size() > 0)	connectionString += tr("dbname=") + name;
        if(host.size() > 0)	connectionString += tr(" host=") + host;
        if(port.size() > 0)	connectionString += tr(" port=") + port;
        if(user.size() > 0)	connectionString += tr(" user=") + user;
        if(pass.size() > 0)	connectionString += tr(" password=") + pass;
    } else if(connectionType.compare("QMYSQL") == 0) {
        separator = ",";
        if(name.size() > 0)	connectionString = tr("MySQL:") + name;
        if(host.size() > 0)	connectionString += ",host=" + host;
        if(port.size() > 0)	connectionString += ",port=" + port;
        if(user.size() > 0)	connectionString += ",user=" + user;
        if(pass.size() > 0)	connectionString += ",password=" + pass;
     } else if(connectionType.compare("QODBC") == 0) {
        separator = "";
        if(user.size() > 0)	connectionString = "ODBC:" + user;
        if(pass.size() > 0)	connectionString += "/" + pass;
        if(host.size() > 0)	connectionString += "@" + host;
    } else if(connectionType.compare("QSQLITE") == 0) {
        separator = "";
    }
    int nb = 0;
    selectedTables.clear();
    for(int i = 0; i < lstTables->count(); ++i) {
        if(lstTables->item(i)->checkState() == Qt::Checked) {
            if(nb > 0) {
                tables += ",";
            }
            tables += lstTables->item(i)->text();
            selectedTables.append(lstTables->item(i)->text());
            ++nb;
        }
    }
    if(connectionType.compare(tr("QSQLITE")) != 0) {
        if(nb > 0) {
            connectionString += separator;
            connectionString += "tables=";
            connectionString += tables;
        }
    } else {
        connectionString = name;
    }
    this->accept();
}

void DBConnect::evtBtnCancel(void) {
    this->reject();
}

void DBConnect::setConnectionType(const QString type) {
    if(connectionType.compare(type) != 0) {
        txtHost->clear();
        txtPort->clear();
        txtName->clear();
        txtUser->clear();
        txtPass->clear();
        lstTables->clear();
        btnAccept->setEnabled(false);
        connectionType = type;
    }
    txtHost->setEnabled(true);
    txtHost->setFocus();
    txtPort->setEnabled(true);
    txtName->setReadOnly(false);
    txtUser->setEnabled(true);
    txtPass->setEnabled(true);
    radAllTables->setEnabled(true);
    radNonTables->setEnabled(true);
    btnConnect->setText(tr("Connect"));
    lstTables->setSelectionMode(QAbstractItemView::NoSelection);

    if(connectionType.compare(tr("QPSQL")) == 0) {
        txtPort->setText(tr("5432"));
    } else if(connectionType.compare(tr("QMYSQL")) == 0) {
        txtPort->setText(tr("3306"));
    } else if(connectionType.compare(tr("QODBC")) == 0) {
        txtPort->setText(tr("1433"));
    } else if(connectionType.compare(tr("QSQLITE")) == 0) {
        txtHost->setEnabled(false);
        txtPort->setEnabled(false);
        txtName->setReadOnly(true);
        txtUser->setEnabled(false);
        txtPass->setEnabled(false);
        radAllTables->setEnabled(false);
        radNonTables->setEnabled(false);
        btnConnect->setText(tr("Open file"));
    }
}

QString DBConnect::getConnectionString(void) const {
    return connectionString;
}

QStringList DBConnect::getSelectedTables(void) const {
    return selectedTables;
}
