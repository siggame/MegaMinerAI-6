#include "gameboardWidget.h"

#include <iostream>



Gameboard::Gameboard( QWidget *prt )
	: QGLWidget( QGLFormat(QGL::SampleBuffers),prt)
{
	// This timer tells us when to repaint the gameboard.
	// 20 milliseconds or microseconds, I'm not sure
	

	initializeGL();
	// This makes it about 50 Frames Per Second
	timerId = startTimer(15);
	parent = ((VisualizerWindow*)prt);
	time.start();
  //setFixedSize(500,500);

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

	textures[T_SPRITE].loadImage( "megaman.png" );
	textures[T_BG].loadImage( "background.png" );

	
}

void Gameboard::drawSprite( int x, int y, int w, int h, int texture )
{

	glBindTexture( GL_TEXTURE_2D, textures[texture].getTexture() );
	glPushMatrix();
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
	glPopMatrix();



}

void Gameboard::resizeGL( int w, int h )
{
	h = h?h:1;
	//cout << "resize" << endl;

	glViewport( 0, 0, (GLint)w, (GLint)h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,100.0f);
	glOrtho( 0, w, h, 0, 0, 10 );

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void Gameboard::drawBots()
{
	
	int frame = getAttr(frameNumber);
	int unitSize = getAttr( unitSize );

	int x0, y0, x1, y1;
	float falloff = 0;

	if( parent->gamelog )
	{

		Game *game = parent->gamelog;
		if( time.elapsed() > getAttr(playSpeed) && !getAttr(dragging) )
		{

			time.restart();
			if( frame < (int)game->states.size() )
				setAttr( frameNumber, ++frame );
			parent->controlBar->blockSignals(true);
			parent->controlBar->setSliderPosition( frame );
			parent->controlBar->blockSignals(false);
		}

		falloff = (float)time.elapsed()/getAttr(playSpeed);

		for( std::vector<Bot>::iterator i = game->states[frame].bots.begin(); i != game->states[frame].bots.end(); i++ )
		{
			
			x0 = x1 = i->x*unitSize;
			y0 = y1 = i->y*unitSize;
			if( frame+1 < game->states.size() )
			{
				
				for( std::vector<Bot>::iterator j = game->states[frame+1].bots.begin(); j!= game->states[frame+1].bots.end(); j++ )
				{
					if( j->id == i->id )
					{
						x1 = j->x*unitSize;
						y1 = j->y*unitSize;
						break;
					}
				}
				
				
			} 

			drawSprite( x0+(x1-x0)*falloff,y0+(y1-y0)*falloff,unitSize,unitSize, T_SPRITE );

		} 
	}

	
}

void Gameboard::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, textures[T_BG].getTexture() );

	glBegin( GL_QUADS );

	glTexCoord2f( 0, 0 );
	glVertex3f( 0, 0, 0 );
	glTexCoord2f( 20, 0 );
	glVertex3f( 1280, 0, 0 );
	glTexCoord2f( 20, 10 );
	glVertex3f( 1280, 640, 0 );
	glTexCoord2f( 0, 10 );
	glVertex3f( 0, 640, 0 );

	glEnd();

	drawBots();
}	


void Gameboard::timerEvent( QTimerEvent *)
{
	update();
}

