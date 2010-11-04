# -*- coding: utf-8 -*-
#New Game Visualizer Scheduler Update Function
#the game holders themselves are not deleted so that the queue can easily tell wether a game between these two with the same version numbers has already been played, as if one has it gets no bonus to its priority.
import heapq

# tentq is a priority heap with entries of the following type:
#   [priority, player1, player2]

# visq is a priority heap with entries of the following type:
#   [priority, player1, player2, gamelogNumber, played]

# each is of size n^2 where n is the number of teams.

# teamlist is a dict for current version numbers

tentq = []
visq = []
teamlist = {}

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
  
#New Version Game Scheduler Update Function  
def gameQueueUpdate(newAI):
  if team in teamlist:
    teamlist[team] += 1
    for game in tentq:
      if newAI in game:
        game[0] += 2*len(tentq)
  else:
    teamlist[newAI] = 0
    for team in teamlist:
      heapq.heappush(tentq,[2*len(tentq)+2*len(teamlist),newAI,team])
      heapq.heappush(tentq,[2*len(tentq)+2*len(teamlist),team,newAI])
    
#Removes a competitor
def removeCompetitor(removee):
  #Iterates through each of tentacle queue, visualizer queue, and team list.  Removes everything in which the team being removed participated.
  if removee in teamlist:
    del teamlist[removee]
  else :
    return
  for schedule in tentq:
    if removee in schedule
      tentq.remove(schedule)
  for game in visq:
    if removee in game:
      visq.remove(game)
  heapq.heapify(tentq)
  heapq.heapify(visq)

#grabs the next game to be run by a tentacle and makes the proper adjustments
def nextGame(tentq):
  nextUp = tentq[0]
  for schedule in tentq:
    if nextUp.priority < schedule.priority:
      nextUp = schedule
  nextUp.priority = 0
  for schedule in tentq:
    if nextUp.team1 != schedule.team1 and nextUp.team1 != schedule.team2:
      schedule.priority++
    if nextUp.team2 != schedule.team1 and nextUp.team2 != schedule.team2:
      schedule.priority++
  return nextUp
  
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
  
