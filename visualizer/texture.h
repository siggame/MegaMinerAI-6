#include <qimage.h>
#include <qgl.h>

class texture
{
private:
	QImage texture;
	QImage buffer;
	unsigned int texId;
public:
        bool loadImage( const char *path );
	int getTexture();

};
