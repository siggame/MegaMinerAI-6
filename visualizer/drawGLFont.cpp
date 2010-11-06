#include "drawGLFont.h"

#include <iostream>
#include <sstream>
using namespace std;

DrawGLFont::DrawGLFont()
{

	// Do Nothing.... Oh What fun...
	alignment = align_left;
}

Color DrawGLFont::retrieveColor( int id )
{
	if( id >= colors.size() )
		return Color( 0, 0, 0 );
	return colors[id];
}

void DrawGLFont::resetColors()
{
	colors.clear();
}

void DrawGLFont::setAlignment( int align )
{
	alignment=align;
}

void DrawGLFont::addColor( float r, float g, float b )
{
	colors.push_back( Color( r, g, b ) );
}

bool DrawGLFont::loadNewFont(
int fontTextureId,
string fontWidthsFile
)
{
	textureId = fontTextureId;

	ifstream file( fontWidthsFile.c_str() );
	if( !file.is_open() )
		return false;

	for( int i = 0; i < 256; i++ )
	{
		char temp;
		file.read( &temp, sizeof(char) );
		widths[i] = temp;
		file.read( &temp, sizeof(char) );
	}

	kerning = 1;
	bold = false;

	return true;
}

void DrawGLFont::setColor( int &i, string message )
{
	i++;
	i++;
	stringstream ss;
	while( message[i] != ')' )
	{
		ss << message[i];
		i++;
	}
	
	int k = atoi( ss.str().c_str() );
	Color color = retrieveColor( k );
	glColor3f( color.r, color.g, color.b );

}

void DrawGLFont::drawAlignedLeft( string message )
{
	for( int i = 0; (unsigned)i < message.size(); i++ )
	{

		// Not a real C++ program until there's a ternary operator
		// Also, this is a shortened font list due to boldness
		// So our first character is space, so we adjust for that
		unsigned char c = message[i];

		if( c == '$' )
		{
			setColor( i, message );
			continue;
		}

		c = c-32 + (bold ? 128 : 0);

		// Draw Current Character
		drawCharacter( c );
		// Move Cursor over by character width plus some
		glTranslatef( widths[c]+kerning, 0, 0 );
	}

}

void DrawGLFont::drawAlignedCenter( string message )
{
	int mid = message.size()/2;
	glPushMatrix();

	string left = message.substr( 0, mid );
	drawAlignedRight( left );
	glPopMatrix();
	string right = message.substr( mid, mid+1 );
	drawAlignedLeft( right );
	

}

void DrawGLFont::drawAlignedRight( string message )
{
	for( int i = message.size()-1; i >= 0; i-- )
		{

			// Not a real C++ program until there's a ternary operator
			// Also, this is a shortened font list due to boldness
			// So our first character is space, so we adjust for that
			unsigned char c = message[i];
			//unsigned char d = message[i-1];
#if 0
			if( c == '$' )
			{
				setColor( i, message );
				continue;
			}
#endif

			c = c-32 + (bold ? 128 : 0);

			glTranslatef( -widths[c]-kerning, 0, 0 );
			// Draw Current Character
			drawCharacter( c );
			// Move Cursor over by character width plus some
		}
}

void DrawGLFont::drawString( string message )
{
	// We don't want to mess with the original matrix
	glPushMatrix();

	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, textureId );
	Color color(0,0,0);
	if( colors.size() > 0 )
	{
		color = retrieveColor( 0 );
		glColor3f( color.r, color.g, color.b );
	}

	switch( alignment )
	{
		case align_right:
			drawAlignedRight( message );
			break;
		case align_center:
			drawAlignedCenter( message );
			break;
		default:
			drawAlignedLeft( message );
	}
	



	glPopMatrix();

}


void DrawGLFont::drawCharacter( unsigned char c )
{
	float off = (float)-1/16;

	int tmp = (int)c;
	float x = (float)((int)tmp%16)/16;
	float y = 1-(float)((int)tmp/16)/16;

	glBegin( GL_QUADS );

	glTexCoord2f(x, y+off);
	glVertex3f( 0, 32, 0 );
	glTexCoord2f(x-off,y+off);
	glVertex3f( 32, 32, 0 );
	glTexCoord2f( x-off,y);
	glVertex3f( 32, 0, 0 );
	glTexCoord2f( x, y );
	glVertex3f( 0, 0, 0 );

	glEnd();

}
