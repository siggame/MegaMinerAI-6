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

int built;

//This function is run once, before your first turn.
void AI::init()
{
  built=0;
  srand(time(NULL));
}


int xMod[] = { 0, 1, 0,-1};
int yMod[] = {-1, 0, 1, 0};
enum DIR{UP,RIGHT,DOWN,LEFT,DIR_SIZE};
string direction[] = {"up","right","down","left"};

//This function is called each time it is your turn.
//Return true to end your turn, return false to ask the server for updated information.
bool AI::run()
{
  cout<<"Turn: "<<turnNumber()<<endl;
  vector<int> builders, uncombined, actors;
  for(unsigned int b=0;b<bots.size();b++)
  {
    // if it is my bot
    if(bots[b].owner()==playerID() && bots[b].partOf()==0)
    {
      if(bots[b].buildRate()>0 && builders.size()<4 && bots[b].size()==1)
      {
        builders.push_back(b);
      }
      else if(bots[b].size()==1)
      {
        uncombined.push_back(b);
      }
      else
      {
        actors.push_back(b);
      }
    }
  }
  // starting builders
  if(builders.size()<4)
  {
    
    for(unsigned int b=0;b<builders.size();b++)
    {
      int x=bots[builders[b]].x()+xMod[playerID()*2 +1];
      int y=bots[builders[b]].y()+yMod[playerID()*2 +1];
      bots[builders[b]].build(types[1], x, y, 1);
    }    
  }
  // if there are 4 builders
  if(builders.size()==4)
  {
    // check if the builders are in their correct locations
    for(unsigned int b=0;b<builders.size();b++)
    {
      int dir=1;
      if(bots[builders[b]].y()==9)
      {
        bots[builders[b]].move("up");
      }
      else if(bots[builders[b]].y()==10)
      {
        bots[builders[b]].move("down");
      }
      if(bots[builders[b]].y()==8)
      {
        dir = 2;
      }
      else if(bots[builders[b]].y()==11)
      {
        dir = 0;
      }
      int x=bots[builders[b]].x()+xMod[dir];
      int y=bots[builders[b]].y()+yMod[dir];
      if(bots[builders[b]].actions()>0)
      {
        // builds 4 different guys
        bots[builders[b]].build(types[(built/4+b)%types.size()], x, y, 1);
        built++;
      }
    }
  }
  if(uncombined.size()==4)
  {
    /*
    for(unsigned int b=0;b<uncombined.size();b++)
    {
      if(bots[uncombined[b]].y()==9)
      {
        bots[uncombined[b]].move("down");
      }
      else if(bots[builders[b]].y()==10)
      {
        bots[builders[b]].move("down");
      }
    }
    */
    bots[uncombined[0]].combine(bots[uncombined[1]],bots[uncombined[2]],bots[uncombined[3]]);
  }
  // Handles all of the non builders
  for(unsigned int b=0;b<actors.size();b++)
  {
    Unit* target = findNearestTarget(bots[actors[b]]);
    moveTowardsTarget(bots[actors[b]], *target);
    if(inRange(bots[actors[b]], *target))
    {
      cout<<"In RANGE!"<<endl;
      unload(bots[actors[b]],*target);
    }
  }
  return true;
}

void AI::unload(Bot& actor, Unit& target)
{
  if(actor.actions()==0)
  {
    cout<<"Big guy cant attack?"<<endl;
  }
  while(actor.actions()>0)
  {
    if(actor.damage()==0){cout<<"NOT ";};
    cout<<"ATTACKING!"<<endl;
    actor.attack(target);
  }
}

bool AI::inRange(Bot& actor, Unit& target)
{
//  return distance(actor.x(),actor.y(),actor.size(),target.x(),target.y(),target.size()) <= actor.range();
  return distance(actor.x(),actor.y(),actor.size(),target.x(),target.y(),1) <= actor.range();
}


void AI::moveTowardsTarget(Bot& actor, Unit& target)
{
  int dist = INT_MAX,startDist = 0;
  while(actor.steps()>0 && dist > actor.range() && dist != startDist)
  {
    //startDist = distance(actor.x(),actor.y(),actor.size(), target.x(),target.y(),target.size());
    startDist = distance(actor.x(),actor.y(),actor.size(), target.x(),target.y(),1)+1;
    cout<<"Distance to target: "<<startDist<<endl;
    dist = startDist;
    int dir = 0;
    // find the best, non blocked direction
    for(unsigned int d=0;d<DIR_SIZE;d++)
    {
      int x=actor.x()+xMod[d];
      int y=actor.y()+yMod[d];
      
      if(x>=0 && x<boardX() && y>=0 && y<boardY())
      {
        //int tempDist = distance(x,y,actor.size(), target.x(),target.y(),target.size());
        int tempDist = distance(x,y,actor.size(), target.x(),target.y(),1);
        if(tempDist < dist)
        {
          bool blocked = false;
          // check if blocked TODO add other blocking calls
          for(unsigned int b=0;b<bots.size() && !blocked;b++)
          {
            //if(bots[b].x()==x && bots[b].y()==y && bots[b].partOf()==0)
            if(bots[b].partOf()==0 && distance(bots[b].x(),bots[b].y(),bots[b].size(),x,y,actor.size())==0 && bots[b].id() != actor.id())
            {
              blocked=true;
            }
          }
          if(!blocked)
          {
            dir=d;
            dist = tempDist;
          }
        }
      }
    }
    if(dist != startDist)
    {
      cout<<"Big guy moving: "<<direction[dir]<<endl;
      actor.move(direction[dir]);
    }
    else
    {
      cout<<"Nothing worth going to!"<<endl;
    }
  }
}
Unit* AI::findNearestTarget(Bot& actor)
{
  int x=actor.x();
  int y=actor.y();
  int size = actor.size();
  int bestDist = INT_MAX;
  Unit* target=NULL;
  // If it can attack or it cannot heal
  //bool attacker = actor.damage()>0 || actor.buildRate()==0;
  bool attacker =true;
  // loops through all bots
  for(unsigned int b=0;b<bots.size();b++)
  {
    // if I want to attack, and it is an enemy or I want to heal and its an ally
    if((attacker && (playerID()!=bots[b].owner()) || !(attacker && (playerID()==bots[b].owner()))))
    {
      int tempDist = distance(x,y,size, bots[b].x(),bots[b].y(),bots[b].size());
      if(tempDist < bestDist)
      {
        bestDist=tempDist;
        target=&(bots[b]);
      }
    }
  }
  
  // if I am an attacker, include walls and frames
  if(attacker)
  {
    for(unsigned int w=0;w<walls.size();w++)
    {
      int tempDist = distance(x,y,size, walls[w].x(),walls[w].y(),1);
      if(tempDist < bestDist)
      {
        bestDist=tempDist;
        target=&(walls[w]);
      }
    }
    for(unsigned int f=0;f<frames.size();f++)
    {
      if(frames[f].owner() != playerID())
      {
        int tempDist = distance(x,y,size, frames[f].x(),frames[f].y(),frames[f].size());
        if(tempDist < bestDist)
        {
          bestDist=tempDist;
          target=&(frames[f]);
        }
      }
    }
  }  
  return target;
}

//This function is run once, after your last turn.
void AI::end(){}
