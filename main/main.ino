#include "header.h"
LedString mainString (0, 7, 8, 9);          //setup main string running on channel 0


void setup() {
  Serial.begin(9600);
  Serial.println("Reset");
  mainString.changeVal(0, 'r', 0, 'g', 0, 'b');
  randomSeed(analogRead(0));
}


void loop() {
  readSerial();					    //read serial buffer & change mode
  runInstructions();				//run the corresponding mode
  delay(40);
  if(i > 255)
  {
    Serial.println("Error");
    digitalWrite(13, LOW);
    delay(200);
    digitalWrite(13, HIGH);
  }
  if(i > 300)
  {
    runFlash = false;
    shutDown = true;
    newInstructions = true;
  }
}




void runInstructions()
{
  if (runFlash)
  {
    mainString.flash(255, 255, 255);
    runFlash = false;
    newInstructions = true;
  }
  if (fading)
  {
    mainString.fade();
  }
  else if (shutDown && newInstructions)                                  //only run shutdown if not already shutdown
  {
    mainString.shutDown();
    newInstructions = false;
  }
  else if (not(shutDown) && newInstructions)                             //only run dim if not already dimmed
  {
    mainString.dim();
    newInstructions = false;
  }
}
