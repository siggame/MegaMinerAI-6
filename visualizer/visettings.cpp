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
	setAttr( unitSize, configFile.pInt( "UnitSize" ) );

        // File Name Attributes

        setAttr( defBGFileName, configFile.pString( "defBGFileName" ) );
        setAttr( wallFileName, configFile.pString( "wallFileName" ) );
        setAttr( gridFileName, configFile.pString( "gridFileName" ) );

        
	//setAttr( filename, configFile.pString( "filenameString" ) );
	// Eh.... to retrieve a particular type of input it's:
	// configFile.pString,pBool,pDouble,or pInt
	//
	// I don't remember what happens if it turns out not to be there.
}
