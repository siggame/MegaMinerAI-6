/////////////////////////////////////////////////////////
/// @file .h
///
/// @author Brian Goldman
///
/// @language C++
///
/// @compiler g++ 4.43
///
/// @project 
///
/// @description 
///
/////////////////////////////////////////////////////////
#ifndef ORDER_H
#define ORDER_H

#include "MyUtil.h"
#include "Unit.h"

enum OTYPE{MOVE,ATTACK,HEAL,BUILD,COMBINE,SPLIT,OTYPE_SIZE};
static string OTYPE_DISPLAY[]={"MOVE","ATTACK","HEAL","BUILD","COMBINE","SPLIT"};
enum DIR{LEFT,RIGHT,UP,DOWN,DIR_SIZE};
static string direction[] = {"right","down","left","up"};

const int xMod[] = {1, 0,-1, 0,0};
const int yMod[] = {0, 1, 0,-1,0};

struct Order
{
  OTYPE type;
  DIR dir;
  Bot * toOrder,*toHeal,*c1,*c2,*c3;
  Unit * target;
  
  Type* buildType;
  int buildSize;
  int buildX,buildY;

  float fitness;
  
  Order():toOrder(NULL){};
  
  // Stubs
  Order(Bot* WHO,OTYPE T):toOrder(WHO),type(T){};  

  friend bool operator<(const Order& lhs, const Order& rhs)
  {
    return lhs.fitness<rhs.fitness;
  }
  friend ostream& operator <<(ostream &out,const Order &toDisplay)
  {
    if(toDisplay.toOrder != NULL)
    {
//    cout<<"TOP OF order << "<<endl;
      out<<toDisplay.toOrder->id()<<" will "<<OTYPE_DISPLAY[toDisplay.type];
//    cout<<"After type display"<<endl;
      switch(toDisplay.type)
      {
        case MOVE:
          out<<" "<<direction[toDisplay.dir];
          break;
        case ATTACK:
          out<<" "<<toDisplay.target->id();
          break;
        case HEAL:
          out<<" "<<toDisplay.toHeal->id();
          break;
        case BUILD:
          out<<" a "<<toDisplay.buildType->name()<<" of size "<<toDisplay.buildSize<<" at ("<<toDisplay.buildX<<","<<toDisplay.buildY<<")";
          break;
        case COMBINE:
        case SPLIT:
          break;
      }
    }
    else
    {
      out<<"To order null"<<endl;
    }
    return out;
  }
};


#endif
