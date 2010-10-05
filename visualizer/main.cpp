#include <QtGui>
#include <qglobal.h>

#include "visualizerWindow.h"


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	VisualizerWindow window;

        //todo: set argv input as the filename for loading
        //      read metadata ...

	window.show();
	
	return app.exec();
}
