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

  def talk(self, message):
    self.game.animations.append(['talk', self.id, message])
    return True

  def _takeDamage(self, damage):
    self.health -= damage
    if self.health < 1:
      self.game.removeObject(self)



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

  def _takeDamage(self, damage):
    Unit._takeDamage(self, damage)
    if self.health > self.maxHealth:
      self.health = self.maxHealth

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

  def _distance(self, target):
    if isinstance(target, Bot) or isinstance(target, Frame):
      x = 0
      y = 0
      if self.x > target.x + target.size:
        x = self.x - (target.x + target.size-1)
      elif target.x > self.x + self.size-1:
        x = target.x - (self.x + self.size-1)
      if self.y > target.y + target.size-1:
        x = self.y - (target.y + target.size-1)
      elif target.y > self.y + self.size-1:
        x = target.y - (self.y + self.size-1)
      return x + y
    else:
      x = y = 0
      if target.x < self.x:
        x = self.x - target.x
      if target.x > (self.x + self.size-1):
        x = target.x - (self.x + self.size-1)
      if target.y < self.y:
        x = self.y - target.y
      if target.y > (self.y + self.size-1):
        x = target.y - (self.y + self.size-1)
      return x + y

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
    return bot1._combine(bot2, bot3, bot4)

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
    return Unit.talk(message)

  def move(self, direction):
    d = direction[0]
    if d.lower() not in 'udlr':
      return "%s is not a direction." % d
    if self.steps < 1:
      return "Out of steps."
    x = y = 0
    if d == 'u':
      x = -1
    elif d == 'd':
      x = 1
    elif d == 'l':
      y = 1
    elif d == 'r':
      y = -1
    victims = []
    for i in self.game.objects:
      if isinstance(i, Bot) or isinstance(i, Frame):
        if self._distance(i) == 1:
          victims.append(i)
    if x == -1:
      victims = [i for i in victims if i.x+i.size == self.x - 2]
    elif y == -1:
      victims = [i for i in victims if i.y+i.size == self.y - 2]
    elif x == 1:
      victims = [i for i in victims if i.x == self.x + self.size]
    elif y == 1:
      victims = [i for i in victims if i.y == self.y + self.size]

    if victims:
      victimHealth = sum([i.health for i in victims])
      for i in victims:
        damage = (i.health * self.size**2 + victimHealth - 1) / victimHealth
        victim._takeDamage(damage)
      damage = min(sum([i.health for i in victims]), self.size**2)
      self._damage(damage)
      victims = [i for i in victims if i.health > 0]
    
    if not victims:
      self.x += x
      self.y += y
    
    return True

  def attack(self, target):
    if self._distance(target) > (self.range + 1):
      return "Target out of range."

    if self.actions < 1:
      return "Out of actions."
    self.actions -= 1

    self.game.animations.append(['attack', self.id, target.id])
    target._takeDamage(self.damage)

    return True

  def heal(self, target):
    if self._distance(target) > (self.range + 1):
      return "Target out of range."

    if self.actions < 1:
      return "Out of actions."
    self.actions -= 1

    self.game.animations.append(['heal', self.id, target.id])
    target._takeDamage(-target.maxHealth * self.builditude / (2 * target.size**2))

    return True

  def build(self, type, x, y, size):
    if self.actions < 1:
      return "Out of actions"
    completionTime = self.builditude / (4 * size**2)
    health = min(type.maxHealth * buildRate / 4, type.maxHealth * size**2)
    f = Frame(self.game, 0, x, y, self,owner, health, type.maxHealth * size**2, completionTime)
    for i in self.game.objects:
      if isinstance(i, Unit):
        if f._distance(i) == 0:
          return "Overlap."
    f.id = self.game.nextid
    self.game.nextid += 1
    self.game.addObject(f)
    self.actions = 0
    self.building = f.id

    return True

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

  def _distance(self, target):
    if isinstance(target, Bot) or isinstance(target, Frame):
      x = 0
      y = 0
      if self.x > target.x + target.size-1:
        x = self.x - (target.x + target.size-1)
      elif target.x > self.x + self.size-1:
        x = target.x - (self.x + self.size-1)
      if self.y > target.y + target.size-1:
        x = self.y - (target.y + target.size-1)
      elif target.y > self.y + self.size-1:
        x = target.y - (self.y + self.size-1)
      return x + y
    else:
      x = y = 0
      if target.x < self.x:
        x = self.x - target.x
      if target.x > (self.x + self.size-1):
        x = target.x - (self.x + self.size-1)
      if target.y < self.y:
        x = self.y - target.y
      if target.y > (self.y + self.size-1):
        x = target.y - (self.y + self.size-1)


  def nextTurn(self):
    pass

  def talk(self):
    return Unit.talk(message)



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



