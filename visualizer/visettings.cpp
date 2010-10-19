#include "visettings.h"

visettings *visettings::inst = NULL;

visettings::visettings()
{
	// Every 150 ms
	defaultSpeed = 150;
	playSpeed = defaultSpeed;
	frameNumber = 0;

	dragging = false;

	unitSize = 32;

}


visettings::~visettings()
{
	if( inst )
		delete inst;
	inst = 0;
}


void visettings::loadFromFile()
{
	Config configFile( "VISCONFIG" );

	setAttr( defaultSpeed, configFile.pInt( "DefaultSpeed" ) );
	setAttr( playSpeed, configFile.pInt( "DefaultSpeed" ) );
}
