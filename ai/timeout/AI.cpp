#include "AI.h"

AI::AI(Connection* conn) : BaseAI(conn) {}

const char* AI::username()
{
  return "Shell AI";
}

const char* AI::password()
{
  return "password";
}

int timeOutTurn;

//This function is run once, before your first turn.
void AI::init()
{
  srand(time(NULL));
  timeOutTurn=rand()%50;
}

//This function is called each time it is your turn.
//Return true to end your turn, return false to ask the server for updated information.
bool AI::run()
{
  cout<<"Turn: "<<turnNumber()<<" time out on: "<<timeOutTurn<<" P0: "<<player0Time()<<" "<<player1Time()<<endl;
  if(turnNumber()>=timeOutTurn && playerID()==0)
  {
    sleep(player0Time());
  }
  return true;
  //return turnNumber()<timeOutTurn;
}

//This function is run once, after your last turn.
void AI::end()
{
  cout<<"Called my end function"<<endl;
}
