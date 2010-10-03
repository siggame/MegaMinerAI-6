#include <iostream>
using namespace std;
#include "visualizerWindow.h"

VisualizerWindow::VisualizerWindow()
{
	createActions();
	createMenus();
	createLayout();	

	setWindowTitle( "Modular Visualizer" );
}

void VisualizerWindow::closeEvent( QCloseEvent *event )
{
	if( event ) {}
}

void VisualizerWindow::openGamelog()
{
	cout << "Opening your gamelog, sir." << endl;
}

void VisualizerWindow::createMenus()
{
	
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(openGameAct);

	viewMenu = menuBar()->addMenu(tr("&View"));
	helpMenu = menuBar()->addMenu(tr("&Help"));
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
	openGameAct = new QAction(tr("&Open Gamelog"), this);
	openGameAct->setShortcut(tr("Ctrl+O"));
	openGameAct->setStatusTip(tr("Open a Gamelog"));
	connect( openGameAct, SIGNAL(triggered()), this, SLOT(openGamelog()));
}
