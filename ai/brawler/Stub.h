/////////////////////////////////////////////////////////
/// @file STUB.h
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
#ifndef STUB_H
#define STUB_H

#include <list>
#include "Order.h"
using namespace std;


// This structure is used as a stub for each unit.  Contains what actions could be available to this unit
struct Stub
{
  list<Order> orders;
  // Points at the best order in the list
  list<Order>::iterator bestOrder;
  
  Stub(){ };
  Stub(Bot& toOrder)
  {
    init(toOrder);
  }

  void init(Bot& toOrder)
  {
    orders.clear();
    for(unsigned int i=0;i<OTYPE_SIZE;i++)
    {
      orders.push_back(Order(&toOrder,(OTYPE)i));
    }
  }
  
  bool empty()
  {
    return orders.size()==0;
  }
};


#endif
