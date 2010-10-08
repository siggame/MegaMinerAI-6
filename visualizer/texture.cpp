#include "texture.h"

void texture::loadImage( const char *path )
{
	buffer.load( path );
	texture = QGLWidget::convertToGLFormat( buffer );
	glGenTextures( 1, &texId );

	glBindTexture( GL_TEXTURE_2D, texId );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

	glTexImage2D( GL_TEXTURE_2D, 0, 3, texture.width(), texture.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.bits() );



}

int texture::getTexture()
{
	return texId;
}
