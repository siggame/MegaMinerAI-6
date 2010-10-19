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

	hasMapGrid = false;
	hasDefaultBG = true;

}


Gameboard::~Gameboard()
{

	// cleanup Everything
	//
}


void Gameboard::initializeGL()
{
	glShadeModel(GL_SMOOTH);

	glClearColor(1.0f, 0.7f, 1.0f, 0.0f);
	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable( GL_TEXTURE_2D );

	//todo: filenames should come from a config file
	bool flag = false;
	QString errString;

	if ( !textures[T_RED].loadImage( "megaman.png" ) )
	{
		errString += "megaman.png";
		flag = true;
	}

	if ( !textures[T_BLUE].loadImage( "megamanblue.png" ) )
	{
		if (flag)
		{
			errString += ", ";
		}
		flag = true;
		errString += "megamanblue.png";

	}

	if( !textures[T_DEFAULTBG].loadImage( "background.png" ) )
	{
		if (flag)
		{
			errString += ", ";
		}
		flag = true;
		errString += "background.png";
	}

	if ( !textures[T_GRID].loadImage( "grid.png" ) )
	{
		if (flag)
		{
			errString += ", ";
		}
		flag = true;
		errString += "grid.png";
	}

	if ( !textures[T_WALL].loadImage( "wall.png" ) )
	{
		if (flag)
		{
			errString += ", ";
		}
		flag = true;
		errString += "wall.png";
	}

	if ( !textures[T_BLUEFRAME].loadImage( "frameblue.png" ) )
	{
		if (flag)
		{
			errString += ", ";
		}
		flag = true;
		errString += "frameblue.png";
	}

	if ( !textures[T_REDFRAME].loadImage( "framered.png" ) )
	{
		if (flag)
		{
			errString += ", ";
		}
		flag = true;
		errString += "framered.png";
	}

	if (flag)
	{
		QMessageBox::critical(
			this,
			"Error",
			tr("Default textures failed to load: ") + errString
			);
	}

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

	glViewport( 0, 0, (GLint)w, (GLint)h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho( 0, w, h, 0, 0, 10 );

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void Gameboard::drawBots( Game *game, float falloff )
{

	int frame = getAttr(frameNumber);
	int unitSize = getAttr( unitSize );

	int x0, y0, x1, y1;

	for(
		std::vector<Bot>::iterator i = game->states[frame].bots.begin();
		i != game->states[frame].bots.end();
		i++
		)
	{

		x0 = x1 = i->x*unitSize;
		y0 = y1 = i->y*unitSize;
		if( frame+1 < game->states.size() )
		{

			for(
				std::vector<Bot>::iterator j = game->states[frame+1].bots.begin();
				j!= game->states[frame+1].bots.end();
				j++
				)
			{
				if( j->id == i->id )
				{
					x1 = j->x*unitSize;
					y1 = j->y*unitSize;
					break;
				}
			}
		}

		int sprite = T_RED;

		if( i->owner == 1 )
			sprite = T_BLUE;

		drawSprite( x0+(x1-x0)*falloff,y0+(y1-y0)*falloff,unitSize,unitSize, sprite );

	}
}


//todo: naming is bad, game frames and frame bots are too similar
void Gameboard::drawFrames( Game *game, float falloff )
{

	int frame = getAttr(frameNumber);
	int unitSize = getAttr( unitSize );

	int x0, y0, x1, y1;

	for(
		std::vector<Frame>::iterator i = game->states[frame].frames.begin();
		i != game->states[frame].frames.end();
		i++
		)
	{

		x0 = x1 = i->x*unitSize;
		y0 = y1 = i->y*unitSize;
		if( frame+1 < game->states.size() )
		{

			for(
				std::vector<Frame>::iterator j = game->states[frame+1].frames.begin();
				j!= game->states[frame+1].frames.end();
				j++
				)
			{
				if( j->id == i->id )
				{
					x1 = j->x*unitSize;
					y1 = j->y*unitSize;
					break;
				}
			}
		}

		int sprite = T_REDFRAME;

		if( i->owner == 1 )
			sprite = T_BLUEFRAME;

		drawSprite( x0+(x1-x0)*falloff,y0+(y1-y0)*falloff,unitSize,unitSize, sprite );

	}
}


//Warning this has been hacked from the drawbots function
void Gameboard::drawWalls( Game *game, float falloff )
{

	int frame = getAttr( frameNumber );
	int unitSize = getAttr( unitSize );

	int x0, y0, x1, y1;

	for(
		std::vector<Wall>::iterator i = game->states[frame].walls.begin();
		i != game->states[frame].walls.end();
		i++
		)
	{

		x0 = x1 = i->x;
		y0 = y1 = i->y;
		if( frame+1 < game->states.size() )
		{

			for(
				std::vector<Wall>::iterator j = game->states[frame+1].walls.begin();
				j!= game->states[frame+1].walls.end();
				j++
				)
			{
				if( j->id == i->id )
				{
					x1 = j->x;
					y1 = j->y;
					break;
				}
			}
		}

		drawSprite( x0+(x1-x0)*falloff,y0+(y1-y0)*falloff,unitSize,unitSize, T_WALL );

	}

}


void Gameboard::drawBackground()
{
	if ( hasDefaultBG || (!hasDefaultBG && hasMapGrid ) )
	{
		if ( hasDefaultBG )
		{
			glBindTexture( GL_TEXTURE_2D, textures[T_DEFAULTBG].getTexture() );
		}
		else
		{
			glBindTexture( GL_TEXTURE_2D, textures[T_GRID].getTexture() );
		}
		glBegin( GL_QUADS );
		//todo: set sizes configurable by config file

		// float heightRatio = 10.0f / 640.0f;
		// float widthRatio  = 20.0f / 1280.0f;

		glTexCoord2f( 0, 0 );
		glVertex3f( 0, 0, 0 );
		glTexCoord2f( 20, 0 );
		glVertex3f( 1280, 0, 0 );
		glTexCoord2f( 20, 10 );
		glVertex3f( 1280, 640, 0 );
		glTexCoord2f( 0, 10 );
		glVertex3f( 0, 640, 0 );

		glEnd();
	}

	if ( !hasDefaultBG )
	{
		//todo: maximums should be defined by config file
		glBindTexture( GL_TEXTURE_2D, textures[T_BG].getTexture() );

		float width = (float)textures[T_BG].getWidth();
		float height =(float)textures[T_BG].getHeight();

		float aspect = width / height;

		if ( width > 1280 )					 // width too big
		{
			width = 1280;
			height =  aspect / 1280;
		}

		if ( height > 640 )					 // height too big
		{
			height = 640;
			width = aspect * 640;
		}
		glBegin( GL_QUADS );

		glTexCoord2f( 0, 1 );
		glVertex3f( 0, 0, 0 );

		glTexCoord2f( 1, 1 );
		glVertex3f( width, 0, 0 );

		glTexCoord2f( 1, 0 );
		glVertex3f( width, height, 0 );

		glTexCoord2f( 0, 0 );
		glVertex3f( 0, height, 0 );

		glEnd();

	}
}


void Gameboard::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable( GL_TEXTURE_2D );

	Game *game = parent->gamelog;
	int frame = getAttr( frameNumber );

	drawBackground();

	if( game )
	{

		if( time.elapsed() > getAttr(playSpeed) && !getAttr(dragging) 
		    && getAttr(currentMode) != paused )
		{

			time.restart();
			if( frame < (int)game->states.size() )
				setAttr( frameNumber, ++frame );

			parent->controlSlider->blockSignals(true);
			parent->controlSlider->setSliderPosition( frame );
			parent->controlSlider->blockSignals(false);
		}

		float falloff;

		// ------------NEEDS WORK, possibly--------------------
		// falloff assignment while rewinding
                if(getAttr(currentMode) == rewinding)
                	falloff = 1-((float)time.elapsed()/getAttr(playSpeed));

		// This allows the visualizer to finish the animation it is
		// currently on and then stop while paused/dragging the slider
		else if(getAttr(currentMode) == paused||getAttr(dragging))
		{
			if((float)time.elapsed()/getAttr(playSpeed) <1)
                		falloff = 
				  (float)time.elapsed()/getAttr(playSpeed);
			else
			falloff = 1;
		}

		// The normal falloff assignment, when game is moving forwards
                else
                	falloff = (float)time.elapsed()/getAttr(playSpeed);

		drawWalls( game, falloff );
		drawBots( game, falloff );
		drawFrames( game, falloff );
	}
}


void Gameboard::timerEvent( QTimerEvent *)
{
	update();
}


void Gameboard::toggleMapGrid()
{
	hasMapGrid = !hasMapGrid;
}


bool Gameboard::loadBackground( QString filename )
{
	if ( textures[T_BG].loadImage( filename ) )
	{
		hasDefaultBG = false;
		return true;
	}

	return false;
}


void Gameboard::clearBackground()
{
	hasDefaultBG = true;
}
