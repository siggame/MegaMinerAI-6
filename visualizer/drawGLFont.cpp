#include "drawGLFont.h"

#include <iostream>
#include <sstream>
using namespace std;

DrawGLFont::DrawGLFont()
{

	// Do Nothing.... Oh What fun...
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


void DrawGLFont::drawString( string message )
{
	// We don't want to mess with the original matrix
	glPushMatrix();

	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, textureId );
	Color color = retrieveColor( 0 );
	glColor3f( color.r, color.g, color.b );
	for( int i = 0; (unsigned)i < message.size(); i++ )
	{

		// Not a real C++ program until there's a ternary operator
		// Also, this is a shortened font list due to boldness
		// So our first character is space, so we adjust for that
		unsigned char c = message[i];

		if( c == '$' )
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
			color = retrieveColor( k );
			glColor3f( color.r, color.g, color.b );
			continue;
			
		}

		c = c-32 + (bold ? 128 : 0);

		// Draw Current Character
		drawCharacter( c );
		// Move Cursor over by character width plus some
		glTranslatef( widths[c]+kerning, 0, 0 );
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
