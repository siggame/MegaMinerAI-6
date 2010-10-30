//Copyright (C) 2009 - Missouri S&T ACM AI Team
//Please do not modify this file while building your AI
//See AI.h & AI.cpp for that
#pragma warning(disable : 4996)

#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>

#include "game.h"
#include "network.h"
#include "structures.h"

#include "sexp/sfcompat.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#ifdef _WIN32
//Doh, namespace collision.
namespace Windows
{
    #include <Windows.h>
};
#else
#include <unistd.h>
#endif

#ifndef THREADLESS
#define LOCK(X) pthread_mutex_lock(X)
#define UNLOCK(X) pthread_mutex_unlock(X)
#else
#define LOCK(X)
#define UNLOCK(X)
#endif

using namespace std;

DLLEXPORT Connection* createConnection()
{
  Connection* c = new Connection;
  c->socket = -1;
  #ifndef THREADLESS
  pthread_mutex_init(&c->mutex, NULL);
  #endif
  
  c->turnNumber = 0;
  c->playerID = 0;
  c->boardX = 0;
  c->boardY = 0;
  c->gameNumber = 0;
  c->player0Time = 0;
  c->player1Time = 0;
  c->player0Name = 0;
  c->player1Name = 0;
  c->Bots = NULL;
  c->BotCount = 0;
  c->Frames = NULL;
  c->FrameCount = 0;
  c->Walls = NULL;
  c->WallCount = 0;
  c->Types = NULL;
  c->TypeCount = 0;
  return c;
}

DLLEXPORT int serverConnect(Connection* c, const char* host, const char* port)
{
  c->socket = open_server_connection(host, port);
  return c->socket + 1; //false if socket == -1
}

DLLEXPORT int serverLogin(Connection* c, const char* username, const char* password)
{
  string expr = "(login \"";
  expr += username;
  expr += "\" \"";
  expr += password;
  expr +="\")";

  send_string(c->socket, expr.c_str());

  sexp_t* expression, *message;

  char* reply = rec_string(c->socket);
  expression = extract_sexpr(reply);
  delete[] reply;
  
  message = expression->list;
  if(message->val == NULL || strcmp(message->val, "login-accepted") != 0)
  {
    cerr << "Unable to login to server" << endl;
    destroy_sexp(expression);
    return 0;
  }
  destroy_sexp(expression);
  return 1;
}

DLLEXPORT int createGame(Connection* c)
{
  sexp_t* expression, *number;

  send_string(c->socket, "(create-game)");
  
  char* reply = rec_string(c->socket);
  expression = extract_sexpr(reply);
  delete[] reply;
  
  number = expression->list->next;
  c->gameNumber = atoi(number->val);
  destroy_sexp(expression);
  
  std::cout << "Creating game " << c->gameNumber << endl;
  
  c->playerID = 0;
  
  return c->gameNumber;
}

DLLEXPORT int joinGame(Connection* c, int gameNum)
{
  sexp_t* expression;
  stringstream expr;
  
  c->gameNumber = gameNum;
  
  expr << "(join-game " << c->gameNumber << ")";
  send_string(c->socket, expr.str().c_str());
  
  char* reply = rec_string(c->socket);
  expression = extract_sexpr(reply);
  delete[] reply;
  
  if(strcmp(expression->list->val, "join-accepted") != 0)
  {
    cerr << "Game " << c->gameNumber << " doesn't exist." << endl;
    destroy_sexp(expression);
    return 0;
  }
  destroy_sexp(expression);
  
  c->playerID = 1;
  send_string(c->socket, "(game-start)");
  
  return 1;
}

DLLEXPORT void endTurn(Connection* c)
{
  LOCK( &c->mutex );
  send_string(c->socket, "(end-turn)");
  UNLOCK( &c->mutex );
}

DLLEXPORT void getStatus(Connection* c)
{
  LOCK( &c->mutex );
  send_string(c->socket, "(game-status)");
  UNLOCK( &c->mutex );
}



DLLEXPORT int unitTalk(_Unit* object, char* message)
{
  stringstream expr;
  expr << "(game-talk " << object->id
      << " \"" << escape_string(message) << "\""
       << ")";
  LOCK( &object->_c->mutex);
  send_string(object->_c->socket, expr.str().c_str());
  UNLOCK( &object->_c->mutex);
  return 1;
}


DLLEXPORT int botTalk(_Bot* object, char* message)
{
  stringstream expr;
  expr << "(game-talk " << object->id
      << " \"" << escape_string(message) << "\""
       << ")";
  LOCK( &object->_c->mutex);
  send_string(object->_c->socket, expr.str().c_str());
  UNLOCK( &object->_c->mutex);
  return 1;
}

DLLEXPORT int botMove(_Bot* object, char* direction)
{
  stringstream expr;
  expr << "(game-move " << object->id
      << " \"" << escape_string(direction) << "\""
       << ")";
  LOCK( &object->_c->mutex);
  send_string(object->_c->socket, expr.str().c_str());
  UNLOCK( &object->_c->mutex);
  return 1;
}

DLLEXPORT int botAttack(_Bot* object, _Unit* target)
{
  stringstream expr;
  expr << "(game-attack " << object->id
      << " " << target->id
       << ")";
  LOCK( &object->_c->mutex);
  send_string(object->_c->socket, expr.str().c_str());
  UNLOCK( &object->_c->mutex);
  return 1;
}

DLLEXPORT int botHeal(_Bot* object, _Bot* target)
{
  stringstream expr;
  expr << "(game-heal " << object->id
      << " " << target->id
       << ")";
  LOCK( &object->_c->mutex);
  send_string(object->_c->socket, expr.str().c_str());
  UNLOCK( &object->_c->mutex);
  return 1;
}

DLLEXPORT int botBuild(_Bot* object, _Type* type, int x, int y, int size)
{
  stringstream expr;
  expr << "(game-build " << object->id
      << " " << type->id
       << " " << x
       << " " << y
       << " " << size
       << ")";
  LOCK( &object->_c->mutex);
  send_string(object->_c->socket, expr.str().c_str());
  UNLOCK( &object->_c->mutex);
  return 1;
}

DLLEXPORT int botCombine(_Bot* object, _Bot* bot2, _Bot* bot3, _Bot* bot4)
{
  stringstream expr;
  expr << "(game-combine " << object->id
      << " " << bot2->id
      << " " << bot3->id
      << " " << bot4->id
       << ")";
  LOCK( &object->_c->mutex);
  send_string(object->_c->socket, expr.str().c_str());
  UNLOCK( &object->_c->mutex);
  return 1;
}

DLLEXPORT int botSplit(_Bot* object)
{
  stringstream expr;
  expr << "(game-split " << object->id
       << ")";
  LOCK( &object->_c->mutex);
  send_string(object->_c->socket, expr.str().c_str());
  UNLOCK( &object->_c->mutex);
  return 1;
}


DLLEXPORT int botMaxActions(_Bot* object)
{
}

DLLEXPORT int botMaxSteps(_Bot* object)
{
}

DLLEXPORT int frameTalk(_Frame* object, char* message)
{
  stringstream expr;
  expr << "(game-talk " << object->id
      << " \"" << escape_string(message) << "\""
       << ")";
  LOCK( &object->_c->mutex);
  send_string(object->_c->socket, expr.str().c_str());
  UNLOCK( &object->_c->mutex);
  return 1;
}


DLLEXPORT int wallTalk(_Wall* object, char* message)
{
  stringstream expr;
  expr << "(game-talk " << object->id
      << " \"" << escape_string(message) << "\""
       << ")";
  LOCK( &object->_c->mutex);
  send_string(object->_c->socket, expr.str().c_str());
  UNLOCK( &object->_c->mutex);
  return 1;
}



//Utility functions for parsing data
void parseMappable(Connection* c, _Mappable* object, sexp_t* expression)
{
  sexp_t* sub;
  sub = expression->list;
  
  object->_c = c;
  
  object->id = atoi(sub->val);
  sub = sub->next;
  object->x = atoi(sub->val);
  sub = sub->next;
  object->y = atoi(sub->val);
  sub = sub->next;
  
}
void parseUnit(Connection* c, _Unit* object, sexp_t* expression)
{
  sexp_t* sub;
  sub = expression->list;
  
  object->_c = c;
  
  object->id = atoi(sub->val);
  sub = sub->next;
  object->x = atoi(sub->val);
  sub = sub->next;
  object->y = atoi(sub->val);
  sub = sub->next;
  object->owner = atoi(sub->val);
  sub = sub->next;
  object->health = atoi(sub->val);
  sub = sub->next;
  object->maxHealth = atoi(sub->val);
  sub = sub->next;
  
}
void parseBot(Connection* c, _Bot* object, sexp_t* expression)
{
  sexp_t* sub;
  sub = expression->list;
  
  object->_c = c;
  
  object->id = atoi(sub->val);
  sub = sub->next;
  object->x = atoi(sub->val);
  sub = sub->next;
  object->y = atoi(sub->val);
  sub = sub->next;
  object->owner = atoi(sub->val);
  sub = sub->next;
  object->health = atoi(sub->val);
  sub = sub->next;
  object->maxHealth = atoi(sub->val);
  sub = sub->next;
  object->actions = atoi(sub->val);
  sub = sub->next;
  object->steps = atoi(sub->val);
  sub = sub->next;
  object->size = atoi(sub->val);
  sub = sub->next;
  object->damage = atoi(sub->val);
  sub = sub->next;
  object->range = atoi(sub->val);
  sub = sub->next;
  object->movitude = atoi(sub->val);
  sub = sub->next;
  object->actitude = atoi(sub->val);
  sub = sub->next;
  object->buildRate = atoi(sub->val);
  sub = sub->next;
  object->partOf = atoi(sub->val);
  sub = sub->next;
  object->building = atoi(sub->val);
  sub = sub->next;
  object->type = atoi(sub->val);
  sub = sub->next;
  
}
void parseFrame(Connection* c, _Frame* object, sexp_t* expression)
{
  sexp_t* sub;
  sub = expression->list;
  
  object->_c = c;
  
  object->id = atoi(sub->val);
  sub = sub->next;
  object->x = atoi(sub->val);
  sub = sub->next;
  object->y = atoi(sub->val);
  sub = sub->next;
  object->owner = atoi(sub->val);
  sub = sub->next;
  object->health = atoi(sub->val);
  sub = sub->next;
  object->maxHealth = atoi(sub->val);
  sub = sub->next;
  sub = sub->next;
  object->size = atoi(sub->val);
  sub = sub->next;
  object->completionTime = atoi(sub->val);
  sub = sub->next;
  
}
void parseWall(Connection* c, _Wall* object, sexp_t* expression)
{
  sexp_t* sub;
  sub = expression->list;
  
  object->_c = c;
  
  object->id = atoi(sub->val);
  sub = sub->next;
  object->x = atoi(sub->val);
  sub = sub->next;
  object->y = atoi(sub->val);
  sub = sub->next;
  object->owner = atoi(sub->val);
  sub = sub->next;
  object->health = atoi(sub->val);
  sub = sub->next;
  object->maxHealth = atoi(sub->val);
  sub = sub->next;
  
}
void parseType(Connection* c, _Type* object, sexp_t* expression)
{
  sexp_t* sub;
  sub = expression->list;
  
  object->_c = c;
  
  object->id = atoi(sub->val);
  sub = sub->next;
  object->name = new char[strlen(sub->val)+1];
  strncpy(object->name, sub->val, strlen(sub->val));
  object->name[strlen(sub->val)] = 0;
  sub = sub->next;
  object->maxHealth = atoi(sub->val);
  sub = sub->next;
  object->damage = atoi(sub->val);
  sub = sub->next;
  object->range = atoi(sub->val);
  sub = sub->next;
  object->movitude = atoi(sub->val);
  sub = sub->next;
  object->actitude = atoi(sub->val);
  sub = sub->next;
  object->buildRate = atoi(sub->val);
  sub = sub->next;
  
}

DLLEXPORT int networkLoop(Connection* c)
{
  while(true)
  {
    sexp_t* base, *expression, *sub, *subsub;
    char* message = rec_string(c->socket);
    string text = message;
    base = extract_sexpr(message);
    delete[] message;
    expression = base->list;
    if(expression->val != NULL && strcmp(expression->val, "game-winner") == 0)
    {
      expression = expression->next->next->next;
      int winnerID = atoi(expression->val);
      if(winnerID == c->playerID)
      {
        cout << "You win!" << endl;
      }
      else
      {
        cout << "You lose. :(" << endl;
      }
      stringstream expr;
      expr << "(request-log " << c->gameNumber << ")";
      send_string(c->socket, expr.str().c_str());
      return 0;
    }
    else if(expression->val != NULL && strcmp(expression->val, "log") == 0)
    {
      ofstream out;
      stringstream filename;
      expression = expression->next;
      filename << expression->val;
      filename << ".gamelog";
      expression = expression->next;
      out.open(filename.str().c_str());
      if (out.good())
        out.write(expression->val, strlen(expression->val));
      else
        cerr << "Error : Could not create log." << endl;
      out.close();
      return 0;
    }
    else if(expression->val != NULL && strcmp(expression->val, "game-accepted")==0)
    {
      char gameID[30];

      expression = expression->next;
      strcpy(gameID, expression->val);
      cout << "Created game " << gameID << endl;
    }
    else if(expression->val != NULL && strcmp(expression->val, "ident")==0)
    {
      if(c->player0Name)
        delete[] c->player0Name;
      int length = strlen(expression->next->list->list->next->next->val)+1;
      c->player0Name = new char[length];
      strcpy(c->player0Name, expression->next->list->list->next->next->val);
      c->player0Name[length-1] = 0;

      if(c->player1Name)
        delete[] c->player1Name;
      length = strlen(expression->next->list->next->list->next->next->val)+1;
      c->player1Name = new char[length];
      strcpy(c->player1Name, expression->next->list->next->list->next->next->val);
      c->player1Name[length-1] = 0;
    }

    else if(expression->val != NULL && strstr(expression->val, "denied"))
    {
      cout << expression->val << endl;
      cout << expression->next->val << endl;
    }
    else if(expression->val != NULL && strcmp(expression->val, "status") == 0)
    {
      while(expression->next != NULL)
      {
        expression = expression->next;
        sub = expression->list;
        if(string(sub->val) == "game")
        {
          sub = sub->next;
          c->turnNumber = atoi(sub->val);
          sub = sub->next;

          c->playerID = atoi(sub->val);
          sub = sub->next;

          c->boardX = atoi(sub->val);
          sub = sub->next;

          c->boardY = atoi(sub->val);
          sub = sub->next;

          c->gameNumber = atoi(sub->val);
          sub = sub->next;

          c->player0Time = atoi(sub->val);
          sub = sub->next;

          c->player1Time = atoi(sub->val);
          sub = sub->next;

        }
        else if(string(sub->val) == "Bot")
        {
          if(c->Bots)
          {
            for(int i = 0; i < c->BotCount; i++)
            {
            }
            delete[] c->Bots;
          }
          c->BotCount =  sexp_list_length(expression)-1; //-1 for the header
          c->Bots = new _Bot[c->BotCount];
          for(int i = 0; i < c->BotCount; i++)
          {
            sub = sub->next;
            parseBot(c, c->Bots+i, sub);
          }
        }
        else if(string(sub->val) == "Frame")
        {
          if(c->Frames)
          {
            for(int i = 0; i < c->FrameCount; i++)
            {
            }
            delete[] c->Frames;
          }
          c->FrameCount =  sexp_list_length(expression)-1; //-1 for the header
          c->Frames = new _Frame[c->FrameCount];
          for(int i = 0; i < c->FrameCount; i++)
          {
            sub = sub->next;
            parseFrame(c, c->Frames+i, sub);
          }
        }
        else if(string(sub->val) == "Wall")
        {
          if(c->Walls)
          {
            for(int i = 0; i < c->WallCount; i++)
            {
            }
            delete[] c->Walls;
          }
          c->WallCount =  sexp_list_length(expression)-1; //-1 for the header
          c->Walls = new _Wall[c->WallCount];
          for(int i = 0; i < c->WallCount; i++)
          {
            sub = sub->next;
            parseWall(c, c->Walls+i, sub);
          }
        }
        else if(string(sub->val) == "Type")
        {
          if(c->Types)
          {
            for(int i = 0; i < c->TypeCount; i++)
            {
              delete[] c->Types[i].name;
            }
            delete[] c->Types;
          }
          c->TypeCount =  sexp_list_length(expression)-1; //-1 for the header
          c->Types = new _Type[c->TypeCount];
          for(int i = 0; i < c->TypeCount; i++)
          {
            sub = sub->next;
            parseType(c, c->Types+i, sub);
          }
        }
      }
      return 1;
    }
    else
    {
#ifdef SHOW_WARNINGS
      cerr << "Unrecognized message: " << text << endl;
#endif
    }
  }
}

DLLEXPORT _Bot* getBot(Connection* c, int num)
{
  return c->Bots + num;
}
DLLEXPORT int getBotCount(Connection* c)
{
  return c->BotCount;
}

DLLEXPORT _Frame* getFrame(Connection* c, int num)
{
  return c->Frames + num;
}
DLLEXPORT int getFrameCount(Connection* c)
{
  return c->FrameCount;
}

DLLEXPORT _Wall* getWall(Connection* c, int num)
{
  return c->Walls + num;
}
DLLEXPORT int getWallCount(Connection* c)
{
  return c->WallCount;
}

DLLEXPORT _Type* getType(Connection* c, int num)
{
  return c->Types + num;
}
DLLEXPORT int getTypeCount(Connection* c)
{
  return c->TypeCount;
}


DLLEXPORT int getTurnNumber(Connection* c)
{
  return c->turnNumber;
}
DLLEXPORT int getPlayerID(Connection* c)
{
  return c->playerID;
}
DLLEXPORT int getBoardX(Connection* c)
{
  return c->boardX;
}
DLLEXPORT int getBoardY(Connection* c)
{
  return c->boardY;
}
DLLEXPORT int getGameNumber(Connection* c)
{
  return c->gameNumber;
}
DLLEXPORT int getPlayer0Time(Connection* c)
{
  return c->player0Time;
}
DLLEXPORT int getPlayer1Time(Connection* c)
{
  return c->player1Time;
}
DLLEXPORT char* getPlayer0Name(Connection* c)
{
  return c->player0Name;
}
DLLEXPORT char* getPlayer1Name(Connection* c)
{
  return c->player1Name;
}
