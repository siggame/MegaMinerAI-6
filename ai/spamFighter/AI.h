#ifndef AI_H
#define AI_H

#include "BaseAI.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <fstream>
#include <list>
#include <map>
#include <limits.h>
using namespace std;
struct Order;
struct Stub;
///The class implementing gameplay logic.
class AI: public BaseAI
{
public:
  AI(Connection* c);
  virtual const char* username();
  virtual const char* password();
  virtual void init();
  virtual bool run();
  
  void execute(Order&order);
  float getScore(Stub&stub);
  
  float bestMove(Order&order);
  float bestAttack(Order&order);
  float bestHeal(Order&order);
  float bestBuild(Order&order);
  float bestCombine(Order&order);
  float bestSplit(Order&order);
  map<int, int> idToBot;
  virtual void end();
};

#endif
