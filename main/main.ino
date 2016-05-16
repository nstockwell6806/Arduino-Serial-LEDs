#include "header.h"
LedString String1 (0, 7, 8, 9);          //setup string 1 running on channel 0


void setup() {
  Serial.begin(9600);
  Serial.println("Reset");
}


void loop() {
  readSerial();					    //read serial buffer & change mode
  runInstructions();				//run the corresponding mode
  delay(40);
}




void runInstructions()
{
  if (fading)
  {
    String1.fade();

  }
  else if (shutDown && newInstructions)                                  //only run shutdown if there are new instructions
  {
    String1.shutDown();
//    Serial.println("Shutting down string 1");
    newInstructions = false;
  }
  else if (not(shutDown) && newInstructions)                             //only run dim if there are new instructions
  {
    String1.dim();
//    Serial.println("Setting string to dim");
    newInstructions = false;
  }
}
