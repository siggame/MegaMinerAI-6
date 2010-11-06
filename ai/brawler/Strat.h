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
#ifndef STRAT_H
#define STRAT_H
#include <vector>
#include "MyUtil.h"

using namespace std;

enum GENE{FRIEND,FOE,G_SIZE};

struct Strat
{
  bool played;
  int score;
  vector<int> gene;
  static void load(string,vector<Strat>& pop);
  static void save(string,vector<Strat>& pop);
};


#endif
