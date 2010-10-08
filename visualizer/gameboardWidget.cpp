#include "gameboardWidget.h"


Gameboard::Gameboard( QWidget *parent )
	: QGLWidget( QGLFormat(QGL::SampleBuffers),parent )
{
	// This timer tells us when to repaint the gameboard.
	// 20 milliseconds or microseconds, I'm not sure
	timerId = startTimer(20);
        setFixedSize(500,500);

}

Gameboard::~Gameboard()
{

	// cleanup Everything
	//
}

void Gameboard::initializeGL()
{
	glShadeModel(GL_SMOOTH);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);


	glEnable( GL_TEXTURE_2D );
	sprite.loadImage( "sprite.bmp" );
	
}

void Gameboard::resizeGL( int w, int h )
{
	h = h?h:1;

	glViewport( 0, 0, (GLint)w, (GLint)h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Gameboard::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	static int r = 0;

	glTranslatef(-1.5f,0.0f,-6.0f);

	//glRotatef( r++, 0, 1, 0 );
	glBegin(GL_TRIANGLES);
		glVertex3f( 0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f,-1.0f, 0.0f);
		glVertex3f( 1.0f,-1.0f, 0.0f);
	glEnd(); 

	glTranslatef(3.0f,0.0f,0.0f);

	glEnable( GL_TEXTURE_2D );

	glBindTexture( GL_TEXTURE_2D, sprite.getTexture() );
	glBegin(GL_QUADS);


	glTexCoord2f( 0, 1 );
	glVertex3f(-1.0f, 1.0f, 0.0f);
	glTexCoord2f( 1, 1 );
	glVertex3f( 1.0f, 1.0f, 0.0f);
	glTexCoord2f( 1, 0 );
	glVertex3f( 1.0f,-1.0f, 0.0f);
	glTexCoord2f( 0, 0 );
	glVertex3f(-1.0f,-1.0f, 0.0f);
	glEnd();   
}	


void Gameboard::timerEvent( QTimerEvent *)
{
	update();
}

