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
 *	\file app.cpp
 *	\brief ogr2ogr GUI
 *	\author Olivier Pilotte[Inventis], Mohamed Hedi Lassoued[Inventis], David Tran[HSR]
 *	\version 0.7
 *	\date 13/06/14
 */

#include "app.h"

App::App(QWidget *widget) : QMainWindow(widget) {
    ogr = new Ogr();
    dbConnect = new DBConnect(this);
    wsConnect = new WebServiceConnect(this);
    initData();
    initInterface();
    translateInterface();
    initProjections();
    updateParameters();
    this->show();
}

App::~App(void) {
}

void App::initData(void) {
    QFile resFormats(":/formats");
    QFile resDatabases(":/databases");
    QFile resWebServices(":/webservices");
    readResources(resFormats, formatsListReadOnly, formatsListReadWrite);
    readResources(resDatabases, databaseListReadOnly, databaseListReadWrite);
    readResources(resWebServices, webServiceList);
}

void App::readResources(QFile &file, QList<QPair<QString, QString> > &readonlyList, QList<QPair<QString, QString> > &readwriteList) {
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
    QString line;
    QPair<QString, QString> pair;
    boolean readwrite = true;
    while(!(line = in.readLine()).isNull()) {
        QStringList t = line.split(",");
        if(line.compare(tr("#readonly")) == 0)
            readwrite = false;
        if(t.size() <= 1)
            continue;
        if(!t.at(0).isNull())
            pair.first = t.at(0);
        if(!t.at(1).isNull())
            pair.second = t.at(1);
        readonlyList << pair;
        if(readwrite)
            readwriteList << pair;
    }
    file.close();
    qSort(readwriteList.begin(), readwriteList.end());
    qSort(readonlyList.begin(), readonlyList.end());
}

void App::initProjections(void) {
    const QString file_gcs = tr("gcs.csv");
    const QString file_pcs = tr("pcs.csv");
    readProjections(file_gcs);
    readProjections(file_pcs);
    addProjections();
}

void App::readProjections(const QString filename) {
    const QString folder = tr("data");
    const QString filepath = QDir::toNativeSeparators(QCoreApplication::applicationDirPath() + QDir::separator() + folder + QDir::separator() + filename);
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox msg;
        msg.setText("* No " + filename + " file found in folder " + folder);
        msg.exec();
        return;
    }
    QTextStream in(&file);
    QString line;
    QPair<QString, QString> pair;
    in.readLine();
    while(!(line = in.readLine()).isNull()) {
        QStringList t = line.split(",");
        if(t.size() <= 1) {
            QMessageBox msg;
            msg.setText("* Wrong " + filename + " file found in folder " + folder);
            msg.exec();
            break;
        }
        if(!t.at(0).isNull())
            pair.first = t.at(0);
        if(!t.at(1).isNull())
            pair.second = t.at(1);
        projectionsList << pair;
    }
}

bool sortCOORD_REF_SYS_CODE(const QPair<QString, QString> &s1, const QPair<QString, QString> &s2) {
  return s1.first.toInt() < s2.first.toInt();
}

void App::addProjections() {
    qSort(projectionsList.begin(), projectionsList.end(), sortCOORD_REF_SYS_CODE);
    QPair<QString, QString> pair;
    projectionsList.insert(0, pair);
    cmbTargetProj->addItem(tr(""));
    for(int i=1;i<projectionsList.size();++i) {
        QPair<QString, QString> pair = projectionsList.at(i);
        cmbTargetProj->addItem(pair.first + tr(" : ") + pair.second);
    }
}

void App::initInterface(void) {
    thePanel = new QWidget();

    initMenu();
    initLayout();
    initSlots();

    radSourceFile->setChecked(true);
    radTargetFile->setChecked(true);

    this->setCentralWidget(thePanel);
}

void App::initMenu(void) {
    theMenu = new QMenuBar(this);

    {
        fileMenu = new QMenu(theMenu);
        {
            mnuExit = new QAction(this);
            mnuExit->setShortcuts(QKeySequence::Quit);

            fileMenu->addSeparator();
            fileMenu->addAction(mnuExit);
        }

        helpMenu = new QMenu(theMenu);
        {
            mnuOgr = new QAction(this);
            mnuOgr->setShortcuts(QKeySequence::HelpContents);
            mnuDoc = new QAction(this);
            mnuDoc->setShortcuts(QKeySequence::WhatsThis);
            mnuAbout = new QAction(this);

            helpMenu->addAction(mnuOgr);
            helpMenu->addAction(mnuDoc);
            helpMenu->addSeparator();
            helpMenu->addAction(mnuAbout);
        }
        theMenu->addAction(fileMenu->menuAction());
        theMenu->addAction(helpMenu->menuAction());
    }

    this->setMenuBar(theMenu);
}

void App::initLayout(void) {
    theLayout = new QVBoxLayout(thePanel);
    {
        theLayout->setMargin(7);
        theLayout->setSpacing(7);

        grpSource = new QGroupBox(thePanel);
        {
            grpSource->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

            lytSource = new QGridLayout();
            {
                lytSource->setMargin(7);
                lytSource->setSpacing(7);

                lytSourceInput = new QHBoxLayout();
                {
                    radSourceFile = new QRadioButton();
                    radSourceFolder = new QRadioButton();
                    radSourceDatabase = new QRadioButton();
                    radSourceWebService = new QRadioButton();

                    lytSourceInput->addWidget(radSourceFile);
                    lytSourceInput->addWidget(radSourceFolder);
                    lytSourceInput->addWidget(radSourceDatabase);
                    lytSourceInput->addWidget(radSourceWebService);
                }

                lytSource->addLayout(lytSourceInput, 0, 1);

                lblSourceFormat = new QLabel();
                lblSourceFormat->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
                lblSourceFormat->setMinimumWidth(70);
                lblSourceFormat->setMaximumWidth(70);

                cmbSourceFormat = new QComboBox();

                lytSource->addWidget(lblSourceFormat, 1, 0);
                lytSource->addWidget(cmbSourceFormat, 1, 1);

                lblSourceName = new QLabel();
                lblSourceName->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
                lblSourceName->setMinimumWidth(70);
                lblSourceName->setMaximumWidth(70);

                lytSourceName = new QHBoxLayout();
                {
                    txtSourceName = new QLineEdit();

                    btnSourceName = new QPushButton();

                    lytSourceName->addWidget(txtSourceName);
                    lytSourceName->addWidget(btnSourceName);
                }

                lytSource->addWidget(lblSourceName, 2, 0);
                lytSource->addLayout(lytSourceName, 2, 1);

                lblSourceProj = new QLabel();
                lblSourceProj->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
                lblSourceProj->setMinimumWidth(70);
                lblSourceProj->setMaximumWidth(70);

                txtSourceProj = new QLineEdit();
                txtSourceProj->setReadOnly(true);

                lytSource->addWidget(lblSourceProj, 3, 0);
                lytSource->addWidget(txtSourceProj, 3, 1);

                lblSourceQuery = new QLabel();
                lblSourceQuery->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
                lblSourceQuery->setMinimumWidth(70);
                lblSourceQuery->setMaximumWidth(70);

                txtSourceQuery = new QLineEdit();

                lytSource->addWidget(lblSourceQuery);
                lytSource->addWidget(txtSourceQuery);
            }

            grpSource->setLayout(lytSource);
        }

        theLayout->addWidget(grpSource);

        grpTarget = new QGroupBox(thePanel);
        {
            grpTarget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

            lytTarget = new QGridLayout();
            {
                lytTargetOutput = new QHBoxLayout();
                {
                    grpTargetOutput = new QButtonGroup();
                    {
                        radTargetFile = new QRadioButton();
                        radTargetFolder = new QRadioButton();
                        radTargetDatabase = new QRadioButton();

                        grpTargetOutput->addButton(radTargetFile);
                        grpTargetOutput->addButton(radTargetFolder);
                        grpTargetOutput->addButton(radTargetDatabase);

                        lytTargetOutput->addWidget(radTargetFile);
                        lytTargetOutput->addWidget(radTargetFolder);
                        lytTargetOutput->addWidget(radTargetDatabase);
                    }
                }

                lytTarget->addLayout(lytTargetOutput, 0, 1);

                lblTargetFormat = new QLabel();
                lblTargetFormat->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
                lblTargetFormat->setMinimumWidth(70);
                lblTargetFormat->setMaximumWidth(70);

                cmbTargetFormat = new QComboBox();

                lytTarget->addWidget(lblTargetFormat, 1, 0);
                lytTarget->addWidget(cmbTargetFormat, 1, 1);


                lblTargetName = new QLabel();
                lblTargetName->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
                lblTargetName->setMinimumWidth(70);
                lblTargetName->setMaximumWidth(70);

                lytTargetName = new QHBoxLayout();
                {
                    txtTargetName = new QLineEdit();
                    txtTargetName->setReadOnly(true);

                    btnTargetName = new QPushButton();

                    lytTargetName->addWidget(txtTargetName);
                    lytTargetName->addWidget(btnTargetName);
                }

                lytTarget->addWidget(lblTargetName, 2, 0);
                lytTarget->addLayout(lytTargetName, 2, 1);


                lblTargetProj = new QLabel();
                lblTargetProj->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
                lblTargetProj->setMinimumWidth(70);
                lblTargetProj->setMaximumWidth(70);

                lytTargetProj = new QHBoxLayout();
                {
                    txtTargetProj = new QLineEdit();
                    txtTargetProj->setMaxLength(5);
                    txtTargetProj->setMinimumWidth(50);
                    txtTargetProj->setMaximumWidth(50);
                    QValidator *validator = new QIntValidator(0, 99999, this);
                    txtTargetProj->setValidator(validator);

                    cmbTargetProj = new QComboBox();
                    cmbTargetProj->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

                    lytTargetProj->addWidget(txtTargetProj);
                    lytTargetProj->addWidget(cmbTargetProj);
                }

                lytTarget->addWidget(lblTargetProj, 3, 0);
                lytTarget->addLayout(lytTargetProj, 3, 1);

                lytTargetOptions = new QHBoxLayout();
                {
                    radTargetOverwrite = new QCheckBox();
                    radTargetAppend = new QCheckBox();
                    radTargetUpdate = new QCheckBox();

                    lytTargetOptions->addWidget(radTargetOverwrite);
                    lytTargetOptions->addWidget(radTargetAppend);
                    lytTargetOptions->addWidget(radTargetUpdate);
                }
                lytTarget->addLayout(lytTargetOptions, 4, 1);
            }
            grpTarget->setLayout(lytTarget);
        }

        theLayout->addWidget(grpTarget);

        grpOptions = new QGroupBox(thePanel);
        {
            grpOptions->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

            lytOptions = new QGridLayout();
            {
                txtInput = new QTextEdit();
                txtInput->setMaximumHeight(80);
            }
            lytOptions->addWidget(txtInput, 1, 0);
            grpOptions->setLayout(lytOptions);
        }

        theLayout->addWidget(grpOptions);

        txtOutput = new QTextEdit();
        txtOutput->setReadOnly(true);

        lytExecute = new QHBoxLayout();
        {
            btnExecute = new QPushButton();
            btnExecute->setMinimumWidth(200);

            lytExecute->addWidget(btnExecute);
        }

        theLayout->addWidget(txtOutput);
        theLayout->addLayout(lytExecute);

        progress = new QProgressBar();
        progress->setValue(0);
        progress->setMinimum(0);
        progress->setMaximum(100);
        progress->setTextVisible(false);

        theLayout->addWidget(progress);
    }

    thePanel->setLayout(theLayout);
}

void App::initSlots(void) {
    QObject::connect(mnuExit, SIGNAL(triggered()), this, SLOT(close(void)));
    QObject::connect(mnuOgr, SIGNAL(triggered()), this, SLOT(evtMnuOgrHelp(void)));
    QObject::connect(mnuDoc, SIGNAL(triggered()), this, SLOT(evtMnuGuiHelp(void)));
    QObject::connect(mnuAbout, SIGNAL(triggered()), this, SLOT(evtMnuOgrAbout(void)));

    QObject::connect(radSourceFile, SIGNAL(toggled(bool)), this, SLOT(evtRadSourceFile(void)));
    QObject::connect(radSourceFolder, SIGNAL(toggled(bool)), this, SLOT(evtRadSourceFolder(void)));
    QObject::connect(radSourceDatabase, SIGNAL(toggled(bool)), this, SLOT(evtRadSourceDatabase(void)));
    QObject::connect(radSourceWebService, SIGNAL(toggled(bool)), this, SLOT(evtRadSourceWebService(void)));

    QObject::connect(cmbSourceFormat, SIGNAL(currentIndexChanged(int)), this, SLOT(evtCmbSourceFormat(void)));
    QObject::connect(txtSourceName, SIGNAL(textChanged(QString)), this, SLOT(evtTxtSourceName(void)));
    QObject::connect(btnSourceName, SIGNAL(clicked(void)), this, SLOT(evtBtnSourceName(void)));
    QObject::connect(txtSourceQuery, SIGNAL(textChanged(QString)), this, SLOT(evtUpdateParameters(void)));
    QObject::connect(txtInput, SIGNAL(textChanged()), this, SLOT(evtUpdateParameters(void)));

    QObject::connect(radTargetFile, SIGNAL(toggled(bool)), this, SLOT(evtRadTargetFile(void)));
    QObject::connect(radTargetFolder, SIGNAL(toggled(bool)), this, SLOT(evtRadTargetFolder(void)));
    QObject::connect(radTargetDatabase, SIGNAL(toggled(bool)), this, SLOT(evtRadTargetDatabase(void)));

    QObject::connect(cmbTargetFormat, SIGNAL(currentIndexChanged(int)), this, SLOT(evtCmbTargetFormat(void)));
    QObject::connect(txtTargetName, SIGNAL(textChanged(QString)), this, SLOT(evtTxtTargetName(void)));
    QObject::connect(btnTargetName, SIGNAL(clicked()), this, SLOT(evtBtnTargetName(void)));
    QObject::connect(txtTargetProj, SIGNAL(textChanged(QString)), this, SLOT(evtTxtTargetProj(void)));
    QObject::connect(cmbTargetProj, SIGNAL(currentIndexChanged(int)), this, SLOT(evtUpdateParameters(void)));

    QObject::connect(radTargetOverwrite, SIGNAL(toggled(bool)), this, SLOT(evtUpdateParameters(void)));
    QObject::connect(radTargetAppend, SIGNAL(toggled(bool)), this, SLOT(evtUpdateParameters(void)));
    QObject::connect(radTargetUpdate, SIGNAL(toggled(bool)), this, SLOT(evtUpdateParameters(void)));

    QObject::connect(btnExecute, SIGNAL(clicked(void)), this, SLOT(evtBtnExecute(void)));

    QMetaObject::connectSlotsByName(this);
}

void App::translateInterface(void) {
    this->setWindowTitle(tr("OGR2GUI"));
    this->setWindowIcon(QIcon(":/icons/gdalicon.png"));

    fileMenu->setTitle(tr("&File"));
    {
        mnuExit->setText(tr("E&xit"));
    }

    helpMenu->setTitle(tr("&Help"));
    {
        mnuOgr->setText(tr("Command-Line Options"));
        mnuDoc->setText(tr("Documentation"));
        mnuAbout->setText(tr("About OGR2GUI"));
    }

    grpSource->setTitle(tr("Source"));
    {
        radSourceFile->setText(tr("File"));
        radSourceFolder->setText(tr("Folder"));
        radSourceDatabase->setText(tr("Database"));
        radSourceWebService->setText(tr("Web Service"));

        lblSourceFormat->setText(tr("Format"));

        lblSourceName->setText(tr("Name"));
        btnSourceName->setText(tr("Open"));

        lblSourceProj->setText(tr("Projection"));

        lblSourceQuery->setText(tr("Query"));
    }

    grpTarget->setTitle(tr("Target"));
    {
        radTargetFile->setText(tr("File"));
        radTargetFolder->setText(tr("Folder"));
        radTargetDatabase->setText(tr("Database"));

        lblTargetFormat->setText(tr("Format"));

        lblTargetName->setText(tr("Name"));
        btnTargetName->setText(tr("Save"));

        lblTargetProj->setText(tr("Projection"));

        radTargetOverwrite->setText(tr("overwrite"));
        radTargetAppend->setText(tr("append"));
        radTargetUpdate->setText(tr("update"));
    }

    grpOptions->setTitle(tr("Options (optional)"));

    btnExecute->setText(tr("Execute"));
}

void App::updateParameters(void) {
    parameters = tr("ogr2ogr");
    parameters += currentParameters();
    if(radSourceWebService->isChecked())
        parameters += tr(" ") + wsConnect->getSelectedLayers();
    if(!txtInput->toPlainText().isEmpty())
        parameters += tr(" ") + txtInput->toPlainText().simplified();
    txtOutput->setText(parameters);
    progress->setValue(0);
}

QString App::currentParameters(void) const {
    QString parameters = tr(" -f ") + tr("\"") + cmbTargetFormat->currentText() + tr("\" ");
    parameters += tr("\"") + txtTargetName->text()+ tr("\" ");
    if(radSourceWebService->isChecked() && !txtSourceName->text().isEmpty())
        parameters += webServiceList.at(cmbSourceFormat->currentIndex()).second;
    parameters += tr("\"") + txtSourceName->text().trimmed() + tr("\"");
    if(!cmbTargetProj->currentText().isEmpty())
        parameters += tr(" -t_srs EPSG:") + projectionsList.at(cmbTargetProj->currentIndex()).first;
    if(!txtSourceQuery->text().isEmpty())
        parameters += tr(" -sql ") + tr("\"") + txtSourceQuery->text() + tr("\"");
    if(radTargetOverwrite->isChecked())
        parameters += tr(" -overwrite");
    if(radTargetAppend->isChecked())
        parameters += tr(" -append");
    if(radTargetUpdate->isChecked())
        parameters += tr(" -update");
    return parameters;
}

void App::evtMnuOgrHelp(void) {
    QDesktopServices::openUrl(QUrl(tr("http://www.gdal.org/ogr2ogr.html")));
}

void App::evtMnuGuiHelp(void) {
    const QString doc = tr("file:///") + QCoreApplication::applicationDirPath() + tr("/doc/html/index.html");
    QDesktopServices::openUrl(QUrl(doc));
}

void App::evtMnuOgrAbout(void) {
    QDesktopServices::openUrl(QUrl(tr("http://www.ogr2gui.ca/")));
}

void App::evtRadSourceFile(void) {
    btnSourceName->setText(tr("Open"));

    cmbSourceFormat->clear();

    for(int i = 0; i < formatsListReadOnly.size(); ++i) {
        cmbSourceFormat->addItem(formatsListReadOnly.at(i).first);
    }

    radTargetFile->setEnabled(true);
    radTargetFolder->setEnabled(false);
    radTargetDatabase->setEnabled(true);

    if(radTargetFolder->isChecked())
        radTargetFile->setChecked(true);

    lblSourceName->setText(tr("Name"));
    txtSourceName->clear();
    txtSourceProj->clear();
    txtSourceQuery->clear();

    txtSourceProj->setEnabled(true);
    txtSourceQuery->setEnabled(true);
}

void App::evtRadSourceFolder(void) {
    btnSourceName->setText(tr("Browse"));

    cmbSourceFormat->clear();

    for(int i = 0; i < formatsListReadOnly.size(); ++i) {
        cmbSourceFormat->addItem(formatsListReadOnly.at(i).first);
    }

    radTargetFile->setEnabled(false);
    radTargetFolder->setEnabled(true);
    radTargetDatabase->setEnabled(true);

    if(radTargetFile->isChecked())
        radTargetFolder->setChecked(true);

    lblSourceName->setText(tr("Name"));
    txtSourceName->clear();
    txtSourceProj->clear();
    txtSourceQuery->clear();

    txtSourceProj->setEnabled(true);
    txtSourceQuery->setEnabled(true);
}

void App::evtRadSourceDatabase(void) {
    btnSourceName->setText(tr("Open"));

    cmbSourceFormat->clear();

    for(int i = 0; i < databaseListReadOnly.size(); ++i) {
        cmbSourceFormat->addItem(databaseListReadOnly.at(i).first);
    }

    radTargetFile->setEnabled(true);
    radTargetFolder->setEnabled(true);
    radTargetDatabase->setEnabled(true);

    lblSourceName->setText(tr("Name"));
    txtSourceName->clear();
    txtSourceProj->clear();
    txtSourceQuery->clear();

    txtSourceProj->setEnabled(true);
    txtSourceQuery->setEnabled(true);
}

void App::evtRadSourceWebService(void) {
    btnSourceName->setText(tr("Open"));

    cmbSourceFormat->clear();

    for(int i = 0; i < webServiceList.size(); ++i) {
        cmbSourceFormat->addItem(webServiceList.at(i).first);
    }

    radTargetFile->setEnabled(true);
    radTargetFolder->setEnabled(true);
    radTargetDatabase->setEnabled(true);

    lblSourceName->setText(tr("URI"));
    txtSourceProj->clear();
    txtSourceQuery->clear();

    txtSourceProj->setEnabled(true);
    txtSourceQuery->setEnabled(true);
}

void App::evtCmbSourceFormat(void) {
    txtSourceName->clear();
    txtSourceProj->clear();
    txtSourceQuery->clear();
}

void App::evtTxtSourceName(void) {
    string name = txtSourceName->text().trimmed().toStdString();
    string epsg, query, error;

    txtSourceProj->clear();
    if(radSourceWebService->isChecked())
        name = webServiceList.at(0).second.toStdString() + name;
    bool isOpen = ogr->openSource(name, epsg, query, error);
    if(isOpen) {
        for(int i = 0; i < projectionsList.size(); ++i) {
            if(strcmp(epsg.c_str(), projectionsList.at(i).first.toStdString().c_str()) == 0) {
                if(i > 1)
                    txtSourceProj->setText(projectionsList.at(i).first + tr(" : ") + projectionsList.at(i).second);
                break;
            }
        }
        ogr->closeSource();
        if(radSourceFile->isChecked())
            txtSourceQuery->setText(query.c_str());
        else if(radSourceWebService->isChecked())
            btnSourceName->setText(tr("Connected"));
    } else {
        txtSourceQuery->clear();
        if(radSourceWebService->isChecked())
            btnSourceName->setText(tr("Open"));
    }
    updateParameters();
}

void App::evtBtnSourceName(void) {
    txtSourceName->selectAll();
    txtSourceName->setFocus();
    int index = cmbSourceFormat->currentIndex();
    QString type;
    if(radSourceFile->isChecked()) {
        type = tr("\"") + formatsListReadOnly.at(index).first + tr(" (*.") + formatsListReadOnly.at(index).second + tr(")\"");
        txtSourceName->setText(QDir::toNativeSeparators(QFileDialog::getOpenFileName(this, tr("Source File"), tr(""), type)));
    } else if(radSourceFolder->isChecked()) {
        QStringList types;
        type = tr("*.") + formatsListReadOnly.at(cmbSourceFormat->currentIndex()).second;

        txtSourceName->setText(QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this, tr("Source Folder"), tr(""), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks)));
        QDir dir(txtSourceName->text());

        types.append(type);
        QStringList list = dir.entryList(types);

        if(list.size() > 1) {
            txtSourceProj->setEnabled(false);
            txtSourceQuery->setEnabled(false);
        }
    } else if(radSourceDatabase->isChecked()) {
        dbConnect->setConnectionType(databaseListReadOnly.at(index).second);
        dbConnect->showTables(true);
        if(dbConnect->exec() == QDialog::Accepted) {
            txtSourceName->setText(dbConnect->getConnectionString());
        }
        QStringList fileList;
        QStringList tables = dbConnect->getSelectedTables();
        QString connectionString = txtSourceName->text();
        connectionString.truncate(connectionString.lastIndexOf(tr("tables=")));

        for(int i = 0; i < tables.size(); ++i) {
            fileList.append(connectionString + tr("tables=") + tables.at(i));
        }
        if(fileList.size() > 1) {
            txtSourceProj->setEnabled(false);
            txtSourceQuery->setEnabled(false);
        }
    } else if(radSourceWebService->isChecked()) {
        wsConnect->setConnectionType(webServiceList.at(index).second);
        if(wsConnect->exec() == QDialog::Accepted) {
            txtSourceName->setText(wsConnect->getConnectionString());
        }
    }
    updateParameters();
}

void App::evtRadTargetFile(void) {
    btnTargetName->setText(tr("Save"));

    cmbTargetFormat->clear();
    for(int i = 0; i < formatsListReadWrite.size(); ++i) {
        cmbTargetFormat->addItem(formatsListReadWrite.at(i).first);
    }

    txtTargetName->clear();
}

void App::evtRadTargetFolder(void) {
    btnTargetName->setText(tr("Browse"));

    cmbTargetFormat->clear();
    for(int i = 0; i < formatsListReadWrite.size(); ++i) {
        cmbTargetFormat->addItem(formatsListReadWrite.at(i).first);
    }
}

void App::evtRadTargetDatabase(void) {
    btnTargetName->setText(tr("Open"));

    cmbTargetFormat->clear();
    for(int i = 0; i < databaseListReadWrite.size(); ++i) {
        cmbTargetFormat->addItem(databaseListReadWrite.at(i).first);
    }
}

void App::evtCmbTargetFormat(void) {
    txtTargetName->clear();
    updateParameters();
}

void App::evtTxtTargetName(void) {
    updateParameters();
}

void App::evtBtnTargetName(void) {
    QString type;
    int index = cmbTargetFormat->currentIndex();
    if(radTargetDatabase->isChecked()) {
        if(databaseListReadWrite.at(index).first == "SQLite") {
            type = tr("\"") + databaseListReadWrite.at(index).first + tr(" (*") + tr(".sqlite") + tr(")\"");
            txtTargetName->setText(QDir::toNativeSeparators(QFileDialog::getSaveFileName(this, tr("Save File"), tr(""), type)));
            updateParameters();
            return;
        }
        dbConnect->showTables(false);
        dbConnect->setConnectionType(databaseListReadWrite.at(cmbTargetFormat->currentIndex()).second);
        if(dbConnect->exec() == QDialog::Accepted)
            txtTargetName->setText(dbConnect->getConnectionString());
    } else if(radTargetFolder->isChecked()) {
        if(radSourceFile->isChecked()) {
            type = tr("\"") + formatsListReadWrite.at(index).first + tr(" (*.") + formatsListReadWrite.at(index).second + tr(") | *.") + formatsListReadWrite.at(index).second;
            txtTargetName->setText(QDir::toNativeSeparators(QFileDialog::getSaveFileName(this, tr("Save File"), tr(""), type)));
        } else if(radTargetFolder->isChecked()) {
            txtTargetName->setText(QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this, tr("Target Folder"), tr(""), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks)));
        }
    } else {
        type = tr("\"") + formatsListReadWrite.at(index).first + tr(" (*.") + formatsListReadWrite.at(index).second + tr(")\"");
        txtTargetName->setText(QDir::toNativeSeparators(QFileDialog::getSaveFileName(this, tr("Target File"), tr(""), type)));
    }
    updateParameters();
}

void App::evtTxtTargetProj(void) {
    const QString projection = txtTargetProj->text();
    if(projection.isEmpty()) {
        cmbTargetProj->setCurrentIndex(0);
    } else {
        for(int i = 0; i < projectionsList.size(); ++i) {
            if(projectionsList.at(i).first.startsWith(projection)) {
                cmbTargetProj->setCurrentIndex(i);
                break;
            }
        }
    }
    updateParameters();
}

void App::evtUpdateParameters(void) {
    updateParameters();
}

void App::evtBtnExecute(void) {
    updateParameters();

    QString sourcename = txtSourceName->text().trimmed();
    QString targetname = txtTargetName->text().trimmed();
    string epsg;
    string query;
    string error;

    int progressSteps = 6;
    int maxValue = 100;
    if(!ogr->openDriver(cmbTargetFormat->currentText().toStdString())) {
        txtOutput->append(tr("\n * unable to open driver !\n"));
        progress->setValue(maxValue/progressSteps);
        return;
    }
    bool resVal = true;
    QStringList fileList;
    if(radSourceWebService->isChecked()) {
        fileList = wsConnect->getSelectedLayersAsList();
        sourcename = webServiceList.at(cmbSourceFormat->currentIndex()).second + sourcename;
    }
    if(fileList.size() > 0) {
        for(int i=0; i<fileList.size(); ++i) {
            if(!ogr->openSource(sourcename.toStdString(), fileList.at(i).toStdString(), epsg, query, error)) {
                resVal = false;
                break;
            }
        }
    } else {
        resVal = ogr->openSource(sourcename.toStdString(), epsg, query, error);
    }
    if(!resVal) {
        txtOutput->append(tr("\n * unable to open source !\n"));
        progress->setValue(maxValue/progressSteps*2);
        return;
    }
    if(!txtSourceQuery->text().isEmpty()) {
        if(!ogr->testExecuteSQL(txtSourceQuery->text().toStdString())) {
            txtOutput->append(tr("\n * unable to execute sql query !\n"));
            progress->setValue(maxValue/progressSteps*3);
            return;
        }
    }
    if(txtTargetName->text().isEmpty()) {
        txtOutput->append(tr("\n * unable to open target !\n"));
        progress->setValue(maxValue/progressSteps*4);
        return;
    }
    if(!ogr->testSpatialReference((projectionsList.at(cmbTargetProj->currentIndex()).first).toInt()))
        txtOutput->append(tr("\n * unable to create spatial reference !\n"));
    if(!radSourceDatabase->isChecked() && !radSourceWebService->isChecked())
        if(!ogr->testFeatureProjection())
            txtOutput->append(tr("\n * unable to transform feature with projection !\n"));
    txtOutput->append(tr("\n") + sourcename + tr(" > ") + targetname + tr(" ... ") + tr("\n"));
    QString parameters = currentParameters();
    QString command = QDir::toNativeSeparators(QCoreApplication::applicationFilePath());
    if(radSourceWebService->isChecked())
        parameters += tr(" ") + wsConnect->getSelectedLayers();
    if(!txtInput->toPlainText().isEmpty())
        parameters += tr(" ") + txtInput->toPlainText();
    command += parameters;
    if(ogr->openOgr2ogr(command, btnExecute)) {
        progress->setValue(maxValue);
    } else {
        txtOutput->append(tr("\n * unable to open ogr2ogr !\n"));
        progress->setValue(maxValue/progressSteps*5);
    }
    ogr->closeSource();
}
