// -*-c++-*-

#include "structures.h"

#include <iostream>


std::ostream& operator<<(std::ostream& stream, Mappable ob)
{
  stream << "id: " << ob.id  <<'\n';
  stream << "x: " << ob.x  <<'\n';
  stream << "y: " << ob.y  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, Unit ob)
{
  stream << "id: " << ob.id  <<'\n';
  stream << "x: " << ob.x  <<'\n';
  stream << "y: " << ob.y  <<'\n';
  stream << "owner: " << ob.owner  <<'\n';
  stream << "health: " << ob.health  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, Bot ob)
{
  stream << "id: " << ob.id  <<'\n';
  stream << "x: " << ob.x  <<'\n';
  stream << "y: " << ob.y  <<'\n';
  stream << "owner: " << ob.owner  <<'\n';
  stream << "health: " << ob.health  <<'\n';
  stream << "attack: " << ob.attack  <<'\n';
  stream << "range: " << ob.range  <<'\n';
  stream << "speed: " << ob.speed  <<'\n';
  stream << "buildRate: " << ob.buildRate  <<'\n';
  stream << "size: " << ob.size  <<'\n';
  return stream;
}



std::ostream& operator<<(std::ostream& stream, GameState ob)
{
  stream << "turnNumber: " << ob.turnNumber  <<'\n';
  stream << "playerID: " << ob.playerID  <<'\n';
  stream << "boardX: " << ob.boardX  <<'\n';
  stream << "boardY: " << ob.boardY  <<'\n';
  stream << "gameNumber: " << ob.gameNumber  <<'\n';
  
  stream << "\n\nMappables:\n";
  for(std::vector<Mappable>::iterator i = ob.mappables.begin(); i != ob.mappables.end(); i++)
    stream << *i << '\n';
  stream << "\n\nUnits:\n";
  for(std::vector<Unit>::iterator i = ob.units.begin(); i != ob.units.end(); i++)
    stream << *i << '\n';
  stream << "\n\nBots:\n";
  for(std::vector<Bot>::iterator i = ob.bots.begin(); i != ob.bots.end(); i++)
    stream << *i << '\n';
  stream << "\nAnimation\n";
  for(std::vector<Animation*>::iterator i = ob.animations.begin(); i != ob.animations.end(); i++)
  {
  }
}

Game::Game()
{
  winner = -1;
}