//Copyright (C) 2009 - Missouri S&T ACM AI Team
//Please do not modify this file while building your AI
//See AI.h & AI.cpp for that
#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <iostream>
#include <vector>
#include <string>


struct Mappable
{
  int id;
  int x;
  int y;
  
  friend std::ostream& operator<<(std::ostream& stream, Mappable obj);
};

struct Unit
{
  int id;
  int x;
  int y;
  int owner;
  int health;
  
  friend std::ostream& operator<<(std::ostream& stream, Unit obj);
};

struct Bot
{
  int id;
  int x;
  int y;
  int owner;
  int health;
  int attack;
  int range;
  int speed;
  int buildRate;
  int size;
  
  friend std::ostream& operator<<(std::ostream& stream, Bot obj);
};


struct Animation
{
  int type;
};


struct GameState
{
  std::vector<Mappable> mappables;
  std::vector<Unit> units;
  std::vector<Bot> bots;
  
  int turnNumber;
  int playerID;
  int boardX;
  int boardY;
  int gameNumber;
  
  std::vector<Animation*> animations;
  friend std::ostream& operator<<(std::ostream& stream, GameState obj);
};

struct Game
{
  std::vector<GameState> states;
  std::string players[2];
  int winner;

  Game();
};

#endif
