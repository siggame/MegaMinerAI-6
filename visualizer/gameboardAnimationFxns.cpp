#include "gameboardWidget.h"
#include <stdlib.h>
#include <time.h>


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

Unit *findExistance( GameState &state, int unit )
{
	if( state.bots.find( unit ) != state.bots.end() )
		return (Unit *)&state.bots[unit];	
	if( state.frames.find( unit ) != state.frames.end() )
		return (Unit *)&state.frames[unit];
	if( state.walls.find( unit ) != state.walls.end() )
		return (Unit *)&state.walls[unit];
	if( state.units.find( unit ) != state.units.end() )
		return (Unit *)&state.units[unit];

	return 0;


}	

void Gameboard::drawAttack( Game * game, Attack * attack, float falloff )
{
	int x0, y0, xf, yf;
	int frame = getAttr( frameNumber );
	int unitSize = getAttr( unitSize );
	// Make the random seed the pointer so jitter is consistant
	srand( (long unsigned int)attack );

	if ((unsigned)frame + 1 < game->states.size()-1)
	{
		GameState state1 = game->states[frame];
		GameState state2 = game->states[frame-1];

		int bulletSize = unitSize*3/5;

		Unit *attacker = findExistance( state1, attack->attacker );
		Unit *victim = findExistance( state2, attack->victim );


		int xJitter = rand() % attacker->size*unitSize*2/3- attacker->size*unitSize/3;
		int yJitter = rand() % attacker->size*unitSize*2/3 - attacker->size*unitSize/3;

		x0 = attacker->x*unitSize+(attacker->size-1)*unitSize/2+(unitSize-bulletSize)/2 + xJitter;
		y0 = attacker->y*unitSize+(attacker->size-1)*unitSize/2+(unitSize-bulletSize)/2 + yJitter;

		xf = victim->x*unitSize+(victim->size-1)*unitSize/2+(unitSize-bulletSize)/2;
		yf = victim->y*unitSize+(victim->size-1)*unitSize/2+(unitSize-bulletSize)/2;

		float x, y;
		x = (xf-x0)*falloff + x0;
		y = (yf-y0)*falloff + y0;

		glPushMatrix();
		glTranslatef(x,y,0);
		glScalef( bulletSize , bulletSize, 1 );

		glEnable( GL_TEXTURE_2D );
		switch (state1.bots[attack->attacker].owner)
		{
			case 0:
				
				glColor4f( 0, 1, 0, 1 );
				glBindTexture( GL_TEXTURE_2D, textures[T_REDPART_ATTACK].getTexture() );
				break;
			default:
				glColor4f( 0, .7, 1, 1 );
				glBindTexture( GL_TEXTURE_2D, textures[T_BLUPART_ATTACK].getTexture() );

		}

		glBegin(GL_QUADS);


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


void Gameboard::drawHeal( Game * game , Heal * heal , float falloff  )
{
	int x0, y0, xf, yf;
	int frame = getAttr( frameNumber );
	int unitSize = getAttr( unitSize );

	if ((unsigned)frame + 1 < game->states.size()-1)
	{
		GameState state1 = game->states[frame];
		GameState state2 = game->states[frame+1];

		x0 = state1.bots[heal->healer].x*getAttr(unitSize);
		y0 = state1.bots[heal->healer].y*getAttr(unitSize);

		xf = state2.frames[heal->victim].x*getAttr(unitSize);
		yf = state2.frames[heal->victim].y*getAttr(unitSize);

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

		glScalef( unitSize * state1.bots[heal->healer].size , unitSize * state1.bots[heal->healer].size, 1 );
		glEnable( GL_TEXTURE_2D );
		switch (state1.bots[heal->healer].owner)
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
