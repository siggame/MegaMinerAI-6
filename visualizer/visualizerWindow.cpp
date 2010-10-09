#include <iostream>
#include "visualizerWindow.h"

using namespace std;


VisualizerWindow::VisualizerWindow()
{
	setGeometry( 0, 0, 1200, 1000 );
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

void VisualizerWindow::loadGamelog( char *filename )
{
		if( gamelog )
			delete gamelog;
		gamelog = new Game;
    parseFile( *gamelog, filename  );

		controlBar->setMaximum( gamelog->states.size() );
}

void VisualizerWindow::openGamelog()
{
    //Get the gamelog's Filename:


    //todo: argument 3 should be the default directory of the game logs
    //todo: argument 4 should have the actual extention of a game log
       QString fileName = QFileDialog::getOpenFileName(this,tr("Open Game Log"),"~/",tr("Log Files(*.gamelog)"));

			 loadGamelog( (char *)fileName.toLocal8Bit().constData() );

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

	helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(viewGameDocsAct);
}

void VisualizerWindow::controlBarDrag()
{
	setAttr( dragging, true );
}

void VisualizerWindow::controlBarReleased()
{
	setAttr( dragging, false );
}

void VisualizerWindow::controlBarChanged(int frame)
{
	if( getAttr( dragging ) )
		setAttr( frameNumber, frame ); 
}

void VisualizerWindow::createLayout()
{
	QGLFormat f = QGLFormat::defaultFormat();
	f.setSampleBuffers(true);
	QGLFormat::setDefaultFormat(f);
	if (!QGLFormat::hasOpenGL())
	{
		QMessageBox::information( 0, "Opengl", "SYSTEM DOES NOT SUPPORT OPENGL", QMessageBox::Ok);
		return;
	}

	controlBar = new QSlider(Qt::Horizontal);
	gameboard = new Gameboard(this);
	QGroupBox *centralWidget = new QGroupBox;

	QHBoxLayout *debugLayout = new QHBoxLayout;
	console = new QTextEdit;
	toolBox = new QTabWidget;
	bottomBar = new QFrame;
	scoreboard = new Scoreboard;
	unitSelection = new UnitSelection;

	toolBox->addTab( scoreboard, tr( "Scoreboard" ) );
	toolBox->addTab( unitSelection, tr( "Unit Stats" ) );
	

	debugLayout->addWidget( console );
	debugLayout->addWidget( toolBox );
	
	bottomBar->setLayout( debugLayout );

	bottomBar->setFixedHeight( 250 );

	QVBoxLayout *vbox = new QVBoxLayout;

	controlBar->setFixedHeight( 15 );
	controlBar->setTickInterval( 50 );
	controlBar->setTickPosition( QSlider::TicksBothSides );
	controlBar->setMaximum( 0 );
	controlBar->setMinimum( 0 );
	controlBar->setTracking( true );

	connect( controlBar, SIGNAL(sliderPressed()), this, SLOT(controlBarDrag()));
	connect( controlBar, SIGNAL(sliderReleased()), this, SLOT(controlBarReleased()));
	connect( controlBar, SIGNAL(valueChanged(int)), this, SLOT(controlBarChanged(int)));

  vbox->addWidget(gameboard, 4);
	vbox->addWidget(bottomBar, 2);
	//todo: Change this to control layout and add play, pause buttons
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


}


