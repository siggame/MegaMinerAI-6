#include "AI.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
using namespace std;
AI::AI(Connection* conn) : BaseAI(conn) {}

const char* AI::username()
{
  return "Shell AI";
}

const char* AI::password()
{
  return "password";
}


//This function is run once, before your first turn.
void AI::init()
{
  srand(time(NULL));
}

int shitDist(int x, int y, int ox, int oy)
{
  return abs(x-ox)+abs(y-oy);
}

int xMod[] = {-1, 1,-1, 0,0};
int yMod[] = { 0, 0,-1, 1,0};

char* direction[] = {"left","right","up","down"};

//This function is called each time it is your turn.
//Return true to end your turn, return false to ask the server for updated information.
bool AI::run()
{
  cout<<"Turn: "<<turnNumber()<<endl;
  // Performs a stacking robot check
  for(unsigned int b=0;b<bots.size();b++)
  {
    for(unsigned int o=0;o<bots.size();o++)
    {
      if(b!=o && bots[b].x()==bots[o].x() && bots[b].y()==bots[o].y())
      {
        cout<<"BOTS ARE STACKING AT: ("<<bots[b].x()<<","<<bots[b].y()<<")"<<endl;
        return true;
      }
    }
  }
  
  
  int target=0;
  
  for(unsigned int b=0;b<bots.size();b++)
  {
    if(bots[b].owner() != playerID())
    {
      target=b;
    }
  }
  
  for(unsigned int b=0;b<bots.size();b++)
  {
    if(bots[b].owner()==playerID())
    {
      int dist=999,best=4;
      for(unsigned int i=0;i<5;i++)
      {
        int tempDist = shitDist(bots[b].x()+xMod[i],bots[b].y()+yMod[i],bots[target].x(),bots[target].y());
        if(tempDist < dist)
        {
          dist=tempDist;
          best=i;
        }
      }
      if(best != 4)
      {
        bots[b].move(direction[best]);
      }
    }
  }
  return true;
}

void AI::end()
{
  cout<<"THE GAME IS OVER, ALL IS ?"<<endl;
}
