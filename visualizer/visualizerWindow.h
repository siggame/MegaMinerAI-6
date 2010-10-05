#ifndef VISUALIZERWINDOW_H
#define VISUALIZERWINDOW_H

#include <QtGui>
#include <QMainWindow>
#include "gameboardWidget.h"


//todo: seperate into seperate file and build in functionality
typedef class GameLog{};

class VisualizerWindow: public QMainWindow
{
	Q_OBJECT
public:
	VisualizerWindow();

protected:
	void closeEvent( QCloseEvent *event );

private slots:
	void openGamelog();
        void closeGameLog();
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


	Gameboard *gameboard;

        GameLog gameLog;


};


#endif
