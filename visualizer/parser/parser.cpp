#include "parser.h"
#include "sexp/sexp.h"
#include "sexp/parser.h"
#include "sexp/sfcompat.h"

#include <cstdio>
#include <cstdlib>
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
  object.maxHealth = atoi(sub->val);
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
  object.maxHealth = atoi(sub->val);
  sub = sub->next;
  object.actions = atoi(sub->val);
  sub = sub->next;
  object.steps = atoi(sub->val);
  sub = sub->next;
  object.size = atoi(sub->val);
  sub = sub->next;
  object.damage = atoi(sub->val);
  sub = sub->next;
  object.range = atoi(sub->val);
  sub = sub->next;
  object.movitude = atoi(sub->val);
  sub = sub->next;
  object.actitude = atoi(sub->val);
  sub = sub->next;
  object.buildRate = atoi(sub->val);
  sub = sub->next;
  object.partOf = atoi(sub->val);
  sub = sub->next;
  object.building = atoi(sub->val);
  sub = sub->next;
  
}
static void parseFrame(Frame& object, sexp_t* expression)
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
  object.maxHealth = atoi(sub->val);
  sub = sub->next;
  sub = sub->next;
  object.size = atoi(sub->val);
  sub = sub->next;
  object.completionTime = atoi(sub->val);
  sub = sub->next;
  
}
static void parseWall(Wall& object, sexp_t* expression)
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
  object.maxHealth = atoi(sub->val);
  sub = sub->next;
  
}
static void parseType(Type& object, sexp_t* expression)
{
  sexp_t* sub;
  sub = expression->list;
  
  object.id = atoi(sub->val);
  sub = sub->next;
  object.name = new char[strlen(sub->val)+1];
  strncpy(object.name, sub->val, strlen(sub->val));
  object.name[strlen(sub->val)] = 0;
  sub = sub->next;
  object.maxHealth = atoi(sub->val);
  sub = sub->next;
  object.damage = atoi(sub->val);
  sub = sub->next;
  object.range = atoi(sub->val);
  sub = sub->next;
  object.movitude = atoi(sub->val);
  sub = sub->next;
  object.actitude = atoi(sub->val);
  sub = sub->next;
  object.buildRate = atoi(sub->val);
  sub = sub->next;
  
}

static void parseAdd(Add& object, sexp_t* expression)
{
  sexp_t* sub;
  sub = expression->list;
  
  sub = sub->next;
  
}
static void parseCollide(Collide& object, sexp_t* expression)
{
  sexp_t* sub;
  sub = expression->list;
  
  sub = sub->next;
  sub = sub->next;
  
}
static void parseBuild(Build& object, sexp_t* expression)
{
  sexp_t* sub;
  sub = expression->list;
  
  sub = sub->next;
  sub = sub->next;
  
}
static void parseCombine(Combine& object, sexp_t* expression)
{
  sexp_t* sub;
  sub = expression->list;
  
  sub = sub->next;
  sub = sub->next;
  sub = sub->next;
  sub = sub->next;
  
}
static void parseHeal(Heal& object, sexp_t* expression)
{
  sexp_t* sub;
  sub = expression->list;
  
  sub = sub->next;
  sub = sub->next;
  
}
static void parseMove(Move& object, sexp_t* expression)
{
  sexp_t* sub;
  sub = expression->list;
  
  sub = sub->next;
  object.direction = atoi(sub->val);
  sub = sub->next;
  
}
static void parseRemove(Remove& object, sexp_t* expression)
{
  sexp_t* sub;
  sub = expression->list;
  
  sub = sub->next;
  
}
static void parseSplit(Split& object, sexp_t* expression)
{
  sexp_t* sub;
  sub = expression->list;
  
  sub = sub->next;
  
}
static void parseTalk(Talk& object, sexp_t* expression)
{
  sexp_t* sub;
  sub = expression->list;
  
  sub = sub->next;
  object.message = new char[strlen(sub->val)+1];
  strncpy(object.message, sub->val, strlen(sub->val));
  object.message[strlen(sub->val)] = 0;
  sub = sub->next;
  
}

static bool parseSexp(Game& game, sexp_t* expression)
{
  sexp_t* sub, *subsub;
  expression = expression->list;
  if( !expression )
    return false;
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
      else if(string(sub->val) == "Frame")
      {
        sub = sub->next;
        while(sub)
        {
          Frame object;
          parseFrame(object, sub);
          gs.frames.push_back(object);
          
          sub = sub->next;
        }
      }
      else if(string(sub->val) == "Wall")
      {
        sub = sub->next;
        while(sub)
        {
          Wall object;
          parseWall(object, sub);
          gs.walls.push_back(object);
          
          sub = sub->next;
        }
      }
      else if(string(sub->val) == "Type")
      {
        sub = sub->next;
        while(sub)
        {
          Type object;
          parseType(object, sub);
          gs.types.push_back(object);
          
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
      if(string(sub->val) == "add")
      {
        Add* animation = new Add;
        parseAdd(*animation, sub);
        animations.push_back(animation);
      }
      if(string(sub->val) == "collide")
      {
        Collide* animation = new Collide;
        parseCollide(*animation, sub);
        animations.push_back(animation);
      }
      if(string(sub->val) == "build")
      {
        Build* animation = new Build;
        parseBuild(*animation, sub);
        animations.push_back(animation);
      }
      if(string(sub->val) == "combine")
      {
        Combine* animation = new Combine;
        parseCombine(*animation, sub);
        animations.push_back(animation);
      }
      if(string(sub->val) == "heal")
      {
        Heal* animation = new Heal;
        parseHeal(*animation, sub);
        animations.push_back(animation);
      }
      if(string(sub->val) == "move")
      {
        Move* animation = new Move;
        parseMove(*animation, sub);
        animations.push_back(animation);
      }
      if(string(sub->val) == "remove")
      {
        Remove* animation = new Remove;
        parseRemove(*animation, sub);
        animations.push_back(animation);
      }
      if(string(sub->val) == "split")
      {
        Split* animation = new Split;
        parseSplit(*animation, sub);
        animations.push_back(animation);
      }
      if(string(sub->val) == "talk")
      {
        Talk* animation = new Talk;
        parseTalk(*animation, sub);
        animations.push_back(animation);
      }
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

  return true;
}


bool parseFile(Game& game, const char* filename)
{
  bool value;
  FILE* in = fopen(filename, "r");
  int size;
  if(!in)
    return false;
  
  parseFile(in);
  
  sexp_t* st = NULL;
  
  while(st = parse())
  {
    if( !parseSexp(game, st) )
      return false;
    destroy_sexp(st);
  }
  
  fclose(in);
  
  return true;
}


bool parseString(Game& game, const char* string)
{
  sexp_t* st = NULL;
  
  st = extract_sexpr(string);

  while(st)
  {
    parseSexp(game, st);
    destroy_sexp(st);
    st = parse();
  }
  
  return true;
}
