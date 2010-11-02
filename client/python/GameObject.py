# -*- python -*-

from library import library

from ExistentialError import ExistentialError

class GameObject(object):
  def __init__(self, ptr):
    from BaseAI import BaseAI
    self.ptr = ptr
    self.iteration = BaseAI.iteration


class Mappable(GameObject):
  def __init__(self, ptr):
    from BaseAI import BaseAI
    self.ptr = ptr
    self.iteration = BaseAI.iteration
    
    self.id = library.mappableGetId(ptr)

  def getId(self):
    self.validify()
    return library.mappableGetId(self.ptr)

  def getX(self):
    self.validify()
    return library.mappableGetX(self.ptr)

  def getY(self):
    self.validify()
    return library.mappableGetY(self.ptr)


  def __str__(self):
    self.validify()
    ret = ""
    ret += "id: %s\n" % self.getId()
    ret += "x: %s\n" % self.getX()
    ret += "y: %s\n" % self.getY()
    return ret

class Unit(Mappable):
  def __init__(self, ptr):
    from BaseAI import BaseAI
    self.ptr = ptr
    self.iteration = BaseAI.iteration
    
    self.id = library.unitGetId(ptr)

  def talk(self, message):
    self.validify()
    return library.unitTalk(self.ptr, message)

  def getId(self):
    self.validify()
    return library.unitGetId(self.ptr)

  def getX(self):
    self.validify()
    return library.unitGetX(self.ptr)

  def getY(self):
    self.validify()
    return library.unitGetY(self.ptr)

  def getOwner(self):
    self.validify()
    return library.unitGetOwner(self.ptr)

  def getHealth(self):
    self.validify()
    return library.unitGetHealth(self.ptr)

  def getMaxHealth(self):
    self.validify()
    return library.unitGetMaxHealth(self.ptr)

  def getSize(self):
    self.validify()
    return library.unitGetSize(self.ptr)


  def __str__(self):
    self.validify()
    ret = ""
    ret += "id: %s\n" % self.getId()
    ret += "x: %s\n" % self.getX()
    ret += "y: %s\n" % self.getY()
    ret += "owner: %s\n" % self.getOwner()
    ret += "health: %s\n" % self.getHealth()
    ret += "maxHealth: %s\n" % self.getMaxHealth()
    ret += "size: %s\n" % self.getSize()
    return ret

class Bot(Unit):
  def __init__(self, ptr):
    from BaseAI import BaseAI
    self.ptr = ptr
    self.iteration = BaseAI.iteration
    
    self.id = library.botGetId(ptr)

  def validify(self):
    from BaseAI import BaseAI
    #if this class is pointing to an object from before the current turn it's probably
    #somewhere else in memory now
    if self.iteration == BaseAI.iteration:
      return True
    for i in BaseAI.bots:
      if i.id == self.id:
        self.ptr = i.ptr
        self.iteration = BaseAI.iteration
        return True
    raise ExistentialError()
  def talk(self, message):
    self.validify()
    return library.botTalk(self.ptr, message)

  def move(self, direction):
    self.validify()
    return library.botMove(self.ptr, direction)

  def attack(self, target):
    self.validify()
    if target.__class__ not in [Unit]:
      raise TypeError('target should be of [Unit]')
    target.validify()
    return library.botAttack(self.ptr, target.ptr)

  def heal(self, target):
    self.validify()
    if target.__class__ not in [Bot]:
      raise TypeError('target should be of [Bot]')
    target.validify()
    return library.botHeal(self.ptr, target.ptr)

  def build(self, type, x, y, size):
    self.validify()
    if type.__class__ not in [Type]:
      raise TypeError('type should be of [Type]')
    type.validify()
    return library.botBuild(self.ptr, type.ptr, x, y, size)

  def combine(self, bot2, bot3, bot4):
    self.validify()
    if bot2.__class__ not in [Bot]:
      raise TypeError('bot2 should be of [Bot]')
    bot2.validify()
    if bot3.__class__ not in [Bot]:
      raise TypeError('bot3 should be of [Bot]')
    bot3.validify()
    if bot4.__class__ not in [Bot]:
      raise TypeError('bot4 should be of [Bot]')
    bot4.validify()
    return library.botCombine(self.ptr, bot2.ptr, bot3.ptr, bot4.ptr)

  def split(self):
    self.validify()
    return library.botSplit(self.ptr)

  def maxActions(self):
    self.validify()
    return library.botMaxActions(self.ptr)

  def maxSteps(self):
    self.validify()
    return library.botMaxSteps(self.ptr)

  def getId(self):
    self.validify()
    return library.botGetId(self.ptr)

  def getX(self):
    self.validify()
    return library.botGetX(self.ptr)

  def getY(self):
    self.validify()
    return library.botGetY(self.ptr)

  def getOwner(self):
    self.validify()
    return library.botGetOwner(self.ptr)

  def getHealth(self):
    self.validify()
    return library.botGetHealth(self.ptr)

  def getMaxHealth(self):
    self.validify()
    return library.botGetMaxHealth(self.ptr)

  def getSize(self):
    self.validify()
    return library.botGetSize(self.ptr)

  def getActions(self):
    self.validify()
    return library.botGetActions(self.ptr)

  def getSteps(self):
    self.validify()
    return library.botGetSteps(self.ptr)

  def getDamage(self):
    self.validify()
    return library.botGetDamage(self.ptr)

  def getRange(self):
    self.validify()
    return library.botGetRange(self.ptr)

  def getMovitude(self):
    self.validify()
    return library.botGetMovitude(self.ptr)

  def getActitude(self):
    self.validify()
    return library.botGetActitude(self.ptr)

  def getBuildRate(self):
    self.validify()
    return library.botGetBuildRate(self.ptr)

  def getPartOf(self):
    self.validify()
    return library.botGetPartOf(self.ptr)

  def getBuilding(self):
    self.validify()
    return library.botGetBuilding(self.ptr)

  def getType(self):
    self.validify()
    return library.botGetType(self.ptr)


  def __str__(self):
    self.validify()
    ret = ""
    ret += "id: %s\n" % self.getId()
    ret += "x: %s\n" % self.getX()
    ret += "y: %s\n" % self.getY()
    ret += "owner: %s\n" % self.getOwner()
    ret += "health: %s\n" % self.getHealth()
    ret += "maxHealth: %s\n" % self.getMaxHealth()
    ret += "size: %s\n" % self.getSize()
    ret += "actions: %s\n" % self.getActions()
    ret += "steps: %s\n" % self.getSteps()
    ret += "damage: %s\n" % self.getDamage()
    ret += "range: %s\n" % self.getRange()
    ret += "movitude: %s\n" % self.getMovitude()
    ret += "actitude: %s\n" % self.getActitude()
    ret += "buildRate: %s\n" % self.getBuildRate()
    ret += "partOf: %s\n" % self.getPartOf()
    ret += "building: %s\n" % self.getBuilding()
    ret += "type: %s\n" % self.getType()
    return ret

class Frame(Unit):
  def __init__(self, ptr):
    from BaseAI import BaseAI
    self.ptr = ptr
    self.iteration = BaseAI.iteration
    
    self.id = library.frameGetId(ptr)

  def validify(self):
    from BaseAI import BaseAI
    #if this class is pointing to an object from before the current turn it's probably
    #somewhere else in memory now
    if self.iteration == BaseAI.iteration:
      return True
    for i in BaseAI.frames:
      if i.id == self.id:
        self.ptr = i.ptr
        self.iteration = BaseAI.iteration
        return True
    raise ExistentialError()
  def talk(self, message):
    self.validify()
    return library.frameTalk(self.ptr, message)

  def getId(self):
    self.validify()
    return library.frameGetId(self.ptr)

  def getX(self):
    self.validify()
    return library.frameGetX(self.ptr)

  def getY(self):
    self.validify()
    return library.frameGetY(self.ptr)

  def getOwner(self):
    self.validify()
    return library.frameGetOwner(self.ptr)

  def getHealth(self):
    self.validify()
    return library.frameGetHealth(self.ptr)

  def getMaxHealth(self):
    self.validify()
    return library.frameGetMaxHealth(self.ptr)

  def getSize(self):
    self.validify()
    return library.frameGetSize(self.ptr)

  def getType(self):
    self.validify()
    return library.frameGetType(self.ptr)

  def getCompletionTime(self):
    self.validify()
    return library.frameGetCompletionTime(self.ptr)


  def __str__(self):
    self.validify()
    ret = ""
    ret += "id: %s\n" % self.getId()
    ret += "x: %s\n" % self.getX()
    ret += "y: %s\n" % self.getY()
    ret += "owner: %s\n" % self.getOwner()
    ret += "health: %s\n" % self.getHealth()
    ret += "maxHealth: %s\n" % self.getMaxHealth()
    ret += "size: %s\n" % self.getSize()
    ret += "type: %s\n" % self.getType()
    ret += "completionTime: %s\n" % self.getCompletionTime()
    return ret

class Wall(Unit):
  def __init__(self, ptr):
    from BaseAI import BaseAI
    self.ptr = ptr
    self.iteration = BaseAI.iteration
    
    self.id = library.wallGetId(ptr)

  def validify(self):
    from BaseAI import BaseAI
    #if this class is pointing to an object from before the current turn it's probably
    #somewhere else in memory now
    if self.iteration == BaseAI.iteration:
      return True
    for i in BaseAI.walls:
      if i.id == self.id:
        self.ptr = i.ptr
        self.iteration = BaseAI.iteration
        return True
    raise ExistentialError()
  def talk(self, message):
    self.validify()
    return library.wallTalk(self.ptr, message)

  def getId(self):
    self.validify()
    return library.wallGetId(self.ptr)

  def getX(self):
    self.validify()
    return library.wallGetX(self.ptr)

  def getY(self):
    self.validify()
    return library.wallGetY(self.ptr)

  def getOwner(self):
    self.validify()
    return library.wallGetOwner(self.ptr)

  def getHealth(self):
    self.validify()
    return library.wallGetHealth(self.ptr)

  def getMaxHealth(self):
    self.validify()
    return library.wallGetMaxHealth(self.ptr)

  def getSize(self):
    self.validify()
    return library.wallGetSize(self.ptr)


  def __str__(self):
    self.validify()
    ret = ""
    ret += "id: %s\n" % self.getId()
    ret += "x: %s\n" % self.getX()
    ret += "y: %s\n" % self.getY()
    ret += "owner: %s\n" % self.getOwner()
    ret += "health: %s\n" % self.getHealth()
    ret += "maxHealth: %s\n" % self.getMaxHealth()
    ret += "size: %s\n" % self.getSize()
    return ret

class Type(GameObject):
  def __init__(self, ptr):
    from BaseAI import BaseAI
    self.ptr = ptr
    self.iteration = BaseAI.iteration
    
    self.id = library.typeGetId(ptr)

  def validify(self):
    from BaseAI import BaseAI
    #if this class is pointing to an object from before the current turn it's probably
    #somewhere else in memory now
    if self.iteration == BaseAI.iteration:
      return True
    for i in BaseAI.types:
      if i.id == self.id:
        self.ptr = i.ptr
        self.iteration = BaseAI.iteration
        return True
    raise ExistentialError()
  def getId(self):
    self.validify()
    return library.typeGetId(self.ptr)

  def getName(self):
    self.validify()
    return library.typeGetName(self.ptr)

  def getMaxHealth(self):
    self.validify()
    return library.typeGetMaxHealth(self.ptr)

  def getDamage(self):
    self.validify()
    return library.typeGetDamage(self.ptr)

  def getRange(self):
    self.validify()
    return library.typeGetRange(self.ptr)

  def getMovitude(self):
    self.validify()
    return library.typeGetMovitude(self.ptr)

  def getActitude(self):
    self.validify()
    return library.typeGetActitude(self.ptr)

  def getBuildRate(self):
    self.validify()
    return library.typeGetBuildRate(self.ptr)


  def __str__(self):
    self.validify()
    ret = ""
    ret += "id: %s\n" % self.getId()
    ret += "name: %s\n" % self.getName()
    ret += "maxHealth: %s\n" % self.getMaxHealth()
    ret += "damage: %s\n" % self.getDamage()
    ret += "range: %s\n" % self.getRange()
    ret += "movitude: %s\n" % self.getMovitude()
    ret += "actitude: %s\n" % self.getActitude()
    ret += "buildRate: %s\n" % self.getBuildRate()
    return ret
