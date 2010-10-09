#include "texture.h"
#include <QPainter>

void texture::loadImage( const char *path )
{
	buffer.load( path );

	QImage fixed( buffer.width(), buffer.height(), QImage::Format_ARGB32 );
	QPainter painter(&fixed);
	painter.setCompositionMode(QPainter::CompositionMode_Source);
	painter.fillRect( fixed.rect(), Qt::transparent );
	painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
	painter.drawImage( 0, 0, buffer );
	painter.end();
 	
	texture = QGLWidget::convertToGLFormat( fixed );
	glGenTextures( 1, &texId );

	glBindTexture( GL_TEXTURE_2D, texId );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

	glTexImage2D( GL_TEXTURE_2D, 0, 4, texture.width(), texture.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.bits() );



}

int texture::getTexture()
{
	return texId;
}
