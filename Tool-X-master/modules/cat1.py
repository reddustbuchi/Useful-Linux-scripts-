#Tool Name :- Tool-X v2.0 
# Author :- Rajkumar Dusad
# Date :- 1/11/2017
# Aex Software's :- Tool-X is a automatic tool installer. Specially made for termux and GNURoot Debian terminal.

import os
import sys
from time import sleep
from core.system import *
from logo import *

def inst():
	os.system("cd .tools && python2 .inst.aex")

def inst1():
	os.system("cd .tools && python2 .inst1.aex")

def cat1():
	os.system("clear")
	cat1_logo()

	Toolo = raw_input("\n\033[1;33m >>>  \033[1;m")
	if Toolo == "1":
		usr=open(".tools/uip.aex","w")
		usr.write("33")
		usr.close()
		inst1()
	elif Toolo == "2":
		usr=open(".tools/uip.aex","w")
		usr.write("43")
		usr.close()
		inst()
	elif Toolo == "3":
		usr=open(".tools/uip.aex","w")
		usr.write("68")
		usr.close()
		inst()
	elif Toolo == "4":
		usr=open(".tools/uip.aex","w")
		usr.write("48")
		usr.close()
		inst()
	elif Toolo == "5":
		usr=open(".tools/uip.aex","w")
		usr.write("22")
		usr.close()
		inst()
	elif Toolo == "6":
		usr=open(".tools/uip.aex","w")
		usr.write("42")
		usr.close()
		inst()
	elif Toolo == "7":
		usr=open(".tools/uip.aex","w")
		usr.write("138")
		usr.close()
		inst()
	elif Toolo == "8":
		usr=open(".tools/uip.aex","w")
		usr.write("77")
		usr.close()
		inst()
	elif Toolo == "9":
		usr=open(".tools/uip.aex","w")
		usr.write("132")
		usr.close()
		inst()
	elif Toolo == "10":
		usr=open(".tools/uip.aex","w")
		usr.write("133")
		usr.close()
		inst()
	elif Toolo == "11":
		usr=open(".tools/uip.aex","w")
		usr.write("79")
		usr.close()
		inst()
	elif Toolo == "12":
		usr=open(".tools/uip.aex","w")
		usr.write("47")
		usr.close()
		inst()
	elif Toolo == "13":
		usr=open(".tools/uip.aex","w")
		usr.write("117")
		usr.close()
		inst()
	elif Toolo == "14":
		usr=open(".tools/uip.aex","w")
		usr.write("134")
		usr.close()
		inst()
	elif Toolo == "15":
		usr=open(".tools/uip.aex","w")
		usr.write("135")
		usr.close()
		inst()
	elif Toolo == "16":
		usr=open(".tools/uip.aex","w")
		usr.write("136")
		usr.close()
		inst()
	elif Toolo == "00" or Toolo == "back":
		pass
	else:
		print ("\033[01;34m\007\n error : \033[01;37m\'"+Toolo+"\' \033[01;31minvalid option !!!")
		sleep(1)
		cat1()
