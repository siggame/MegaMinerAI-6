#include "parser.h"
#include "sexp/sexp.h"
#include "sexp/parser.h"
#include "sexp/sfcompat.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;


static bool parseMappable(Mappable& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  sub = expression->list;

  if ( !sub ) return false;
  object.id = atoi(sub->val);
  sub = sub->next;
  if ( !sub ) return false;
  object.x = atoi(sub->val);
  sub = sub->next;
  if ( !sub ) return false;
  object.y = atoi(sub->val);
  sub = sub->next;
  return true;
}
static bool parseUnit(Unit& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  sub = expression->list;

  if ( !sub ) return false;
  object.id = atoi(sub->val);
  sub = sub->next;
  if ( !sub ) return false;
  object.x = atoi(sub->val);
  sub = sub->next;
  if ( !sub ) return false;
  object.y = atoi(sub->val);
  sub = sub->next;
  if ( !sub ) return false;
  object.owner = atoi(sub->val);
  sub = sub->next;
  if ( !sub ) return false;
  object.health = atoi(sub->val);
  sub = sub->next;
  if ( !sub ) return false;
  object.maxHealth = atoi(sub->val);
  sub = sub->next;
  return true;
}
static bool parseBot(Bot& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  sub = expression->list;

  if ( !sub ) return false;
  object.id = atoi(sub->val);
  sub = sub->next;
  if ( !sub ) return false;
  object.x = atoi(sub->val);
  sub = sub->next;
  if ( !sub ) return false;
  object.y = atoi(sub->val);
  sub = sub->next;
  if ( !sub ) return false;
  object.owner = atoi(sub->val);
  sub = sub->next;
  if ( !sub ) return false;
  object.health = atoi(sub->val);
  sub = sub->next;
  if ( !sub ) return false;
  object.maxHealth = atoi(sub->val);
  sub = sub->next;
  if ( !sub ) return false;
  object.actions = atoi(sub->val);
  sub = sub->next;
  if ( !sub ) return false;
  object.steps = atoi(sub->val);
  sub = sub->next;
  if ( !sub ) return false;
  object.size = atoi(sub->val);
  sub = sub->next;
  if ( !sub ) return false;
  object.damage = atoi(sub->val);
  sub = sub->next;
  if ( !sub ) return false;
  object.range = atoi(sub->val);
  sub = sub->next;
  if ( !sub ) return false;
  object.movitude = atoi(sub->val);
  sub = sub->next;
  if ( !sub ) return false;
  object.actitude = atoi(sub->val);
  sub = sub->next;
  if ( !sub ) return false;
  object.buildRate = atoi(sub->val);
  sub = sub->next;
  if ( !sub ) return false;
  object.partOf = atoi(sub->val);
  sub = sub->next;
  if ( !sub ) return false;
  object.building = atoi(sub->val);
  sub = sub->next;
  return true;
}
static bool parseFrame(Frame& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  sub = expression->list;

  if ( !sub ) return false;
  object.id = atoi(sub->val);
  sub = sub->next;
  if ( !sub ) return false;
  object.x = atoi(sub->val);
  sub = sub->next;
  if ( !sub ) return false;
  object.y = atoi(sub->val);
  sub = sub->next;
  if ( !sub ) return false;
  object.owner = atoi(sub->val);
  sub = sub->next;
  if ( !sub ) return false;
  object.health = atoi(sub->val);
  sub = sub->next;
  if ( !sub ) return false;
  object.maxHealth = atoi(sub->val);
  sub = sub->next;
  if ( !sub ) return false;
  sub = sub->next;
  if ( !sub ) return false;
  object.size = atoi(sub->val);
  sub = sub->next;
  if ( !sub ) return false;
  object.completionTime = atoi(sub->val);
  sub = sub->next;
  return true;
}
static bool parseWall(Wall& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  sub = expression->list;

  if ( !sub ) return false;
  object.id = atoi(sub->val);
  sub = sub->next;
  if ( !sub ) return false;
  object.x = atoi(sub->val);
  sub = sub->next;
  if ( !sub ) return false;
  object.y = atoi(sub->val);
  sub = sub->next;
  if ( !sub ) return false;
  object.owner = atoi(sub->val);
  sub = sub->next;
  if ( !sub ) return false;
  object.health = atoi(sub->val);
  sub = sub->next;
  if ( !sub ) return false;
  object.maxHealth = atoi(sub->val);
  sub = sub->next;
  return true;
}
static bool parseType(Type& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  sub = expression->list;

  if ( !sub ) return false;
  object.id = atoi(sub->val);
  sub = sub->next;
  if ( !sub ) return false;
  object.name = new char[strlen(sub->val)+1];
  strncpy(object.name, sub->val, strlen(sub->val));
  object.name[strlen(sub->val)] = 0;
  sub = sub->next;
  if ( !sub ) return false;
  object.maxHealth = atoi(sub->val);
  sub = sub->next;
  if ( !sub ) return false;
  object.damage = atoi(sub->val);
  sub = sub->next;
  if ( !sub ) return false;
  object.range = atoi(sub->val);
  sub = sub->next;
  if ( !sub ) return false;
  object.movitude = atoi(sub->val);
  sub = sub->next;
  if ( !sub ) return false;
  object.actitude = atoi(sub->val);
  sub = sub->next;
  if ( !sub ) return false;
  object.buildRate = atoi(sub->val);
  sub = sub->next;
  return true;
}

static bool parseAdd(Add& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  sub = expression->list;
  if( !sub ) return false;
  sub = sub->next;
  return true;
}
static bool parseCollide(Collide& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  sub = expression->list;
  if( !sub ) return false;
  sub = sub->next;
  if( !sub ) return false;
  sub = sub->next;
  return true;
}
static bool parseBuild(Build& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  sub = expression->list;
  if( !sub ) return false;
  sub = sub->next;
  if( !sub ) return false;
  sub = sub->next;
  return true;
}
static bool parseCombine(Combine& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  sub = expression->list;
  if( !sub ) return false;
  sub = sub->next;
  if( !sub ) return false;
  sub = sub->next;
  if( !sub ) return false;
  sub = sub->next;
  if( !sub ) return false;
  sub = sub->next;
  return true;
}
static bool parseHeal(Heal& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  sub = expression->list;
  if( !sub ) return false;
  sub = sub->next;
  if( !sub ) return false;
  sub = sub->next;
  return true;
}
static bool parseMove(Move& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  sub = expression->list;
  if( !sub ) return false;
  sub = sub->next;
  if( !sub ) return false;
  object.direction = atoi(sub->val);
  sub = sub->next;
  return true;
}
static bool parseRemove(Remove& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  sub = expression->list;
  if( !sub ) return false;
  sub = sub->next;
  return true;
}
static bool parseSplit(Split& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  sub = expression->list;
  if( !sub ) return false;
  sub = sub->next;
  return true;
}
static bool parseTalk(Talk& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  sub = expression->list;
  if( !sub ) return false;
  sub = sub->next;
  if( !sub ) return false;
  object.message = new char[strlen(sub->val)+1];
  strncpy(object.message, sub->val, strlen(sub->val));
  object.message[strlen(sub->val)] = 0;
  sub = sub->next;
  return true;
}

static bool parseSexp(Game& game, sexp_t* expression)
{
  sexp_t* sub, *subsub;
  if( !expression ) return false;
  expression = expression->list;
  if( !expression ) return false;
  if(expression->val != NULL && strcmp(expression->val, "status") == 0)
  {
    GameState gs;
    while(expression->next != NULL)
    {
      expression = expression->next;
      sub = expression->list;
      if ( !sub ) return false;
      if(string(sub->val) == "game")
      {
          if ( !sub ) return false;
          gs.turnNumber = atoi(sub->val);
          sub = sub->next;
          if ( !sub ) return false;
          gs.playerID = atoi(sub->val);
          sub = sub->next;
          if ( !sub ) return false;
          gs.boardX = atoi(sub->val);
          sub = sub->next;
          if ( !sub ) return false;
          gs.boardY = atoi(sub->val);
          sub = sub->next;
          if ( !sub ) return false;
          gs.gameNumber = atoi(sub->val);
          sub = sub->next;
      }
      else if(string(sub->val) == "Mappable")
      {
        sub = sub->next;
        bool flag = true;
        while(sub && flag)
        {
          Mappable object;
          flag = parseMappable(object, sub);
          gs.mappables.push_back(object);
          sub = sub->next;
        }
        if ( !flag ) return false;
      }
      else if(string(sub->val) == "Unit")
      {
        sub = sub->next;
        bool flag = true;
        while(sub && flag)
        {
          Unit object;
          flag = parseUnit(object, sub);
          gs.units.push_back(object);
          sub = sub->next;
        }
        if ( !flag ) return false;
      }
      else if(string(sub->val) == "Bot")
      {
        sub = sub->next;
        bool flag = true;
        while(sub && flag)
        {
          Bot object;
          flag = parseBot(object, sub);
          gs.bots.push_back(object);
          sub = sub->next;
        }
        if ( !flag ) return false;
      }
      else if(string(sub->val) == "Frame")
      {
        sub = sub->next;
        bool flag = true;
        while(sub && flag)
        {
          Frame object;
          flag = parseFrame(object, sub);
          gs.frames.push_back(object);
          sub = sub->next;
        }
        if ( !flag ) return false;
      }
      else if(string(sub->val) == "Wall")
      {
        sub = sub->next;
        bool flag = true;
        while(sub && flag)
        {
          Wall object;
          flag = parseWall(object, sub);
          gs.walls.push_back(object);
          sub = sub->next;
        }
        if ( !flag ) return false;
      }
      else if(string(sub->val) == "Type")
      {
        sub = sub->next;
        bool flag = true;
        while(sub && flag)
        {
          Type object;
          flag = parseType(object, sub);
          gs.types.push_back(object);
          sub = sub->next;
        }
        if ( !flag ) return false;
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
      if ( !sub ) return false;
      if(string(sub->val) == "add")
      {
        Add* animation = new Add;
        if ( !parseAdd(*animation, sub) )
          return false;
        animations.push_back(animation);
      }
      if(string(sub->val) == "collide")
      {
        Collide* animation = new Collide;
        if ( !parseCollide(*animation, sub) )
          return false;
        animations.push_back(animation);
      }
      if(string(sub->val) == "build")
      {
        Build* animation = new Build;
        if ( !parseBuild(*animation, sub) )
          return false;
        animations.push_back(animation);
      }
      if(string(sub->val) == "combine")
      {
        Combine* animation = new Combine;
        if ( !parseCombine(*animation, sub) )
          return false;
        animations.push_back(animation);
      }
      if(string(sub->val) == "heal")
      {
        Heal* animation = new Heal;
        if ( !parseHeal(*animation, sub) )
          return false;
        animations.push_back(animation);
      }
      if(string(sub->val) == "move")
      {
        Move* animation = new Move;
        if ( !parseMove(*animation, sub) )
          return false;
        animations.push_back(animation);
      }
      if(string(sub->val) == "remove")
      {
        Remove* animation = new Remove;
        if ( !parseRemove(*animation, sub) )
          return false;
        animations.push_back(animation);
      }
      if(string(sub->val) == "split")
      {
        Split* animation = new Split;
        if ( !parseSplit(*animation, sub) )
          return false;
        animations.push_back(animation);
      }
      if(string(sub->val) == "talk")
      {
        Talk* animation = new Talk;
        if ( !parseTalk(*animation, sub) )
          return false;
        animations.push_back(animation);
      }
    }
    game.states[game.states.size()-1].animations = animations;
  }
  else if(string(expression->val) == "ident")
  {
    expression = expression->next;
    if ( !expression ) return false;
    sub = expression->list;
    while(sub)
    {
      subsub = sub->list;
      if ( !subsub ) return false;
      int number = atoi(subsub->val);
      if(number > 0)
      {
        subsub = subsub->next;
        if ( !subsub ) return false;
        subsub = subsub->next;
        if ( !subsub ) return false;
        game.players[number] = subsub->val;
      }
      sub = sub->next;
    }
  }
  else if(string(expression->val) == "game-winner")
  {
    expression = expression->next;
    if ( !expression ) return false;
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
    if( !parseSexp(game, st) ) return false;
    destroy_sexp(st);
  }

  fclose(in);

  return true;
}


bool parseString(Game& game, const char* string)
{
  sexp_t* st = NULL;

  st = extract_sexpr(string);
  bool flag = true;
  while(st && flag)
  {
    flag = parseSexp(game, st);
    destroy_sexp(st);
    st = parse();
  }

  return flag;
}
