#include "AI.h"

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


int xMod[] = {-1, 1,0,0,0};
int yMod[] = {0, 0,-1,1,0};

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
  int c1,c2,c3;

  float fitness;
  
  // Default
  Order():type(MOVE),dir(UP),toOrder(0),targetID(0),buildType(0),buildSize(1),x(0),y(0){};
  
  // Stubs
  Order(int WHO,OTYPE T):
    type(T),dir(UP),toOrder(WHO),targetID(0),buildType(0),buildSize(1),x(0),y(0){};  
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
};

// This structure is used as a stub for each unit.  Contains what actions could be available to this unit
struct Stub
{
  list<Order> stubs;
  // Points at the best order in the list
  list<Order>::iterator bestOrder;
  
  // Stuff used for order validation
  int actionsTaken;
  int movesTaken;
  
  Stub(){ };
  Stub(int id)
  {
    init(id);
  }

  void init(int id)
  {
    stubs.clear();
    for(unsigned int i=0;i<OTYPE_SIZE;i++)
    {
      stubs.push_back(Order(id,(OTYPE)i));
    }
    actionsTaken=0;
    movesTaken=0;
  }
  
  bool empty()
  {
    return stubs.size()==0;
  }
};


float AI::getScore(Stub& stub)
{
  stub.bestOrder=stub.stubs.begin();
  float best = INT_MIN;
  for(list<Order>::iterator it=stub.stubs.begin();it!=stub.stubs.end();it++)
  {
    float score=INT_MIN;
    // depending on the type of order
    switch(it->type)
    {
      case MOVE:
        score=bestMove(*it);
        break;
      case ATTACK:
        score=bestAttack(*it);
        break;
      case HEAL:
        score=bestHeal(*it);
        break;
      case BUILD:
        score=bestBuild(*it);
        break;
      case COMBINE:
        score=bestCombine(*it);
        break;
      case SPLIT:
        score=bestSplit(*it);
        break;
    }
    if(score>best)
    {
      best=score;
      stub.bestOrder=it;
    }
  }
  return best;
}

float AI::bestMove(Order& order)
{
  int b = idToBot.find(order.toOrder)->second;
  order.fitness=INT_MIN;
  // calculate the quality of each type of move
  for(unsigned int i=0;i<DIR_SIZE;i++)
  {
    int x=bots[b].x()+xMod[i];
    int y=bots[b].y()+yMod[i];
    // Check if it is in bounds
    if(x>=0 && x<boardX() && y>=0 && y<boardY())
    {
      //TODO score move
      float score = rand()%20+1;
      if(score > order.fitness)
      {
        order.fitness=score;
        order.dir = (DIR)i;
      }
    }
  }
//  cout<<"Scored move: "<<order.fitness<<endl;
  return order.fitness;
}

float AI::bestAttack(Order&order)
{
  return INT_MIN;
}
float AI::bestHeal(Order&order)
{
  return INT_MIN;
}
float AI::bestBuild(Order&order)
{
  return INT_MIN;
}
float AI::bestCombine(Order&order)
{
  return INT_MIN;
}
float AI::bestSplit(Order&order)
{
  return INT_MIN;
}



void AI::removeInvalid(Stub& stub)
{
  //cout<<"Attempting to remove invalid actions from a stub"<<endl;
  for(list<Order>::iterator it=stub.stubs.begin();it!=stub.stubs.end();it++)
  {
    int b=idToBot.find(it->toOrder)->second;
    bool remove=false;
    // depending on the type of order
    switch(it->type)
    {
      case MOVE:
        remove= stub.movesTaken>=bots[b].movitude();
        break;
      case ATTACK:
        remove=true;
        break;
      case HEAL:
        remove=true;
        break;
      case BUILD:
        remove=true;
        break;
      case COMBINE:
        remove=true;
        break;
      case SPLIT:
        remove=true;
        break;
    }
    if(remove)
    {
      stub.stubs.erase(it);
      it--;
    }
  }
}

void AI::execute(Stub& stub)
{
  Order order= *(stub.bestOrder);
  cout<<"Executing: "<<order<<endl;
  int b=idToBot.find(order.toOrder)->second;
  int target;
  int c1,c2,c3;
  switch(order.type)
  {
    case MOVE:
      bots[b].move(direction[order.dir]);
      stub.movesTaken++;
      break;
    case ATTACK:
      target=idToBot.find(order.targetID)->second;
      bots[b].attack(bots[target]);
      //stub.actionsTaken++;
      break;
    case HEAL:
      target=idToBot.find(order.targetID)->second;
      bots[b].heal(bots[target]);
      break;
    case BUILD:
      bots[b].build(types[order.buildType],order.x,order.y,order.buildSize);
      break;
    case COMBINE:
      c1=target=idToBot.find(order.c1)->second;
      c2=target=idToBot.find(order.c2)->second;
      c3=target=idToBot.find(order.c3)->second;
      bots[b].combine(bots[c1],bots[c2],bots[c3]);
    case SPLIT:
      bots[b].split();
      break;
    default:
      cout<<"Unknown order type!"<<endl;
      break;
  }
}

//This function is called each time it is your turn.
//Return true to end your turn, return false to ask the server for updated information.
bool AI::run()
{
  cout<<"Turn: "<<turnNumber()<<endl;

  list<Stub> orderList;
  
  // set up the map
  idToBot.clear();
  for(unsigned int b=0;b<bots.size();b++)
  {
    idToBot[bots[b].id()]=b;
  }
  
  // This section generates actions
  for(unsigned int b=0;b<bots.size();b++)
  {
    if(bots[b].owner()==playerID())
    {
      Stub toAdd(bots[b].id());
      removeInvalid(toAdd);
      // Pushes on a stub for this unit
      if(!toAdd.empty())
      {
        //cout<<"Pushing back orders for: "<<bots[b].id()<<endl;
        orderList.push_back(toAdd);
      }
    }
  }
  list<Stub>::iterator it,bestIt;
  bool goodOrders=true;
  while(!orderList.empty() && goodOrders)
  {
    float best = -10;
    for(it=orderList.begin();it != orderList.end();it++)
    {
      int score=getScore(*it);
      if(score>best)
      {
        bestIt=it;
        best=score;
      }
    }
    if(best>0)
    {
      execute(*bestIt);
      removeInvalid(*bestIt);
      if(bestIt->empty())
      {
        orderList.erase(bestIt);
      }
    }
    else
    {
      goodOrders=false;
    }
  }
  return true;
}
