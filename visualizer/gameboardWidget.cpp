#include "gameboardWidget.h"

#include <iostream>
#include <sstream>
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

	if ( !loadTexture( getAttr( redAttackFile ).c_str(), T_REDPART_ATTACK, errString ) )
		flag = true;

	if ( !loadTexture( getAttr( redJointFile ).c_str(), T_REDBOT_JOINT, errString ) )
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

	if ( !loadTexture( getAttr( bluAttackFile ).c_str(), T_BLUPART_ATTACK, errString ) )
		flag = true;

	if ( !loadTexture( getAttr( bluJointFile ).c_str(), T_BLUBOT_JOINT, errString ) )
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


//Draws Territory Control Bar
void Gameboard::drawControl(  )
{
	float baseWidth  = getAttr( boardWidthPx );

	float barWidth = .9*baseWidth;
	float spacer = .05*baseWidth;
																 //Player 1's control percentage
	float onePercent = getPercentage(0);
																 //Player 2's control percentage
	float twoPercent = getPercentage(1);

	glColor4f(1, 1, 1, 1);
	glLoadIdentity();
	glPushMatrix();
	glDisable( GL_TEXTURE_2D );

	glTranslatef( spacer, 10, 0);

	//draws all the basic lines that form the bar
	glLineWidth(3.0f);
	glBegin(GL_LINES);
	glVertex3f(0, 8, 0);
	glVertex3f(0, -8, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(barWidth, 0, 0);

	glVertex3f(barWidth, 8, 0);
	glVertex3f(barWidth, -8, 0);

	glVertex3f(barWidth/2, 8, 0);
	glVertex3f(barWidth/2, -8, 0);
	glEnd();

	//draws player 1's control percentage
	glColor4f(1, 0, 0, .8);
	glBegin(GL_QUADS);
	glVertex3f(0, 7.5, 0);
	glVertex3f(onePercent*barWidth, 7.5, 0);
	glVertex3f(onePercent*barWidth, -7.5, 0);
	glVertex3f(0, -7.5, 0);
	glEnd();

	//draws player 2's control percentage
	glColor4f(0, 0, 1, .8);
	glBegin(GL_QUADS);
	glVertex3f(barWidth, 7.5, 0);
	glVertex3f(barWidth-(twoPercent*barWidth), 7.5, 0);
	glVertex3f(barWidth-(twoPercent*barWidth), -7.5, 0);
	glVertex3f(barWidth, -7.5, 0);
	glEnd();

	glPopMatrix();
	glEnable( GL_TEXTURE_2D );
}


void Gameboard::drawHealth( int x, int y, int w, int h __attribute__ ((unused)), int maxHealth, int health, int owner = 2)
{
	float barLength = (health/static_cast<float>(maxHealth));

	glDisable(GL_TEXTURE_2D);
	switch(owner)
	{
		case 0:											 //player 1
			glColor4f(1, 1, 0, .6);
			break;
		case 1:											 //player 2
			glColor4f(0, 1, 1, .8);
			break;
		default:										 //shouldn't happen
			glColor4f(.5, .5, .5, .6);
			break;
	}
	glLoadIdentity();
	glPushMatrix();
	glTranslatef( (x + w*.05), y+2, 0 );
	glScalef( (w*.9), 1, 1 );

	glBegin(GL_QUADS);

	glVertex3f(0.0f, 4.0f, 0.0f);
	glVertex3f(barLength, 4.0f, 0.0f);
	glVertex3f(barLength, 0.0f, 0.0f);
	glVertex3f(0.0f,0.0f,0.0f);
	glEnd();
	if(owner == 1)
	{

	}
	else
	{
	}
	glColor4f( 0, 0, 0, .7 );

	glBegin(GL_LINE_LOOP);
	glVertex3f( 0.0, 4.0f, 0 );
	glVertex3f( 1, 4.0f, 0 );
	glVertex3f( 1, 0.0, 0 );
	glVertex3f( 0.0f, 0.0, 0 );
	glLineWidth (1.0);

	glEnd();
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);

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

	glDisable( GL_TEXTURE_2D );

	if (selected)
	{
		switch (owner)
		{
			case 0:										 //player 1
				glColor4f(5.0f,0.0f,0.0f,1.0f);
				break;
			case 1:										 //player 2
				glColor4f(0.0f,0.0f,5.0f,1.0f);
				break;
			default:
				glColor4f(0.2f,0.2f,0.2f,1.0f);

		}

		glLineWidth(3.0f);

		glBegin (GL_LINE_LOOP);

		glVertex3f(0, 1.0f, 1);
		glVertex3f( 1.0f, 1.0f, 1);
		glVertex3f( 1.0f,0, 1);
		glVertex3f(0,0, 1);

		glEnd();
		glLineWidth(1.0f);
	}

	glPopMatrix();

	glEnable( GL_TEXTURE_2D );

}


//Returns the percentage of the map the passed owner controls.  If given a size parameter, will recalculate owner's controlled region by adding the bot's area (size*size)
float Gameboard::getPercentage( int owner, int size )
{
	float baseHeight = getAttr( boardHeightPx );
	float baseWidth  = getAttr( boardWidthPx );
	static float onePercent = 0;
	static float twoPercent = 0;
	float retVal = -1;

	switch(owner)
	{
		case 0:
			if(size == -1)
			{
				retVal = onePercent;
			}
			else
			{
				onePercent += (size*size)/(baseHeight*baseWidth);
			}
			break;
		case 1:
			if(size == -1)
			{
				retVal = twoPercent;
			}
			else
			{
				twoPercent += (size*size)/(baseHeight*baseWidth);
			}
			break;
		default:
			onePercent = 0;
			twoPercent = 0;
			break;
	}
	return retVal;
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
		std::map<int,Bot>::iterator it = game->states[frame].bots.begin();
		it != game->states[frame].bots.end();
		it++
		)
	{
		bool flag = false;

		if (it->second.partOf != 0)
		{
																 // if the bot it is part of is a non-typed bot, draw it
			if (game->states[frame].bots.find(it->second.partOf)->second.type == 0)
			{
				flag = true;
			}
		}

		if ((it->second.partOf == 0 ) || flag)
		{

			x0 = x1 = it->second.x*unitSize;
			y0 = y1 = it->second.y*unitSize;
			if((unsigned)frame+1 < game->states.size() )
			{
				if( game->states[frame+1].bots.find(it->second.id) != game->states[frame+1].bots.end() )
				{
					x1 = game->states[frame+1].bots[it->second.id].x*unitSize;
					y1 = game->states[frame+1].bots[it->second.id].y*unitSize;
				}
			}

			//is it selected?
			bool selected = false;
			if ( selectedIDs.find( it->second.id ) != selectedIDs.end() )
			{

				selected = true;
			}

			// find owner
			int owner = it->second.owner;

			//set bot to appropriate type
			int sprite;

			if (owner == 0)
			{
				switch (it->second.type)
				{
					case 1:								 //Action
						sprite = T_REDBOT_ACTION;
						break;

					case 2:								 //Builder
						sprite = T_REDBOT_BUILDER;
						break;

					case 3:								 //Cannon
						sprite = T_REDBOT_CANNON;
						break;

					case 4:								 //Damage
						sprite = T_REDBOT_DAMAGE;
						break;

					case 5:								 //Engine
						sprite = T_REDBOT_ENGINE;
						break;

					case 6:								 //Force
						sprite = T_REDBOT_FORCE;
						break;

					default:							 // temp fix
						sprite = T_REDBOT_JOINT;

				}
			}
			else
			{
				switch (it->second.type)
				{
					case 1:								 //Action
						sprite = T_BLUBOT_ACTION;
						break;

					case 2:								 //Builder
						sprite = T_BLUBOT_BUILDER;
						break;

					case 3:								 //Cannon
						sprite = T_BLUBOT_CANNON;
						break;

					case 4:								 //Damage
						sprite = T_BLUBOT_DAMAGE;
						break;

					case 5:								 //Engine
						sprite = T_BLUBOT_ENGINE;
						break;

					case 6:								 //Force
						sprite = T_BLUBOT_FORCE;
						break;

					default:							 // temp fix
						sprite = T_BLUBOT_JOINT;
				}
			}

			drawSprite( x0+(x1-x0)*falloff,y0+(y1-y0)*falloff,unitSize*it->second.size,unitSize*it->second.size, sprite, selected, owner );
			if ( it->second.partOf == 0)
				drawHealth( x0+(x1-x0)*falloff, y0+(y1-y0)*falloff, unitSize*it->second.size, unitSize*it->second.size, it->second.maxHealth, it->second.health, owner );

																 //keeps count of each player's percentage
			getPercentage(owner, unitSize*it->second.size);
		}

	}
}


//todo: naming is bad, game frames and frame bots are too similar
void Gameboard::drawFrames( Game *game, float falloff __attribute__ ((unused)) )
{

	int frame = getAttr(frameNumber);
	int unitSize = getAttr( unitSize );

	int x0, y0;

	for(
		std::map<int,Frame>::iterator it = game->states[frame].frames.begin();
		it != game->states[frame].frames.end();
		it++
		)
	{

		x0 = it->second.x*unitSize;
		y0 = it->second.y*unitSize;

		//is it selected?
		bool selected = false;
		if ( selectedIDs.find( it->second.id ) != selectedIDs.end() )
		{

			selected = true;
		}

		int sprite = T_REDBOT_FRAME;

		if( it->second.owner == 1 )
			sprite = T_BLUBOT_FRAME;

		drawSprite( x0,y0,unitSize*it->second.size,unitSize*it->second.size, sprite, selected, it->second.owner );
		drawHealth( x0,y0, unitSize*it->second.size, unitSize*it->second.size, it->second.maxHealth, it->second.health, it->second.owner );

	}
}


//Warning this has been hacked from the drawbots function
void Gameboard::drawWalls( Game *game, float falloff __attribute__ ((unused)) )
{

	int frame = getAttr( frameNumber );
	int unitSize = getAttr( unitSize );

	int x0, y0;

	for(
		std::map<int,Wall>::iterator it = game->states[frame].walls.begin();
		it != game->states[frame].walls.end();
		it++
		)
	{

		x0 = it->second.x*unitSize;
		y0 = it->second.y*unitSize;

		//is it selected?
		bool selected = false;
		if ( selectedIDs.find( it->second.id ) != selectedIDs.end() )
		{

			selected = true;
		}

		drawSprite( x0,y0,unitSize,unitSize, T_WALL, selected, 2 );

	}

}


void Gameboard::drawBackground()
{

	float baseHeight = getAttr( boardHeightPx );
	float baseWidth  = getAttr( boardWidthPx );

	if ( hasDefaultBG )
	{
		glBindTexture( GL_TEXTURE_2D, textures[T_DEFAULTBG].getTexture() );

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

		if ( hasMapGrid )
		{
			glBindTexture( GL_TEXTURE_2D, textures[T_GRID].getTexture() );

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


void Gameboard::mousePressEvent( QMouseEvent *e )
{

	if( e->button() == Qt::LeftButton )
	{
		clickX = e->x();
		clickY = e->y();
		if( buttonTimes.elapsed() - leftButtonTime < getAttr( doubleClickTime ) )
		{
			// Do Double click event

		}
		else
		{

			leftButtonTime = buttonTimes.elapsed();
		}

		leftButtonDown = true;
		dragX = clickX;
		dragY = clickY;

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


bool touchingBox( int selectX, int selectY, int selectWidth, int selectHeight, int x, int y, int size )
{
	if(
		selectX <= x+(size-1) &&
		selectWidth >= x &&
		selectY <=y+(size-1) &&
		selectHeight >= y )
	{
		return true;
	}
	//if( x >= selectX && x <= selectWidth && y >=selectY && y <= selectHeight )
	//	return true;
	return false;
}


template <class T>
void addSelection(std::map<int, T > & objects, std::map<int,string> & selectedIDs, const int & selectX, const int & selectY, const int & selectWidth, const int & selectHeight)
{
	typename std::map < int, T > :: iterator it;

	for(
		it = objects.begin();
		it != objects.end();
		it++ )
	{
		stringstream ss;
		if( touchingBox( selectX, selectY, selectWidth, selectHeight, it->second.x, it->second.y, it->second.size )  )
		{
			ss << it->second;
			selectedIDs[it->second.id] = ss.str() ;
		}
	}
}


void Gameboard::mouseReleaseEvent( QMouseEvent *e )
{
	curX = e->x()+1;
	curY = e->y()+1;
	int selectWidth, selectHeight;
	int selectX = selectWidth = curX/getAttr(unitSize);
	int selectY = selectHeight = curY/getAttr(unitSize);

	if( e->button() == Qt::LeftButton )
	{
		if( leftButtonDrag )
		{

			selectX = (curX<dragX ? curX:dragX)/getAttr(unitSize);
			selectWidth = (curX<dragX ? dragX:curX)/getAttr(unitSize);
			selectY = (curY<dragY ? curY:dragY)/getAttr(unitSize);
			selectHeight = (curY<dragY ? dragY:curY)/getAttr(unitSize);

		}

		if( leftDoubleClick )
		{
			leftDoubleClick = false;
			return;
		}

		Game *game = parent->gamelog;
		int frame = getAttr( frameNumber );
		if( game )
		{
			if( !(QApplication::keyboardModifiers() & Qt::ShiftModifier) )
				selectedIDs.clear();

			addSelection(game->states[frame].units, selectedIDs, selectX, selectY, selectWidth, selectHeight);
			std::map<int,Unit> tBots;
			for( std::map<int,Bot>::iterator i = game->states[frame].bots.begin(); i != game->states[frame].bots.end(); i++ )
			{
				if( !i->second.partOf )
					tBots[i->second.id] = i->second;
			}

			addSelection(tBots, selectedIDs, selectX, selectY, selectWidth, selectHeight);
			addSelection(game->states[frame].frames, selectedIDs, selectX, selectY, selectWidth, selectHeight);
			addSelection(game->states[frame].walls, selectedIDs, selectX, selectY, selectWidth, selectHeight);

			stringstream ss;
			ss << "Selected Units: " << selectedIDs.size() << ", X: " << selectX << ", Y: " << selectY << '\n';

			for (map<int,string>::iterator it = selectedIDs.begin(); it != selectedIDs.end(); it++)
			{
				ss << it->second << '\n';
			}

			//parent->console->setText( ss.str().c_str() );
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

	// Invalidate last frame so we get the latest talkers.
	setAttr( lastFrame, -1 );
}


void Gameboard::mouseMoveEvent( QMouseEvent *e )
{
	// If manhatten distance is 6 or greater, we're draggin
	if( abs(curX-dragX)+abs(curY-dragY) > 6 )
		leftButtonDrag = true;

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


void Gameboard::talkRobotsGodDamnitTalk( Game *game )
{
	stringstream ss;
	int startFrame = getAttr( frameNumber )-1;
	if( getAttr( persistantTalking ) )
		startFrame = 0;
	if( startFrame < 0 )
		startFrame = 0;
	for( int i = startFrame; i <= getAttr(frameNumber); i++ )
	{
		for(
			std::vector<Animation*>::iterator j = game->states[i].animations.begin();
			j != game->states[i].animations.end();
			j++ )
		{

			// Not talking, continue
			if( (*j)->type != TALK )
				continue;

			Talk *t = (Talk*)*j;

			// If not selected, continue
			if( selectedIDs.find( t->speaker ) == selectedIDs.end() )
				continue;

			// Ok, selected and talking... whew
			// Let's see if the unit is in this frame:
			if( game->states[i].bots.find( t->speaker ) == game->states[i].bots.end() )
				continue;

			// Yes, he's in the frame!!!
			// GETTING CLOSER!!
			// Correct team!?!?!?!?!
			if( (game->states[i].bots[t->speaker].owner+1)&(getAttr(team1Talk)|((getAttr(team2Talk))<<1) ) )
			{
				// CORRECT TEAM!!!!
				ss << t->message << endl;
			}

		}
	}

	parent->console->setText( ss.str().c_str() );

}


void Gameboard::paintGL()
{
	// We only want to update output if our frame has changed.
	// Other wise we're wasting our time.
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
			if( frame < (int)game->states.size()-1 && frame >= 0 )
			{
				if(getAttr(currentMode) == rewinding &&
					frame>0)
				{
					setAttr( frameNumber, --frame );
					if( frame <=0 )
						setAttr( currentMode, paused );
				}
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

		getPercentage();						 //gets function ready to recalculate percentage controlled
		drawWalls( game, falloff );
		drawFrames( game, falloff );
		drawBots( game, falloff );
		drawAnimations( game, falloff );
		drawControl();

		if( getAttr(frameNumber) != getAttr(lastFrame) )
		{
			setAttr( lastFrame, getAttr( frameNumber ) );
			talkRobotsGodDamnitTalk(game);

			stringstream text;
			text << getAttr(frameNumber) << "/" << game->states.size();

			parent->turnLabel->setText( text.str().c_str() );

			switch( getAttr( currentMode ) )
			{
				case stop:
				case paused:
					parent->playButton->setText( "Play" );
					break;
				case rewinding:
				case fastForward:
				case play:
				default:
					parent->playButton->setText( "Pause" );
					break;
			}
		}
		//parent->console

	}
	drawScoreboard();
	drawMouse();
}


void Gameboard::drawAnimations( Game * game, float falloff)
{

	int frame = getAttr( frameNumber );
	for (std::vector<Animation*>::iterator it = game->states[frame].animations.begin();
		it != game->states[frame].animations.end();
		it++)
	{
		switch ( (*it)->type)
		{
			case ADD:
				break;
			case ATTACK:
				drawAttack(game,(Attack*)(*it),falloff);
				break;
			case BUILD:
				drawBuild(game,(Build*)(*it),falloff);
				break;
			case COLLIDE:
				break;
			case COMBINE:
				break;
			case HEAL:
				drawHeal(game,(Heal*)(*it),falloff);
				break;
			case MOVE:
				break;
			case REMOVE:
				break;
			case SPLIT:
				break;
		}
	}
}


void Gameboard::drawAttack( Game * game, Attack * attack, float falloff )
{
	int x0, y0, xf, yf;
	int frame = getAttr( frameNumber );
	int unitSize = getAttr( unitSize );

	if ((unsigned)frame + 1 < game->states.size()-1)
	{
		GameState state1 = game->states[frame];
		GameState state2 = game->states[frame-1];

		x0 = state1.bots[attack->attacker].x;
		x0 += state1.units[attack->attacker].x;
		x0 += state1.frames[attack->attacker].x;
		x0 += state1.walls[attack->attacker].x;
		x0 *= getAttr(unitSize);

		y0 = state1.bots[attack->attacker].y;
		y0 += state1.units[attack->attacker].y;
		y0 += state1.frames[attack->attacker].y;
		y0 += state1.walls[attack->attacker].y;
		y0 *= getAttr(unitSize);

		xf = state2.mappables[attack->victim].x*getAttr(unitSize);
		yf = state2.mappables[attack->victim].y*getAttr(unitSize);

		xf = state2.bots[attack->victim].x;
		xf += state2.units[attack->victim].x;
		xf += state2.frames[attack->victim].x;
		xf += state2.walls[attack->victim].x;
		xf *= getAttr(unitSize);

		yf = state2.bots[attack->victim].y;
		yf += state2.units[attack->victim].y;
		yf += state2.frames[attack->victim].y;
		yf += state2.walls[attack->victim].y;
		yf *= getAttr(unitSize);

		float x, y;
		x = (xf-x0)*falloff + x0;
		y = (yf-y0)*falloff + y0;

		glPushMatrix();
		glTranslatef(x,y,0);
		glScalef( unitSize * state1.bots[attack->attacker].size/2 , unitSize * state1.bots[attack->attacker].size/2, 1 );

		glEnable( GL_TEXTURE_2D );
		switch (state1.bots[attack->attacker].owner)
		{
			case 0:
				glBindTexture( GL_TEXTURE_2D, textures[T_REDPART_ATTACK].getTexture() );
				break;
			default:
				glBindTexture( GL_TEXTURE_2D, textures[T_BLUPART_ATTACK].getTexture() );

		}

		glBegin(GL_QUADS);

		glColor4f( 1, 1, 1, 1 );

		glTexCoord2f( 0, 0 ); glVertex3f(0, 1.0f, 0);
		glTexCoord2f( 1, 0 ); glVertex3f( 1.0f, 1.0f, 0);
		glTexCoord2f( 1, 1 ); glVertex3f( 1.0f,0, 0);
		glTexCoord2f( 0, 1 ); glVertex3f(0,0,0);

		glEnd();

		glPopMatrix();
	}
}


void Gameboard::drawBuild( Game * game __attribute__ ((unused)), Build * build __attribute__ ((unused)), float falloff __attribute__ ((unused)) )
{
	int x0, y0, xf, yf;
	int frame = getAttr( frameNumber );
	int unitSize = getAttr( unitSize );

	if ((unsigned)frame + 1 < game->states.size()-1)
	{
		GameState state1 = game->states[frame];
		GameState state2 = game->states[frame+1];

		x0 = state1.bots[build->builder].x*getAttr(unitSize);
		y0 = state1.bots[build->builder].y*getAttr(unitSize);

		xf = state2.frames[build->frame].x*getAttr(unitSize);
		yf = state2.frames[build->frame].y*getAttr(unitSize);




		float x, y;
		x = (xf-x0)*falloff + x0;
		y = (yf-y0)*falloff + y0;

		glPushMatrix();
		glTranslatef(x,y,0);

		if ( (xf-x0 == 0) && (yf-y0 > 0) )
			glRotated(90, 0,0,1);

		if ( (xf-x0 < 0) && (yf-y0 == 0) )
			glRotated(90, 0,0,2);

		if ( (xf-x0 == 0) && (yf-y0 < 0) )
			glRotated(90, 0,0,-1);


		glScalef( unitSize * state1.bots[build->builder].size , unitSize * state1.bots[build->builder].size, 1 );
		glEnable( GL_TEXTURE_2D );
		switch (state1.bots[build->builder].owner)
		{
			case 0:
				glBindTexture( GL_TEXTURE_2D, textures[T_REDPART_BUILD].getTexture() );
				break;
			default:
				glBindTexture( GL_TEXTURE_2D, textures[T_BLUPART_BUILD].getTexture() );

		}
		glColor3d(1.0,1.0,1.0);
		glBegin(GL_QUADS);

		glTexCoord2f( 0, 0 ); glVertex3f(0, 1.0f, 0);
		glTexCoord2f( 1, 0 ); glVertex3f( 1.0f, 1.0f, 0);
		glTexCoord2f( 1, 1 ); glVertex3f( 1.0f,0, 0);
		glTexCoord2f( 0, 1 ); glVertex3f(0,0,0);

		glEnd();

		glPopMatrix();
	}
}


void Gameboard::drawHeal( Game * game __attribute__ ((unused)), Heal * heal __attribute__ ((unused)), float falloff __attribute__ ((unused)) )
{
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
