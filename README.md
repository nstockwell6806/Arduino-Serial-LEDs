# Arduino-Serial-LEDs
This is a simple header with a test implementation in an Arduino sketch to control LEDs. It uses object-oriented-programming with a simple LedString class. Many thanks to [Nick Sevens](http://www.nicksevens.com/) for his Kodi/Serial code!

## __Notes:__ ##

#### The Arduino part is out of beta!
The Arduino code is consistent with no apparent errors. _The Kodi/Python code is still in beta and is currently unfinished_.

#### Usage:
The Arduino can be controlled through serial by sending 'f' to start fade, 'o' for off, 'd' for dim, 'i' to change intensity, 'l' to flash white, and 'u' to force an update for the fade values.


## Upcoming features:
- [x] Implementation of serial to control actions taken by the Arduino
- [x] A [Kodi](https://kodi.tv) addon script to control the Arduino through serial
- [x] Greater serial functionality
- [ ] Kodi-side improvements
