#include "header.h"

void setup() {
Serial.begin(9600);
setPins( 0, 7, 8, 9 );          //initialize pins 7, 8, and 9 to channel 0
LedString String1 (0);          //setup string 1 running on channel 0
}

void loop() {
String1.fade();
}
