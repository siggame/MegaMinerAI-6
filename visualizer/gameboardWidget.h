#ifndef GAMEBOARDWIDGET_H
#define GAMEBOARDWIDGET_H

#include <QtGui>
#include <QtOpenGL>
#include <QTime>
#include <QTimer>
#include "texture.h"
#include "parser.h"
#include "visualizerWindow.h"
#include "visettings.h"
#include "drawGLFont.h"

class VisualizerWindow;

//#define numTextures 2
enum textures
{
	T_RED = 0,
	T_BLUE,
	T_BG,
	T_DEFAULTBG,
	T_REDFRAME,
	T_BLUEFRAME,
	T_GRID,
	T_WALL,
	T_FONT,

	numTextures

};

class Gameboard : public QGLWidget
{
	Q_OBJECT

		public:
		Gameboard( QWidget *parent );
		~Gameboard();

		void toggleMapGrid();

		bool loadBackground( QString filename );
		void clearBackground();

	private slots:
		void handleMouse();

	protected:
		void initializeGL();
		void resizeGL( int width, int height );
		void paintGL();
		void timerEvent( QTimerEvent * );
		void drawBots( Game* game, float falloff );
		void drawBackground( );
		void drawScoreboard();
		void drawMouse();
		void drawWalls( Game *game, float falloff);
		void drawFrames( Game *game, float falloff);

		void drawSprite( int x, int y, int h, int w, int texture );

		texture textures[numTextures];

		VisualizerWindow *parent;

		QTime time;
		QTime buttonTimes;

		bool hasMapGrid;
		bool hasDefaultBG;					 //default background

		void mousePressEvent( QMouseEvent *event );
		void mouseReleaseEvent( QMouseEvent *event );
		void mouseMoveEvent( QMouseEvent *event );

		DrawGLFont *drawFont;

		bool leftButtonDown;
		bool leftDoubleClick;
		bool leftButtonDrag;
		bool rightButtonDown;
		bool midButtonDown;

		int curX;
		int curY;

		int clickX;
		int clickY;

		int dragX;
		int dragY;

		int leftButtonTime;
		int rightButtonTime;
		int midButtonTime;

	public:
		int timerId;

};
#endif
