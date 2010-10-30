// -*-c++-*-

#ifndef WALL_H
#define WALL_H

#include <iostream>
#include "structures.h"

#include "Unit.h"

///A pile of hard stuff that is in the way.
class Wall : public Unit {
  public:
  Wall(_Wall* ptr = NULL);

  // Accessors
  ///Unique Identifier
  int id();
  ///The X position of the top left corner of this object.  X is horizontal
  int x();
  ///The Y position of the top left corner of this object.  Y is vertical
  int y();
  ///The owning player
  int owner();
  ///How much health this unit currently has
  int health();
  ///The maximum amount of health this unit can ever have
  int maxHealth();

  // Actions
  ///Sends a message to be visualized when this unit is selected
  int talk(char* message);

  // Properties


  friend std::ostream& operator<<(std::ostream& stream, Wall ob);
};

#endif

