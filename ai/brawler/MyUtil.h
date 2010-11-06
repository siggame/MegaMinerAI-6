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
#ifndef MYUTIL
#define MYUTIL
#include <utility>
#include <vector>
#include <set>
#include "util.h"
#include <vector>
#include <iostream>
#include <list>
#include <algorithm>
#include <limits.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <fstream>
#include <list>
#include <map>
#include <limits.h>
#include <cmath>
#include <utility>
#include <fstream>
#include <algorithm>
#include "util.h"
#include <cstdlib>

using namespace std;
#include "Bot.h"

template <class T>

pair<int,int> distToNearest(vector<T> & group, int x, int y, int size)
{
  set<int> empty;
  return distToNearest(group, x,y,size,empty);
}

template <class T>
pair<int,int> distToNearest(vector<T> & group, int x, int y, int size, set<int> & ignore)
{
  pair<int,int> ret;
  ret.first=INT_MAX;
  ret.second=-1;
  for(unsigned int i=0;i<group.size();i++)
  {
    int temp = distance(x,y,size,group[i].x(),group[i].y(),group[i].size());
    if(temp < ret.first && ignore.find(group[i].id())==ignore.end())
    {
      ret.first=temp;
      ret.second=i;
    }
  }
  return ret;
}

template <class T>
bool inRange(Bot& actor, T& target)
{
  return distance(actor.x(),actor.y(),actor.size(),target.x(),target.y(),target.size()) <= (actor.range()+1);
}

#endif
