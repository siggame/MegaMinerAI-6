# -*- coding: iso-8859-1 -*-
import random

words = [i.strip().lower() for i in file('english.txt').readlines()]

def makePassword():
  word = ""
  while len(word) < 8:
    word += random.choice(words) + str(random.randint(0, 9))
    if word[0] in 'aeiouy':
      word = ""
  word = word.replace('a', '6')
  word = word.replace('e', '3')
  word = word.replace('i', '1')
  word = word.replace('o', '0')
  word = word.replace('u', '4')
  word = word.replace('y', '9')
    
  return word[0].upper() + word[1:]


if __name__ == '__main__':
  input = file('teams.txt', 'r')
  output = file('passwords.txt', 'w')
  lines = [i.strip() for i in input.readlines()]
  for l in lines:
   if l is not lines[0]:
     output.write('\n')
   output.write(l + "\t" + makePassword())
   