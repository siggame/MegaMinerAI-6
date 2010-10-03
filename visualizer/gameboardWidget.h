#ifndef GAMEBOARDWIDGET_H
#define GAMEBOARDWIDGET_H

#include <QtGui>

#include <QtOpenGL>

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

private:
	int timerId;

};


#endif
