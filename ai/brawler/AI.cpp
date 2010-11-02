#include "AI.h"
using namespace std;
AI::AI(Connection* conn) : BaseAI(conn) {}

const char* AI::username()
{
  return "BRAWLER";
}

const char* AI::password()
{
  return "lolGene";
}

vector<Type> gTypes;

int shitDist(int x, int y, int ox, int oy)
{
  return abs(x-ox)+abs(y-oy);
}

int xMod[] = {1, 0,-1, 0,0};
int yMod[] = {0, 1, 0,-1,0};
bool less(const strat&lhs, const strat&rhs)
{
  return lhs.score<rhs.score;
}
bool great(const strat&lhs, const strat&rhs)
{
  return lhs.score>rhs.score;
}
enum OTYPE{MOVE,ATTACK,HEAL,BUILD,COMBINE,SPLIT,OTYPE_SIZE};
string OTYPE_DISPLAY[]={"MOVE","ATTACK","HEAL","BUILD","COMBINE","SPLIT"};
enum DIR{LEFT,RIGHT,UP,DOWN,DIR_SIZE};
string direction[] = {"right","down","left","up"};

enum GENE{FRIEND,FOE,G_SIZE};

//This function is run once, before your first turn.
void AI::init()
{
  cout<<"INIT"<<endl;
  srand(time(NULL));
  gTypes.resize(types.size());
  
  for(unsigned int t=0;t<types.size();t++)
  {
    gTypes[t]=types[t];
  }
  
  // build the data file name
  if(playerID()==0)
  {
    dataFile=string(player1Name())+".imFirst";
  }
  else
  {
    dataFile=string(player0Name())+".imSecond";
  }
  
  
  // Magic number of population size
  pop.resize(12);
  // TODO Load genes
  ifstream in(dataFile.c_str());
  // If there was a database file
  if(in.is_open())
  {
    for(unsigned int i=0;i<pop.size();i++)
    {
      cout<<"Reading in "<<i<<endl;
      in>>pop[i].played;
      in>>pop[i].score;
      pop[i].gene.resize(G_SIZE);
      for(unsigned int g=0;g<G_SIZE;g++)
      {
        in>>pop[i].gene[g];
      }
    }
  }
  else
  {
    for(unsigned int i=0;i<pop.size();i++)
    {
      pop[i].played=false;
      pop[i].score=false;
      pop[i].gene.resize(G_SIZE);
      for(unsigned int g=0;g<G_SIZE;g++)
      {
        pop[i].gene[g]=rand()%10;
      }
    }
  }
  in.close();
  bool found=false;
  for(unsigned int i=0;i<pop.size()&&!found;i++)
  {
    if(!pop[i].played)
    {
      found=true;
      popIndex=i;
    }
  }
  cout<<"Past beginning stuff"<<endl;
  // Handles if everyone has played
  if(!found)
  {
    // Sorts the population so the best are at the lowest index
    sort(pop.begin(),pop.end(),great);
    
    // ensure there are enough parents
    int pEnd=pop.size()/2;
    int cBegin=pop.size()*3/4;
    // If there is not enough differentialtion,
    if(pop[pEnd-1].score==pop[cBegin].score)
    {
      // reset everyone
      for(unsigned int i=0;i<pop.size();i++)
      {
        pop[i].played=false;
      }
    }
    else// evolution
    {
      // TODO 
    }
    // start playing from the top
    popIndex=0;
  }
  // Copies over the genes for easy access
  gene.resize(G_SIZE);
  for(unsigned int i=0;i<gene.size();i++)
  {
    gene[i]=pop[popIndex].gene[i];
  }
  cout<<"FINISHED INIT"<<endl;
}

void AI::end()
{
  vector<Bot> mine, theirs;
  unsigned int myCount=0,theirCount=0;
  float myHealth=0,theirHealth=0;
  cout<<"At the end of the game there are "<<bots.size()<<" bots "<<endl;
  for(unsigned int i=0;i<bots.size();i++)
  {
    //cout<<bots[i]<<endl;
    if(bots[i].owner()==playerID())
    {
      if(bots[i].size()==1)
      {
        myCount++;
      }
      if(bots[i].partOf()==0)
      {
        myHealth+=1.0*bots[i].health()/bots[i].maxHealth();
      }
      mine.push_back(bots[i]);
    }
    else
    {
      if(bots[i].size()==1)
      {
        theirCount++;
      }
      if(bots[i].partOf()==0)
      {
        theirHealth+=1.0*bots[i].health()/bots[i].maxHealth();
      }
      theirs.push_back(bots[i]);
    }
  }
  bool win;
  if(myCount == theirCount)
  {
    if(myHealth == theirHealth)
    {
      cout<<"We were entirely equal, my playerID = " <<playerID()<<endl;
      win=playerID()==1;
    }
    else 
    {
      cout<<"We had the same count "<<myHealth<<" "<<theirHealth<<endl;
      win = (myHealth>theirHealth);
    }
  }
  else
  {
    cout<<"We had different counts "<<myCount<<" "<<theirCount<<endl;
    win=myCount>theirCount;
  }
  cout<<"MINE: "<<myCount<<" "<<myHealth<<" "<<playerID()<<endl;
  cout<<"NTME: "<<theirCount<<" "<<theirHealth<<endl;
  cout<<"THE GAME IS OVER, ALL IS "<<(win?"WON":"LOST")<<endl;
  // probably unnecessary
  int score = (win)?1:0;
  
  // Add the score to this player
  pop[popIndex].score+=score;
  pop[popIndex].played=true;
  
  ofstream out(dataFile.c_str());
  // If there was a database file
  for(unsigned int i=0;i<pop.size();i++)
  {
    out<<pop[i].played<<" ";
    out<<pop[i].score<<" ";
    for(unsigned int g=0;g<G_SIZE;g++)
    {
      out<<pop[i].gene[g]<<" ";
    }
    out<<endl;
  }
}

pair<int, int> AI::distToNearest(vector<Bot>& group,int x, int y, int ignore)
{
  pair<int,int> ret;
  ret.first=INT_MAX;
  ret.second=-1;
  for(unsigned int i=0;i<group.size();i++)
  {
    int temp = shitDist(x,y,group[i].x(),group[i].y());
    if(temp < ret.first && group[i].id() != ignore)
    {
      ret.first=temp;
      ret.second=i;
    }
  }
  return ret;
}
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
//    cout<<"TOP OF order << "<<endl;
    out<<toDisplay.toOrder<<" will "<<OTYPE_DISPLAY[toDisplay.type];
//    cout<<"After type display"<<endl;
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
    return out;
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
        //score=bestAttack(*it);
        break;
      case HEAL:
        //score=bestHeal(*it);
        break;
      case BUILD:
        score=bestBuild(*it);
        break;
      case COMBINE:
        //score=bestCombine(*it);
        break;
      case SPLIT:
        //score=bestSplit(*it);
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
  cout<<"Scoring move "<<order.toOrder<<" "<<bots[b].x()<<" "<<bots[b].y()<<endl;
  order.fitness=INT_MIN;
  // Checks if they are already in range
  pair<int,int> foe = distToNearest(theirBots,bots[b].x(),bots[b].y());
  if(foe.first <=bots[b].range())
  {
    // breaks out
    return order.fitness;
  }
  // calculate the quality of each type of move
  for(unsigned int i=0;i<DIR_SIZE;i++)
  {
    int x=bots[b].x()+xMod[i];
    int y=bots[b].y()+yMod[i];
    // Check if it is in bounds
    if(x>=0 && x<boardX() && y>=0 && y<boardY())
    {
      float score = 0;
      pair<int,int> ally = distToNearest(myBots,x,y,order.toOrder);
      // if I don't hit my own guy
      if(ally.first != 0)
      {
        pair<int,int> foe = distToNearest(theirBots,x,y);
        if(foe.first == 0)
        {
          //TODO Logic for ramming goes here
          score=INT_MIN;
        }
        int maxMove=boardX()+boardY();
        // friendly distance
        //score += (maxMove-ally.first)*gene[FRIEND];
        score += (maxMove-foe.first)*gene[FOE];       
        
        if(score > order.fitness)
        {
          order.fitness=score;
          order.dir = (DIR)i;
        }
      }
    }
  }
//  cout<<"Scored move: "<<order.fitness<<endl;
  return order.fitness;
}

float AI::bestAttack(Order&order)
{
  order.fitness=rand()%20-10;
  //cout<<"Attack ranked: "<<order.fitness<<endl;
  order.targetID=bots[rand()%bots.size()].id();
  //order.targetID=order.toOrder;
  return order.fitness;
}
float AI::bestHeal(Order&order)
{
  order.fitness=rand()%20-10;
  order.targetID=bots[rand()%bots.size()].id();
  return order.fitness;
}
float AI::bestBuild(Order&order)
{
/*
  order.fitness=rand()%20-10;
  order.buildType=rand()%types.size();
  order.x=rand()%boardX();
  order.y=rand()%boardY();
  order.buildSize=pow(2.0,rand()%4);
*/
  // Movement bots
  int b = idToBot.find(order.toOrder)->second;
  order.fitness=boardX()+boardY()*100;
  order.buildType=4;
  order.x=bots[b].x()+xMod[playerID()*2];
  order.y=bots[b].y()+yMod[playerID()*2];
  return order.fitness;
}
float AI::bestCombine(Order&order)
{
  order.fitness=rand()%20-10;
  order.c1=bots[rand()%bots.size()].id();
  order.c2=bots[rand()%bots.size()].id();
  order.c3=bots[rand()%bots.size()].id();
  return order.fitness;
}
float AI::bestSplit(Order&order)
{
  order.fitness=rand()%20-10;
  return order.fitness;
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
        remove=(stub.actionsTaken>=bots[b].actitude()) || (bots[b].damage()==0);
        break;
      case HEAL:
        remove=(stub.actionsTaken>=bots[b].actitude()) || (bots[b].buildRate()==0);
        break;
      case BUILD:
        remove=(stub.actionsTaken>=bots[b].actitude()) || (bots[b].buildRate()==0);
        break;
      case COMBINE:
        remove=(stub.actionsTaken!=0);
        break;
      case SPLIT:
        remove=(stub.actionsTaken!=0) || (bots[b].size()==1);
        break;
    }
    if(remove)
    {
      cout<<"Removing invalid: "<<OTYPE_DISPLAY[it->type]<<endl;
      stub.stubs.erase(it);
      it--;
    }
  }
}

void AI::execute(Stub& stub)
{
  Order order= *(stub.bestOrder);
//  cout<<"Top of execute"<<endl;
//  cout<<"Type of order: "<<order.type<<endl;
  cout<<"Executing: "<<order<<endl;
  int b=idToBot.find(order.toOrder)->second;
//  cout<<"After id lookup"<<endl;
  int target;
  int c1,c2,c3;
  
  int tempx, tempy;
  switch(order.type)
  {
    case MOVE:
      tempx=bots[b].x();
      tempy=bots[b].y();
      bots[b].move(direction[order.dir]);
      if(tempx==bots[b].x() && tempy==bots[b].y())
      {
        cout<<"Blocked"<<endl;
      }
      stub.movesTaken++;
      break;
    case ATTACK:
      target=idToBot.find(order.targetID)->second;
      bots[b].attack(bots[target]);
      stub.actionsTaken++;
      break;
    case HEAL:
      target=idToBot.find(order.targetID)->second;
      bots[b].heal(bots[target]);
      stub.actionsTaken++;
      break;
    case BUILD:
      bots[b].build(types[order.buildType],order.x,order.y,order.buildSize);
      stub.actionsTaken=bots[b].actitude();
      stub.movesTaken=bots[b].movitude();
      break;
    case COMBINE:
      c1=target=idToBot.find(order.c1)->second;
      c2=target=idToBot.find(order.c2)->second;
      c3=target=idToBot.find(order.c3)->second;
      bots[b].combine(bots[c1],bots[c2],bots[c3]);
      stub.actionsTaken++;
      break;
    case SPLIT:
      bots[b].split();
      stub.actionsTaken++;
      break;
    default:
      cout<<"Unknown order type!"<<endl;
      break;
  }
}

void AI::setBots()
{
  myBots.clear();
  theirBots.clear();
  for(unsigned int b=0;b<bots.size();b++)
  {
    if(bots[b].owner()==playerID())
    {
      myBots.push_back(bots[b]);
    }
    else
    {
      theirBots.push_back(bots[b]);
    }
  }
}

//This function is called each time it is your turn.
//Return true to end your turn, return false to ask the server for updated information.
bool AI::run()
{

  if(turnNumber()>10)
  {
//    return true;
  }
  cout<<"Turn: "<<turnNumber()<<endl;
  cout<<player0Time()<<" "<<player1Time()<<" "<<player0Name()<<" "<<player1Name()<<endl;
  setBots();

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
      cout<<"No good orders"<<endl;
      goodOrders=false;
    }
  }
  return true;
}





