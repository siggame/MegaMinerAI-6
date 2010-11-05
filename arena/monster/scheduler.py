# -*- coding: iso-8859-1 -*-
#New Game Visualizer Scheduler Update Function
#the game holders themselves are not deleted so that the queue can easily tell wether a game between these two with the same version numbers has already been played, as if one has it gets no bonus to its priority.

# tentq is a priority heap with entries of the following type:
#   [priority, player1, player2]

# visq is a priority heap with entries of the following type:
#   [priority, player1, player2, gamelogNumber, played]

# each is of size n^2 - n where n is the number of teams.

# teamlist is a dict for current version numbers

class Match:
  def __init__(priority, p1, p2):
    self.priority = priority
    self.p1 = p1
    self.p2 = p2

class GameScheduler:
  tentq = []
  teamlist = {}
  
  def __init__(self):
    self.tentq = []
    self.teamlist = {}
    
  #New Version Game Scheduler Update Function  
  def updateQueue(newAI, version):
    self.teamlist[newAI] = version
    if team in self.teamlist:
      for m in self.tentq:
        if newAI in [m.p1, m.p2]:
          m.priority += 2*len(self.tentq)
          m.priority = min(m.priority, 5*len*self.tentq)
    else:
      for team in self.teamlist:
        self.tentq.append(Match(2*len(self.tentq)+2*len(self.teamlist), newAI, team))
        self.tentq.append(Match(2*len(self.tentq)+2*len(self.teamlist), team, newAI))
      self.teamlist[newAI] = version
    
    return True
      
  #Removes a competitor
  def removeCompetitor(removee):
    #Iterates through each of tentacle queue, visualizer queue, and team list.  Removes everything in which the team being removed participated.
    if removee in self.teamlist:
      del self.teamlist[removee]
    else:
      return False
    for s in self.tentq:
      if removee in [s.p1, s.p2]
        self.tentq.remove(schedule)
    for game in visq:
      if removee in game:
        visq.remove(game)
    return True

  #grabs the next game to be run by a tentacle and makes the proper adjustments
  def nextGame(self.tentq):
    self.tentq.sort(key = lambda x: x.priority, reverse=True)
    nextUp = self.tentq[0]
    nextUp.priority = 0
    for s in self.tentq[1:]:
      if nextUp.p1 not in [s.p1, s.p2]:
        s.priority += 1
      if nextUp.p2 not in [s.p1, s.p2]:
        s.priority += 1
    
    return nextUp

"""
def visualizerQueueUpdate(game,gamelog):
  for game in visq:
    found = False
    #finds the previous game between the same players in the same player numbers
    if newgame[1:3] == game[1:3]:
      found = True
      #updates the gamelog stored
      game[3] = gamelog
      #makes the game playable agian
      game[4] = False
      #Checks if its a new version
      if game.p1ver != newgame.p1ver or game.p2ver != newgame.p2ver:
	#if so, it updates the version and increases the priority (new games are more interesting than old games!)
	game.p1ver = newgame.p1ver
	game.p2ver = newgame.p2ver
	game.priority += 2*visq.len()
  #If the game holder between those players doesn't already exist, it creates it
  if !found:
    newgame.priority = 2*visq.len() + 2
    newgame.played = false
    visq.append(newgame)
  
#grabs the next thing to be visualized and makes proper adjustments
def nextVideo(visq):
  nextUp = visq[0]
  for game in visq:
    if nextUp.priority < game.priority:
      nextUp = game
  nextUp.priority = 0;
  for schedule in visq:
    if nextUp.player1 != game.player1 and nextUp.player1 != game.player2:
      game.priority++
    if nextUp.player2 != game.player1 and nextUp.team2 != game.player1:
      game.priority++
  return nextUp

#loop that checks for tentacles, gives them things to visualise, tentq contains priority, team1, team2, teams each contain teamName, version, AI.
def primaryScheduleLoop():
  tentq = {}
  visq = {}
  teamlist = {}
  while(running):
    #check for stop signal and stop if it says so
    #check for new AI
    #check for AI extraction requests
    #check for tentacles seeking work
    #check if the visualizer needs a log
  
  #once it finishes the loop, if it was told to run a tournament it runs a round robin tournament
  rrTournament(teamlist)


def rrTournament(teamlist):
  
"""