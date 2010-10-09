#ifndef VISUALIZERWINDOW_H
#define VISUALIZERWINDOW_H

#include <QtGui>
#include <QSlider>
#include <QMainWindow>
#include "gameboardWidget.h"
#include "parser.h"
#include "statsDialog.h"

class Gameboard;

class UnitSelection: public QWidget
{
	Q_OBJECT
public:

};

class Scoreboard: public QWidget
{
	Q_OBJECT
public:

};

class VisualizerWindow: public QMainWindow
{
	Q_OBJECT
public:
	VisualizerWindow();
	GameState *getFrame( int frame = -1 );
	void loadGamelog( char *filename );

	Game *gamelog;
	QSlider *controlBar;
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

	void controlBarDrag();
	void controlBarChanged(int frame);

private:
	void createMenus();
	void createLayout();
	void createActions();

	QMenu *fileMenu;
	QMenu *viewMenu;
	QMenu *helpMenu;

	QFrame *bottomBar;
	QTextEdit *console;
	QTabWidget *toolBox;

	Scoreboard *scoreboard;
	UnitSelection *unitSelection;


	QAction *viewGameDocsAct;
	QAction *openGameAct;
	QAction *closeGameAct;
	QAction *toggleFullScreenAct;
	QAction *exitAct;


	Gameboard *gameboard;
};


#endif
