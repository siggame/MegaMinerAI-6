#include "AI.h"
#include <iostream>
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


//This function is run once, before your first turn.
void AI::init()
{
  srand(time(NULL));
}

int xMod[] = {0,0,-1,1,0};
int yMod[] = {-1,1,0,0,0};

char* direction[] = {"left","right","up","down"};

//This function is called each time it is your turn.
//Return true to end your turn, return false to ask the server for updated information.
bool AI::run()
{
  cout<<"Turn: "<<turnNumber()<<endl;
  for(unsigned int i=0;i<bots.size();i++)
  {
    if(bots[i].x()<0 || bots[i].y()<0 || bots[i].x()>boardX() ||bots[i].y()>boardY())
    {
      cout<<"Bot out of bounds At: "<<bots[i].x()<<","<<bots[i].y()<<endl;
      return true;
    }
    for(unsigned int j=0;j<bots.size();j++)
    {
      if(bots[i].x()==bots[j].x() && bots[i].y()==bots[j].y() && i != j)
      {
        cout<<"Stacking bots: "<<bots[i].id()<<"-"<<bots[j].id()<<" At: "<<bots[i].x()<<","<<bots[i].y()<<endl;
        return true;
      }
    }
  }
  for(unsigned int b=0;b<bots.size();b++)
  {
    if(bots[b].owner()==playerID())
    {
      if(bots[b].actions()>0)
      {
        int d=rand()%5;
        bots[b].build(types[1],bots[b].x()+xMod[d],bots[b].y()+yMod[d],1);
      }
    }
  }
  return true;
}
