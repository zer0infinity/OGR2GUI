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
 *	\file langSettings.cpp
 *	\brief Language settings
 *	\author David Tran [HSR]
 *	\version 0.7
 */

#include "langSettings.h"

LangSettings::LangSettings(QWidget *parent) : QDialog(parent) {
    initInterface();
    initSlots();
    translateInterface();
    initLanguage();

    this->setWindowModality(Qt::ApplicationModal);
    this->setMinimumWidth(280);
}

LangSettings::~LangSettings(void) {
}

void LangSettings::initLanguage(void) {
    QFile file(":/languages");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
    QString line;
    QPair<QString, QString> pair;
    while(!(line = in.readLine()).isNull()) {
        QStringList t = line.split(",");
        if(!t.at(0).isNull())
            pair.first = t.at(0);
        if(!t.at(1).isNull())
            pair.second = t.at(1);
        languageList << pair;
    }
    file.close();
    qSort(languageList.begin(), languageList.end());

    for(int i = 0; i < languageList.size(); ++i) {
        QPair<QString, QString> language = languageList.at(i);
        cmbLang->addItem(language.first);
    }
}

void LangSettings::initInterface(void) {
    theLayout = new QVBoxLayout(this);
    {
        lytLang = new QGridLayout();
        {
            lblLang = new QLabel();
            lblLang->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
            lblLang->setMinimumSize(70, 20);
            lblLang->setMaximumSize(70, 20);

            cmbLang = new QComboBox();

            lytLang->addWidget(lblLang, 1, 0);
            lytLang->addWidget(cmbLang, 1, 1);
        }

        lytDialog = new QHBoxLayout();
        {
            btnOK = new QPushButton();
            btnCancel = new QPushButton();

            lytDialog->addWidget(btnOK);
            lytDialog->addWidget(btnCancel);
        }

        theLayout->addLayout(lytLang);
        theLayout->addLayout(lytDialog);
    }

    this->setLayout(theLayout);
}

void LangSettings::initSlots(void) {
    QObject::connect(btnCancel, SIGNAL(clicked()), this, SLOT(evtBtnCancel(void)));
    QObject::connect(btnOK, SIGNAL(clicked()), this, SLOT(evtBtnOK(void)));
}

void LangSettings::translateInterface(void) {
    this->setWindowTitle(tr("Language Settings"));

    lblLang->setText(tr("Language"));
    btnOK->setText(tr("Save"));
    btnCancel->setText(tr("Cancel"));
}

void LangSettings::evtBtnOK(void) {
    language = languageList.at(cmbLang->currentIndex()).second;
    QSettings settings("ogr2gui.ini", QSettings::IniFormat);
    settings.setValue("language", language);
    I18N *i18n = I18N::getInstance();
    i18n->translate(language);
    this->accept();
}

void LangSettings::evtBtnCancel(void) {
    this->reject();
}

