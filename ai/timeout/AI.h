#ifndef AI_H
#define AI_H

#include "BaseAI.h"
#include <iostream>
using namespace std;
#include <cstdlib>
///The class implementing gameplay logic.
class AI: public BaseAI
{
public:
  AI(Connection* c);
  virtual const char* username();
  virtual const char* password();
  virtual void init();
  virtual bool run();
  virtual void end();
};

#endif
