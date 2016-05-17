# Arduino-Serial-LEDs
This is a simple header with a test implementation in an Arduino sketch to control analog RGB LEDs. It uses object-oriented-programming with a simple LedString class. Many thanks to [Nick Sevens](http://www.nicksevens.com/) for his Kodi/Serial code: the basis for this project's serial communication! This project uses [pyserial](https://github.com/pyserial/pyserial) for serial communication on the python side of things.

## __Install:__

1. Upload main.ino to the Arduino after setting the correct PWM pins for your specific board for the strings' class declarations.
2. Find some way to control the lights from the pins. I like the tutorial from Adafruit [found here](https://learn.adafruit.com/rgb-led-strips/overview).
3. Either place the folder "service.arduinoconnector" into Kodi's _addons_ folder or install from the zip file service.arduinoconnector.zip inside Kodi's addon manager itself. Personally, I recommend the direct folder option.
4. Take note of the serial port that the Arduino is connected to. The easiest way is inside the Arduino IDE on the bottom right.
5. Navigate to the addon inside Kodi and click _Configure_. Enter in the serial port.
6. All done! You may have to restart Kodi.

## __Updates:__ ##

#### The Arduino part is out of beta!
The Arduino code is consistent with no apparent errors. ~~_The Kodi/Python code is still in beta and is currently unfinished_.~~

#### The Kodi part is out of beta!
The Kodi code is bug-free! Will improve functionality in future versions.

## __Usage:__
The Arduino can be controlled through serial by sending 'f' to start fade, 'o' for off, 'd' for dim, 'i' to change intensity, 'l' to flash white, and 'u' to force an update for the fade values. The Kodi addon sends the appropriate commands to fade/dim/shut down the LEDs at appropriate times. The lights will be fading unless a video is playing when they will dim or when Kodi is asked to shutdown, when the strips will turn off.


## Upcoming features:
- [x] Implementation of serial to control actions taken by the Arduino
- [x] A [Kodi](https://kodi.tv) addon script to control the Arduino through serial
- [x] Greater serial functionality
- [ ] Kodi-side improvements
