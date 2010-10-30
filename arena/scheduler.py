# -*- coding: utf-8 -*-
#New Game Visualizer Scheduler Update Function
#the game holders themselves are not deleted so that the queue can easily tell wether a game between these two with the same version numbers has already been played, as if one has it gets no bonus to its priority.
def visualizerQueueUpdate(newgame,visq):
  found = False
  for game in visq:
    #finds the previous game between the same players in the same player numbers
    if newgame.player1 == game.player1 and newgame.player2 == game.player2:
      found = True
      #updates the gamelog stored
      game.gamelog = newgame.gamelog
      #makes the game playable agian
      game.played = false
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
def gameQueueUpdate(newAI,tentq,teamlist):
  found = False
  #updates the teamlist with the new ai and new version information
  for team in teamlist:
    if newAI.teamName == team.teamName:
      found = True
      newAI.ver = team.ver + 1
      team = newAI
  for schedule in tentq:
    #finds all previously scheduled games and updates them for new version
    if newAI.teamName == schedule.team1.teamName:
      schedule.team1 = newAI
      schedule.priority += 2 * tentq.len()
    elif newAI.teamName == schedule.team2.teamName:
      schedule.team2 = newAI
      schedule.priority += 2 * tentq.len()
  #if it is the very first submission it sets up matches and stores the team in the teamlist
  if !found:
    newAI.ver = 1
    for team in teamlist:
      tentq.append(gamify(newAI,team,2*tentq.len()+2*teamlist.len()))
      tentq.append(gamify(team,newAI,2*tentq.len()+2*teamlist.len()))
    teamlist.append(newAI)
    
#Little function that makes a temp variable because I don't know how to do that >_>    
def gamify(t1,t2,pri):
  schedule.team1 = t1
  schedule.team2 = t2
  schedule.priority = pri
  return schedule
  
#Removes a competitor
def removeCompetitor(tentq,teamlist,visq,removee):
  #Iterates through each of tentacle queue, visualizer queue, and team list.  Removes everything in which the team being removed participated.
  for team in teamlist:
    if team.name == removee:
      teamlist.remove(team)
  for schedule in tentq:
    if schedule.team1.teamName == removee:
      tentq.remove(schedule)
    if schedule.team2.teamName == removee:
      tentq.remove(schedule)
  for game in visq:
    if game.player1 == removee:
      visq.remove(game)
    if game.player2 == removee:
      visq.remove(game)
      
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
  