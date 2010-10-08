#include <qimage.h>
#include <qgl.h>

class texture
{
private:
	QImage texture;
	QImage buffer;
	unsigned int texId;
public:
	void loadImage( const char *path );
	int getTexture();




};
