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
 *	\mainpage OGR2GUI
 *	\section desc_sec Description
 *
 *	OGR2GUI is an application used to convert and manipulate geospatial data.
 *  It is based on ogr2ogr, a command line utility from the "Geospatial Data
 *  Abstraction Library" (gdal.org). Through its graphical user interface,
 *  OGR2GUI gives all the power of ogr2ogr without worrying about its complex
 *  syntax. It brings speed, efficiency and simplicity to its users. OGR2GUI
 *  is a free, open source project released under GPL License. Everyone in
 *  the geospatial community is invited to join. If you want to get involved
 *  in the project development, please contact us at dev@ogr2gui.ca
 *
 *	\section supp_sec Support
 *	<a href="mailto:dev@ogr2gui.ca">dev@ogr2gui.ca</a>
 */

/**
 *	\file App.h
 *	\brief Qt Application
 *	\author Olivier Pilotte [ Inventis ], Mohamed Hedi Lassoued [ Inventis ], David Tran [ HSR ]
 *	\version 0.7
 *	\date 13/06/14
 */

#ifndef APP
#define APP

#include "ogr.h"
#include "dbConnect.h"
#include "webServiceConnect.h"

QT_BEGIN_NAMESPACE

class App : public QMainWindow
{
    Q_OBJECT

private:
    Ogr *ogr;

    DBConnect *dbConnect;
    WebServiceConnect *wsConnect;

    QString parameters;

    const static int formatsCount = 47;
    QString **formats;
    const static int formatsOutput = 28;

    const static int databasesCount = 4;
    QString **databases;
    const static int databasesOutput = 2;

    const static int webServicesCount = 1;
    QString **webservices;

    QList<QPair<QString, QString> > projectionsList;

    QMenuBar *theMenu;
    QMenu *fileMenu;
    QMenu *helpMenu;

    QAction *mnuExit;
    QAction *mnuOgrHelp;
    QAction *mnuGuiHelp;
    QAction *mnuAbout;

    QProgressBar *theProgress;

    QWidget *thePanel;
    QVBoxLayout *theLayout;
    QGroupBox *grpSource;
    QGridLayout *lytSource;

    QLabel *lblSourceFormat;
    QComboBox *cmbSourceFormat;

    QHBoxLayout *lytSourceInput;
    QRadioButton *radSourceFile;
    QRadioButton *radSourceFolder;
    QRadioButton *radSourceDatabase;
    QRadioButton *radSourceWebService;

    QLabel *lblSourceName;
    QHBoxLayout *lytSourceName;
    QLineEdit *txtSourceName;
    QPushButton *btnSourceName;

    QLabel *lblSourceProj;
    QLineEdit *txtSourceProj;

    QLabel *lblSourceQuery;
    QLineEdit *txtSourceQuery;

    QGroupBox *grpTarget;
    QGridLayout *lytTarget;

    QHBoxLayout *lytTargetOutput;
    QButtonGroup *grpTargetOutput;
    QRadioButton *radTargetFile;
    QRadioButton *radTargetFolder;
    QRadioButton *radTargetDatabase;

    QLabel *lblTargetFormat;
    QComboBox *cmbTargetFormat;

    QLabel *lblTargetName;
    QHBoxLayout *lytTargetName;
    QLineEdit *txtTargetName;
    QPushButton *btnTargetName;

    QLabel *lblTargetProj;
    QHBoxLayout *lytTargetProj;
    QLineEdit *txtTargetProj;
    QComboBox *cmbTargetProj;

    QHBoxLayout *lytTargetOptions;
    QCheckBox *radTargetAppend;
    QCheckBox *radTargetOverwrite;
    QCheckBox *radTargetUpdate;

    QGroupBox *grpOptions;
    QGridLayout *lytOptions;

    QTextEdit *txtOutput;
    QTextEdit *txtInput;

    QHBoxLayout *lytExecute;
    QPushButton *btnExecute;

    /**
         *	\fn void InitData( void );
         *	\brief Inits data
         */
    void initData( void );

    /**
         *	\fn void void InitProjections( void );
         *	\brief Inits projections
         */
    void initProjections( void );

    /**
        * \fn void ReadProjections(QString filename);
        * \brief Read projections
        */
    void readProjections(QString filename);

    /**
        * \fn addProjections();
        * \brief Add Projections to UI
        */
    void addProjections();

    /**
         *	\fn void InitInterface( void );
         *	\brief Inits Interface
         */
    void initInterface( void );

    /**
         *	\fn void InitMenu( void );
         *	\brief Inits Menu
         */
    void initMenu( void );

    /**
         *	\fn void InitLayout( void );
         *	\brief Inits Layout
         */
    void initLayout( void );

    /**
         *	\fn void InitSlots( void );
         *	\brief Inits Slots
         */
    void initSlots( void );

    /**
         *	\fn void TranslateInterface( void );
         *	\brief Translates Interface
         */
    void translateInterface( void );

    /**
         *	\fn void UpdateParameters( void );
         *	\brief Updates parameters
         */
    void updateParameters( void );

    /**
         * \brief QString currentParameters(void);
         * \return QString with parameters
         */
    QString currentParameters(void);


private slots :
    void evtMnuOgrHelp( void );
    void evtMnuGuiHelp( void );
    void evtMnuOgrAbout( void );

    void evtRadSourceFile( void );
    void evtRadSourceFolder( void );
    void evtRadSourceDatabase( void );
    void evtRadSourceWebService( void );

    void evtCmbSourceFormat( void );
    void evtTxtSourceName( void );
    void evtBtnSourceName( void );

    void evtRadTargetFile( void );
    void evtRadTargetFolder( void );
    void evtRadTargetDatabase( void );

    void evtCmbTargetFormat( void );
    void evtTxtTargetName( void );
    void evtBtnTargetName( void );
    void evtTxtTargetProj( void );

    void evtUpdateParameters( void );

    void evtBtnExecute( void );

public:

    /**
         *	\fn App( QWidget * = 0 );
         *	\brief Constructor
         */
    App( QWidget * = 0 );

    /**
         *	\fn ~App
         *	\brief Destructor
         */
    ~App( void );
};

QT_END_NAMESPACE

#endif
