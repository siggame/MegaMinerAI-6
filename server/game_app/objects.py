class Mappable:
  def __init__(self, game, id, x, y):
    self.game = game
    self.id = id
    self.x = x
    self.y = y

  def toList(self):
    value = [
      self.id,
      self.x,
      self.y,
      ]
    return value

  def nextTurn(self):
    pass



class Unit(Mappable):
  def __init__(self, game, id, x, y, owner, health, maxHealth):
    self.game = game
    self.id = id
    self.x = x
    self.y = y
    self.owner = owner
    self.health = health
    self.maxHealth = maxHealth

  def toList(self):
    value = [
      self.id,
      self.x,
      self.y,
      self.owner,
      self.health,
      self.maxHealth,
      ]
    return value

  def nextTurn(self):
    pass

  def talk(self, talk_string):
    pass



class Bot(Unit):
  def __init__(self, game, id, x, y, owner, health, maxHealth, actions, steps, size, damage, range, movitude, actitude, buildRate, partOf, building):
    self.game = game
    self.id = id
    self.x = x
    self.y = y
    self.owner = owner
    self.health = health
    self.maxHealth = maxHealth
    self.actions = actions
    self.steps = steps
    self.size = size
    self.damage = damage
    self.range = range
    self.movitude = movitude
    self.actitude = actitude
    self.buildRate = buildRate
    self.partOf = partOf
    self.building = building

  def toList(self):
    value = [
      self.id,
      self.x,
      self.y,
      self.owner,
      self.health,
      self.maxHealth,
      self.actions,
      self.steps,
      self.size,
      self.damage,
      self.range,
      self.movitude,
      self.actitude,
      self.buildRate,
      self.partOf,
      self.building,
      ]
    return value

  @staticmethod
  def fromType(game, x, y, owner, type):
    id = game.nextid
    game.nextid += 1
    return Bot(game, id, x, y, owner, type.maxHealth,  type.maxHealth, 0, 0, 1, type.damage, type.range, type.movitude, type.actitude,
      type.buildRate, -1, -1)

  def _combine(self, bot2, bot3, bot4):
    bots = [self, bot2, bot3, bot4]
    id = self.game.nextid
    self.game.nextid += 1
    #I am so sorry.
    #This calls the Bot constructor, taking the min or sum of the mini bot values as appropriate
    newBot = Bot(game, id, min([i.x for i in bots], min([i.y for y in bots]), self.owner, sum([i.health for i in bots]),
      sum([i.maxHealth for i in bots]), 0, 0, self.size * 2, sum([i.damage for i in bots]), sum([i.range for i in bots]),
      sum([i.movitude for i in bots]), sum([i.actitude for i in bots]), sum([i.buildRate for i in bots]), -1, -1))
    self.game.addObject(newBot)
    for i in bots:
      i.partOf = id
    return newBot

  @staticmethod
  def makeBot(game, x, y, owner, type, size):
    if size == 1:
      bot = Bot.fromType(game, x, y, owner, type)
      addObject(bot)
      return bot
    bot1 = makeBot(game, x, y, owner, type, size/2)
    bot2 = makeBot(game, x+size/2, y, owner, type, size/2)
    bot3 = makeBot(game, x, y+size/2, owner, type, size/2)
    bot4 = makeBot(game, x+size/2, y+size/2, owner, type, size/2)
    bot1._combine(bot2, bot3, bot4)

  def nextTurn(self):
    self.actions = 0
    self.steps = 0
    if self.game.playerID != self.owner:
      return True
    if self.partOf != -1:
      return True
    if self.building == -1:
      self.actions = self.actitude / self.size**2
      self.steps = self.movitude / self.size**2
      return True
    else:
      baby =  self.game.objects[self.building]
      baby.completionTime -= 1
      if baby.completionTime < 1:
        type = self.game.objects[baby.type]
        newBot = Bot.makeBot(self.game, baby.x, baby.y, self.owner, type, baby.size)
        game.removeObject(baby)
        self.building = -1
        self.newTurn()
        newBot.newTurn()
        return True
      else:
        return True


  def talk(self, message):
    self.game.animations.append(['talk', self.id, message])

  def move(self, direction):
    pass

  def attack(self, target):
    pass

  def heal(self, target):
    pass

  def build(self, type, x, y, size):
    pass

  def combine(self, bot2, bot3, bot4):
    bots = [self, bot2, bot3, bot4]
    if min([i.actions for i in bots]) < 1:
      return "Not every bot has actions."
    if not self.size == bot2.size == bot3.size == bot4.size:
      return "Not every bot is the same size."
    x = min([i.x for i in bots])
    y = min([i.y for i in bots])
    s = self.size
    pos = [(i.x, i.y) for i in bots]
    if (not (x, y) in pos) or (not (x+s, y) in pos) or (not (x, y+s) in pos) or (not (x+s, y+s) in pos):
      return "Bots not in a square."
    self._combine(bot2, bot3, bot4)
    return True

  def split(self):
    if self.actions < 1:
      return "No actions left."
    if self.size < 2:
      return "Not compound."
    for i in self.game.objects:
      if isinstance(i, Bot):
        if i.partOf == self.id:
          i.partOf = -1
    self.game.animations.append('split', self.id)
    self.game.remove(self)

    return True


  def maxActions(self):
    pass

  def moveRate(self):
    pass


class Frame(Unit):
  def __init__(self, game, id, x, y, owner, health, maxHealth, type, size, completionTime):
    self.game = game
    self.id = id
    self.x = x
    self.y = y
    self.owner = owner
    self.health = health
    self.maxHealth = maxHealth
    self.type = type
    self.size = size
    self.completionTime = completionTime

  def toList(self):
    value = [
      self.id,
      self.x,
      self.y,
      self.owner,
      self.health,
      self.maxHealth,
      self.type,
      self.size,
      self.completionTime,
      ]
    return value

  def nextTurn(self):
    pass

  def talk(self, talk_string):
    pass



class Type:
  def __init__(self, game, id, name, maxHealth, damage, range, movitude, actitude, buildRate):
    self.game = game
    self.id = id
    self.name = name
    self.maxHealth = maxHealth
    self.damage = damage
    self.range = range
    self.movitude = movitude
    self.actitude = actitude
    self.buildRate = buildRate

  def toList(self):
    value = [
      self.id,
      self.name,
      self.maxHealth,
      self.damage,
      self.range,
      self.movitude,
      self.actitude,
      self.buildRate,
      ]
    return value

  def nextTurn(self):
    pass



