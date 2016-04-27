import xbmc
import time
 
class XBMCPlayer(xbmc.Player):
    def __init__(self, *args):
        pass
 
    def onPlayBackStarted(self):
        xbmc.log("Playback started - LED ON")
 
    def onPlayBackPaused(self):
        xbmc.log("Playback paused - LED OFF")
 
    def onPlayBackResumed(self):
        xbmc.log("Playback resumed - LED ON")
 
    def onPlayBackEnded(self):
        xbmc.log("Playback ended - LED OFF")
 
    def onPlayBackStopped(self):
        xbmc.log("Playback stopped - LED OFF")
 
player = XBMCPlayer()
 
monitor = xbmc.Monitor()
 
while True:
    if monitor.waitForAbort(1): # Sleep/wait for abort for 1 second.
        break # Abort was requested while waiting. Exit the while loop.
