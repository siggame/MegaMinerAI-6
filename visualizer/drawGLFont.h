#ifndef DRAWGLFONT_H
#define DRAWGLFONT_H

#include <QtOpenGL>
#include <fstream>
#include <string>

#include "visettings.h"

using namespace std;

class DrawGLFont
{
	public:
		DrawGLFont();
		DrawGLFont( int fontTextureId, string fontWidthsFile )
		{
			loadNewFont( fontTextureId, fontWidthsFile );
		}

		void setBold( bool isBold )
		{
			bold = isBold;
		}

		bool loadNewFont( int fontTextureId, string fontWidthsFile );

		void drawString( string message );

	private:

		// Don't want to waste a bunch of time rebinding the font
		// So we'll make this private and do the binding in
		// drawString
		void drawCharacter( unsigned char c );

		// We know there's 256 widths
		char widths[256];

		// ID of texture to bind
		int textureId;

		float kerning;
		bool bold;
};
#endif
