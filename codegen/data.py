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
      arguments = [ Variable('talk_string', str),]
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
    Variable('actions', int),
    Variable('size', int),
    Variable('damage', int),
    Variable('range', int),
    Variable('movitude', int),
    Variable('actitude', int),
    Variable('buildRate', int),
    Variable('partOf', Bot),
    Variable('building', Frame),
  ])
    
Bot.addFunctions([
    Function('move',
      arguments = [Variable('direction', int),],
      result = bool
      ),
    Function('attack',
      arguments = [Variable('target', Unit),],
      result = bool
      ),
    Function('build',
      arguments = [Variable('type', type), Variable('x', int), Variable('y', int), Variable('size', int), ],
      result = bool
      ),
    Function('combine',
      arguments = [Variable('Bot2', Bot), Variable('Bot3', Bot), Variable('Bot4', Bot)],
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
  Function('moveRate',
    result = int
    ),
  ])

move = Animation("move",
  data = [Variable("robot", Bot),
    Variable("direction", int)]
  )
add = Animation("add",
  data = [Variable("robot", Unit)]
  )
remove = Animation("remove",
  data = [Variable("robot", Unit)]
  )



globals = [
  Variable('turnNumber', int),
  Variable('playerID', int, 'Player Number; either 0 or 1'),
  Variable('boardX', int),
  Variable('boardY', int),
  Variable('gameNumber', int)
  ]
