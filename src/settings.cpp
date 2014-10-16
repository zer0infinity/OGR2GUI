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
 *	\file settings.cpp
 *	\brief Settings
 *	\author David Tran [HSR]
 *	\version 0.7
 */

#include "settings.h"

Settings::Settings(QWidget *parent) : QDialog(parent) {
    initInterface();
    initSlots();
    translateInterface();
    initLanguage();

    this->setWindowModality(Qt::ApplicationModal);
    this->setMinimumWidth(280);
}

Settings::~Settings(void) {
}

void Settings::initLanguage(void) {
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

    QSettings settings("ogr2gui.ini", QSettings::IniFormat);
    QVariant lang = settings.value("language");
    for(int i = 0; i < languageList.size(); ++i) {
        QPair<QString, QString> language = languageList.at(i);
        cmbLang->addItem(language.first);
        if(language.second.compare(lang.toString()) == 0)
            cmbLang->setCurrentIndex(i);
    }
}

void Settings::initInterface(void) {
    theLayout = new QVBoxLayout(this);
    {
        lytLang = new QGridLayout();
        {
            lblLang = new QLabel();
            lblLang->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            lblLang->setMinimumSize(70, 20);
            lblLang->setMaximumSize(70, 20);

            cmbLang = new QComboBox();

            lytLang->addWidget(lblLang, 1, 0);
            lytLang->addWidget(cmbLang, 1, 1);
        }

        lytFile = new QGridLayout();
        {
            lblProj = new QLabel();
            lblProj->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            lblProj->setMinimumSize(70, 20);
            lblProj->setMaximumSize(70, 20);
            ckbGcsPcs = new QCheckBox;
            ckbGcsPcs->setChecked(true);
            ckbGcsOverride = new QCheckBox;
            ckbPcsOverride = new QCheckBox;

            lytFile->addWidget(lblProj, 1, 0);
            lytFile->addWidget(ckbGcsPcs, 1, 1);
            lytFile->addWidget(ckbGcsOverride, 2, 1);
            lytFile->addWidget(ckbPcsOverride, 3, 1);
        }

        lytDialog = new QHBoxLayout();
        {
            btnOK = new QPushButton();
            btnCancel = new QPushButton();

            lytDialog->addWidget(btnOK);
            lytDialog->addWidget(btnCancel);
        }

        theLayout->addLayout(lytLang);
        theLayout->addLayout(lytFile);
        theLayout->addLayout(lytDialog);
    }

    this->setLayout(theLayout);
}

void Settings::initSlots(void) {
    QObject::connect(btnCancel, SIGNAL(clicked()), this, SLOT(evtBtnCancel(void)));
    QObject::connect(btnOK, SIGNAL(clicked()), this, SLOT(evtBtnOK(void)));
}

void Settings::translateInterface(void) {
    this->setWindowTitle(tr("Settings"));

    lblLang->setText(tr("Language"));
    lblProj->setText(tr("Projection"));
    ckbGcsPcs->setText("gcs.csv/pcs.csv");
    ckbGcsOverride->setText("gcs.override.csv");
    ckbPcsOverride->setText("pcs.override.csv");
    btnOK->setText(tr("Save"));
    btnCancel->setText(tr("Cancel"));
}

void Settings::evtBtnOK(void) {
    language = languageList.at(cmbLang->currentIndex()).second;
    QSettings settings("ogr2gui.ini", QSettings::IniFormat);
    settings.setValue("language", language);
    I18N *i18n = I18N::getInstance();
    i18n->translate(language);
    this->accept();
}

void Settings::evtBtnCancel(void) {
    this->reject();
}

void Settings::initFiles(void) {
    const QString gcs = "gcs.csv", pcs = "pcs.csv";
    const QString gcsOverride = "gcs.override.csv", pcsOverride = "pcs.override.csv";
    if(isFile(gcs) && isFile(pcs))
        ckbGcsPcs->setEnabled(true);
    else
        ckbGcsPcs->setEnabled(false);
    if(isFile(gcsOverride))
        ckbGcsOverride->setEnabled(true);
    else
        ckbGcsOverride->setEnabled(false);
    if(isFile(pcsOverride))
        ckbPcsOverride->setEnabled(true);
    else
        ckbPcsOverride->setEnabled(false);
}

bool Settings::isFile(const QString filename) {
    const QString folder = "data";
    const QString absolutePath = QDir::toNativeSeparators(QCoreApplication::applicationDirPath() + QDir::separator() + folder + QDir::separator() + filename);
    QFile file(absolutePath);
    return file.exists();
}

QStringList Settings::getProjectionFileList(void) {
    QStringList fileList;
    if(ckbGcsPcs->isChecked()) {
        const QString gcs = "gcs.csv", pcs = "pcs.csv";
        if(isFile(gcs))
            fileList << gcs;
        if(isFile(pcs))
            fileList << pcs;
    }
    if(ckbGcsOverride->isChecked() && ckbGcsOverride->isEnabled())
        fileList << "gcs.override.csv";
    if(ckbPcsOverride->isChecked() && ckbPcsOverride->isEnabled())
        fileList << "pcs.override.csv";
    return fileList;
}
