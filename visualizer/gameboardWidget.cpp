#include "gameboardWidget.h"

#include <iostream>
using namespace std;

Gameboard::Gameboard( QWidget *prt )
: QGLWidget( QGLFormat(QGL::SampleBuffers),prt)
{
	// This timer tells us when to repaint the gameboard.
	// 20 milliseconds or microseconds, I'm not sure

	// This makes it about 50 Frames Per Second
	timerId = startTimer(50);
	parent = ((VisualizerWindow*)prt);
	time.start();
	buttonTimes.start();

	hasMapGrid = false;
	hasDefaultBG = true;
	drawFont = NULL;

}


Gameboard::~Gameboard()
{
	if (drawFont != NULL)
	{
	    delete drawFont;
	}

}


void Gameboard::initializeGL()
{
	glShadeModel(GL_SMOOTH);

	glClearColor(0.0f, 0.4f, 0.0f, 0.0f);
	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable( GL_TEXTURE_2D );


	bool flag = false;
	QString errString;


	if (!loadAllTextures(errString))
	{
		QMessageBox::critical(
			this,
			"Error",
			tr("Default textures failed to load: ") + errString
			);
	}

}

bool Gameboard::loadTexture(QString filename, eTextures texID, QString & errString)
{
	if ( !textures[texID].loadImage( filename ) )
	{
		if (QString("") != errString)
		{
			errString += ", ";
		}

		errString += filename;
		return false;
	}
	return true;
}

bool Gameboard::loadAllTextures( QString & message )
{

	bool flag = false;
	QString errString;

	if ( !textures[T_FONT].loadImage( getAttr( defaultFont ).c_str() ) )
	{
		errString += getAttr( defaultFont ).c_str();
		flag = true;
	}
	else
	{
		drawFont = new DrawGLFont( textures[T_FONT].getTexture(), getAttr( defaultFontWidths ) );
	}


	//red bots:


	if ( !loadTexture( getAttr( redActionFile ).c_str(), T_REDBOT_ACTION, errString ) )
		    flag = true;

	if ( !loadTexture( getAttr( redBuilderFile ).c_str(), T_REDBOT_BUILDER, errString ) )
		    flag = true;

	if ( !loadTexture( getAttr( redCannonFile ).c_str(), T_REDBOT_CANNON, errString ) )
		    flag = true;

	if ( !loadTexture( getAttr( redDamageFile ).c_str(), T_REDBOT_DAMAGE, errString ) )
		    flag = true;

	if ( !loadTexture( getAttr( redEngineFile ).c_str(), T_REDBOT_ENGINE, errString ) )
		    flag = true;

	if ( !loadTexture( getAttr( redForceFile ).c_str(), T_REDBOT_FORCE, errString ) )
		    flag = true;

	if ( !loadTexture( getAttr( redFrameFile ).c_str(), T_REDBOT_FRAME, errString ) )
		    flag = true;


	//blue bots:
	if ( !loadTexture( getAttr( bluActionFile ).c_str(), T_BLUBOT_ACTION, errString ) )
		    flag = true;

	if ( !loadTexture( getAttr( bluBuilderFile ).c_str(), T_BLUBOT_BUILDER, errString ) )
		    flag = true;

	if ( !loadTexture( getAttr( bluCannonFile ).c_str(), T_BLUBOT_CANNON, errString ) )
		    flag = true;

	if ( !loadTexture( getAttr( bluDamageFile ).c_str(), T_BLUBOT_DAMAGE, errString ) )
		    flag = true;

	if ( !loadTexture( getAttr( bluEngineFile ).c_str(), T_BLUBOT_ENGINE, errString ) )
		    flag = true;

	if ( !loadTexture( getAttr( bluForceFile ).c_str(), T_BLUBOT_FORCE, errString ) )
		    flag = true;

	if ( !loadTexture( getAttr( bluFrameFile ).c_str(), T_BLUBOT_FRAME, errString ) )
		    flag = true;



	//Other Textures

	if ( !loadTexture( getAttr( defBGFileName ).c_str(), T_DEFAULTBG, errString ) )
		    flag = true;


	if ( !loadTexture( getAttr( gridFileName ).c_str(), T_GRID, errString ) )
		    flag = true;


	if ( !loadTexture( getAttr( wallFileName ).c_str(), T_WALL, errString ) )
		    flag = true;


	message = errString;

	return !flag;

}


void Gameboard::drawSprite( int x, int y, int w, int h, int texture, bool selected = false, int owner = 2)
{

	glBindTexture( GL_TEXTURE_2D, textures[texture].getTexture() );
	glPushMatrix();
	glTranslatef( x, y, 0 );
	glScalef( w, h, 0 );
	glColor4f(1.0,1.0,1.0,1.0f);

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


	glDisable( GL_TEXTURE_2D );

	glPushMatrix();
	if (selected)
	{

		switch (owner)
		{
			case 0: //player 1
			glColor4f(1.0f,0.0f,0.0f,1.0f);
			break;
			case 1: //player 2
			glColor4f(0.0f,0.0f,1.0f,1.0f);
			break;
			default:
			glColor4f(0.5f,0.5f,0.5f,1.0f);

		}
		glBegin (GL_LINE_LOOP);

		glVertex3f(0, 1.0f, -0.01f);
		glVertex3f( 1.0f, 1.0f, -0.01f);
		glVertex3f( 1.0f,0, -0.01f);
		glVertex3f(0,0,-0.01f);

		glEnd();
	}
	glPopMatrix();

	glEnable( GL_TEXTURE_2D );


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
		if (i->partOf == 0)
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

			//is it selected?
			bool selected = true;
			for (list<int>::iterator l = selectedIDs.begin(); l != selectedIDs.end(); l++)
			{
				if ( *l == i->id )
				{

				    selected = true;
				}
			}


			// find owner
			int owner = i->owner;

			//set bot to appropriate type
			int sprite;
			if (owner == 0)
			{
			    sprite = T_REDBOT_ENGINE;
			}
			else
			{
			    sprite = T_BLUBOT_ENGINE;
			}


			drawSprite( x0+(x1-x0)*falloff,y0+(y1-y0)*falloff,unitSize*i->size,unitSize*i->size, sprite, selected, owner );
		}

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

		//is it selected?
		bool selected = false;
		for (list<int>::iterator l = selectedIDs.begin(); l != selectedIDs.end(); l++)
		{
			if (*l == i->id)
			{
			    selected = true;
			}
		}

		int sprite = T_REDBOT_FRAME;

		if( i->owner == 1 )
			sprite = T_BLUBOT_FRAME;

		drawSprite( x0+(x1-x0)*falloff,y0+(y1-y0)*falloff,unitSize*i->size,unitSize*i->size, sprite, selected, i->owner );

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

		//is it selected?
		bool selected = false;
		for (list<int>::iterator l = selectedIDs.begin(); l != selectedIDs.end(); l++)
		{
			if (*l == i->id)
			{
			    selected = true;
			}
		}

		drawSprite( x0+(x1-x0)*falloff,y0+(y1-y0)*falloff,unitSize,unitSize, T_WALL, selected, 2 );

	}

}


void Gameboard::drawBackground()
{

	float baseHeight = getAttr( boardHeightPx );
	float baseWidth  = getAttr( boardWidthPx );

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

		glTexCoord2f( 0, 0 );
		glVertex3f( 0, 0, 0 );
		glTexCoord2f( 20, 0 );
		glVertex3f( baseWidth, 0, 0 );
		glTexCoord2f( 20, 10 );
		glVertex3f( baseWidth, baseHeight, 0 );
		glTexCoord2f( 0, 10 );
		glVertex3f( 0, baseHeight, 0 );

		glEnd();
	}

	if ( !hasDefaultBG )
	{
		//todo: maximums should be defined by config file
		glBindTexture( GL_TEXTURE_2D, textures[T_BG].getTexture() );

		float width = (float)textures[T_BG].getWidth();
		float height =(float)textures[T_BG].getHeight();

		float aspect = width / height;

		if ( width > baseWidth )		 // width too big
		{
			width = baseWidth;
			height =  aspect / baseWidth;
		}

		if ( height > baseHeight )	 // height too big
		{
			height = baseHeight;
			width = aspect * baseHeight;
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


void Gameboard::handleMouse()
{
	if( leftButtonDown )
	{
		// Do Drag event
		leftButtonDrag = true;
		dragX = clickX;
		dragY = clickY;
	}

}


void Gameboard::mousePressEvent( QMouseEvent *e )
{

	if( e->button() == Qt::LeftButton )
	{
		clickX = e->x();
		clickY = e->y();
		// TODO: Move double click time into VISCONFIG
		if( buttonTimes.elapsed() - leftButtonTime < 275 )
		{
			// Do Double click event

		}
		else
		{

			leftButtonTime = buttonTimes.elapsed();
		}

		leftButtonDown = true;
		QTimer::singleShot( 150, this, SLOT( handleMouse() ) );

	} else if ( e->button() == Qt::RightButton )
	{
		rightButtonTime = buttonTimes.elapsed();
		rightButtonDown = true;
	} else if( e->button() == Qt::MidButton )
	{
		midButtonTime = buttonTimes.elapsed();
		midButtonDown = true;
	}
}


bool touchingBox( int bX, int bY, int bW, int bH, int x, int y )
{
	if( x >= bX && x <= bW && y >=bY && y <= bH )
		return true;
	return false;
}


#define addSelection(type1,type2) \
	for( \
	vector<type1>::iterator i = game->states[frame].type2.begin(); \
	i != game->states[frame].type2.end(); \
	i++ ) \
	{ \
		if( touchingBox( bX, bY, bW, bH, i->x, i->y ) ) \
		{ \
			selectedIDs.push_back( i->id ); \
		} \
	}

		void Gameboard::mouseReleaseEvent( QMouseEvent *e )
		{
			curX = e->x()+1;
			curY = e->y()+1;
			int bW, bH;
			int bX = bW = curX/getAttr(unitSize);
			int bY = bH = curY/getAttr(unitSize);

			if( e->button() == Qt::LeftButton )
			{
				if( leftButtonDrag )
				{
					bX = (curX<dragX ? curX:dragX)/getAttr(unitSize);
			// I think I may have to increase bH and bW by one...
					bW = (curX<dragX ? dragX:curX)/getAttr(unitSize);
					bY = (curY<dragY ? curY:dragY)/getAttr(unitSize);
					bH = (curY<dragY ? dragY:curY)/getAttr(unitSize);

				}

				if( leftDoubleClick )
					return;

				Game *game = parent->gamelog;
				int frame = getAttr( frameNumber );
				if( game )
				{
			// TODO: Check if shift is held down.  If so, don't clear
					selectedIDs.clear();
			// Probably could have used templates, or anything else.  Bad implementation but works;

					addSelection(Unit, units);
					addSelection(Mappable, mappables);
					addSelection(Bot, bots);
					addSelection(Frame, frames);
					addSelection(Wall, walls );



					char *unitSelection = new char[255];
					sprintf( unitSelection, "Selected Units: %d, X: %d, Y: %d\n", selectedIDs.size(), bX, bY );

					QString OutText(unitSelection);

					for (list<int>::iterator it = selectedIDs.begin(); it != selectedIDs.end(); it++)
					{
					    sprintf( unitSelection, "%d\n", *it);
					    OutText += QString(unitSelection);
					}
					parent->console->setText( OutText );
				}

				leftButtonDown = false;
				leftButtonDrag = false;
			} else if ( e->button() == Qt::RightButton )
			{
				rightButtonDown = false;
			} else if( e->button() == Qt::MidButton )
			{
				rightButtonDown = false;
			}
		}

void Gameboard::mouseMoveEvent( QMouseEvent *e )
{
	curX = e->x();
	curY = e->y();
}


void Gameboard::drawScoreboard()
{

	glLoadIdentity();

	glEnable(GL_BLEND);

	glTranslatef( 10, 640, 0 );
	glColor3f( 1, 1, 0 );
	if (drawFont != NULL)
	{
		drawFont->drawString( "The quick brown fox jumped over the lazy dog" );
	}
	glColor3f( 1, 1, 1 );

}


void Gameboard::drawMouse()
{
	if( leftButtonDrag )
	{

		glDisable( GL_TEXTURE_2D );

		glLoadIdentity();

		glColor4f( 0, .7, 0, .4 );
		glBegin( GL_QUADS );
		glVertex3f( curX, curY, 0 );
		glVertex3f( dragX, curY, 0 );
		glVertex3f( dragX, dragY, 0 );
		glVertex3f( curX, dragY, 0 );
		glEnd();

		glColor4f( 0, .5, 0, .7 );

		glLineWidth( 2 );
		glBegin( GL_LINE_LOOP );
		glVertex3f( curX, curY, 0 );
		glVertex3f( dragX, curY, 0 );
		glVertex3f( dragX, dragY, 0 );
		glVertex3f( curX, dragY, 0 );
		glEnd();

		glColor4f( 1, 1, 1, 1 );
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

			// This is where we advance to the next frame
			if( frame < (int)game->states.size() && frame >= 0 )
			{
				if(getAttr(currentMode) == rewinding &&
					frame>0)
					setAttr( frameNumber, --frame );
				else
					setAttr( frameNumber, ++frame );
			}

			parent->controlSlider->blockSignals(true);
			parent->controlSlider->setSliderPosition( frame );
			parent->controlSlider->blockSignals(false);
		}

		float falloff;

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
				// This needs to be 0, other wise, when paused, player sees future
				falloff = 0;
		}

		// The normal falloff assignment, when game is moving forwards
		else
			falloff = (float)time.elapsed()/getAttr(playSpeed);

		drawWalls( game, falloff );
		drawBots( game, falloff );
		drawFrames( game, falloff );
	}
	drawScoreboard();
	drawMouse();
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
