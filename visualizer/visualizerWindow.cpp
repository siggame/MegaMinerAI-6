#include <iostream>
#include "visualizerWindow.h"

using namespace std;


VisualizerWindow::VisualizerWindow()
{
	createActions();
	createMenus();
	createLayout();

	setWindowTitle( "Modular Visualizer" );
        //setFixedSize(800,600);

}

void VisualizerWindow::closeEvent( QCloseEvent *event )
{
	if( event ) {}
}

void VisualizerWindow::viewGameDocs()
{
	cout << "Going to game docs website" << endl;
}

void VisualizerWindow::openGamelog()
{
       //Get the gamelog's Filename:

       //todo: argument 3 should be the default directory of the game logs
       //todo: argument 4 should have the actual extention of a game log
       QString fileName = QFileDialog::getOpenFileName(this,tr("Open Game Log"),"/",tr("Log Files(*.log)"));

       //todo: use the filename to open up the gameLog object


	cout << "Opening your gamelog, sir." << endl;
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
	helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(viewGameDocsAct);
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


	gameboard = new Gameboard(0);
	QGroupBox *centralWidget = new QGroupBox;
	QToolBox *tb = new QToolBox;


	QHBoxLayout *hbox = new QHBoxLayout;
	QLabel *lbl = new QLabel( "Hello" );
	QLabel *lbl2 = new QLabel( "test" );
	tb->addItem( lbl, "too" );
	tb->addItem( lbl2, "too2" );

        hbox->addWidget(gameboard,5);

	hbox->addWidget( tb,1 );

	centralWidget->setLayout( hbox );



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

}


