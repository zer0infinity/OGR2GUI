/*****************************************************************************
 *	ogr2gui is an application used to convert and manipulate geospatial
 *	data. It is based on the "OGR Simple Feature Library" from the 
 *	"Geospatial Data Abstraction Library" <http://gdal.org>.
 *
 *	Copyright (c) 2009 Inventis <mailto:developpement@inventis.ca>
 *
 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <http://www.gnu.org/licenses/>
 *****************************************************************************/

/*!
 *	\file App.cpp
 *	\brief Qt Application
 *	\author Olivier Pilotte [ Inventis ], Mohamed Hedi Lassoued [ Inventis ]
 *	\version 0.6
 *	\date 27/10/09
 */

#include "../inc/App.h"

App::App( QWidget *widget ) : QMainWindow( widget )
{
	InitData();

	InitInterface();

	TranslateInterface();

	InitProjections();

	UpdateParameters();
}

App::~App( void )
{
	delete [] *formats;
	delete [] *databases;
	delete [] *projections;
}

void App::InitData( void )
{
	ogr = new Ogr();

	formats = new QString * [ formatsCount ];
		
	for( int i = 0; i < formatsCount; i ++ )
	{
		formats[ i ] = new QString[ 2 ];
	}

	databases = new QString * [ databasesCount ];

	for( int i = 0; i < databasesCount; i ++ )
	{
		databases[ i ] = new QString[ 2 ];
	}

	projections = new QString*[ projectionsCount ];
	
	for( int i = 0; i < projectionsCount; i ++ )
	{
		projections[ i ] = new QString[ 2 ];
	}

	#include "../inc/Dta.h"	
}

void App::InitProjections( void )
{
	QString prj;
	
	cmbTargetProj->addItem( tr( "" ) );

	for( int i = 1; i < projectionsCount; i ++ )
	{
		prj.clear();
		prj = projections[ i ][ 0 ];
		prj.append( tr( " : " ) );
		prj.append( projections[ i ][ 1 ] );

		cmbTargetProj->addItem( prj );
	}
}

void App::InitInterface( void )
{
	thePanel = new QWidget();

	inf = new Inf( this );


	InitMenu();

	InitLayout();

	InitSlots();


	radSourceFile->setChecked( true );
	
	radTargetFile->setChecked( true );

	radTargetOverwrite->setChecked( true );
	
	btnExecute->setEnabled( false );


	this->setCentralWidget( thePanel );

	this->show();
}

void App::InitMenu( void )
{
	theMenu = new QMenuBar( this );
	{
		fileMenu = new QMenu( theMenu );
		{
			mnuQuit = new QAction( this );

			fileMenu->addAction( mnuQuit );
		}
		
		helpMenu = new QMenu( theMenu );
		{
			mnuOgrHelp = new QAction( this );
			mnuGuiHelp = new QAction( this );
			mnuAbout = new QAction( this );

			helpMenu->addAction( mnuOgrHelp );
			helpMenu->addAction( mnuGuiHelp );
			helpMenu->addSeparator();
			helpMenu->addAction( mnuAbout );
		}

		theMenu->addAction( fileMenu->menuAction() );
		theMenu->addAction( helpMenu->menuAction() );
	}
	
	this->setMenuBar( theMenu );
}

void App::InitLayout( void )
{
	theLayout = new QVBoxLayout( thePanel );
	{
		theLayout->setMargin( 7 );
		theLayout->setSpacing( 7 );

		grpSource = new QGroupBox( thePanel );
		{
			grpSource->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Fixed );

			lytSource = new QGridLayout();
			{
				lytSource->setMargin( 7 );
				lytSource->setSpacing( 7 );

				lytSourceInput = new QHBoxLayout();
				{
					radSourceFile = new QRadioButton();
					radSourceFolder = new QRadioButton();
					radSourceDatabase = new QRadioButton();

					lytSourceInput->addWidget( radSourceFile );
					lytSourceInput->addWidget( radSourceFolder );
					lytSourceInput->addWidget( radSourceDatabase );
				}

				lytSource->addLayout( lytSourceInput, 0, 1 );

				lblSourceFormat = new QLabel();
				lblSourceFormat->setAlignment( Qt::AlignRight | Qt::AlignVCenter );
				lblSourceFormat->setMinimumWidth( 70 );
				lblSourceFormat->setMaximumWidth( 70 );

				cmbSourceFormat = new QComboBox();

				lytSource->addWidget( lblSourceFormat, 1, 0 );
				lytSource->addWidget( cmbSourceFormat, 1, 1 );

				lblSourceName = new QLabel();
				lblSourceName->setAlignment( Qt::AlignRight | Qt::AlignVCenter );
				lblSourceName->setMinimumWidth( 70 );
				lblSourceName->setMaximumWidth( 70 );

				lytSourceName = new QHBoxLayout();
				{
					txtSourceName = new QLineEdit();
					txtSourceName->setReadOnly( true );

					btnSourceName = new QPushButton();

					lytSourceName->addWidget( txtSourceName );
					lytSourceName->addWidget( btnSourceName );
				}

				lytSource->addWidget( lblSourceName, 2, 0 );
				lytSource->addLayout( lytSourceName, 2, 1 );
				
				lblSourceProj = new QLabel();
				lblSourceProj->setAlignment( Qt::AlignRight | Qt::AlignVCenter );
				lblSourceProj->setMinimumWidth( 70 );
				lblSourceProj->setMaximumWidth( 70 );

				txtSourceProj = new QLineEdit();
				txtSourceProj->setReadOnly( true );

				lytSource->addWidget( lblSourceProj, 3, 0 );
				lytSource->addWidget( txtSourceProj, 3, 1 );

				lblSourceQuery = new QLabel();
				lblSourceQuery->setAlignment( Qt::AlignRight | Qt::AlignVCenter );
				lblSourceQuery->setMinimumWidth( 70 );
				lblSourceQuery->setMaximumWidth( 70 );

				txtSourceQuery = new QLineEdit();

				lytSource->addWidget( lblSourceQuery );
				lytSource->addWidget( txtSourceQuery );
			}
			
			grpSource->setLayout( lytSource );
		}

		theLayout->addWidget( grpSource );

		grpTarget = new QGroupBox( thePanel );
		{
			grpTarget->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Fixed );

			lytTarget = new QGridLayout();
			{
				lytTargetOutput = new QHBoxLayout();
				{
					grpTargetOutput = new QButtonGroup();
					{
						radTargetFile = new QRadioButton();
						radTargetFolder = new QRadioButton();
						radTargetDatabase = new QRadioButton();

						grpTargetOutput->addButton( radTargetFile );
						grpTargetOutput->addButton( radTargetFolder );
						grpTargetOutput->addButton( radTargetDatabase );

						lytTargetOutput->addWidget( radTargetFile );
						lytTargetOutput->addWidget( radTargetFolder );
						lytTargetOutput->addWidget( radTargetDatabase );
					}
				}

				lytTarget->addLayout( lytTargetOutput, 0, 1 );


				lblTargetFormat = new QLabel();
				lblTargetFormat->setAlignment( Qt::AlignRight | Qt::AlignVCenter );
				lblTargetFormat->setMinimumWidth( 70 );
				lblTargetFormat->setMaximumWidth( 70 );

				cmbTargetFormat = new QComboBox();
		
				lytTarget->addWidget( lblTargetFormat, 1, 0 );
				lytTarget->addWidget( cmbTargetFormat, 1, 1 );


				lblTargetName = new QLabel();
				lblTargetName->setAlignment( Qt::AlignRight | Qt::AlignVCenter );
				lblTargetName->setMinimumWidth( 70 );
				lblTargetName->setMaximumWidth( 70 );

				lytTargetName = new QHBoxLayout();
				{
					txtTargetName = new QLineEdit();
					txtTargetName->setReadOnly( true );

					btnTargetName = new QPushButton();

					lytTargetName->addWidget( txtTargetName );
					lytTargetName->addWidget( btnTargetName );
				}

				lytTarget->addWidget( lblTargetName, 2, 0 );
				lytTarget->addLayout( lytTargetName, 2, 1 );


				lblTargetProj = new QLabel();
				lblTargetProj->setAlignment( Qt::AlignRight | Qt::AlignVCenter );
				lblTargetProj->setMinimumWidth( 70 );
				lblTargetProj->setMaximumWidth( 70 );

				lytTargetProj = new QHBoxLayout();
				{
					txtTargetProj = new QLineEdit();
					txtTargetProj->setMaxLength( 5 );
					txtTargetProj->setMinimumWidth( 50 );
					txtTargetProj->setMaximumWidth( 50 );
					
					cmbTargetProj = new QComboBox();
					cmbTargetProj->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Fixed );

					lytTargetProj->addWidget( txtTargetProj );
					lytTargetProj->addWidget( cmbTargetProj );
				}

				lytTarget->addWidget( lblTargetProj, 3, 0 );
				lytTarget->addLayout( lytTargetProj, 3, 1 );

				lytTargetOptions = new QHBoxLayout();
				{
					grpTargetOptions = new QButtonGroup();
					{
						radTargetOverwrite = new QRadioButton();
						radTargetAppend = new QRadioButton();
						radTargetUpdate = new QRadioButton();

						lytTargetOptions->addWidget( radTargetOverwrite );
						lytTargetOptions->addWidget( radTargetAppend );						
						lytTargetOptions->addWidget( radTargetUpdate );

						grpTargetOptions->addButton( radTargetOverwrite );
						grpTargetOptions->addButton( radTargetAppend );
						grpTargetOptions->addButton( radTargetUpdate );
					}
				}

				lytTarget->addLayout( lytTargetOptions, 4, 1 );
			}

			grpTarget->setLayout( lytTarget );
		}

		theLayout->addWidget( grpTarget );

		txtOutput = new QTextEdit();
		txtOutput->setReadOnly( true );

		lytExecute = new QHBoxLayout();
		{
			btnExecute = new QPushButton();
			btnExecute->setMinimumWidth( 200 );
			btnExecute->setEnabled( false );
			
			btnQuit = new QPushButton();
			btnQuit->setMinimumWidth( 200 );

			lytExecute->addWidget( btnExecute );
			lytExecute->addWidget( btnQuit );
		}

		theLayout->addWidget( txtOutput );
		theLayout->addLayout( lytExecute );

		theProgress = new QProgressBar();

		theLayout->addWidget( theProgress );
	}

	thePanel->setLayout( theLayout );
}

void App::InitSlots( void )
{
	QObject::connect( mnuQuit, SIGNAL( activated() ), this, SLOT( close( void ) ) );

	QObject::connect( mnuOgrHelp, SIGNAL( activated() ), this, SLOT( evtMnuOgrHelp( void ) ) );

	QObject::connect( mnuGuiHelp, SIGNAL( activated() ), this, SLOT( evtMnuGuiHelp( void ) ) );

	QObject::connect( mnuAbout, SIGNAL( activated() ), this, SLOT( evtMnuAbout( void ) ) );


	QObject::connect( radSourceFile, SIGNAL( toggled( bool ) ), this, SLOT( evtRadSourceFile( void ) ) );

	QObject::connect( radSourceFolder, SIGNAL( toggled( bool ) ), this, SLOT( evtRadSourceFolder( void ) ) );

	QObject::connect( radSourceDatabase, SIGNAL( toggled( bool ) ), this, SLOT( evtRadSourceDatabase( void ) ) );


	QObject::connect( cmbSourceFormat, SIGNAL( currentIndexChanged( int ) ), this, SLOT( evtCmbSourceFormat( int ) ) );

	QObject::connect( txtSourceName, SIGNAL( textChanged( QString ) ), this, SLOT( evtTxtSourceName( void ) ) );

	QObject::connect( btnSourceName, SIGNAL( clicked( void ) ), this, SLOT( evtBtnSourceName( void ) ) );

	QObject::connect( txtSourceQuery, SIGNAL( textChanged( QString ) ), this, SLOT( evtTxtSourceQuery( void ) ) );


	QObject::connect( radTargetFile, SIGNAL( toggled( bool ) ), this, SLOT( evtRadTargetFile( void ) ) );

	QObject::connect( radTargetFolder, SIGNAL( toggled( bool ) ), this, SLOT( evtRadTargetFolder( void ) ) );

	QObject::connect( radTargetDatabase, SIGNAL( toggled( bool ) ), this, SLOT( evtRadTargetDatabase( void ) ) );


	QObject::connect( cmbTargetFormat, SIGNAL( currentIndexChanged( int ) ), this, SLOT( evtCmbTargetFormat( void ) ) );

	QObject::connect( txtTargetName, SIGNAL( textChanged( QString ) ), this, SLOT( evtTxtTargetName( void ) ) );

	QObject::connect( btnTargetName, SIGNAL( clicked() ), this, SLOT( evtBtnTargetName( void ) ) );

	QObject::connect( txtTargetProj, SIGNAL( textChanged( QString ) ), this, SLOT( evtTxtTargetProj( void ) ) );

	QObject::connect( cmbTargetProj, SIGNAL( currentIndexChanged( int ) ), this, SLOT( evtCmbTargetProj( void ) ) );


	QObject::connect( radTargetOverwrite, SIGNAL( toggled( bool ) ), this, SLOT( evtRadTargetOverwrite( void ) ) );

	QObject::connect( radTargetAppend, SIGNAL( toggled( bool ) ), this, SLOT( evtRadTargetAppend( void ) ) );

	QObject::connect( radTargetUpdate, SIGNAL( toggled( bool ) ), this, SLOT( evtRadTargetUpdate( void ) ) );


	QObject::connect( btnExecute, SIGNAL( clicked( void ) ), this, SLOT( evtBtnExecute( void ) ) );

	QObject::connect( btnQuit, SIGNAL( clicked( void ) ), this, SLOT( evtBtnQuit( void ) ) );


	QMetaObject::connectSlotsByName( this );
}


void App::TranslateInterface( void )
{
    this->setWindowTitle( tr( "ogr2gui - Inventis" ) );

	fileMenu->setTitle( tr( "&File" ) );
	{
		mnuQuit->setText( tr( "&Quit" ) );
	}

    helpMenu->setTitle( tr( "&Help" ) );
	{
		mnuOgrHelp->setText( tr( "&ogr2ogr" ) );
		mnuGuiHelp->setText( tr( "ogr&2gui" ) );
		
		mnuAbout->setText( tr( "&About" ) );
	}

	grpSource->setTitle( tr( "Source" ) );
	{
		radSourceFile->setText( tr( "File" ) );
		radSourceFolder->setText( tr( "Folder" ) );
		radSourceDatabase->setText( tr( "Database" ) );

		lblSourceFormat->setText( tr( "Format" ) );

		lblSourceName->setText( tr( "Name" ) );
		btnSourceName->setText( tr( "&Open" ) );

		lblSourceProj->setText( tr( "Projection" ) );

		lblSourceQuery->setText( tr( "Query" ) );
	}

	grpTarget->setTitle( tr( "Target" ) );
	{
		radTargetFile->setText( tr( "File" ) );
		radTargetFolder->setText( tr( "Folder" ) );
		radTargetDatabase->setText( tr( "Database" ) );

		lblTargetFormat->setText( tr( "Format" ) );

		lblTargetName->setText( tr( "Name" ) );
		btnTargetName->setText( tr( "&Save" ) );

		lblTargetProj->setText( tr( "Projection" ) );

		radTargetOverwrite->setText( tr( "overwrite" ) );
		radTargetAppend->setText( tr( "append" ) );
		radTargetUpdate->setText( tr( "update" ) );
	}

	btnExecute->setText( tr( "&Execute" ) );
	btnQuit->setText( tr( "&Quit" ) );
}


void App::UpdateParameters( void )
{
	parameters = tr( "ogr2ogr" ) + tr( " -f \"" ) + cmbTargetFormat->currentText() + tr( "\" " );

	if( radTargetOverwrite->isChecked() )
	{
		parameters += tr( "-overwrite" );
	}
	
	if( radTargetAppend->isChecked() )
	{
		parameters += tr( "-append" );
	}

	if( radTargetUpdate->isChecked() )
	{
		parameters += tr( "-update" );
	}

	parameters += tr( " \"" ) + txtTargetName->text() + tr( "\" \"" ) + txtSourceName->text() + tr( "\" " );

	if( ! cmbTargetProj->currentText().isEmpty() )
	{
		parameters += tr( "-T_SRS EPSG:" ) + projections[ cmbTargetProj->currentIndex() ][ 0 ] + tr( " " );
	}

	if( ! txtSourceQuery->text().isEmpty() )
	{
		parameters += tr( "-sql \"" ) + txtSourceQuery->text() + tr( "\" " );
	}

	for( int i = 0; i < ( int ) parameters.size(); i ++ )
	{
		if( parameters.at( i ) == '\\' )
		{
			parameters[ i ] = '/';
		}
	}

	parameters += tr( "\n" );

	txtOutput->setText( parameters );
}


void App::evtMnuOgrHelp( void )
{
	QDesktopServices::openUrl( QUrl( tr( "http://gdal.org/ogr" ) ) );
}

void App::evtMnuGuiHelp( void )
{
	QDesktopServices::openUrl( QUrl( tr( "http://www.ogr2gui.ca/0.5/doc/index.html" ) ) );
}

void App::evtMnuAbout( void )
{
	QDesktopServices::openUrl( QUrl( tr( "http://www.ogr2gui.ca/" ) ) );
}


void App::evtRadSourceFile( void )
{
	btnSourceName->setText( tr( "&Open" ) );

	cmbSourceFormat->clear();

	for( int i = 0; i < formatsCount; i ++ )
	{
		cmbSourceFormat->addItem( formats[ i ][ 0 ] );
	}

	radTargetFile->setEnabled( true );
	radTargetFolder->setEnabled( false );
	radTargetDatabase->setEnabled( true );

	radTargetFile->setChecked( true );

	txtSourceName->clear();
	txtSourceProj->clear();
	txtSourceQuery->clear();

	txtSourceProj->setEnabled( true );
	txtSourceQuery->setEnabled( true );
}

void App::evtRadSourceFolder( void )
{
	btnSourceName->setText( tr( "&Browse" ) );

	cmbSourceFormat->clear();

	for( int i = 0; i < formatsCount; i ++ )
	{
		cmbSourceFormat->addItem( formats[ i ][ 0 ] );
	}

	radTargetFile->setEnabled( false );
	radTargetFolder->setEnabled( true );
	radTargetDatabase->setEnabled( true );

	radTargetFolder->setChecked( true );

	txtSourceName->clear();
	txtSourceProj->clear();
	txtSourceQuery->clear();

	txtSourceProj->setEnabled( true );
	txtSourceQuery->setEnabled( true );
}

void App::evtRadSourceDatabase( void )
{
	btnSourceName->setText( tr( "&Connect" ) );

	cmbSourceFormat->clear();

	for( int i = 0; i < databasesCount; i ++ )
	{
		cmbSourceFormat->addItem( databases[ i ][ 0 ] );
	}

	radTargetFile->setEnabled( true );
	radTargetFolder->setEnabled( true );
	radTargetDatabase->setEnabled( true );

	radTargetFile->setChecked( true );

	txtSourceName->clear();
	txtSourceProj->clear();
	txtSourceQuery->clear();

	txtSourceProj->setEnabled( true );
	txtSourceQuery->setEnabled( true );
}


void App::evtCmbSourceFormat( int i )
{
	txtSourceName->clear();

	txtSourceProj->clear();

	txtSourceQuery->clear();

	UpdateParameters();
}


void App::evtTxtSourceName( void )
{
	if( txtSourceName->text().startsWith( tr( "file://" ) ) )
	{
		txtSourceName->setText( QUrl( txtSourceName->text() ).authority().trimmed() );
	}

	string name = txtSourceName->text().toStdString();
	string epsg;
	string query;
	string error;

	if( ogr->OpenSource( name, epsg, query, error ) )
	{
		for( int i = 0; i < projectionsCount; i ++ )
		{
			if( strcmp( epsg.c_str(), projections[ i ][ 0 ].toStdString().c_str() ) == 0 )
			{
				if( i > 1 )
				{
					txtSourceProj->setText( projections[ i ][ 0 ] + tr( " : " ) + projections[ i ][ 1 ] );
				}

				break;
			}
		}

		ogr->CloseSource();

		if( radSourceFile->isChecked() )
		{
			txtSourceQuery->setText( query.c_str() );
		}
	}
	else
	{
		txtSourceProj->clear();
		txtSourceQuery->clear();
	}

	UpdateParameters();
}

void App::evtBtnSourceName( void )
{
	int idx = cmbSourceFormat->currentIndex();

	QString type;

	if( radSourceFile->isChecked() )
	{
		type = tr( "\"" ) + formats[ idx ][ 0 ] + tr( "\" | *." ) + formats[ idx ][ 1 ];

		txtSourceName->setText( QFileDialog::getOpenFileName( this, tr( "Source File" ), tr( "" ), type ) );

		fileList.clear();

		fileList.append( txtSourceName->text() );
	}
	else if( radSourceFolder->isChecked() )
	{
		QStringList types;

		type = tr( "*." ) + formats[ cmbSourceFormat->currentIndex() ][ 1 ];

		txtSourceName->setText( QFileDialog::getExistingDirectory( this, tr( "Source Folder" ), tr( "" ), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks ) );

		QDir dir( txtSourceName->text() );

		types.append( type );

		QStringList list = dir.entryList( types );

		fileList.clear();

		for( int i = 0; i < list.size(); i ++ )
		{
			fileList.append( list.at( i ) );
		}

		if( list.size() > 1 )
		{
			txtSourceProj->setEnabled( false );
			txtSourceQuery->setEnabled( false );
		}
	}
	else if( radSourceDatabase->isChecked() )
	{
		inf->setConnectionType( databases[ idx ][ 1 ] );

		inf->setDialogStyle( 1 );

		if( inf->exec() == QDialog::Accepted )
		{
			txtSourceName->setText( inf->getConnectionString() );
		}

		fileList.clear();

		QStringList tables = inf->getSelectedTables();

		QString connectionString = txtSourceName->text();

		connectionString.truncate( connectionString.lastIndexOf( tr( "tables=" ) ) );

		for( int i = 0; i < tables.size(); i ++ )
		{
			fileList.append( connectionString + tr( "tables=" ) + tables.at( i ) );
		}

		if( fileList.size() > 1 )
		{
			txtSourceProj->setEnabled( false );
			txtSourceQuery->setEnabled( false );

			radTargetFile->setEnabled( false );
			radTargetFolder->setChecked( true );
		}
		else
		{
			radTargetFile->setEnabled( true );
			radTargetFile->setChecked( true );
		}
	}
}

void App::evtTxtSourceQuery( void )
{
	UpdateParameters();
}


void App::evtRadTargetFile( void )
{
	btnTargetName->setText( tr( "&Save" ) );

	cmbTargetFormat->clear();

	for( int i = 0; i < formatsOutput; i ++ )
	{
		cmbTargetFormat->addItem( formats[ i ][ 0 ] );
	}

	txtTargetName->clear();
	txtTargetProj->clear();

	cmbTargetProj->setCurrentIndex( 0 );
}

void App::evtRadTargetFolder( void )
{
	btnTargetName->setText( tr( "&Browse" ) );

	cmbTargetFormat->clear();

	for( int i = 0; i < formatsOutput; i ++ )
	{
		cmbTargetFormat->addItem( formats[ i ][ 0 ] );
	}
}

void App::evtRadTargetDatabase( void )
{
	btnTargetName->setText( tr( "&Connect" ) );

	cmbTargetFormat->clear();

	for( int i = 0; i < databasesOutput; i ++ )
	{
		cmbTargetFormat->addItem( databases[ i ][ 0 ] );
	}
}

void App::evtCmbTargetFormat( void )
{
	txtTargetName->clear();
}

void App::evtTxtTargetName( void )
{
	btnExecute->setEnabled( true );

	UpdateParameters();
}

void App::evtBtnTargetName( void )
{
	QString type;

	int idx = cmbTargetFormat->currentIndex();

	if( radTargetDatabase->isChecked() )
	{
		inf->setDialogStyle( 0 );

		inf->setConnectionType( databases[ cmbTargetFormat->currentIndex() ][ 1 ] );

		if( inf->exec() == QDialog::Accepted )
		{
			txtTargetName->setText( inf->getConnectionString() );
		}
	}
	else if( radTargetFolder->isChecked() )
	{
		if( radSourceFile->isChecked() )
		{
			type = tr( "\"" ) + formats[ idx ][ 0 ] + tr( " (*." ) + formats[ idx ][ 1 ] + tr( ") | *." ) + formats[ idx ][ 1 ];

			txtTargetName->setText( QFileDialog::getSaveFileName( this, tr( "Save File" ), tr( "" ), type ) );
		}
		else if( radTargetFolder->isChecked() )
		{
			txtTargetName->setText( QFileDialog::getExistingDirectory( this, tr( "Target Folder" ), tr( "" ), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks ) );
		}		
	}
	else
	{
		type = tr( "\"" ) + formats[ idx ][ 0 ] + tr( "\" | *." ) + formats[ idx ][ 1 ];

		txtTargetName->setText( QFileDialog::getSaveFileName( this, tr( "Target File" ), tr( "" ), type ) );
	}

	btnExecute->setEnabled( true );
}

void App::evtTxtTargetProj( void )
{
	QString projection = txtTargetProj->text();

	for( int i = 0; i < projectionsCount; i ++ )
	{
		if( ( projections[ i ][ 0 ] ).startsWith( projection ) )
		{
			cmbTargetProj->setCurrentIndex( i );

			break;
		}
	}

	UpdateParameters();
}

void App::evtCmbTargetProj( void )
{
	UpdateParameters();
}

void App::evtRadTargetAppend( void )
{
	UpdateParameters();
}

void App::evtRadTargetOverwrite( void )
{
	UpdateParameters();
}

void App::evtRadTargetUpdate( void )
{
	UpdateParameters();
}

void App::evtBtnExecute( void )
{
	QString name;
	QString sourcename;
	QString targetname;

	string epsg;
	string query;
	string error;

	int featuresCount = 0;
	int progress = 0;

	txtOutput->clear();

	for( int i = 0; i < fileList.size(); i ++ )
	{
		if( radSourceFile->isChecked() )
		{
			sourcename = txtSourceName->text();
			targetname = txtTargetName->text();
		}
		else if( radSourceFolder->isChecked() )
		{
			sourcename = txtSourceName->text() + tr( "/" ) + fileList.at( i );
			targetname = txtTargetName->text();
		}
		else if( radSourceDatabase->isChecked() )
		{
			sourcename = fileList.at( i );
			targetname = txtTargetName->text();
		}

		txtOutput->append( QString( sourcename + tr( " > " ) + targetname + tr( " ... " ) ) );

		if( ogr->OpenSource( sourcename.toStdString(), epsg, query, error ) )
		{
			if( ogr->OpenDriver( cmbTargetFormat->currentText().toStdString(), error ) )
			{
				if( ogr->OpenTarget( targetname.toStdString(), atoi( projections[ cmbTargetProj->currentIndex() ][ 0 ].toStdString().c_str() ) ) )
				{
					ogr->Prepare( featuresCount, "" );

					theProgress->setMinimum( 0 );
					theProgress->setMaximum( featuresCount );
					theProgress->setValue( 0 );	

					while( ogr->Process() )
					{
						progress ++;

						theProgress->setValue( progress );
					}
					
					ogr->CloseTarget();
					ogr->CloseSource();

					theProgress->setValue( 0 );

					txtOutput->append( tr( "successful.\n" ) );
				}
				else
				{
					txtOutput->append( tr( "\n * unable to open target !\n" ) );
				}
			}
			else
			{
				txtOutput->append( tr( "\n * unable to open driver !\n" ) );
			}
		}
		else
		{
			txtOutput->append( tr( "\n * unable to open source !\n" ) );
		}
	}
}

void App::evtBtnQuit( void )
{
	this->close();
}

int main( int argc, char **argv )
{
	QApplication app( argc, argv );

	new App();

	return app.exec();
}
