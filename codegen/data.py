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
      arguments = [ Variable('talk_string', string),]
      ),],
  doc = 'An object that exists on the grid',
  type = 'virtual'
  )

Bot = Model('Bot',
  parent = Unit,
  data = [],
  functions = [
    Function('move',
      arguments = [ Variable('direction', enum),]
      ),
  ],
  properties = [],
  doc = 'The bot class.'
  )
  
Builder = Model('Builder',
  parent = Bot,
  data = [],
  functions = [
    Function('build',
      arguments = [ Variable('type', enum), Variable('direction', enum),] ), ]
  properties = [Function('canBuild',
    result = bool
    ), ],
  doc = 'A robot that can build other bots. Build them all! Rule the world!'
  )


Tube = Model('Tube',
  parent = Unit,
  data = [ Variable('points', int, 'Points to grow a strong baby.'),
    ],
  functions = [ Function('hatch',
    arguments = [ Variable('damage', int),
      Variable('reach', int),
      Variable('speed', int),
      Variable('health', int),
      Variable('view', int) ]
    ) ],
  properties = [ Function('canHatch',
    arguments = [ Variable('damage', int),
      Variable('reach', int),
      Variable('speed', int),
      Variable('health', int),
      Variable('view', int) ],
    result = bool
    ) ],
  doc = 'A test tube full of baby.'
  )

ASM = Model('Superman',
  parent = Unit,
  data = [ Variable('damage', int),
    Variable('reach', int),
    Variable('speed', int),
    Variable('view', int),
    ],
  functions = [ Function('move',
      arguments = [ Variable('x', int),
        Variable('y', int) ]
      ), 
    Function ('attack',
      arguments = [ Variable('target', Unit) ] )
   ],
  doc = 'A test tube full of baby.'
  )

globals = [
  Variable('turnNumber', int),
  Variable('playerID', int, 'Player Number; either 0 or 1'),
  Variable('boardX', int),
  Variable('boardY', int),
  Variable('gameNumber', int)
  ]
