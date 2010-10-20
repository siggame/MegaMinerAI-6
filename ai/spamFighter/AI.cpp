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

int seed;
//This function is run once, before your first turn.
void AI::init()
{
//  seed= time(NULL);
  seed=1287585768;
  srand(seed);
  
}

int shitDist(int x, int y, int ox, int oy)
{
  return abs(x-ox)+abs(y-oy);
}

int xMod[] = {-1, 1, 0, 0,0};
int yMod[] = { 0, 0, -1, 1,0};

char* direction[] = {"left","right","up","down"};

//This function is called each time it is your turn.
//Return true to end your turn, return false to ask the server for updated information.
bool AI::run()
{
  cout<<"Turn: "<<turnNumber()<<" Bots: "<<bots.size()<<" "<<seed<<" "<<playerID()<<endl;
  /*
  // Shows types
  for(unsigned int t=0;t<types.size();t++)
  {
    cout<<t<<") "<<types[t].name()<<endl;
  }
  // Performs a stacking robot check
  for(unsigned int b=0;b<bots.size();b++)
  {
    for(unsigned int o=0;o<bots.size();o++)
    {
      if(b!=o && bots[b].x()==bots[o].x() && bots[b].y()==bots[o].y())
      {
        cout<<"BOTS ARE STACKING AT: ("<<bots[b].x()<<","<<bots[b].y()<<")"<<endl;
      }
    }
  }
  */
  bool hasAttacker=false;
  int mine=0,theirs=0;
  for(unsigned int b=0;b<bots.size();b++)
  {
    if(bots[b].owner()==playerID() && bots[b].damage()>0)
    {
      hasAttacker=true;
    }    
    if(bots[b].owner()==playerID())
    {
      mine++;
    }
    else
    {
      theirs++;
    }
  }
  for(unsigned int b=0;b<bots.size();b++)
  {
    if(bots[b].owner()==playerID() && bots[b].buildRate()>0 )
    {
      if(bots[b].actions()>0)
      {
        int d = rand()%4;
  //      int d = 1+playerID();
        // Builds a fat bot
//        bots[b].build(types[5],bots[b].x()+xMod[d], bots[b].y()+yMod[d],1);
        bots[b].build(types[rand()%types.size()],bots[b].x()+xMod[d], bots[b].y()+yMod[d],1);
//        cout<<"Building at: "<<
      }
    }
    else if(bots[b].owner()==playerID())
    {
            
      cout<<"My Bots HP: "<<bots[b].health()<<endl;
      int dist=999,best=4,target=0;
      for(unsigned int t=0;t<bots.size();t++)
      {
        if(bots[t].owner() != playerID())
        {
          int tempDist = shitDist(bots[b].x(),bots[b].y(),bots[t].x(),bots[t].y());
          if(tempDist < dist )
          {
            dist=tempDist;
            target=t;
          }
        }
      }
      
      dist=9999;
      for(unsigned int i=0;i<5;i++)
      {
        int tempDist = shitDist(bots[b].x()+xMod[i],bots[b].y()+yMod[i],bots[target].x(),bots[target].y());
        if(tempDist < dist || (tempDist==dist && rand()%2))
        {
          dist=tempDist;
          best=i;
        }
      }
      if(best != 4 && dist !=0)
      {
        bots[b].move(direction[best]);
      }
      else
      {
        if(playerID()==1 || theirs!=1)// || rand()%10==0)
        {
          // attack the target
          bots[b].attack(bots[target]); 
          cout<<"Attacking for: "<<bots[b].damage()<<endl;
        }
      }
    }
  }
  return true;
}
