import xbmc
import xbmcaddon
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
serial_connect = xbmcaddon.Addon()
arduino_port = serial_connect.getSetting('serial_port')
con = serial.Serial(arduino_port, 9600)

def ledDim():
    if xbmc.Player().isPlayingVideo():
        con.write("d".encode('ASCII'))

def ledFade():
    con.write("f".encode('ASCII'))

def ledOff():
    con.write("o".encode('ASCII'))

ledFade(): 
while True:
    if monitor.waitForAbort(1):
        ledOff()
        break
