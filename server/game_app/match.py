# -*- coding: iso-8859-1 -*-
from base import *
from matchUtils import *
from objects import *
import networking.config.config
from collections import defaultdict
from networking.sexpr.sexpr import *
import os
import itertools
import scribe

Scribe = scribe.Scribe

def loadClassDefaults(cfgFile = "config/defaults.cfg"):
  cfg = networking.config.config.readConfig(cfgFile)
  for className in cfg.keys():
    for attr in cfg[className]:
      setattr(eval(className), attr, cfg[className][attr])

class Match(DefaultGameWorld):
  def __init__(self, id, controller):
    self.id = int(id)
    self.controller = controller
    DefaultGameWorld.__init__(self)
    self.scribe = Scribe(self.logPath())
    self.addPlayer(self.scribe, "spectator")

    #TODO: INITIALIZE THESE!
    self.turnNumber = -1
    self.playerID = -1
    self.gameNumber = id
    self.initTypes()
    self.startBots()

  def initTypes(self):
    self.objects[self.nextid] = Type(self, self.nextid, "action", 10, 0, 0, 1, 4, 0)
    self.nextid += 1
    self.objects[self.nextid] = Type(self, self.nextid, "builder", 5, 0, 0, 1, 1, 1)
    self.nextid += 1
    self.objects[self.nextid] = Type(self, self.nextid, "cannon", 10, 2, 0, 1, 1, 0)
    self.nextid += 1
    self.objects[self.nextid] = Type(self, self.nextid, "damage", 10, 5, 0, 1, 1, 0)
    self.nextid += 1
    self.objects[self.nextid] = Type(self, self.nextid, "engine", 10, 2, 0, 4, 1, 0)
    self.nextid += 1
    self.objects[self.nextid] = Type(self, self.nextid, "fat", 20, 2, 0, 1, 1, 0)
    self.nextid += 1
    #(self.objects[self.nextid] = Type(self, self.nextid, name, maxHealth, damage, range, movitude, actitude, buildRate)
    #self.nextid += 1

  def startBots(self):
    self.addObject(Bot.fromType(self, 0, 0, 0, self.objects[1]))
    self.addObject(Bot.fromType(self, self.boardX, self.boardY, 1, self.objects[1]))

    #__init__(self, game, id, x, y, owner, health, maxHealth, actions, size, damage, range, movitude, actitude, buildRate, partOf, building)
    pass

  def addPlayer(self, connection, type="player"):
    connection.type = type
    if len(self.players) >= 2 and type == "player":
      return "Game is full"
    if type == "player":
      self.players.append(connection)
    elif type == "spectator":
      self.spectators.append(connection)
      #If the game has already started, send them the ident message
      if (self.turn is not None):
        self.sendIdent([connection])
    return True

  def removePlayer(self, connection):
    if connection in self.players:
      if self.turn is not None:
        winner = self.players[1 - self.getPlayerIndex(connection)]
        self.declareWinner(winner)
      self.players.remove(connection)
    else:
      self.spectators.remove(connection)

  def start(self):
    if len(self.players) < 2:
      return "Game is not full"
    if self.winner is not None or self.turn is not None:
      return "Game has already begun"
    
    #TODO: START STUFF

    self.turnNumber = -1
    
    self.sendIdent(self.players + self.spectators)

    self.nextTurn()
    return True


  def nextTurn(self):
    self.turnNumber += 1
    if (self.turn == self.players[0]):
      self.turn = self.players[1]
      self.playerID = 1
    else:
      self.turn = self.players[0]
      self.playerID = 0

    for obj in self.objects.values():
      obj.nextTurn()

    self.checkWinner()
    if self.winner is None:
      self.sendStatus([self.turn] +  self.spectators)
    else:
      self.sendStatus(self.spectators)
    self.animations = ["animations"]
    return True

  def checkWinner(self):
    if not [i for i in self.objects.values() if isinstance(i, Bot) and i.owner == 0]:
      self.declareWinner(self.players[1])
    elif not [i for i in self.objects.values() if isinstance(i, Bot) and i.owner == 1]:
      self.declareWinner(self.players[0])
    elif self.turnNumber >= 500:
      self.declareWinner(self.players[0])
    
    pass

  def declareWinner(self, winner):
    self.winner = winner
    self.turn = None

    msg = ["game-winner", self.id, self.winner.user, self.getPlayerIndex(self.winner)]
    self.scribe.writeSExpr(msg)
    self.scribe.finalize()
    self.removePlayer(self.scribe)

    for p in self.players + self.spectators:
      p.writeSExpr(msg)
    
  def logPath(self):
    return "logs/" + str(self.id) + ".gamelog"
  
  @derefArgs(Unit, None)
  @requireOwn
  def talk(self, object, talk_string):
    return object.talk(talk_string, )


  @derefArgs(Bot, None)
  @requireOwn
  def talk(self, object, talk_string):
    return object.talk(talk_string, )

  @derefArgs(Bot, None)
  @requireOwn
  def move(self, object, direction):
    return object.move(direction, )

  @derefArgs(Bot,Unit)
  @requireOwn
  def attack(self, object, target):
    return object.attack(target, )

  @derefArgs(Bot, Type, None, None, None)
  @requireOwn
  def build(self, object, type, x, y, size):
    return object.build(type, x, y, size, )

  @derefArgs(Bot, Bot, Bot, Bot)
  @requireOwn
  def combine(self, object, Bot2, Bot3, Bot4):
    return object.combine(Bot2, Bot3, Bot4, )

  @derefArgs(Bot)
  @requireOwn
  def split(self, object):
    return object.split()

  @derefArgs(Unit, None)
  @requireOwn
  def talk(self, object, talk_string):
    return object.talk(talk_string, )


  def sendIdent(self, players):
    if len(self.players) < 2:
      return False
    list = []
    for i in itertools.chain(self.players, self.spectators):
      list += [[self.getPlayerIndex(i), i.user, i.screenName, i.type]]
    for i in players:
      i.writeSExpr(['ident', list, self.id, self.getPlayerIndex(i)])

  def getPlayerIndex(self, player):
    try:
      playerIndex = self.players.index(player)
    except ValueError:
      playerIndex = -1
    return playerIndex

  def sendStatus(self, players):
    for i in players:
      i.writeSExpr(self.status())
      i.writeSExpr(self.animations)
    return True


  def status(self):
    msg = ["status"]

    msg.append(["game", self.turnNumber, self.playerID, self.boardX, self.boardY, self.gameNumber])

    typeLists = []
    typeLists.append(["Bot"] + [i.toList() for i in self.objects.values() if i.__class__ is Bot])
    typeLists.append(["Frame"] + [i.toList() for i in self.objects.values() if i.__class__ is Frame])
    if self.turnNumber < 2:
      typeLists.append(["Type"] + [i.toList() for i in self.objects.values() if i.__class__ is Type])

    msg.extend(typeLists)

    return msg


loadClassDefaults()

