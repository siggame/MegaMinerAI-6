#include <QtGui>
#include <qglobal.h>

#include "visualizerWindow.h"


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	VisualizerWindow window;
	window.show();
	
	return app.exec();
}
