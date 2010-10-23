#include "drawGLFont.h"


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

	ifstream file( fontWidthsFile, "rb" );
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

	glBindTexture( GL_TEXTURE_2D, textureId );
	for( int i = 0; i < message.size(); i++ )
	{
	
		// Not a real C++ program until there's a ternary operator
		// Also, this is a shortened font list due to boldness
		// So our first character is space, so we adjust for that
		char c = c-32 + (bold ? 128 : 0);	
		// Draw Current Character
		drawCharacter( c );
		// Move Cursor over by character width plus some
		glTranslatef( widths[c]+kerning, 0, 0 );
	}

	glPopMatrix();

}

void DrawGLFont::drawCharacter( char c )
{
	const float off = 1/16;

	float x = (c % 16)/16;
	float y = (c - x*16)/16;
	glBegin( GL_QUADS );
	
	glTexCoord2f(x, y) 
	glVertex3f( 0, 0, 0 );
	glTexCoord2f(x+off,y);
	glVertex3f( 32, 0, 0 );
	glTexCoord2f( x+off,y+off);
	glVertex3f( 32, 32, 0 );
	glTexCoord2f( x, y+off );
	glVertex3f( 0, 32, 0 );

	glEnd( GL_QUADS );
}
