import aspects

import main
from game_app.match import Match


def install():
  def wrapNextTurn(self):
    if self.turn == self.players[0]:
      self.player1Time += self.timeInc
      print "player1Time = ", self.player1Time
    elif self.turn == self.players[1]:
      self.player0Time += self.timeInc
      print "player0Time = ", self.player0Time
    retval = yield aspects.proceed

  #aspects.with_wrap(wrapNextTurn, Match.nextTurn)

  def tick():
    for i in main.GameApp.games.values():
      if i.turn == i.players[0]:
        i.player0Time -= 1
      elif i.turn == i.players[1]:
        i.player1Time -= 1
        
