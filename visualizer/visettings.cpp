#include "visettings.h"

visettings *visettings::inst = NULL;

visettings::visettings()
{
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
