#ifndef VISUALIZERWINDOW_H
#define VISUALIZERWINDOW_H

#include <QtGui>
#include <QMainWindow>
#include <QProcess>
#include <list>
#include "gameboardWidget.h"



//todo: seperate into seperate file and build in functionality
typedef class  Frame{};

class VisualizerWindow: public QMainWindow
{
	Q_OBJECT
public:
	VisualizerWindow();

protected:
	void closeEvent( QCloseEvent *event );

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


	Gameboard *gameboard;

        std::list<Frame> gameLog;

};


#endif
