#include "visettings.h"

visettings *visettings::inst = NULL;

visettings::visettings()
{
	// Every 150 ms
	playSpeed = 150;
	frameNumber = 0;

	dragging = false;


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

  setAttr( playSpeed, configFile.pInt( "DefaultSpeed" ) );
}
