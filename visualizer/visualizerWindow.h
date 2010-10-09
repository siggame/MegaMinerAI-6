#ifndef VISUALIZERWINDOW_H
#define VISUALIZERWINDOW_H

#include <QtGui>
#include <QSlider>
#include <QMainWindow>
#include "gameboardWidget.h"
#include "parser.h"
#include "statsDialog.h"

class Gameboard;

class VisualizerWindow: public QMainWindow
{
	Q_OBJECT
public:
	VisualizerWindow();
	GameState *getFrame( int frame = -1 );

	Game *gamelog;
	int frameNumber; 

protected:
	void closeEvent( QCloseEvent *event );

	bool fullScreen;

private slots:
	void openGamelog();
	void closeGamelog();
	void exitProgram(); 
	void toggleFullScreen();

// Help File
	void viewGameDocs();

private:
	void createMenus();
	void createLayout();
	void createActions();

	StatsDialog *statsDialog;

	QMenu *fileMenu;
	QMenu *viewMenu;
	QMenu *helpMenu;

	QAction *viewGameDocsAct;
	QAction *openGameAct;
	QAction *closeGameAct;
	QAction *toggleFullScreenAct;
	QAction *exitAct;


	Gameboard *gameboard;
	QSlider *controlBar;
};


#endif
