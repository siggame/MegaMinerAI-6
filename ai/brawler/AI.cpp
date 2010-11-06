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


bool less(const Strat&lhs, const Strat&rhs)
{
  return lhs.score<rhs.score;
}
bool great(const Strat&lhs, const Strat&rhs)
{
  return lhs.score>rhs.score;
}

//This function is run once, before your first turn.
void AI::init()
{
  cout<<"INIT"<<endl;
  srand(time(NULL));
    
  // build the data file name
  if(playerID()==0)
  {
    dataFile=string(player1Name())+".imFirst";
  }
  else
  {
    dataFile=string(player0Name())+".imSecond";
  }
  Strat::load(dataFile,pop);
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
  Strat::save(dataFile,pop);
}

float AI::getScore(Stub& stub)
{
  stub.bestOrder=stub.orders.begin();
  float best = INT_MIN;
  for(list<Order>::iterator it=stub.orders.begin();it!=stub.orders.end();it++)
  {
    if(it->toOrder != NULL)
    {
      if(it->toOrder->size()==0)
      {
        cout<<"Ordering a size zero bot!: "<<it->toOrder->id()<<endl;
        /*
        for(unsigned int i=0;i<bots.size();i++)
        {
          if(bots[i].id()==it->toOrder->id())
          {
            cout<<"In bots: "<<endl;
            cout<<bots[i]<<endl;
            cout<<endl<<"Pointer: "<<endl;
            cout<<*(it->toOrder)<<endl;
          }
        }
        */
      }
    }
    float score=INT_MIN;
    // depending on the type of order
    switch(it->type)
    {
      case MOVE:
        //cout<<"Scoring move: "<<it->toOrder->id()<<endl;
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
  order.fitness=INT_MIN;
  if(order.toOrder->size()>1)
  {
    cout<<"Trying to move a big guy"<<endl;
  }
  // Checks if they are already in range
  pair<int,int> foe = distToNearest(bots,order.toOrder->x(),order.toOrder->y(),order.toOrder->size(),myBots);
  if(foe.second>=0 && inRange(*order.toOrder, bots[foe.second]))
  {
    return order.fitness;
  }
  /*
  if(order.toOrder->size()>1)
  {
    cout<<"\twas not in range"<<endl;
  }
  */
  // calculate the quality of each type of move
  for(unsigned int i=0;i<DIR_SIZE;i++)
  {
    int x=order.toOrder->x()+xMod[i];
    int y=order.toOrder->y()+yMod[i];
    // Check if it is in bounds
    if(x>=0 && x<boardX() && y>=0 && y<boardY())
    {
      float score = 0;
      
      theirBots.insert(order.toOrder->id());
      pair<int,int> ally = distToNearest(bots,x,y,order.toOrder->size(),theirBots);
      theirBots.erase(order.toOrder->id());
      
      pair<int, int> friendlyFrame = distToNearest(frames,x,y,order.toOrder->size(),theirFrames);
      
      pair<int,int> wall = distToNearest(walls,x,y,order.toOrder->size());
      // if I don't hit my own guy
      if(ally.first != 0 && friendlyFrame.first!=0 && wall.first !=0)
      {
      /*
        if(order.toOrder->size()>1)
        {
          cout<<"\t found an unblocked direction"<<endl;
        }
*/
        pair<int,int> foe = distToNearest(bots,x,y,order.toOrder->size(),myBots);
        pair<int,int> foeFrame = distToNearest(frames,x,y,order.toOrder->size(),myFrames);
        if(foe.first == 0 || foeFrame.first==0)
        {
         /* if(order.toOrder->size()>1)
          {
            cout<<"\t  hit a foe frame or thing"<<endl;
            cout<<"ME: "<<*(order.toOrder)<<endl;
            if(foe.second>=0)
            {
              cout<<"FOE: "<<bots[foe.second]<<endl;
            }
            if(foeFrame.second>=0)
            {
              cout<<"Frame: "<<bots[foeFrame.second]<<endl;
            }
          }
          */
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
  if(order.toOrder->size()>1)
  {
    cout<<"Returning "<<order.fitness<<endl;
  }

//  cout<<"Scored move: "<<order.fitness<<endl;
  return order.fitness;
}

float AI::bestAttack(Order&order)
{
  order.fitness=INT_MIN;
  // TODO Be more selective
  pair<int,int> target = distToNearest(bots,order.toOrder->x(),order.toOrder->y(),order.toOrder->size(),myBots);
  pair<int,int> wallTarget = distToNearest(walls,order.toOrder->x(),order.toOrder->y(),order.toOrder->size());
  // if it is in range
  if(target.second >=0 && inRange(*order.toOrder, bots[target.second]))
  {
    order.fitness=rand()%5 + 1;
    order.target=&bots[target.second];
  }
  else if(wallTarget.second>=0 && inRange(*order.toOrder, walls[wallTarget.second]))
  {
    order.fitness=rand()%5 + 1;
    order.target=&walls[wallTarget.second];
  }
  
  return order.fitness;
}
float AI::bestHeal(Order&order)
{
  order.fitness=INT_MIN;
  // TODO Be more selective
  pair<int,int> target = distToNearest(bots,order.toOrder->x(),order.toOrder->y(),order.toOrder->size(),theirBots);
  // if it is in range
  if(target.second >=0 && inRange(*order.toOrder, bots[target.second]));
  {
    order.fitness=rand()%5 + 1;
    order.toHeal=&bots[target.second];
  }
  return order.fitness;
}

float AI::bestBuild(Order&order)
{
  for(unsigned int b=0;b<bots.size();b++)
  {
    if(bots[b].size()==0)
    {
      cout<<"TOP OF BUILD FOUND ZERO"<<endl;
      return INT_MIN;
    }
  }

  order.fitness=INT_MIN;
  // TODO determine the best build type here
  order.buildType = &(types[rand()%types.size()]);
  
  // TODO determine best build size
  order.buildSize=order.toOrder->size();
  // for each direction
  for(unsigned int d=0;d<DIR_SIZE;d++)
  {
    int x=order.toOrder->x()+xMod[d]*order.toOrder->size();
    int y=order.toOrder->y()+yMod[d]*order.toOrder->size();
    int size = order.toOrder->size();
    // check if anyone is at that space
    if(distToNearest(bots, x, y, size).first !=0 && distToNearest(frames, x, y, size).first!=0 && distToNearest(walls, x, y, size).first!=0)
    {
      // TODO score pos
      int scorePos=rand()%20+1;
      if(order.fitness < scorePos)
      {
        order.fitness = scorePos;
        order.buildX=x;
        order.buildY=y;
      }
    }
  }
  for(unsigned int b=0;b<bots.size();b++)
  {
    if(bots[b].size()==0)
    {
      cout<<"BOT OF BUILD FOUND ZERO"<<endl;
      return INT_MIN;
    }
  }

  return order.fitness;
}

int flip[] = {7, 0 ,1 ,6, -1, 2, 5, 3, 3};

float AI::bestCombine(Order&order)
{
  order.fitness=INT_MIN;
//  cout<<"Trying to combine"<<endl;
  int x=order.toOrder->x();
  int y=order.toOrder->y();
  int size = order.toOrder->size();
  vector<Bot*> cell(8,(Bot*)NULL);
  // set up the possible combines
  int count=0;
  for(unsigned int b=0;b<bots.size();b++)
  {
    // if I own it, its not in something and its size is the same as me
    if(bots[b].owner()==playerID() && bots[b].partOf()==0 && bots[b].size()==size && bots[b].id()!=order.toOrder->id() && bots[b].actions()>0)
    {
      int cellX=bots[b].x()-x;
      int cellY=bots[b].y()-y;
      /*
      if(abs(cellX)<=size)
      {
        cout<<"CellX: "<<cellX<<endl;
      }
      if(abs(cellY)<=size)
      {
        cout<<"CellY: "<<cellY<<endl;
      }
      if(abs(cellX)<=size && abs(cellY)<=size)
      {
        cout<<"\t\tBOTH"<<endl;
      }
      */
      //cout<<"Passed the legal check: "<<cellX<<" "<<cellY<<" "<<size<<endl;
      // if it is in the correct spot
      if(abs(cellX)<=size && abs(cellY)<=size)
      {
      //  cout<<"\t\tFOUND SOMEONE ADJ"<<endl;
        count++;
        // converts to 0,1,2 independent of size
        //cout<<"Original: "<<cellX<<" "<<cellY<<endl;
        cellX=cellX/size+1;
        cellY=cellY/size+1;
        //cout<<"After: "<<cellX<<" "<<cellY<<endl;
        cell[flip[cellY*3+cellX]]=&(bots[b]);
      }
    }
  }
  if(count>=5)
  {
   // cout<<"CLOSE ENOUGH"<<endl;
  }
  for(unsigned int i=0;i<9;i+=2)
  {
    bool allThere=true;
    for(unsigned int j=0;j<3 && allThere;j++)
    {
      allThere=(cell[(i+j)%cell.size()]!=NULL);
    }
    
    if(allThere)
    {
      //cout<<"HOLY CRAP A COMBINE"<<endl;
      order.c1=cell[(i+0)%cell.size()];
      order.c2=cell[(i+1)%cell.size()];
      order.c3=cell[(i+2)%cell.size()];
      order.fitness=9999;    
    }
  }
  return order.fitness;
}


float AI::bestSplit(Order&order)
{
  order.fitness=INT_MIN;
  // TODO determine dynamic splitting
  order.fitness = rand()%12-10;
  return order.fitness;
}

void AI::removeInvalid(Stub& stub)
{
  //cout<<"Attempting to remove invalid actions from a stub"<<endl;
  for(list<Order>::iterator it=stub.orders.begin();it!=stub.orders.end();it++)
  {
    if(it->toOrder->size()==0)
    {
      cout<<"In remove invalid, size = 0"<<endl;
    }
    Bot* toOrder=it->toOrder;
    bool remove=false;
    // depending on the type of order
    switch(it->type)
    {
      case MOVE:
        remove= toOrder->steps()==0;
        break;
      case ATTACK:
        remove=(toOrder->actions()==0) || (toOrder->damage()==0);
        break;
      case HEAL:
        remove=(toOrder->actions()==0) || (toOrder->buildRate()==0);
        break;
      case BUILD:
        remove=(toOrder->actions()==0) || (toOrder->buildRate()==0);
        break;
      case COMBINE:
        remove=(toOrder->actions()!=toOrder->maxActions());
        break;
      case SPLIT:
        remove=(toOrder->actions()!=toOrder->maxActions()) || (toOrder->size()==1);
        break;
    }
    if(remove)
    {
      //cout<<"Removing invalid: "<<OTYPE_DISPLAY[it->type]<<endl;
      stub.orders.erase(it);
      it--;
    }
  }
}

void AI::execute(Stub& stub)
{

  Order order= *(stub.bestOrder);
//  cout<<"Top of execute"<<endl;
//  cout<<"Type of order: "<<order.type<<endl;
//  cout<<"Executing: "<<order<<endl;
//  cout<<"After id lookup"<<endl;
  
  int tempx, tempy;
  switch(order.type)
  {
    case MOVE:
      order.toOrder->move(direction[order.dir]);
      break;
    case ATTACK:
      order.toOrder->attack(*order.target);
      if(order.target->health()<=0){myBots.insert(order.target->id());};
      break;
    case HEAL:
      order.toOrder->heal(*order.toHeal);
      break;
    case BUILD:
      order.toOrder->build(*order.buildType,order.buildX,order.buildY,order.buildSize);
      break;
    case COMBINE:
      //cout<<"TRYING TO COMBINE!"<<endl;
      order.toOrder->combine(*order.c1,*order.c2,*order.c3);
      break;
    case SPLIT:
      order.toOrder->split();
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
  myFrames.clear();
  theirFrames.clear();
  for(unsigned int b=0;b<bots.size();b++)
  {
    if(bots[b].owner()==playerID())
    {
      myBots.insert(bots[b].id());
    }
    else
    {
      theirBots.insert(bots[b].id());
    }
    // Always ignore bots that are part of others
    if(bots[b].partOf()!=0)
    {
      myBots.insert(bots[b].id());
      theirBots.insert(bots[b].id());
    }
  }
  for(unsigned int f=0;f<frames.size();f++)
  {
    if(frames[f].owner()==playerID())
    {
      myFrames.insert(frames[f].id());
    }
    else
    {
      theirFrames.insert(frames[f].id());
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
  
  // This section generates actions
  for(unsigned int b=0;b<bots.size();b++)
  {
    if(bots[b].owner()==playerID())
    {
      Stub toAdd(bots[b]);
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
      //cout<<"No good orders"<<endl;
      goodOrders=false;
    }
  }
  return true;
}





