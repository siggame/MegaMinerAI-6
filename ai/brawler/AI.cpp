#include "AI.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <fstream>
#include <list>
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

vector<Type> gTypes;

//This function is run once, before your first turn.
void AI::init()
{
  srand(time(NULL));
  gTypes.resize(types.size());
  for(unsigned int t=0;t<types.size();t++)
  {
    gTypes[t]=types[t];
  }
}

enum OTYPE{MOVE,ATTACK,HEAL,BUILD,COMBINE,SPLIT,OTYPE_SIZE};
string OTYPE_DISPLAY[]={"MOVE","ATTACK","HEAL","BUILD","COMBINE","SPLIT"};
enum DIR{LEFT,RIGHT,UP,DOWN,DIR_SIZE};
char* direction[] = {"left","right","up","down"};



struct Order
{
  OTYPE type;
  DIR dir;
  int toOrder;
  int targetID;
  int buildType,buildSize;
  int x,y;
  // Default
  Order():type(MOVE),dir(UP),toOrder(0),targetID(0),buildType(0),buildSize(1),x(0),y(0){};
  
  // Move
  Order(OTYPE T,int WHO, DIR D):
    type(T),dir(D),toOrder(WHO),targetID(0),buildType(0),buildSize(1),x(0),y(0){};
  
  // Attack and Heal
  Order(OTYPE T,int WHO, int TAR):
    type(T),dir(UP),toOrder(WHO),targetID(TAR),buildType(0),buildSize(1),x(0),y(0){};
  
  // Build 
  Order(OTYPE T,int WHO, int BT, int BS, int X, int Y):
    type(T),dir(UP),toOrder(WHO),targetID(0),buildType(BT),buildSize(BS),x(X),y(Y){};

  // Combine and Split
  Order(OTYPE T,int WHO):type(T),dir(UP),toOrder(WHO),targetID(0),buildType(0),buildSize(1),x(0),y(0){};
  
  float fitness;
  friend bool operator<(const Order& lhs, const Order& rhs)
  {
    return lhs.fitness<rhs.fitness;
  }
  friend ostream& operator <<(ostream &out,const Order &toDisplay)
  {
    out<<toDisplay.toOrder<<" will "<<OTYPE_DISPLAY[toDisplay.type];
    switch(toDisplay.type)
    {
      case MOVE:
        out<<" "<<direction[toDisplay.dir];
        break;
      case ATTACK:
        out<<" "<<toDisplay.targetID;
        break;
      case HEAL:
        out<<" "<<toDisplay.targetID;
        break;
      case BUILD:
        out<<" a "<<gTypes[toDisplay.buildType].name()<<" of size "<<toDisplay.buildSize<<" at ("<<toDisplay.x<<","<<toDisplay.y<<")";
        break;
      case COMBINE:
      case SPLIT:
        break;
    }
  }
  void execute()
  {
    cout<<"Trying to execute: "<<*this<<endl;
  }
  
  bool isValid()
  {
    cout<<"Performing validity check on: "<<*this<<endl;
    return true;
  }
};

void appendMoves(list<Order> & orders, int toOrder)
{
  for(int i=0;i<4;i++)
  {
    orders.push_back(Order(MOVE,toOrder,(DIR)i));
    cout<<"Pushing back: "<<Order(MOVE,toOrder,(DIR)i)<<endl;
  }
}


int xMod[] = {0,0,-1,1,0};
int yMod[] = {-1,1,0,0,0};

float getScore(const Order& order)
{
  return rand()%20;
}

//This function is called each time it is your turn.
//Return true to end your turn, return false to ask the server for updated information.
bool AI::run()
{
  cout<<"Turn: "<<turnNumber()<<endl;

  list<Order> orderList;
  // This section generates actions
  for(unsigned int b=0;b<bots.size();b++)
  {
    if(bots[b].owner()==playerID())
    {
      appendMoves(orderList,bots[b].id());
      // TODO Add all other kinds of moves      
    }
  }
  list<Order>::iterator it,bestIt;
  bool goodOrders=true;
  while(!orderList.empty() && goodOrders)
  {
    float best = -10;
    for(it=orderList.begin();it != orderList.end();it++)
    {
      // Checks that that order is valid on this turn
      if(it->isValid())
      {
        int score=getScore(*it);
        if(score>best)
        {
          bestIt=it;
          best=score;
        }
      }
      else
      {
        cout<<"Invalid"<<endl;
      }
    }
    if(best>0)
    {
      bestIt->execute();
      orderList.erase(bestIt);
    }
    else
    {
      goodOrders=false;
    }
    
    // TODO Perform cleanup for things that will never be valid again
  }
  
  return true;
}
