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

	textures[T_SPRITE].loadImage( "sprite.png" );

	
}

void Gameboard::drawSprite( int x, int y, int w, int h, int texture )
{

	if( texture == -1 )
		glDisable( GL_TEXTURE_2D );
	else 
	{
		glEnable( GL_TEXTURE_2D ); 
		glBindTexture( GL_TEXTURE_2D, textures[texture].getTexture() );
	}

	glLoadIdentity();
	glTranslatef( x, y, 0 );
	glScalef( w, h, 0 );

	glBegin(GL_QUADS);
	glTexCoord2f( 0, 0 );
	glVertex3f(0, 1.0f, 0);
	glTexCoord2f( 1, 0 );
	glVertex3f( 1.0f, 1.0f, 0);
	glTexCoord2f( 1, 1 );
	glVertex3f( 1.0f,0, 0);
	glTexCoord2f( 0, 1 );
	glVertex3f(0,0,0);
	glEnd();   



}

void Gameboard::resizeGL( int w, int h )
{
	h = h?h:1;

	glViewport( 0, 0, (GLint)w, (GLint)h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,100.0f);
	glOrtho( 0, w, h, 0, 0, 10 );

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

	glBindTexture( GL_TEXTURE_2D, textures[T_SPRITE].getTexture() );

	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA ); 

	//glLoadIdentity();
	//glScalef( 50, 50, 1 );
	//drawSprite( 150, 250, T_SPRITE );

	for( int i = 0; i < 25; i++ )
	{
		for( int j= 0; j < 25; j++ )
		{
			drawSprite( i*50, j*50,50,50, T_SPRITE );
		}
	}
}	


void Gameboard::timerEvent( QTimerEvent *)
{
	update();
}

