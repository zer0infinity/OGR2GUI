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
 *	\file webServiceConnect.cpp
 *	\brief Web Service Connect
 *	\author David Tran [HSR]
 *	\version 0.7
 */

#include "webServiceConnect.h"

WebServiceConnect::WebServiceConnect(QWidget *parent) : QDialog(parent) {
    initInterface();
    initSlots();
    translateInterface();

    this->setWindowModality(Qt::ApplicationModal);
    this->setMinimumWidth(380);
}

WebServiceConnect::~WebServiceConnect(void) {
}

void WebServiceConnect::initInterface(void) {
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
            }

            lytInfo->addWidget(lblHost, 0, 0);
            lytInfo->addLayout(lytHost, 0, 1);

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
            btnOK = new QPushButton();
            btnOK->setEnabled(false);

            btnCancel = new QPushButton();

            lytDialog->addWidget(btnOK);
            lytDialog->addWidget(btnCancel);
        }

        theLayout->addLayout(lytDialog);
    }

    this->setLayout(theLayout);
}

void WebServiceConnect::initSlots(void) {
    QObject::connect(btnConnect, SIGNAL(clicked()), this, SLOT(evtBtnConnect(void)));
    QObject::connect(radAllTables, SIGNAL(clicked()), this, SLOT(evtRadAllLayers(void)));
    QObject::connect(radNonTables, SIGNAL(clicked()), this, SLOT(evtRadNonLayers(void)));
    QObject::connect(btnCancel, SIGNAL(clicked()), this, SLOT(evtBtnCancel(void)));
    QObject::connect(btnOK, SIGNAL(clicked()), this, SLOT(evtBtnOK(void)));
}

void WebServiceConnect::translateInterface(void) {
    this->setWindowTitle(tr("Web Service"));

    lblHost->setText(tr("URI"));

    btnConnect->setText(tr("Connect"));

    lblTables->setText(tr("Layers"));

    radAllTables->setText(tr("Select All"));
    radNonTables->setText(tr("Reset"));

    btnOK->setText("OK");
    btnCancel->setText(tr("Cancel"));
}

void WebServiceConnect::evtBtnConnect(void) {
    lstTables->clear();
    Ogr ogr;
    QStringList fileList;
    QString filename = connectionType + txtHost->text();
    if(ogr.openWFS(filename, fileList)) {
        QStringList::Iterator it = fileList.begin();
        while(it != fileList.end()) {
            QListWidgetItem *item = new QListWidgetItem(*it);
            item->setCheckState(Qt::Unchecked);
            lstTables->addItem(item);
            ++it;
        }
        btnOK->setEnabled(true);
    } else {
        QMessageBox msg;
        msg.setText(tr("Can't connect to web service !"));
        msg.exec();
    }
}

void WebServiceConnect::evtRadAllLayers(void) {
    for(int i = 0; i < lstTables->count(); ++i) {
        lstTables->item(i)->setCheckState(Qt::Checked);
    }
}

void WebServiceConnect::evtRadNonLayers(void) {
    for(int i = 0; i < lstTables->count(); ++i) {
        lstTables->item(i)->setCheckState(Qt::Unchecked);
    }
}

void WebServiceConnect::evtBtnOK(void) {
    Ogr ogr;
    if(!ogr.openWFS(connectionType + txtHost->text(), QStringList())) {
        btnOK->setEnabled(false);
        lstTables->clear();
        QMessageBox msg;
        msg.setText(tr("Can't connect to web service !"));
        msg.exec();
        return;
    }

    connectionString = txtHost->text();
    selectedLayers.clear();
    selectedLayersList.clear();
    for(int i = 0; i < lstTables->count(); ++i) {
        if(lstTables->item(i)->checkState() == Qt::Checked) {
            selectedLayers += lstTables->item(i)->text() + " ";
        }
    }
    selectedLayers = selectedLayers.simplified();
    selectedLayersList = selectedLayers.split(" ");

    lstTables->clear();
    btnOK->setEnabled(false);
    this->accept();
}

void WebServiceConnect::evtBtnCancel(void) {
    lstTables->clear();
    btnOK->setEnabled(false);
    this->reject();
}

void WebServiceConnect::setConnectionType(const QString type) {
    connectionType = type;
}

QString WebServiceConnect::getConnectionString(void) const {
    return connectionString;
}

QString WebServiceConnect::getSelectedLayers(void) const {
    return selectedLayers;
}

QStringList WebServiceConnect::getSelectedLayersAsList(void) const {
    return selectedLayersList;
}
