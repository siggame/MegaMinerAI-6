from getpass import getpass

from ssh_session import ssh_session


def launch(host, username, passwvord, command):
  session = ssh_session(username, host, password, 1)
  
  session.ssh('nohup %s > /dev/null 2> /dev/null < /dev/null &' % command)
  

if __name__ == '__main__':
  import sys, traceback
  if len(sys.argv) > 1:
    command = sys.argv[1]
  else:
    command = "sh tentacle.sh"
  hosts = [i for i in open('serverList.txt', 'r').readlines()]
  username = raw_input('Username: ')
  password = getpass()
  
  
  for i in hosts:
    try:
      launch(i, username, password, command)
    except:
      traceback.print_exc()
