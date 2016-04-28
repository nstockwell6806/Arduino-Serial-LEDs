import xbmc
import time
import serial

class XBMCPlayer(xbmc.Player):
    def __init__(self, *args):
        pass
 
    def onPlayBackStarted(self):
        ledDim()
 
    def onPlayBackPaused(self):
        ledFade()
 
    def onPlayBackResumed(self):
        ledDim()
 
    def onPlayBackEnded(self):
        ledFade()
 
    def onPlayBackStopped(self):
        ledFade()
 
player = XBMCPlayer()
monitor = xbmc.Monitor()
con = serial.Serial("", 9600)

def ledDim()
    con.write("d".encode('ASCII'))

def ledFade()
    con.write("f".encode('ASCII'))

def ledOff()
    con.write("o".encode('ASCII'))
 
while True:
    if monitor.waitForAbort(1):
        ledOff()
        break
