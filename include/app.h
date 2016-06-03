/*****************************************************************************
 * OGR2GUI is an application used to convert and manipulate geospatial
 * data. It is based on the "OGR Simple Feature Library" from the
 * "Geospatial Data Abstraction Library" <http://gdal.org>.
 *
 * Copyright (c) 2009 Inventis <mailto:developpement@inventis.ca>
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
 *	\file app.h
 *	\brief ogr2ogr GUI
 *	\author Olivier Pilotte [Inventis], Mohamed Hedi Lassoued [Inventis], David Tran
 *	\version 0.8
 */

#ifndef APP
#define APP

#include "ogr.h"
#include "dbConnect.h"
#include "webServiceConnect.h"
#include "settings.h"

QT_BEGIN_NAMESPACE

class App : public QMainWindow
{
    Q_OBJECT

private:
    Ogr *ogr;
    DBConnect *dbConnect;
    WebServiceConnect *wsConnect;
    Settings *settings;

    QString parameters;
    QString sourceProjInit;

    QList<QPair<QString, QString> > formatsListReadWrite;
    QList<QPair<QString, QString> > formatsListReadOnly;
    QList<QPair<QString, QString> > databaseListReadWrite;
    QList<QPair<QString, QString> > databaseListReadOnly;
    QList<QPair<QString, QString> > webServiceList;
    QList<QPair<QString, QString> > projectionsList;

    QMenuBar *theMenu;
    QMenu *fileMenu;
    QMenu *helpMenu;

    QAction *mnuSettings;
    QAction *mnuExit;
    QAction *mnuOgr;
    QAction *mnuDoc;
    QAction *mnuAbout;

    QProgressBar *progress;

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
    QLabel *lblSourceEPSG;
    QHBoxLayout *lytSourceProj;
    QLineEdit *txtSourceProj;
    QLineEdit *txtSourceProjInit;
    QComboBox *cmbSourceProj;

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

    QLabel *lblTargetSpat;
    QHBoxLayout *lytTargetSpat;
    QTableWidget *tabTargetSpat;
    QPushButton *btnTargetSpat;

    QHBoxLayout *lytTargetOptions;
    QCheckBox *radTargetAppend;
    QCheckBox *radTargetOverwrite;
    QCheckBox *radTargetUpdate;
    QCheckBox *radTargetSkipfailures;

    QGroupBox *grpOptions;
    QGridLayout *lytOptions;

    QTextEdit *txtOptionOutput;
    QTextEdit *txtOption;

    QHBoxLayout *lytExecute;
    QPushButton *btnConvert;

    /**
         *	\fn void InitData(void);
         *	\brief Inits data
         */
    void initData(void);

    /**
     * \fn void readResources(const QFile file, QList<QPair<QString, QString> > &readonlyList, QList<QPair<QString, QString> > &readwriteList);
     * \brief Read Resources
     * \param file : resource file
     * \param readonlyList : read file into readonly list
     * \param readwriteList : read file into readwrite list
     */
    void readResources(QFile &file, QList<QPair<QString, QString> > &readonlyList, QList<QPair<QString, QString> > &readwriteList = QList<QPair<QString, QString> >());

    /**
         *	\fn void void InitProjections(void);
         *	\brief Inits projections
         */
    void initProjectionFiles(void);

    /**
        * \fn void ReadProjections(QString filename);
        * \brief Read projections
        */
    void readProjections(const QString filename);

    /**
        * \fn addProjections();
        * \brief Add Projections to UI
        */
    void initProjection();

    /**
         *	\fn void InitInterface(void);
         *	\brief Inits Interface
         */
    void initInterface(void);

    /**
         *	\fn void InitMenu(void);
         *	\brief Inits Menu
         */
    void initMenu(void);

    /**
         *	\fn void InitLayout(void);
         *	\brief Inits Layout
         */
    void initLayout(void);

    /**
         *	\fn void InitSlots(void);
         *	\brief Inits Slots
         */
    void initSlots(void);

    /**
         *	\fn void TranslateInterface(void);
         *	\brief Translates Interface
         */
    void translateInterface(void);

    /**
         *	\fn void UpdateParameters(void);
         *	\brief Updates parameters
         */
    void updateParameters(void);

    /**
         * \brief QString currentParameters(void);
         * \return QString with parameters
         */
    QString currentParameters(void) const;


private slots :
    void evtMnuSettings(void);
    void evtMnuOgrHelp(void);
    void evtMnuGuiHelp(void);
    void evtMnuOgrAbout(void);

    void evtRadSourceFile(void);
    void evtRadSourceFolder(void);
    void evtRadSourceDatabase(void);
    void evtRadSourceWebService(void);

    void evtCmbSourceFormat(void);
    void evtTxtSourceName(void);
    void evtBtnSourceName(void);
    void evtTxtSourceProj(void);
    void evtCmbSourceProj(void);

    void evtRadTargetFile(void);
    void evtRadTargetFolder(void);
    void evtRadTargetDatabase(void);

    void evtCmbTargetFormat(void);
    void evtTxtTargetName(void);
    void evtBtnTargetName(void);
    void evtTxtTargetProj(void);
    void evtBtnTargetSpat(void);

    void evtUpdateParameters(void);

    void evtBtnExecute(void);

public:

    /**
         *	\fn App(QWidget * = 0);
         *	\brief Constructor
         */
    App(QWidget * = 0);

    /**
         *	\fn ~App
         *	\brief Destructor
         */
    ~App(void);
};

QT_END_NAMESPACE

#endif
