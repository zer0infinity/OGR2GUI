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
 *	\file langSettings.h
 *	\brief Language settings
 *	\author David Tran [HSR]
 *	\version 0.7
 */

#ifndef _LANGSETTINGS_H
#define _LANGSETTINGS_H

#include <QtWidgets>
#include "i18n.h"

QT_BEGIN_NAMESPACE

class LangSettings : public QDialog {
    Q_OBJECT
private:
    QString language;

    QVBoxLayout *theLayout;
    QHBoxLayout *lytDialog;
    QPushButton *btnOK;
    QPushButton *btnCancel;
    QComboBox *cmbLang;
    QLabel *lblLang;
    QGridLayout *lytLang;

    QList<QPair<QString, QString> > languageList;

    /**
         *	\fn void initLanguage(void);
         *	\brief Inits Language
         */
    void initLanguage(void);

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
    void evtBtnOK(void);
    void evtBtnCancel(void);
public:
    /**
         *	\fn LangSettings(QWidget * = 0);
         *	\brief Constructor
         */
    LangSettings(QWidget * = 0);

    /**
         *	\fn ~LangSettings(void);
         *	\brief Destructor
         */
    ~LangSettings(void);

    /**
         *	\fn void TranslateInterface(void);
         *	\brief Translates Interface
         */
    void translateInterface(void);
};

QT_END_NAMESPACE

#endif
