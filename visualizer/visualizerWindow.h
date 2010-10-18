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
		bool loadGamelog( char *filename );

		Game *gamelog;
		QSlider *controlSlider;
		QPushButton *playButton;
		QPushButton *rewindButton;
		QPushButton *fastForwardButton;
		QPushButton *stopButton;
	protected:
		void closeEvent( QCloseEvent *event );

		bool fullScreen;

	private slots:
		void openGamelog();
		void closeGamelog();
		void exitProgram();
		void toggleFullScreen();
		void toggleMapGrid();
		void loadBackground();
		void clearBackground();

		// Help File
		void viewGameDocs();

		void controlSliderDrag();
		void controlSliderReleased();
		void controlSliderChanged(int frame);

	private:
		void createMenus();
		void createLayout();
		void createActions();

		QMenu *fileMenu;
		QMenu *viewMenu;
		QMenu *helpMenu;

		QFrame *bottomBar;
		QFrame *controlBar;
		QTextEdit *console;
		QTabWidget *toolBox;

		Scoreboard *scoreboard;
		UnitSelection *unitSelection;

		QAction *viewGameDocsAct;
		QAction *openGameAct;
		QAction *closeGameAct;
		QAction *toggleFullScreenAct;
		QAction *toggleMapGridAct;
		QAction *loadBackgroundAct;
		QAction *clearBackgroundAct;

		QAction *exitAct;

		Gameboard *gameboard;
};
#endif
