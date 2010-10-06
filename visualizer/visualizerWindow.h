#ifndef VISUALIZERWINDOW_H
#define VISUALIZERWINDOW_H

#include <QtGui>
#include <QMainWindow>
#include "gameboardWidget.h"
#include "parser.h"





class VisualizerWindow: public QMainWindow
{
	Q_OBJECT
public:
	VisualizerWindow();
	GameState *getFrame( int frame = -1 );

protected:
	void closeEvent( QCloseEvent *event );
	int frameNumber; 

private slots:
	void openGamelog();
	void closeGamelog();
	void exitProgram(); 

// Help File
	void viewGameDocs();

private:
	void createMenus();
	void createLayout();
	void createActions();

	QMenu *fileMenu;
	QMenu *viewMenu;
	QMenu *helpMenu;

	QAction *viewGameDocsAct;
	QAction *openGameAct;
	QAction *closeGameAct;
	QAction *exitAct;

	Game gamelog;

        Gameboard *gameboard;
};


#endif
