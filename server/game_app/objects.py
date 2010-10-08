class Mappable:
  def __init__(self, game, id, x, y):
    self.game = game
    self.id = id
    self.x = x
    self.y = y

  def toList(self):
    value = [
      id,
      x,
      y,
      ]
    return value



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
      id,
      x,
      y,
      owner,
      health,
      maxHealth,
      ]
    return value

  def talk(self, talk_string):
    pass



class Bot(Unit):
  def __init__(self, game, id, x, y, owner, health, maxHealth, actions, size, damage, range, movitude, actitude, buildRate, partOf, building):
    self.game = game
    self.id = id
    self.x = x
    self.y = y
    self.owner = owner
    self.health = health
    self.maxHealth = maxHealth
    self.actions = actions
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
      id,
      x,
      y,
      owner,
      health,
      maxHealth,
      actions,
      size,
      damage,
      range,
      movitude,
      actitude,
      buildRate,
      partOf,
      building,
      ]
    return value

  def talk(self, talk_string):
    pass

  def move(self, direction):
    pass

  def attack(self, target):
    pass

  def build(self, type, x, y, size):
    pass

  def combine(self, Bot2, Bot3, Bot4):
    pass

  def split(self):
    pass


  def maxActions(self):
    pass

  def moveRate(self):
    pass


class Frame(Unit):
  def __init__(self, game, id, x, y, owner, health, maxHealth, type, size):
    self.game = game
    self.id = id
    self.x = x
    self.y = y
    self.owner = owner
    self.health = health
    self.maxHealth = maxHealth
    self.type = type
    self.size = size

  def toList(self):
    value = [
      id,
      x,
      y,
      owner,
      health,
      maxHealth,
      type,
      size,
      ]
    return value

  def talk(self, talk_string):
    pass



class Type:
  def __init__(self, game, id, name, maxHealth, damage, range, moveRate, maxActions, buildRate):
    self.game = game
    self.id = id
    self.name = name
    self.maxHealth = maxHealth
    self.damage = damage
    self.range = range
    self.moveRate = moveRate
    self.maxActions = maxActions
    self.buildRate = buildRate

  def toList(self):
    value = [
      id,
      name,
      maxHealth,
      damage,
      range,
      moveRate,
      maxActions,
      buildRate,
      ]
    return value



