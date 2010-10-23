#include "drawGLFont.h"

#include <iostream>
using namespace std;

DrawGLFont::DrawGLFont()
{

	// Do Nothing.... Oh What fun...
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
	for( int i = 0; i < message.size(); i++ )
	{

		// Not a real C++ program until there's a ternary operator
		// Also, this is a shortened font list due to boldness
		// So our first character is space, so we adjust for that
		unsigned char c = message[i];

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

	cout << tmp << " " << y*16 << " " <<   y << endl;

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
