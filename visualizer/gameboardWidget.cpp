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

        if ( !textures[T_RED].loadImage( "megaman.png" ) ||
             !textures[T_BLUE].loadImage( "megamanblue.png" ) ||
             !textures[T_DEFAULTBG].loadImage( "background.png" )||
             !textures[T_GRID].loadImage( "grid.png" ))
        {
            QMessageBox::critical(this,"Error","Default textures failed to load.");
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
	//cout << "resize" << endl;

	glViewport( 0, 0, (GLint)w, (GLint)h);

	glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
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

            int sprite = T_RED;

            if( i->owner == 1 )
                sprite = T_BLUE;

            drawSprite( x0+(x1-x0)*falloff,y0+(y1-y0)*falloff,unitSize,unitSize, sprite );

        }
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


        if ( width > 1280 ) // width too big
        {
            width = 1280;
            height =  aspect / 1280;
        }

        if ( height > 640 ) // height too big
        {
            height = 640;
            width = aspect * 640;
        }
        glBegin( GL_QUADS );

        glTexCoord2f( 0, 0 );
        glVertex3f( 0, 0, 0 );
        glTexCoord2f( 1, 0 );
        glVertex3f( width, 0, 0 );
        glTexCoord2f( 1, 1 );
        glVertex3f( width, height, 0 );
        glTexCoord2f( 0, 1 );
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

        drawBackground();

	drawBots();
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
