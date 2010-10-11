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
  for(unsigned int b=0;b<bots.size();b++)
  {
    if(bots[b].owner()==playerID())
    {
      bots[b].move(direction[rand()%4]);
    }
  }
  return true;
}
