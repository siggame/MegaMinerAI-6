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
    ],
  functions = [
    Function('talk',
      arguments = [ Variable('talk_string', str),]
      ),],
  doc = 'An object that exists on the grid',
  type = 'virtual'
  )

Bot = Model('Bot',
  parent = Unit,
  data = [
  Variable('attack', int),
  Variable('range', int),
  Variable('speed', int),
  Variable('buildRate', int),
  ],
  functions = [
    Function('move',
      arguments = [Variable('direction', int),],
      result = bool
      ),
    Function('attack',
      arguments = [Variable('direction', int),],
      result = bool
      ),
    Function('build',
      arguments = [Variable('type', int), Variable('direction', int),],
      result = bool
      ),
    Function('combine',
      arguments = [], #What would go here?
      result = bool
    ),
    Function('split',
      arguments = [],
      result = bool
    ),
  ],
  properties = [
    Function(Variable('buildRate', int),
    result = int
    ),
    Function(Variable('attackRate', int),
    result = int
    ),
    Function(Variable('range', int),
    result = int
    ),
    Function(Variable('speed', int),
    result = int
    ),
    Function(Variable('size', int),
    result = int
    ),
    Function(Variable('locX', int),
    result = int
    ),
    Function(Variable('locY', int),
    result = int
    ),
    Function(Variable('madeOf', int),
    result = int #What goes here?
    ),
    Function(Variable('partOf', int),
    result = int #What goes here?
    ),
  ],
  doc = 'The bot class.'
  )

globals = [
  Variable('turnNumber', int),
  Variable('playerID', int, 'Player Number; either 0 or 1'),
  Variable('boardX', int),
  Variable('boardY', int),
  Variable('gameNumber', int)
  ]
