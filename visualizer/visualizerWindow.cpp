#include <iostream>
#include "visualizerWindow.h"

using namespace std;


VisualizerWindow::VisualizerWindow()
{
	setGeometry( 0, 0, 1280, 1024 );
	createActions();
	createMenus();
	createLayout();

	setWindowTitle( "Modular Visualizer" );
	fullScreen = false;
	gamelog = 0;
}

void VisualizerWindow::closeEvent( QCloseEvent *event )
{
	if( event ) {}
}

void VisualizerWindow::viewGameDocs()
{
	//experement:
	QProcess webPage;
	//todo: Need to make this cross platform
	webPage.start(tr("firefox.exe"),QStringList(tr("mail.google.com")));

	cout << "Going to game docs website" << endl;
}

GameState *VisualizerWindow::getFrame( int frame )
{
	if( frame == -1 )
		frame = getAttr(frameNumber);
	return &gamelog->states[frame];
}

bool VisualizerWindow::loadGamelog( char *filename )
{
    Game * temp = new Game;

    if ( filename == NULL )
        return false;

    if ( !parseFile( *temp, filename ) )
        return false;

    if( gamelog )
            delete gamelog;

    gamelog = temp;

    controlSlider->setMaximum( gamelog->states.size() );

    return true;
}

void VisualizerWindow::openGamelog()
{
    //Get the gamelog's Filename:


    //todo: argument 3 should be the default directory of the game logs
    //todo: argument 4 should have the actual extention of a game log
       QString fileName = QFileDialog::getOpenFileName(this,tr("Open Game Log"),"~/",tr("Log Files(*.gamelog)"));

       if ( !loadGamelog( (char *)fileName.toLocal8Bit().constData() ))
       {
            QMessageBox::critical(this,"Error","Game Log Failed to Open");
       }

}

void VisualizerWindow::toggleFullScreen()
{

	if( !fullScreen )
		showFullScreen();
	else
		showNormal();
	fullScreen = !fullScreen;
	show();
}

void VisualizerWindow::toggleMapGrid()
{
    gameboard->toggleMapGrid();
}

void VisualizerWindow::clearBackground()
{
    gameboard->clearBackground();
}

void VisualizerWindow::loadBackground()
{
   QString filename = QFileDialog::getOpenFileName( this,"Open Background","~/","Images(*.png)" );

   if ( filename == tr("") )
      return;

   if ( !gameboard->loadBackground( filename ) )
   {
       QMessageBox::critical( this, "Error", "The file you selected for a background wouldn't load" );
   }

}

void VisualizerWindow::closeGamelog()
{
   //todo: clear out the game log and recover all allocated memory
}

void VisualizerWindow::exitProgram()
{
   //clear out the game log, recover all allocated memory
   closeGamelog();

   //exit the program
   QApplication::quit();
}



void VisualizerWindow::createMenus()
{

	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(openGameAct);
	fileMenu->addAction(closeGameAct);
	fileMenu->addAction(exitAct);

	viewMenu = menuBar()->addMenu(tr("&View"));
	viewMenu->addAction(toggleFullScreenAct);
        viewMenu->addAction(toggleMapGridAct);
        viewMenu->addAction(loadBackgroundAct);
        viewMenu->addAction(clearBackgroundAct);


	helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(viewGameDocsAct);
}

void VisualizerWindow::controlSliderDrag()
{
	setAttr( dragging, true );
}

void VisualizerWindow::controlSliderReleased()
{
	setAttr( dragging, false );
}

void VisualizerWindow::controlSliderChanged(int frame)
{
	if( getAttr( dragging ) )
		setAttr( frameNumber, frame ); 
}

void VisualizerWindow::createLayout()
{
	// Remove awkward spacing around the edges
	setContentsMargins( 0, 0, 0, 0 );
	layout()->setContentsMargins( 0, 0, 0, 0 );
	QGLFormat f = QGLFormat::defaultFormat();
	f.setSampleBuffers(true);
	QGLFormat::setDefaultFormat(f);
	if (!QGLFormat::hasOpenGL())
	{
		QMessageBox::information( 0, "Opengl", "SYSTEM DOES NOT SUPPORT OPENGL", QMessageBox::Ok);
		return;
	}

	controlSlider = new QSlider(Qt::Horizontal);
	gameboard = new Gameboard(this);
	QFrame *centralWidget = new QFrame;

	QHBoxLayout *debugLayout = new QHBoxLayout;
	console = new QTextEdit;
	toolBox = new QTabWidget;
	bottomBar = new QFrame;
        controlBar = new QFrame;
	scoreboard = new Scoreboard;
	unitSelection = new UnitSelection;
        playButton = new QPushButton("Play");
        rewindButton = new QPushButton("<<");
        fastForwardButton = new QPushButton(">>");
        stopButton = new QPushButton("Stop");

        // Creates the layout for the controlBar
        QHBoxLayout *controlLayout = new QHBoxLayout;
        controlLayout->addWidget(playButton);
        controlLayout->addWidget(rewindButton);
        controlLayout->addWidget(fastForwardButton);
        controlLayout->addWidget(stopButton);
        controlLayout->addWidget(controlSlider);
        controlBar->setLayout(controlLayout);

	toolBox->addTab( scoreboard, tr( "Scoreboard" ) );
	toolBox->addTab( unitSelection, tr( "Unit Stats" ) );
	

	debugLayout->addWidget( console );
	debugLayout->addWidget( toolBox );
	
	bottomBar->setLayout( debugLayout );

	bottomBar->setFixedHeight( 250 );

	QVBoxLayout *vbox = new QVBoxLayout;
	vbox->setContentsMargins( 0, 0, 0, 0 );
	debugLayout->setContentsMargins( 0, 0, 0, 0 );

	controlBar->setFixedHeight( 45 );
	controlSlider->setTickInterval( 50 );
	controlSlider->setTickPosition( QSlider::TicksBothSides );
	controlSlider->setMaximum( 0 );
	controlSlider->setMinimum( 0 );
	controlSlider->setTracking( true );

	connect( controlSlider, SIGNAL(sliderPressed()), this, SLOT(controlSliderDrag()));
	connect( controlSlider, SIGNAL(sliderReleased()), this, SLOT(controlSliderReleased()));
	connect( controlSlider, SIGNAL(valueChanged(int)), this, SLOT(controlSliderChanged(int)));

  vbox->addWidget(gameboard, 4);
	vbox->addWidget(bottomBar, 2);
	vbox->addWidget(controlBar, 1);


	centralWidget->setLayout( vbox );
	setCentralWidget( centralWidget );
}

void VisualizerWindow::createActions()
{
	openGameAct = new QAction(tr("&Open Game Log"), this);
	openGameAct->setShortcut(tr("Ctrl+O"));
	openGameAct->setStatusTip(tr("Open a Game Log"));
	connect( openGameAct, SIGNAL(triggered()), this, SLOT(openGamelog()));

	closeGameAct = new QAction(tr("&Close Gamelog"),this);
	openGameAct->setStatusTip(tr("Close the current Game Log"));
	connect( closeGameAct, SIGNAL(triggered()), this, SLOT(closeGamelog()));

	exitAct = new QAction(tr("&Exit"),this);
	exitAct->setShortcut(tr("Ctrl+Q"));
	exitAct->setStatusTip(tr("Exit the program"));
	connect( exitAct, SIGNAL(triggered()), this, SLOT(exitProgram()));

	viewGameDocsAct = new QAction( tr("View &Game Documents"), this);
	viewGameDocsAct->setShortcut(tr("F1"));
	viewGameDocsAct->setStatusTip(tr("Documents Related to the Competition"));
	connect( viewGameDocsAct, SIGNAL(triggered()), this, SLOT(viewGameDocs()));

	toggleFullScreenAct = new QAction( tr("&Full Screen"), this );
	toggleFullScreenAct->setShortcut( tr("F11" ) );
	toggleFullScreenAct->setStatusTip( tr("Toggle Fullscreen Mode") );
	connect( toggleFullScreenAct, SIGNAL(triggered()), this, SLOT(toggleFullScreen()) );

        //todo: give this a shortcut key
        toggleMapGridAct = new QAction( tr("Toggle Grid"), this );
        toggleMapGridAct->setCheckable( true );
        toggleMapGridAct->setStatusTip( tr("Toggle the grid on the map") );
        connect( toggleMapGridAct, SIGNAL(triggered()), this, SLOT(toggleMapGrid()) );


        loadBackgroundAct = new QAction( tr("Load Background"), this );
        loadBackgroundAct->setStatusTip( tr("Load a new picture as the background") );
        connect( loadBackgroundAct, SIGNAL(triggered()), this, SLOT(loadBackground()) );


        clearBackgroundAct = new QAction( tr("Clear Background"), this );
        clearBackgroundAct->setStatusTip( tr("Go back to the default background") );
        connect( clearBackgroundAct, SIGNAL(triggered()), this, SLOT(clearBackground()) );

}


