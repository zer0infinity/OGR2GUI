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
 *	\file settings.h
 *	\brief Settings
 *	\author David Tran
 *	\version 0.8
 */

#ifndef _SETTINGS_H
#define _SETTINGS_H

#include <QtWidgets>
#include "i18n.h"

QT_BEGIN_NAMESPACE

class Settings : public QDialog {
    Q_OBJECT
private:
    QString language;
    QVariant gcs, pcs, gcsoverride, pcsoverride;

    QVBoxLayout *theLayout;
    QHBoxLayout *lytDialog;
    QPushButton *btnOK;
    QPushButton *btnCancel;
    QComboBox *cmbLang;
    QLabel *lblLang;
    QLabel *lblProj;
    QGridLayout *lytLang;
    QGridLayout *lytFile;
    QCheckBox *ckbGcs;
    QCheckBox *ckbPcs;
    QCheckBox *ckbGcsOverride;
    QCheckBox *ckbPcsOverride;

    QList<QPair<QString, QString> > languageList;

    /**
         *	\fn void initLanguage(void);
         *	\brief Inits Language
         */
    void initSettings(void);

    /**
         *	\fn void initInterface(void);
         *	\brief Inits Interface
         */
    void initInterface(void);

    /**
         *	\fn void InitSlots(void);
         *	\brief Inits Slots
         */
    void initSlots(void);

    /**
         *	\fn isFile(const QString filename);
         *	\brief is 'filename' a file?
         */
    bool isFile(const QString filename);

public slots:
    void evtBtnOK(void);
    void evtBtnCancel(void);
public:
    /**
         *	\fn Settings(QWidget * = 0);
         *	\brief Constructor
         */
    Settings(QWidget * = 0);

    /**
         *	\fn ~Settings(void);
         *	\brief Destructor
         */
    ~Settings(void);

    /**
         *	\fn void translateInterface(void);
         *	\brief Translates Interface
         */
    void translateInterface(void);

    /**
         *	\fn void initFile(void);
         *	\brief Inits File
         */
    void initFiles(void);

    /**
         *	\fn QStringList getFileList(void);
         *	\brief Get list with filenames
         */
    QStringList getProjectionFileList(void);
};

QT_END_NAMESPACE

#endif
