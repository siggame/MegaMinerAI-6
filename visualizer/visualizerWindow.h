#ifndef VISUALIZERWINDOW_H
#define VISUALIZERWINDOW_H

#include <QtGui>
#include <QMainWindow>
#include "gameboardWidget.h"

class VisualizerWindow: public QMainWindow
{
	Q_OBJECT
public:
	VisualizerWindow();

protected:
	void closeEvent( QCloseEvent *event );

private slots:
	void openGamelog();

private:
	void createMenus();
	void createLayout();
	void createActions();

	QMenu *fileMenu;
	QMenu *viewMenu;
	QMenu *helpMenu;

	QAction *openGameAct;


	Gameboard *gameboard;
};


#endif
