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
#include <cmath>
#include <utility>
#include <fstream>
#include <algorithm>
#include "util.h"

#include "Stub.h"
#include "Strat.h"
#include "MyUtil.h"
using namespace std;


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
  void execute(Stub&order);
  float getScore(Stub&stub);
  void removeInvalid(Stub& stub);
  
  string dataFile;  
    
  float bestMove(Order&order);
  float bestAttack(Order&order);
  float bestHeal(Order&order);
  float bestBuild(Order&order);
  float bestCombine(Order&order);
  float bestSplit(Order&order);
  map<int, int> idToBot;
  vector<int> gene;
  
  int popIndex;  
  void setBots();
  set<int> myBots,theirBots,myFrames, theirFrames;
  
  
  
  vector<Strat> pop;
};




#endif
