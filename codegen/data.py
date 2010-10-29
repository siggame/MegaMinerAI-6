# -*- coding: iso-8859-1 -*-
from structures import *

Mappable = Model('Mappable', 
  data = [ Variable('x', int),
    Variable('y', int),
    ],
  doc = 'An object that exists on the grid',
  type = 'virtual'
  )

Unit = Model('Unit', 
  parent = Mappable,
  data = [ Variable('owner', int, 'The owning player'),
    Variable('health', int),
    Variable('maxHealth', int),
    ],
  functions = [
    Function('talk',
      arguments = [ Variable('message', str),]
      ),],
  doc = 'An object that exists on the grid',
  type = 'virtual'
  )

type = Model('Type',
  data = [Variable('name', str),
    Variable('maxHealth', int),
    Variable('damage', int),
    Variable('range', int),
    Variable('movitude', int),
    Variable('actitude', int),
    Variable('buildRate', int),
    ],
  doc = 'A kind of robot.'
  )

Wall = Model('Wall',
  parent = Unit,
  doc = 'A pile of hard stuff that is in the way.')

Frame = Model('Frame',
  parent = Unit,
  data = [Variable('type', type),
    Variable('size', int),
    Variable('completionTime', int)],
  doc = 'A baby robot.')


#Split up the Bot class because of self-referential variables

Bot = Model('Bot',
  parent = Unit,
  doc = 'The bot class.')

Bot.addData([
    Variable('actions', int, 'How many actions this bot can still perform'),
    Variable('steps', int, 'How many steps this bot can still take'),
    Variable('size', int, 'The width of this bot, such that size^2 = number of bots combined into this bot'),
    Variable('damage', int, 'The amount of damage this robot does when attacking'),
    Variable('range', int, 'How far this robot can attack from its edge'),
    Variable('movitude', int),
    Variable('actitude', int),
    Variable('buildRate', int, 'How many turns it would take to build a robot one size smaller than this robot'),
    Variable('partOf', int, 'ID of the robot this robot is apart of, 0 if not in a robot'),
    Variable('building', int, 'ID of the robot this robot is building, 0 if not building'),
  ])
    
Bot.addFunctions([
    Function('move',
      arguments = [Variable('direction', str),],
      result = bool,
      ),
    Function('attack',
      arguments = [Variable('target', Unit),],
      result = bool
      ),
    Function('heal',
      arguments = [Variable('target', Bot),],
      result = bool
      ),
    Function('build',
      arguments = [Variable('type', type), Variable('x', int), Variable('y', int), Variable('size', int), ],
      result = bool
      ),
    Function('combine',
      arguments = [Variable('bot2', Bot), Variable('bot3', Bot), Variable('bot4', Bot)],
      result = bool
    ),
    Function('split',
      arguments = [],
      result = bool
    ),
  ])


Bot.addProperties([
  Function('maxActions',
    result = int
    ),
  Function('maxSteps',
    result = int
    ),
  ])

move = Animation("Move",
  data = [Variable("robot", Bot),
    Variable("direction", int)]
  )
add = Animation("Add",
  data = [Variable("robot", Unit)]
  )
remove = Animation("Remove",
  data = [Variable("robot", Unit)]
  )
talk = Animation("Talk",
  data = [Variable("speaker", Unit), Variable("message", str)]
  )
split = Animation("Split",
  data = [Variable("robot", Bot)]
  )
combine = Animation("Combine",
  data = [Variable("bot1", Bot), Variable("bot2", Bot), Variable("bot3", Bot), Variable("bot4", Bot)]
  )
attack = Animation("Attack",
  data = [Variable("attacker", Bot), Variable("victim", Unit)]
  )
heal = Animation("Heal",
  data = [Variable("healer", Bot), Variable("victim", Unit)]
  )
build = Animation("Build",
  data = [Variable("builder", Bot), Variable("frame", Frame)]
  )
attack = Animation("Collide",
  data = [Variable("attacker", Bot), Variable("victim", Unit)]
  )





globals = [
  Variable('turnNumber', int, 'How many turns it has been since the beginning of the game'),
  Variable('playerID', int, 'Player Number; either 0 or 1'),
  Variable('boardX', int, 'Maximum valid position in the X (right) direction.  (0,0) is top left'),
  Variable('boardY', int, 'Maximum valid position in the Y (down) direction.  (0,0) is top left'),
  Variable('gameNumber', int, 'What number game this is for the server')
  ]
