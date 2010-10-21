#include "AI.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
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

bool splitTime=false;

//This function is run once, before your first turn.
void AI::init()
{
  srand(time(NULL));
}
/*
int xMod[] = {0,0,-1,1,0};
int yMod[] = {-1,1,0,0,0};
*/
int xMod[] = { 1, 0,-1, 0,0};
int yMod[] = { 0, 1, 0,-1,0};


char* direction[] = {"right","down","left","up"};
//char* direction[] = {"left","right","up","down"};

//This function is called each time it is your turn.
//Return true to end your turn, return false to ask the server for updated information.
bool AI::run()
{
  /*
  0) action
  1) builder
  2) cannon
  3) damage
  4) engine
  5) fat
 */
  /*
  // Shows types
  for(unsigned int t=0;t<types.size();t++)
  {
    cout<<t<<") "<<types[t].name()<<endl;
  }
  */
  for(unsigned int b=0;b<bots.size();b++)
  {
    for(unsigned int o=0;o<bots.size();o++)
    {
      if(o != b && bots[b].x()==bots[o].x() && bots[b].y()==bots[o].y())
      {
        cout<<"Failed to move as group!"<<endl;
      }
    }
  }
  cout<<"Turn: "<<turnNumber()<<endl;
  vector<Bot> myBots;
  for(unsigned int b=0;b<bots.size();b++)
  {
    if(bots[b].owner()==playerID() && bots[b].partOf()==0)
    {
      myBots.push_back(bots[b]);
      cout<<"Bot at: "<<bots[b].x()<<" "<<bots[b].y()<<" my id: "<<bots[b].id()<<" part of: "<<bots[b].partOf()<<endl;   
    }
  }


  if(splitTime)
  {
    for(unsigned int b=0;b<myBots.size();b++)
    {
      myBots[b].split();
    }
    return true;
  }

  if(myBots.size() && myBots[0].size()==16)
  {
    splitTime=true;
    myBots[0].move(direction[playerID()*2]);
    return true;
  }  
  for(unsigned int b=0;b<myBots.size();b++)
  {
    if(myBots[b].actions()>0)
    {
      int baseD=playerID()*2;
      if(myBots.size()%4==2)
      {
        baseD++;
      }
      if(myBots.size()!=4)
      {
        cout<<"Building at: "<<myBots[b].x()+xMod[baseD]*myBots[b].size()<<","<<myBots[b].y()+yMod[baseD]*myBots[b].size()<<endl;
        myBots[b].build(types[1],myBots[b].x()+xMod[baseD]*myBots[b].size(),myBots[b].y()+yMod[baseD]*myBots[b].size(),myBots[b].size());
      }
    }
  }
  if(myBots.size()%4==0)
  {
    myBots[0].combine(myBots[1],myBots[2],myBots[3]);
  }
  
  return true;
}
