#ifndef GAMEBOARDWIDGET_H
#define GAMEBOARDWIDGET_H

#include <QtGui>
#include <QtOpenGL>
#include <QTime>
#include "texture.h"
#include "parser.h"
#include "visualizerWindow.h"
#include "visettings.h"

class VisualizerWindow;

enum textures
{
	T_SPRITE = 0

};

class Gameboard : public QGLWidget
{
	Q_OBJECT

public:
	Gameboard( QWidget *parent );
	~Gameboard();

protected:
	void initializeGL();
	void resizeGL( int width, int height );
	void paintGL();
	void timerEvent( QTimerEvent * );

	void drawSprite( int x, int y, int h, int w, int texture );

	texture textures[1];

	VisualizerWindow *parent;
	
	QTime time;

private:
	int timerId;

};


#endif
