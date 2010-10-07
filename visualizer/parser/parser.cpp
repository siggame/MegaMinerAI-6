#include "parser.h"
#include "sexp/sexp.h"

#include <cstdio>
#include <cstring>

using namespace std;


static void parseMappable(Mappable& object, sexp_t* expression)
{
  sexp_t* sub;
  sub = expression->list;
  
  object.id = atoi(sub->val);
  sub = sub->next;
  object.x = atoi(sub->val);
  sub = sub->next;
  object.y = atoi(sub->val);
  sub = sub->next;
  
}
static void parseUnit(Unit& object, sexp_t* expression)
{
  sexp_t* sub;
  sub = expression->list;
  
  object.id = atoi(sub->val);
  sub = sub->next;
  object.x = atoi(sub->val);
  sub = sub->next;
  object.y = atoi(sub->val);
  sub = sub->next;
  object.owner = atoi(sub->val);
  sub = sub->next;
  object.health = atoi(sub->val);
  sub = sub->next;
  
}
static void parseBot(Bot& object, sexp_t* expression)
{
  sexp_t* sub;
  sub = expression->list;
  
  object.id = atoi(sub->val);
  sub = sub->next;
  object.x = atoi(sub->val);
  sub = sub->next;
  object.y = atoi(sub->val);
  sub = sub->next;
  object.owner = atoi(sub->val);
  sub = sub->next;
  object.health = atoi(sub->val);
  sub = sub->next;
  object.attack = atoi(sub->val);
  sub = sub->next;
  object.range = atoi(sub->val);
  sub = sub->next;
  object.speed = atoi(sub->val);
  sub = sub->next;
  object.buildRate = atoi(sub->val);
  sub = sub->next;
  object.size = atoi(sub->val);
  sub = sub->next;
  
}


static bool parseSexp(Game& game, sexp_t* expression)
{
  sexp_t* sub, *subsub;
  expression = expression->list;
  if(expression->val != NULL && strcmp(expression->val, "status") == 0)
  {
    GameState gs;
    while(expression->next != NULL)
    {
      expression = expression->next;
      sub = expression->list;
      if(string(sub->val) == "game")
      {
          gs.turnNumber = atoi(sub->val);
          sub = sub->next;
          
          gs.playerID = atoi(sub->val);
          sub = sub->next;
          
          gs.boardX = atoi(sub->val);
          sub = sub->next;
          
          gs.boardY = atoi(sub->val);
          sub = sub->next;
          
          gs.gameNumber = atoi(sub->val);
          sub = sub->next;
          
      }
      else if(string(sub->val) == "Mappable")
      {
        sub = sub->next;
        while(sub)
        {
          Mappable object;
          parseMappable(object, sub);
          gs.mappables.push_back(object);
          
          sub = sub->next;
        }
      }
      else if(string(sub->val) == "Unit")
      {
        sub = sub->next;
        while(sub)
        {
          Unit object;
          parseUnit(object, sub);
          gs.units.push_back(object);
          
          sub = sub->next;
        }
      }
      else if(string(sub->val) == "Bot")
      {
        sub = sub->next;
        while(sub)
        {
          Bot object;
          parseBot(object, sub);
          gs.bots.push_back(object);
          
          sub = sub->next;
        }
      }
    }
    game.states.push_back(gs);
  }
  else if(string(expression->val) == "animations")
  {
    std::vector<Animation*> animations;
    while(expression->next)
    {
      expression = expression->next;
      sub = expression->list;
    }
    game.states[game.states.size()-1].animations = animations;
  }
  else if(string(expression->val) == "ident")
  {
    expression = expression->next;
    sub = expression->list;
    while(sub)
    {
      subsub = sub->list;
      int number = atoi(subsub->val);
      if(number > 0)
      {
        subsub = subsub->next->next;
        game.players[number] = subsub->val;
      }
      sub = sub->next;
    }
  }
  else if(string(expression->val) == "game-winner")
  {
    expression = expression->next;
    game.winner = atoi(expression->val);
  }
}

bool parseFile(Game& game, char* filename)
{
  bool value;
  FILE* in = fopen(filename, "r");
  int size;
  if(!in)
    return false;
  
  fseek(in, 0, SEEK_END);
  size = ftell(in);
  fseek(in, 0L, SEEK_SET);
  
  char* buffer = new char[size+1];
  fread(buffer, 1, size, in);
  buffer[size] = 0;
  
  fclose(in);
  
  value = parseString(game, buffer);
  
  delete[] buffer;
  
  return value;
}


bool parseString(Game& game, char* string)
{
  sexp_t* st = NULL;
  pcont_t* cc;
  cc = init_continuation(string);
  
  while(st = iparse_sexp( string, strlen(string), cc))
  {
    parseSexp(game, st);
    destroy_sexp(st);
  }
  
  return true;
}