//Copyright (C) 2009 - Missouri S&T ACM AI Team
//Please do not modify this file while building your AI
//See AI.h & AI.cpp for that
#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <iostream>
#include <vector>
#include <string>

const int ADD = 0;
const int COLLIDE = 1;
const int BUILD = 2;
const int COMBINE = 3;
const int HEAL = 4;
const int MOVE = 5;
const int REMOVE = 6;
const int SPLIT = 7;
const int TALK = 8;

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
  int maxHealth;
  
  friend std::ostream& operator<<(std::ostream& stream, Unit obj);
};

struct Bot
{
  int id;
  int x;
  int y;
  int owner;
  int health;
  int maxHealth;
  int actions;
  int steps;
  int size;
  int damage;
  int range;
  int movitude;
  int actitude;
  int buildRate;
  int partOf;
  int building;
  
  friend std::ostream& operator<<(std::ostream& stream, Bot obj);
};

struct Frame
{
  int id;
  int x;
  int y;
  int owner;
  int health;
  int maxHealth;
  int type;
  int size;
  int completionTime;
  
  friend std::ostream& operator<<(std::ostream& stream, Frame obj);
};

struct Wall
{
  int id;
  int x;
  int y;
  int owner;
  int health;
  int maxHealth;
  
  friend std::ostream& operator<<(std::ostream& stream, Wall obj);
};

struct Type
{
  int id;
  char* name;
  int maxHealth;
  int damage;
  int range;
  int movitude;
  int actitude;
  int buildRate;
  
  friend std::ostream& operator<<(std::ostream& stream, Type obj);
};


struct Animation
{
  int type;
};

struct Add : public Animation
{
  int robot;
  
  friend std::ostream& operator<<(std::ostream& stream, Add obj);
};

struct Collide : public Animation
{
  int attacker;
  int victim;
  
  friend std::ostream& operator<<(std::ostream& stream, Collide obj);
};

struct Build : public Animation
{
  int builder;
  int frame;
  
  friend std::ostream& operator<<(std::ostream& stream, Build obj);
};

struct Combine : public Animation
{
  int bot1;
  int bot2;
  int bot3;
  int bot4;
  
  friend std::ostream& operator<<(std::ostream& stream, Combine obj);
};

struct Heal : public Animation
{
  int healer;
  int victim;
  
  friend std::ostream& operator<<(std::ostream& stream, Heal obj);
};

struct Move : public Animation
{
  int robot;
  int direction;
  
  friend std::ostream& operator<<(std::ostream& stream, Move obj);
};

struct Remove : public Animation
{
  int robot;
  
  friend std::ostream& operator<<(std::ostream& stream, Remove obj);
};

struct Split : public Animation
{
  int robot;
  
  friend std::ostream& operator<<(std::ostream& stream, Split obj);
};

struct Talk : public Animation
{
  int speaker;
  char* message;
  
  friend std::ostream& operator<<(std::ostream& stream, Talk obj);
};


struct GameState
{
  std::vector<Mappable> mappables;
  std::vector<Unit> units;
  std::vector<Bot> bots;
  std::vector<Frame> frames;
  std::vector<Wall> walls;
  std::vector<Type> types;
  
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
